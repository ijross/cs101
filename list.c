//list.c
//
//by Ian Ross
//
//Implements list ADT used for storing customer book purchases
//
//Mainly uses insertion sort to add customer ID's which will then be used in
//a hashtable to keep track of copurchases

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct Node *nodeRef;

struct List{
    nodeRef first;
    nodeRef last;
    nodeRef current;
};

struct Node{
   long data;
   nodeRef next;
   nodeRef prev;
};

//CONSTRUCTORS/DESTRUCTORS

////Structure for new list
ListRef newlist(void){
   ListRef list = malloc(sizeof (struct List));
   assert(list!= NULL);
   list->first = NULL;
   list->last = NULL;
   list->current = NULL;
   return list;
}

bool isList(ListRef list){
   if(list != NULL){
      return;
   }
   else return false;
}

////Method for freeing list
void freelist(ListRef list){
   if(list == NULL) return;
   list->current = list->first;
   while(list->current != NULL){
      nodeRef tmp = list->current;
      list->first = NULL;
      list->current = list->current->next;
      free(tmp);
   }
   free(list);
}   

////ACCESS FUNCTIONS
////returns true if list is empty else returns false
int isEmpty(ListRef list){
   assert(isList(list));
   if(list->first == NULL) return 1;
   else return 0;
} 
////returns true if current == null
int offEnd(ListRef list){
   if(list->current == NULL) return 1;
   else return 0;
}

////returns true if current == first and !offEND()
int atFirst(ListRef list){
   assert(isList(list));
   if(list->current==list->first) return 1;
   else return 0;
}

////returns true if current == last and !offend()
int atLast(ListRef list){
   assert(isList(list));
   if(list->current == list->last) return 1;
   else return 0;
}

////return the first element
long getFirst(ListRef list ){
   assert(isList(list));
   return  list->first->data;
   
}
   
////returns the last element
long getLast(ListRef list ){
   assert(isList(list));
   return list->last->data; 
}

////returns the current element  
long getCurrent(ListRef list){
//   assert(isList(list));
   return list->current->data;
}

////returns the length of the list as an integer
int getLength(ListRef list){
   assert(isList(list));
   int count = 0;
   list->current = list->first;
   while(list->current!= NULL){
      count++;
      list->current = list->current->next;
   }
   list->current = list->last;
   return count;
}

////return true iff the wo lists have the same keys in the same order
int equals(ListRef list1 , ListRef list2){
   assert(isList(list1));
   assert(isList(list2));
   int index = getLength(list1);
   int index2 = getLength(list2);
   if(index != index2){
      return 0;
   }
   else{
      while(list1->current != NULL){
         if(list1->current->data != list2->current->data){
            return 0;
         }
         else{
            list1->current= list1->current->next;
            list2->current = list2->current->next; 
         }
      }
   return 1;
   }
}   

////MANIPULATION PROCEDURES

////makes list empty
void makeEmpty(ListRef list){
   assert(isList(list));
   list->current = list->first;
   while(list->current != NULL){
      nodeRef tmp = list->current;
      list->first = NULL;
      list->current= list->current->next;
      //free(tmp->data);
      free(tmp);
   }
}
//
///sets current marker to the first element in the list
void moveFirst(ListRef list){
//   assert(isList(list));
   list->current = list->first;
}

//set current marker to the last element of the list
void moveLast(ListRef list){
   assert(isList(list));
   list->current = list->last;
}

//set current marker to the previous element
void movePrev(ListRef list){
   assert(isList(list));
   if(list->current->prev != NULL){
      list->current = list->current->prev;
   }
   else{
      fprintf(stderr, "Trying to move off list\n");
   }
}

////set current marker to the next element in the list
void moveNext(ListRef list){
//   assert(isList(list));
      list->current = list->current->next;
}

//inserts an element in sorted order
void insertionSort(ListRef list, long data){
   nodeRef new = malloc(sizeof(struct Node));
   new->data = data;
   if(list->first == NULL){
      list->first = list->last =list->current= new;
      new->prev = NULL;
      new->next = NULL;
      
   }
   else{
      list->current = list->first;
      while(list->current != NULL){
         if(list->current->data > new->data){
            if(list->current == list->first){
               new->next = list->current;
               list->current->prev = new;
               new->prev = NULL;
               list->current = list->first = new;
               break;
             }
             else{
               new->prev = list->current->prev;
               list->current->prev->next = new;
               list->current->prev = new; 
               new->next = list->current;  
               list->current = new;
               break;
             }
         }
         else{
            if(list->current == list->last){
               new->prev = list->current;
               list->current->next = new;
               new->next = NULL;
               list->last = list->current = new;
            }
            list->current = list->current->next;
         }
      }
   }  
}
////inserts a new element before first element
void insertBeforeFirst(ListRef list, long data){
   assert(isList(list));
   nodeRef new = malloc(sizeof(struct Node));
   new->data = data; 
   if(list->first == NULL){
      list->first = list->last = new;
      list->current = new;
      new->prev = NULL;
      new->next = NULL;
   }
   else{
      list->first->prev = new;
      new->prev = NULL;
      new->next = list->first; 
      list->first = list->current = new;
   }
}
   

////inserts a new element after the last element
void insertAfterLast(ListRef list, long data){
   assert(isList(list));
   nodeRef new = malloc(sizeof(struct Node));
   new->data = data;
   if(list->first== NULL){
      list->first= list->last = new;
      list->current = new;
   }
   else{
      list->last->next = new;
      new->prev = list->last;
      new->next = NULL;
      list->last = list->current = new;
   }
}

////inserts a new element before the current element
void insertBeforeCurrent(ListRef list, long data){
   assert(isList(list));
   nodeRef new = malloc(sizeof(struct Node));
   new->data = data;
   if(list->first == NULL){
      list->first = list->last = new;
      list->current = new;
   }
   else{
      if(list->current == list->first){
         new->prev = NULL;
         list->current->prev = new;
         new->next = list->current;    
         list->current = new;
         list->first = new;  
      }
      else{
         new->prev = list->current->prev;
         list->current->prev->next = new;
         list->current->prev = new;
         new->next = list->current;
         list->current = new;
      } 
   }
}

////inserts a new element after the current element
void insertAfterCurrent(ListRef list, long data){
   assert(isList(list));
   nodeRef new = malloc(sizeof(struct Node));
   new->data = data;
   if(list->first == NULL){
      list->first = list->last = new;
      list->current = new;
   }
   else{
      if(list->current == list->last){
         new->next = NULL;
         list->current->next = new;
         new->prev = list->current;
         list->current = new; 
         list->last = list->current;
      }
      else{ 
         new->next = list->current->next;
         list->current->next->prev = new;
         list->current->next = new;
         new->prev = list->current;
         list->current = new;
      }   
   }
}

////deletes the first element
void deleteFirst(ListRef list){
   assert(isList(list));
   list->current = list->first;
   if(list->first == list->last){
      nodeRef tmp = list->current;
      list->current = list->first = list->last = NULL;
    //free(tmp->data);
      free(tmp);
   }
   else{
      nodeRef tmp = list->current;
      list->current->next->prev = NULL;
      list->first = NULL;
      list->current = list->current->next;
      list->first = list->current;
    //free(tmp->data);
      free(tmp);
   }
}

////deletes the last element
void deleteLast(ListRef list){
   assert(isList(list));
   list->current = list->last;
   if(list->first==list->last){
      nodeRef tmp = list->current;
      list->current = list->first = list->last = NULL;
      //free(tmp->data);
      free(tmp);
   }
   else{
      nodeRef tmp = list->current;
      list->current->prev->next = NULL;
      list->last = NULL;
      list->current = list->current->prev;
      list->last = list->current;
      //free(tmp->data);
      free(tmp);
   }
}

////deletes the current element
void deleteCurrent(ListRef list){
   assert(isList(list));
   if(list->first == list->last){
      nodeRef tmp = list->current;
      list->current = list->last = list->first = NULL;
    //free(tmp->data);
      free(tmp);
   }
   else if(list->current == list->first){
     nodeRef tmp = list->current;
     list->current->next->prev = NULL;
     list->first = NULL;
     list->current = list->current->next;
     list->first = list->current;
    //free(tmp->data);
      free(tmp);
   }
   else if(list->current == list->last){
     nodeRef tmp = list->current;
     list->current->prev->next = NULL;
     list->last = NULL;
     list->current = list->current->prev;
     list->last = list->current;
     //free(tmp->data);
     free(tmp);
     }
   else{
      nodeRef tmp = list->current;
      list->current->prev->next = list->current->next;
      list->current->next->prev = list->current->prev;
      list->current = list->current->next;
      //free(tmp->data);
      free(tmp);
   }
}

////OTHER OPERATIONS
////prints list
void printList(ListRef list){
   list->current = list->first;
   while(list->current != NULL){
      printf("%ld   ", list->current->data);
      list->current = list->current->next;
   }
   printf("\n");
   list->current = list->last; 
}

////copies list
ListRef copyList(ListRef);


