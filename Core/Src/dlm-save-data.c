/*
 * dlm-save-data.c
 *
 *  Created on: Mar 13, 2022
 *      Author: jonathan
 */

#include <stdlib.h>
#include "main.h"

#include "dlm-save-data.h"
#include "dlm.h"

void save_nodes(DATA_INFO_NODE* bufferHead) {
    DATA_INFO_NODE* node = bufferHead->next;

    // clear all nodes from the buffer
    while (node != NULL) {
        // wait for access to the data buffer
        osStatus_t status = osMutexAcquire(bufferMutexHandle, osWaitForever);
        if (status == osOK) {
            osKernelLock();

            // remove node
            bufferHead->next = node->next;
            free(node);
            node = bufferHead->next;

            osKernelUnlock();
            osMutexRelease(bufferMutexHandle);
        }
    }
}
