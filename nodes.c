
#include <stdlib.h>
#include "graph.h"
//This function will add a node to the graph and returns 1 
//if node exists in graph return 0.


int addNode (char *ndstr){  //ndstr is the string without B.
  //extract node number from string
  char *str = ndstr;
  int node_num = *str - '0';
  int res = 0;
  str++;
  pnode newNode;
  //if node is not already in graph  first add it.
  if(get_node_by_id(node_num) == NULL){
    //we will just add it to the head of the list, it's easier.    
    newNode = malloc(sizeof(struct GRAPH_NODE_));
    if(newNode == NULL)
       perror("Memory fault: ");
    newNode->next = nodes;
    nodes = newNode;
    }// if node is not already in graph! end
    else{    
    newNode = get_node_by_id(node_num);
    res = 1;
    }
    newNode->node_num = node_num;
    pedge edgPointer;
    newNode->edges = malloc(sizeof(struct edge_));
    if(newNode == NULL)
      perror("Memory fault: ");
    edgPointer = newNode->edges;
    pedge prv = edgPointer;
    while(*str != '\0' && *str != '\n' && *str != '\r')
    {                            
       edgPointer->endpoint = get_node_by_id((int)(*str -'0'));
       str++;     
       edgPointer->weight = (int)(*str - '0');  
       edgPointer->next = malloc(sizeof(struct edge_));
       if(edgPointer->next == NULL)
          perror("Memory fault: ");
       prv = edgPointer;
       edgPointer = edgPointer->next;  
       str++;     
    }  
     prv->next = NULL; 
  return res;
}
//end of addNode().

void deleteNode(int node_num){
  //if node doesn't exist..return.
  if(get_node_by_id(node_num) == NULL)
    return ;

  //handle incoming edges. (wipe them)
  pnode delNode = get_node_by_id(node_num);
  pnode nodes_list = nodes;
  //printf("deleting node #%d\n", delNode->node_num);
  //printf("delNode=%d nodes=%d\n", delNode->node_num, nodes_list->node_num);
  while(nodes_list != NULL){

    //no need to handle edges on the node to be deleted./'

    if(nodes_list->node_num != delNode->node_num)
     {       
       nodes_list = nodes_list->next;       
       continue;
     }
    pedge edg = nodes_list->edges;
    pedge edg_prv = nodes_list->edges;
    if(nodes_list->edges->endpoint == delNode)  //handle first node
       nodes_list->edges = nodes_list->edges->next;
    edg = edg->next;
    while(edg != NULL){
      if(edg->endpoint == delNode)
         edg_prv->next = edg->next;
      edg = edg->next;
      edg_prv = edg_prv->next;
    }
    nodes_list = nodes_list->next;
  }

  //now wipe node
  nodes_list = nodes;
  pnode prvNode = nodes;
  if(nodes_list->node_num == node_num) // if first node is the one to be deleted.
     {
       nodes = nodes->next;
       free((void *)prvNode);
       return;
     }
  nodes_list=nodes_list->next;
  while(nodes_list!=NULL){
    if(nodes_list->node_num == node_num)
      {
        free((void *) prvNode->next);        
        prvNode->next = nodes_list->next;       
      }
    prvNode = prvNode->next;
    nodes_list = nodes_list->next;
  }
  return;
}

void printNodes(){
pnode it = nodes;
while(it != NULL){
printf("node[%d] ->",it->node_num);
printEdges(it->edges);
it=it->next;
}
free(it);
}



pnode get_node_by_id(int id){
  pnode itr = nodes;
  while(itr!=NULL){
    if(itr->node_num == id)
        return itr;
    itr = itr->next;
  }
  free(itr);
  return NULL;
}
