#include <stdio.h>
#include <upo_dir_graph.h>
#include <upo_visit.h>

static void test_create_destroy();
static void test_add_remove_vertex();
static void test_add_remove_edges();
static void test_vertex_degree();
static void test_adjacency();
static void test_incidence();
static void test_print_graph();
static void test_BFS();
static void test_DFS_tot();
static void test_cyclic_DAG();
static void test_topological_sort();
static void test_strongly_connected_components();

/**
* Funzioni testate:
* upo_dirgraph_t upo_dirgraph_create();
* int upo_dirgraph_destroy(upo_dirgraph_t graph);
*/
void test_create_destroy()
{
    upo_dirgraph_t graph = NULL;

    assert(upo_dirgraph_destroy(graph) == -1);

    graph = upo_dirgraph_create();

    assert(graph != NULL);
    assert(upo_dirgraph_destroy(graph) == 1);
}

/**
* Funzioni testate:
* int upo_add_vertex(upo_dirgraph_t graph);
* int upo_remove_vertex(upo_dirgraph_t graph, int vertex);
* int upo_has_vertex(upo_dirgraph_t graph, int vertex);
* int upo_num_vertices(upo_dirgraph_t graph);
*/
void test_add_remove_vertex()
{
    upo_dirgraph_t graph = NULL;

    assert(upo_has_vertex(graph, 0) == -1);
    assert(upo_add_vertex(graph) == -1);
    assert(upo_num_vertices(graph) == -1);
    assert(upo_remove_vertex(graph, 0) == -1);

    graph = upo_dirgraph_create();

    /**
    * Adj matrix n: 1
    *   0
    * 0 0
    */
    assert(upo_add_vertex(graph) == 1);
    assert(upo_has_vertex(graph, 0) == 1);
    assert(upo_has_vertex(graph, 1) == 0);
    assert(upo_num_vertices(graph) == 1);

    /**
    * Adj matrix n: 2
    *   0   1
    * 0 0   0
    * 1 0   0
    */
    assert(upo_add_vertex(graph) == 1);
    assert(upo_has_vertex(graph, 1) == 1);
    assert(upo_num_vertices(graph) == 2);

    /**
    * Adj matrix n: 1
    *   0
    * 0 0
    */
    assert(upo_remove_vertex(graph, 0) == 1);
    assert(upo_remove_vertex(graph, 4) == 0);
    assert(upo_has_vertex(graph, 1) == 0);
    assert(upo_num_vertices(graph) == 1);

    /**
    * Adj matrix n: 1
    *   0
    * 0 0
    */
    assert(upo_remove_vertex(graph, 10) == 0);
    assert(upo_has_vertex(graph, 10) == 0);
    assert(upo_num_vertices(graph) == 1);

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
        assert(upo_add_vertex(graph) == 1);
    }
    assert(upo_has_vertex(graph, 10) == 1);
    assert(upo_has_vertex(graph, 11) == 0);
    assert(upo_num_vertices(graph) == 11);
        
    /**
    * Adj matrix n: 0
    */
    while (upo_num_vertices(graph) > 0)
    {
        assert(upo_remove_vertex(graph, upo_num_vertices(graph) - 1) == 1);
    }
    assert(upo_has_vertex(graph, 0) == 0);
    assert(upo_num_vertices(graph) == 0);

    upo_dirgraph_destroy(graph);
}

/**
* Funzioni testate:
* int upo_add_edge(upo_dirgraph_t graph, int vertex1, int vertex2);
* int upo_remove_edge(upo_dirgraph_t graph, int vertex1, int vertex2);
* int upo_has_edge(upo_dirgraph_t graph, int vertex1, int vertex2);
* int upo_num_edges(upo_dirgraph_t graph);
*/
void test_add_remove_edges()
{
    upo_dirgraph_t graph = NULL;

    assert(upo_add_edge(graph, 0, 1) == -1);
    assert(upo_has_edge(graph, 0, 1) == -1);
    assert(upo_num_edges(graph) == -1);
    assert(upo_remove_edge(graph, 0, 1) == -1);

    graph = upo_dirgraph_create();
    
    /**
    * Adj matrix n: 0
    */
    assert(upo_add_edge(graph, 0, 1) == 0);
    assert(upo_has_edge(graph, 0, 1) == 0);
    assert(upo_num_edges(graph) == 0);
    assert(upo_remove_edge(graph, 0, 1) == 0);

    upo_add_vertex(graph);

    /**
    * Adj matrix n: 1
    */
    assert(upo_add_edge(graph, 0, 1) == 0);
    assert(upo_has_edge(graph, 0, 1) == 0);
    assert(upo_num_edges(graph) == 0);
    assert(upo_remove_edge(graph, 0, 1) == 0);

    upo_add_vertex(graph);
    
    /**
    * Adj matrix n: 2
    *   0   1
    * 0 0   1
    * 1 0   0
    */
    assert(upo_add_edge(graph, 0, 1) == 1);
    assert(upo_add_edge(graph, 0, 1) == 0);
    assert(upo_add_edge(graph, 0, 2) == 0);
    assert(upo_has_edge(graph, 0, 1) == 1);
    assert(upo_num_edges(graph) == 1);

    /**
    * Adj matrix n: 2
    *   0   1
    * 0 0   0
    * 1 0   0
    */
    assert(upo_remove_edge(graph, 0, 1) == 1);
    assert(upo_remove_edge(graph, 0, 1) == 0);
    assert(upo_has_edge(graph, 0, 1) == 0);
    assert(upo_num_edges(graph) == 0);

    /**
    * Adj matrix n: 2
    *   0   1
    * 0 0   1
    * 1 1   0
    */
    assert(upo_add_edge(graph, 0, 1) == 1);
    assert(upo_add_edge(graph, 1, 0) == 1);
    assert(upo_has_edge(graph, 0, 1) == 1);
    assert(upo_has_edge(graph, 1, 0) == 1);
    assert(upo_num_edges(graph) == 2);

    /**
    * Adj matrix n: 2
    *   0   1
    * 0 0   1
    * 1 0   0
    */
    assert(upo_remove_edge(graph, 1, 0) == 1);
    assert(upo_has_edge(graph, 1, 0) == 0);
    assert(upo_has_edge(graph, 0, 1) == 1);
    assert(upo_num_edges(graph) == 1);
    assert(upo_remove_edge(graph, 1, 0) == 0);
    assert(upo_num_edges(graph) == 1);
    assert(upo_remove_edge(graph, 0, 1) == 1);
    assert(upo_num_edges(graph) == 0);

    upo_dirgraph_destroy(graph);
}

/**
* Funzioni testate:
* int upo_get_in_degree(upo_dirgraph_t graph, int vertex);
* int upo_get_out_degree(upo_dirgraph_t graph, int vertex);
* int upo_get_degree(upo_dirgraph_t graph, int vertex);
*/
void test_vertex_degree()
{
    upo_dirgraph_t graph = NULL;

    assert(upo_get_in_degree(graph, 0) == -1);
    assert(upo_get_out_degree(graph, 0) == -1);
    assert(upo_get_degree(graph, 0) == -1);
    
    graph = upo_dirgraph_create();
    
    assert(upo_get_in_degree(graph, 0) == 0);
    assert(upo_get_out_degree(graph, 0) == 0);
    assert(upo_get_degree(graph, 0) == 0);
    
    assert(upo_get_in_degree(graph, 1) == 0);
    assert(upo_get_out_degree(graph, 1) == 0);
    assert(upo_get_degree(graph, 1) == 0);

    /**
    * Adj matrix n: 2
    *   0   1
    * 0 0   1
    * 1 0   0
    */
    upo_add_vertex(graph);
    upo_add_vertex(graph);
    upo_add_edge(graph, 0, 1);
    
    assert(upo_get_in_degree(graph, 0) == 0);
    assert(upo_get_in_degree(graph, 1) == 1);
    assert(upo_get_out_degree(graph, 0) == 1);
    assert(upo_get_out_degree(graph, 1) == 0);
    assert(upo_get_degree(graph, 0) == 1);
    assert(upo_get_degree(graph, 1) == 1);

    /**
    * Adj matrix n: 3
    *   0   1   2
    * 0 0   1   0
    * 1 0   0   0
    * 2 0   1   0
    */
    upo_add_vertex(graph);
    upo_add_edge(graph, 2, 1);

    assert(upo_get_in_degree(graph, 0) == 0);
    assert(upo_get_in_degree(graph, 1) == 2);
    assert(upo_get_in_degree(graph, 2) == 0);
    assert(upo_get_out_degree(graph, 0) == 1);
    assert(upo_get_out_degree(graph, 1) == 0);
    assert(upo_get_out_degree(graph, 2) == 1);
    assert(upo_get_degree(graph, 0) == 1);
    assert(upo_get_degree(graph, 1) == 2);
    assert(upo_get_degree(graph, 2) == 1);

    upo_dirgraph_destroy(graph);
}

/**
* Funzioni testate:
* int upo_are_adj(upo_dirgraph_t graph, int vertex1, int vertex2);
* int upo_is_graph_empty(upo_dirgraph_t graph);
* upo_list_t upo_get_adj_vert(upo_dirgraph_t graph, int vertex);
*/
void test_adjacency()
{
    upo_dirgraph_t graph = NULL;

    assert(upo_are_adj(graph, 0, 1) == -1);
    assert(upo_is_graph_empty(graph) == -1);
    upo_list_t list = upo_get_adj_vert(graph, 0);
    assert(list == NULL);

    graph = upo_dirgraph_create();

    assert(upo_are_adj(graph, 0, 1) == 0);
    assert(upo_is_graph_empty(graph) == 1);
    assert(list == NULL);

    /**
    * Adj matrix n: 2
    *   0   1
    * 0 0   1
    * 1 0   0
    */
    upo_add_vertex(graph);
    upo_add_vertex(graph);
    upo_add_edge(graph, 0, 1);

    assert(upo_are_adj(graph, 0, 1) == 0);
    assert(upo_are_adj(graph, 1, 0) == 1);
    assert(upo_are_adj(graph, 3, 7) == 0);
    assert(upo_is_graph_empty(graph) == 0);

    list = upo_get_adj_vert(graph, 1);

    assert(list != NULL);
    assert(upo_list_size(list) == 1);
    assert(*((int*)upo_get(list, 0)) == 0);

    upo_destroy_list(list);

    /**
    * Adj matrix n: 2
    *   0   1
    * 0 0   0
    * 1 1   0
    */
    upo_add_edge(graph, 1, 0);
    upo_remove_edge(graph, 0, 1);

    assert(upo_are_adj(graph, 0, 1) == 1);
    assert(upo_are_adj(graph, 1, 0) == 0);
    assert(upo_are_adj(graph, 3, 7) == 0);
    assert(upo_is_graph_empty(graph) == 0);

    list = upo_get_adj_vert(graph, 0);

    assert(list != NULL);
    assert(upo_list_size(list) == 1);
    assert(*((int*)upo_get(list, 0)) == 1);

    upo_destroy_list(list);

    /**
    * Adj matrix n: 5
    *   0   1   2   3   4
    * 0 0   0   0   0   0
    * 1 1   0   0   0   0
    * 2 0   0   0   1   0
    * 3 0   0   1   0   0
    * 4 1   0   0   0   0
    */
    upo_add_vertex(graph);
    upo_add_vertex(graph);
    upo_add_vertex(graph);
    upo_add_edge(graph, 4, 0);
    upo_add_edge(graph, 2, 3);
    upo_add_edge(graph, 3, 2);

    assert(upo_are_adj(graph, 0, 1) == 1);
    assert(upo_are_adj(graph, 1, 0) == 0);
    assert(upo_are_adj(graph, 0, 4) == 1);
    assert(upo_are_adj(graph, 2, 3) == 1);
    assert(upo_are_adj(graph, 3, 2) == 1);
    assert(upo_is_graph_empty(graph) == 0);

    list = upo_get_adj_vert(graph, 2);

    assert(list != NULL);
    assert(upo_list_size(list) == 1);
    assert(*((int*)upo_get(list, 0)) == 3);

    upo_destroy_list(list);
    upo_dirgraph_destroy(graph);
}

/**
* Funzioni testate:
* upo_list_t upo_get_inc_out_edg(upo_dirgraph_t graph, int vertex);
* upo_list_t upo_get_inc_in_edg(upo_dirgraph_t graph, int vertex);
* upo_list_t upo_get_inc_edg(upo_dirgraph_t graph, int vertex);
*/
void test_incidence()
{
    upo_dirgraph_t graph = NULL;

    assert(upo_get_inc_out_edg(graph, 0) == NULL);
    assert(upo_get_inc_in_edg(graph, 0) == NULL);
    assert(upo_get_inc_edg(graph, 0) == NULL);

    graph = upo_dirgraph_create();

    assert(upo_get_inc_out_edg(graph, 0) == NULL);
    assert(upo_get_inc_in_edg(graph, 0) == NULL);
    assert(upo_get_inc_edg(graph, 0) == NULL);
    
    /**
    * Adj matrix n: 5
    *   0   1   2   3   4
    * 0 0   1   1   1   1
    * 1 0   0   0   0   0
    * 2 0   0   0   0   0
    * 3 0   0   0   0   0
    * 4 0   0   0   0   0
    */
    upo_add_vertex(graph);
    upo_add_vertex(graph);
    upo_add_vertex(graph);
    upo_add_vertex(graph);
    upo_add_vertex(graph);
    upo_add_edge(graph, 0, 1);
    upo_add_edge(graph, 0, 2);
    upo_add_edge(graph, 0, 3);
    upo_add_edge(graph, 0, 4);

    upo_list_t list = upo_get_inc_out_edg(graph, 0);

    assert(list != NULL);
    assert(upo_list_size(list) == 4);
    assert(((upo_dir_edge_t)upo_get(list, 0))->from == 0);
    assert(((upo_dir_edge_t)upo_get(list, 0))->to == 1);
    assert(((upo_dir_edge_t)upo_get(list, 1))->from == 0);
    assert(((upo_dir_edge_t)upo_get(list, 1))->to == 2);
    assert(((upo_dir_edge_t)upo_get(list, 2))->from == 0);
    assert(((upo_dir_edge_t)upo_get(list, 2))->to == 3);
    assert(((upo_dir_edge_t)upo_get(list, 3))->from == 0);
    assert(((upo_dir_edge_t)upo_get(list, 3))->to == 4);

    upo_destroy_list(list);
    list = upo_get_inc_out_edg(graph, 1);

    assert(list != NULL);
    assert(upo_list_size(list) == 0);

    upo_destroy_list(list);
    list = upo_get_inc_in_edg(graph, 0);

    assert(list != NULL);
    assert(upo_list_size(list) == 0);

    upo_destroy_list(list);
    list = upo_get_inc_in_edg(graph, 1);

    assert(list != NULL);
    assert(upo_list_size(list) == 1);
    assert(((upo_dir_edge_t)upo_get(list, 0))->from == 0);
    assert(((upo_dir_edge_t)upo_get(list, 0))->to == 1);

    upo_destroy_list(list);
    list = upo_get_inc_edg(graph, 0);

    assert(list != NULL);
    assert(upo_list_size(list) == 4);
    assert(((upo_dir_edge_t)upo_get(list, 0))->from == 0);
    assert(((upo_dir_edge_t)upo_get(list, 0))->to == 1);
    assert(((upo_dir_edge_t)upo_get(list, 1))->from == 0);
    assert(((upo_dir_edge_t)upo_get(list, 1))->to == 2);
    assert(((upo_dir_edge_t)upo_get(list, 2))->from == 0);
    assert(((upo_dir_edge_t)upo_get(list, 2))->to == 3);
    assert(((upo_dir_edge_t)upo_get(list, 3))->from == 0);
    assert(((upo_dir_edge_t)upo_get(list, 3))->to == 4);

    upo_destroy_list(list);
    list = upo_get_inc_edg(graph, 1);

    assert(list != NULL);
    assert(upo_list_size(list) == 1);
    assert(((upo_dir_edge_t)upo_get(list, 0))->from == 0);
    assert(((upo_dir_edge_t)upo_get(list, 0))->to == 1);

    upo_destroy_list(list);

    upo_dirgraph_destroy(graph);
}

/**
* Funzioni testate:
* char *upo_print_graph(upo_dirgraph_t graph);
*/
void test_print_graph()
{
    upo_dirgraph_t graph = NULL;
    char* string = upo_print_graph(graph);

    assert(string == NULL);

    graph = upo_dirgraph_create();
    string = upo_print_graph(graph);

    assert(string == NULL);

    /**
    * Adj matrix n: 3
    *   0   1   2
    * 0 0   1   1
    * 1 0   0   1
    * 2 0   1   0
    */
    upo_add_vertex(graph);
    upo_add_vertex(graph);
    upo_add_vertex(graph);
    upo_add_edge(graph, 0, 1);
    upo_add_edge(graph, 0, 2);
    upo_add_edge(graph, 1, 2);
    upo_add_edge(graph, 2, 1);

    string = upo_print_graph(graph);

    printf("%s", string);
    free(string);
    upo_dirgraph_destroy(graph);
}

/**
* Caso di test illustrato qui: https://www.youtube.com/watch?v=Zlk2FX-8RYs
*/
void test_BFS()
{
    upo_dirgraph_t graph = NULL;

    assert(upo_BFS(graph, 0) == NULL);

    graph = upo_dirgraph_create();

    assert(upo_BFS(graph, 0) == NULL);

    for (int i = 0; i < 8; i++)
        upo_add_vertex(graph);
    upo_add_edge(graph, 0, 2);
    upo_add_edge(graph, 1, 6);
    upo_add_edge(graph, 2, 4);
    upo_add_edge(graph, 2, 5);
    upo_add_edge(graph, 3, 1);
    upo_add_edge(graph, 3, 5);
    upo_add_edge(graph, 3, 7);
    upo_add_edge(graph, 4, 6);
    upo_add_edge(graph, 4, 7);
    upo_add_edge(graph, 5, 1);
    upo_add_edge(graph, 5, 3);
    upo_add_edge(graph, 5, 6);
    upo_add_edge(graph, 5, 7);
    upo_add_edge(graph, 6, 5);
    upo_add_edge(graph, 7, 5);

    int* vector = upo_BFS(graph, 0);

    /**
    * Parent vector
    *
    *   0[-1]
    *   1[5]
    *   2[0]
    *   3[5]
    *   4[2]
    *   5[2]
    *   6[4]
    *   7[4]
    *           
    */
    assert(vector != NULL);
    assert(vector[0] == -1);
    assert(vector[1] == 5);
    assert(vector[2] == 0);
    assert(vector[3] == 5);
    assert(vector[4] == 2);
    assert(vector[5] == 2);
    assert(vector[6] == 4);
    assert(vector[7] == 4);

    free(vector);
    upo_dirgraph_destroy(graph);
}

/**
* Caso di test illustrato qui: https://www.youtube.com/watch?v=CZc_hdTYGKc
*/
void test_DFS_tot()
{
    upo_dirgraph_t graph = NULL;

    assert(upo_DFS_tot(graph) == NULL);

    graph = upo_dirgraph_create();

    assert(upo_DFS_tot(graph) == NULL);

    for (int i = 0; i < 8; i++)
        upo_add_vertex(graph);
    upo_add_edge(graph, 0, 2);
    upo_add_edge(graph, 1, 3);
    upo_add_edge(graph, 1, 5);
    upo_add_edge(graph, 1, 6);
    upo_add_edge(graph, 2, 0);
    upo_add_edge(graph, 2, 4);
    upo_add_edge(graph, 2, 6);
    upo_add_edge(graph, 3, 5);
    upo_add_edge(graph, 3, 7);
    upo_add_edge(graph, 4, 2);
    upo_add_edge(graph, 5, 3);
    upo_add_edge(graph, 6, 2);
    upo_add_edge(graph, 6, 5);

    int* vector = upo_DFS_tot(graph);

    assert(vector != NULL);
    assert(vector[0] == -1);
    assert(vector[1] == -1);
    assert(vector[2] == 0);
    assert(vector[3] == 5);
    assert(vector[4] == 2);
    assert(vector[5] == 6);
    assert(vector[6] == 2);
    assert(vector[7] == 3);

    free(vector);
    upo_dirgraph_destroy(graph);
}

void test_cyclic_DAG()
{
    upo_dirgraph_t cyclic_graph = NULL;

    assert(upo_cyclic(cyclic_graph) == -1);
    assert(upo_is_DAG(cyclic_graph) == -1);

    cyclic_graph = upo_dirgraph_create();

    assert(upo_cyclic(cyclic_graph) == -1);
    assert(upo_is_DAG(cyclic_graph) == -1);

    // Test case: https://www.youtube.com/watch?v=Zlk2FX-8RYs
    for (int i = 0; i < 8; i++)
        upo_add_vertex(cyclic_graph);
    upo_add_edge(cyclic_graph, 0, 2);
    upo_add_edge(cyclic_graph, 1, 6);
    upo_add_edge(cyclic_graph, 2, 4);
    upo_add_edge(cyclic_graph, 2, 5);
    upo_add_edge(cyclic_graph, 3, 1);
    upo_add_edge(cyclic_graph, 3, 5);
    upo_add_edge(cyclic_graph, 3, 7);
    upo_add_edge(cyclic_graph, 4, 6);
    upo_add_edge(cyclic_graph, 4, 7);
    upo_add_edge(cyclic_graph, 5, 1);
    upo_add_edge(cyclic_graph, 5, 3);
    upo_add_edge(cyclic_graph, 5, 6);
    upo_add_edge(cyclic_graph, 5, 7);
    upo_add_edge(cyclic_graph, 6, 5);
    upo_add_edge(cyclic_graph, 7, 5);

    assert(upo_cyclic(cyclic_graph) == 1);
    assert(upo_is_DAG(cyclic_graph) == 0);

    upo_dirgraph_destroy(cyclic_graph);

    upo_dirgraph_t acyclic_graph = upo_dirgraph_create();

    assert(upo_cyclic(acyclic_graph) == -1);
    assert(upo_is_DAG(acyclic_graph) == -1);

    // Test case: https://upload.wikimedia.org/wikipedia/commons/thumb/4/4b/Directed_acyclic_graph.svg/800px-Directed_acyclic_graph.svg.png
    for (int i = 0; i < 8; i++)
        upo_add_vertex(acyclic_graph);
    upo_add_edge(acyclic_graph, 1, 2);
    upo_add_edge(acyclic_graph, 2, 3);
    upo_add_edge(acyclic_graph, 2, 4);
    upo_add_edge(acyclic_graph, 2, 5);
    upo_add_edge(acyclic_graph, 3, 5);
    upo_add_edge(acyclic_graph, 4, 5);
    upo_add_edge(acyclic_graph, 5, 6);
    upo_add_edge(acyclic_graph, 4, 7);

    assert(upo_cyclic(acyclic_graph) == 0);
    assert(upo_is_DAG(acyclic_graph) == 1);

    upo_dirgraph_destroy(acyclic_graph);
}

void test_topological_sort()
{
    upo_dirgraph_t graph = NULL;

    assert(upo_topological_sort(graph) == NULL);

    graph = upo_dirgraph_create();

    assert(upo_topological_sort(graph) == NULL);

    // Test case: https://www.youtube.com/watch?v=fS3Ljm_gVN4
    for (int i = 0; i < 8; i++)
        upo_add_vertex(graph);
    upo_add_edge(graph, 0, 1);
    upo_add_edge(graph, 0, 2);
    upo_add_edge(graph, 0, 3);
    upo_add_edge(graph, 1, 2);
    upo_add_edge(graph, 1, 3);
    upo_add_edge(graph, 1, 5);
    upo_add_edge(graph, 1, 6);
    upo_add_edge(graph, 2, 5);
    upo_add_edge(graph, 3, 5);
    upo_add_edge(graph, 4, 7);
    upo_add_edge(graph, 5, 6);

    int* ts = upo_topological_sort(graph);

    assert(ts != NULL);
    assert(ts[0] == 4);
    assert(ts[1] == 7);
    assert(ts[2] == 0);
    assert(ts[3] == 1);
    assert(ts[4] == 3);
    assert(ts[5] == 2);
    assert(ts[6] == 5);
    assert(ts[7] == 6);

    free(ts);
    upo_dirgraph_destroy(graph); 
    
    upo_dirgraph_t cyclic_graph = NULL;

    assert(upo_topological_sort(cyclic_graph) == NULL);

    cyclic_graph = upo_dirgraph_create();

    assert(upo_topological_sort(cyclic_graph) == NULL);

    // Test case: https://www.youtube.com/watch?v=Zlk2FX-8RYs
    for (int i = 0; i < 8; i++)
        upo_add_vertex(cyclic_graph);
    upo_add_edge(cyclic_graph, 0, 2);
    upo_add_edge(cyclic_graph, 1, 6);
    upo_add_edge(cyclic_graph, 2, 4);
    upo_add_edge(cyclic_graph, 2, 5);
    upo_add_edge(cyclic_graph, 3, 1);
    upo_add_edge(cyclic_graph, 3, 5);
    upo_add_edge(cyclic_graph, 3, 7);
    upo_add_edge(cyclic_graph, 4, 6);
    upo_add_edge(cyclic_graph, 4, 7);
    upo_add_edge(cyclic_graph, 5, 1);
    upo_add_edge(cyclic_graph, 5, 3);
    upo_add_edge(cyclic_graph, 5, 6);
    upo_add_edge(cyclic_graph, 5, 7);
    upo_add_edge(cyclic_graph, 6, 5);
    upo_add_edge(cyclic_graph, 7, 5);

    assert(upo_topological_sort(cyclic_graph) == NULL);

    upo_dirgraph_destroy(cyclic_graph);
}

void test_strongly_connected_components()
{
    upo_dirgraph_t graph = NULL;

    assert(upo_strongly_connected_components(graph) == NULL);

    graph = upo_dirgraph_create();

    assert(upo_strongly_connected_components(graph) == NULL);

    for (int i = 0; i < 6; i++)
        upo_add_vertex(graph);
    upo_add_edge(graph, 0, 3);
    upo_add_edge(graph, 1, 2);
    upo_add_edge(graph, 2, 3);
    upo_add_edge(graph, 3, 1);
    upo_add_edge(graph, 3, 4);
    upo_add_edge(graph, 4, 5);
    upo_add_edge(graph, 5, 4);

    int* cfc = upo_strongly_connected_components(graph);

    for (int i = 0; i < 6; i++)
        printf("cfc[%d] = %d\n", i, cfc[i]);

    assert(cfc != NULL);
    assert(cfc[0] == -1);
    assert(cfc[1] == 3);
    assert(cfc[2] == 1);
    assert(cfc[3] == -1);
    assert(cfc[4] == -1);
    assert(cfc[5] == 4);

    /**
    * Test case: https://www.dir.uniupo.it/pluginfile.php/302330/mod_resource/content/1/10%20GrafiComponentiFortementeConnesse.pdf
    * page 2 slide 1
    */
    // for (int i = 0; i < 10; i++)
    //     upo_add_vertex(graph);
    // upo_add_edge(graph, 0, 4);
    // upo_add_edge(graph, 0, 5);
    // upo_add_edge(graph, 1, 0);
    // upo_add_edge(graph, 2, 1);
    // upo_add_edge(graph, 2, 3);
    // upo_add_edge(graph, 2, 6);
    // upo_add_edge(graph, 3, 2);
    // upo_add_edge(graph, 4, 0);
    // upo_add_edge(graph, 4, 7);
    // upo_add_edge(graph, 5, 1);
    // upo_add_edge(graph, 5, 4);
    // upo_add_edge(graph, 5, 7);
    // upo_add_edge(graph, 6, 2);
    // upo_add_edge(graph, 6, 5);
    // upo_add_edge(graph, 6, 8);
    // upo_add_edge(graph, 8, 7);
    // upo_add_edge(graph, 8, 9);
    // upo_add_edge(graph, 9, 8);
    
    // int* cfc = upo_strongly_connected_components(graph);

    // for (int i = 0; i < 10; i++)
    //     printf("cfc[%d] = %d\n", i, cfc[i]);

    // assert(cfc != NULL);
    // assert(cfc[0] == -1);
    // assert(cfc[1] == 5);
    // assert(cfc[2] == -1);
    // assert(cfc[3] == 2);
    // assert(cfc[4] == 0);
    // assert(cfc[5] == 4);
    // assert(cfc[6] == 2);
    // assert(cfc[7] == -1);
    // assert(cfc[8] == -1);
    // assert(cfc[9] == 8);

    free(cfc);
    upo_dirgraph_destroy(graph);
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

    printf("Test case 'vertex degree'... ");
    fflush(stdout);
    test_vertex_degree();
    printf("OK\n");

    printf("Test case 'adjacency'... ");
    fflush(stdout);
    test_adjacency();
    printf("OK\n");

    printf("Test case 'incidence'... ");
    fflush(stdout);
    test_incidence();
    printf("OK\n");

    printf("Test case 'print graph'... ");
    fflush(stdout);
    test_print_graph();
    printf("OK\n");

    printf("Test case 'BFS'... ");
    fflush(stdout);
    test_BFS();
    printf("OK\n");

    printf("Test case 'DFS total'... ");
    fflush(stdout);
    test_DFS_tot();
    printf("OK\n");

    printf("Test case 'cyclic/DAG'... ");
    fflush(stdout);
    test_cyclic_DAG();
    printf("OK\n");

    printf("Test case 'topological sort'... ");
    fflush(stdout);
    test_topological_sort();
    printf("OK\n");

    printf("Test case 'strongly connected components'... ");
    fflush(stdout);
    test_strongly_connected_components();
    printf("OK\n");

    return 0;
}
