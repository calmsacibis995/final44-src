h06233
s 00005/00005/00572
d D 8.1 93/06/06 16:24:23 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00015/00002/00562
d D 4.5 91/04/18 18:07:53 bostic 5 4
c new copyright; att/bsd/shared
e
s 00022/00003/00542
d D 4.4 91/02/02 17:54:43 torek 4 3
c putw => putword; argument declarations (all from gcc -W)
e
s 00005/00001/00540
d D 4.3 90/05/15 22:29:03 edward 3 2
c fixed an obscure bug that doesn't show up in English
e
s 00003/00001/00538
d D 4.2 86/06/03 14:57:47 bloom 2 1
c fix race in system scheduling
e
s 00539/00000/00000
d D 4.1 82/12/18 15:10:31 sam 1 0
c date and time created 82/12/18 15:10:31 by sam
e
u
U
t
T
I 5
/*-
D 6
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.proprietary.c%
 */

E 5
I 1
#ifndef lint
D 5
static char sccsid[] = "%W% %G%";
#endif
E 5
I 5
D 6
char copyright[] =
"%Z% Copyright (c) 1991 The Regents of the University of California.\n\
 All rights reserved.\n";
E 6
I 6
static char copyright[] =
"%Z% Copyright (c) 1991, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 6
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 5

#include "spell.h"
#define DLEV 2

char	*strcat();
int	strip();
char	*skipv();
int	an();
int	s();
int	es();
int	ily();
int	ncy();
int	CCe();
int	VCe();
int	bility();
int	tion();
int	ize();
int	y_to_e();
int	i_to_y();
int	nop();
int	metry();

struct suftab {
	char *suf;
	int (*p1)();
	int n1;
	char *d1;
	char *a1;
	int (*p2)();
	int n2;
	char *d2;
	char *a2;
} suftab[] = {
	{"ssen",ily,4,"-y+iness","+ness" },
	{"ssel",ily,4,"-y+i+less","+less" },
	{"se",s,1,"","+s",		es,2,"-y+ies","+es" },
	{"s'",s,2,"","+'s"},
	{"s",s,1,"","+s"},
	{"ecn",ncy,1,"","-t+ce"},
	{"ycn",ncy,1,"","-cy+t"},
	{"ytilb",nop,0,"",""},
	{"ytilib",bility,5,"-le+ility",""},
	{"elbaif",i_to_y,4,"-y+iable",""},
	{"elba",CCe,4,"-e+able","+able"},
	{"yti",CCe,3,"-e+ity","+ity"},
	{"ylb",y_to_e,1,"-e+y",""},
	{"yl",ily,2,"-y+ily","+ly"},
	{"laci",strip,2,"","+al"},
	{"latnem",strip,2,"","+al"},
	{"lanoi",strip,2,"","+al"},
	{"tnem",strip,4,"","+ment"},
	{"gni",CCe,3,"-e+ing","+ing"},
	{"reta",nop,0,"",""},
	{"re",strip,1,"","+r",		i_to_y,2,"-y+ier","+er"},
	{"de",strip,1,"","+d",		i_to_y,2,"-y+ied","+ed"},
	{"citsi",strip,2,"","+ic"},
	{"cihparg",i_to_y,1,"-y+ic",""},
	{"tse",strip,2,"","+st",	i_to_y,3,"-y+iest","+est"},
	{"cirtem",i_to_y,1,"-y+ic",""},
	{"yrtem",metry,0,"-ry+er",""},
	{"cigol",i_to_y,1,"-y+ic",""},
	{"tsigol",i_to_y,2,"-y+ist",""},
	{"tsi",VCe,3,"-e+ist","+ist"},
	{"msi",VCe,3,"-e+ism","+ist"},
	{"noitacif",i_to_y,6,"-y+ication",""},
	{"noitazi",ize,5,"-e+ation",""},
	{"rota",tion,2,"-e+or",""},
	{"noit",tion,3,"-e+ion","+ion"},
	{"naino",an,3,"","+ian"},
	{"na",an,1,"","+n"},
	{"evit",tion,3,"-e+ive","+ive"},
	{"ezi",CCe,3,"-e+ize","+ize"},
	{"pihs",strip,4,"","+ship"},
	{"dooh",ily,4,"-y+hood","+hood"},
	{"ekil",strip,4,"","+like"},
	0
};

char *preftab[] = {
	"anti",
	"bio",
	"dis",
	"electro",
	"en",
	"fore",
	"hyper",
	"intra",
	"inter",
	"iso",
	"kilo",
	"magneto",
	"meta",
	"micro",
	"milli",
	"mis",
	"mono",
	"multi",
	"non",
	"out",
	"over",
	"photo",
	"poly",
	"pre",
	"pseudo",
	"re",
	"semi",
	"stereo",
	"sub",
	"super",
	"thermo",
	"ultra",
	"under",	/*must precede un*/
	"un",
	0
};

int vflag;
int xflag;
char word[100];
char original[100];
char *deriv[40];
char affix[40];

main(argc,argv)
I 4
int argc;
E 4
char **argv;
{
	register char *ep, *cp;
	register char *dp;
	int fold;
	int j;
	FILE *file, *found;
	if(!prime(argc,argv)) {
		fprintf(stderr,
		    "spell: cannot initialize hash table\n");
		exit(1);
	}
	found = fopen(argv[2],"w");
	for(argc-=3,argv+=3; argc>0 && argv[0][0]=='-'; argc--,argv++)
		switch(argv[0][1]) {
		case 'b':
			ise();
			break;
		case 'v':
			vflag++;
			break;
		case 'x':
			xflag++;
			break;
		}
	for(;; fprintf(file,"%s%s\n",affix,original)) {
		affix[0] = 0;
		file = found;
		for(ep=word;(*ep=j=getchar())!='\n';ep++)
D 2
			if(j == EOF)
E 2
I 2
			if(j == EOF) {
				fclose(found);
E 2
				exit(0);
I 2
			}
E 2
		for(cp=word,dp=original; cp<ep; )
			*dp++ = *cp++;
		*dp = 0;
		fold = 0;
		for(cp=word;cp<ep;cp++)
			if(islower(*cp))
				goto lcase;
		if(putsuf(ep,".",0))
			continue;
		++fold;
		for(cp=original+1,dp=word+1;dp<ep;dp++,cp++)
			*dp = Tolower(*cp);
lcase:
		if(putsuf(ep,".",0)||suffix(ep,0))
			continue;
		if(isupper(word[0])) {
			for(cp=original,dp=word; *dp = *cp++; dp++)
				if (fold) *dp = Tolower(*dp);
			word[0] = Tolower(word[0]);
			goto lcase;
		}
		file = stdout;
	}
}

suffix(ep,lev)
char *ep;
I 4
int lev;
E 4
{
	register struct suftab *t;
	register char *cp, *sp;
	lev += DLEV;
	deriv[lev] = deriv[lev-1] = 0;
	for(t= &suftab[0];sp=t->suf;t++) {
		cp = ep;
		while(*sp)
			if(*--cp!=*sp++)
				goto next;
		for(sp=cp; --sp>=word&&!vowel(*sp); ) ;
		if(sp<word)
			return(0);
		if((*t->p1)(ep-t->n1,t->d1,t->a1,lev+1))
			return(1);
		if(t->p2!=0) {
			deriv[lev] = deriv[lev+1] = 0;
			return((*t->p2)(ep-t->n2,t->d2,t->a2,lev));
		}
		return(0);
next:		;
	}
	return(0);
}

nop()
{
	return(0);
}

strip(ep,d,a,lev)
char *ep,*d,*a;
I 4
int lev;
E 4
{
	return(putsuf(ep,a,lev)||suffix(ep,lev));
}

s(ep,d,a,lev)
char *ep,*d,*a;
I 4
int lev;
E 4
{
	if(lev>DLEV+1)
		return(0);
	if(*ep=='s'&&ep[-1]=='s')
		return(0);
	return(strip(ep,d,a,lev));
}

an(ep,d,a,lev)
char *ep,*d,*a;
I 4
int lev;
E 4
{
	if(!isupper(*word))	/*must be proper name*/
		return(0);
	return(putsuf(ep,a,lev));
}

ize(ep,d,a,lev)
char *ep,*d,*a;
I 4
int lev;
E 4
{
	*ep++ = 'e';
	return(strip(ep,"",d,lev));
}

y_to_e(ep,d,a,lev)
char *ep,*d,*a;
I 4
int lev;
E 4
{
I 3
	char c = *ep;
E 3
	*ep++ = 'e';
D 3
	return(strip(ep,"",d,lev));
E 3
I 3
	if (strip(ep,"",d,lev))
		return (1);
	ep[-1] = c;
	return (0);
E 3
}

ily(ep,d,a,lev)
char *ep,*d,*a;
I 4
int lev;
E 4
{
	if(ep[-1]=='i')
		return(i_to_y(ep,d,a,lev));
	else
		return(strip(ep,d,a,lev));
}

ncy(ep,d,a,lev)
char *ep, *d, *a;
I 4
int lev;
E 4
{
	if(skipv(skipv(ep-1))<word)
		return(0);
	ep[-1] = 't';
	return(strip(ep,d,a,lev));
}

bility(ep,d,a,lev)
char *ep,*d,*a;
I 4
int lev;
E 4
{
	*ep++ = 'l';
	return(y_to_e(ep,d,a,lev));
}

i_to_y(ep,d,a,lev)
char *ep,*d,*a;
I 4
int lev;
E 4
{
	if(ep[-1]=='i') {
		ep[-1] = 'y';
		a = d;
	}
	return(strip(ep,"",a,lev));
}

es(ep,d,a,lev)
char *ep,*d,*a;
I 4
int lev;
E 4
{
	if(lev>DLEV)
		return(0);
	switch(ep[-1]) {
	default:
		return(0);
	case 'i':
		return(i_to_y(ep,d,a,lev));
	case 's':
	case 'h':
	case 'z':
	case 'x':
		return(strip(ep,d,a,lev));
	}
}

metry(ep,d,a,lev)
char *ep, *d,*a;
I 4
int lev;
E 4
{
	ep[-2] = 'e';
	ep[-1] = 'r';
	return(strip(ep,d,a,lev));
}

tion(ep,d,a,lev)
char *ep,*d,*a;
I 4
int lev;
E 4
{
	switch(ep[-2]) {
	case 'c':
	case 'r':
		return(putsuf(ep,a,lev));
	case 'a':
		return(y_to_e(ep,d,a,lev));
	}
	return(0);
}

/*	possible consonant-consonant-e ending*/
CCe(ep,d,a,lev)
char *ep,*d,*a;
I 4
int lev;
E 4
{
	switch(ep[-1]) {
	case 'l':
		if(vowel(ep[-2]))
			break;
		switch(ep[-2]) {
		case 'l':
		case 'r':
		case 'w':
			break;
		default:
			return(y_to_e(ep,d,a,lev));
		}
		break;
	case 's':
		if(ep[-2]=='s')
			break;
	case 'c':
	case 'g':
		if(*ep=='a')
			return(0);
	case 'v':
	case 'z':
		if(vowel(ep[-2]))
			break;
	case 'u':
		if(y_to_e(ep,d,a,lev))
			return(1);
		if(!(ep[-2]=='n'&&ep[-1]=='g'))
			return(0);
	}
	return(VCe(ep,d,a,lev));
}

/*	possible consonant-vowel-consonant-e ending*/
VCe(ep,d,a,lev)
char *ep,*d,*a;
I 4
int lev;
E 4
{
	char c;
	c = ep[-1];
	if(c=='e')
		return(0);
	if(!vowel(c) && vowel(ep[-2])) {
		c = *ep;
		*ep++ = 'e';
		if(putsuf(ep,d,lev)||suffix(ep,lev))
			return(1);
		ep--;
		*ep = c;
	}
	return(strip(ep,d,a,lev));
}

char *lookuppref(wp,ep)
char **wp;
char *ep;
{
	register char **sp;
	register char *bp,*cp;
	for(sp=preftab;*sp;sp++) {
		bp = *wp;
		for(cp= *sp;*cp;cp++,bp++)
			if(Tolower(*bp)!=*cp)
				goto next;
		for(cp=bp;cp<ep;cp++) 
			if(vowel(*cp)) {
				*wp = bp;
				return(*sp);
			}
next:	;
	}
	return(0);
}

putsuf(ep,a,lev)
char *ep,*a;
I 4
int lev;
E 4
{
	register char *cp;
	char *bp;
	register char *pp;
	int val = 0;
	char space[20];
	deriv[lev] = a;
D 4
	if(putw(word,ep,lev))
E 4
I 4
	if(putword(word,ep,lev))
E 4
		return(1);
	bp = word;
	pp = space;
	deriv[lev+1] = pp;
	while(cp=lookuppref(&bp,ep)) {
		*pp++ = '+';
		while(*pp = *cp++)
			pp++;
D 4
		if(putw(bp,ep,lev+1)) {
E 4
I 4
		if(putword(bp,ep,lev+1)) {
E 4
			val = 1;
			break;
		}
	}
	deriv[lev+1] = deriv[lev+2] = 0;
	return(val);
}

D 4
putw(bp,ep,lev)
E 4
I 4
putword(bp,ep,lev)
E 4
char *bp,*ep;
I 4
int lev;
E 4
{
	register i, j;
	char duple[3];
	if(ep-bp<=1)
		return(0);
	if(vowel(*ep)) {
		if(monosyl(bp,ep))
			return(0);
	}
	i = dict(bp,ep);
	if(i==0&&vowel(*ep)&&ep[-1]==ep[-2]&&monosyl(bp,ep-1)) {
		ep--;
		deriv[++lev] = duple;
		duple[0] = '+';
		duple[1] = *ep;
		duple[2] = 0;
		i = dict(bp,ep);
	}
	if(vflag==0||i==0)
		return(i);
	j = lev;
	do {
		if(deriv[j])
			strcat(affix,deriv[j]);
	} while(--j>0);
	strcat(affix,"\t");
	return(i);
}


monosyl(bp,ep)
char *bp, *ep;
{
	if(ep<bp+2)
		return(0);
	if(vowel(*--ep)||!vowel(*--ep)
		||ep[1]=='x'||ep[1]=='w')
		return(0);
	while(--ep>=bp)
		if(vowel(*ep))
			return(0);
	return(1);
}

char *
skipv(s)
char *s;
{
	if(s>=word&&vowel(*s))
		s--;
	while(s>=word&&!vowel(*s))
		s--;
	return(s);
}

vowel(c)
I 4
int c;
E 4
{
	switch(Tolower(c)) {
	case 'a':
	case 'e':
	case 'i':
	case 'o':
	case 'u':
	case 'y':
		return(1);
	}
	return(0);
}

/* crummy way to Britishise */
ise()
{
	register struct suftab *p;
	for(p = suftab;p->suf;p++) {
		ztos(p->suf);
		ztos(p->d1);
		ztos(p->a1);
	}
}
ztos(s)
char *s;
{
	for(;*s;s++)
		if(*s=='z')
			*s = 's';
}

dict(bp,ep)
char *bp, *ep;
{
	register char *wp;
	long h;
	register long *lp;
	register i;
	if(xflag)
		printf("=%.*s\n",ep-bp,bp);
	for(i=0; i<NP; i++) {
		for (wp = bp, h = 0, lp = pow2[i]; wp < ep; ++wp, ++lp)
			h += *wp * *lp;
		h += '\n' * *lp;
		h %= p[i];
		if(get(h)==0)
			return(0);
	}
	return(1);
}
E 1
