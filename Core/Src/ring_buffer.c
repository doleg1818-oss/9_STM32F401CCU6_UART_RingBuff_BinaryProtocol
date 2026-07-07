/*
 * ring_buffer.c
 *
 *  Created on: Jun 3, 2026
 *      Author: Olegd
 */

#include "ring_buffer.h"


bool rb_init(ring_buffer_t *rb, uint8_t *buffer, size_t size)
{
    if(rb == NULL || buffer == NULL || size == 0)
    {
        return false;
    }
    rb->buffer = buffer;
    rb->size = size;
    rb->head = 0;
    rb->tail = 0;
    rb->count = 0;

    return true;
}
bool rb_is_empty(const ring_buffer_t *rb)
{
    return rb->count == 0;
}
bool rb_is_full(const ring_buffer_t *rb)
{
    return rb->count == rb->size;
}
size_t rb_available(const ring_buffer_t *rb)	// how many bytes available to read
{
    return rb->count;
}
void rb_clear(ring_buffer_t *rb)
{
    rb->head = 0;
    rb->tail = 0;
    rb->count = 0;
}
bool rb_push(ring_buffer_t *rb, uint8_t data)
{
    if(rb == NULL)
    {
        return false;
    }
    if(rb_is_full(rb))
    {
        return false;
    }

    rb->buffer[rb->head] = data;
    rb->head++;
    if(rb->head >= rb->size)
    {
        rb->head = 0;
    }
    rb->count++;
    return true;
}
bool rb_pop(ring_buffer_t *rb, uint8_t *data)
{
    if(rb == NULL || data == NULL)
    {
        return false;
    }
    if(rb_is_empty(rb))
    {
        return false;
    }

    *data = rb->buffer[rb->tail];
    rb->tail++;

    if(rb->tail >= rb->size)
    {
        rb->tail = 0;
    }
    rb->count--;
    return true;
}

