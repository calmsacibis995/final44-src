h35342
s 00002/00002/00042
d D 8.3 94/02/21 15:08:20 bostic 11 10
c first pass at making DB use basic integral types (the Alpha port)
e
s 00000/00001/00044
d D 8.2 93/09/07 11:50:36 bostic 10 9
c __bt_open declared in db.h, don't need it here
e
s 00002/00002/00043
d D 8.1 93/06/04 15:21:16 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00044
d D 5.8 93/05/24 08:56:33 bostic 8 7
c add in __bt_fd, to return a file descriptor
e
s 00001/00001/00043
d D 5.7 93/05/16 15:42:42 bostic 7 6
c sync now takes a flags argument
e
s 00001/00001/00043
d D 5.6 93/02/19 14:31:41 bostic 6 5
c fix some types for the Sun compiler
e
s 00001/00000/00043
d D 5.5 92/12/04 14:15:03 bostic 5 4
c add routine to dump a single page
e
s 00001/00001/00042
d D 5.4 92/11/13 16:04:59 bostic 4 3
c bt_put can set the key, now, no longer const arg
e
s 00002/00000/00041
d D 5.3 92/10/09 16:25:52 bostic 3 2
c implement free page reuse
e
s 00002/00018/00039
d D 5.2 91/09/12 11:43:05 bostic 2 1
c get routines take const *key; move recno externs into recno.h
e
s 00057/00000/00000
d D 5.1 91/09/04 12:50:48 bostic 1 0
c Rev #2.  Redo the btree code add recno's and checkpoint
e
u
U
t
T
I 1
/*-
D 9
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

int	 __bt_close __P((DB *));
int	 __bt_cmp __P((BTREE *, const DBT *, EPG *));
int	 __bt_crsrdel __P((BTREE *, EPGNO *));
int	 __bt_defcmp __P((const DBT *, const DBT *));
D 11
int	 __bt_defpfx __P((const DBT *, const DBT *));
E 11
I 11
size_t	 __bt_defpfx __P((const DBT *, const DBT *));
E 11
int	 __bt_delete __P((const DB *, const DBT *, u_int));
int	 __bt_dleaf __P((BTREE *, PAGE *, int));
I 8
int	 __bt_fd __P((const DB *));
E 8
D 2
EPG	*__bt_first __P((BTREE *, DBT *, int *));
int	 __bt_get __P((const DB *, DBT *, DBT *, u_int));
E 2
I 2
EPG	*__bt_first __P((BTREE *, const DBT *, int *));
I 3
int	 __bt_free __P((BTREE *, PAGE *));
E 3
int	 __bt_get __P((const DB *, const DBT *, DBT *, u_int));
I 3
PAGE	*__bt_new __P((BTREE *, pgno_t *));
E 3
E 2
D 10
DB	*__bt_open __P((const char *, int, int, const BTREEINFO *));
E 10
void	 __bt_pgin __P((void *, pgno_t, void *));
void	 __bt_pgout __P((void *, pgno_t, void *));
int	 __bt_push __P((BTREE *, pgno_t, int));
D 4
int	 __bt_put __P((const DB *dbp, const DBT *, const DBT *, u_int));
E 4
I 4
int	 __bt_put __P((const DB *dbp, DBT *, const DBT *, u_int));
E 4
int	 __bt_ret __P((BTREE *, EPG *, DBT *, DBT *));
EPG	*__bt_search __P((BTREE *, const DBT *, int *));
int	 __bt_seq __P((const DB *, DBT *, DBT *, u_int));
int	 __bt_split __P((BTREE *, PAGE *,
D 6
	    const DBT *, const DBT *, u_long, size_t, int));
E 6
I 6
D 11
	    const DBT *, const DBT *, u_long, size_t, u_int));
E 11
I 11
	    const DBT *, const DBT *, int, size_t, indx_t));
E 11
E 6
D 7
int	 __bt_sync __P((const DB *));
E 7
I 7
int	 __bt_sync __P((const DB *, u_int));
E 7

int	 __ovfl_delete __P((BTREE *, void *));
int	 __ovfl_get __P((BTREE *, void *, size_t *, char **, size_t *));
int	 __ovfl_put __P((BTREE *, const DBT *, pgno_t *));
D 2

int	 __rec_close __P((DB *));
int	 __rec_delete __P((const DB *, const DBT *, u_int));
int	 __rec_fmap __P((BTREE *, recno_t));
int	 __rec_fout __P((BTREE *));
int	 __rec_fpipe __P((BTREE *, recno_t));
int	 __rec_get __P((const DB *, DBT *, DBT *, u_int));
int	 __rec_iput __P((BTREE *, recno_t, const DBT *, u_int));
int	 __rec_put __P((const DB *dbp, const DBT *, const DBT *, u_int));
int	 __rec_ret __P((BTREE *, EPG *, DBT *));
EPG	*__rec_search __P((BTREE *, recno_t, int *));
int	 __rec_seq __P((const DB *, DBT *, DBT *, u_int));
int	 __rec_sync __P((const DB *));
int	 __rec_vmap __P((BTREE *, recno_t));
int	 __rec_vout __P((BTREE *));
int	 __rec_vpipe __P((BTREE *, recno_t));
E 2

#ifdef DEBUG
I 5
void	 __bt_dnpage __P((DB *, pgno_t));
E 5
void	 __bt_dpage __P((PAGE *));
void	 __bt_dump __P((DB *));
#endif
#ifdef STATISTICS
void	 __bt_stat __P((DB *));
#endif
E 1
