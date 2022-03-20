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

enum DATA_TYPE {UNKNOWN, UNSIGNED8, UNSIGNED16, UNSIGNED32, UNSIGNED64, SIGNED8, SIGNED16, SIGNED32, SIGNED64};

typedef struct DATA_NODE {
	uint32_t timestamp;
	uint16_t id;
	enum DATA_TYPE type;
	void* data;
	struct DATA_NODE* next;
} DATA_NODE;

#endif /* INC_DLM_H_ */
