#include <stdio.h>
#include <stdlib.h>
#include <esp32/rom/ets_sys.h>
#include "circular_buffer.h"

/*
 * Change the value of BUFFER_SIZE if you want to change the size of the buffer. 
 */
#define BUFFER_SIZE 4

void app_main()
{

    // Some code to help you get started
    struct circularBuffer buffer;
    int *buffer_data = (int *)malloc(BUFFER_SIZE * sizeof(int));    //allokerar minne i datorn för arrayn
    initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE);



    int addel, addel2, addel3, addel4, addel5;
    int delel, delel2, delel3, delel4, delel5;
    //BlackBoxTesting
    printf("\n\n\nBlackbox-testing:\n________________________\n\n\n\n");

    printf("Blackbox-test 1\n\n");
    addel = addElement(&buffer, 5);
    printf("Added element: %d \n", addel);
    delel = removeHead(&buffer);
    printf("Removed element: %d \n", delel);
    initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE);
    printf("\n\n\n");

    printf("Blackbox-test 2\n\n");
    addel = addElement(&buffer, 5);
    printf("Added element: %d \n", addel);
    addel2 = addElement(&buffer, 6);
    printf("Added element: %d \n", addel2);
    delel = removeHead(&buffer);
    printf("Removed element: %d \n", delel);
    initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE);
    printf("\n\n\n");

    printf("Blackbox-test 3\n\n");
    addel = addElement(&buffer, 5);
    printf("Added element: %d \n", addel);
    addel2 = addElement(&buffer, 6);
    printf("Added element: %d \n", addel2);
    addel3 = addElement(&buffer, 7);
    printf("Added element: %d \n", addel3);
    addel4 = addElement(&buffer, 8);
    printf("Added element: %d \n", addel4);

    delel = removeHead(&buffer);
    printf("Removed element: %d \n", delel);
    delel2 = removeHead(&buffer);
    printf("Removed element: %d \n", delel2);
    delel3 = removeHead(&buffer);
    printf("Removed element: %d \n", delel3);
    delel4 = removeHead(&buffer);
    printf("Removed element: %d \n", delel4);
    initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE);
    printf("\n\n\n");


    printf("Blackbox-test 4\n\n");
    addel = addElement(&buffer, 5);
    printf("Added element: %d \n", addel);
    addel2 = addElement(&buffer, 6);
    printf("Added element: %d \n", addel2);
    addel3 = addElement(&buffer, 7);
    printf("Added element: %d \n", addel3);
    addel4 = addElement(&buffer, 8);
    printf("Added element: %d \n", addel4);
    addel5 = addElement(&buffer, 9);
    printf("Added element: %d \n\n", addel5);
    printf("Now printing full buffer:\n");
    printBuffer(&buffer);
    initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE);
    printf("\n\n\n");


    printf("Blackbox-test 5\n\n");
    addel = addElement(&buffer, 5);
    printf("Added element: %d \n", addel);
    addel2 = addElement(&buffer, 6);
    printf("Added element: %d \n", addel2);
    addel3 = addElement(&buffer, 7);
    printf("Added element: %d \n", addel3);
    addel4 = addElement(&buffer, 8);
    printf("Added element: %d \n", addel4);
    addel5 = addElement(&buffer, 9);
    printf("Added element: %d \n", addel5);
    delel = removeHead(&buffer);
    printf("Removed element: %d \n", delel);
    delel2 = removeHead(&buffer);
    printf("Removed element: %d \n", delel2);
    delel3 = removeHead(&buffer);
    printf("Removed element: %d \n", delel3);
    delel4 = removeHead(&buffer);
    printf("Removed element: %d \n", delel4);
    delel5 = removeHead(&buffer);
    printf("Removed element: %d \n", delel5);
    initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE);
    printf("\n\n\n");


    printf("Blackbox-test 6\n\n");
    int val = contains(&buffer, 8);
    printf("Contains, empty buffer: %d \n", val);
    printf("\n\n\n");


    printf("Blackbox-test 7\n\n");
    addel = addElement(&buffer, 5);
    printf("Added element: %d \n", addel);
    val = contains(&buffer, 5);
    printf("running contains with val 5: %d \n", val);
    initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE);
    printf("\n\n\n");


    printf("Blackbox-test 8\n\n");
    addel = addElement(&buffer, 5);
    printf("Added element: %d \n", addel);
    addel2 = addElement(&buffer, 6);
    printf("Added element: %d \n", addel2);
    val = contains(&buffer, 6);
    printf("running contains with val 6: %d \n", val);
    initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE);
    printf("\n\n\n");


    printf("Blackbox-test 9\n\n");
    addel = addElement(&buffer, 5);
    printf("Added element: %d \n", addel);
    addel2 = addElement(&buffer, 6);
    printf("Added element: %d \n", addel2);
    addel3 = addElement(&buffer, 7);
    printf("Added element: %d \n", addel3);
    addel4 = addElement(&buffer, 8);
    printf("Added element: %d \n", addel4);
    val = contains(&buffer, 8);
    printf("running contains with val 8: %d \n", val);
    

    free(buffer_data);
}