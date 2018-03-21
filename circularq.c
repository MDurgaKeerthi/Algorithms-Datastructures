/*
Queue implementation using Circular Arrays */

#include<stdio.h>	//including header file

int first = -1;		//initialising first and last, positional indices,to -1 
int last = -1;
int size;		//declaring size of queue to be global

void enqueue(int queue[]){	//defing enqueue function
    if(first==0 && last == size-1 || last == first-1){	//if queue is full
	printf("Queue is full.Dequeue to make new entries.\n");
	return;
       }
    else {
	int input;
	printf("enter the number:");
	scanf("%d",&input);//input of element to be enqueued
	if(first==-1 && last==-1){	//if queue has no elements
	   first++;
	   last++;
	   queue[last] = input;
	   return;
           }
    	else {				//if queue has some elements & not full
	   last = (last+1)%size;
	   queue[last] = input;
           } 
     }
     return; 
}

void dequeue(int queue[]){		//defining dequeue function
     if(first==-1 && last==-1){		//if queue is empty
	printf("No elements in Queue to Dequeue\n");
	return;
       }
     else if(first ==last){		//if queue has only one element
	printf("Dequeued element is %d\n",queue[first]);
	first = -1;
	last = -1;
	return;
       }
     else {				//if queue has some elements
	printf("Dequeued element is %d\n",queue[first]);
	first++;
       }
     return;
}

void print(int queue[]){		//defining print function
     int i;
     if(first==-1 && last==-1){		//if queue has no elements
	printf("No elements in Queue\n");
	return;
       }
     else if(last>=first) {		//if no dequeuing happened
	printf("Elements of Queue: ");
	for(i=first; i<=last; i++)
	    printf("%d   ",queue[i]);
        printf("\n");
	return;
       }
     else {				//if queue has become full and then
	for(i=first; i<=size-1; i++)	//enqueuing happened after dequeuing
	    printf("%d   ",queue[i]);
        for(i=0; i<=last; i++)
	    printf("%d   ",queue[i]);
        printf("\n");
       }
     return; 
}

int main() {				//staring of main
    int i,entry;
    printf("enter number of integers to be in Queue:");
    scanf("%d",&size);			//input of number of entries in queue
    if(size>0){
      int Q[size];			//declaration of queue
      printf("Press 1 to Enqueue, 2 to Dequeue and 3 to Print\n");
      scanf("%d",&entry);		//input of index of action
      while(entry>=1 && entry<=3){	//starting of while loop
	switch(entry){			//starting of switch
	    case 1:  {			//enqueue
			enqueue(Q);
			break;
			}
	    case 2:  {			//dequeue
			dequeue(Q);
			break;
			}
	    case 3:  {			//printing the elements in queue
            		print(Q);
			break;
			}
	    }				//end of switch
	 printf("Press 1 to Enqueue, 2 to Dequeue and 3 to Print\n");
    	 scanf("%d",&entry);		//continuing the queue operations
       }					//end of while loop
    else
      printf("size can not be non-positive"); 	
    return;				//end of main
}
