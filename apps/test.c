#include <stdio.h>
#include <upo_dir_graph.h>

#define NOT_VALID -1
#define CREATE 0
#define DESTROY 1
#define QUIT 2

int quit;
upo_dirgraph_t graph = NULL;

void print_menu()
{
    printf("\n========================\n");
    printf("Scegliere una opzione:\n");
    printf("c - Creare un grafo\n");
    printf("d - Distruggere il grafo\n");
    printf("q - quit\n");
    printf("========================\n\n");
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
