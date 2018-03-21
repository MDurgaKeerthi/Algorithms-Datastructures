/*
RED BLACK TREES
*/


#include<stdio.h>
#include<malloc.h>

struct rbnode{
   enum {red, black} color;      //red = 0, black =1
   int value;
   struct rbnode *left;          //left child
   struct rbnode *right;         //right child
   struct rbnode *parent;        //parent of the node
   };
   
struct rbnode *root;             //root of the tree
struct rbnode *Tnil;
void print();

void leftRotate(struct rbnode *x) {    //left rotate function
   struct rbnode *y;
   y = x->right;
      x->right = y->left;
      if(y->left != Tnil )
         y->left->parent = x;    //x as parent of left child of y
      y->parent = x->parent;     //y changing its parent
      if(x->parent == Tnil)
         root = y;
      else if(x == x->parent->left)
         x->parent->left = y;    //y in x place
      else
         x->parent->right = y;
      y->left = x;
      x->parent = y;       //completely changed
   return;
}

void rightRotate(struct rbnode *y) { //similarly right rotate, with left and right interchanged from above
   struct rbnode *x;
   x = y->left;
      y->left = x->right;
      if(x->right != Tnil  )
         x->right->parent = y;
      x->parent = y->parent;
      if(y->parent == Tnil)
         root = x;
      else if(y == y->parent->left)
         y->parent->left = x;       //x in y place
      else
         y->parent->right = x;
      x->right = y;
      y->parent = x; 
   return;
}

void insertFixup(struct rbnode *z) { //maintains rbt properties
   struct rbnode *y, *t1, *t2;
   while(z->parent->color == red) {
      if(z->parent == z->parent->parent->left){
         y = z->parent->parent->right;
         if(y->color == red){ //case 1 - children of red node are black -- uncle is also red
            z->parent->color = black; //changing their colors to black
            y->color = black;
            z->parent->parent->color = red; //and grandfather to red
            z = z->parent->parent;
            }
         else{
          if(z == z->parent->right) {  //case 2 - if z and its parent are red, rotation is needed
            z = z->parent;
            leftRotate(z);
            }
          else{                       //case3 --setting back
            z->parent->color = black;
            z->parent->parent->color = red;
            rightRotate(z->parent->parent);
            }
         }   
      }
      else {                //cases are same as above since left and right are interchangeable
         y = z->parent->parent->left;
         if(y->color == red){          //case 1
            z->parent->color = black;
            y->color = black;
            z->parent->parent->color = red;
            z = z->parent->parent;
            }
         else if(z == z->parent->left) { //case 2
            z = z->parent;
            rightRotate(z);
            }
         else{                                //case 3
            z->parent->color = black;
            z->parent->parent->color = red;
            leftRotate(z->parent->parent);
            }
         }   
      }
   root->color = black;    //finally maintaining that root is black
   return;
}

void insert(){
   struct rbnode *new = (struct rbnode *)malloc(sizeof(struct rbnode));
   printf("Enter the integer to insert: ");
   scanf("%d",&new->value);
   new->right = Tnil;            //making the new node
   new->left = Tnil;
   new->parent = Tnil;
   new->color = red;
   struct rbnode *ptr, *prev = Tnil;
   if(root != Tnil) {         //traversing through the nodes just like in  binary search tree
      ptr = root;
      while(ptr != Tnil) {
         prev = ptr;
         if(new->value > ptr->value) 
            ptr = ptr->right;
         else 
            ptr = ptr->left;
      }
      new->parent = prev;
      if(prev->value < new->value)  //and inserting in the position obtained through traversing
         prev->right = new;
      else 
         prev->left = new;
   }
   else 
      root = new;
         
    insertFixup(new);      //fixing the properties of rbt since every input node is colored to red
    return;
}        

void rbDeleteFixup(struct rbnode* x) {    //maintains rbt properties after deletion
   struct rbnode *w;
   while(x != root && x->color == black) {
      if(x == x->parent->left) {
         w = x->parent->right;
         if(w->color == red) {      //case1: sibiling of x is red
            w->color = black;
            x->parent->color = red;
            leftRotate(x->parent);     //left rotation
            w = x->parent->right;
            }
         if(w->left->color == black && w->right->color == black){       //case2 - x's sibiling is black and both the children of x' sibiling are black
            w->color = red;
            x = x->parent;
            }
         else { //case 3- x's sibling is black, sibling's left child is red and right child is black
            if(w->right->color == black) {      
               w->left->color = black;
               w->color = red;
               rightRotate(w);
               w = x->parent->right;  
               }  //case 4 - x's sibling is black,sibling's right child is red and left child is black             
            w->color = x->parent->color;     
            x->parent->color = black;
            w->right->color = black;
            leftRotate(x->parent);
            x = root;
            }
         }
      else{     //same as above except that right and left are interchanged                 
         w = x->parent->left;
         if(w->color == red) {         //case 1
            w->color = black;
            x->parent->color = red;
            rightRotate(x->parent);
            w = x->parent->left;
            }
         if(w->left->color == black && w->right->color == black){             //case2
            w->color = red;
            x = x->parent;
            }
         else{
            if(w->left->color == black) {  //case 3
               w->right->color = black;
               w->color = red;
               leftRotate(w);
               w = x->parent->left;  
               }                
            w->color = x->parent->color;  //case 4
            x->parent->color = black;
            w->left->color = black;
            rightRotate(x->parent);
            x = root;
         } 
      }     
   }   
   x->color = black;      
   return;
}

void rbTransplant(struct rbnode* u, struct rbnode* v) { //putting v in place of u
   if(u->parent == Tnil)
      root = v;
   else if(u == u->parent->left)    //occupying u's place
      u->parent->left = v;
   else 
      u->parent->right = v ;
   v->parent = u->parent;        //changing its (v) parent
   return;
}   

struct rbnode* treeMin(struct rbnode* x) {  //getting minimum from right subtree to overwrite the internal node to be deleted
   while(x->left != Tnil)
      x = x->left;
   return x;
}      

struct rbnode* getPTR(int number) {    //returns ptr which holds the value "number"
   struct rbnode *ptr;
   if(root != Tnil) {
      ptr = root;
      while(ptr != Tnil) {
         if(number == ptr->value)
            break;
         else if(number > ptr->value) 
            ptr = ptr->right;
         else 
            ptr = ptr->left;
        }
    } 
    return ptr;
}

void delete() {
   if(root == Tnil){
      printf("No elements to delete\n");
      return;
      }
   int dinput;
   printf("Enter the integer to delete: ");
   scanf("%d",&dinput);
   struct rbnode *ptrToDel = getPTR(dinput); //getting adress of element to be deleted
   if(ptrToDel == Tnil ) {
      printf("Does not exist\n");         //if not found
      return;
   }
   struct rbnode *x;
   struct rbnode *y = ptrToDel;        //initialising y
   int yOriginalColor = y->color;
   if(ptrToDel->left == Tnil){         //if left child is null just bring up next link
      x = ptrToDel->right;
      rbTransplant(ptrToDel, ptrToDel->right);
      }
   else if(ptrToDel->right == Tnil){ //if right child is null, move the link from grandparent to child of node
      x = ptrToDel->left;
      rbTransplant(ptrToDel, ptrToDel->left);
      }  
   else{          //has both children
      y = treeMin(ptrToDel->right);    //get the proper min value to replace it
      yOriginalColor = y->color;
      x = y->right;        //initailising x
      if(y->parent == ptrToDel)  //if element to be deleted is in parent of y
         x->parent = y;          //make y as parent of y->right (x)
      else{    
         rbTransplant(y, y->right);  //gets y->right in y place
         y->right = ptrToDel->right;
         y->right->parent = y;
         }
      rbTransplant(ptrToDel, y);    //y in place of ptr to delete
      y->left = ptrToDel->left; 
      y->left->parent = y;
      y->color = ptrToDel->color;
      }
   if(yOriginalColor == black)
      rbDeleteFixup(x);       //fixing the rbt after deletion
   return;
} 


struct rbnode search(){                //search function
    struct rbnode *ptr;
    int input,flag=0;
    printf("Enter the integer to search: ");
    scanf("%d",&input);  
     
    if(root!=NULL) {
        ptr = root;
        while(ptr!=NULL) {
            if(input == ptr->value){      //if found
                printf("Found\n");
                flag = 1;
                break;
                }
            else if(input > ptr->value) {    //else if bigger than pointer value, take right
                ptr = ptr->right;
                }
            else {
                ptr = ptr->left;             //else take left
                } 
        }
    } 
    if(flag == 0)
        printf("DOes not exist\n");
    return ;
}


int height(struct rbnode *slot){                   //getting the level of a node
   if(slot == Tnil )
      return 0; 
      
   int lheight = height(slot->left);
   int rheight = height(slot->right); 
   if(lheight > rheight)
      return (lheight + 1);
   else
      return (rheight + 1);
}

void printLevel(struct rbnode *slot, int level) {     //prints each level
   if(slot == Tnil  ){
      printf("   ");
      return;
      } 
      
   if(level == 1)
      printf("%d-%d  ",slot->value, slot->color);
   else if(level > 1) {
      printLevel(slot->left,level-1);                 //going to children's level
      printLevel(slot->right,level-1);  
      } 
   return;
}        

void print(){                                //level order print
   if(root == Tnil)
      printf("No elements\n");
   else{
      int d;
      for(d=1; d<=height(root); d++) {       //prints by height
         printLevel(root,d);                 
         printf("\n");
         }
      }  
    return;    
}

int main() {
  
   Tnil = (struct rbnode *)malloc(sizeof(struct rbnode));      //allocating memory for Tnil
   Tnil->left = NULL;                                          //giving values for Tnil
   Tnil->right = NULL;
   Tnil->parent = NULL;
   Tnil->color = black;
   root = Tnil;                                                //intialising root to Tnil
   
   int entry;
   printf("RED BLACK TREE.\nEnter 1 to Insert, 2 to search, 3 to Delete and 4 to Print: ");
	scanf("%d",&entry);
	while(entry>=1 && entry<=4) {
		switch(entry) {
			case 1: {
				insert();                                          //for insertion
				break;
				}
			case 2: {
				search();                                          //to search
				break;
				}
			case 3: {
				delete();                                          //to delete
				break;
				}	
			case 4: {
				print();                                           //to print
				break;
				}
		}  
		printf("Enter 1 to Insert, 2 to search, 3 to Delete and 4 to Print: ");
		scanf("%d",&entry);
	}

   printf("end of the porgram\n");
   return 0;
}   

