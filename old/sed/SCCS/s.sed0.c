h43685
s 00001/00000/00999
d D 4.8 91/09/11 19:16:33 torek 8 7
c stdout must have a name, not just NULL: use empty string
e
s 00007/00001/00992
d D 4.7 91/04/18 18:00:55 bostic 7 6
c new copyright; att/bsd/shared
e
s 00001/00001/00992
d D 4.6 91/03/01 18:34:50 bostic 6 5
c ANSI
e
s 00002/00002/00991
d D 4.5 87/12/21 12:28:23 bostic 5 4
c make ANSI C compatible
e
s 00019/00002/00974
d D 4.4 87/09/16 13:41:33 bostic 4 3
c malloc space for file names; bug report 4.3BSD/bin/64
e
s 00002/00002/00974
d D 4.3 87/09/16 13:06:33 bostic 3 2
c allow 10 files; bug report 4.3BSD/bin/64
e
s 00007/00001/00969
d D 4.2 85/06/19 00:01:50 bloom 2 1
c fix looping problem when no first RE
e
s 00970/00000/00000
d D 4.1 85/04/05 09:29:15 ralph 1 0
c date and time created 85/04/05 09:29:15 by ralph
e
u
U
t
T
I 1
D 7
/*	%M%	%I%	%E%	*/
E 7
I 7
/*-
 * %sccs.include.proprietary.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 7

I 4
#include <sys/param.h>
E 4
#include <stdio.h>
#include "sed.h"

struct label	*labtab = ltab;
char	CGMES[]	= "command garbled: %s\n";
char	TMMES[]	= "Too much text: %s\n";
char	LTL[]	= "Label too long: %s\n";
char	AD0MES[]	= "No addresses allowed: %s\n";
char	AD1MES[]	= "Only one address allowed: %s\n";
char	bittab[]  = {
		1,
		2,
		4,
		8,
		16,
		32,
		64,
		128
	};

main(argc, argv)
char	*argv[];
{

	eargc = argc;
	eargv = argv;

	badp = &bad;
	aptr = abuf;
	lab = labtab + 1;	/* 0 reserved for end-pointer */
	rep = ptrspace;
	rep->ad1 = respace;
	lbend = &linebuf[LBSIZE];
	hend = &holdsp[LBSIZE];
	lcomend = &genbuf[71];
	ptrend = &ptrspace[PTRSIZE];
	reend = &respace[RESIZE];
	labend = &labtab[LABSIZE];
	lnum = 0;
	pending = 0;
	depth = 0;
	spend = linebuf;
	hspend = holdsp;
	fcode[0] = stdout;
I 8
	fname[0] = "";
E 8
	nfiles = 1;

	if(eargc == 1)
		exit(0);


	while (--eargc > 0 && (++eargv)[0][0] == '-')
		switch (eargv[0][1]) {

		case 'n':
			nflag++;
			continue;

		case 'f':
			if(eargc-- <= 0)	exit(2);

			if((fin = fopen(*++eargv, "r")) == NULL) {
				fprintf(stderr, "Cannot open pattern-file: %s\n", *eargv);
				exit(2);
			}

			fcomp();
			fclose(fin);
			continue;

		case 'e':
			eflag++;
			fcomp();
			eflag = 0;
			continue;

		case 'g':
			gflag++;
			continue;

		default:
			fprintf(stdout, "Unknown flag: %c\n", eargv[0][1]);
			continue;
		}


	if(compfl == 0) {
		eargv--;
		eargc++;
		eflag++;
		fcomp();
		eargv++;
		eargc--;
		eflag = 0;
	}

	if(depth) {
		fprintf(stderr, "Too many {'s");
		exit(2);
	}

	labtab->address = rep;

	dechain();

/*	abort();	/*DEBUG*/

	if(eargc <= 0)
		execute((char *)NULL);
	else while(--eargc >= 0) {
		execute(*eargv++);
	}
	fclose(stdout);
	exit(0);
}
fcomp()
{

	register char	*p, *op, *tp;
	char	*address();
D 5
	union reptr	*pt, *pt1;
E 5
I 5
	struct reptr	*pt, *pt1;
E 5
	int	i;
	struct label	*lpt;
I 4
	char fbuf[MAXPATHLEN + 1], *newstr();
E 4

	compfl = 1;
	op = lastre;

	if(rline(linebuf) < 0)	return;
	if(*linebuf == '#') {
		if(linebuf[1] == 'n')
			nflag = 1;
	}
	else {
		cp = linebuf;
		goto comploop;
	}

	for(;;) {
		if(rline(linebuf) < 0)	break;

		cp = linebuf;

comploop:
/*	fprintf(stdout, "cp: %s\n", cp);	/*DEBUG*/
		while(*cp == ' ' || *cp == '\t')	cp++;
		if(*cp == '\0' || *cp == '#')		continue;
		if(*cp == ';') {
			cp++;
			goto comploop;
		}

		p = address(rep->ad1);
		if(p == badp) {
			fprintf(stderr, CGMES, linebuf);
			exit(2);
		}

		if(p == rep->ad1) {
			if(op)
				rep->ad1 = op;
			else {
				fprintf(stderr, "First RE may not be null\n");
				exit(2);
			}
		} else if(p == 0) {
			p = rep->ad1;
			rep->ad1 = 0;
		} else {
			op = rep->ad1;
			if(*cp == ',' || *cp == ';') {
				cp++;
				if((rep->ad2 = p) > reend) {
					fprintf(stderr, TMMES, linebuf);
					exit(2);
				}
				p = address(rep->ad2);
				if(p == badp || p == 0) {
					fprintf(stderr, CGMES, linebuf);
					exit(2);
				}
				if(p == rep->ad2)
					rep->ad2 = op;
				else
					op = rep->ad2;

			} else
				rep->ad2 = 0;
		}

		if(p > reend) {
			fprintf(stderr, "Too much text: %s\n", linebuf);
			exit(2);
		}

		while(*cp == ' ' || *cp == '\t')	cp++;

swit:
		switch(*cp++) {

			default:
				fprintf(stderr, "Unrecognized command: %s\n", linebuf);
				exit(2);

			case '!':
				rep->negfl = 1;
				goto swit;

			case '{':
				rep->command = BCOM;
				rep->negfl = !(rep->negfl);
				cmpend[depth++] = &rep->lb1;
				if(++rep >= ptrend) {
					fprintf(stderr, "Too many commands: %s\n", linebuf);
					exit(2);
				}
				rep->ad1 = p;
				if(*cp == '\0')	continue;

				goto comploop;

			case '}':
				if(rep->ad1) {
					fprintf(stderr, AD0MES, linebuf);
					exit(2);
				}

				if(--depth < 0) {
					fprintf(stderr, "Too many }'s\n");
					exit(2);
				}
				*cmpend[depth] = rep;

				rep->ad1 = p;
				continue;

			case '=':
				rep->command = EQCOM;
				if(rep->ad2) {
					fprintf(stderr, AD1MES, linebuf);
					exit(2);
				}
				break;

			case ':':
				if(rep->ad1) {
					fprintf(stderr, AD0MES, linebuf);
					exit(2);
				}

				while(*cp++ == ' ');
				cp--;


				tp = lab->asc;
				while((*tp++ = *cp++))
					if(tp >= &(lab->asc[8])) {
						fprintf(stderr, LTL, linebuf);
						exit(2);
					}
				*--tp = '\0';

				if(lpt = search(lab)) {
					if(lpt->address) {
						fprintf(stderr, "Duplicate labels: %s\n", linebuf);
						exit(2);
					}
				} else {
					lab->chain = 0;
					lpt = lab;
					if(++lab >= labend) {
						fprintf(stderr, "Too many labels: %s\n", linebuf);
						exit(2);
					}
				}
				lpt->address = rep;
				rep->ad1 = p;

				continue;

			case 'a':
				rep->command = ACOM;
				if(rep->ad2) {
					fprintf(stderr, AD1MES, linebuf);
					exit(2);
				}
				if(*cp == '\\')	cp++;
				if(*cp++ != '\n') {
					fprintf(stderr, CGMES, linebuf);
					exit(2);
				}
				rep->re1 = p;
				p = text(rep->re1);
				break;
			case 'c':
				rep->command = CCOM;
				if(*cp == '\\')	cp++;
				if(*cp++ != ('\n')) {
					fprintf(stderr, CGMES, linebuf);
					exit(2);
				}
				rep->re1 = p;
				p = text(rep->re1);
				break;
			case 'i':
				rep->command = ICOM;
				if(rep->ad2) {
					fprintf(stderr, AD1MES, linebuf);
					exit(2);
				}
				if(*cp == '\\')	cp++;
				if(*cp++ != ('\n')) {
					fprintf(stderr, CGMES, linebuf);
					exit(2);
				}
				rep->re1 = p;
				p = text(rep->re1);
				break;

			case 'g':
				rep->command = GCOM;
				break;

			case 'G':
				rep->command = CGCOM;
				break;

			case 'h':
				rep->command = HCOM;
				break;

			case 'H':
				rep->command = CHCOM;
				break;

			case 't':
				rep->command = TCOM;
				goto jtcommon;

			case 'b':
				rep->command = BCOM;
jtcommon:
				while(*cp++ == ' ');
				cp--;

				if(*cp == '\0') {
					if(pt = labtab->chain) {
						while(pt1 = pt->lb1)
							pt = pt1;
						pt->lb1 = rep;
					} else
						labtab->chain = rep;
					break;
				}
				tp = lab->asc;
				while((*tp++ = *cp++))
					if(tp >= &(lab->asc[8])) {
						fprintf(stderr, LTL, linebuf);
						exit(2);
					}
				cp--;
				*--tp = '\0';

				if(lpt = search(lab)) {
					if(lpt->address) {
						rep->lb1 = lpt->address;
					} else {
						pt = lpt->chain;
						while(pt1 = pt->lb1)
							pt = pt1;
						pt->lb1 = rep;
					}
				} else {
					lab->chain = rep;
					lab->address = 0;
					if(++lab >= labend) {
						fprintf(stderr, "Too many labels: %s\n", linebuf);
						exit(2);
					}
				}
				break;

			case 'n':
				rep->command = NCOM;
				break;

			case 'N':
				rep->command = CNCOM;
				break;

			case 'p':
				rep->command = PCOM;
				break;

			case 'P':
				rep->command = CPCOM;
				break;

			case 'r':
				rep->command = RCOM;
				if(rep->ad2) {
					fprintf(stderr, AD1MES, linebuf);
					exit(2);
				}
				if(*cp++ != ' ') {
					fprintf(stderr, CGMES, linebuf);
					exit(2);
				}
				rep->re1 = p;
				p = text(rep->re1);
				break;

			case 'd':
				rep->command = DCOM;
				break;

			case 'D':
				rep->command = CDCOM;
				rep->lb1 = ptrspace;
				break;

			case 'q':
				rep->command = QCOM;
				if(rep->ad2) {
					fprintf(stderr, AD1MES, linebuf);
					exit(2);
				}
				break;

			case 'l':
				rep->command = LCOM;
				break;

			case 's':
				rep->command = SCOM;
				seof = *cp++;
				rep->re1 = p;
				p = compile(rep->re1);
				if(p == badp) {
					fprintf(stderr, CGMES, linebuf);
					exit(2);
				}
				if(p == rep->re1) {
D 2
					rep->re1 = op;
E 2
I 2
					if(op)
					    rep->re1 = op;
					else {
					    fprintf(stderr, 
						"First RE may not be null\n");
					    exit(2);
					}
E 2
				} else {
					op = rep->re1;
				}

				if((rep->rhs = p) > reend) {
					fprintf(stderr, TMMES, linebuf);
					exit(2);
				}

				if((p = compsub(rep->rhs)) == badp) {
					fprintf(stderr, CGMES, linebuf);
					exit(2);
				}
				if(*cp == 'g') {
					cp++;
					rep->gfl++;
				} else if(gflag)
					rep->gfl++;

				if(*cp == 'p') {
					cp++;
					rep->pfl = 1;
				}

				if(*cp == 'P') {
					cp++;
					rep->pfl = 2;
				}

				if(*cp == 'w') {
					cp++;
					if(*cp++ !=  ' ') {
						fprintf(stderr, CGMES, linebuf);
						exit(2);
					}
D 3
					if(nfiles >= 10) {
E 3
I 3
					if(nfiles > 10) {
E 3
						fprintf(stderr, "Too many files in w commands\n");
						exit(2);
					}

D 4
					text(fname[nfiles]);
E 4
I 4
					text(fbuf);
					fname[nfiles] = newstr(fbuf);
E 4
					for(i = nfiles - 1; i >= 0; i--)
						if(cmp(fname[nfiles],fname[i]) == 0) {
							rep->fcode = fcode[i];
							goto done;
						}
					if((rep->fcode = fopen(fname[nfiles], "w")) == NULL) {
						fprintf(stderr, "cannot open %s\n", fname[nfiles]);
						exit(2);
					}
					fcode[nfiles++] = rep->fcode;
				}
				break;

			case 'w':
				rep->command = WCOM;
				if(*cp++ != ' ') {
					fprintf(stderr, CGMES, linebuf);
					exit(2);
				}
D 3
				if(nfiles >= 10){
E 3
I 3
				if(nfiles > 10){
E 3
					fprintf(stderr, "Too many files in w commands\n");
					exit(2);
				}

D 4
				text(fname[nfiles]);
E 4
I 4
				text(fbuf);
				fname[nfiles] = newstr(fbuf);
E 4
				for(i = nfiles - 1; i >= 0; i--)
					if(cmp(fname[nfiles], fname[i]) == 0) {
						rep->fcode = fcode[i];
						goto done;
					}

				if((rep->fcode = fopen(fname[nfiles], "w")) == NULL) {
					fprintf(stderr, "Cannot create %s\n", fname[nfiles]);
					exit(2);
				}
				fcode[nfiles++] = rep->fcode;
				break;

			case 'x':
				rep->command = XCOM;
				break;

			case 'y':
				rep->command = YCOM;
				seof = *cp++;
				rep->re1 = p;
				p = ycomp(rep->re1);
				if(p == badp) {
					fprintf(stderr, CGMES, linebuf);
					exit(2);
				}
				if(p > reend) {
					fprintf(stderr, TMMES, linebuf);
					exit(2);
				}
				break;

		}
done:
		if(++rep >= ptrend) {
			fprintf(stderr, "Too many commands, last: %s\n", linebuf);
			exit(2);
		}

		rep->ad1 = p;

		if(*cp++ != '\0') {
			if(cp[-1] == ';')
				goto comploop;
			fprintf(stderr, CGMES, linebuf);
			exit(2);
		}

	}
	rep->command = 0;
	lastre = op;
}
char	*compsub(rhsbuf)
char	*rhsbuf;
{
	register char	*p, *q;

	p = rhsbuf;
	q = cp;
	for(;;) {
		if((*p = *q++) == '\\') {
			*p = *q++;
			if(*p > numbra + '0' && *p <= '9')
				return(badp);
			*p++ |= 0200;
			continue;
		}
		if(*p == seof) {
			*p++ = '\0';
			cp = q;
			return(p);
		}
		if(*p++ == '\0') {
			return(badp);
		}

	}
}

char *compile(expbuf)
char	*expbuf;
{
	register c;
	register char *ep, *sp;
	char	neg;
	char *lastep, *cstart;
	int cclcnt;
	int	closed;
	char	bracket[NBRA], *bracketp;

	if(*cp == seof) {
		cp++;
		return(expbuf);
	}

	ep = expbuf;
	lastep = 0;
	bracketp = bracket;
	closed = numbra = 0;
	sp = cp;
	if (*sp == '^') {
		*ep++ = 1;
		sp++;
	} else {
		*ep++ = 0;
	}
	for (;;) {
		if (ep >= &expbuf[ESIZE]) {
			cp = sp;
			return(badp);
		}
		if((c = *sp++) == seof) {
			if(bracketp != bracket) {
				cp = sp;
				return(badp);
			}
			cp = sp;
			*ep++ = CEOF;
			return(ep);
		}
		if(c != '*')
			lastep = ep;
		switch (c) {

		case '\\':
			if((c = *sp++) == '(') {
				if(numbra >= NBRA) {
					cp = sp;
					return(badp);
				}
				*bracketp++ = numbra;
				*ep++ = CBRA;
				*ep++ = numbra++;
				continue;
			}
			if(c == ')') {
				if(bracketp <= bracket) {
					cp = sp;
					return(badp);
				}
				*ep++ = CKET;
				*ep++ = *--bracketp;
				closed++;
				continue;
			}

			if(c >= '1' && c <= '9') {
				if((c -= '1') >= closed)
					return(badp);
	
				*ep++ = CBACK;
				*ep++ = c;
				continue;
			}
			if(c == '\n') {
				cp = sp;
				return(badp);
			}
			if(c == 'n') {
				c = '\n';
			}
			goto defchar;

		case '\0':
			continue;
		case '\n':
			cp = sp;
			return(badp);

		case '.':
			*ep++ = CDOT;
			continue;

		case '*':
			if (lastep == 0)
				goto defchar;
			if(*lastep == CKET) {
				cp = sp;
				return(badp);
			}
			*lastep |= STAR;
			continue;

		case '$':
			if (*sp != seof)
				goto defchar;
			*ep++ = CDOL;
			continue;

		case '[':
			if(&ep[17] >= &expbuf[ESIZE]) {
				fprintf(stderr, "RE too long: %s\n", linebuf);
				exit(2);
			}

			*ep++ = CCL;

			neg = 0;
			if((c = *sp++) == '^') {
				neg = 1;
				c = *sp++;
			}

			cstart = sp;
			do {
				if(c == '\0') {
					fprintf(stderr, CGMES, linebuf);
					exit(2);
				}
				if (c=='-' && sp>cstart && *sp!=']') {
					for (c = sp[-2]; c<*sp; c++)
						ep[c>>3] |= bittab[c&07];
				}
				if(c == '\\') {
					switch(c = *sp++) {
						case 'n':
							c = '\n';
							break;
					}
				}

				ep[c >> 3] |= bittab[c & 07];
			} while((c = *sp++) != ']');

			if(neg)
				for(cclcnt = 0; cclcnt < 16; cclcnt++)
					ep[cclcnt] ^= -1;
			ep[0] &= 0376;

			ep += 16;

			continue;

		defchar:
		default:
			*ep++ = CCHR;
			*ep++ = c;
		}
	}
}
rline(lbuf)
char	*lbuf;
{
	register char	*p, *q;
	register	t;
	static char	*saveq;

	p = lbuf - 1;

	if(eflag) {
		if(eflag > 0) {
			eflag = -1;
			if(eargc-- <= 0)
				exit(2);
			q = *++eargv;
			while(*++p = *q++) {
				if(*p == '\\') {
					if((*++p = *q++) == '\0') {
						saveq = 0;
						return(-1);
					} else
						continue;
				}
				if(*p == '\n') {
					*p = '\0';
					saveq = q;
					return(1);
				}
			}
			saveq = 0;
			return(1);
		}
		if((q = saveq) == 0)	return(-1);

		while(*++p = *q++) {
			if(*p == '\\') {
				if((*++p = *q++) == '0') {
					saveq = 0;
					return(-1);
				} else
					continue;
			}
			if(*p == '\n') {
				*p = '\0';
				saveq = q;
				return(1);
			}
		}
		saveq = 0;
		return(1);
	}

	while((t = getc(fin)) != EOF) {
		*++p = t;
		if(*p == '\\') {
			t = getc(fin);
			*++p = t;
		}
		else if(*p == '\n') {
			*p = '\0';
			return(1);
		}
	}
	*++p = '\0';
	return(-1);
}

char	*address(expbuf)
char	*expbuf;
{
	register char	*rcp;
	long	lno;

	if(*cp == '$') {
		cp++;
		*expbuf++ = CEND;
		*expbuf++ = CEOF;
		return(expbuf);
	}

	if(*cp == '/') {
		seof = '/';
		cp++;
		return(compile(expbuf));
	}

	rcp = cp;
	lno = 0;

	while(*rcp >= '0' && *rcp <= '9')
		lno = lno*10 + *rcp++ - '0';

	if(rcp > cp) {
		*expbuf++ = CLNUM;
		*expbuf++ = nlno;
		tlno[nlno++] = lno;
		if(nlno >= NLINES) {
			fprintf(stderr, "Too many line numbers\n");
			exit(2);
		}
		*expbuf++ = CEOF;
		cp = rcp;
		return(expbuf);
	}
	return(0);
}
cmp(a, b)
char	*a,*b;
{
	register char	*ra, *rb;

	ra = a - 1;
	rb = b - 1;

	while(*++ra == *++rb)
		if(*ra == '\0')	return(0);
	return(1);
}

char	*text(textbuf)
char	*textbuf;
{
	register char	*p, *q;

	p = textbuf;
	q = cp;
	while(*q == '\t' || *q == ' ')	q++;
	for(;;) {

		if((*p = *q++) == '\\')
			*p = *q++;
		if(*p == '\0') {
			cp = --q;
			return(++p);
		}
		if(*p == '\n') {
			while(*q == '\t' || *q == ' ')	q++;
		}
		p++;
	}
}


struct label	*search(ptr)
struct label	*ptr;
{
	struct label	*rp;

	rp = labtab;
	while(rp < ptr) {
		if(cmp(rp->asc, ptr->asc) == 0)
			return(rp);
		rp++;
	}

	return(0);
}


dechain()
{
	struct label	*lptr;
D 5
	union reptr	*rptr, *trptr;
E 5
I 5
	struct reptr	*rptr, *trptr;
E 5

	for(lptr = labtab; lptr < lab; lptr++) {

		if(lptr->address == 0) {
			fprintf(stderr, "Undefined label: %s\n", lptr->asc);
			exit(2);
		}

		if(lptr->chain) {
			rptr = lptr->chain;
			while(trptr = rptr->lb1) {
				rptr->lb1 = lptr->address;
				rptr = trptr;
			}
			rptr->lb1 = lptr->address;
		}
	}
}

char *ycomp(expbuf)
char	*expbuf;
{
	register char	c, *ep, *tsp;
	char	*sp;

	ep = expbuf;
	sp = cp;
	for(tsp = cp; *tsp != seof; tsp++) {
		if(*tsp == '\\')
			tsp++;
		if(*tsp == '\n')
			return(badp);
	}
	tsp++;

	while((c = *sp++ & 0177) != seof) {
		if(c == '\\' && *sp == 'n') {
			sp++;
			c = '\n';
		}
		if((ep[c] = *tsp++) == '\\' && *tsp == 'n') {
			ep[c] = '\n';
			tsp++;
		}
		if(ep[c] == seof || ep[c] == '\0')
			return(badp);
	}
	if(*tsp != seof)
		return(badp);
	cp = ++tsp;

	for(c = 0; !(c & 0200); c++)
		if(ep[c] == 0)
			ep[c] = c;

	return(ep + 0200);
I 4
}

D 6
static char *
E 6
I 6
char *
E 6
newstr(buf)
	char	*buf;
{
	char	*new, *malloc(), *strcpy();

	if (!(new = malloc((u_int)(strlen(buf) + 1)))) {
		fputs("sed: out of memory.\n", stderr);
		exit(2);
	}
	return(strcpy(new, buf));
E 4
}
E 1
