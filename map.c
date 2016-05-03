#include "map.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//Single tree node structure
typedef struct Node{
    struct Node *left;
    Key k;
    Value v;
    struct Node *right;
} node;

//Tree structure
struct Tree{
    node *root;
};

//Creates a new node containing both key and value and pointing to NULL
//both left and right.
node* newNode(Key k, Value v){
    node *new = malloc(sizeof(node));
    *new = (node) {NULL, k, v, NULL};
    return new;
}

//If the current node is NULL it inserts new node at that place, otherwise
//it compares the key and moves left or right accordingly recursively calling
//itself untill a NULL node is reached.
void insertItem(node **n, Key k, Value v){
    if (*n == NULL){
        *n = newNode(k, v);
    } else {
        if (compare(k, (*n)->k) < 0) {
            insertItem(&(*n)->left, k, v);
        } else if (compare(k, (*n)->k) > 0){
            insertItem(&(*n)->right, k, v);
        }
    }
}

//Wrapper for the insert function.
void insert(Key k, Value v, tree *t){
    insertItem(&t->root, k, v);
}

//Creates a new tree and sets root to NULL.
tree* newTree(){
    tree *new = malloc(sizeof(tree));
    new->root = NULL;
    return new;
}

//Looks through the tree for a key and if found returns the node that
//contains it. Otherwise it returns NULL.
node *findNode(node *n, Key k) {
    if(n == NULL){
        return NULL;
    }
    else if(compare(k,n->k) == 0){
        return n;
    }
    else if(compare(k,n->k) < 0) {
        findNode(n->left,k);
    }
    else if(compare(k,n->k) > 0) {
        findNode(n->right,k);
    }
    return n;
}

//Wrapper for find function
void find(Key k, tree *t){
    t->root = findNode(t->root,k);
}

//Finds a minimum value (left most value) in the tree.
node* min(node* n){
    while (n->left != NULL){
        n = n->left;
    }
    return n;
}

//Recursively searches for the node and deletes it.
node* deleteNode(node *root, Key k){
    if (root == NULL) {
        return root;
    }
    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if (compare(k,root->k) < 0){
        root->left = deleteNode(root->left, k);
    }
    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if (compare(k,root->k) > 0){
        root->right = deleteNode(root->right, k);
    }
    // if key is same as root's key, then This is the node
    // to be deleted
    else{
        // node with only one child or no child
        if (root->left == NULL){
            node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL){
            node *temp = root->left;
            free(root);
            return temp;
        }
        // node with two children: Get the smallest value
        // from the right subtree
        node* temp = min(root->right);
        // Copy it's content to the current node
        root->k = temp->k;
        root->v = temp->v;
        // Delete it from it's previous place.
        root->right = deleteNode(root->right, temp->k);
    }
    return root;
}

//Wrapper for a delete function.
void delete(Key k, tree *t){
    t->root = deleteNode(t->root, k);
}

//Prints all the node content and stops when it reaches NULL.
void printNodeItems(node *n){
    if(n == NULL){
        return;
    }
    print(n->k,n->v);
    printNodeItems(n->left);
    printNodeItems(n->right);
}

//Calls print on the root of the tree.
void printTree(tree *t){
    printNodeItems(t->root);
}
