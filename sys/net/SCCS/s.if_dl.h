h49349
s 00002/00002/00052
d D 8.1 93/06/10 22:44:38 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00000/00044
d D 7.2 91/02/22 09:22:17 donn 2 1
c Declarations for link_addr and link_ntoa.
e
s 00044/00000/00000
d D 7.1 90/07/01 10:59:18 karels 1 0
c initial version by sklower
e
u
U
t
T
I 1
/*
D 3
 * Copyright (c) 1990 Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/* 
 * A Link-Level Sockaddr may specify the interface in one of two
 * ways: either by means of a system-provided index number (computed
 * anew and possibly differently on every reboot), or by a human-readable
 * string such as "il0" (for managerial convenience).
 * 
 * Census taking actions, such as something akin to SIOCGCONF would return
 * both the index and the human name.
 * 
 * High volume transactions (such as giving a link-level ``from'' address
 * in a recvfrom or recvmsg call) may be likely only to provide the indexed
 * form, (which requires fewer copy operations and less space).
 * 
 * The form and interpretation  of the link-level address is purely a matter
 * of convention between the device driver and its consumers; however, it is
 * expected that all drivers for an interface of a given if_type will agree.
 */

/*
 * Structure of a Link-Level sockaddr:
 */
struct sockaddr_dl {
	u_char	sdl_len;	/* Total length of sockaddr */
	u_char	sdl_family;	/* AF_DLI */
	u_short	sdl_index;	/* if != 0, system given index for interface */
	u_char	sdl_type;	/* interface type */
	u_char	sdl_nlen;	/* interface name length, no trailing 0 reqd. */
	u_char	sdl_alen;	/* link level address length */
	u_char	sdl_slen;	/* link layer selector length */
	char	sdl_data[12];	/* minimum work area, can be larger;
				   contains both if name and ll address */
};

#define LLADDR(s) ((caddr_t)((s)->sdl_data + (s)->sdl_nlen))

I 2
#ifndef KERNEL

#include <sys/cdefs.h>

__BEGIN_DECLS
void	link_addr __P((const char *, struct sockaddr_dl *));
char	*link_ntoa __P((const struct sockaddr_dl *));
__END_DECLS

#endif /* !KERNEL */
E 2
E 1
