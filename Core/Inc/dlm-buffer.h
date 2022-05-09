/*
 * dlm-buffer.h
 *
 *  Created on: May 9, 2022
 *      Author: jonathan
 */

#ifndef INC_DLM_BUFFER_H_
#define INC_DLM_BUFFER_H_

#include <stdint.h>
#include "dlm.h"

// swap a ping-pong buffer
// PARAMETERS:
// buffer: ping-pong buffer to swap
// RETURNS:
// buffer fill level just before swap
uint32_t swap_buffer(PPBuff* buffer);

// append the standard packet structure to a buffer
// PARAMETERS:
// buffer: the ping-pong buffer to append to
// timestamp: 4 byte timestamp in ms
// id: 2 byte data ID
// data: address of the data
// dataSize: size of the data in bytes
void append_packet(PPBuff* buffer, uint32_t timestamp, uint16_t id, void* data, uint8_t dataSize);

// escapes a byte if necessary then appends it to the provided buffer
// PARAMETERS:
// buffer: the ping-pong buffer to append to
// byte: byte to append
void append_byte(PPBuff* buffer, uint8_t byte);

#endif /* INC_DLM_BUFFER_H_ */
