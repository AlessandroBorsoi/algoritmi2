#include <stdio.h>
#include <upo_dir_graph.h>

#define NOT_VALID -1
#define CREATE 0
#define DESTROY 1
#define NUM_VERTEX 2
#define NUM_EDGE 3
#define DEG_IN 4
#define DEG_OUT 5
#define DEG_TOT 6
#define QUIT 20

int quit;
upo_dirgraph_t graph = NULL;

void print_menu()
{
    int n = 120;
    printf("\n");
    for (int i = 0; i < n; i++)
        printf("=");
    printf("\n");
    printf("Scegliere una opzione:\n");
    printf("create \t\t\t\t Creare un grafo\n");
    printf("destroy \t\t\t Distruggere il grafo creato\n");
    printf("vnum \t\t\t\t Numero di vertici del grafo\n");
    printf("enum \t\t\t\t Numero di archi del grafo\n");

    printf("TODO\n");
    printf("din \t [vertex] \t\t Grado entrante di un vertice\n");
    printf("dout \t [vertex] \t\t Grado uscente di un vertice\n");
    printf("dtot \t [vertex] \t\t Grado totale di un vertice\n");
    printf("empty \t\t\t\t Controlla se il grafo e' vuoto\n");
    printf("vadj \t [vertex] \t\t Vertici adiacenti a un vertice\n");
    printf("eout \t [vertex] \t\t Archi uscenti da un vertice\n");
    printf("ein \t [vertex] \t\t Archi entranti da un vertice\n");
    printf("einc \t [vertex] \t\t Archi incidenti a un vertice\n");
    printf("addv \t [number] \t\t Aggiunge un numero [number] di vertici al grafo\n");
    printf("hasv \t [vertex] \t\t Controlla se il grafo ha il dato vertice\n");
    printf("remv \t [vertex] \t\t Rimozione del vertice\n");
    printf("adde \t [vertex1] [vertex2] \t Aggiunge un arco che esce da [vertex1] ed entra in [vertex2]\n");
    printf("hase \t [vertex1] [vertex2] \t Controlla se il grafo ha un arco che esce da [vertex1] ed entra in [vertex2]\n");
    printf("reme \t [vertex1] [vertex2] \t Rimozione dell'arco che esce da [vertex1] ed entra in [vertex2]\n");
    printf("adj? \t [vertex1] [vertex2] \t Vertici adiacenti\n");
    printf("\n");
    printf("BFS \t [source] \t\t Visita in ampiezza del grafo\n");
    printf("DFS \t\t\t\t Visita in profondità totale del grafo\n");
    printf("cyc \t\t\t\t Controlla se il grafo contiene dei cicli\n");
    printf("DAG \t\t\t\t Controlla se un grafo graph e' un DAG\n");
    printf("top \t\t\t\t Ordinamento topologico del grafo\n");
    printf("cfc \t\t\t\t Componenti fortemente connesse del grafo\n");
    printf("\n");
    printf("q \t\t\t\t Quit\n");
    for (int i = 0; i < n; i++)
        printf("=");
    printf("\n");
}

int get_action()
{
    int action;
    char input[30];
    printf("> ");
    scanf("%29s", input);
    input[29] = '\0';
    switch (input[0])
    {
        case 'c':
        {  
            action = CREATE;
        } break;
        case 'd':
        {  
            action = DESTROY;
        } break;
        case 'n':
        {  
            if (input[1] == 'v')
                action = NUM_VERTEX;
            else if (input[1] == 'a')
                action = NUM_EDGE;
            else
                action = NOT_VALID;
        } break;
        case 'g':
        {  
            if (input[1] == 'i')
                action = DEG_IN;
            else if (input[1] == 'u')
                action = DEG_OUT;
            else if (input[1] == 't')
                action = DEG_TOT;
            else
                action = NOT_VALID;
        } break;
        case 'q':
        {  
            action = QUIT;
        } break;
        default:
        {
            action = NOT_VALID;
        }
    }
    return action;
}

void execute_action(int action)
{
    switch (action)
    {
        case NOT_VALID:
        {
            printf("\nComando non valido!\n");
        } break;
        case CREATE:
        {
            if (graph == NULL)
            {
                graph = upo_dirgraph_create();
                printf("\nGrafo creato\n");
            }
            else
            {
                printf("\nGrafo già creato\n");
            }
        } break;
        case DESTROY:
        {
            int res = upo_dirgraph_destroy(graph);
            if (res < 1)
            {
                printf("\nImpossibile distruggere il grafo (già distrutto?)\n");
            }
            else
            {
                graph = NULL;
                printf("\nGrafo distrutto\n");
            }
        } break;
        case NUM_VERTEX:
        {
            int n = upo_num_vertices(graph);
            if (n == -1)
                printf("\nIl grafo non esiste\n");
            else
                printf("\nIl grafo ha %d vertici\n", n);
        } break;
        case NUM_EDGE:
        {
            int n = upo_num_edges(graph);
            if (n == -1)
                printf("\nIl grafo non esiste\n");
            else
                printf("\nIl grafo ha %d archi\n", n);
        } break;
        case QUIT:
        {
            quit = 1;
        } break;
    }
}

int main()
{
    quit = 0;
    while (!quit)
    {
        print_menu();
        int action = get_action();
        execute_action(action);
    }
    return 0;
}
