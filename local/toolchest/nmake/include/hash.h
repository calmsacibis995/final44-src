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
 * hash routine definitions
 *
 * G. S. Fowler
 * AT&T Bell Laboratories
 */

#define HASH_ALLOCATE	(1<<0)		/* allocate new key names	*/
#define HASH_DATA	(1<<1)		/* key names are not strings	*/
#define HASH_EXAMINE	(1<<2)		/* currently in exhash()	*/
#define HASH_POWER2	(1<<3)		/* pass log2(size) to (*hash)()	*/
#define HASH_REMOVE	(1<<4)		/* remove error value entries	*/

#ifndef DEF_GENERIC
#define DEF_GENERIC
#if lint
typedef struct hashtable *GENERIC;	/* generic pointer		*/
#else
typedef char *GENERIC;			/* generic pointer		*/
#endif
#endif

typedef struct hashtable *TABLE;	/* hash table pointer		*/
typedef struct hashbucket *BUCKET;	/* hash table bucket pointer	*/

struct hashbucket			/* hash bucket			*/
{
	BUCKET 		next;		/* next bucket in list		*/
	char		*name;		/* name				*/
	GENERIC		value;		/* value			*/
};

struct hashtable			/* hash table information	*/
{
	BUCKET		*table;		/* actual hash table		*/
	unsigned int	size;		/* size of table		*/
	unsigned int	(*hash)();	/* string hash routine		*/
	int		(*compare)();	/* string comparision routine	*/
	GENERIC		error;		/* lookup error return value	*/
	unsigned int	arg;		/* second argument to (*hash)()	*/
	unsigned int	flags;		/* flags: see HASH_*		*/
	char		*lastname;	/* most recent hash name	*/
	unsigned int	lastindex;	/* most recent hash index	*/
	BUCKET		lastbucket;	/* most recent hash bucket	*/
	int		chains;		/* number of bucket chains	*/
#if HASH_INFO
	char		*name;		/* hash table name		*/
	TABLE		next;		/* next in list	of all tables	*/
	int		accesses;	/* number of accesses		*/
	int		buckets;	/* number of buckets		*/
	int		collisions;	/* number of collisions		*/
#endif
};

extern TABLE	mkhash(/*unsigned int size, unsigned int flags, unsigned int (*hash)(), int (*compare)(), GENERIC error, char* name*/);
extern void	rmhash(/*TABLE tab*/);
extern TABLE	rehash(/*TABLE tab, unsigned int size*/);
extern void	exhash(/*TABLE tab, int (*examiner)()*/);
extern void	dumphash(/*TABLE tab, int flag*/);
extern GENERIC	gethash(/*TABLE tab, char* name*/);
extern char	*puthash(/*TABLE tab, char* name, GENERIC value*/);

extern unsigned int chash(/*char* name, unsigned int size*/);
extern unsigned int chash2(/*char* name, unsigned int bits*/);
