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
#define BUFFER_SIZE 16
// TODO: handle not fitting a whole packet at the end of the buffer
// idea: if the next packet isnt going to fit, write dummy bytes to the rest of the buffer and ping-pong
// stretching packets across buffers could get messy if something goes wrong with a write

// TODO: what if the write buffer fills before the other one has been flushed
// wont have anywhere to put the incoming data

void dlm_generate_data(void);
void dlm_transmit_data(void);
void dlm_save_data(void);

typedef struct PPBuff {
	uint8_t* rows[2]; // pointers to 2 byte buffers
	uint8_t write; // index of the write buffer (0 or 1)
	uint8_t written; // # of bytes written
	uint8_t full; // 1 if the write buffer is full
	uint8_t flushed; // 1 if the read buffer has been flushed
} PPBuff;

#endif /* INC_DLM_H_ */
