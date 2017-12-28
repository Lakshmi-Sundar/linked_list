/*C**********************************************************************
* FILENAME    :       ll.c 
* DESCRIPTION :       Linked list library routines
* NOTES       :       *Caution* Data in listP might change based 
*                     on functions.
*
* AUTHOR      :       Vijayalakshmi Sundar     START DATE :   22 Dec 17
*
* CHANGES :
*
*C***********************************************************************/

#include "ll.h"

#define ASSERT( cond, format, ... ) \
   if( cond ){ \
      printf("[%s@%s] Error in %s:%d => " format "\n", __DATE__, __TIME__, __FILE__, __LINE__, ##__VA_ARGS__); \
      exit(0); \
   }

/*!public*/
listPT createList()
/*!endpublic*/
{
   return calloc (1, sizeof(listT));
}

/*!public*/
void destroyList( listPT listP, void (*destroyP)(void*))
/*!endpublic*/
{
   ASSERT ( !listP, "List not allocated" );
   nodePT currentP = listP->headP;
   while( currentP != NULL ) {
      listP->headP    = currentP->nextP;
      (*destroyP)( currentP->data );
      free( currentP );
      currentP        = listP->headP;
   }
   free( listP );
}

static nodePT createNode ( void* data ) {
   nodePT nodeP = (nodePT) calloc (1,sizeof(nodeT));
   // data on RHS is the one being passed in this function
   // data on LHS is the member of nodeT data structure
   nodeP->data  = data; 
   return nodeP;
}

/*!public*/
int listNodeCount ( listPT listP ) 
/*!endpublic*/
{
   ASSERT ( !listP, "List not allocated" );
   return listP->count;
}


/*!public*/
void printList (listPT listP, listDirT dir) 
/*!endpublic*/
{
   ASSERT ( !listP, "List not allocated" );
   nodePT currentP    = (dir == LIST_DIR_FWD) ? listP->headP : listP->tailP; 
   while( currentP != NULL ) {
      printf("%d\n", *((int*)(currentP->data)));
      currentP        = (dir == LIST_DIR_FWD) ? currentP->nextP : currentP->prevP;
   }
}

//extern void func( void*, void* );

/*!public*/
void forEach (listPT listP, void* userData, void (*funcP) (void*, void*) ) 
/*!endpublic*/
{
   ASSERT ( !listP, "List not allocated" );
   nodePT currentP = listP->headP;
   while( currentP != NULL ) {
      (*funcP) ( currentP->data, userData );
      currentP = currentP->nextP;
   }
}

/*!public*/
bool pushHead ( listPT listP, void* data ) 
/*!endpublic*/
{
   ASSERT ( !listP, "List not allocated" );
   nodePT nodeP = createNode(data);
   //1. Insert when headP == NULL
   if(listP->headP != NULL) {
      listP->headP->prevP = nodeP;
      nodeP->nextP        = listP->headP;
   }
   else
      listP->tailP        = nodeP;
   listP->headP           = nodeP;
   listP->count++;
   return true;
}

/*!public*/
bool pushTail ( listPT listP, void* data ) 
/*!endpublic*/
{
   ASSERT ( !listP, "List not allocated" );
   nodePT nodeP = createNode(data);
   if(listP->tailP != NULL) {
      listP->tailP->nextP = nodeP;
      nodeP->prevP        = listP->tailP;
   }
   else
      listP->headP        = nodeP;
   listP->tailP           = nodeP;
   listP->count++;
   return true;
}

/*!public*/
bool pushNth ( listPT listP, int n, void* data ) 
/*!endpublic*/
{
   ASSERT ( !listP, "List not allocated" );
   if(!(n >= 0 && n <= listP->count))
      return false;

   if(n == listP->count) 
      return pushTail ( listP, data );
   if(n == 0)
      return pushHead ( listP, data );

   nodePT nodeP     = createNode(data);
   nodePT currentP  = listP->headP;

#ifdef PUSH_POP_PERF_HACK
   if(n <= (listP->count)/2) {
      currentP  = listP->headP;
      while(--n) currentP = currentP->nextP;
   }
   else{
      currentP  = listP->tailP;
      while( listP->count - (n++) ) currentP = currentP->prevP;
   }
#else
   while(--n) currentP = currentP->nextP;
#endif

   ASSERT ( currentP->nextP == NULL, "Unexpected next null found" );
   nodeP->nextP           = currentP->nextP;
   currentP->nextP->prevP = nodeP;
   currentP->nextP        = nodeP;
   nodeP->prevP           = currentP;
   listP->count++;
   return true;
}

/*!public*/
void* popHead (listPT listP) 
/*!endpublic*/
{
   ASSERT ( !listP, "List not allocated" );
   if(listP->headP == NULL) return NULL;
   void* data            = listP->headP->data;
   nodePT deleteP        = listP->headP;
   listP->headP          = listP->headP->nextP;
   if(listP->headP != NULL) listP->headP->prevP = NULL;
   else                     listP->tailP        = NULL;
   listP->count--;
   free(deleteP);
   return data;
}

/*!public*/
void* popTail (listPT listP) 
/*!endpublic*/
{
   ASSERT ( !listP, "List not allocated" );
   if(listP->tailP == NULL) return NULL;
   void* data            = listP->tailP->data;
   nodePT deleteP        = listP->tailP;
   listP->tailP          = listP->tailP->prevP;
   if(listP->tailP != NULL) listP->tailP->nextP = NULL;
   else                     listP->headP        = NULL;
   listP->count--;
   free(deleteP);
   return data;
}

/*!public*/
void* popNth (listPT listP, int n) 
/*!endpublic*/
{
   ASSERT ( !listP, "List not allocated" );
   if(!(n >= 0 && n <= listP->count)) return NULL;
   if(n == listP->count)              return popTail (listP);
   if(n == 0)                         return popHead (listP);
   nodePT currentP         = listP->headP;

#ifdef PUSH_POP_PERF_HACK
   if(n <= (listP->count)/2) {
      currentP  = listP->headP;
      while(n--) currentP = currentP->nextP;
   }
   else{
      currentP  = listP->tailP;
      while( listP->count - (++n) ) currentP = currentP->prevP;
   }
#else
   while(n--) currentP = currentP->nextP;
#endif

   ASSERT ( currentP->nextP == NULL, "Unexpected next null found" );
   ASSERT ( currentP->prevP == NULL, "Unexpected prev null found" );
   void* data                = currentP->data;
   currentP->prevP->nextP  = currentP->nextP;
   currentP->nextP->prevP  = currentP->prevP;
   listP->count--;
   free(currentP);
   return data;
}

