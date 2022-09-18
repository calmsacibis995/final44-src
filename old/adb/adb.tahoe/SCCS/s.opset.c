h62433
s 00008/00001/00177
d D 5.1 91/04/04 17:52:23 bostic 5 4
c new copyright; att/bsd/shared
e
s 00006/00002/00172
d D 1.4 90/04/27 09:03:04 torek 4 3
c that was not quite right either: take dot as instr for SP_NONE,
c otherwise take instruction from given space
e
s 00001/00001/00173
d D 1.3 90/04/27 08:55:58 torek 3 2
c read opcodes from specified space, not always from i-space
e
s 00149/00128/00025
d D 1.2 89/01/16 20:26:46 bostic 2 1
c new version from Chris Torek
e
s 00153/00000/00000
d D 1.1 86/02/25 16:04:46 sam 1 0
c date and time created 86/02/25 16:04:46 by sam
e
u
U
t
T
I 5
/*-
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.proprietary.c%
 */

E 5
I 1
#ifndef lint
D 2
static	char sccsid[] = "%W% (Berkeley) %G%";
E 2
I 2
static char sccsid[] = "%W% (Berkeley) %G%";
E 2
D 5
#endif
E 5
I 5
#endif /* not lint */
E 5
I 2

E 2
/*
D 2
 *
 *	UNIX debugger
 *
E 2
I 2
 * adb - instruction decoding
E 2
 */

#include "defs.h"
#include "optab.h"

D 2
STRING		errflg;
L_INT		dot;
INT		dotinc;
L_INT		var[];
E 2
I 2
struct	optab *ioptab[256];	/* index by opcode to optab */
E 2

I 2
/* set up ioptab */
mkioptab()
{
	register struct optab *p;
E 2

D 2
/* instruction printing */

POS	type, space, incp;

OPTAB ioptab[256]; /* index by opcode to optab */

mkioptab() {/* set up ioptab */
	REG OPTAB p=optab;
	while (p->iname){
		ioptab[p->val&LOBYTE]=p;
		p++;
	}
E 2
I 2
	for (p = optab; p->iname; p++)
		ioptab[p->val] = p;
E 2
}

D 2
printins(idsp,ins)
	REG L_INT	ins;
E 2
I 2
/*
 * Print one instruction, and leave dotinc set to the number of bytes
 * it occupied.
 */
printins(space)
	int space;
E 2
{
D 2
	short	argno;		/* argument index */
	REG	mode;		/* mode */
	REG	r;		/* register name */
	REG	d;		/* assembled byte, word, long or float */
	long	snarf();
	REG char *	ap;
	REG OPTAB	ip;
E 2
I 2
	u_char ins;		/* instruction opcode */
	int argno;		/* argument index */
	register int mode;	/* mode */
	register int r;		/* register name */
	register int d;		/* assembled byte, word, long or float */
	register int dotoff;	/* offset from dot of current byte */
	register u_char *ap;
	register struct optab *ip;
	union {
		u_char	ub;
		char	b;
		short	w;
		int	l;
	} mem;
	extern char *syscalls[];
	extern int nsys;
#define	snarfbytes(nbytes) \
	(void) adbread(space, inkdot(dotoff), &mem.b, nbytes); \
	checkerr(); \
	dotoff += (nbytes)
E 2

D 2
	type = DSYM;
	space = idsp;
	ins = byte(ins);
	if((ip=ioptab[ins]) == (OPTAB)0) {
		printf("?%2x%8t", ins);
E 2
I 2
D 3
	(void) adbread(SP_INSTR, dot, &ins, 1);
E 3
I 3
D 4
	(void) adbread(space, dot, &ins, 1);
E 3
	checkerr();
E 4
I 4
	if (space == SP_NONE)
		ins = (u_char)dot;
	else {
		(void) adbread(space, dot, &ins, 1);
		checkerr();
	}
E 4
	if ((ip = ioptab[ins]) == NULL) {
		adbprintf("?%2x", ins);
E 2
		dotinc = 1;
		return;
	}
D 2
	printf("%s%8t",ip->iname);
	incp = 1;
E 2
I 2
	adbprintf("%s%8t", ip->iname);
	dotoff = 1;
E 2
	ap = ip->argtype;
D 2
	for (argno=0; argno<ip->nargs; argno++,ap++) {
E 2
I 2
	for (argno = 0; argno < ip->nargs; argno++, ap++) {
E 2
		var[argno] = 0x80000000;
D 2
		if (argno!=0) printc(',');
	  top:
		if (*ap&ACCB)
			mode = 0xAF + ((*ap&7)<<5);  /* branch displacement */
		else{
			mode = bchkget(inkdot(incp),idsp); ++incp;
E 2
I 2
		if (argno != 0)
			printc(',');
again:
		if (*ap & ACCB)		/* branch displacement */
			mode = 0xAF + ((*ap & 7) << 5);
		else {
			snarfbytes(1);
			mode = mem.ub;
E 2
		}
D 2
		r = mode&0xF;
E 2
I 2
		r = mode & 0xF;
E 2
		mode >>= 4;
D 2
		switch ((int)mode) {
			case 0:
			case 1:
			case 2:
			case 3:
				/* short literal */
				printc('$');
				d = mode<<4|r;
				goto immed;
			case 4: /* [r] */
				printf("[%s]",regname[r]);
				goto top;
			case 5: /* r */
				printf("%s",regname[r]);
				break;
			case 6: /* (r) */
				printf("(%s)",regname[r]);
				break;
			case 7: /* -(r) */
				printf("-(%s)",regname[r]);
				break;
			case 9: /* *(r)+ */
				printc('*');
			case 8: /* (r)+ */
				if(r==0xF || mode==8 && (r==8 || r==9)) {
					printc('$');
					d = snarf((r&03)+1, idsp);
				} else {	/*it's not PC immediate or abs*/
					printf("(%s)+",regname[r]);
					break;
				}
			immed:
				if(ins == KCALL && d>=0 && d<SYSSIZ) {
					if(systab[d])
						printf(systab[d]);
					else
						printf("%R", d);
					break;
				}
				goto disp;
			case 0xB:	/* byte displacement deferred */
			case 0xD:	/* word displacement deferred */
			case 0xF:	/* long displacement deferred */
				printc('*');
			case 0xA:	/* byte displacement */
			case 0xC:	/* word displacement */
			case 0xE:	/* long displacement */
				d = snarf(1<<((mode>>1&03)-1), idsp);
				if (r==0xF) { /* PC offset addressing */
					d += dot+incp;
					psymoff(d,type,"");
					var[argno]=d;
					break;
				}
			disp:
				if(d>=0 && d<maxoff)
					printf("%R", d);
				else
					psymoff(d,type,"");
				if (mode>=0xA)
					printf("(%s)",regname[r]);
				var[argno]=d;
				break;
		} /* end of the mode switch */
	}
	if (ins==CASEL) {
		if(inkdot(incp)&01)	/* align */
			incp++;
		for (argno=0; argno<=var[2]; ++argno) {
			printc(EOR);
			printf("    %R:  ",argno+var[1]);
			d=shorten(get(inkdot(incp+argno+argno),idsp));
			if (d&0x8000) d -= 0x10000;
			psymoff(inkdot(incp)+d,type,"");
E 2
I 2
		switch (mode) {

		case 0: case 1: case 2: case 3:
			/* short literal */
			d = mode << 4 | r;
			goto immed;

		case 4:	/* [r] */
			adbprintf("[%s]", regname[r]);
			goto again;

		case 5:	/* r */
			adbprintf("%s", regname[r]);
			continue;

		case 6:	/* (r) */
			adbprintf("(%s)", regname[r]);
			continue;

		case 7:	/* -(r) */
			adbprintf("-(%s)", regname[r]);
			continue;

		case 9:	/* *(r)+ */
			printc('*');
			/* FALLTHROUGH */

		case 8:	/* (r)+ */
			if (r == 0xf) {
				/* PC immediate */
				snarfbytes(4);
				d = mem.l;
			} else if (mode == 8 && (r == 8 || r == 9)) {
				/* absolute */
				snarfbytes((r & 1) + 1);
				d = r == 8 ? mem.b : mem.w;
			} else {
				adbprintf("(%s)+", regname[r]);
				continue;
			}
	immed:
			printc('$');
			if (ins == KCALL && (u_int)d < nsys && syscalls[d])
				prints(syscalls[d]);
			else
				adbprintf("%R", d);
			var[argno] = d;
			continue;

		case 0xA:	/* byte displacement */
		case 0xB:	/* byte displacement deferred */
			d = 1;
			break;

		case 0xC:	/* word displacement */
		case 0xD:	/* word displacement deferred */
			d = 2;
			break;

		case 0xE:	/* long displacement */
		case 0xF:	/* long displacement deferred */
			d = 4;
			break;
E 2
		}
D 2
		incp += var[2]+var[2]+2;
E 2
I 2

		/* displacement or displacement deferred */
		if (mode & 1)
			printc('*');
		snarfbytes(d);
		switch (d) {
		case 1:
			d = mem.b;
			break;
		case 2:
			d = mem.w;
			break;
		case 4:
			d = mem.l;
			break;
		}
		if (r == 0xF) {	/* PC offset addressing */
			d += dot + dotoff;
			psymoff("%R", (addr_t)d, SP_DATA, maxoff, "");
		} else
			adbprintf("%V(%s)", d, regname[r]);
		var[argno] = d;
E 2
	}
D 2
	dotinc=incp;
}
E 2
I 2
	if (ins == CASEL) {
		register addr_t adjdot;
E 2

D 2
long snarf (nbytes, idsp)
{
	register long value;

	value = chkget(inkdot(incp), idsp);
	incp += nbytes;
	return(value>>(4-nbytes)*8);
E 2
I 2
		if (inkdot(dotoff) & 01)	/* align */
			dotoff++;
		adjdot = inkdot(dotoff);
		for (argno = 0; argno <= var[2]; ++argno) {
			adbprintf("\n    %R:  ", argno + var[1]);
			snarfbytes(2);
			psymoff("%R", adjdot + mem.w, SP_DATA, maxoff, "");
		}
	}
	dotinc = dotoff;
E 2
}
E 1
