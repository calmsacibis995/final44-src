h02565
s 00008/00008/00626
d D 8.2 95/05/30 22:02:50 dab 16 15
c code cleanup, change b*() to mem*()
c Add setting up of LINEMODE environment variable.
e
s 00002/00002/00632
d D 8.1 93/06/04 19:07:30 bostic 15 14
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00632
d D 5.14 93/05/20 11:37:59 dab 14 13
c Several fixes.  The big one is that all of the
c code that was "#if defined(ENCRYPTION)" is now changed
c to "#ifdef ENCRYPTION", so that all the encryption code
c can be stripped out using unifdef.
c Other fixes:
c 	Add support for HP-UX (untested...)
c 	Simplification of the ENV_HACK stuff
c 	Add in UNICOS 8.0 secure system changes
c 	Clean up the option processing
c 	Fix up the usage() statement
e
s 00029/00019/00605
d D 5.13 93/04/05 16:48:20 dab 13 12
c Fix gcc2 warnings.
c Add ENV_HACK stuff to deal with telnet clients that
c have the wrong definitions for ENV_VAR and ENV_VALUE.
c Fix up the flow-control processing to work on systems
c that don't use Linemode in the server.
e
s 00007/00006/00617
d D 5.12 93/01/19 12:47:17 dab 12 11
c Fix up the code that deals with the
c flowcontrol option to properly deal with the
c RESTART_ANY and RESTART_XON suboptions.
e
s 00021/00003/00602
d D 5.11 92/12/18 14:05:42 dab 11 10
c Change ENCRYPT to ENCRYPTION
c Change AUTHENTICATE to AUTHENTICATION
c Add Sun/SVR4 Streams support
c Allow for more ptys
c Environ suboption USERVAR support
c New Telnet Flowcontrol suboption support
c Server -k option to default to no kludge linemode
c Server -U option, allow only registered hosts to connect
e
s 00020/00000/00585
d D 5.10 91/03/22 13:16:38 dab 10 9
c Upgrade to the latest & greatest authentication/encryption
e
s 00053/00022/00532
d D 5.9 91/03/01 01:35:20 dab 9 8
c Telnet AUTHENTICATION option
c Telnet ENCRYPT option (test version)
c Function prototypes
c Bug fixes and code cleanup
e
s 00001/00001/00553
d D 5.8 91/02/02 08:32:26 bostic 8 7
c tty_istrapsig is a function
e
s 00007/00005/00547
d D 5.7 90/09/14 11:26:41 borman 7 6
c Latest round of bug fixes.  See the README file
c in src/usr.bin/telnet/README for the details.
e
s 00032/00029/00520
d D 5.6 90/06/28 13:06:55 borman 6 5
c Lots of bugfixes, add the ENVIRON and X-DISPLAY-LOC
c options, "-l user" to the command line, diagnostic flags.
e
s 00001/00011/00548
d D 5.5 90/06/01 15:56:37 bostic 5 4
c new copyright notice
e
s 00011/00009/00548
d D 5.4 90/02/28 15:36:05 borman 4 3
c Many fixes.  1) Use the cc_t typedef from termios.h
c 2) Fix for SYSV VEOF/VMIN overlap
c 3) Add two missing "break" statements
c 4) Add SLC_FORW[12] support
c 5) start of TOS support
c 6) Make sure things get initialized properly
c 7) Don't send Urgent mode data, since some clients go into infinate loops...
e
s 00001/00001/00556
d D 5.3 89/11/14 10:43:55 borman 3 2
c Bug fixes to the state machine
e
s 00012/00012/00545
d D 5.2 89/11/10 10:22:51 borman 2 1
c Fix bugs in state machine, add more TERMIOS support
e
s 00557/00000/00000
d D 5.1 89/09/01 15:17:54 borman 1 0
c New telnetd, with LINEMODE support
e
u
U
t
T
I 1
/*
D 15
 * Copyright (c) 1989 Regents of the University of California.
 * All rights reserved.
E 15
I 15
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 15
 *
D 5
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
E 5
I 5
 * %sccs.include.redist.c%
E 5
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include "telnetd.h"

/*
 * local variables
 */
D 9
#ifdef	LINEMODE
static int _terminit = 0;
static int def_tspeed = -1, def_rspeed = -1;
E 9
I 9
int def_tspeed = -1, def_rspeed = -1;
E 9
#ifdef	TIOCSWINSZ
D 9
static int def_row = 0, def_col = 0;
E 9
I 9
int def_row = 0, def_col = 0;
E 9
#endif
D 9
#endif	LINEMODE
E 9
I 9
#ifdef	LINEMODE
static int _terminit = 0;
#endif	/* LINEMODE */
E 9

D 4
#ifdef	CRAY2
E 4
I 4
#if	defined(CRAY2) && defined(UNICOS5)
E 4
int	newmap = 1;	/* nonzero if \n maps to ^M^J */
#endif

#ifdef	LINEMODE
/*
 * localstat
 *
 * This function handles all management of linemode.
 *
 * Linemode allows the client to do the local editing of data
 * and send only complete lines to the server.  Linemode state is
 * based on the state of the pty driver.  If the pty is set for
 * external processing, then we can use linemode.  Further, if we
 * can use real linemode, then we can look at the edit control bits
 * in the pty to determine what editing the client should do.
 *
 * Linemode support uses the following state flags to keep track of
 * current and desired linemode state.
 *	alwayslinemode : true if -l was specified on the telnetd
 * 	command line.  It means to have linemode on as much as
 *	possible.
 *
 * 	lmodetype: signifies whether the client can
 *	handle real linemode, or if use of kludgeomatic linemode
 *	is preferred.  It will be set to one of the following:
 *		REAL_LINEMODE : use linemode option
I 11
 *		NO_KLUDGE : don't initiate kludge linemode.
E 11
 *		KLUDGE_LINEMODE : use kludge linemode
 *		NO_LINEMODE : client is ignorant of linemode
 *
 *	linemode, uselinemode : linemode is true if linemode
 *	is currently on, uselinemode is the state that we wish
 *	to be in.  If another function wishes to turn linemode
 *	on or off, it sets or clears uselinemode.
 *
 *	editmode, useeditmode : like linemode/uselinemode, but
 *	these contain the edit mode states (edit and trapsig).
 *
 * The state variables correspond to some of the state information
 * in the pty.
 *	linemode:
 *		In real linemode, this corresponds to whether the pty
 *		expects external processing of incoming data.
 *		In kludge linemode, this more closely corresponds to the
 *		whether normal processing is on or not.  (ICANON in
 *		system V, or COOKED mode in BSD.)
 *		If the -l option was specified (alwayslinemode), then
 *		an attempt is made to force external processing on at
 *		all times.
 *
 * The following heuristics are applied to determine linemode
 * handling within the server.
 *	1) Early on in starting up the server, an attempt is made
 *	   to negotiate the linemode option.  If this succeeds
 *	   then lmodetype is set to REAL_LINEMODE and all linemode
 *	   processing occurs in the context of the linemode option.
 *	2) If the attempt to negotiate the linemode option failed,
I 11
 *	   and the "-k" (don't initiate kludge linemode) isn't set,
E 11
 *	   then we try to use kludge linemode.  We test for this
 *	   capability by sending "do Timing Mark".  If a positive
 *	   response comes back, then we assume that the client
 *	   understands kludge linemode (ech!) and the
 *	   lmodetype flag is set to KLUDGE_LINEMODE.
 *	3) Otherwise, linemode is not supported at all and
 *	   lmodetype remains set to NO_LINEMODE (which happens
 *	   to be 0 for convenience).
 *	4) At any time a command arrives that implies a higher
 *	   state of linemode support in the client, we move to that
 *	   linemode support.
 *
 * A short explanation of kludge linemode is in order here.
 *	1) The heuristic to determine support for kludge linemode
 *	   is to send a do timing mark.  We assume that a client
 *	   that supports timing marks also supports kludge linemode.
 *	   A risky proposition at best.
 *	2) Further negotiation of linemode is done by changing the
 *	   the server's state regarding SGA.  If server will SGA,
 *	   then linemode is off, if server won't SGA, then linemode
 *	   is on.
 */
I 9
	void
E 9
localstat()
{
	void netflush();
I 9
	int need_will_echo = 0;
E 9

D 4
#ifdef	CRAY2
E 4
I 4
D 6
#ifdef	defined(CRAY2) && defined(UNICOS5)
E 6
I 6
#if	defined(CRAY2) && defined(UNICOS5)
E 6
E 4
	/*
	 * Keep track of that ol' CR/NL mapping while we're in the
	 * neighborhood.
	 */
	newmap = tty_isnewmap();
D 4
#endif	/* CRAY2 */
E 4
I 4
D 9
#endif	defined(CRAY2) && defined(UNICOS5)
E 9
I 9
#endif	/* defined(CRAY2) && defined(UNICOS5) */
E 9
E 4

	/*
	 * Check for state of BINARY options.
	 */
	if (tty_isbinaryin()) {
D 6
		if (hiswants[TELOPT_BINARY] == OPT_NO)
E 6
I 6
		if (his_want_state_is_wont(TELOPT_BINARY))
E 6
D 2
			willoption(TELOPT_BINARY, 1);
E 2
I 2
			send_do(TELOPT_BINARY, 1);
E 2
	} else {
D 6
		if (hiswants[TELOPT_BINARY] == OPT_YES)
E 6
I 6
		if (his_want_state_is_will(TELOPT_BINARY))
E 6
D 2
			wontoption(TELOPT_BINARY, 1);
E 2
I 2
			send_dont(TELOPT_BINARY, 1);
E 2
	}

	if (tty_isbinaryout()) {
D 6
		if (mywants[TELOPT_BINARY] == OPT_NO)
E 6
I 6
		if (my_want_state_is_wont(TELOPT_BINARY))
E 6
D 2
			dooption(TELOPT_BINARY, 1);
E 2
I 2
			send_will(TELOPT_BINARY, 1);
E 2
	} else {
D 6
		if (mywants[TELOPT_BINARY] == OPT_YES)
E 6
I 6
		if (my_want_state_is_will(TELOPT_BINARY))
E 6
D 2
			dontoption(TELOPT_BINARY, 1);
E 2
I 2
			send_wont(TELOPT_BINARY, 1);
E 2
	}

	/*
	 * Check for changes to flow control if client supports it.
	 */
D 6
	if (hisopts[TELOPT_LFLOW] == OPT_YES) {
E 6
I 6
D 13
	if (his_state_is_will(TELOPT_LFLOW)) {
E 6
		if (tty_flowmode() != flowmode) {
			flowmode = tty_flowmode();
D 12
			(void) sprintf(nfrontp, "%c%c%c%c%c%c", IAC, SB,
D 11
				TELOPT_LFLOW, flowmode, IAC, SE);
E 11
I 11
				TELOPT_LFLOW, flowmode ? LFLOW_ON : LFLOW_OFF,
				IAC, SE);
E 12
I 12
			(void) sprintf(nfrontp, "%c%c%c%c%c%c",
					IAC, SB, TELOPT_LFLOW,
					flowmode ? LFLOW_ON : LFLOW_OFF,
					IAC, SE);
E 12
E 11
			nfrontp += 6;
I 12
		}
		if (tty_restartany() != restartany) {
E 12
I 11
			restartany = tty_restartany();
D 12
			if (restartany >= 0) {
				(void) sprintf(nfrontp, "%c%c%c%c%c%c",
E 12
I 12
			(void) sprintf(nfrontp, "%c%c%c%c%c%c",
E 12
					IAC, SB, TELOPT_LFLOW,
					restartany ? LFLOW_RESTART_ANY
						   : LFLOW_RESTART_XON,
					IAC, SE);
D 12
			}
E 12
			nfrontp += 6;
E 11
		}
	}
E 13
I 13
	flowstat();
E 13

	/*
	 * Check linemode on/off state
	 */
	uselinemode = tty_linemode();

	/*
	 * If alwayslinemode is on, and pty is changing to turn it off, then
	 * force linemode back on.
	 */
	if (alwayslinemode && linemode && !uselinemode) {
		uselinemode = 1;
		tty_setlinemode(uselinemode);
	}

I 10
D 11
#if	defined(ENCRYPT)
E 11
I 11
D 14
#if	defined(ENCRYPTION)
E 14
I 14
#ifdef	ENCRYPTION
E 14
E 11
	/*
	 * If the terminal is not echoing, but editing is enabled,
	 * something like password input is going to happen, so
	 * if we the other side is not currently sending encrypted
	 * data, ask the other side to start encrypting.
	 */
	if (his_state_is_will(TELOPT_ENCRYPT)) {
		static int enc_passwd = 0;
		if (uselinemode && !tty_isecho() && tty_isediting()
		    && (enc_passwd == 0) && !decrypt_input) {
			encrypt_send_request_start();
			enc_passwd = 1;
		} else if (enc_passwd) {
			encrypt_send_request_end();
			enc_passwd = 0;
		}
	}
D 14
#endif
E 14
I 14
#endif	/* ENCRYPTION */
E 14

E 10
D 6
# ifdef	KLUDGELINEMODE
E 6
	/*
D 6
	 * If using kludge linemode and linemode is desired, it can't
	 * be done if normal line editing is not available on the
	 * pty.  This becomes the test for linemode on/off when
	 * using kludge linemode.
	 */
D 4
	if (lmodetype == KLUDGE_LINEMODE && uselinemode && tty_israw())
E 4
I 4
	if (lmodetype == KLUDGE_LINEMODE && uselinemode && tty_israw()) {
E 4
		uselinemode = 0;
I 4
		tty_setlinemode(uselinemode);
	}
E 4
# endif	/* KLUDGELINEMODE */

	/*
E 6
	 * Do echo mode handling as soon as we know what the
	 * linemode is going to be.
	 * If the pty has echo turned off, then tell the client that
	 * the server will echo.  If echo is on, then the server
	 * will echo if in character mode, but in linemode the
	 * client should do local echoing.  The state machine will
	 * not send anything if it is unnecessary, so don't worry
	 * about that here.
I 9
	 *
	 * If we need to send the WILL ECHO (because echo is off),
	 * then delay that until after we have changed the MODE.
	 * This way, when the user is turning off both editing
	 * and echo, the client will get editing turned off first.
	 * This keeps the client from going into encryption mode
	 * and then right back out if it is doing auto-encryption
	 * when passwords are being typed.
E 9
	 */
D 7
	if (tty_isecho() && uselinemode)
D 2
		dontoption(TELOPT_ECHO, 1);
E 2
I 2
		send_wont(TELOPT_ECHO, 1);
E 2
	else
D 2
		dooption(TELOPT_ECHO, 1);
E 2
I 2
		send_will(TELOPT_ECHO, 1);
E 7
I 7
	if (uselinemode) {
		if (tty_isecho())
			send_wont(TELOPT_ECHO, 1);
		else
D 9
			send_will(TELOPT_ECHO, 1);
E 9
I 9
			need_will_echo = 1;
I 11
#ifdef	KLUDGELINEMODE
		if (lmodetype == KLUDGE_OK)
			lmodetype = KLUDGE_LINEMODE;
#endif
E 11
E 9
	}
E 7
E 2

	/*
	 * If linemode is being turned off, send appropriate
	 * command and then we're all done.
	 */
	 if (!uselinemode && linemode) {
# ifdef	KLUDGELINEMODE
D 9
		if (lmodetype == REAL_LINEMODE)
E 9
I 9
		if (lmodetype == REAL_LINEMODE) {
E 9
# endif	/* KLUDGELINEMODE */
D 2
			wontoption(TELOPT_LINEMODE, 1);
E 2
I 2
			send_dont(TELOPT_LINEMODE, 1);
E 2
# ifdef	KLUDGELINEMODE
D 9
		else if (lmodetype == KLUDGE_LINEMODE)
E 9
I 9
		} else if (lmodetype == KLUDGE_LINEMODE)
E 9
D 2
			dooption(TELOPT_SGA, 1);
E 2
I 2
D 3
			send_wont(TELOPT_SGA, 1);
E 3
I 3
			send_will(TELOPT_SGA, 1);
E 3
E 2
# endif	/* KLUDGELINEMODE */
I 9
		send_will(TELOPT_ECHO, 1);
E 9
		linemode = uselinemode;
		goto done;
	}

# ifdef	KLUDGELINEMODE
	/*
	 * If using real linemode check edit modes for possible later use.
I 6
	 * If we are in kludge linemode, do the SGA negotiation.
E 6
	 */
	if (lmodetype == REAL_LINEMODE) {
# endif	/* KLUDGELINEMODE */
		useeditmode = 0;
		if (tty_isediting())
			useeditmode |= MODE_EDIT;
		if (tty_istrapsig())
			useeditmode |= MODE_TRAPSIG;
I 6
		if (tty_issofttab())
			useeditmode |= MODE_SOFT_TAB;
		if (tty_islitecho())
			useeditmode |= MODE_LIT_ECHO;
E 6
# ifdef	KLUDGELINEMODE
I 6
	} else if (lmodetype == KLUDGE_LINEMODE) {
		if (tty_isediting() && uselinemode)
			send_wont(TELOPT_SGA, 1);
		else
			send_will(TELOPT_SGA, 1);
E 6
	}
# endif	/* KLUDGELINEMODE */

	/*
	 * Negotiate linemode on if pty state has changed to turn it on.
	 * Send appropriate command and send along edit mode, then all done.
	 */
	if (uselinemode && !linemode) {
# ifdef	KLUDGELINEMODE
		if (lmodetype == KLUDGE_LINEMODE) {
D 2
			dontoption(TELOPT_SGA, 1);
E 2
I 2
			send_wont(TELOPT_SGA, 1);
E 2
		} else if (lmodetype == REAL_LINEMODE) {
# endif	/* KLUDGELINEMODE */
D 2
			willoption(TELOPT_LINEMODE, 1);
E 2
I 2
			send_do(TELOPT_LINEMODE, 1);
E 2
			/* send along edit modes */
			(void) sprintf(nfrontp, "%c%c%c%c%c%c%c", IAC, SB,
				TELOPT_LINEMODE, LM_MODE, useeditmode,
				IAC, SE);
			nfrontp += 7;
			editmode = useeditmode;
# ifdef	KLUDGELINEMODE
		}
# endif	/* KLUDGELINEMODE */
		linemode = uselinemode;
		goto done;
	}

# ifdef	KLUDGELINEMODE
	/*
	 * None of what follows is of any value if not using
	 * real linemode.
	 */
	if (lmodetype < REAL_LINEMODE)
		goto done;
# endif	/* KLUDGELINEMODE */

D 7
	if (linemode) {
E 7
I 7
	if (linemode && his_state_is_will(TELOPT_LINEMODE)) {
E 7
		/*
		 * If edit mode changed, send edit mode.
		 */
		 if (useeditmode != editmode) {
			/*
			 * Send along appropriate edit mode mask.
			 */
			(void) sprintf(nfrontp, "%c%c%c%c%c%c%c", IAC, SB,
				TELOPT_LINEMODE, LM_MODE, useeditmode,
				IAC, SE);
			nfrontp += 7;
			editmode = useeditmode;
		}
D 16
							
E 16

I 16

E 16
		/*
		 * Check for changes to special characters in use.
		 */
		start_slc(0);
		check_slc();
D 9
		end_slc(0);
E 9
I 9
		(void) end_slc(0);
E 9
	}

done:
I 9
	if (need_will_echo)
		send_will(TELOPT_ECHO, 1);
E 9
	/*
	 * Some things should be deferred until after the pty state has
	 * been set by the local process.  Do those things that have been
	 * deferred now.  This only happens once.
	 */
	if (_terminit == 0) {
		_terminit = 1;
		defer_terminit();
	}

	netflush();
	set_termbuf();
	return;

}  /* end of localstat */
#endif	/* LINEMODE */

I 13
/*
 * flowstat
 *
 * Check for changes to flow control
 */
	void
flowstat()
{
	if (his_state_is_will(TELOPT_LFLOW)) {
		if (tty_flowmode() != flowmode) {
			flowmode = tty_flowmode();
			(void) sprintf(nfrontp, "%c%c%c%c%c%c",
					IAC, SB, TELOPT_LFLOW,
					flowmode ? LFLOW_ON : LFLOW_OFF,
					IAC, SE);
			nfrontp += 6;
		}
		if (tty_restartany() != restartany) {
			restartany = tty_restartany();
			(void) sprintf(nfrontp, "%c%c%c%c%c%c",
					IAC, SB, TELOPT_LFLOW,
					restartany ? LFLOW_RESTART_ANY
						   : LFLOW_RESTART_XON,
					IAC, SE);
			nfrontp += 6;
		}
	}
}
E 13

/*
 * clientstat
 *
 * Process linemode related requests from the client.
 * Client can request a change to only one of linemode, editmode or slc's
 * at a time, and if using kludge linemode, then only linemode may be
 * affected.
 */
I 9
	void
E 9
clientstat(code, parm1, parm2)
D 9
register int code, parm1, parm2;
E 9
I 9
	register int code, parm1, parm2;
E 9
{
	void netflush();

	/*
	 * Get a copy of terminal characteristics.
	 */
	init_termbuf();

	/*
	 * Process request from client. code tells what it is.
	 */
	switch (code) {
#ifdef	LINEMODE
	case TELOPT_LINEMODE:
		/*
		 * Don't do anything unless client is asking us to change
		 * modes.
		 */
		uselinemode = (parm1 == WILL);
		if (uselinemode != linemode) {
# ifdef	KLUDGELINEMODE
			/*
			 * If using kludge linemode, make sure that
			 * we can do what the client asks.
			 * We can not turn off linemode if alwayslinemode
D 2
			 * or if the ICANON bit is set.
E 2
I 2
			 * and the ICANON bit is set.
E 2
			 */
			if (lmodetype == KLUDGE_LINEMODE) {
D 2
				if (alwayslinemode || tty_isediting()) {
E 2
I 2
				if (alwayslinemode && tty_isediting()) {
E 2
					uselinemode = 1;
				}
			}
D 16
		
E 16
I 16

E 16
			/*
			 * Quit now if we can't do it.
			 */
			if (uselinemode == linemode)
				return;

			/*
			 * If using real linemode and linemode is being
			 * turned on, send along the edit mode mask.
			 */
			if (lmodetype == REAL_LINEMODE && uselinemode)
# else	/* KLUDGELINEMODE */
			if (uselinemode)
# endif	/* KLUDGELINEMODE */
			{
				useeditmode = 0;
				if (tty_isediting())
					useeditmode |= MODE_EDIT;
D 8
				if (tty_istrapsig)
E 8
I 8
D 9
				if (tty_istrapsig())
E 9
I 9
				if (tty_istrapsig)
E 9
E 8
					useeditmode |= MODE_TRAPSIG;
I 6
				if (tty_issofttab())
					useeditmode |= MODE_SOFT_TAB;
				if (tty_islitecho())
					useeditmode |= MODE_LIT_ECHO;
E 6
				(void) sprintf(nfrontp, "%c%c%c%c%c%c%c", IAC,
					SB, TELOPT_LINEMODE, LM_MODE,
							useeditmode, IAC, SE);
				nfrontp += 7;
				editmode = useeditmode;
			}


			tty_setlinemode(uselinemode);

			linemode = uselinemode;

I 11
			if (!linemode)
				send_will(TELOPT_ECHO, 1);
E 11
		}
		break;
D 16
	
E 16
I 16

E 16
	case LM_MODE:
	    {
D 6
		register int mode, sig, ack;
E 6
I 6
		register int ack, changed;
E 6

		/*
		 * Client has sent along a mode mask.  If it agrees with
		 * what we are currently doing, ignore it; if not, it could
		 * be viewed as a request to change.  Note that the server
		 * will change to the modes in an ack if it is different from
		 * what we currently have, but we will not ack the ack.
		 */
		 useeditmode &= MODE_MASK;
		 ack = (useeditmode & MODE_ACK);
		 useeditmode &= ~MODE_ACK;

D 6
		 if (useeditmode != editmode) {
			mode = (useeditmode & MODE_EDIT);
			sig = (useeditmode & MODE_TRAPSIG);
E 6
I 6
		 if (changed = (useeditmode ^ editmode)) {
I 9
			/*
			 * This check is for a timing problem.  If the
			 * state of the tty has changed (due to the user
			 * application) we need to process that info
			 * before we write in the state contained in the
			 * ack!!!  This gets out the new MODE request,
			 * and when the ack to that command comes back
			 * we'll set it and be in the right mode.
			 */
			if (ack)
				localstat();
E 9
			if (changed & MODE_EDIT)
				tty_setedit(useeditmode & MODE_EDIT);
E 6

D 6
			if (mode != (editmode & LM_MODE)) {
				tty_setedit(mode);
			}
			if (sig != (editmode & MODE_TRAPSIG)) {
				tty_setsig(sig);
			}
E 6
I 6
			if (changed & MODE_TRAPSIG)
				tty_setsig(useeditmode & MODE_TRAPSIG);

			if (changed & MODE_SOFT_TAB)
				tty_setsofttab(useeditmode & MODE_SOFT_TAB);

			if (changed & MODE_LIT_ECHO)
				tty_setlitecho(useeditmode & MODE_LIT_ECHO);
E 6

			set_termbuf();

 			if (!ack) {
 				(void) sprintf(nfrontp, "%c%c%c%c%c%c%c", IAC,
					SB, TELOPT_LINEMODE, LM_MODE,
 					useeditmode|MODE_ACK,
 					IAC, SE);
 				nfrontp += 7;
 			}
D 16
 		
E 16
I 16

E 16
			editmode = useeditmode;
		}

		break;

	    }  /* end of case LM_MODE */
#endif	/* LINEMODE */

	case TELOPT_NAWS:
#ifdef	TIOCSWINSZ
	    {
		struct winsize ws;

I 9
		def_col = parm1;
		def_row = parm2;
E 9
#ifdef	LINEMODE
		/*
		 * Defer changing window size until after terminal is
		 * initialized.
		 */
D 9
		if (terminit() == 0) {
			def_col = parm1;
D 4
			def_row = parm1;
E 4
I 4
			def_row = parm2;
E 9
I 9
		if (terminit() == 0)
E 9
E 4
			return;
D 9
		}
E 9
#endif	/* LINEMODE */

		/*
		 * Change window size as requested by client.
		 */

		ws.ws_col = parm1;
		ws.ws_row = parm2;
		(void) ioctl(pty, TIOCSWINSZ, (char *)&ws);
	    }
#endif	/* TIOCSWINSZ */
D 16
		
E 16
I 16

E 16
		break;
D 16
	
E 16
I 16

E 16
	case TELOPT_TSPEED:
	    {
I 9
		def_tspeed = parm1;
		def_rspeed = parm2;
E 9
#ifdef	LINEMODE
		/*
		 * Defer changing the terminal speed.
		 */
D 9
		if (terminit() == 0) {
			def_tspeed = parm1;
			def_rspeed = parm2;
E 9
I 9
		if (terminit() == 0)
E 9
			return;
D 9
		}
E 9
#endif	/* LINEMODE */
		/*
		 * Change terminal speed as requested by client.
I 9
		 * We set the receive speed first, so that if we can't
		 * store seperate receive and transmit speeds, the transmit
		 * speed will take precedence.
E 9
		 */
D 9
		tty_tspeed(parm1);
E 9
		tty_rspeed(parm2);
I 9
		tty_tspeed(parm1);
E 9
		set_termbuf();

		break;

	    }  /* end of case TELOPT_TSPEED */

	default:
		/* What? */
		break;
	}  /* end of switch */

D 4
#ifdef CRAY2
E 4
I 4
#if	defined(CRAY2) && defined(UNICOS5)
E 4
	/*
	 * Just in case of the likely event that we changed the pty state.
	 */
	rcv_ioctl();
D 4
#endif /* CRAY2 */
E 4
I 4
#endif	/* defined(CRAY2) && defined(UNICOS5) */
E 4

	netflush();

}  /* end of clientstat */

D 4
#ifdef	CRAY2
E 4
I 4
#if	defined(CRAY2) && defined(UNICOS5)
I 9
	void
E 9
E 4
termstat()
{
	needtermstat = 1;
}

I 9
	void
E 9
_termstat()
{
	needtermstat = 0;
	init_termbuf();
	localstat();
	rcv_ioctl();
}
D 4
#endif	/* CRAY2 */
E 4
I 4
#endif	/* defined(CRAY2) && defined(UNICOS5) */
E 4

#ifdef	LINEMODE
/*
 * defer_terminit
 *
 * Some things should not be done until after the login process has started
 * and all the pty modes are set to what they are supposed to be.  This
D 16
 * function is called when the pty state has been processed for the first time. 
E 16
I 16
 * function is called when the pty state has been processed for the first time.
E 16
 * It calls other functions that do things that were deferred in each module.
 */
I 9
	void
E 9
defer_terminit()
{

	/*
	 * local stuff that got deferred.
	 */
	if (def_tspeed != -1) {
		clientstat(TELOPT_TSPEED, def_tspeed, def_rspeed);
		def_tspeed = def_rspeed = 0;
	}

#ifdef	TIOCSWINSZ
	if (def_col || def_row) {
		struct winsize ws;

I 9
D 16
		bzero((char *)&ws, sizeof(ws));
E 16
I 16
		memset((char *)&ws, 0, sizeof(ws));
E 16
E 9
		ws.ws_col = def_col;
		ws.ws_row = def_row;
		(void) ioctl(pty, TIOCSWINSZ, (char *)&ws);
	}
#endif

	/*
	 * The only other module that currently defers anything.
	 */
	deferslc();

}  /* end of defer_terminit */

/*
 * terminit
 *
 * Returns true if the pty state has been processed yet.
 */
D 9
int terminit()
E 9
I 9
	int
terminit()
E 9
{
D 11
	return _terminit;
E 11
I 11
	return(_terminit);
E 11

}  /* end of terminit */
#endif	/* LINEMODE */
E 1
