h21315
s 00082/00082/00172
d D 7.5 90/05/03 17:47:40 sklower 5 4
c first crack at torek changes, may need bug fixes
e
s 00015/00009/00239
d D 7.4 86/12/15 20:26:47 sam 4 3
c lint
e
s 00003/00001/00245
d D 7.3 86/11/23 13:36:02 sam 3 2
c move machine dependencies to ../machine/kdbparam.h
e
s 00016/00033/00230
d D 7.2 86/11/20 14:43:55 sam 2 1
c pitch floating point formats; fix expr=[cCbb1] handling
e
s 00263/00000/00000
d D 7.1 86/11/20 12:22:03 sam 1 0
c date and time created 86/11/20 12:22:03 by sam
e
u
U
t
T
I 1
D 4
/*	%M%	%I%	%E%	*/
E 4
I 4
/*
 * Copyright (c) 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	%W% (Berkeley) %G%
 */
E 4

#include "../kdb/defs.h"

D 5
char	*BADMOD;
char	*ADWRAP;
E 5
I 5
char	*kdbBADMOD;
char	*kdbADWRAP;
E 5

D 5
char	*lp;
char	lastc,peekc;
long	expv;
E 5
I 5
char	*kdblp;
char	kdblastc,kdbpeekc;
long	kdbexpv;
E 5

D 5
scanform(icount,ifp,itype,ptype)
E 5
I 5
kdbscanform(icount,ifp,itype,ptype)
E 5
	long icount;
	char *ifp;
{
	register char *fp;
	char modifier;
	register fcount, init=1;
	long savdot;
	int exact;

	while (icount) {
		fp=ifp;
D 5
		savdot=dot; init=0;
		if (!init && (exact=(findsym(dot,ptype)==0)) && maxoff)
			printf("\n%s:%16t",cursym->n_un.n_name);
E 5
I 5
		savdot=kdbdot; init=0;
		if (!init && (exact=(kdbfindsym(kdbdot,ptype)==0)) && kdbmaxoff)
			kdbprintf("\n%s:%16t",kdbcursym->n_un.n_name);
E 5
		/*now loop over format*/
D 5
		while (*fp && errflg==0) {
E 5
I 5
		while (*fp && kdberrflg==0) {
E 5
			if (isdigit(modifier = *fp)) {
				fcount = 0;
				while (isdigit(modifier = *fp++)) {
				   fcount *= 10;
				   fcount += modifier-'0';
				}
				fp--;
			} else
				fcount = 1;
			if (*fp==0)
				break;
I 3
#ifdef	ENTRYMASK
E 3
			/* check for entry mask */
D 5
			if (exact && dot==savdot && 
			   (cursym->n_type&N_TYPE)==N_TEXT &&
			   cursym->n_un.n_name[0]=='_' && *fp=='i') {
D 4
				exform(1,"x",itype,ptype);
E 4
I 4
				(void) exform(1,"x",itype,ptype);
E 5
I 5
			if (exact && kdbdot==savdot && 
			   (kdbcursym->n_type&N_TYPE)==N_TEXT &&
			   kdbcursym->n_un.n_name[0]=='_' && *fp=='i') {
				(void) kdbexform(1,"x",itype,ptype);
E 5
E 4
				fp++;
D 5
				printc(EOR);
E 5
I 5
				kdbprintc(EOR);
E 5
			} else
I 3
#endif
E 3
D 4
				fp=exform(fcount,fp,itype,ptype);
E 4
I 4
D 5
				fp = exform(fcount,fp,itype,ptype);
E 5
I 5
				fp = kdbexform(fcount,fp,itype,ptype);
E 5
E 4
		}
D 5
		dotinc=dot-savdot;
		dot=savdot;
E 5
I 5
		kdbdotinc=kdbdot-savdot;
		kdbdot=savdot;
E 5

D 5
		if (errflg) {
E 5
I 5
		if (kdberrflg) {
E 5
			if (icount<0) {
D 5
				 errflg=0;
E 5
I 5
				 kdberrflg=0;
E 5
				 break;
			}
D 5
			error(errflg);
E 5
I 5
			kdberror(kdberrflg);
E 5
		}
		if (--icount)
D 5
			dot=inkdot(dotinc);
		if (mkfault)
D 4
			error(0);
E 4
I 4
			error((char *)0);
E 5
I 5
			kdbdot=kdbinkdot(kdbdotinc);
		if (kdbmkfault)
			kdberror((char *)0);
E 5
E 4
	}
}

/*
 * Execute single format item `fcount' times
 * sets `dotinc' and moves `dot'
 * returns address of next format item
 */
char *
D 5
exform(fcount,ifp,itype,ptype)
E 5
I 5
kdbexform(fcount,ifp,itype,ptype)
E 5
	int fcount;
	char *ifp;
{
	register POS w;
	register long savdot, wx;
	register char *fp;
	char c, modifier, longpr;
D 2
	union{	/* compatible with both VAX and TAHOE */
		double	d;
		int	s[4];
	} fw;
E 2

	while (fcount>0) {
	  	fp = ifp; c = *fp;
D 2
		longpr=(c>='A')&&(c<='Z')||(c=='f')||(c=='4')||(c=='p');
		if (itype==NSP || *fp=='a') {
			wx=dot; w=dot;
E 2
I 2
		longpr = (isupper(c) || c=='f' || c=='4' || c=='p');
		if (itype != NSP && *fp != 'a') {
D 5
			wx = get(dot, itype);
E 5
I 5
			wx = kdbget(kdbdot, itype);
E 5
			w = shorten(wx);
E 2
		} else {
D 2
			wx=get(dot,itype);
			w=shorten(wx);
E 2
I 2
D 5
			wx = w = dot;
E 5
I 5
			wx = w = kdbdot;
E 5
			if (itype == NSP &&
			    (c == 'b' || c == 'B' ||
			     c == 'c' || c == 'C' || c == '1'))
				w = btol(wx);
E 2
		}
D 5
		if (errflg)
E 5
I 5
		if (kdberrflg)
E 5
			return (fp);
D 5
		if (mkfault)
D 4
			error(0);
E 4
I 4
			error((char *)0);
E 4
D 2
		var[0]=wx;
E 2
I 2
		var[0] = wx;
E 5
I 5
		if (kdbmkfault)
			kdberror((char *)0);
		kdbvar[0] = wx;
E 5
E 2
		modifier = *fp++;
D 2
		dotinc=(longpr?4:2);
E 2
I 2
D 5
		dotinc = (longpr ? sizeof (long):sizeof (short));
E 5
I 5
		kdbdotinc = (longpr ? sizeof (long):sizeof (short));
E 5
E 2

D 5
		if (charpos()==0 && modifier!='a')
			printf("%16m");
E 5
I 5
		if (kdbcharpos()==0 && modifier!='a')
			kdbprintf("%16m");
E 5
		switch (modifier) {

		case SP: case TB:
			break;

		case 't': case 'T':
D 5
			printf("%T",fcount); return (fp);
E 5
I 5
			kdbprintf("%T",fcount); return (fp);
E 5

		case 'r': case 'R':
D 5
			printf("%M",fcount); return (fp);
E 5
I 5
			kdbprintf("%M",fcount); return (fp);
E 5

		case 'a':
D 5
			psymoff(dot,ptype,":%16t"); dotinc=0; break;
E 5
I 5
			kdbpsymoff(kdbdot,ptype,":%16t"); kdbdotinc=0; break;
E 5

		case 'p':
D 5
			psymoff(var[0],ptype,"%16t"); break;
E 5
I 5
			kdbpsymoff(kdbvar[0],ptype,"%16t"); break;
E 5

		case 'u':
D 5
			printf("%-8u",w); break;
E 5
I 5
			kdbprintf("%-8u",w); break;
E 5

		case 'U':
D 5
			printf("%-16U",wx); break;
E 5
I 5
			kdbprintf("%-16U",wx); break;
E 5

		case 'c': case 'C':
D 2
			if (modifier=='C')
				printesc(byte(wx));
E 2
I 2
			if (modifier == 'C')
D 4
				printesc(byte(w));
E 4
I 4
D 5
				printesc((int)byte(w));
E 5
I 5
				kdbprintesc((int)byte(w));
E 5
E 4
E 2
			else
D 2
				printc(byte(wx));
E 2
I 2
D 4
				printc(byte(w));
E 4
I 4
D 5
				printc((char)byte(w));
E 4
E 2
			dotinc=1; break;
E 5
I 5
				kdbprintc((char)byte(w));
			kdbdotinc=1; break;
E 5

		case 'b': case 'B':
D 2
			printf("%-8o", byte(wx)); dotinc=1; break;
E 2
I 2
D 5
			printf("%-8o", byte(w)); dotinc=1; break;
E 5
I 5
			kdbprintf("%-8o", byte(w)); kdbdotinc=1; break;
E 5
E 2

		case '1':
D 2
			printf("%-8R", byte(wx)); dotinc=1; break;
E 2
I 2
D 5
			printf("%-8R", byte(w)); dotinc=1; break;
E 5
I 5
			kdbprintf("%-8R", byte(w)); kdbdotinc=1; break;
E 5
E 2

		case 'w': case '2':
D 5
			printf("%-8R", w); break;
E 5
I 5
			kdbprintf("%-8R", w); break;
E 5

		case 'W': case '4':
D 5
			printf("%-16R", wx); break;
E 5
I 5
			kdbprintf("%-16R", wx); break;
E 5

		case 's': case 'S':
D 5
			savdot=dot; dotinc=1;
			while ((c=byte(get(dot,itype))) && errflg==0) {
				dot=inkdot(1);
E 5
I 5
			savdot=kdbdot; kdbdotinc=1;
			while ((c=byte(kdbget(kdbdot,itype))) && kdberrflg==0) {
				kdbdot=kdbinkdot(1);
E 5
				if (modifier == 'S')
D 4
					printesc(c);
E 4
I 4
D 5
					printesc((int)c);
E 5
I 5
					kdbprintesc((int)c);
E 5
E 4
				else
D 5
					printc(c);
				endline();
E 5
I 5
					kdbprintc(c);
				kdbendline();
E 5
			}
D 5
			dotinc=dot-savdot+1; dot=savdot; break;
E 5
I 5
			kdbdotinc=kdbdot-savdot+1; kdbdot=savdot; break;
E 5

		case 'x':
D 5
			printf("%-8x",w); break;
E 5
I 5
			kdbprintf("%-8x",w); break;
E 5

		case 'X':
D 5
			printf("%-16X", wx); break;
E 5
I 5
			kdbprintf("%-16X", wx); break;
E 5

		case 'z':
D 5
			printf("%-8z",w); break;
E 5
I 5
			kdbprintf("%-8z",w); break;
E 5

		case 'Z':
D 5
			printf("%-16Z", wx); break;
E 5
I 5
			kdbprintf("%-16Z", wx); break;
E 5

		case 'Y':
D 5
			printf("%-24Y", wx); break;
E 5
I 5
			kdbprintf("%-24Y", wx); break;
E 5

		case 'q':
D 5
			printf("%-8q", w); break;
E 5
I 5
			kdbprintf("%-8q", w); break;
E 5

		case 'Q':
D 5
			printf("%-16Q", wx); break;
E 5
I 5
			kdbprintf("%-16Q", wx); break;
E 5

		case 'o':
D 5
			printf("%-8o", w); break;
E 5
I 5
			kdbprintf("%-8o", w); break;
E 5

		case 'O':
D 5
			printf("%-16O", wx); break;
E 5
I 5
			kdbprintf("%-16O", wx); break;
E 5

		case 'i': case 'I':
D 5
			printins(itype,wx); printc(EOR); break;
E 5
I 5
			kdbprintins(itype,wx); kdbprintc(EOR); break;
E 5

		case 'd':
D 5
			printf("%-8d", w); break;
E 5
I 5
			kdbprintf("%-8d", w); break;
E 5

		case 'D':
D 5
			printf("%-16D", wx); break;
E 5
I 5
			kdbprintf("%-16D", wx); break;
E 5
D 2

		case 'f':
			fw.d = 0;
			fw.s[0] = w;
			fw.s[1] = wx&0xffff;
			printf("%-16.9f", fw.d);
			dotinc=4; break;

		case 'F':	/* may be done with one get call on TAHOE */
			fw.s[0] = w;
			fw.s[1] = wx&0xffff;
			fw.s[2]=shorten(get(inkdot(4),itype));
			fw.s[3]=shorten(get(inkdot(6),itype));
			if (errflg)
				return (fp);
			printf("%-32.18F", fw.d);
			dotinc=8; break;
E 2

		case 'n': case 'N':
D 5
			printc('\n'); dotinc=0; break;
E 5
I 5
			kdbprintc('\n'); kdbdotinc=0; break;
E 5

		case '"':
D 5
			dotinc=0;
E 5
I 5
			kdbdotinc=0;
E 5
			while (*fp != '"' && *fp)
D 5
				printc(*fp++);
E 5
I 5
				kdbprintc(*fp++);
E 5
			if (*fp)
				fp++;
			break;

		case '^':
D 5
			dot=inkdot(-dotinc*fcount); return (fp);
E 5
I 5
			kdbdot=kdbinkdot(-kdbdotinc*fcount); return (fp);
E 5

		case '+':
D 5
			dot=inkdot(fcount); return (fp);
E 5
I 5
			kdbdot=kdbinkdot(fcount); return (fp);
E 5

		case '-':
D 5
			dot=inkdot(-fcount); return (fp);
E 5
I 5
			kdbdot=kdbinkdot(-fcount); return (fp);
E 5

		default:
D 5
			error(BADMOD);
E 5
I 5
			kdberror(kdbBADMOD);
E 5
		}
		if (itype!=NSP)
D 5
			dot=inkdot(dotinc);
		fcount--; endline();
E 5
I 5
			kdbdot=kdbinkdot(kdbdotinc);
		fcount--; kdbendline();
E 5
	}
	return (fp);
}

static
D 5
printesc(c)
E 5
I 5
kdbprintesc(c)
E 5
D 4
	register c;
E 4
I 4
	register int c;
E 4
{

	c &= STRIP;
	if (c==0177 || c<SP)
D 5
		printf("^%c", c ^ 0100);
E 5
I 5
		kdbprintf("^%c", c ^ 0100);
E 5
	else
D 5
		printc(c);
E 5
I 5
		kdbprintc(c);
E 5
}

long
D 5
inkdot(incr)
E 5
I 5
kdbinkdot(incr)
E 5
{
	register long newdot;

D 5
	newdot=dot+incr;
D 3
	if ((dot ^ newdot) >> 24)
E 3
I 3
	if (addrwrap(dot, newdot))
E 3
		error(ADWRAP);
E 5
I 5
	newdot=kdbdot+incr;
	if (addrwrap(kdbdot, newdot))
		kdberror(kdbADWRAP);
E 5
	return (newdot);
}
E 1
