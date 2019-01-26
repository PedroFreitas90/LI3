/**
 * @file mypost.c
 * @brief Ficheiro que contém a implementação de Posts.
 */

#include "mypost.h"

struct post{
  long id;
  int type; // 1 ou 2 (pergunta ou resposta)
  long pid;
  int score; 
  int vcount;
  Date date;
  long owner;
  int ownerRep;
  int numcom;
  int nres;
  char * titulo;
  char** tag;
  int ntags;
};

struct arrayd{
  Post* array;
  long used;
  long size;
  long res;
  long per;
};

/**
  *@brief   Liberta a memória alocada por um Date.
  *@param   void* apontador para uma data.
*/
void destroyDate (void *d){
  Date aux = (Date) d;
  free_date(aux);
}

/**
  *@brief   Cria um array dinâmico que guarda Posts, e o número de respostas e perguntas que existem nesse array de Posts.
  *@param   long tamanho a dar ao array.
*/
ArrayD createArray(long comp){
  ArrayD a = malloc (sizeof(struct arrayd));
  a->array = malloc(comp * sizeof(struct post));
  a->used = 0;
  a->size = comp;
  a->res = 0;
  a->per = 0;
  return a;
}

/**
  *@brief   Retorna o número de perguntas contidas num dado array dinâmico.
  *@param   ArrayD array dinâmico.
  *return   long número de perguntas contidas no array de Posts.
*/
long getPer(ArrayD d){
  if(d) return d->per;
  return -1;
}

/**
  *@brief   Retorna o número de respostas contidas num dado array dinâmico.
  *@param   ArrayD array dinâmico.
  *return   long número de respostas contidas no array de Posts.
*/
long getRes(ArrayD d){
  if(d) return d->res;
  return -1;
}

/**
  *@brief   Retorna o tamanho de um dado array dinâmico.
  *@param   ArrayD array dinâmico.
  *return   long tamanho do array.
*/
long getSize(ArrayD d){
  if(d) return d->size;
  else return -1;
}

/**
  *@brief   Retorna o número de Posts num dado array.
  *@param   ArrayD array dinâmico.
  *return   long número de Posts contidos no array.
*/
long getUsed(ArrayD d){
  if(d) return d->used;
  else return -1;
}

/**
  *@brief   Retorna o Post na posição i de um dado array.
  *@param   ArrayD array dinâmico.
  *@param   int índice i.
  *return   Post na posição i do array.
*/
Post getInd(ArrayD d, int i){
  if (d)
    return (d->array[i]);
  else return NULL;
}

/**
  *@brief   Insere um Post no array.
  *@param   ArrayD array dinâmico.
  *@param   Post post.
*/
void insereArray(ArrayD a, Post p){
  if (a-> used == a->size){
    a->size *= 2;
    a->array = realloc (a->array, a->size * (sizeof(struct post)));
  }
  int type = getPostType(p);
  if (type == 1) a->per++;
  if (type == 2) a->res++;
  a->array[a->used++] = p;
}

/**
  *@brief   Liberta a memória alocada pelo array dinâmico.
  *@param   void* apontador para o array.
*/
void freeArray(void *a){
  ArrayD aux = (ArrayD) a;
  if(aux){
    free(aux->array);
    free(aux);
  }
}

/**
  *@brief   Inicializa um Post.
  *@return  Post inicializado.
*/
Post initPost(){
  Post p = malloc(sizeof(struct post));
  return p;
}

/**
  *@brief   Cria um Post.
  *@param   long id do Post.
  *@param   int tipo do Post.
  *@param   long parent id do Post.
  *@param   int score do Post.
  *@param   int view count do Post.
  *@param   Date data de criação do Post.
  *@param   long id do User que criou o Post.
  *@param   int reputação do User que criou o Post.
  *@param   int número de comentários do Post.
  *@param   int de respostas do Post.
  *@param   char* título do Post.
  *@param   char** array com as tags do Post.
  *@param   int número de tags do Post.
  *@return  Post criado.
*/
Post createPost(long id, int type, long pid, int score, int vcount, Date date, long owner, int ownerRep, int numcom, int nres, char* titulo, char** tags, int ntags){
    Post p = malloc(sizeof(struct post));
    p->id = id;
    p->type = type;
    p->pid = pid;
    p->score = score;
    p->vcount = vcount;
    p->date = date;
    p->owner = owner;
    p->ownerRep = ownerRep;
    p->numcom = numcom;
    p->nres = nres;
    p->titulo = mystrdup(titulo);
    p->tag= mystrdups(tags);
    p->ntags = ntags;
    return p;
}

/**
  *@brief   Retorna o número de tags de um dado Post.
  *@param   Post post.
  *@return  int número de tags contidas nesse Post.
*/
int getPostNTags(Post p){
    if(p)
      return p->ntags;
    return 0;
}

/**
  *@brief   Retorna o array das tags de um dado Post.
  *@param   Post post.
  *@return  char** array das tags contidas nesse Post.
*/
char** getPostTags(Post p){
    if(p) return mystrdups(p->tag);
    return NULL;
}

/**
  *@brief   Retorna o id de um dado Post.
  *@param   Post post.
  *@return  long id do Post.
*/
long getPostId(Post p){
  if(p) return p->id;
  return -1;
}

/**
  *@brief   Retorna o tipo de um dado Post.
  *@param   Post post.
  *@return  int tipo do Post.
*/
int getPostType(Post p){
  if(p) return p->type;
  return -1;
}

/**
  *@brief   Retorna o id do Post que é resposta a um dado Post.
  *@param   Post post.
  *@return  long id do Post que responde ao Post dado.
*/
long getPid(Post p){
  if(p) return p->pid;
  return -1;
}

/**
  *@brief   Retorna o score de um dado Post.
  *@param   Post post.
  *@return  int score do Post.
*/
int getPostScore(Post p){
  if(p) return p->score;
  return -1;
}

/**
  *@brief   Retorna o view count do Post.
  *@param   Post post.
  *@return  int view count do Post.
*/
int getPostVCount(Post p){
  if(p) return p->vcount;
  return -1;
}

/**
  *@brief   Retorna a data de criação de um dado Post.
  *@param   Post post.
  *@return  Date data do Post.
*/
Date getPostDate(Post p){
  if (p){
  int day = get_day(p->date);
  int month = get_month(p->date);
  int year = get_year(p->date);
  Date d = createDate(day,month,year);
  return d;
  }
  return NULL;
}

/**
  *@brief   Retorna o criador de um dado Post.
  *@param   Post post.
  *@return  long id do criador do Post.
*/
long getPostOwner(Post p){
  if(p) return p->owner;
  return -1;
}

/**
  *@brief   Retorna a reputação do criador de um dado Post.
  *@param   Post post.
  *@return  int reputação do criador do Post.
*/
int getPostOwnerRep(Post p){
  if(p) return p->ownerRep;
  return -1;
}

/**
  *@brief   Retorna o número de comentários de um dado Post.
  *@param   Post post.
  *@return  int número de comentários do Post.
*/
int getPostNumCom(Post p) {
  if (p) return p->numcom;
  return -1;
}

/**
  *@brief   Retorna o número de respostas de um dado Post.
  *@param   Post post.
  *@return  int número de respostas do Post.
*/
int getPostNRes(Post p) {
  if (p) return p->nres;
  else return -2;
}


/**
  *@brief   Retorna o título de um dado Post.
  *@param   Post post.
  *@return  char* título do post.
*/
char* getPostTitulo(Post p){
  if(p) return mystrdup(p->titulo);
  return NULL;
}

/**
  *@brief   Retorna a Tag de um determinado índice.
  *@param   Post post.
  *@param   int índice.
  *@return  char* Tag da posição index.
*/
char* getTagI(Post p,int index){
  if(p)
      return mystrdup(p->tag[index]);
  return NULL;
}

/**
  *@brief   Retorna a média ponderada da classificação de uma resposta.
  *@param   Post post.
  *@return  double classificação da resposta.
*/
double calcMedia(Post p){
    int sc = getPostScore(p);
    int com = getPostNumCom(p);
    int rep = getPostOwnerRep(p);
    double media = (0.65 * sc) + (0.25 * rep) + (0.1 * com);
    return media;
}

/**
  *@brief   Liberta a memória alocada por um Post.
  *@param   void* apontador para o Post a limpar da memória.
*/
void freePost(void *p){
  Post aux = (Post) p;
  if(aux) {
    free_date(aux->date);
    free(aux->titulo);
    for(int i=0; i<aux->ntags; i++)
        free(aux->tag[i]);
    free(aux->tag);
    free(aux);
  }
}
