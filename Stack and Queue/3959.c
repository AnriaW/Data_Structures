#include <stdio.h>
#include <stdlib.h>
#define ITEM char
#define TAM 50

typedef struct pilha_dupla {
    ITEM vet[TAM];
    int topo1, topo2;
} TPilhaDupla;

void create(TPilhaDupla *pd) {
pd->topo1 = -1;
    pd->topo2 = TAM;
}

void destroy(TPilhaDupla *pd) {
pd->topo1 = -1;
    pd->topo2 = TAM;
}

int isfull(TPilhaDupla *pd) {
return (pd->topo1 + 1 == pd->topo2);
}

int isempty(TPilhaDupla *pd, int topo) {
if (topo == 1){
        return (pd->topo1 == -1);
}else if (topo == 2){
        return (pd->topo2 == TAM);
}else {
        printf("Invalid stack number!\n");
        return -1;
}
}

void push(TPilhaDupla *pd, ITEM x, int topo) {
if (isfull(pd)) {
        printf("Stack overflow!\n");
        return;
    }
    
    if (topo == 1)
        pd->vet[++pd->topo1] = x; 
    else if (topo == 2)
        pd->vet[--pd->topo2] = x; 
    else
        printf("Invalid stack number!\n");
}

ITEM pop(TPilhaDupla *pd, int topo) {
ITEM item;
    if (isempty(pd, topo)) {
        printf("Stack %d is empty!\n", topo);
        return '\0';
    }
    
    if (topo == 1)
        item = pd->vet[pd->topo1--];
    else if (topo == 2)
        item = pd->vet[pd->topo2++]; 
    else {
        printf("Invalid stack number!\n");
        return '\0';
    }
    return item;
}

ITEM top(TPilhaDupla *pd, int topo) {
if (isempty(pd, topo)) {
        printf("Stack %d is empty!\n", topo);
        return '\0';
    }
    
    if (topo == 1)
        return pd->vet[pd->topo1]; 
    else if (topo == 2)
        return pd->vet[pd->topo2];
    else {
        printf("Invalid stack number!\n");
        return '\0';
    }
}

void preenche(TPilhaDupla *pd) {
    ITEM x;
    int topo, qtd, i;

    scanf("%d%*c", &qtd);

    for( i=0; i<qtd; i++ ) {
        scanf("%c %d%*c", &x, &topo);
        push(pd, x, topo);
    }
}

void exibe(TPilhaDupla *pd) {
    int topo;

    while( scanf("%d", &topo) != EOF )
        printf("TOPO %d = %c\n", topo, pop(pd, topo));
}

int main(void) {
    TPilhaDupla pd;

    create(&pd);
    preenche(&pd);
    exibe(&pd);
    destroy(&pd);

    return 0;
}
