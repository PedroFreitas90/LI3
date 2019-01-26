#ifndef _HEAPU_H_
#define _HEAPU_H_

#include <stdlib.h>
#include <string.h>

typedef struct heapu *HeapU;

HeapU initHeapU();
HeapU heap_pushU(HeapU heap, long id,long qnt);
long heap_popU(HeapU heap);
int heap_countU(HeapU heap);
void heap_freeU(HeapU heap);

#endif
