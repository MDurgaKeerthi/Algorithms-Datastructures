/*
Assignment-2
name:Durga Keerthi
roll number: cs15btech11024
Single Linked List. Entries with uniqueness on roll number */

#include<stdio.h>
#include<string.h>
#include<malloc.h>

struct student{
    char name[25];
    char rollno[20];
    int age;
    char gender[6];
    struct student *next;
}; 

struct student *first = NULL;
struct student *current = NULL;
int count;

int search(char *data){
    if(first==NULL){
	printf("No entries. ");
	return;
    }
    struct student *ptr = first;
    int value; 
    extern int count;
    count = 0;
    while(ptr!=NULL){
	count++;
        value = strcmp(data,ptr->rollno);
	if(value == 0){
	   printf("Roll number exists\n");
	   return value;
	}
	ptr = ptr->next;
    }
    return value;
}

void getdetails() {
    printf("Name:");
    scanf("%s",current->name);	//input of structure element
    printf("Age:");
    scanf("%d",&current->age);
    printf("Gender:");
    scanf("%s",current->gender); 
    current->next = NULL;
    return;
}

void insertion(char *data){
    int i;
	struct student *new = (struct student*)malloc(sizeof(struct student));
	if(new == NULL){
  	    printf("error\n");
	  }
	else {
	    if(first != NULL){
		    current->next = new;
	        current = new;
			for(i=0;i<18;i++){
	            current->rollno[i] = data[i];}
	        getdetails();
	  	}
	    else {	  
	  		first = new;
	  		first->next = NULL;
	  		current = new;   
	  		for(i=0;i<18;i++){
	            current->rollno[i] = data[i];}
	  		getdetails();
	  	}
    }
    return;     
}

void deletion(char *data){
    struct student *ptr, *prev;
    int q = search(data);
    int recount = 0;
    if(q==0){
        if(count == 1){
	       if(first->next == NULL){
			  first = NULL;
			  current = NULL;
			}
	    else{
		   ptr = first;
		   first = first->next;
		   free(ptr);
		   }
	    }
	else{
		ptr = first->next;
		prev = first;
		while(ptr != NULL){
		     recount++;
		     if(recount == count){
				prev->next = ptr->next;
				if(ptr == current){
			   		current = prev;
				}
		     }
		     prev = ptr;  
		     ptr = ptr->next;	
		  }
	    }
	printf("Deleted\n");
    }
    else
	printf("Roll number does not exist to delete\n");
    return;	
}

void print(){
    struct student *ptr = first;
    int i = 1;
    while(ptr != NULL){
	printf("student%d\n",i++);
	printf("Name: %s\n",ptr->name);
	printf("Roll Number: %s\n",ptr->rollno);
	printf("Age: %d\n",ptr->age);
	printf("Gender: %s\n",ptr->gender);
	ptr = ptr->next;
  	}
    if(ptr==NULL)
	printf("No elements\n");
    return;
}

int main(){
    int entry;
    char input[20];
    printf("Press 1 to Insert(at end), 2 to Search, 3 to Delete and 4 to Print\n");
    scanf("%d",&entry);			//input of index of action
    while(entry>=1 && entry<=4){	//starting of while loop
	switch(entry){			//starting of switch
	    case 1:  {			//enqueue
				printf("enter the roll number to insert:");
    			scanf("%s",input);
				int result = search(input);
				if(result != 0){
			   		insertion(input);
			    }
				break;
			}
	    case 2:  {	
				if(first!=NULL){
			   		printf("enter the roll number to search:");
    				scanf("%s",input);
			   		int result = search(input);
			   		if(result != 0)
			        	printf("Roll number does not exist\n");
				}
				else
			   		printf("No entries to search");
				break;
			}
	    case 3:  {	
				if(first!=NULL){
			   		printf("enter the roll number to delete:");
			   		scanf("%s",input);		
			   		deletion(input);
				}
				else
			  	 	printf("No entries to delete");
				break;
			}
	    case 4:  {			//printing the elements in queue
            		print();
					break;
			}
	    }				//end of switch
	 printf("Press 1 to Insert(at end), 2 to Search, 3 to Delete and 4 to Print\n");
     scanf("%d",&entry);		//continuing the queue operations
     }					//end of while loop
    return;				//end of main
}


