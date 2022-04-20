/*
 * dlm-util.c
 *
 *  Created on: Mar 13, 2022
 *      Author: jonathan
 */

#include "dlm-util.h"
#include "dlm.h"

uint32_t append_byte(uint8_t buffer[], uint32_t size, uint8_t byte) {
    uint32_t sz = size;

    // check for a control byte
    if (byte == START_BYTE || byte == ESCAPE_BYTE) {
        // append an escape byte
        buffer[sz] = ESCAPE_BYTE;
        sz++;
        // append the desired byte, escaped
        buffer[sz] = byte ^ 0x20;
        sz++;
    } else {
    	// append the raw byte
        buffer[sz] = byte;
        sz++;
    }

    return sz;
}

uint32_t append_packet(uint8_t buffer[], uint32_t size, uint32_t timestamp, uint16_t id, void* data, uint8_t dataSize) {
	uint32_t sz = size;
    uint8_t i;
    uint8_t* bytes;

    buffer[sz] = START_BYTE;
    sz++;

    // append components with MSB first
    bytes = (uint8_t*) &(timestamp);
    for (i = sizeof(timestamp); i > 0; i--) {
        sz = append_byte(buffer, sz, bytes[i - 1]);
    }

    bytes = (uint8_t*) &(id);
    for (i = sizeof(id); i > 0; i--) {
		sz = append_byte(buffer, sz, bytes[i - 1]);
	}

    bytes = (uint8_t*) data;
    for (i = dataSize; i > 0; i--) {
		sz = append_byte(buffer, sz, bytes[i - 1]);
	}

    return sz;
}
