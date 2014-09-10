//list.h
//
//by Ian Ross
//
//Provides module for list functions to be used to add, delete things
//from a generic linked list

#ifndef __LIST_H__
#define __LIST_H__

//CONSTRUCTORS/DESTRUCTORS
//
typedef struct List *ListRef;

//Structure for new list
ListRef newlist(void);


//Method for freeing list
void freelist(ListRef L );

//ACCESS FUNCTIONS
//
//returns true if list is empty else returns false
int isEmpty(ListRef );

//returns true if current == null
int offEnd(ListRef );

//returns true if current == first and !offEND()
int atFirst(ListRef );

//returns true if current == last and !offend()
int atLast(ListRef );

//return the first element
long getFirst(ListRef );

//returns the last element
long getLast(ListRef );

//returns the current element  
long getCurrent(ListRef );

//returns the length of the list as an integer
int getLength(ListRef );

//return true iff the wo lists have the same keys in the same order
int equals(ListRef , ListRef );

//MANIPULATION PROCEDURES
//
//makes list empty
void makeEmpty(ListRef);

//sets current marker to the first element in the list
void moveFirst(ListRef);

//set current marker to the last element of the list
void moveLast(ListRef);

//set current marker to the previous element
void movePrev(ListRef);

//set current marker to the next element in the list
void moveNext(ListRef);

//inserts a new element before first element
void insertBeforeFirst(ListRef, long data);

//inserts a new element after the last element
void insertAfterLast(ListRef, long data);

//inserts a new element before the current element
void insertBeforeCurrent(ListRef, long data);

//inserts a new element after the current element
void insertAfterCurrent(ListRef, long data);

//deletes the first element
void deleteFirst(ListRef);

//deletes the last element
void deleteLast(ListRef);

//deletes the current element
void deleteCurrent(ListRef);

//OTHER OPERATIONS
//prints list
void printList(ListRef);

//copies list
ListRef copyList(ListRef);


#endif
