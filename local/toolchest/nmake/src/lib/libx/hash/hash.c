/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
/*
 * hash routines
 *
 * G. S. Fowler
 * AT&T Bell Laboratories
 *
 * HASH_INFO enables hash monitoring
 */

#include <stdio.h>
#include <hash.h>

static char	stamp[] = "@(#)hash (AT&T Bell Laboratories) 08/30/85a";

#define HASH(t,n,a,v)	if((t)->hash)v=(*t->hash)(n,a);\
			else{register char *s=n;register int i=0;\
			while(*s)i=(i<<1)+*s++;if((i%=(t)->size)<0)i+=(t)->size;v=(unsigned int)i;}

extern char	*malloc();
extern char	*strcpy();

extern int	strlen();

#if HASH_INFO

static void	hashinfo();
static void	hashrm();

static TABLE	tables;

#else

#define hashrm(t)	free(t)

#endif

/*
 * create a new hash table
 */

TABLE
mkhash(size, flags, hash, compare, error, name)
register unsigned int	size;
unsigned int		flags;
unsigned int		(*hash)();
int			(*compare)();
GENERIC			error;
char			*name;
{
	register TABLE	tab;
	register BUCKET	*b;
	unsigned int	i;

	if (!(tab = (TABLE)malloc(sizeof(struct hashtable)))) return((TABLE)0);
	if (!(b = (BUCKET*)malloc(sizeof(BUCKET) * size)))
	{
		free(tab);
		return((TABLE)0);
	}
	tab->table = b;
	tab->size = size;
	if (flags & HASH_POWER2) for (i = size, tab->arg = 1; i >>= 1; tab->arg++);
	else tab->arg = size;
	tab->flags = flags;
	tab->hash = hash;
	tab->compare = compare;
	tab->error = error;
	while (size--) *b++ = (BUCKET)0;
	tab->chains = 0;
#if HASH_INFO
	tab->name = name;
	tab->accesses = 0;
	tab->buckets = 0;
	tab->collisions = 0;
	tab->next = tables;
	tables = tab;
#endif
	return(tab);
}

/*
 * remove a hash table
 */

void
rmhash(tab)
register TABLE	tab;
{
	register unsigned int	i;
	register BUCKET		*b, k;

	b = tab->table;
	i = tab->size;
	while (i--)
		for (k = *b++; k; k = k->next)
		{
			if (tab->flags & HASH_ALLOCATE) free(k->name);
			free(k);
		}
	free(tab->table);
	hashrm(tab);
}

/*
 * rehash an old table
 */

TABLE
rehash(tab, size)
TABLE		tab;
unsigned int	size;
{
	unsigned int	i, index;
	TABLE		new;
	register BUCKET	*tab_b, tab_k, *new_b, new_k;

	if (size > 0 && tab->size != size)
	{
#if HASH_INFO
		if (!(new = mkhash(size, tab->flags, tab->hash, tab->compare, tab->error, tab->name))) return((TABLE)0);
		new->buckets = tab->buckets;
#else
		if (!(new = mkhash(size, tab->flags, tab->hash, tab->compare, tab->error, (char*)0))) return((TABLE)0);
#endif
		tab_b = tab->table;
		new_b = new->table;
		i = tab->size;
		while (i--)
		{
			tab_k = *tab_b++;
			while (tab_k)
			{
				new_k = tab_k;
				tab_k = tab_k->next;
				HASH(tab, new_k->name, new->arg, index);
				if (!(new_k->next = new_b[index])) new->chains++;
				new_b[index] = new_k;
			}
		}
		hashrm(tab);
		return(new);
	}
	return(tab);
}

/*
 * examine (walk through) a hash table
 */

void
exhash(tab, examiner)
TABLE	tab;
int	(*examiner)();
{
	register unsigned int	i;
	register BUCKET		*b, k;

	b = tab->table;
	i = tab->size;
	tab->flags |= HASH_EXAMINE;
	while (i--)
		for (k = *b++; k; k = k->next)
			if (k->value != tab->error && (*examiner)(k->name, k->value) < 0)
			{
				tab->flags &= ~HASH_EXAMINE;
				return;
			}
	tab->flags &= ~HASH_EXAMINE;
}

/*
 * get value for name
 */

GENERIC
gethash(tab, name)
register TABLE	tab;
char		*name;
{
	register BUCKET	b, p;

#if HASH_INFO
	tab->accesses++;
#endif
	tab->lastname = name;
	tab->lastbucket = (BUCKET)0;
	HASH(tab, name, tab->arg, tab->lastindex);
	for (p = (BUCKET)0, b = tab->table[tab->lastindex]; b; p = b, b = b->next)
	{
		if (tab->compare)
		{
			if (!(*tab->compare)(b->name, name)) goto found;
#if HASH_INFO
			tab->collisions++;
#endif
			continue;
		}
		else
		{
			register char	*s1 = b->name, *s2 = name;

			/*
			 * default string comparison
			 */

			while (*s1 == *s2++)
				if (!*s1++) goto found;
#if HASH_INFO
			tab->collisions++;
#endif
			continue;
		}

		/*
		 * found a match
		 */

	found:
		tab->lastbucket = b;
		if (p && !(tab->flags & HASH_EXAMINE))
		{
			/*
			 * move this bucket to the front of the list
			 * this places the popular names near the front
			 */

			p->next = b->next;
			b->next = tab->table[tab->lastindex];
			tab->table[tab->lastindex] = b;
		}
		return(b->value);
	}
	return(tab->error);
}

/*
 * put name=value
 *
 * the code is optimized for the sequence
 *
 * 	if (gethash(tab, name) == tab->error) puthash(tab, (char*)0, value);
 *
 * which is equivalent to but more efficient than
 *
 * 	if (gethash(tab, name) == tab->error) puthash(tab, name, value);
 */

char*
puthash(tab, name, value)
register TABLE	tab;
char		*name;
GENERIC		value;
{
	unsigned int	index;
	register BUCKET	b;

	if (name || (tab->flags & HASH_DATA)) (void)gethash(tab, name);
	else
	{
#if HASH_INFO
		tab->accesses++;
#endif
		name = tab->lastname;
	}
	if (b = tab->lastbucket)
	{
#if HASH_INFO
		if (value == tab->error) tab->buckets--;
		else if (b->value == tab->error) tab->buckets++;
#endif
		if ((b->value = value) == tab->error &&
		    (tab->flags & (HASH_EXAMINE | HASH_REMOVE)) == HASH_REMOVE)
		{
			if (tab->flags & HASH_ALLOCATE) free(b->name);
			tab->table[tab->lastindex] = b->next;
			free(b);
			return((char*)0);
		}
		return(b->name);
	}
	else if (value == tab->error) return((char*)0);
	else index = tab->lastindex;
	if (!(b = (BUCKET)malloc(sizeof(struct hashbucket)))) return((char*)0);
	if (!(b->next = tab->table[index])) tab->chains++;
	tab->table[index] = tab->lastbucket = b;
	if (tab->flags & HASH_ALLOCATE)
	{
		if (!(b->name = malloc(strlen(name)+1)))
		{
			tab->table[index] = b->next;
			free(b);
			return((char*)0);
		}
		(void)strcpy(b->name, name);
	}
	else b->name = name;
#if HASH_INFO
	tab->buckets++;
#endif
	b->value = value;
	return(b->name);
}

/*
 * dump hash table accounting info
 * if p is 0 then dump all tables
 */

void
dumphash(tab)
register TABLE	tab;
{
#if HASH_INFO
	fprintf(stderr, "\nhash table information:\n\n");
	if (tab) hashinfo(tab);
	else for (tab = tables; tab; tab = tab->next) hashinfo(tab);
	fflush(stderr);
#else
	static int	first = 1;

	if (first)
	{
		first = 0;
		fprintf(stderr, "hash: compile hash routines with -DHASH_INFO to get detailed hash table accounting\n");
		fflush(stderr);
	}
#endif
}

#if HASH_INFO

/*
 * dump info on a single table
 */

static void
hashinfo(tab)
register TABLE	tab;
{
	fprintf(stderr, "\tname:        %s\n", tab->name);
	fprintf(stderr, "\taddress:     0x%06lx\n", (unsigned long)tab);
	fprintf(stderr, "\tsize:        %d\n", tab->size);
	fprintf(stderr, "\tflags:       ");
	if (tab->flags & HASH_ALLOCATE) fprintf(stderr, "[allocate] ");
	if (tab->flags & HASH_DATA) fprintf(stderr, "[data] ");
	if (tab->flags & HASH_POWER2) fprintf(stderr, "[power/2] ");
	if (tab->flags & HASH_REMOVE) fprintf(stderr, "[remove] ");
	fprintf(stderr, "\n");
	fprintf(stderr, "\taccesses:    %d\n", tab->accesses);
	fprintf(stderr, "\tbuckets:     %d\n", tab->buckets);
	fprintf(stderr, "\tchains:      %d\n", tab->chains);
	fprintf(stderr, "\tcollisions:  %d\n", tab->collisions);
	fprintf(stderr, "\n");
	fflush(stderr);
}

/*
 * remove a table from the accounting list
 */

static void
hashrm(tab)
register TABLE	tab;
{
	register TABLE	q;

	if (tab == tables) tables = tab->next;
	else for (q = tables; q; q = q->next)
		if (tab == q->next)
		{
			q->next = tab->next;
			break;
		}
	free(tab);
}

#endif
