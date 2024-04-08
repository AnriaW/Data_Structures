#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int data;
    struct Node* next;
};

struct StackNode {
    struct Node* list;
    struct StackNode* next;
};

struct Stack {
    struct StackNode* top;
};

struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    if (stack == NULL) {
        printf("Erro ao alocar mem?ria para a pilha.\n");
        exit(EXIT_FAILURE);
    }
    stack->top = NULL;
    return stack;
}

int isEmpty(struct Stack* stack) {
    return (stack->top == NULL);
}

void pushList(struct Stack* stack, struct Node* newList) {
    struct StackNode* newStackNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    if (newStackNode == NULL) {
        printf("Erro ao alocar mem?ria para o n? da pilha.\n");
        exit(EXIT_FAILURE);
    }
    newStackNode->list = newList;
    newStackNode->next = stack->top;
    stack->top = newStackNode;
}

void popAndPrint(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("EMPTY STACK\n");
        return;
    }
    struct StackNode* temp = stack->top;
    struct Node* current = temp->list;
    struct Node* tempList = NULL;
    while (current != NULL) {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        if (newNode == NULL) {
            printf("Erro ao alocar mem�ria para o n� da lista tempor�ria.\n");
            exit(EXIT_FAILURE);
        }
        newNode->data = current->data;
        newNode->next = tempList;
        tempList = newNode;
        current = current->next;
    }
    while (tempList != NULL) {
        printf("%d", tempList->data);
        if (tempList->next != NULL) {
            printf(" ");
        }
        struct Node* nextNode = tempList->next;
        free(tempList);
        tempList = nextNode;
    }
    printf("\n");
    stack->top = stack->top->next;
    free(temp);
}
int main() {
    struct Stack* stack = createStack();
    char command[1000];
    int num;

    while (scanf("%s", command) != EOF) {
        if (strcmp(command, "PUSH") == 0) {
            struct Node* newList = NULL;
            while (1) {
                scanf("%d", &num);
                struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
                newNode->data = num;
                newNode->next = newList;
                newList = newNode;
                if (getchar() == '\n') {
                    break;
                }
            }
            pushList(stack, newList);
        } else if (strcmp(command, "POP") == 0) {
            popAndPrint(stack);
        } else {
            printf("Comando inv?lido. Tente novamente.\n");
        }
    }

    return 0;
}
