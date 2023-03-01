// do not include other libraries
#include <stdio.h>
#include <stdlib.h>

// Struct to be used for nodes
typedef struct NODE {
	int data; 
	struct NODE* next;
} NODE; // nodes of the linked list
typedef struct LINKED_LIST {
	struct NODE *head;
} LINKED_LIST; // struct to act as the head of the list


// this function returns a LINKED_LIST struct to
// act as the head of the linked list.
// do not change this function
LINKED_LIST Create_List(void) {
	LINKED_LIST list = {NULL}; 
	return list;
}

// call this function to verify malloc worked when you create new nodes
void Verify_Malloc(NODE *node) {
	if (node == NULL) {
		printf("Malloc Failed\n"); 
		exit(1);
	}
       	return;
}

// this function prints out all of the nodes in the linked list
void Print_List(FILE *out, LINKED_LIST list) {
    if (list.head == NULL) {printf("\n"); return;} //empty list
    NODE *current = list.head;
    while (current->next != NULL) {
        fprintf(out, "%d -> ",current->data);
        current = current->next;
    }
    fprintf(out, "%d\n",current->data);
    return;
}

// this function returns the number 
// of elements in the linked list
int Size(LINKED_LIST list){
    // create size tracker
    int size = 0;

    // traverse through the list and increment
    // size at each node
    NODE *cur = list.head;
    while(cur != NULL){
        size++;
	cur = cur->next;
    }

    return size;
}

// this function adds an element to
// the front of the list
void Push_Front(LINKED_LIST *list, int data){
	    // create a new node
    NODE *new_node = malloc(sizeof(NODE));
    new_node->data = data;
    new_node->next = list->head;

    //reassign the head
    list->head = new_node;

    return;	
}

// this function adds an element 
// to the end of the linked list 
void Push_Back(LINKED_LIST *list, int data) {
    // check is list is empty
    if (list->head == NULL){
        Push_Front(list, data);
    }

    // if not empty
    else{
        NODE *cur = list->head;
        // traverse the tree
        while(cur->next != NULL){
            cur = cur->next;
        }
        // create the new node
        NODE *new_node = malloc(sizeof(NODE));

        // assign the node ot the data and make the next NULL
        new_node->data = data;
        new_node->next = NULL;
        cur->next = new_node;
    }
    return;
}


// if the list is not empty
// the value of the first element of the list is returned by reference in the parameter data
// the first element of the list is deleted
// returns 0 if the list is empty otherwise returns 1
// remember to free the deleted node
int Pop_Front(LINKED_LIST *list, int *data) {
    // check if the list is empty
    if (list->head == NULL){
	return 0;
    }

    else{
    // pop the first element
    NODE *temp = list->head;
    *data = temp->data;
    list->head = list->head->next;
    free(temp);
    return 1;
    }

    return 0;
}


// if the list is not empty
// the value of the last element of the list is returned by reference in the parameter data
// the last element of the list is deleted
// returns 0 if the list is empty otherwise returns 1
// remember to free the deleted node
int Pop_Back(LINKED_LIST *list, int *data) {
   // check if the list is empty
   if (list->head == NULL){
	   return 0;
   }

   // if there is one node, pop it
   if (list->head->next == NULL){
	   *data = list->head->data;
	   free(list->head);
	   list->head = NULL;
	   return 1;
   }

   // otherwise, delete back node
	   NODE *cur = list->head;
	   NODE *prev = list->head;

	   while(cur->next != NULL){
		   prev = cur;
		   cur = cur->next;
	   }
	   *data = cur->data;
	   prev->next = NULL;
	   free(cur);
	   return 1;
}

// this function returns the number 
// of times that the value of the parameter 
// data appears in the list
int Count_If(LINKED_LIST list, int data) {
       // start count of times data is found
    int count = 0;
    
    // check for empty list
    if (list.head == NULL){
	    return count;
    }

    // traverse through the list and increment count when if codition is met
    NODE *cur = list.head;
    while(cur->next != NULL){
        if (cur->data == data){
            count++;
        }
        cur = cur->next;
    }
    return count;
}

// delete the first node containing the data value
// return 1 if something was deleted otherwise 0
// remember to free the deleted node
int Delete(LINKED_LIST *list, int data) {
     // check if list is empty and do nothing if so
    if (list->head == NULL){
        return 0;
    }

    // check if the only node is the node
    if (list->head->next == NULL){
        if (list->head->data == data){
            free(list->head);
            list->head = NULL;
            return 1;
        }
    }

    // deleting the first element
    if (list->head->data == data){
	    NODE *to_delete = list->head;
	    list->head = to_delete->next;
	    free(to_delete);
	    return 1;
    }

    // if there is more than one node, find it
    NODE *cur = list->head;
    NODE *last = cur;
    while (cur->next != NULL){
	if (cur-> data == data){
		last->next = cur->next;
		free(cur);
		return 1;
	}
	last = cur;
	cur = cur->next;
    }

    // remove last node
    NODE *node = list->head;
    NODE *prev = list->head;

           while(node->next != NULL){
                   prev = node;
                   node = node->next;
           }
	if (node->data == data){
           prev->next = NULL;
           free(cur);
           return 1;
	}

    return 0;
   
}

// return 1 if the list is empty otherwise returns 0
int Is_Empty(LINKED_LIST list) {
	int result;
       // check head to see if list is empty
    if (list.head == NULL){
        result =  1;
    }
    else{
        result =  0;
    }
	return result;
}

// delete all elements of the list
// remember to free the nodes
void Clear(LINKED_LIST *list) {
    // traverse through list
    NODE *cur = list->head;
    NODE *nextElement;
    while(cur != NULL){
	    nextElement = cur->next;
	    free(cur);
	    cur = nextElement;
    }
    list->head = NULL;
    return; 
}


// if an element appears in the list 
// retain the first occurance but
// remove all other nodes with the same 
// data value
void Remove_Duplicates(LINKED_LIST *list) {
    NODE *cur = list->head;
    NODE *temp = NULL;
    NODE *position = NULL;

    if (list->head == NULL){
        return;
    }

    // traverse through the list
    while(cur != NULL){
        temp = cur;
        position = cur->next;

        // traverse until index is null
        while(position != NULL){
            // check if data is the same
            if (cur->data == position->data){
                temp ->next = position->next;
		free(cur);
            }
            // otherwise keep the same
            else{
                temp = position;
            }
            position = position->next;
        }
        cur = cur->next;

    }

    return;
}


// modify main to completely test your functions 
int main() {
    // create a linked list
    printf("creating linked list\n");
    LINKED_LIST list = Create_List();
   
    // add some data (hardcoded for testing)
    printf("hardcoding some data\n");
    NODE *first  = malloc(sizeof(NODE)); Verify_Malloc(first);
    NODE *second = malloc(sizeof(NODE)); Verify_Malloc(second);
    first->data  = 1;
    second->data = 2;
    list.head = first;
    first->next = second;
    second->next = NULL;

    // print the list
    printf("Testing Print_List\n");
    Print_List(stdout, list);

    // write a better test for Size
    printf("Testing Size\n");
    printf("size = %d\n",Size(list));

    // write a better test for Push_Front
    printf("Testing Push_Front\n");
    Push_Front(&list, 0);
    Print_List(stdout, list);
    
    // write a better test for Push_Back
    printf("Testing Push_Back\n");
    Push_Back(&list, 3);
    Print_List(stdout, list);

    // write a better test for Pop_Front
    printf("Testing Pop_Front\n");
    {
        int x; 
        int not_empty = Pop_Front(&list, &x);
        if (not_empty) {
            printf("Element popped was %d\n",x);
            Print_List(stdout, list);
            printf("size = %d\n",Size(list));
        }
        else 
            printf("List was empty\n");
    }

    // write a better test for Pop_Back
    printf("Testing Pop_Back\n");
    {
        int x; 
        int not_empty = Pop_Back(&list, &x);
        if (not_empty) {
            printf("Element popped was %d\n",x);
            Print_List(stdout, list);
            printf("size = %d\n",Size(list));
        }
        else 
            printf("List was empty\n");
    }

    // write a beter test for Count_If
    printf("Testing Count_If(5)\n");
    Push_Front(&list, 5);
    Push_Front(&list, 5);
    Print_List(stdout, list);
    printf("5 count = %d\n",Count_If(list, 5));
    
    // write a test for Delete 
    printf("Testing Delete(1)\n");
    Print_List(stdout, list);
    Delete(&list, 1); 
    Print_List(stdout, list);

    // write a better test for Is_Empty
    printf("Testing Is_Empty\n");
    if (Is_Empty(list)) printf("List is Empty\n"); else printf("List is not empty\n");
    
    // write a better test for Clear
    printf("Testing Clear (list should be empty)\n");
    Clear(&list);
    if (Is_Empty(list)) printf("List is Empty\n"); else printf("List is not empty\n");
    return 0;
}
