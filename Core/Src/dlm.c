/*
 * dlm.c
 *
 *  Created on: Mar 17, 2022
 *      Author: jonathan
 */

#include <stdlib.h>
#include "dlm.h"
#include "main.h"
#include "cmsis_os2.h"
#include "dlm-generate-data.h"
#include "dlm-save-data.h"
#include "dlm-transmit-data.h"

// dlm.c contains the high level duties of the data logging module
// the functions here are called by RTOS task handlers and their implementation is abstracted to similarly-named files

// buffers have padding beyond the "max size" to prevent packets being cut off
uint8_t row1[BUFFER_SIZE + MAX_PACKET_SIZE];
uint8_t row2[BUFFER_SIZE + MAX_PACKET_SIZE];
PPBuff buffer = {
		.rows = {row1, row2},
		.write = 0,
		.writeSize = 0,
		.writeFull = 0,
		.flushSize = 0,
		.flushed = 1,
};

// any necessary initialization
void dlm_init(void) {
}

// for simulation purposes, generate random data nodes and append them to the buffer
void dlm_generate_data(void) {
    HAL_GPIO_TogglePin(BLED_GPIO_Port, BLED_Pin);

    generate_packet(&buffer);

    // this task should run every 100ms
    osDelay(100);
}

// step through the buffer, packetize data nodes, and send them to an Xbee
void dlm_transmit_data(void) {
    HAL_GPIO_TogglePin(GLED_GPIO_Port, GLED_Pin);

    transmit_packets(&buffer);

    // this task should run every 500ms
    osDelay(500);
}

// this is where we would write the buffer data to storage
// in the simulation, we just clear the buffer
void dlm_save_data(void) {
    HAL_GPIO_TogglePin(RLED_GPIO_Port, RLED_Pin);

    store_data(&buffer);

    // this task should run every 2s
    osDelay(2000);
}
