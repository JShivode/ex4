
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
    if(newNode->edges == NULL)
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
 // printf("deleteNode() triggerred nod_num=%d!\n",node_num);
  if(get_node_by_id(node_num) == NULL)
  {
  //  printf("node to delete not found! #%d\n", node_num);
    return ;
  }
  //handle incoming edges. (wipe them)
  pnode delNode = get_node_by_id(node_num);
  pnode nodes_list = nodes;
 // printf("first while loop entery..\n");
  while(nodes_list != NULL){
   // printf("current nodes_list #%d\n", nodes_list->node_num);
    //nodes_list = nodes;
    //no need to handle edges on the node to be deleted, it's edges will simply be all deleted.
    if(nodes_list->node_num == delNode->node_num)
     {       
      // printf("bypassed delNode edge handling..!\n");
       nodes_list = nodes_list->next;  //bypass deleted node, for now.     
       continue;
     }
    
    pedge edg1 = nodes_list->edges; //if no edges on node, continue to next node.
    if(edg1 == NULL)
       {
       //  printf("next node to check\n");
         nodes_list = nodes_list->next;
         continue;
       }
     
    if(edg1->endpoint->node_num == delNode->node_num)
      {// if first edge on node needs to be deleted.
      //   printf("found delNode edge to be first edge!\n");
         nodes_list->edges = edg1->next; // delete it.
         free(edg1);                     // free memory
         nodes_list = nodes_list->next;  
         continue;                       //goto next node.
      }
    pedge head = edg1;
    edg1 = edg1->next;
    //printf("second while loop entry...\n");
    while(edg1 != NULL && edg1->endpoint->node_num != delNode->node_num)
    { 
       //printf("skipping through edges\n");
       head = edg1;            //forward pointers until edge to be deleted is found. 
       edg1 = edg1->next;           
    } // edges while loop..
    if(edg1 != NULL)
    {
     // printf("edg1 nailed..\n");
      head->next = edg1->next;  //delete edge.
      free(edg1);
      
    }
   // printf("nodes_list forwarded, was #%d!!\n", nodes_list->node_num);
    nodes_list = nodes_list->next;  //goto next node.
    
  }
  //now wipe node
  nodes_list = nodes;
  pnode prvNode = nodes;
  if(nodes_list->node_num == node_num) // if first node is the one to be deleted.
     {
       //printf("deleting first node!!\n");
       nodes = nodes->next;
       free(prvNode);
       return;
     }
  nodes_list=nodes->next;
  prvNode = nodes_list;
  while(nodes_list!=NULL && nodes_list->node_num!=node_num){ //advance until node to be deleted is found.
      {
       // printf("skipping through nodes..\n");
       prvNode = nodes_list; 
       nodes_list=nodes_list->next;   
      }
    if(nodes_list != NULL){
     // printf("and nailed node\n");
      prvNode->next = nodes_list->next;
      free(nodes_list);
      return;
    }
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
