/*
Heap Sort
*/

#include<stdio.h>
#include<malloc.h>

int *heap;              //heap array
int elements = 0;

void swap(int *element1, int *element2){     //swap function
   int temp;
   temp  = *element1;
   *element1 = *element2;
   *element2 = temp;
   return;
}

void heapify(int i) {      //coverts the subtree into min heap basing on the value of i
   int l = 2*i+1;
   int r = 2*i+2;
   int smallest;
   if(l<elements && heap[i] > heap[l])
      smallest = l;           //getting the smallest element
   else 
      smallest = i;
   if(r<elements && heap[smallest] > heap[r] ) 
      smallest = r;
   if(smallest != i){
      swap(&heap[i], &heap[smallest]);
      heapify(smallest);      //going down the subtree and heapifying
   }
   return ;
}

void buildHeap(){
   int i = (elements-1) / 2 ;
   for(; i >= 0; i--)
      heapify(i);       //building the heap by heapifying from base 
   return;
}

void heapsort() {
   buildHeap();            //making heap
   int i = elements-1;
   printf("The sorted numbers: ");
   for(; i>=0; i--){                //printing out the elements by extracting them
      printf("%4d",heap[0]);
      heap[0] = heap[elements-1];
      elements--;
      heapify(0);             //heapifying again
   }
   return;
}

int main() {
   printf("HEAPSORT\n");
   printf("Number of elements to be sorted: ");       
   scanf("%d", &elements);
   heap = (int*)malloc(sizeof(int) * elements);
   printf("Enter the numbers: ");
   int i = 0;
   while(i < elements){             //input of array
      scanf("%d", &heap[i]);
      i++;      
   }
   
   heapsort();                   //calling heapsort to sort the elements   
   printf("\nEnd of the porgram\n");
   return 0;
}         


