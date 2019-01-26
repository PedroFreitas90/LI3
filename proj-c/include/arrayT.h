#ifndef __MYARRAYT_H__
#define __MYARRAYT_H__

#include <stdlib.h>
#include <stdio.h>
#include <common.h>

typedef struct tagnum * TNum;
typedef struct arraytagnum* ATNum;


ATNum insere_tagnum(ATNum a, TNum t);

TNum incTNum(TNum pair);
TNum create_tnum_pair(char* fst, int snd);
void set_tag_tnum(TNum pair, char* str);
void set_num_tnum(TNum pair, int num);
char* get_tag_tnum(TNum pair);
int get_num_tnum(TNum pair);
void free_tnum(TNum pair);
TNum get_atnum_tnum(ATNum pares, int index);
long get_atnum_used(ATNum a);
long get_atnum_size(ATNum pares);
ATNum init_atnum(long N);
TNum getMax(ATNum pares);
void getOrderNum(int ocor[],int N, ATNum pares);
void bubbleTNumSort(ATNum pares);
#endif
