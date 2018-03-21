/*
MINIMUM SPANNING TREE - KRUSKAL'S ALGORITHM
algorithm:
1.input of vertices connected to a vertex
2.making the edges array
3.sorting the edges array
4.taking the edge and forming a connected spanning graph
5.checking before considering an edge if the vertices are already connected
*/


#include<stdio.h>
#include<malloc.h>

struct vertex{             //structure of a vertex
   int vertexValue;
   int weight;
   struct vertex *next;
};

struct edge{       //strcuture of edge
   int vertex1;
   int vertex2;
   int edgeweight;
};
   

int n;
struct vertex *set;     //array of linked list heads
struct vertex* *tailset;  //array of linked list tails
void makeMST(struct edge array[], int edges);

void insert(int pos, int num, int numWeight){     //inserts the vertices adjacent to each vertex
   struct vertex *new = (struct vertex *)malloc(sizeof(struct vertex));
   new->vertexValue = num;
   new->weight = numWeight;
   new->next = NULL;
   tailset[pos]->next = new;              //maintaining linked list
   tailset[pos] = new;    
   return ;
}

void merge(struct edge *b, int l, int m, int h) {     //merge function of merge sort
   struct edge c[h-l+1];
   int j,i,k=0;

   for(i=l,j=m+1;(i<=m) && (j<=h);) {  
	   if(b[i].edgeweight < b[j].edgeweight){        //getting lower weights first into array
	       c[k] = b[i];      
	       i++;
	       k++; 
		   }
	   else{
	       c[k] = b[j];
	       j++;
	       k++;
		   }
       }
   while(i<=m) {                
	   c[k] = b[i];         //and then all reamining elements into array
	   k++;
	   i++;
	   }    
   while(j<=h) {                 
	   c[k] = b[j];
	   k++;
	   j++;
	   }
   for(i=0;i<k;i++)        //copying back the weights       
      b[l+i]=c[i];
      
   return;
}


void mergesort(struct edge *a, int low, int high){       //normal merge sort function
   if(low<high){
      int mid=(low+high)/2;
      mergesort(a,low,mid);         //sorting left half
      mergesort(a,mid+1,high);      //sorting right half
      merge(a,low,mid,high);       //merging both halves
	   }
   return;   
}

void makeEdgesArray(int edges) {             //making edges array from the input
   int a = 0, edge = 0;
   struct edge edgesArray[edges];
   struct vertex *ptr = NULL;
   for(a=0; a<n; a++){ 
      ptr = set[a].next;         //traversing through the array of linked lists (vertices)
      while(ptr != NULL) {
         if(set[a].vertexValue < ptr->vertexValue){
            edgesArray[edge].vertex1 = set[a].vertexValue;
            edgesArray[edge].vertex2 = ptr->vertexValue;
            edgesArray[edge].edgeweight = ptr->weight;
            edge++;
         }
         ptr = ptr->next;            
      }
   }
   
   mergesort(edgesArray,0, edge);            //calling merge sort to sort the edges
   //for(edge = 0; edge<edges; edge++)
   //   printf("%d-%d: %d\n", edgesArray[edge].vertex1, edgesArray[edge].vertex2, edgesArray[edge].edgeweight);
   makeMST(edgesArray, edge);
   return;
}


int *leader, *height;

int getroot(int k){           //function to find leader of a vertex
   if(leader[k-1] == k)
      return k;
   getroot(leader[k-1]);
}

void makeMST(struct edge array[], int edges){
   int i, j=0,l;
   leader = (int *)malloc(sizeof(int) * n);
   height = (int *)malloc(sizeof(int) * n);
   struct edge MST[n-1];
   for(i=0; i<n; i++){ 
      leader[i] = i+1;
      height[i] = 0;
      }
   for(i=0; i<edges; i++){
      int root1 = getroot(array[i].vertex1);
      int root2 = getroot(array[i].vertex2);
      if(root1 != root2){           //if they are not already connected
         if(height[root1-1] < height[root2-1]){    //tree of less height points to tree of more height
            leader[root1 - 1] = root2;
            height[root2-1]++;
            }
         else{
            leader[root2 - 1] = root1;
            height[root1-1]++;
            }         
         MST[j].vertex1 = array[i].vertex1;        //putting the edge in the mst array
         MST[j].vertex2 = array[i].vertex2;
         MST[j].edgeweight = array[i].edgeweight;
         j++;         
      }
      
   } 

   for(i = 0; i<j; i++)                //printing the mst array
      printf("%d-%d: %d\n", MST[i].vertex1, MST[i].vertex2, MST[i].edgeweight);

   return;
}

int main() {
   int i=0, degree, j=1, adjacent, edgeCount = 0, adjacentWeight = 0; 
   printf("MINIMUM SPANNING TREE - KRUSKAL'S ALGORITHM");
   printf("Enter the number of vertices: ");
   scanf("%d", &n);
   set = (struct vertex *)malloc(sizeof(struct vertex) * n);         //array of vertices
   tailset = (struct vertex* *)malloc(sizeof(struct vertex*) * n);      //array of tails
   printf("edges will be considered if second vertex is more than first vertex for the purpose of reducing space. \n");

   for(i=0; i<n; i++){
      set[i].next = NULL;
      set[i].vertexValue = i+1;
      set[i].weight = 0;
      tailset[i] = &set[i];
      } 
   i = 0;
   while(i<n) {
      printf("enter the number of vertices connected to vertex %d: ", i+1); //enter the edges only once
      scanf("%d", &degree);
      j = 0 ;
      while(j<degree) {                   //taking the input
         printf("enter the vertices connected to vertex %d: ", i+1);
         scanf("%d", &adjacent);
         printf("enter the weight of this edge %d-%d: ", i+1,adjacent);
         scanf("%d", &adjacentWeight);
         insert(i, adjacent, adjacentWeight);
         edgeCount++;
         j++;
         }
      i++;
   }

   makeEdgesArray(edgeCount);    //making the array of edges
   
   printf("End of the program\n");
   return 0;
}
   //end of the program
