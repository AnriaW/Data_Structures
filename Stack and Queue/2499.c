#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    int top;
    int items[MAX];
} Stack;

void push(Stack *s, int value) {
    if (s->top == MAX - 1) {
        printf("Pilha cheia\n");
        return;
    }
    s->items[++(s->top)] = value;
}

int pop(Stack *s) {
    if (s->top == -1) {
        printf("Pilha vazia\n");
        return -1;
    }
    return s->items[(s->top)--];
}

void print(Stack *s) {
    for (int i = s->top; i >= 0; i--) {
        printf("%d", s->items[i]);
        if (i != 0) {
            printf(" ");
        }
    }
    printf("\n");
}

int main() {
    Stack s;
    s.top = -1;

    char command[20];
    int value;

    while (1) {
        scanf("%s", command);
        if (strcmp(command, "Finalizar") == 0) {
            break;
        } else if (strcmp(command, "Empilhar") == 0) {
            scanf("%d", &value);
            push(&s, value);
        } else if (strcmp(command, "Desempilhar") == 0) {
            pop(&s);
        } else if (strcmp(command, "Imprimir") == 0) {
            print(&s);
        }
    }

    return 0;
}
