/*
 * dlm-util.h
 *
 *  Created on: Mar 13, 2022
 *      Author: jonathan
 */

#ifndef INC_DLM_UTIL_H_
#define INC_DLM_UTIL_H_

#include <stdint.h>

// escapes a byte if necessary then appends it to the provided buffer
// PARAMETERS:
// buffer: the byte buffer to append to
// size: current size of the buffer in bytes
// byte: byte to append
// RETURNS:
// the new buffer size
uint32_t append_byte(uint8_t buffer[], uint32_t size, uint8_t byte);

// append the standard packet structure to a buffer
// PARAMETERS:
// buffer: the byte buffer to append to
// size: current size of the buffer in bytes
// timestamp: 4 byte timestamp in ms
// id: 2 byte data ID
// data: address of the data
// dataSize: size of the data in bytes
// RETURNS:
// the new buffer size
uint32_t append_packet(uint8_t buffer[], uint32_t size, uint32_t timestamp, uint16_t id, void* data, uint8_t dataSize);

#endif /* INC_DLM_UTIL_H_ */
