h58019
s 00002/00002/00269
d D 7.7 90/12/16 16:46:18 bostic 7 6
c kernel reorg
e
s 00075/00000/00196
d D 7.6 90/06/22 15:44:05 sklower 6 5
c changes to accomodate vax specific printing of stack.
e
s 00049/00049/00147
d D 7.5 90/05/03 18:02:09 sklower 5 4
c incorporate recent torek changes (not tested)
e
s 00007/00001/00189
d D 7.4 88/05/21 18:35:26 karels 4 3
c bring up to revision 7 for tahoe release
e
s 00004/00004/00186
d D 7.3 86/12/15 20:27:48 sam 3 2
c lint
e
s 00019/00001/00171
d D 7.2 86/11/23 13:36:54 sam 2 1
c move register list
e
s 00172/00000/00000
d D 7.1 86/11/20 15:50:33 sam 1 0
c date and time created 86/11/20 15:50:33 by sam
e
u
U
t
T
I 1
D 4
/*	%M%	%I%	%E%	*/
E 4
I 4
/*
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	%W% (Berkeley) %G%
 */
E 4

D 7
#include "../kdb/defs.h"
E 7
I 7
#include "kdb/defs.h"
E 7

/*
D 2
 * Instruction printing
E 2
I 2
 * Instruction printing.
E 2
 */
I 2

D 5
REGLIST reglist[] = {
	"p2lr",	&pcb.pcb_p2lr,	"p2br",	(int *)&pcb.pcb_p2br,
	"p1lr",	&pcb.pcb_p1lr,	"p1br",	(int *)&pcb.pcb_p1br,
	"p0lr",	&pcb.pcb_p0lr,	"p0br",	(int *)&pcb.pcb_p0br,
	"ksp",	&pcb.pcb_ksp,	"hfs",	&pcb.pcb_hfs,
	"psl",	&pcb.pcb_psl,	"pc",	&pcb.pcb_pc,
	"ach",	&pcb.pcb_ach,	"acl",	&pcb.pcb_acl,
	"usp",	&pcb.pcb_usp,	"fp",	&pcb.pcb_fp,
	"r12",	&pcb.pcb_r12,	"r11",	&pcb.pcb_r11,
	"r10",	&pcb.pcb_r10,	"r9",	&pcb.pcb_r9,
	"r8",	&pcb.pcb_r8,	"r7",	&pcb.pcb_r7,
	"r6",	&pcb.pcb_r6,	"r5",	&pcb.pcb_r5,
	"r4",	&pcb.pcb_r4,	"r3",	&pcb.pcb_r3,
	"r2",	&pcb.pcb_r2,	"r1",	&pcb.pcb_r1,
	"r0",	&pcb.pcb_r0,
E 5
I 5
REGLIST kdbreglist[] = {
	"p2lr",	&kdbpcb.pcb_p2lr,	"p2br",	(int *)&kdbpcb.pcb_p2br,
	"p1lr",	&kdbpcb.pcb_p1lr,	"p1br",	(int *)&kdbpcb.pcb_p1br,
	"p0lr",	&kdbpcb.pcb_p0lr,	"p0br",	(int *)&kdbpcb.pcb_p0br,
	"ksp",	&kdbpcb.pcb_ksp,	"hfs",	&kdbpcb.pcb_hfs,
	"psl",	&kdbpcb.pcb_psl,	"pc",	&kdbpcb.pcb_pc,
	"ach",	&kdbpcb.pcb_ach,	"acl",	&kdbpcb.pcb_acl,
	"usp",	&kdbpcb.pcb_usp,	"fp",	&kdbpcb.pcb_fp,
	"r12",	&kdbpcb.pcb_r12,	"r11",	&kdbpcb.pcb_r11,
	"r10",	&kdbpcb.pcb_r10,	"r9",	&kdbpcb.pcb_r9,
	"r8",	&kdbpcb.pcb_r8,	"r7",	&kdbpcb.pcb_r7,
	"r6",	&kdbpcb.pcb_r6,	"r5",	&kdbpcb.pcb_r5,
	"r4",	&kdbpcb.pcb_r4,	"r3",	&kdbpcb.pcb_r3,
	"r2",	&kdbpcb.pcb_r2,	"r1",	&kdbpcb.pcb_r1,
	"r0",	&kdbpcb.pcb_r0,
E 5
	0
};
E 2

/*
 * Argument access types
 */
#define ACCA	(8<<3)	/* address only */
#define ACCR	(1<<3)	/* read */
#define ACCW	(2<<3)	/* write */
#define ACCM	(3<<3)	/* modify */
#define ACCB	(4<<3)	/* branch displacement */
#define ACCI	(5<<3)	/* XFC code */

/*
 * Argument data types
 */
#define TYPB	0	/* byte */
#define TYPW	1	/* word */
#define TYPL	2	/* long */
#define TYPQ	3	/* quad */
#define TYPF	4	/* float */
#define TYPD	5	/* double */

struct optab {
	char *iname;
	char val;
	char nargs;
	char argtype[6];
};

static	struct optab *ioptab[256];	/* index by opcode to optab */
static	struct optab optab[] = {	/* opcode table */
#define OP(a,b,c,d,e,f,g,h,i) {a,b,c,d,e,f,g,h,i}
D 7
#include "../tahoe/kdb_instrs"
E 7
I 7
#include "kdb_instrs"
E 7
0};
static	char *regname[] = {
	"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7",
	"r8", "r9", "r10", "r11", "r12", "fp", "sp", "pc"
};
D 3
static	POS type, space, incp;
E 3
I 3
static	int type, space, incp;
E 3

/* set up ioptab */
kdbsetup()
{
	register struct optab *p;

	for (p = optab; p->iname; p++)
		ioptab[p->val&LOBYTE] = p;
}

static long
snarf(nbytes, idsp)
{
	register long value;

D 3
	value = chkget(inkdot(incp), idsp);
E 3
I 3
D 5
	value = (u_int)chkget((off_t)inkdot(incp), idsp);
E 5
I 5
	value = (u_int)kdbchkget((off_t)kdbinkdot(incp), idsp);
E 5
E 3
	incp += nbytes;
	return(value>>(4-nbytes)*8);
}

D 3
printins(idsp,ins)
E 3
I 3
D 5
printins(idsp, ins)
E 5
I 5
kdbprintins(idsp, ins)
E 5
E 3
	register long ins;
{
	short argno;		/* argument index */
	register mode;		/* mode */
	register r;		/* register name */
D 3
	register d;		/* assembled byte, word, long or float */
E 3
I 3
	register long d;	/* assembled byte, word, long or float */
E 3
	register char *ap;
	register struct optab *ip;

	type = DSYM;
	space = idsp;
	ins = byte(ins);
	if ((ip = ioptab[ins]) == (struct optab *)0) {
D 5
		printf("?%2x%8t", ins);
		dotinc = 1;
E 5
I 5
		kdbprintf("?%2x%8t", ins);
		kdbdotinc = 1;
E 5
		return;
	}
D 5
	printf("%s%8t",ip->iname);
E 5
I 5
	kdbprintf("%s%8t",ip->iname);
E 5
	incp = 1;
	ap = ip->argtype;
	for (argno = 0; argno < ip->nargs; argno++, ap++) {
D 5
		var[argno] = 0x80000000;
		if (argno!=0) printc(',');
E 5
I 5
		kdbvar[argno] = 0x80000000;
		if (argno!=0) kdbprintc(',');
E 5
	  top:
		if (*ap&ACCB)
			mode = 0xAF + ((*ap&7)<<5);  /* branch displacement */
		else {
D 5
			mode = bchkget(inkdot(incp),idsp); ++incp;
E 5
I 5
			mode = kdbbchkget(kdbinkdot(incp),idsp); ++incp;
E 5
		}
		r = mode&0xF;
		mode >>= 4;
		switch ((int)mode) {
			case 0: case 1:
			case 2: case 3:	/* short literal */
D 5
				printc('$');
E 5
I 5
				kdbprintc('$');
E 5
				d = mode<<4|r;
				goto immed;
			case 4: /* [r] */
D 5
				printf("[%s]", regname[r]);
E 5
I 5
				kdbprintf("[%s]", regname[r]);
E 5
				goto top;
			case 5: /* r */
D 5
				printf("%s", regname[r]);
E 5
I 5
				kdbprintf("%s", regname[r]);
E 5
				break;
			case 6: /* (r) */
D 5
				printf("(%s)", regname[r]);
E 5
I 5
				kdbprintf("(%s)", regname[r]);
E 5
				break;
			case 7: /* -(r) */
D 5
				printf("-(%s)", regname[r]);
E 5
I 5
				kdbprintf("-(%s)", regname[r]);
E 5
				break;
			case 9: /* *(r)+ */
D 5
				printc('*');
E 5
I 5
				kdbprintc('*');
E 5
			case 8: /* (r)+ */
				if (r == 0xF ||
				    mode == 8 && (r == 8 || r == 9)) {
D 5
					printc('$');
E 5
I 5
					kdbprintc('$');
E 5
					d = snarf((r&03)+1, idsp);
				} else {	/*it's not PC immediate or abs*/
D 5
					printf("(%s)+", regname[r]);
E 5
I 5
					kdbprintf("(%s)+", regname[r]);
E 5
					break;
				}
			immed:
				if (ins == KCALL && d >= 0 && d < 200) {
D 5
					printf("%R", d);
E 5
I 5
					kdbprintf("%R", d);
E 5
					break;
				}
				goto disp;
			case 0xB:	/* byte displacement deferred */
			case 0xD:	/* word displacement deferred */
			case 0xF:	/* long displacement deferred */
D 5
				printc('*');
E 5
I 5
				kdbprintc('*');
E 5
			case 0xA:	/* byte displacement */
			case 0xC:	/* word displacement */
			case 0xE:	/* long displacement */
				d = snarf(1<<((mode>>1&03)-1), idsp);
				if (r==0xF) { /* PC offset addressing */
D 5
					d += dot+incp;
					psymoff(d,type,"");
					var[argno]=d;
E 5
I 5
					d += kdbdot+incp;
					kdbpsymoff(d,type,"");
					kdbvar[argno]=d;
E 5
					break;
				}
			disp:
D 5
				if (d >= 0 && d < maxoff)
					printf("%R", d);
E 5
I 5
				if (d >= 0 && d < kdbmaxoff)
					kdbprintf("%R", d);
E 5
				else
D 5
					psymoff(d,type,"");
E 5
I 5
					kdbpsymoff(d,type,"");
E 5
				if (mode >= 0xA)
D 5
					printf("(%s)", regname[r]);
				var[argno] = d;
E 5
I 5
					kdbprintf("(%s)", regname[r]);
				kdbvar[argno] = d;
E 5
				break;
		}
	}
	if (ins == CASEL) {
D 5
		if (inkdot(incp)&01)	/* align */
E 5
I 5
		if (kdbinkdot(incp)&01)	/* align */
E 5
			incp++;
D 5
		for (argno = 0; argno <= var[2]; ++argno) {
			printc(EOR);
			printf("    %R:  ", argno+var[1]);
			d = shorten(get(inkdot(incp+argno+argno), idsp));
E 5
I 5
		for (argno = 0; argno <= kdbvar[2]; ++argno) {
			kdbprintc(EOR);
			kdbprintf("    %R:  ", argno+kdbvar[1]);
			d = shorten(kdbget(kdbinkdot(incp+argno+argno), idsp));
E 5
			if (d&0x8000)
				d -= 0x10000;
D 5
			psymoff(inkdot(incp)+d, type, "");
E 5
I 5
			kdbpsymoff(kdbinkdot(incp)+d, type, "");
E 5
		}
D 5
		incp += var[2]+var[2]+2;
E 5
I 5
		incp += kdbvar[2]+kdbvar[2]+2;
E 5
	}
D 5
	dotinc = incp;
E 5
I 5
	kdbdotinc = incp;
E 5
}
I 6
ADDR	kdblastframe;
ADDR	kdbcallpc;


kdbstacktrace(dolocals)
	int dolocals;
{
	register int narg;
	register ADDR argp, frame;
	int tramp;

	if (kdbadrflg) {
		frame = kdbadrval;
		kdbcallpc = getprevpc(frame);
	} else {
		frame = kdbpcb.pcb_fp;
		kdbcallpc = kdbpcb.pcb_pc;
	}
	kdblastframe = NOFRAME;
	while (kdbcntval-- && frame != NOFRAME) {
		char *name;

		kdbchkerr();
		/* check for pc in pcb (signal trampoline code) */
		if (issignalpc(kdbcallpc)) {
			tramp = 1;
			name = "sigtramp";
		} else {
			tramp = 0;
			(void) kdbfindsym((long)kdbcallpc, ISYM);
			if (kdbcursym)
				name = kdbcursym->n_un.n_name;
			else
				name = "?";
		}
		kdbprintf("%s(", name);
		narg = getnargs(frame);
		if (narg > 10)
			narg = 10;
		argp = frame;
		if (!tramp)
			while (narg) {
				kdbprintf("%R",
				    kdbget((off_t)(argp = nextarg(argp)),
					DSP));
				if (--narg != 0)
					kdbprintc(',');
			}
		kdbprintf(") at ");
		kdbpsymoff((long)kdbcallpc, ISYM, "\n");

		if (dolocals) {
			register ADDR word;

			while (kdblocalsym((long)frame)) {
				word = kdbget((off_t)kdblocalval, DSP);
				kdbprintf("%8t%s:%10t",
				    kdbcursym->n_un.n_name);
				if (kdberrflg) {
					kdbprintf("?\n");
					kdberrflg = 0;
				} else
					kdbprintf("%R\n", word);
			}
		}
		if (!tramp) {
			kdbcallpc = getprevpc(frame);
			kdblastframe = frame;
			frame = getprevframe(frame);
		} else
			kdbcallpc = getsignalpc(kdblastframe);
		if (!kdbadrflg && !INSTACK(frame))
			break;
	}
}
E 6
E 1
