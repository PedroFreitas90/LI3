/**
 * @file util.c
 * @brief Ficheiro que contém a implementação de estruturas e funções úteis para resolução de querys.
 */

#include "util.h"

struct respostas{
  Heap h;
  Key parent;
};

struct duplo{
  LONG_list ll;
  TNum tnum;
  int pos;
};



/**
  *@brief   Retorna uma estrutura ResPost inicializada.
  *@param   long id de uma pergunta.
  *return   ResPost estrutura inicializada.
*/
ResPost initResPost(long pid){
  ResPost res = (ResPost)malloc(sizeof(struct respostas));
  res->h = initHeap();
  res->parent = createKey(pid);
  return res;
}

/**
  *@brief   Retorna o ID guardado na estrutura.
  *@param   ResPost.
  *return   Key ID.
*/
Key getResPostParent(ResPost r){
    return r->parent;
}

/**
  *@brief   Retorna a heap guardada na estrutura.
  *@param   ResPost.
  *return   Heap.
*/
Heap getResPostHeap(ResPost r){
    return r->h;
}

void freeResPost(ResPost r){
  heap_free(r->h);
  freekey(r->parent);
  free(r);
}

/**
  *@brief   Função que inicializa uma LONG_list.
  *@param   int tamanho da LONG_list.
  *return   LONG_list criada e inicializada.
*/
LONG_list init_ll(int N){
  LONG_list ll = create_list(N);
  int i = 0;
  while(i < N) {
    set_list(ll,i,-2);
    i++;
  }
  return ll;
}

/**
  *@brief   Função que inicializa a estrutura Duplos.
  *@param   int tamanho da LONG_list do duplos.
  *return   Duplos inicializado
*/
Duplos initDuplos(int N){
  Duplos res = (Duplos)malloc(sizeof(struct duplo));
  res->ll = init_ll(N);
  res->tnum = create_tnum_pair(NULL,0);
  res->pos = -1;
  return res;
}

/**
  *@brief   Função que altera o campo "pos" de um Duplos.
  *@param   int número a ser introduzido no campo "pos" do Duplos.
*/
void set_duplos_pos(Duplos dup, int i){
  dup->pos = i;
}

/**
  *@brief   Função que introduz um par Tag-Num em um Duplos.
  *@param   Duplos duplo de LONG_list e TNum.
  *return   Duplos inicializado
*/
Duplos set_duplos_tnum(Duplos dup, TNum tn){
  if(dup)
    dup->tnum = tn;
  return dup;
}

/**
  *@brief   Função cria e preenche os parâmetros de um Duplos.
  *@param   LONG_list lista a ser introduzida.
  *@param   TNum par Tag-Num a ser introduzido.
  *@param   int tamanho da LONG_list.
  *@param   int índice a ser introduzido.
  *return   Duplos criado.
*/
Duplos insere_Duplos(LONG_list ll, TNum tn,int N, int i){
  Duplos res = initDuplos(N);
  res->ll = ll;
  res->tnum = tn;
  res->pos = i;
  return res;
}

/**
  *@brief   Função que retorna a LONG_list de um Duplos.
  *@param   Duplos duplo.
  *return   LONG_list do Duplos.
*/
LONG_list get_duplos_ll(Duplos dup){
  if(dup)
    return dup->ll;
  return NULL;
}

/**
  *@brief   Função que retorna um par Tag-Num de um Duplos.
  *@param   Duplos duplo.
  *return   TNum par Tag-Num.
*/
TNum get_duplos_tnum(Duplos dup){
  if(dup) return dup->tnum;
  return NULL;
}

/**
  *@brief   Função que retorna o parâmetro 'pos' de um Duplos.
  *@param   Duplos duplo.
  *return   int inteiro do parâmetro 'pos' de um Duplos.
*/
int get_duplos_pos(Duplos dup){
  if (dup) return dup->pos;
  return -1;
}

/**
  *@brief   Função que copia um array de strings.
  *@param   char** Array de strings.
  *return   char** Array de strings copiado.
*/
char** mystrdups(char** s) {
    if(!s) return NULL;
    int l = nTags(s);
    char** n=malloc((l+1)*sizeof(char*));
    if (n == NULL){
        printf("Algo está errado\n");
        return NULL;
    }
    int i = 0;
    while(s[i]!=NULL){
       n[i]= mystrdup(s[i]);
       i++;
    }
    n[i] = NULL;
    return n;
}
