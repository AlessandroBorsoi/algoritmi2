#include <stdio.h>
#include <upo_dir_graph.h>
#include <upo_visit.h>

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
    INC,
    ADDV,
    HASV,
    REMV,
    ADDE,
    HASE,
    REME,
    ADJ,
    PRINT,
    BFS,
    DFS,
    CYC,
    DAG,
    TOP,
    CFC,
    MENU,
    QUIT
};
typedef enum action_e action_t;

struct command_s {
    action_t action;
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
    printf("\n");
    printf("COMMAND\t PARAM1  PARAM2 \t DESCRIZIONE\n");
    printf("create \t\t\t\t Creare un grafo\n");
    printf("destroy \t\t\t Distruggere il grafo creato\n");
    printf("vnum \t\t\t\t Numero di vertici del grafo\n");
    printf("enum \t\t\t\t Numero di archi del grafo\n");
    printf("din \t vertex \t\t Grado entrante di un vertice\n");
    printf("dout \t vertex \t\t Grado uscente di un vertice\n");
    printf("dtot \t vertex \t\t Grado totale di un vertice\n");
    printf("empty \t\t\t\t Controlla se il grafo e' vuoto\n");
    printf("vadj \t vertex \t\t Vertici adiacenti a un vertice\n");
    printf("eout \t vertex \t\t Archi uscenti da un vertice\n");
    printf("ein \t vertex \t\t Archi entranti da un vertice\n");
    printf("inc \t vertex \t\t Archi incidenti a un vertice\n");
    printf("addv \t number \t\t Aggiunge un numero <number> di vertici al grafo\n");
    printf("hasv \t vertex \t\t Controlla se il grafo ha il dato vertice\n");
    printf("remv \t vertex \t\t Rimozione del vertice\n");
    printf("adde \t vertex1 vertex2 \t Aggiunge un arco che esce da vertex1 ed entra in vertex2\n");
    printf("hase \t vertex1 vertex2 \t Controlla se il grafo ha un arco che esce da vertex1 ed entra in vertex2\n");
    printf("reme \t vertex1 vertex2 \t Rimozione dell'arco che esce da vertex1 ed entra in vertex2\n");
    printf("adj \t vertex1 vertex2 \t Vertici adiacenti\n");
    printf("print \t\t\t\t Stampa il grafo\n");
    printf("\n");
    printf("BFS \t source \t\t Visita in ampiezza del grafo\n");
    printf("DFS \t\t\t\t Visita in profondità totale del grafo\n");
    printf("cyc \t\t\t\t Controlla se il grafo contiene dei cicli\n");
    printf("DAG \t\t\t\t Controlla se un grafo e' un DAG\n");
    printf("top \t\t\t\t Ordinamento topologico del grafo\n");
    printf("cfc \t\t\t\t Componenti fortemente connesse del grafo\n");
    printf("\n");
    printf("m \t\t\t\t Menu\n");
    printf("q \t\t\t\t Quit\n");
    for (int i = 0; i < n; i++)
        printf("=");
    printf("\n");
}

action_t string_to_action(char* action)
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
    if (strncmp(action, "inc", 3) == 0)
        return INC;
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
    if (strncmp(action, "print", 5) == 0)
        return PRINT;
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
    if (strncmp(action, "m", 1) == 0)
        return MENU;
    if (strncmp(action, "q", 1) == 0)
        return QUIT;
    return NOT_VALID;
}

int one_param_required(action_t action)
{
    action_t one_param_actions[] = {DIN, DOUT, DTOT, VADJ, EOUT, EIN, INC, ADDV, HASV, REMV, BFS};
    int res = 0;
    for (int i = 0; i < 11; i++)
        res += (action == one_param_actions[i]);
    return res;
}

int two_param_required(action_t action)
{
    action_t two_param_actions[] = {ADDE, HASE, REME, ADJ};
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
    char* token = strtok(input, " ");                       // Si usa strtok con lo spazio come separatore
    while (token)                                           // Si cicla finchè ci sono parametri searati da spazi
    {
        argv = realloc(argv, sizeof(char*) * ++argc);       // Ad ogni iterazione si rialloca lo spazio
        if (argv == NULL)
            exit(-1);
        argv[argc - 1] = token;                             // Si inserisce l'ultimo parametro letto
        token = strtok(NULL, " ");
    }
    command->action = string_to_action(argv[0]);
    command->param1 = 0;
    command->param2 = 0;
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
        {
            command->param1 = atoi(argv[1]);
            command->param2 = atoi(argv[2]);
        }
    }
    free(argv);
    free(input);
}

void print_list(upo_list_t list)
{
    upo_iterator iterator = upo_get_list_iterator(list);
    if (iterator == NULL)
        printf("Nessun elemento trovato\n");
    while (iterator != NULL)  
    {
        upo_dir_edge_t edge = (upo_dir_edge_t)upo_get_iterator_element(iterator);
        printf("%d -> %d\n", edge->from, edge->to);
        iterator = upo_get_next(iterator);
    }
    upo_destroy_list(list);
}

void print_visit(int* visit, int n)
{
    for (int i = 0; i < n; i++)
        if (visit[i] > -1 && visit[i] < n)
            printf("%d -> %d;\n", visit[i], i);
    free(visit);
}

void print_top(int* top, int n)
{
    printf("L'ordinamento topologico è: ");
    for (int i = 0; i < n; i++)
        printf("%d ", top[i]);
    printf("\n");
    free(top);
}

void print_matrix(int** matrix, int rows, int columns)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
            printf("%d\t", matrix[i][j]);
        printf("\n");
    }
}

void print_cfc(int* cfc, int n)
{
    int m = 0;
    int checked[n];
    // Conta delle radici per sapere quante righe creare
    for (int i = 0; i < n; i++)
    {
        checked[i] = 0;
        if (cfc[i] == -1)
            m++;
    }

    // Viene creata la matrice degli insiemi
    int** cfc_matrix = NULL;                           
    cfc_matrix = malloc(sizeof(int*) * m);
    for (int i = 0; i < m; i++)
        cfc_matrix[i] = malloc(sizeof(int) * n);            
    // E inizializzata a -1
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            cfc_matrix[i][j] = -1;                          
    
    // Vengono inserite le radici al primo elemento
    for (int i = 0, j = 0; i < n; i++)
    {
        if (cfc[i] == -1)
        {
            cfc_matrix[j][0] = i;
            checked[i] = 1;
            j++;
        }
    }

    // Fino a quando tutti gli elementi non sono stati inseriti
    for (int row = 0; row < m; row++)
    {
        for (int column = 1; column < n; column++)
        {
            for (int i = 0; i < n; i++)
            {
                if (checked[i]) 
                    continue;
                int counter = column;
                int found = 0;
                while (counter > 0)
                {
                    --counter;
                    if (cfc[i] == cfc_matrix[row][counter])
                    {
                        cfc_matrix[row][column] = i;
                        checked[i] = 1;
                        found = 1;
                        break;
                    }
                }
                if (found) break;
            }
        }
    }
    // print_matrix(cfc_matrix, m, n);

    // Print della matrice
    printf("Le cfc sono: { ");
    for (int i = 0; i < m && cfc_matrix[i][0] > -1; i++)
    {
        if (i != 0)
            printf(", ");
        printf("{");
        for (int j = 0; j < n && cfc_matrix[i][j] > -1; j++)
        {
            if (j != 0)
                printf(", ");
            printf("%d", cfc_matrix[i][j]);
        }
        printf("}");
    }
    printf(" }\n");

    // Liberazione della memoria
    for (int i = 0; i < m; i++)
        free(cfc_matrix[i]);
    free(cfc_matrix);
    free(cfc);
}

void execute_command(const command_t command)
{
    action_t action = command->action;
    int param1 = command->param1;
    int param2 = command->param2;
    switch (action)
    {
        case NOT_VALID:
        {
            printf("Comando non valido!\n");
        } break;
        case CREATE:
        {
            if (graph == NULL)
            {
                graph = upo_dirgraph_create();
                printf("Grafo creato\n");
            }
            else
            {
                printf("Grafo già creato\n");
            }
        } break;
        case DESTROY:
        {
            int res = upo_dirgraph_destroy(graph);
            if (res < 1)
            {
                printf("Impossibile distruggere il grafo (già distrutto?)\n");
            }
            else
            {
                graph = NULL;
                printf("Grafo distrutto\n");
            }
        } break;
        case VNUM:
        {
            int n = upo_num_vertices(graph);
            if (n == -1)
                printf("Il grafo non esiste\n");
            else
                printf("Il grafo ha %d vertici\n", n);
        } break;
        case ENUM:
        {
            int n = upo_num_edges(graph);
            if (n == -1)
                printf("Il grafo non esiste\n");
            else
                printf("Il grafo ha %d archi\n", n);
        } break;
        case DIN:
        {
            int n = upo_get_in_degree(graph, param1);
            if (n == -1)
                printf("Il grafo non esiste\n");
            else
                printf("Il grado entrante del vertice %d è %d\n", param1, n);
        } break;
        case DOUT:
        {
            int n = upo_get_out_degree(graph, param1);
            if (n == -1)
                printf("Il grafo non esiste\n");
            else
                printf("Il grado uscente del vertice %d è %d\n", param1, n);
        } break;
        case DTOT:
        {
            int n = upo_get_degree(graph, param1);
            if (n == -1)
                printf("Il grafo non esiste\n");
            else
                printf("Il grado complessivo del vertice %d è %d\n", param1, n);
        } break;
        case EMPTY:
        {
            int n = upo_is_graph_empty(graph);
            if (n == -1)
                printf("Il grafo non esiste\n");
            else if (n == 0)
                printf("Il grafo non è vuoto\n");
            else
                printf("Il grado è vuoto\n");
        } break;
        case VADJ:
        {
            upo_list_t list = upo_get_adj_vert(graph, param1);
            if (list == NULL)
                printf("Il grafo non esiste\n");
            else
                print_list(list);
        } break;
        case EOUT:
        {
            upo_list_t list = upo_get_inc_out_edg(graph, param1);
            if (list == NULL)
                printf("Il grafo non esiste\n");
            else
                print_list(list);            
        } break;
        case EIN:
        {
            upo_list_t list = upo_get_inc_in_edg(graph, param1);
            if (list == NULL)
                printf("Il grafo non esiste\n");
            else
                print_list(list);            
        } break;
        case INC:
        {
            upo_list_t list = upo_get_inc_edg(graph, param1);
            if (list == NULL)
                printf("Il grafo non esiste\n");
            else
                print_list(list);            
        } break;
        case ADDV:
        {
            if (graph == NULL)
            {
                graph = upo_dirgraph_create();
                printf("Grafo creato\n");
            }
            for (int i = 0; i < param1; i++)
                upo_add_vertex(graph);
            printf("Aggiunti %d vertici al grafo\n", param1);
        } break;
        case HASV:
        {
            int n = upo_has_vertex(graph, param1);
            if (n == -1)
                printf("Il grafo non esiste\n");
            else if (n == 0)
                printf("Il vertice %d non è presente\n", param1);
            else
                printf("Il vertice %d è presente\n", param1);
        } break;
        case REMV:
        {
            int n = upo_remove_vertex(graph, param1);
            if (n == -1)
                printf("Il grafo non esiste\n");
            else if (n == 0)
                printf("Il vertice %d non è stato eliminato\n", param1);
            else
                printf("Il vertice %d è stato eliminato\n", param1); 
        } break;
        case ADDE:
        {
            int n = upo_add_edge(graph, param1, param2);
            if (n == -1)
                printf("Il grafo non esiste\n");
            else if (n == 0)
                printf("L'arco %d -> %d non è stato aggiunto\n", param1, param2);
            else
                printf("L'arco %d -> %d è stato aggiunto\n", param1, param2);
        } break;
        case HASE:
        {
            int n = upo_has_edge(graph, param1, param2);
            if (n == -1)
                printf("Il grafo non esiste\n");
            else if (n == 0)
                printf("L'arco %d -> %d non è presente\n", param1, param2);
            else
                printf("L'arco %d -> %d è presente\n", param1, param2);
        } break;
        case REME:
        {
            int n = upo_remove_edge(graph, param1, param2);
            if (n == -1)
                printf("Il grafo non esiste\n");
            else if (n == 0)
                printf("L'arco %d -> %d non è stato eliminato\n", param1, param2);
            else
                printf("L'arco %d -> %d è stato eliminato\n", param1, param2);
        } break;
        case ADJ:
        {
            int n = upo_are_adj(graph, param1, param2);
            if (n == -1)
                printf("Il grafo non esiste\n");
            else if (n == 0)
                printf("I vertici %d e %d non sono adiacenti\n", param1, param2);
            else
                printf("I vertici %d e %d sono adiacenti\n", param1, param2);
        } break;
        case PRINT:
        {
            char* string = upo_print_graph(graph);
            if (string == NULL)
                printf("Il grafo non esiste\n");
            else
                printf("%s", string);
            free(string);
        } break;
        case BFS:
        {
            int* res = upo_BFS(graph, param1);   
            if (res == NULL)
                printf("Il grafo non esiste o non ci sono vertici\n");
            else
                print_visit(res, upo_num_vertices(graph));
        } break;
        case DFS:
        {
            int* res = upo_DFS_tot(graph);   
            if (res == NULL)
                printf("Il grafo non esiste o non ci sono vertici\n");
            else
                print_visit(res, upo_num_vertices(graph));
        } break;
        case CYC:
        {
            int res = upo_cyclic(graph);
            if (res == -1)
                printf("Il grafo non esiste o non ci sono vertici\n");
            else if (res == 0)
                printf("Il grafo non contiene cicli\n");
            else
                printf("Il grafo contiene cicli\n");
        } break;
        case DAG:
        {
            int res = upo_is_DAG(graph);
            if (res == -1)
                printf("Il grafo non esiste o non ci sono vertici\n");
            else if (res == 0)
                printf("Il grafo non è un DAG\n");
            else
                printf("Il grafo è un DAG\n");
        } break;
        case TOP:
        {
            int* res = upo_topological_sort(graph);
            if (res == NULL)
                printf("Il grafo non esiste o non ci sono vertici\n");
            else
                print_top(res, upo_num_vertices(graph));
        } break;
        case CFC:
        {
            int* res = upo_strongly_connected_components(graph); 
            if (res == NULL)
                printf("Il grafo non esiste o non ci sono vertici\n");
            else
                print_cfc(res, upo_num_vertices(graph));
        } break;
        case MENU:
        {
            print_menu();
        } break;
        case QUIT:
        {
            upo_dirgraph_destroy(graph);
            quit = 1;
        } break;
    }
}

int main()
{
    quit = 0;
    command_t command = malloc(sizeof(struct command_s));
    print_menu();
    while (!quit)
    {
        get_command(command);
        execute_command(command);
    }
    free(command);
    return 0;
}
