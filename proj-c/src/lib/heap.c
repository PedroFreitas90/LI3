/**
 * @file heap.c
 * @brief Ficheiro que contém a implementação de Max Heap's de Posts.
 */

#include "heap.h"

#define PAI(i) (i-1)/2
#define ESQUERDO(i) 2*i + 1
#define DIREITO(i) 2*i + 2

struct heap {
    int tamanho;
    int pos;
    char* pal;
    Post* posts;
};

/**
 * @brief Compara duas datas.
 * @param Date data1.
 * @param Date data2.
 * @return int resultado da comparação (-1 se data1 for a mais recente, 1 se data2 for a mais recente ou 0 se forem iguais).
 */
 int maisRecente(Date date1, Date date2);

/**
 * @brief Troca dois elementos da heap.
 * @param int posição do primeiro elemento.
 * @param int posição do segundo elemento.
 * @return Heap alterada.
 */
static Heap swap(Heap heap,int n1,int n2);

/**
 * @brief Realiza o bubble down da heap.
 * @param Heap heap a alterar.
 * @return Heap alterada.
 */
static Heap bubbleDown(Heap heap,int n, char ord);

/**
 * @brief Realiza o bubble up da heap.
 * @param Heap heap a alterar.
 * @return Heap alterada.
 */
static Heap bubbleUp(Heap heap,int i, char ord);


//Função devolve -1 se a primeira data for mais recente e 1 se a segunda data for a mais recente
int maisRecente(Date date1, Date date2){
  int y1 = get_year(date1);
  int m1 = get_month(date1);
  int d1 = get_day(date1);
  int y2 = get_year(date2);
  int m2 = get_month(date2);
  int d2 = get_day(date2);
  if(y1 > y2) return -1;
  if(y2 > y1) return 1;
  if(y1 == y2){
    if(m1 > m2) return -1;
    if(m2 > m1) return 1;
    if(m1 == m2){
      if(d1 > d2) return -1;
      if(d2 > d1) return 1;
    }
  }
  return 0;
}

/**
 * @brief Inicia uma nova heap de posts.
 * @return Heap inicializada.
 */
Heap initHeap(){
    Heap heap = malloc(sizeof(struct heap));
    heap->tamanho = 5;
    heap->pos = 0;
    heap->posts = malloc(5 * sizeof(Post));
    heap->pal = NULL;
    return heap;
}

/**
 * @brief  Inicia uma nova heap de posts que guarda adicionalmente uma dada palavra.
 * @param  char* palavra.
 * @return Heap inicializada.
 */
Heap initHeapPal(char* word){
    Heap heap = malloc(sizeof(struct heap));
    heap->tamanho = 5;
    heap->pos = 0;
    heap->posts = malloc(5 * sizeof(Post));
    heap->pal = malloc(5 * sizeof(word));
    heap->pal = mystrdup(word);
    return heap;
}

/**
 * @brief  Devolve a palavra guardada na heap.
 * @param  Heap heap.
 * @return char* palavra.
 */
char* getHeapPal(Heap h){
  return mystrdup(h->pal);
}

/**
 * @brief  Insere um post na heap tendo como referência o parâmetro da ordenação.
 * @param  Heap heap.
 * @param  Post post.
 * @param  char caracter que determina a ordenação (D-Data do post, S-Score do post, R-Número de respostas do post, M-Média ponderada da classificação do post).
 * @return Heap com o novo Post adicionado.
 */
Heap heap_push(Heap heap, Post post, char ord){
    if(heap->tamanho-1 == heap->pos) {
        heap->tamanho *= 2;
        heap->posts = realloc(heap->posts,heap->tamanho *sizeof(Post));
    }
    heap->posts[heap->pos] = post;
    heap = bubbleUp(heap,heap->pos,ord);
    heap->pos++;
    return heap;
}

/**
 * @brief Retorna o "maior" post segundo a ordenação dada.
 * @param Heap heap de todos os posts.
 * @param char ordenação segundo a qual a Heap se ordena.
 * @return Post removido.
 */
Post heap_pop(Heap heap, char ord) {
    if(heap->pos==0) return 0;
    Post r = heap->posts[0];
    heap->pos--;
    heap->posts[0] = heap->posts[(heap->pos)];

    heap = bubbleDown(heap,heap->pos,ord);

    return r;
}

// n -> tamanho do array
// ord pode ser 'D' (data masi recente) ou 'S' (score mais alto)
static Heap bubbleDown(Heap heap, int n, char ord){
    int i, m, r;
    Date de = NULL;
    Date dd = NULL;
    Date d1 = NULL;
    Date d2 = NULL;
    i=0;
    if(ord == 'D'){
      while(ESQUERDO(i) < n){
          if(DIREITO(i) < n){
            r = maisRecente((de =getPostDate(heap->posts[(ESQUERDO(i))])), (dd = getPostDate(heap->posts[(DIREITO(i))])));
            free_date(de);
            free_date(dd);
            if (r <= 0) m = ESQUERDO(i);
            else m = DIREITO(i);
          }
          else m = ESQUERDO(i);

          //Se a data do post de indice i(pai) for menos recente do que a data do post de indice m(um dos filhos), fazer swap
          if(maisRecente((d1 = getPostDate(heap->posts[i])), (d2 = getPostDate(heap->posts[m]))) >= 0){
              free_date(d1);
              free_date(d2);
              heap = swap(heap,i,m);
              i = m;
          }
          else{
              free_date(d1);
              free_date(d2); 
              return heap;
          }
        }
      return heap;
    }
    else if(ord == 'S'){
      while(ESQUERDO(i) < n){
          if(DIREITO(i) < n){
            r = (getPostScore(heap->posts[(ESQUERDO(i))])) - (getPostScore(heap->posts[(DIREITO(i))]));
            if (r > 0) m = ESQUERDO(i);
            else m = DIREITO(i);
          }
          else m = ESQUERDO(i);

          //Se a data do post de indice i(pai) for menos recente do que a data do post de indice m(um dos filhos), fazer swap
          if((getPostScore(heap->posts[i])) - (getPostScore(heap->posts[m])) < 0){
              heap = swap(heap,i,m);
              i = m;
          }
          else return heap;
      }
      return heap;
    }
    else{
      while(ESQUERDO(i) < n){
          if(DIREITO(i) < n){
            r = (getPostNRes(heap->posts[(ESQUERDO(i))])) - (getPostNRes(heap->posts[(DIREITO(i))]));
            if (r > 0) m = ESQUERDO(i);
            else m = DIREITO(i);
          }
          else m = ESQUERDO(i);

          //Se a data do post de indice i(pai) for menos recente do que a data do post de indice m(um dos filhos), fazer swap
          if((getPostNRes(heap->posts[i])) - (getPostNRes(heap->posts[m])) < 0){
              heap = swap(heap,i,m);
              i = m;
          }
          else return heap;
      }
      return heap;
    }
}


static Heap bubbleUp(Heap heap, int i, char ord){
    if(ord == 'D'){
      Date dpai = NULL;
      Date di = NULL; //filho é mais recente ou seja, score do filho é maior
      while(i > 0 && maisRecente(dpai = getPostDate(heap->posts[PAI(i)]), di = getPostDate(heap->posts[i])) == 1){
          free_date(dpai);
          free_date(di);
          heap=swap(heap,i,PAI(i)); 
          i = PAI(i);
      } 
      if(i>0){
          free_date(dpai);
          free_date(di);
      }
      return heap;
    } else if(ord == 'S'){
        while(i > 0 && (getPostScore(heap->posts[PAI(i)]) - (getPostScore(heap->posts[i]))) < 0){
            heap=swap(heap,i,PAI(i));
            i = PAI(i);
        }
        return heap;
    }
    else{
      while(i > 0 && (getPostNRes(heap->posts[PAI(i)]) - (getPostNRes(heap->posts[i]))) < 0){
          heap=swap(heap,i,PAI(i));
          i = PAI(i);
      }
      return heap;
    }
}


static Heap swap(Heap heap,int n1,int n2) {
    Post p = heap->posts[(n1)];
    heap->posts[(n1)] = heap->posts[(n2)];
    heap->posts[(n2)] = p;
    return heap;
}

/**
 * @brief  Retorna o número de posts que uma dada heap contém.
 * @param  Heap heap.
 * @return int número de Posts na heap.
 */
int heap_count(Heap heap){
    return heap->pos;
}

/**
 * @brief  Retorna o número de perguntas e respostas que uma dada heap de posts contém.
 * @param  Heap heap.
 * @return int número de posts na heap.
 */
int cont_RP (Heap heap){
  int i,count = 0;
  for(i=0; i< heap->pos; i++){
    if(getPostType(heap->posts[i]) == 1 || getPostType(heap->posts[i]) == 2)
      count++;
  }
  return count;
}


/**
 * @brief  Retorna o Post que se encontrada num indice i de uma dada heap.
 * @param  Heap heap.
 * @param  int i.
 *return   Post na posição i da heap.
 */

Post getIndP(Heap h, int i){
    if (h)
        return (h->posts[i]);
    else return NULL;
}

/**
  *@brief   Liberta a memória alocada por uma Heap.
  *@param   void* apontador para a heap a limpar da memória.
*/
void heap_free(Heap heap){
    free(heap->posts);
    free(heap);
}

void heapPal_free(Heap heap){
    free(heap->posts);
    free(heap->pal);
    free(heap);
}
