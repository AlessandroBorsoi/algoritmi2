#include <stdio.h>
#include <upo_dir_graph.h>

enum action_e {
    NOT_VALID, 
    CREATE,
    DESTROY,
    VNUM,
    ENUM,
    DIN,
    DOUT,
    DTOT,
    EMPTY,
    VADJ,
    EOUT,
    EIN,
    EINC,
    ADDV,
    HASV,
    REMV,
    ADDE,
    HASE,
    REME,
    ADJ,
    BFS,
    DFS,
    CYC,
    DAG,
    TOP,
    CFC,
    QUIT
};
typedef enum action_e action;

struct command_s {
    action action;
    int param1;
    int param2;
};
typedef struct command_s* command_t;

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
    printf("din \t vertex \t\t Grado entrante di un vertice\n");
    printf("dout \t vertex \t\t Grado uscente di un vertice\n");
    printf("dtot \t vertex \t\t Grado totale di un vertice\n");
    printf("empty \t\t\t\t Controlla se il grafo e' vuoto\n");
    printf("vadj \t vertex \t\t Vertici adiacenti a un vertice\n");
    printf("eout \t vertex \t\t Archi uscenti da un vertice\n");
    printf("ein \t vertex \t\t Archi entranti da un vertice\n");
    printf("einc \t vertex \t\t Archi incidenti a un vertice\n");
    printf("addv \t [number] \t\t Aggiunge un numero [number] di vertici al grafo\n");
    printf("hasv \t vertex \t\t Controlla se il grafo ha il dato vertice\n");
    printf("remv \t vertex \t\t Rimozione del vertice\n");
    printf("adde \t vertex1 vertex2 \t Aggiunge un arco che esce da vertex1 ed entra in vertex2\n");
    printf("hase \t vertex1 vertex2 \t Controlla se il grafo ha un arco che esce da vertex1 ed entra in vertex2\n");
    printf("reme \t vertex1 vertex2 \t Rimozione dell'arco che esce da vertex1 ed entra in vertex2\n");
    printf("adj \t vertex1 vertex2 \t Vertici adiacenti\n");
    printf("\n");
    printf("BFS \t source \t\t Visita in ampiezza del grafo\n");
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

action string_to_action(char* action)
{
    if (strncmp(action, "create", 6) == 0)
        return CREATE;
    if (strncmp(action, "destroy", 7) == 0)
        return DESTROY;
    if (strncmp(action, "vnum", 4) == 0)
        return VNUM;
    if (strncmp(action, "enum", 4) == 0)
        return ENUM;
    if (strncmp(action, "din", 3) == 0)
        return DIN;
    if (strncmp(action, "dout", 4) == 0)
        return DOUT;
    if (strncmp(action, "dtot", 4) == 0)
        return DTOT;
    if (strncmp(action, "empty", 5) == 0)
        return EMPTY;
    if (strncmp(action, "vadj", 4) == 0)
        return VADJ;
    if (strncmp(action, "eout", 4) == 0)
        return EOUT;
    if (strncmp(action, "ein", 3) == 0)
        return EIN;
    if (strncmp(action, "einc", 4) == 0)
        return EINC;
    if (strncmp(action, "addv", 4) == 0)
        return ADDV;
    if (strncmp(action, "hasv", 4) == 0)
        return HASV;
    if (strncmp(action, "remv", 4) == 0)
        return REMV;
    if (strncmp(action, "adde", 4) == 0)
        return ADDE;
    if (strncmp(action, "hase", 4) == 0)
        return HASE;
    if (strncmp(action, "reme", 4) == 0)
        return REME;
    if (strncmp(action, "adj", 3) == 0)
        return ADJ;
    if (strncmp(action, "BFS", 3) == 0)
        return BFS;
    if (strncmp(action, "DFS", 3) == 0)
        return DFS;
    if (strncmp(action, "cyc", 3) == 0)
        return CYC;
    if (strncmp(action, "DAG", 3) == 0)
        return DAG;
    if (strncmp(action, "top", 3) == 0)
        return TOP;
    if (strncmp(action, "cfc", 3) == 0)
        return CFC;
    if (strncmp(action, "q", 1) == 0)
        return QUIT;
    return NOT_VALID;
}

int one_param_required(action action)
{
    enum action_e one_param_actions[] = {DIN, DOUT, DTOT, VADJ, EOUT, EIN, EINC, HASV, REMV, BFS};
    int res = 0;
    for (int i = 0; i < 10; i++)
        res += (action == one_param_actions[i]);
    return res;
}

int two_param_required(action action)
{
    enum action_e two_param_actions[] = {ADDE, HASE, REME, ADJ};
    int res = 0;
    for (int i = 0; i < 4; i++)
        res += (action == two_param_actions[i]);
    return res;
}

void get_command(command_t command)
{
    printf("> ");
    int input_size = 512;
    char* input = malloc(input_size);
    fgets(input, input_size, stdin);                        // In input viene riversato il comando

    int argc = 0; 
    char** argv = NULL;                                     // argv conterrà l'elenco dei parametri passati
    char* p = strtok(input, " ");                           // Si usa strtok con lo spazio come separatore
    while (p)                                               // Si cicla finchè ci sono parametri searati da spazi
    {
        argv = realloc(argv, sizeof(char*) * ++argc);       // Ad ogni iterazione si rialloca lo spazio
        if (argv == NULL)
            exit (-1);
        argv[argc - 1] = p;                                 // Si inserisce l'ultimo parametro letto
        p = strtok(NULL, " ");
    }
    argv = realloc(argv, sizeof(char*) * (argc + 1));       // Si alloca spazio per il terminatore
    argv[argc] = 0;

    command->action = string_to_action(argv[0]);
    if (one_param_required(command->action))                // Se il comando prevede un parametro 
    {
        if (argc < 2)                                       // e non è stato passato
            command->action = NOT_VALID;                    // Il comando non è valido
        else
            command->param1 = atoi(argv[1]);
    }
    if (two_param_required(command->action))                // Se il comando prevede due parametri
    {
        if (argc < 3)                                       // e non sono stati passati
            command->action = NOT_VALID;                    // Il comando non è valido
        else
            command->param2 = atoi(argv[2]);
    }
    // printf("argc: %d\n", argc);
    // for (int i = 0; i < (argc + 1); ++i)
    //     printf("argv[%d] = %s\n", i, argv[i]);
    free(argv);
    free(input);
}

void execute_command(command_t command)
{
    action action = command->action;
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
        case VNUM:
        {
            int n = upo_num_vertices(graph);
            if (n == -1)
                printf("\nIl grafo non esiste\n");
            else
                printf("\nIl grafo ha %d vertici\n", n);
        } break;
        case ENUM:
        {
            int n = upo_num_edges(graph);
            if (n == -1)
                printf("\nIl grafo non esiste\n");
            else
                printf("\nIl grafo ha %d archi\n", n);
        } break;
        case DIN:
        {
            int vertex = command->param1;
            int n = upo_get_in_degree(graph, vertex);
            if (n == -1)
                printf("\nIl grafo non esiste\n");
            else
                printf("\nIl grado entrante del vertice %d è %d\n", vertex, n);
        } break;
        case DOUT:
        {
        } break;
        case DTOT:
        {
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
    command_t command = malloc(sizeof(struct command_s));
    while (!quit)
    {
        print_menu();
        get_command(command);
        execute_command(command);
    }
    free(command);
    return 0;
}
