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
#include "dlm-util.h"

void generate_node(DATA_NODE* bufferHead) {
    static uint32_t nodeCount = 0;

    // create a data node
    DATA_NODE* node = malloc(sizeof(DATA_NODE)); // allocate space for the node structure
    if (node == NULL) return;

    node->timestamp = nodeCount;
	node->id = 0x0001;
	node->type = UNSIGNED64;

	node->data = malloc(get_node_data_size(node->type)); // allocate space for the node's data
	if (node->data == NULL) return;

    uint64_t fakeData = 0x69;
    uint8_t success = set_node_data(node, &fakeData);
    if (!success) {
    	// something went wrong with this node
    	free(node->data);
		free(node);
		return;
    }

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
        free(node->data);
        free(node);
        return;
    }
}
