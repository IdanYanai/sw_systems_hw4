#include "nodes.h"
#include "edges.h"
#include "algo.h"
#include <stdlib.h>
#include <stdio.h>

void delete_node_cmd(pnode *head) {
    int node_num;
    scanf(" %d", &node_num);

    // remove incoming edges
    pnode current_node = *head;
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
    current_node = *head;
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
    if(*head != NULL)
        deleteGraph_cmd(head);

    int len;
    scanf(" %d", &len);
    int node_num, weight, endpoint_num;
    pnode current_node, endpoint;
    pedge edges, iterator;
    char n;
    
    for(int i=0;i<len;i++) {
        if((scanf(" %c", &n)) != 1)
            break;
        scanf(" %d", &node_num);
        // if first node create the head
        if(*head == NULL) {
            (*head) = newNode(node_num, NULL, NULL);
            current_node = *head;
        }
        else {
            // check if node exists already
            current_node = *head;
            while((current_node->node_num != node_num) && (current_node->next != NULL))
                    current_node = current_node->next;

            // if node doesnt exist we create new one at end of list
            if(current_node->node_num != node_num) {
                current_node->next = newNode(node_num, NULL, NULL);
                current_node = current_node->next;
            }
        }

        // get edges and create new endpoint node if doesnt exist
        edges = NULL;
        endpoint = NULL;
        iterator = NULL;
        while(1) {
            if(scanf(" %d %d", &endpoint_num, &weight) != 2)
                break;

            // find endpoint node
            endpoint = *head;
            while((endpoint->node_num != endpoint_num) && (endpoint->next != NULL))
                endpoint = endpoint->next;

            // if it doesnt exist, create new one at end of list
            if(endpoint->node_num != endpoint_num) {
                endpoint->next = newNode(endpoint_num, NULL, NULL);
                endpoint = endpoint->next;
            }
            
            if(edges == NULL)
                edges = newEdge(weight, endpoint, NULL);
            else {
                iterator = edges;
                while(iterator->next != NULL)
                    iterator = iterator->next;
                iterator->next = newEdge(weight, endpoint, NULL);
            }
        }

        current_node->edges = edges;
    }
    printf("finished");
}

void insert_node_cmd(pnode *head) {
    // get node num
    int node_num;
    scanf(" %d", &node_num);

    // create new edges linked list
    int weight, endpoint_num;
    pnode current_node;
    pedge edges = NULL;
    pedge iterator;
    while(1) {
        if(scanf(" %d %d", &endpoint_num, &weight) != 2)
            break;
        current_node = *head;
        while(current_node->node_num != endpoint_num)
            current_node = current_node->next;
        if(edges == NULL)
            edges = newEdge(weight, current_node, NULL);
        else {
            iterator = edges;
            while(iterator->next != NULL)
                iterator = iterator->next;
            iterator->next = newEdge(weight, current_node, NULL);
        }
    }

    // check if node exists already
    current_node = *head;
    while(current_node->node_num != node_num && current_node != NULL)
            current_node = current_node->next;

    // if node doesnt exist create new one at end of list
    if(current_node == NULL) {
        current_node = *head;
        while(current_node->next != NULL)
            current_node = current_node->next;
        
        current_node->next = newNode(node_num, edges, NULL);
    }
    else // if node exists we simply give it the new edges
        current_node->edges = edges;
}

void printGraph_cmd(pnode head) {
    printf("============= GRAPH =============\n");
    while(head != NULL) {
        printNode(head);
        head = head->next;
    }
}

void deleteGraph_cmd(pnode* head) {
    pnode next;
    pnode current_node = *head;
    while(head != NULL) {
        next = current_node->next;
        removeNode(current_node);
        current_node = next;
    }
}

void shortsPath_cmd(pnode head) {
    int path = -1, src_num, dest_num;
    pnode src, dest, iterator;
    scanf(" %d %d", &src_num, &dest_num);

    // find source node
    iterator = head;
    while(iterator->node_num != src_num)
        iterator = iterator->next;
    src = iterator;

    // find dest node
    iterator = head;
    while(iterator->node_num != dest_num)
        iterator = iterator->next;
    dest = iterator;

    // find shortest path;



    printf("Dijsktra shortest path: %d\n", path);
}

void TSP_cmd(pnode head) {
    int path = -1;
    int len;
    scanf(" %d", &len);
    pnode nodes[len];
    pnode current_node;
    int node_num;

    // get nodes
    for(int i=0;i<len;i++) {
        scanf(" %d", &node_num);
        current_node = head;
        while(current_node->node_num != node_num)
            current_node = current_node->next;
        nodes[i] = current_node;
    }

    // calculate path



    printf("TSP shortest path: %d\n", path);
}
