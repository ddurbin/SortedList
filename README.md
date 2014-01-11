SortedList
==========
This program implements a sorted list of opaque type objects.

*Special notes*
	-Our code allows for duplicates to be inserted into the list.  When a duplicate is to be removed, the first instance of the duplicate is removed.  
	-In the case where the list is {12,7,5} and SLNextItem is called twice returning 12 and 7, the iterator will be pointing to 5, so if any item is added to the list greater than 5, it will not be returned until a new iterator is created.

Functions:

SLCreate:
	This method just allocates memory for a new sorted-list.  It is done in O(1) time.

SLDestroy:
	This method traverses through the linked list, freeing each node as it goes.  After that it free's the memory allocated when the list was first created.  Free the linked list is done in O(n) time and freeing the list is just O(1) time, making this method O(n) overall.

SLInsert:
	This method starts by allocating memory for a new node and sets that nodes data to the given object.  This is done in O(1) time.  Then, starting at the front of the list, it begins to compare the data in the new node to the data in the current nodes until it finds the location in the list the new node should be placed so that the list maintains sorted order.  For the worst case scenario, the new node would be the last item in the list.  In this case, it would take n comparisons to figure out where the node should be inserted, so the running time would be O(n).

SLRemove:
	This method starts at the beginning of the list and then compares the given object to the objects held by the nodes, starting at the front, looking for a match so that node can be removed from the list.  If a match if found, if there is no iterators pointing to the node, that node is freed.  If there is one or more iterators pointing to the node, the node is not freed right away, but it will not be returned by an iterator, the iterator will just skip over and go to the next node in the list. The worst case for this method, is if the item being searched for to remove is not in the list.  Then the given object will be compared to every node in the list.  In this case, there would be n comparisons making for an O(n) run time.

SLCreateIterator:
	This method just allocates memory for a new iterator, points that iterator at the front of the list, and increments the reference pointer count of the front node.  This is done on O(1) time.

SLDestroyIterator:
	This method just free's the memory that was allocated for the given iterator.  It is done in O(1) run time.

SLNextItem:
	This method checks if the node it is currently pointing to has been removed or not.  If it hasn't been, it returns a void pointer to the nodes data, and then iterates to the next node.  If it has been removed, it iterates to the next node in the list and decrements the reference pointer count of the node it just moved from.  If that count is then zero, it free's that node.  Then it checks to see if the node it just moved to has been deleted or not. 
	The worst case scenario for this method would be if the iterator was on a node that has been removed.  Then it would iterate to the next node and return a pointer to that nodes data or return null if there was no next node.  Since when a node is deleted, the node before has its pointer pointed around the removed node, an iterator will never run into multiple removed nodes in a row.  The run time for this method is O(1).
