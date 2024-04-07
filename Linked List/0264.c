#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

typedef struct node node;

node* add(node* head, int data) {
    node* new = (node*)malloc(sizeof(node));
    new->data = data;
    new->next = head;
    return new;
}

void print_backward(node *tail) {
    if (tail != NULL) {
        printf("%d ", tail->data);
        print_backward(tail->next);
    }
}

int main() {
    node* head = NULL;
    int data;
    
    while (scanf("%d", &data) != EOF) {
        head = add(head, data);
    }

    print_backward(head);

    return 0;
}
