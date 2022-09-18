h37914
s 00000/00000/00392
d D 8.2 95/04/28 17:08:05 christos 8 7
c Updated to the latest version from the NetBSD source
e
s 00002/00002/00390
d D 8.1 93/06/06 15:15:07 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00005/00387
d D 5.6 93/05/24 14:45:35 bostic 6 5
c update, bug fix, ANSI C, lint from Christos Zoulas
c see SCCS/README.christos for details
e
s 00174/00424/00218
d D 5.5 90/12/28 18:07:00 bostic 5 4
c replace hash.c; speedup/cleanup from Chris Torek
e
s 00001/00011/00641
d D 5.4 90/06/01 17:07:55 bostic 4 3
c new copyright notice
e
s 00005/00005/00647
d D 5.3 90/03/19 09:50:48 bostic 3 2
c replace malloc with emalloc
e
s 00026/00007/00626
d D 5.2 90/03/11 16:50:55 bostic 2 1
c add Berkeley specific copyright notices
e
s 00633/00000/00000
d D 5.1 90/03/11 16:48:03 bostic 1 0
c release 2.1 of pmake
e
u
U
t
T
I 2
/*
D 7
 * Copyright (c) 1988, 1989, 1990 The Regents of the University of California.
 * Copyright (c) 1988, 1989 by Adam de Boor
E 7
I 7
 * Copyright (c) 1988, 1989, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 * Copyright (c) 1989 by Berkeley Softworks
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
D 4
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 4
I 4
 * %sccs.include.redist.c%
E 4
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 2
I 1
/* hash.c --
 *
 * 	This module contains routines to manipulate a hash table.
 * 	See hash.h for a definition of the structure of the hash
 * 	table.  Hash tables grow automatically as the amount of
 * 	information increases.
D 2
 *
 * Copyright (C) 1983 Regents of the University of California
 * All rights reserved.
E 2
 */
D 2

#ifndef lint
static char rcsid[] = "$Id: hash.c,v 2.1 89/06/13 17:24:54 adam Exp $ SPRITE (Berkeley)";
#endif  not lint
E 2
D 6

E 6
#include "sprite.h"
I 6
#include "make.h"
E 6
#include "hash.h"
D 5
#include "list.h"
E 5

/*
 * Forward references to local procedures that are used before they're
 * defined:
 */

D 5
static Hash_Entry *	ChainSearch();
static int		Hash();
E 5
D 6
static void		RebuildTable();
E 6
I 6
static void RebuildTable __P((Hash_Table *));
E 6

/* 
 * The following defines the ratio of # entries to # buckets
 * at which we rebuild the table to make it larger.
 */

D 5
static rebuildLimit = 3;

E 5
I 5
#define rebuildLimit 8

E 5
/*
 *---------------------------------------------------------
 * 
 * Hash_InitTable --
 *
 *	This routine just sets up the hash table.
 *
 * Results:	
 *	None.
 *
 * Side Effects:
 *	Memory is allocated for the initial bucket area.
 *
 *---------------------------------------------------------
 */

void
D 5
Hash_InitTable(tablePtr, numBuckets, keyType)
    register Hash_Table *tablePtr;	/* Structure to use to hold table. */
    int 	        numBuckets;	/* How many buckets to create for
					 * starters. This number is rounded
					 * up to a power of two.   If <= 0,
					 * a reasonable default is chosen.
					 * The table will grow in size later
					 * as needed. */
    int 	        keyType;	/* HASH_STRING_KEYS means that key
    					 * values passed to HashFind will be
					 * strings, passed via a (char *)
					 * pointer.  HASH_ONE_WORD_KEYS means
					 * that key values will be any
					 * one-word value passed as Address.
			 		 * > 1 means that key values will be 
				 	 * multi-word values whose address is
					 * passed as Address.  In this last
					 * case, keyType is the number of
					 * words in the key, not the number
					 * of bytes. */
E 5
I 5
Hash_InitTable(t, numBuckets)
	register Hash_Table *t;	/* Structure to use to hold table. */
	int numBuckets;		/* How many buckets to create for starters.
				 * This number is rounded up to a power of
				 * two.   If <= 0, a reasonable default is
				 * chosen. The table will grow in size later
				 * as needed. */
E 5
{
D 5
    register	int 		i;
    register	List_Links 	*bucketPtr;
E 5
I 5
	register int i;
	register struct Hash_Entry **hp;
E 5

D 5
    /* 
     * Round up the size to a power of two. 
     */

    if (numBuckets <= 0) {
	numBuckets = 16;
    }
    tablePtr->numEntries = 0;
    tablePtr->keyType = keyType;
    tablePtr->size = 2;
    tablePtr->mask = 1;
    tablePtr->downShift = 29;
    while (tablePtr->size < numBuckets) {
	tablePtr->size <<= 1;
	tablePtr->mask = (tablePtr->mask << 1) + 1;
	tablePtr->downShift--;
    }

D 3
    tablePtr->bucketPtr = (List_Links *) malloc(sizeof(List_Links)
E 3
I 3
    tablePtr->bucketPtr = (List_Links *) emalloc(sizeof(List_Links)
E 3
	    * tablePtr->size);
    for (i=0, bucketPtr = tablePtr->bucketPtr; i < tablePtr->size;
	    i++, bucketPtr++) {
	List_Init(bucketPtr);
    }
E 5
I 5
	/*
	 * Round up the size to a power of two. 
	 */
	if (numBuckets <= 0)
		i = 16;
	else {
		for (i = 2; i < numBuckets; i <<= 1)
D 6
			 /* void */ ;
E 6
I 6
			 continue;
E 6
	}
	t->numEntries = 0;
	t->size = i;
	t->mask = i - 1;
	t->bucketPtr = hp = (struct Hash_Entry **)emalloc(sizeof(*hp) * i);
	while (--i >= 0)
		*hp++ = NULL;
E 5
}
D 5

E 5
I 5

E 5
/*
 *---------------------------------------------------------
 *
 * Hash_DeleteTable --
 *
 *	This routine removes everything from a hash table
 *	and frees up the memory space it occupied (except for
 *	the space in the Hash_Table structure).
 *
 * Results:	
 *	None.
 *
 * Side Effects:
 *	Lots of memory is freed up.
 *
 *---------------------------------------------------------
 */

void
D 5
Hash_DeleteTable(tablePtr)
    Hash_Table *tablePtr;		/* Hash table whose entries are all to
					 * be freed.  */
E 5
I 5
Hash_DeleteTable(t)
	Hash_Table *t;
E 5
{
D 5
    register List_Links *hashTableEnd;
    register Hash_Entry *hashEntryPtr;
    register List_Links *bucketPtr;
E 5
I 5
D 6
	register struct Hash_Entry **hp, *h, *nexth;
E 6
I 6
	register struct Hash_Entry **hp, *h, *nexth = NULL;
E 6
	register int i;
E 5

D 5
    bucketPtr = tablePtr->bucketPtr;
    hashTableEnd = &(bucketPtr[tablePtr->size]);
    for (; bucketPtr < hashTableEnd; bucketPtr++) {
	while (!List_IsEmpty(bucketPtr)) {
	    hashEntryPtr = (Hash_Entry *) List_First(bucketPtr);
	    List_Remove((List_Links *) hashEntryPtr);
	    free((Address) hashEntryPtr);
E 5
I 5
	for (hp = t->bucketPtr, i = t->size; --i >= 0;) {
		for (h = *hp++; h != NULL; h = nexth) {
			nexth = h->next;
			free((char *)h);
		}
E 5
	}
D 5
    }
    free((Address) tablePtr->bucketPtr);
E 5
I 5
	free((char *)t->bucketPtr);
E 5

D 5
    /*
     * Set up the hash table to cause memory faults on any future
     * access attempts until re-initialization.
     */

    tablePtr->bucketPtr = (List_Links *) NIL;
E 5
I 5
	/*
	 * Set up the hash table to cause memory faults on any future access
	 * attempts until re-initialization. 
	 */
	t->bucketPtr = NULL;
E 5
}
D 5

E 5
I 5

E 5
/*
 *---------------------------------------------------------
 *
 * Hash_FindEntry --
 *
 * 	Searches a hash table for an entry corresponding to key.
 *
 * Results:
 *	The return value is a pointer to the entry for key,
 *	if key was present in the table.  If key was not
 *	present, NULL is returned.
 *
 * Side Effects:
 *	None.
 *
 *---------------------------------------------------------
 */

Hash_Entry *
D 5
Hash_FindEntry(tablePtr, key)
    Hash_Table *tablePtr;	/* Hash table to search. */
    Address key;		/* A hash key. */
E 5
I 5
Hash_FindEntry(t, key)
	Hash_Table *t;		/* Hash table to search. */
	char *key;		/* A hash key. */
E 5
{
D 5
    return(ChainSearch(tablePtr, key,
	    &(tablePtr->bucketPtr[Hash(tablePtr, key)])));
E 5
I 5
	register Hash_Entry *e;
	register unsigned h;
	register char *p;

	for (h = 0, p = key; *p;)
		h = (h << 5) - h + *p++;
	p = key;
	for (e = t->bucketPtr[h & t->mask]; e != NULL; e = e->next)
		if (e->namehash == h && strcmp(e->name, p) == 0)
			return (e);
	return (NULL);
E 5
}
D 5

E 5
I 5

E 5
/*
 *---------------------------------------------------------
 *
 * Hash_CreateEntry --
 *
 *	Searches a hash table for an entry corresponding to
 *	key.  If no entry is found, then one is created.
 *
 * Results:
 *	The return value is a pointer to the entry.  If *newPtr
 *	isn't NULL, then *newPtr is filled in with TRUE if a
 *	new entry was created, and FALSE if an entry already existed
 *	with the given key.
 *
 * Side Effects:
 *	Memory may be allocated, and the hash buckets may be modified.
 *---------------------------------------------------------
 */

Hash_Entry *
D 5
Hash_CreateEntry(tablePtr, key, newPtr)
    register Hash_Table *tablePtr;	/* Hash table to search. */
    Address key;			/* A hash key. */
    Boolean *newPtr;			/* Filled in with TRUE if new entry
    					 * created, FALSE otherwise. */
E 5
I 5
Hash_CreateEntry(t, key, newPtr)
	register Hash_Table *t;	/* Hash table to search. */
	char *key;		/* A hash key. */
	Boolean *newPtr;	/* Filled in with TRUE if new entry created,
				 * FALSE otherwise. */
E 5
{
D 5
    register Hash_Entry *hashEntryPtr;
    register int 	*hashKeyPtr;
    register int 	*keyPtr;
    List_Links 		*hashList;
E 5
I 5
	register Hash_Entry *e;
	register unsigned h;
	register char *p;
	int keylen;
	struct Hash_Entry **hp;
E 5

D 5
    keyPtr = (int *) key;

    hashList = &(tablePtr->bucketPtr[Hash(tablePtr, (Address) keyPtr)]);
    hashEntryPtr = ChainSearch(tablePtr, (Address) keyPtr, hashList);

    if (hashEntryPtr != (Hash_Entry *) NULL) {
	if (newPtr != NULL) {
	    *newPtr = FALSE;
E 5
I 5
	/*
	 * Hash the key.  As a side effect, save the length (strlen) of the
	 * key in case we need to create the entry.
	 */
	for (h = 0, p = key; *p;)
		h = (h << 5) - h + *p++;
	keylen = p - key;
	p = key;
	for (e = t->bucketPtr[h & t->mask]; e != NULL; e = e->next) {
		if (e->namehash == h && strcmp(e->name, p) == 0) {
			if (newPtr != NULL)
				*newPtr = FALSE;
			return (e);
		}
E 5
	}
D 5
    	return hashEntryPtr;
    }
E 5

D 5
    /* 
     * The desired entry isn't there.  Before allocating a new entry,
     * see if we're overloading the buckets.  If so, then make a
     * bigger table.
     */
E 5
I 5
	/*
	 * The desired entry isn't there.  Before allocating a new entry,
	 * expand the table if necessary (and this changes the resulting
	 * bucket chain). 
	 */
	if (t->numEntries >= rebuildLimit * t->size)
		RebuildTable(t);
	e = (Hash_Entry *) emalloc(sizeof(*e) + keylen);
	hp = &t->bucketPtr[h & t->mask];
	e->next = *hp;
	*hp = e;
	e->clientData = NULL;
	e->namehash = h;
	(void) strcpy(e->name, p);
	t->numEntries++;
E 5

D 5
    if (tablePtr->numEntries >= rebuildLimit * tablePtr->size) {
	RebuildTable(tablePtr);
	hashList = &(tablePtr->bucketPtr[Hash(tablePtr, (Address) keyPtr)]);
    }
    tablePtr->numEntries += 1;

    /*
     * Not there, we have to allocate.  If the string is longer
     * than 3 bytes, then we have to allocate extra space in the
     * entry.
     */

    switch (tablePtr->keyType) {
	case HASH_STRING_KEYS:
D 3
	    hashEntryPtr = (Hash_Entry *) malloc(sizeof(Hash_Entry) + 
E 3
I 3
	    hashEntryPtr = (Hash_Entry *) emalloc(sizeof(Hash_Entry) + 
E 3
		    strlen((char *) keyPtr) - 3);
	    strcpy(hashEntryPtr->key.name, (char *) keyPtr);
	    break;
	case HASH_ONE_WORD_KEYS:
D 3
	    hashEntryPtr = (Hash_Entry *) malloc(sizeof(Hash_Entry));
E 3
I 3
	    hashEntryPtr = (Hash_Entry *) emalloc(sizeof(Hash_Entry));
E 3
	    hashEntryPtr->key.ptr = (Address) keyPtr;
	    break;
	case 2:
	    hashEntryPtr = 
D 3
		(Hash_Entry *) malloc(sizeof(Hash_Entry) + sizeof(int));
E 3
I 3
		(Hash_Entry *) emalloc(sizeof(Hash_Entry) + sizeof(int));
E 3
	    hashKeyPtr = hashEntryPtr->key.words;
	    *hashKeyPtr++ = *keyPtr++;
	    *hashKeyPtr = *keyPtr;
	    break;
	default: {
	    register 	n;

	    n = tablePtr->keyType;
	    hashEntryPtr = (Hash_Entry *) 
D 3
		    malloc(sizeof(Hash_Entry) + (n - 1) * sizeof(int));
E 3
I 3
		    emalloc(sizeof(Hash_Entry) + (n - 1) * sizeof(int));
E 3
	    hashKeyPtr = hashEntryPtr->key.words;
	    do { 
		*hashKeyPtr++ = *keyPtr++; 
	    } while (--n);
	    break;
	}
    }

    hashEntryPtr->clientData = (ClientData) NULL;
    List_Insert((List_Links *) hashEntryPtr, LIST_ATFRONT(hashList));

    if (newPtr != NULL) {
	*newPtr = TRUE;
    }
    return hashEntryPtr;
E 5
I 5
	if (newPtr != NULL)
		*newPtr = TRUE;
	return (e);
E 5
}
D 5

E 5
I 5

E 5
/*
 *---------------------------------------------------------
 *
 * Hash_DeleteEntry --
 *
 * 	Delete the given hash table entry and free memory associated with
 *	it.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	Hash chain that entry lives in is modified and memory is freed.
 *
 *---------------------------------------------------------
 */

void
D 5
Hash_DeleteEntry(tablePtr, hashEntryPtr)
    Hash_Table			*tablePtr;
    register	Hash_Entry	*hashEntryPtr;
E 5
I 5
Hash_DeleteEntry(t, e)
	Hash_Table *t;
	Hash_Entry *e;
E 5
{
D 5
    if (hashEntryPtr != (Hash_Entry *) NULL) {
	List_Remove((List_Links *) hashEntryPtr);
	free((Address) hashEntryPtr);
	tablePtr->numEntries--;
    }
E 5
I 5
	register Hash_Entry **hp, *p;

	if (e == NULL)
		return;
	for (hp = &t->bucketPtr[e->namehash & t->mask];
	     (p = *hp) != NULL; hp = &p->next) {
		if (p == e) {
			*hp = p->next;
			free((char *)p);
			t->numEntries--;
			return;
		}
	}
	(void) write(2, "bad call to Hash_DeleteEntry\n", 29);
	abort();
E 5
}
D 5

E 5
I 5

E 5
/*
 *---------------------------------------------------------
 *
 * Hash_EnumFirst --
 *	This procedure sets things up for a complete search
 *	of all entries recorded in the hash table.
 *
 * Results:	
 *	The return value is the address of the first entry in
 *	the hash table, or NULL if the table is empty.
 *
 * Side Effects:
D 5
 *	The information in hashSearchPtr is initialized so that successive
E 5
I 5
 *	The information in searchPtr is initialized so that successive
E 5
 *	calls to Hash_Next will return successive HashEntry's
 *	from the table.
 *
 *---------------------------------------------------------
 */

Hash_Entry *
D 5
Hash_EnumFirst(tablePtr, hashSearchPtr)
    Hash_Table *tablePtr;			/* Table to be searched. */
    register Hash_Search *hashSearchPtr;	/* Area in which to keep state 
						 * about search.*/
E 5
I 5
Hash_EnumFirst(t, searchPtr)
	Hash_Table *t;			/* Table to be searched. */
	register Hash_Search *searchPtr;/* Area in which to keep state 
					 * about search.*/
E 5
{
D 5
    hashSearchPtr->tablePtr = tablePtr;
    hashSearchPtr->nextIndex = 0;
    hashSearchPtr->hashEntryPtr = (Hash_Entry *) NULL;
    return Hash_EnumNext(hashSearchPtr);
E 5
I 5
	searchPtr->tablePtr = t;
	searchPtr->nextIndex = 0;
	searchPtr->hashEntryPtr = NULL;
	return Hash_EnumNext(searchPtr);
E 5
}

/*
 *---------------------------------------------------------
 *
 * Hash_EnumNext --
 *    This procedure returns successive entries in the hash table.
 *
 * Results:
 *    The return value is a pointer to the next HashEntry
 *    in the table, or NULL when the end of the table is
 *    reached.
 *
 * Side Effects:
D 5
 *    The information in hashSearchPtr is modified to advance to the
E 5
I 5
 *    The information in searchPtr is modified to advance to the
E 5
 *    next entry.
 *
 *---------------------------------------------------------
 */

Hash_Entry *
D 5
Hash_EnumNext(hashSearchPtr)
    register Hash_Search *hashSearchPtr; /* Area used to keep state about 
E 5
I 5
Hash_EnumNext(searchPtr)
	register Hash_Search *searchPtr; /* Area used to keep state about 
E 5
					    search. */
{
D 5
    register List_Links *hashList;
    register Hash_Entry *hashEntryPtr;
E 5
I 5
	register Hash_Entry *e;
	Hash_Table *t = searchPtr->tablePtr;
E 5

D 5
    hashEntryPtr = hashSearchPtr->hashEntryPtr;
    while (hashEntryPtr == (Hash_Entry *) NULL ||
	   List_IsAtEnd(hashSearchPtr->hashList,
	   (List_Links *) hashEntryPtr)) {
	if (hashSearchPtr->nextIndex >= hashSearchPtr->tablePtr->size) {
	    return((Hash_Entry *) NULL);
E 5
I 5
	/*
	 * The hashEntryPtr field points to the most recently returned
	 * entry, or is nil if we are starting up.  If not nil, we have
	 * to start at the next one in the chain.
	 */
	e = searchPtr->hashEntryPtr;
	if (e != NULL)
		e = e->next;
	/*
	 * If the chain ran out, or if we are starting up, we need to
	 * find the next nonempty chain.
	 */
	while (e == NULL) {
		if (searchPtr->nextIndex >= t->size)
			return (NULL);
		e = t->bucketPtr[searchPtr->nextIndex++];
E 5
	}
D 5
	hashList = &(hashSearchPtr->tablePtr->bucketPtr[
		hashSearchPtr->nextIndex]);
	hashSearchPtr->nextIndex++;
	if (!List_IsEmpty(hashList)) {
	    hashEntryPtr = (Hash_Entry *) List_First(hashList);
	    hashSearchPtr->hashList = hashList;
	    break;
	}
    }

    hashSearchPtr->hashEntryPtr = 
		(Hash_Entry *) List_Next((List_Links *) hashEntryPtr);

    return(hashEntryPtr);
E 5
I 5
	searchPtr->hashEntryPtr = e;
	return (e);
E 5
}
D 5

/*
 *---------------------------------------------------------
 *
 * Hash_PrintStats --
 *
 *	This routine calls a caller-supplied procedure to print
 *	statistics about the current bucket situation.
 *
 * Results:	
 *	None.
 *
 * Side Effects:	
 *	Proc gets called (potentially many times) to output information
 *	about the hash table. It must have the following calling sequence:
 *
 *	void
 *	proc(clientData, string)
 *	    ClientData clientData;
 *	    char *string;
 *	{
 *	}
 *
 *	In each call, clientData is the same as the clientData argument
 *	to this procedure, and string is a null-terminated string of
 *	characters to output.
 *
 *---------------------------------------------------------
 */
E 5

D 5
void
Hash_PrintStats(tablePtr, proc, clientData)
    Hash_Table *tablePtr;		/* Table for which to print info. */
    void (*proc)();			/* Procedure to call to do actual
    					 * I/O. */
{
    int count[10], overflow, i, j;
    char msg[100];
    Hash_Entry 	*hashEntryPtr;
    List_Links	*hashList;

    for (i=0; i<10; i++) {
	count[i] = 0;
    }
    overflow = 0;
    for (i = 0; i < tablePtr->size; i++) {
	j = 0;
	hashList = &(tablePtr->bucketPtr[i]);
	LIST_FORALL(hashList, (List_Links *) hashEntryPtr) {
	    j++;
	}
	if (j < 10) {
	    count[j]++;
	} else {
	    overflow++;
	}
    }

    sprintf(msg, "Entries in table %d number of buckets %d\n", 
		tablePtr->numEntries, tablePtr->size);
    (*proc)(clientData, msg);
    for (i = 0;  i < 10; i++) {
	sprintf(msg, "Number of buckets with %d entries: %d.\n",
		i, count[i]);
	(*proc)(clientData, msg);
    }
    sprintf(msg, "Number of buckets with > 9 entries: %d.\n",
	    overflow);
    (*proc)(clientData, msg);
}

E 5
/*
 *---------------------------------------------------------
 *
D 5
 * Hash --
 *	This is a local procedure to compute a hash table
 *	bucket address based on a string value.
 *
 * Results:
 *	The return value is an integer between 0 and size - 1.
 *
 * Side Effects:	
 *	None.
 *
 * Design:
 *	It is expected that most keys are decimal numbers,
 *	so the algorithm behaves accordingly.  The randomizing
 *	code is stolen straight from the rand library routine.
 *
 *---------------------------------------------------------
 */

static int
Hash(tablePtr, key)
    register Hash_Table *tablePtr;
    register char 	*key;
{
    register int 	i = 0;
    register int 	j;
    register int 	*intPtr;

    switch (tablePtr->keyType) {
	case HASH_STRING_KEYS:
	    while (*key != 0) {
		i = (i * 10) + (*key++ - '0');
	    }
	    break;
	case HASH_ONE_WORD_KEYS:
	    i = (int) key;
	    break;
	case 2:
	    i = ((int *) key)[0] + ((int *) key)[1];
	    break;
	default:
	    j = tablePtr->keyType;
	    intPtr = (int *) key;
	    do { 
		i += *intPtr++; 
		j--;
	    } while (j > 0);
	    break;
    }


    return(((i*1103515245 + 12345) >> tablePtr->downShift) & tablePtr->mask);
}

/*
 *---------------------------------------------------------
 *
 * ChainSearch --
 *
 * 	Search the hash table for the entry in the hash chain.
 *
 * Results:
 *	Pointer to entry in hash chain, NULL if none found.
 *
 * Side Effects:
 *	None.
 *
 *---------------------------------------------------------
 */

static Hash_Entry *
ChainSearch(tablePtr, key, hashList)
    Hash_Table 		*tablePtr;	/* Hash table to search. */
    register Address	key;	/* A hash key. */
    register List_Links *hashList;
{
    register Hash_Entry *hashEntryPtr;
    register int 	*hashKeyPtr;
    int 		*keyPtr;
    register int	numKeys;

    numKeys = tablePtr->keyType;
    LIST_FORALL(hashList, (List_Links *) hashEntryPtr) {
	switch (numKeys) {
	    case 0:
		if (strcmp(hashEntryPtr->key.name, key) == 0) {
		    return(hashEntryPtr);
		}
		break;
	    case 1:
		if (hashEntryPtr->key.ptr == key) {
		    return(hashEntryPtr);
		}
		break;
	    case 2:
		hashKeyPtr = hashEntryPtr->key.words;
		keyPtr = (int *) key;
		if (*hashKeyPtr++ == *keyPtr++ && *hashKeyPtr == *keyPtr) {
		    return(hashEntryPtr);
		}
		break;
	    default:
		if (bcmp((Address) hashEntryPtr->key.words,
			    (Address) key, numKeys * sizeof(int))) {
		    return(hashEntryPtr);
		}
		break;
	}
    }

    /* 
     * The desired entry isn't there 
     */

    return ((Hash_Entry *) NULL);
}

/*
 *---------------------------------------------------------
 *
E 5
 * RebuildTable --
 *	This local routine makes a new hash table that
 *	is larger than the old one.
 *
 * Results:	
 * 	None.
 *
 * Side Effects:
 *	The entire hash table is moved, so any bucket numbers
 *	from the old table are invalid.
 *
 *---------------------------------------------------------
 */

static void
D 5
RebuildTable(tablePtr)
    Hash_Table 	*tablePtr;		/* Table to be enlarged. */
E 5
I 5
RebuildTable(t)
	register Hash_Table *t;
E 5
{
D 5
    int 		 oldSize;
    int 		 bucket;
    List_Links		 *oldBucketPtr;
    register Hash_Entry  *hashEntryPtr;
    register List_Links	 *oldHashList;
E 5
I 5
D 6
	register Hash_Entry *e, *next, **hp, **xp;
E 6
I 6
	register Hash_Entry *e, *next = NULL, **hp, **xp;
E 6
	register int i, mask;
        register Hash_Entry **oldhp;
	int oldsize;
E 5

D 5
    oldBucketPtr = tablePtr->bucketPtr;
    oldSize = tablePtr->size;

    /* 
     * Build a new table 4 times as large as the old one. 
     */

    Hash_InitTable(tablePtr, tablePtr->size * 4, tablePtr->keyType);

    for (oldHashList = oldBucketPtr; oldSize > 0; oldSize--, oldHashList++) {
	while (!List_IsEmpty(oldHashList)) {
	    hashEntryPtr = (Hash_Entry *) List_First(oldHashList);
	    List_Remove((List_Links *) hashEntryPtr);
	    switch (tablePtr->keyType) {
		case HASH_STRING_KEYS:
		    bucket = Hash(tablePtr, (Address) hashEntryPtr->key.name);
		    break;
		case HASH_ONE_WORD_KEYS:
		    bucket = Hash(tablePtr, (Address) hashEntryPtr->key.ptr);
		    break;
		default:
		    bucket = Hash(tablePtr, (Address) hashEntryPtr->key.words);
		    break;
	    }
	    List_Insert((List_Links *) hashEntryPtr, 
		LIST_ATFRONT(&(tablePtr->bucketPtr[bucket])));
	    tablePtr->numEntries++;
E 5
I 5
	oldhp = t->bucketPtr;
	oldsize = i = t->size;
	i <<= 1;
	t->size = i;
	t->mask = mask = i - 1;
	t->bucketPtr = hp = (struct Hash_Entry **) emalloc(sizeof(*hp) * i);
	while (--i >= 0)
		*hp++ = NULL;
	for (hp = oldhp, i = oldsize; --i >= 0;) {
		for (e = *hp++; e != NULL; e = next) {
			next = e->next;
			xp = &t->bucketPtr[e->namehash & mask];
			e->next = *xp;
			*xp = e;
		}
E 5
	}
D 5
    }

    free((Address) oldBucketPtr);
E 5
I 5
	free((char *)oldhp);
E 5
}
E 1
