#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Armazena o primeiro item da fila
typedef struct _stack STACK;

//Armazena o conteudo do no e um ponteiro para o proximo no da fila
typedef struct _node NODE;

struct _stack
{
    NODE* head;
};
struct _node
{
    int element;
    NODE* next;
};

//Cria uma stack com o a head NULL
STACK* Create_stack();

//Recebe um elemento e cria e retorna um novo node
// com o elemento passado
NODE* create_node(int element);

//Verifica se a pilha esta vazia
int IS_EMPTY(STACK* stack);

//Recebe uma pilha e Retorna o elemento que esta no topo da fila
int POP(STACK* stack);

//Recebe uma pilha e um inteiro e retorna a nova pilha
//Adiciona um novo node no topo da pilha
void PUSH(STACK* stack, int element);

//Recebe a pilha e a operacao a ser feita
//faz a operacao da calculadora
void result(STACK* stack, char operation);

//Recebe uma pilha vazia e quantas strings serao lidas
//Le as n strings que vao seguir e resolve as expressoes
void Calculadora(STACK* calculadora, int size);

int main()
{
    STACK* calculadora = Create_stack();
    int k;
    scanf("%d", &k);
    Calculadora(calculadora, k);
    printf("Coordenada 1: %d\n", POP(calculadora));
    scanf("%d", &k);
    Calculadora(calculadora, k);
    printf("Coordenada 2: %d\n", POP(calculadora));

}
NODE* create_node(int element) {
    NODE* new_node = (NODE*)malloc(sizeof(NODE));
    new_node->element = element;
    new_node->next = NULL;
    return new_node;
}

STACK* Create_stack() {
    STACK* stack = (STACK*)malloc(sizeof(STACK));
    if (stack == NULL) {
        printf("Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    stack->head = NULL;
    return stack;
}

int IS_EMPTY(STACK* stack) {
    return stack->head == NULL;
}

int POP(STACK* stack) {
    if (IS_EMPTY(stack)) {
        printf("Error: Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    int element = stack->head->element;
    NODE* temp = stack->head;
    stack->head = stack->head->next;
    free(temp);
    return element;
}

void PUSH(STACK* stack, int element) {
    NODE* new_node = create_node(element);
    new_node->next = stack->head;
    stack->head = new_node;
}

void result(STACK* stack, char operation) {
    int operand2 = POP(stack);
    int operand1 = POP(stack);
    int result;
    switch (operation) {
        case '+':
            result = operand1 + operand2;
            break;
        case '-':
            result = operand1 - operand2;
            break;
        case '*':
            result = operand1 * operand2;
            break;
        case '/':
            if (operand2 == 0) {
                printf("Error: Division by zero\n");
                exit(EXIT_FAILURE);
            }
            result = operand1 / operand2;
            break;
        default:
            printf("Error: Invalid operation\n");
            exit(EXIT_FAILURE);
    }
    PUSH(stack, result);
}

void Calculadora(STACK* calculadora, int size) {
    char expression[100];
    for (int i = 0; i < size; i++) {
        scanf("%s", expression);
        if (expression[0] >= '0' && expression[0] <= '9') {
            PUSH(calculadora, atoi(expression));
        } else {
            result(calculadora, expression[0]);
        }
    }
}
