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
#include "dlm-buffer.h"

void start_broadcast(PPBuff* buffer) {
	uint32_t transferSize = swap_buffer(buffer);
	HAL_UART_Transmit_DMA(&huart7, buffer->buffs[!buffer->write], transferSize);
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef* huart) {
	// tell the broadcast thread that the transfer is complete
	osThreadFlagsSet(BroadcastDataHandle, FLAG_TRANSFER_DONE);
}
