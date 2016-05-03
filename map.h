//Definition of Key and Value.
//It can be changed to any type as long as functions compare and print
//are changed accordingly. Compare just determines how are keys compared as it
//will not be the same for chars and ints and print determines how are key
//and value printed. Bellow commented out is an example when Key and Value
//are ints and user can use that as a template to change Key and Value to any type.

typedef char* Key;
typedef char* Value;

void print(Key k, Value v);
int compare(Key p, Key s);


struct Tree;
typedef struct Tree tree;

//Creates a new empty tree
tree* newTree();

//Finds a leaf of the tree containing stated key.
void find(Key k, tree *t);

//Inserts a specific key and value into the tree.
void insert(Key k, Value v, tree *t);

//Deletes a leaf with specific key from the tree.
void delete(Key k, tree *t);

//Prints all the leafs from the tree.
void printTree(tree *t);
