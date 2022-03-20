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

uint8_t get_node_data_size(enum DATA_TYPE type) {
	switch (type) {
		case UNSIGNED8: return 1;
		case UNSIGNED16: return 2;
		case UNSIGNED32: return 4;
		case UNSIGNED64: return 8;
		case SIGNED8: return 1;
		case SIGNED16: return 2;
		case SIGNED32: return 4;
		case SIGNED64: return 8;
		case UNKNOWN:
		default: return 0;
	}
}

// conditionally cast void pointers to set the node's data
// returns 1 if successful, 0 if failed
uint8_t set_node_data(DATA_NODE* node, void* data) {
	switch (node->type) {
		case UNSIGNED8:
			*(uint8_t*)(node->data) = *(uint8_t*) data;
			break;
		case UNSIGNED16:
			*(uint16_t*)(node->data) = *(uint16_t*) data;
			break;
		case UNSIGNED32:
			*(uint32_t*)(node->data) = *(uint32_t*) data;
			break;
		case UNSIGNED64:
			*(uint64_t*)(node->data) = *(uint64_t*) data;
			break;
		case SIGNED8:
			*(int8_t*)(node->data) = *(uint8_t*) data;
			break;
		case SIGNED16:
			*(int16_t*)(node->data) = *(uint16_t*) data;
			break;
		case SIGNED32:
			*(int32_t*)(node->data) = *(uint32_t*) data;
			break;
		case SIGNED64:
			*(int64_t*)(node->data) = *(uint64_t*) data;
			break;
		case UNKNOWN:
		default:
			// something went wrong with this node
			return 0;
	}
	return 1;
}

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

    for (i = get_node_data_size(node->type); i > 0; i--) {
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
