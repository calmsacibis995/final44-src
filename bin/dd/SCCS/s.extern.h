h46819
s 00001/00001/00038
d D 8.3 94/04/02 09:55:28 pendry 7 6
c add 1994 copyright
e
s 00002/00003/00037
d D 8.2 94/04/02 07:39:21 pendry 6 5
c prettyness police
e
s 00002/00002/00038
d D 8.1 93/05/31 14:22:27 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00002/00040
d D 5.4 91/11/13 09:17:35 bostic 4 3
c multiple defines for dd_close(), setup()
e
s 00004/00001/00038
d D 5.3 91/07/29 13:30:47 bostic 3 2
c fix block/unblock, ascii/ebcdic, cbs relationships (extensive)
c check for read/write/seek overflow; move stats into separate structure
c treat odd-length swab errors like truncate errors
e
s 00002/00001/00037
d D 5.2 91/07/27 10:55:19 bostic 2 1
c add Lance Visser to contrib list
e
s 00038/00000/00000
d D 5.1 91/07/26 15:42:41 bostic 1 0
c date and time created 91/07/26 15:42:41 by bostic
e
u
U
t
T
I 1
/*-
D 5
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
D 7
 * Copyright (c) 1991, 1993
E 7
I 7
 * Copyright (c) 1991, 1993, 1994
E 7
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
D 2
 * Keith Muller of the University of California, San Diego.
E 2
I 2
 * Keith Muller of the University of California, San Diego and Lance
 * Visser of Convex Computer Corporation.
E 2
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#include <sys/cdefs.h>

void block __P((void));
void block_close __P((void));
D 4
void dd_close __P((void));
E 4
void dd_out __P((int));
void def __P((void));
void def_close __P((void));
D 6
void err __P((const char *, ...));
E 6
void jcl __P((char **));
void pos_in __P((void));
void pos_out __P((void));
D 4
void setup __P((void));
E 4
D 6
void summary __P((int));
E 6
I 6
void summary __P((void));
void summaryx __P((int));
E 6
void terminate __P((int));
void unblock __P((void));
void unblock_close __P((void));
D 6
void warn __P((const char *, ...));
E 6

D 3
extern struct io_desc in, out;
E 3
I 3
extern IO in, out;
extern STAT st;
E 3
extern void (*cfunc)();
extern u_long cpy_cnt;
extern u_int cbsz;
extern u_int ddflags;
extern u_int files_cnt;
extern u_char *ctab;
I 3
extern u_char a2e_32V[], a2e_POSIX[], a2ibm_32V[], a2ibm_POSIX[], e2a_32V[];
extern u_char e2a_POSIX[], l2u[], u2l[];
E 3
E 1
