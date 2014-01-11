
#include	"sorted-list.h"

int compareInts(void *p1, void *p2)
{
	int i1 = *(int*)p1;
	int i2 = *(int*)p2;
	return i1 - i2;
}

int compareDoubles(void *p1, void *p2)
{
	double d1 = *(double*)p1;
	double d2 = *(double*)p2;
    
	return (d1 < d2) ? -1 : ((d1 > d2) ? 1 : 0);
}

int compareStrings(void *p1, void *p2)
{
	char *s1 = p1;
	char *s2 = p2;
    
	return strcmp(s1, s2);
}

int main(){
    void* stuff;
    void *stuff2;   
    SortedListPtr list = SLCreate(&compareInts);
    int a = 12;
    int y = 5;
    int x = 3;
    int z = 1;
    int b = 7;
    SLInsert(list, &b);
    SLInsert(list, &a);
    SLInsert(list, &z);
    SLInsert(list, &y);
    SLInsert(list, &x);
    SortedListIteratorPtr iter = SLCreateIterator(list);
    SortedListIteratorPtr iter2 = SLCreateIterator(list);
    stuff = SLNextItem(iter);
    printf("returned by iterator1: %d\n", *(int*)stuff);
    stuff = SLNextItem(iter);
    printf("returned by iterator1: %d\n", *(int*)stuff);
    SLRemove(list, &b);
    SLRemove(list, &y);
    stuff = SLNextItem(iter);
    while(stuff != NULL){
        if(stuff != NULL){
            printf("returned by iterator1: %d\n", *(int*)stuff);
        }
        stuff = SLNextItem(iter);
        
    }
    stuff2 = SLNextItem(iter2);
    while(stuff2 != NULL){
        
        printf("returned by iterator2: %d\n", *(int*)stuff2);
        stuff2 = SLNextItem(iter2);
        
    }

    Node *curr;
    for(curr = list->front; curr != NULL; curr = curr->next){

        if(curr->data != NULL){

            printf("node data: %d\n", *(int*)curr->data);

        }
    }
    SLDestroyIterator(iter);
    SLDestroy(list);
    return 0;
}







