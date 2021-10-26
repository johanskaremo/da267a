#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "double_linked_list.h"

/* 
 * This function should initialize the linked list structure that is given as
 * argument to the function, that is setting list->first and list->last to NULL
 */
void initDoubleLinkedList(struct doubleLinkedList *list)
{
  list->first = NULL;
  list->last = NULL;
}

/* 
 * This function should add a new element with value 'value' to the argument linked list.
 * A new value should be added even if the list already contains an element with the 
 * argument value. 
 *
 * When adding elements, you should make sure that the linked list is sorted based on the
 * 'data' field in the linkedListElements, so that the element with smallest value is the
 * first element in the list, followed by the second smallest element, etc. 
 *
 * Please note that you need to dynamically allocate memory (using malloc or calloc) to 
 * your new element. 
 * 
 * When adding an element to your double linked list, you have the choice to start either 
 * from the beginning or the end of the list when searching for the position where to 
 * insert a new element. It is up to you how to decide which search strategy to use. 
 *
 * 
 * Return values:
 *   'value' - If a new element with value 'value' successfully added to the list.
 *   INT_MIN (defined in limits.h) - If a new element could not be added to the list.
 */
int addElementDoubleLinkedList(struct doubleLinkedList *listD, int value)
{

  struct doubleLinkedListElement *newNode = (struct doubleLinkedListElement *)malloc(sizeof(struct doubleLinkedListElement));

  newNode->data = value;
  newNode->next = NULL;
  newNode->previous = NULL;

  if (listD->first == NULL)
  {
    listD->first = newNode;
    listD->last = newNode;
    return value;
  }
  else
  {
    newNode->previous = listD->last;
    listD->last->next = newNode;
    listD->last = newNode;
    sortDoubleLinkedList(listD);
    return value;
  }
  return INT_MIN;
}

/* 
 * This function should remove the first element in the linked list, i.e., list->first.
 * 
 * Don't forget to free memory (using free) of the struct element you remove.
 *
 * Return values:
 *  list->first->data if the element was successfully removed.
 *  INT_MIN (defined in limits.h) - If no element could be removed (i.e. the list->first == NULL).
 */
int removeFirstElementDoubleLinkedList(struct doubleLinkedList *listD)
{
  struct doubleLinkedListElement *temp = NULL;
  int tempData = 0;

  if (listD->first == NULL)     //listan helt tom
  {
    printf("Couldn't remove, list is empty\n");
    return INT_MIN;
  }
  else
  {
    if (listD->first->next == NULL)   //ifall det bara finns ett element i listan
    {
      tempData = listD->first->data;    
      free(listD->first);
      listD->first = NULL;
      listD->last = NULL;
    }
    else              //fler än ett element
    {
      temp = listD->first->next;      //tempnode = näst första då vi ska ta bort den första noden
      temp->previous = NULL;          //den nya noden kommer vara först, då är "P" NULL
      tempData = listD->first->data;  //värdet som skall returneras
      free(listD->first);
      listD->first = temp;          //listans första till den som tidigare var nästförsta
    }

    return tempData;
  }
}

/* 
 * This function should remove the last element in the linked list.
 * 
 * Don't forget to free memory (using free) of the struct element you remove.
 *
 * Return values:
 *  list->last->data if the element was successfully removed.
 *  INT_MIN (defined in limits.h) - If no element could be removed (i.e. the list->first == NULL).
 */
int removeLastElementDoubleLinkedList(struct doubleLinkedList *listD)
{
  struct doubleLinkedListElement *temp = NULL;
  int tempData = 0;

  if (listD->first == NULL)     //listan tom
  {
    printf("Couldn't remove, list is empty\n");
    return INT_MIN;
  }
  else
  {
    if (listD->first->next == NULL)     //ett elemt, spcialfall, både first och last är null
    {
      tempData = listD->first->data;
      free(listD->first);
      listD->first = NULL;
      listD->last = NULL;
    }
    else{                          //över ett element i listan, sätter näst sista till temp och temps
      tempData = listD->last->data;             // "N" till null då det är den sista noden som skall bort
      temp = listD->last->previous;   
      temp->next = NULL;
      free(listD->last);
      listD->last = temp;
    }
    return tempData;
  }
}

void printDoubleLinkedList(struct doubleLinkedList *listD)
{
  struct doubleLinkedListElement *head = listD->first;

  if (listD->first == NULL)
  {
    printf("LinkedList is empty \n");
  }
  else
  {
    printf("P: NULL, V: %d, N--> | ", head->data);

    while (head->next != NULL)
    {
      head = head->next;
      printf("P: %d, V: %d, N--> | ", head->previous->data, head->data);
    }
  }
}

void sortDoubleLinkedList(struct doubleLinkedList *listD) //using bubblesort
{

  struct doubleLinkedListElement *head = NULL;
  struct doubleLinkedListElement *end = NULL;
  int swapOn;

  if (listD->first == NULL)
  {
    return;
  }

  do
  {
    swapOn = 0;
    head = listD->first;

    while (head->next != end)
    {

      if (head->data > head->next->data)
      {

        int temp = head->data;
        head->data = head->next->data;
        head->next->data = temp;
        swapOn = 1;
      }
      head = head->next;
    }
    end = head;
  } while (swapOn);
}
