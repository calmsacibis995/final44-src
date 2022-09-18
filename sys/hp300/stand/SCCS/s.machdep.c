h33524
s 00002/00002/00124
d D 8.1 93/06/10 21:47:25 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00008/00116
d D 7.7 93/04/27 13:35:52 hibler 7 6
c take structure defn out of param list
e
s 00001/00001/00123
d D 7.6 92/10/11 10:01:45 bostic 6 5
c make kernel includes standard
e
s 00025/00013/00099
d D 7.5 92/06/18 21:33:29 hibler 5 4
c merge with latest Utah version
e
s 00000/00005/00112
d D 7.4 91/05/05 13:55:29 bostic 4 3
c use common nodev() routne -- note, it returns -1
e
s 00003/00003/00114
d D 7.3 91/05/05 13:48:58 bostic 3 2
c I deleted the romprintf() routine, and userom variable -- it's not set by
c any of the current HP code, and has to be done differently anyway to use
c the common printf routines
e
s 00001/00001/00116
d D 7.2 90/12/16 16:39:35 bostic 2 1
c kernel reorg
e
s 00117/00000/00000
d D 7.1 90/05/08 22:46:09 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 8
 * Copyright (c) 1982, 1986, 1990 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1982, 1986, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 5
 * from: Utah $Hdr: machdep.c 1.6 88/05/24$
E 5
I 5
 * from: Utah $Hdr: machdep.c 1.10 92/06/18
E 5
 *
 *	%W% (Berkeley) %G%
 */

D 2
#include "param.h"
E 2
I 2
D 6
#include "sys/param.h"
E 6
I 6
#include <sys/param.h>
E 6
E 2

/*
 * Copy bytes within kernel
 */
bcopy(from, to, count)
	register caddr_t from, to;
	register unsigned count;
{
	while (count--)
		*to++ = *from++;
}

bzero(to, count)
	register caddr_t to;
	register unsigned count;
{
	while (count--)
		*to++ = 0;
}

bcmp(s1, s2, len)
	register char *s1, *s2;
	register int len;
{
	while (len--)
		if (*s1++ != *s2++)
			return (1);
	return (0);
}

I 5
#ifdef ROMPRF
int userom;
#endif

I 7
struct trapframe {
	int dregs[8];
	int aregs[8];
	int whoknows;
	short sr;
	int pc;
	short frame;
};

E 7
E 5
trap(fp)
D 5
 struct frame {
	 int dregs[8];
	 int aregs[8];
	 int whoknows;
	 short sr;
	 int pc;
	 short frame;
 } *fp;
E 5
I 5
D 7
	struct frame {
		int dregs[8];
		int aregs[8];
		int whoknows;
		short sr;
		int pc;
		short frame;
	} *fp;
E 7
I 7
	struct trapframe *fp;
E 7
E 5
{
	static int intrap = 0;

	if (intrap)
D 5
		return;
E 5
I 5
		return(0);
E 5
	intrap = 1;
D 3
	romprintf("Got unexpected trap, vector = %x, ps = %x, pc = %x\n",
E 3
I 3
D 5
	printf("Got unexpected trap, vector = %x, ps = %x, pc = %x\n",
E 3
	       fp->frame&0xFFF, fp->sr, fp->pc);
E 5
I 5
#ifdef ROMPRF
	userom = 1;
#endif
	printf("Got unexpected trap: format=%x vector=%x ps=%x pc=%x\n",
		  (fp->frame>>12)&0xF, fp->frame&0xFFF, fp->sr, fp->pc);
E 5
D 3
	romprintf("dregs: %x %x %x %x %x %x %x %x\n",
E 3
I 3
	printf("dregs: %x %x %x %x %x %x %x %x\n",
E 3
	       fp->dregs[0], fp->dregs[1], fp->dregs[2], fp->dregs[3], 
	       fp->dregs[4], fp->dregs[5], fp->dregs[6], fp->dregs[7]);
D 3
	romprintf("aregs: %x %x %x %x %x %x %x %x\n",
E 3
I 3
	printf("aregs: %x %x %x %x %x %x %x %x\n",
E 3
	       fp->aregs[0], fp->aregs[1], fp->aregs[2], fp->aregs[3], 
	       fp->aregs[4], fp->aregs[5], fp->aregs[6], fp->aregs[7]);
I 5
#ifdef ROMPRF
	userom = 0;
#endif
E 5
	intrap = 0;
I 5
	return(0);
E 5
}

D 4
nodev()
{
	return(0);
}

E 4
#ifdef ROMPRF
#define ROWS	46
#define COLS	128

romputchar(c)
D 5
 register int c;
E 5
I 5
	register int c;
E 5
{
	static char buf[COLS];
	static int col = 0, row = 0;
	register int i;

	switch (c) {
	case '\0':
		break;
	case '\r':
I 5
		break;	/* ignore */
E 5
	case '\n':
		for (i = col; i < COLS-1; i++)
			buf[i] = ' ';
		buf[i] = '\0';
		romout(row, buf);
		col = 0;
		if (++row == ROWS)
			row = 0;
		break;

	case '\t':
		do {
			romputchar(' ');
		} while (col & 7);
		break;

	default:
		buf[col] = c;
		if (++col == COLS-1)
			romputchar('\n');
		break;
	}
}
#endif
E 1
