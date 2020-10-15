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
  if (temp == NULL) {
    fprintf(stderr, "%s\n", "Error, malloc failed");
    exit(0);
  }
  if ((temp->data = (void *)malloc(sizeof(width))) == NULL) {
    fprintf(stderr, "%s\n", "Error, malloc failed");
    exit(0);
  }

  memcpy((char *)temp->data,src,width);

  temp->next = *list_ptr;
  *list_ptr = temp;

  performance->mallocs++;
  performance->writes++;
}


void readHead (struct Performance *performance, struct Node **list_ptr, void *dest, unsigned int width ) {
  if (*list_ptr != NULL) {
    memcpy(dest,(char *) (*list_ptr)->data, width);
    performance->reads++;
  } else {
    fprintf(stderr, "%s\n", "Error, list empty");
    exit(0);
  }
}

void pop (struct Performance *performance, struct Node **list_ptr, void *dest, unsigned int width ) {
  if (*list_ptr == NULL) {
    fprintf(stderr, "%s\n", "Error, list empty");
    exit(0);
  }
  memcpy(dest, (*list_ptr)->data, width);
  struct Node *temp = *list_ptr;
  *list_ptr = (*list_ptr)->next;
  free(temp->data);
  free(temp);

  performance->frees++;
  performance->reads++;

}

struct Node **next( struct Performance *performance, struct Node **list_ptr) {
  if (*list_ptr == NULL) {
    fprintf(stderr, "%s\n", "Error, list empty");
    exit(0);
  }
  performance->reads++;
  return &((*list_ptr)->next);
}

int isEmpty (struct Performance *performance, struct Node **list_ptr) {
  if (*list_ptr == NULL) {
    return 1;
  } else {
    return 0;
  }
}

void freeList(struct Performance *performance, struct Node **list_ptr) {
  void *tempDest = malloc(sizeof(struct Node));
  while (!(isEmpty(performance, list_ptr))) {
    pop(performance, list_ptr, tempDest, sizeof((*list_ptr)->data));
  }
  free(tempDest);
}

void readItem( struct Performance *performance, struct Node **list_ptr, unsigned int index, void *dest, unsigned int width) {
  struct Node **temp = list_ptr;
  for(int i = 0; i < index ; i++) {
    temp = next(performance, temp);
  }
  readHead(performance, temp, dest, width);
}


void appendItem( struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width) {
  struct Node **temp = list_ptr;
  while(!(isEmpty(performance, temp))) {
    temp = next(performance, temp);
  }
  push(performance, temp, src, width);
}

void insertItem( struct Performance *performance, struct Node **list_ptr, unsigned int index, void *src, unsigned int width) {
  struct Node **temp = list_ptr;
  for(int i = 0; i < index; i++) {
    temp = next(performance, temp);
  }
  push(performance, temp, src, width);
}

void prependItem( struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width) {
  insertItem(performance, list_ptr, 0, src, width);
}

void deleteItem(struct Performance *performance, struct Node **list_ptr, unsigned int index) {
  void *tempDest = malloc(sizeof(struct Node));
  struct Node **temp = list_ptr;
  for(int i = 0; i < index; i++) {
    temp = next(performance, temp);
  }
  pop(performance, temp, tempDest, sizeof((*list_ptr)->data));
  free(tempDest);
}


int findItem(struct Performance *performance, struct Node **list_ptr, int (*compar)(const void *, const void *), void *target, unsigned int width) {
  struct Node **temp = list_ptr;
  void *tempDest = malloc(width);
  int i = 0;

  while(isEmpty(performance, temp) == 0) {
    readHead(performance, temp, tempDest, width);
    if (compar(tempDest, target) == 0) {
      free(tempDest);
      return(i);
    } else {
      temp = next(performance, temp);
    }
    i++;
  }
  free(tempDest);
  return(-1);
}
