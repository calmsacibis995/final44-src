h41313
s 00002/00002/00031
d D 8.1 93/06/10 23:35:29 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00032
d D 7.4 90/06/28 21:49:29 bostic 7 6
c new copyright notice
e
s 00011/00006/00032
d D 7.3 88/06/29 17:13:42 bostic 6 5
c install approved copyright notice
e
s 00010/00004/00028
d D 7.2 88/01/20 15:15:35 sklower 5 4
c Change licensing/use notice.
e
s 00001/00001/00031
d D 7.1 86/06/05 00:38:36 mckusick 4 3
c 4.3BSD release version
e
s 00001/00001/00031
d D 6.3 86/02/03 17:41:12 sklower 3 2
c Correct erroneous copyright information.
e
s 00007/00001/00025
d D 6.2 85/06/08 12:52:19 mckusick 2 1
c Add copyright
e
s 00026/00000/00000
d D 6.1 85/05/30 19:11:12 sklower 1 0
c date and time created 85/05/30 19:11:12 by sklower
e
u
U
t
T
I 1
D 2
/*      %M%     %I%     %E%     */
E 2
I 2
/*
D 3
 * Copyright (c) 1982 Regents of the University of California.
E 3
I 3
D 4
 * Copyright (c) 1984 Regents of the University of California.
E 4
I 4
D 5
 * Copyright (c) 1984, 1986 Regents of the University of California.
E 4
E 3
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
D 8
 * Copyright (c) 1984, 1985, 1986, 1987 Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1984, 1985, 1986, 1987, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
E 5
 *
D 5
 *	%W% (Berkeley) %G%
E 5
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
D 6
 *      %W% (Berkeley) %G%
E 6
I 6
 *	%W% (Berkeley) %G%
E 6
E 5
 */
E 2

struct	spp_debug {
	u_long	sd_time;
	short	sd_act;
	short	sd_ostate;
	caddr_t	sd_cb;
	short	sd_req;
	struct	spidp sd_si;
	struct	sppcb sd_sp;
};

#define	SA_INPUT 	0
#define	SA_OUTPUT	1
#define	SA_USER		2
#define	SA_RESPOND	3
#define	SA_DROP		4

#ifdef SANAMES
char	*sanames[] =
    { "input", "output", "user", "respond", "drop" };
#endif

#define	SPP_NDEBUG 100
struct	spp_debug spp_debug[SPP_NDEBUG];
int	spp_debx;
E 1
