#ifndef UPO_PRIORITY_QUEUE_PRIVATE_H
#define UPO_PRIORITY_QUEUE_PRIVATE_H

#include <stddef.h>
#include <upo_priority_queue.h>

struct upo_priority_queue_node_s {
    int data;
    int priority;
};

typedef struct upo_priority_queue_node_s upo_priority_queue_node_t;

struct upo_priority_queue_s {
    upo_priority_queue_node_t* node;
    int len;
    int size;
};

#endif /* UPO_PRIORITY_QUEUE_PRIVATE_H */
