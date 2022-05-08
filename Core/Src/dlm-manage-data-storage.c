/*
 * dlm-manage-data-storage.c
 *
 *  Created on: Apr 24, 2022
 *      Author: jonathan
 */

#include "dlm-manage-data-storage.h"
#include "fatfs.h"
#include "main.h"

uint8_t sd_init(void) {
	FRESULT res;

	// check if the sd card is inserted (0 if inserted)
	if (HAL_GPIO_ReadPin(SDMMC_CD_GPIO_Port, SDMMC_CD_Pin)) return 1;

	// mount
	res = f_mount(&SDFatFS, SDPath, 1);
	if (res != FR_OK) return 1;

	// open a file
	res = f_open(&SDFile, "data.dat", FA_CREATE_ALWAYS | FA_WRITE);
	if (res != FR_OK) return 1;

	return 0;
}

void sd_deinit(void) {
	f_mount(NULL, SDPath, 0);
	f_close(&SDFile);
}

uint8_t store_data(PPBuff* buffer) {
	FRESULT res;

	osMutexAcquire(mutex_storage_bufferHandle, osWaitForever);
	// ping-pong the buffer
	uint32_t transferSize = buffer->fill;
	buffer->fill = 0;
	buffer->write = !buffer->write;
	osMutexRelease(mutex_storage_bufferHandle);

	// write data
	res = f_write(&SDFile, buffer->buffs[!buffer->write], transferSize, NULL);
	if (res != FR_OK) return 1;

	// flush cached data
	res = f_sync(&SDFile);
	if (res != FR_OK) return 1;

	return 0;
}
