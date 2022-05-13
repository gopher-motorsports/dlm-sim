/*
 * dlm-buffer.c
 *
 *  Created on: May 9, 2022
 *      Author: jonathan
 */

#include "dlm-buffer.h"
#include <string.h>

uint32_t swap_buffer(PPBuff* buffer) {
	osMutexAcquire(buffer->mutex, osWaitForever);
	// ping-pong the buffer
	uint32_t fill = buffer->fill;
	buffer->fill = 0;
	buffer->write = !buffer->write;
	osMutexRelease(buffer->mutex);

	return fill;
}

void append_packet(PPBuff* buffer, uint32_t timestamp, uint16_t id, void* data, uint8_t dataSize) {
	uint32_t freeSpace = buffer->size - buffer->fill;
	if (MAX_PACKET_SIZE > freeSpace) {
		// this packet might not fit
		return;
	}

	uint8_t packet[MAX_PACKET_SIZE] = {0};
	uint8_t packetFill = 0;

	packet[packetFill++] = START_BYTE;
	packetFill = append_value(packet, packetFill, &timestamp, sizeof(timestamp));
	packetFill = append_value(packet, packetFill, &id, sizeof(id));
	packetFill = append_value(packet, packetFill, data, dataSize);

	// minimize packet size
	uint8_t packetSize = MAX_PACKET_SIZE;
	if (packetFill <= 16) packetSize = 16;
	else if (packetFill <= 24) packetSize = 24;

	osMutexAcquire(buffer->mutex, osWaitForever);
	memcpy(&buffer->buffs[buffer->write][buffer->fill], packet, packetSize);
	buffer->fill += packetSize;
	osMutexRelease(buffer->mutex);
}

uint8_t append_value(uint8_t packet[], uint8_t fill, void* value, uint8_t size) {
	// append the value byte-by-byte (big endian)
	uint8_t i;
	uint8_t* bytes = (uint8_t*) value;
	for (i = size; i > 0; i--) {
		uint8_t byte = bytes[i - 1];
		// check for a control byte
		if (byte == START_BYTE || byte == ESCAPE_BYTE) {
			// append an escape byte
			packet[fill++] = ESCAPE_BYTE;
			// append the desired byte, escaped
			packet[fill++] = byte ^ 0x20;
		} else {
			// append the raw byte
			packet[fill++] = byte;
		}
	}

	return fill;
}
