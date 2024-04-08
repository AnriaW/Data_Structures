//hash table

#include <stdio.h>
#include <stdlib.h>

#define SIZE 200

typedef struct element element;
typedef struct hashTable hashTable;

struct element
{
    int val;
    element *next;
};

struct hashTable
{
    element *table[SIZE];
};

hashTable* criar_ht();
void put(hashTable *ht, int chav, int val);
int dis(int x, int n);
void print_ht(hashTable *ht, int size);
void rem_h(hashTable *hash, int chav);

int main()
{

    int n, i;
    scanf("%d", &n);

    for(i = 0; i < n; i++){

        hashTable *ht = criar_ht();

        int m, c, j;
        scanf("%d %d", &m, &c);

        for(j = 0; j < c; j++)
        {
            int valor;
            scanf("%d", &valor);

            int posicao = dis(valor, m);

            put(ht, posicao, valor);
        }


        print_ht(ht, m);
        printf("\n");

        free(ht);
    }

}

int dis(int x, int n)
{
    return x % n;
}

void print_ht(hashTable *ht, int size)
{
    int i=0;
    for(i=0;i<size;i++)
    {
        element *aux = ht->table[i];
        printf("%d ->",i);
        while(aux!=NULL){
            printf(" %d ->", aux->val);
            aux = aux->next ;
        }
       printf(" \\\n");
    }    
}

hashTable* criar_ht()
{
    hashTable *nova_ht = (hashTable*) malloc(sizeof(hashTable));

    int i;
    for (i = 0; i < SIZE; i++)
    {
        nova_ht->table[i] = NULL;
    }

    return nova_ht;
}

void put(hashTable *ht, int position, int val)
{
    element *node = (element*) malloc(sizeof(node));

    node->val = val;
    node->next = NULL;

    if(ht->table[position] == NULL)
    {
        ht->table[position] = node;
    }else{
        element *aux = ht->table[position];
        while(aux->next != NULL)
        {
            aux = aux->next;
        }

        aux->next = node;
    }
}