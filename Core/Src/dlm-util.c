/*
 * dlm-util.c
 *
 *  Created on: Mar 13, 2022
 *      Author: jonathan
 */

#include <stdint.h>

#include "dlm-util.h"
#include "dlm.h"
#include "GopherCAN.h"

// dlm-util.c contains functions that may be used across dlm features

// takes a data node, breaks it into bytes, and writes it to a packet (byte array)
// returns the length of the packet
uint8_t packetize_node(DATA_INFO_NODE* node, uint8_t packet[]) {
    uint8_t i;
    uint8_t* bytes;
    uint8_t packetLength = 0;

    packet[packetLength] = (uint8_t)START_BYTE;
    packetLength++;

    for (i = sizeof(node->timestamp); i > 0; i--) {
        bytes = (uint8_t*) &(node->timestamp);
        packetLength = append_byte(packet, packetLength, bytes[i - 1]);
    }

    for (i = sizeof(node->id); i > 0; i--) {
        bytes = (uint8_t*) &(node->id);
        packetLength = append_byte(packet, packetLength, bytes[i - 1]);
    }

    DPF_CONVERTER data;
//    data.d = convert_data_to_dpf(node);
    data.d = (double)(((U8_DATA_NODE*)node)->data);
    for (i = sizeof(data.u64); i > 0; i--) {
        bytes = (uint8_t*) &(data.u64);
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

// convert any data size into a double precision float
double convert_data_to_dpf(DATA_INFO_NODE* node) {
    switch (parameter_data_types[node->id]) {
		case UNSIGNED8:
			return (double)(((U8_DATA_NODE*)node)->data);

		case UNSIGNED16:
			return (double)(((U16_DATA_NODE*)node)->data);

		case UNSIGNED32:
			return (double)(((U32_DATA_NODE*)node)->data);

		case UNSIGNED64:
			return (double)(((U64_DATA_NODE*)node)->data);

		case SIGNED8:
			return (double)(((S8_DATA_NODE*)node)->data);

		case SIGNED16:
			return (double)(((S16_DATA_NODE*)node)->data);

		case SIGNED32:
			return (double)(((S32_DATA_NODE*)node)->data);

		case SIGNED64:
			return (double)(((S64_DATA_NODE*)node)->data);

		case FLOATING:
			return (double)(((FLOAT_DATA_NODE*)node)->data);

		default:
			// something went wrong, just write 0 to data
			return 0;
	}
}
