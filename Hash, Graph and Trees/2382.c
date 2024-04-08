#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

int countNodes(Node* root) {
    if (root == NULL)
        return 0;
    return (1 + countNodes(root->left) + countNodes(root->right));
}

int isCompleteUtil(Node* root, int index, int node_count) {
    if (root == NULL)
        return 1;
    if (index >= node_count)
        return 0;
    return (isCompleteUtil(root->left, 2 * index + 1, node_count) &&
            isCompleteUtil(root->right, 2 * index + 2, node_count));
}

int isComplete(Node* root) {
    int node_count = countNodes(root);
    return isCompleteUtil(root, 0, node_count);
}

Node* createTree(char* str, int* index, int* node_count) {
    if (str[*index] == '(') {
        (*index)++;
        if (str[*index] == ')') {
            (*index)++;
            return NULL;
        }
        int num = 0;
        while (str[*index] != '(') {
            num = num * 10 + (str[*index] - '0');
            (*index)++;
        }
        Node* root = newNode(num);
        (*node_count)++;
        root->left = createTree(str, index, node_count);
        root->right = createTree(str, index, node_count);
        (*index)++;
        return root;
    }
    return NULL;
}

bool printOneChildNodes(Node* root) {
    if (root == NULL)
        return false;

    bool has_one_child = false;

    bool left_has_one_child = printOneChildNodes(root->left);

    if ((root->left == NULL && root->right != NULL) || (root->left != NULL && root->right == NULL)) {
        printf("%d ", root->data);
        has_one_child = true;
    }

    bool right_has_one_child = printOneChildNodes(root->right);

    return has_one_child || left_has_one_child || right_has_one_child;
}


int main() {
    char str[1000];
    while (scanf("%s", str) != EOF) {
        int index = 0;
        int node_count = 0;
        Node* root = createTree(str, &index, &node_count);
        
        if (root == NULL) {
            printf("arvore vazia\n");
            continue; 
        }

        if (!isComplete(root)) {
            printf("nao completa\n");
            printf("nos com um filho: ");
            printOneChildNodes(root);
            printf("\n");
        } else {
            printf("completa\n");
            printf("total de nos: %d\n", node_count);
        }
    }
    return 0;
}
