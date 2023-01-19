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
    pedge last_edge;
    while(current_node != NULL) {
        current_edge = current_node->edges;
        last_edge = NULL;
        while(current_edge != NULL) {
            if(current_edge->endpoint->node_num == node_num)
                break;
            last_edge = current_edge;
            current_edge = current_edge->next;
        }
        if(current_edge != NULL) {
            if(last_edge != NULL)
                last_edge->next = current_edge->next;
            else
                current_node->edges = current_edge->next;
            free(current_edge);
        }
        current_node = current_node->next;
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
    while(current_node != NULL) {
        if(current_node->node_num == node_num)
            break;
        current_node = current_node->next;
    }

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
    while(current_node != NULL) {
        next = current_node->next;
        removeNode(current_node);
        current_node = next;
    }
    (*head) = NULL;
}

void shortsPath_cmd(pnode head) {
    int src_num, dest_num, len=0;
    pnode src, dest, iterator;
    pnode* unvisited = (pnode*)malloc(100 * sizeof(pnode));
    scanf(" %d %d", &src_num, &dest_num);

    // find source and destination nodes, and number of nodes
    iterator = head;
    while(iterator != NULL) {
        iterator->distance = -1;
        if(iterator->node_num == src_num) {
            src = iterator;
            src->distance = 0;
        }
        if(iterator->node_num == dest_num)
            dest = iterator;
        unvisited[len] = iterator;
        len++;
        iterator = iterator->next;
    }
    unvisited = (pnode*)realloc(unvisited, len * sizeof(pnode));

    // find shortest path;
    pnode min, current_node;
    int min_dis, isVisited;
    pedge current_edge;
    current_node = src;
    while(1) {
        current_edge = current_node->edges;

        while(current_edge != NULL) {
            iterator = current_edge->endpoint;

            // if node already visited continue
            isVisited = 1;
            for(int i=0;i<len;i++)
                if(unvisited[i] == iterator) {
                    isVisited = 0;
                    break;
                }
            
            if(isVisited == 0) {
                // relax function basically
                if(iterator->distance == -1) // minus 1 is infinity
                    iterator->distance = (current_node->distance + current_edge->weight);
                else if(iterator->distance > (current_node->distance + current_edge->weight))
                    iterator->distance = (current_node->distance + current_edge->weight);
            }

            current_edge = current_edge->next;
        }

        // if last node then end
        if(len == 1)
            break;

        // remove current node from unvisited
        int index;
        for(int i=0;i<len;i++)
            if(unvisited[i] == current_node) {
                index = i;
                break;
            }
        for(int i=index;i<len-1;i++)
            unvisited[i] = unvisited[i+1];
        unvisited = (pnode*)realloc(unvisited, (--len)*sizeof(pnode));

        // find next node
        min_dis = 99999999;
        for(int i=0;i<len;i++)
            if(unvisited[i]->distance < min_dis) {
                min_dis = unvisited[i]->distance;
                min = unvisited[i];
            }
        current_node = min;
    }

    printf("Dijsktra shortest path: %d \n", dest->distance);
}

void shortsPath(pnode head, int src_num, int dest_num) {
    int len=0;
    pnode src, dest, iterator;
    pnode* unvisited = (pnode*)malloc(100 * sizeof(pnode));

    // find source and destination nodes, and number of nodes
    iterator = head;
    while(iterator != NULL) {
        iterator->distance = -1;
        if(iterator->node_num == src_num) {
            src = iterator;
            src->distance = 0;
        }
        if(iterator->node_num == dest_num)
            dest = iterator;
        unvisited[len] = iterator;
        len++;
        iterator = iterator->next;
    }
    unvisited = (pnode*)realloc(unvisited, len * sizeof(pnode));

    // find shortest path;
    pnode min, current_node;
    int min_dis, isVisited;
    pedge current_edge;
    current_node = src;
    while(1) {
        current_edge = current_node->edges;

        while(current_edge != NULL) {
            iterator = current_edge->endpoint;

            // if node already visited continue
            isVisited = 1;
            for(int i=0;i<len;i++)
                if(unvisited[i] == iterator) {
                    isVisited = 0;
                    break;
                }
            
            if(isVisited == 0) {
                // relax function basically
                if(iterator->distance == -1) // minus 1 is infinity
                    iterator->distance = (current_node->distance + current_edge->weight);
                else if(iterator->distance > (current_node->distance + current_edge->weight))
                    iterator->distance = (current_node->distance + current_edge->weight);
            }

            current_edge = current_edge->next;
        }

        // if last node then end
        if(len == 1)
            break;

        // remove current node from unvisited
        int index;
        for(int i=0;i<len;i++)
            if(unvisited[i] == current_node) {
                index = i;
                break;
            }
        for(int i=index;i<len-1;i++)
            unvisited[i] = unvisited[i+1];
        unvisited = (pnode*)realloc(unvisited, (--len)*sizeof(pnode));

        // find next node
        min_dis = 99999999;
        for(int i=0;i<len;i++)
            if(unvisited[i]->distance < min_dis) {
                min_dis = unvisited[i]->distance;
                min = unvisited[i];
            }
        if(min_dis == -1)
            return;
        current_node = min;
    }
}

void TSP_cmd(pnode head) {
    int k;
    scanf(" %d", &k);
    pnode nodes[k];
    pnode current_node;
    int node_num;

    // get nodes
    for(int i=0;i<k;i++) {
        scanf(" %d", &node_num);
        current_node = head;
        while(current_node->node_num != node_num)
            current_node = current_node->next;
        nodes[i] = current_node;
    }
    
    int len =0;
    current_node = head;
    while(current_node != NULL) {
        len++;
        current_node = current_node->next;
    }

    current_node = head;
    int isIn;
    int index=0;
    pnode leftover[len-k];
    while(current_node != NULL) {
        isIn = 0;
        for(int i=0;(i<k) && (isIn == 0);i++)
            if(nodes[i]->node_num == current_node->node_num)
                isIn = 1;
        if(isIn == 0)
            leftover[index++] = current_node;
        current_node = current_node->next;
    }

    // printf("NODES:\n");
    // for(int i=0;i<k;i++)
    //     printf("%d ", nodes[i]->node_num);
    // printf("\n");

    // printf("LEFTOVERS:\n");
    // for(int i=0;i<len-k;i++)
    //     printf("%d ", leftover[i]->node_num);
    // printf("\n");
    
    int min = 99999;
    int* pmin = &min;
    int count;
    int indexes[len-k];
    for(int i=0;i<len-k;i++)
        indexes[i] = 0;

    while(indexes[len-k-1] != 2) {
        count=0;
        for(int j=0;j<len-k;j++)
            if(indexes[j] == 1)
                count++;

        pnode arr[k+count];
        for(int j=0;j<k;j++)
            arr[j] = nodes[j];
        index=0;
        for(int j=0;j<len-k;j++) {
            if(indexes[j] == 1) {
                arr[k+index] = leftover[j];
                index++;
            }
        }

        // for(int i=0;i<k+count;i++)
        //     printf("%d ", arr[i]->node_num);
        // printf("PERMA\n");
        permutation(head, pmin, arr, 0, k+count-1);

        indexes[0]++;
        for(int j=0;j<len-k-1;j++)
            if(indexes[j] == 2) {
                indexes[j] = 0;
                indexes[j+1] += 1;
            }
    }
    if((*pmin) == 99999)
        printf("TSP shortest path: -1 \n");
    else    
        printf("TSP shortest path: %d \n", (*pmin));
}

void swap(pnode* a, pnode* b) {
    pnode temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void permutation(pnode head, int* min,pnode* arr, int start, int end) {
    if(start==end) {
        int sum = 0;
        for(int j=0;j<end;j++) {
            shortsPath(head ,arr[j]->node_num, arr[j+1]->node_num);
            if(arr[j+1]->distance == -1)
                return;
            sum += arr[j+1]->distance;
        }
        // for(int j=0;j<end;j++)
        //     printf("%d ", arr[j]->node_num);
        // printf("%d | sum:%d", arr[end]->node_num, sum);
        if(sum < (*min))
            (*min) = sum;
        // printf("\n");
        return;
    }

    for(int i=start;i<=end;i++) {
        swap((arr+i), (arr+start));
        permutation(head, min, arr, start+1, end);
        swap((arr+i), (arr+start));
    }
}
