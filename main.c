#include "edges.h"
#include "nodes.h"
#include "algo.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    pnode graph = NULL;
    char command = '0';
    while(command != EOF) {
        command = getc(stdin);
        // printf("COMMAND: %c\n", command);
        switch (command) {
        case 'A':
            build_graph_cmd(&graph);
            printGraph_cmd(graph);
            break;

        case 'B':
            insert_node_cmd(&graph);
            printGraph_cmd(graph);
            break;

        case 'D':
            delete_node_cmd(&graph);
            printGraph_cmd(graph);
            break;
        
        case 'S':
            shortsPath_cmd(graph);
            break;

        case 'T':
            TSP_cmd(graph);
            break;

        default:
            break;
        }
    }
    return 0;
}