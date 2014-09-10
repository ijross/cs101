//ADT for hashtable
//******list.h must be included BEFORE hash.h!!!*********
//
//by Ian Ross
//
//ADT module for the hash table intended to hash BookID's into a table of 
//lists.
//Will use multiplcation method for hashing


#ifndef __Hash_H_
#define __Hash_H__

#include <stdbool.h>
#include "list.h"

//Defines structure for the hashtable
typedef struct hash *hashRef;

//Function to create a hash table
//Takes in a size as an integer which will be used to allocate a large
//enough array of lists and will also be used for the hashing function
hashRef newHash(size_t);

//Function to hash a bookID to find the place of insertion in the table
//Will use the multiplication method for hashing
int hashkey(size_t, long);

//Function to free memory allocated by the hash table
void freeHash(hashRef);

//Funtion to return a recommendation given a purchase and a hashtable
//Will call another function in hashlist to actually print the rec
void getRecommendation(hashRef,long);

//Function to insert a book into the hashlist and add its copurchase list
//into that node's bookcountlist
void insertbook(hashRef, long, ListRef);


#endif 
