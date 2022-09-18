h23648
s 00000/00004/00501
d D 8.2 94/01/28 09:35:30 vern 6 5
c removed unmatchable rule
e
s 00000/00000/00505
d D 8.1 93/06/06 14:34:14 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00069/00068/00436
d D 4.4 92/04/14 09:35:35 vern 4 3
c Introduced "my_yytext" to emulate AT&T lex's yytext semantics
e
s 00007/00003/00497
d D 4.3 91/04/17 17:15:34 bostic 3 2
c new copyright; att/bsd/shared
e
s 00123/00061/00377
d D 4.2 82/11/06 14:34:42 rrh 2 1
c Bill Jolitz @ Berkeley received this version from Lorindia Cherry
c around September 1981, as the ``most recent version''.  Deltas 
c seem to be progressive, rather than regressive, although the BTL sid for
c deroff.c is retrograde; this is probably a case of parallel development
e
s 00438/00000/00000
d D 4.1 82/11/06 13:47:56 rrh 1 0
c Oldest available version at Berkeley
e
u
U
t
T
I 1
%{
D 3
/* break out words, output cap + word(inverted) */
E 3
I 3
/*-
 * %sccs.include.proprietary.c%
 */
E 3

#ifndef lint
D 3
static char sccsid[] = "%W%	(Berkeley)	%E%";
#endif not lint
E 3
I 3
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/* break out words, output cap + word(inverted) */
E 3

#include <stdio.h>
I 2
#include <ctype.h>
E 2
D 4
#define OUT()	for(i=yyleng-1;i>=0; i--)putchar(yytext[i]); putchar('\n')
#define OUT1(nam)	printf("%c:%s\n",nam,yytext)
E 4
I 4
#define OUT()	for(i=yyleng-1;i>=0; i--)putchar(my_yytext[i]); putchar('\n')
#define OUT1(nam)	printf("%c:%s\n",nam,my_yytext)
E 4
#define OUTN(string)	printf("%s\n",string)
#include "names.h"
#include "nhash.c"
#include "dict.c"
#include "ydict.c"
I 2
#include "abbrev.c"
E 2
char nt[]  = "D:n't";
char qs[]  = "c:'s";
char fin[]  = "E:.";
I 2
int NOCAPS = 0;		/* if set all caps are turned to lower case */
E 2
int i,j;
int dot = 0;
int first  = 1;
int qflg,nflg;
int cap  = 0;
I 4

static char my_yytext[YY_BUF_SIZE];

#define YY_USER_ACTION strcpy(my_yytext, yytext);
E 4
%}
D 4
%p 3000
D 2
%a 2500
E 2
I 2
%a 3300
%o 4500
E 4
E 2

L	[a-z]
N	[0-9]
C	[A-Z]
I 2
A	[a-zA-Z]
P	[a-zA-Z0-9]
E 2

%%
D 2
(St|Dr|Drs|Mr|Mrs|Ms)"."	{
E 2
I 2
^[.!].+[\n]	{
	if(dot){
		OUTN(fin);
		dot = 0;
		first = 1;
	}
D 4
	printf(":%s",yytext);
E 4
I 4
	printf(":%s",my_yytext);
E 4
	}
May	{
		if(first == 0){
			OUT1(NOUN);
		}
		else {
			first = 0;
D 4
			yytext[0] = tolower(yytext[0]);
E 4
I 4
			my_yytext[0] = tolower(my_yytext[0]);
E 4
			cap = 1;
			goto wd;
		}
	}
"U.S."		{
E 2
		OUT1(NOUN);
		}
{C}{L}*'[s]	{
		pos(1);
		if(first==1)first=0;
		}
D 2
{C}+['][s]*	{
E 2
I 2
{C}+['][s]	{
		if(NOCAPS)
			for(i=0;i<yyleng;i++)
D 4
				if(isupper(yytext[i]))yytext[i] = tolower(yytext[i]);
E 4
I 4
				if(isupper(my_yytext[i]))my_yytext[i] = tolower(my_yytext[i]);
E 4
E 2
		OUT1(POS);
		}
D 2
(({C}+{L}*)|({C}*{L}+))+([-](({C}*{L}+)|({C}+{L}*))+)+	{
E 2
I 2
{P}+([-]{P}+)+	{
		if(NOCAPS)
			for(i=0;i<yyleng;i++)
D 4
				if(isupper(yytext[i]))yytext[i] = tolower(yytext[i]);
E 4
I 4
				if(isupper(my_yytext[i]))my_yytext[i] = tolower(my_yytext[i]);
E 4
E 2
		OUT1(NOUN_ADJ);
		}
{C}{C}+	{
I 2
		if(NOCAPS)
			for(i=0;i<yyleng;i++)
D 4
				yytext[i] = tolower(yytext[i]);
E 4
I 4
				my_yytext[i] = tolower(my_yytext[i]);
E 4
E 2
		if((i=input()) == 's'){
D 4
			yytext[yyleng++] = 's';
			yytext[yyleng] = '\0';
E 4
I 4
			my_yytext[yyleng++] = 's';
			my_yytext[yyleng] = '\0';
E 4
D 2
			OUT1(NOUN);
E 2
I 2
			OUT1(PNOUN);
E 2
		}
		else {
			unput(i);
D 2
			for(i=0;i<yyleng;i++)yytext[i]+= 'a' - 'A';
E 2
I 2
			if(!NOCAPS)
D 4
				for(i=0;i<yyleng;i++)yytext[i] = tolower(yytext[i]);
E 4
I 4
				for(i=0;i<yyleng;i++)my_yytext[i] = tolower(my_yytext[i]);
E 4
E 2
				goto wd;
		}
		}
[LD][']{C}{L}*	{
I 2
		if(NOCAPS){
D 4
			yytext[0] = tolower(yytext[0]);
			yytext[2] = tolower(yytext[2]);
E 4
I 4
			my_yytext[0] = tolower(my_yytext[0]);
			my_yytext[2] = tolower(my_yytext[2]);
E 4
		}
E 2
		OUT1(NOUN_ADJ);
		}
{C}{L}*	{
		if(first==1)
			first=0;
		else cap = 1;
D 4
		if(yyleng==1 && yytext[0] == 'I'){
E 4
I 4
		if(yyleng==1 && my_yytext[0] == 'I'){
E 4
			cap = 0;
			goto wd;
		}
D 2
		yytext[0]+= 'a' - 'A';
E 2
I 2
D 4
		yytext[0] = tolower(yytext[0]);
E 4
I 4
		my_yytext[0] = tolower(my_yytext[0]);
E 4
E 2
		goto wd;
	}
D 2
({N}+[-]{N}+[-]*)+	{
E 2
I 2
{N}":"{N}{N}	{
E 2
		OUT1(NOUN_ADJ);
		}
D 2
({N}+[-]*{L}+[-]*)+	{
		OUT1(NOUN_ADJ);
		}
E 2
({N}*[,])*({N}+".")+[ \t\n]+{C}	{
		for(i=yyleng-1;i>0;i--)
D 4
			if(yytext[i] == '.')break;
		unput(yytext[yyleng-1]);
		yytext[i] = '\0';
E 4
I 4
			if(my_yytext[i] == '.')break;
		unput(my_yytext[yyleng-1]);
		my_yytext[i] = '\0';
E 4
		OUT1(NOUN_ADJ);
		OUTN(fin);
		first = 1;
	}
D 2
[ \t`][a-zA-Z0-9.]*("\/"[a-zA-Z0-9]+"."*)+[']*	{
		if(yytext[yyleng-1] == '.')dot=1;
E 2
I 2
([hH]e"/"[sS]he)|([sS]he"/"[hH]e)		{
	if(NOCAPS)
D 4
		if(isupper(yytext[0]))yytext[0] = tolower(yytext[0]);
E 4
I 4
		if(isupper(my_yytext[0]))my_yytext[0] = tolower(my_yytext[0]);
E 4
	OUT1(PRONS);
	}
([hH]is"/"[hH]er)|([hH]er"/"[hH]is)	{
	if(NOCAPS)
D 4
		if(isupper(yytext[0]))yytext[0] = tolower(yytext[0]);
E 4
I 4
		if(isupper(my_yytext[0]))my_yytext[0] = tolower(my_yytext[0]);
E 4
	OUT1(POS);
	}
[ \t`]*[a-zA-Z0-9.]*("\/"[a-zA-Z0-9.]+)+[']*	{
D 4
		if(yytext[yyleng-1] == '.'){
E 4
I 4
		if(my_yytext[yyleng-1] == '.'){
E 4
			if(ahead() == 0)dot=1;
		}
		if(NOCAPS)
			for(i=0;i<yyleng;i++)
D 4
				if(isupper(yytext[i]))yytext[i] = tolower(yytext[i]);
E 4
I 4
				if(isupper(my_yytext[i]))my_yytext[i] = tolower(my_yytext[i]);
E 4
E 2
		OUT1(NOUN_ADJ);
		}
{N}+([,]{N}+)*("."{N}+)*[']*[s]*	{
	OUT1(NOUN_ADJ);
	}
{N}*([,]{N}+)*("."{N}+)+[']*[s]*	{
	OUT1(NOUN_ADJ);
	}
{N}+([,]{N}+)*("."{N}*)*[']*[s]*	{
D 4
	if(yytext[yyleng-1] == '.')dot=1;
E 4
I 4
	if(my_yytext[yyleng-1] == '.')dot=1;
E 4
	OUT1(NOUN_ADJ);
	}
D 2
{L}+[-]*{N}+	{
		OUT1(NOUN_ADJ);
		}
{C}+[-]*{N}+	{
E 2
I 2
({A}*{N}+{A}*)+	{
	if(input() == '.')
		ahead();
	if(NOCAPS)
		for(i=0;i<yyleng;i++)
D 4
			if(isupper(yytext[i]))yytext[i]=tolower(yytext[i]);
E 4
I 4
			if(isupper(my_yytext[i]))my_yytext[i]=tolower(my_yytext[i]);
E 4
E 2
	OUT1(NOUN_ADJ);
	}
D 2
{N}+[-]+{C}+	{
	OUT1(NOUN_ADJ);
		}
E 2
{N}+[%]		{
		OUT1(NOUN_ADJ);
		}
"$"{N}+([,]{N}+)*("."{N}*)*	{
D 4
		if(yytext[yyleng-1] == '.')dot=1;
E 4
I 4
		if(my_yytext[yyleng-1] == '.')dot=1;
E 4
		OUT1(NOUN);
		}
[Aa]"."[ ]*[Mm]"."	{
		OUT1(ADJ_ADV);
		}
[Pp]"."[ ]*[Mm]"."	{
		OUT1(ADJ_ADV);
		}
"a."[ ]*"d."	{
		OUT1(ADJ_ADV);
		}
"b."[ ]*"c."	{
		OUT1(ADJ_ADV);
		}
"i."[ ]*"e."	{
		OUT1(PREP);
		}
"e."[ ]*"g."	{
		OUT1(PREP);
		}
"etc."[ \n]*[,)]*	{
D 4
		i = yytext[4];
		yytext[4] = '\0';
E 4
I 4
		i = my_yytext[4];
		my_yytext[4] = '\0';
E 4
		OUT1(NOUN);
D 4
		yytext[4] = i;
		yytext[0] = yytext[yyleng-1];
		yytext[1] = '\0';
		if(yytext[0] == ',' || yytext[0] == ')')
E 4
I 4
		my_yytext[4] = i;
		my_yytext[0] = my_yytext[yyleng-1];
		my_yytext[1] = '\0';
		if(my_yytext[0] == ',' || my_yytext[0] == ')')
E 4
			OUT1(',');
		else {
			OUTN(fin);
			first = 1;
		}
	}
"et al."	{
		OUT1(NOUN);
		}
D 2
[Nn][Oo][s]*"."	{
		OUT1(NOUN_ADJ);
		}
[Ff]ig[s]*"."	{
		OUT1(NOUN_ADJ);
		}
[Dd]ept[s]*"."	{
		OUT1(NOUN_ADJ);
	}
[Ee]q"."	{
		OUT1(NOUN_ADJ);
		}
dB"."	{
		OUT1(NOUN_ADJ);
		}
vs"."	{
	OUT1(PREP);
	}
E 2
in"."[ \n]*{C}	{
D 4
		unput(yytext[yyleng-1]);
		yytext[2] = '\0';
E 4
I 4
		unput(my_yytext[yyleng-1]);
		my_yytext[2] = '\0';
E 4
		OUT1(PREP);
		OUTN(fin);
		first = 1;
		}
D 2
(in|ft|yr|ckts|mi)"."	{
		OUT1(NOUN_ADJ);
		}
E 2
Ph"."[ ]*[Dd]"."	{
		OUT1(ADJ);
		}
D 2
[Jj]r"."	{
	OUT1(ADJ);
	}
[Cc]h"."	{
		OUT1(NOUN_ADJ);
	}
[Rr]ef[s]*"."	{
		OUT1(NOUN_ADJ);
	}
Inc"."	{
		OUT1(ADJ);
	}
E 2
[A-Z]"."	{
		dot=1;
		OUT1(NOUN);
		}
can't		{
D 4
		yytext[3]='\0';
E 4
I 4
		my_yytext[3]='\0';
E 4
		yyleng -= 2;
		nflg=1;
		goto wd;
		}
won't		{
		OUT1('X');
		}
I 2
ain't		{
		OUT1('g');
		}
E 2
{L}+n't		{
		nflg=1;
D 4
		yytext[yyleng-3]='\0';
E 4
I 4
		my_yytext[yyleng-3]='\0';
E 4
		yyleng -= 3;
		goto wd;
		}
[A-Z]{L}+n't	{
D 2
		yytext[0]+= 'a' - 'A';
E 2
I 2
D 4
		yytext[0] = tolower(yytext[0]);
E 4
I 4
		my_yytext[0] = tolower(my_yytext[0]);
E 4
E 2
		nflg=1;
D 4
		yytext[yyleng-3]='\0';
E 4
I 4
		my_yytext[yyleng-3]='\0';
E 4
		yyleng -= 3;
		goto wd;
		}
D 2
o'clock	{
E 2
I 2
o'clock		{
E 2
		OUT1(ADV);
	}
{L}+'[s]	{
		pos(0);
		}
'll	{
		OUT1(lookup("will",1,0));
	}
've	{
		OUT1(lookup("have",1,0));
	}
're	{
		OUT1(lookup("are",1,0));
	}
'd	{
		OUT1(lookup("had",1,0));
	}
'm	{
		OUT1(lookup("am",1,0));
	}
'ld	{
		OUT1(lookup("would",1,0));
	}
{L}+	{
wd:
D 4
	if((j = lookup(yytext,1,0)) != 0){
E 4
I 4
	if((j = lookup(my_yytext,1,0)) != 0){
E 4
		first=0;
		if(cap){
D 2
			yytext[0] += 'A' - 'a';
E 2
I 2
			if(!NOCAPS)
D 4
				yytext[0] = toupper(yytext[0]);
E 4
I 4
				my_yytext[0] = toupper(my_yytext[0]);
E 4
E 2
			cap = 0;
			if(dot)OUTN(fin);
		}
		dot=0;
		OUT1(j);
		if(nflg==1){
			nflg=0;
			OUTN(nt);
		}
	}
	else{
		first = dot=0;
D 4
		if(yytext[yyleng-1] == 'y' && cap == 0){
			switch(yytext[yyleng-2]){
E 4
I 4
		if(my_yytext[yyleng-1] == 'y' && cap == 0){
			switch(my_yytext[yyleng-2]){
E 4
			case 'c': look(cy,yyleng-2,NOUN);
					break;
			case 'f': look(fy,yyleng-2,VERB);
					break;
			case 'l': look(ly,yyleng-2,ADV);
					break;
D 4
			case 'g': if(yytext[yyleng-3] == 'o'){
E 4
I 4
			case 'g': if(my_yytext[yyleng-3] == 'o'){
E 4
					OUT1(NOUN);
					break;
				}
D 2
				 look(gy,yyleng-2,ADJ);
E 2
I 2
				look(gy,yyleng-2,ADJ);
E 2
				break;
D 4
			case 'r':	switch(yytext[yyleng-3]){
E 4
I 4
			case 'r':	switch(my_yytext[yyleng-3]){
E 4
				case 'a': look(ary,yyleng-3,ADJ);
						break;
				case 'o': look(ory,yyleng-3,ADJ);
						break;
				case 'e': look(ery,yyleng-3,NOUN);
						break;
				default: look(ry,yyleng-2,NOUN);
				}
				break;
D 4
			case 't': if(yytext[yyleng-3] == 'i')look(ity,yyleng-3,NOUN);
E 4
I 4
			case 't': if(my_yytext[yyleng-3] == 'i')look(ity,yyleng-3,NOUN);
E 4
				else look(ty,yyleng-2,ADJ);
				break;
			default: OUT();
			}
D 2
		}
E 2
I 2
	}
E 2
		else {
			if(cap){
D 2
				yytext[0] += 'A' - 'a';
E 2
I 2
D 4
				if(!NOCAPS)yytext[0] = toupper(yytext[0]);
E 4
I 4
				if(!NOCAPS)my_yytext[0] = toupper(my_yytext[0]);
E 4
E 2
				cap = 0;
				OUT1(NOUN_ADJ);
			}
			else {
				OUT();
			}
		}
	}
	}
[\n]	;
[ ]+	;
[\t]+	;
";"	{
	OUT1(';');
	first=1;
	}
(\"|`|')+	{
	if(dot){
		OUTN(fin);
		dot=0;
	}
	if(qflg==1){
		qflg=0;
		OUT1('"');
	}
	else {
		qflg=1;
		first=1;
		OUT1('"');
	}
	}
".\""	{
	qflg=0;
	first=1;
	OUT1(END);
	}
"..."	{
	OUT1(',');
	}
D 6
"/."	{
	first = 1;
	OUT1(END);
	}
E 6
I 2
{A}{A}+"."	{
D 4
		yytext[yyleng-1] = '\0';
		if((j=abbrev(yytext,1,0)) != 0){
			if(isupper(yytext[0])){
				if(NOCAPS)yytext[0] = tolower(yytext[0]);
E 4
I 4
		my_yytext[yyleng-1] = '\0';
		if((j=abbrev(my_yytext,1,0)) != 0){
			if(isupper(my_yytext[0])){
				if(NOCAPS)my_yytext[0] = tolower(my_yytext[0]);
E 4
				if(first == 1)first=0;
			}
D 4
			yytext[yyleng-1] = '.';
E 4
I 4
			my_yytext[yyleng-1] = '.';
E 4
			OUT1(j);
		}
		else {
			j = ahead();
			if(j == 0)
				yyleng--;
			for(i=0;i<yyleng;i++)
D 4
				if(isupper(yytext[i])){
					yytext[i] = tolower(yytext[i]);
E 4
I 4
				if(isupper(my_yytext[i])){
					my_yytext[i] = tolower(my_yytext[i]);
E 4
					if(i == 0)cap = 1;
					else cap = 0;
				}
			if(j == 0)goto wd;
			OUT1(NOUN_ADJ);
		}
	}
E 2
"."	{
	first=1;
	OUT1(END);
	}
"!\""	{
	qflg=0;
	first=1;
	OUT1(END);
	}
"!"	{
	first=1;
	OUT1(END);
	}
"?\""	{
	qflg=0;
	first=1;
	OUT1(END);
	}
"?"	{
	first=1;
	OUT1(END);
	}
":"	{
	OUT1(',');
	first=1;
	}
[-]+	{
	OUT1(',');
	first=1;
	}
","	{
	OUT1(',');
	}
(\[|\(|\{|\]|\)|\})	{
	OUT1(',');
	}
.	{
D 4
/*	fprintf(stderr,"nwords funny char: %c\n",yytext[0])*/ ;
E 4
I 4
/*	fprintf(stderr,"nwords funny char: %c\n",my_yytext[0])*/ ;
E 4
	}
%%
look(f,n,cc)
char (*f)();
int n;
char cc;
{
	int nn;
	char  save;
D 4
	save=yytext[n];
	yytext[n] = '\0';
	nn=(*f)(yytext,1,0);
	yytext[n] = save;
E 4
I 4
	save=my_yytext[n];
	my_yytext[n] = '\0';
	nn=(*f)(my_yytext,1,0);
	my_yytext[n] = save;
E 4
	if(nn != 0){
		OUT1(nn);
	}
	else {
		OUT1(cc);
	}
}
pos(flg){
	int ii,j;
D 2
	if(flg==1)yytext[0] += 'a' - 'A';
E 2
I 2
D 4
	if(flg == 1)yytext[0] = tolower(yytext[0]);
E 2
	for(ii=yyleng-1;yytext[ii] != '\''; ii--);
	yytext[ii] = '\0';
	if((j=lookup(yytext,1,0)) != 0){
E 4
I 4
	if(flg == 1)my_yytext[0] = tolower(my_yytext[0]);
	for(ii=yyleng-1;my_yytext[ii] != '\''; ii--);
	my_yytext[ii] = '\0';
	if((j=lookup(my_yytext,1,0)) != 0){
E 4
		yyleng = ii;
		OUT1(j);
		OUTN(qs);
	}
	else{
D 2
		if(flg==1)yytext[0] += 'A' - 'a';
E 2
I 2
D 4
		if(flg==1 && !NOCAPS)yytext[0] = toupper(yytext[0]);
E 2
		yytext[ii] = '\'';
E 4
I 4
		if(flg==1 && !NOCAPS)my_yytext[0] = toupper(my_yytext[0]);
		my_yytext[ii] = '\'';
E 4
		OUT1(POS);
	}
}
char	*filename="-";

main(argc,argv)
int	argc;
char	*argv[];
{
	register int rc=0;
	putchar(':'); putchar('\n');
	getd();
I 2
	getab();
E 2
	ygetd();
	if(argc<=1) {
		yylex();
I 2
		OUTN(fin);
E 2
	}else{
		while(argc>1) {
			if(freopen(argv[1],"r",stdin)==NULL) {
				fprintf(stderr,"%s: cannot open\n", argv[1]);
				rc++;
			}else{
				filename=argv[1];
				yylex();
I 2
				OUTN(fin);
E 2
			}
			argc--; argv++;
		}
	}
	return(rc);
I 2
}
ahead(){
	register int c;
	if(isalnum((c=input()))){
D 4
		yytext[yyleng++] = '.';
E 4
I 4
		my_yytext[yyleng++] = '.';
E 4
		while(!isspace((c=input() )))
D 4
			yytext[yyleng++] = c;
		yytext[yyleng] = '\0';
E 4
I 4
			my_yytext[yyleng++] = c;
		my_yytext[yyleng] = '\0';
E 4
		unput(c);
		return(1);
	}
	unput(c);
	unput('.');
	return(0);
E 2
}
E 1
