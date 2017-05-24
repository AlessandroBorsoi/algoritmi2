#ifndef UPO_WDIR_GRAPH_H
#define UPO_WDIR_GRAPH_H

#include "upo_list.h"

typedef struct upo_wdirgraph_s *upo_wdirgraph_t;
typedef struct upo_wdir_edge_s *upo_wdir_edge_t;

/**
 * @brief Definizione della struttura per rappresentare un arco diretto
 */
struct upo_wdir_edge_s
{
    int from; /**< Vertice da cui l'arco esce. */
    int to;   /**< Vertice nel quale l'arco entra. */
};

/**
 * @brief Crea un nuovo grafo orientato
 *
 * @return un nuovo grafo diretto vuoto
 *
 */
upo_wdirgraph_t upo_wdirgraph_create();

/**
 * @brief Distrugge un grafo liberando tutta la memoria
 *
 * @param graph il grafo da eliminare
 * @return 1 se l'operazione è andata a buon fine, -1 se il grafo e' nullo, 0 altrimenti
 *
 */
int upo_wdirgraph_destroy(upo_wdirgraph_t graph);

/**
 * @brief Restituisce il numero di vertici del grafo
 *
 * @param graph il grafo
 * @return il numero di vertici del grafo, -1 se il grafo e' nullo
 */
int upo_wnum_vertices(upo_wdirgraph_t graph);

/**
 * @brief Aggiunge un nuovo vertice al grafo di indice size+1 (dove size è il numero di vertici)
 *
 * @param graph il grafo
 * @return 1 se l'operazione è andata a buon fine, -1 se il grafo e' nullo, 0 altrimenti
 *
 */
int upo_wadd_vertex(upo_wdirgraph_t graph);

/**
 * @brief Controlla l'esistenza di un vertice di indice vertex nel grafo
 *
 * @param graph il grafo
 * @param vertex il vertice da cercare
 * @return 1 se il grafo contiene il vertice, -1 se il grafo e' nullo, 0 altrimenti
 */
int upo_whas_vertex(upo_wdirgraph_t graph, int vertex);

/**
 * @brief Elimina un vertice di indice vertex dal grafo e tutti gli archi ad esso incidenti. Attenzione, le liste di adiacenza vanno aggiornate.
 *
 * @param graph il grafo
 * @param vertex il vertice da eliminare
 * @return 1 se l'operazione è andata a buon fine, -1 se il grafo e' nullo, 0 altrimenti
 */
int upo_wremove_vertex(upo_wdirgraph_t graph, int vertex);

/**
 * @brief Aggiunge un arco al grafo. Se l'arco gia' esiste non fa nulla
 *
 * @param graph il grafo
 * @param vertex1 da dove esce l'arco
 * @param vertex2 dove entra l'arco
 * @param weight il peso dell'arco
 * @return 1 se l'operazione è andata a buon fine, -1 se il grafo e' nullo, 0 altrimenti
 */
int upo_wadd_edge(upo_wdirgraph_t graph, int vertex1, int vertex2, int weight);

/**
 * @brief Controlla l'esistenza di un arco nel grafo
 *
 * @param graph il grafo
 * @param vertex1 da dove esce l'arco
 * @param vertex2 dove entra l'arco
 * @return 1 se il grafo contiene l'arco, -1 se il grafo e' nullo, 0 altrimenti
 */
int upo_whas_edge(upo_wdirgraph_t graph, int vertex1, int vertex2);

/**
 * @brief Rimuove un arco dal grafo
 *
 * @param graph il grafo
 * @param vertex1 da dove esce l'arco
 * @param vertex2 dove entra l'arco
 * @return 1 se l'operazione è andata a buon fine, -1 se il grafo e' nullo, 0 altrimenti
 */
int upo_wremove_edge(upo_wdirgraph_t graph, int vertex1, int vertex2);

/**
 * @brief Restituisce il numero di archi del grafo
 *
 * @param graph il grafo
 * @return il numero di archi del grafo, -1 se il grafo e' nullo
 */
int upo_wnum_edges(upo_wdirgraph_t graph);

/**
 * @brief Restituisce il peso di un arco del grafo
 *
 * @param graph il grafo
 * @param vertex1 da dove esce l'arco
 * @param vertex2 dove entra l'arco
 * @return il peso dell'arco del grafo, -1 se il grafo e' nullo, 0 altrimenti
 */
int upo_weight(upo_wdirgraph_t graph, int vertex1, int vertex2);

/**
 * @brief Restituisce una lista contenente gli archi uscenti da vertex
 *
 * @param graph il grafo
 * @param vertex il vertice
 * @return una lista contenente gli archi uscenti da vertex, NULL se il grafo e' vuoto
 */
upo_list_t upo_wget_inc_out_edg(upo_wdirgraph_t graph, int vertex);


/**
 * @brief Restituisce una stringa rappresentante il grafo, nella forma Vertice: v;\n v -> i;\n v -> j\n dove i e j sono i vertici adiacenti a v
 *
 * @param graph il grafo
 * @return una stringa rappresentante il grafo
 */
char *upo_wprint_graph(upo_wdirgraph_t graph);

/**
 * @brief Restituisce il peso di un arco del grafo
 *
 * @param graph il grafo
 * @param s il nodo di origine
 * @return NULL se il grafo non esiste o è vuoto, altrimenti una matrice 2 per n dove la prima riga contiene
 * il vettore dei padri e la seconda le distanze calcolate da Dijkstra.
 */
int** cmDijkstra(upo_wdirgraph_t graph, int s);

#endif /* UPO_WDIR_GRAPH_H */
