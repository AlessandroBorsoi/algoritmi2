#include <upo_visit.h>
#include <upo_queue.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2

void upo_DFS_tot_ric(upo_dirgraph_t graph, int u, int n, int* color, int* parentVector);
int upo_cyclic_ric(upo_dirgraph_t graph, int u, int* color);
void upo_topological_sort_ric(upo_dirgraph_t graph, int u, int n, int* color, int* ts, int* t);
void upo_scc_DFS_tot_ric(upo_dirgraph_t graph, int u, int n, int* color, int* vertexList, int* t);
void upo_DFS_tot_transposed_ric(upo_dirgraph_t graph, int u, int n, int* color, int* parentVector);

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
        upo_list_t list = upo_get_inc_out_edg(graph, u);        // Viene estratta la lista di tutti i vertici uscenti da u
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
        upo_queue_dequeue(queue, 1);                            // Viene tolto un elemento dalla coda
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
    int* parentVector = malloc(sizeof(int) * n);                // Si istanzia la memoria per l'array dei padri da ritornare
    int color[n];                                
    for (int i = 0; i < n; i++)
    {
        parentVector[i] = -1;                                   // Si inizializzano gli array parent e color a -1
        color[i] = WHITE;                                       // e WHITE rispettivamente
    }
    for (int i = 0; i < n; i++)                                 // Per ogni nodo
        if (color[i] == WHITE)                                  // bianco
            upo_DFS_tot_ric(graph, i, n, color, parentVector);  // si richiama la funzione ricorsiva
    return parentVector;
}

void upo_DFS_tot_ric(upo_dirgraph_t graph, int u, int n, int* color, int* parentVector)
{
    color[u] = GRAY;                                            // Il nodo appena visitato viene settato a GREY
    upo_list_t list = upo_get_inc_out_edg(graph, u);
    upo_iterator iterator = upo_get_list_iterator(list);
    while (iterator != NULL)                                    // Si itera su tutti i nodi con vertice uscente da u
    {
        upo_dir_edge_t edge = (upo_dir_edge_t)upo_get_iterator_element(iterator);
        int v = edge->to;                                   
        if (color[v] == WHITE)                                  // Se il vertice considerato è WHITE
        {
            parentVector[v] = u;                                // Si memorizza il padre
            upo_DFS_tot_ric(graph, v, n, color, parentVector);  // E si chiama di nuovo la funzione ricorsiva
        }
        iterator = upo_get_next(iterator);
    }
    color[u] = BLACK;                                           // Al ritorno della ricorsione si può settare il nodo a BLACK
    upo_destroy_list(list);
}

/**
 * @brief Controlla se un grafo graph contiene dei cicli
 *
 * @param graph il grafo da esaminare
 * @return 1 se il grafo contiene cicli, 0 se e' aciclico, -1 se il grafo e' nullo
 *
 */
int upo_cyclic(upo_dirgraph_t graph) 
{
    if (graph == NULL)                                                  // Se il grafo è NULL o non ci sono vertici viene tornato -1
        return -1;
    int n = upo_num_vertices(graph);
    if (n < 1)
        return -1;    
    int color[n];
    for (int i = 0; i < n; i++)
        color[i] = WHITE;                                               // Inizializzazione del vettore color
    for (int i = 0; i < n; i++)
        if (color[i] == WHITE && upo_cyclic_ric(graph, i, color) == 1)  // Se il vertice è inesplorato viene chiamata la funzione ricorsiva
            return 1;
    return 0;
}

int upo_cyclic_ric(upo_dirgraph_t graph, int u, int* color)
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
            if (upo_cyclic_ric(graph, v, color) == 1)
            {
                upo_destroy_list(list);
                return 1;
            }
        }
        else if (color[v] == GRAY)
        {
            upo_destroy_list(list);
            return 1;
        }
        iterator = upo_get_next(iterator);
    }
    color[u] = BLACK;
    upo_destroy_list(list);
    return 0;
} 

/**
 * @brief Controlla se un grafo graph e' un DAG (partendo dall'assunzione che sia diretto)
 *
 * @param graph il grafo da esaminare
 * @return 1 se il grafo e' un DAG, 0 se non lo e', -1 se il grafo e' nullo
 *
 */
int upo_is_DAG(upo_dirgraph_t graph) 
{
    int res = upo_cyclic(graph);    // Si controlla se il grafo contiene cicli
    if (res == -1)      
        return -1;                  // Se il grafo è NULL o non ha vertici si ritorna -1
    return 1 - res;                 // Se non contiene cicli si ritorna 1 e viceversa
}

/**
 * @brief Calcola un ordinamento topologico di un grafo graph
 *
 * @param graph il grafo da esaminare
 * @return il vettore ord dell'ordinamento topologico di graph
 *
 */
int* upo_topological_sort(upo_dirgraph_t graph) 
{
    if (upo_is_DAG(graph) < 1)                                  // Se il grafo non è un DAG, è NULL o non ha vertici
        return NULL;                                            // si ritorna NULL
    int n = upo_num_vertices(graph);
    int* ts = calloc(sizeof(int), n);
    int* t = malloc(sizeof(int));
    *t = n - 1;
    int color[n];                                
    for (int i = 0; i < n; i++)
        color[i] = WHITE;                                       
    for (int i = 0; i < n; i++)                                 // Per ogni nodo
        if (color[i] == WHITE)                                  // bianco
            upo_topological_sort_ric(graph, i, n, color, ts, t);// si richiama la funzione ricorsiva
    free(t);
    return ts;
}

void upo_topological_sort_ric(upo_dirgraph_t graph, int u, int n, int* color, int* ts, int* t)
{
    color[u] = GRAY;                                            // Il nodo appena visitato viene settato a GREY
    upo_list_t list = upo_get_inc_out_edg(graph, u);
    upo_iterator iterator = upo_get_list_iterator(list);
    while (iterator != NULL)                                    // Si itera su tutti i nodi con vertice uscente da u
    {
        upo_dir_edge_t edge = (upo_dir_edge_t)upo_get_iterator_element(iterator);
        int v = edge->to;                                   
        if (color[v] == WHITE)                                  // Se il vertice considerato è WHITE
            upo_topological_sort_ric(graph, v, n, color, ts, t);// si chiama di nuovo la funzione ricorsiva
        iterator = upo_get_next(iterator);
    }
    color[u] = BLACK;                                           // Al ritorno della ricorsione si può settare il nodo a BLACK
    upo_destroy_list(list);
    ts[*t] = u;
    (*t)--;
}

/**
 * @brief Calcola le componenti fortemente connesse di un grafo graph con l'algoritmo di Kosaraju 
 * Nota: per comodita', restituiamo la foresta delle cfc. Quando la stampate pero' fate capire che e' un multiinsieme e non una foresta
 *
 * @param graph il grafo da esaminare
 * @return la foresta delle componenti fortemente connesse restituita dall'algoritmo di Kosaraju
 *
 */
int* upo_strongly_connected_components(upo_dirgraph_t graph) 
{
    if (graph == NULL)
        return NULL;
    int n = upo_num_vertices(graph);
    if (n < 1)
        return NULL;   
    int* vertexList = malloc(sizeof(int) * n);
    int* t = malloc(sizeof(int));
    *t = n - 1;
    int color[n];                  
    for (int i = 0; i < n; i++)
        color[i] = WHITE;
    for (int i = 0; i < n; i++)                                 
        if (color[i] == WHITE)                                  
            upo_scc_DFS_tot_ric(graph, i, n, color, vertexList, t);
    int* cfc = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
    {
        cfc[i] = -1;
        color[i] = WHITE;
    }
    for (int i = 0; i < n; i++)
        if (color[vertexList[i]] == WHITE)
            upo_DFS_tot_transposed_ric(graph, vertexList[i], n, color, cfc);
    free(vertexList);
    free(t);
    return cfc;
}

void upo_scc_DFS_tot_ric(upo_dirgraph_t graph, int u, int n, int* color, int* vertexList, int* t)
{
    color[u] = GRAY;                                            // Il nodo appena visitato viene settato a GREY
    upo_list_t list = upo_get_inc_out_edg(graph, u);
    upo_iterator iterator = upo_get_list_iterator(list);
    while (iterator != NULL)                                    // Si itera su tutti i nodi con vertice uscente da u
    {
        upo_dir_edge_t edge = (upo_dir_edge_t)upo_get_iterator_element(iterator);
        int v = edge->to;                                   
        if (color[v] == WHITE)                                  // Se il vertice considerato è WHITE
            upo_scc_DFS_tot_ric(graph, v, n, color, vertexList, t);  // si chiama di nuovo la funzione ricorsiva
        iterator = upo_get_next(iterator);
    }
    color[u] = BLACK;                                           // Al ritorno della ricorsione si può settare il nodo a BLACK
    vertexList[*t] = u;
    (*t)--;
    upo_destroy_list(list);
}

void upo_DFS_tot_transposed_ric(upo_dirgraph_t graph, int u, int n, int* color, int* parentVector)
{
    color[u] = GRAY;                                            // Il nodo appena visitato viene settato a GREY
    upo_list_t list = upo_get_inc_in_edg(graph, u);
    upo_iterator iterator = upo_get_list_iterator(list);
    while (iterator != NULL)                                    // Si itera su tutti i nodi con vertice entrante da u
    {
        upo_dir_edge_t edge = (upo_dir_edge_t)upo_get_iterator_element(iterator);
        int v = edge->from;       
        if (color[v] == WHITE)                                  // Se il vertice considerato è WHITE
        {
            parentVector[v] = u;                                // Si memorizza il padre
            upo_DFS_tot_transposed_ric(graph, v, n, color, parentVector);  // E si chiama di nuovo la funzione ricorsiva
        }
        iterator = upo_get_next(iterator);
    }
    color[u] = BLACK;                                           // Al ritorno della ricorsione si può settare il nodo a BLACK
    upo_destroy_list(list);
}
