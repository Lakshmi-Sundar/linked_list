#include "main.h"


void printList (listPT listP) {
   nodePT currentP    = listP->headP; 
   while( currentP != NULL ) {
      printf("%d\n", currentP->data);
      currentP        = currentP->nextP;
   }
}

void insertNode ( listPT listP, int data ) {
   // Insertion at beginning
   if(listP->headP == NULL || listP->headP->data > data) {
      nodePT nodeP        = createNode ( data );
      // headP has the address of the one it is currently pointing to.
      // so the next of your new node will be the following chain.
      if( listP->headP != NULL )
         listP->headP->prevP = nodeP;
      nodeP->nextP        = listP->headP;
      listP->headP        = nodeP;
   }
   // Insertion in between
   else{
      nodePT currentP  = listP->headP;
      while( currentP != NULL && currentP->data < data ) {
         // Special condition in if to check for nextP == NULL cases 
         if( currentP->data < data && ( !(currentP->nextP) || currentP->nextP->data > data ) ) {
            nodePT nodeP           = createNode ( data );
            nodeP->nextP           = currentP->nextP;
            // The previous pointer of your next node must point to the one you are inserting
            // The next pointer of the current node must point to the one you are inserting
            if(currentP->nextP != NULL)
               currentP->nextP->prevP = nodeP;
            currentP->nextP        = nodeP;
            nodeP->prevP           = currentP;
            break;
         }
         currentP         = currentP->nextP;
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
   insertNode( listP, 3 );
   insertNode( listP, 0 );
   printList(listP);
}
