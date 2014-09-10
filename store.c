//store.c
//
//USAGE:  store [filename]
//
//by Ian Ross
//
//implements the hash table and stores customers purchases
//as well as a list of copurchases associated with each book
//in order to offer a recommendation to a custoemr based upon
//the books most frequently bought with a particular item
//
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "list.h"
#include "hash.h"

int main(int argc, char **argv){
   long data;
   int id,i,action;
   FILE *file;
   if(argc >1){
      file = fopen(argv[1], "r");
      int numberCust;
      int numberPur;
      int sizeofHash;
      ListRef* lists;

      //scans and gets number of customers and purchases
      fscanf(file, "%d", &numberCust);
      fscanf(file, "%d", &numberPur);
      fscanf(file, "%d", &sizeofHash);     

      //makes correct number of lists for number of customers
      lists = malloc(numberCust * sizeof (ListRef));
      hashRef hashtable = newHash(sizeofHash);

      //goes through and allocates correct purchases to Cust ID
      for(i = 0; i < numberPur ; ++i){
         fscanf(file, "%d", &id);
         fscanf(file, "%ld", &data);
         fscanf(file, "%d", &action);

         if(lists[id-1] == NULL){
            lists[id-1] = newlist();
         }
         insertionSort(lists[id-1], data);
         insertbook(hashtable, data, lists[id-1]);
         if(action == 1){
            getRecommendation(hashtable,data);
         }
      }
  
      fclose(file);


       for(i = 0; i < numberCust; ++i){
           freelist(lists[i]);
       }
      free(lists);
      freeHash(hashtable);
   }
   else{
      fprintf(stderr, "Please specify a file name\n");
   }
   return 0;
}
