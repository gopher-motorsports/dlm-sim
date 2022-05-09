/*
 * dlm-buffer.c
 *
 *  Created on: May 9, 2022
 *      Author: jonathan
 */

#include "dlm-buffer.h"

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
	osMutexAcquire(buffer->mutex, osWaitForever);

	// calculate the packet size and available buffer space
	uint8_t packetSize = sizeof(timestamp) + sizeof(id) + dataSize;
	uint32_t freeSpace = buffer->size - buffer->fill;
	if (packetSize > freeSpace) {
		// this packet won't fit
		return;
	}

	// find the write buffer
	uint8_t* buff = buffer->buffs[buffer->write];

    uint8_t i;
    uint8_t* bytes;

    // insert start byte
    buff[buffer->fill++] = START_BYTE;

    // append components with MSB first
    bytes = (uint8_t*) &(timestamp);
    for (i = sizeof(timestamp); i > 0; i--) {
        append_byte(buffer, bytes[i - 1]);
    }

    bytes = (uint8_t*) &(id);
    for (i = sizeof(id); i > 0; i--) {
		append_byte(buffer, bytes[i - 1]);
	}

    bytes = (uint8_t*) data;
    for (i = dataSize; i > 0; i--) {
		append_byte(buffer, bytes[i - 1]);
	}

    osMutexRelease(buffer->mutex);
}

void append_byte(PPBuff* buffer, uint8_t byte) {
	// find the write buffer
	uint8_t* buff = buffer->buffs[buffer->write];

    // check for a control byte
    if (byte == START_BYTE || byte == ESCAPE_BYTE) {
        // append an escape byte
    	buff[buffer->fill++] = ESCAPE_BYTE;
        // append the desired byte, escaped
    	buff[buffer->fill++] = byte ^ 0x20;
    } else {
    	// append the raw byte
    	buff[buffer->fill++] = byte;
    }
}
