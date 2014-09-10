//bookcountlist.c
//by Ian Ross
//
//Implements the bookcountlist ADT to store book copurchase pairs and how
//many times each list is copurchased.
//
//Intended to be used in the hashlist nodes so each bookID will contain
//the correct list of book count pairs. 
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "bookcountlist.h"

typedef struct CountNode *CountNodeRef;

//Provides typical list structure to bookcountlist
struct BookCountList{
   CountNodeRef first;
   CountNodeRef last;
   CountNodeRef current;
};

//Each node will countain both a bookID to serve as the key and a count
//which will count how many times a particular book has been added
//to the list. If a book is in the list, it will not be added again
struct CountNode{
   int count;
   long bookID;
   CountNodeRef next;
   CountNodeRef prev;
}; 
   
//To be called when making a new hashlist node, will give that node
//a new bookcountlist to store bookcount pairs
CountListRef newCountList(void){
   CountListRef new = malloc(sizeof( struct BookCountList));
   new->first = NULL;
   new->last = NULL;
   new->current = NULL;
   return new;
}

//Frees memory allocated by newCountlist
void freeList(CountListRef list){
   if(list == NULL) return;
   list->current = list->first;
   while(list->current != NULL){
      CountNodeRef tmp = list->current;
      list->first = NULL;
      list->current = list->current->next;
      free(tmp);
   }
   free(list);
}

//L should be a list and an ID is to be inserted
//Takes an ID and if that ID is already in the list, adds one to that ID's 
//count. Otherwise it adds that ID to the last and makes it of count 1
void insertCount(CountListRef L,long ID){
   L->current = L->first;
  //If the ID is in the list, add 1 to its count
   while(L->current != NULL){
      if(L->current->bookID == ID){
         L->current->count++;
         return;
      }
      L->current = L->current->next;
    }
   
   //book is not in the list, a new node is added
   CountNodeRef new = malloc(sizeof(struct CountNode));
   new->count = 1;
   new->bookID = ID; 

  //if list is empty, add it to the front
   if(L->first == NULL){
      L->first = L->last = new;
      L->current = new;
   }
  
   //If list is not empty, add it to the end
   else{
      L->last->next = new;
      new->prev = L->last;
      new->next = NULL;
      L->last = L->current = new;
   }
}

//Returns the max count in the list,
//To be called when trying to get a recommendation
//Will return an ID which is to be recommendeded to the customer
long getMaxCount(CountListRef list){
   list->current = list->first;
   long max;
   int count = 0;

   //Goes through list comparing counts to the max count, if the count
   //is greater, the new node becomes to max
   while(list->current != NULL){
      if(list->current->count > count){
         max = list->current->bookID;
         count = list->current->count;
      }
      list->current = list->current->next;
   }
   
   //max is returned
   return max;
}



  
