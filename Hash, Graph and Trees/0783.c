//arvore_do_cao

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

struct binary_tree{
    int item;
    struct binary_tree *esq;
    struct binary_tree *dir;
};

typedef struct binary_tree BT;

BT* create_bt()
{
    return NULL;
}

BT* inite_bt(int item, BT* esq, BT* dir)
{
    BT* bt = (BT*) malloc(sizeof(BT));

    bt->item = item;
    bt->dir = dir;
    bt->esq = esq;

    return bt;
}

int is_empty(BT* bt)
{
    return bt == NULL ? 1 : 0;
}

void preOrder(BT* bt)
{
    if(!is_empty(bt)){
        printf(" ( %d ", bt->item);
        
        if(bt->esq == NULL){
            printf(" () ");
        }else{
            preOrder(bt->esq);
        }

        if(bt->dir == NULL){
            printf(" () ");
        }else{
            preOrder(bt->dir); 
        }
    }
    printf(") ");
}

BT* add(BT *bt, int item)
{
    if(is_empty(bt)) bt = inite_bt(item, NULL, NULL);

    else if(bt->item > item) bt->esq = add(bt->esq, item);

    else bt->dir = add(bt->dir, item);

    return bt;
}

void printa_valor(BT *bt, int *cont)
{
    printf("( %d ", bt->item);
    
    if(bt->esq == NULL){
        printf(" () ");
        if(bt->dir == NULL){
            printf(" () ");
        }else{
            *cont++;
            printa_valor(bt->dir, cont);
            int aux = 0;
            while(aux < *cont - 2){
                printf(") ");
                aux++;
            }
            return;
        }
    }

    else{
        printa_valor(bt->esq, cont);
        if(bt->dir == NULL){
            printf(" () )");
            return;
        }else{
            *cont++;
            printa_valor(bt->dir, cont);
            int aux = 0;
            while(aux < *cont - 1){
                printf(") ");
                aux++;
            }
            return;
        }
    }

    printf(") ");

    return;
}

int main()
{
    BT *bt = create_bt();

    int x, aux = 0;

    while(scanf("%d", &x) != EOF){
        bt = add(bt, x);

        printf("----\n");
        printf("Adicionando %d\n  ", x);

        preOrder(bt);
        

        printf("\n");
    }

    printf("----");

    printf("\n");

    return 0;
}