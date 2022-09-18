h32879
s 00001/00001/00040
d D 8.3 95/02/19 07:50:24 cgd 16 15
c fix return type for unp_detach()
e
s 00018/00003/00023
d D 8.2 95/01/09 18:16:14 cgd 15 14
c 64-bit changes: ioctl cmd -> u_long, some protos.  some style, return vals.
e
s 00002/00002/00024
d D 8.1 93/06/02 19:56:34 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00025
d D 7.7 90/06/28 22:01:45 bostic 13 12
c new copyright notice
e
s 00005/00000/00031
d D 7.6 90/06/06 08:14:51 karels 12 11
c add macro for len of sockaddr_un
e
s 00001/00001/00030
d D 7.5 89/12/15 14:27:46 karels 11 10
c mbufs are smaller now, so this must be too.
e
s 00002/00001/00029
d D 7.4 89/09/04 18:14:44 sklower 10 9
c change to add explicit length field and make compatible with
c other sockaddr types.
e
s 00010/00005/00020
d D 7.3 88/06/27 18:54:53 bostic 9 8
c install approved copyright notice
e
s 00008/00002/00017
d D 7.2 87/12/30 12:04:51 bostic 8 7
c add Berkeley header
e
s 00001/00001/00018
d D 7.1 86/06/04 23:30:57 mckusick 7 6
c 4.3BSD release version
e
s 00007/00001/00012
d D 6.3 85/06/08 15:11:41 mckusick 6 5
c Add copyright
e
s 00001/00001/00012
d D 6.2 84/05/07 13:12:59 karels 5 4
c avoid sizeof compiler padding
e
s 00000/00000/00013
d D 6.1 83/07/29 06:14:47 sam 4 3
c 4.2 distribution
e
s 00001/00001/00012
d D 5.3 83/06/13 23:03:29 sam 3 2
c show true limitation
e
s 00004/00000/00009
d D 5.2 83/05/27 13:59:07 sam 2 1
c wnj'ify for rights passing
e
s 00009/00000/00000
d D 5.1 82/08/02 00:05:25 root 1 0
c date and time created 82/08/02 00:05:25 by root
e
u
U
t
T
I 1
D 6
/*	%M%	%I%	%E%	*/
E 6
I 6
/*
D 7
 * Copyright (c) 1982 Regents of the University of California.
E 7
I 7
D 14
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 7
D 8
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 8
I 8
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1982, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
 *
D 13
 * Redistribution and use in source and binary forms are permitted
D 9
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 9
I 9
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
E 13
I 13
 * %sccs.include.redist.c%
E 13
E 9
E 8
 *
 *	%W% (Berkeley) %G%
 */
E 6

/*
 * Definitions for UNIX IPC domain.
 */
struct	sockaddr_un {
D 10
	short	sun_family;		/* AF_UNIX */
E 10
I 10
	u_char	sun_len;		/* sockaddr len including null */
	u_char	sun_family;		/* AF_UNIX */
E 10
D 3
	char	sun_path[14];		/* path name */
E 3
I 3
D 5
	char	sun_path[109];		/* path name (gag) */
E 5
I 5
D 11
	char	sun_path[108];		/* path name (gag) */
E 11
I 11
	char	sun_path[104];		/* path name (gag) */
E 11
E 5
E 3
};
I 2

#ifdef KERNEL
D 15
int	unp_discard();
I 12
#else
E 15
I 15
struct unpcb;
E 15

I 15
int	uipc_usrreq __P((struct socket *so, int req, struct mbuf *m,
		struct mbuf *nam, struct mbuf *control));
int	unp_attach __P((struct socket *so));
int	unp_bind __P((struct unpcb *unp, struct mbuf *nam, struct proc *p));
int	unp_connect __P((struct socket *so, struct mbuf *nam, struct proc *p));
int	unp_connect2 __P((struct socket *so, struct socket *so2));
D 16
int	unp_detach __P((struct unpcb *unp));
E 16
I 16
void	unp_detach __P((struct unpcb *unp));
E 16
void	unp_discard __P((struct file *fp));
void	unp_disconnect __P((struct unpcb *unp));
void	unp_drop __P((struct unpcb *unp, int errno));
void	unp_gc __P((void));
void	unp_mark __P((struct file *fp));
void	unp_scan __P((struct mbuf *m0, void (*op) __P((struct file *))));
void	unp_shutdown __P((struct unpcb *unp));
#else /* !KERNEL */

E 15
/* actual length of an initialized sockaddr_un */
#define SUN_LEN(su) \
	(sizeof(*(su)) - sizeof((su)->sun_path) + strlen((su)->sun_path))
E 12
D 15
#endif
E 15
I 15
#endif /* KERNEL */
E 15
E 2
E 1
