/*
 * dlm-transmit-data.c
 *
 *  Created on: Mar 10, 2022
 *      Author: jonathan
 */

#include "dlm-transmit-data.h"
#include "dlm.h"
#include "main.h"

void transmit_packets(PPBuff* buffer) {
	// be smart about searching for whitelisted packets
	// look for a start byte -> id is 4 bytes ahead
	// id tells how many bytes long the packet is -> leads to next id
	// wont have to search every byte
}
