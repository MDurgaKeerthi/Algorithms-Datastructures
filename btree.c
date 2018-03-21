/*
BTREE
BTREE of order n has nodes with atmost n+1 children and therefore n keys
number of keys = 5
number of children = 6
2t-1 keys = max = 5 keys
Atmost 2t-1 keys. every node except root must contain atleast t-1 keys
*/ 



#include<stdio.h>
#include<malloc.h>

#define max 5              //order of btree

struct bnode {             //structure of a node in btree
   int count;              //countains the number of keys
   int key[max];           //keys the node holds
   struct bnode *ptr[max+1];     //pointers to its children
   int leaf;
   };
   
struct bnode *root = NULL;
int t = (max + 1) / 2;       //t=3

void btreeSplitChild(struct bnode *x, int i){            //x is the node being split
   struct bnode *z = (struct bnode *)malloc(sizeof(struct bnode));    
   struct bnode *y = x->ptr[i];              //ith child of x
   z->leaf = y->leaf;
   z->count = t-1 ;
   int j;
   for(j=0; j< t-1 ; j++)              //taking t-1 bigger keys from y
      z->key[j] = y->key[j + t];
   if(y->leaf == 0){
      for(j=0; j< t; j++)
         z->ptr[j] = y->ptr[j + t];       //similar children pointers
      }
   y->count = t-1;               //reducing keys of y, since new node z takes them
   
   for(j = x->count; j>= i+1; j--)
      x->ptr[j+1] = x->ptr[j];
   x->ptr[i+1] = z;                 //z becoming new child of x
   for(j = x->count-1; j>= i; j--)
      x->key[j+1] = x->key[j];   
   x->key[i] = y->key[t-1];
   x->count++;                      //increasing count of x since new child formed
   return;
}

void btreeInsertNonfull(struct bnode *x, int k){         //inserting k in a non-full node 
   int i = x->count - 1 ;
   if(x->leaf == 1){          //if leaf, simply inserting
      while(i>=0 && k < x->key[i]){             //traversing through the keys of x to find the position for k
         x->key[i+1] = x->key[i];
         i--;
         }
      x->key[i+1] = k;           //placing k
      x->count++;                //increasing count since new key joined
      }
   else {
      while(i>=0 && k < x->key[i])
         i--;
      i++;       
      struct bnode *q = x->ptr[i];        //child node to which recurion descends
      if(q->count == max){                //if node where k may belong is full splitting the parent "x"
         btreeSplitChild(x,i);
         if(k > x->key[i])
            i++;
         }
      btreeInsertNonfull(x->ptr[i], k);      //otherwise inserting in q 
      }
   
   return;
}                

void insert(){             //the basic function which inserts a element
   int value;
   printf("Enter the value to be inserted: ");
   scanf("%d", &value);
   
   if(root == NULL){          //if the tree is empty
      struct bnode *new = (struct bnode *)malloc(sizeof(struct bnode)); 
      new->leaf = 1;       
      new->count = 1;
      new->key[0] = value;
      int i;
      for(i=0; i<max; i++)
         new->ptr[i] = NULL;
      root = new;
      return; 
      }
   
   struct bnode *r = root;
   if(r->count == max ){         //if node is full - contains 2t-1 keys
      struct bnode *s = (struct bnode *)malloc(sizeof(struct bnode)); 
      root = s;
      s->leaf = 0;
      s->count = 0;        //initialiing a new node
      int i;
      for(i=0; i<max; i++)
         s->ptr[i] = NULL;
      s->ptr[0] = r;
      btreeSplitChild(s,0);            //splitting is only way by which a btree grows
      btreeInsertNonfull(s, value);    //inserts value in node s
      }
   else
      btreeInsertNonfull(r, value);    //inserts value in node r (root)  

return;
}



struct bnode *btreesearch(struct bnode *x, int k){       //recursive search
   int i=0;
   while(i< x->count && k> x->key[i])                 //checks among keys of a node
      i++;
   if(i< x->count && k == x->key[i]){
      return x;
      }
   else if(x->leaf == 1){           //if its the leaf and key is not found in the node x
      return NULL;
      }      
   else
      return btreesearch(x->ptr[i], k);         //goes to its children
return;
} 

//functions concerned with deletion

void delete(struct bnode*, int );
void fillnode(struct bnode*, int);
void fromnext(struct bnode*, int);
void fromprev(struct bnode*, int);
void merge(struct bnode*, int );
int findpred(struct bnode*, int);
int findsuc(struct bnode*, int);

void basedel(int val){              //checks if tree is non empty and then calls delete function
   if(root==NULL){
      printf("no keys to delete\n");
      return;
      }
 
   delete(root,val);
   
   if(root->count==0){           //setting up issues with root
      struct bnode *del=root;
      if(root->leaf==1){
         root=NULL;
         }
      else{
         root=root->ptr[0];
         }
      free(del);
      }
   return;
}

void delete(struct bnode *x,int val){                 //the function which is called recursively to delete given key
   
   int index = 0;
   int i;
   struct bnode *y,*z;
   while(index < x->count && x->key[index] < val){       //finding posiible position of node
      index++;
      }
    
   if((index<x->count) && (val==x->key[index])){         //if key exists in the present node
      if(x->leaf==1){                                    //simple leaf case
         for(i=index+1;i<x->count;i++){
            x->key[i-1]=x->key[i];                    //moving the keys to overwrite val
            }
         x->count--;
         return;
         }  
      else{
        y=x->ptr[index];                  //left child of key's place
        z=x->ptr[index+1];                //right child

        if(y->count>=t){                  //if left child has enough keys to give
            int predkey = findpred(x,index); //getting the key
            x->key[index] = predkey;
            delete(y,predkey);            //going on recursively
            }  
        else if(z->count>=t){          //if right child has enough keys to give
            int suckey = findsuc(x,index);
            x->key[index] = suckey;
            delete(z,suckey);          //going on recursively
            }
         else{
           merge(x,index);       //if neither child have enough keys to give, merge them
           delete(y,val);        //and delete the key
            }
         }
      }     
   else{                      //if present node does not contain key to delete
      struct bnode *c=x->ptr[index];
      if(c->count<t){                  
         fillnode(x,index);         //fill c if it does not have enough keys to give
         }
      if(index>x->count){
         delete(x->ptr[index-1],val);     //going on recursively
         }
      else{
         delete(x->ptr[index],val);    //going on recursively
         }
      }
   return;
}

void fillnode(struct bnode *x,int index){  //if the node contains < t-1 keys, getting keys from the neighbouring nodes
   struct bnode *l, *r;
   if(index>0)
      l = x->ptr[index-1];
   else
      l = NULL;
      
   if(index<x->count)
      r = x->ptr[index+1];
   else
      r = NULL;
    
   if(l != NULL && l->count >= t)         //if left neighbour has enough keys to give, getting from left
      fromprev(x, index);
   else if(r != NULL && r->count >= t) 
      fromnext(x, index);                    //else if right has, getting from it
   else{
      if(index != x->count)                 //if neither neighbours has keys to give, the child nodes are merged
         merge(x, index);
      else
        merge(x, index-1);
      }
   return;
}

void fromnext(struct bnode *x,int index){          
   int i;
   struct bnode *c = x->ptr[index];          //node which needs key
   struct bnode *next = x->ptr[index+1];     //which gives key
   c->key[c->count] = x->key[index];         //putting the key a from x to its child
   
   if(c->leaf != 1)
      c->ptr[c->count +1] = next->ptr[0];    //similarily adding a child from next

   x->key[index] = next->key[0];             //getting key from next to x to compensate loss of a
   for(i=1; i< next->count; i++)
      next->key[i-1] = next->key[i];         //moving keys in next forward since one key is given to x
      
   if(next->leaf!=1){
      for(i=1; i<= next->count; i++)         //similarly child pointers
         next->ptr[i-1] = next->ptr[i];
      }

   c->count = c->count + 1;               //increasing count of left child
   next->count = next->count - 1;         //decreasing count of child which gave key
   return;
}

void fromprev(struct bnode *x,int index){
   int i;
   struct bnode *c = x->ptr[index];
   struct bnode *pre = x->ptr[index-1];

   for(i= c->count - 1; i>=0; i--){       //moving keys in c backward since one key is borrowed
      c->key[i+1] = c->key[i];
      }
   if(c->leaf!=1){
      for(i= c->count; i>=0; i--){
         c->ptr[i+1] = c->ptr[i];         //similarly child pointers
         }
      }
   c->key[0] = x->key[index-1];           //taking key from x
   if(x->leaf != 1){
      c->ptr[0] = pre->ptr[pre->count];   //getting child pointer from pre   
      }
   x->key[index-1] = pre->key[pre->count-1];  //taking key from pre since it gave to c        
   c->count = c->count + 1;                  //increasing count of right child
   pre->count = pre->count - 1;              //decreasing count of child which gave key
   return;
}


void merge(struct bnode *x,int index){       //merges children of given index and next index      
   int i;
   struct bnode *child1 = x->ptr[index];     
   struct bnode *child2 = x->ptr[index+1];
   child1->key[t-1] = x->key[index];         //getting key from x to middle of child1
    
   for(i=0; i < child2->count; i++){
      child1->key[i+t] = child2->key[i];     //getting remaining keys from child2
      }
   if(child1->leaf != 1){
      for(i=0; i <= child2->count; i++){
         child1->ptr[t+i] = child2->ptr[i];  //similarly child pointers
         }
      }

   for(i = index+1; i < x->count; i++){      //moving keys to cover up key moved to child1
      x->key[i-1] = x->key[i];
      }

   for(i = index+2; i <= x->count; i++){     //similarly child pointer
      x->ptr[i-1] = x->ptr[i];
   }

   child1->count = child1->count + child2->count + 1;    //increasing count of child1
   x->count--;                                           //decreasing the count of x
   free(child2);
   return;
}
 
int findpred(struct bnode *x, int index){        //gets the key of predecessor node of given x
   struct bnode *tmp = x->ptr[index];
      while(tmp->leaf == 0){
         tmp = tmp->ptr[tmp->count];         //traversing for the predecessor
      }
   return tmp->key[tmp->count-1];
}


int findsuc(struct bnode *x,int index){         //gets the key of successor node of given x
   struct bnode *temp = x->ptr[index+1];
   while(temp->leaf == 0){
      temp = temp->ptr[0];                      //traversing for the successor
      }
   return temp->key[0];
}

//functions below do printing of nodes

int height(struct bnode *slot){                    //getting the level of a node
   if(slot==NULL)
      return 0;
   else {
       int heights[slot->count+1];                    //array of height of its children
       int e,maxheight; 
       for(e = 0; e <= slot->count; e++)   
          heights[e] = height(slot->ptr[e]);
       
       for(e = 0; e < slot->count; e++){
         if(heights[e] > heights[e+1])       //height of a node - depends on max height among its children
            maxheight = heights[e];
         else
            maxheight = heights[e+1];
         }      
       return (maxheight + 1);               //returning the height
       }           
}

void printLevel(struct bnode *slot, int level) {         //prints each level
   if(slot == NULL)
      return;
   if(level == 1){
      int v;
      for(v=0; v < slot->count ; v++)                    //printing all keys
          printf("%d  ",slot->key[v]);
      printf("--");    
      }    
   else if(level > 1) {
      int v;
      for(v=0; v <= slot->count ; v++) 
          printLevel(slot->ptr[v],level-1);        //going to each of its children's level
       }   
   return;
}        

void print(){                                   //level order print
   if(root == NULL)
       printf("No elements\n");     
   else {    
       int d;
       for(d=1; d<=height(root); d++) {         //prints by height
           printLevel(root,d);
           printf("\n");
       }
   }        
   return;    
}

int main() {            //main program
   int entry;
   printf("B-TREE. Enter 1 to Insert, 2 to Delete, 3 to Search and 4 to print: ");
	scanf("%d",&entry);
	while(entry>=1 && entry<=4) {
		switch(entry) {
			case 1: {         
				insert();            //for insertion 
				break;
				}
			case 2: {
			   int value;
            printf("Enter the value to be deleted: ");
            scanf("%d", &value);  
            struct bnode *v = btreesearch(root,value);           //searching if value exists
            if(v == NULL)
               printf("The node doesnot exist in the tree\n");
            else
     			   basedel(value);         //calling a deletion function which further calls others
				break;
				}
			case 3: {
			   int value;
            printf("Enter the value to be searched: ");
            scanf("%d", &value);
			   struct bnode *x = btreesearch(root, value);     //calling search function
			   if(x == NULL)                                   //printing its output   
			      printf("Value not found\n");
			   else
			      printf("value is found\n");         
			   break;
			   }	
			case 4: {
				print();                                  //level order print
				break;
				}
		}  
		printf("Enter 1 to Insert, 2 to Delete, 3 to Search and 4 to print: ");
		scanf("%d",&entry);
	}
   printf("End of the program\n");
   return 0;
}                 //end of the program
