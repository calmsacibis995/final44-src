h38862
s 00000/00000/00136
d D 2.1 84/02/08 20:40:41 aoki 4 3
c synchronize to version 2
e
s 00000/00000/00136
d D 1.3 83/09/19 07:08:36 thien 3 2
c changing to unlinted source
e
s 00000/00008/00136
d D 1.2 83/02/01 20:30:02 peter 2 1
c things more from here to pc.h;  to make this file machine dependent.
e
s 00144/00000/00000
d D 1.1 80/08/27 19:54:25 peter 1 0
c date and time created 80/08/27 19:54:25 by peter
e
u
U
t
T
I 1
/* Copyright (c) 1979 Regents of the University of California */

/* static	char sccsid[] = "%Z%%M% %I% %G%"; */

    /*
     *	tree node operators
     */
#define	P2UNDEFINED	1
#define	P2NAME		2
#define	P2STRING	3
#define	P2ICON		4
#define	P2FCON		5
#define	P2PLUS		6
#define	P2MINUS		8		/* also unary == P2NEG */
#define	P2MUL		11		/* also unary == P2INDIRECT */
#define	P2AND		14		/* also unary */
#define	P2OR		17
#define	P2ER		19
#define	P2QUEST		21
#define	P2COLON		22
#define	P2ANDAND	23
#define	P2OROR		24
    /*
     *	yacc operator classes, reserved words, little symbols, etc.
     *	operators 25 .. 57 not used, except 56
     */
#define P2LISTOP	56
#define	P2ASSIGN	58
#define	P2COMOP		59
#define	P2DIV		60
#define	P2MOD		62
#define	P2LS		64
#define	P2RS		66
#define	P2DOT		68
#define	P2STREF		69
#define	P2CALL		70		/* also unary */
#define	P2FORTCALL	73		/* also unary */
#define	P2NOT		76
#define	P2COMPL		77
#define	P2INCR		78
#define	P2DECR		79
#define	P2EQ		80
#define	P2NE		81
#define	P2LE		82
#define	P2LT		83
#define	P2GE		84
#define	P2GT		85
#define	P2ULE		86
#define	P2ULT		87
#define	P2UGE		88
#define	P2UGT		89
#define	P2SETBIT	90
#define	P2TESTBIT	91
#define	P2RESETBIT	92
#define	P2ARS		93
#define	P2REG		94
#define	P2OREG		95
#define	P2CCODES	96
#define	P2FREE		97
#define	P2STASG		98
#define	P2STARG		99
#define	P2STCALL	100		/* also unary */

    /*
     *	some conversion operators
     */
#define	P2FLD		103
#define	P2SCONV		104
#define	P2PCONV		105
#define	P2PMCONV	106
#define	P2PVCONV	107

    /*
     *	special node operators, used for special contexts
     */
#define	P2FORCE		108
#define	P2CBRANCH	109
#define	P2INIT		110
#define	P2CAST		111

    /*
     *	prefix unary operator modifier
     */
#define	P2ASG		1+
#define	P2UNARY		2+

    /*
     *	these borrowed from /usr/src/cmd/mip/fort.c
     *	to use the binary interface.
     *	only FTEXT, FEXPR, FLBRAC, FRBRAC, and FEOF are used
     */
#define	P2FTEXT		200
#define	P2FEXPR		201
#define	P2FLBRAC	203
#define	P2FRBRAC	204
#define	P2FEOF		205

    /*
     *	type names
     */
#define	P2UNDEF		0
#define	P2FARG		1
#define	P2CHAR		2
#define	P2SHORT		3
#define	P2INT		4	/* this is also used for booleans */
#define	P2LONG		5	/* don't use these, the second pass chokes */
#define	P2FLOAT		6
#define	P2DOUBLE	7
#define	P2STRTY		8
#define	P2UNIONTY	9
#define	P2ENUMTY	10
#define	P2MOETY		11
#define	P2UCHAR		12
#define	P2USHORT	13
#define	P2UNSIGNED	14
#define	P2ULONG		15

    /*
     *	type modifiers
     */
#define	P2PTR		020
#define	P2FTN		040
#define	P2ARY		060

    /*
     *	see the comment for p2type for an explanation of c type words
     */
#define	P2BASETYPE	017
#define	P2TYPESHIFT	2

    /*
     *	add a most significant type modifier, m, to a type, t
     */
#define ADDTYPE( t,m )	( ( ( ( t ) & ~P2BASETYPE ) << P2TYPESHIFT )	\
		  | ( m )						\
		  | ( ( t ) & P2BASETYPE ) )
D 2

    /*
     *	the runtime framepointer and argumentpointer registers
     */
#define	P2FP		13
#define	P2FPNAME	"fp"
#define	P2AP		12
#define P2APNAME	"ap"
E 2
E 1
