h36133
s 00009/00002/00331
d D 4.3 91/04/18 16:49:20 bostic 3 2
c new copyright; att/bsd/shared
e
s 00001/00001/00332
d D 4.2 86/07/07 18:09:56 mckusick 2 1
c paranoia from torek
e
s 00333/00000/00000
d D 4.1 82/06/07 15:45:29 rrh 1 0
c date and time created 82/06/07 15:45:29 by rrh
e
u
U
t
T
I 3
/*-
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.proprietary.c%
 */

E 3
I 1
#ifndef lint
D 3
static char sccsid[] = "%W% %G%";
#endif lint
E 3
I 3
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 3

#include "tdef.h"
extern
#include "d.h"
extern
#include "v.h"
#ifdef NROFF
extern
#include "tw.h"
#endif
/*
troff9.c

misc functions
*/

extern int cbuf[];
extern int *cp;
extern int ch;
extern int chbits;
extern int dfact;
extern int vflag;
extern int pts;
extern int fc;
extern int padc;
extern int tabtab[];
extern int nlflg;
extern int lss;
extern int tabch, ldrch;
extern int tabc, dotc;
extern int nchar, rchar;
extern int xxx;

setz(){
	register i;

	if(!((i = getch()) & MOT))i |= ZBIT;
	return(i);
}
setline(){
	register *i, length, c;
	int w, cnt, delim, rem, temp;

	if((delim = getch()) & MOT)return;
		else delim &= CMASK;
	vflag = 0;
	dfact = EM;
	length = quant(atoi(),HOR);
	dfact = 1;
	if(!length){
		eat(delim);
		return;
	}
s0:
	if(((c = getch()) & CMASK) == delim){
		ch = c;
		c = 0204 | chbits;
	}else if((c & CMASK) == FILLER)goto s0;
	w = width(c);
	i = cbuf;
	if(length < 0){
		*i++ = makem(length);
		length = -length;
	}
	if(!(cnt = length/w)){
		*i++ = makem(-(temp = ((w-length)/2)));
		*i++ = c;
		*i++ = makem(-(w - length - temp));
		goto s1;
	}
	if(rem = length%w){
		switch(c & CMASK){
			case 0204: /*rule*/
			case 0224: /*underrule*/
			case 0276: /*root en*/
				*i++ = c | ZBIT;
			default:
				*i++ = makem(rem);
		}
	}
	if(cnt){
		*i++ = RPT;
		*i++ = cnt;
		*i++ = c;
	}
s1:
	*i++ = 0;
	eat(delim);
	cp = cbuf;
}
eat(c)
int c;
{
	register i;

	while(((i = getch() & CMASK) != c) &&
		(i != '\n'));
	return(i);
}
setov(){
	register i, j, k;
D 2
	int *p, delim, o[NOV], w[NOV];
E 2
I 2
	int *p, delim, o[NOV+1], w[NOV+1];
E 2

	if((delim = getch()) & MOT)return;
		else delim &= CMASK;
	for(k=0; (k<NOV) && ((j=(i = getch()) & CMASK) != delim) &&
		(j != '\n'); k++){
			o[k] = i;
			w[k] = width(i);
	}
	o[k] = w[k] = 0;
	if(o[0])for(j=1; j;){
		j = 0;
		for(k=1; o[k] ; k++){
			if(w[k-1] < w[k]){
				j++;
				i = w[k];
				w[k] = w[k-1];
				w[k-1] = i;
				i = o[k];
				o[k] = o[k-1];
				o[k-1] = i;
			}
		}
	}else return;
	p = cbuf;
	for(k=0; o[k]; k++){
		*p++ = o[k];
		*p++ = makem(-((w[k]+w[k+1])/2));
	}
	*p++ = makem(w[0]/2);
	*p = 0;
	cp = cbuf;
}
setbra(){
	register i, *j, k;
	int cnt, delim, dwn;

	if((delim = getch()) & MOT)return;
		else delim &= CMASK;
	j = cbuf + 1;
	cnt = 0;
#ifdef NROFF
	dwn = (2*t.Halfline) | MOT | VMOT;
#endif
#ifndef NROFF
	dwn = EM | MOT | VMOT;
#endif
	while(((k = (i = getch()) & CMASK) != delim) && (k != '\n') &&
		(j <= (cbuf+NC-4))){
		*j++ = i | ZBIT;
		*j++ = dwn;
		cnt++;
	}
	if(--cnt < 0)return;
		else if (!cnt){
			ch = *(j-2);
			return;
	}
	*j = 0;
#ifdef NROFF
	*--j = *cbuf = (cnt*t.Halfline) | MOT | NMOT | VMOT;
#endif
#ifndef NROFF
	*--j = *cbuf = (cnt*EM)/2 | MOT | NMOT | VMOT;
#endif
	*--j &= ~ZBIT;
	cp = cbuf;
}
setvline(){
	register i, c, *k;
	int cnt, neg, rem, ver, delim;

	if((delim = getch()) & MOT)return;
		else delim &= CMASK;
	dfact = lss;
	vflag++;
	i = quant(atoi(),VERT);
	dfact = 1;
	if(!i){
		eat(delim);
		vflag = 0;
		return;
	}
	if(((c = getch()) & CMASK) == delim){
		c = 0337 | chbits;	/*default box rule*/
	}else getch();
	c |= ZBIT;
	neg = 0;
	if(i < 0){
		i = -i;
		neg = NMOT;
	}
#ifdef NROFF
	ver = 2*t.Halfline;
#endif
#ifndef NROFF
	ver = EM;
#endif
	cnt = i/ver;
	rem = makem(i%ver) | neg;
	ver = makem(ver) | neg;
	k = cbuf;
	if(!neg)*k++ = ver;
	if(rem & ~MOTV){
		*k++ = c;
		*k++ = rem;
	}
	while((k < (cbuf+NC-3)) && cnt--){
		*k++ = c;
		*k++ = ver;
	}
	*(k-2) &= ~ZBIT;
	if(!neg)k--;
	*k = 0;
	cp = cbuf;
	vflag = 0;
}
casefc(){
	register i;

	fc = IMP;
	padc = ' ';
	if(skip() ||
	   ((i = getch()) & MOT) ||
	   ((i &= CMASK) == '\n'))return;
	fc = i;
	if(skip() || (ch & MOT) || ((ch &= CMASK) == fc))return;
	padc = ch;
}
setfield(x)
int x;
{
	register i, j, *fp;
	int length, ws, npad, temp, type;
	int **pp, *padptr[NPP];
	static int fbuf[FBUFSZ];
	int savfc, savtc, savlc;

	if(x == tabch) rchar = tabc | chbits;
	else if(x ==  ldrch) rchar = dotc | chbits;
	temp = npad = ws = 0;
	savfc = fc; savtc = tabch; savlc = ldrch;
	tabch = ldrch = fc = IMP;
	for(j=0;;j++){
		if((tabtab[j] & TMASK)== 0){
			if(x==savfc)prstr("Zero field width.\n");
			j = 0;
			goto rtn;
		}
		v.hp = sumhp();	/* XXX */
		if((length = ((tabtab[j] & TMASK) - v.hp)) > 0 )break;
	}
	type = tabtab[j] & (~TMASK);
	fp = fbuf;
	pp = padptr;
	if(x == savfc){while(1){
		if(((j = (i = getch()) & CMASK)) == padc){
			npad++;
			*pp++ = fp;
			if(pp > (padptr + NPP - 1))break;
			goto s1;
		}else if(j == savfc) break;
			else if(j == '\n'){
				temp = j;
				nlflg = 0;
				break;
			}
		ws += width(i);
	s1:
		*fp++ = i;
		if(fp > (fbuf + FBUFSZ -3))break;
	}
	if(!npad){
		npad++;
		*pp++ = fp;
		*fp++ = 0;
	}
	*fp++ = temp;
	*fp++ = 0;
	temp = i = (j = length-ws)/npad;
	i = (i/HOR)*HOR;
	if((j -= i*npad) <0)j = -j;
	i = makem(i);
	if(temp <0)i |= NMOT;
	for(;npad > 0; npad--){
		*(*--pp) = i;
		if(j){
			j -= HOR;
			(*(*pp)) += HOR;
		}
	}
	cp = fbuf;
	j = 0;
	}else if(type == 0){
	/*plain tab or leader*/
		if((j = width(rchar)) == 0)nchar = 0;
		else{
			nchar = length /j;
			length %= j;
		}
		if(length)j = length | MOT;
		else j = getch0();
	}else{
	/*center tab*/
	/*right tab*/
		while(((j = (i = getch()) & CMASK) != savtc) &&
			(j != '\n') && (j != savlc)){
			ws += width(i);
			*fp++ = i;
			if(fp > (fbuf +FBUFSZ - 3)) break;
		}
		*fp++ = i;
		*fp++ = 0;
		if(type == RTAB)length -= ws;
		else length -= ws/2; /*CTAB*/
		if(((j = width(rchar)) == 0) || (length <= 0))nchar = 0;
		else{
			nchar = length/j;
			length %= j;
		}
		length = (length/HOR)*HOR;
		j = makem(length);
		cp = fbuf;
		nlflg = 0;
	}
rtn:
	fc = savfc; tabch = savtc; ldrch = savlc;
	return(j);
}
E 1
