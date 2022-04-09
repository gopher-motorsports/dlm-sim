/*
 * dlm-util.h
 *
 *  Created on: Mar 13, 2022
 *      Author: jonathan
 */

#ifndef INC_DLM_UTIL_H_
#define INC_DLM_UTIL_H_

#include <stdint.h>

uint8_t append_byte(uint8_t buffer[], uint8_t sz, uint8_t byte);
uint8_t append_packet(uint8_t buffer[], uint8_t sz, uint32_t timestamp, uint16_t id, void* data, uint8_t dataSize);

#endif /* INC_DLM_UTIL_H_ */
