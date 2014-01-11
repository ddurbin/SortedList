
#include "sorted-list.h"

SortedListPtr SLCreate(CompareFuncT cf){
    SortedListPtr list = (SortedListPtr)malloc(sizeof(SortedListPtr));
    list->front = NULL;
    list->size = 0;
    list->comparator = cf;
    return list;
}


void SLDestroy(SortedListPtr list){
    Node *temp, *next;
    for(temp = list->front; temp != NULL; temp = next){ //loop through list and set each field to NULL
        next = temp->next;
        temp->data = NULL;
        temp->boolean = 0;
        temp->next = NULL;
        free(temp); //free node
    }
    free(list); //free the  SortedPtrList structure
}


int SLInsert(SortedListPtr list, void *newObj){
    if(newObj == NULL){ //if newObj argument is NULL
        return 0;
    }
    Node *newNode = (Node*)malloc(sizeof(Node)); //Create new Node and initialize all fields
    newNode->data = newObj;
    newNode->next = NULL;
    newNode->refCount = 1;
    newNode->boolean = 1;
    
                                //insert new node into list in sorted order
    if(list->size == 0){        //when the list is empty
        list->front = newNode;
        list->size++;
        return 1;
    }
                                //when the list is not empty
    Node *curr = list->front;
    Node *prev = NULL;
    int compare;
    while(curr != NULL){    //loop through list and find position for new node
        compare = list->comparator(newNode->data, curr->data); //void type compare function
        if(compare >= 0){   // New node is larger than curr Node, will be inserted in front of curr node
            if(prev == NULL){   //New node must be placed in front of the list
                newNode->next = list->front;
                list->front = newNode;
                list->size++;
                return 1;
            } else {    //New node will be placed inside of the list
                prev->next = newNode;
                newNode->next = curr;
                list->size++;
                return 1;
            }
        } else if(curr->next == NULL){  // New node wil be placed at the end of the list
            curr->next = newNode;
            list->size++;
            return 1;
        }
        prev = curr;    //increment the pointers to the next nodes respectively
        curr = curr->next;
    }
    
    return 0;
}


int SLRemove(SortedListPtr list, void *newObj){
    Node *curr;
    Node *prev = NULL;
    int compare;
    for(curr = list->front; curr != NULL; curr = curr->next){   //Loop through the list
        compare = list->comparator(curr->data, newObj);
        if(compare == 0){   //node data and object to be removed match
            curr->boolean = 0;  
            curr->refCount--;   
            if(curr == list->front && list->front->next != NULL){ //Node to be removed is in front of the list
                list->size--;
                list->front = curr->next;
                list->front->refCount++;
                if(curr->refCount == 0){    //if Node has no more reference pointers, free it
                    list->front->refCount--;
                    free(curr);
                }
                return 1;
            }
            else if(curr == list->front && list->front->next == NULL){  //Node to be removed is the only node int he list
                Node *tempPtr = list->front;
                list->front = NULL;
                free(tempPtr);
                list->size--;
                return 1;
            }
            else if(curr->next == NULL){    //Node to be removes is the last in the list
                prev->next = NULL;
                list->size--;
                if(curr->refCount == 0){    //if Node has no more reference pointers, free it
                    free(curr);
                }
                return 1;
            }
            else {     //Node is somewhere in the middle of the list
                prev->next = curr->next;
                list->size--;
                if(curr->refCount == 0){
                    free(curr);
                }
                return 1;
            }
        }
        prev = curr;
    }
    return 0;
}


SortedListIteratorPtr SLCreateIterator(SortedListPtr list){
    SortedListIteratorPtr iter = (SortedListIteratorPtr)malloc(sizeof(SortedListIteratorPtr));
    if(list->front != NULL){    //initialize the iter
        iter->ptr = list->front;
        list->front->refCount++;
        return iter;
    }
    return NULL;  
}


void SLDestroyIterator(SortedListIteratorPtr iter){
    free(iter); //free iter
}


void *SLNextItem(SortedListIteratorPtr iter){
   Node *tempPtr = (Node*)malloc(sizeof(Node));
    tempPtr = iter->ptr;
    void *tempVoid;
    while(iter->ptr != NULL){   //loop through the list to find the first node that has valid data
        if(iter->ptr->boolean != 0){    //Node has NOT been removed from the list
            iter->ptr->refCount--;
            tempVoid = iter->ptr->data; //store the void data to be returned
            iter->ptr = iter->ptr->next; //move iter to next node
            if(iter->ptr != NULL){  //if node is not NULL increment the iter refCount, since iter is now pointing to it
                iter->ptr->refCount++;
            }
            return tempVoid;    //return the nextItem
        }
        if(iter->ptr->boolean == 0){    //Node has been removed from the list **Don't return it's data**
            iter->ptr->refCount--;
            iter->ptr = iter->ptr->next;
            if(tempPtr->refCount == 0){ //if refernce pointers to Node is 0, free node
                free(tempPtr);
            }
        }
        tempPtr = iter->ptr;    //increment tempPtr to next node
    }
     
    return NULL;
}
