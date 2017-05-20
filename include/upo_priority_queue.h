#ifndef UPO_PRIORITY_QUEUE_T
#define UPO_PRIORITY_QUEUE_T

#include <stddef.h>

/** \brief The queue abstract data type. */
typedef struct upo_priority_queue_s* upo_priority_queue_t;

/** \brief Creates a new queue. */
upo_priority_queue_t upo_priority_queue_create();

/** \brief Destroys the given queue. */
void upo_priority_queue_destroy(upo_priority_queue_t queue, int destroy_data);

/** \brief Removes all elements from the given queue. */
void upo_priority_queue_clear(upo_priority_queue_t queue, int destroy_data);

/** \brief Inserts the given element into the given queue. */
void upo_priority_queue_enqueue(upo_priority_queue_t queue, void *data, int priority);

/** \brief Removes the next element from the given queue. */
void upo_priority_queue_dequeue(upo_priority_queue_t queue, int destroy_data);

/** \brief Returns the next element from the given queue. */
void* upo_priority_queue_peek(const upo_priority_queue_t queue);

/** \brief Returns the length of the given queue. */
size_t upo_priority_queue_size(const upo_priority_queue_t queue);

/** \brief Tells whether the given queue is empty. */
int upo_priority_queue_is_empty(const upo_priority_queue_t queue);

/** \brief Change the priority of the given element into the given queue. */
void upo_priority_queue_change(upo_priority_queue_t queue, void *data, int priority);

#endif /* UPO_PRIORITY_QUEUE_T */
