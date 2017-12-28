/*C**********************************************************************
* FILENAME    :       main.c 
* DESCRIPTION :       Main C file
* NOTES       :       -NA-
*
* AUTHOR      :       Vijayalakshmi Sundar     START DATE :   22 Dec 17
*
* CHANGES :
*
*C***********************************************************************/

#include "ll.h"

typedef struct _dnaT{
   char   A;
   char   T;
   char   C;
   char   G;
}dnaT;

void func( void *dataP, void *userData ) {
   *(int*)dataP            += *(int*)userData;
}

bool compare( void* data, void* userData ){
   return *(int*)data == *(int*)userData;
}

void* prepareData( int data ){
   int* dataP = (int*) calloc(1, sizeof(int));
   *dataP     = data;
   return dataP;
}

void main () {
   listPT listP = createList();
   pushNth(listP, 0, prepareData(1));
   pushHead(listP, prepareData(3));
   pushTail(listP, prepareData(5));
   pushNth(listP, 1, prepareData(4));
   pushTail(listP, prepareData(1));
   pushHead(listP, prepareData(8));
   pushNth(listP, 1, prepareData(0));
   printList(listP, LIST_DIR_FWD);
   printf("\n");
   free(popHead(listP));
   free(popTail(listP));
   free(popNth(listP, 3));
   printList(listP, LIST_DIR_FWD);
   forEach( listP, prepareData(500), func );
   printf("Index: %d\n", findCustomIndex(listP, prepareData(500), compare));
   printf("Index: %d\n", findCustomIndex(listP, prepareData(509), compare));
   printList(listP, LIST_DIR_FWD);
   destroyList( listP, free );
}
