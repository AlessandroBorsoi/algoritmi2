#include <stdio.h>
#include <stdlib.h>
#include "upo_priority_queue_private.h"

typedef struct upo_priority_queue_s* upo_priority_queue_t;

upo_priority_queue_t upo_priority_queue_create() 
{
    upo_priority_queue_t queue = malloc(sizeof(struct upo_priority_queue_s));
    if (queue == NULL)
    {
        perror("Unable to create the queue");
        abort();
    }
    queue->len = 0;
    queue->size = 4;
    queue->node = malloc(sizeof(struct upo_priority_queue_node_s) * queue->size);
    if (queue->node == NULL)
    {
        perror("Unable to create the queue node");
        abort();
    }
    return queue;
}

void upo_priority_queue_destroy(upo_priority_queue_t queue)
{
    free(queue->node);
    free(queue);
}

void upo_priority_queue_enqueue(upo_priority_queue_t queue, int data, int priority)
{
    if (queue == NULL) 
        return;
    // Se data è già stato inserito non viene fatto nulla
    for (int i = 1; i <= queue->len; i++)
        if (queue->node[i].data == data)
            return;
    // Se gli elementi nello heap occupano tutto lo spazio disponibile allora si raddoppia lo spazio.
    if (queue->len == queue->size) 
    {
        queue->size *= 2;
        queue->node = realloc(queue->node, sizeof(struct upo_priority_queue_node_s) * queue->size);
    }
    int i = queue->len + 1;
    int j = i / 2;
    while (i > 1 && queue->node[j].priority > priority) 
    {
        queue->node[i] = queue->node[j];
        i = j;
        j = j / 2;
    }
    queue->node[i].priority = priority;
    queue->node[i].data = data;
    queue->len++;
}

int upo_priority_queue_dequeue(upo_priority_queue_t queue)
{
    if (queue == NULL) 
        return -1;
    int data = queue->node[1].data;
    queue->node[1] = queue->node[queue->len];
    queue->len--;
    int i = 1, j, k;
    while (1) {
        k = i;
        j = 2 * i;
        if (j <= queue->len && queue->node[j].priority < queue->node[k].priority) {
            k = j;
        }
        if (j + 1 <= queue->len && queue->node[j + 1].priority < queue->node[k].priority) {
            k = j + 1;
        }
        if (k == i) {
            break;
        }
        queue->node[i] = queue->node[k];
        i = k;
    }
    queue->node[i] = queue->node[queue->len + 1];
    return data;
}

int upo_priority_queue_is_empty(const upo_priority_queue_t queue)
{
    if (queue != NULL)
        return queue->len == 0 ? 1 : 0;
    return 1;
}

void upo_priority_queue_update(upo_priority_queue_t queue, int data, int priority)
{
    if (queue == NULL) 
        return;
    int i;
    for (i = 1; i <= queue->len; i++)
    {
        if (queue->node[i].data == data)
        {
            queue->node[i].priority = priority;
            break;
        }
    }
    int j = i / 2;
    while (i > 1 && queue->node[j].priority > priority)
    {
        queue->node[i] = queue->node[j];
        i = j;
        j = j / 2;
    }
    queue->node[i].priority = priority;
    queue->node[i].data = data;
}
