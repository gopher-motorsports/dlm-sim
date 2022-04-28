/*
 * dlm-manage-data-acquisition.h
 *
 *  Created on: Apr 19, 2022
 *      Author: jonathan
 */

#ifndef INC_DLM_MANAGE_DATA_ACQUISITION_H_
#define INC_DLM_MANAGE_DATA_ACQUISITION_H_

#include <stdint.h>
#include "dlm.h"

// append the standard packet structure to a buffer
// PARAMETERS:
// buffer: the ping-pong buffer to append to
// bufferSize: buffer size (in bytes) to check overflow
// timestamp: 4 byte timestamp in ms
// id: 2 byte data ID
// data: address of the data
// dataSize: size of the data in bytes
void append_packet(PPBuff* buffer, uint32_t bufferSize, uint32_t timestamp, uint16_t id, void* data, uint8_t dataSize);

// escapes a byte if necessary then appends it to the provided buffer
// PARAMETERS:
// buffer: the ping-pong buffer to append to
// byte: byte to append
void append_byte(PPBuff* buffer, uint8_t byte);

#endif /* INC_DLM_MANAGE_DATA_ACQUISITION_H_ */
