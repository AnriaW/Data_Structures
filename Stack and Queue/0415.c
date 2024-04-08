#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node node;
struct node {
  char item;
  node *next;
};

typedef struct stack stack;
struct stack {
  int size;
  node *top;
};

stack* createStack() {
  stack *new_stack = (stack*) malloc(sizeof(stack));
  new_stack->size = 0;
  new_stack->top = NULL;
  return new_stack;
}

node* createNode(char item)
{
  node *new_node = (node*) malloc(sizeof(node));
  new_node->item = item;
  new_node->next = NULL;
  return new_node;
}

void push(stack *stack, char item) {
  node *new_node = createNode(item);
  new_node->next = stack->top;
  stack->top = new_node;
  stack->size += 1;
}

int peek(stack *stack) {
  return stack->top->item;
}

int pop(stack *stack) {
  char value = stack->top->item;
  node *el = stack->top;
  stack->top = stack->top->next;
  free(el);

  return value;
}

int main() {
  char arr[256];
  int i, j, qtde, tam, cnt = 1;
  stack *stack = createStack();

  scanf("%d", &qtde);
  getchar();

  for(i = 0; i < qtde; i++) {
    fgets(arr, 256, stdin);

    for(j = 0; arr[j] != '\0'; j++) {
      if(arr[j] == ']' || arr[j] == ')') {
        if(stack->top == NULL) {
          cnt = -1;
          printf("No\n");
          break;
        }
        else {
          if(peek(stack) == '(' && arr[j] == ')' || peek(stack) == '[' && arr[j] == ']') {
            pop(stack);
          }
          else {
            cnt = 0;
          }
        }
      }
      else if(arr[j] == '(' || arr[j] == '[') {
        push(stack, arr[j]);
      }
    }

    if(stack->top == NULL && cnt == 1) {
      printf("Yes\n");
    }
    if(stack->top != NULL || cnt == 0) {
      cnt = 1;
      printf("No\n");
    }
    stack->top = NULL;
    cnt = 1;
  }

  return 0;
}