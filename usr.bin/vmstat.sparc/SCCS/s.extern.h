h25690
s 00002/00002/00028
d D 8.1 93/06/06 22:22:30 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00030/00000/00000
d D 5.1 93/05/21 15:10:05 torek 1 0
c date and time created 93/05/21 15:10:05 by torek
e
u
U
t
T
I 1
/*
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

struct dkinfo {
	struct	dkinfo *dk_next;
	char	*dk_name;	/* full-length name */
	char	dk_2c[3];	/* two-character version of dk_name */
	int	dk_sel;		/* 1 if we should print this one */
	u_long	dk_addr;	/* kernel addr of struct dkdevice */
	long	dk_oxfer;	/* previous xfer stat */
	long	dk_dxfer;	/* delta between oxfer and cur xfer */
};
extern struct dkinfo *dkinfo;
extern int ndrives;
extern kvm_t *kd;

void	dointr __P((void));
void	domem __P((void));
void	dosum __P((void));
void	dovmstat __P((u_int, int));
void	errexit __P((const char *, ...));
long	getuptime __P((void));
void	knlist __P((struct nlist *));
void	kread __P((u_long, void *, size_t, char *));
E 1
