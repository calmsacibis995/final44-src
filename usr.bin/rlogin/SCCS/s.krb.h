h20968
s 00002/00002/00023
d D 8.1 93/06/06 16:09:39 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00025/00000/00000
d D 5.1 93/03/04 18:31:32 bostic 1 0
c date and time created 93/03/04 18:31:32 by bostic
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1993 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * XXX
 * These should be in a kerberos include file.
 */
void	 des_clear_key __P(());
int	 des_read __P((int, char *, int));
void	 des_set_key __P((C_Block, Key_schedule));
int	 des_write __P((int, char *, int));
int	 krb_net_read __P((int, char *, int));
char	*krb_realmofhost __P((char *));
int	 krb_sendauth __P((long, int, KTEXT, char *, char *, char *,
	    u_long, MSG_DAT *, CREDENTIALS *, Key_schedule,
	    struct sockaddr_in *, struct sockaddr_in *, char *));
int	 krcmd __P((char **, u_short, char *, char *, int *, char *));
int	 krcmd_mutual __P((char **, u_short, char *, char *, int *,
	    char *, CREDENTIALS *, Key_schedule));
E 1
