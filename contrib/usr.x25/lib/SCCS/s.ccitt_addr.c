h47732
s 00007/00003/00142
d D 5.3 91/07/01 11:58:06 sklower 3 2
c allow more than 4 bytes of c/userdata
e
s 00009/00000/00136
d D 5.2 91/04/29 18:36:24 sklower 2 1
c initialize x25_len field.  Put in yucky berkeley copyright
e
s 00136/00000/00000
d D 5.1 90/09/03 18:58:37 sklower 1 0
c date and time created 90/09/03 18:58:37 by sklower
e
u
U
t
T
I 1
/*
I 2
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */
/*
E 2
 * parse CCITT addresses
 *
 * Addresses must have the format: [hpr],x121address[,userdata][,protocol]
 * items enclosed with square brackets are optional
 * 'h' or 'p' means hi priority (packet size = 128; specific to Datapac
 * and necessary only for X.25(76) and non-negotiating X.25(80) DTE's)
 * 'r' means reverse charge (remote DTE pays for call).
 * The x121address consists of an optional netid and dot, followed
 * by a dte address.
 *
 * Frank Pronk
 * The University of British Columbia
 * Laboratory for Computational Vision
 * Copyright (c) 1984
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netccitt/x25.h>

static char *copychar ();

ccitt_addr (addr, xp)
char *addr;
register struct sockaddr_x25 *xp;
{
	register char *p, *ap, *limit;
D 3
	register int havenet = 0;
E 3
I 3
	int havenet = 0;
E 3

	bzero ((char *)xp, sizeof (*xp));
	xp->x25_family = AF_CCITT;
I 2
	xp->x25_len = sizeof(*xp);
E 2
D 3
	xp->x25_udlen = 4;
E 3
	p = addr;

	/*
	 * process optional priority and reverse charging flags
	 */

	if (*p == 'p' || *p == 'r' || *p == 'h') {
		while (*p == 'p' || *p == 'r' || *p == 'h') {
			if (*p == 'p' || *p == 'h')
				xp->x25_opts.op_psize = X25_PS128;
			else if (*p == 'r')
				xp->x25_opts.op_flags |= X25_REVERSE_CHARGE;
			p++;
		}
		if (*p != ',')
			return (0);
		p++;
	}
	if (*p == '\0')
		return (0);

	/*
	 * [network id:]X.121 address
	 */

	ap = xp->x25_addr;
	limit = ap + sizeof (xp->x25_addr) - 1;
	while (*p) {
		if (*p == ',')
			break;
		if (*p == '.' || *p == ':') {
			if (havenet)
				return (0);
			havenet++;
			xp->x25_net = atoi (xp->x25_addr);
			p++;
			ap = xp->x25_addr;
			*ap = '\0';
		}
		if (*p < '0' || *p > '9')
			return (0);
		if (ap >= limit)
			return (0);
		*ap++ = *p++;
	}
	if (*p == '\0')
		return (1);

	/*
	 * optional user data, bytes 4 to 16
	 */

	p++;
	ap = xp->x25_udata + 4;		/* first four bytes are protocol id */
	limit = ap + sizeof (xp->x25_udata) - 4;
I 3
	xp->x25_udlen = 4;
E 3
	while (*p) {
		if (*p == ',')
			break;
		if (ap >= limit)
			return (0);
		p = copychar (p, ap++);
		xp->x25_udlen++;
	}
I 3
	if (xp->x25_udlen == 4)
		xp->x25_udlen = 0;
E 3
	if (*p == '\0')
		return (1);

	p++;
	ap = xp->x25_udata;		/* protocol id */
D 3
	limit = ap + 4;
E 3
I 3
	limit = ap + (xp->x25_udlen ? 4 : sizeof(xp->x25_udata));
E 3
	while (*p) {
		if (*p == ',')
			return (0);
		if (ap >= limit)
			return (0);
		p = copychar (p, ap++);
	}
I 3
	if (xp->x25_udlen == 0)
		xp->x25_udlen = ap - xp->x25_udata;
E 3
	return (1);
}

static char *
copychar (from, to)
register char *from, *to;
{
	register int n;

	if (*from != '\\' || from[1] < '0' || from[1] > '7') {
		*to = *from++;
		return (from);
	}
	n = *++from - '0';
	from++;
	if (*from >= '0' && *from <= '7') {
		register int n1;

		n = n*8 + *from++ - '0';
		if (*from >= '0' && *from <= '7' && (n1 = n*8 + *from-'0') < 256) {
			n = n1;
			from++;
		}
	}
	*to = n;
	return (from);
}
E 1
