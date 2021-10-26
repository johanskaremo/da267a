#ifndef SINGLE_LINKED_LIST_H
#define SINGLE_LINKED_LIST_H

struct singleLinkedListElement{
  int data;
  struct singleLinkedListElement *next;
};

struct singleLinkedList{
  struct singleLinkedListElement *first;
};

int addElementSingleLinkedList(struct singleLinkedList* list, int value);
void initSingleLinkedList(struct singleLinkedList* list);
int removeFirstElementSingleLinkedList(struct singleLinkedList* list);
int removeLastElementSingleLinkedList(struct singleLinkedList* list);
void printSingleLinkedList(struct singleLinkedList* list);
void sortSingleLinkedList(struct singleLinkedList* list);

#endif
