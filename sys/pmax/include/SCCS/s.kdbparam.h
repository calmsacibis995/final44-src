h06479
s 00002/00002/00044
d D 8.1 93/06/10 23:02:06 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00045
d D 7.2 92/03/22 20:46:38 ralph 2 1
c fix register listing break point.
e
s 00043/00000/00000
d D 7.1 92/03/19 20:18:47 bostic 1 0
c date and time created 92/03/19 20:18:47 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Ralph Campbell.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Machine dependent definitions for kdb.
 */

#if BYTE_ORDER == LITTLE_ENDIAN
#define kdbshorten(w)	((w) & 0xFFFF)
#define	kdbbyte(w)	((w) & 0xFF)
#define	kdbitol(a,b)	((long)(((b) << 16) | ((a) & 0xFFFF)))
#define	kdbbtol(a)	((long)(a))
#endif

#define LPRMODE		"%R"
#define OFFMODE		"+%R"

#define	SETBP(ins)	MACH_BREAK_BRKPT

/* return the program counter value modified if we are in a delay slot */
#define	kdbgetpc(pcb)		(kdbvar[kdbvarchk('t')] < 0 ? \
	(pcb).pcb_regs[34] + 4 : (pcb).pcb_regs[34])
D 2
#define	kdbishiddenreg(p)	((p) >= &kdbreglist[29])
E 2
I 2
#define	kdbishiddenreg(p)	((p) >= &kdbreglist[33])
E 2
#define	kdbisbreak(type)	(((type) & MACH_CR_EXC_CODE) == 0x24)

/* check for address wrap around */
#define	kdbaddrwrap(addr,newaddr)	(((addr)^(newaddr)) >> 31)

/* declare machine dependent routines defined in kadb.c */
void	kdbprinttrap __P((unsigned, unsigned));
void	kdbsetsstep __P((void));
void	kdbclrsstep __P((void));
void	kdbreadc __P((char *));
void	kdbwrite __P((char *, int));
void	kdbprintins __P((int, long));
void	kdbstacktrace __P((int));
char	*kdbmalloc __P((int));
E 1
