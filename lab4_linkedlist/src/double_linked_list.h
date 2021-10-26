#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H


struct doubleLinkedList{
  struct doubleLinkedListElement *first;
  struct doubleLinkedListElement *last;
};

struct doubleLinkedListElement{
  int data;
  struct doubleLinkedListElement *next;
  struct doubleLinkedListElement *previous;
};

int addElementDoubleLinkedList(struct doubleLinkedList* list, int value);
void initDoubleLinkedList(struct doubleLinkedList* list);
int removeFirstElementDoubleLinkedList(struct doubleLinkedList* list);
int removeLastElementDoubleLinkedList(struct doubleLinkedList* list);
void printDoubleLinkedList(struct doubleLinkedList* listD);
void sortDoubleLinkedList(struct doubleLinkedList *listD);

#endif
