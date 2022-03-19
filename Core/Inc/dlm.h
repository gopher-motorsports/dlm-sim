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

void dlm_generate_data(void);
void dlm_transmit_data(void);
void dlm_save_data(void);

typedef struct DATA_NODE {
	uint32_t timestamp;
	uint16_t id;
	void* data;
	struct DATA_NODE* next;
} DATA_NODE;

#endif /* INC_DLM_H_ */
