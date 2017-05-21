#ifndef UPO_PRIORITY_QUEUE_T
#define UPO_PRIORITY_QUEUE_T

#include <stddef.h>

/** \brief The queue abstract data type. */
typedef struct upo_priority_queue_s* upo_priority_queue_t;

/** \brief Creates a new queue. */
upo_priority_queue_t upo_priority_queue_create();

/** \brief Destroys the given queue. */
void upo_priority_queue_destroy(upo_priority_queue_t queue);

/** \brief Inserts the given element into the given queue. */
void upo_priority_queue_enqueue(upo_priority_queue_t queue, int data, int priority);

/** \brief Removes the next element from the given queue. */
int upo_priority_queue_dequeue(upo_priority_queue_t queue);

/** \brief Tells whether the given queue is empty. */
int upo_priority_queue_is_empty(const upo_priority_queue_t queue);

/** \brief Change the priority of the given element into the given queue. */
void upo_priority_queue_update(upo_priority_queue_t queue, int data, int priority);

#endif /* UPO_PRIORITY_QUEUE_T */
