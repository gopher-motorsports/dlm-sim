/*
 * dlm-util.c
 *
 *  Created on: Mar 13, 2022
 *      Author: jonathan
 */

#include <stdint.h>

#include "dlm-util.h"
#include "dlm.h"

// dlm-util.c contains functions that may be used across dlm features

// takes a data node, breaks it into bytes, and writes it to a packet (byte array)
// returns the length of the packet
uint8_t packetize_node(DATA_NODE* node, uint8_t packet[]) {
    uint8_t i;
    uint8_t* bytes;
    uint8_t packetLength = 0;

    packet[packetLength] = (uint8_t) START_BYTE;
    packetLength++;

    for (i = sizeof(node->timestamp); i > 0; i--) {
        bytes = (uint8_t*) &(node->timestamp);
        packetLength = append_byte(packet, packetLength, bytes[i - 1]);
    }

    for (i = sizeof(node->id); i > 0; i--) {
        bytes = (uint8_t*) &(node->id);
        packetLength = append_byte(packet, packetLength, bytes[i - 1]);
    }

    for (i = sizeof(uint8_t); i > 0; i--) {
        bytes = (uint8_t*) (node->data);
        packetLength = append_byte(packet, packetLength, bytes[i - 1]);
    }

    return packetLength;
}

// escapes a byte if necessary, then appends it to the packet
// takes the current length of the packet and the byte to append
// returns the new packet length
uint8_t append_byte(uint8_t packet[], uint8_t packetLength, uint8_t byte) {
    uint8_t bytesFilled = 0;

    // check for a control byte
    if (byte == 0x7e || byte == 0x7d) {
        // append an escape byte
        packet[packetLength + bytesFilled] = 0x7d;
        bytesFilled++;
        // append escaped byte
        packet[packetLength + bytesFilled] = byte ^ 0x20;
        bytesFilled++;
    } else {
        packet[packetLength + bytesFilled] = byte;
        bytesFilled++;
    }

    return packetLength + bytesFilled;
}
