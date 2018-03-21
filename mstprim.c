/*
MINIMUM SPANNING TREE IMPLEMENTATION USING PRIM'S ALGORITHM
*/


#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<stdint.h>
#include<limits.h>

struct vertex{             //structure of a vertex
   int vertexValue;
   int weight;
   struct vertex *next;
};

struct edge{            //structure of an edge
   int vertex1;
   int vertex2;
   int edgeweight;
};
   

int n;                     //number of vertices
struct vertex *set;        //array of vertices
struct vertex* *tailset;   //array of tails of linked list
struct edge *heap;         //heap array
int verticesInA;           //A is the intermediate spanning graph    
int heapLength;

void insert(int pos, int num, int numWeight){            //for inserting the vertices, in a lined list, adjacent to a vertex 
   struct vertex *new = (struct vertex *)malloc(sizeof(struct vertex));
   new->vertexValue = num;
   new->weight = numWeight;
   new->next = NULL;
   tailset[pos]->next = new;
   tailset[pos] = new;    
   return ;
}

void swap(struct edge *edge1, struct edge *edge2){       //swap function
   struct edge temp;
   temp  = *edge1;
   *edge1 = *edge2;
   *edge2 = temp;
   return;
}

void heapify(int i) {         //makes the subtree from "i" into heap
   int l = 2*i+1;
   int r = 2*i+2;
   int smallest;
   if(l<heapLength && heap[i].edgeweight > heap[l].edgeweight)
      smallest = l;
   else 
      smallest = i;
   if(r<heapLength && heap[smallest].edgeweight > heap[r].edgeweight ) 
      smallest = r;
   if(smallest != i){         //getting the smallest element to carry up the heap
      swap(&heap[i], &heap[smallest]);
      heapify(smallest);      //checking subtree of the given subtree
   }
   return ;
}

void buildQ(int *Array) {
   int j,k = 0, temp, flag=0;
   heapLength = n - verticesInA;
   heap = (struct edge *)malloc(sizeof(struct edge) * heapLength);      //heap is of data type "edge"
   for(j=0; j<n; j++) {                          
      if(Array[j] != 1){
         heap[k].vertex2 = j+1;                 //intialising heap with vertices not present in A
         heap[k].edgeweight = 2147483647;       //and their edge length to infinity
         k++;
      }
   }   
   
   for(j=0; j<n; j++) {
      if(Array[j] == 1){
         struct vertex *ptr = set[j].next;
         while(ptr != NULL){                       //getting the bridge lengths for each vertex by traversing through the input linked list
            if(Array[ptr->vertexValue - 1] != 1) {
               for(temp=0; temp<k; temp++) {
                  if(heap[temp].vertex2 == ptr->vertexValue){
                     flag = 1;
                     if(heap[temp].edgeweight > ptr->weight){     
                        heap[temp].edgeweight = ptr->weight;
                        heap[temp].vertex1 = set[j].vertexValue; 
                     }
                  }
               }
              
            }
            ptr = ptr->next;
         }  
      }
   }
   
   heapify(0);             //making the heap for the least bridge length
   return;
}

struct edge extractMin(int *A) {          //function which returns the edge to put in A
   buildQ(A);                             //building heap   
   struct edge returnvalue = heap[0];     //edge is returhned
   //free(heap);
   return returnvalue;
}

void makeMST() {
   struct edge MST[n-1];            //array of MST
   struct edge returned;
   int *isPresent = (int *)malloc(sizeof(int) * n);
   int k;
   for(k=0; k<n; k++)
      isPresent[k]  = 0;
   int rootVertex = 0;              //choosing a random vertex as 1 to start with
   isPresent[rootVertex] = 1;                //making that vertex present in A
   verticesInA = 1;                          //A is partial MST, after final stage MST is A
   while(verticesInA <= n){
      returned = extractMin(isPresent);      //edge returned by heap
      MST[verticesInA - 1] = returned;       //putting the edge in MST
      isPresent[returned.vertex2 - 1] = 1;   //making the vertex present in MST
      verticesInA++;                         //increasing the number of vertices in (partial) MST
   }

   int i;
   printf("MST\n");
   for(i = 0; i < n-1; i++)                  //printing out mst 
      printf("%d-%d: %d\n", MST[i].vertex1, MST[i].vertex2, MST[i].edgeweight);

   return;
}
 
int main() {
   int i=0, j=1, adjacent, edgeCount = 0, adjacentWeight = 0; 
   printf("MINIMUM SPANNING TREE - PRIM'S ASLGORITHM");
   printf("Enter the number of vertices: ");
   scanf("%d", &n);
   int *degree;  
   set = (struct vertex *)malloc(sizeof(struct vertex) * n);            //allocating memory of vertices set
   tailset = (struct vertex* *)malloc(sizeof(struct vertex*) * n);      //allocating memory tails of vertices linked list      
   degree = (int *)malloc(sizeof(int) * n);                       //an array to hold degree of each vertex, even a temporaray variable will do
   //printf("edges will be considered if second vertex is more than first vertex for the purpose of reducing space. \n");
   
   for(i=0; i<n; i++){                 //intialising the linked list with vertex info
      set[i].next = NULL;
      set[i].vertexValue = i+1;
      set[i].weight = 0;
      tailset[i] = &set[i];
      } 
   i = 0;
   while(i<n) {
      printf("enter the number of vertices connected to vertex %d: ", i+1);      //input of verteices adjacent and their edgelength
      scanf("%d", &degree[i]);
      j = 0 ;
      while(j< degree[i]) {
         printf("enter the vertices connected to vertex %d: ", i+1);
         scanf("%d", &adjacent);
         printf("enter the weight of this edge %d-%d: ", i+1,adjacent);
         scanf("%d", &adjacentWeight);
         insert(i, adjacent, adjacentWeight);
         j++;
         edgeCount++;
         }
      i++;
   }

   makeMST();        //calling function which makes mst by calling other functions
   printf("End of the program\n");
   return 0;
}                    //end of main


