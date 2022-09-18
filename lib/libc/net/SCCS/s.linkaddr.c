h26424
s 00002/00002/00130
d D 8.1 93/06/04 12:50:51 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00019/00007/00113
d D 5.4 92/06/25 08:23:28 bostic 4 3
c KNF
e
s 00008/00004/00112
d D 5.3 91/07/29 19:50:03 karels 3 2
c use alen for hex address, not nlen; no ':' if no addr
e
s 00005/00003/00111
d D 5.2 91/02/24 12:40:16 bostic 2 1
c Add include files to get prototype declarations, and fix bugs found.
e
s 00114/00000/00000
d D 5.1 90/06/01 16:25:30 bostic 1 0
c date and time created 90/06/01 16:25:30 by bostic
e
u
U
t
T
I 1
/*-
D 5
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <sys/types.h>
#include <sys/socket.h>
#include <net/if_dl.h>
I 2
#include <string.h>
E 2

/* States*/
#define NAMING	0
#define GOTONE	1
#define GOTTWO	2
#define RESET	3
/* Inputs */
#define	DIGIT	(4*0)
#define	END	(4*1)
#define DELIM	(4*2)
#define LETTER	(4*3)

I 2
void
E 2
link_addr(addr, sdl)
D 2
register char *addr;
register struct sockaddr_dl *sdl;
E 2
I 2
	register const char *addr;
	register struct sockaddr_dl *sdl;
E 2
{
	register char *cp = sdl->sdl_data;
	char *cplim = sdl->sdl_len + (char *)sdl;
	register int byte = 0, state = NAMING, new;

	bzero((char *)&sdl->sdl_family, sdl->sdl_len - 1);
	sdl->sdl_family = AF_LINK;
	do {
		state &= ~LETTER;
		if ((*addr >= '0') && (*addr <= '9')) {
			new = *addr - '0';
		} else if ((*addr >= 'a') && (*addr <= 'f')) {
			new = *addr - 'a' + 10;
		} else if ((*addr >= 'A') && (*addr <= 'F')) {
			new = *addr - 'A' + 10;
		} else if (*addr == 0) {
			state |= END;
		} else if (state == NAMING &&
			   (((*addr >= 'A') && (*addr <= 'Z')) ||
			   ((*addr >= 'a') && (*addr <= 'z'))))
			state |= LETTER;
		else
			state |= DELIM;
		addr++;
		switch (state /* | INPUT */) {
		case NAMING | DIGIT:
		case NAMING | LETTER:
D 4
			*cp++ = addr[-1]; continue;
E 4
I 4
			*cp++ = addr[-1];
			continue;
E 4
		case NAMING | DELIM:
D 4
			state = RESET; sdl->sdl_nlen = cp - sdl->sdl_data; continue;
E 4
I 4
			state = RESET;
			sdl->sdl_nlen = cp - sdl->sdl_data;
			continue;
E 4
		case GOTTWO | DIGIT:
D 4
			*cp++ = byte; /*FALLTHROUGH*/
E 4
I 4
			*cp++ = byte;
			/* FALLTHROUGH */
E 4
		case RESET | DIGIT:
D 4
			state = GOTONE; byte = new; continue;
E 4
I 4
			state = GOTONE;
			byte = new;
			continue;
E 4
		case GOTONE | DIGIT:
D 4
			state = GOTTWO; byte = new + (byte << 4); continue;
E 4
I 4
			state = GOTTWO;
			byte = new + (byte << 4);
			continue;
E 4
		default: /* | DELIM */
D 4
			state = RESET; *cp++ = byte; byte = 0; continue;
E 4
I 4
			state = RESET;
			*cp++ = byte;
			byte = 0;
			continue;
E 4
		case GOTONE | END:
		case GOTTWO | END:
D 4
			*cp++ = byte; /* FALLTHROUGH */
E 4
I 4
			*cp++ = byte;
			/* FALLTHROUGH */
E 4
		case RESET | END:
			break;
		}
		break;
	} while (cp < cplim); 
	sdl->sdl_alen = cp - LLADDR(sdl);
	new = cp - (char *)sdl;
	if (new > sizeof(*sdl))
		sdl->sdl_len = new;
	return;
}

static char hexlist[] = "0123456789abcdef";

char *
link_ntoa(sdl)
D 2
register struct sockaddr_dl *sdl;
E 2
I 2
	register const struct sockaddr_dl *sdl;
E 2
{
	static char obuf[64];
	register char *out = obuf; 
	register int i;
	register u_char *in = (u_char *)LLADDR(sdl);
D 3
	u_char *inlim = in + sdl->sdl_nlen;
E 3
I 3
	u_char *inlim = in + sdl->sdl_alen;
E 3
	int firsttime = 1;

	if (sdl->sdl_nlen) {
		bcopy(sdl->sdl_data, obuf, sdl->sdl_nlen);
		out += sdl->sdl_nlen;
D 3
		*out++ = ':';
E 3
I 3
		if (sdl->sdl_alen)
			*out++ = ':';
E 3
	}
	while (in < inlim) {
D 3
		if (firsttime) firsttime = 0; else *out++ = '.';
E 3
I 3
		if (firsttime)
			firsttime = 0;
		else
			*out++ = '.';
E 3
		i = *in++;
		if (i > 0xf) {
			out[1] = hexlist[i & 0xf];
			i >>= 4;
			out[0] = hexlist[i];
			out += 2;
		} else
			*out++ = hexlist[i];
	}
	*out = 0;
D 3
	return(obuf);
E 3
I 3
	return (obuf);
E 3
}
E 1
