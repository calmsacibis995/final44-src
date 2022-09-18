h11435
s 00003/00013/00048
d D 5.2 93/05/29 11:20:58 bostic 2 1
c new copyright notice
e
s 00061/00000/00000
d D 5.1 89/05/16 08:59:33 bostic 1 0
c date and time created 89/05/16 08:59:33 by bostic
e
u
U
t
T
I 1
D 2
/*
 * Copyright (c) 1989 The Regents of the University of California.
E 2
I 2
/*-
 * Copyright (c) 1993 The Regents of the University of California.
E 2
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Bill Jolitz.
 *
D 2
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 2
I 2
 * %sccs.include.redist.c%
E 2
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Telephone number address processing
 */

/*
 * Structures returned by network
 * data base library.
 */
struct	phonenumberent {
	char	*pn_name;	/* directory listing name */
	char	**pn_aliases;	/* alias list */
	int	pn_length;	/* length of phone number address */
	char	**pn_addr_list;	/* list of addresses from name server */
	struct	pn_addr	*pn_addrtype;	/* list of phone number address types */
};

struct pn_addrtype {
	u_char	pn_tos ;	/* type of service */
# define	PNT_POTS	0	/* plain ordinary telephone service */
# define	PNT_ISDN	1	/* Integrated Services Digital Network*/
	int	pn_tnplan ;	/* type of numbering plan */
# define	PNAT_INTL	0x21	/* International number */
# define	PNAT_NATNL	0x41	/* National number */
# define	PNAT_LOCAL	0x81	/* Local(directory) number */
} ;

struct phonenumberent	*getphonenumberbyname(), *getnamebyphonenumber(),
			*getphonenumberent();

/*
 * Error return codes from getphonenumberbyname() and getnamebyphonenumber()
 */

extern  int pn_errno;	

#define	ENTRY_NOT_FOUND	1 /* Authoritive Answer Host not found */
#define	TRY_AGAIN	2 /* Non-Authoritive Host not found, or SERVERFAIL */
#define	NO_RECOVERY	3 /* Non recoverable errors, FORMERR, REFUSED, NOTIMP */
#define NO_ADDRESS	4 /* Valid host name, no address, look for MX record */
E 1
