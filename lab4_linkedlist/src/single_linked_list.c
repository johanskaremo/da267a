#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "single_linked_list.h"

/* 
 * This function should initialize the linked list structure that is given as
 * argument to the function, that is setting list->first to NULL
 */
void initSingleLinkedList(struct singleLinkedList *list)
{
  list->first = NULL;
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
 * Return values:
 *   'value' - If a new element with value 'value' successfully added to the list.
 *   INT_MIN (defined in limits.h) - If a new element could not be added to the list.
 */
int addElementSingleLinkedList(struct singleLinkedList *list, int value)
{
  struct singleLinkedListElement *newNode = (struct singleLinkedListElement *)malloc(sizeof(struct singleLinkedListElement));
  struct singleLinkedListElement *head = list->first;

  newNode->data = value;
  newNode->next = NULL;

  if (list->first == NULL)    //första elementet  listan är null, första elementet är den vi lägger till
  {
    list->first = newNode;
    return value;
  }
  else
  {
    while (head->next != NULL)    //för att hitta den sista noden
    {
      head = head->next;
    }
    head->next = newNode;       //sätter sista nodens "next" till den nya noden
    sortSingleLinkedList(list);
    return value;
  }
  return INT_MIN;
}

/* 
 * This function should remove the first element in the linked list, i.e., list->first.
 * 
 * Don't forget to free memory of the struct element you remove.
 *
 * Return values:
 *  list->first->data if the element was successfully removed.
 *  INT_MIN (defined in limits.h) - If no element could be removed (i.e. the list->first == NULL).
 */
int removeFirstElementSingleLinkedList(struct singleLinkedList *list)
{
  int tempData;
  struct singleLinkedListElement *temp = NULL;

  if (list->first == NULL)
  {
    printf("Couldn't remove, list is empty\n");
    return INT_MIN;
  }
  else
  {
    tempData = list->first->data;     //tempdata, den som skall tas bort och returnas
    temp = list->first->next;         //sätter tempNoden till näst första noden, den som sen skall bli
    free(list->first);                    //den nya första
    list->first = temp;

    return tempData;
  }
}

/* 
 * This function should remove the last element in the linked list.
 * 
 * Don't forget to free memory (using free) of the struct element you remove.
 *
 * Return values:
 *  list->first->data if the element was successfully removed.
 *  INT_MIN (defined in limits.h) - If no element could be removed (i.e. the list->first == NULL).
 */
int removeLastElementSingleLinkedList(struct singleLinkedList *list)
{
  struct singleLinkedListElement *delete = list->first;
  struct singleLinkedListElement *previous = list->first;

  if (list->first == NULL)
  {
    printf("Couldn't remove, list is empty\n");
    return INT_MIN;
  }
  else
  {

    while (delete->next != NULL)
    {
      previous = delete;
      delete = delete->next;
    }

    if (delete == list->first)      // specialfall ifall det bara finns en nod i listan, då har inte
    {                                 //while-satsen gått igenom, ta bara bort första elementet, listan
      list->first = NULL;               //är tom
      return delete->data;              
    }
    else
    {
      previous->next = NULL;        //annars om det finns fler än ett element, sätt den nästsistas "next"
    }                               //till null, då vi har tagit bort den sista
    free(delete);
    return previous->data;
  }
}

void printSingleLinkedList(struct singleLinkedList *list)
{
  struct singleLinkedListElement *head = list->first;

  if (list->first == NULL)
  {
    printf("LinkedList is empty \n");
  }
  else
  {
    printf("V: %d , N --> | ", head->data);

    while (head->next != NULL)
    {
      head = head->next;
      printf("V: %d, N--> | ", head->data);
    }
  }
}

void sortSingleLinkedList(struct singleLinkedList *list) //using bubblesort
{

  struct singleLinkedListElement *head = NULL;
  struct singleLinkedListElement *end = NULL;
  int swapOn;

  if (list->first == NULL)
  {
    return;
  }

  do
  {
    swapOn = 0;
    head = list->first;

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
