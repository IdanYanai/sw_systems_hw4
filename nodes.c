#include "nodes.h"
#include "edges.h"
#include <stdlib.h>
#include <stdio.h>

node* newNode(int node_num, pedge edges, node* next) {
    node* n = (node*)malloc(sizeof(node));
    if(n == NULL)
        return NULL;

    n->next = next;
    n->node_num = node_num;
    n->edges = edges;

    return n;
}

void removeNode(pnode n) {
    if(n == NULL)
        return;

    pedge current_edge = n->edges;
    pedge next = NULL;
    while(current_edge != NULL) {
        next = current_edge->next;
        free(current_edge);
        current_edge = next;
    }   
    free(n);
}

void printNode(pnode n) {
    printf(" | %d | \n", n->node_num);
    pedge current_edge = n->edges;
    while(current_edge != NULL) {
        printf("---%d--->%d\n", current_edge->weight, current_edge->endpoint->node_num);
        current_edge = current_edge->next;
    }
}