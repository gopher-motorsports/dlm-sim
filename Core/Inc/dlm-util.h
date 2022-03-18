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

uint8_t packetize_node(DATA_INFO_NODE* node, uint8_t packet[]);
uint8_t append_byte(uint8_t packet[], uint8_t packetLength, uint8_t byte);
double convert_data_to_dpf(DATA_INFO_NODE* node);

#endif /* INC_DLM_UTIL_H_ */
