/**
 * @file heapU.c
 * @brief Ficheiro que contém a implementação de Max Heap's.
 */

#include "heapU.h"

#define PAI(i) (i-1)/2
#define ESQUERDO(i) 2*i + 1
#define DIREITO(i) 2*i + 2

struct heapu {
    long tamanho;
    long pos;
    long* qnt;
    long* ids;
};

/**
 * @brief Troca dois elementos da heap.
 * @param int posição do primeiro elemento.
 * @param int posição do segundo elemento.
 * @return HeapU alterada.
 */
static void swapU(HeapU heap,int n1,int n2);

/**
 * @brief Realiza o bubble down da Heap.
 * @param HeapU heap a alterar.
 * @return HeapU alterada.
 */
static HeapU bubbleDownU(HeapU heap);

/**
 * @brief Realiza o bubble up da heap.
 * @param HeapU heap a alterar.
 * @return HeapU alterada.
 */
static HeapU bubbleUpU(HeapU heap);

/**
 * @brief Inicia uma nova Heap.
 * @return Nova HeapU nula.
 */
HeapU initHeapU(){
    HeapU heap = malloc(sizeof(struct heapu));
    heap->tamanho = 5;
    heap->pos = 0;
    heap->qnt = malloc(5 * sizeof(long));
    heap->ids = malloc(5 * sizeof(long));
    return heap;
}

/**
 * @brief  Insere na Heap tendo como referência a quantidade.
 * @param  HeapU onde se insere.
 * @param  long id do elemento.
 * @param  long quantidade do elemento.
 * @return HeapU com o novo elemento adicionado.
 */
HeapU heap_pushU(HeapU heap, long id,long qnt){
    if(heap->tamanho == heap->pos) {
        heap->tamanho *= 2;
        heap->ids = realloc(heap->ids,sizeof(long)*heap->tamanho);
        heap->qnt = realloc(heap->qnt,sizeof(long)*heap->tamanho);
    }
  heap->ids[heap->pos] = id;
  heap->qnt[heap->pos] = qnt;
  heap = bubbleUpU(heap);
  heap->pos++;
  return heap;
}

/**
 * @brief Retorna o maior elemento da Heap.
 * @param HeapU da qual se retira o elemento.
 * @return Id do elemento removido.
 */
long heap_popU(HeapU heap) {
    if(heap->pos==0) return 0;
    long r = heap->ids[0];
    heap->pos--;
    heap->qnt[0] = heap->qnt[(heap->pos)];
    heap->ids[0] = heap->ids[(heap->pos)];

    heap = bubbleDownU(heap);

    return r;
}

static HeapU bubbleDownU(HeapU heap){
    int i, m, r;
    i=0;
    int n = heap->tamanho;
    while(ESQUERDO(i) < n){
          if(DIREITO(i) < n){
            r = (heap->qnt[(ESQUERDO(i))] - (heap->qnt[(DIREITO(i))]));
            if (r > 0) m = ESQUERDO(i);
            else m = DIREITO(i);
          }
          else m = ESQUERDO(i);

          if((heap->qnt[i]) - (heap->qnt[m]) < 0){
              swapU(heap,i,m);
              i = m;
          }
          else return heap;
      }
      return heap;
  }



static HeapU bubbleUpU(HeapU heap){
    int i = heap->pos;
    while(i > 0 && (heap->qnt[PAI(i)] < heap->qnt[i])){
            swapU(heap,i,PAI(i));
            i = PAI(i);
        }
        return heap;
}


static void swapU(HeapU heap,int n1,int n2) {
    long id = heap->ids[n1];
    long qnt = heap->qnt[n1];
    heap->ids[n1] = heap->ids[n2];
    heap->qnt[n1] = heap->qnt[n2];
    heap->ids[n2] = id;
    heap->qnt[n2] = qnt;
}

/**
 * @brief  Retorna o número de elementos de uma Heap.
 * @param  HeapU heap.
 * @return Número de elementos da heap.
 */
int heap_countU(HeapU heap){
    return heap->pos;
}

/**
  *@brief   Liberta a memória alocada por uma HeapU.
  *@param   void* apontador para a HeapU a limpar da memória.
*/
void heap_freeU(HeapU heap){
    free(heap->qnt);
    free(heap->ids);
    free(heap);
}
