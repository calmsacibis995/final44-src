/*  
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * Copyright (c) 1986 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	dis_opset.c,v $
 * Revision 2.3  89/03/09  22:14:18  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  20:17:53  gm0w
 * 	Changes for cleanup.
 * 
 * 15-May-87  Robert Baron (rvb) at Carnegie-Mellon University
 *	This has been revamped do produce a standalone disassembler
 *	module for the vax.  It has very few external variables and they
 *	all begin with "dis_".  Everything that could became a static
 *	var/or function.
 *
 *  1-Jan-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Revamped for building as part of KERNEL compilation.
 *
 */
#ifndef	lint
static	char sccsid[] = "@(#)opset.c 4.4 5/12/83";
#endif	lint
/*
 *	UNIX debugger
 *	Instruction printing routines.
 *	MACHINE DEPENDENT
 */

#ifdef	ADB
#include <defs.h>
#endif	ADB
#ifdef	SDB
#include <head.h>
#endif	SDB
#ifdef	KERNEL
#define DIS 1
#endif	KERNEL
#ifdef	DIS
typedef char *string_t;
typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned int u_int;
#define DISSTATIC static
#define printc(x) printf("%c", x)
typedef	struct	as_number	*numberp;
DISSTATIC
char	*insregname();	/* how to print a register */
DISSTATIC
int mapescbyte();
DISSTATIC
printins();
DISSTATIC
casebody();
DISSTATIC
numberp snarfreloc();
DISSTATIC
numberp snarf();
DISSTATIC
u_char snarfuchar();
DISSTATIC
char *operandout();
DISSTATIC
dispaddress();
DISSTATIC
char *insregname();
DISSTATIC
shortliteral();
DISSTATIC
pcimmediate();
DISSTATIC
bignumprint();

#define DSYM 0
#define EOR '\n'
#endif	DIS

DISSTATIC
long		dot;
DISSTATIC
long		dotinc;
DISSTATIC
long		insoutvar[36];
#ifdef	ADB
long		var[36];
#endif	ADB

#undef	INSTTAB
#include <instrs.h>

string_t	dis_regname[];
string_t	dis_fltimm[];
DISSTATIC
unsigned	type, space, incp;
/*
 *	Definitions for registers and for operand classes
 */

#define R_PC		0xF

#define OC_IMM0		0x0
#define OC_IMM1		0x1
#define OC_IMM2		0x2
#define OC_IMM3		0x3
#define OC_INDEX	0x4
#define OC_REG		0x5
#define OC_DREG		0x6
#define OC_ADREG	0x7
#define OC_AIREG	0x8
#define OC_DAIREG	0x9

#define OC_BDISP	0xA
#define OC_DBDISP	0xB
#define OC_WDISP	0xC
#define OC_DWDISP	0xD
#define OC_LDISP	0xE
#define OC_DLDISP	0xF

#define OC_SHIFT	4
#define OC_CONS(oc,reg)	(((oc & 0xF) << OC_SHIFT) | (reg & 0xF))
#define OC_AMEXT(x)	(((x) >> OC_SHIFT) & 0xF)
#define OC_REGEXT(x)	((x) & 0xF)

/*
 *	Definitions for large numbers
 */
#include <asnumber.h>
numberp snarf();
numberp snarfreloc();
/*
 *	Definitions for special instructions
 */
#define CASEB	0x8F
#define CASEW	0xAF
#define CASEL	0xCF
/*
 *	Definitions for converting TYP's into numbers, booleans, etc.
 *	These are shared with the assembler.
 */
extern	int	dis_ty_NORELOC[];
extern	int	dis_ty_nbyte[];
/* 
 * not used
	extern	int	ty_float[];
	extern	int	ty_nlg[];
	extern	char	*ty_string[];
 */
DISSTATIC
short ioptab[3][256];	/* two level 1-based index by opcode into insttab */

	/* interface to the outside world */
#ifdef	DIS
static char (*snarf_fn)();
static char *(*number_string_fn)();

dis7xx_init(snarf, addr_str)
char (*snarf)();
char *(*addr_str)();
{
	snarf_fn = snarf;
	number_string_fn = addr_str;
	mkioptab();
	
}

dis7xx(pt, len)
int *len;
{
u_char ins; 

	incp = 0;
	dot = pt;
	ins = snarfuchar();

	printins(0,  /* space */0, ins);

	*len = dotinc;
}
#endif	DIS

DISSTATIC
int mapescbyte(byte)
u_char	byte;
{
	switch(byte){
	default:
		return(0);
	case ESCD:
		return(1);
	case ESCF:
		return(2);
	}
}

DISSTATIC
mkioptab()
{
	register	struct insttab *p;
	int	mapchar;
#ifdef	DIS
	for(p = dis_insttab; p->iname; p++) {
		mapchar = mapescbyte(p->eopcode);
		if (ioptab[mapchar][p->popcode])
			continue;
		ioptab[mapchar][p->popcode] = (p - dis_insttab) + 1;
	}
#else	DIS
	for(p = insttab; p->iname; p++) {
		mapchar = mapescbyte(p->eopcode);
		if (ioptab[mapchar][p->popcode])
			continue;
		ioptab[mapchar][p->popcode] = (p - insttab) + 1;
	}
#endif	DIS
}

u_char snarfuchar();
/*
 *	Global variables for communicating with the minions and printins
 */
static	int	idsp;
static	short	argno;		/* which argument one is working on */
static	char	insoutfmt[2];	/* how to format the relocated symbols */
#ifdef	SDB
static	struct	proct	*procp;
#endif	SDB

static savevar(val)
long	val;
{
#ifdef	ADB
	var[argno] = val;
#endif	ADB
	insoutvar[argno] = val;
}

DISSTATIC
printins(fmt, Idsp, ins)
char	fmt;
#ifndef	vax
u_char	ins;
#else
u_char	ins;
#endif
int	Idsp;
{
	u_char	mode;		/* mode */
	u_char	ins2;
	char	*indexreg;	/* print of which register indexes */
	char	*indexed;	/* we indexed */
	char	*operandout();
	register	u_char 	*ap;
	register	struct insttab *ip;
	u_char	optype;
	int	mapchar;

	idsp = Idsp;
	type = DSYM;
	space = idsp;
#ifdef	SDB
	procp = adrtoprocp(dot);
	if (procp->paddr == dot){
		printf("0x%04.4x", ins);
		incp = 2;
		goto ret;
	}
#endif	SDB

#ifdef	ADB
	insoutfmt[0] = 0;
#endif	ADB
#ifdef	SDB
	insoutfmt[0] = fmt;
#endif	SDB

	incp = 1;
	if ((mapchar = mapescbyte(ins)) != 0){
		ins2 = snarfuchar();
		if (ioptab[mapchar][ins2] == 0){
			/*
						 *	Oops; not a defined instruction;
						 *	back over this escape byte.
						 */
			incp -= 1;
			mapchar = 0;
		} else {
			ins = ins2;
		}
	}
	if (ioptab[mapchar][ins] == 0){
		printf("<undefined operator byte>: %x", ins);
		goto ret;
	}
#ifdef	DIS
	ip = &dis_insttab[ioptab[mapchar][ins] - 1];
#else	DIS
	ip = &insttab[ioptab[mapchar][ins] - 1];
#endif	DIS
	printf("%s\t", ip->iname);

	for (ap = ip->argtype, argno = 0; argno < ip->nargs; argno++, ap++) {
		savevar(0x80000000);	/* an illegal symbol */
		optype = *ap;
		if (argno != 0)
			printc(',');
		indexreg = 0;
		indexed = 0;
		do{
			if (A_ACCEXT(optype) & ACCB){
				switch(A_TYPEXT(optype)){
				case TYPB:
					mode = OC_CONS(OC_BDISP, R_PC);
					break;
				case TYPW:
					mode = OC_CONS(OC_WDISP, R_PC);
					break;
				}
			} else {
				mode = snarfuchar();
			}
			indexreg = operandout(mode, optype);
			if (indexed)
				printf("[%s]", indexed);
			indexed = indexreg;
		}
		while(indexed);
	}
	if (mapchar == 0){
		switch(ins){
		case CASEB:
		case CASEW:
		case CASEL:
			casebody(insoutvar[1], insoutvar[2]);
			break;
		default:
			break;
		}
	}
ret:
	;

#ifdef	SDB
	oincr = incp;
#endif	SDB
#ifdef	ADB
	dotinc = incp;
#endif	ADB
#ifdef	DIS
	dotinc = incp;
#endif	DIS
}


DISSTATIC
casebody(base, limit)
long	base;
long	limit;
{
	int	i;
	unsigned	baseincp;
	unsigned	advincp;
	struct	as_number	*valuep;
#define OSIZE (sizeof(short))
	argno = 0;
	baseincp = incp;
	for (i = 0; i <= limit; i++) {
		printc(EOR);
#ifdef	SDB
		printf("    %d:  ", i + base);
#endif	SDB
#ifdef	ADB
		printf("    %R:  ", i + base);
#endif	ADB
#ifdef	DIS
		printf("    %d:  ", i + base);
#endif	DIS
		valuep = snarfreloc(OSIZE, 0);
		advincp = incp;
		incp = baseincp;
		dispaddress(valuep, OC_CONS(OC_WDISP, R_PC));
		incp = advincp;
	}
}

/*
 *	magic values to mung an offset to a register into
 *	something that psymoff can understand.. all magic
 */
/* 0	1	2	3	4 */
static long magic_masks[5] =	{
	0,	0x80,	0x8000,	0,	0};
static long magic_compl[5] =	{
	0,	0x100,	0x10000,0,	0};
/*
 *	Snarf up some bytes, and put in the magic relocation flags
 */
DISSTATIC
numberp snarfreloc(nbytes)
int	nbytes;
{
	numberp	back;
	back = snarf(nbytes);
	if (back->num_ulong[0] & magic_masks[nbytes])
		back->num_ulong[0] -= magic_compl[nbytes];
	return(back);
}
/*
 *	The following code is NOT portable from the PDP 11 to the VAX
 *	because of the byte ordering problem.
 */
DISSTATIC
numberp snarf(nbytes)
int	nbytes;
{
	register	int	i;

	static	struct	as_number	backnumber;
	static	struct	as_number	znumber;	/* init'ed to 0 */

	backnumber = znumber;
	for (i = 0; i < nbytes; i++)
		backnumber.num_uchar[i] = snarfuchar();
	return(&backnumber);
}
/*
 *	Read one single character, and advance the dot
 */
DISSTATIC
u_char snarfuchar()
{
	u_char	back;
		/*
		 *	assert: bchkget and inkdot don't have side effects
		 */
#ifdef	DIS
	back = (*snarf_fn)((unsigned char *) (inkdot(incp)));
#else	DIS
	back = (u_char)bchkget(inkdot(incp), idsp);
#endif	DIS
	incp += 1;
	return(back);
}
/*
 *	normal operand; return non zero pointer to register
 *	name if this is an index instruction.
 */
DISSTATIC
char *operandout(mode, optype)
u_char	mode;
u_char	optype;
{
	char	*r;
	int	regnumber;
	int	nbytes;

	regnumber = OC_REGEXT(mode);
	r = insregname(regnumber);
	switch (OC_AMEXT(mode)){
	case OC_IMM0:
	case OC_IMM1:
	case OC_IMM2:
	case OC_IMM3:
		shortliteral(mode, optype);
		return(0);
	case OC_INDEX:
		return(r);		/* will be printed later */
	case OC_REG:
		printf("%s", r);
		return(0);
	case OC_DREG:
		printf("(%s)", r);
		return(0);
	case OC_ADREG:
		printf("-(%s)", r);
		return(0);
	case OC_DAIREG:
		printc('*');
	case OC_AIREG:
		if (regnumber == R_PC){
			pcimmediate(mode, optype);
		} else {
			printf("(%s)+", r);
		}
		return(0);
	case OC_DBDISP:
		printc('*');
	case OC_BDISP:
		nbytes = 1;
		break;
	case OC_DWDISP:
		printc('*');
	case OC_WDISP:
		nbytes = 2;
		break;
	case OC_DLDISP:
		printc('*');
	case OC_LDISP:
		nbytes = 4;
		break;
	}
	dispaddress(snarfreloc(nbytes), mode);
	return(0);
}

DISSTATIC
dispaddress(valuep, mode)
numberp	valuep;
u_char	mode;
{
	int	regnumber = OC_REGEXT(mode);

	switch(OC_AMEXT(mode)){
	case OC_BDISP:
	case OC_DBDISP:
	case OC_WDISP:
	case OC_DWDISP:
	case OC_LDISP:
	case OC_DLDISP:
		if (regnumber == R_PC){
			/* PC offset addressing */
			valuep->num_ulong[0] += inkdot(incp);
		}
	}
#ifdef	ADB
	psymoff(valuep->num_ulong[0], type, &insoutfmt[0]);
	if (regnumber != R_PC){
		printf("(%s)", insregname(regnumber));
	}
#endif	ADB
#ifdef	SDB
	if(psymoff(valuep->num_ulong[0], regnumber, &insoutfmt[0])
		    && (regnumber != R_PC)){
		printf("(%s)", insregname(regnumber));
	}
#endif	SDB
#ifdef	DIS
	if (regnumber != R_PC){int num = (int)valuep->num_ulong[0];
		if (num < 0) {
			printc('-');
			num = - num;
		}
		printf("%s", (*number_string_fn)(num));
		printf("(%s)", insregname(regnumber));
	} else {
		printf("%s", (*number_string_fn)((int)valuep->num_ulong[0]));
	}
#endif	DIS
	savevar((long)valuep->num_ulong[0]);
}
/*
	 *	get a register name
	 */
DISSTATIC
char *insregname(regnumber)
int	regnumber;
{
	char	*r;
	r = dis_regname[regnumber];
#ifdef	SDB
	if (   (insoutfmt[0] == 'i')
	    && (regnumber >= 6)
	    && (regnumber <= 11)
	    && (adrtoregvar(regnumber, procp) != -1)) {
		r = sl_name;
	}
#endif	SDB
	return(r);
}
	/*
	 *	print out a short literal
	 */
DISSTATIC
shortliteral(mode, optype)
u_char	mode;
u_char	optype;
{
	savevar((long)mode);
	switch(A_TYPEXT(optype)){
	case TYPF:
	case TYPD:
	case TYPG:
	case TYPH:
		printf("$%s", dis_fltimm[mode]);
		break;
	default:
#ifdef	ADB
		printf("$%r", mode);
#endif	ADB
#ifdef	SDB
		printf("$%d", mode);
#endif	SDB
#ifdef	DIS
		printf("$%d", mode);
#endif	DIS
		break;
	}
}

DISSTATIC
pcimmediate(mode, optype)
u_char	mode;
u_char	optype;
{
	int	nbytes;

	printc('$');
	if (mode == OC_CONS(OC_DAIREG, R_PC)){	/* PC absolute, always 4 bytes*/
		dispaddress(snarfreloc(4), mode);
		return;
	}
	nbytes = dis_ty_nbyte[A_TYPEXT(optype)];
	if (! dis_ty_NORELOC[A_TYPEXT(optype)]){
		dispaddress(snarfreloc(nbytes), mode);
		return;
	}
	bignumprint(nbytes, optype);
}

DISSTATIC
bignumprint(nbytes, optype)
int	nbytes;
u_char	optype;
{
	numberp	valuep;
	int	leading_zero = 1;
	register	int	bindex;
	register	int	nindex;
	register	int	ch;

	valuep = snarf(nbytes);
	switch(A_TYPEXT(optype)){
	case TYPF:
		printf("0f%f", valuep->num_num.numFf_float.Ff_value);
		break;
	case TYPD:
		printf("0d%f", valuep->num_num.numFd_float.Fd_value);
		break;
	case TYPG:
		printf("0g::");
		goto qprint;
	case TYPH:
		printf("0h::");
		goto qprint;
	case TYPQ:
	case TYPO:
qprint:
		for (bindex = nbytes - 1; bindex >= 0; --bindex){
			for (nindex = 4; nindex >= 0; nindex -= 4){
				ch = (valuep->num_uchar[bindex] >> nindex);
				ch &= 0x0F;
				if ( ! (leading_zero &= (ch == 0) ) ){
					if (ch <= 0x09)
						printc(ch + '0');
					else
						printc(ch - 0x0A + 'a');
				}
			}
		}
		break;
	}
}

#ifdef	ADB
#else	ADB

DISSTATIC
long inkdot(incr)
int	incr;
{
	long		newdot;

	newdot = dot + incr;
	return(newdot);
}

#ifdef	SDB
printc(c)
char c;
{
	printf("%c", c);
}

psymoff(v, regnumber, fmt)
long	v;
char	*fmt;
{
	struct	proct	*procp;
	register	int diff;
	if (fmt[0] == 'i') {
		switch(regnumber){
		case 12:	/* parameter */
			if ((diff = adrtoparam((long) v, adrtoprocp(dot)))
			    != -1) {
				printf("%s", sl_name);
				prdiff(diff);
				return(0);
			}
			break;
		case 13:	/* local */
			if ((diff = adrtolocal((long) -v, adrtoprocp(dot))
			    ) != -1) {
				printf("%s", sl_name);
				prdiff(diff);
				return(0);
			}
			break;
		default:
			break;
		}
		if (v < firstdata) {
			if ((procp = adrtoprocp((long) v)) != badproc) {
				prlnoff(procp, v);
				return(0);
			}
		} else {
			if ((diff = adrtoext((long) v)) != -1) {
				printf("%s", sl_name);
				prdiff(diff);
				return(0);
			}
		}
	}
	prhex(v);
	return(1);
}

prdiff(diff)
{
	if (diff) {
		printf("+");
		prhex(diff);
	}
}

#endif	SDB
#endif	ADB
