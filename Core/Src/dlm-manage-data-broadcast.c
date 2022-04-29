/*
 * dlm-manage-data-broadcast.c
 *
 *  Created on: Apr 19, 2022
 *      Author: jonathan
 */

#include "dlm-manage-data-broadcast.h"
#include "stm32f7xx_hal.h"
#include "main.h"
#include "cmsis_os2.h"

void start_broadcast(PPBuff* buffer) {
	osMutexAcquire(mutex_broadcast_bufferHandle, osWaitForever);
	// ping-pong the buffer
	uint32_t transferSize = buffer->fill;
	buffer->fill = 0;
	buffer->write = !buffer->write;
	osMutexRelease(mutex_broadcast_bufferHandle);

	// start transfer
	HAL_UART_Transmit_DMA(&huart2, buffer->buffs[!buffer->write], transferSize);
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef* huart) {
	// tell the broadcast thread that the transfer is complete
	osThreadFlagsSet(BroadcastDataHandle, FLAG_TRANSFER_DONE);
}
