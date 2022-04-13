/*
 * dlm-generate-data.c
 *
 *  Created on: Mar 10, 2022
 *      Author: jonathan
 */

#include "dlm-generate-data.h"
#include "cmsis_os2.h"
#include "dlm-util.h"

void generate_packet(PPBuff* buffer) {
    static uint32_t packetCount = 0;

    if (buffer->writeFull) {
    	// check if we're ready to ping-pong
    	if (buffer->flushed) {
    		osKernelLock();
    		buffer->flushed = 0;
    		buffer->flushSize = buffer->writeSize;
    		buffer->writeSize = 0;
    		buffer->writeFull = 0;
    		buffer->write = !buffer->write;
    		osKernelUnlock();
    	} else return;
    }

    uint32_t timestamp = packetCount;
    uint16_t id = 0x0001;
    uint8_t data = 0x69;

    buffer->writeSize = append_packet(buffer->rows[buffer->write], buffer->writeSize, timestamp, id, &data, sizeof(data));
    packetCount++;

    if (buffer->writeSize >= BUFFER_SIZE) {
    	buffer->writeFull = 1;
    }
}
