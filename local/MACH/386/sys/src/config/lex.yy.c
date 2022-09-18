# include "stdio.h"
# define U(x) x
# define NLSTATE yyprevious=YYNEWLINE
# define BEGIN yybgin = yysvec + 1 +
# define INITIAL 0
# define YYLERR yysvec
# define YYSTATE (yyestate-yysvec-1)
# define YYOPTIM 1
# define YYLMAX 200
# define output(c) putc(c,yyout)
# define input() (((yytchar=yysptr>yysbuf?U(*--yysptr):getc(yyin))==10?(yylineno++,yytchar):yytchar)==EOF?0:yytchar)
# define unput(c) {yytchar= (c);if(yytchar=='\n')yylineno--;*yysptr++=yytchar;}
# define yymore() (yymorfg=1)
# define ECHO fprintf(yyout, "%s",yytext)
# define REJECT { nstr = yyreject(); goto yyfussy;}
int yyleng; extern char yytext[];
int yymorfg;
extern char *yysptr, yysbuf[];
int yytchar;
FILE *yyin ={stdin}, *yyout ={stdout};
extern int yylineno;
struct yysvf { 
	struct yywork *yystoff;
	struct yysvf *yyother;
	int *yystops;};
struct yysvf *yyestate;
extern struct yysvf yysvec[], *yybgin;
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
 * $Log:	config.l,v $
 * Revision 2.6  89/02/25  19:21:27  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.5  89/02/07  22:56:08  mwyoung
 * Code cleanup cataclysm.
 * 
 * Revision 2.4  89/01/23  22:21:52  af
 * 	Add mips keywords. Also make makevariables an alias for
 * 	makeoptions.
 * 	[89/01/09            rvb]
 * 
 * Revision 2.3  88/11/23  16:41:24  rpd
 * 	Changed the definition of WORD, to allow numbers
 * 	if the identifier starts with a capital letter.
 * 	[88/11/04  17:58:13  rpd]
 * 
 * 08-Jan-87  Robert Beck (beck) at Sequent Computer Systems, Inc.
 *	Added "bin" keyword.
 *
 * 27-Oct-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Merged in David Black's changes for the Multimax.
 *
 * 02-Jun-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Added rules for Sun VMEbus.
 *
 */
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)config.l	5.2 (Berkeley) 4/18/86
 */

#include <ctype.h>
#include "y.tab.h"
#include "config.h"

#define tprintf if (do_trace) printf

/*
 * Key word table
 */

struct kt {
	char *kt_name;
	int kt_val;
} key_words[] = {
	{ "and",	AND },
	{ "args",	ARGS },
	{ "at",		AT },
	{ "config",	CONFIG },
	{ "controller",	CONTROLLER },
	{ "cpu",	CPU },
	{ "csr",	CSR },
	{ "device",	DEVICE },
	{ "disk",	DISK },
	{ "drive",	DRIVE },
	{ "dst",	DST },
	{ "dumps",	DUMPS },
	{ "flags",	FLAGS },
	{ "hz",		HZ },
	{ "ident",	IDENT },
	{ "machine",	MACHINE },
	{ "major",	MAJOR },
	{ "makeoptions", MAKEOPTIONS },
	{ "makevariables", MAKEOPTIONS },
	{ "master",	MASTER },
	{ "maxdsiz",	MAXDSIZ },
	{ "maxusers",	MAXUSERS },
	{ "mba",	MBA },
	{ "minor",	MINOR },
	{ "nexus",	NEXUS },
	{ "on",		ON },
	{ "options",	OPTIONS },
	{ "priority",	PRIORITY },
	{ "pseudo-device",PSEUDO_DEVICE },
	{ "root",	ROOT },
	{ "size",	SIZE },
	{ "slave",	SLAVE },
	{ "swap",	SWAP },
	{ "tape",	DEVICE },
	{ "timezone",	TIMEZONE },
	{ "trace",	TRACE },
	{ "uba",	UBA },
	{ "vector",	VECTOR },
	{ "lun",	LUN },			/* MMAX only */
	{ "slot",	SLOT },			/* MMAX only */
	{ "tape",	TAPE },			/* MMAX only */
	{ "bin",	BIN },			/* SQT ONLY */
	{ "am",		ADDRMOD },		/* MIPS */
	{ "mbii",	MBII },			/* MIPS */
 	{ "vme",	VME },			/* MIPS */
	{ 0, 0 },
};
# define YYNEWLINE 10
yylex(){
int nstr; extern int yyprevious;
while((nstr = yylook()) >= 0)
yyfussy: switch(nstr){
case 0:
if(yywrap()) return(0); break;
case 1:
	{
			int i;

			if ((i = kw_lookup(yytext)) == -1)
			{
				yylval.str = yytext;
				tprintf("id(%s) ", yytext);
				return ID;
			}
			tprintf("(%s) ", yytext);
			return i;
		}
break;
case 2:
{
			yytext[strlen(yytext)-1] = '\0';
			yylval.str = yytext + 1;
			return ID;
		}
break;
case 3:
	{
			yylval.val = octal(yytext);
			tprintf("#O:%o ", yylval.val);
			return NUMBER;
		}
break;
case 4:
{
			yylval.val = hex(yytext);
			tprintf("#X:%x ", yylval.val);
			return NUMBER;
		}
break;
case 5:
{
			yylval.val = atoi(yytext);
			tprintf("#D:%d ", yylval.val);
			return NUMBER;
		}
break;
case 6:
{
			double atof();
			yylval.val = (int) (60 * atof(yytext) + 0.5);
			return FPNUMBER;
		}
break;
case 7:
	{
			return MINUS;
		}
break;
case 8:
	{
			yylval.val = -1;
			tprintf("? ");
			return NUMBER;
		}
break;
case 9:
{
			yyline++;
			tprintf("\n... ");
		}
break;
case 10:
	{
			yyline++;
			tprintf("\n");
			return SEMICOLON;
		}
break;
case 11:
	{	/* Ignored (comment) */;	}
break;
case 12:
	{	/* Ignored (white space) */;	}
break;
case 13:
	{	return SEMICOLON;		}
break;
case 14:
	{	return COMMA;			}
break;
case 15:
	{	return EQUALS;			}
break;
case 16:
	{	return AT;			}
break;
case 17:
	{	return yytext[0];		}
break;
case 18:
          {       return VME16D16;                }
break;
case 19:
          {       return VME24D16;                }
break;
case 20:
          {       return VME32D32;                }
break;
case 21:
       {       return VME16D16;                }
break;
case 22:
       {       return VME24D16;                }
break;
case 23:
       {       return VME32D16;                }
break;
case 24:
       {       return VME16D32;                }
break;
case 25:
       {       return VME24D32;                }
break;
case 26:
       {       return VME32D32;                }
break;
case -1:
break;
default:
fprintf(yyout,"bad switch yylook %d",nstr);
} return(0); }
/* end of yylex */
/*
 * kw_lookup
 *	Look up a string in the keyword table.  Returns a -1 if the
 *	string is not a keyword otherwise it returns the keyword number
 */

kw_lookup(word)
register char *word;
{
	register struct kt *kp;

	for (kp = key_words; kp->kt_name != 0; kp++)
		if (eq(word, kp->kt_name))
			return kp->kt_val;
	return -1;
}

/*
 * Number conversion routines
 */

octal(str)
char *str;
{
	int num;

	(void) sscanf(str, "%o", &num);
	return num;
}

hex(str)
char *str;
{
	int num;

	(void) sscanf(str+2, "%x", &num);
	return num;
}
int yyvstop[] ={
0,

12,
0,

12,
0,

17,
0,

12,
17,
0,

10,
-9,
0,

17,
0,

11,
17,
0,

14,
17,
0,

7,
17,
0,

3,
17,
0,

5,
17,
0,

13,
17,
0,

15,
17,
0,

8,
17,
0,

16,
17,
0,

1,
17,
0,

1,
17,
0,

1,
17,
0,

12,
0,

9,
0,

11,
0,

6,
0,

3,
0,

5,
0,

1,
0,

1,
0,

1,
0,

1,
0,

2,
0,

4,
0,

1,
0,

18,
0,

19,
0,

20,
0,

21,
0,

24,
0,

22,
0,

25,
0,

23,
0,

26,
0,
0};
# define YYTYPE char
struct yywork { YYTYPE verify, advance; } yycrank[] ={
0,0,	0,0,	1,3,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	1,4,	1,5,	
22,0,	0,0,	4,19,	5,20,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	1,6,	
1,7,	4,19,	5,20,	21,31,	
0,0,	0,0,	0,0,	0,0,	
6,21,	1,8,	1,9,	2,7,	
0,0,	1,10,	1,11,	36,39,	
6,21,	6,21,	35,38,	34,37,	
2,8,	1,11,	43,49,	40,43,	
1,12,	40,44,	1,13,	44,50,	
1,14,	1,15,	1,16,	33,34,	
33,35,	33,36,	45,51,	2,12,	
1,16,	2,13,	46,52,	2,14,	
2,15,	6,0,	7,22,	41,45,	
42,47,	41,46,	42,48,	47,53,	
48,54,	0,0,	7,22,	7,0,	
6,21,	0,0,	0,0,	6,21,	
6,21,	0,0,	0,0,	0,0,	
1,17,	0,0,	1,17,	6,21,	
24,24,	24,24,	24,24,	24,24,	
24,24,	24,24,	24,24,	24,24,	
6,21,	30,33,	18,30,	7,22,	
37,40,	38,41,	6,21,	39,42,	
0,0,	0,0,	0,0,	1,18,	
0,0,	0,0,	7,22,	0,0,	
0,0,	7,22,	7,22,	0,0,	
0,0,	0,0,	2,18,	0,0,	
0,0,	7,22,	0,0,	0,0,	
0,0,	0,0,	6,21,	0,0,	
6,21,	0,0,	7,22,	0,0,	
0,0,	0,0,	0,0,	10,23,	
7,22,	10,24,	10,24,	10,24,	
10,24,	10,24,	10,24,	10,24,	
10,24,	11,23,	0,0,	11,26,	
11,26,	11,26,	11,26,	11,26,	
11,26,	11,26,	11,26,	11,26,	
11,26,	0,0,	0,0,	0,0,	
7,22,	16,27,	7,22,	0,0,	
16,28,	16,28,	16,28,	16,28,	
16,28,	16,28,	16,28,	16,28,	
16,28,	16,28,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	16,27,	16,27,	16,27,	
16,27,	16,27,	16,27,	16,27,	
16,27,	16,27,	16,27,	16,27,	
16,27,	16,27,	16,27,	16,27,	
16,27,	16,27,	16,27,	16,27,	
16,27,	16,27,	16,27,	16,27,	
16,27,	16,27,	16,27,	0,0,	
0,0,	10,25,	0,0,	16,27,	
0,0,	16,27,	16,27,	16,27,	
16,27,	16,27,	16,27,	16,27,	
16,27,	16,27,	16,27,	16,27,	
16,27,	16,27,	16,27,	16,27,	
16,27,	16,27,	16,27,	16,27,	
16,27,	16,27,	16,27,	16,27,	
16,27,	16,27,	16,27,	17,29,	
23,23,	23,23,	23,23,	23,23,	
23,23,	23,23,	23,23,	23,23,	
23,23,	23,23,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	17,29,	
17,29,	17,29,	17,29,	17,29,	
17,29,	17,29,	17,29,	17,29,	
17,29,	17,29,	17,29,	17,29,	
17,29,	17,29,	17,29,	17,29,	
17,29,	17,29,	17,29,	17,29,	
17,29,	17,29,	17,29,	17,29,	
17,29,	0,0,	0,0,	0,0,	
0,0,	17,29,	0,0,	17,29,	
17,29,	17,29,	17,29,	17,29,	
17,29,	17,29,	17,29,	17,29,	
17,29,	17,29,	17,29,	17,29,	
17,29,	17,29,	17,29,	17,29,	
17,29,	17,29,	17,29,	17,29,	
17,29,	17,29,	17,29,	17,29,	
17,29,	25,32,	25,32,	25,32,	
25,32,	25,32,	25,32,	25,32,	
25,32,	25,32,	25,32,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	25,32,	25,32,	
25,32,	25,32,	25,32,	25,32,	
26,26,	26,26,	26,26,	26,26,	
26,26,	26,26,	26,26,	26,26,	
26,26,	26,26,	0,0,	0,0,	
28,28,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	25,32,	25,32,	
25,32,	25,32,	25,32,	25,32,	
28,28,	28,28,	28,28,	28,28,	
28,28,	28,28,	28,28,	28,28,	
28,28,	28,28,	28,28,	28,28,	
28,28,	28,28,	28,28,	28,28,	
28,28,	28,28,	28,28,	28,28,	
28,28,	28,28,	28,28,	28,28,	
28,28,	28,28,	0,0,	0,0,	
0,0,	0,0,	28,28,	0,0,	
28,28,	28,28,	28,28,	28,28,	
28,28,	28,28,	28,28,	28,28,	
28,28,	28,28,	28,28,	28,28,	
28,28,	28,28,	28,28,	28,28,	
28,28,	28,28,	28,28,	28,28,	
28,28,	28,28,	28,28,	28,28,	
28,28,	28,28,	0,0,	0,0,	
0,0};
struct yysvf yysvec[] ={
0,	0,	0,
yycrank+-1,	0,		yyvstop+1,
yycrank+-12,	yysvec+1,	yyvstop+3,
yycrank+0,	0,		yyvstop+5,
yycrank+5,	0,		yyvstop+7,
yycrank+6,	0,		yyvstop+10,
yycrank+-43,	0,		yyvstop+13,
yycrank+-77,	0,		yyvstop+15,
yycrank+0,	0,		yyvstop+18,
yycrank+0,	0,		yyvstop+21,
yycrank+101,	0,		yyvstop+24,
yycrank+111,	0,		yyvstop+27,
yycrank+0,	0,		yyvstop+30,
yycrank+0,	0,		yyvstop+33,
yycrank+0,	0,		yyvstop+36,
yycrank+0,	0,		yyvstop+39,
yycrank+128,	0,		yyvstop+42,
yycrank+206,	0,		yyvstop+45,
yycrank+1,	yysvec+17,	yyvstop+48,
yycrank+0,	yysvec+4,	yyvstop+51,
yycrank+0,	0,		yyvstop+53,
yycrank+-5,	yysvec+6,	0,	
yycrank+-2,	yysvec+7,	yyvstop+55,
yycrank+204,	0,		yyvstop+57,
yycrank+52,	0,		yyvstop+59,
yycrank+281,	0,		0,	
yycrank+304,	0,		yyvstop+61,
yycrank+0,	yysvec+16,	yyvstop+63,
yycrank+319,	yysvec+16,	yyvstop+65,
yycrank+0,	yysvec+17,	yyvstop+67,
yycrank+8,	yysvec+17,	yyvstop+69,
yycrank+0,	0,		yyvstop+71,
yycrank+0,	yysvec+25,	yyvstop+73,
yycrank+18,	yysvec+17,	yyvstop+75,
yycrank+1,	0,		0,	
yycrank+2,	0,		0,	
yycrank+1,	0,		0,	
yycrank+12,	0,		yyvstop+77,
yycrank+13,	0,		yyvstop+79,
yycrank+15,	0,		yyvstop+81,
yycrank+10,	0,		0,	
yycrank+30,	0,		0,	
yycrank+31,	0,		0,	
yycrank+4,	0,		0,	
yycrank+13,	0,		0,	
yycrank+16,	0,		0,	
yycrank+24,	0,		0,	
yycrank+29,	0,		0,	
yycrank+34,	0,		0,	
yycrank+0,	0,		yyvstop+83,
yycrank+0,	0,		yyvstop+85,
yycrank+0,	0,		yyvstop+87,
yycrank+0,	0,		yyvstop+89,
yycrank+0,	0,		yyvstop+91,
yycrank+0,	0,		yyvstop+93,
0,	0,	0};
struct yywork *yytop = yycrank+441;
struct yysvf *yybgin = yysvec+1;
char yymatch[] ={
00  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,011 ,012 ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
011 ,01  ,'"' ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,'-' ,01  ,01  ,
'0' ,'1' ,'1' ,'1' ,'1' ,'1' ,'1' ,'1' ,
'8' ,'8' ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'G' ,
'G' ,'G' ,'G' ,'G' ,'G' ,'G' ,'G' ,'G' ,
'G' ,'G' ,'G' ,'G' ,'G' ,'G' ,'G' ,'G' ,
'G' ,'G' ,'G' ,01  ,01  ,01  ,01  ,'_' ,
01  ,'a' ,'a' ,'a' ,'a' ,'a' ,'a' ,'_' ,
'_' ,'_' ,'_' ,'_' ,'_' ,'_' ,'_' ,'_' ,
'_' ,'_' ,'_' ,'_' ,'_' ,'_' ,'_' ,'_' ,
'_' ,'_' ,'_' ,01  ,01  ,01  ,01  ,01  ,
0};
char yyextra[] ={
0,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0};
/*	ncform	4.1	83/08/11	*/

int yylineno =1;
# define YYU(x) x
# define NLSTATE yyprevious=YYNEWLINE
char yytext[YYLMAX];
struct yysvf *yylstate [YYLMAX], **yylsp, **yyolsp;
char yysbuf[YYLMAX];
char *yysptr = yysbuf;
int *yyfnd;
extern struct yysvf *yyestate;
int yyprevious = YYNEWLINE;
yylook(){
	register struct yysvf *yystate, **lsp;
	register struct yywork *yyt;
	struct yysvf *yyz;
	int yych;
	struct yywork *yyr;
# ifdef LEXDEBUG
	int debug;
# endif
	char *yylastch;
	/* start off machines */
# ifdef LEXDEBUG
	debug = 0;
# endif
	if (!yymorfg)
		yylastch = yytext;
	else {
		yymorfg=0;
		yylastch = yytext+yyleng;
		}
	for(;;){
		lsp = yylstate;
		yyestate = yystate = yybgin;
		if (yyprevious==YYNEWLINE) yystate++;
		for (;;){
# ifdef LEXDEBUG
			if(debug)fprintf(yyout,"state %d\n",yystate-yysvec-1);
# endif
			yyt = yystate->yystoff;
			if(yyt == yycrank){		/* may not be any transitions */
				yyz = yystate->yyother;
				if(yyz == 0)break;
				if(yyz->yystoff == yycrank)break;
				}
			*yylastch++ = yych = input();
		tryagain:
# ifdef LEXDEBUG
			if(debug){
				fprintf(yyout,"char ");
				allprint(yych);
				putchar('\n');
				}
# endif
			yyr = yyt;
			if ( (int)yyt > (int)yycrank){
				yyt = yyr + yych;
				if (yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transitions */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					goto contin;
					}
				}
# ifdef YYOPTIM
			else if((int)yyt < (int)yycrank) {		/* r < yycrank */
				yyt = yyr = yycrank+(yycrank-yyt);
# ifdef LEXDEBUG
				if(debug)fprintf(yyout,"compressed state\n");
# endif
				yyt = yyt + yych;
				if(yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transitions */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					goto contin;
					}
				yyt = yyr + YYU(yymatch[yych]);
# ifdef LEXDEBUG
				if(debug){
					fprintf(yyout,"try fall back character ");
					allprint(YYU(yymatch[yych]));
					putchar('\n');
					}
# endif
				if(yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transition */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					goto contin;
					}
				}
			if ((yystate = yystate->yyother) && (yyt= yystate->yystoff) != yycrank){
# ifdef LEXDEBUG
				if(debug)fprintf(yyout,"fall back to state %d\n",yystate-yysvec-1);
# endif
				goto tryagain;
				}
# endif
			else
				{unput(*--yylastch);break;}
		contin:
# ifdef LEXDEBUG
			if(debug){
				fprintf(yyout,"state %d char ",yystate-yysvec-1);
				allprint(yych);
				putchar('\n');
				}
# endif
			;
			}
# ifdef LEXDEBUG
		if(debug){
			fprintf(yyout,"stopped at %d with ",*(lsp-1)-yysvec-1);
			allprint(yych);
			putchar('\n');
			}
# endif
		while (lsp-- > yylstate){
			*yylastch-- = 0;
			if (*lsp != 0 && (yyfnd= (*lsp)->yystops) && *yyfnd > 0){
				yyolsp = lsp;
				if(yyextra[*yyfnd]){		/* must backup */
					while(yyback((*lsp)->yystops,-*yyfnd) != 1 && lsp > yylstate){
						lsp--;
						unput(*yylastch--);
						}
					}
				yyprevious = YYU(*yylastch);
				yylsp = lsp;
				yyleng = yylastch-yytext+1;
				yytext[yyleng] = 0;
# ifdef LEXDEBUG
				if(debug){
					fprintf(yyout,"\nmatch ");
					sprint(yytext);
					fprintf(yyout," action %d\n",*yyfnd);
					}
# endif
				return(*yyfnd++);
				}
			unput(*yylastch);
			}
		if (yytext[0] == 0  /* && feof(yyin) */)
			{
			yysptr=yysbuf;
			return(0);
			}
		yyprevious = yytext[0] = input();
		if (yyprevious>0)
			output(yyprevious);
		yylastch=yytext;
# ifdef LEXDEBUG
		if(debug)putchar('\n');
# endif
		}
	}
yyback(p, m)
	int *p;
{
if (p==0) return(0);
while (*p)
	{
	if (*p++ == m)
		return(1);
	}
return(0);
}
	/* the following are only used in the lex library */
yyinput(){
	return(input());
	}
yyoutput(c)
  int c; {
	output(c);
	}
yyunput(c)
   int c; {
	unput(c);
	}
