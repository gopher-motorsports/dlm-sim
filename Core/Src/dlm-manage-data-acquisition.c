/*
 * dlm-manage-data-acquisition.c
 *
 *  Created on: Apr 19, 2022
 *      Author: jonathan
 */

#include "dlm-manage-data-acquisition.h"
#include <stdint.h>
#include "cmsis_os2.h"
#include "dlm-util.h"

void generate_data(PPBuff* storageBuffer, PPBuff* telemetryBuffer) {
	// generate some dummy data
	static uint32_t packetNum = 0;
	uint32_t timestamp = packetNum;
	uint16_t id = 1;
	uint8_t data = 0x69;

	// append the data point in packet form
	osKernelLock(); // TODO: figure out how to do this without locking
	storageBuffer->writeSize = append_packet(storageBuffer->buffs[storageBuffer->write], storageBuffer->writeSize, timestamp, id, &data, sizeof(data));
	telemetryBuffer->writeSize = append_packet(telemetryBuffer->buffs[telemetryBuffer->write], telemetryBuffer->writeSize, timestamp, id, &data, sizeof(data));
	osKernelUnlock();

	packetNum++;

	if (storageBuffer->writeSize >= STORAGE_BUFFER_SIZE) {
		// oops the storage buffer overflowed
		storageBuffer->writeSize = 0;
	}

	if (telemetryBuffer->writeSize >= TELEMETRY_BUFFER_SIZE) {
		// oops the telemetry buffer overflowed
		telemetryBuffer->writeSize = 0;
	}
}
