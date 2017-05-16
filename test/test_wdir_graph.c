#include <stdio.h>
#include <assert.h>
#include <upo_wdir_graph.h>

static void test_create_destroy();
static void test_add_remove_vertex();

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

    return 0;
}
