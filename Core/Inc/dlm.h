/*
 * dlm.h
 *
 *  Created on: Mar 17, 2022
 *      Author: jonathan
 */

#ifndef INC_DLM_H_
#define INC_DLM_H_

#include <stdint.h>

#define START_BYTE 0x7e

void dlm_generate_data(void);
void dlm_transmit_data(void);
void dlm_save_data(void);

typedef union {
	double d;
	uint64_t u64;
} DPF_CONVERTER;

// general node to refer to varying data sizes
typedef struct DATA_INFO_NODE {
    uint32_t timestamp;
    uint16_t id;
    struct DATA_INFO_NODE* next;
} DATA_INFO_NODE;

// nodes for each data size
typedef struct {
    uint32_t timestamp;
    uint16_t id;
    DATA_INFO_NODE* next;
    uint8_t data;
} U8_DATA_NODE;

typedef struct {
    uint32_t timestamp;
    uint16_t id;
    DATA_INFO_NODE* next;
    uint16_t data;
} U16_DATA_NODE;

typedef struct {
    uint32_t timestamp;
    uint16_t id;
    DATA_INFO_NODE* next;
    uint32_t data;
} U32_DATA_NODE;

typedef struct {
    uint32_t timestamp;
    uint16_t id;
    DATA_INFO_NODE* next;
    uint64_t data;
} U64_DATA_NODE;

typedef struct {
    uint32_t timestamp;
    uint16_t id;
    DATA_INFO_NODE* next;
    int8_t data;
} S8_DATA_NODE;

typedef struct {
    uint32_t timestamp;
    uint16_t id;
    DATA_INFO_NODE* next;
    int16_t data;
} S16_DATA_NODE;

typedef struct {
    uint32_t timestamp;
    uint16_t id;
    DATA_INFO_NODE* next;
    int32_t data;
} S32_DATA_NODE;

typedef struct {
    uint32_t timestamp;
    uint16_t id;
    DATA_INFO_NODE* next;
    int64_t data;
} S64_DATA_NODE;

typedef struct {
    uint32_t timestamp;
    uint16_t id;
    DATA_INFO_NODE* next;
    float data;
} FLOAT_DATA_NODE;

#endif /* INC_DLM_H_ */
