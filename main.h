#include<stdio.h>
#include<malloc.h>

typedef struct _nodeT* nodePT;
typedef struct _listT* listPT;

typedef struct _nodeT {
   nodePT nextP;
   nodePT prevP;
   int data;
}nodeT;

typedef struct _listT{
   nodePT headP;

   // TODO: Placeholder
   nodePT tailP;
   int    count;
}listT;

nodePT createNode ( int data );
