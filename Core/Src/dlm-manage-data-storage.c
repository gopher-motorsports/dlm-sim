/*
 * dlm-manage-data-storage.c
 *
 *  Created on: Apr 24, 2022
 *      Author: jonathan
 */

#include "dlm-manage-data-storage.h"

uint8_t sd_init(void) {
	// mount

	// open a new file

	return 0;
}

uint8_t store_data(PPBuff* buffer) {
	// ping-pong the buffer
	uint32_t transferSize = buffer->writeSize;
	buffer->writeSize = 0;
	buffer->write = !buffer->write;

	// write data

	return 0;
}
