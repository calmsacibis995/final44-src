h55174
s 00000/00000/00072
d D 8.1 93/06/06 16:08:21 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00006/00001/00066
d D 1.2 91/04/16 14:45:25 bostic 2 1
c new copyright; att/bsd/shared
e
s 00067/00000/00000
d D 1.1 82/12/15 21:46:19 clemc 1 0
c date and time created 82/12/15 21:46:19 by clemc
e
u
U
t
Original BTL Ratfor System for 4.2
T
I 1
D 2
/* %W% (Berkeley) %G% */
E 2
I 2
/*-
 * %sccs.include.proprietary.c%
 *
 *	%W% (Berkeley) %G%
 */

E 2
%{
extern int transfer;
extern	int	indent;
%}

%term	IF ELSE FOR WHILE BREAK NEXT 
%term	DIGITS DO
%term	GOK DEFINE INCLUDE
%term	REPEAT UNTIL
%term	RETURN
%term	SWITCH CASE DEFAULT
%%

statl	: statl  stat
	|
	;
stat	: if stat	={ indent--; outcont($1); }
	| ifelse stat	={ indent--; outcont($1+1); }
	| switch fullcase '}'	={ endsw($1, $2); }
	| while stat	={ whilestat($1); }
	| for stat	={ forstat($1); }
	| repeat stat UNTIL	={ untils($1,1); }
	| repeat stat		={ untils($1,0); }
	| BREAK	={ breakcode(); }
	| NEXT		={ nextcode(); }
	| do stat	={ dostat($1); }
	| GOK		={ gokcode($1); }
	| RETURN	={ retcode(); }
	| ';'
	| '{' statl '}'
	| label stat
	| error		={ errcode(); yyclearin; }
	;
switch	: sw '{'
	;
sw	: SWITCH	={ swcode(); }
	;
fullcase: caselist	={ $$ = 0; }
	| caselist defpart	={ $$ = 1; }
	;
caselist: casepart
	| caselist casepart
	;
defpart	: default statl
	;
default	: DEFAULT	={ getdefault(); }
	;
casepart: case statl
	;
case	: CASE	={ getcase(); }
	;
label	: DIGITS	={ transfer = 0; outcode($1); }
	;
if	: IF		={ ifcode(); }
	;
ifelse	: if stat ELSE	={ elsecode($1); }
	;
while	: WHILE	={ whilecode(); }
	;
for	: FOR		={ forcode(); }
	;
repeat	: REPEAT	={ repcode(); }
	;
do	: DO		={ docode(); }
	;
%%
E 1
