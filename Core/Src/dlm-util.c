/*
 * dlm-util.c
 *
 *  Created on: Mar 13, 2022
 *      Author: jonathan
 */

#include "dlm-util.h"
#include "dlm.h"

// dlm-util.c contains functions that may be used across DLM features

// escapes a byte if necessary, then appends it to the buffer
// PARAMETERS:
// - buffer: the buffer to append to
// - sz: current size of the buffer
// - byte: byte to append
// RETURNS: the new buffer size
uint8_t append_byte(uint8_t buffer[], uint8_t sz, uint8_t byte) {
    uint8_t size = sz;

    // check for a control byte
    if (byte == 0x7e || byte == 0x7d) {
        // append an escape byte
        buffer[size] = 0x7d;
        size++;
        // append the escaped byte
        buffer[size] = byte ^ 0x20;
        size++;
    } else {
    	// append the raw byte
        buffer[size] = byte;
        size++;
    }

    return size;
}

// takes packet components, breaks them into bytes, and appends them to a buffer
// PARAMETERS:
// - buffer: the buffer to append to
// - sz: current size of buffer
// - timestamp: in ms
// - id
// - data: pointer to the data
// - dataSize: size of the data in bytes
// RETURNS: the new buffer size
uint8_t append_packet(uint8_t buffer[], uint8_t sz, uint32_t timestamp, uint16_t id, void* data, uint8_t dataSize) {
	uint8_t size = sz;
    uint8_t i;
    uint8_t* bytes;

    buffer[size] = (uint8_t) START_BYTE;
    size++;

    for (i = sizeof(timestamp); i > 0; i--) {
        bytes = (uint8_t*) &(timestamp);
        size = append_byte(buffer, size, bytes[i - 1]);
    }

    for (i = sizeof(id); i > 0; i--) {
		bytes = (uint8_t*) &(id);
		size = append_byte(buffer, size, bytes[i - 1]);
	}

    for (i = dataSize; i > 0; i--) {
		bytes = (uint8_t*) data;
		size = append_byte(buffer, size, bytes[i - 1]);
	}

    return size;
}
