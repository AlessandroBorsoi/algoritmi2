#include "upo_priority_queue_private.h"

typedef struct upo_priority_queue_s* upo_priority_queue_t;

upo_priority_queue_t upo_priority_queue_create() 
{
    return NULL;
}

void upo_priority_queue_destroy(upo_priority_queue_t queue, int destroy_data)
{

}

void upo_priority_queue_clear(upo_priority_queue_t queue, int destroy_data)
{

}

void upo_priority_queue_enqueue(upo_priority_queue_t queue, void *data, int priority)
{

}

void upo_priority_queue_dequeue(upo_priority_queue_t queue, int destroy_data)
{

}

void* upo_priority_queue_peek(const upo_priority_queue_t queue)
{
    return NULL;
}

size_t upo_priority_queue_size(const upo_priority_queue_t queue)
{
    return 0;
}

int upo_priority_queue_is_empty(const upo_priority_queue_t queue)
{
    return 1;
}

void upo_priority_queue_change(upo_priority_queue_t queue, void *data, int priority)
{
    
}
