h48187
s 00005/00048/00310
d D 2.2 93/07/27 09:15:38 bostic 3 2
c checkpoint; Mike Karels left this checked out.
e
s 00109/00100/00249
d D 2.1 85/07/18 14:22:13 jaap 2 1
c Edition 8 Version of troff (May 1985), (Dennis did the caching). 
c Local hacks from jaap.
e
s 00349/00000/00000
d D 1.1 85/07/17 17:54:19 jaap 1 0
c date and time created 85/07/17 17:54:19 by jaap
e
u
U
t
T
I 1
#ifndef lint
D 3
static char sccsid[] = "%W% (CWI) %E%";
E 3
I 3
/*
static char sccsid[] = "@(#)n2.c	2.1 (CWI) 85/07/18";
*/
static char sccsid[] = "%W% (Berkeley) %G%";
E 3
#endif lint
I 2
/*
 * n2.c
 *
 * output, cleanup
 */
E 2

#include "tdef.h"
#include <sgtty.h>
D 2
extern
#include "d.h"
extern
#include "v.h"
E 2
I 2
#include <signal.h>
E 2
#ifdef NROFF
D 2
extern
E 2
#include "tw.h"
#endif
D 2
#include "s.h"
E 2
#include <setjmp.h>
D 2

/*
troff2.c

output, cleanup
*/

E 2
#include "ext.h"
D 2
extern jmp_buf	sjbuf;
E 2
I 2

extern	jmp_buf	sjbuf;
E 2
int	toolate;
int	error;

pchar(i)
D 2
tchar i;
E 2
I 2
	register tchar i;
E 2
{
D 2
	int j;
E 2
I 2
	register int j;
E 2
	static int hx = 0;	/* records if have seen HX */

	if (hx) {
		hx = 0;
		j = absmot(i);
		if (isnmot(i)) {
			if (j > dip->blss)
				dip->blss = j;
		} else {
			if (j > dip->alss)
				dip->alss = j;
			ralss = dip->alss;
		}
		return;
	}
	if (ismot(i)) {
		pchar1(i); 
		return;
	}
	switch (j = cbits(i)) {
	case 0:
	case IMP:
	case RIGHT:
	case LEFT:
		return;
	case HX:
		hx = 1;
		return;
	case PRESC:
		if (dip == &d[0])
			j = eschar;	/* fall through */
	default:
		setcbits(i, trtab[j]);
	}
	pchar1(i);
}


pchar1(i)
D 2
tchar i;
E 2
I 2
	register tchar i;
E 2
{
D 2
	register j, *k;
	static int seendraw;
E 2
I 2
	register j;
E 2

	j = cbits(i);
	if (dip != &d[0]) {
		wbf(i);
		dip->op = offset;
		return;
	}
	if (!tflg && !print) {
		if (j == '\n')
			dip->alss = dip->blss = 0;
		return;
	}
	if (no_out || j == FILLER)
		return;
	if (tflg) {	/* transparent mode, undiverted */
D 2
		fprintf(ptid, "%c", j);
E 2
I 2
		fdprintf(ptid, "%c", j);
E 2
		return;
	}
#ifndef NROFF
D 2
	if (ascii) {
		if (ismot(i)) {
			if(!seendraw) {
				oput(' ');
E 2
I 2
	if (ascii)
		outascii(i);
	else
#endif
		ptout(i);
}

outascii(i)	/* print i in best-guess ascii */
	tchar i;
{
	static int seendraw;
	int j = cbits(i);

	if (ismot(i)) {
		if(!seendraw) {
			oput(' ');
		}
		return;
	}
	if (j < 0177 && j >= 040) {
		if(!seendraw) {
			oput(j);
			return;
		} else {
			switch(j) {
				case DRAWCIRCLE: oputs("CIRCLE ");
					break;
				case DRAWELLIPSE: oputs("ELLIPSE ");
					break;
				case DRAWLINE: oputs("LINE ");
					break;
				case DRAWSPLINE: oputs("SPLINE ");
					break;
				case DRAWARC: oputs("ARC ");
					break;
				case '.':oputs(".");
					/*
					if(seendraw == 2)
						seendraw = 0;
					else
						seendraw++;
					*/
					break;
				default: oputs("UNKNOWN "); flusho();
					errprint("Unknown 0%o %c function", j,j);
					break;
E 2
			}
			return;
		}
D 2
		if (j < 0177 && j >= 040) {
			if(!seendraw) {
				oput(j);
E 2
I 2
	}
	if( j < 040) {
		switch(j) {
			case SLANT:
			case CHARHT:
			case WORDSP:
			case HX:
E 2
				return;
D 2
			} else {
				switch(j) {
					case DRAWCIRCLE: oputs("CIRCLE");
						break;
					case DRAWELLIPSE: oputs("ELLIPSE");
						break;
					case DRAWLINE: oputs("LINE");
						break;
					case DRAWWIG: oputs("SPLINE");
						break;
					case DRAWARC: oputs("ARC");
						break;
					case '.':
						if(seendraw == 2)
							seendraw = 0;
						else
							seendraw++;
						break;
					default: oputs("UNKNOWN");
						break;
E 2
I 2
			case DRAWFCN:
				if(seendraw == 1){
					seendraw = 0;
				} else {
					oputs("DRAWFUNCTION ");flusho();
					seendraw++;
E 2
				}
I 2
				/*
				errprint("Seendraw %d", seendraw);
				*/
E 2
				return;
D 2
			}
E 2
I 2
			case '\n':
				oput(j);
				return;
			default:
				errprint("Unknown (2) 0%o function", j);
				return;
E 2
		}
D 2
		if( j < 040) {
			switch(j) {
				case SLANT:
				case CHARHT:
				case WORDSP:
				case HX:
				case FONTPOS:	/* creeps in as well */
					return;
				case DRAWFCN:
					seendraw++;
					oputs("DRAWFUNCTION ");
					return;
				case '\n':
					oput(j);
					return;
				default:
					fprintf(stderr,"Unknown 0%o function\n",
								j);
					return;
			}
		}
					
		if (j == HYPHEN || j == MINUS)
			oput('-');
		else if (j == LIG_FI)
			oputs("fi");
		else if (j == LIG_FL)
			oputs("fl");
		else if (j == LIG_FF)
			oputs("ff");
		else if (j == LIG_FFI)
			oputs("ffi");
		else if (j == LIG_FFL)
			oputs("ffl");
		else if (j == NARSP || j == HNARSP || j == WORDSP)
			;	/* nothing at all */
		else {
			oput('\\');
			oput('(');
			oput(chname[chtab[j-128]]);
			oput(chname[chtab[j-128]+1]);
		}
	} else
#endif
		ptout(i);
E 2
I 2
	}
	if (j == HYPHEN || j == MINUS)
		oput('-');
	else if (j == LIG_FI)
		oputs("fi");
	else if (j == LIG_FL)
		oputs("fl");
	else if (j == LIG_FF)
		oputs("ff");
	else if (j == LIG_FFI)
		oputs("ffi");
	else if (j == LIG_FFL)
		oputs("ffl");
	else {
		oput('\\');
		oput('(');
		oput(chname[chtab[j-128]]);
		oput(chname[chtab[j-128]+1]);
	}
E 2
}

D 3

I 2
/*
 * now a macro
E 2
oput(i)
D 2
char	i;
E 2
I 2
	register int	i;
E 2
{
	*obufp++ = i;
	if (obufp >= &obuf[OBUFSZ])
		flusho();
}
I 2
*/
E 2

E 3
D 2

E 2
oputs(i)
register char	*i;
{
	while (*i != 0)
		oput(*i++);
}

D 3

flusho()
{
	if (obufp == obuf)
		return;
	if (no_out == 0) {
		if (!toolate) {
			toolate++;
#ifdef NROFF
			if (t.bset || t.breset) {
				if (ttysave == -1) {
					gtty(1, &ttys);
					ttysave = ttys.sg_flags;
				}
				ttys.sg_flags &= ~t.breset;
				ttys.sg_flags |= t.bset;
				stty(1, &ttys);
			}
			 {
				char	*p = t.twinit;
				while (*p++)
					;
D 2
				write(ptid, t.twinit, p - t.twinit - 1);
E 2
I 2
				if (p - t.twinit > 1)
					write(ptid, t.twinit, p - t.twinit - 1);
E 2
			}
#endif
		}
		toolate += write(ptid, obuf, obufp - obuf);
	}
	obufp = obuf;
}


E 3
done(x) 
int	x;
{
	register i;

	error |= x;
D 2
	level = 0;
E 2
	app = ds = lgf = 0;
	if (i = em) {
		donef = -1;
		em = 0;
		if (control(i, 0))
			longjmp(sjbuf, 1);
	}
	if (!nfo)
		done3(0);
	mflg = 0;
	dip = &d[0];
	if (woff)
		wbt((tchar)0);
	if (pendw)
		getword(1);
	pendnf = 0;
	if (donef == 1)
		done1(0);
	donef = 1;
	ip = 0;
	frame = stk;
	nxf = frame + 1;
	if (!ejf)
		tbreak();
	nflush++;
	eject((struct s *)0);
	longjmp(sjbuf, 1);
}


done1(x) 
int	x; 
{
	error |= x;
D 2
	if (v.nl) {
E 2
I 2
	if (numtab[NL].val) {
E 2
		trap = 0;
		eject((struct s *)0);
		longjmp(sjbuf, 1);
	}
	if (nofeed) {
		ptlead();
		flusho();
		done3(0);
	} else {
		if (!gflag)
			pttrailer();
		done2(0);
	}
}


done2(x) 
int	x; 
{
	ptlead();
#ifndef NROFF
	if (!ascii)
		ptstop();
#endif
	flusho();
	done3(x);
}

done3(x) 
int	x;
{
	error |= x;
	signal(SIGINT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
D 3
	unlink(unlkp);
E 3
#ifdef NROFF
	twdone();
#endif
	if (quiet) {
		ttys.sg_flags |= ECHO;
		stty(0, &ttys);
	}
	if (ascii)
		mesg(1);
	exit(error);
}


edone(x) 
int	x;
{
	frame = stk;
	nxf = frame + 1;
	ip = 0;
	done(x);
}



casepi()
{
	register i;
	int	id[2];

	if (toolate || skip() || !getname() || pipe(id) == -1 || (i = fork()) == -1) {
D 2
		fprintf(stderr, "Pipe not created.\n");
E 2
I 2
		errprint("Pipe not created.");
E 2
		return;
	}
D 3
	ptid = id[1];
E 3
I 3
	ptid = fdopen(id[1], "w");
E 3
	if (i > 0) {
		close(id[0]);
		toolate++;
		pipeflg++;
		return;
	}
	close(0);
	dup(id[0]);
	close(id[1]);
	execl(nextf, nextf, 0);
D 2
	fprintf(stderr, "Cannot exec %s\n", nextf);
E 2
I 2
	errprint("Cannot exec %s", nextf);
E 2
	exit(-4);
}
E 1
