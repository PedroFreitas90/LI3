#ifndef __KEY_H__
#define __KEY_H__

typedef struct key* Key;

Key createKey(long key);
long getKey(Key k);
void freekey (Key k);

#endif
