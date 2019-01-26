/**
 * @file key.c
 * @brief Ficheiro que contem a implementação de Keys. Uma Key é um apontador para um long.
 */

#include "key.h"
#include <stdlib.h>

struct key{
  long key;
};

/**
  *@brief   Converte um long numa Key.
  *@param   long a ser convertido.
  *@return  Key criada.
*/
Key createKey(long key){
  Key k = malloc(sizeof(struct key));
  k->key = key;
  return k;
}

/**
  *@brief   Converte uma Key num long.
  *@param   Key a ser convertida.
  *@return  long.
*/
long getKey(Key k){
  return k->key;
}

/**
  *@brief   Liberta a memória alocada por uma Key.
  *@param   Key a ser libertada.
*/
void freekey (Key k){
   free(k);
}

