/***
 * Phil Liu
 * phzliu
 * 2024 Fall CSE101 PA4
 * ListTest.c
 * Test file for List ADT
 ***/

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

int main() {
    // Create new lists for testing
    List A = newList();
    List B = newList();

    // Test append() and prepend()
    printf("Testing append and prepend:\n");
    for (int i = 1; i <= 5; i++) {
        append(A, (void*)(long)i);  // Append elements 1 to 5
        prepend(B, (void*)(long)(i * 10));  // Prepend elements 10, 20, 30, 40, 50
    }
    printf("List A after appending 1 to 5:\n");
    printList(stdout, A);
    printf("\nList B after prepending 10, 20, 30, 40, 50:\n");
    printList(stdout, B);
    printf("\n\n");

    // Test length() and index()
    printf("Testing length and index:\n");
    printf("Length of A: %d\n", length(A));
    printf("Length of B: %d\n", length(B));
    moveFront(A);
    printf("Index of cursor in A after moveFront: %d\n", index(A));
    moveNext(A);
    printf("Index of cursor in A after moveNext: %d\n", index(A));
    moveBack(A);
    printf("Index of cursor in A after moveBack: %d\n", index(A));
    printf("\n");

    // Test get(), front(), and back()
    printf("Testing get, front, and back:\n");
    printf("Front of A: %ld\n", (long)front(A));
    printf("Back of A: %ld\n", (long)back(A));
    printf("Current cursor element in A: %ld\n", (long)get(A));
    printf("\n");

    // Test insertBefore() and insertAfter()
    printf("Testing insertBefore and insertAfter:\n");
    moveFront(A);
    insertAfter(A, (void*)(long)100);  // Insert 100 after the front
    moveBack(A);
    insertBefore(A, (void*)(long)200);  // Insert 200 before the back
    printf("List A after inserting 100 after front and 200 before back:\n");
    printList(stdout, A);
    printf("\n\n");

    // Test deleteFront(), deleteBack(), and delete()
    printf("Testing deleteFront, deleteBack, and delete:\n");
    deleteFront(A);
    deleteBack(A);
    printf("List A after deleting front and back:\n");
    printList(stdout, A);
    moveFront(A);
    moveNext(A);  // Move cursor to the second element
    delete(A);
    printf("\nList A after deleting the second element (with cursor):\n");
    printList(stdout, A);
    printf("\n\n");

    // Test concatList()
    printf("Testing concatList:\n");
    List C = concatList(A, B);
    printf("List C (A concatenated with B):\n");
    printList(stdout, C);
    printf("\n\n");

    // Test clear()
    printf("Testing clear:\n");
    clear(A);
    printf("List A after clear:\n");
    printList(stdout, A);
    printf("\nLength of A after clear: %d\n", length(A));

    // Free all lists
    freeList(&A);
    freeList(&B);
    freeList(&C);

    return 0;
}