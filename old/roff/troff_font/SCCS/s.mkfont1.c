h49297
s 00006/00002/00373
d D 4.4 91/04/18 17:56:03 bostic 4 3
c new copyright; att/bsd/shared
e
s 00147/00145/00228
d D 4.3 88/02/16 09:02:00 bostic 3 2
c GNU fixes for multi char constants
e
s 00003/00003/00370
d D 4.2 87/06/25 15:54:18 bostic 2 1
c old assignment operators
e
s 00373/00000/00000
d D 4.1 82/06/07 15:53:07 rrh 1 0
c date and time created 82/06/07 15:53:07 by rrh
e
u
U
t
T
I 4
/*-
 * %sccs.include.proprietary.c%
 */

E 4
I 1
#ifndef lint
D 4
static char mkfont1sccsid[] = "%W% %G%";
#endif lint
E 4
I 4
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 4

I 3
#define BYTE 8
#define PAIR(a,b) ((a)|((b)<<BYTE))
E 3

struct {
	int name;
	int ctval;
D 2
	} font[102] {
E 2
I 2
	} font[102] = {
E 2
'h',2,
't',2,
'n',0,
'm',0,
'l',2,
'i',2,
'z',0,
's',0,
'd',2,
'b',2,
'x',0,
'f',2,
'j',3,
'u',0,
'k',2,
'p',1,
D 3
'em',0,
E 3
I 3
PAIR('e','m'),0,
E 3
';',0,
'a',0,
D 3
'ru',0,
E 3
I 3
PAIR('r','u'),0,
E 3
'c',0,
'`',0,
'e',0,
'\'',0,
'o',0,
D 3
'14',0,
E 3
I 3
PAIR('1','4'),0,
E 3
'r',0,
D 3
'12',0,
E 3
I 3
PAIR('1','2'),0,
E 3
'v',0,
D 3
'hy',0,
E 3
I 3
PAIR('h','y'),0,
E 3
'w',0,
'q',1,
'/',0,
'.',0,
'g',1,
D 3
'34',0,
E 3
I 3
PAIR('3','4'),0,
E 3
',',0,
'&',0,
'y',1,
'%',0,
'Q',3,
'T',2,
'O',2,
'H',2,
'N',2,
'M',2,
'L',2,
'R',2,
'G',2,
'I',2,
'P',2,
'C',2,
'V',2,
'E',2,
'Z',2,
'D',2,
'B',2,
'S',2,
'Y',2,
'F',2,
'X',2,
'A',2,
'W',2,
'J',2,
'U',2,
'K',2,
'0',2,
'1',2,
'2',2,
'3',2,
'4',2,
'5',2,
'6',2,
'7',2,
'8',2,
'9',2,
'*',0,
D 3
'--',0,
'fi',0,
'fl',0,
'ff',0,
'ct',0,
'Fl',0,
'Fi',0,
E 3
I 3
PAIR('-','-'),0,
PAIR('f','i'),0,
PAIR('f','l'),0,
PAIR('f','f'),0,
PAIR('c','t'),0,
PAIR('F','l'),0,
PAIR('F','i'),0,
E 3
'(',0,
')',0,
'[',0,
']',0,
D 3
'de',0,
'dg',0,
E 3
I 3
PAIR('d','e'),0,
PAIR('d','g'),0,
E 3
'=',0,
D 3
'rg',0,
E 3
I 3
PAIR('r','g'),0,
E 3
':',0,
'+',0,
'!',0,
D 3
'bu',0,
E 3
I 3
PAIR('b','u'),0,
E 3
'?',0,
D 3
'fm',0,
E 3
I 3
PAIR('f','m'),0,
E 3
'|',0,
D 3
'co',0,
'sq',0,
E 3
I 3
PAIR('c','o'),0,
PAIR('s','q'),0,
E 3
'$',0};
D 2
char *nametab[256-32] {
E 2
I 2
char *nametab[256-32] = {
E 2
"/*space*/",
"/*!*/",
"/*\"*/",
"/*#*/",
"/*$*/",
"/*%*/",
"/*&*/",
"/*' close*/",
"/*(*/",
"/*)*/",
"/***/",
"/*+*/",
"/*,*/",
"/*- hyphen*/",
"/*.*/",
"/*/*/",
"/*0*/",
"/*1*/",
"/*2*/",
"/*3*/",
"/*4*/",
"/*5*/",
"/*6*/",
"/*7*/",
"/*8*/",
"/*9*/",
"/*:*/",
"/*;*/",
"/*<*/",
"/*=*/",
"/*>*/",
"/*?*/",
"/*@*/",
"/*A*/",
"/*B*/",
"/*C*/",
"/*D*/",
"/*E*/",
"/*F*/",
"/*G*/",
"/*H*/",
"/*I*/",
"/*J*/",
"/*K*/",
"/*L*/",
"/*M*/",
"/*N*/",
"/*O*/",
"/*P*/",
"/*Q*/",
"/*R*/",
"/*S*/",
"/*T*/",
"/*U*/",
"/*V*/",
"/*W*/",
"/*X*/",
"/*Y*/",
"/*Z*/",
"/*[*/",
"/*\\*/",
"/*]*/",
"/*^*/",
"/*_*/",
"/*` open*/",
"/*a*/",
"/*b*/",
"/*c*/",
"/*d*/",
"/*e*/",
"/*f*/",
"/*g*/",
"/*h*/",
"/*i*/",
"/*j*/",
"/*k*/",
"/*l*/",
"/*m*/",
"/*n*/",
"/*o*/",
"/*p*/",
"/*q*/",
"/*r*/",
"/*s*/",
"/*t*/",
"/*u*/",
"/*v*/",
"/*w*/",
"/*x*/",
"/*y*/",
"/*z*/",
"/*{*/",
"/*|*/",
"/*}*/",
"/*~*/",
"/*narrow space*/",
"/*hyphen*/",
"/*bullet*/",
"/*square*/",
"/*3/4 em*/",
"/*rule*/",
"/*1/4*/",
"/*1/2*/",
"/*3/4*/",
"/*minus*/",
"/*fi*/",
"/*fl*/",
"/*ff*/",
"/*ffi*/",
"/*ffl*/",
"/*degree*/",
"/*dagger*/",
"/*section*/",
"/*foot mark*/",
"/*'*/",
"/*`*/",
"/*_*/",
0,
"/*half nar sp*/",
0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,
"/*registered*/",
"/*copywrite*/",
0,
"/*cent*/",
};
D 2
int chtab [] {
E 2
I 2
int chtab [] = {
E 2
D 3
'--', 0210,	/*font minus*/
'hy', 0200,	/*hyphen*/
'bu', 0201,	/*bullet*/
'sq', 0202,	/*square*/
'em', 0203,	/*3/4em*/
'ru', 0204,	/*rule*/
'14', 0205,	/*1/4*/
'12', 0206,	/*1/2*/
'34', 0207,	/*3/4*/
'mi', 0302,	/*equation minus*/
'fi', 0211,	/*fi*/
'fl', 0212,	/*fl*/
'ff', 0213,	/*ff*/
'Fi', 0214,	/*ffi*/
'Fl', 0215,	/*ffl*/
'de', 0216,	/*degree*/
'dg', 0217,	/*dagger*/
'sc', 0220,	/*section*/
'fm', 0221,	/*foot mark*/
'aa', 0222,	/*acute accent*/
'ga', 0223,	/*grave accent*/
'ul', 0224,	/*underrule*/
'sl', 0225,	/*slash (longer)*/
'*a', 0230,	/*alpha*/
'*b', 0231,	/*beta*/
'*g', 0232,	/*gamma*/
'*d', 0233,	/*delta*/
'*e', 0234,	/*epsilon*/
'*z', 0235,	/*zeta*/
'*y', 0236,	/*eta*/
'*h', 0237,	/*theta*/
'*i', 0240,	/*iota*/
'*k', 0241,	/*kappa*/
'*l', 0242,	/*lambda*/
'*m', 0243,	/*mu*/
'*n', 0244,	/*nu*/
'*c', 0245,	/*xi*/
'*o', 0246,	/*omicron*/
'*p', 0247,	/*pi*/
'*r', 0250,	/*rho*/
'*s', 0251,	/*sigma*/
'*t', 0252,	/*tau*/
'*u', 0253,	/*upsilon*/
'*f', 0254,	/*phi*/
'*x', 0255,	/*chi*/
'*q', 0256,	/*psi*/
'*w', 0257,	/*omega*/
'*A', 0101,	/*Alpha*/
'*B', 0102,	/*Beta*/
'*G', 0260,	/*Gamma*/
'*D', 0261,	/*Delta*/
'*E', 0105,	/*Epsilon*/
'*Z', 0132,	/*Zeta*/
'*Y', 0110,	/*Eta*/
'*H', 0262,	/*Theta*/
'*I', 0111,	/*Iota*/
'*K', 0113,	/*Kappa*/
'*L', 0263,	/*Lambda*/
'*M', 0115,	/*Mu*/
'*N', 0116,	/*Nu*/
'*C', 0264,	/*Xi*/
'*O', 0117,	/*Omicron*/
'*P', 0265,	/*Pi*/
'*R', 0120,	/*Rho*/
'*S', 0266,	/*Sigma*/
'*T', 0124,	/*Tau*/
'*U', 0270,	/*Upsilon*/
'*F', 0271,	/*Phi*/
'*X', 0130,	/*Chi*/
'*Q', 0272,	/*Psi*/
'*W', 0273,	/*Omega*/
'sr', 0274,	/*square root*/
'ts', 0275,	/*terminal sigma*/
'rn', 0276,	/*root en*/
'>=', 0277,	/*>=*/
'<=', 0300,	/*<=*/
'==', 0301,	/*identically equal*/
'~=', 0303,	/*approx =*/
'ap', 0304,	/*approximates*/
'!=', 0305,	/*not equal*/
'->', 0306,	/*right arrow*/
'<-', 0307,	/*left arrow*/
'ua', 0310,	/*up arrow*/
'da', 0311,	/*down arrow*/
'eq', 0312,	/*equation equal*/
'mu', 0313,	/*multiply*/
'di', 0314,	/*divide*/
'+-', 0315,	/*plus-minus*/
'cu', 0316,	/*cup (union)*/
'ca', 0317,	/*cap (intersection)*/
'sb', 0320,	/*subset of*/
'sp', 0321,	/*superset of*/
'ib', 0322,	/*improper subset*/
'ip', 0323,	/*  " superset*/
'if', 0324,	/*infinity*/
'pd', 0325,	/*partial derivative*/
'gr', 0326,	/*gradient*/
'no', 0327,	/*not*/
'is', 0330,	/*integral sign*/
'pt', 0331,	/*proportional to*/
'es', 0332,	/*empty set*/
'mo', 0333,	/*member of*/
'pl', 0334,	/*equation plus*/
'rg', 0335,	/*registered*/
'co', 0336,	/*copyright*/
'br', 0337,	/*box vert rule*/
'ct', 0340,	/*cent sign*/
'dd', 0341,	/*dbl dagger*/
'rh', 0342,	/*right hand*/
'lh', 0343,	/*left hand*/
'**', 0344,	/*math * */
'bs', 0345,	/*bell system sign*/
'or', 0346,	/*or*/
'ci', 0347,	/*circle*/
'lt', 0350,	/*left top (of big curly)*/
'lb', 0351,	/*left bottom*/
'rt', 0352,	/*right top*/
'rb', 0353,	/*right bot*/
'lk', 0354,	/*left center of big curly bracket*/
'rk', 0355,	/*right center of big curly bracket*/
'bv', 0356,	/*bold vertical*/
'lf', 0357,	/*left floor (left bot of big sq bract)*/
'rf', 0360,	/*right floor (rb of ")*/
'lc', 0361,	/*left ceiling (lt of ")*/
'rc', 0362,	/*right ceiling (rt of ")*/
E 3
I 3
PAIR('-','-'), 0210,	/*font minus*/
PAIR('h','y'), 0200,	/*hyphen*/
PAIR('b','u'), 0201,	/*bullet*/
PAIR('s','q'), 0202,	/*square*/
PAIR('e','m'), 0203,	/*3/4em*/
PAIR('r','u'), 0204,	/*rule*/
PAIR('1','4'), 0205,	/*1/4*/
PAIR('1','2'), 0206,	/*1/2*/
PAIR('3','4'), 0207,	/*3/4*/
PAIR('m','i'), 0302,	/*equation minus*/
PAIR('f','i'), 0211,	/*fi*/
PAIR('f','l'), 0212,	/*fl*/
PAIR('f','f'), 0213,	/*ff*/
PAIR('F','i'), 0214,	/*ffi*/
PAIR('F','l'), 0215,	/*ffl*/
PAIR('d','e'), 0216,	/*degree*/
PAIR('d','g'), 0217,	/*dagger*/
PAIR('s','c'), 0220,	/*section*/
PAIR('f','m'), 0221,	/*foot mark*/
PAIR('a','a'), 0222,	/*acute accent*/
PAIR('g','a'), 0223,	/*grave accent*/
PAIR('u','l'), 0224,	/*underrule*/
PAIR('s','l'), 0225,	/*slash (longer)*/
PAIR('*','a'), 0230,	/*alpha*/
PAIR('*','b'), 0231,	/*beta*/
PAIR('*','g'), 0232,	/*gamma*/
PAIR('*','d'), 0233,	/*delta*/
PAIR('*','e'), 0234,	/*epsilon*/
PAIR('*','z'), 0235,	/*zeta*/
PAIR('*','y'), 0236,	/*eta*/
PAIR('*','h'), 0237,	/*theta*/
PAIR('*','i'), 0240,	/*iota*/
PAIR('*','k'), 0241,	/*kappa*/
PAIR('*','l'), 0242,	/*lambda*/
PAIR('*','m'), 0243,	/*mu*/
PAIR('*','n'), 0244,	/*nu*/
PAIR('*','c'), 0245,	/*xi*/
PAIR('*','o'), 0246,	/*omicron*/
PAIR('*','p'), 0247,	/*pi*/
PAIR('*','r'), 0250,	/*rho*/
PAIR('*','s'), 0251,	/*sigma*/
PAIR('*','t'), 0252,	/*tau*/
PAIR('*','u'), 0253,	/*upsilon*/
PAIR('*','f'), 0254,	/*phi*/
PAIR('*','x'), 0255,	/*chi*/
PAIR('*','q'), 0256,	/*psi*/
PAIR('*','w'), 0257,	/*omega*/
PAIR('*','A'), 0101,	/*Alpha*/
PAIR('*','B'), 0102,	/*Beta*/
PAIR('*','G'), 0260,	/*Gamma*/
PAIR('*','D'), 0261,	/*Delta*/
PAIR('*','E'), 0105,	/*Epsilon*/
PAIR('*','Z'), 0132,	/*Zeta*/
PAIR('*','Y'), 0110,	/*Eta*/
PAIR('*','H'), 0262,	/*Theta*/
PAIR('*','I'), 0111,	/*Iota*/
PAIR('*','K'), 0113,	/*Kappa*/
PAIR('*','L'), 0263,	/*Lambda*/
PAIR('*','M'), 0115,	/*Mu*/
PAIR('*','N'), 0116,	/*Nu*/
PAIR('*','C'), 0264,	/*Xi*/
PAIR('*','O'), 0117,	/*Omicron*/
PAIR('*','P'), 0265,	/*Pi*/
PAIR('*','R'), 0120,	/*Rho*/
PAIR('*','S'), 0266,	/*Sigma*/
PAIR('*','T'), 0124,	/*Tau*/
PAIR('*','U'), 0270,	/*Upsilon*/
PAIR('*','F'), 0271,	/*Phi*/
PAIR('*','X'), 0130,	/*Chi*/
PAIR('*','Q'), 0272,	/*Psi*/
PAIR('*','W'), 0273,	/*Omega*/
PAIR('s','r'), 0274,	/*square root*/
PAIR('t','s'), 0275,	/*terminal sigma*/
PAIR('r','n'), 0276,	/*root en*/
PAIR('>','='), 0277,	/*>=*/
PAIR('<','='), 0300,	/*<=*/
PAIR('=','='), 0301,	/*identically equal*/
PAIR('~','='), 0303,	/*approx =*/
PAIR('a','p'), 0304,	/*approximates*/
PAIR('!','='), 0305,	/*not equal*/
PAIR('-','>'), 0306,	/*right arrow*/
PAIR('<','-'), 0307,	/*left arrow*/
PAIR('u','a'), 0310,	/*up arrow*/
PAIR('d','a'), 0311,	/*down arrow*/
PAIR('e','q'), 0312,	/*equation equal*/
PAIR('m','u'), 0313,	/*multiply*/
PAIR('d','i'), 0314,	/*divide*/
PAIR('+','-'), 0315,	/*plus-minus*/
PAIR('c','u'), 0316,	/*cup (union)*/
PAIR('c','a'), 0317,	/*cap (intersection)*/
PAIR('s','b'), 0320,	/*subset of*/
PAIR('s','p'), 0321,	/*superset of*/
PAIR('i','b'), 0322,	/*improper subset*/
PAIR('i','p'), 0323,	/*  " superset*/
PAIR('i','f'), 0324,	/*infinity*/
PAIR('p','d'), 0325,	/*partial derivative*/
PAIR('g','r'), 0326,	/*gradient*/
PAIR('n','o'), 0327,	/*not*/
PAIR('i','s'), 0330,	/*integral sign*/
PAIR('p','t'), 0331,	/*proportional to*/
PAIR('e','s'), 0332,	/*empty set*/
PAIR('m','o'), 0333,	/*member of*/
PAIR('p','l'), 0334,	/*equation plus*/
PAIR('r','g'), 0335,	/*registered*/
PAIR('c','o'), 0336,	/*copyright*/
PAIR('b','r'), 0337,	/*box vert rule*/
PAIR('c','t'), 0340,	/*cent sign*/
PAIR('d','d'), 0341,	/*dbl dagger*/
PAIR('r','h'), 0342,	/*right hand*/
PAIR('l','h'), 0343,	/*left hand*/
PAIR('*','*'), 0344,	/*math * */
PAIR('b','s'), 0345,	/*bell system sign*/
PAIR('o','r'), 0346,	/*or*/
PAIR('c','i'), 0347,	/*circle*/
PAIR('l','t'), 0350,	/*left top (of big curly)*/
PAIR('l','b'), 0351,	/*left bottom*/
PAIR('r','t'), 0352,	/*right top*/
PAIR('r','b'), 0353,	/*right bot*/
PAIR('l','k'), 0354,	/*left center of big curly bracket*/
PAIR('r','k'), 0355,	/*right center of big curly bracket*/
PAIR('b','v'), 0356,	/*bold vertical*/
PAIR('l','f'), 0357,	/*left floor (left bot of big sq bract)*/
PAIR('r','f'), 0360,	/*right floor (rb of ")*/
PAIR('l','c'), 0361,	/*left ceiling (lt of ")*/
PAIR('r','c'), 0362,	/*right ceiling (rt of ")*/
E 3
0,0};
E 1
