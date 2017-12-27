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

//void func1( int *dataP, int userData ) {
//   *dataP            += userData;
//}
//
//void func2( int *dataP, int userData ) {
//   *dataP            *= userData;
//}
//
//void main () {
//   listPT listP = (listPT) calloc( 1, sizeof(listT) );
//   pushNth(listP, 0, 5);
//   pushHead(listP, 0);
//   pushTail(listP, 3);
//   pushNth(listP, 1, 7);
//   pushTail(listP, 0);
//   pushHead(listP, 2);
//   pushNth(listP, 1, 2);
//   popHead(listP);
//   popTail(listP);
//   popNth(listP, 3);
//   printList(listP, LIST_DIR_FWD);
//   forEach( listP, func1, 5 );
//   printf("\n");
//   printList(listP, LIST_DIR_FWD);
//   printf("\n");
//
//   listPT list1P = (listPT) calloc( 1, sizeof(listT) );
//   pushNth(list1P, 0, 5);
//   pushHead(list1P, 0);
//   pushTail(list1P, 3);
//   pushNth(list1P, 1, 7);
//   pushTail(list1P, 0);
//   pushHead(list1P, 2);
//   pushNth(list1P, 1, 2);
//   popHead(list1P);
//   popTail(list1P);
//   printList(list1P, LIST_DIR_FWD);
//   printf("\n");
//   forEach( list1P, func2, 100 );
//   printList(list1P, LIST_DIR_FWD);
//   printf("\n");
//}

void func( void* dataP, void* userData ) {
   *(int*)dataP            += *(int*)userData;
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
   //forEach( listP, 5 );
   printf("\n");
   printList(listP, LIST_DIR_FWD);
   printf("\n");
}
