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

void main () {
   listPT listP = (listPT) calloc( 1, sizeof(listT) );
   pushNth(listP, 0, 5);
   pushHead(listP, 0);
   pushTail(listP, 3);
   pushNth(listP, 1, 7);
   pushTail(listP, 0);
   pushHead(listP, 2);
   pushNth(listP, 1, 2);
   popHead(listP);
   popTail(listP);
   popNth(listP, 3);
   printList(listP, LIST_DIR_FWD);
   printf("\n");
   printList(listP, LIST_DIR_FWD);
   printf("\n");
   printList(listP, LIST_DIR_BKD);
}
