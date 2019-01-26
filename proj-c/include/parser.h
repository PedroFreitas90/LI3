#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdlib.h>
#include <string.h>
#include <gmodule.h>
#include <stdio.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include "key.h"
#include "myuser.h"
#include "mypost.h"
#include "mytags.h"
#include "heap.h"


gint hash (gconstpointer);

Date incrementaData (Date);

int date_equal(Date begin, Date end);

gboolean iguais (gconstpointer, gconstpointer);

int idusercompare(gconstpointer, gconstpointer);

int idpostcompare(gconstpointer, gconstpointer);

int idtagcompare(gconstpointer id1, gconstpointer id2);

void userInfo (xmlDocPtr, GTree*);

void postsInfo(xmlDocPtr, GTree*, GHashTable*, GTree*);

void tagsInfo (xmlDocPtr doc, GTree * arv_tags);

int count_tags(char*);

int nTags(char** list);

char** takeTag(char*);

#endif
