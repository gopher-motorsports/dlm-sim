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
    U8_DATA_NODE* node = malloc(sizeof(U8_DATA_NODE));

    if (node == NULL) return;

    node->timestamp = nodeCount;
	node->id = 0x007e;
    node->data = 0x7d;

	DATA_INFO_NODE* infoNode = (DATA_INFO_NODE*)node;

    // wait for access to the data buffer
    osStatus_t status = osMutexAcquire(bufferMutexHandle, osWaitForever);
    if (status == osOK) {
        // mutex acquired, push a node to the buffer
        osKernelLock();

        infoNode->next = bufferHead->next;
        bufferHead->next = infoNode;

        osKernelUnlock();
        osMutexRelease(bufferMutexHandle);

        nodeCount++;
    } else {
        // couldn't get access to the buffer, throw away this node
        free(infoNode);
    }
}
