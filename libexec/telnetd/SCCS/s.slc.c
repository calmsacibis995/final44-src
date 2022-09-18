h51253
s 00006/00008/00459
d D 8.2 95/05/30 22:02:43 dab 10 9
c code cleanup, change b*() to mem*()
c Add setting up of LINEMODE environment variable.
e
s 00002/00002/00465
d D 8.1 93/06/04 19:07:03 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00466
d D 5.8 92/12/18 14:05:45 dab 8 7
c Change ENCRYPT to ENCRYPTION
c Change AUTHENTICATE to AUTHENTICATION
c Add Sun/SVR4 Streams support
c Allow for more ptys
c Environ suboption USERVAR support
c New Telnet Flowcontrol suboption support
c Server -k option to default to no kludge linemode
c Server -U option, allow only registered hosts to connect
e
s 00030/00019/00436
d D 5.7 91/03/01 01:35:21 dab 7 6
c Telnet AUTHENTICATION option
c Telnet ENCRYPT option (test version)
c Function prototypes
c Bug fixes and code cleanup
e
s 00003/00002/00452
d D 5.6 91/02/26 11:50:39 bostic 6 5
c ANSI fixes (one real bug!)
e
s 00026/00011/00428
d D 5.5 90/09/14 11:26:31 borman 5 4
c Latest round of bug fixes.  See the README file
c in src/usr.bin/telnet/README for the details.
e
s 00010/00010/00429
d D 5.4 90/06/28 13:06:05 borman 4 3
c Lots of bugfixes, add the ENVIRON and X-DISPLAY-LOC
c options, "-l user" to the command line, diagnostic flags.
e
s 00001/00011/00438
d D 5.3 90/06/01 15:55:55 bostic 3 2
c new copyright notice
e
s 00023/00014/00426
d D 5.2 90/02/28 15:35:50 borman 2 1
c Many fixes.  1) Use the cc_t typedef from termios.h
c 2) Fix for SYSV VEOF/VMIN overlap
c 3) Add two missing "break" statements
c 4) Add SLC_FORW[12] support
c 5) start of TOS support
c 6) Make sure things get initialized properly
c 7) Don't send Urgent mode data, since some clients go into infinate loops...
e
s 00440/00000/00000
d D 5.1 89/09/01 15:17:50 borman 1 0
c New telnetd, with LINEMODE support
e
u
U
t
T
I 1
/*
D 9
 * Copyright (c) 1989 Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
D 3
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 3
I 3
 * %sccs.include.redist.c%
E 3
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include "telnetd.h"

#ifdef	LINEMODE
/*
 * local varibles
 */
D 2
static char	*def_slcbuf = (char *)0;;
E 2
I 2
D 4
static char	*def_slcbuf = (char *)0;
E 2
static int	def_slclen = 0;
static int	slcchange;	/* change to slc is requested */
static char	*slcptr;	/* pointer into slc buffer */
static char	slcbuf[NSLC*6];	/* buffer for slc negotiation */
E 4
I 4
static unsigned char	*def_slcbuf = (unsigned char *)0;
static int		def_slclen = 0;
static int		slcchange;	/* change to slc is requested */
static unsigned char	*slcptr;	/* pointer into slc buffer */
static unsigned char	slcbuf[NSLC*6];	/* buffer for slc negotiation */
E 4

/*
 * send_slc
 *
 * Write out the current special characters to the client.
 */
I 7
	void
E 7
send_slc()
{
	register int i;

	/*
	 * Send out list of triplets of special characters
	 * to client.  We only send info on the characters
	 * that are currently supported.
	 */
	for (i = 1; i <= NSLC; i++) {
D 5
		if ((slctab[i].current.flag & SLC_LEVELBITS) != SLC_NOSUPPORT) {
			add_slc((unsigned char)i, slctab[i].current.flag,
E 5
I 5
		if ((slctab[i].defset.flag & SLC_LEVELBITS) == SLC_NOSUPPORT)
			continue;
		add_slc((unsigned char)i, slctab[i].current.flag,
E 5
							slctab[i].current.val);
D 5
		}
E 5
	}

}  /* end of send_slc */

/*
 * default_slc
 *
 * Set pty special characters to all the defaults.
 */
I 7
	void
E 7
default_slc()
{
	register int i;

	for (i = 1; i <= NSLC; i++) {
D 5
		slctab[i].current.flag = slctab[i].defset.flag;
E 5
		slctab[i].current.val = slctab[i].defset.val;
I 5
		if (slctab[i].current.val == (cc_t)(_POSIX_VDISABLE))
			slctab[i].current.flag = SLC_NOSUPPORT;
		else
			slctab[i].current.flag = slctab[i].defset.flag;
E 5
		if (slctab[i].sptr) {
			*(slctab[i].sptr) = slctab[i].defset.val;
		}
	}
	slcchange = 1;

}  /* end of default_slc */
D 7
#endif	LINEMODE
E 7
I 7
#endif	/* LINEMODE */
E 7

/*
 * get_slc_defaults
 *
 * Initialize the slc mapping table.
 */
I 7
	void
E 7
get_slc_defaults()
{
	register int i;

	init_termbuf();

	for (i = 1; i <= NSLC; i++) {
D 10
		slctab[i].defset.flag = 
E 10
I 10
		slctab[i].defset.flag =
E 10
			spcset(i, &slctab[i].defset.val, &slctab[i].sptr);
D 10
		slctab[i].current.flag = SLC_NOSUPPORT; 
		slctab[i].current.val = 0; 
E 10
I 10
		slctab[i].current.flag = SLC_NOSUPPORT;
		slctab[i].current.val = 0;
E 10
	}

}  /* end of get_slc_defaults */

#ifdef	LINEMODE
/*
 * add_slc
 *
 * Add an slc triplet to the slc buffer.
 */
I 7
	void
E 7
add_slc(func, flag, val)
D 2
	register unsigned char func, flag, val;
E 2
I 2
D 7
	register unsigned char func, flag;
	cc_t val;
E 7
I 7
	register char func, flag;
	register cc_t val;
E 7
E 2
{

D 2
	if (func == 0xff)
E 2
I 2
D 7
	if ((*slcptr++ = func) == 0xff)
E 7
I 7
	if ((*slcptr++ = (unsigned char)func) == 0xff)
E 7
E 2
		*slcptr++ = 0xff;
D 2
	*slcptr++ = func;
E 2

D 2
	if (flag == 0xff)
E 2
I 2
D 7
	if ((*slcptr++ = flag) == 0xff)
E 7
I 7
	if ((*slcptr++ = (unsigned char)flag) == 0xff)
E 7
E 2
		*slcptr++ = 0xff;
D 2
	*slcptr++ = flag;
E 2

D 2
	if (val == 0xff)
E 2
I 2
	if ((*slcptr++ = (unsigned char)val) == 0xff)
E 2
		*slcptr++ = 0xff;
D 2
	*slcptr++ = val;
E 2

}  /* end of add_slc */

/*
 * start_slc
 *
 * Get ready to process incoming slc's and respond to them.
 *
 * The parameter getit is non-zero if it is necessary to grab a copy
 * of the terminal control structures.
 */
I 7
	void
E 7
start_slc(getit)
	register int getit;
{

	slcchange = 0;
	if (getit)
		init_termbuf();
D 6
	(void) sprintf(slcbuf, "%c%c%c%c", IAC, SB, TELOPT_LINEMODE, LM_SLC);
E 6
I 6
D 7
	(void) sprintf((char *)slcbuf,
	    "%c%c%c%c", IAC, SB, TELOPT_LINEMODE, LM_SLC);
E 7
I 7
	(void) sprintf((char *)slcbuf, "%c%c%c%c",
					IAC, SB, TELOPT_LINEMODE, LM_SLC);
E 7
E 6
	slcptr = slcbuf + 4;

}  /* end of start_slc */

/*
 * end_slc
 *
 * Finish up the slc negotiation.  If something to send, then send it.
 */
I 7
	int
E 7
end_slc(bufp)
D 4
register char **bufp;
E 4
I 4
D 7
register unsigned char **bufp;
E 7
I 7
	register unsigned char **bufp;
E 7
E 4
{
	register int len;
	void netflush();

	/*
	 * If a change has occured, store the new terminal control
	 * structures back to the terminal driver.
	 */
	if (slcchange) {
		set_termbuf();
	}

	/*
	 * If the pty state has not yet been fully processed and there is a
	 * deferred slc request from the client, then do not send any
	 * sort of slc negotiation now.  We will respond to the client's
	 * request very soon.
	 */
	if (def_slcbuf && (terminit() == 0)) {
D 7
		return;
E 7
I 7
		return(0);
E 7
	}

	if (slcptr > (slcbuf + 4)) {
		if (bufp) {
			*bufp = &slcbuf[4];
			return(slcptr - slcbuf - 4);
		} else {
D 6
			(void) sprintf(slcptr, "%c%c", IAC, SE);
E 6
I 6
			(void) sprintf((char *)slcptr, "%c%c", IAC, SE);
E 6
			slcptr += 2;
			len = slcptr - slcbuf;
			writenet(slcbuf, len);
			netflush();  /* force it out immediately */
I 8
			DIAG(TD_OPTIONS, printsub('>', slcbuf+2, len-2););
E 8
		}
	}
I 7
	return (0);
E 7

}  /* end of end_slc */

/*
 * process_slc
 *
 * Figure out what to do about the client's slc
 */
I 7
	void
E 7
process_slc(func, flag, val)
D 2
	register unsigned char func, flag, val;
E 2
I 2
	register unsigned char func, flag;
D 7
	cc_t val;
E 7
I 7
	register cc_t val;
E 7
E 2
{
	register int hislevel, mylevel, ack;

	/*
	 * Ensure that we know something about this function
	 */
	if (func > NSLC) {
		add_slc(func, SLC_NOSUPPORT, 0);
		return;
	}

	/*
	 * Process the special case requests of 0 SLC_DEFAULT 0
	 * and 0 SLC_VARIABLE 0.  Be a little forgiving here, don't
	 * worry about whether the value is actually 0 or not.
	 */
	if (func == 0) {
		if ((flag = flag & SLC_LEVELBITS) == SLC_DEFAULT) {
			default_slc();
I 5
D 7
			send_slc(1);
E 7
I 7
			send_slc();
E 7
		} else if (flag == SLC_VARIABLE) {
D 7
			send_slc(0);
E 7
I 7
			send_slc();
E 7
E 5
		}
D 5
		if (flag == SLC_DEFAULT || flag == SLC_VARIABLE) {
			send_slc();
		}
E 5
		return;
	}

	/*
	 * Appears to be a function that we know something about.  So
	 * get on with it and see what we know.
	 */

	hislevel = flag & SLC_LEVELBITS;
	mylevel = slctab[func].current.flag & SLC_LEVELBITS;
	ack = flag & SLC_ACK;
	/*
	 * ignore the command if:
	 * the function value and level are the same as what we already have;
	 * or the level is the same and the ack bit is set
	 */
	if (hislevel == mylevel && (val == slctab[func].current.val || ack)) {
		return;
I 5
	} else if (ack) {
		/*
		 * If we get here, we got an ack, but the levels don't match.
		 * This shouldn't happen.  If it does, it is probably because
		 * we have sent two requests to set a variable without getting
		 * a response between them, and this is the first response.
		 * So, ignore it, and wait for the next response.
		 */
		return;
E 5
	} else {
		change_slc(func, flag, val);
	}

}  /* end of process_slc */

/*
 * change_slc
 *
 * Process a request to change one of our special characters.
 * Compare client's request with what we are capable of supporting.
 */
I 7
	void
E 7
change_slc(func, flag, val)
D 2
	register unsigned char func, flag, val;
E 2
I 2
D 7
	register unsigned char func, flag;
	cc_t val;
E 7
I 7
	register char func, flag;
	register cc_t val;
E 7
E 2
{
	register int hislevel, mylevel;
D 10
	
E 10
I 10

E 10
	hislevel = flag & SLC_LEVELBITS;
	mylevel = slctab[func].defset.flag & SLC_LEVELBITS;
	/*
	 * If client is setting a function to NOSUPPORT
	 * or DEFAULT, then we can easily and directly
	 * accomodate the request.
	 */
	if (hislevel == SLC_NOSUPPORT) {
		slctab[func].current.flag = flag;
D 5
		slctab[func].current.val = val;
E 5
I 5
		slctab[func].current.val = (cc_t)_POSIX_VDISABLE;
E 5
		flag |= SLC_ACK;
		add_slc(func, flag, val);
		return;
	}
	if (hislevel == SLC_DEFAULT) {
		/*
		 * Special case here.  If client tells us to use
		 * the default on a function we don't support, then
		 * return NOSUPPORT instead of what we may have as a
		 * default level of DEFAULT.
		 */
		if (mylevel == SLC_DEFAULT) {
			slctab[func].current.flag = SLC_NOSUPPORT;
		} else {
			slctab[func].current.flag = slctab[func].defset.flag;
		}
		slctab[func].current.val = slctab[func].defset.val;
		add_slc(func, slctab[func].current.flag,
						slctab[func].current.val);
		return;
	}

	/*
	 * Client wants us to change to a new value or he
	 * is telling us that he can't change to our value.
	 * Some of the slc's we support and can change,
	 * some we do support but can't change,
	 * and others we don't support at all.
	 * If we can change it then we have a pointer to
	 * the place to put the new value, so change it,
	 * otherwise, continue the negotiation.
	 */
	if (slctab[func].sptr) {
		/*
		 * We can change this one.
		 */
		slctab[func].current.val = val;
		*(slctab[func].sptr) = val;
		slctab[func].current.flag = flag;
		flag |= SLC_ACK;
		slcchange = 1;
		add_slc(func, flag, val);
	} else {
		/*
		* It is not possible for us to support this
		* request as he asks.
		*
		* If our level is DEFAULT, then just ack whatever was
D 10
		* sent. 
E 10
I 10
		* sent.
E 10
		*
		* If he can't change and we can't change,
		* then degenerate to NOSUPPORT.
		*
		* Otherwise we send our level back to him, (CANTCHANGE
		* or NOSUPPORT) and if CANTCHANGE, send
		* our value as well.
		*/
		if (mylevel == SLC_DEFAULT) {
			slctab[func].current.flag = flag;
			slctab[func].current.val = val;
			flag |= SLC_ACK;
		} else if (hislevel == SLC_CANTCHANGE &&
				    mylevel == SLC_CANTCHANGE) {
			flag &= ~SLC_LEVELBITS;
			flag |= SLC_NOSUPPORT;
			slctab[func].current.flag = flag;
		} else {
			flag &= ~SLC_LEVELBITS;
			flag |= mylevel;
			slctab[func].current.flag = flag;
			if (mylevel == SLC_CANTCHANGE) {
				slctab[func].current.val =
					slctab[func].defset.val;
				val = slctab[func].current.val;
			}
D 10
			
E 10
		}
		add_slc(func, flag, val);
	}

}  /* end of change_slc */

I 2
D 5
#if	defined(USE_TERMIO) && defined(SYSV_TERMIO)
E 5
I 5
#if	defined(USE_TERMIO) && (VEOF == VMIN)
E 5
cc_t oldeofc = '\004';
#endif

E 2
/*
 * check_slc
 *
 * Check the special characters in use and notify the client if any have
 * changed.  Only those characters that are capable of being changed are
 * likely to have changed.  If a local change occurs, kick the support level
 * and flags up to the defaults.
 */
I 7
	void
E 7
check_slc()
{
	register int i;

	for (i = 1; i <= NSLC; i++) {
D 5
#if	defined(USE_TERMIO) && defined(SYSV_TERMIO)
E 5
I 5
#if	defined(USE_TERMIO) && (VEOF == VMIN)
E 5
		/*
		 * In a perfect world this would be a neat little
		 * function.  But in this world, we should not notify
		 * client of changes to the VEOF char when
		 * ICANON is off, because it is not representing
		 * a special character.
		 */
D 2
		if (!tty_isediting() && i == SLC_EOF)
			continue;
E 2
I 2
		if (i == SLC_EOF) {
			if (!tty_isediting())
				continue;
			else if (slctab[i].sptr)
				oldeofc = *(slctab[i].sptr);
		}
E 2
#endif	/* defined(USE_TERMIO) && defined(SYSV_TERMIO) */
		if (slctab[i].sptr &&
				(*(slctab[i].sptr) != slctab[i].current.val)) {
			slctab[i].current.val = *(slctab[i].sptr);
D 5
			slctab[i].current.flag = slctab[i].defset.flag;
E 5
I 5
			if (*(slctab[i].sptr) == (cc_t)_POSIX_VDISABLE)
				slctab[i].current.flag = SLC_NOSUPPORT;
			else
				slctab[i].current.flag = slctab[i].defset.flag;
E 5
			add_slc((unsigned char)i, slctab[i].current.flag,
						slctab[i].current.val);
		}
	}
D 10
			
E 10
}  /* check_slc */

/*
 * do_opt_slc
 *
 * Process an slc option buffer.  Defer processing of incoming slc's
 * until after the terminal state has been processed.  Save the first slc
 * request that comes along, but discard all others.
 *
 * ptr points to the beginning of the buffer, len is the length.
 */
I 7
	void
E 7
do_opt_slc(ptr, len)
D 7
register char *ptr;
register int len;
E 7
I 7
	register unsigned char *ptr;
	register int len;
E 7
{
D 2
	register unsigned char func, flag, val;
E 2
I 2
	register unsigned char func, flag;
	cc_t val;
E 2
D 7
	register char *end = (char *)(ptr + len);
	char *malloc();
E 7
I 7
	register unsigned char *end = ptr + len;
E 7

	if (terminit()) {  /* go ahead */
		while (ptr < end) {
			func = *ptr++;
			if (ptr >= end) break;
			flag = *ptr++;
			if (ptr >= end) break;
D 2
			val = *ptr++;
E 2
I 2
			val = (cc_t)*ptr++;
E 2

			process_slc(func, flag, val);

		}
	} else {
		/*
		 * save this slc buffer if it is the first, otherwise dump
		 * it.
		 */
D 4
		if (def_slcbuf == (char *)0) {
E 4
I 4
		if (def_slcbuf == (unsigned char *)0) {
E 4
			def_slclen = len;
D 4
			def_slcbuf = malloc((unsigned)len);
			if (def_slcbuf == (char *)0)
E 4
I 4
			def_slcbuf = (unsigned char *)malloc((unsigned)len);
			if (def_slcbuf == (unsigned char *)0)
E 4
				return;  /* too bad */
D 10
			bcopy(ptr, def_slcbuf, len);
E 10
I 10
			memmove(def_slcbuf, ptr, len);
E 10
		}
	}

}  /* end of do_opt_slc */

/*
 * deferslc
 *
 * Do slc stuff that was deferred.
 */
I 7
	void
E 7
deferslc()
{
	if (def_slcbuf) {
		start_slc(1);
		do_opt_slc(def_slcbuf, def_slclen);
D 7
		end_slc(0);
E 7
I 7
		(void) end_slc(0);
E 7
		free(def_slcbuf);
D 4
		def_slcbuf = (char *)0;
E 4
I 4
		def_slcbuf = (unsigned char *)0;
E 4
		def_slclen = 0;
	}

}  /* end of deferslc */

#endif	/* LINEMODE */
E 1
