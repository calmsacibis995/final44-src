h46881
s 00001/00001/00027
d D 8.2 94/02/21 15:12:45 bostic 7 6
c first pass at making DB use basic integral types (the Alpha port)
e
s 00002/00002/00026
d D 8.1 93/06/04 15:25:06 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00027
d D 5.5 93/05/24 09:48:41 bostic 5 4
c add __rec_fd, to return a file descriptor
e
s 00001/00001/00026
d D 5.4 93/05/16 15:44:46 bostic 4 3
c sync now takes a flags argument
e
s 00002/00002/00025
d D 5.3 92/11/13 17:16:01 bostic 3 2
c __rec_put can fill in the key, so it's no longer a const *
c __rec_ret now fills in the key
e
s 00005/00004/00022
d D 5.2 91/09/11 16:21:02 bostic 2 1
c add __rec_dleaf; __rec_get takes const key; __rec_search takes argument
c for modifying parent pages during search
e
s 00026/00000/00000
d D 5.1 91/09/04 12:54:00 bostic 1 0
c Rev #2.  Redo the btree code add recno's and checkpoint
e
u
U
t
T
I 1
/*-
D 6
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

I 2
#include "../btree/extern.h"

E 2
int	 __rec_close __P((DB *));
int	 __rec_delete __P((const DB *, const DBT *, u_int));
I 2
D 7
int	 __rec_dleaf __P((BTREE *, PAGE *, int));
E 7
I 7
int	 __rec_dleaf __P((BTREE *, PAGE *, indx_t));
E 7
I 5
int	 __rec_fd __P((const DB *));
E 5
E 2
int	 __rec_fmap __P((BTREE *, recno_t));
int	 __rec_fout __P((BTREE *));
int	 __rec_fpipe __P((BTREE *, recno_t));
D 2
int	 __rec_get __P((const DB *, DBT *, DBT *, u_int));
E 2
I 2
int	 __rec_get __P((const DB *, const DBT *, DBT *, u_int));
E 2
int	 __rec_iput __P((BTREE *, recno_t, const DBT *, u_int));
D 3
int	 __rec_put __P((const DB *dbp, const DBT *, const DBT *, u_int));
int	 __rec_ret __P((BTREE *, EPG *, DBT *));
E 3
I 3
int	 __rec_put __P((const DB *dbp, DBT *, const DBT *, u_int));
int	 __rec_ret __P((BTREE *, EPG *, recno_t, DBT *, DBT *));
E 3
D 2
EPG	*__rec_search __P((BTREE *, recno_t, int *));
E 2
I 2
EPG	*__rec_search __P((BTREE *, recno_t, enum SRCHOP));
E 2
int	 __rec_seq __P((const DB *, DBT *, DBT *, u_int));
D 4
int	 __rec_sync __P((const DB *));
E 4
I 4
int	 __rec_sync __P((const DB *, u_int));
E 4
int	 __rec_vmap __P((BTREE *, recno_t));
int	 __rec_vout __P((BTREE *));
int	 __rec_vpipe __P((BTREE *, recno_t));
D 2

#include "../btree/extern.h"
E 2
E 1
