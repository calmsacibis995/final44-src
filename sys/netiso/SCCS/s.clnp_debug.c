h27858
s 00002/00002/00232
d D 8.1 93/06/10 23:18:18 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00005/00229
d D 7.11 93/05/25 11:51:26 bostic 11 10
c trailing comment after #else or #endif
e
s 00013/00014/00221
d D 7.10 92/10/11 12:21:32 bostic 10 9
c make kernel includes standard
e
s 00004/00003/00231
d D 7.9 92/02/14 14:16:30 sklower 9 8
c changes proposed by hagens to make CLNP EchoReply work
e
s 00000/00001/00234
d D 7.8 91/05/27 14:43:38 sklower 8 7
c no more clnp_sprintf.c; merged into main kernel
e
s 00001/00001/00234
d D 7.7 91/05/09 11:46:27 sklower 7 6
c change name of file
e
s 00003/00093/00232
d D 7.6 91/05/08 23:01:50 bostic 6 5
c redo sprintf to be general purpose, delete any AT&T propriety code
e
s 00009/00005/00316
d D 7.5 91/05/06 18:58:46 bostic 5 4
c new copyright; att/bsd/shared
e
s 00002/00001/00319
d D 7.4 89/08/29 13:43:43 sklower 4 3
c checkpoint for ``alpha tape''; tp is still a little broken.
e
s 00008/00008/00312
d D 7.3 89/04/25 17:19:25 mckusick 3 2
c ../h => (implicitly) ../sys
e
s 00021/00042/00299
d D 7.2 89/04/22 11:53:14 sklower 2 1
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00341/00000/00000
d D 7.1 88/12/14 15:29:22 sklower 1 0
c date and time created 88/12/14 15:29:22 by sklower
e
u
U
t
T
I 5
/*-
D 12
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 12
I 12
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 12
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 5
I 1
/***********************************************************
		Copyright IBM Corporation 1987

                      All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the name of IBM not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.  

IBM DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
IBM BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/

/*
 * ARGO Project, Computer Sciences Dept., University of Wisconsin - Madison
 */
/* $Header: clnp_debug.c,v 4.2 88/06/29 14:58:34 hagens Exp $ */
/* $Source: /usr/argo/sys/netargo/RCS/clnp_debug.c,v $ */
I 4
D 5
/*	%W% (Berkeley) %G% */
E 4

#ifndef lint
static char *rcsid = "$Header: clnp_debug.c,v 4.2 88/06/29 14:58:34 hagens Exp $";
#endif lint
E 5

D 3
#include "../h/types.h"
#include "../h/param.h"
#include "../h/mbuf.h"
#include "../h/domain.h"
#include "../h/protosw.h"
#include "../h/socket.h"
#include "../h/socketvar.h"
#include "../h/errno.h"
E 3
I 3
D 10
#include "types.h"
#include "param.h"
#include "mbuf.h"
#include "domain.h"
#include "protosw.h"
#include "socket.h"
#include "socketvar.h"
#include "errno.h"
E 10
I 10
#include <sys/param.h>
#include <sys/mbuf.h>
#include <sys/domain.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/errno.h>
E 10
E 3

D 10
#include "../net/if.h"
#include "../net/route.h"
E 10
I 10
#include <net/if.h>
#include <net/route.h>
E 10

D 2
#include "../netiso/iso.h"
#include "../netiso/clnp.h"
#include "../netiso/clnp_stat.h"
#include "../netiso/argo_debug.h"
E 2
I 2
D 10
#include "iso.h"
#include "clnp.h"
#include "clnp_stat.h"
#include "argo_debug.h"
E 10
I 10
#include <netiso/iso.h>
#include <netiso/clnp.h>
#include <netiso/clnp_stat.h>
#include <netiso/argo_debug.h>
E 10
E 2

#ifdef	ARGO_DEBUG

#ifdef	TESTDEBUG
#ifdef notdef
struct addr_37 u_37 = {
	{0x00, 0x02, 0x00, 0x10, 0x20, 0x30, 0x35}, 
	{0x01, 0x02, 0x03, 0x04, 0x50, 0x60, 0x70, 0x80, 0x90}
};
struct addr_osinet u_osinet = {
	{0x00, 0x04},
	{0x00, 0x02, 0x00, 0x01, 0x23, 0x42, 0x78, 0x20, 0x01, 0x05, 0x00}
};
D 11
#endif notdef
E 11
I 11
#endif /* notdef */
E 11
struct addr_rfc986 u_rfc986 = {
	{0x00, 0x06},
	{0x01, 0xc0, 0x0c, 0x0c, 0xab, 0x11}
};
struct addr_rfc986 u_bad = {
	{0x00, 0x01},
	{0x01, 0xc0, 0x0c, 0x0c, 0xab, 0x11}
};
#include <stdio.h>
main()
{
	struct iso_addr	a;

	a.isoa_afi = AFI_37;
	a.isoa_u.addr_37 = u_37;
	a.isoa_len = 17;
	printf("type 37: %s\n", clnp_iso_addrp(&a));

	a.isoa_afi = AFI_OSINET;
	a.isoa_u.addr_osinet = u_osinet;
	a.isoa_len = 14;
	printf("type osinet: %s\n", clnp_iso_addrp(&a));

	a.isoa_afi = AFI_RFC986;
	a.isoa_u.addr_rfc986 = u_rfc986;
	a.isoa_len = 9;
	printf("type rfc986: %s\n", clnp_iso_addrp(&a));

	a.isoa_afi = 12;
	a.isoa_u.addr_rfc986 = u_rfc986;
	a.isoa_len = 9;
	printf("type bad afi: %s\n", clnp_iso_addrp(&a));

	a.isoa_afi = AFI_RFC986;
	a.isoa_u.addr_rfc986 = u_bad;
	a.isoa_len = 9;
	printf("type bad idi: %s\n", clnp_iso_addrp(&a));
}
D 11
#endif	TESTDEBUG
E 11
I 11
#endif	/* TESTDEBUG */
E 11

unsigned int	clnp_debug;
static char letters[] = "0123456789abcdef";

/*
 *	Print buffer in hex, return addr of where we left off.
 *	Do not null terminate.
 */
char *
clnp_hexp(src, len, where)
char	*src;		/* src of data to print */
D 9
int		len;		/* lengthof src */
E 9
I 9
int		len;				/* lengthof src */
E 9
char	*where;		/* where to put data */
{
	int i;

	for (i=0; i<len; i++) {
D 9
		*where++ = letters[src[i] >> 4];
		*where++ = letters[src[i] & 0x0f];
E 9
I 9
		register int j = ((u_char *)src)[i];
		*where++ = letters[j >> 4];
		*where++ = letters[j & 0x0f];
E 9
	}
	return where;
}

/*
 *	Return a ptr to a human readable form of an iso addr 
 */
static char iso_addr_b[50];
#define	DELIM	'.';

char *
clnp_iso_addrp(isoa)
struct iso_addr *isoa;
{
	char	*cp;

	/* print length */
D 6
	clnp_sprintf(iso_addr_b, "[%d] ", isoa->isoa_len);
E 6
I 6
	sprintf(iso_addr_b, "[%d] ", isoa->isoa_len);
E 6

	/* set cp to end of what we have */
	cp = iso_addr_b;
	while (*cp)
		cp++;

	/* print afi */
D 2
	cp = clnp_hexp(&isoa->isoa_afi, 1, cp);
E 2
I 2
	cp = clnp_hexp(isoa->isoa_genaddr, (int)isoa->isoa_len, cp);
#ifdef notdef
E 2
	*cp++ = DELIM;

	/* print type specific part */
	switch(isoa->isoa_afi) {
		case AFI_37:
			cp = clnp_hexp(isoa->t37_idi, ADDR37_IDI_LEN, cp);
			*cp++ = DELIM;
			cp = clnp_hexp(isoa->t37_dsp, ADDR37_DSP_LEN, cp);
			break;
		
/* 		case AFI_OSINET:*/
		case AFI_RFC986: {
			u_short	idi;

			/* osinet and rfc986 have idi in the same place */
			/* print idi */
			cp = clnp_hexp(isoa->rfc986_idi, ADDROSINET_IDI_LEN, cp);
			*cp++ = DELIM;
			CTOH(isoa->rfc986_idi[0], isoa->rfc986_idi[1], idi);

			if (idi == IDI_OSINET) {
				struct ovl_osinet *oosi = (struct ovl_osinet *)isoa;
				cp = clnp_hexp(oosi->oosi_orgid, OVLOSINET_ORGID_LEN, cp);
				*cp++ = DELIM;
				cp = clnp_hexp(oosi->oosi_snetid, OVLOSINET_SNETID_LEN, cp);
				*cp++ = DELIM;
				cp = clnp_hexp(oosi->oosi_snpa, OVLOSINET_SNPA_LEN, cp);
				*cp++ = DELIM;
				cp = clnp_hexp(oosi->oosi_nsap, OVLOSINET_NSAP_LEN, cp);
			} else if (idi == IDI_RFC986) {
				struct ovl_rfc986 *o986 = (struct ovl_rfc986 *)isoa;
				cp = clnp_hexp(&o986->o986_vers, 1, cp);
				*cp++ = DELIM;
#ifdef  vax
D 6
				clnp_sprintf(cp, "%d.%d.%d.%d.%d", 
E 6
I 6
				sprintf(cp, "%d.%d.%d.%d.%d", 
E 6
				o986->o986_inetaddr[0] & 0xff,
				o986->o986_inetaddr[1] & 0xff,
				o986->o986_inetaddr[2] & 0xff,
				o986->o986_inetaddr[3] & 0xff,
				o986->o986_upid & 0xff);
				return(iso_addr_b);
#else
				cp = clnp_hexp(&o986->o986_inetaddr[0], 1, cp);
				*cp++ = DELIM;
				cp = clnp_hexp(&o986->o986_inetaddr[1], 1, cp);
				*cp++ = DELIM;
				cp = clnp_hexp(&o986->o986_inetaddr[2], 1, cp);
				*cp++ = DELIM;
				cp = clnp_hexp(&o986->o986_inetaddr[3], 1, cp);
				*cp++ = DELIM;
				cp = clnp_hexp(&o986->o986_upid, 1, cp);
D 11
#endif vax
E 11
I 11
#endif /* vax */
E 11
			}
			
		} break;

		default:
			*cp++ = '?';
			break;
	}
I 2
D 11
#endif notdef
E 11
I 11
#endif /* notdef */
E 11
E 2
	*cp = (char)0;
	
	return(iso_addr_b);
}

D 2
#define	MAX_COLUMNS	8
/*
 *	Dump the buffer to the screen in a readable format. Format is:
 *
 *		hex/dec  where hex is the hex format, dec is the decimal format.
 *		columns of hex/dec numbers will be printed, followed by the
 *		character representations (if printable).
 */
dump_buf(buf, len)
char	*buf;
int		len;
E 2
I 2
char *
clnp_saddr_isop(s)
register struct sockaddr_iso *s;
E 2
{
D 2
	int		i,j;
E 2
I 2
	register char	*cp = clnp_iso_addrp(&s->siso_addr);
E 2

D 2
	printf("Dump buf 0x%x len 0x%x\n", buf, len);
	for (i = 0; i < len; i += MAX_COLUMNS) {
		printf("+%d:\t", i);
		for (j = 0; j < MAX_COLUMNS; j++) {
			if (i + j < len) {
				printf("%x/%d\t", buf[i+j]&0xff, buf[i+j]);
			} else {
				printf("	");
			}
		}

		for (j = 0; j < MAX_COLUMNS; j++) {
			if (i + j < len) {
				if (((buf[i+j]) > 31) && ((buf[i+j]) < 128))
					printf("%c", buf[i+j]&0xff);
				else
					printf(".");
			}
		}
		printf("\n");
	}
E 2
I 2
	while (*cp) cp++;
	*cp++ = '(';
D 4
	cp = clnp_hexp(TSEL(s), (int)s->siso_tsuffixlen, cp);
E 4
I 4
	cp = clnp_hexp(TSEL(s), (int)s->siso_tlen, cp);
E 4
	*cp++ = ')';
	*cp++ = 0;
	return (iso_addr_b);
E 2
}

D 6

/*
 *		The following hacks are a trimmed down version of sprintf.
 */
/*VARARGS1*/
I 2
/*ARGSUSED*/
E 2
clnp_sprintf(buf, fmt, x1, x2)
D 2
	register char *fmt;
E 2
I 2
	register char *buf, *fmt;
E 2
	unsigned x1, x2;
{
D 2
	clnp_prf(buf, fmt, &x1, 0);
E 2
I 2
	clnp_prf(buf, fmt, (unsigned int *)&x1);
E 2
}

D 2
clnp_prf(buf, fmt, adx, dummy)
E 2
I 2
clnp_prf(buf, fmt, adx)
E 2
	register char	*buf;
	register char *fmt;
	register unsigned int *adx;
D 2
	int	dummy;
E 2
{
	register int b, c, i;
	char *s;
	char *clnp_printn();

loop:
	while ((c = *fmt++) != '%') {
		if(c == '\0') {
			*buf++ = (char)0;
			return;
		}
		*buf++ = c;
	}
again:
	c = *fmt++;
	switch (c) {
	case 'l':
		goto again;
	case 'x': case 'X':
		b = 16;
		goto number;
	case 'd': case 'D':
	case 'u':		/* what a joke */
		b = 10;
		goto number;
	case 'o': case 'O':
		b = 8;
number:
		buf = clnp_printn((unsigned long)*adx, b, buf);
		break;
	case 'c':
		b = *adx;
		for (i = 24; i >= 0; i -= 8)
			if (c = (b >> i) & 0x7f)
				*buf++ = c;
		break;

	case 's':
		s = (char *)*adx;
		while (*s)
			*buf++ = *s++;
		break;

	case '%':
		*buf++ = '%';
		break;
	}
	adx++;
	goto loop;
}

char *
clnp_printn(n, b, where)
unsigned long	n;
int		b;
char	*where;
{
	char prbuf[11];
	register char *cp;

	if (b == 10 && (int)n < 0) {
		*where++ = '-';
		n = (unsigned)(-(int)n);
	}
	cp = prbuf;
	do {
		*cp++ = "0123456789abcdef"[n%b];
		n /= b;
	} while (n);
	do {
		*where++ = *--cp;
	} while (cp > prbuf);
	return(where);
}
E 6
I 6
D 7
#include "subr_prf.sprintf"
E 7
I 7
D 8
#include "clnp_sprintf.c"
E 8
E 7
E 6
D 11
#endif	ARGO_DEBUG
E 11
I 11
#endif	/* ARGO_DEBUG */
E 11
E 1
