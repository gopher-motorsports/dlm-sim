/*
 * dlm-transmit-data.c
 *
 *  Created on: Mar 10, 2022
 *      Author: jonathan
 */

#include "dlm-transmit-data.h"
#include "dlm.h"
#include "main.h"

void transmit_packets(PPBuff* buffer) {
	if (!buffer->transmissionDone) {
		HAL_UART_Transmit(&huart2, buffer->rows[!buffer->write], buffer->flushSize, HAL_MAX_DELAY);

		buffer->transmissionDone = 1;
	}
}
