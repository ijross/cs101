//Provides driver program for hash.c
//
//by Ian Ross


#include <assert.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "list.h"
#include "hash.h"

long test= 1323243; 
long test1 = 2357943;
long test2 = 394328409;
long test3 = 428392;

int main(int argc, char **argv){
   int index;

   //Makes a new hashtable of size 10 and ensure the hashing function is working correctly
   hashRef hashtable = newHash(10);
   printf("%ld hashing to: %d\n",test,hashkey(10,test));
   printf("%ld hashing to: %d\n",test1,hashkey(10,test1));
   printf("%ld hashing to: %d\n", test2, hashkey(10,test2));
   printf("%ld hashing to: %d\n", test3,hashkey(10, test3));

   //testing hashtable insertion
   
   //Populatest list to insert into the hashtable 
   ListRef list = newlist();
   for(index = 0; index < 10; ++index){
      insertAfterLast(list,(long)index);
   }


 //hashes books and prints nothing
 //Used to print some debugging statements in hashlist and bookcountlist
 //but I took them out of the final prorgam
   insertbook(hashtable, test,list);   
   insertbook(hashtable, test1,list);
   insertbook(hashtable, test2,list);
   insertbook(hashtable, test3,list);

   freeHash(hashtable);
   freelist(list);    
 
   return 0; 
} 
