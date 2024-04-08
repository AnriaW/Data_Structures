#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct TreeNode {
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode* createNode(int value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

TreeNode* buildTree(char* s, int* index) {
    if (s[*index] == '\0') return NULL;
    (*index)++;
    int num = 0;
    while (s[*index] >= '0' && s[*index] <= '9') {
        num = num * 10 + (s[*index] - '0');
        (*index)++;
    }
    TreeNode* root = createNode(num);
    if (s[*index] == '(') {
        root->left = buildTree(s, index);
    }
    if (s[*index] == '(') {
        root->right = buildTree(s, index);
    }
    (*index)++;
    return root;
}

bool findNode(TreeNode* root, int target, int* depth) {
    if (root == NULL) return false;
    if (root->value == target) return true;
    if (findNode(root->left, target, depth)) {
        (*depth)++;
        return true;
    }
    if (findNode(root->right, target, depth)) {
        (*depth)++;
        return true;
    }
    return false;
}

int main() {
    char treeStr[1000];
    fgets(treeStr, 1000, stdin);
    int target;
    scanf("%d", &target);
    int i = 0;
    while (treeStr[i] != '\0') {
        if (treeStr[i] == '\n') {
            treeStr[i] = '\0';
            break;
        }
        i++;
    }

    int index = 0;
    TreeNode* root = buildTree(treeStr, &index);

    int depth = 0;
    if (findNode(root, target, &depth)) {
        printf("ESTA NA ARVORE\n");
        printf("%d\n", depth);
    } else {
        printf("NAO ESTA NA ARVORE\n");
        printf("-1\n");
    }

    return 0;
}
