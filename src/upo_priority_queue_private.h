#ifndef UPO_PRIORITY_QUEUE_PRIVATE_H
#define UPO_PRIORITY_QUEUE_PRIVATE_H

#include <stddef.h>
#include <upo_priority_queue.h>

struct upo_priority_queue_node_s {
    void* data;
    struct upo_priority_queue_node_s* next;
    struct upo_priority_queue_node_s* prev;
};

typedef struct upo_priority_queue_node_s upo_priority_queue_node_t;

struct upo_priority_queue_s {
    upo_priority_queue_node_t* front;
    upo_priority_queue_node_t* back;
    size_t size;
};

#endif /* UPO_PRIORITY_QUEUE_PRIVATE_H */
