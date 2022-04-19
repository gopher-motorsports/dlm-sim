/*
 * dlm.c
 *
 *  Created on: Mar 17, 2022
 *      Author: jonathan
 */

#include "dlm.h"
#include "main.h"
#include "cmsis_os2.h"

void dlm_init(void) {
}

void dlm_manage_data_acquisition(void) {
	HAL_GPIO_TogglePin(GLED_GPIO_Port, GLED_Pin);
    osDelay(100);
}

void dlm_manage_data_storage(void) {
	HAL_GPIO_TogglePin(BLED_GPIO_Port, BLED_Pin);
    osDelay(1000);
}

void dlm_manage_data_broadcast(void) {
    HAL_GPIO_TogglePin(RLED_GPIO_Port, RLED_Pin);
    osDelay(1000);
}
