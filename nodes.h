typedef struct edge *pedge;

typedef struct node {
    int node_num;
    pedge edges;
    struct node *next;
} node, *pnode;

node* newNode(int node_num, pedge edges, node* next);
void removeNode(pnode n);
void printNode(pnode n);