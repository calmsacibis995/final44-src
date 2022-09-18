/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	format.c,v $
 * Revision 2.4  89/03/09  21:34:10  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:40:14  gm0w
 * 	Changes for cleanup.
 * 
 * 08-Feb-88  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Removed else leg of KERNEL conditionals and fixed 
 *	includes as part of kernel cleanup.
 *
 * 29-Jan-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Conditionalized kdb code under KERNEL in order to make
 *	kdb part of the kernel rather than a separate library.
 *
 *  5-Sep-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Converted into kernel debugger, "kdb".
 *
 */
#ifndef	lint
static	char sccsid[] = "@(#)format.c 1.1 86/02/03 SMI";
#endif
/*
 * adb - output formatting
 */

#include <sun3/kdb/adb.h>
#include <ctype.h>
#include <sun3/kdb/fpascii.h>

scanform(icount, ifp, itype, ptype)
	int icount;
	char *ifp;
	int itype, ptype;
{
	char *fp, modifier;
	int fcount, savdot, exact;

	while (icount) {
		fp = ifp;
		savdot = dot;

		if (itype != SSP) {
			exact = findsym(dot, ptype) == 0;
			if (exact && maxoff)
				printf("\n%s:%16t", cursym->n_un.n_name);
		}

		while (*fp && errflg==0) {
			if (isdigit(modifier = *fp)) {
				fcount = 0;
				while (isdigit(modifier = *fp++)) {
					fcount *= 10;
					fcount += modifier-'0';
				}
				fp--;
			} else
				fcount = 1;
			if (*fp == 0)
				break;

#ifdef	vax
			if (exact && dot==savdot && (itype==ISP||itype==DSP) &&
			    cursym->s_name[0]=='_' && *fp=='i') {
				(void) exform(1, "x", itype, ptype);
				fp++;
				printc('\n');
			} else
#endif
				fp = exform(fcount, fp, itype, ptype);
		}

		dotinc = dot - savdot;
		dot = savdot;

		if (errflg) {
			if (icount < 0) {
				errflg = 0;
				break;
			}
			error(errflg);
		}

		if (--icount)
			dot = inkdot(dotinc);
		if (interrupted)
			error((char *)0);
	}
}

char *
exform(fcount, ifp, itype, ptype)
	int fcount;
	char *ifp;
	int itype, ptype;
{
	u_short shortval; int val;
	addr_t savdot;
	char *fp, modifier;
	unsigned char c;
	double fval;
	union{
		int funi[3];
		double fund;
		ext_fp x ;
	}fun;

	if (fcount <= 0){
	    /* stupid hack to make zero repeat count do something reasonable */
	    fp = ifp;
	    if (*fp =='"'){
		/* scan out quoted string */
		/* idiot really deserves a core dump here... */
		fp++;
		while (*fp != '"' && *fp)
			fp++;
	    }
	    if (*fp)
		    fp++;
	    return fp;
	}
	while (fcount > 0) {
		fp = ifp;
		c = *fp;
		var[0] = dot;
		modifier = *fp++;
		switch (modifier) {

		case 't': case 'T':
			printf("%T", fcount); return (fp);
		case '+':
			dot = inkdot(fcount); return (fp);
		case '-':
			dot = inkdot(-fcount); return (fp);
		case '^':
			dot = inkdot(-dotinc*fcount); return (fp);

		case ' ': case '\t':
			goto next;


		case 'a':
			psymoff(dot, ptype, ":%16t");
			dotinc = 0;
			goto next;

		case 'i':
			if (itype != SSP)
				break;
			savdot = dot;
				    if (charpos() == 0)
					    printf("%16m");
#ifdef	vax
				    printins(0, ISP, (u_char)chkget(dot, ISP));
#endif
#ifdef	mc68000
				    if (modifier == 'i')  /* the old way */
					printins(0, ISP, 
					    (chkget(dot, ISP)>>16)&0xffff);
#endif
				    printc('\n');
				    dot = inkdot(dotinc);
			dot = savdot;
			dotinc = 1;
			goto next;
		}
		if (charpos() == 0)
			printf("%16m");
		switch (modifier) {

		case '"':
			dotinc = 0;
			while (*fp != '"' && *fp)
				printc(*fp++);
			if (*fp)
				fp++;
			goto next;

		case 'n': case 'N':
			printc('\n'); dotinc = 0; goto next;

		}
		if (itype == SSP)
			error("format not supported with @");
		if (itype == NSP) {
			val = dot;
			shortval = dot;
			c = dot;
		} else {
			/* 32- bit hacks go here */
			val = get(dot, itype);
			/* handle big-end and little-end machines */
			shortval = *(short *)&val;
			c = *(char *)&val;
			if (!index("pPU4WXYQODfF", modifier))
				val = shortval;
		}
		if (errflg)
			return (fp);
		if (interrupted)
			error((char *)0);
		var[0] = val;
		switch (modifier) {

		case 'i':
#ifdef	vax
			printins(0, itype, (u_char)val);
#endif
#ifdef	mc68000
			printins(0, itype, (u_short)val);
#endif
			printc('\n'); break;

		case 'p':
			dotinc = 4; psymoff(val, ptype, "%16t"); break;
		case 'u':	
			dotinc = 2; printf("%-8u", shortval); break;
		case 'U':
			dotinc = 4; printf("%-16U", val); break;
		case 'c':
			dotinc = 1; printc(c); break;
		case 'C':
			dotinc = 1; printesc(c); break;
		case 'b': case 'B':
			dotinc = 1; printf("%-8o", c); break;
		case 'w':
			dotinc = 2; printf("%-8r", shortval); break;
		case 'W':
			dotinc = 4; printf("%-16R", val); break;

		case 's': case 'S':
			savdot = dot;
			dotinc = 1;
#ifdef	vax
			while ((c = get(dot, itype) & 0377) && errflg == 0) 
#else
			/* nonuxi */
			while ((c = (get(dot, itype) >>24)) && errflg == 0) 
#endif
			{
				dot = inkdot(1);
				if (modifier == 'S')
					printesc(c);
				else
					printc(c);
				endline();
			}
			dotinc = dot - savdot + 1;
			dot = savdot;
			break;

		case 'x':
			dotinc = 2; printf("%-8x", shortval); break;
		case 'X':
			dotinc = 4; printf("%-16X", val); break;
		case 'Y':
			dotinc = 4; printf("%-24Y", val); break;
		case 'q':
			dotinc = 2; printf("%-8q", shortval); break;
		case 'Q':
			dotinc = 4; printf("%-16Q", val); break;
		case 'o':
			dotinc = 2; printf("%-8o", shortval); break;
		case 'O':
			dotinc = 4; printf("%-16O", val); break;
		case 'd':
			dotinc = 2; printf("%-8d", shortval); break;
		case 'D':
			dotinc = 4; printf("%-16D", val); break;
		case 'f':
			dotinc = 4;
			fval = *(float *)&val;
			printf("%-16.9f", fval); break;
		case 'F':
			dotinc = 8;
			/* these lines depend on the layout of doubles */
			if (fp_reg_address == 0)
				{
				fun.funi[0] = get(dot,itype) ;
				fun.funi[1] = get(dot+4,itype) ;
				}
			else
				{
				fun.funi[0] = *(long *)fp_reg_address ;
				fun.funi[1] = *(long *)(fp_reg_address+4) ;
				}
			printf("%-32.18F", fun.fund); break;
		case 'e':
		case 'E':
			if (mc68881==0)
				{
				error("no 68881") ;
				}
			else
			{
			char s[64] ;

			dotinc = 12;
			/* these lines depend on the layout of extendeds */
			if (fp_reg_address == 0)
				{
				fun.funi[0] = get(dot,itype) ;
				fun.funi[1] = get(dot+4,itype) ;
				fun.funi[2] = get(dot+8,itype) ;
				}
			else
				{
				fun.funi[0] = *(long *)fp_reg_address ;
				fun.funi[1] = *(long *)(fp_reg_address+4) ;
				fun.funi[2] = *(long *)(fp_reg_address+8) ;
				}
			fprtos(&fun.x, s) ;
			printf("%s",s) ;
			}
			break;
		default:
			error("bad modifier");
		}
next:
		if (itype != NSP)
			dot = inkdot(dotinc);
		fcount--;
		endline();
	}
	return (fp);
}

printesc(c)
	char c;
{

	c &= 0177;
	if (c == 0177)
		printf("^?");
	else if (c < ' ')
		printf("^%c", c + '@');
	else
		printc(c);
}

inkdot(incr)
	int incr;
{
	addr_t newdot;

	newdot = dot + incr;
	if ((dot ^ newdot) & 0x80000000)
		error("address wrap around");
	return (newdot);
}
