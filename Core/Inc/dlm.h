/*
 * dlm.h
 *
 *  Created on: Mar 17, 2022
 *      Author: jonathan
 */

#ifndef INC_DLM_H_
#define INC_DLM_H_

#include <stdint.h>

void dlm_init(void);
void dlm_generate_data(void);
void dlm_transmit_data(void);
void dlm_save_data(void);

#define START_BYTE 0x7e

#define BUFFER_SIZE 32

typedef struct PPBuff {
	uint8_t* buffs[2]; // pointers to 2 byte buffers
	uint8_t write; // index of the write buffer (0 or 1)
	uint8_t writeSize; // # of bytes in write buffer
	uint8_t flushSize; // # of bytes ready to be flushed
} PPBuff;

#endif /* INC_DLM_H_ */
