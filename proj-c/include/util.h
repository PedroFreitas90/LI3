#ifndef __UTIL_H__
#define __UTIL_H__

#include "arrayT.h"
#include "heap.h"
#include "list.h"
#include "key.h"
#include "parser.h"


typedef struct respostas *ResPost;
typedef struct duplo *Duplos;

ResPost initResPost(long pid);
Key getResPostParent(ResPost r);
Heap getResPostHeap(ResPost r);
void freeResPost(ResPost r);
LONG_list init_ll(int N);
Duplos initDuplos(int N);
void set_duplos_pos(Duplos dup, int i);
Duplos set_duplos_tnum(Duplos dup, TNum tn);
Duplos insere_Duplos(LONG_list ll, TNum tn,int N, int i);
LONG_list get_duplos_ll(Duplos dup);
TNum get_duplos_tnum(Duplos dup);
int get_duplos_pos(Duplos dup);
char** mystrdups(char** s);


#endif
