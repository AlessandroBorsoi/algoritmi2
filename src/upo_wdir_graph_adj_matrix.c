#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <upo_priority_queue.h>
#include "upo_wdir_graph_adj_matrix.h"

/**
 * @brief Crea un nuovo grafo orientato
 *
 * @return un nuovo grafo diretto vuoto
 *
 */
upo_wdirgraph_t upo_wdirgraph_create()
{
    upo_wdirgraph_t graph = malloc(sizeof(struct upo_wdirgraph_s));
    if (graph == NULL)
    {
        perror("Unable to create the direct graph");
        abort();
    }
    graph->adj = NULL;
    graph->n = 0;
    return graph;
}

/**
 * @brief Distrugge un grafo liberando tutta la memoria
 *
 * @param graph il grafo da eliminare
 * @return 1 se l'operazione è andata a buon fine, -1 se il grafo e' nullo, 0 altrimenti
 *
 */
int upo_wdirgraph_destroy(upo_wdirgraph_t graph)
{
    if (graph == NULL)
        return -1;
    if (graph != NULL)
    {
        int n = upo_wnum_vertices(graph);
        for (int i = 0; i < n; i++)
            free(graph->adj[i]);
        free(graph->adj);
        free(graph);
        return 1;
    }
    return 0;
}

/**
 * @brief Restituisce il numero di vertici del grafo
 *
 * @param graph il grafo
 * @return il numero di vertici del grafo, -1 se il grafo e' nullo
 */
int upo_wnum_vertices(upo_wdirgraph_t graph)
{
    if (graph == NULL)
        return -1;
    return graph->n;
}

/**
 * @brief Aggiunge un nuovo vertice al grafo di indice size+1 (dove size è il numero di vertici)
 *
 * @param graph il grafo
 * @return 1 se l'operazione è andata a buon fine, -1 se il grafo e' nullo, 0 altrimenti
 *
 */
int upo_wadd_vertex(upo_wdirgraph_t graph)
{
    if (graph == NULL)
        return -1;
    if (graph != NULL)
    {
        int n = upo_wnum_vertices(graph);            // Controllo la dimensione della matrice attuale
        ++n;                                        // Incremento n alla nuova dimensione
        int** newAdj = calloc(sizeof(int*), n);     // Alloco lo spazio per una dimensione della matrice.
        if (newAdj == NULL)                         // Uso calloc per inizializzare a 0 gli elementi della nuova matrice.
        {
            perror("Unable to create the new adj matrix");
            abort();
        }
        for (int i = 0; i < n; i++)                 // Per ogni riga, alloco lo spazio per una colonna
        {
            newAdj[i] = calloc(sizeof(int), n);     // Uso calloc per inizializzare a 0 gli elementi della nuova matrice.
            if (newAdj[i] == NULL)
            {
                perror("Unable to create the new adj matrix row");
                abort();
            }
        }
        for (int i = 0; i < n - 1; i++)         
            for (int j = 0; j < n - 1; j++)
                newAdj[i][j] = graph->adj[i][j];    // Copio gli elementi della vecchia matrice in quella nuova maggiorata di 1
        int** oldAdj = graph->adj;                  // Memorizzo la vecchia matrice per poterne liberare la memoria
        graph->adj = newAdj;                        // Ora la struttura punta alla matrice con un vertice aggiunto
        graph->n = n;

        for (int i = 0; i < n - 1; i++)             // Libero lo spazio occupato dalla vecchia matrice
            free(oldAdj[i]);
        free(oldAdj);

        return 1;
    }
    return 0;
}

/**
 * @brief Controlla l'esistenza di un vertice di indice vertex nel grafo
 *
 * @param graph il grafo
 * @param vertex il vertice da cercare
 * @return 1 se il grafo contiene il vertice, -1 se il grafo e' nullo, 0 altrimenti
 */
int upo_whas_vertex(upo_wdirgraph_t graph, int vertex)
{
    if (graph == NULL)
        return -1;
    if (vertex < upo_wnum_vertices(graph))
        return 1;
    return 0;
}

/**
 * @brief Elimina un vertice di indice vertex dal grafo e tutti gli archi ad esso incidenti. Attenzione, le liste di adiacenza vanno aggiornate.
 *
 * @param graph il grafo
 * @param vertex il vertice da eliminare
 * @return 1 se l'operazione è andata a buon fine, -1 se il grafo e' nullo, 0 altrimenti
 */
int upo_wremove_vertex(upo_wdirgraph_t graph, int vertex)
{
    if (graph == NULL)
        return -1;
    int n = upo_wnum_vertices(graph);                // Controllo la dimensione della matrice attuale
    if (n > 0 && vertex < n)                        // Procedo alla rimozione di un vertice solo se ce ne sono
    {                                               // e se il vertice da eliminare è presente
        --n;                                        // Decremento la dimensione per la nuova matrice.
        int** newAdj = calloc(sizeof(int*), n);     // Uso calloc per inizializzare a 0 gli elementi della nuova matrice.
        if (newAdj == NULL)                         
        {
            perror("Unable to create the new adj matrix");
            abort();
        }
        for (int i = 0; i < n; i++)                 // Per ogni riga, alloco lo spazio per una colonna
        {
            newAdj[i] = calloc(sizeof(int), n);     // Uso calloc per inizializzare a 0 gli elementi della nuova matrice.
            if (newAdj[i] == NULL)
            {
                perror("Unable to create the new adj matrix row");
                abort();
            }
        }

        int iOffset = 0;                            // Gli offset servono per tenere traccia della riga e della colonna
        int jOffset = 0;                            // da 'saltare' durante la copia della matrice vecchia in quella nuova.
        for (int i = 0; i < n; i++)                 // Quando il loop arriva alla riga/colonna da eliminare, la salta aggiungendo
        {                                           // 1 agli indici e quindi non copiando la cella
            if (i >= vertex) 
                iOffset = 1;
            for (int j = 0; j < n; j++)
            {
                if (j >= vertex) 
                    jOffset = 1;
                newAdj[i][j] = graph->adj[i + iOffset][j + jOffset];    // Vengono copiati i valori dalla matrice vecchia a quella nuova
            }
            jOffset = 0;
        }
        int** oldAdj = graph->adj;                  // Memorizzo la vecchia matrice per poterne liberare la memoria
        graph->adj = newAdj;                        // Ora la struttura punta alla matrice con un vertice aggiunto
        graph->n = n;

        for (int i = 0; i < n + 1; i++)             // Libero lo spazio occupato dalla vecchia matrice
            free(oldAdj[i]);
        free(oldAdj);

        return 1;
    }
    return 0;
}

/**
 * @brief Aggiunge un arco al grafo. Se l'arco gia' esiste non fa nulla
 *
 * @param graph il grafo
 * @param vertex1 da dove esce l'arco
 * @param vertex2 dove entra l'arco
 * @param weight il peso dell'arco
 * @return 1 se l'operazione è andata a buon fine, -1 se il grafo e' nullo, 0 altrimenti
 */
int upo_wadd_edge(upo_wdirgraph_t graph, int vertex1, int vertex2, int weight)
{
    if (graph == NULL)
        return -1;
    int n = upo_wnum_vertices(graph);
    if (vertex1 < n && vertex2 < n)                     // Se i vertici esistono 
    {                                                   
        graph->adj[vertex1][vertex2] = weight;          // allora si aggiunge/modifica l'arco col peso
        return 1;
    }
    return 0;
}

/**
 * @brief Controlla l'esistenza di un arco nel grafo
 *
 * @param graph il grafo
 * @param vertex1 da dove esce l'arco
 * @param vertex2 dove entra l'arco
 * @return 1 se il grafo contiene l'arco, -1 se il grafo e' nullo, 0 altrimenti
 */
int upo_whas_edge(upo_wdirgraph_t graph, int vertex1, int vertex2)
{
    if (graph == NULL)
        return -1;
    int n = upo_wnum_vertices(graph);
    if (vertex1 < n && vertex2 < n)                             // Si controlla che i vertici esistano
        return (graph->adj[vertex1][vertex2] != 0 ? 1 : 0);    // e si ritorna 1 o 0
    return 0;
}

/**
 * @brief Rimuove un arco dal grafo
 *
 * @param graph il grafo
 * @param vertex1 da dove esce l'arco
 * @param vertex2 dove entra l'arco
 * @return 1 se l'operazione è andata a buon fine, -1 se il grafo e' nullo, 0 altrimenti
 */
int upo_wremove_edge(upo_wdirgraph_t graph, int vertex1, int vertex2)
{
    if (graph == NULL)
        return -1;
    int n = upo_wnum_vertices(graph);
    if (vertex1 < n && vertex2 < n && graph->adj[vertex1][vertex2] != 0)    // Viene rimosso l'arco solo se
    {                                                                       // i vertici esistono e l'arco è presente
        graph->adj[vertex1][vertex2] = 0;
        return 1;
    }
    return 0;
}

/**
 * @brief Restituisce il numero di archi del grafo
 *
 * @param graph il grafo
 * @return il numero di archi del grafo, -1 se il grafo e' nullo
 */
int upo_wnum_edges(upo_wdirgraph_t graph)
{
    if (graph == NULL)
        return -1;
    int n = upo_wnum_vertices(graph);
    int edges = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            edges += (graph->adj[i][j] != 0 ? 1 : 0);
    return edges;
}

/**
 * @brief Restituisce il peso di un arco del grafo
 *
 * @param graph il grafo
 * @param vertex1 da dove esce l'arco
 * @param vertex2 dove entra l'arco
 * @return il peso dell'arco del grafo, -1 se il grafo e' nullo, 0 altrimenti
 */
int upo_weight(upo_wdirgraph_t graph, int vertex1, int vertex2)
{
    if (graph == NULL)
        return -1;
    int n = upo_wnum_vertices(graph);
    if (vertex1 < n && vertex2 < n)
        return graph->adj[vertex1][vertex2];
    return 0;
}

/**
 * @brief Restituisce una lista contenente gli archi uscenti da vertex
 *
 * @param graph il grafo
 * @param vertex il vertice
 * @return una lista contenente gli archi uscenti da vertex, NULL se il grafo e' vuoto
 */
upo_list_t upo_wget_inc_out_edg(upo_wdirgraph_t graph, int vertex)
{
    upo_list_t list = NULL;
    int n = upo_wnum_vertices(graph);
    if (n > 0 && vertex < n)
    {
        list = upo_create_list(sizeof(struct upo_wdir_edge_s), NULL);            // Si crea una lista di edges
        for (int i = 0; i < n; i++)
        {
            if (graph->adj[vertex][i] != 0)                                     // Se l'arco è uscente lo si aggiunge alla lista
            {
                upo_wdir_edge_t element = malloc(sizeof(struct upo_wdir_edge_s));
                element->from = vertex;
                element->to = i;
                upo_add_last(list, element);
            }
        }
    }
    return list;
}

/**
 * @brief Restituisce una stringa rappresentante il grafo, nella forma Vertice: v;\n v -> i;\n v -> j\n dove i e j sono i vertici adiacenti a v
 *
 * @param graph il grafo
 * @return una stringa rappresentante il grafo
 */
char *upo_wprint_graph(upo_wdirgraph_t graph)
{
    char* string = NULL;
    int n = upo_wnum_vertices(graph);
    if (n > 0)
    {
        int pos = 0;
        int verticesBytes = sizeof(char) * 15 * n;                  // Calcolo lo spazio da allocare per la stringa
        int edgesBytes = sizeof(char) * 15 * upo_wnum_edges(graph);  // come somma dello spazio che mi serve per i vertici
        string = malloc(verticesBytes + edgesBytes);                // e per gli archi
        upo_list_t list = NULL;
        for (int i = 0; i < n; i++)                                 // Per ogni vertice stampo le informazioni richieste
        {                                                           // tenendo conto della posizione di 'append' nella stringa
            pos+= sprintf(&string[pos], "Vertice: %d;\n", i);
            list = upo_wget_inc_out_edg(graph, i);
            for (int j = 0; j < upo_list_size(list); j++)
            {
                int vertex1 = ((upo_wdir_edge_t)upo_get(list, j))->from;
                int vertex2 = ((upo_wdir_edge_t)upo_get(list, j))->to;
                pos+= sprintf(&string[pos], " %d -> %d; w: %d\n", vertex1, vertex2, upo_weight(graph, vertex1, vertex2));
            }
            upo_destroy_list(list);
        }
    }
    return string;
}

/**
 * @brief Restituisce il peso di un arco del grafo
 *
 * @param graph il grafo
 * @param s il nodo di origine
 * @return NULL se il grafo non esiste o è vuoto, altrimenti una matrice 2 per n dove la prima riga contiene
 * il vettore dei padri e la seconda le distanze calcolate da Dijkstra.
 */
int** cmDijkstra(upo_wdirgraph_t graph, int s)
{
    if (graph == NULL)                                          // Se il grafo è NULL o non ci sono vertici viene tornato NULL
        return NULL;
    int n = upo_wnum_vertices(graph);
    if (n < 1)
        return NULL;
    // INIZIALIZZA (G)
    int** mat = malloc(sizeof(int*) * 2);
    if (mat == NULL)
    {
        perror("Unable to create mat");
        abort();
    }
    for (int i = 0; i < 2; i++)                 // Per ogni riga, alloco lo spazio per una colonna
    {
        mat[i] = malloc(sizeof(int) * n);
        if (mat[i] == NULL)
        {
            perror("Unable to create the new mat row");
            abort();
        }
    }
    for (int i = 0; i < n; i++)
    {
        mat[0][i] = -1;
        mat[1][i] = 1000000;
    }
    // D <- empty_priority_queue()
    upo_priority_queue_t queue = upo_priority_queue_create();

    // d[s] <- 0
    mat[1][s] = 0;

    // for ogni v in V[G]
    //     enqueue(D,v,d[v])
    for (int i = 0; i < n; i++)
        upo_priority_queue_enqueue(queue, i, mat[1][i]);

    // while NotEmpty(D) do begin
    //     u <- dequeue_min(D)
    //     S <- S ∪ {u} //aggiungo u all’albero definitivamente
    //     for ogni v adj ad u then
    //         if d[v] > d[u] + W(u,v) then
    //              π[v] <- u
    //              d[v] <- d[u] + W(u,v)
    //              decrease_key(D,v,d[v])
    //     end for 
    // end
    while (upo_priority_queue_is_empty(queue) == 0)
    {
        int u = upo_priority_queue_dequeue(queue);
        upo_list_t list = upo_wget_inc_out_edg(graph, u);
        upo_iterator iterator = upo_get_list_iterator(list);
        while (iterator != NULL) 
        {
            upo_wdir_edge_t edge = (upo_wdir_edge_t)upo_get_iterator_element(iterator);
            int v = edge->to;
            if (mat[1][v] > mat[1][u] + upo_weight(graph, u, v))
            {
                mat[0][v] = u;
                mat[1][v] = mat[1][u] + upo_weight(graph, u, v);
                upo_priority_queue_update(queue, v, mat[1][v]);
            }
            iterator = upo_get_next(iterator);
        }
        upo_destroy_list(list);   
    }
    upo_priority_queue_destroy(queue);
    return mat;
}
