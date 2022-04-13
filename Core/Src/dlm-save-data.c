/*
 * dlm-save-data.c
 *
 *  Created on: Mar 13, 2022
 *      Author: jonathan
 */

#include "dlm-save-data.h"
#include "cmsis_os2.h"

void store_data(PPBuff* buffer) {
    if (!buffer->flushed) {
    	// dump read buffer somewhere...
    	// buffer->rows[!buffer->write] from 0 to buffer->flushSize
    	osDelay(5000);

    	buffer->flushed = 1;
    }
}
