//booklistdr.c
//
//by Ian Ross
//
//Provides driver to make sure my bookcountlist is working correctly, adding 
//multiple nodes which should result in different counts
//Prints the max at the end

#include <assert.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "bookcountlist.h"

long test= 1323243; 
long test1 = 2357943;
long test2 = 394328409;
long test3 = 428392;

int main(int argc, char **argv){
   int index;

   //Makes a new list
   CountListRef new= newCountList();

   //Tests the insert function
   insertCount(new, test);  
   insertCount(new, test);
   insertCount(new, test);
   insertCount(new, test2);
   insertCount(new, test2);
 
   //Prints the max ID
   printf("max= %ld\n", getMaxCount(new));

   freeList(new); 
   return 0; 
} 
