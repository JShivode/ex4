#include <stdlib.h>
#include "graph.h"

int dest_node_num, path_size;
pnode *path, *res_path ;
int p[100], idx, total_weight;
//int brute(pnode e, pnode n);
int bruteCycles;


//////////////////////////



/* Arrange the N elements of ARRAY in random order.
   Only effective if N is much smaller than RAND_MAX;
   if this may not be the case, use a better random
   number generator. */
void shuffle(int *array, size_t n)
{
    if (n > 1) 
    {
        size_t i;
        for (i = 0; i < n - 1; i++) 
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);          
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}

void tsp(char *data, size_t size){
  int min = 10000, sum=0;
  int arr[size];
  for(int i=0;i<size;i++){
      arr[i] = data[i]-'0';
  }

  for(int i=0 ; i<10; i++){
     /////////////////////////////
     for(int j=0; j<size-1; j++){
      int res = brute(get_node_by_id(arr[j]), get_node_by_id(arr[j+1]));
      if(res > -1) 
         sum +=  res;   // we are calling s(int a, int b). 
      else{
      sum = 10000;
      break; 
     }      
     }
     
    if(sum != -1 && sum<min)
       min = sum;
    
    sum = 0; 
     ////////////////////////////
      shuffle(arr, size);
  }
    if(min<10000)
      printf("TSP shortest path: %d\n", min);
    else 
      printf("TSP shortest path: %d\n", -1);
}

void deColorGraph(){
  pnode it = nodes;
  while(it != NULL){
    it->color = 0;
    it = it->next;
  }
}

void weighGraph(){
  pnode it = nodes;
  while(it != NULL){
    it->node_weight = 10000;
    it = it->next;
  }
}

int brute(pnode src, pnode dst){
   int visited = 0, all = numOfNodes;
   deColorGraph();
   weighGraph();
   src->node_weight = 0;
   ///////// main loop //////////////////////////////
   while(visited < all){
   pedge edItr = src->edges;
   int min = 10000;
   if(dst->color == 1) break;

   while (edItr != NULL) // 
   {
     if(edItr->endpoint->color == 0){
     if(edItr->weight+src->node_weight < edItr->endpoint->node_weight)
              edItr->endpoint->node_weight = edItr->weight+src->node_weight;
     if(edItr->endpoint->node_weight < min)
               min = edItr->endpoint->node_weight;
     }
     edItr = edItr->next;
   }
   edItr = src->edges;
   src->color = 1;
   //printf("colored node# %d it's weight is %d\n", src->node_num, src->node_weight);
   visited++;
   while (edItr != NULL)
   {
     if(edItr->endpoint->node_weight == min)
        {
          src = edItr->endpoint;
          min = 10000;
        }
      edItr = edItr -> next;
   }
   }// while visisted..
    


  return dst->node_weight; 
}

int s(int a, int b,int silent){
  
  get_node_by_id(a)->node_weight = 0;
  int result = brute(get_node_by_id(a), get_node_by_id(b));
  if (result == 10000)
     result = -1;
    printf("Dijsktra shortest path: %d\n", result);   //we need this function to run silently..no prints!!   
  return 0;
  }
  





/*

int s(int a, int b,int silent){
  bruteCycles = 0;
  minTSP = 10000;
  tmpWeight = 0;
  int tmp = brute(get_node_by_id(a)->edges, get_node_by_id(b));
  if(tmp < minTSP)
     minTSP = tmp;
  //int m = brute(get_node_by_id(a)->edges, get_node_by_id(b));
  //m=+0;
  if(minTSP<10000){
    if(silent == 0)
    printf("Dijsktra shortest path: %d\n", minTSP);   //we need this function to run silently..no prints!!
    return minTSP; //printf("shortest path=%d\n", minTSP);
    }
  else
  {
    if(silent == 0)
   printf("Dijsktra shortest path: -1\n");
   return -1;///printf("shortest path=%d\n", -1);
  }
}

int brute(pedge e, pnode n){
  bruteCycles++; 
  if(e == NULL) return 100001;
  if(bruteCycles>20)
     return -1;
    if(e->endpoint != NULL)
    //printf("\nedge->weight %d endpoint->node#%d \n",e->weight, e->endpoint->node_num);
  if(e->endpoint->node_num == n->node_num)      
    {      
        tmpWeight += e->weight;
        if(tmpWeight<minTSP)  
        minTSP = tmpWeight ;
        //printf("tmpWeight=%d\n",tmpWeight);
        tmpWeight = 0;
        return e->weight;                
    } 
   if(e->endpoint == NULL){       
       return 100001;
   }
   if(e->next != NULL)                                    
      brute(e->next, n);
    
    tmpWeight += e->weight;
   return e->weight+brute(e->endpoint->edges,n);   
}


*/