/*
priority queue
low "priority number" implies high priority
min heap
*/

#include<stdio.h>
#include<malloc.h>

struct task{
   int priority;              //structure of task
   char taskname[50];
};

struct task *priorityQueue;      //priority queue array
int tasks;                       //number of tasks
int lastTask = -1;               //index of last element in the array

void swap(struct task *task1, struct task *task2){   //swapping by reference
   struct task temp;
   temp  = *task1;
   *task1 = *task2;
   *task2 = temp;
   return;
}

void heapify(int i) {         //makes the subtree from "i" into heap
   int l = 2*i+1;
   int r = 2*i+2;
   int smallest;
   if(l<=lastTask && priorityQueue[i].priority > priorityQueue[l].priority)
      smallest = l;
   else 
      smallest = i;
   if(r<=lastTask && priorityQueue[smallest].priority > priorityQueue[r].priority ) 
      smallest = r;
   if(smallest != i){            //getting the smallest element to carry up the heap
      swap(&priorityQueue[i], &priorityQueue[smallest]);
      heapify(smallest);         //checking subtree of the given subtree
   }
   return ;
}

void setPriority(int i, struct task temp) {
   /*if(temp.priority > priorityQueue[i].priority)
      printf("error");*/
   priorityQueue[i] = temp;
   while(i>=0 && priorityQueue[(i-1)/2].priority > priorityQueue[i].priority) {     //arranges elements in the queue in their priority order
      swap(&priorityQueue[(i-1)/2], &priorityQueue[i]);
      i = (i-1)/2;         //from an element to its parent
   }
   return;
}

void insert(){
   if(lastTask != tasks-1){
      lastTask++;    
      printf("Enter the priority number: ");          //inserting the element
      scanf("%d", &priorityQueue[lastTask].priority);
      printf("Enter the task: ");
      scanf("%s", priorityQueue[lastTask].taskname);
      setPriority(lastTask, priorityQueue[lastTask]);    //inserting in the proper place according to the priority
   }
   else
      printf("Too many tasks already in list\n");
   return;
}

void min(){       //prints the first(high priotity) element in the array(queue)
   if(lastTask >= 0) 
      printf("priority: %d, Task name: %s\n", priorityQueue[0].priority, priorityQueue[0].taskname);
   else
      printf("No tasks in Priority Queue\n");   
   return;
}

void extractMin() {
   if(lastTask >= 0) {
      min();
      priorityQueue[0] = priorityQueue[lastTask];  //overwriting the element
      lastTask--;       //removing the elment
      heapify(0);       //making sure that heap property is maintained
   }
   else
      printf("No tasks in Priority Queue\n");
   return;
}



int main() {                     //main function
   printf("PRIORITY QUEUE");
   printf("Max number of tasks you would like in Priority Queue: ");
   scanf("%d", &tasks);
   priorityQueue = (struct task*)malloc(sizeof(struct task) * tasks);            //allocating space for priorityQueue
   int choice;
   printf("1.Insert a task 2.Extract task 3.Print present task\nEnter: ");
   scanf("%d", &choice);
   printf("Priority is integer and taskname is string\n");
   while(choice >= 1 && choice <= 3){
   switch(choice) {
   case 1:  {
               insert();         //calling insert function
               break;
            }
   case 2:  {
               extractMin();     //extracting the high priority task
               break;
            }
   case 3:  {
               min();            //prints high priority task
               break;
            }
   
      }
   printf("1.Insert a task 2.Extract task 3.Print present task \nEnter: ");
   scanf("%d", &choice);  
   }
   printf("End of the program\n");
   return 0;
}                                //end of main


