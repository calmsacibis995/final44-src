h60959
s 00009/00096/00115
d D 8.3 94/12/05 21:56:01 mckusick 3 2
c update from mycroft
e
s 00001/00000/00210
d D 8.2 94/08/20 16:07:23 mckusick 2 1
c off-by-one error when translating names for associated files (from mycroft)
e
s 00210/00000/00000
d D 8.1 94/01/21 18:28:59 mckusick 1 0
c from Mike Hibler
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1994
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley
 * by Pace Willisson (pace@blitz.com).  The Rock Ridge Extension
 * Support code is derived from software contributed to Berkeley
 * by Atsushi Murai (amurai@spec.co.jp).
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/namei.h>
#include <sys/resourcevar.h>
#include <sys/kernel.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/buf.h>
#include <sys/proc.h>
#include <sys/conf.h>
#include <sys/mount.h>
#include <sys/vnode.h>
#include <miscfs/specfs/specdev.h> /* XXX */
#include <miscfs/fifofs/fifo.h> /* XXX */
#include <sys/malloc.h>
#include <sys/dir.h>

#include <isofs/cd9660/iso.h>

D 3
#ifdef	__notanymore__
int
isonum_711 (p)
unsigned char *p;
{
	return (*p);
}

int
isonum_712 (p)
signed char *p;
{
	return (*p);
}

int
isonum_721 (p)
unsigned char *p;
{
	/* little endian short */
#if BYTE_ORDER != LITTLE_ENDIAN
	printf ("isonum_721 called on non little-endian machine!\n");
#endif

	return *(short *)p;
}

int
isonum_722 (p)
unsigned char *p;
{
        /* big endian short */
#if BYTE_ORDER != BIG_ENDIAN
        printf ("isonum_722 called on non big-endian machine!\n");
#endif

	return *(short *)p;
}

int
isonum_723 (p)
unsigned char *p;
{
#if BYTE_ORDER == BIG_ENDIAN
        return isonum_722 (p + 2);
#elif BYTE_ORDER == LITTLE_ENDIAN
	return isonum_721 (p);
#else
	printf ("isonum_723 unsupported byte order!\n");
	return 0;
#endif
}

int
isonum_731 (p)
unsigned char *p;
{
        /* little endian long */
#if BYTE_ORDER != LITTLE_ENDIAN
        printf ("isonum_731 called on non little-endian machine!\n");
#endif

	return *(long *)p;
}

int
isonum_732 (p)
unsigned char *p;
{
        /* big endian long */
#if BYTE_ORDER != BIG_ENDIAN
        printf ("isonum_732 called on non big-endian machine!\n");
#endif

	return *(long *)p;
}

int
isonum_733 (p)
unsigned char *p;
{
#if BYTE_ORDER == BIG_ENDIAN
        return isonum_732 (p + 4);
#elif BYTE_ORDER == LITTLE_ENDIAN
	return isonum_731 (p);
#else
	printf ("isonum_733 unsupported byte order!\n");
	return 0;
#endif
}
#endif	/* __notanymore__ */

E 3
/*
 * translate and compare a filename
 * Note: Version number plus ';' may be omitted.
 */
int
D 3
isofncmp(unsigned char *fn,int fnlen,unsigned char *isofn,int isolen)
E 3
I 3
isofncmp(fn, fnlen, isofn, isolen)
	u_char *fn, *isofn;
	int fnlen, isolen;
E 3
{
	int i, j;
	char c;
	
	while (--fnlen >= 0) {
		if (--isolen < 0)
			return *fn;
		if ((c = *isofn++) == ';') {
			switch (*fn++) {
			default:
				return *--fn;
			case 0:
				return 0;
			case ';':
				break;
			}
			for (i = 0; --fnlen >= 0; i = i * 10 + *fn++ - '0') {
				if (*fn < '0' || *fn > '9') {
					return -1;
				}
			}
			for (j = 0; --isolen >= 0; j = j * 10 + *isofn++ - '0');
			return i - j;
		}
		if (c != *fn) {
			if (c >= 'A' && c <= 'Z') {
				if (c + ('a' - 'A') != *fn) {
					if (*fn >= 'a' && *fn <= 'z')
						return *fn - ('a' - 'A') - c;
					else
						return *fn - c;
				}
			} else
				return *fn - c;
		}
		fn++;
	}
	if (isolen > 0) {
		switch (*isofn) {
		default:
			return -1;
		case '.':
			if (isofn[1] != ';')
				return -1;
		case ';':
			return 0;
		}
	}
	return 0;
}

/*
 * translate a filename
 */
void
D 3
isofntrans(unsigned char *infn,int infnlen,
	   unsigned char *outfn,unsigned short *outfnlen,
	   int original,int assoc)
E 3
I 3
isofntrans(infn, infnlen, outfn, outfnlen, original, assoc)
	u_char *infn, *outfn;
	int infnlen;
	u_short *outfnlen;
	int original;
	int assoc;
E 3
{
	int fnidx = 0;
	
	if (assoc) {
		*outfn++ = ASSOCCHAR;
		fnidx++;
I 2
		infnlen++;
E 2
	}
	for (; fnidx < infnlen; fnidx++) {
		char c = *infn++;
		
		if (!original && c >= 'A' && c <= 'Z')
			*outfn++ = c + ('a' - 'A');
		else if (!original && c == '.' && *infn == ';')
			break;
		else if (!original && c == ';')
			break;
		else
			*outfn++ = c;
	}
	*outfnlen = fnidx;
}
E 1
