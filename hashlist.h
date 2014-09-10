//ADT for the list that is to be used in the array of the hashtable
//****list.h must be included BEFORE hashlist.h!!!!*********
//
//hashlist.h 
//
//by Ian Ross
//
//hashlist provides the method of chanining to resolve collisions in the 
//hash table
//
//Makes a new node for each newly hashed book ID and for each node,
//makes a bookcountlist as a field in the hashlist node.
//


#ifndef __HASHLIST_H__
#define __HASHLIST_H__

#include "list.h"

//defines hashlist struct
typedef struct HashList *HashListRef;

//Provides function to make a new hashlist
//needs to have an ID already hashed to be called
HashListRef newhashlist(void);

//provides function to free memory allocated by hashlist
//needs a hashlist to have been created
void freehashlist(HashListRef);

//Responsible for printing the recomendation to the customer
//gets the max to produce a recommendation, needs a hashlist and an ID
//to be looked up
void getMax(HashListRef, long);

//inserts the ID into the hashlist as well as puts the customer list
//into the bookcountlist to keep track of copurchases
void insert(HashListRef,long,ListRef);

#endif
