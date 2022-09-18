h27157
s 00000/00001/00046
d D 5.5 91/02/06 12:01:29 bostic 8 7
c ANSI; don't redefine malloc
e
s 00001/00011/00046
d D 5.4 90/06/01 18:40:54 bostic 7 6
c new copyright notice
e
s 00010/00005/00047
d D 5.3 88/06/18 14:00:50 bostic 6 5
c install approved copyright notice
e
s 00011/00004/00041
d D 5.2 88/02/23 15:25:47 bostic 5 4
c portability fixes from Bill Nowicki (nowicki@sun.com); add Berkeley
c specific header
e
s 00007/00001/00038
d D 5.1 85/05/28 14:04:05 dist 4 3
c add copyright
e
s 00010/00000/00029
d D 4.3 83/11/03 12:21:49 karels 3 2
c calculate connectivity of gateways to find multi-hop gateways;
c read localgateways and use in eliminating dups and gateways remote from them;
c take local nets and connected nets in args, not compiled in.
e
s 00002/00012/00027
d D 4.2 82/10/21 22:24:36 sam 2 1
c cleanup
e
s 00039/00000/00000
d D 4.1 82/10/20 21:26:50 sam 1 0
c date and time created 82/10/20 21:26:50 by sam
e
u
U
t
T
I 1
D 4
/*	%W% (Berkeley) %G%	*/
E 4
I 4
/*
 * Copyright (c) 1983 Regents of the University of California.
D 5
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
 * All rights reserved.
E 5
 *
I 5
D 7
 * Redistribution and use in source and binary forms are permitted
D 6
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 6
I 6
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 7
I 7
 * %sccs.include.redist.c%
E 7
E 6
 *
E 5
 *	%W% (Berkeley) %G%
 */
E 4

#include <sys/types.h>
I 5
#include <netinet/in.h>
E 5

/*
 * common definitions for htable
 */

struct addr {
D 5
	u_long	addr_val;
E 5
I 5
	struct	in_addr addr_val;
E 5
	struct	addr *addr_link;
};

struct name {
	char	*name_val;
	struct	name *name_link;
};

I 3
struct gateway {
	struct	gateway *g_link;
	struct	gateway *g_dst;		/* connected gateway if metric > 0 */
	struct	gateway *g_firstent;	/* first entry for this gateway */
	struct	name	*g_name;
	int	g_net;
D 5
	u_long	g_addr;			/* address on g_net */
E 5
I 5
	struct	in_addr g_addr;		/* address on g_net */
E 5
	int	g_metric;		/* hops to this net */
};

E 3
D 2
#define	alloc_addr(dummy)	((struct addr *) malloc(sizeof(struct addr)))
#define	free_addr(x)		free((char *) x)
#define	NOADDR			((struct addr *) 0)
#define net(x)			((x) & 0xff)
#define host(x)			(((x) >> 8) & 0xff)
#define lhost(x)		(((x) >> 16) & 0xff)
#define imp(x)			(((x) >> 24) & 0xff)

#define	alloc_name(dummy)	((struct name *) malloc(sizeof(struct name)))
#define	free_name(x)		free(x->name_val); \
				free((char *) x)
#define	NONAME			((struct name *) 0)
E 2
I 2
#define	NOADDR			((struct addr *)0)
#define	NONAME			((struct name *)0)
E 2

#define	KW_NET		1
#define	KW_GATEWAY	2
#define	KW_HOST		3

struct name *newname();
D 8
char *malloc();
E 8

char *infile;			/* Input file name */
E 1
