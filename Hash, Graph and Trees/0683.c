#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list list;
typedef struct list_names list_names;
typedef struct graph graph;

typedef struct list_names{
    int index;
    char name[16];
    list_names *next;
} list_names;

typedef struct list{
    int elem;
    list *next;
} list;

typedef struct graph{
    int size;
    int *visited;
    list **adj_list;
} graph;

graph *create_graph()
{
    graph *g = (graph *) malloc(sizeof(graph));
    g->size = 100;
    g->adj_list = (list **) malloc(g->size * sizeof(list *));
    g->visited = (int *) malloc(g->size * sizeof(int));

    for (int i = 0; i < g->size; i++)
    {
        g->adj_list[i]  = NULL;
        g->visited[i]   = 1;
    }
    
    return g;
}

int size_graph(graph *g)
{
    int count = 0;

    for (int i = 0; i < 100; i++)
        count += (g->adj_list[i] != NULL) ? 1 : 0;
    
    return count;
}

void print_list (list *head, list_names *names)
{
    list *temp = head;

    while (temp != NULL)
    {
        printf("%d ", temp->elem);
        temp = temp->next;
    }
}

void print_list_names (list_names *head)
{
    list_names *temp = head;

    while (temp != NULL)
    {
        printf("%s\n", temp->name);
        temp = temp->next;
    }
}

list *add_node (list *head, int elem)
{
    list *new_node = (list *) malloc(sizeof(list));
    
    new_node->elem = elem;
    new_node->next = head;

    return new_node;
}

int verify_names (char *name1, char *name2)
{
    int i = 0;

    while (name1[i] != '\0' && name2[i] != '\0')
    {
        if ((int)name1[i] > (int)name2[i])
            return 0;
        else if ((int) name1[i] < name2[i])
            return 1;

        i++;
    }

    return (name1[i] == '\0') ? 0 : 1;
}

list_names *add_node_name (list_names *head, char name[16], int elem)
{
    list_names *new_node = (list_names *) malloc(sizeof(list_names));
    
    new_node->index = elem;
    strcpy(new_node->name, name);
    new_node->next = NULL;

    if (head == NULL)
        return new_node;
    
    list_names *current = head;
    list_names *prev = NULL;

    while(current != NULL && verify_names(current->name, name))
    {
        prev = current;
        current = current->next;
    }

    if (prev == NULL)
    {
        new_node->next = current;
        head = new_node;
    }
    else
    {
        prev->next = new_node;
        new_node->next = current;
    }

    return head;
}

list *remove_node (list *head, int elem)
{
    if (head == NULL)
        return head;

    list *current   = head;
    list *prev      = NULL;

    while (current != NULL && current->elem != elem)
    {
        prev = current;
        current = current->next;
    }
    
    if (current == NULL)
        return head;

    if (prev == NULL)
        head = head->next;
    else
        prev->next = current->next;

    free(current);

    return head;
}

list_names *remove_node_names (list_names *head, int elem)
{
    if (head == NULL)
        return head;

    list_names *current   = head;
    list_names *prev      = NULL;

    while (current != NULL && current->index != elem)
    {
        prev = current;
        current = current->next;
    }
    
    if (current == NULL)
        return head;

    if (prev == NULL)
        head = head->next;
    else
        prev->next = current->next;

    free(current);

    return head;
}

int index_of_name (list_names *head, char name[])
{
    list_names *temp = head;

    while (temp != NULL && (strcmp(temp->name, name) != 0))
        temp = temp->next;
    
    return (temp != NULL) ? temp->index : -1;
}

void remove_edges (graph *g, int size, int index)
{
    for (int i = 0; i < size; i++)
    {
        g->adj_list[i] = remove_node(g->adj_list[i], index);
    }
    
}

void dfs (graph *g, list_names *in, int size)
{
    while (in != NULL)
    {
        list_names *temp_in = in;
        list_names *out = NULL;

        while (temp_in != NULL)
        {
            int index = index_of_name(in, temp_in->name);

            if (g->adj_list[index] == NULL)
                out = add_node_name(out, temp_in->name, index);

            temp_in = temp_in->next;
        }
        
        print_list_names(out);

        temp_in = out;

        while (temp_in != NULL)
        {
            remove_edges(g, size, temp_in->index);
            in = remove_node_names(in, temp_in->index);
            temp_in = temp_in->next;
        }
    }
}

void add_edge(graph *g, int v, int u)
{
    g->adj_list[v] = add_node(g->adj_list[v], u);
}

void solve ()
{
    int n, size = 0;

    if (scanf("%d", &n) == EOF)
        return;
    
    graph *g = create_graph();
    list *lst = NULL;
    list_names *names_list = NULL;
    char name1[16], name2[16];

    for (int i = 0; i < n; i++)
    {
        scanf("%s %s", name1, name2);

        int index1 = index_of_name(names_list, name1);

        if (index1 == -1)
        {
            names_list = add_node_name(names_list, name1, size);
            index1 = size;
            size++;
        }

        int index2 = index_of_name(names_list, name2);

        if (index2 == -1)
        {
            names_list = add_node_name(names_list, name2, size);
            index2 = size;
            size++;
        }

        add_edge(g, index1, index2);       
    }

    dfs(g, names_list, size); 
    solve();
}

int main ()
{
    solve();
    return 0;
}
