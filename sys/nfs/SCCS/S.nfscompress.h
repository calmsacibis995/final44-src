h20042
s 00001/00001/00051
d D 7.2 90/10/02 10:46:16 mckusick 2 1
c fixes for compressed NFS (from Macklem)
e
s 00052/00000/00000
d D 7.1 90/10/01 14:08:49 mckusick 1 0
c from Rick Macklem
e
u
U
t
T
I 1
/*
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Rick Macklem at The University of Guelph.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Definitions for the compression algorithm
 */
#define NFSC_MAX	17
#define	NFSCRL		0xe0
#define	NFSCRLE(a)	(NFSCRL | ((a) - 2))

#define	nfscput(c) \
		if (oleft == 0) { \
D 2
			MGET(om, MT_DATA, M_WAIT); \
E 2
I 2
			MGET(om, M_WAIT, MT_DATA); \
E 2
			if (clget) \
				MCLGET(om, M_WAIT); \
			om->m_len = 0; \
			oleft = M_TRAILINGSPACE(om) - 1; \
			*mp = om; \
			mp = &om->m_next; \
			op = mtod(om, u_char *); \
		} else \
			oleft--; \
		*op++ = (c); \
		om->m_len++; \
		olen++

#define nfscget(c) \
		if (ileft == 0) { \
			do { \
				m = m->m_next; \
			} while (m && m->m_len == 0); \
			if (m) { \
				ileft = m->m_len - 1; \
				ip = mtod(m, u_char *); \
				(c) = *ip++; \
			} else { \
				(c) = '\0'; \
				noteof = 0; \
			} \
		} else { \
			(c) = *ip++; \
			ileft--; \
		}
E 1
