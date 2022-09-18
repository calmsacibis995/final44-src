h08612
s 00007/00007/00083
d D 8.2 95/04/28 17:08:06 christos 7 6
c Updated to the latest version from the NetBSD source
e
s 00002/00002/00088
d D 8.1 93/06/06 15:15:13 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00016/00082
d D 5.5 93/05/24 14:45:36 bostic 5 4
c update, bug fix, ANSI C, lint from Christos Zoulas
c see SCCS/README.christos for details
e
s 00005/00041/00093
d D 5.4 90/12/28 18:07:03 bostic 4 3
c replace hash.c; speedup/cleanup from Chris Torek
e
s 00001/00011/00133
d D 5.3 90/06/01 17:08:05 bostic 3 2
c new copyright notice
e
s 00028/00006/00120
d D 5.2 90/03/11 15:55:13 bostic 2 1
c add Berkeley specific copyright notice
e
s 00126/00000/00000
d D 5.1 90/03/11 15:48:57 bostic 1 0
c release 2.1 of pmake
e
u
U
t
T
I 1
D 2
/* hash.h --
E 2
I 2
/*
D 6
 * Copyright (c) 1988, 1989, 1990 The Regents of the University of California.
 * Copyright (c) 1988, 1989 by Adam de Boor
E 6
I 6
 * Copyright (c) 1988, 1989, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 * Copyright (c) 1989 by Berkeley Softworks
 * All rights reserved.
E 2
 *
D 2
 * 	This file contains definitions used by the hash module,
 * 	which maintains hash tables.
E 2
I 2
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
E 2
 *
D 2
 * Copyright 1986 Regents of the University of California
 * All rights reserved.
E 2
I 2
D 3
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
E 3
I 3
 * %sccs.include.redist.c%
E 3
E 2
 *
D 2
 * $Id: hash.h,v 2.1 89/07/03 15:56:19 adam Exp $ SPRITE (Berkeley)
E 2
I 2
 *	%W% (Berkeley) %G%
E 2
 */

I 2
/* hash.h --
 *
 * 	This file contains definitions used by the hash module,
 * 	which maintains hash tables.
 */
E 2

#ifndef	_HASH
#define	_HASH

D 4
#include "list.h"
E 4
/* 
 * The following defines one entry in the hash table.
 */

typedef struct Hash_Entry {
D 4
    List_Links	      links;		/* Used to link together all the
E 4
I 4
    struct Hash_Entry *next;		/* Used to link together all the
E 4
    					 * entries associated with the same
					 * bucket. */
    ClientData	      clientData;	/* Arbitrary piece of data associated
    					 * with key. */
D 4
    union {
	Address	 ptr;			/* One-word key value to identify
					 * entry. */
	int words[1];			/* N-word key value.  Note: the actual
					 * size may be longer if necessary to
					 * hold the entire key. */
	char 	 name[4];		/* Text name of this entry.  Note: the
					 * actual size may be longer if
					 * necessary to hold the whole string.
					 * This MUST be the last entry in the
					 * structure!!! */
    } key;
E 4
I 4
    unsigned	      namehash;		/* hash value of key */
    char	      name[1];		/* key string */
E 4
} Hash_Entry;

D 4
/* 
 * A hash table consists of an array of pointers to hash
 * lists.  Tables can be organized in either of three ways, depending
 * on the type of comparison keys:
 *
 *	Strings:	  these are NULL-terminated; their address
 *			  is passed to HashFind as a (char *).
 *	Single-word keys: these may be anything, but must be passed
 *			  to Hash_Find as an Address.
 *	Multi-word keys:  these may also be anything; their address
 *			  is passed to HashFind as an Address.
 *
 *	Single-word keys are fastest, but most restrictive.
 */
 
#define HASH_STRING_KEYS	0
#define HASH_ONE_WORD_KEYS	1

E 4
typedef struct Hash_Table {
D 4
    List_Links 	*bucketPtr;	/* Pointer to array of List_Links, one
E 4
I 4
    struct Hash_Entry **bucketPtr;/* Pointers to Hash_Entry, one
E 4
    				 * for each bucket in the table. */
    int 	size;		/* Actual size of array. */
    int 	numEntries;	/* Number of entries in the table. */
D 4
    int 	downShift;	/* Shift count, used in hashing function. */
E 4
    int 	mask;		/* Used to select bits for hashing. */
D 4
    int 	keyType;	/* Type of keys used in table:
    				 * HASH_STRING_KEYS, HASH_ONE-WORD_KEYS,
				 * or >1 menas keyType gives number of words
				 * in keys.
				 */
E 4
} Hash_Table;

/* 
 * The following structure is used by the searching routines
 * to record where we are in the search.
 */

typedef struct Hash_Search {
    Hash_Table  *tablePtr;	/* Table being searched. */
    int 	nextIndex;	/* Next bucket to check (after current). */
    Hash_Entry 	*hashEntryPtr;	/* Next entry to check in current bucket. */
D 4
    List_Links	*hashList;	/* Hash chain currently being checked. */
E 4
} Hash_Search;

/*
 * Macros.
 */

/*
 * ClientData Hash_GetValue(h) 
 *     Hash_Entry *h; 
 */

#define Hash_GetValue(h) ((h)->clientData)

/* 
 * Hash_SetValue(h, val); 
D 4
 *     HashEntry *h; 
E 4
I 4
 *     Hash_Entry *h; 
E 4
 *     char *val; 
 */

#define Hash_SetValue(h, val) ((h)->clientData = (ClientData) (val))

/* 
 * Hash_Size(n) returns the number of words in an object of n bytes 
 */

#define	Hash_Size(n)	(((n) + sizeof (int) - 1) / sizeof (int))

D 5
/*
 * The following procedure declarations and macros
 * are the only things that should be needed outside
 * the implementation code.
 */
E 5
I 5
D 7
Hash_Entry	*Hash_CreateEntry __P((Hash_Table *, char *, Boolean *));
void		 Hash_DeleteEntry __P((Hash_Table *, Hash_Entry *));
void		 Hash_DeleteTable __P((Hash_Table *));
Hash_Entry	*Hash_EnumFirst __P((Hash_Table *, Hash_Search *));
Hash_Entry	*Hash_EnumNext __P((Hash_Search *));
Hash_Entry	*Hash_FindEntry __P((Hash_Table *, char *));
void		 Hash_InitTable __P((Hash_Table *, int));
E 7
I 7
void Hash_InitTable __P((Hash_Table *, int));
void Hash_DeleteTable __P((Hash_Table *));
Hash_Entry *Hash_FindEntry __P((Hash_Table *, char *));
Hash_Entry *Hash_CreateEntry __P((Hash_Table *, char *, Boolean *));
void Hash_DeleteEntry __P((Hash_Table *, Hash_Entry *));
Hash_Entry *Hash_EnumFirst __P((Hash_Table *, Hash_Search *));
Hash_Entry *Hash_EnumNext __P((Hash_Search *));
E 7
E 5

D 5
extern Hash_Entry *	Hash_CreateEntry();
extern void		Hash_DeleteTable();
extern void		Hash_DeleteEntry();
extern void		Hash_DeleteTable();
extern Hash_Entry *	Hash_EnumFirst();
extern Hash_Entry *	Hash_EnumNext();
extern Hash_Entry *	Hash_FindEntry();
extern void		Hash_InitTable();
extern void		Hash_PrintStats();

#endif _HASH
E 5
I 5
#endif /* _HASH */
E 5
E 1
