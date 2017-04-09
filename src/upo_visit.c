#include <upo_visit.h>
#include <upo_queue.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2

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
    if (graph == NULL)
        return NULL;
    int n = upo_num_vertices(graph);
    if (n < 1)
        return NULL;    
    upo_queue_t queue = upo_queue_create();
    int* parentVector = malloc(sizeof(int) * n);
    int color[n];
    for (int i = 0; i < n; i++)
    {
        parentVector[i] = -1;
        color[i] = 0;
    }
    color[source] = GRAY;
    upo_queue_enqueue(queue, &source);
    while (upo_queue_is_empty(queue) == 0) {
        int u = *((int*)upo_queue_peek(queue));
        upo_list_t list = upo_get_inc_out_edg(graph, u);
        upo_iterator iterator = upo_get_list_iterator(list);
        while (iterator != NULL)
        {
            upo_dir_edge_t edge = (upo_dir_edge_t)upo_get_iterator_element(iterator);
            int v = edge->to;
            if (color[v] == WHITE)
            {
                color[v] = GRAY;
                parentVector[v] = u;
                upo_queue_enqueue(queue, &v);
            }
            iterator = upo_get_next(iterator);
        }
        color[u] = BLACK;
        upo_queue_dequeue(queue, 0);
        upo_destroy_list(list);
    }
    upo_queue_destroy(queue, 0);
    return parentVector;
}

/**
 * @brief Effettua una visita in profondita' DFS totale ricorsiva di un grafo graph
 * Attenzione: per implementare questa funzione, sara' necessaria una funzione ausiliaria
 *
 * @param graph il grafo da visitare
 * @return il vettore dei padri della foresta di visita, NULL se il grafo e' vuoto.
 *
 */
int* upo_DFS_tot(upo_dirgraph_t graph) {
    fprintf(stderr, "To be implemented!\n");
    abort();
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
