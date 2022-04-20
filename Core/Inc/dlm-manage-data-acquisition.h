/*
 * dlm-manage-data-acquisition.h
 *
 *  Created on: Apr 19, 2022
 *      Author: jonathan
 */

#ifndef INC_DLM_MANAGE_DATA_ACQUISITION_H_
#define INC_DLM_MANAGE_DATA_ACQUISITION_H_

#include "dlm.h"

// create some dummy data and write it to the buffers
// PARAMETERS:
// storageBuffer: address of ping-pong buffer struct for data storage
// telemetryBuffer: address of buffer for telemetry
void generate_data(PPBuff* storageBuffer, PPBuff* telemetryBuffer);

#endif /* INC_DLM_MANAGE_DATA_ACQUISITION_H_ */
