/*
 * dlm-util.h
 *
 *  Created on: Mar 13, 2022
 *      Author: jonathan
 */

#ifndef INC_DLM_UTIL_H_
#define INC_DLM_UTIL_H_

#include <stdint.h>
#include "dlm.h"

uint8_t get_node_data_size(enum DATA_TYPE type);
uint8_t set_node_data(DATA_NODE* node, void* data);
uint8_t packetize_node(DATA_NODE* node, uint8_t packet[]);
uint8_t append_byte(uint8_t packet[], uint8_t packetLength, uint8_t byte);

#endif /* INC_DLM_UTIL_H_ */
