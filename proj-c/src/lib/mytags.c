/**
 * @file mytags.c
 * @brief Ficheiro que contém a implementação das Tags.
 */

#include "mytags.h"

struct tag{
  long id;
  char* name;
};

/**
*@return  Tag inicializada.
  *@brief   Inicializa uma Tag.
*/
Tag initTag(){
  Tag t = malloc(sizeof(struct tag));
  return t;
}

/**
  *@brief   Cria uma Tag.
  *@param   long id da Tag.
  *@param   char* string com o nome da Tag.
  *@return  Tag criada.
*/
Tag createTag(long id, char* name){
  Tag t = initTag();
  t->id = id;
  t->name= mystrdup(name);
  return t;
}

/**
  *@brief   Retorna o id de uma Tag.
  *@param   Tag tag.
  *@return  long id da Tag.
*/
long getTagId(Tag t){
    if (t) return t->id;
    return -1;
}

/**
  *@brief   Retorna a string com o nome da Tag.
  *@param   Tag tag.
  *@return  char* string com o nome da Tag.
  */
char* getTagName(Tag t){
  if(t) return mystrdup(t->name);
  return NULL;
}

/**
  *@brief   Liberta a memória alocada por uma Tag.
  *@param   void* apontador para a Tag a limpar da memória.
*/
void freeTag(void * t){
  Tag aux = (Tag) t;
  if(aux){
    free(aux->name);
    free(aux);
  }
}
