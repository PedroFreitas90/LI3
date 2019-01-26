/**
 * @file mypost.c
 * @brief Ficheiro que contém a implementação de Users.
 */

#include "myuser.h"

struct userint{
  long id;
  int reputacao;
  char* nome;
  char* bio;
  int nposts;
  Heap uposts;
};

/**
  *@brief   Cria um User.
  *@param   long id do User.
  *@param   int reputação do User.
  *@param   char* nome do User.
  *@param   char* biografia do User.
  *@param   int número de Posts do User.
  *@param   Heap dos Posts do User.
  *@return  User criado.
*/
User mycreateUser(long id, int reputacao, char* nome, char* bio, int nposts, Heap uposts){
  if(id>=-1){
    User u = malloc(sizeof(struct userint));
    u->id = id;
    u->reputacao = reputacao;
    u->nome = mystrdup(nome);
    u->bio = mystrdup(bio);
    u->nposts = nposts;
    u->uposts = uposts;
    return u;
  }
  return NULL;
}

/**
  *@brief   Retorna a heap dos posts de um dado User.
  *@param   User.
  *@return  Heap dos posts do User.
*/
Heap getUserHeap(User u){
  if(u) return u->uposts;
  return NULL;
}

/**
  *@brief   Retorna o Id de um dado User.
  *@param   User.
  *@return  long Id do User.
*/
long getUserId(User u){
  if(u) return u->id;
  return -2;
}

/**
  *@brief   Retorna a reputação de um dado User.
  *@param   User.
  *@return  int Reputação do User.
*/
int getUserRep(User u){
  if(u) return u->reputacao;
  return -1;
}

/**
  *@brief   Retorna o nome de um dado User.
  *@param   User.
  *@return  char* Nome do User.
*/
char* getUserName(User u){
  if(u) return mystrdup(u->nome);
  return NULL;
}

/**
  *@brief   Retorna a biografia de um dado User.
  *@param   User.
  *@return  char* Biografia do User.
*/
char* mygetUserBio(User u){
  if(u) return mystrdup(u->bio);
  return NULL;
}

/**
  *@brief   Retorna o número de posts criados por um dado User.
  *@param   User.
  *@return  int número de posts do User.
*/
int getUserNPosts(User u){
  if(u) return u->nposts;
  return -1;
}

/**
  *@brief   Retorna o número de posts de um dado User.
  *@param   User.
*/
void incUserNPosts(User u){
  u->nposts++;
}

/**
  *@brief   Liberta a memória alocada por um User.
  *@param   void* Apontador para o User a limpar da memória.
*/
void myfreeUser(void *u){
  User aux = (User) u;
  if (aux){
    free(aux->nome);
    free(aux->bio);
    heap_free(aux->uposts);
    free(aux);
  }
}
