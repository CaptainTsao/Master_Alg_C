//
// Created by rcao on 2021/6/14.
//
#include <stdlib.h>

#include "list.h"
#include "queue.h"

/* Enqueue data*/
int queue_enqueue(Queue *queue, const void *data) {
    return list_ins_next(queue, list_tail(queue), data);
}

/* Dequeue data */
int queue_dequeue(Queue *queue, void **data) {
    return list_rem_next(queue, NULL, data);
}