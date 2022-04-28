/*
 * dlm-manage-data-broadcast.h
 *
 *  Created on: Apr 19, 2022
 *      Author: jonathan
 */

#ifndef INC_DLM_MANAGE_DATA_BROADCAST_H_
#define INC_DLM_MANAGE_DATA_BROADCAST_H_

#include "dlm.h"

// start the UART DMA transfer
// PARAMETERS:
// buffer: telemetry ping-pong buffer
void start_broadcast(PPBuff* buffer);

#endif /* INC_DLM_MANAGE_DATA_BROADCAST_H_ */
