//hashlist.c
//
//Implements ADT used for chaining the the hash.c file
//
//Creates a list that contains bookID's which each contain
//their own list of bookcounts to keep track of copurchases

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "bookcountlist.h"
#include "hashlist.h"
#include "list.h"


//Defines struct for the nodes in the hashlist
typedef struct ListNode *NodeRef;

//outlines hashlist struct
struct HashList{
   NodeRef first;
   NodeRef last;
   NodeRef current;
};

//Provides the struct for each node in the hashlist
struct ListNode{
   long bookID;
   CountListRef list;
   NodeRef next;
   NodeRef prev;
};

//Creates a newhashlist
//An ID should have already been hashed and then then is creating the 
//actual list
HashListRef newhashlist(void){
   HashListRef hashlist = malloc(sizeof (struct HashList));
   assert(hashlist != NULL);
   hashlist->first = NULL;
   hashlist->last = NULL;
   hashlist->current = NULL;
   return hashlist;
}

//Frees memory allocated by a hashlist
void freehashlist(HashListRef hashlist){
   if(hashlist == NULL) return;
   hashlist->current = hashlist->first;
   while(hashlist->current != NULL){
      NodeRef tmp = hashlist->current;
      hashlist->first= NULL;
      freeList(hashlist->current->list);
      hashlist->current = hashlist->current->next;
      free(tmp);
   }
   free(hashlist);
} 

//Function responsible for printing the recommendation to the customer
//takes a list and an ID and returns the bookcountlist associated with
//that particular ID
void getMax(HashListRef h, long ID){
   h->current = h->first;
   long max;
   while(h->current != NULL){
      if(h->current->bookID == ID){
         max = getMaxCount(h->current->list);
         break;
      }
      else h->current = h->current->next;
   }
   printf("Customers buying %ld also bought %ld\n", h->current->bookID, max);
}

//Inserts a new ID into the hashlist
//If the ID already exists in the hashlist it will simply 
//add to that ID's bookcount list by going trhough the customer
//purchases and adding them to the list
void insert(HashListRef h,long ID, ListRef custlist){
   h->current = h->first;
  
   //if the ID is in the list, modify the bookcount list
   while(h->current != NULL){
      if(h->current->bookID == ID){
         moveFirst(custlist);
          while(offEnd(custlist) != 1){
           
             //Add everything in the customer list to the bookcount
             //list except for the newly added ID
             if(getCurrent(custlist) != h->current->bookID){
                insertCount(h->current->list,getCurrent(custlist));
                moveNext(custlist);
             }
             else moveNext(custlist);
          }
          return;
      }
      else h->current = h->current->next;
   }

   //ID is not in the list so make a new node
   NodeRef new = malloc(sizeof(struct ListNode));
   new->bookID = ID;

   //Gives new node a new count list
   new->list = newCountList();
   moveFirst(custlist);

   //copies customerlist into the bookcount list
   while(offEnd(custlist) != 1){
      if(getCurrent(custlist) != new->bookID){
         insertCount(new->list,getCurrent(custlist));
         moveNext(custlist);
      }
      else moveNext(custlist);
   }

   //inserts node into thel ist
   new->next = new->prev = NULL;
   if(h->first == NULL){
      h->first = h->last = new;
      h->current = new;
   }
   else{
      h->last->next = new;
      new->prev = h->last;
      new->next = NULL;
      h->last = h->current = new;
   }
}

