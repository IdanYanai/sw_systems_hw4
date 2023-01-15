typedef struct node *pnode;;

typedef struct edge {
    int weight;
    pnode endpoint;
    struct edge *next;
} edge, *pedge;

pedge newEdge(int weight, pnode endpoint, edge* next);