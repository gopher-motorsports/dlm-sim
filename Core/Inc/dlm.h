/*
 * dlm.h
 *
 *  Created on: Mar 17, 2022
 *      Author: jonathan
 */

#ifndef INC_DLM_H_
#define INC_DLM_H_

#include <stdint.h>

#define START_BYTE 0x7e

typedef struct PPBuff {
	uint8_t* buffs[2]; // pointers to 2 byte buffers
	uint8_t write; // index of the write buffer (0 or 1)
	uint8_t writeSize; // # of bytes in write buffer
	uint8_t flushSize; // # of bytes ready to be flushed
} PPBuff;

void dlm_init(void);
void dlm_manage_data_acquisition(void);
void dlm_manage_data_storage(void);
void dlm_manage_data_broadcast(void);

#endif /* INC_DLM_H_ */
