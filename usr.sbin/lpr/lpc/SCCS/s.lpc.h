h01740
s 00002/00002/00017
d D 8.1 93/06/06 14:00:12 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00017
d D 5.5 92/07/21 10:28:59 bostic 6 5
c prototype lpr to fix quad's
e
s 00001/00011/00017
d D 5.4 90/06/01 18:44:16 bostic 5 4
c new copyright notice
e
s 00010/00005/00018
d D 5.3 88/06/30 17:59:49 bostic 4 3
c install approved copyright notice
e
s 00008/00002/00015
d D 5.2 88/05/05 18:07:58 bostic 3 2
c written by Ralph Campbell; add Berkeley specific header
e
s 00007/00001/00010
d D 5.1 85/06/06 10:11:32 dist 2 1
c Add copyright
e
s 00011/00000/00000
d D 4.1 83/05/11 16:03:40 ralph 1 0
c date and time created 83/05/11 16:03:40 by ralph
e
u
U
t
T
I 1
D 2
/*	%M% (Berkeley) %G%	*/
E 2
I 2
/*
D 7
 * Copyright (c) 1983 Regents of the University of California.
D 3
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
D 5
 * Redistribution and use in source and binary forms are permitted
D 4
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 4
I 4
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
E 5
I 5
 * %sccs.include.redist.c%
E 5
E 4
E 3
 *
 *	%W% (Berkeley) %G%
 */
E 2

/*
 * Line printer control program.
 */
struct	cmd {
	char	*c_name;		/* command name */
	char	*c_help;		/* help message */
D 6
	int	(*c_handler)();		/* routine to do the work */
E 6
I 6
					/* routine to do the work */
	void	(*c_handler) __P((int, char *[]));
E 6
	int	c_priv;			/* privileged command */
};
E 1
