#include <stdio.h>
#include <stdlib.h>

typedef struct NoLista {
    int vertice;
    struct NoLista* prox;
} NoLista;

typedef struct ListaAdj {
    NoLista* inicio;
} ListaAdj;

typedef struct Grafo {
    int numVertices;
    ListaAdj* arrayListaAdj;
} Grafo;

typedef struct Fila {
    int *array;
    int inicio;
    int fim;
    int capacidade;
} Fila;

int casoTeste = 1;

NoLista* criarNoLista(int vertice) {
    NoLista* novoNo = (NoLista*)malloc(sizeof(NoLista));
    novoNo->vertice = vertice;
    novoNo->prox = NULL;
    return novoNo;
}

Fila* criarFila(int capacidade) {
    Fila* fila = (Fila*)malloc(sizeof(Fila));
    fila->capacidade = capacidade;
    fila->inicio = fila->fim = -1;
    fila->array = (int*)malloc(fila->capacidade * sizeof(int));
    return fila;
}

int filaVazia(Fila* fila) {
    return fila->inicio == -1;
}

void enfileirar(Fila* fila, int item) {
    if (fila->fim == fila->capacidade - 1)
        return;
    if (fila->inicio == -1)
        fila->inicio = 0;
    fila->fim++;
    fila->array[fila->fim] = item;
}

int desenfileirar(Fila* fila) {
    if (filaVazia(fila))
        return -1;
    int item = fila->array[fila->inicio];
    if (fila->inicio == fila->fim)
        fila->inicio = fila->fim = -1;
    else
        fila->inicio++;
    return item;
}

Grafo* criarGrafo(int numVertices) {
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->numVertices = numVertices;
    grafo->arrayListaAdj = (ListaAdj*)malloc(numVertices * sizeof(ListaAdj));
    for (int i = 0; i < numVertices; ++i)
        grafo->arrayListaAdj[i].inicio = NULL;
    return grafo;
}

void adicionarAresta(Grafo* grafo, int origem, int destino) {
    NoLista* novoNo = criarNoLista(destino);
    novoNo->prox = grafo->arrayListaAdj[origem].inicio;
    grafo->arrayListaAdj[origem].inicio = novoNo;
}

void buscaEmLargura(Grafo* grafo, int origem, int destino) {
    Fila* fila = criarFila(grafo->numVertices);
    int* visitados = (int*)malloc(grafo->numVertices * sizeof(int));
    int* distancia = (int*)malloc(grafo->numVertices * sizeof(int));
    int* predecessor = (int*)malloc(grafo->numVertices * sizeof(int));

    for (int i = 0; i < grafo->numVertices; ++i) {
        visitados[i] = 0;
        distancia[i] = -1;
        predecessor[i] = -1; 
    }

    enfileirar(fila, origem);
    visitados[origem] = 1;
    distancia[origem] = 0;

    printf("Caso de Teste #%d - BFS(%d)\n\n", casoTeste++, origem);

    while (!filaVazia(fila)) {
        int verticeAtual = desenfileirar(fila);
        printf("Iniciando busca em largura a partir de %d\n", verticeAtual);

       
        NoLista* temp = grafo->arrayListaAdj[verticeAtual].inicio;
        int* verticesAdjacentes = (int*)malloc(grafo->numVertices * sizeof(int));
        int count = 0;
        while (temp) {
            verticesAdjacentes[count++] = temp->vertice;
            temp = temp->prox;
        }
        for (int i = 0; i < count - 1; ++i) {
            for (int j = i + 1; j < count; ++j) {
                if (verticesAdjacentes[i] > verticesAdjacentes[j]) {
                    int temp = verticesAdjacentes[i];
                    verticesAdjacentes[i] = verticesAdjacentes[j];
                    verticesAdjacentes[j] = temp;
                }
            }
        }
        for (int i = 0; i < count; ++i) {
            int verticeAdjacente = verticesAdjacentes[i];
            if (!visitados[verticeAdjacente]) {
                enfileirar(fila, verticeAdjacente);
                visitados[verticeAdjacente] = 1;
                distancia[verticeAdjacente] = distancia[verticeAtual] + 1;
                predecessor[verticeAdjacente] = verticeAtual;
            }
        }
        free(verticesAdjacentes);
    }
    printf("\n");

    for (int i = 0; i < grafo->numVertices; ++i) {
        printf("%d | ", i);
        if (distancia[i] == -1)
            printf("- | ");
        else
            printf("%d | ", distancia[i]);

        if (predecessor[i] == -1)
            printf("-\n");
        else
            printf("%d\n", predecessor[i]);
    }
    printf("\n");

    if (distancia[destino] == -1){
        printf("Sem caminho entre %d e %d\n", origem, destino);
    }
    else {
        printf("Caminho entre %d e %d: ", origem, destino);
        int caminho[grafo->numVertices], count = 0;
        int pred = destino;
        while (pred != -1) {
            caminho[count++] = pred;
            pred = predecessor[pred];
        }
        for (int i = count - 1; i >= 0; --i)
            printf("%d%s", caminho[i], i == 0 ? "\n" : " => ");
    }
    
    printf("\n--------\n");

    free(visitados);
    free(distancia);
    free(predecessor);
    free(fila);
}

int main() {
    int V, A, T;
    scanf("%d %d %d", &V, &A, &T);

    Grafo* grafo = criarGrafo(V);
    
    printf("--------\n\n");
    for (int i = 0; i < A; ++i) {
        int origem, destino;
        scanf("%d %d", &origem, &destino);
        adicionarAresta(grafo, origem, destino);
    }


    for (int i = 0; i < T; ++i) {
        int origem, destino;
        scanf("%d %d", &origem, &destino);
        buscaEmLargura(grafo, origem, destino);
        printf("\n");
    }

    return 0;
}
