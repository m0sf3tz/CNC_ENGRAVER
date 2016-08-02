#include<stdio.h>
#include "buffer.h"
#include <stdlib.h>     /* malloc, free, rand */
#include <assert.h>

//void cb_init(circular_buffer *cb, size_t capacity, size_t sz)
//{
//    cb->buffer = malloc(capacity * sz);
//    if(cb->buffer == NULL)
//        while(1);
//    cb->buffer_end = (char *)cb->buffer + capacity * sz;
//    cb->capacity = capacity;
//    cb->count = 0;
//    cb->sz = sz;
//    cb->head = cb->buffer;
//    cb->tail = cb->buffer;
//}
//
//void cb_free(circular_buffer *cb)
//{
//    free(cb->buffer);
//    // clear out other fields too, just to be safe
//}
//
//void cb_push_back(circular_buffer *cb, const void *item)
//{
//    if(cb->count == cb->capacity)
//        while(1);
//    if(!memcpy(cb->head, item, cb->sz))
//        while(1);
//    cb->head = (char*)cb->head + cb->sz;
//    if(cb->head == cb->buffer_end)
//        cb->head = cb->buffer;
//    cb->count++;
//}
//
//void cb_pop_front(circular_buffer *cb, void *item)
//{
//    if(cb->count == 0)
//        while(1);
//    memcpy(item, cb->tail, cb->sz);
//    cb->tail = (char*)cb->tail + cb->sz;
//    if(cb->tail == cb->buffer_end)
//        cb->tail = cb->buffer;
//    cb->count--;
//}
