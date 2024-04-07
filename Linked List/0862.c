#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    int item;
    struct node *next;
    int position;
} node;

node *linking_numbers_backwards(node *head, int item, node **tail, int position)
{
    node *new_node = (node*) malloc(sizeof(node));
    new_node->item = item;
    new_node->next = NULL;
    new_node->position = position;

    if(head == NULL)
    {
        head = new_node;
        *tail = new_node;
        return new_node;
    }
    else
    {
        (*tail)->next = new_node;
        *tail = new_node;
        return head;
    }
}

void breakNumber(char *num, node **head, node **tail)
{
    int length = strlen(num);
    for(int i = 0; i < length; i++)
    {
        int item = num[i] - '0';
        *head = linking_numbers_backwards(*head, item, tail, i); 
    }
}

void sequence_of_zeros(node *list){
    node *final = list;
    int cnt = 0;
    int final_big = 0;
    int cnt_big = 0;

    while(final !=  NULL){
        if(final->item == 0){
            cnt++;
        }
        else{
            cnt = 0;
        }

        if(cnt >= cnt_big){
            cnt_big = cnt;
            final_big = final->position;        
        }
        final = final->next;
    }

   printf("%d %d\n", final_big-cnt_big+1, final_big);
}

void free_list(node *list)
{
    node *tmp;

    while (list != NULL)
    {
        tmp = list;
        list = list->next;
        free(tmp);
    }
}

int main(){
    node *list = NULL;
    node* tail = NULL;
    char entrada[1000];

    while (1) {
        scanf("%s", entrada);
        
        if (strcmp(entrada, "0") == 0) {
            break;
        }

        breakNumber(entrada, &list, &tail);
        sequence_of_zeros(list);

        free_list(list);
        list = NULL;
        tail = NULL;
    }
    
    return 0;
}