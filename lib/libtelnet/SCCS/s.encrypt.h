h13758
s 00002/00002/00080
d D 8.1 93/06/04 17:35:35 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00012/00010/00070
d D 5.4 93/05/20 10:51:34 dab 4 3
c Fix all the "#if defined(ENCRYPTION)" lines to just
c be "#ifdef ENCRYPTION", so that unifdef can be used to strip
c out all the encryption code.
e
s 00002/00002/00078
d D 5.3 92/12/18 14:11:02 dab 3 2
c Change ENCRYPT to ENCRYPTION
c Change AUTHENTICATE to AUTHENTICATION
c Latest version of Kerberos V stuff
c Bug fixes
e
s 00001/00000/00079
d D 5.2 91/03/22 13:17:50 dab 2 1
c Upgrade to the latest & greatest authentication/encryption
e
s 00079/00000/00000
d D 5.1 91/02/28 22:01:29 dab 1 0
c date and time created 91/02/28 22:01:29 by dab
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
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Copyright (C) 1990 by the Massachusetts Institute of Technology
 *
 * Export of this software from the United States of America is assumed
 * to require a specific license from the United States Government.
 * It is the responsibility of any person or organization contemplating
 * export to obtain such a license before exporting.
 *
 * WITHIN THAT CONSTRAINT, permission to use, copy, modify, and
 * distribute this software and its documentation for any purpose and
 * without fee is hereby granted, provided that the above copyright
 * notice appear in all copies and that both that copyright notice and
 * this permission notice appear in supporting documentation, and that
 * the name of M.I.T. not be used in advertising or publicity pertaining
 * to distribution of the software without specific, written prior
 * permission.  M.I.T. makes no representations about the suitability of
 * this software for any purpose.  It is provided "as is" without express
 * or implied warranty.
 */

D 3
#ifndef	__ENCRYPT__
#define	__ENCRYPT__
E 3
I 3
D 4
#ifndef	__ENCRYPTION__
#define	__ENCRYPTION__
E 4
I 4
#ifdef	ENCRYPTION
# ifndef __ENCRYPTION__
# define __ENCRYPTION__
E 4
E 3

#define	DIR_DECRYPT		1
#define	DIR_ENCRYPT		2

typedef	unsigned char Block[8];
typedef unsigned char *BlockT;
typedef struct { Block _; } Schedule[16];

#define	VALIDKEY(key)	( key[0] | key[1] | key[2] | key[3] | \
			  key[4] | key[5] | key[6] | key[7])

#define	SAMEKEY(k1, k2)	(!bcmp((void *)k1, (void *)k2, sizeof(Block)))

typedef	struct {
	short		type;
	int		length;
	unsigned char	*data;
} Session_Key;

D 4
#if	!defined(P)
#ifdef	__STDC__
#define P(x)	x
#else
#define P(x)	()
#endif
#endif
E 4
I 4
# if !defined(P)
#  ifdef __STDC__
#   define P(x)	x
#  else
#   define P(x)	()
#  endif
# endif
E 4

typedef struct {
	char	*name;
	int	type;
	void	(*output) P((unsigned char *, int));
	int	(*input) P((int));
	void	(*init) P((int));
	int	(*start) P((int, int));
	int	(*is) P((unsigned char *, int));
	int	(*reply) P((unsigned char *, int));
	void	(*session) P((Session_Key *, int));
I 2
	int	(*keyid) P((int, unsigned char *, int *));
E 2
	void	(*printsub) P((unsigned char *, int, unsigned char *, int));
} Encryptions;

#define	SK_DES		1	/* Matched Kerberos v5 KEYTYPE_DES */

#include "enc-proto.h"

extern int encrypt_debug_mode;
extern int (*decrypt_input) P((int));
extern void (*encrypt_output) P((unsigned char *, int));
D 4
#endif
E 4
I 4
# endif /* __ENCRYPTION__ */
#endif /* ENCRYPTION */
E 4
E 1
