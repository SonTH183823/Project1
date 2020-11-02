#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node_Tree
{
    int key;
    int value;
    int check;
    struct Node_Tree *left;
    struct Node_Tree *right;
    int height;
}Map;

int height(struct Node_Tree *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

int Max(int a, int b)
{
    return (a > b) ? a : b;
}

//tao node tree moi
struct Node_Tree *newNode_Tree(int key, int value)
{
    struct Node_Tree *node_Tree = (struct Node_Tree *)
        malloc(sizeof(struct Node_Tree));
    node_Tree->key = key;
    node_Tree->value = value;
    node_Tree->check = 0;
    node_Tree->left = NULL;
    node_Tree->right = NULL;
    node_Tree->height = 1; 
    return (node_Tree);
}

//xoay de tao cay can bang
struct Node_Tree *rightRotate(struct Node_Tree *y)
{
    struct Node_Tree *x = y->left;
    struct Node_Tree *T2 = x->right;

    x->right = y;
    y->left = T2;
    y->height = Max(height(y->left), height(y->right)) + 1;
    x->height = Max(height(x->left), height(x->right)) + 1;
    return x;
}

struct Node_Tree *leftRotate(struct Node_Tree *x)
{
    struct Node_Tree *y = x->right;
    struct Node_Tree *T2 = y->left;

    y->left = x;
    x->right = T2;
    x->height = Max(height(x->left), height(x->right)) + 1;
    y->height = Max(height(y->left), height(y->right)) + 1;
    return y;
}

int getBalance(struct Node_Tree *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

struct Node_Tree *insert(struct Node_Tree *node_Tree, int key, int value)
{
    if (node_Tree == NULL)
        return (newNode_Tree(key, value));
    if (key < node_Tree->key)
        node_Tree->left = insert(node_Tree->left, key, value);
    else if (key > node_Tree->key)
        node_Tree->right = insert(node_Tree->right, key, value);
    else 
        return node_Tree;

    node_Tree->height = 1 + Max(height(node_Tree->left),
                           height(node_Tree->right));

    int balance = getBalance(node_Tree);

    if (balance > 1 && key < node_Tree->left->key)
        return rightRotate(node_Tree);

    // Right Right Case
    if (balance < -1 && key > node_Tree->right->key)
        return leftRotate(node_Tree);

    // Left Right Case
    if (balance > 1 && key > node_Tree->left->key)
    {
        node_Tree->left = leftRotate(node_Tree->left);
        return rightRotate(node_Tree);
    }

    // Right Left Case
    if (balance < -1 && key < node_Tree->right->key)
    {
        node_Tree->right = rightRotate(node_Tree->right);
        return leftRotate(node_Tree);
    }

    return node_Tree;
}



int findValue(struct Node_Tree *root, int key)
{
    if(root == NULL) return -1;
    struct Node_Tree *p = root;
    while (1)
    {
        if (key > p->key)
        {
            if (p->right != NULL)
                p = p->right;
            else
            {
                return -1;
            }
        }
        else if (key < p->key)
        {
            if (p->left != NULL)
                p = p->left;
            else
            {
                return -1;
            }
        }
        else
            return p->value;
    }
    return -1;
}
