#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _no
{
    int valor;
    struct _no *esquerda;
    struct _no *direita;
    struct _no *pai;
} no;

no *criar_arvore(int valor, no *esquerda, no *direita, no *pai)
{
    no *nova_arvore = (no *) calloc(1, sizeof(no));
    nova_arvore->valor = valor;
    nova_arvore->esquerda = esquerda;
    nova_arvore->direita = direita;
    nova_arvore->pai = pai;
    return nova_arvore;
}

int tem_valor(no *arvore, int procurado, no **achado)
{
    *achado = arvore;
    if(arvore == NULL) return 0;
    if(arvore->valor == procurado) return 1;
    tem_valor(arvore->esquerda, procurado, achado);
    tem_valor(arvore->direita, procurado, achado);
    return tem_valor(arvore->esquerda, procurado, achado) || tem_valor(arvore->direita, procurado, achado);
}

no *buscar_valor(no *arvore, int procurado, no **achado)
{
    return tem_valor(arvore, procurado, achado) == 1 ? arvore : NULL; 
}

no *construir_arvore(char arvore[], int *indice, no *pai)
{
    if(arvore[*indice] == '(' && arvore[*indice + 1] == ')')
    {
        *indice += 2;
        return NULL;
    }

    else if(arvore[*indice] == '(') *indice += 1;

    char numeros[100];
    
    int j = 0;
    while(arvore[*indice] != '(' && arvore[*indice] != ')')
    {
        if(arvore[*indice] == ' ')
        {
            (*indice) += 1;
        }
        else
        {
            numeros[j] = arvore[*indice];
            (*indice) += 1;
            j++;
        }
    }

    numeros[j] = '\0';

    int valor_final = atoi(numeros);

    no *nova_raiz = criar_arvore(valor_final, NULL, NULL, pai);
    nova_raiz->esquerda = construir_arvore(arvore, indice, nova_raiz);
    nova_raiz->direita = construir_arvore(arvore, indice, nova_raiz);
    if(arvore[*indice] == ')') *indice += 1;
    return nova_raiz;
}

void imprimir_arvore(no *raiz)
{
    if(raiz != NULL) printf("(%d", raiz->valor);
    else printf("()");
    if(raiz != NULL) imprimir_arvore(raiz->esquerda);
    if(raiz != NULL) imprimir_arvore(raiz->direita);
    if(raiz != NULL) printf(")");
    return;
}

int main()
{
    char entrada[1000];
    fgets(entrada, 1000, stdin);
    int n = strlen(entrada);
    int j = 0;
    char sem_espacos[1000];

    for(int i = 0; i < n; i++)
    {
        if(entrada[i] != ' ')
        {
            sem_espacos[j] = entrada[i];
            j++;
        }
    }

    int indice = 0;
    no *raiz = construir_arvore(sem_espacos, &indice, NULL);

    while(1)
    {
        char entrada_auxiliar[1000];

        fgets(entrada_auxiliar, 1000, stdin);
        int n_auxiliar = strlen(entrada_auxiliar);

        if(n_auxiliar <= 3) break;

        char arvore_limpa[1000];

        int j = 0;

        for(int i = 0; i < n_auxiliar; i++)
        {
            if(entrada_auxiliar[i] != ' ')
            {
                arvore_limpa[j] = entrada_auxiliar[i];
                j++;
            }
        }

        int indice_auxiliar = 0;
        no *raiz_auxiliar = construir_arvore(arvore_limpa, &indice_auxiliar, NULL);
        int valor_procurado = raiz_auxiliar->valor;

        if(valor_procurado != raiz->valor)
        {
            no *achado = NULL;
            no *nova_raiz = buscar_valor(raiz, valor_procurado, &achado);

            no *pai_novo;

            if(achado->pai->esquerda == achado)
            {
                pai_novo = achado->pai->esquerda;
                achado->pai->esquerda = raiz_auxiliar;
                raiz_auxiliar->pai = pai_novo;
            }
            else if (achado->pai->direita == achado)
            {
                pai_novo = achado->pai->direita;
                achado->pai->direita = raiz_auxiliar;
                raiz_auxiliar->pai = pai_novo;
            }
            else if(achado == NULL)
            {
                raiz = raiz_auxiliar;
                imprimir_arvore(raiz);
            }
        }
        else
        {
            raiz = raiz_auxiliar;
        }
    }

    imprimir_arvore(raiz);
    puts("");
    
    return 0;
}
