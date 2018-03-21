//hashing. resolving collisions using overflow area


#include<stdio.h>

#define size 13

struct slot{
   int value;
   int empty;
   struct slot *next;
   };
   
struct slot ht[size];
struct slot ofarea[size];
struct slot* tail[size]; 

void insert(){
   int input,flag = 0;
   printf("Enter the value to be hashed: ");
   scanf("%d", &input);
   int position = input % size;
   
   if(ht[position].empty == 0){
   
      ht[position].value = input;
      ht[position].empty = 1;
      tail[position] = &(ht[position]);
      }
   else{
      int i;
      for(i=0; i<size; i++){
         if(ofarea[i].empty == 0){
            ofarea[i].empty = 1;
            ofarea[i].value = input;
            tail[position]->next = (&ofarea[i]);
            tail[position] = &(ofarea[i]);
            flag = 1;
            return;
            } 
         } 
      }
                   
   if(flag != 0)
      printf("Overflow area is full, can't insert.\n");
   
   return;
}   

void search(){
   int input,i;
   printf("Enter the value to be searched: ");
   scanf("%d", &input);

   i = input % size;
   struct slot *ptr;
      ptr = &(ht[i]);
      while(ptr != NULL){
         if(ptr->empty == 1 && input == ptr->value){ 
            printf("found\n");
            return;
            }
         ptr = ptr->next;
         }
   printf("does not exist\n");      
   return;
} 

void delete(){
   int input,position,flag = 0;
   printf("Enter the value to be deleted: ");
   scanf("%d", &input);

   position = input % size;
   struct slot *ptr, *prev;
   ptr = &(ht[position]);
   while(ptr != NULL){
      if(ptr->empty == 1 && input == ptr->value){
         flag = 1;
         break;
         }
      prev = ptr;   
      ptr = ptr->next;
      }
         
   if(flag ==1) {   
      if(prev != NULL){
         ptr->empty = 0;
         ptr->value = -1;
         prev->next = ptr->next;
         }
      else{
         while(ptr != tail[position]){
            prev = ptr;
            ptr = ptr->next;
            }
         ht[position].value = tail[position]->value;
         tail[position]->empty =0;
         tail[position] = prev;  
         }  
      }
   if(flag==0)      
      printf("does not exist\n");  

   return;
} 

void display(){
   int i;
   struct slot *ptr;
   for(i=0; i< size; i++){
      ptr = &(ht[i]);
      while(ptr != NULL){
         if(ptr->empty == 1) 
            printf("%d   ", ptr->value);
         else
            printf("--- ");   
         ptr = ptr->next;
         }
      printf("\n");
      }    

   return;
} 

void initialise(){
   int i;
   for( i=0; i<size; i++){
      ht[i].empty = 0;
      ht[i].next = NULL;
      ofarea[i].empty = 0;
      ofarea[i].next = NULL;
      }
   return;
}      

int main() {
   int choice;
   initialise();
   printf("1.insert\t2.search\t3.delete\t4.display\nenter choice: ");
   scanf("%d",&choice);
   while(choice>=1 && choice<=4){
      switch(choice) {
      case 1: {
	      insert();
         break;
	      }
      case 2:  {
	      search();
	      break;
	      }
      case 3:  {
	      delete();
	      break;
	      }
      case 4:  {
	      display();
	      break;
	      }
	   }
      printf("1.insert\t2.search\t3.delete\t4.display\nenter choice: ");
      scanf("%d",&choice);
   }
   return;
}

   
   
