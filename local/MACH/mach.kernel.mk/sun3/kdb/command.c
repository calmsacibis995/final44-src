/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	command.c,v $
 * Revision 2.5  89/03/09  21:33:56  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/25  19:39:30  gm0w
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
static	char sccsid[] = "@(#)command.c 1.1 86/02/03 SMI";
#endif
/*
 * adb - command parser
 */

#include <sun3/kdb/adb.h>
#include <sun3/kdb/fpascii.h>

char	eqformat[512] = "z";
char	stformat[512] = "X\"= \"^i";

#define QUOTE	0200
#define STRIP	0177

int	lastcom = '=';

command(buf, defcom)
	char *buf, defcom;
{
	int itype, ptype, modifier;
	long reg;
	int fourbyte, eqcom, atcom;
	char wformat[1];
	char c, savc;
	int w, savdot;
	char *savlp = lp;
	int locval, locmsk;

	if (buf) {
		if (*buf == '\n')
			return (0);
		lp = buf;
	}
	do {
		fp_reg_address = 0 ; /* initialize to no */
		if (hadaddress = expr(0)) {
			dot = expv;
			ditto = dot;
		}
		address = dot;
		if (rdc() == ',' && expr(0)) {
			hadcount = 1;
			count = expv;
		} else {
			hadcount = 0;
			count = 1;
			lp--;
		}
		if (!eol(rdc()))
			lastcom = lastc;
		else {
			if (hadaddress == 0)
				dot = inkdot(dotinc);
			lp--;
			lastcom = defcom;
		}

		switch (lastcom&STRIP) {

		case '/':
			itype = DSP; ptype = DSYM;
			goto trystar;

		case '=':
			itype = NSP; ptype = 0;
			goto trypr;

		case '?':
			itype = ISP; ptype = ISYM;
			goto trystar;

trystar:
			if (rdc() == '*')
				lastcom |= QUOTE;
			else
				lp--;
			if (lastcom & QUOTE) {
				itype |= STAR;
				ptype = (DSYM+ISYM) - ptype;
			}

trypr:
			fourbyte = 0;
			eqcom = lastcom=='=';
			atcom = lastcom=='@';
			c = rdc();
			if ((eqcom || atcom) && index("mLlWw", c))
				error(eqcom ?
				    "unexpected '='" : "unexpected '@'");
			switch (c) {

			case 'L':
				fourbyte = 1;
			case 'l':
				dotinc = (fourbyte ? 4 : 2);
				savdot = dot;
				(void) expr(1); locval = expv;
				locmsk = expr(0) ? expv : -1;
				if (!fourbyte) {
					locmsk &= 0xffff;
					locval &= 0xffff;
				}
				for (;;) {
					w = get(dot, itype);
					if (errflg || interrupted)
						break;
					if ((w&locmsk) == locval)
						break;
					dot = inkdot(dotinc);
				}
				if (errflg) {
					dot = savdot;
					errflg = "cannot locate value";
				}
				psymoff(dot, ptype, "");
				break;

			case 'W':
				fourbyte = 1;
			case 'w':
				wformat[0] = lastc; (void) expr(1);
				do {
				    savdot = dot;
				    psymoff(dot, ptype, ":%16t");
				    (void) exform(1,wformat,itype,ptype);
				    errflg = 0; dot = savdot;
				    if (fourbyte)
					put(dot, itype, expv);
				    else {
					/*NONUXI*/
					long longvalue;
					longvalue = get(dot, itype);
					*(short*)&longvalue = (short)expv;
					put(dot, itype, longvalue);
				    }
				    savdot = dot;
				    printf("=%8t");
				    (void) exform(1,wformat,itype,ptype);
				    newline();
				} while (expr(0) && errflg == 0);
				dot = savdot;
				chkerr();
				break;

			default:
				lp--;
				getformat(eqcom ? eqformat : stformat);
				if (atcom) {
				} else if (!eqcom)
					psymoff(dot, ptype, ":%16t");
				scanform(count, (eqcom?eqformat:stformat),
				    itype, ptype);
			}
			break;

		case '>':
			lastcom = 0; savc = rdc();
			reg = getreg(savc);
			if (reg >= 0) {
				(void) writereg(reg, dot);
				break;
			}
			modifier = varchk(savc);
			if (modifier == -1)
				error("bad variable");
			var[modifier]=dot;
			break;

		case '$':
			lastcom = 0;
			printtrace(nextchar());
			break;

		case ':':
			if (!executing) {
				executing = 1;
				subpcs(nextchar());
				executing = 0;
				lastcom = 0;
			}
			break;

		case 0:
			break;

		default:
			error("bad command");
		}
		flushbuf();
	} while (rdc()==';');
	if (buf)
		lp = savlp;
	else
		lp--;
	return (hadaddress && dot != 0);		/* for :b */
}
