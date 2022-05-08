/*
 * dlm.h
 *
 *  Created on: Mar 17, 2022
 *      Author: jonathan
 */

#ifndef INC_DLM_H_
#define INC_DLM_H_

#include <stdint.h>

// byte to indicate the start of a packet
#define START_BYTE 0x7e
// byte to indicate that the next byte has been escaped
#define ESCAPE_BYTE 0x7d

// size in bytes for half of the ping-pong buffer
#define STORAGE_BUFFER_SIZE 1500
#define BROADCAST_BUFFER_SIZE 1500

// thread periods/delays in RTOS ticks (also in ms for a 1ms tick)
#define THREAD_DELAY_STORE_DATA 1000
#define THREAD_DELAY_BROADCAST_DATA 1000
#define THREAD_DELAY_ACQUIRE_DATA 10

// thread flag to indicate that a previous transfer is complete
#define FLAG_TRANSFER_DONE 0x00000001U

// ping-pong buffer struct
typedef struct PPBuff {
	uint8_t* buffs[2]; // pointers to 2 byte buffers
	uint8_t write; // index of the write buffer (0 or 1)
	uint32_t fill; // fill level of the write buffer (in bytes)
} PPBuff;

// global initialization
void dlm_init(void);

// high level function for the data acquisition task
// responsible for servicing CAN hardware, requesting data buckets, and writing data in packets
void dlm_manage_data_acquisition(void);

// high level function for the data storage task
// responsible for setting up SD card transfers and swapping its ping-pong buffer
void dlm_manage_data_storage(void);

// high level function for the data broadcast task (telemetry)
// responsible for setting up UART transfers to an Xbee module and swapping its ping-pong buffer
void dlm_manage_data_broadcast(void);

#endif /* INC_DLM_H_ */
