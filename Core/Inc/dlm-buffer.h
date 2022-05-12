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

// append a packet to a ping-pong buffer
// PARAMETERS:
// buffer: the ping-pong buffer to append to
// timestamp: 4 byte timestamp in ms
// id: 2 byte data ID
// data: address of the data
// dataSize: size of the data in bytes
void append_packet(PPBuff* buffer, uint32_t timestamp, uint16_t id, void* data, uint8_t dataSize);

// escapes bytes if necessary and append a value to a packet
// PARAMETERS:
// packet: the byte array being built
// fill: current packet fill level
// value: address of the value
// size: size of the value in bytes
// RETURNS:
// # new packet fill level
uint8_t append_value(uint8_t packet[], uint8_t fill, void* value, uint8_t size);

#endif /* INC_DLM_BUFFER_H_ */
