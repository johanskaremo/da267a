#include <stdio.h>
#include <stdlib.h>

#include "single_linked_list.h"
#include "double_linked_list.h"

void app_main() {

printf("\n\n\n");
struct singleLinkedList list;
initSingleLinkedList(&list);
struct doubleLinkedList listD;
initDoubleLinkedList(&listD);



printf("Tests SingleLinkedList, V = Value, N = Next node \n__________________________\n\n\n");

printf("Adding 5 elements then printing, order: 6, 2, 10, 7, 5 \n\n");
addElementSingleLinkedList(&list, 6);
addElementSingleLinkedList(&list, 2);
addElementSingleLinkedList(&list, 10);
addElementSingleLinkedList(&list, 7);
addElementSingleLinkedList(&list, 5);
printSingleLinkedList(&list);
printf("\n\n\n\n");


printf("Deleting last element then printing:\n\n");
removeLastElementSingleLinkedList(&list);
printSingleLinkedList(&list);
printf("\n\n\n\n");


printf("Deleting first element then printing: \n\n");
removeFirstElementSingleLinkedList(&list);
printSingleLinkedList(&list);
printf("\n\n\n\n");


printf("Special case, trying to remove element from already empty list then printing: \n\n");
int removed = removeFirstElementSingleLinkedList(&list);
printf("Removed node with value: %d\n\n", removed);
printSingleLinkedList(&list);
printf("\n");
int removed2 = removeFirstElementSingleLinkedList(&list);
printf("Removed node with value: %d\n\n", removed2);
printSingleLinkedList(&list);
printf("\n");
int removed3 = removeFirstElementSingleLinkedList(&list);
printf("Removed node with value: %d\n\n", removed3);
printSingleLinkedList(&list);
printf("\n");
removeFirstElementSingleLinkedList(&list);
removeLastElementSingleLinkedList(&list);
printf("\nfirst was errormessage, now printing \n\n");
printSingleLinkedList(&list);
printf("\n\n\n\n");




printf("Tests DoubleLinkedList, P = prev(Value), V = Value, N = Next node\n_________________________________________  \n\n");


printf("Adding 5 elements then printing, order: 6, 2, 10, 7, 5 \n\n");
addElementDoubleLinkedList(&listD, 6);
addElementDoubleLinkedList(&listD, 2);
addElementDoubleLinkedList(&listD, 10);
addElementDoubleLinkedList(&listD, 7);
addElementDoubleLinkedList(&listD, 5);
printDoubleLinkedList(&listD);
printf("\n\n\n\n");


printf("Deleting first element then printing:\n\n");
removeFirstElementDoubleLinkedList(&listD);
printDoubleLinkedList(&listD);
printf("\n\n\n\n");


printf("Deleting last element then printing:\n\n");
removeLastElementDoubleLinkedList(&listD);
printDoubleLinkedList(&listD);
printf("\n\n\n\n");


printf("Special case, trying to remove element from already empty list then printing: \n\n");
removed = removeFirstElementDoubleLinkedList(&listD);
printf("Removed node with value: %d\n\n", removed);
printDoubleLinkedList(&listD);
printf("\n");
removed2 = removeFirstElementDoubleLinkedList(&listD);
printf("Removed node with value: %d\n\n", removed2);
printDoubleLinkedList(&listD);
printf("\n");
removed3 = removeFirstElementDoubleLinkedList(&listD);
printf("Removed node with value: %d\n\n", removed3);
printDoubleLinkedList(&listD);
printf("\n");
removeFirstElementDoubleLinkedList(&listD);
removeLastElementDoubleLinkedList(&listD);
printf("\nfirst was errormessage, now printing \n\n");
printDoubleLinkedList(&listD);
printf("\n\n\n\n");
}