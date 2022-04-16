/*
 * dlm-generate-data.c
 *
 *  Created on: Mar 10, 2022
 *      Author: jonathan
 */

#include "dlm-generate-data.h"
#include "cmsis_os2.h"
#include "dlm-util.h"
#include "main.h"

void generate_packet(PPBuff* buffer) {
    static uint32_t packetCount = 0;

    uint32_t timestamp = packetCount;
    uint16_t id = 0x0001;
    uint8_t data = 0x69;

    osMutexAcquire(bufferMutexHandle, osWaitForever);
    buffer->writeSize = append_packet(buffer->buffs[buffer->write], buffer->writeSize, timestamp, id, &data, sizeof(data));
    packetCount++;
    osMutexRelease(bufferMutexHandle);
}
