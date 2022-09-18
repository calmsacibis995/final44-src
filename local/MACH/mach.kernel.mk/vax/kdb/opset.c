/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	opset.c,v $
 * Revision 2.6  89/03/09  22:17:36  rpd
 * 	More cleanup.
 * 
 * Revision 2.5  89/02/27  21:44:43  mrt
 * 	Make sccsid a comment.
 * 	[89/02/27            rvb]
 * 
 * Revision 2.4  89/02/25  20:22:57  gm0w
 * 	Changes for cleanup.
 * 
 *  3-Mar-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Include CS_LINT to turn on lint fixes.
 *
 * 21-Nov-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	NOFLOAT is standard.
 *
 *  3-Oct-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	De-linted.
 *
 * 19-Feb-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	MACH_NOFLOAT: Remove printing of floating numbers, as it
 *	causes floating code to be generated.
 *
 *  1-Jan-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Revamped for building as part of KERNEL compilation.
 *
 */

/*
 *	UNIX debugger
 *	Instruction printing routines.
 *	MACHINE DEPENDENT
 */

/* static	char sccsid[] = "@(#)opset.c 4.4 5/12/83"; */

#include <vax/kdb/defs.h>

long		dot;
INT		dotinc;
long		insoutvar[36];
long		var[36];

#include <vax/kdb/instrs.h>

string_t	regname[];
string_t	fltimm[];
unsigned	type, space, incp;
/*
 *	Definitions for registers and for operand classes
 */
char	*insregname();	/* how to print a register */

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
#include <vax/kdb/asnumber.h>
typedef	struct	as_number	*numberp;
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
extern	int	ty_NORELOC[];
extern	int	ty_float[];
extern	int	ty_nbyte[];
extern	int	ty_nlg[];
extern	char	*ty_string[];

short ioptab[3][256];	/* two level 1-based index by opcode into insttab */

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

mkioptab()
{
	register	struct insttab *p;
	int	mapchar;

	for(p = insttab; p->iname; p++){
		mapchar = mapescbyte(p->eopcode);
		if (ioptab[mapchar][p->popcode])
			continue;
		ioptab[mapchar][p->popcode] = (p - insttab) + 1;
	}
}

u_char snarfuchar();
/*
 *	Global variables for communicating with the minions and printins
 */
static	int	idsp;
static	short	argno;		/* which argument one is working on */
static	char	insoutfmt[2];	/* how to format the relocated symbols */

static savevar(val)
long	val;
{
	var[argno] = val;
	insoutvar[argno] = val;
}

printins(fmt, Idsp, ins)
char	fmt;
u_char	ins;
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

#ifdef	lint
	fmt++;
#endif	lint
	idsp = Idsp;
	type = DSYM;
	space = idsp;

	insoutfmt[0] = 0;
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
	ip = &insttab[ioptab[mapchar][ins] - 1];
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

	dotinc = incp;
}

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
		printf("    %R:  ", i + base);
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
u_char snarfuchar()
{
	u_char	back;
	/*
		 *	assert: bchkget and inkdot don't have side effects
		 */
	back = (u_char)bchkget(inkdot(incp), idsp);
	incp += 1;
	return(back);
}
/*
 *	normal operand; return non zero pointer to register
 *	name if this is an index instruction.
 */
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
	psymoff(valuep->num_ulong[0], type, &insoutfmt[0]);
	if (regnumber != R_PC){	
			printf("(%s)", insregname(regnumber));
		}
		savevar((long)valuep->num_ulong[0]);
	}
	/*
	 *	get a register name
	 */
	char *insregname(regnumber)
		int	regnumber;
	{
		char	*r;
		r = regname[regnumber];
		return(r);
	}
	/*
	 *	print out a short literal
	 */
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
			printf("$%s", fltimm[mode]);
			break;
		default:
			printf("$%r", mode);
			break;
		}
	}

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
		nbytes = ty_nbyte[A_TYPEXT(optype)];
		if (! ty_NORELOC[A_TYPEXT(optype)]){
			dispaddress(snarfreloc(nbytes), mode);
			return;
		}
		bignumprint(nbytes, optype);
	}

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
	case TYPD:
		printf("no floating numbers in this kernel");
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
