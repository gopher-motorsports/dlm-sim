/*
 * dlm-generate-data.c
 *
 *  Created on: Mar 10, 2022
 *      Author: jonathan
 */

#include "dlm-generate-data.h"
#include "dlm-util.h"

void generate_packet(PPBuff* buffer) {
    static uint32_t packetCount = 0;

    if (buffer->full) {
    	// write buffer is full
    	// check if we're ready to ping-pong
    	if (buffer->flushed) {
    		buffer->write = !buffer->write;
    		buffer->written = 0;
    		buffer->full = 0;
    		buffer->flushed = 0;
    	} else return;
    }

    uint32_t timestamp = packetCount;
    uint16_t id = 0x0001;
    uint8_t data = 0x69;

    buffer->written = append_packet(buffer->rows[buffer->write], buffer->written, timestamp, id, &data, sizeof(data));
    packetCount++;

    if (buffer->written == BUFFER_SIZE) {
    	buffer->full = 1;
    }
}
