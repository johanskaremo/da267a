#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H


/* 
 * Data structure used to hold a circular buffer.
 */
struct circularBuffer{
  int * data;
  int head;
  int tail;
  int maxLength;
  int filledElements;
};

void initCircularBuffer(struct circularBuffer* bufferPtr, int* data, int maxLen);
int contains(struct circularBuffer* bufferPtr, int value);
int addElement(struct circularBuffer* bufferPtr, int value);
int removeValue(struct circularBuffer* bufferPtr, int value);
int removeHead(struct circularBuffer* bufferPtr);
void printBuffer(struct circularBuffer* bufferPtr);
#endif

