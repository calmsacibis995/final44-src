/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	output.c,v $
 * Revision 2.4  89/03/09  22:17:44  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  20:23:11  gm0w
 * 	Changes for cleanup.
 * 
 *  3-Mar-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Removed more lint.
 *
 *  3-Oct-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	De-linted.
 *
 * 11-Oct-85  Robert V Baron (rvb) at Carnegie-Mellon University
 *	FLushed the stupid #
 *
 */

/*
 *
 *	UNIX debugger
 *
 */

/* static	char sccsid[] = "@(#)output.c	4.3 8/11/83"; */

#include <vax/kdb/defs.h>

INT		mkfault;
INT		infile;
INT		outfile = 1;
long		maxpos;
long		maxoff;
INT		radix = 16;

char		printbuf[MAXLIN];
char		*printptr = printbuf;
char		*digitptr;


eqstr(s1, s2)
register string_t	s1, s2;
{
	while ( *s1++ == *s2 ) {
		if ( *s2++ == 0 ) {
			return(1);
		}
	}
	return(0);
}

length(s)
register string_t		s;
{
	INT		n = 0;
	while ( *s++ ) {
		n++;
	}
	return(n);
}

printc(c)
char		c;
{
	char		d;
	string_t		q;
	INT		posn, tabs, p;

	if ( mkfault ) {
		return;
	} else if ( (*printptr=c)==EOR ) {
		tabs=0;
		posn=0;
		q=printbuf;
		for ( p=0; p<printptr-printbuf; p++ ) {
			    d=printbuf[p];
			if ( (p&7)==0 && posn ) {
				tabs++;
				posn=0;
			}
			if ( d==' ' ) {
				posn++;
			} else {
				while ( tabs>0 ) {
					*q++='	';
					tabs--;
				}
				while ( posn>0 ) {
					*q++=' ';
					posn--;
				}
				*q++=d;
			}
		}
		*q++=EOR;
		write(outfile,printbuf,q-printbuf);
		printptr=printbuf;
	} else if ( c=='	' ) {
		*printptr++=' ';
		while ( (printptr-printbuf)&7 ) {
			*printptr++=' ';
		}
	} else if ( c ) {
		printptr++;
	}
	if ( printptr >= &printbuf[MAXLIN-9] ) {
		write(outfile, printbuf, printptr - printbuf);
		printptr = printbuf;
	}
}

charpos()
{
	return(printptr-printbuf);
}

flushbuf()
{
	if ( printptr!=printbuf ) {
		printc(EOR);
	}
}

/*VARARGS1*/
printf(fmat,a1)
string_t		fmat;
string_t		*a1;
{
	string_t		fptr, s;
	INT		*vptr;
	long		*dptr;
	INT		width, prec;
	char		c, adj;
	INT		x, n;
	long		lx;
	char		digits[64];

	fptr = fmat;
	vptr = (INT *)&a1;
	dptr = (long *)vptr;

	while ( c = *fptr++ ) {
		if ( c!='%' ) {
			printc(c);
		} else {
			if ( *fptr=='-' ) {
				adj='l';
				fptr++;
			} else {
				adj='r';
			}
			width=convert(&fptr);
			if ( *fptr=='.' ) {
				fptr++;
				prec=convert(&fptr);
			} else {
				prec = -1;
			}
			digitptr=digits;
			x = shorten(lx = *dptr++);
			s=0;
			switch (c = *fptr++) {

			case 'd':
			case 'u':
				printnum(x,c,10);
				break;
			case 'o':
				printoct(itol(0,x),0);
				break;
			case 'q':
				lx=x;
				printoct(lx,-1);
				break;
			case 'x':
				printdbl(itol(0,x),c,16);
				break;
			case 'r':
				printdbl(lx=x,c,radix);
				break;
			case 'R':
				printdbl(lx,c,radix);
				vptr++;
				break;
			case 'Y':
				printdate(lx);
				vptr++;
				break;
			case 'D':
			case 'U':
				printdbl(lx,c,10);
				vptr++;
				break;
			case 'O':
				printoct(lx,0);
				vptr++;
				break;
			case 'Q':
				printoct(lx,-1);
				vptr++;
				break;
			case 'X':
				printdbl(lx,'x',16);
				vptr++;
				break;
			case 'c':
				printc(x);
				break;
			case 's':
				s=(char *)lx;
				break;
			case 'm':
				vptr--;
				break;
			case 'M':
				width=x;
				break;
			case 'T':
			case 't':
				if ( c=='T' ) {
					width=x;
				} else {
					dptr--;
				}
				if ( width ) {
					width -= charpos()%width;
				}
				break;
			default:
				printc(c);
				dptr--;
			}

			if ( s==0 ) {
				*digitptr=0;
				s=digits;
			}
			n=length(s);
			n=(prec<n && prec>=0 ? prec : n);
			width -= n;
			if ( adj=='r' ) {
				while ( width-- > 0 ) {
					printc(' ');
				}
			}
			while ( n-- ) {
				printc(*s++);
			}
			while ( width-- > 0 ) {
				printc(' ');
			}
			digitptr=digits;
		}
	}
}

printdate(tvec)
long		tvec;
{
	register INT		i;
	register string_t	timeptr;

	timeptr="????????????????????????";
	for ( i=20; i<24; i++ ) {
		*digitptr++ = *(timeptr+i);
	}
	for ( i=3; i<19; i++ ) {
		*digitptr++ = *(timeptr+i);
	}
} /*printdate*/

prints(s)
char *s;
{
	printf("%s",s);
}

newline()
{
	printc(EOR);
}

convert(cp)
register string_t	*cp;
{
	register char	c;
	INT		n;
	n=0;
	while ( ((c = *(*cp)++)>='0') && (c<='9') ) {
		n=n*10+c-'0';
	}
	(*cp)--;
	return(n);
}

printnum(n,fmat,base)
register INT		n;
{
	register char	k;
	register INT		*dptr;
	INT		digs[15];
	dptr=digs;
	if ( n<0 && fmat=='d' ) {
		n = -n;
		*digitptr++ = '-';
	}
	n &= 0xffff;
	while ( n ) {
		*dptr++ = ((unsigned)(n&0xffff))%base;
		n=((unsigned)(n&0xffff))/base;
	}
	if ( dptr==digs ) {
		*dptr++=0;
	}
	while ( dptr!=digs ) {
		k = *--dptr;
		*digitptr++ = (k+(k<=9 ? '0' : 'a'-10));
	}
}

printoct(o,s)
long		o;
INT		s;
{
	INT		i;
	long		po = o;
	char		digs[12];

	if ( s ) {
		if ( po<0 ) {
			po = -po;
			*digitptr++='-';
		} else {
			if ( s>0 ) {
				*digitptr++='+';
			}
		}
	}
	for ( i=0;i<=11;i++ ) {
		    digs[i] = po&7;
		po >>= 3;
	}
	digs[10] &= 03;
	digs[11]=0;
	for ( i=11;i>=0;i-- ) {
		    if ( digs[i] ) {
			break;
		}
	}
	for ( i++;i>=0;i-- ) {
		    *digitptr++=digs[i]+'0';
	}
}

printdbl(lxy,fmat,base)
long lxy;
char fmat;
int base;
{
	int digs[20];
	int *dptr;
	char k;
	double f ,g;
	long q;
	INT lx,ly;
	ly=lxy;
	lx=(lxy>>16)&0xFFFF;
	dptr=digs;
	if ( fmat=='D' || fmat=='r' ) {
		f=itol(lx,ly);
		if ( f<0 ) {
			*digitptr++='-';
			f = -f;
		}
	} else {
		if ( lx==-1 ) {
			*digitptr++='-';
			f=leng(-ly);
		} else {
			f=leng(lx);
			f *= itol(1,0);
			f += leng(ly);
		}
	}
	while ( f ) {
		q=f/base;
		g=q;
		*dptr++ = f-g*base;
		f=q;
	}
	if ( dptr==digs || dptr[-1]>9 ) {
		*dptr++=0;
	}
	while ( dptr!=digs ) {
		k = *--dptr;
		*digitptr++ = (k+(k<=9 ? '0' : 'a'-10));
	}
}

#define MAXIFD	5
struct {
	int	fd;
	int	r9;
}

istack[MAXIFD];
int	ifiledepth;

iclose(){}
oclose(){}

endline()
{

	if (maxpos <= charpos())
		printf("\n");
}
