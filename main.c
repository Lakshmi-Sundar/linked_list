#include "main.h"
#include "main.h"

#define ASSERT( cond, format, ... ) \
   if( cond ){ \
      printf("[%s@%s] Error in %s:%d => " format "\n", __DATE__, __TIME__, __FILE__, __LINE__, ##__VA_ARGS__); \
      exit(0); \
   }

inline int listNodeCount ( listPT listP ) {
   ASSERT ( !listP, "List not allocated" );
   return listP->count;
}


void printList (listPT listP, listDirT dir) {
   ASSERT ( !listP, "List not allocated" );
   nodePT currentP    = (dir == LIST_DIR_FWD) ? listP->headP : listP->tailP; 
   while( currentP != NULL ) {
      printf("%d\n", currentP->data);
      currentP        = (dir == LIST_DIR_FWD) ? currentP->nextP : currentP->prevP;
   }
}

void insertNode ( listPT listP, int data ) {
   ASSERT ( !listP, "List not allocated" );
   // Insertion at beginning
   if(listP->headP == NULL || listP->headP->data > data) {
      nodePT nodeP        = createNode ( data );
      // headP has the address of the one it is currently pointing to.
      // so the next of your new node will be the following chain.
      if( listP->headP != NULL )
         listP->headP->prevP = nodeP;
      else
         listP->tailP     = nodeP;
      nodeP->nextP        = listP->headP;
      listP->headP        = nodeP;
      listP->count++;
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
            else
               listP->tailP        = nodeP;
            currentP->nextP        = nodeP;
            nodeP->prevP           = currentP;
            listP->count++;
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
   printList(listP, LIST_DIR_FWD);
   printList(listP, LIST_DIR_BKD);
}
