/*
 * dlm-save-data.c
 *
 *  Created on: Mar 13, 2022
 *      Author: jonathan
 */

#include "dlm-save-data.h"
#include "cmsis_os2.h"

void store_data(PPBuff* buffer) {
    if (buffer->full) {
    	osDelay(5000); // dump buffer somewhere...
    	buffer->flushed = 1;
    }
}
