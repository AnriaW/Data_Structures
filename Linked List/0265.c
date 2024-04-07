#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char item;
    int data;
    struct Node* next;
};

typedef struct Node node;

node *add_node(node *head, int occurence, int item)
{
    node *new_node = (node*) calloc(1, sizeof(node));
    new_node->data = occurence;
    new_node->item = item;
    new_node->next = NULL;

    if(head == NULL)
    {
        return new_node;
    }
    else
    {
        node *aux = head;
        while(aux->next != NULL)
        {
            aux = aux->next;
        }

        aux->next = new_node;

        return head;
    }
}

void frequencies(node *head, int letter_and_numbers)
{
    node *aux = head;
    while(aux != NULL)
    {
        if(aux->item == letter_and_numbers)
        {
            aux->data += 1;
            break;
        }
        aux = aux->next;
    }
}

void print_list(node *head)
{
    node *aux = head;
    while(aux != NULL)
    {
        if(aux->data != 0)
            printf("%c %d\n", aux->item, aux->data);
        
        aux = aux->next;
    }
}

void free_list(node* head) {
    node* temp;

    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}


int main(){
    node *list = NULL;

    for (int i = 255; i >= 0; i--) list = add_node(list, 0, i);

    char texto[1000];
    fgets(texto, 1000, stdin);

    int tam = strlen(texto);

    for(int i = 0; i < tam; i++) frequencies(list, texto[i]);

    print_list(list);

    free_list(list);
    
    return 0;
}
