//bookcountlist.h
////by Ian Ross
////
////Provides  bookcountlist ADT to store book copurchase pairs and how
////many times each list is copurchased.
////
////Intended to be used in the hashlist nodes so each bookID will contain
////the correct list of book count pairs.
//


#ifndef __BOOKCOUNTLIST_H__
#define __BOOKCOUNTLIST_H__

//Defines the BookCountList struct
typedef struct BookCountList *CountListRef;

//To be called when making a new hashlist node, will give that node
//a new bookcountlist to store bookcount pairs
CountListRef newCountList(void);

//Frees memory allocated by making a new bookcountlist
void freeList(CountListRef);

//Should take a countlist in a hashlist and an ID
//Takes an ID and if it is already in the list, its count will increase
//and if it is not it will be added to the list
void insertCount(CountListRef,long);

//Returns max count in the list
//To be called when trying to obtain a recommendation
//Will return an ID which is to be recomended to the customer
long getMaxCount(CountListRef);

#endif
