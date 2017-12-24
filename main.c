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


//// 1 => Success
//// 0 => Failure
//int deleteNode ( listPT listP, int data ) {
//   // Defaultig success to failure
//   int success        = 0;
//   nodePT currentP    = listP->headP;
//   // Traversal until data found with advanced loop ending for not-found data
//   while( currentP != NULL  ){
//      if( currentP->data == data && currentP->data <= data ){
//         // Data found! Modify links and free it
//         // Take care of boundary conditions
//         if( currentP == listP->headP ){
//            // Data to be deleted is first node
//            listP->headP = currentP->nextP;
//         }
//         if( currentP == listP->tailP ){
//            // Data to be deleted is last node
//            listP->tailP = currentP->prevP;
//         }
//
//         // Link mods required
//         // What if ->prevP/->nextP are null?
//         if( currentP->prevP != NULL )
//            currentP->prevP->nextP = currentP->nextP;
//         if( currentP->nextP != NULL )
//            currentP->nextP->prevP = currentP->prevP;
//
//         success                   = 1;
//         listP->count--;
//         free( currentP );
//         break;
//      }
//      currentP                     = currentP->nextP;
//   }
//   return success;
//}

// 1 => Success
// 0 => Failure
int deleteNode (listPT listP, int data ) {
   //1. Traverse from head to where you want to delete the node
   //2. Update its prevP and nextP, and update the neighbouring links
   //3. Free the deleted node
   ASSERT ( !listP, "List not allocated" );
   nodePT currentP = listP->headP;
   while(currentP != NULL) {
      if(currentP->data == data) {
         //1. Deleting the very first node
         if(currentP->prevP == NULL) {
            if(currentP->nextP != NULL) {
               currentP->nextP->prevP = NULL;
            }
            else 
               listP->tailP           = currentP->nextP;
            listP->headP           = currentP->nextP;
       
         }
         //2. Deleting the last node
         else if(currentP->nextP == NULL) {
            if(currentP->prevP != NULL) {
               currentP->prevP->nextP = NULL;
            }
            listP->tailP           = currentP->prevP;
         }
         //3. Deleting in between
         else {
            currentP->prevP->nextP = currentP->nextP;
            currentP->nextP->prevP = currentP->prevP;
         }
         listP->count--;
         free(currentP);
         return 1;
      }
      currentP = currentP->nextP;
   }
   return 0;
}

int insertNode ( listPT listP, int data ) {
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
      return 1;
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
            return 1;
         }
         currentP         = currentP->nextP;
      }
   }
   return 0;
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
   printf("\n");
   //deleteNode( listP, 5 );
   //deleteNode( listP, 1 );
   //deleteNode( listP, 3 );
   //deleteNode( listP, 3 );
   //deleteNode( listP, 2 );
   //deleteNode( listP, 0 );
   //insertNode( listP, 1 );
   //insertNode( listP, 2 );
   //insertNode( listP, 5 );
   //insertNode( listP, 3 );
   //insertNode( listP, 0 );
   //insertNode( listP, 3 );
   printList(listP, LIST_DIR_FWD);
   printf("\n");
   printList(listP, LIST_DIR_BKD);
}
