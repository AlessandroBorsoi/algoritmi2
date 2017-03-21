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
    if (graph == NULL)
        return -1;
    if (graph != NULL)
    {
        int n = upo_num_vertices(graph);
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
upo_list *upo_get_adj_vert(upo_dirgraph_t graph, int vertex)
{
    upo_list* list = NULL;
    int n = upo_num_vertices(graph);
    if (n > 0)
    {
        list = upo_create_list(sizeof(int), NULL);      // Si crea una lista di interi
        for (int i = 0; i < n; i++)
        {
            if (upo_are_adj(graph, vertex, i) == 1)     // Se il vertice è adiacente allora si inserisce
            {                                           // come ultimo elemento della lista
                int* element = malloc(sizeof(int));
                *element = i;
                upo_add_last(list, element);
            }
        }
    }
    return list;
}

/**
 * @brief Restituisce una lista contenente gli archi uscenti da vertex
 *
 * @param graph il grafo
 * @param vertex il vertice
 * @return una lista contenente gli archi uscenti da vertex, NULL se il grafo e' vuoto
 */
upo_list *upo_get_inc_out_edg(upo_dirgraph_t graph, int vertex)
{
    upo_list* list = NULL;
    int n = upo_num_vertices(graph);
    if (n > 0)
    {
        list = upo_create_list(sizeof(struct upo_dir_edge_s), NULL);            // Si crea una lista di edges
        for (int i = 0; i < n; i++)
        {
            if (graph->adj[vertex][i] == 1)                                     // Se l'arco è uscente lo si aggiunge alla lista
            {
                upo_dir_edge_t element = malloc(sizeof(struct upo_dir_edge_s));
                element->from = vertex;
                element->to = i;
                upo_add_last(list, element);
            }
        }
    }
    return list;
}

/**
 * @brief Restituisce una lista contenente gli archi entranti in vertex
 *
 * @param graph il grafo
 * @param vertex il vertice
 * @return una lista contenente gli archi archi entranti in vertex, NULL se il grafo e' vuoto
 */
upo_list *upo_get_inc_in_edg(upo_dirgraph_t graph, int vertex)
{
    upo_list* list = NULL;
    int n = upo_num_vertices(graph);
    if (n > 0)
    {
        list = upo_create_list(sizeof(struct upo_dir_edge_s), NULL);            // Si crea una lista di edges
        for (int i = 0; i < n; i++)
        {
            if (graph->adj[i][vertex] == 1)                                     // Se l'arco è entrante lo si aggiunge alla lista
            {
                upo_dir_edge_t element = malloc(sizeof(struct upo_dir_edge_s));
                element->from = i;
                element->to = vertex;
                upo_add_last(list, element);
            }
        }
    }
    return list;
}

/**
 * @brief Restituisce una lista contenente gli archi incidenti a vertex
 *
 * @param graph il grafo
 * @param vertex il vertice
 * @return una lista contenente gli archi incidenti a vertex, NULL se il grafo e' vuoto
 */
upo_list *upo_get_inc_edg(upo_dirgraph_t graph, int vertex)
{
    upo_list* list = NULL;
    int n = upo_num_vertices(graph);
    if (n > 0)
    {
        list = upo_create_list(sizeof(struct upo_dir_edge_s), NULL);            // Si crea una lista di edges
        for (int i = 0; i < n; i++)
        {
            if (graph->adj[vertex][i] == 1)                                     // Se l'arco è uscente lo si aggiunge alla lista
            {
                upo_dir_edge_t element = malloc(sizeof(struct upo_dir_edge_s));
                element->from = vertex;
                element->to = i;
                upo_add_last(list, element);
            }
            if (graph->adj[i][vertex] == 1)                                     // Se l'arco è entrante lo si aggiunge alla lista
            {
                upo_dir_edge_t element = malloc(sizeof(struct upo_dir_edge_s)); 
                element->from = i;
                element->to = vertex;
                upo_add_last(list, element);
            }
        }
    }
    return list;
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
        int n = upo_num_vertices(graph);            // Controllo la dimensione della matrice attuale
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
    int n = upo_num_vertices(graph);                // Controllo la dimensione della matrice attuale
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
 * @return 1 se l'operazione è andata a buon fine, -1 se il grafo e' nullo, 0 altrimenti
 */
int upo_add_edge(upo_dirgraph_t graph, int vertex1, int vertex2)
{
    if (graph == NULL)
        return -1;
    int n = upo_num_vertices(graph);
    if (vertex1 < n && vertex2 < n && graph->adj[vertex1][vertex2] == 0)    // Se i vertici esistono e non è presente un arco
    {                                                                       // allora lo si aggiunge
        graph->adj[vertex1][vertex2] = 1;
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
int upo_has_edge(upo_dirgraph_t graph, int vertex1, int vertex2)
{
    if (graph == NULL)
        return -1;
    int n = upo_num_vertices(graph);
    if (vertex1 < n && vertex2 < n)             // Si controlla che i vertici esistano
        return graph->adj[vertex1][vertex2];    // e si ritorna 1 o 0
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
    if (vertex1 < n && vertex2 < n && graph->adj[vertex1][vertex2] == 1)    // Viene rimosso l'arco solo se
    {                                                                       // i vertici esistono e l'arco è presente
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
    if (graph == NULL)
        return -1;
    int n = upo_num_vertices(graph);
    if (vertex1 < n && vertex2 < n)             // Controllo che i vertici richiesti esistano
        return graph->adj[vertex2][vertex1];    // Per controllare che il vertice 1 sia adiacente al vertice 2
    return 0;                                   // occorre invertire gli indici
}

/**
 * @brief Restituisce una stringa rappresentante il grafo, nella forma Vertice: v;\n v -> i;\n v -> j\n dove i e j sono i vertici adiacenti a v
 *
 * @param graph il grafo
 * @return una stringa rappresentante il grafo
 */
char *upo_print_graph(upo_dirgraph_t graph)
{
    char* string = NULL;
    int n = upo_num_vertices(graph);
    if (n > 0)
    {
        int pos = 0;
        int verticesBytes = sizeof(char) * 15 * n;                  // Calcolo lo spazio da allocare per la stringa
        int edgesBytes = sizeof(char) * 15 * upo_num_edges(graph);  // come somma dello spazio che mi serve per i vertici
        string = malloc(verticesBytes + edgesBytes);                // e per gli archi
        upo_list* list = NULL;
        for (int i = 0; i < n; i++)                                 // Per ogni vertice stampo le informazioni richieste
        {                                                           // tenendo conto della posizione di 'append' nella stringa
            pos+= sprintf(&string[pos], "Vertice: %d;\n", i);
            list = upo_get_inc_out_edg(graph, i);
            for (int j = 0; j < upo_list_size(list); j++)
                pos+= sprintf(&string[pos], " %d -> %d;\n", ((upo_dir_edge_t)upo_get(list, j))->from, ((upo_dir_edge_t)upo_get(list, j))->to);
            upo_destroy_list(list);
        }
    }
    return string;
}
