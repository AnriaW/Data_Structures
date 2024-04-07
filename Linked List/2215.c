#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Erro ao alocar mem�ria\n");
        exit(0);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void prepend(Node** head, int data) {
    Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

Node* add(Node* a, Node* b) {
    Node* result = NULL;
    int carry = 0;

    while (a != NULL || b != NULL || carry) {
        int sum = carry;

        if (a != NULL) {
            sum += a->data;
            a = a->next;
        }

        if (b != NULL) {
            sum += b->data;
            b = b->next;
        }

        carry = sum / 10;
        sum %= 10;

        prepend(&result, sum);
    }

    return result;
}

void printList(Node* head) {
    if (head == NULL) {
        printf("Lista vazia!\n");
        return;
    }
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

void freeList(Node* head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Node* a = NULL;
    Node* b = NULL;
    char op;
    int num;
    int isFirstDigitA = 1;
    int isFirstDigitB = 1;

    while (1) {
        scanf(" %c", &op);
        if (op == '+') break;

        if (isdigit(op)) {
            num = op - '0';
            if (isFirstDigitA && num == 0) continue;
            prepend(&a, num);
            isFirstDigitA = 0;
        }
    }

    while (1) {
        scanf(" %c", &op);
        if (op == '=') break;

        if (isdigit(op)) {
            num = op - '0';
            if (isFirstDigitB && num == 0) continue;
            prepend(&b, num);
            isFirstDigitB = 0;
        }
    }

    Node* result = add(a, b);

    printList(result);

    freeList(a);
    freeList(b);
    freeList(result);

    return 0;
}
