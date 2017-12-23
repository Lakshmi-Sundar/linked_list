#ifndef _MAIN_H //{
#define _MAIN_H

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

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

nodePT createNode ( int data );
void printList (listPT listP, listDirT dir);
#endif //} _MAIN_H
