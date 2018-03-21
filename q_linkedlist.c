/*
Implementation of Queue on single linked lists */

#include<stdio.h>
#include<malloc.h>

struct position{
	int value;
    struct position *next;
};

struct position *first = NULL;
struct position *last = NULL;

void enqueue(){
	int input;
	printf("Enter the number to be enqueued: ");
	scanf("%d",&input);
	struct position *new = (struct position *)malloc(sizeof(struct position));
	if(new == NULL)
		printf("error");
	else{	
		new->value = input;
		new->next = NULL;
		if(first != NULL) 
			last->next = new;
		else
			first = new;
		last = new;
	}	
	return;
}

void dequeue(){
	if(first == NULL && last == NULL)
		printf("No elements in Queue to dequeue\n");
	else if(first == last) {
		printf("Dequeued element is %d\n",first->value);
		free(first);
		first = NULL;
		last = NULL;
		}
	else {
		printf("Dequeued element is %d\n",first->value);
		struct position *ptr = first;
		first = first->next;
		free(ptr);
		}	
	return;
}

void print() {
	struct position *ptr = first;
    if(ptr == NULL)
		printf("No elements in Queue.\n");
	else { 
		printf("Elements in Queue: ");
		while(ptr != NULL){
			printf("%d  ",ptr->value);
			ptr = ptr->next;
			}
		printf("\n");
		}
	return;
}


int main() {
	int entry;
    printf("Queue using Linked List. Enter 1 to Enqueue, 2 to Dequeue and 3 to Print: ");
	scanf("%d",&entry);
	while(entry>=0 && entry<=3) {
		switch(entry) {
			case 1: {
				enqueue();
				break;
				}
			case 2: {
				dequeue();
				break;
				}
			case 3: {
				print();
				break;
				}
		}  
		printf("Enter 1 to Enqueue, 2 to Dequeue and 3 to Print: ");
		scanf("%d",&entry);
	}
	return;
}
