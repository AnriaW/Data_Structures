#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node node;
struct node {
  int item;
  node *next;
};

typedef struct stack stack;
struct stack {
  int size, current;
  node *top;
};

stack* createStack() {
  stack *new_stack = (stack*) malloc(sizeof(stack));
  new_stack->size = 0;
  new_stack->top = NULL;
  return new_stack;
}

node* createNode(int item)
{
  node *new_node = (node*) malloc(sizeof(node));
  new_node->item = item;
  new_node->next = NULL;
  return new_node;
}

void push(stack *stack, int item) {
  node *new_node = createNode(item);
  new_node->next = stack->top;
  stack->top = new_node;
  stack->size += 1;
  stack->current = stack->size;
}

int peek(stack *stack) {
  return stack->top->item;
}

int pop(stack *stack) {
  int value = stack->top->item;
  node *el = stack->top;
  stack->top = stack->top->next;
  free(el);

  return value;
}

int main() {
  int i, b = -1;
  char act[255];
  node *node;
  stack *stack = createStack();

  while (scanf(" %[^\n]", act) != EOF) {
    if(act[0] == 'E') {
      push(stack, 1);
    }
    else if(act[0] == 'B') {
      stack->current -= 1;
      pop(stack);
    }
    else {
      push(stack, 1);
    }
  }
  while(stack->top != NULL) {
    if(stack->top != NULL) {
      b += 1;
    }
    pop(stack);
  }
  printf("BACK: %d\nFORWARD: %d\n", b, stack->size - stack->current);

  return 0;
}