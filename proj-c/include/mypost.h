#ifndef __MYPOST_H__
#define __MYPOST_H__

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <gmodule.h>
#include "common.h"
#include "date.h"


typedef struct post* Post;
typedef struct arrayd *ArrayD;

void destroyDate (void*);

ArrayD createArray(long);
long getPer(ArrayD);
long getRes(ArrayD);
long getSize(ArrayD);
long getUsed(ArrayD);
Post getInd (ArrayD, int);
void insereArray(ArrayD, Post);
void freeArray(void*);

Post initPost();
Post createPost(long, int, long, int, int, Date, long, int, int, int, char*, char**, int);
int getPostNTags(Post);
char** getPostTags(Post);
double calcMedia(Post);
long getPostId(Post);
int getPostType(Post);
long getPid(Post);
int getPostScore(Post);
int getPostVCount(Post);
Date getPostDate(Post);
long getPostOwner(Post);
int getPostOwnerRep(Post);
int getPostNumCom(Post);
int getPostNRes(Post);
void incPostNRes(Post);
char* getPostTitulo(Post);
char* getTagI(Post p,int index);
void freePost(void*);

#endif
