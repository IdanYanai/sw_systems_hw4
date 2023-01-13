#include "edges.h"
#include <stdlib.h>

pedge newEdge(int weight, pnode endpoint, edge* next) {
    pedge e = (edge*)malloc(sizeof(edge));
    if (e == NULL)
        return NULL;

    e->weight = weight;
    e->endpoint = endpoint;
    e->next = next;

    return e;
}