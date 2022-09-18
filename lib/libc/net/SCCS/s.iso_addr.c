h43944
s 00002/00002/00091
d D 8.1 93/06/04 12:50:41 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00002/00089
d D 5.4 91/02/24 12:40:15 bostic 5 4
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00011/00090
d D 5.3 90/06/01 14:15:54 bostic 4 3
c new copyright notice
e
s 00035/00018/00066
d D 5.2 89/09/25 12:49:04 sklower 3 1
c rewrite ascii to addr conversion, fixing bugs
e
s 00006/00005/00079
d R 5.2 89/03/28 16:06:55 sklower 2 1
c correct errors in iso_addr()
e
s 00084/00000/00000
d D 5.1 89/03/27 15:31:16 sklower 1 0
c date and time created 89/03/27 15:31:16 by sklower
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1989 Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
D 4
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 4
I 4
 * %sccs.include.redist.c%
E 4
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <sys/types.h>
#include <netiso/iso.h>
I 5
#include <string.h>

E 5
I 3
/* States*/
#define VIRGIN	0
#define GOTONE	1
#define GOTTWO	2
/* Inputs */
#define	DIGIT	(4*0)
#define	END	(4*1)
#define DELIM	(4*2)
E 3

struct iso_addr *
iso_addr(addr)
D 5
register char *addr;
E 5
I 5
	register const char *addr;
E 5
{
	static struct iso_addr out_addr;
	register char *cp = out_addr.isoa_genaddr;
	char *cplim = cp + sizeof(out_addr.isoa_genaddr);
D 3
	register int byte;
	register nibble_cnt = 0;
E 3
I 3
	register int byte = 0, state = VIRGIN, new;
E 3

	bzero((char *)&out_addr, sizeof(out_addr));
D 3
	while (*addr && (cp < cplim)) {
		byte <<= 8;
E 3
I 3
	do {
E 3
		if ((*addr >= '0') && (*addr <= '9')) {
D 3
			byte += *addr - '0';
E 3
I 3
			new = *addr - '0';
E 3
		} else if ((*addr >= 'a') && (*addr <= 'f')) {
D 3
			byte += *addr - 'a' + 10;
E 3
I 3
			new = *addr - 'a' + 10;
E 3
		} else if ((*addr >= 'A') && (*addr <= 'F')) {
D 3
			byte += *addr - 'A' + 10;
		} else
			nibble_cnt++;
E 3
I 3
			new = *addr - 'A' + 10;
		} else if (*addr == 0) 
			state |= END;
		else
			state |= DELIM;
E 3
		addr++;
D 3
		nibble_cnt++;
		if (nibble_cnt > 1) {
			*cp++ = byte;
			nibble_cnt = byte = 0;
E 3
I 3
		switch (state /* | INPUT */) {
		case GOTTWO | DIGIT:
			*cp++ = byte; /*FALLTHROUGH*/
		case VIRGIN | DIGIT:
			state = GOTONE; byte = new; continue;
		case GOTONE | DIGIT:
			state = GOTTWO; byte = new + (byte << 4); continue;
		default: /* | DELIM */
			state = VIRGIN; *cp++ = byte; byte = 0; continue;
		case GOTONE | END:
		case GOTTWO | END:
			*cp++ = byte; /* FALLTHROUGH */
		case VIRGIN | END:
			break;
E 3
		}
D 3
	}
	if (nibble_cnt && (cp < cplim))
		*cp++ = byte;
E 3
I 3
		break;
	} while (cp < cplim); 
E 3
	out_addr.isoa_len = cp - out_addr.isoa_genaddr;
	return (&out_addr);
}
I 3
static char hexlist[] = "0123456789abcdef";
E 3

char *
iso_ntoa(isoa)
D 5
struct iso_addr *isoa;
E 5
I 5
	const struct iso_addr *isoa;
E 5
{
D 3
	static char hexlist[] = "0123456789abcdef";
E 3
	static char obuf[64];
	register char *out = obuf; 
	register int i;
	register u_char *in = (u_char *)isoa->isoa_genaddr;
	u_char *inlim = in + isoa->isoa_len;

	out[1] = 0;
	while (in < inlim) {
		i = *in++;
		*out++ = '.';
		if (i > 0xf) {
			out[1] = hexlist[i & 0xf];
D 3
			i >>= 8;
E 3
I 3
			i >>= 4;
E 3
			out[0] = hexlist[i];
			out += 2;
		} else
			*out++ = hexlist[i];
	}
	*out = 0;
	return(obuf + 1);
}
E 1
