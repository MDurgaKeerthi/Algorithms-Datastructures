/*
Binary Search Tree with insert, search, delete operations */

#include<stdio.h>
#include<malloc.h>

struct node{
	int value;
    struct node *rchild;      //node structure with two children and a key
	struct node *lchild;
};

struct node *root = NULL;     //root of bst

void insert(){                //inserts integers into tree
    struct node *new = (struct node *)malloc(sizeof(struct node));
    printf("Enter the integer to insert: ");
    scanf("%d",&new->value);
    new->rchild = NULL;
    new->lchild = NULL;
    struct node *ptr, *prev;
    if(root!=NULL) {
        ptr = root;
        while(ptr!=NULL) {
            if(new->value > ptr->value) {    //if higher than a node, going right
                prev = ptr;
                ptr = ptr->rchild;
            }
            else {
                prev = ptr;            
                ptr = ptr->lchild;           //otherwise left
            } 
        }
        if(prev->value < new->value) {       //putting the new node in position
            prev->rchild = new;
            }
        else {
            prev->lchild = new;
            }
    }
    else {
        root = new;                       //if root was null
        } 
    return;
}             
                                    
struct node search(){                     //for searching the values
    struct node *ptr;
    int input,flag=0;
    printf("Enter the integer to search: ");
    scanf("%d",&input);  
     
    if(root!=NULL) {
        ptr = root;
        while(ptr!=NULL) {
            if(input == ptr->value){      //if value is found
                printf("Found\n");     
                flag = 1;
                break;
                }
            else if(input > ptr->value) { //otherwise if greater than present node key, go to left 
                ptr = ptr->rchild;
                }
            else {
                ptr = ptr->lchild;        //otherwise left
                } 
        }
    } 
    if(flag == 0)                         //if value is not found
        printf("DOes not exist\n");
    return ;
}

struct node del2node(struct node *ptr){
    struct node *temp , *ptemp = NULL;
    temp = ptr->rchild;
    while(temp->lchild != NULL){    //finding the smallest in the right subtree
        ptemp = temp;
        temp = temp->lchild;
    }
    if(ptemp != NULL){
       ptr->value = temp->value;    //replacing the value to be deleted with the 
       ptemp->lchild = NULL;
       free(temp); 
       }
    else{
       //temp->lchild = ptr->lchild;
       if(ptr != root){
         struct node *storechild = ptr->lchild;
         ptr = temp; 
         ptr->lchild = storechild;
         }
       else{
         root = temp;
         root->lchild = ptr->lchild;
         } 
       }
    return;    
}

void delete(int input){
    struct node *dptr, *dpre = NULL;
    int flag = 0;
    
    if(root!=NULL) {          //searching for the value to be deleted
        dptr = root;
        while(dptr!=NULL) {
            if(input == dptr->value){
                flag = 1; 
                break;
                }
            else if(input > dptr->value) {
                dpre = dptr;              //and getting the corresponding node and its parent
                dptr = dptr->rchild;
                }
            else {
                dpre = dptr;
                dptr = dptr->lchild;
                } 
        }
    } 
    
    if(flag == 0){
      printf("Does not exist to delete\n");
      return;
    }  
    
    if(dptr != root && input == dptr->value){         //if the value to be deleted is not in root
        if(dptr->rchild == NULL && dptr->lchild == NULL){   //deleting leaf
            if(dpre->lchild == dptr){
                dpre->lchild = NULL;
                }
            else {
                dpre->rchild = NULL; 
                }
        }           
        else if(dptr->rchild == NULL && dptr->lchild != NULL) {   //if the node to be deleted has only left child
            if(dpre->lchild == dptr){
                dpre->lchild = dptr->lchild;
                }
            else {
                dpre->rchild = dptr->lchild; 
                }
        }
        else if(dptr->rchild != NULL && dptr->lchild == NULL) {   //if the node to be deleted has only right child
            if(dpre->lchild == dptr){
                dpre->lchild = dptr->rchild;
                }
            else {
                dpre->rchild = dptr->rchild; 
                }
        } 
        else if(dptr->rchild != NULL && dptr->lchild != NULL) { //if the node to be deleted has both children
            del2node(dptr);   //function to delete further
        }          
    }
    else if(dptr == root && input == dptr->value){       //if the value to be deleted is in root
        if(dptr->rchild == NULL && dptr->lchild == NULL) {  //root has no children
            root = NULL;
        }           
        else if(dptr->rchild == NULL && dptr->lchild != NULL) {   //root has only left child
            root = root->lchild;
        }
        else if(dptr->rchild != NULL && dptr->lchild == NULL) {  //root has only right child 
            root = root->rchild;
        }
        else if(dptr->rchild != NULL && dptr->lchild != NULL) {   //root has both children
            del2node(root);
        }             
    } 
    printf("value is deleted\n");
    return; 
}

int height(struct node *slot){         //functions for printing the values in the tree
    if(slot==NULL)
        return 0;
    else {
        int lheight = height(slot->lchild);     //finding the height, to print the level
        int rheight = height(slot->rchild); 
        if(lheight > rheight)
            return (lheight + 1);
        else
            return (rheight + 1);
        }           
}

void printLevel(struct node *slot, int level) {
    if(slot == NULL)
        return;
    if(level == 1)            //printing values in the leve;
        printf("%d  ",slot->value);
    else if(level > 1) {
        printLevel(slot->lchild,level-1);    //going to child nodes
        printLevel(slot->rchild,level-1);  
        }   
    return;
}        

void print(){           //prints in level order
    if(root == NULL)
        printf("No elements\n");
    else {    
        int d;
        for(d=1; d<=height(root); d++) {
            printLevel(root,d);     //going to each level from top
            printf("\n");
        }
    }        
    return;    
}

int main() {
	int entry;
    printf("Binary Search Tree.\n Enter 1 to Insert, 2 to Search, 3 to Delete and 4 to Print: ");
	scanf("%d",&entry);
	while(entry>=0 && entry<=4) {
		switch(entry) {
			case 1: {
				insert();      //insert
				break;
				}
			case 2: {         //search
				search();
				break;
				}
			case 3: {         //delete
			   int dinput;       
            printf("Enter the integer to delete: ");
            scanf("%d",&dinput);
				delete(dinput);
				break;
				}
			case 4: {
				print();          //level order print
				break;
				}
		}  
		printf("Enter 1 to Insert, 2 to Search, 3 to Delete and 4 to Print: ");
		scanf("%d",&entry);
	}
	printf("End of the program\n");
	return;
}        //end of the program
