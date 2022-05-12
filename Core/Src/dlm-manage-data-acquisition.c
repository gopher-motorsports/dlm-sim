/*
 * dlm-manage-data-acquisition.c
 *
 *  Created on: Apr 19, 2022
 *      Author: jonathan
 */

#include "dlm-manage-data-acquisition.h"
#include "dlm-buffer.h"

void generate_data(PPBuff* storageBuffer, PPBuff* broadcastBuffer) {
	static uint16_t packetNum = 0;

	uint32_t timestamp = osKernelGetTickCount();
	uint16_t id = packetNum;
	uint32_t data = 0x12345678;

	// append the data in packet form
	append_packet(storageBuffer, timestamp, id, &data, sizeof(data));
	append_packet(broadcastBuffer, timestamp, id, &data, sizeof(data));

	packetNum++;
}
