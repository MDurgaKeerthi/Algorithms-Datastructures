/* Hashing using chaining
new elements are inserted after older ones*/

#include<stdio.h>
#include<malloc.h>

#define size 11

struct slot {
   int val;
   struct slot *prev;
   struct slot *next;
   };

struct slot hash[size];
struct slot *tail[size];
int first[size];

void insert() {
	int number,i;
	printf("enter number: ");
	scanf("%d",&number);
	i = number % size;
	   
	if(first[i] == 0){
	   hash[i].val = number;
	   hash[i].prev = NULL;
 	   hash[i].next = NULL;	
	   //head[i] = hash[i] ;
	   first[i] = 1;
	   printf("assigned first\n");
	   }
	else if(first[i] == 1){
	   struct slot *new = (struct slot *)malloc(sizeof(struct slot));
	   hash[i].next = new;
	   new->prev = hash+i;
	   new->next = NULL;
	   new->val = number;
	   tail[i] = new;
	   first[i] = 2;
	   printf("assigned\n");
	   }
	else {
	   struct slot *new = (struct slot *)malloc(sizeof(struct slot));
	   tail[i]->next = new;
	   new->prev = hash+i;
	   new->next = NULL;
	   new->val = number;
	   tail[i] = new;
	   first[i]++;
	   printf("assigned\n");
	}
   return;
}

void search() {
	int number,i;
	printf("enter number: ");
	scanf("%d",&number);
	i = number % size;
	struct slot *new ;
	
	if(hash[i].val == number){
	   printf("found\n");	
	   return;
	   }
	else {
	   new = hash[i].next;
	   while(new!=NULL){
	      if(new->val == number){
	         printf("found\n");
	         return;
	         }
	      new = new->next;
	      } 
	   }
   printf("not found\n");
   return;
}

void delete(){
	int number,i;
	printf("enter number: ");
	scanf("%d",&number);
	i = number % size;
	struct slot *new ;
	if(first[i]!=0){
	   if(hash[i].val == number){
		   if(first[i]==1){
	     		first[i] =0;
	     		hash[i].val = 0;
	     		printf("deleted\n");	
	    		return;
	    		}
		   else if(first[i]==2){
			   hash[i].val = tail[i]->val;
			   hash[i].next = NULL;
			   tail[i] = NULL;
			   first[i] = 1;
			   return;
			   }
		   else{
			   new = hash[i].next;
			   hash[i].val = new->val;
			   hash[i].next = new->next;
			   first[i]--;
			   free(new);
			   return;
			   }
	     }
	   else {
		   if(first[i]==1){
	     	   printf("does not exist\n");	
	    		return;
	    		}
		   else if(first[i]==2){
			   if(tail[i]->val == number){
			       hash[i].next = NULL;
			       tail[i] = NULL;
			       first[i] = 1;
			       printf("deleted\n");
			       free(new);
			       return;
			       }
			   else {
			       printf("does not exist\n");
			       return;
			       }
		      }
		   else {
			   new = hash[i].next;
			   if(new->val == number){
			       hash[i].next = new->next;
			       first[i]--;
			       printf("deleted\n");
			       free(new);
			       return;
			       }
			   else {
                struct slot *temp;
			       new = new->next;
			       while(new!=tail[i]){
			          if(new->val == number){
			             new->next->prev = new->prev;
			             new->prev->next = new ->next;
			             first[i]--;
	             		 printf("deleted\n");
			             free(new);
	            		 return; 
	      		      }
			         temp =new;
	    		      new = new->next;}
			         if(new == tail[i] && new->val == number ) {
				         temp->next = NULL;
				         tail[i] = temp;
				         first[i]--;
				         printf("deleted\n");
				         free(new);
	      		    	return; 
	      		    	}
			         }
		         }
	         }
	      }

   printf("does not exist\n");
   return;
}

void display(){
	int i;
	struct slot *new ;
	for(i=0;i<size;i++){
	   printf("elements at index%d\n",i);
      if(first[i]!=0){
	      printf("%d-->",hash[i].val);
	      new = hash[i].next;
	      while(new!=NULL){
	         printf("%d-->",new->val );
	         new = new->next;
	         } 
	      }
	   printf("no more--\n");
	   }
   return;	   
}

int main() {
  int choice;
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


	
