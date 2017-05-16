#include <stdio.h>
#include <stdlib.h>
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
