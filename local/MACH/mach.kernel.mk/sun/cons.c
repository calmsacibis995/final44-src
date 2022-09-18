/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	cons.c,v $
 * Revision 2.8  90/12/17  17:16:33  berman
 * 	Added sun4c include of machine/eeprom.h  and conditionally fix
 * 	the arguments to v_fwritestr().
 * 	[90/09/10            berman]
 * 
 * Revision 2.7  89/08/02  10:22:12  jsb
 * 	Only change interrupt vector when at high spl otherwise
 * 	softint can be called and we lose softclock state.
 * 	[89/07/31            rwd]
 * 
 * 	Make sure cnpollc(TRUE) is not called without interceding
 * 	cnpollc(FALSE).
 * 	[89/07/14            rwd]
 * 
 * Revision 2.6  89/07/11  13:54:53  jjc
 * 	Defined INTERREG to be INTREG on Sun 4.
 * 	Removed definition of _O_TIOCGSIZE since it is now defined
 * 	in sys/ioctl.h.
 * 	[89/04/25            jjc]
 * 
 * Revision 2.5  89/06/03  15:41:25  jsb
 * 	Added cnpollc to enable and disable sunromp keyboard input for
 * 	use by kdb.
 * 	[89/05/18            rwd]
 * 
 * Revision 2.4  89/03/09  21:29:26  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:27:27  gm0w
 * 	Removed else legs of MACH and CMU conditionals and fixed 
 * 	includes as part of kernel cleanup.
 * 	[89/02/08            jjc]
 * 
 * 05-Nov-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Defined O_TIOCGSIZE for backward compatibility.
 *
 * 04-Oct-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Added code to cnioctl() to get size of display from EEPROM
 *	on Sun 3/{60,260}.
 *
 * 23-Oct-86  David Golub (dbg) at Carnegie-Mellon University
 *	Disable TIOCCONS.
 *
 *  7-Oct-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Merged in CMUCS stuff.
 *
 *  9-Aug-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Modified for Mach:
 *	1) Replaced all occurences of "romp" with "sunromp" to avoid 
 *	   name conflict with IBM PC RT "romp".
 *	2) Conditionalized including "pte.h" on whether MACH is
 *	   off.
 *	3) Added dummy routine, "slave_cnenable", that needs to be
 *	   filled in when this machine has more than one cpu.
 *
 */
#ifndef	lint
static	char sccsid[] = "@(#)cons.c 1.1 86/02/03 Copyr 1983 Sun Micro";
#endif

/*
 * Copyright (c) 1983 by Sun Microsystems, Inc.
 */

/*
 * Console driver for Sun.
 *
 * Either indirects to the tty that is the pseudo-console,
 * or calls the monitor for output.
 */


#include <sys/param.h>
#include <sys/conf.h>
#include <sys/user.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
#include <sys/systm.h>
#include <sys/kernel.h>
#include <sys/buf.h>
#include <sys/vmmac.h>
#include <sys/uio.h>
#include <sys/proc.h>

#include <machine/mmu.h>
#include <machine/cpu.h>
#ifdef	sun3
#include <machine/interreg.h>
#endif	sun3

#include <mon/keyboard.h>

#include <sundev/mbvar.h>

#include <sun/consdev.h>

#ifdef	sun4
#include <machine/intreg.h>
#define INTERREG	INTREG
#endif	sun4

#ifdef	sun3
#include <sun3/eeprom.h>

#define MINLINES             1   
#define LOSCREENLINES       34
#define HISCREENLINES       48
#define LORESMAXLINES       34
#define HIRESMAXLINES       48

#define MINCOLS              1   
#define LORESMAXCOLS        80
#define HIRESMAXCOLS       120
#define LOSCREENCOLS        80
#define HISCREENCOLS       120
#endif	sun3

/*
 *	Use fields in 4.3 winsize structure to hold dimensions
 */
#define t_nlines	t_winsize.ws_row
#define t_ncols		t_winsize.ws_col

struct	tty cons;
int	ncons = 1;	/* only one console */
int	cn_pendc;	/* pending output character */
int	cnstart(), ttrstrt();

/*ARGSUSED*/
cnopen(dev, flag)
	dev_t dev;
{
	register struct tty *tp;
	int error, first = 0;

	if (consdev)
		return ((*cdevsw[major(consdev)].d_open)(consdev, flag));
	tp = &cons;
	tp->t_addr = 0;
	tp->t_oproc = cnstart;
	if ((tp->t_state&TS_ISOPEN) == 0) {
		first = 1;
		ttychars(tp);
		tp->t_flags = EVENP|ODDP|ECHO|XTABS|CRMOD;
		tp->t_ispeed = tp->t_ospeed = B9600;
		tp->t_state = TS_ISOPEN|TS_CARR_ON;
		tp->t_ttyloc.tlc_hostid = TLC_MYHOST;
		tp->t_ttyloc.tlc_ttyid = TLC_CONSOLE;
	}
	if (tp->t_state&TS_XCLUDE && u.u_uid != 0)
		return (EBUSY);
	error = ((*linesw[tp->t_line].l_open)(dev, tp));
	if (error)
		return (error);
#include <kb.h>
#if	NKB > 0
	if (first)		/* must be after cons l_open */
		(void) kbdsettrans(tp, TR_ASCII);
#endif	NKB > 0
	return (0);
}

/*ARGSUSED*/
cnclose(dev, flag)
	dev_t dev;
{

	if (consdev)
		return ((*cdevsw[major(consdev)].d_close)(consdev, flag));
	(*linesw[cons.t_line].l_close)(&cons);
	ttyclose(&cons);
	return (0);
}

/*ARGSUSED*/
cnread(dev, uio)
	dev_t dev;
	struct uio *uio;
{

	if (consdev)
		return ((*cdevsw[major(consdev)].d_read)(consdev, uio));
	return ((*linesw[cons.t_line].l_read)(&cons, uio));
}

/*ARGSUSED*/
cnwrite(dev, uio)
	dev_t dev;
	struct uio *uio;
{

	if (consdev)
		return ((*cdevsw[major(consdev)].d_write)(consdev, uio));
	return ((*linesw[cons.t_line].l_write)(&cons, uio));
}

cnselect(dev, rw)
	dev_t dev;
	int rw;
{

	if (consdev)
		return ((*cdevsw[major(consdev)].d_select)(consdev, rw));
	return (ttselect(dev, rw));
}

cninput(c, tp)
	char c;
	register struct tty *tp;
{
	tp = &cons;
	if (tp->t_state & TS_ISOPEN)
		(*linesw[tp->t_line].l_rint)(c, tp);
}

cnopoll()
{
	register struct tty *tp = &cons;
	register int s;

	if ((tp->t_state & TS_ISOPEN) == 0)
		return;
	/* See if we can continue output */
	s = spl1();
	if ((tp->t_state & TS_BUSY) && cn_pendc != -1) {
		if ((*sunromp->v_mayput)(cn_pendc) == 0) {
			cn_pendc = -1;
			tp->t_state &= ~TS_BUSY;
			(*linesw[tp->t_line].l_start)(tp);
		} else
			timeout(cnopoll, (caddr_t)0, 1);
	}
	(void) splx(s);
}

/*
 * Start console output
 * always called at level 5 - not safe to drop level
 */
cnstart(tp)
	register struct tty *tp;
{
	register int c;
	register int cc = 0;
	int consout();

	if (tp->t_state & (TS_TIMEOUT|TS_BUSY|TS_TTSTOP))
		goto out;
	if (tp->t_outq.c_cc == 0)
		goto out;
	if (*sunromp->v_outsink == OUTSCREEN) {
		/* never do output here - we're at spl5 and it takes forever */
		tp->t_state |= TS_BUSY;
		cn_pendc = -1;
		if (tp->t_outq.c_cc > TTLOWAT(tp))	/* do it soon */
			softcall(consout, (caddr_t)0);
		else
			timeout(consout, (caddr_t)0, hz/30);	/* wait a bit */
		return;
	}
	while (tp->t_outq.c_cc > 0) {
		c = getc(&tp->t_outq);
		if ((c&0200) && (tp->t_flags&(RAW|LITOUT)) == 0) {
			timeout(ttrstrt, (caddr_t)tp, cc&0x7f);
			tp->t_state |= TS_TIMEOUT;
			break;
		}
		if ((*sunromp->v_mayput)(c) != 0) {
			tp->t_state |= TS_BUSY;
			cn_pendc = c;
			timeout(cnopoll, (caddr_t)0, 1);
			break;
		}
	}
out:
	if (tp->t_outq.c_cc <= TTLOWAT(tp)) {
		if (tp->t_state&TS_ASLEEP) {
			tp->t_state &= ~TS_ASLEEP;
			wakeup((caddr_t)&tp->t_outq);
		}
		if (tp->t_wsel) {
			selwakeup(tp->t_wsel, tp->t_state & TS_WCOLL);
			tp->t_wsel = 0;
			tp->t_state &= ~TS_WCOLL;
		}
	}
}

#define MAXHIWAT	2000

/*
 * Output to frame buffer console
 * Called at software interrupt level 
 * because it takes a long time to scroll
 */
consout()
{
	register struct tty *tp = &cons;
	static char obuf[MAXHIWAT];
	register char *cp;
	register int cc, tcc;
	int s;

	s = spl1();
	cc = -1;
	for (cp = obuf, tcc = 0; tp->t_outq.c_cc > 0; cp += cc, tcc += cc) {
		if ((tp->t_flags&(RAW|LITOUT)))
			cc = ndqb(&tp->t_outq, 0);
		else
			cc = ndqb(&tp->t_outq, 0200);
		if (cc == 0)
			break;
		if (tcc + cc > sizeof obuf)
			break;
		(void) q_to_b(&tp->t_outq, cp, cc);
	}
	(void) splx(s);
	if (tcc > 0) {
		/* Must clear high bit for monitor */
		for (cp = obuf; cp < &obuf[tcc]; cp++)
			*cp &= 0177;
#if	sun4c
		(*sunromp->v_fwritestr)(obuf, tcc);
#else	sun4c
		(*sunromp->v_fwritestr)(obuf, tcc, sunromp->v_fbaddr);
#endif	sun4c
	}
	s = spl1();
	if (cc == 0) {
		cc = getc(&tp->t_outq);
		timeout(ttrstrt, (caddr_t)tp, cc&0x7f);
		tp->t_state |= TS_TIMEOUT;
	} else if (tp->t_outq.c_cc > 0)
		softcall(consout, (caddr_t)0);
	tp->t_state &= ~TS_BUSY;
	if (tp->t_outq.c_cc <= TTLOWAT(tp)) {
		if (tp->t_state&TS_ASLEEP) {
			tp->t_state &= ~TS_ASLEEP;
			wakeup((caddr_t)&tp->t_outq);
		}
		if (tp->t_wsel) {
			selwakeup(tp->t_wsel, tp->t_state & TS_WCOLL);
			tp->t_wsel = 0;
			tp->t_state &= ~TS_WCOLL;
		}
	}
	(void) splx(s);
}

/*ARGSUSED*/
cnioctl(dev, cmd, data, flag)
	dev_t dev;
	caddr_t data;
{
	register struct tty *tp;
	int error;

	if (consdev)
		return ((*cdevsw[major(consdev)].d_ioctl)
		    (consdev, cmd, data, flag));
	tp = &cons;
	error = (*linesw[tp->t_line].l_ioctl)(tp, cmd, data, flag);
	if (error >= 0)
		return (error);
#ifdef	sun3
        if (((cpu == CPU_SUN3_260) || (cpu == CPU_SUN3_60)) &&
                ((cmd == TIOCGSIZE) || (cmd ==  _O_TIOCGSIZE))) {
                int maxlines, maxcols, screenlines, screencols;

                if (EEPROM->ee_diag.eed_scrsize == EED_SCR_1600X1280) {
                        maxlines = HIRESMAXLINES;
                        maxcols = HIRESMAXCOLS;
                        screenlines = HIRESMAXLINES;
                        screencols = HISCREENCOLS;
                } else {
                        maxlines = LORESMAXLINES;
                        maxcols = LORESMAXCOLS;
                        screenlines = LORESMAXLINES;
                        screencols = LOSCREENCOLS;
                }
                if ((EEPROM->ee_diag.eed_rowsize < MINLINES) ||
                       (EEPROM->ee_diag.eed_rowsize > maxlines))
                        tp->t_nlines = screenlines;
                else
                        tp->t_nlines = EEPROM->ee_diag.eed_rowsize;

                if ((EEPROM->ee_diag.eed_colsize < MINCOLS) ||
                       (EEPROM->ee_diag.eed_colsize > maxcols))
                        tp->t_ncols = screencols;
                else
                        tp->t_ncols = EEPROM->ee_diag.eed_colsize;
                ((struct ttysize *)data)->ts_lines = tp->t_nlines;
                ((struct ttysize *)data)->ts_cols = tp->t_ncols;
                return (0);
        }
#endif	
	error = ttioctl(tp, cmd, data, flag);
	if (error >= 0)
		return (error);
	return (ENOTTY);
}

cnputc(c)
	register int c;
{
	register int s;

	s = spl7();
	if (c == '\n')
		(*sunromp->v_putchar)('\r');
	(*sunromp->v_putchar)(c);
	(void) splx(s);
}

cngetc()
{
	register int c;

	while ((c = (*sunromp->v_mayget)()) == -1)
		;
	return (c);
}

slave_cnenable()
{
}

cnpollc(flag)
int flag;
{
    static u_char interreg;
    static int spl;
    static last=0;

    if (flag) {
	if (!last) {
#if	sun4c
           start_mon_clock();
#else	sun4c
	   (*sunromp->v_initgetkey)();
	    startnmi();
#endif	sun4c
	    spl = spl7();		/* we can take hi clock ints now */
	    interreg = *INTERREG;
	    *INTERREG |= IR_ENA_INT;	/* make sure interrupts can occur */
	}
    } else {
	*INTERREG = interreg;
	splx(spl);
#if	sun4c
	stop_mon_clock();
#else	sun4c
	stopnmi();
#endif	sun4c
    }
   last = flag;
}
