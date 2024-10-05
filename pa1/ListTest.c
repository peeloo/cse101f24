/***
* Phil Liu
* phzliu
* 2024 Fall CSE101 PA1
* ListTest.c
* Testing file for List ADT
***/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"

int main(int argc, char* argv[]){
   // Create a new list
   List A = newList();
   
   // Test length on empty list
   printf("Length of A (should be 0): %d\n", length(A));
    
   // Test append and prepend
   prepend(A, 10);
   append(A, 20);
   prepend(A, 5);
   printf("List A after prepend 10, append 20, prepend 5 (should be 5 10 20): ");
   printList(stdout, A);
   printf("\n");

   // Test length
   printf("Length of A (should be 3): %d\n", length(A));

   // Test front, back, and get functions
   printf("Front of A (should be 5): %d\n", front(A));
   printf("Back of A (should be 20): %d\n", back(A));
    
   // Test cursor functions
   moveFront(A);
   printf("Cursor at front (should be 5): %d\n", get(A));
    
   moveNext(A);
   printf("Cursor after moving next (should be 10): %d\n", get(A));

   movePrev(A);
   printf("Cursor after moving next (should be 5): %d\n", get(A));
    
   moveBack(A);
   printf("Cursor at back (should be 20): %d\n", get(A));

   // Test insertBefore and insertAfter
   moveFront(A);
   insertAfter(A, 9);
   moveNext(A);
   insertBefore(A, 8);
   printf("List A after insertAfter 9 and insertBefore 8 (should be 5 8 9 10 20): ");
   printList(stdout, A);
   printf("\n");
    
   // Test delete functions
   deleteFront(A);
   printf("List A after deleteFront (should be 8 9 10 20): ");
   printList(stdout, A);
   printf("\n");

   deleteBack(A);
   printf("List A after deleteBack (should be 8 9 10): ");
   printList(stdout, A);
   printf("\n");
    
   moveFront(A);
   moveNext(A);
   delete(A);
   printf("List A after deleting cursor (should be 8 10): ");
   printList(stdout, A);
   printf("\n");

   // Test equality
   List B = newList();
   append(B, 10);
   append(B, 15);
   if (equals(A, B)) {
      printf("List A and B are equal (they should not be).\n");
   } 
   else {
      printf("List A and B are not equal (this is expected).\n");
   }

   // Test copy before clearing A
   List C = NULL;
   C = copyList(B);  // Copy List B instead of A
   if (equals(B, C)) {
      printf("List B and C are equal (they is expected).\n");
   } 
   else {
      printf("List B and C are not equal (this is not expected).\n");
   }   

   // Test clear
   clear(A);
   printf("List A after clear (should be empty): ");
   printList(stdout, A);
   printf("\n");

   // Clean up
   freeList(&A);
   freeList(&B);
   freeList(&C);

   return 0;
}
