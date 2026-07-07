/*
 * ring_buffer.h
 *
 *  Created on: Jun 3, 2026
 *      Author: Olegd
 */

#ifndef INC_RING_BUFFER_H_
#define INC_RING_BUFFER_H_

#include "main.h"

typedef struct
{
    uint8_t *buffer;
    size_t size;

    size_t head;
    size_t tail;

    size_t count;
}ring_buffer_t;

bool rb_init(ring_buffer_t *rb, uint8_t *buffer, size_t size);
bool rb_push(ring_buffer_t *rb, uint8_t data);
bool rb_pop(ring_buffer_t *rb, uint8_t *data);
bool rb_is_empty(const ring_buffer_t *rb);
bool rb_is_full(const ring_buffer_t *rb);
void rb_clear(ring_buffer_t *rb);
size_t rb_available(const ring_buffer_t *rb);

#endif /* INC_RING_BUFFER_H_ */
