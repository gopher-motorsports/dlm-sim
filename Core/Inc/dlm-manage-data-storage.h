/*
 * dlm-manage-data-storage.h
 *
 *  Created on: Apr 24, 2022
 *      Author: jonathan
 */

#ifndef INC_DLM_MANAGE_DATA_STORAGE_H_
#define INC_DLM_MANAGE_DATA_STORAGE_H_

#include <stdint.h>
#include "dlm.h"

// attempt to mount the SD card and open a file
// RETURNS
// 0 if successful, else 1
uint8_t sd_init(void);

// unmount and close the file in case of an error
void sd_deinit(void);

// attempt to write data to an open file
// PARAMETERS:
// buffer: storage ping-pong buffer
// RETURNS:
// 0 if successful, else 1
uint8_t store_data(PPBuff* buffer);

#endif /* INC_DLM_MANAGE_DATA_STORAGE_H_ */
