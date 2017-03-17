#include <stdio.h>
#include <upo_dir_graph.h>

static void test_create_destroy();
static void test_add_remove();
static void test_num_vertices();

void test_create_destroy()
{
    upo_dirgraph_t graph = NULL;
    int res = upo_dirgraph_destroy(graph);

    assert(res == -1);

    graph = upo_dirgraph_create();

    assert(graph != NULL);

    res = upo_dirgraph_destroy(graph);

    assert(res == 1);

    graph = upo_dirgraph_create();

    assert(graph != NULL);

    res = upo_dirgraph_destroy(graph);

    assert(res == 1);
}

void test_add_remove()
{
    upo_dirgraph_t graph = NULL;
    int res = upo_add_vertex(graph);

    assert(res == -1);

    res = upo_remove_vertex(graph, 0);

    assert(res == -1);

    graph = upo_dirgraph_create();
    res = upo_add_vertex(graph);

    assert(res == 1);
    assert(upo_num_vertices(graph) == 1);

    res = upo_remove_vertex(graph, 0);

    assert(res == 1);
    assert(upo_num_vertices(graph) == 0);

    res = upo_remove_vertex(graph, 0);

    assert(res == 0);
    assert(upo_num_vertices(graph) == 0);

    upo_dirgraph_destroy(graph);
}

void test_num_vertices() 
{
    upo_dirgraph_t graph = NULL;
    int res = upo_num_vertices(graph);

    assert(res == -1);

    graph = upo_dirgraph_create();
    res = upo_num_vertices(graph);

    assert(res == 0);

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
    test_add_remove();
    printf("OK\n");

    printf("Test case 'number of vertices'... ");
    fflush(stdout);
    test_num_vertices();
    printf("OK\n");

    return 0;
}
