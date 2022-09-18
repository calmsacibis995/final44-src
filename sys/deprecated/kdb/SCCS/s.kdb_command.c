h53115
s 00091/00091/00100
d D 7.4 90/05/03 17:47:48 sklower 4 3
c first crack at torek changes, may need bug fixes
e
s 00011/00005/00180
d D 7.3 86/12/15 20:26:44 sam 3 2
c lint
e
s 00013/00015/00172
d D 7.2 86/11/20 14:43:02 sam 2 1
c miscellaneous cleanups; don't print debugger name on blank line
e
s 00187/00000/00000
d D 7.1 86/11/20 12:22:01 sam 1 0
c date and time created 86/11/20 12:22:01 by sam
e
u
U
t
T
I 1
D 3
/*	%M%	%I%	%E%	*/
E 3
I 3
/*
 * Copyright (c) 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	%W% (Berkeley) %G%
 */
E 3

#include "../kdb/defs.h"

D 4
char	*BADEQ;
char	*NOMATCH;
char	*BADVAR;
char	*BADCOM;
E 4
I 4
char	*kdbBADEQ;
char	*kdbNOMATCH;
char	*kdbBADVAR;
char	*kdbBADCOM;
E 4

D 4
int	executing;
char	*lp;
E 4
I 4
int	kdbexecuting;
char	*kdblp;
E 4

D 4
char	lastc;
char	eqformat[512] = "z";
char	stformat[512] = "X\"= \"^i";
E 4
I 4
char	kdblastc;
char	kdbeqformat[512] = "z";
char	kdbstformat[512] = "X\"= \"^i";
E 4

D 4
long	ditto;
int	lastcom = '=';
long	locval;
long	locmsk;
long	expv;
E 4
I 4
long	kdbditto;
int	kdblastcom = '=';
long	kdblocval;
long	kdblocmsk;
long	kdbexpv;
E 4

/* command decoding */

D 4
command(buf, defcom)
E 4
I 4
kdbcommand(buf, defcom)
E 4
	char *buf, defcom;
{
	register itype, ptype, modifier, regptr;
	int longpr, eqcom;
	char wformat[1], savc;
	register long w, savdot;
D 4
	char *savlp=lp;
E 4
I 4
	char *savlp=kdblp;
E 4

	if (buf) {
		if (*buf==EOR)
D 2
			return (FALSE);
E 2
I 2
			return (0);
E 2
D 4
		lp=buf;
E 4
I 4
		kdblp=buf;
E 4
	}

	do {
D 4
		if (adrflg=expr(0)) {
			dot=expv;
			ditto=dot;
E 4
I 4
		if (kdbadrflg=kdbexpr(0)) {
			kdbdot=kdbexpv;
			kdbditto=kdbdot;
E 4
		}
D 4
		adrval=dot;
D 2
		if (rdc()==',' && expr(0))
			cntflg=TRUE, cntval=expv;
E 2
I 2
		cntflg = (rdc() == ',' && expr(0));
		if (cntflg)
			cntval=expv;
E 4
I 4
		kdbadrval=kdbdot;
		kdbcntflg = (kdbrdc() == ',' && kdbexpr(0));
		if (kdbcntflg)
			kdbcntval=kdbexpv;
E 4
E 2
		else
D 2
			cntflg=FALSE, cntval=1, lp--;
E 2
I 2
D 4
			cntval=1, lp--;
E 2
		if (eol(rdc())) {
			if (!adrflg)
				dot=inkdot(dotinc);
			lp--; lastcom=defcom;
E 4
I 4
			kdbcntval=1, kdblp--;
		if (kdbeol(kdbrdc())) {
			if (!kdbadrflg)
				kdbdot=kdbinkdot(kdbdotinc);
			kdblp--; kdblastcom=defcom;
E 4
		} else
D 4
			lastcom=lastc;
		switch (lastcom&STRIP) {
E 4
I 4
			kdblastcom=kdblastc;
		switch (kdblastcom&STRIP) {
E 4

		case '/':
			itype=DSP; ptype=DSYM;
			goto trystar;

		case '=':
			itype=NSP; ptype=0;
			goto trypr;

		case '?':
			itype=ISP; ptype=ISYM;
			goto trystar;

		trystar:
D 4
			if (rdc()=='*')
				lastcom |= QUOTE;
E 4
I 4
			if (kdbrdc()=='*')
				kdblastcom |= QUOTE;
E 4
			else
D 4
				lp--;
			if (lastcom&QUOTE) {
E 4
I 4
				kdblp--;
			if (kdblastcom&QUOTE) {
E 4
				itype |= STAR;
				ptype = (DSYM+ISYM)-ptype;
			}

		trypr:
D 2
			longpr=FALSE; eqcom=lastcom=='=';
E 2
I 2
D 4
			longpr=0; eqcom=lastcom=='=';
E 2
			switch (rdc()) {
E 4
I 4
			longpr=0; eqcom=kdblastcom=='=';
			switch (kdbrdc()) {
E 4

			case 'L':
D 2
				longpr=TRUE;
E 2
I 2
				longpr=1;
E 2
			case 'l':
				/*search for exp*/
				if (eqcom)
D 4
					error(BADEQ);
				dotinc=(longpr?4:2); savdot=dot;
D 3
				expr(1); locval=expv;
E 3
I 3
				(void) expr(1); locval=expv;
E 3
				if (expr(0))
					locmsk=expv;
E 4
I 4
					kdberror(kdbBADEQ);
				kdbdotinc=(longpr?4:2); savdot=kdbdot;
				(void) kdbexpr(1); kdblocval=kdbexpv;
				if (kdbexpr(0))
					kdblocmsk=kdbexpv;
E 4
				else
D 4
					locmsk = -1L;
E 4
I 4
					kdblocmsk = -1L;
E 4
				if (!longpr) {
D 4
					locmsk &= 0xFFFF;
					locval &= 0xFFFF;
E 4
I 4
					kdblocmsk &= 0xFFFF;
					kdblocval &= 0xFFFF;
E 4
				}
				for (;;) {
D 4
					w=get(dot,itype);
					if (errflg || mkfault ||
					    (w&locmsk)==locval)
E 4
I 4
					w=kdbget(kdbdot,itype);
					if (kdberrflg || kdbmkfault ||
					    (w&kdblocmsk)==kdblocval)
E 4
						break;
D 4
					 dot=inkdot(dotinc);
E 4
I 4
					 kdbdot=kdbinkdot(kdbdotinc);
E 4
				}
D 4
				if (errflg) {
					dot=savdot;
					errflg=NOMATCH;
E 4
I 4
				if (kdberrflg) {
					kdbdot=savdot;
					kdberrflg=kdbNOMATCH;
E 4
				}
D 4
				psymoff(dot,ptype,"");
E 4
I 4
				kdbpsymoff(kdbdot,ptype,"");
E 4
				break;

			case 'W':
D 2
				longpr=TRUE;
E 2
I 2
				longpr=1;
E 2
			case 'w':
				if (eqcom)
D 4
					error(BADEQ);
D 3
				wformat[0]=lastc; expr(1);
E 3
I 3
				wformat[0]=lastc; (void) expr(1);
E 4
I 4
					kdberror(kdbBADEQ);
				wformat[0]=kdblastc; (void) kdbexpr(1);
E 4
E 3
				do {
D 4
					savdot=dot;
					psymoff(dot,ptype,":%16t");
D 3
					exform(1,wformat,itype,ptype);
E 3
I 3
					(void) exform(1,wformat,itype,ptype);
E 3
					errflg=0; dot=savdot;
E 4
I 4
					savdot=kdbdot;
					kdbpsymoff(kdbdot,ptype,":%16t");
					(void) kdbexform(1,wformat,itype,ptype);
					kdberrflg=0; kdbdot=savdot;
E 4
					if (longpr)
D 4
						put(dot,itype,expv);
E 4
I 4
						kdbput(kdbdot,itype,kdbexpv);
E 4
					else
D 4
						put(dot,itype,
						    itol(expv,get(dot,itype)));
					savdot=dot;
					printf("=%8t");
D 3
					exform(1,wformat,itype,ptype);
E 3
I 3
					(void) exform(1,wformat,itype,ptype);
E 3
					printc(EOR);
				} while (expr(0) && errflg==0);
				dot=savdot;
				chkerr();
E 4
I 4
						kdbput(kdbdot,itype,
						    itol(kdbexpv,kdbget(kdbdot,itype)));
					savdot=kdbdot;
					kdbprintf("=%8t");
					(void) kdbexform(1,wformat,itype,ptype);
					kdbprintc(EOR);
				} while (kdbexpr(0) && kdberrflg==0);
				kdbdot=savdot;
				kdbchkerr();
E 4
				break;

			default:
D 4
				lp--;
				getformat(eqcom ? eqformat : stformat);
E 4
I 4
				kdblp--;
				kdbgetformat(eqcom ? kdbeqformat : kdbstformat);
E 4
				if (!eqcom)
D 4
					psymoff(dot,ptype,":%16t");
				scanform(cntval,
				    (eqcom?eqformat:stformat),itype,ptype);
E 4
I 4
					kdbpsymoff(kdbdot,ptype,":%16t");
				kdbscanform(kdbcntval,
				    (eqcom?kdbeqformat:kdbstformat),itype,ptype);
E 4
			}
			break;

		case '>':
D 4
			lastcom=0; savc=rdc();
			if ((regptr=getreg(savc)) != -1)
				*(int *)regptr = dot;
			else if ((modifier=varchk(savc)) != -1)
				var[modifier]=dot;
E 4
I 4
			kdblastcom=0; savc=kdbrdc();
			if ((regptr=kdbgetreg(savc)) != -1)
				*(int *)regptr = kdbdot;
			else if ((modifier=kdbvarchk(savc)) != -1)
				kdbvar[modifier]=kdbdot;
E 4
			else
D 4
				error(BADVAR);
E 4
I 4
				kdberror(kdbBADVAR);
E 4
			break;

		case '$':
D 4
			lastcom=0;
			printtrace(nextchar());
E 4
I 4
			kdblastcom=0;
			kdbprinttrace(kdbnextchar());
E 4
			break;

		case ':':
D 2
			if (!executing) {
				executing=TRUE;
				subpcs(nextchar());
				executing=FALSE;
				lastcom=0;
			}
E 2
I 2
D 4
			if (executing)
E 4
I 4
			if (kdbexecuting)
E 4
				break;
D 4
			executing=1; subpcs(nextchar()); executing=0;
			lastcom=0;
E 4
I 4
			kdbexecuting=1; kdbsubpcs(kdbnextchar()); kdbexecuting=0;
			kdblastcom=0;
E 4
E 2
			break;

D 2
		case 0:
			printf(DBNAME);
E 2
I 2
		case '\0':
E 2
			break;

		default:
D 4
			error(BADCOM);
E 4
I 4
			kdberror(kdbBADCOM);
E 4
		}
D 4
		flushbuf();
	} while (rdc()==';');
E 4
I 4
		kdbflushbuf();
	} while (kdbrdc()==';');
E 4
	if (buf)
D 4
		lp=savlp;
E 4
I 4
		kdblp=savlp;
E 4
	else
D 4
		lp--;
	return (adrflg && dot!=0);
E 4
I 4
		kdblp--;
	return (kdbadrflg && kdbdot!=0);
E 4
}
E 1
