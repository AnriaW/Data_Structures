#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct binary_tree
{
	int item;
	int niv;
    int value;
	struct binary_tree *dir;
	struct binary_tree *esq;
};

typedef struct binary_tree BT;

BT *create_tree(int item, BT *dir, BT *esq);

int verifica(BT *raiz, int array[], int menor[], int count);

int main()
{
	int count, n1, n2, n3, i;

	scanf("%d", &count);
	
	BT* array_nodes[count];

	for (i = 0; i < count; i++)
	{
		scanf("%d %d %d\n", &n1, &n2, &n3);

		BT *raiz = create_tree(i, NULL, NULL);
		BT *no1;
		if(n2 != -1){
            no1 = create_tree(n2, NULL, NULL);
        }
			
		else{
            no1 = NULL;
        }

		BT *no2;
		if(n3 != -1){
            no2 = create_tree(n3, NULL, NULL);
        }
		else{
            no2 = NULL;
        }

		raiz->esq = no1;
		raiz->dir = no2;
		raiz->value = n1;

		array_nodes[i] = raiz;
	}

	for (i = 0; i < count; i++)
	{
		BT *node = array_nodes[i];
		
        int position;

		if(node->esq)
		{
			position = node->esq->item;
			node->esq = array_nodes[position];
		}

		if(node->dir)
		{
			position = node->dir->item;
			node->dir = array_nodes[position];
		}

	}

	int tamanho = 200;
	int maior[tamanho];
	int menor[tamanho];

	for (i = 0; i <tamanho; i++)
	{
		maior[i] = 0;
	}

	for (i = 0; i <tamanho; i++)
	{
		menor[i] = __INT16_MAX__;
	}

	int aux = verifica(array_nodes[0], maior, menor, 0);
	
	for (i = 0; i < aux; i++)
	{
		int biggest = maior[i];
		int smallest = menor[i];
		printf("Nivel %d: Maior = %d, Menor = %d\n", i + 1, biggest, smallest);
	}
    return 0;
}

BT *create_tree(int item, BT *esq, BT *dir)
{
	BT *bt = malloc(sizeof(BT));
    
	bt->item = item;
	bt->dir = dir;
	bt->esq = esq;

	return bt;
}

int verifica(BT *raiz, int array[], int menor[], int count)
{
	if(raiz == NULL)
	{
		return count;
	}

	raiz->niv = count;

	if(raiz->value > array[count])
	{
		array[count] = raiz->value;
	}

	if(raiz->value < menor[count])
	{
		menor[count] = raiz->value;
	}

	int value1 = verifica(raiz->esq, array, menor, count + 1);
	int value2 = verifica(raiz->dir, array, menor, count + 1);

	return value1 > value2 ? value1 : value2;
}