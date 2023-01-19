void delete_node_cmd(pnode *head);
void build_graph_cmd(pnode *head);
void insert_node_cmd(pnode *head);
void printGraph_cmd(pnode head); //for self debug
void deleteGraph_cmd(pnode* head);
void shortsPath_cmd(pnode head);
void TSP_cmd(pnode head);
// int TSP(pnode src, pnode unvisited[], int len);
void swap(pnode* a, pnode* b);
void permutation(pnode head, int* min, pnode* arr, int start, int end);
void shortsPath(pnode head, int src_num, int dest_num);