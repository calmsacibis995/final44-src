h09863
s 00002/00002/00033
d D 8.1 93/06/06 16:32:40 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00035
d D 5.1 90/09/14 10:41:58 borman 11 10
c Bump the sccs id to 5.1
e
s 00002/00000/00033
d D 1.10 90/06/28 12:58:23 borman 10 9
c Lots of bugfixes, add the ENVIRON and X-DISPLAY-LOC
c options, "-l user" to the command line, diagnostic flags.
e
s 00001/00011/00032
d D 1.9 90/06/01 17:44:56 bostic 9 8
c new copyright notice
e
s 00003/00009/00040
d D 1.8 89/08/21 14:58:37 borman 8 7
c Add support for LINEMODE option
e
s 00000/00002/00049
d D 1.7 88/11/30 22:28:02 minshall 7 6
c Flush out the last dregs in the terminal before quitting when
c the remote side quits (actually, there *may* be something left in the
c network input ring, so we don't actually guarantee to get everything).
e
s 00010/00005/00041
d D 1.6 88/06/29 20:15:15 bostic 6 5
c install approved copyright notice
e
s 00014/00000/00032
d D 1.5 88/03/08 10:30:45 bostic 5 4
c add Berkeley specific copyright
e
s 00005/00005/00027
d D 1.4 87/10/23 11:57:16 minshall 4 3
c Make the ring buffer a two-state buffer (supplier and consumer)
c rather than a three-state buffer (supplier, sender, and acker).
e
s 00002/00002/00030
d D 1.3 87/10/10 16:11:08 minshall 3 2
c This version (appears to) works.
e
s 00010/00012/00022
d D 1.2 87/10/10 14:27:09 minshall 2 1
c This is the first version to get near rings.  It compiles,
c but doesn't work.
e
s 00034/00000/00000
d D 1.1 87/09/11 15:40:29 minshall 1 0
c date and time created 87/09/11 15:40:29 by minshall
e
u
U
t
T
I 5
/*
D 12
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 12
I 12
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 12
 *
D 9
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
E 9
I 9
 * %sccs.include.redist.c%
E 9
E 6
 *
 *	%W% (Berkeley) %G%
 */

E 5
I 1
#define	settimer(x)	clocks.x = clocks.system++

#if	!defined(TN3270)

D 2
#define	ExitString(f,s,r)	{ fprintf(f, s); exit(r); }
E 2
I 2
D 7
#define	ExitString(s,r)	{ fprintf(stderr, s); exit(r); }
E 2
#define	Exit(x)			exit(x)
E 7
#define	SetIn3270()

#endif	/* !defined(TN3270) */

D 2
#define	NETADD(c)	{ *nfrontp++ = c; }
E 2
I 2
D 3
#define	NETADD(c)	{ *netoring.send = c; ring_added(&netoring, 1); }
E 3
I 3
D 4
#define	NETADD(c)	{ *netoring.add = c; ring_added(&netoring, 1); }
E 4
I 4
#define	NETADD(c)	{ *netoring.supply = c; ring_supplied(&netoring, 1); }
E 4
E 3
E 2
#define	NET2ADD(c1,c2)	{ NETADD(c1); NETADD(c2); }
D 2
#define NETLOC()	(nfrontp)
#define	NETMAX()	(netobuf+sizeof netobuf-1)
#define	NETBYTES()	(nfrontp-nbackp)
#define	NETROOM()	(NETMAX()-NETLOC()+1)
E 2
I 2
D 4
#define	NETBYTES()	(ring_unsent_count(&netoring))
E 4
I 4
#define	NETBYTES()	(ring_full_count(&netoring))
E 4
#define	NETROOM()	(ring_empty_count(&netoring))
E 2

D 2
#define	TTYADD(c)	{ if (!(SYNCHing||flushout)) { *tfrontp++ = c; } }
#define	TTYLOC()	(tfrontp)
#define	TTYMAX()	(ttyobuf+sizeof ttyobuf-1)
#define	TTYMIN()	(netobuf)
#define	TTYBYTES()	(tfrontp-tbackp)
#define	TTYROOM()	(TTYMAX()-TTYLOC()+1)
E 2
I 2
#define	TTYADD(c)	if (!(SYNCHing||flushout)) { \
D 3
				*ttyoring.send = c; \
E 3
I 3
D 4
				*ttyoring.add = c; \
E 3
				ring_added(&ttyoring, 1); \
E 4
I 4
				*ttyoring.supply = c; \
				ring_supplied(&ttyoring, 1); \
E 4
			}
D 4
#define	TTYBYTES()	(ring_unsent_count(&ttyoring))
E 4
I 4
#define	TTYBYTES()	(ring_full_count(&ttyoring))
E 4
#define	TTYROOM()	(ring_empty_count(&ttyoring))
E 2

/*	Various modes */
D 8
#define	MODE_LINE(m)	(modelist[m].modetype & LINE)
#define	MODE_LOCAL_CHARS(m)	(modelist[m].modetype &  LOCAL_CHARS)
#define	MODE_LOCAL_ECHO(m)	(modelist[m].modetype & LOCAL_ECHO)
#define	MODE_COMMAND_LINE(m)	(modelist[m].modetype & COMMAND_LINE)

#define	LOCAL_CHARS	0x01		/* Characters processed locally */
#define	LINE		0x02		/* Line-by-line mode of operation */
#define	LOCAL_ECHO	0x04		/* Echoing locally */
#define	COMMAND_LINE	0x08		/* Command line mode */
E 8
I 8
#define	MODE_LOCAL_CHARS(m)	((m)&(MODE_EDIT|MODE_TRAPSIG))
#define	MODE_LOCAL_ECHO(m)	((m)&MODE_ECHO)
#define	MODE_COMMAND_LINE(m)	((m)==-1)
I 10

#define	CONTROL(x)	((x)&0x1f)		/* CTRL(x) is not portable */
E 10
E 8
E 1
