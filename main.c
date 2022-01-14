#include <stdlib.h>
#include "graph.h"
#define MAX_SIZE 300

int main (){
char mat[MAX_SIZE];

for(int i=0;i<MAX_SIZE;i++)
  mat[i] = '\0';


fgets(mat, MAX_SIZE, stdin);
                                    // A 4 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2 n 3 T 3 2 1 3 B 5 0 4 2 1 B 2 1 3 5 1 T 3 2 1 3 D 2 T 2 3 0

int graphInfoSize = 0;
for(int i=0;i<MAX_SIZE;i++)
   {       
       if(mat[i] == '\0' || mat[i] == 'B' || mat[i] == 'D' || mat[i] == 'S' || mat[i] == 'T') break;
       graphInfoSize++;
   }
if(graphInfoSize > 0) graphInfoSize+=1;   // unless array is empty add 2 to graphInfoSize. example: 2, 3, n, '\0' graphInfoSize = 4.

char dt[graphInfoSize];
for(int i=0;i<graphInfoSize;i++)
   dt[i] = mat[i];
dt[graphInfoSize-1] = '\0'; //termination

buildGraph(dt);
/////////////////////////////////////////
int k = graphInfoSize-1;

char tmp[6]; 
while(mat[k]!='\0'){

int kx=0;
///////////////////
if(mat[k] == 'B'){   // B 5 0 4 2 1    we send --> 50421
k++;
for(int j=0;j<10;j++){
if(mat[k+j] == ' ') {continue;}
tmp[kx] = mat[k+j];
kx++;
}
addNode(tmp);  //tmp has no spaces!
k+=10;
}
///////////////////

///////////////////
if(mat[k] == 'D') // working..V
  {
    //printNodes();
    //printf("dleting %d\n", mat[k+2]-'0');
    deleteNode(mat[k+2]-'0');k++;
    //printf("deleted\n");
    //printNodes();
    }
/////////////////////////
if(mat[k] == 'S') //check
{    //printf("s(%d, %d)\n", mat[k+2]-'0', mat[k+4]-'0');
    s(mat[k+2]-'0', mat[k+4]-'0', 0);
    k+=2;
}
/////////////////////
if(mat[k] == 'T')
{
   // printf("got a T request\n");
    int n = mat[k+2]-'0';
    k+=2;
    char tt[n];
    k+=2;
    
    for(int y=0;y<n;y++)
    {
      tt[y] = mat[k];
      k+=2;      
    } 
    tt[n] = '\0'  ;
    //printf("trying tsp(%s)\n", tt);
    tsp(tt, n);
    k--;
}

k++;
}
/////////////////

//printNodes();


//freeEdges();
/*
pnode del = nodes;
while(nodes!=NULL){
    nodes=nodes->next;
    free(del);
    del = nodes;
}
*/
return 0;
}
