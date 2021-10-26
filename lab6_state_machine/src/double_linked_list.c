#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "double_linked_list.h"

void initDoubleLinkedList(struct doubleLinkedList *list)
{
  list->first = NULL;
  list->last = NULL;
}

void addElementDoubleLinkedList(struct doubleLinkedList *listD, int nextTravel)
{

  struct doubleLinkedListElement *newNode = (struct doubleLinkedListElement *)malloc(sizeof(struct doubleLinkedListElement));

  newNode->travel = nextTravel;
  newNode->next = NULL;
  newNode->previous = NULL;

  if (listD->first == NULL)
  {
    listD->first = newNode;
    listD->last = newNode;
  }
  else
  {
    newNode->previous = listD->last;
    listD->last->next = newNode;
    listD->last = newNode;
  }
}

int removeFirstElementDoubleLinkedList(struct doubleLinkedList *listD)
{
  struct doubleLinkedListElement *temp = NULL;

  if (listD->first == NULL)     //listan helt tom
  {
    printf("Couldn't remove, list is empty\n");
    return INT_MIN;
  }
  else
  {
    if (listD->first->next == NULL)   //ifall det bara finns ett element i listan
    {    
      free(listD->first);
      listD->first = NULL;
      listD->last = NULL;
    }
    else              //fler än ett element
    {
      temp = listD->first->next;      //tempnode = näst första då vi ska ta bort den första noden
      temp->previous = NULL;          //den nya noden kommer vara först, då är "P" NULL
      free(listD->first);
      listD->first = temp;          //listans första till den som tidigare var nästförsta
    }

    return INT_MIN;
  }
}