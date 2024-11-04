/***
* Phil Liu
* phzliu
* 2024 Fall CSE101 PA4
* List.c
* Implements List ADT and its operations
***/

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj{
   void* data;
   Node next;
   Node prev;
} NodeObj;

// private QueueObj type
typedef struct ListObj{
   Node front;
   Node back;
   Node cursor;
   int index;
   int length;
} ListObj;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(void* data){
   Node N = malloc(sizeof(NodeObj));
   assert( N!=NULL );
   N->data = data;
   N->next = NULL;
   N->prev = NULL;
   return(N);
}


// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ) {
      free(*pN);
      *pN = NULL;
   }
}

// Creates and returns a new empty List.
List newList(){
   List L;
   L = malloc(sizeof(ListObj));
   assert( L!=NULL );
   L->front = L->back = L->cursor = NULL;
   L->length = 0;
   L->index = -1;
   return(L);
}


// Frees all heap memory associated with *pL, and sets
 // *pL to NULL.
void freeList(List* pL){
   if(pL!=NULL && *pL!=NULL) { 
      while(length(*pL) != 0) { 
         deleteFront(*pL); 
      }
      free(*pL);
      *pL = NULL;
   }
}



// Access functions -----------------------------------------------------------

int length(List L) {
   if (L == NULL) {
      fprintf(stderr, "List error: calling length() on NULL list\n");
      exit(EXIT_FAILURE);
   }
   return L->length;
}

int index(List L) {
   if (L == NULL) {
      fprintf(stderr, "List error: calling index() on NULL list\n");
      exit(EXIT_FAILURE);
   }
   return L->index;
}

void* front(List L) {
   if (L == NULL) {
      fprintf(stderr, "List error: calling front() on NULL list\n");
      exit(EXIT_FAILURE);
   }
   if (length(L) <= 0) {
      fprintf(stderr, "List Error: calling front() on list with length() <= 0\n");
      exit(EXIT_FAILURE);
   
   }
   return L->front->data;
}

void* back(List L) {
   if (L == NULL) {
      fprintf(stderr, "List error: calling back() on NULL list\n");
      exit(EXIT_FAILURE);
   }
   if (length(L) <= 0) {
      fprintf(stderr, "List Error: calling back() on list with length() <= 0\n");
      exit(EXIT_FAILURE);
   }
   return L->back->data;
}

void* get(List L) {
   if (L == NULL) {
      fprintf(stderr, "List error: calling get() on NULL list\n");
      exit(EXIT_FAILURE);
   }
   if (length(L) <= 0) {
      fprintf(stderr, "List Error: calling get() on list with length() <= 0\n");
      exit(EXIT_FAILURE);
   }
   if (index(L) < 0 || L->cursor == NULL) {
      fprintf(stderr, "List Error: calling get() on list with index() < 0\n");
      exit(EXIT_FAILURE);
   }
   return L->cursor->data;
}

// bool equals(List A, List B) {
//     if(A == NULL || B == NULL) {
//         fprintf(stderr, "List Error: calling equals() on NULL List reference\n");
//         exit(EXIT_FAILURE);
//     }

//    if (A->length != B->length) {
//       return false;
//    }

//    Node curr1 = A->front;
//    Node curr2 = B->front;
   
//    while (curr1 != NULL) {
//       if (curr1->data != curr2->data) {
//          return false;
//       }
//       curr1 = curr1->next;
//       curr2 = curr2->next;
//    }
   
//    return true;
// }

// Manipulation procedures ----------------------------------------------------

void clear(List L) {
   if (L == NULL) {
      fprintf(stderr, "List Error: calling clear() on NULL List reference\n");
      exit(EXIT_FAILURE);      
   }

   while (length(L) > 0) {
      deleteFront(L);
   }

   L->cursor = NULL;
   L->index = -1;

}

void set(List L, void* x) {
   if( L==NULL ){
      fprintf(stderr, "List Error: calling set() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   if ((index(L) != -1) && (L->cursor != NULL)) {
      L->cursor->data = x;
   }
}

void moveFront(List L) { // fixed
   if (L == NULL) {
      printf("List error: calling mvoeFront() on NULL list\n");
      exit(EXIT_FAILURE);
   }
   if (length(L) > 0) {
      L->cursor = L->front;
      L->index = 0;
   }
}

void moveBack(List L) { // fixed
   if (L == NULL) {
      printf("List error: calling mvoeBack() on NULL list\n");
      exit(EXIT_FAILURE);
   }
   if (length(L) > 0) {
      L->cursor = L->back;
      L->index = length(L) - 1;
   }
}

void movePrev(List L) {
   if (L == NULL) {
      fprintf(stderr, "List Error: calling movePrev() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   if (length(L) == 0) {
      fprintf(stderr, "List Error: calling movePrev() on an empty List\n");
      exit(EXIT_FAILURE);
   }

   if (L->cursor != NULL) {
      if (L->cursor != L->front) {
         L->cursor = L->cursor->prev;
         L->index--;
      }
      else {
         L->cursor = NULL;
         L->index = -1;
      }
   }
}


void moveNext(List L) {
   if (L == NULL) {
      fprintf(stderr, "List Error: calling moveNext() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   if (length(L) == 0) {
      fprintf(stderr, "List Error: calling moveNext() on an empty List\n");
      exit(EXIT_FAILURE);
   }

   if (L->cursor != NULL) {
      if (L->cursor != L->back) {
         L->cursor = L->cursor->next;
         L->index++;
      }
      else {
         L->cursor = NULL;
         L->index = -1;
      }
   }
}

void prepend(List L, void* data) {   
   if (L == NULL) {
      fprintf(stderr, "List Error: calling prepend() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   Node N = newNode(data);

   if (length(L) == 0) {
      L->front = L->back = N;
   }
   else {
      N->next = L->front;
      L->front->prev = N;
      L->front = N;
   }
   L->length++;
   L->index++;
}

void append(List L, void* data) {
   if (L == NULL) {
      fprintf(stderr, "List Error: calling append() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   Node N = newNode(data);

   if (length(L) == 0) {
      L->front = L->back = N;
   }
   else {
      N->prev = L->back;
      L->back->next = N;
      L->back = N;
   }
   L->length++;
}

void insertBefore(List L, void* data) {
   if (L == NULL) {
      fprintf(stderr, "List Error: calling insertBefore() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (L->cursor == NULL) {
      fprintf(stderr, "List Error: calling insertBefore() on NULL cursor reference\n");
      exit(EXIT_FAILURE);
   }

   Node N = newNode(data);

   if (L->cursor == L->front) {
      L->front->prev = N;
      N->next = L->front;
      L->front = N;
      L->index++;
      L->length++;
   }
   else {
      N->prev = L->cursor->prev;
      N->next = L->cursor;
      L->cursor->prev->next = N;
      L->cursor->prev = N;
      L->index++;
      L->length++;
   }
}

void insertAfter(List L, void* data) {
   if (L == NULL) {
      fprintf(stderr, "List Error: calling insertBefore() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (L->cursor == NULL) {
      fprintf(stderr, "List Error: calling insertBefore() on NULL cursor reference\n");
      exit(EXIT_FAILURE);
   }

   Node N = newNode(data);

   if (L->cursor == L->back) {
      L->back->next = N;
      N->prev = L->back;
      L->back = N;
      L->length++;
   }
   else {
      N->next = L->cursor->next;
      N->prev = L->cursor;
      L->cursor->next->prev = N;
      L->cursor->next = N;
      L->length++;
   }
}


void deleteFront(List L){
   Node N = NULL;

   if (L == NULL) {
      fprintf(stderr, "List Error: calling deleteFront() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (length(L) == 0) {
      fprintf(stderr, "List Error: calling deleteFront() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   
   N = L->front;
   if (length(L) > 1) {
      if (L->cursor == N) {
         L->cursor = NULL;
         L->index = -1;
      }
      if (L->index != -1) {
         L->index--;
      }
      L->front = L->front->next; 
      L->front->prev = NULL;
   }
   else { 
      L->front = L->back = L->cursor = NULL;
      L->index = -1;
   }
   L->length--;
   freeNode(&N);
}

void deleteBack(List L) {
   Node N = NULL;
   if(L == NULL) {
      fprintf(stderr, "List Error: calling deleteBack() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (length(L) == 0) {
      fprintf(stderr, "List Error: calling deleteback() on an empty List\n");
      exit(EXIT_FAILURE);
   }  

   N = L->back;
   if (length(L) > 1) {
      if (L->cursor == N) {
         L->cursor = NULL;
         L->index = -1;
      }
      L->back = L->back->prev;
      L->back->next = NULL;
   }
   else {
      L->front = L->back = L->cursor = NULL;
      L->index = -1;
   }
   L->length--;
   freeNode(&N);
}

void delete(List L) {
   if(L == NULL) {
      fprintf(stderr, "List Error: calling delete() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (length(L) == 0) {
      fprintf(stderr, "List Error: calling delete() on an empty List\n");
      exit(EXIT_FAILURE);
   }  
   if (L->cursor == NULL) {
      fprintf(stderr, "List Error: calling delete() on NULL cursor reference\n");
      exit(EXIT_FAILURE);
   }
   
   Node N = NULL;
   N = L->cursor;
   if (N == L->front) {
      deleteFront(L);
   }
   else if (N == L->back) {
      deleteBack(L);
   }
   else {
      N->prev->next = N->next;
      N->next->prev = N->prev;
      freeNode(&N);
      L->length--;
   }
   L->index = -1;
}

// Other operations -----------------------------------------------------------

void printList(FILE* out, List L) {  //fixed
   if (L == NULL) {
      printf("List error: calling printList() on NULL list\n");
      exit(EXIT_FAILURE);
   }
   if (out == NULL) {
      printf("List error: calling printList on NULL outfile");
      exit(EXIT_FAILURE);
   }

   Node N = L->front;
   while (N != NULL) {
      fprintf(out, "%p ", N->data);
      N = N->next;
   }
   fprintf(out, "\n");
}

// List copyList(List L) {
//    if (L == NULL) {
//       fprintf(stderr, "List Error: calling copyList() on NULL List reference\n");
//       exit(EXIT_FAILURE);
//    }

//    List copy = newList();
//    Node curr = NULL;
//    curr = L->front;   

//    while (curr != NULL) {
//       append(copy, curr->data);
//       curr = curr->next;
//    }

//    return copy;
// }


List concatList(List A, List B) { // added
   List C = newList();
   Node N = A->front;
   Node M = B->front;
   while (N != NULL) {
      append(C, N->data);
      N = N->next;
   }
   while (M != NULL) {
      append(C, M->data);
      M = M->next;
   }
   C->cursor = NULL;
   C->index = -1;
   return C;
}