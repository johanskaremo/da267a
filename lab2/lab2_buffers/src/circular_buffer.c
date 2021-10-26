#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "circular_buffer.h"

/*
 * Initialize an empty buffer.
 */
void initCircularBuffer(struct circularBuffer *bufferPtr, int *data, int maxLength)
{
  bufferPtr->data = data;
  for (int i = 0; i < bufferPtr->maxLength; i++)
  {
    bufferPtr->data[i] = INT_MIN;
  }
  bufferPtr->head = 0;
  bufferPtr->tail = 0;
  bufferPtr->maxLength = maxLength;
  bufferPtr->filledElements = 0;
}

/* 
 * This function should check if the buffer pointed to by bufferPtr
 * contains one or more elements with the value specified by the 
 * 'value' argument.
 *
 * The function should return:
 *  - 'value' if the an element with the argument value was found in the queue.
 *  - INT_MIN (defined in limits.h) if value was not found.
 */
int contains(struct circularBuffer *bufferPtr, int value)
{
  int counter = 0;
  for (int i = 0; i < bufferPtr->maxLength; i++)
  {
    if (bufferPtr->data[i] == value)
    {
      counter++;
    }
  }
  if (counter > 0)
  {
    return value;
  }
  else
  {
    return INT_MIN;
  }
}

/*
 * This function should add the value specified by the 'value' 
 * argument at the tail of the buffer.
 *
 * The function should return:
 *  - 'value' if the value was successfully added to the queue.
 *  - INT_MIN (defined in limits.h) if the value was not added.
 */
int addElement(struct circularBuffer *bufferPtr, int value)
{
  if (bufferPtr->filledElements == 0) //buffern är tom, lägg till värde men ändra ej head och tail
  {
    bufferPtr->data[bufferPtr->tail] = value;
    bufferPtr->filledElements++;
  }
  else
  {
    if (bufferPtr->filledElements == bufferPtr->maxLength) //om buffern är full
    {
      int overwritedElement = bufferPtr->data[bufferPtr->head];
      printf("OverWriting oldest val: %d\n", overwritedElement);
      bufferPtr->tail = bufferPtr->head;        //överskriver äldsta elementet därav hamnar
      bufferPtr->data[bufferPtr->tail] = value; //nya värdet på heads plats, och head flyttas

      if (bufferPtr->head == bufferPtr->maxLength - 1) //om head är på max, börja om på 0
      {
        bufferPtr->head = 0;
      }
      else //annars öka med 1
      {
        bufferPtr->head = bufferPtr->head + 1;
      }
    }
    else //om buffern ej är full
    {
      if (bufferPtr->tail == bufferPtr->maxLength - 1) //är tail på max, börja om på 0
      {
        bufferPtr->tail = 0;
        bufferPtr->data[bufferPtr->tail] = value;
      }
      else //tail ej max, öka med 1
      {
        bufferPtr->tail = bufferPtr->tail + 1;
        bufferPtr->data[bufferPtr->tail] = value;
      }

      bufferPtr->filledElements++;
    }
  }
  return value;
}

/* 
 * This function should remove all elements in the buffer whose
 * value matches the 'value' argument.
 * 
 * The function should return:
 *  The argument value: if at least one element was removed from queue.
 *  INT_MIN (defined in limits.h) if no element was removed. 
 */

int removeValue(struct circularBuffer *bufferPtr, int value)
{
  if (bufferPtr->filledElements == 0) //Buffern är tom, gör inget
  {
    return INT_MIN;
  }
  else                                              //ta bort element ifall det finns
  {
    int tempElements = 0;       //variabel för antal element i temparray

    for (int i = 0; i < bufferPtr->maxLength; i++)
    {                                                   //kollar hur många elemet den nya skall ha
      if (bufferPtr->data[i] != INT_MIN && bufferPtr->data[i] != value)
      {
        tempElements++;
      }
    }

   // int tempArray[tempElements];      //skapa temparray
    int* tempArray = malloc(tempElements*sizeof(int));
    int tempPos = bufferPtr->head;    //sätter headen till samma plats
    int tempCounter = 0;
                                           //är filled elements > tempElement skall en ny array skapas
    if (bufferPtr->filledElements > tempElements) 
    {
      while (tempCounter < tempElements)
      {

        if (bufferPtr->data[tempPos] != INT_MIN && bufferPtr->data[tempPos] != value)
        {

          tempArray[tempCounter] = bufferPtr->data[tempPos];
          tempCounter++;
        }

        if (tempPos == bufferPtr->maxLength - 1)
        {
          tempPos = 0;
        }
        else
        {
          tempPos++;
        }
      }

      for (int i = 0; i < bufferPtr->maxLength; i++)
      {                                                 //nollställ buffern
        bufferPtr->data[i] = INT_MIN;
      }

      tempPos = bufferPtr->head;

      for (int i = 0; i < tempElements; i++)            //lägg in de nya elementen
      {
        if (tempPos == bufferPtr->maxLength - 1)
        {
          bufferPtr->data[tempPos] = tempArray[i];
          tempPos = 0;
        }
        else
        {
          bufferPtr->data[tempPos] = tempArray[i];
          tempPos++;
        }
      }
      if (tempPos == 0)
      {
        bufferPtr->tail = bufferPtr->maxLength - 1;
      }
      else
      {
        bufferPtr->tail = tempPos - 1;
      }
      free(tempArray);
      return value;
    }
    else
    {
      free(tempArray);
      return INT_MIN;
    }
  }
}

/* 
 * Remove the oldest element, which is at the head of the queue. 
 * 
 * The function should return:
 *   - 'value' if the head element was successfully removed
 *   - INT_MIN (defined in limits.h) if no element was removed (i.e., the
 *     queue was empty when the function was called.       
 */

int removeHead(struct circularBuffer *bufferPtr)
{
  int value;
  if (bufferPtr->filledElements == 0) //buffern är tom
  {
    printf("Couldnt remove head, buffer is empty\n");
    return INT_MIN;
  }
  else if (bufferPtr->filledElements == 1) //finns endast 1 element står head och tail på samma
  {
    value = bufferPtr->data[bufferPtr->head];
    bufferPtr->data[bufferPtr->head] = INT_MIN;
    bufferPtr->filledElements = bufferPtr->filledElements - 1;
    return value;
  }
  else //finns fler element, skall head flyttas till näst äldsta
  {    //element
    value = bufferPtr->data[bufferPtr->head];
    bufferPtr->data[bufferPtr->head] = INT_MIN;

    if (bufferPtr->head == bufferPtr->maxLength - 1)
    {
      bufferPtr->head = 0;
    }
    else
    {
      bufferPtr->head = bufferPtr->head + 1;
    }
    bufferPtr->filledElements = bufferPtr->filledElements - 1;
    return value;
  }
}

/* 
 * Print the elements in the buffer from head to tail. 
 */
void printBuffer(struct circularBuffer *bufferPtr)
{
  printf("Head: %d,  ValueHead: %d, tail %d,   ValueTail: %d\n", bufferPtr->head, bufferPtr->data[bufferPtr->head], bufferPtr->tail, bufferPtr->data[bufferPtr->tail]);
  printf("Buffer from index 0-3\n");
  for (int i = 0; i < bufferPtr->maxLength; i++)
  {
    printf("Data: %d \n", bufferPtr->data[i]);
  }
}
