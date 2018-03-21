/*hashtable implementation using quadratic probing. element 0 can not be inserted

h(k,i) = (h1(k) + c*i+ c1*i**2) mod m
h1(k) = k mod m
*/


#include<stdio.h>
#include<malloc.h>

struct pair{
   int value;
   int empty;     //if empty is 0 slot is empty, if 1 slot is not empty
   }; 

int size = 23;

int position(int key, int counter){
   int h, h1, c = 1, c1 = 3;
   h = key % size;
   h1 = ( h + (c * counter) + (c1 * counter * counter) ) % size;
   return h1;
}   

void insert(struct pair *ptr, int key) {
   int i=0,j,k;
   while(i!=size) {
      k = position(key, i);
     	if(ptr[k].empty == 0) {
	      ptr[k].value = key;
	      ptr[k].empty = 1;
	      printf("element assigned\n");
	      break;
	      }
	   else
	      i++;
	if(i==size-1)
	   printf("can not insert. Hashtable is full\n");
   }
   return;
}

void search(struct pair *ptr, int key) {
   int i=0,k;
   while(i!=size) {
      k = position(key,i);
	   if(ptr[k].empty == 1 && ptr[k].value == key) {
	      printf("element found\n");
	      return;
	      }
	   i++;
   }
   printf("element does not exist\n");
   return;
}

void delete(struct pair *ptr, int key) {
   int i=0,j,k;
   while(i!=size) {
      k = position(key,i);
	   if(ptr[k].empty ==1 && ptr[k].value == key) {
	      ptr[k].empty = 0;
	      printf("element deleted\n");
	      return;
	      }
	   i++;
    }
   printf("element does not exist\n");
   return;
}


void display(struct pair *ht) {
	int i =0;
	for(i=0;i<size;i++){
	   if(ht[i].empty == 1)
	      printf("%d   ", ht[i].value);
	   else
	      printf("---   ");
	   } 
	printf("\n");     
	return;
}


void intialise(struct pair *ptr){
   int i;
   for(i=0; i< size; i++)
      ptr[i].empty = 0;
   return;
}      

int main() {
   int n,choice;
   struct pair *ht = (struct pair *)malloc(size * sizeof(struct pair));
   intialise(ht);
   printf("1.insert\t2.delete\t3.search\t4.display\nenter the choice:");
   scanf("%d",&choice);
   while(choice>=1 && choice<=4) {
      if(choice>=1 && choice<=3){
         printf("enter element: ");
	      scanf("%d",&n);
	      }
      switch(choice)  { 
      case 1: {
	      insert(ht,n);
	      break;
	      }
      case 2: {
	      delete(ht,n);
	      break;
	      }
      case 3: {
	      search(ht,n);
	      break;
	      }
      case 4: {
	      display(ht);
	      break;
	      }
       }
     printf("1.insert\t2.delete\t3.search\t4.display\nenter the choice:");
     scanf("%d",&choice);
   }

   return 0;
}

