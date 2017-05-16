#ifndef UPO_WDIR_GRAPH_ADJ_MATRIX_H
#define UPO_WDIR_GRAPH_ADJ_MATRIX_H

#include "upo_wdir_graph.h"

/**
 * @brief Definizione della struttura per rappresentare un grafo pesato con matrice di adiacenza
 */
struct upo_wdirgraph_s
{
    int **adj; /**< Matrice di adiacenza. */
    int n;     /**< Numero di nodi del grafo. */
};

#endif /* UPO_WDIR_GRAPH_ADJ_MATRIX_H */
