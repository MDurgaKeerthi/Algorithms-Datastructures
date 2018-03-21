/*

Stack on Array */

#include<stdio.h>		//including header file

int top = -1;			//initialising top,the positional index,to -1
int size;			//declaring size of stack to be global

void push(int arr[], int data){	//defining push function
    if(top != size-1){		//if stack is not full
       top++;			//incrementing the top
       arr[top] = data;
      }
    else			//if stack is full
       printf("You crossed your mentioned limit");
    return;
}

void pop(int arr[]){		//defining the pop function
    if(top != -1){		//if stack is not empty
       printf("Element to be popped:%d\n", arr[top]);
       top--;			//decrementing top
       }
    else			//if stack is empty
       printf("No elements to be popped");
    return;
}

void print(int arr[]){		//defining print function
    int j;
    if(top != -1){		//printing from the end of array so that it 
	for(j=top;j>=0;j--)	//gives actual stack feel
	   printf("%d\n",arr[j]);
     }
     else			//if there are no elements in stack
	   printf("\nStack is empty");
     return;
}

int main() {			//starting of main	
    int i,entry,input;
    printf("enter number of integers to be in stack:");
    scanf("%d",&size);		//input of stack size
    if(size>0){
    int stack[size];
    printf("Press 1 to push, 2 to pop and 3 to print\n");
    scanf("%d",&entry);		//input of index of action
    while(entry>=1 && entry<=3){//starting of while loop
	switch(entry){		//starting of switch
	    case 1:  {		// push of data
			printf("enter the number:");
			scanf("%d",&input);	//input of element to be pushed
			push(stack,input);
			break;
			}
	    case 2:  {		//pop of data
			pop(stack);
			break;
			}
	    case 3:  {		//printing elements of stack
            		print(stack);
			break;
			}
	    }			//end of switch
	 printf("Press 1 to push, 2 to pop and 3 to print\n");
    	 scanf("%d",&entry);	//end of while
     }
    }
    else
         printf("Not possible");
    return;			//end of main
}
