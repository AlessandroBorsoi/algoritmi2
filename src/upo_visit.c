#include <upo_visit.h>
#include <upo_queue.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2

void upo_DFS_tot_ric(upo_dirgraph_t graph, int u, int n, int* color, int* parentVector);

/**
 * @brief Effettua una visita in ampiezza BFS semplice di un grafo graph a partire da un vertice sorgente source
 *
 * @param graph il grafo da visitare
 * @param source il vertice sorgente
 * @return il vettore dei padri dell'albero di visita, NULL se il grafo e' vuoto.
 *
 */
int* upo_BFS(upo_dirgraph_t graph, int source) 
{
    if (graph == NULL)                                          // Se il grafo è NULL o non ci sono vertici viene tornato NULL
        return NULL;
    int n = upo_num_vertices(graph);
    if (n < 1)
        return NULL;    
    upo_queue_t queue = upo_queue_create();                     // Si instanzia la coda per gestire l'ordine di visita
    int* parentVector = malloc(sizeof(int) * n);                // Si istanzia la memoria per l'array dei padri da ritornare
    int color[n];                                   
    for (int i = 0; i < n; i++)
    {
        parentVector[i] = -1;                                   // Si inizializzano gli array parent e color a -1
        color[i] = WHITE;                                       // e WHITE rispettivamente
    }
    color[source] = GRAY;                                       // Il primo elemento, segnato a GRAY viene passato alla coda
    int* s = malloc(sizeof(int));
    *s = source;
    upo_queue_enqueue(queue, s);                    
    while (upo_queue_is_empty(queue) == 0) {                    // Finchè ci sono elementi nella coda...
        int u = *((int*)upo_queue_peek(queue));                 // Viene preso il primo elemento della coda u
        upo_list_t list = upo_get_inc_out_edg(graph, u);        // Viene estratta la lista di tutti i vertici uscenti d u
        upo_iterator iterator = upo_get_list_iterator(list);
        while (iterator != NULL)                                // Vengono iterati tutti i vertici incidenti
        {
            upo_dir_edge_t edge = (upo_dir_edge_t)upo_get_iterator_element(iterator);   // Si estrae il primo vertice
            if (color[edge->to] == WHITE)                       // Se non è mai stato visitato
            {
                int* v = malloc(sizeof(int));
                *v = edge->to;
                color[*v] = GRAY;                               // Lo si visita cambiandone lo stato in GRAY
                parentVector[*v] = u;                           // Si assegna il nodo da cui si è arrivati
                upo_queue_enqueue(queue, v);                    // Si aggiunge il vertice alla coda
            }
            iterator = upo_get_next(iterator);
        }
        color[u] = BLACK;                                       // Una volta iterati tutti i vertici incidenti, il vertice diventa BLACK
        int* deletingVertex = (int*)upo_queue_peek(queue);      // Viene assegnato il puntatore al vertice che verrà tolto dalla coda
        upo_queue_dequeue(queue, 0);
        free(deletingVertex);                                   // per poterne liberare la memoria
        upo_destroy_list(list);                                 // La lista di vertici incidenti non è più necessaria
    }
    upo_queue_destroy(queue, 0);                                // La coda viene distrutta
    return parentVector;                                        // e il vettore dei padri ritornato.
}

/**
 * @brief Effettua una visita in profondita' DFS totale ricorsiva di un grafo graph
 * Attenzione: per implementare questa funzione, sara' necessaria una funzione ausiliaria
 *
 * @param graph il grafo da visitare
 * @return il vettore dei padri della foresta di visita, NULL se il grafo e' vuoto.
 *
 */
int* upo_DFS_tot(upo_dirgraph_t graph) 
{
    if (graph == NULL)                                          // Se il grafo è NULL o non ci sono vertici viene tornato NULL
        return NULL;
    int n = upo_num_vertices(graph);
    if (n < 1)
        return NULL;    
    int* parentVector = malloc(sizeof(int) * n); 
    int color[n];                                
    for (int i = 0; i < n; i++)
    {
        parentVector[i] = -1;                                   // Si inizializzano gli array parent e color a -1
        color[i] = WHITE;                                       // e WHITE rispettivamente
    }
    for (int i = 0; i < n; i++)
    {
        if (color[i] == WHITE)
            upo_DFS_tot_ric(graph, i, n, color, parentVector);
    }
    return parentVector;
}

void upo_DFS_tot_ric(upo_dirgraph_t graph, int u, int n, int* color, int* parentVector)
{
    color[u] = GRAY;
    upo_list_t list = upo_get_inc_out_edg(graph, u);
    upo_iterator iterator = upo_get_list_iterator(list);
    while (iterator != NULL)
    {
        upo_dir_edge_t edge = (upo_dir_edge_t)upo_get_iterator_element(iterator);
        int v = edge->to;
        if (color[v] == WHITE)
        {
            parentVector[v] = u;
            upo_DFS_tot_ric(graph, v, n, color, parentVector);
        }
        iterator = upo_get_next(iterator);
    }
    color[u] = BLACK;
    upo_destroy_list(list);
}

/**
 * @brief Controlla se un grafo graph contiene dei cicli
 *
 * @param graph il grafo da esaminare
 * @return 1 se il grafo contiene cicli, 0 se e' aciclico, -1 se il grafo e' nullo
 *
 */
int upo_cyclic(upo_dirgraph_t graph) {
    fprintf(stderr, "To be implemented!\n");
    abort();
}

/**
 * @brief Controlla se un grafo graph e' un DAG (partendo dall'assunzione che sia diretto)
 *
 * @param graph il grafo da esaminare
 * @return 1 se il grafo e' un DAG, 0 se non lo e', -1 se il grafo e' nullo
 *
 */
int upo_is_DAG(upo_dirgraph_t graph) {
    fprintf(stderr, "To be implemented!\n");
    abort();
}

/**
 * @brief Calcola un ordinamento topologico di un grafo graph
 *
 * @param graph il grafo da esaminare
 * @return il vettore ord dell'ordinamento topologico di graph
 *
 */
int* upo_topological_sort(upo_dirgraph_t graph) {
    fprintf(stderr, "To be implemented!\n");
    abort();
}

/**
 * @brief Calcola le componenti fortemente connesse di un grafo graph con l'algoritmo di Kosaraju 
 * Nota: per comodita', restituiamo la foresta delle cfc. Quando la stampate pero' fate capire che e' un multiinsieme e non una foresta
 *
 * @param graph il grafo da esaminare
 * @return la foresta delle componenti fortemente connesse restituita dall'algoritmo di Kosaraju
 *
 */
int* upo_strongly_connected_components(upo_dirgraph_t graph) {
    fprintf(stderr, "To be implemented!\n");
    abort();
}
