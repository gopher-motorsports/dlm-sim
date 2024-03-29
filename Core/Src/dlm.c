/*
 * dlm.c
 *
 *  Created on: Mar 17, 2022
 *      Author: jonathan
 */

#include "dlm.h"
#include "main.h"
#include "cmsis_os2.h"
#include "fatfs.h"
#include "dlm-manage-data-acquisition.h"
#include "dlm-manage-data-broadcast.h"
#include "dlm-manage-data-storage.h"

// create the buffer for SD card data
uint8_t storageBuff1[STORAGE_BUFFER_SIZE];
uint8_t storageBuff2[STORAGE_BUFFER_SIZE];
PPBuff storageBuffer = {
		.size = STORAGE_BUFFER_SIZE,
		.mutex = NULL,
		.buffs = {storageBuff1, storageBuff2},
		.write = 0,
		.fill = 0
};

// create the buffer for telemetry data
uint8_t broadcastBuff1[BROADCAST_BUFFER_SIZE];
uint8_t broadcastBuff2[BROADCAST_BUFFER_SIZE];
PPBuff broadcastBuffer = {
		.size = BROADCAST_BUFFER_SIZE,
		.mutex = NULL,
		.buffs = {broadcastBuff1, broadcastBuff2},
		.write = 0,
		.fill = 0
};

void dlm_init(void) {
	// assign mutexes
	storageBuffer.mutex = mutex_storage_bufferHandle;
	broadcastBuffer.mutex = mutex_broadcast_bufferHandle;

	// clear transfer flag initially
	osThreadFlagsSet(BroadcastDataHandle, FLAG_TRANSFER_DONE);
}

void dlm_manage_data_acquisition(void) {
	HAL_GPIO_TogglePin(GLED_GPIO_Port, GLED_Pin);

	// in a real DLM this is where we would service the CAN hardware and request data buckets
	// GopherCAN would then make the data available in memory

	// instead generate some dummy data
	generate_data(&storageBuffer, &broadcastBuffer);

    osDelay(THREAD_DELAY_ACQUIRE_DATA);
}

void dlm_manage_data_storage(void) {
	HAL_GPIO_TogglePin(BLED_GPIO_Port, BLED_Pin);

	static uint8_t sdReady = 0;
	uint8_t err = 0;

	if (!sdReady) {
		// attempt to initialize the SD card
		err = sd_init();
		if (err) sd_deinit();
		else sdReady = 1;
	}

	if (sdReady) {
		err = store_data(&storageBuffer);
		if (err) {
			// write failed
			sd_deinit();
			sdReady = 0;
		}
	}

    osDelay(THREAD_DELAY_STORE_DATA);
}

void dlm_manage_data_broadcast(void) {
    HAL_GPIO_TogglePin(RLED_GPIO_Port, RLED_Pin);

	// wait for the previous transfer to complete
	osThreadFlagsWait(FLAG_TRANSFER_DONE, osFlagsWaitAny, 0);

    start_broadcast(&broadcastBuffer);

    osDelay(THREAD_DELAY_BROADCAST_DATA);
}
