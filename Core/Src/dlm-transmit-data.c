/*
 * dlm-transmit-data.c
 *
 *  Created on: Mar 10, 2022
 *      Author: jonathan
 */

#include <stdint.h>
#include "cmsis_os2.h"
#include "main.h"

#include "dlm-transmit-data.h"
#include "dlm.h"
#include "dlm-util.h"

void transmit_nodes(DATA_NODE* bufferHead) {
    static DATA_NODE* prevTransmission = NULL;
    uint8_t packet[32];
    DATA_NODE* node = bufferHead->next;
    DATA_NODE* transmissionHead = node;

    // step through nodes from the buffer head to the start of the last transmission
    while (node != NULL && node != prevTransmission) {
        // wait for access to the data buffer
        osStatus_t status = osMutexAcquire(bufferMutexHandle, osWaitForever);
        if (status == osOK) {
            osKernelLock();

            // build a packet from the data node
            uint8_t packetLength = packetize_node(node, packet);
            node = node->next;

            osKernelUnlock();
            osMutexRelease(bufferMutexHandle);

            // if the xbee buffer has space, send packet
            uint8_t xbFull = HAL_GPIO_ReadPin(NCTS_GPIO_Port, NCTS_Pin);
            if (!xbFull) {
                HAL_UART_Transmit(&huart2, packet, packetLength, HAL_MAX_DELAY);
            }
        }
    }

    // remember the first node in this transmission
    prevTransmission = transmissionHead;
}
