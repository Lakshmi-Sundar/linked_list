/*H**********************************************************************
* FILENAME    :       ll.h 
* DESCRIPTION :       Linked list library header file 
* NOTES       :       -NA-
*
* AUTHOR      :       Vijayalakshmi Sundar     START DATE :   22 Dec 17
*
* CHANGES :
*
*H***********************************************************************/

#ifndef _LL_H //{
#define _LL_H

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct _nodeT* nodePT;
typedef struct _listT* listPT;

typedef struct _nodeT {
   nodePT nextP;
   nodePT prevP;
   int data;
}nodeT;

typedef struct _listT{
   nodePT headP;
   nodePT tailP;
   int    count;
}listT;

typedef enum _listDirT{
   LIST_DIR_FWD = 1,
   LIST_DIR_BKD = 0
}listDirT;

//--------------------------- PROTOTYPES BEGIN ---------------------
int listNodeCount ( listPT listP );
void printList (listPT listP, listDirT dir);
void func( int *dataP, int userData );
void forEach (listPT listP, int userData);
bool pushHead ( listPT listP, int data );
bool pushTail ( listPT listP, int data );
bool pushNth ( listPT listP, int n, int data );
int popHead (listPT listP);
int popTail (listPT listP);
int popNth (listPT listP, int n);
//---------------------------- PROTOTYPES END ----------------------

#endif //} _LL_H
