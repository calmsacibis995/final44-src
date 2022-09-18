h11098
s 00001/00001/00038
d D 8.2 94/02/21 15:09:06 bostic 5 4
c first pass at making DB use basic integral types (the Alpha port)
e
s 00002/00002/00037
d D 8.1 93/06/04 15:21:38 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00024/00023/00015
d D 5.3 93/01/17 16:20:17 bostic 3 2
c can't have a global "hashp", pass it around as an argument
c change default_hash to __default_hash for the same reason
e
s 00004/00004/00034
d D 5.2 91/09/08 12:27:47 bostic 2 1
c delete unused arguments, modify some return values
e
s 00038/00000/00000
d D 5.1 91/09/06 16:25:33 bostic 1 0
c Rev #2.  ANSI/POSIX and reformatting, a few bug fixes thrown in
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

D 3
BUFHEAD	*__add_ovflpage __P((BUFHEAD *));
int	 __addel __P((BUFHEAD *, const DBT *, const DBT *));
D 2
int	 __big_delete __P((BUFHEAD *, int));
E 2
I 2
int	 __big_delete __P((BUFHEAD *));
E 2
int	 __big_insert __P((BUFHEAD *, const DBT *, const DBT *));
D 2
int	 __big_keydata __P((BUFHEAD *, int, DBT *, DBT *, int));
E 2
I 2
int	 __big_keydata __P((BUFHEAD *, DBT *, DBT *, int));
E 2
int	 __big_return __P((BUFHEAD *, int, DBT *, int));
int	 __big_split __P((BUFHEAD *, BUFHEAD *, BUFHEAD *,
E 3
I 3
BUFHEAD	*__add_ovflpage __P((HTAB *, BUFHEAD *));
int	 __addel __P((HTAB *, BUFHEAD *, const DBT *, const DBT *));
int	 __big_delete __P((HTAB *, BUFHEAD *));
int	 __big_insert __P((HTAB *, BUFHEAD *, const DBT *, const DBT *));
int	 __big_keydata __P((HTAB *, BUFHEAD *, DBT *, DBT *, int));
int	 __big_return __P((HTAB *, BUFHEAD *, int, DBT *, int));
int	 __big_split __P((HTAB *, BUFHEAD *, BUFHEAD *, BUFHEAD *,
E 3
		int, u_int, SPLIT_RETURN *));
D 3
int	 __buf_free __P((int, int));
void	 __buf_init __P((int));
u_int	 __call_hash __P((char *, int));
int	 __delpair __P((BUFHEAD *, int));
int	 __expand_table __P((void));
int	 __find_bigpair __P((BUFHEAD *, int, char *, int));
u_short	 __find_last_page __P((BUFHEAD **));
void	 __free_ovflpage __P((BUFHEAD *));
BUFHEAD	*__get_buf __P((u_int, BUFHEAD *, int));
int	 __get_page __P((char *, u_int, int, int, int));
D 2
u_long	*__init_bitmap __P((int, int, int));
int	 __log2 __P((int));
E 2
I 2
int	 __init_bitmap __P((int, int, int));
E 3
I 3
int	 __buf_free __P((HTAB *, int, int));
void	 __buf_init __P((HTAB *, int));
u_int	 __call_hash __P((HTAB *, char *, int));
int	 __delpair __P((HTAB *, BUFHEAD *, int));
int	 __expand_table __P((HTAB *));
int	 __find_bigpair __P((HTAB *, BUFHEAD *, int, char *, int));
u_short	 __find_last_page __P((HTAB *, BUFHEAD **));
void	 __free_ovflpage __P((HTAB *, BUFHEAD *));
BUFHEAD	*__get_buf __P((HTAB *, u_int, BUFHEAD *, int));
int	 __get_page __P((HTAB *, char *, u_int, int, int, int));
int	 __init_bitmap __P((HTAB *, int, int, int));
E 3
u_int	 __log2 __P((u_int));
E 2
D 3
int	 __put_page __P((char *, u_int, int, int));
void	 __reclaim_buf __P((BUFHEAD *));
int	 __split_page __P((u_int, u_int));
E 3
I 3
int	 __put_page __P((HTAB *, char *, u_int, int, int));
void	 __reclaim_buf __P((HTAB *, BUFHEAD *));
int	 __split_page __P((HTAB *, u_int, u_int));
E 3

D 3
extern HTAB *hashp;
E 3
I 3
/* Default hash routine. */
D 5
extern int	(*__default_hash) __P((u_char *, int));
E 5
I 5
extern u_int32_t (*__default_hash) __P((const void *, size_t));
E 5

E 3
#ifdef HASH_STATISTICS
extern long hash_accesses, hash_collisions, hash_expansions, hash_overflows;
#endif
D 3
extern int (*default_hash) __P((u_char *, int));
E 3
E 1
