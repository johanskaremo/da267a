#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H


struct doubleLinkedList{
  struct doubleLinkedListElement *first;
  struct doubleLinkedListElement *last;
};

struct doubleLinkedListElement{
  int travel;
  struct doubleLinkedListElement *next;
  struct doubleLinkedListElement *previous;
};

void addElementDoubleLinkedList(struct doubleLinkedList* list, int travel);
void initDoubleLinkedList(struct doubleLinkedList* list);
int removeFirstElementDoubleLinkedList(struct doubleLinkedList* list);

#endif