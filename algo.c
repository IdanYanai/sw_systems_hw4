#include "nodes.h"
#include "edges.h"
#include <stdlib.h>
#include <stdio.h>

void delete_node_cmd(pnode *head) {
    int node_num;
    scanf(" %d", &node_num);

    // remove incoming edges
    pnode current_node = head;
    pedge current_edge;
    pedge last_edge = NULL;
    while(current_node != NULL) {
        current_edge = current_node->edges;
        while((current_edge->endpoint->node_num != node_num) && (current_edge != NULL)) {
            last_edge = current_edge;
            current_edge = current_edge->next;
        }
        if(current_edge != NULL) {
            if(last_edge != NULL)
                last_edge->next = current_edge->next;
            free(current_edge);
        }
    }

    // remove the node from the list
    current_node = head;
    pnode last_node = NULL;
    while(current_node->node_num != node_num) {
        last_node = current_node;
        current_node = current_node->next;
    }

    if(last_node != NULL)
        last_node->next = current_node->next;
    
    removeNode(current_node);
}

void build_graph_cmd(pnode *head) {
    // if there is already a graph we delete it first
    if(head != NULL)
        deleteGraph_cmd(head);

    int len;
    scanf(" %d", &len);
    node nodes[len];
    for(int i=0;i<len;i++) {
        scanf(" %c");
        
    }
}

void insert_node_cmd(pnode *head) {
    // get node num
    int node_num;
    scanf(" %d", &node_num);

    // create new edges linked list
    int weight, endpoint_num;
    pnode current_node;
    pedge edges = NULL;
    while(1) {
        if(scanf(" %d %d", &endpoint_num, &weight) != 2)
            break;
        current_node = head;
        while(current_node->node_num != endpoint_num)
            current_node = current_node->next;
        if(edges == NULL)
            edges = newEdge(weight, current_node, NULL);
        else
            edges->next = newEdge(weight, current_node, NULL);
    }

    // check if node exists already
    pnode current_node = head;
    while(current_node->node_num != node_num && current_node != NULL)
            current_node = current_node->next;

    // if node doesnt exist create new one at end of list
    if(current_node == NULL) {
        current_node = head;
        while(current_node->next != NULL)
            current_node = current_node->next;
        
        current_node->next = newNode(node_num, edges, NULL);
    }
    else // if node exists we simply give it the new edges
        current_node->edges = edges;
}

void printGraph_cmd(pnode head) {
    while(head != NULL) {
        printNode(head);
        head = head->next;
    }
}

void deleteGraph_cmd(pnode* head) {
    pnode next;
    pnode current_node = head;
    while(head != NULL) {
        next = current_node->next;
        removeNode(current_node);
        current_node = next;
    }
}

void shortsPath_cmd(pnode head) {

}

void TSP_cmd(pnode head) {

}
