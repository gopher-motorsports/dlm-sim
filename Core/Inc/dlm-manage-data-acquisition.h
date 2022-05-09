/*
 * dlm-manage-data-acquisition.h
 *
 *  Created on: Apr 19, 2022
 *      Author: jonathan
 */

#ifndef INC_DLM_MANAGE_DATA_ACQUISITION_H_
#define INC_DLM_MANAGE_DATA_ACQUISITION_H_

#include "dlm.h"

// create packets and append them to the buffers
// PARAMETERS:
// storageBuffer: storage ping-pong buffer
// broadcastBuffer: broadcast ping-pong buffer
void generate_data(PPBuff* storageBuffer, PPBuff* broadcastBuffer);

#endif /* INC_DLM_MANAGE_DATA_ACQUISITION_H_ */
