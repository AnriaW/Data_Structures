#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

typedef struct node node;

node* add(node* head, int data) {
    node* new_node = (node*)malloc(sizeof(node));
    if (new_node == NULL) {
        fprintf(stderr, "Falha na aloca??o de mem?ria\n");
        exit(1);
    }
    new_node->data = data;
    new_node->next = NULL;

    if (head == NULL) {
        return new_node;
    } else {
        node* current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
        return head;
    }
}


node* comparation(node* head1, node* head2) {
    node* result = NULL;
    node* current1 = head1;
    node* current2 = head2;

    while (current1 != NULL && current2 != NULL) {
        if (current1->data == current2->data) {
            node* temp = result;
            while (temp != NULL) {
                if (temp->data == current1->data) {
                    break;
                }
                temp = temp->next;
            }
            if (temp == NULL) {
                result = add(result, current1->data);
            }
            current1 = current1->next;
            current2 = current2->next;
        } else if (current1->data < current2->data) {
            current1 = current1->next;
        } else {
            current2 = current2->next;
        }
    }

    return result;
}



void insertion_sort(node **head) {
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }

    node *sorted = NULL;
    node *current = *head;

    while (current != NULL) {
        node *next = current->next;

        if (sorted == NULL || current->data < sorted->data) {
            current->next = sorted;
            sorted = current;
        } else {
            node *temp = sorted;
            while (temp->next != NULL && temp->next->data < current->data) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }

        current = next;
    }

    *head = sorted;
}

void print_forward(node* head) {
    node* current = head;
    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    }
}

void free_list(node* head) {
    while (head != NULL) {
        node* temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    node* head1 = NULL;
    node* head2 = NULL;
    node* head3 = NULL;
    int i, data;

    for (i = 0; i < 20; i++) {
        scanf("%d", &data);
        head1 = add(head1, data);
    }

    insertion_sort(&head1);


    for (i = 0; i < 20; i++) {
        scanf("%d", &data);
        head2 = add(head2, data);
    }

    insertion_sort(&head2);

    head3 = comparation(head1, head2);

    if (head3 == NULL) {
        printf("VAZIO\n");
    } else {
        insertion_sort(&head3);
        print_forward(head3);
    }

    free_list(head1);
    free_list(head2);
    free_list(head3);

    return 0;
}
