#ifndef __MYUSER_H__
#define __MYUSER_H__

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <gmodule.h>
#include "user.h"
#include "parser.h"
#include "heap.h"

typedef struct userint* User;

User mycreateUser(long, int, char*, char*, int, Heap);
Heap getUserHeap(User);
long getUserId(User);
int getUserRep(User);
char* getUserName(User);
char* mygetUserBio(User);
int getUserNPosts(User);
void incUserNPosts(User);
void myfreeUser(void*);

#endif
