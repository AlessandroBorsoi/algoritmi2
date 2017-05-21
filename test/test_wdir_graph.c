#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <upo_wdir_graph.h>
#include <upo_priority_queue.h>

static void test_create_destroy();
static void test_add_remove_vertex();
static void test_add_remove_edges();
static void test_priority_queue();
static void test_dijkstra();

/**
* Funzioni testate:
* upo_wdirgraph_t upo_wdirgraph_create();
* int upo_wdirgraph_destroy(upo_wdirgraph_t graph);
*/
void test_create_destroy()
{
    upo_wdirgraph_t graph = NULL;

    assert(upo_wdirgraph_destroy(graph) == -1);

    graph = upo_wdirgraph_create();

    assert(graph != NULL);
    assert(upo_wdirgraph_destroy(graph) == 1);
}

/**
* Funzioni testate:
* int upo_wadd_vertex(upo_wdirgraph_t graph);
* int upo_wremove_vertex(upo_wdirgraph_t graph, int vertex);
* int upo_whas_vertex(upo_wdirgraph_t graph, int vertex);
* int upo_wnum_vertices(upo_wdirgraph_t graph);
*/
void test_add_remove_vertex()
{
    upo_wdirgraph_t graph = NULL;

    assert(upo_whas_vertex(graph, 0) == -1);
    assert(upo_wadd_vertex(graph) == -1);
    assert(upo_wnum_vertices(graph) == -1);
    assert(upo_wremove_vertex(graph, 0) == -1);

    graph = upo_wdirgraph_create();

    /**
    * Adj matrix n: 1
    *   0
    * 0 0
    */
    assert(upo_wadd_vertex(graph) == 1);
    assert(upo_whas_vertex(graph, 0) == 1);
    assert(upo_whas_vertex(graph, 1) == 0);
    assert(upo_wnum_vertices(graph) == 1);

    /**
    * Adj matrix n: 2
    *   0   1
    * 0 0   0
    * 1 0   0
    */
    assert(upo_wadd_vertex(graph) == 1);
    assert(upo_whas_vertex(graph, 1) == 1);
    assert(upo_wnum_vertices(graph) == 2);

    /**
    * Adj matrix n: 1
    *   0
    * 0 0
    */
    assert(upo_wremove_vertex(graph, 0) == 1);
    assert(upo_wremove_vertex(graph, 4) == 0);
    assert(upo_whas_vertex(graph, 1) == 0);
    assert(upo_wnum_vertices(graph) == 1);

    /**
    * Adj matrix n: 1
    *   0
    * 0 0
    */
    assert(upo_wremove_vertex(graph, 10) == 0);
    assert(upo_whas_vertex(graph, 10) == 0);
    assert(upo_wnum_vertices(graph) == 1);

    /**
    * Adj matrix n: 11
    *   0   1   2   3   4   5   6   7   8   9   10
    * 0 0   0   0   0   0   0   0   0   0   0   0
    * 1 0   0   0   0   0   0   0   0   0   0   0
    * 2 0   0   0   0   0   0   0   0   0   0   0
    * 3 0   0   0   0   0   0   0   0   0   0   0
    * 4 0   0   0   0   0   0   0   0   0   0   0
    * 5 0   0   0   0   0   0   0   0   0   0   0
    * 6 0   0   0   0   0   0   0   0   0   0   0
    * 7 0   0   0   0   0   0   0   0   0   0   0
    * 8 0   0   0   0   0   0   0   0   0   0   0
    * 9 0   0   0   0   0   0   0   0   0   0   0
    *10 0   0   0   0   0   0   0   0   0   0   0
    */
    for (int i = 0; i < 10; i++)
    {
        assert(upo_wadd_vertex(graph) == 1);
    }
    assert(upo_whas_vertex(graph, 10) == 1);
    assert(upo_whas_vertex(graph, 11) == 0);
    assert(upo_wnum_vertices(graph) == 11);
        
    /**
    * Adj matrix n: 0
    */
    while (upo_wnum_vertices(graph) > 0)
    {
        assert(upo_wremove_vertex(graph, upo_wnum_vertices(graph) - 1) == 1);
    }
    assert(upo_whas_vertex(graph, 0) == 0);
    assert(upo_wnum_vertices(graph) == 0);

    upo_wdirgraph_destroy(graph);
}

/**
* Funzioni testate:
* int upo_wadd_edge(upo_wdirgraph_t graph, int vertex1, int vertex2, int weight);
* int upo_wremove_edge(upo_wdirgraph_t graph, int vertex1, int vertex2);
* int upo_whas_edge(upo_wdirgraph_t graph, int vertex1, int vertex2);
* int upo_wnum_edges(upo_wdirgraph_t graph);
* int upo_weight(upo_wdirgraph_t graph, int vertex1, int vertex2);
*/
void test_add_remove_edges()
{
    upo_wdirgraph_t graph = NULL;

    assert(upo_wadd_edge(graph, 0, 1, 8) == -1);
    assert(upo_whas_edge(graph, 0, 1) == -1);
    assert(upo_wnum_edges(graph) == -1);
    assert(upo_wremove_edge(graph, 0, 1) == -1);
    assert(upo_weight(graph, 0, 1) == -1);

    graph = upo_wdirgraph_create();
    
    /**
    * Adj matrix n: 0
    */
    assert(upo_wadd_edge(graph, 0, 1, 4) == 0);
    assert(upo_whas_edge(graph, 0, 1) == 0);
    assert(upo_wnum_edges(graph) == 0);
    assert(upo_wremove_edge(graph, 0, 1) == 0);
    assert(upo_weight(graph, 0, 1) == 0);

    upo_wadd_vertex(graph);

    /**
    * Adj matrix n: 1
    */
    assert(upo_wadd_edge(graph, 0, 1, 6) == 0);
    assert(upo_whas_edge(graph, 0, 1) == 0);
    assert(upo_wnum_edges(graph) == 0);
    assert(upo_wremove_edge(graph, 0, 1) == 0);
    assert(upo_weight(graph, 0, 1) == 0);

    upo_wadd_vertex(graph);
    
    /**
    * Adj matrix n: 2
    *   0   1
    * 0 0   4
    * 1 0   0
    */
    assert(upo_wadd_edge(graph, 0, 1, 3) == 1);
    assert(upo_wadd_edge(graph, 0, 1, 4) == 1);
    assert(upo_wadd_edge(graph, 0, 2, 9) == 0);
    assert(upo_whas_edge(graph, 0, 1) == 1);
    assert(upo_wnum_edges(graph) == 1);
    assert(upo_weight(graph, 0, 1) == 4);
    assert(upo_weight(graph, 0, 2) == 0);

    /**
    * Adj matrix n: 2
    *   0   1
    * 0 0   0
    * 1 0   0
    */
    assert(upo_wremove_edge(graph, 0, 1) == 1);
    assert(upo_wremove_edge(graph, 0, 1) == 0);
    assert(upo_whas_edge(graph, 0, 1) == 0);
    assert(upo_wnum_edges(graph) == 0);
    assert(upo_weight(graph, 0, 1) == 0);

    /**
    * Adj matrix n: 2
    *   0   1
    * 0 0   -22
    * 1 2   0
    */
    assert(upo_wadd_edge(graph, 0, 1, -22) == 1);
    assert(upo_wadd_edge(graph, 1, 0, 2) == 1);
    assert(upo_whas_edge(graph, 0, 1) == 1);
    assert(upo_whas_edge(graph, 1, 0) == 1);
    assert(upo_wnum_edges(graph) == 2);
    assert(upo_weight(graph, 0, 1) == -22);
    assert(upo_weight(graph, 1, 0) == 2);

    /**
    * Adj matrix n: 2
    *   0   1
    * 0 0   1
    * 1 0   0
    */
    assert(upo_wremove_edge(graph, 1, 0) == 1);
    assert(upo_whas_edge(graph, 1, 0) == 0);
    assert(upo_whas_edge(graph, 0, 1) == 1);
    assert(upo_wnum_edges(graph) == 1);
    assert(upo_wremove_edge(graph, 1, 0) == 0);
    assert(upo_wnum_edges(graph) == 1);
    assert(upo_wremove_edge(graph, 0, 1) == 1);
    assert(upo_wnum_edges(graph) == 0);
    assert(upo_weight(graph, 0, 1) == 0);
    assert(upo_weight(graph, 1, 0) == 0);

    upo_wdirgraph_destroy(graph);
}

void test_priority_queue()
{
    upo_priority_queue_t queue = NULL;

    upo_priority_queue_enqueue(queue, 1, 3);
    upo_priority_queue_dequeue(queue);
    upo_priority_queue_update(queue, 1, 2);
    assert(upo_priority_queue_is_empty(queue) == 1);

    queue = upo_priority_queue_create();

    assert(queue != NULL);
    assert(upo_priority_queue_is_empty(queue) == 1);

    upo_priority_queue_enqueue(queue, 1, 3);
    upo_priority_queue_enqueue(queue, 5, 1);
    upo_priority_queue_enqueue(queue, 22, 0);
    upo_priority_queue_enqueue(queue, 2, 7);

    assert(upo_priority_queue_is_empty(queue) == 0);
    assert(upo_priority_queue_dequeue(queue) == 22);
    assert(upo_priority_queue_dequeue(queue) == 5);
    assert(upo_priority_queue_dequeue(queue) == 1);
    assert(upo_priority_queue_dequeue(queue) == 2);
    assert(upo_priority_queue_is_empty(queue) == 1);

    upo_priority_queue_enqueue(queue, 66, 5);
    upo_priority_queue_enqueue(queue, 66, 5);
    upo_priority_queue_enqueue(queue, 6, 6);

    assert(upo_priority_queue_is_empty(queue) == 0);

    upo_priority_queue_update(queue, 6, 4);

    assert(upo_priority_queue_dequeue(queue) == 6);
    assert(upo_priority_queue_dequeue(queue) == 66);
    assert(upo_priority_queue_is_empty(queue) == 1);
    
    upo_priority_queue_destroy(queue);
}

/**
* Funzioni testate:
* int** cmDijkstra(upo_wdirgraph_t graph, int s);
*/
void test_dijkstra()
{
    upo_wdirgraph_t graph = NULL;
    
    assert(cmDijkstra(graph, 0) == NULL);

    graph = upo_wdirgraph_create();

    assert(cmDijkstra(graph, 0) == NULL);

    upo_wadd_vertex(graph);
    upo_wadd_vertex(graph);
    upo_wadd_vertex(graph);
    upo_wadd_vertex(graph);
    upo_wadd_vertex(graph);
    upo_wadd_edge(graph, 0, 1, 3);
    upo_wadd_edge(graph, 0, 2, 2);
    upo_wadd_edge(graph, 0, 3, 4);
    upo_wadd_edge(graph, 1, 4, 3);
    upo_wadd_edge(graph, 2, 3, 3);
    upo_wadd_edge(graph, 3, 4, 1);

    int** mat = cmDijkstra(graph, 0);

    assert(mat[0][0] == -1);
    assert(mat[0][1] == 0);
    assert(mat[0][2] == 0);
    assert(mat[0][3] == 0);
    assert(mat[0][4] == 3);

    assert(mat[1][0] == 0);
    assert(mat[1][1] == 3);
    assert(mat[1][2] == 2);
    assert(mat[1][3] == 4);
    assert(mat[1][4] == 5);

    free(mat[0]);
    free(mat[1]);
    free(mat);

    upo_wdirgraph_destroy(graph);
}

int main()
{
    printf("Test case 'create/destroy'... ");
    fflush(stdout);
    test_create_destroy();
    printf("OK\n");

    printf("Test case 'add/remove vertices'... ");
    fflush(stdout);
    test_add_remove_vertex();
    printf("OK\n");

    printf("Test case 'add/remove edges'... ");
    fflush(stdout);
    test_add_remove_edges();
    printf("OK\n");

    printf("Test case 'priority queue'... ");
    fflush(stdout);
    test_priority_queue();
    printf("OK\n");

    printf("Test case 'Dijkstra'... ");
    fflush(stdout);
    test_dijkstra();
    printf("OK\n");

    return 0;
}
