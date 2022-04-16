/*
 * dlm-save-data.c
 *
 *  Created on: Mar 13, 2022
 *      Author: jonathan
 */

#include "dlm-save-data.h"
#include "cmsis_os2.h"
#include "main.h"

void store_data(PPBuff* buffer) {
	// dump read buffer somewhere...
	// buffer->buffs[!buffer->write] from 0 to buffer->flushSize
	osDelay(10);

	// swap buffers
	osMutexAcquire(bufferMutexHandle, osWaitForever);
	buffer->flushSize = buffer->writeSize;
	buffer->writeSize = 0;
	buffer->write = !buffer->write;
	osMutexRelease(bufferMutexHandle);
}
