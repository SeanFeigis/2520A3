//Author: Sean Shaya Feigis
//October 15, 2020
//Header file for Assignment 3
#ifndef     _LIST_H
#define     _LIST_H


//Struct Definitions
struct Node
{
  void *data;
  struct Node *next;
};

struct Performance
{
  unsigned int reads;
  unsigned int writes;
  unsigned int mallocs;
  unsigned int frees;
};

//Function declarations
struct Performance *newPerformance() ;
void push (struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width);
void readHead (struct Performance *performance, struct Node **list_ptr, void *dest, unsigned int width );
void pop (struct Performance *performance, struct Node **list_ptr, void *dest, unsigned int width );
struct Node **next( struct Performance *performance, struct Node **list_ptr);
int isEmpty (struct Performance *performance, struct Node **list_ptr);
void freeList(struct Performance *performance, struct Node **list_ptr);
void readItem( struct Performance *performance, struct Node **list_ptr, unsigned int index, void *dest, unsigned int width);
void appendItem( struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width);
void insertItem( struct Performance *performance, struct Node **list_ptr, unsigned int index, void *src, unsigned int width);
void prependItem( struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width);
void deleteItem(struct Performance *performance, struct Node **list_ptr, unsigned int index);
int findItem(struct Performance *performance, struct Node **list_ptr, int (*compar)(const void*, const void *), void *target, unsigned int width);

#endif /* <array.h> included */
