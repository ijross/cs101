//hash.c
//
//by Ian Ross
//
// Implements the hash table ADT intended to hash bookID's into a table of lists// Uses multiplication method for hashing 
//
//Uses CHAINING to resolve collisions using the hashlist ADT
//
// The hashtable will include a length, and an array of lists

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "list.h"
#include "hashlist.h"
#include "hash.h"

//Provides struct for hash table
//Provides a length, a load, and an array of lists intended to hold
//book ID's

struct hash{
   size_t length;
   HashListRef *hashlist;
};
   
//returns a new hash table given a size
//The size should be an integer and the size of the hash table array and
//the hashing function will depend on this size
hashRef newHash(size_t size){
   hashRef new = malloc(sizeof (struct hash));
   assert(new != NULL);
   new->length = size;
   new->hashlist = malloc(new->length * sizeof(HashListRef));
   size_t i;
   //initialize array to NULL
   for(i = 0; i < new->length; ++i){
      new->hashlist[i] = NULL;
   }
   return new;
}

//Provides function for hashing the bookID's into the hash array
//Uses the multiplication method for hasing which takes an integer
//between 0 and 1 and multiplies it by the bookID, takes the fractional part
//of that and mutiplies it by the size of the table
//It returns an integer where the ID is to be inserted into the array
int hashkey(size_t hashSize,long bookId){
  double a;
  int key;
 
  //obtain number between 0 and 1
  a = (sqrt(5)-1)/2;

  //Multiplies a by the bookID
  double code = (a) * (double)(bookId); 

  //Obtains fractional part of the code
  code = code - ((long)code);

  //Multiplies by the size of the hashtable
  code = (long)(hashSize * code); 

  //casts the code as an integer
  key = (int)code; 
  return key; 
}

//Provides function for freeing the memory allocated by the hashtable
void freeHash(hashRef h){
   size_t i;
   for(i= 0; i < h->length; ++i){
      HashListRef tmp = h->hashlist[i];
      freehashlist(h->hashlist[i]);
   }
//   memset(h->hashlist,0,h->length * sizeof(HashListRef));
   free(h->hashlist);
   memset(h,0,sizeof(struct hash));
   free(h);
} 

//A function used for obtaining a recommendation for a customer
//based upon a particular book ID
//Goes to a different function in hashlist to obtain that particular
//node's bookcountlist
void getRecommendation(hashRef h, long ID){
  int index = hashkey(h->length, ID);
   getMax( h->hashlist[index], ID);
}
  

//Inserts a book into a hash table and takes a list as an argument intended
//to add the copurchases the that nodes bookcount list
void insertbook(hashRef h, long ID, ListRef list){
   //Obtains hash index for spot of insertion
   int index = hashkey(h->length,ID);
   //If that list has not been created yet, allocate a new hashlist
   if(h->hashlist[index] == NULL){
      h->hashlist[index] = newhashlist();
   }
   //insert the ID at that particular hashlist and add the list to its 
   //bookcountlist
   insert(h->hashlist[index], ID,list);
}


