#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

typedef struct _btree
{
    int item;
    struct _btree *left;
    struct _btree *right;
} btree;

btree *create_tree(int item, btree *left, btree *right)
{
    btree *new_tree = (btree *) calloc(1, sizeof(btree));

    new_tree->item = item;

    new_tree->left = left;

    new_tree->right = right;

    return new_tree;
}

btree *construct_btree(char tree[], int *i)
{
    if(tree[*i] == '(' && tree[*i + 1] == ')')
    {
        *i += 2;
        return NULL;
    }

    else if(tree[*i] == '(') *i += 1;

    char almost_numbers[100];
    
    int j = 0;
    while(tree[*i] != '(' && tree[*i] != ')')
    {
        if(tree[*i] == ' ')
        {
            (*i) += 1;
        }
        else
        {
            almost_numbers[j] = tree[*i];
            (*i) += 1;
            j++;
        }
    }

    almost_numbers[j] = '\0';

    int finally_numbers = atoi(almost_numbers);

    btree *reggae_roots = create_tree(finally_numbers, NULL, NULL);

    reggae_roots->left = construct_btree(tree, i);
    reggae_roots->right = construct_btree(tree,i);

    if(tree[*i] == ')') *i += 1;

    return reggae_roots;
}

int is_valid_btree(btree *root, int min, int max)
{
    if(root == NULL) return 1;

    if(root->item < min || root->item > max) return 0;

    return is_valid_btree(root->left, min, root->item) && is_valid_btree(root->right, root->item, max);
}

int main()
{
    char tree[1000];

    fgets(tree, 1000, stdin);

    //nice_tree(tree);

    int n = strlen(tree);

    char nice_tree[1000];

    /*for(int i = 0; i < n; i++)
    {
        printf("%c", tree[i]);
    }
    puts("\n");*/

    int j = 0;
    for(int i = 0; i < n; i++)
    {
        if(tree[i] != ' ')
        {
            nice_tree[j] = tree[i];
            j++;
        }
    }

    /*int n2 = strlen(nice_tree);

    for(int i = 0; i < n2; i++)
    {
        printf("%c", nice_tree[i]);
    }
    puts("");*/

    int i = 0;
    btree *root = construct_btree(nice_tree, &i);

    if(is_valid_btree(root, INT_MIN, INT_MAX)) printf("VERDADEIRO\n");
    
    else printf("FALSO\n");

    return 0;
}