#include <stdio.h>
#include <upo_dir_graph.h>

static void test_create_destroy();
static void test_add_remove_vertex();
static void test_add_remove_edges();
static void test_vertex_degree();
static void test_adjacency();
static void test_incidence();
static void test_print_graph();

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

    assert(upo_add_edge(graph, 0, 1) == 0);
    assert(upo_has_edge(graph, 0, 1) == 0);
    assert(upo_num_edges(graph) == 0);
    assert(upo_remove_edge(graph, 0, 1) == 0);

    upo_add_vertex(graph);

    assert(upo_add_edge(graph, 0, 1) == 0);
    assert(upo_has_edge(graph, 0, 1) == 0);
    assert(upo_num_edges(graph) == 0);
    assert(upo_remove_edge(graph, 0, 1) == 0);

    upo_add_vertex(graph);
    
    assert(upo_add_edge(graph, 0, 1) == 1);
    assert(upo_add_edge(graph, 0, 1) == 0);
    assert(upo_add_edge(graph, 0, 2) == 0);
    assert(upo_has_edge(graph, 0, 1) == 1);
    assert(upo_num_edges(graph) == 1);
    assert(upo_remove_edge(graph, 0, 1) == 1);
    assert(upo_remove_edge(graph, 0, 1) == 0);
    assert(upo_has_edge(graph, 0, 1) == 0);
    assert(upo_num_edges(graph) == 0);

    assert(upo_add_edge(graph, 0, 1) == 1);
    assert(upo_add_edge(graph, 1, 0) == 1);
    assert(upo_has_edge(graph, 0, 1) == 1);
    assert(upo_has_edge(graph, 1, 0) == 1);
    assert(upo_num_edges(graph) == 2);
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

    upo_add_vertex(graph);
    upo_add_vertex(graph);
    upo_add_edge(graph, 0, 1);
    
    assert(upo_get_in_degree(graph, 0) == 0);
    assert(upo_get_in_degree(graph, 1) == 1);
    assert(upo_get_out_degree(graph, 0) == 1);
    assert(upo_get_out_degree(graph, 1) == 0);
    assert(upo_get_degree(graph, 0) == 1);
    assert(upo_get_degree(graph, 1) == 1);

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
* upo_list upo_get_adj_vert(upo_dirgraph_t graph, int vertex);
*/
void test_adjacency()
{
    upo_dirgraph_t graph = NULL;

    assert(upo_are_adj(graph, 0, 1) == -1);
    assert(upo_is_graph_empty(graph) == -1);
    upo_list* list = upo_get_adj_vert(graph, 0);
    assert(list == NULL);

    graph = upo_dirgraph_create();

    assert(upo_are_adj(graph, 0, 1) == 0);
    assert(upo_is_graph_empty(graph) == 1);
    assert(list == NULL);

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
* upo_list upo_get_inc_out_edg(upo_dirgraph_t graph, int vertex);
* upo_list upo_get_inc_in_edg(upo_dirgraph_t graph, int vertex);
* upo_list upo_get_inc_edg(upo_dirgraph_t graph, int vertex);
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
    
    upo_add_vertex(graph);
    upo_add_vertex(graph);
    upo_add_vertex(graph);
    upo_add_vertex(graph);
    upo_add_vertex(graph);
    upo_add_edge(graph, 0, 1);
    upo_add_edge(graph, 0, 2);
    upo_add_edge(graph, 0, 3);
    upo_add_edge(graph, 0, 4);

    upo_list* list = upo_get_inc_out_edg(graph, 0);

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

    return 0;
}
/*
upo_dirgraph_t upo_dirgraph_create();
int upo_dirgraph_destroy(upo_dirgraph_t graph);

int upo_num_vertices(upo_dirgraph_t graph);
int upo_add_vertex(upo_dirgraph_t graph);
int upo_has_vertex(upo_dirgraph_t graph, int vertex);
int upo_remove_vertex(upo_dirgraph_t graph, int vertex);

int upo_add_edge(upo_dirgraph_t graph, int vertex1, int vertex2);
int upo_has_edge(upo_dirgraph_t graph, int vertex1, int vertex2);
int upo_remove_edge(upo_dirgraph_t graph, int vertex1, int vertex2);
int upo_num_edges(upo_dirgraph_t graph);

int upo_get_in_degree(upo_dirgraph_t graph, int vertex);
int upo_get_out_degree(upo_dirgraph_t graph, int vertex);
int upo_get_degree(upo_dirgraph_t graph, int vertex);

int upo_are_adj(upo_dirgraph_t graph, int vertex1, int vertex2);
int upo_is_graph_empty(upo_dirgraph_t graph);
upo_list upo_get_adj_vert(upo_dirgraph_t graph, int vertex);

upo_list upo_get_inc_out_edg(upo_dirgraph_t graph, int vertex);
upo_list upo_get_inc_in_edg(upo_dirgraph_t graph, int vertex);
upo_list upo_get_inc_edg(upo_dirgraph_t graph, int vertex);

char *upo_print_graph(upo_dirgraph_t graph);
*/
