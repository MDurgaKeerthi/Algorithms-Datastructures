/*
SKIP LIST
maxlevels depend on log(base 1/p) n,  p is 1/2 or 1/4. so maxlevels can be around 6
and number of maxlevels can be adjusted according to implementation
Theoritically these levels can be infinite but for implementation purpose they can be limited
*/

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

#define maxlevels 6     

struct slnode {            //structure of a node skiplist
   int value;
   struct slnode *next;
   struct slnode *down;
   };
      
struct slnode *skiplist[maxlevels];    //heads of all linked list
int count[maxlevels];                  //count of number of values in each linked list
int nodepos;
int prevpromoted = 0;                  //needed as global as excess from different functions

struct slnode* insert(int level, int input){       //function which inserts the given value in the given level
   struct slnode *new = (struct slnode *)malloc(sizeof(struct slnode));
   new->value = input;
   new->next = NULL;
   new->down = NULL;
   
   if(skiplist[level] == NULL){           //if no previous elements in list at level-0
      skiplist[level] = new;
      count[level]++;
      return new;
      }
      
   nodepos = 0;
   int y = maxlevels-1;
   struct slnode *ptr = skiplist[y];         //traversing from top list
   struct slnode *prev = NULL;
   while(y>=level){
      while(ptr != NULL && (input > ptr->value)){     //comparing with ptr values for next direction
         prev = ptr;
         ptr = ptr->next;
         nodepos++;
         }
      if(y==level)                     //if traversed through given base level
         break;   
      y--;
      if(prev == NULL)                 //going down to below level head, if value to  input < ptr value
         ptr = skiplist[y];
      else{
         prev = prev->down;            //going down though down pointer
         ptr = prev->next;
         }
      }   
   if(prev == NULL){                //inserting in the front of given level
      new->next = ptr;
      skiplist[level] = new;  
      count[level]++; 
      }
   else{
      new->next = prev->next;       //otherwise inserting in the obtained position
      prev->next = new;
      count[level]++;
      }   

   return new;
}   

void promote(struct slnode *prom){        //function which promotes the recently inserted value
   int j=0, willgo;
   time_t t;
   srand((unsigned) time(&t));            //for generating random numbers
   struct slnode *ptr = prom;
   struct slnode *q = NULL;
   while(count[j] > 1 && j <= (maxlevels-2)){  //if the level has more than one node 
      if(nodepos %2 == 1){                      //if 1 go to next level
         willgo = rand() % 2;
         if(willgo==1 ){
            //printf("%d---", j);
            q = insert(j+1, ptr->value);        //promoting in the next level
            q->down = ptr;                      //putting the down link
            }
         else
            break;   
         }   
      else if(nodepos%2 == 0 && prevpromoted == 0){ //if not previously promoted and even node
         q = insert(j+1, ptr->value);           //promoting to next level
         q->down = ptr;
         //printf("%d is promo",ptr->value);
         }
      if(q == NULL)           //coming out of loop if once not promoted
         break;
      ptr = q;
      j++;
   } 
   if( q!= NULL)
      prevpromoted = 1;       //setting the value of prevpromoted
   else
      prevpromoted = 0;              
return;  
}

void sldelete(){              //skip list delete
   int input;
   printf("Enter the value to be deleted: ");
   scanf("%d", &input);  
   int deleted = 0;
   int y = maxlevels-1;
   struct slnode *ptr = skiplist[y];
   struct slnode *prev = NULL;
   while(y>=0){                  //checking from top level
      while(ptr != NULL && (input > ptr->value)){
         prev = ptr;
         ptr = ptr->next;      //finding the ptr to delete
         }
      if(ptr!=NULL && input == ptr->value){
         if(prev != NULL)
            prev->next = ptr->next;    //changing the links
         else
            skiplist[y] = ptr->next;  
         deleted = 1;   
         }
      if(y==0)                //stop if reached base level
         break;   
      y--;
      if(prev == NULL)           //changing ptr to traverse through the next levels
         ptr = skiplist[y];
      else{
         prev = prev->down;
         ptr = prev;
         }
      } 
   if(deleted == 0)
      printf("Does not exist to delete\n");
   
   return;
}    

void slsearch(){              //skip list search
   int input;
   printf("Enter the value to be searched: ");
   scanf("%d", &input);   
   
   int y = maxlevels-1;
   struct slnode *ptr = skiplist[y];
   struct slnode *prev = NULL;
   while(y>=0){                   //checking from top level
      while(ptr != NULL && (input > ptr->value)){
         prev = ptr;
         ptr = ptr->next;        //finding the ptr which may contain the value we are searching for
         }
      if(ptr!=NULL && input == ptr->value){
         printf("found\n");
         return;
         }
      if(y==0)                   //stop if reached base level
         break;   
      y--;
      if(prev == NULL)
         ptr = skiplist[y];      //changing ptr to traverse through the next levels
      else{
         prev = prev->down;
         ptr = prev;
         }
      } 

   printf("Not found\n");
   return;
}

void print(){                       //normal linked list print in loop
   int i,flag = 0;
   struct slnode *ptr = NULL;
   for(i=0; i<maxlevels; i++){      //traversing through all levels
      ptr = skiplist[i];
      while(ptr != NULL){           //travering through the list
         printf("%d  ", ptr->value);
         flag = 1;
         ptr = ptr->next;
         }
      printf("\n");   
      }
   if(flag == 0){
      printf("No elements\n");
      return;
      }   
   return;
}         

int main() {            //start of main
   int entry;
   printf("Skip List. Enter 1 to Insert, 2 to Delete, 3 to Search and 4 to print: ");
	scanf("%d",&entry);
	while(entry>=1 && entry<=4) {
		switch(entry) {
			case 1: {
			   int input;
            printf("Enter the value to be inserted: ");
            scanf("%d", &input);
				struct slnode *ptr = insert(0, input);    //first insert in first level and then promote
				promote(ptr);
				break;
				}
			case 2: {
				sldelete();             //calling delete
				break;
				}
			case 3: {
			   slsearch();             //calling search
			   break;
			   }	
			case 4: {
				print();                //calling print
				break;
				}
		}  
		printf("Enter 1 to Insert, 2 to Delete, 3 to Search and 4 to print: ");
		scanf("%d",&entry);
	}

   return 0;
}                                   //end of main


