#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct _node
{
    int item;
    struct _node *next;
} node;

typedef struct _hashtable
{
    int current_elements;
    int size;
    node **table;
    int *adjlist_current_size;
} hashtable;

int hash(int item, int n)
{
    return item%n;
}

hashtable *createhashtable(int n)
{
    hashtable *hash_table = (hashtable*) calloc(1 , sizeof(hashtable));
    hash_table->size = n;
    hash_table->current_elements = 0;
    hash_table->table = (node**) calloc(n , sizeof(node*));
    hash_table->adjlist_current_size = (int *) calloc(n, sizeof(int));

    for(int i = 0; i < n; i++)
    {
        hash_table->table[i] = NULL;
        hash_table->adjlist_current_size[i] = 0;
    }

    return hash_table;
}

int used(hashtable *tabela, int item, int *cont)
{
    int i = hash(item, tabela->size);
    
    node *aux = tabela->table[i];
    while(aux != NULL)
    {
        if(aux->item == item)
        {
            (*cont) += 1;
            return 1;
        }

        (*cont) += 1;
        aux = aux->next;
    }
    
    return 0;
}

int removeitem(hashtable *tabela, int item, int *cont)
{
    int i = hash(item, tabela->size);

    node *previous = NULL;
    node *current = tabela->table[i];

    int jafoimano = 0;

    if(current != NULL && current->item == item)
    {
        (*cont) += 1;
        jafoimano = 1;
    }

    while(current != NULL && current->item != item)
    {
        (*cont) += 1;
        previous = current;
        current = current->next;
    }

    if(current != NULL && current->item == item && jafoimano == 0) (*cont) += 1;

    if(current)
    {
        if(previous)
        {
            previous->next = current->next;
            current->next = NULL;
        }

        else 
        {
            tabela->table[i] = current->next;
        }

        tabela->current_elements--;
        tabela->adjlist_current_size[i]--;
        return 1;
    }

    return 0;
}

int insert(hashtable *tabela, int item, int *cont)
{
    int i = hash(item, tabela->size);
    if(used(tabela, item, cont) == 1) return 0;
    node *new_node = (node*) calloc(1, sizeof(node));
    new_node->item = item;
    new_node->next = tabela->table[i];
    tabela->table[i] = new_node;
    tabela->adjlist_current_size[i]++;
    tabela->current_elements++;    
    return 1;
}

hashtable *rehash(hashtable *table, int n)
{
    hashtable *new_hashtable = createhashtable((2 * n) - 1);

    for(int i = 0; i < n; i++)
    {
        node *aux = table->table[i];

        while(aux != NULL)
        {
            int cont;

            insert(new_hashtable ,aux->item, &cont);

            aux = aux->next;
        }
    }

    return new_hashtable;
}

int Biggest_list_width(int *v, int n)
{
    int maior = INT_MIN;

    for(int i = 0; i < n; i++)
    {
        if(v[i] > maior)
        {
            maior = v[i];
        }
    }

    return maior;
}

void removenewline(char *string)
{
    int post_line = strcspn(string, "\n");
    string[post_line] = '\0';
    return;
}

void printhashtable(hashtable *tabela)
{
    for(int i = 0; i < tabela->size; i++)
    {
        printf("%d -> ", i);
        node *current = tabela->table[i];
        if(current == NULL) printf("\\\n");
        while(current != NULL)
        {
            printf("%d", current->item);
            printf(current->next == NULL ? " -> \\\n" : " -> "); 
            current = current->next;
        }
    }
    return;
}


int main()
{
    int m = 7;
    hashtable *hash_table = createhashtable(m);

    char string[5];
    int item;
    int dejavu;

    for(int i = 0; scanf("%s", string) != EOF; i++)
    {
        
        dejavu = 0;
        removenewline(string);

        if(string[0] == 'A')
        {
            scanf("%d", &item);

            int bool = insert(hash_table, item, &dejavu);

            double a = (double) hash_table->current_elements / hash_table->size;

            if(a >= 0.75) hash_table = rehash(hash_table, hash_table->size);

            printf("%d %d %d\n", i, bool, dejavu);

        }

        if(string[0] == 'D')
        {
            scanf("%d", &item); 
            int bool = removeitem(hash_table, item, &dejavu);
            printf("%d %d %d\n", i, bool, dejavu);

        }

        if(string[0] == 'H')
        {
            scanf("%d", &item);
            int bool = used(hash_table, item, &dejavu);
            printf("%d %d %d\n", i, bool, dejavu);
            
        }

        if(string[0] == 'P')
        {
            printf("%d %d %d %d\n", i, hash_table->size, hash_table->current_elements, Biggest_list_width(hash_table->adjlist_current_size, hash_table->size));            
        }
    }
    return 0;
}