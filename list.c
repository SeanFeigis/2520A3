//Author: Sean Shaya Feigis
//October 15, 2020
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Performance *newPerformance() {
  struct Performance *perf;
  if ((perf = malloc(sizeof(struct Performance))) == NULL) {
    fprintf(stderr, "%s\n", "Error, malloc failed");
  }
  perf->reads=0;
  perf->writes=0;
  perf->mallocs=0;
  perf->frees=0;
  return perf;
}

void push (struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width) {
  struct Node *temp = (struct Node *) malloc(sizeof(struct Node));
  if (temp == NULL) { //Null malloc check
    fprintf(stderr, "%s\n", "Error, malloc failed");
    exit(0);
  }
  if ((temp->data = (void *) malloc(width) ) == NULL) { //Null malloc check
    fprintf(stderr, "%s\n", "Error, malloc failed");
    exit(0);
  }

  memcpy(temp->data,src,width); //Copy data to the new element

  temp->next = *list_ptr; //Attach the rest of the list to the node
  *list_ptr = temp; //Set the head to the new node

  performance->mallocs++;
  performance->writes++;
}


void readHead (struct Performance *performance, struct Node **list_ptr, void *dest, unsigned int width ) {
  if (*list_ptr == NULL) { //Null Pointer check
    fprintf(stderr, "%s\n", "Error, list empty");
    exit(0);
  } else {
    memcpy(dest, (*list_ptr)->data, width); //Copy the data to dest
    performance->reads++;
  }
}

void pop (struct Performance *performance, struct Node **list_ptr, void *dest, unsigned int width ) {
  if (*list_ptr == NULL) { //Null Pointer check
    fprintf(stderr, "%s\n", "Error, list empty");
    exit(0);
  }
  memcpy(dest, (*list_ptr)->data, width);  //Copy the data to dest
  struct Node *temp = *list_ptr; //create a temp to free later
  *list_ptr = (*list_ptr)->next; //move the head forward
  free(temp->data); //free the data and node
  free(temp);

  performance->frees++;
  performance->reads++;

}

struct Node **next( struct Performance *performance, struct Node **list_ptr) {
  if (*list_ptr == NULL) { //Null Pointer check
    fprintf(stderr, "%s\n", "Error, list empty");
    exit(0);
  }
  performance->reads++;
  return &((*list_ptr)->next);
}

int isEmpty (struct Performance *performance, struct Node **list_ptr) {
  if (*list_ptr == NULL) { //Null Pointer check
    return 1;
  } else {
    return 0;
  }
}

void freeList(struct Performance *performance, struct Node **list_ptr) {
  void *tempDest = malloc(sizeof(struct Node));
  while (!(isEmpty(performance, list_ptr))) { //run until empty
    pop(performance, list_ptr, tempDest, sizeof((*list_ptr)->data));
  }
  free(tempDest); //free the temp
}

void readItem( struct Performance *performance, struct Node **list_ptr, unsigned int index, void *dest, unsigned int width) {
  struct Node **temp = list_ptr;
  for(int i = 0; i < index ; i++) {
    temp = next(performance, temp); //iterate through the list
  }
  readHead(performance, temp, dest, width); //read the head into dest
}


void appendItem( struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width) {
  struct Node **temp = list_ptr;
  while(!(isEmpty(performance, temp))) {
    temp = next(performance, temp); //iterate through the list
  }
  push(performance, temp, src, width); //push the node at the end of the list
}

void insertItem( struct Performance *performance, struct Node **list_ptr, unsigned int index, void *src, unsigned int width) {
  struct Node **temp = list_ptr;
  for(int i = 0; i < index; i++) {
    temp = next(performance, temp); //iterate through the list
  }
  push(performance, temp, src, width); //push at the specified position in the list
}

void prependItem( struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width) {
  insertItem(performance, list_ptr, 0, src, width); //insert at position 0
}

void deleteItem(struct Performance *performance, struct Node **list_ptr, unsigned int index) {
  void *tempDest = malloc(sizeof(struct Node));
  struct Node **temp = list_ptr;
  for(int i = 0; i < index; i++) {
    temp = next(performance, temp); //iterate through the list
  }
  pop(performance, temp, tempDest, sizeof((*list_ptr)->data)); //remove the item
  free(tempDest); //free the temp
}


int findItem(struct Performance *performance, struct Node **list_ptr, int (*compar)(const void *, const void *), void *target, unsigned int width) {
  struct Node **temp = list_ptr;
  void *tempDest = malloc(width);
  int i = 0;

  while(!(isEmpty(performance, temp))) {
    readHead(performance, temp, tempDest, width); //read the head into tempDest
    if (!(compar(tempDest, target))) { //compare the items
      free(tempDest); //free temp
      return(i);
    } else {
      temp = next(performance, temp); //iterate through list
    }
    i++;
  }
  free(tempDest); //free temp
  return(-1);
}
