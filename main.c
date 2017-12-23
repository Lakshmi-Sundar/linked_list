#include "main.h"


void printList (listPT listP) {
   nodePT tempP    = listP->headP; 
   while( tempP != NULL ) {
      printf("%d\n", tempP->data);
      tempP        = tempP->nextP;
   }
}

void insertNode ( listPT listP, int data ) {
   // Insertion at beginning
   if(listP->headP == NULL || listP->headP->data > data) {
      nodePT nodeP  = createNode ( data );
      nodeP->nextP  = listP->headP;
      listP->headP  = nodeP;
   }
   // Insertion in between
   else{
      nodePT tempP  = listP->headP;
      while( tempP != NULL && tempP->data < data ) {
         // Special condition in if to check for nextP == NULL cases 
         if( tempP->data < data && ( !(tempP->nextP) || tempP->nextP->data > data ) ) {
            nodePT nodeP = createNode ( data );
            nodeP->nextP = tempP->nextP;
            tempP->nextP = nodeP;
            break;
         }
         tempP         = tempP->nextP;
      }
   }
}

nodePT createNode ( int data ) {
   nodePT nodeP = (nodePT) calloc (1,sizeof(nodeT));
   // data on RHS is the one being passed in this function
   // data on LHS is the member of nodeT data structure
   nodeP->data  = data; 
   return nodeP;
}

void main () {
   listPT listP = (listPT) calloc( 1, sizeof(listT) );

   insertNode( listP, 1 );
   insertNode( listP, 2 );
   insertNode( listP, 5 );
   printList(listP);
   insertNode( listP, 3 );
   insertNode( listP, 0 );
   printList(listP);
}
