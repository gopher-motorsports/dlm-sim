/*
 * dlm-manage-data-acquisition.c
 *
 *  Created on: Apr 19, 2022
 *      Author: jonathan
 */

#include "dlm-manage-data-acquisition.h"

void append_packet(PPBuff* buffer, uint32_t bufferSize, uint32_t timestamp, uint16_t id, void* data, uint8_t dataSize) {
	// calculate the packet size and available buffer space
	uint8_t packetSize = sizeof(timestamp) + sizeof(id) + dataSize;
	uint32_t freeSpace = bufferSize - buffer->fill;
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
