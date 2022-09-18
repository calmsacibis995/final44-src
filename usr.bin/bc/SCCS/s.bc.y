h63396
s 00005/00005/00628
d D 8.1 93/06/06 14:24:29 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00017/00001/00616
d D 5.1 91/04/17 17:00:41 bostic 8 7
c new copyright; att/bsd/shared
e
s 00002/00001/00615
d D 4.7 89/09/15 21:05:32 bostic 7 6
c POSIX signals
e
s 00003/00003/00613
d D 4.6 89/05/10 22:45:54 bostic 6 5
c file reorg, pathnames.h, paths.h
e
s 00001/00001/00615
d D 4.5 88/04/24 17:15:11 bostic 5 4
c fixes for ANSI C
e
s 00017/00011/00599
d D 4.4 87/12/12 15:30:49 bostic 4 3
c add varargs; fix exit statuses; bug report 4.3BSD/usr.bin/119
e
s 00003/00001/00607
d D 4.3 85/11/28 20:34:49 sam 3 2
c fix per dave@cit-vax for failed open of files spec'd on command line
e
s 00013/00003/00595
d D 4.2 81/02/28 20:11:21 wnj 2 1
c op= now accepted
e
s 00598/00000/00000
d D 4.1 80/10/01 17:29:49 bill 1 0
c date and time created 80/10/01 17:29:49 by bill
e
u
U
t
T
I 1
%{
D 2
static char *sccsid = "%W% (Berkeley) %G%";
E 2
I 2
D 8
static	char *sccsid = "%W% (Berkeley) %E%";
E 8
I 8
/*-
D 9
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
 * %sccs.include.proprietary.c%
 */

#ifndef lint
D 9
char copyright[] =
"%Z% Copyright (c) 1991 The Regents of the University of California.\n\
 All rights reserved.\n";
E 9
I 9
static char copyright[] =
"%Z% Copyright (c) 1991, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 9
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 8
E 2
	int *getout();
%}
%right '='
%left '+' '-'
%left '*' '/' '%'
%right '^'
%left UMINUS

%term LETTER DIGIT SQRT LENGTH _IF  FFF EQ
%term _WHILE _FOR NE LE GE INCR DECR
%term _RETURN _BREAK _DEFINE BASE OBASE SCALE
%term EQPL EQMI EQMUL EQDIV EQREM EQEXP
%term _AUTO DOT
%term QSTR

%{
I 7
#include <sys/signal.h>
E 7
#include <stdio.h>
I 4
#include <varargs.h>
I 6
#include "pathnames.h"
E 6
E 4
D 5
int in;
E 5
I 5
FILE *in;
E 5
char cary[1000], *cp = { cary };
char string[1000], *str = {string};
int crs = '0';
int rcrs = '0';  /* reset crs */
int bindx = 0;
int lev = 0;
int ln;
char *ss;
int bstack[10] = { 0 };
char *numb[15] = {
  " 0", " 1", " 2", " 3", " 4", " 5",
  " 6", " 7", " 8", " 9", " 10", " 11",
  " 12", " 13", " 14" };
int *pre, *post;
%}
%%
start	: 
	|  start stat tail
		= output( $2 );
	|  start def dargs ')' '{' dlist slist '}'
		={	bundle( 6,pre, $7, post ,"0",numb[lev],"Q");
			conout( $$, $2 );
			rcrs = crs;
			output( "" );
			lev = bindx = 0;
			}
	;

dlist	:  tail
	| dlist _AUTO dlets tail
	;

stat	:  e 
		={ bundle(2, $1, "ps." ); }
	| 
		={ bundle(1, "" ); }
	|  QSTR
		={ bundle(3,"[",$1,"]P");}
	|  LETTER '=' e
		={ bundle(3, $3, "s", $1 ); }
	|  LETTER '[' e ']' '=' e
		={ bundle(4, $6, $3, ":", geta($1)); }
	|  LETTER EQOP e
		={ bundle(6, "l", $1, $3, $2, "s", $1 ); }
	|  LETTER '[' e ']' EQOP e
		={ bundle(8,$3, ";", geta($1), $6, $5, $3, ":", geta($1));}
	|  _BREAK
		={ bundle(2, numb[lev-bstack[bindx-1]], "Q" ); }
	|  _RETURN '(' e ')'
		= bundle(4, $3, post, numb[lev], "Q" );
	|  _RETURN '(' ')'
		= bundle(4, "0", post, numb[lev], "Q" );
	| _RETURN
		= bundle(4,"0",post,numb[lev],"Q");
	| SCALE '=' e
		= bundle(2, $3, "k");
	| SCALE EQOP e
		= bundle(4,"K",$3,$2,"k");
	| BASE '=' e
		= bundle(2,$3, "i");
	| BASE EQOP e
		= bundle(4,"I",$3,$2,"i");
	| OBASE '=' e
		= bundle(2,$3,"o");
	| OBASE EQOP e
		= bundle(4,"O",$3,$2,"o");
	|  '{' slist '}'
		={ $$ = $2; }
	|  FFF
		={ bundle(1,"fY"); }
	|  error
		={ bundle(1,"c"); }
	|  _IF CRS BLEV '(' re ')' stat
		={	conout( $7, $2 );
			bundle(3, $5, $2, " " );
			}
	|  _WHILE CRS '(' re ')' stat BLEV
		={	bundle(3, $6, $4, $2 );
			conout( $$, $2 );
			bundle(3, $4, $2, " " );
			}
	|  fprefix CRS re ';' e ')' stat BLEV
		={	bundle(5, $7, $5, "s.", $3, $2 );
			conout( $$, $2 );
			bundle(5, $1, "s.", $3, $2, " " );
			}
	|  '~' LETTER '=' e
		={	bundle(3,$4,"S",$2); }
	;

EQOP	:  EQPL
		={ $$ = "+"; }
	|  EQMI
		={ $$ = "-"; }
	|  EQMUL
		={ $$ = "*"; }
	|  EQDIV
		={ $$ = "/"; }
	|  EQREM
		={ $$ = "%%"; }
	|  EQEXP
		={ $$ = "^"; }
	;

fprefix	:  _FOR '(' e ';'
		={ $$ = $3; }
	;

BLEV	:
		={ --bindx; }
	;

slist	:  stat
	|  slist tail stat
		={ bundle(2, $1, $3 ); }
	;

tail	:  '\n'
		={ln++;}
	|  ';'
	;

re	:  e EQ e
		= bundle(3, $1, $3, "=" );
	|  e '<' e
		= bundle(3, $1, $3, ">" );
	|  e '>' e
		= bundle(3, $1, $3, "<" );
	|  e NE e
		= bundle(3, $1, $3, "!=" );
	|  e GE e
		= bundle(3, $1, $3, "!>" );
	|  e LE e
		= bundle(3, $1, $3, "!<" );
	|  e
		= bundle(2, $1, " 0!=" );
	;

e	:  e '+' e
		= bundle(3, $1, $3, "+" );
	|  e '-' e
		= bundle(3, $1, $3, "-" );
	| '-' e		%prec UMINUS
		= bundle(3, " 0", $2, "-" );
	|  e '*' e
		= bundle(3, $1, $3, "*" );
	|  e '/' e
		= bundle(3, $1, $3, "/" );
	|  e '%' e
		= bundle(3, $1, $3, "%%" );
	|  e '^' e
		= bundle(3, $1, $3, "^" );
	|  LETTER '[' e ']'
		={ bundle(3,$3, ";", geta($1)); }
	|  LETTER INCR
		= bundle(4, "l", $1, "d1+s", $1 );
	|  INCR LETTER
		= bundle(4, "l", $2, "1+ds", $2 );
	|  DECR LETTER
		= bundle(4, "l", $2, "1-ds", $2 );
	|  LETTER DECR
		= bundle(4, "l", $1, "d1-s", $1 );
	| LETTER '[' e ']' INCR
		= bundle(7,$3,";",geta($1),"d1+",$3,":",geta($1));
	| INCR LETTER '[' e ']'
		= bundle(7,$4,";",geta($2),"1+d",$4,":",geta($2));
	| LETTER '[' e ']' DECR
		= bundle(7,$3,";",geta($1),"d1-",$3,":",geta($1));
	| DECR LETTER '[' e ']'
		= bundle(7,$4,";",geta($2),"1-d",$4,":",geta($2));
	| SCALE INCR
		= bundle(1,"Kd1+k");
	| INCR SCALE
		= bundle(1,"K1+dk");
	| SCALE DECR
		= bundle(1,"Kd1-k");
	| DECR SCALE
		= bundle(1,"K1-dk");
	| BASE INCR
		= bundle(1,"Id1+i");
	| INCR BASE
		= bundle(1,"I1+di");
	| BASE DECR
		= bundle(1,"Id1-i");
	| DECR BASE
		= bundle(1,"I1-di");
	| OBASE INCR
		= bundle(1,"Od1+o");
	| INCR OBASE
		= bundle(1,"O1+do");
	| OBASE DECR
		= bundle(1,"Od1-o");
	| DECR OBASE
		= bundle(1,"O1-do");
	|  LETTER '(' cargs ')'
		= bundle(4, $3, "l", getf($1), "x" );
	|  LETTER '(' ')'
		= bundle(3, "l", getf($1), "x" );
	|  cons
		={ bundle(2, " ", $1 ); }
	|  DOT cons
		={ bundle(2, " .", $2 ); }
	|  cons DOT cons
		={ bundle(4, " ", $1, ".", $3 ); }
	|  cons DOT
		={ bundle(3, " ", $1, "." ); }
	|  DOT
		={ $$ = "l."; }
	|  LETTER
		= { bundle(2, "l", $1 ); }
	|  LETTER '=' e
		={ bundle(3, $3, "ds", $1 ); }
	|  LETTER EQOP e	%prec '='
		={ bundle(6, "l", $1, $3, $2, "ds", $1 ); }
	| LETTER '[' e ']' '=' e
		= { bundle(5,$6,"d",$3,":",geta($1)); }
	| LETTER '[' e ']' EQOP e
		= { bundle(9,$3,";",geta($1),$6,$5,"d",$3,":",geta($1)); }
	| LENGTH '(' e ')'
		= bundle(2,$3,"Z");
	| SCALE '(' e ')'
		= bundle(2,$3,"X");	/* must be before '(' e ')' */
	|  '(' e ')'
		= { $$ = $2; }
	|  '?'
		={ bundle(1, "?" ); }
	|  SQRT '(' e ')'
		={ bundle(2, $3, "v" ); }
	| '~' LETTER
		={ bundle(2,"L",$2); }
	| SCALE '=' e
		= bundle(2,$3,"dk");
	| SCALE EQOP e		%prec '='
		= bundle(4,"K",$3,$2,"dk");
	| BASE '=' e
		= bundle(2,$3,"di");
	| BASE EQOP e		%prec '='
		= bundle(4,"I",$3,$2,"di");
	| OBASE '=' e
		= bundle(2,$3,"do");
	| OBASE EQOP e		%prec '='
		= bundle(4,"O",$3,$2,"do");
	| SCALE
		= bundle(1,"K");
	| BASE
		= bundle(1,"I");
	| OBASE
		= bundle(1,"O");
	;

cargs	:  eora
	|  cargs ',' eora
		= bundle(2, $1, $3 );
	;
eora:	  e
	| LETTER '[' ']'
		=bundle(2,"l",geta($1));
	;

cons	:  constant
		={ *cp++ = '\0'; }

constant:
	  '_'
		={ $$ = cp; *cp++ = '_'; }
	|  DIGIT
		={ $$ = cp; *cp++ = $1; }
	|  constant DIGIT
		={ *cp++ = $2; }
	;

CRS	:
		={ $$ = cp; *cp++ = crs++; *cp++ = '\0';
			if(crs == '[')crs+=3;
			if(crs == 'a')crs='{';
			if(crs >= 0241){yyerror("program too big");
				getout();
			}
			bstack[bindx++] = lev++; }
	;

def	:  _DEFINE LETTER '('
		={	$$ = getf($2);
			pre = "";
			post = "";
			lev = 1;
			bstack[bindx=0] = 0;
			}
	;

dargs	:
	|  lora
		={ pp( $1 ); }
	|  dargs ',' lora
		={ pp( $3 ); }
	;

dlets	:  lora
		={ tp($1); }
	|  dlets ',' lora
		={ tp($3); }
	;
lora	:  LETTER
	|  LETTER '[' ']'
		={ $$ = geta($1); }
	;

%%
# define error 256

int peekc = -1;
int sargc;
int ifile;
char **sargv;

char funtab[52] = {
	01,0,02,0,03,0,04,0,05,0,06,0,07,0,010,0,011,0,012,0,013,0,014,0,015,0,016,0,017,0,
	020,0,021,0,022,0,023,0,024,0,025,0,026,0,027,0,030,0,031,0,032,0 };
char atab[52] = {
	0241,0,0242,0,0243,0,0244,0,0245,0,0246,0,0247,0,0250,0,0251,0,0252,0,0253,0,
	0254,0,0255,0,0256,0,0257,0,0260,0,0261,0,0262,0,0263,0,0264,0,0265,0,0266,0,
	0267,0,0270,0,0271,0,0272,0};
char *letr[26] = {
  "a","b","c","d","e","f","g","h","i","j",
  "k","l","m","n","o","p","q","r","s","t",
  "u","v","w","x","y","z" } ;
char *dot = { "." };
yylex(){
	int c, ch;
restart:
	c = getch();
	peekc = -1;
	while( c == ' ' || c == '\t' ) c = getch();
	if(c == '\\'){
		getch();
		goto restart;
	}
	if( c<= 'z' && c >= 'a' ) {
		/* look ahead to look for reserved words */
		peekc = getch();
		if( peekc >= 'a' && peekc <= 'z' ){ /* must be reserved word */
			if( c=='i' && peekc=='f' ){ c=_IF; goto skip; }
			if( c=='w' && peekc=='h' ){ c=_WHILE; goto skip; }
			if( c=='f' && peekc=='o' ){ c=_FOR; goto skip; }
			if( c=='s' && peekc=='q' ){ c=SQRT; goto skip; }
			if( c=='r' && peekc=='e' ){ c=_RETURN; goto skip; }
			if( c=='b' && peekc=='r' ){ c=_BREAK; goto skip; }
			if( c=='d' && peekc=='e' ){ c=_DEFINE; goto skip; }
			if( c=='s' && peekc=='c' ){ c= SCALE; goto skip; }
			if( c=='b' && peekc=='a' ){ c=BASE; goto skip; }
			if( c=='i' && peekc == 'b'){ c=BASE; goto skip; }
			if( c=='o' && peekc=='b' ){ c=OBASE; goto skip; }
			if( c=='d' && peekc=='i' ){ c=FFF; goto skip; }
			if( c=='a' && peekc=='u' ){ c=_AUTO; goto skip; }
			if( c == 'l' && peekc=='e'){ c=LENGTH; goto skip; }
			if( c == 'q' && peekc == 'u'){getout();}
			/* could not be found */
			return( error );
		skip:	/* skip over rest of word */
			peekc = -1;
			while( (ch = getch()) >= 'a' && ch <= 'z' );
			peekc = ch;
			return( c );
		}

		/* usual case; just one single letter */

		yylval = letr[c-'a'];
		return( LETTER );
	}
	if( c>= '0' && c <= '9' || c>= 'A' && c<= 'F' ){
		yylval = c;
		return( DIGIT );
	}
	switch( c ){
	case '.':	return( DOT );
	case '=':
		switch( peekc = getch() ){
		case '=': c=EQ; goto gotit;
		case '+': c=EQPL; goto gotit;
		case '-': c=EQMI; goto gotit;
		case '*': c=EQMUL; goto gotit;
		case '/': c=EQDIV; goto gotit;
		case '%': c=EQREM; goto gotit;
		case '^': c=EQEXP; goto gotit;
		default:   return( '=' );
			  gotit:     peekc = -1; return(c);
		  }
D 2
	case '+':	return( cpeek( '+', INCR, '+' ) );
	case '-':	return( cpeek( '-', DECR, '-' ) );
E 2
I 2
	case '+':	return( cpeek( '+', INCR, cpeek( '=', EQPL, '+') ) );
	case '-':	return( cpeek( '-', DECR, cpeek( '=', EQMI, '-') ) );
E 2
	case '<':	return( cpeek( '=', LE, '<' ) );
	case '>':	return( cpeek( '=', GE, '>' ) );
	case '!':	return( cpeek( '=', NE, '!' ) );
	case '/':
		if((peekc = getch()) == '*'){
			peekc = -1;
			while((getch() != '*') || ((peekc = getch()) != '/'));
			peekc = -1;
			goto restart;
		}
I 2
		else if (peekc == '=') {
			c=EQDIV;
			goto gotit;
		}
E 2
		else return(c);
I 2
	case '*':
		return( cpeek( '=', EQMUL, '*' ) );
	case '%':
		return( cpeek( '=', EQREM, '%' ) );
	case '^':
		return( cpeek( '=', EQEXP, '^' ) );
E 2
	case '"':	
		 yylval = str;
		 while((c=getch()) != '"'){*str++ = c;
			if(str >= &string[999]){yyerror("string space exceeded");
			getout();
		}
	}
	 *str++ = '\0';
	return(QSTR);
	default:	 return( c );
	}
}

cpeek( c, yes, no ){
	if( (peekc=getch()) != c ) return( no );
	else {
		peekc = -1;
		return( yes );
	}
}

getch(){
	int ch;
loop:
	ch = (peekc < 0) ? getc(in) : peekc;
	peekc = -1;
	if(ch != EOF)return(ch);
	if(++ifile > sargc){
		if(ifile >= sargc+2)getout();
		in = stdin;
		ln = 0;
		goto loop;
	}
	fclose(in);
	if((in = fopen(sargv[ifile],"r")) != NULL){
		ln = 0;
		ss = sargv[ifile];
		goto loop;
	}
	yyerror("cannot open input file");
}
# define b_sp_max 3000
int b_space [ b_sp_max ];
int * b_sp_nxt = { b_space };

int bdebug = 0;
D 4
bundle(a){
	int i, *p, *q;
E 4
I 4
/*VARARGS*/
bundle(va_alist) va_dcl {
	va_list ap;
	int i, *q;
E 4

D 4
	p = &a;
	i = *p++;
E 4
I 4
	va_start(ap);
	i = va_arg(ap, int);
E 4
	q = b_sp_nxt;
	if( bdebug ) printf("bundle %d elements at %o\n",i,  q );
	while(i-- > 0){
		if( b_sp_nxt >= & b_space[b_sp_max] ) yyerror( "bundling space exceeded" );
D 4
		* b_sp_nxt++ = *p++;
E 4
I 4
		* b_sp_nxt++ = va_arg(ap, int);
E 4
	}
	* b_sp_nxt++ = 0;
	yyval = q;
I 4
	va_end(ap);
E 4
	return( q );
}

routput(p) int *p; {
	if( bdebug ) printf("routput(%o)\n", p );
	if( p >= &b_space[0] && p < &b_space[b_sp_max]){
		/* part of a bundle */
		while( *p != 0 ) routput( *p++ );
	}
	else printf( p );	 /* character string */
}

output( p ) int *p; {
	routput( p );
	b_sp_nxt = & b_space[0];
	printf( "\n" );
	fflush(stdout);
	cp = cary;
	crs = rcrs;
}

conout( p, s ) int *p; char *s; {
	printf("[");
	routput( p );
	printf("]s%s\n", s );
	fflush(stdout);
	lev--;
}

yyerror( s ) char *s; {
	if(ifile > sargc)ss="teletype";
	printf("c[%s on line %d, %s]pc\n", s ,ln+1,ss);
	fflush(stdout);
	cp = cary;
	crs = rcrs;
	bindx = 0;
	lev = 0;
	b_sp_nxt = &b_space[0];
}

pp( s ) char *s; {
	/* puts the relevant stuff on pre and post for the letter s */

	bundle(3, "S", s, pre );
	pre = yyval;
	bundle(4, post, "L", s, "s." );
	post = yyval;
}

tp( s ) char *s; { /* same as pp, but for temps */
	bundle(3, "0S", s, pre );
	pre = yyval;
	bundle(4, post, "L", s, "s." );
	post = yyval;
}

yyinit(argc,argv) int argc; char *argv[];{
D 7
	signal( 2, (int(*)())1 );	/* ignore all interrupts */
E 7
I 7
	(void)signal(SIGINT, SIG_IGN);	/* ignore all interrupts */
E 7
	sargv=argv;
	sargc= -- argc;
	if(sargc == 0)in=stdin;
D 3
	else if((in = fopen(sargv[1],"r")) == NULL)
E 3
I 3
	else if((in = fopen(sargv[1],"r")) == NULL) {
E 3
		yyerror("cannot open input file");
I 3
		in = stdin;
	}
E 3
	ifile = 1;
	ln = 0;
	ss = sargv[1];
}
int *getout(){
	printf("q");
	fflush(stdout);
D 4
	exit();
E 4
I 4
	exit(0);
E 4
}

int *
getf(p) char *p;{
	return(&funtab[2*(*p -0141)]);
}
int *
geta(p) char *p;{
	return(&atab[2*(*p - 0141)]);
}

main(argc, argv)
char **argv;
{
	int p[2];


	if (argc > 1 && *argv[1] == '-') {
		if((argv[1][1] == 'd')||(argv[1][1] == 'c')){
			yyinit(--argc, ++argv);
			yyparse();
D 4
			exit();
E 4
I 4
			exit(0);
E 4
		}
		if(argv[1][1] != 'l'){
			printf("unrecognizable argument\n");
			fflush(stdout);
D 4
			exit();
E 4
I 4
			exit(1);
E 4
		}
D 6
		argv[1] = "/usr/lib/lib.b";
E 6
I 6
		argv[1] = _PATH_LIBB;
E 6
	}
	pipe(p);
	if (fork()==0) {
		close(1);
		dup(p[1]);
		close(p[0]);
		close(p[1]);
		yyinit(argc, argv);
		yyparse();
D 4
		exit();
E 4
I 4
		exit(0);
E 4
	}
	close(0);
	dup(p[0]);
	close(p[0]);
	close(p[1]);
D 4
	execl("/bin/dc", "dc", "-", 0);
	execl("/usr/bin/dc", "dc", "-", 0);
E 4
I 4
D 6
	execl("/bin/dc", "dc", "-", (char *)0);
	execl("/usr/bin/dc", "dc", "-", (char *)0);
E 6
I 6
	execl(_PATH_DC, "dc", "-", (char *)0);
E 6
	perror("bc: can't find dc");
	exit(1);
E 4
}
E 1
