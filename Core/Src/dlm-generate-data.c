/*
 * dlm-generate-data.c
 *
 *  Created on: Mar 10, 2022
 *      Author: jonathan
 */

#include <stdlib.h>
#include <stdint.h>
#include "cmsis_os2.h"
#include "main.h"

#include "dlm-generate-data.h"
#include "dlm.h"

void generate_node(DATA_INFO_NODE* bufferHead) {
    static uint32_t nodeCount = 0;

    // create a data node
    DATA_INFO_NODE* node;
    U8_DATA_NODE* u8_node = malloc(sizeof(U8_DATA_NODE));

    if (u8_node == NULL) return;

    // fill data
    u8_node->data = 0x7d;

    // fill metadata
    node = (DATA_INFO_NODE*)u8_node;
    node->timestamp = nodeCount;
	node->id = 0x007e;

    // wait for access to the data buffer
    osStatus_t status = osMutexAcquire(bufferMutexHandle, osWaitForever);
    if (status == osOK) {
        // mutex acquired, push a node to the buffer
        osKernelLock();

        node->next = bufferHead->next;
        bufferHead->next = node;

        osKernelUnlock();
        osMutexRelease(bufferMutexHandle);

        nodeCount++;
    } else {
        // couldn't get access to the buffer, throw away this node
        free(node);
    }
}
