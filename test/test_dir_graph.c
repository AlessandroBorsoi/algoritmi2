#include <stdio.h>
#include <upo_dir_graph.h>

static void test_create_destroy();
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

void test_num_vertices() 
{
    upo_dirgraph_t graph = NULL;
    int res = upo_num_vertices(graph);

    assert(res == -1);

    graph = upo_dirgraph_create();
    res = upo_num_vertices(graph);

    assert(res == 0);
}

int main()
{
    printf("Test case 'create/destroy'... ");
    fflush(stdout);
    test_create_destroy();
    printf("OK\n");

    printf("Test case 'number of vertices'... ");
    fflush(stdout);
    test_num_vertices();
    printf("OK\n");

    return 0;
}
