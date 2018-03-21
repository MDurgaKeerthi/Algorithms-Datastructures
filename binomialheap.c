/*
BINOMIAL HEAP
*/


#include<stdio.h>
#include<limits.h>
#include<malloc.h>

struct bheap{                 //stucture of a node in the binomial heap
   int value;
   struct bheap *parent;
   struct bheap *left;        //left child
   struct bheap *sibiling;
   int degree;
   };
   
struct bheap *head = NULL;       //head of the heap

void binomialLink(struct bheap *y, struct bheap *z){ //links y to z, z becomes parent of y
   y->parent = z;
   y->sibiling = z->left;
   z->left = y;                  //making y as child of z
   z->degree = z->degree + 1;
   return;
}   
//this merge function ensures that if two roots in binomial heap have same degree, they will be adjacent 
struct bheap* bhmerge(struct bheap *H1, struct bheap *H2){     //merging root lists of H1, H2 according to their degree
   struct bheap *a = H1;
   struct bheap *b = H2;
   struct bheap *H;
   struct bheap *temp, *temp1;
   if (a != NULL && b != NULL){
         if(a->degree <= b->degree)
            H = a;                     //H conatins the smaller heap
         else
            H = b;
         }
   if( a== NULL)
      return b;
   if( b== NULL)
      return a;      
   
   while(b != NULL && a != NULL){         
      if( a->degree < b->degree) {
         a = a->sibiling ;             //going through sibilings of lesser heap size
         }
      else if( a->degree == b->degree){ //making one as the sibiling of other if both have same degrees
         temp = a->sibiling;
         a->sibiling = b;
         a = temp;
         }
      else{
         temp1 = b->sibiling;
         b->sibiling = a;
         b = temp1;
         }                  
      }
   return H;         //returning the merged list
}     

struct bheap* bhunion(struct bheap *H1, struct bheap *H2){
   struct bheap *H = (struct bheap *)malloc(sizeof(struct bheap));
   H = bhmerge(H1, H2);  //calling merge
   if(H == NULL)
      return H;
      
   struct bheap *prev = NULL;          //root of preceeding heap
   struct bheap *x = H;               //root of current heap
   struct bheap *next = x->sibiling;   //root of next
   while( next != NULL ){
      if( x->degree != next->degree || (next->sibiling != NULL && next->sibiling->degree == x->degree) ){
         prev = x;   //if order of x and next are different, we move forward or x is the first of three roots with equal degree
         x = next;
         }
      else{
         if( x->value <= next->value){
            x->sibiling = next->sibiling;
            binomialLink(next, x);
            }
         else {         //if x is first of two roots of equal degree
            if( prev == NULL)
               H = next;
            else   
               prev->sibiling = next; 
            binomialLink(x, next);  //linking x and next so that x and next root don't have equal degrees
            x = next;
            }
         }  
      next = x->sibiling;              
      }
 
   return H;
}   

void bhinsert(){           //inserts the given value
   int input;
   printf("Enter the value to be inserted:");
   scanf("%d", &input);
   struct bheap *h1 = (struct bheap *)malloc(sizeof(struct bheap));  //creating a new node
   h1->left = NULL;
   h1->parent = NULL; 
   h1->sibiling = NULL;
   h1->degree = 0;
   h1->value = input;
   head = bhunion(head,h1);      //making this new node as a part of the existing binomial heap
   return;
}   

void findMin(){            //printing out the min which is one of heap heads
   struct bheap *y = NULL;
   struct bheap *x = head;
   if(x == NULL){          //if binomial heap is empty
      printf("No elements in binomial heap\n");
      return;
      }
   int min = INT_MAX;         //intialising with infinity
   while(x != NULL){
      if(x->value <= min){
         min = x->value;            //getting the in value
         y = x;
         }
      x = x->sibiling;              //traverse across the heap heads
      }
   printf("The min is %d\n", y->value );
   return;
}       

struct bheap *Hr; 
void reverse(struct bheap *y){      //reversing the order of sibilings of y
   if(y->sibiling != NULL){
      reverse(y->sibiling);
      y->sibiling->sibiling = y;
      }
   else
      Hr = y;        //and carrying back the newly ordered ones in Hr
   return;
}  

void deleteMin() {
   struct bheap *x = head;
   Hr = NULL;
   if(x == NULL){             //if bheap is empty
      printf("The heap is empty\n");
      return ;
      }
      
   int min = x->value;
   struct bheap *p = x;
   struct bheap *temp = NULL;
   while(p->sibiling != NULL){   //finding the root with min value
      if( p->sibiling->value < min){
         min = p->sibiling->value;  //storing min for comparing
         temp = p;
         x = p->sibiling;
         }
      p = p->sibiling;
      }
   if(temp == NULL && x->sibiling == NULL) //if that value is there in bheap
      head = NULL;
   else if( temp == NULL)        //if the value to be deleted is in the head
      head = x->sibiling;
   else if ( temp->sibiling == NULL)
      temp = NULL;
   else
      temp->sibiling = x->sibiling;  //removing x from links
   if(x->left != NULL){       //revering the order of linked list of x's children 
      reverse(x->left);
      x->left->sibiling = NULL;
      }
   head = bhunion(head, Hr);  //setting up heap again
   return;         
}         
               

int main() {               //main function
   int entry;
   printf("BINOMIAL HEAP.\nEnter 1 to Insert, 2 to Delete and 3 to print min: ");
	scanf("%d",&entry);
	while(entry>=1 && entry<=3) {
		switch(entry) {
			case 1: {
				bhinsert();       //inserts a value in the binomial heap
				break;
				}
			case 2: {
				deleteMin();      //deletes the minimum
				break;
				}
			case 3: {
			   findMin();        //prints the minimum
				break;
				}
		}  
		printf("Enter 1 to Insert, 2 to Delete and 3 to print min: ");
		scanf("%d",&entry);
	}
   printf("End of the program\n");
   return 0;            //end of the program
}         
