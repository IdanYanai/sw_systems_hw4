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
        printf("COMMAND: %c\n", command);
        if(command == 'A')
            build_graph_cmd(&graph);
        else if(command == 'B')
            insert_node_cmd(&graph);
        else if(command == 'D')
            delete_node_cmd(&graph);
        else if(command == 'S')
            shortsPath_cmd(graph);
        else if(command == 'P')
            TSP_cmd(graph);  
        printGraph_cmd(graph);
    }
    return 0;
}