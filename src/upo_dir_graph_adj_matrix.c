#include "upo_dir_graph_adj_matrix.h"

/**
 * @brief Crea un nuovo grafo orientato
 *
 * @return un nuovo grafo diretto vuoto
 *
 */
upo_dirgraph_t upo_dirgraph_create(int n)
{
    upo_dirgraph_t graph = malloc(sizeof(struct upo_dirgraph_s));
    if (graph == NULL)
    {
        perror("Unable to create the direct graph");
        abort();
    }
    graph->adj = NULL;
    graph->n = n;
    return graph;
}

/**
 * @brief Distrugge un grafo liberando tutta la memoria
 *
 * @param graph il grafo da eliminare
 * @return 1 se l'operazione è andata a buon fine, -1 se il grafo e' nullo, 0 altrimenti
 *
 */
int upo_dirgraph_destroy(upo_dirgraph_t graph)
{
    if (graph != NULL)
    {
        int n = upo_num_vertices(graph);
        if (n > 0)
        {
            for (int i = 0; i < n; i++)
                free(graph->adj[i]);
            free(graph->adj);
        }
        free(graph);
        return 1;
    }
    if (graph == NULL)
        return -1;
    return 0;
}

/**
 * @brief Restituisce il numero di vertici del grafo
 *
 * @param graph il grafo
 * @return il numero di vertici del grafo, -1 se il grafo e' nullo
 */
int upo_num_vertices(upo_dirgraph_t graph)
{
    if (graph == NULL)
        return -1;
    return graph->n;
}

/**
 * @brief Restituisce il numero di archi del grafo
 *
 * @param graph il grafo
 * @return il numero di archi del grafo, -1 se il grafo e' nullo
 */
int upo_num_edges(upo_dirgraph_t graph)
{
    if (graph == NULL)
        return -1;
    int n = upo_num_vertices(graph);
    int edges = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            edges += graph->adj[i][j];
    return edges;
}

/**
 * @brief Restituisce il grado entrante di un vertice
 *
 * @param graph il grafo
 * @param vertex il vertice
 * @return il grado entrante di vertex, -1 se il grafo e' nullo
 */
int upo_get_in_degree(upo_dirgraph_t graph, int vertex)
{
    if (graph == NULL)
        return -1;
    int n = upo_num_vertices(graph);
    int degree = 0;
    if (n > 0 && vertex < n)
        for (int i = 0; i < n; i++)
            degree += graph->adj[i][vertex];
    return degree;
}

/**
 * @brief Restituisce il grado uscente di un vertice
 *
 * @param graph il grafo
 * @param vertex il vertice
 * @return il grado uscente di vertex, -1 se il grafo e' nullo
 */
int upo_get_out_degree(upo_dirgraph_t graph, int vertex)
{
    if (graph == NULL)
        return -1;
    int n = upo_num_vertices(graph);
    int degree = 0;
    if (n > 0 && vertex < n)
        for (int i = 0; i < n; i++)
            degree += graph->adj[vertex][i];
    return degree;
}

/**
 * @brief Restituisce il grado complessivo di un vertice
 *
 * @param graph il grafo
 * @param vertex il vertice
 * @return il grado complessivo di vertex, -1 se il grafo e' nullo
 */
int upo_get_degree(upo_dirgraph_t graph, int vertex)
{
    if (graph == NULL)
        return -1;
    return upo_get_in_degree(graph, vertex) + upo_get_out_degree(graph, vertex);
}

/**
 * @brief Controlla se il grafo e' vuoto
 *
 * @param graph il grafo
 * @return 1 se il grafo e' vuoto, -1 se il grafo e' nullo, 0 altrimenti
 */
int upo_is_graph_empty(upo_dirgraph_t graph)
{
    if (graph == NULL)
        return -1;
    if (upo_num_vertices(graph) == 0)
        return 1;
    return 0;
}

/**
 * @brief Restituisce una lista contenente i vertici adiacenti a vertex
 *
 * @param graph il grafo
 * @param vertex il vertice
 * @return una lista contenente i vertici adiacenti a vertex, NULL se il grafo e' vuoto
 */
upo_list upo_get_adj_vert(upo_dirgraph_t graph, int vertex)
{
    upo_list* list = NULL;
    int n = upo_num_vertices(graph);
    if (graph != NULL && n > 0)
    {
        list = upo_create_list(sizeof(int), NULL);
        for (int i = 0; i < n; i++)
        {
            if (graph->adj[i][vertex] == 1)
            {
                int* element = malloc(sizeof(int));
                upo_add_last(list, element);
            }
        }
    }
    return *list;
}

/**
 * @brief Restituisce una lista contenente gli archi uscenti da vertex
 *
 * @param graph il grafo
 * @param vertex il vertice
 * @return una lista contenente gli archi uscenti da vertex, NULL se il grafo e' vuoto
 */
upo_list upo_get_inc_out_edg(upo_dirgraph_t graph, int vertex)
{
    upo_list* list = NULL;
    int n = upo_num_vertices(graph);
    if (graph != NULL && n > 0)
    {
        list = upo_create_list(sizeof(struct upo_dir_edge_s), NULL);
        for (int i = 0; i < n; i++)
        {
            if (graph->adj[vertex][i] == 1)
            {
                upo_dir_edge_t element = malloc(sizeof(struct upo_dir_edge_s));
                element->from = vertex;
                element->to = i;
                upo_add_last(list, element);
            }
        }
    }
    return *list;
}

/**
 * @brief Restituisce una lista contenente gli archi entranti in vertex
 *
 * @param graph il grafo
 * @param vertex il vertice
 * @return una lista contenente gli archi archi entranti in vertex, NULL se il grafo e' vuoto
 */
upo_list upo_get_inc_in_edg(upo_dirgraph_t graph, int vertex)
{
    upo_list* list = NULL;
    int n = upo_num_vertices(graph);
    if (graph != NULL && n > 0)
    {
        list = upo_create_list(sizeof(struct upo_dir_edge_s), NULL);
        for (int i = 0; i < n; i++)
        {
            if (graph->adj[i][vertex] == 1)
            {
                upo_dir_edge_t element = malloc(sizeof(struct upo_dir_edge_s));
                element->from = i;
                element->to = vertex;
                upo_add_last(list, element);
            }
        }
    }
    return *list;
}

/**
 * @brief Restituisce una lista contenente gli archi incidenti a vertex
 *
 * @param graph il grafo
 * @param vertex il vertice
 * @return una lista contenente gli archi incidenti a vertex, NULL se il grafo e' vuoto
 */
upo_list upo_get_inc_edg(upo_dirgraph_t graph, int vertex)
{
    fprintf(stderr, "To be implemented!\n");
    abort();
}

/**
 * @brief Aggiunge un nuovo vertice al grafo di indice size+1 (dove size è il numero di vertici)
 *
 * @param graph il grafo
 * @return 1 se l'operazione è andata a buon fine, -1 se il grafo e' nullo, 0 altrimenti
 *
 */
int upo_add_vertex(upo_dirgraph_t graph)
{
    if (graph == NULL)
        return -1;
    if (graph != NULL)
    {
        int n = upo_num_vertices(graph);
        ++n;
        int** newAdj = malloc(sizeof(int*) * n);
        for (int i = 0; i < n; i++)
            newAdj[i] = malloc(sizeof(int) * n);

        for (int i = 0; i < n - 1; i++)
            for (int j = 0; j < n - 1; j++)
                newAdj[i][j] = graph->adj[i][j];
        graph->adj = newAdj;
        graph->n = n;

        // TODO: free old matrix and malloc checks

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
int upo_has_vertex(upo_dirgraph_t graph, int vertex)
{
    if (graph == NULL)
        return -1;
    if (vertex < upo_num_vertices(graph))
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
int upo_remove_vertex(upo_dirgraph_t graph, int vertex)
{
    if (graph == NULL)
        return -1;
    int n = upo_num_vertices(graph);
    if (n > 0 && vertex < n)
    {
        --n;
        int** newAdj = malloc(sizeof(int*) * n);
        for (int i = 0; i < n; i++)
            newAdj[i] = malloc(sizeof(int) * n);

        int iOffset = 0;
        int jOffset = 0;
        for (int i = 0; i < n; i++)
        {
            if (i >= vertex) iOffset = 1;
            for (int j = 0; j < n; j++)
            {
                if (j >= vertex) jOffset = 1;
                newAdj[i][j] = graph->adj[i + iOffset][j + jOffset];
            }
            jOffset = 0;
        }
        graph->adj = newAdj;
        graph->n = n;

        // TODO: free old matrix and malloc checks

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
 * @return 1 se l'operazione è andata a buon fine, -1 se il grafo e' nullo, 0 altrimenti
 */
int upo_add_edge(upo_dirgraph_t graph, int vertex1, int vertex2)
{
    if (graph == NULL)
        return -1;
    int n = upo_num_vertices(graph);
    if (vertex1 < n && vertex2 < n && graph->adj[vertex1][vertex2] == 0)
        return graph->adj[vertex1][vertex2] = 1;
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
int upo_has_edge(upo_dirgraph_t graph, int vertex1, int vertex2)
{
    if (graph == NULL)
        return -1;
    int n = upo_num_vertices(graph);
    if (vertex1 < n && vertex2 < n)
        return graph->adj[vertex1][vertex2];
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
int upo_remove_edge(upo_dirgraph_t graph, int vertex1, int vertex2)
{
    if (graph == NULL)
        return -1;
    int n = upo_num_vertices(graph);
    if (vertex1 < n && vertex2 < n && graph->adj[vertex1][vertex2] == 1)
    {
        graph->adj[vertex1][vertex2] = 0;
        return 1;
    }
    return 0;
}

/**
 * @brief Controlla se due vertici sono adiacenti
 *
 * @param graph il grafo
 * @param vertex1 il primo vertice
 * @param vertex2 il secondo vertice
 * @return 1 se i vertici sono adiacenti, -1 se il grafo e' nullo, 0 altrimenti
 */
int upo_are_adj(upo_dirgraph_t graph, int vertex1, int vertex2)
{
    fprintf(stderr, "To be implemented!\n");
    abort();
}

/**
 * @brief Restituisce una stringa rappresentante il grafo, nella forma Vertice: v;\n v -> i;\n v -> j\n dove i e j sono i vertici adiacenti a v
 *
 * @param graph il grafo
 * @return una stringa rappresentante il grafo
 */
char *upo_print_graph(upo_dirgraph_t graph)
{
    fprintf(stderr, "To be implemented!\n");
    abort();
}
