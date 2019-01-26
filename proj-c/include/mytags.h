#ifndef __MYTAGS_H__
#define __MYTAGS_H__

#include <string.h>
#include <stdlib.h>
#include "common.h"

typedef struct tag* Tag;

Tag initTag();
Tag createTag(long id, char* name);
long getTagId(Tag t);
char* getTagName(Tag t);
void freeTag(void *t);

#endif
