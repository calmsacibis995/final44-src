h36828
s 00002/00002/01584
d D 8.5 95/05/30 22:02:44 dab 19 18
c code cleanup, change b*() to mem*()
c Add setting up of LINEMODE environment variable.
e
s 00000/00001/01586
d D 8.4 95/02/20 16:20:51 dab 18 17
c When Linemode was getting turned off, we were changing
c the "lmodetype" to KLUDGE_LINEMODE, even though we know that the
c client supports REAL_LINEMODE.  We now just leave "lmodetype"
c alone when we get WONT LINEMODE.
e
s 00004/00011/01583
d D 8.3 95/02/16 11:50:38 dab 17 16
c Clean up how suboptions are put together to ensure that
c we always double any SE or IAC that is imbedded in the suboption.
e
s 00089/00063/01505
d D 8.2 93/12/15 11:39:57 dab 16 15
c A bunch of bugfixes.
c Support for Solaris.
c new LOGIN_R option for systems that
c don't have "login -f".
c Support for the new ENVIRON option.
e
s 00002/00002/01566
d D 8.1 93/06/04 19:07:07 bostic 15 14
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00015/00023/01553
d D 5.14 93/05/20 11:38:02 dab 14 13
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
s 00135/00004/01441
d D 5.13 93/04/05 16:48:23 dab 13 12
c Fix gcc2 warnings.
c Add ENV_HACK stuff to deal with telnet clients that
c have the wrong definitions for ENV_VAR and ENV_VALUE.
c Fix up the flow-control processing to work on systems
c that don't use Linemode in the server.
e
s 00003/00000/01442
d D 5.12 93/01/19 12:47:20 dab 12 11
c Fix up the code that deals with the
c flowcontrol option to properly deal with the
c RESTART_ANY and RESTART_XON suboptions.
e
s 00047/00022/01395
d D 5.11 92/12/18 14:05:48 dab 11 10
c Change ENCRYPT to ENCRYPTION
c Change AUTHENTICATE to AUTHENTICATION
c Add Sun/SVR4 Streams support
c Allow for more ptys
c Environ suboption USERVAR support
c New Telnet Flowcontrol suboption support
c Server -k option to default to no kludge linemode
c Server -U option, allow only registered hosts to connect
e
s 00011/00002/01406
d D 5.10 91/03/22 13:16:34 dab 10 9
c Upgrade to the latest & greatest authentication/encryption
e
s 00253/00154/01155
d D 5.9 91/03/01 01:35:14 dab 9 8
c Telnet AUTHENTICATION option
c Telnet ENCRYPT option (test version)
c Function prototypes
c Bug fixes and code cleanup
e
s 00038/00011/01271
d D 5.8 90/09/14 11:26:33 borman 8 7
c Latest round of bug fixes.  See the README file
c in src/usr.bin/telnet/README for the details.
e
s 00339/00101/00943
d D 5.7 90/06/28 13:06:09 borman 7 6
c Lots of bugfixes, add the ENVIRON and X-DISPLAY-LOC
c options, "-l user" to the command line, diagnostic flags.
e
s 00001/00011/01043
d D 5.6 90/06/01 15:56:03 bostic 6 5
c new copyright notice
e
s 00013/00013/01041
d D 5.5 90/02/28 15:35:52 borman 5 4
c Many fixes.  1) Use the cc_t typedef from termios.h
c 2) Fix for SYSV VEOF/VMIN overlap
c 3) Add two missing "break" statements
c 4) Add SLC_FORW[12] support
c 5) start of TOS support
c 6) Make sure things get initialized properly
c 7) Don't send Urgent mode data, since some clients go into infinate loops...
e
s 00043/00048/01011
d D 5.4 89/11/14 10:43:47 borman 4 3
c Bug fixes to the state machine
e
s 00219/00194/00840
d D 5.3 89/11/10 10:22:41 borman 3 2
c Fix bugs in state machine, add more TERMIOS support
e
s 00001/00001/01033
d D 5.2 89/09/05 13:42:16 borman 2 1
c When we get TTYPE, throw out if TTYPE not set, not TSPEED not set.
e
s 01034/00000/00000
d D 5.1 89/09/01 15:17:51 borman 1 0
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
D 6
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
E 6
I 6
 * %sccs.include.redist.c%
E 6
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include "telnetd.h"
I 9
D 11
#if	defined(AUTHENTICATE)
E 11
I 11
#if	defined(AUTHENTICATION)
E 11
#include <libtelnet/auth.h>
#endif
E 9

D 16
char	doopt[] = { IAC, DO, '%', 'c', 0 };
char	dont[] = { IAC, DONT, '%', 'c', 0 };
char	will[] = { IAC, WILL, '%', 'c', 0 };
char	wont[] = { IAC, WONT, '%', 'c', 0 };
E 16
I 16
unsigned char	doopt[] = { IAC, DO, '%', 'c', 0 };
unsigned char	dont[] = { IAC, DONT, '%', 'c', 0 };
unsigned char	will[] = { IAC, WILL, '%', 'c', 0 };
unsigned char	wont[] = { IAC, WONT, '%', 'c', 0 };
E 16
int	not42 = 1;

/*
 * Buffer for sub-options, and macros
 * for suboptions buffer manipulations
 */
D 9
char	subbuffer[100], *subpointer= subbuffer, *subend= subbuffer;
E 9
I 9
unsigned char subbuffer[512], *subpointer= subbuffer, *subend= subbuffer;
E 9

D 13
#define	SB_CLEAR()	subpointer = subbuffer;
E 13
I 13
#define	SB_CLEAR()	subpointer = subbuffer
E 13
#define	SB_TERM()	{ subend = subpointer; SB_CLEAR(); }
#define	SB_ACCUM(c)	if (subpointer < (subbuffer+sizeof subbuffer)) { \
				*subpointer++ = (c); \
			}
#define	SB_GET()	((*subpointer++)&0xff)
#define	SB_EOF()	(subpointer >= subend)
I 7
#define	SB_LEN()	(subend - subpointer)
E 7

I 13
#ifdef	ENV_HACK
unsigned char *subsave;
#define SB_SAVE()	subsave = subpointer;
#define	SB_RESTORE()	subpointer = subsave;
#endif
E 13


/*
 * State for recv fsm
 */
#define	TS_DATA		0	/* base state */
#define	TS_IAC		1	/* look for double IAC's */
#define	TS_CR		2	/* CR-LF ->'s CR */
#define	TS_SB		3	/* throw away begin's... */
#define	TS_SE		4	/* ...end's (suboption negotiation) */
#define	TS_WILL		5	/* will option negotiation */
#define	TS_WONT		6	/* wont " */
#define	TS_DO		7	/* do " */
#define	TS_DONT		8	/* dont " */

I 9
	void
E 9
telrcv()
{
	register int c;
	static int state = TS_DATA;
D 5
#ifdef	CRAY2
E 5
I 5
#if	defined(CRAY2) && defined(UNICOS5)
E 5
	char *opfrontp = pfrontp;
#endif

	while (ncc > 0) {
		if ((&ptyobuf[BUFSIZ] - pfrontp) < 2)
			break;
		c = *netip++ & 0377, ncc--;
I 9
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
		if (decrypt_input)
			c = (*decrypt_input)(c);
D 14
#endif
E 14
I 14
#endif	/* ENCRYPTION */
E 14
E 9
		switch (state) {

		case TS_CR:
			state = TS_DATA;
			/* Strip off \n or \0 after a \r */
			if ((c == 0) || (c == '\n')) {
				break;
			}
			/* FALL THROUGH */

		case TS_DATA:
			if (c == IAC) {
				state = TS_IAC;
				break;
			}
			/*
			 * We now map \r\n ==> \r for pragmatic reasons.
			 * Many client implementations send \r\n when
			 * the user hits the CarriageReturn key.
			 *
			 * We USED to map \r\n ==> \n, since \r\n says
			 * that we want to be in column 1 of the next
			 * printable line, and \n is the standard
			 * unix way of saying that (\r is only good
			 * if CRMOD is set, which it normally is).
			 */
D 7
			if ((c == '\r') && (hisopts[TELOPT_BINARY] == OPT_NO)) {
E 7
I 7
			if ((c == '\r') && his_state_is_wont(TELOPT_BINARY)) {
I 9
				int nc = *netip;
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
				if (decrypt_input)
					nc = (*decrypt_input)(nc & 0xff);
D 14
#endif
E 14
I 14
#endif	/* ENCRYPTION */
E 14
#ifdef	LINEMODE
E 9
E 7
				/*
				 * If we are operating in linemode,
				 * convert to local end-of-line.
				 */
D 9
				if ((linemode) && (ncc > 0)&&('\n' == *netip)) {
E 9
I 9
				if (linemode && (ncc > 0) && (('\n' == nc) ||
					 ((0 == nc) && tty_iscrnl())) ) {
E 9
					netip++; ncc--;
					c = '\n';
D 9
				} else {
E 9
I 9
				} else
#endif
				{
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
					if (decrypt_input)
						(void)(*decrypt_input)(-1);
D 14
#endif
E 14
I 14
#endif	/* ENCRYPTION */
E 14
E 9
					state = TS_CR;
				}
			}
			*pfrontp++ = c;
			break;

		case TS_IAC:
gotiac:			switch (c) {

			/*
			 * Send the process on the pty side an
			 * interrupt.  Do this with a NULL or
			 * interrupt char; depending on the tty mode.
			 */
			case IP:
I 7
D 9
#ifdef DIAGNOSTICS
				if (diagnostic & TD_OPTIONS)
					printoption("td: recv IAC", c);
#endif /* DIAGNOSTICS */
E 9
I 9
				DIAG(TD_OPTIONS,
					printoption("td: recv IAC", c));
E 9
E 7
				interrupt();
				break;

			case BREAK:
I 7
D 9
#ifdef DIAGNOSTICS
				if (diagnostic & TD_OPTIONS)
					printoption("td: recv IAC", c);
#endif /* DIAGNOSTICS */
E 9
I 9
				DIAG(TD_OPTIONS,
					printoption("td: recv IAC", c));
E 9
E 7
				sendbrk();
				break;

			/*
			 * Are You There?
			 */
			case AYT:
I 7
D 9
#ifdef DIAGNOSTICS
				if (diagnostic & TD_OPTIONS)
					printoption("td: recv IAC", c);
#endif /* DIAGNOSTICS */
E 9
I 9
				DIAG(TD_OPTIONS,
					printoption("td: recv IAC", c));
E 9
E 7
D 8
				(void) strcpy(nfrontp, "\r\n[Yes]\r\n");
				nfrontp += 9;
E 8
I 8
				recv_ayt();
E 8
				break;

			/*
			 * Abort Output
			 */
			case AO:
			    {
I 7
D 9
#ifdef DIAGNOSTICS
				if (diagnostic & TD_OPTIONS)
					printoption("td: recv IAC", c);
#endif /* DIAGNOSTICS */
E 9
I 9
				DIAG(TD_OPTIONS,
					printoption("td: recv IAC", c));
E 9
E 7
				ptyflush();	/* half-hearted */
				init_termbuf();

				if (slctab[SLC_AO].sptr &&
D 5
				    *slctab[SLC_AO].sptr != '\377') {
					*pfrontp++ = *slctab[SLC_AO].sptr;
E 5
I 5
D 8
				    *slctab[SLC_AO].sptr != (cc_t)-1) {
E 8
I 8
				    *slctab[SLC_AO].sptr != (cc_t)(_POSIX_VDISABLE)) {
E 8
				    *pfrontp++ =
					(unsigned char)*slctab[SLC_AO].sptr;
E 5
				}

				netclear();	/* clear buffer back */
				*nfrontp++ = IAC;
				*nfrontp++ = DM;
				neturg = nfrontp-1; /* off by one XXX */
I 7
D 9
#ifdef DIAGNOSTICS
				if (diagnostic & TD_OPTIONS)
					printoption("td: send IAC", DM);
#endif /* DIAGNOSTICS */
E 9
I 9
				DIAG(TD_OPTIONS,
					printoption("td: send IAC", DM));
E 9
E 7
				break;
			    }

			/*
			 * Erase Character and
			 * Erase Line
			 */
			case EC:
			case EL:
			    {
D 5
				unsigned char ch;
E 5
I 5
				cc_t ch;
E 5

I 7
D 9
#ifdef DIAGNOSTICS
				if (diagnostic & TD_OPTIONS)
					printoption("td: recv IAC", c);
#endif /* DIAGNOSTICS */
E 9
I 9
				DIAG(TD_OPTIONS,
					printoption("td: recv IAC", c));
E 9
E 7
				ptyflush();	/* half-hearted */
				init_termbuf();
D 7
				ch = (c == EC) ? *slctab[SLC_EC].sptr :
						 *slctab[SLC_EL].sptr;
E 7
I 7
				if (c == EC)
					ch = *slctab[SLC_EC].sptr;
				else
					ch = *slctab[SLC_EL].sptr;
E 7
D 5
				if (ch != '\377')
					*pfrontp++ = ch;
E 5
I 5
D 8
				if (ch != (cc_t)-1)
E 8
I 8
				if (ch != (cc_t)(_POSIX_VDISABLE))
E 8
					*pfrontp++ = (unsigned char)ch;
E 5
				break;
			    }

			/*
			 * Check for urgent data...
			 */
			case DM:
I 7
D 9
#ifdef DIAGNOSTICS
				if (diagnostic & TD_OPTIONS)
					printoption("td: recv IAC", c);
#endif /* DIAGNOSTICS */
E 9
I 9
				DIAG(TD_OPTIONS,
					printoption("td: recv IAC", c));
E 9
E 7
				SYNCHing = stilloob(net);
				settimer(gotDM);
				break;


			/*
			 * Begin option subnegotiation...
			 */
			case SB:
				state = TS_SB;
				SB_CLEAR();
				continue;

			case WILL:
				state = TS_WILL;
				continue;

			case WONT:
				state = TS_WONT;
				continue;

			case DO:
				state = TS_DO;
				continue;

			case DONT:
				state = TS_DONT;
				continue;
			case EOR:
D 7
				if (hisopts[TELOPT_EOR])
E 7
I 7
				if (his_state_is_will(TELOPT_EOR))
E 7
					doeof();
				break;

			/*
			 * Handle RFC 10xx Telnet linemode option additions
			 * to command stream (EOF, SUSP, ABORT).
			 */
			case xEOF:
				doeof();
				break;

			case SUSP:
				sendsusp();
				break;

			case ABORT:
				sendbrk();
				break;

			case IAC:
				*pfrontp++ = c;
				break;
			}
			state = TS_DATA;
			break;

		case TS_SB:
			if (c == IAC) {
				state = TS_SE;
			} else {
				SB_ACCUM(c);
			}
			break;

		case TS_SE:
			if (c != SE) {
				if (c != IAC) {
					/*
					 * bad form of suboption negotiation.
					 * handle it in such a way as to avoid
					 * damage to local state.  Parse
					 * suboption buffer found so far,
					 * then treat remaining stream as
					 * another command sequence.
					 */
I 7
D 9
#ifdef	DIAGNOSTICS
E 9
I 9

					/* for DIAGNOSTICS */
E 9
					SB_ACCUM(IAC);
					SB_ACCUM(c);
					subpointer -= 2;
D 9
#endif
E 9
I 9

E 9
E 7
					SB_TERM();
					suboption();
					state = TS_IAC;
					goto gotiac;
				}
				SB_ACCUM(c);
				state = TS_SB;
			} else {
I 7
D 9
#ifdef	DIAGNOSTICS
E 9
I 9
				/* for DIAGNOSTICS */
E 9
				SB_ACCUM(IAC);
				SB_ACCUM(SE);
				subpointer -= 2;
D 9
#endif
E 9
I 9

E 9
E 7
				SB_TERM();
				suboption();	/* handle sub-option */
				state = TS_DATA;
			}
			break;

		case TS_WILL:
D 3
			willoption(c, 0);
E 3
I 3
			willoption(c);
E 3
			state = TS_DATA;
			continue;

		case TS_WONT:
D 3
			wontoption(c, 0);
E 3
I 3
			wontoption(c);
E 3
			state = TS_DATA;
			continue;

		case TS_DO:
D 3
			dooption(c, 0);
E 3
I 3
			dooption(c);
E 3
			state = TS_DATA;
			continue;

		case TS_DONT:
D 3
			dontoption(c, 0);
E 3
I 3
			dontoption(c);
E 3
			state = TS_DATA;
			continue;

		default:
			syslog(LOG_ERR, "telnetd: panic state=%d\n", state);
			printf("telnetd: panic state=%d\n", state);
			exit(1);
		}
	}
D 5
#if	CRAY2
E 5
I 5
#if	defined(CRAY2) && defined(UNICOS5)
E 5
	if (!linemode) {
		char	xptyobuf[BUFSIZ+NETSLOP];
		char	xbuf2[BUFSIZ];
		register char *cp;
		int n = pfrontp - opfrontp, oc;
D 19
		bcopy(opfrontp, xptyobuf, n);
E 19
I 19
		memmove(xptyobuf, opfrontp, n);
E 19
		pfrontp = opfrontp;
		pfrontp += term_input(xptyobuf, pfrontp, n, BUFSIZ+NETSLOP,
					xbuf2, &oc, BUFSIZ);
		for (cp = xbuf2; oc > 0; --oc)
			if ((*nfrontp++ = *cp++) == IAC)
				*nfrontp++ = IAC;
	}
D 5
#endif	/* CRAY2 */
E 5
I 5
#endif	/* defined(CRAY2) && defined(UNICOS5) */
E 5
}  /* end of telrcv */

/*
 * The will/wont/do/dont state machines are based on Dave Borman's
D 7
 * Telnet option processing state machine.  We keep track of the full
 * state of the option negotiation with the following state variables
 *	myopts, hisopts - The last fully negotiated state for each
 *			side of the connection.
 *	mywants, hiswants - The state we wish to be in after a completed
 *			negotiation.  (hiswants is slightly misleading,
 *			this is more precisely the state I want him to
 *			be in.
 *	resp - We count the number of requests we have sent out.
E 7
I 7
 * Telnet option processing state machine.
E 7
 *
 * These correspond to the following states:
 *	my_state = the last negotiated state
 *	want_state = what I want the state to go to
 *	want_resp = how many requests I have sent
 * All state defaults are negative, and resp defaults to 0.
 *
 * When initiating a request to change state to new_state:
D 19
 * 
E 19
I 19
 *
E 19
 * if ((want_resp == 0 && new_state == my_state) || want_state == new_state) {
 *	do nothing;
 * } else {
 *	want_state = new_state;
 *	send new_state;
 *	want_resp++;
 * }
 *
 * When receiving new_state:
 *
 * if (want_resp) {
 *	want_resp--;
 *	if (want_resp && (new_state == my_state))
 *		want_resp--;
 * }
 * if ((want_resp == 0) && (new_state != want_state)) {
 *	if (ok_to_switch_to new_state)
 *		want_state = new_state;
 *	else
 *		want_resp++;
 *	send want_state;
 * }
 * my_state = new_state;
 *
 * Note that new_state is implied in these functions by the function itself.
 * will and do imply positive new_state, wont and dont imply negative.
 *
 * Finally, there is one catch.  If we send a negative response to a
 * positive request, my_state will be the positive while want_state will
 * remain negative.  my_state will revert to negative when the negative
 * acknowlegment arrives from the peer.  Thus, my_state generally tells
 * us not only the last negotiated state, but also tells us what the peer
 * wants to be doing as well.  It is important to understand this difference
 * as we may wish to be processing data streams based on our desired state
 * (want_state) or based on what the peer thinks the state is (my_state).
 *
 * This all works fine because if the peer sends a positive request, the data
 * that we receive prior to negative acknowlegment will probably be affected
 * by the positive state, and we can process it as such (if we can; if we
 * can't then it really doesn't matter).  If it is that important, then the
 * peer probably should be buffering until this option state negotiation
 * is complete.
 *
D 5
 * In processing options, request signifies whether this is a request
 * to send or a response.  request is true if this is a request to 
 * send generated locally.
E 5
 */
I 9
	void
E 9
D 3
willoption(option, request)
	int option, request;
E 3
I 3
send_do(option, init)
	int option, init;
E 3
{
I 3
	if (init) {
D 7
		if ((do_dont_resp[option] == 0 && hisopts[option] == OPT_YES) ||
		    hiswants[option] == OPT_YES)
E 7
I 7
		if ((do_dont_resp[option] == 0 && his_state_is_will(option)) ||
		    his_want_state_is_will(option))
E 7
			return;
D 4
		hiswants[option] = OPT_YES;
E 4
I 4
		/*
		 * Special case for TELOPT_TM:  We send a DO, but pretend
		 * that we sent a DONT, so that we can send more DOs if
		 * we want to.
		 */
		if (option == TELOPT_TM)
D 7
			hiswants[option] = OPT_NO;
E 7
I 7
			set_his_want_state_wont(option);
E 7
		else
D 7
			hiswants[option] = OPT_YES;
E 7
I 7
			set_his_want_state_will(option);
E 7
E 4
		do_dont_resp[option]++;
	}
D 16
	(void) sprintf(nfrontp, doopt, option);
E 16
I 16
	(void) sprintf(nfrontp, (char *)doopt, option);
E 16
	nfrontp += sizeof (dont) - 2;
I 7
D 9
#ifdef DIAGNOSTICS
	/*
	 * Report sending option to other side.
	 */
	if (diagnostic & TD_OPTIONS) {
		printoption("td: send do", option);
	}
#endif /* DIAGNOSTICS */
E 9
I 9

	DIAG(TD_OPTIONS, printoption("td: send do", option));
E 9
E 7
}

I 9
D 11
#ifdef	AUTHENTICATE
E 11
I 11
#ifdef	AUTHENTICATION
E 11
extern void auth_request();
#endif
#ifdef	LINEMODE
extern void doclientstat();
#endif
D 11
#ifdef	ENCRYPT
E 11
I 11
#ifdef	ENCRYPTION
E 11
extern void encrypt_send_support();
D 14
#endif
E 14
I 14
#endif	/* ENCRYPTION */
E 14

	void
E 9
willoption(option)
	int option;
{
E 3
	int changeok = 0;
I 9
	void (*func)() = 0;
E 9
D 3
	char *fmt = (char *)0;
E 3

D 3
    /*
     * process input from peer.
     */
    if (request == 0) {
E 3
I 3
	/*
	 * process input from peer.
	 */

I 7
D 9
#ifdef DIAGNOSTICS
	/*
	 * Report receiving option from other side.
	 */
	if (diagnostic & TD_OPTIONS) {
		printoption("td: recv will", option);
	}
#endif /* DIAGNOSTICS */
E 9
I 9
	DIAG(TD_OPTIONS, printoption("td: recv will", option));
E 9

E 7
	if (do_dont_resp[option]) {
		do_dont_resp[option]--;
D 7
		if (do_dont_resp[option] && hisopts[option] == OPT_YES)
E 7
I 7
		if (do_dont_resp[option] && his_state_is_will(option))
E 7
			do_dont_resp[option]--;
	}
D 4
	if ((do_dont_resp[option] == 0) && (hiswants[option] != OPT_YES)) {
E 4
I 4
	if (do_dont_resp[option] == 0) {
D 7
	    if (hiswants[option] != OPT_YES) {
E 7
I 7
	    if (his_want_state_is_wont(option)) {
E 7
E 4
E 3
		switch (option) {

		case TELOPT_BINARY:
			init_termbuf();
			tty_binaryin(1);
			set_termbuf();
			changeok++;
			break;

		case TELOPT_ECHO:
D 3
			not42 = 0;		/* looks like a 4.2 system */
E 3
I 3
D 7
			not42 = 0;	/* looks like a 4.2 system */
#ifdef notdef
E 7
E 3
			/*
D 3
			 * Now, in a 4.2 system, to break them out of ECHOing
			 * (to the terminal) mode, we need to send a
			 * "WILL ECHO".  Kludge upon kludge!
E 3
I 3
D 7
			 * Now, in a 4.2 system, to break them out of
			 * ECHOing (to the terminal) mode, we need to
			 * send a WILL ECHO.
E 7
I 7
			 * See comments below for more info.
E 7
E 3
			 */
D 7
			if (myopts[TELOPT_ECHO] == OPT_YES) {
D 3
				dooption(TELOPT_ECHO, 1);
E 3
I 3
				send_will(TELOPT_ECHO, 1);
E 3
			}
I 3
#else
E 3
			/*
I 3
			 * "WILL ECHO".  Kludge upon kludge!
			 * A 4.2 client is now echoing user input at
			 * the tty.  This is probably undesireable and
			 * it should be stopped.  The client will
			 * respond WONT TM to the DO TM that we send to
			 * check for kludge linemode.  When the WONT TM
			 * arrives, linemode will be turned off and a
			 * change propogated to the pty.  This change
			 * will cause us to process the new pty state
			 * in localstat(), which will notice that
			 * linemode is off and send a WILL ECHO
			 * so that we are properly in character mode and
			 * all is well.
			 */
#endif
			/*
E 3
			 * Fool the state machine into sending a don't.
D 3
			 * This also allows the initial echo sending code to
			 * break out of the loop that it is
E 3
I 3
			 * This also allows the initial echo sending
			 * code to break out of the loop that it is
E 3
			 * in.  (Look in telnet())
			 */
			hiswants[TELOPT_ECHO] = OPT_NO;
E 7
I 7
			not42 = 0;	/* looks like a 4.2 system */
E 7
			break;

		case TELOPT_TM:
#if	defined(LINEMODE) && defined(KLUDGELINEMODE)
			/*
D 3
		 	 * This telnetd implementation does not really support
			 * timing marks, it just uses them to support the kludge
			 * linemode stuff.  If we receive a will or wont TM in
			 * response to our do TM request that may have been sent
			 * to determine kludge linemode support, process it,
			 * otherwise TM should get a negative response back.
E 3
I 3
			 * This telnetd implementation does not really
			 * support timing marks, it just uses them to
			 * support the kludge linemode stuff.  If we
			 * receive a will or wont TM in response to our
			 * do TM request that may have been sent to
			 * determine kludge linemode support, process
			 * it, otherwise TM should get a negative
			 * response back.
E 3
			 */
			/*
			 * Handle the linemode kludge stuff.
			 * If we are not currently supporting any
			 * linemode at all, then we assume that this
			 * is the client telling us to use kludge
			 * linemode in response to our query.  Set the
			 * linemode type that is to be supported, note
			 * that the client wishes to use linemode, and
			 * eat the will TM as though it never arrived.
			 */
			if (lmodetype < KLUDGE_LINEMODE) {
				lmodetype = KLUDGE_LINEMODE;
				clientstat(TELOPT_LINEMODE, WILL, 0);
D 3
				dontoption(TELOPT_SGA, 0);
E 3
I 3
				send_wont(TELOPT_SGA, 1);
I 11
			} else if (lmodetype == NO_AUTOKLUDGE) {
				lmodetype = KLUDGE_OK;
E 11
E 3
			}
#endif	/* defined(LINEMODE) && defined(KLUDGELINEMODE) */
			/*
D 3
			 * cheat the state machine so that it
			 * looks like we never sent the TM at
			 * all.  The bad part of this is that
			 * if the client sends a will TM on his
			 * own to turn on linemode, then he
			 * won't get a response.
E 3
I 3
D 4
			 * Cheat the state machine so that it
			 * looks like we got back a WONT.
E 4
I 4
			 * We never respond to a WILL TM, and
D 7
			 * we leave the state OPT_NO.
E 7
I 7
			 * we leave the state WONT.
E 7
E 4
E 3
			 */
D 4
			hiswants[TELOPT_TM] = OPT_NO;
E 4
D 3
			resp[TELOPT_TM]--;
E 3
			return;

		case TELOPT_LFLOW:
			/*
D 3
			 * If we are going to support flow control option,
			 * then don't worry peer that we can't change the
			 * flow control characters.
E 3
I 3
			 * If we are going to support flow control
			 * option, then don't worry peer that we can't
			 * change the flow control characters.
E 3
			 */
			slctab[SLC_XON].defset.flag &= ~SLC_LEVELBITS;
			slctab[SLC_XON].defset.flag |= SLC_DEFAULT;
			slctab[SLC_XOFF].defset.flag &= ~SLC_LEVELBITS;
			slctab[SLC_XOFF].defset.flag |= SLC_DEFAULT;
		case TELOPT_TTYPE:
		case TELOPT_SGA:
		case TELOPT_NAWS:
		case TELOPT_TSPEED:
I 7
		case TELOPT_XDISPLOC:
D 16
		case TELOPT_ENVIRON:
E 16
I 16
		case TELOPT_NEW_ENVIRON:
		case TELOPT_OLD_ENVIRON:
E 16
E 7
I 4
			changeok++;
			break;

E 4
#ifdef	LINEMODE
		case TELOPT_LINEMODE:
I 7
D 9
			/*
			 * Local processing of 'will linemode' should
			 * occur after placing 'do linemode' in the data
			 * stream, because we may wish to send other
			 * linemode related messages.  So, we duplicate
			 * the other three lines of code here, and then
			 * return.
			 */
			set_his_want_state_will(option);
			send_do(option, 0);
			set_his_state_will(option);
E 9
E 7
D 4
#endif	LINEMODE
E 4
I 4
# ifdef	KLUDGELINEMODE
			/*
			 * Note client's desire to use linemode.
			 */
			lmodetype = REAL_LINEMODE;
# endif	/* KLUDGELINEMODE */
D 9
			clientstat(TELOPT_LINEMODE, WILL, 0);
E 4
D 7
			changeok++;
			break;
E 7
I 7
			return;
E 9
I 9
			func = doclientstat;
			changeok++;
			break;
E 9
E 7
I 4
#endif	/* LINEMODE */
E 4

I 9
D 11
#ifdef	AUTHENTICATE
E 11
I 11
#ifdef	AUTHENTICATION
E 11
		case TELOPT_AUTHENTICATION:
			func = auth_request;
			changeok++;
			break;
#endif

D 11
#ifdef	ENCRYPT
E 11
I 11
#ifdef	ENCRYPTION
E 11
		case TELOPT_ENCRYPT:
			func = encrypt_send_support;
			changeok++;
			break;
D 14
#endif
E 14
I 14
#endif	/* ENCRYPTION */
E 14

E 9
		default:
			break;
		}
D 3

	}

	if (request) {
		if (!((resp[option] == 0 && hisopts[option] == OPT_YES) ||
		    hiswants[option] == OPT_YES)) {
E 3
I 3
		if (changeok) {
E 3
D 7
			hiswants[option] = OPT_YES;
E 7
I 7
			set_his_want_state_will(option);
E 7
D 3
			fmt = doopt;
			resp[option]++;
E 3
I 3
			send_do(option, 0);
		} else {
			do_dont_resp[option]++;
			send_dont(option, 0);
E 3
		}
I 7
	    } else {
		/*
		 * Option processing that should happen when
		 * we receive conformation of a change in
		 * state that we had requested.
		 */
		switch (option) {
		case TELOPT_ECHO:
			not42 = 0;	/* looks like a 4.2 system */
			/*
			 * Egads, he responded "WILL ECHO".  Turn
			 * it off right now!
			 */
			send_dont(option, 1);
			/*
			 * "WILL ECHO".  Kludge upon kludge!
			 * A 4.2 client is now echoing user input at
			 * the tty.  This is probably undesireable and
			 * it should be stopped.  The client will
			 * respond WONT TM to the DO TM that we send to
			 * check for kludge linemode.  When the WONT TM
			 * arrives, linemode will be turned off and a
			 * change propogated to the pty.  This change
			 * will cause us to process the new pty state
			 * in localstat(), which will notice that
			 * linemode is off and send a WILL ECHO
			 * so that we are properly in character mode and
			 * all is well.
			 */
			break;
#ifdef	LINEMODE
		case TELOPT_LINEMODE:
# ifdef	KLUDGELINEMODE
			/*
			 * Note client's desire to use linemode.
			 */
			lmodetype = REAL_LINEMODE;
# endif	/* KLUDGELINEMODE */
D 9
			clientstat(TELOPT_LINEMODE, WILL, 0);
E 9
I 9
			func = doclientstat;
			break;
E 9
#endif	/* LINEMODE */
I 9

D 11
#ifdef	AUTHENTICATE
E 11
I 11
#ifdef	AUTHENTICATION
E 11
		case TELOPT_AUTHENTICATION:
			func = auth_request;
			break;
#endif

D 11
#ifdef	ENCRYPT
E 11
I 11
#ifdef	ENCRYPTION
E 11
		case TELOPT_ENCRYPT:
			func = encrypt_send_support;
			break;
D 14
#endif
E 14
I 14
#endif	/* ENCRYPTION */
E 14
I 12
		case TELOPT_LFLOW:
D 13
			func = localstat;
E 13
I 13
			func = flowstat;
E 13
			break;
E 12
E 9
		}
E 7
I 4
	    }
E 4
D 3
	} else {
		if (resp[option]) {
			resp[option]--;
			if (resp[option] && hisopts[option] == OPT_YES)
				resp[option]--;
		}
		if ((resp[option] == 0) && (hiswants[option] != OPT_YES)) {
			if (changeok)
				hiswants[option] = OPT_YES;
			else
				resp[option]++;
			fmt = (hiswants[option] ? doopt : dont);
		}
		hisopts[option] = OPT_YES;
E 3
	}
I 3
D 7
	hisopts[option] = OPT_YES;
E 7
I 7
	set_his_state_will(option);
I 9
	if (func)
		(*func)();
E 9
E 7
E 3
D 4

D 3
	if (fmt) {
		(void) sprintf(nfrontp, fmt, option);
		nfrontp += sizeof (dont) - 2;
	}

E 3
	/*
	 * Handle other processing that should occur after we have
	 * responded to client input.
	 */
D 3
	if (!request) {
		switch (option) {
E 3
I 3
	switch (option) {
E 3
#ifdef	LINEMODE
D 3
		case TELOPT_LINEMODE:
E 3
I 3
	case TELOPT_LINEMODE:
E 3
# ifdef	KLUDGELINEMODE
D 3
			/*
			 * Note client's desire to use linemode.
			 */
			lmodetype = REAL_LINEMODE;
E 3
I 3
		/*
		 * Note client's desire to use linemode.
		 */
		lmodetype = REAL_LINEMODE;
E 3
# endif	/* KLUDGELINEMODE */
D 3
			clientstat(TELOPT_LINEMODE, WILL, 0);
			break;
E 3
I 3
		clientstat(TELOPT_LINEMODE, WILL, 0);
		break;
E 3
#endif	LINEMODE
D 3
		
		default:
			break;
		}
E 3
I 3
	
	default:
		break;
E 3
	}
E 4
D 3

E 3
}  /* end of willoption */

I 9
	void
E 9
D 3
wontoption(option, request)
	int option, request;
E 3
I 3
send_dont(option, init)
	int option, init;
E 3
{
I 3
	if (init) {
D 7
		if ((do_dont_resp[option] == 0 && hisopts[option] == OPT_NO) ||
		    hiswants[option] == OPT_NO)
E 7
I 7
		if ((do_dont_resp[option] == 0 && his_state_is_wont(option)) ||
		    his_want_state_is_wont(option))
E 7
			return;
D 7
		hiswants[option] = OPT_NO;
E 7
I 7
		set_his_want_state_wont(option);
E 7
		do_dont_resp[option]++;
	}
D 16
	(void) sprintf(nfrontp, dont, option);
E 16
I 16
	(void) sprintf(nfrontp, (char *)dont, option);
E 16
	nfrontp += sizeof (doopt) - 2;
I 7
D 9
#ifdef DIAGNOSTICS
	/*
	 * Report sending option to other side.
	 */
	if (diagnostic & TD_OPTIONS) {
		printoption("td: send dont", option);
	}
#endif /* DIAGNOSTICS */
E 9
I 9

	DIAG(TD_OPTIONS, printoption("td: send dont", option));
E 9
E 7
}

I 9
	void
E 9
wontoption(option)
	int option;
{
E 3
D 7
	char *fmt = (char *)0;

E 7
	/*
	 * Process client input.
	 */
D 3
	if (!request) {
E 3
I 3

I 7
D 9
#ifdef DIAGNOSTICS
	/*
	 * Report receiving option from other side.
	 */
	if (diagnostic & TD_OPTIONS) {
		printoption("td: recv wont", option);
	}
#endif /* DIAGNOSTICS */
E 9
I 9
	DIAG(TD_OPTIONS, printoption("td: recv wont", option));
E 9

E 7
	if (do_dont_resp[option]) {
		do_dont_resp[option]--;
D 7
		if (do_dont_resp[option] && hisopts[option] == OPT_NO)
E 7
I 7
		if (do_dont_resp[option] && his_state_is_wont(option))
E 7
			do_dont_resp[option]--;
	}
D 4
	if ((do_dont_resp[option] == 0) && (hiswants[option] != OPT_NO)) {
E 4
I 4
	if (do_dont_resp[option] == 0) {
D 7
	    if (hiswants[option] != OPT_NO) {
E 7
I 7
	    if (his_want_state_is_will(option)) {
E 7
E 4
		/* it is always ok to change to negative state */
E 3
		switch (option) {
		case TELOPT_ECHO:
D 3
			not42 = 1;	/* doesn't seem to be a 4.2 system */
E 3
I 3
			not42 = 1; /* doesn't seem to be a 4.2 system */
E 3
			break;

		case TELOPT_BINARY:
			init_termbuf();
			tty_binaryin(0);
			set_termbuf();
			break;

#ifdef	LINEMODE
		case TELOPT_LINEMODE:
# ifdef	KLUDGELINEMODE
			/*
			 * If real linemode is supported, then client is
			 * asking to turn linemode off.
			 */
D 7
			if (lmodetype == REAL_LINEMODE)
E 7
I 7
			if (lmodetype != REAL_LINEMODE)
				break;
D 18
			lmodetype = KLUDGE_LINEMODE;
E 18
E 7
# endif	/* KLUDGELINEMODE */
D 7
				clientstat(TELOPT_LINEMODE, WONT, 0);
E 7
I 7
			clientstat(TELOPT_LINEMODE, WONT, 0);
E 7
			break;
D 9
#endif	LINEMODE
E 9
I 9
#endif	/* LINEMODE */
E 9

		case TELOPT_TM:
D 4
#if	defined(LINEMODE) && defined(KLUDGELINEMODE)
			if (lmodetype < REAL_LINEMODE) {
				lmodetype = NO_LINEMODE;
				clientstat(TELOPT_LINEMODE, WONT, 0);
D 3
				dooption(TELOPT_SGA, 0);
E 3
I 3
				send_will(TELOPT_SGA, 1);
/*@*/				send_will(TELOPT_ECHO, 1);
E 3
			}
#endif	/* defined(LINEMODE) && defined(KLUDGELINEMODE) */
E 4
			/*
D 3
			 * If we get a WONT TM, and had sent a DO TM, don't
			 * respond with a DONT TM, just leave it as is.
			 * Short circut the state machine to achive this.
			 * The bad part of this is that if the client sends
			 * a WONT TM on his own to turn off linemode, then he
			 * won't get a response.
E 3
I 3
			 * If we get a WONT TM, and had sent a DO TM,
			 * don't respond with a DONT TM, just leave it
			 * as is.  Short circut the state machine to
D 4
			 * achive this. The bad part of this is that if
			 * the client sends a WONT TM on his own to
			 * turn off linemode, then he won't get a
			 * response.
E 4
I 4
			 * achive this.
E 4
E 3
			 */
D 7
			hiswants[TELOPT_TM] = OPT_NO;
E 7
I 7
			set_his_want_state_wont(TELOPT_TM);
E 7
D 3
			resp[TELOPT_TM]--;
E 3
I 3
D 4
#ifdef	notdef
			do_dont_resp[TELOPT_TM]--;
#endif
E 4
E 3
			return;

		case TELOPT_LFLOW:
			/*
D 3
			 * If we are not going to support flow control option,
			 * then let peer know that we can't change the
			 * flow control characters.
E 3
I 3
			 * If we are not going to support flow control
			 * option, then let peer know that we can't
			 * change the flow control characters.
E 3
			 */
			slctab[SLC_XON].defset.flag &= ~SLC_LEVELBITS;
			slctab[SLC_XON].defset.flag |= SLC_CANTCHANGE;
			slctab[SLC_XOFF].defset.flag &= ~SLC_LEVELBITS;
			slctab[SLC_XOFF].defset.flag |= SLC_CANTCHANGE;
			break;

I 9
D 11
#if	defined(AUTHENTICATE)
E 11
I 11
#if	defined(AUTHENTICATION)
E 11
		case TELOPT_AUTHENTICATION:
			auth_finished(0, AUTH_REJECT);
			break;
#endif

E 9
I 7
		/*
		 * For options that we might spin waiting for
		 * sub-negotiation, if the client turns off the
		 * option rather than responding to the request,
		 * we have to treat it here as if we got a response
		 * to the sub-negotiation, (by updating the timers)
		 * so that we'll break out of the loop.
		 */
		case TELOPT_TTYPE:
			settimer(ttypesubopt);
			break;

		case TELOPT_TSPEED:
			settimer(tspeedsubopt);
			break;

		case TELOPT_XDISPLOC:
			settimer(xdisplocsubopt);
			break;

D 16
		case TELOPT_ENVIRON:
E 16
I 16
		case TELOPT_OLD_ENVIRON:
			settimer(oenvironsubopt);
			break;

		case TELOPT_NEW_ENVIRON:
E 16
			settimer(environsubopt);
			break;

E 7
		default:
			break;
		}
I 3
D 7
		hiswants[option] = OPT_NO;
		fmt = dont;
		send_dont(option, 0);
E 7
I 7
		set_his_want_state_wont(option);
		if (his_state_is_will(option))
			send_dont(option, 0);
E 7
D 4
	} else if (option == TELOPT_TM) {
		/*
		 * Special case for TM.
		 */
		hiswants[option] = OPT_NO;
E 4
I 4
	    } else {
		switch (option) {
		case TELOPT_TM:
#if	defined(LINEMODE) && defined(KLUDGELINEMODE)
D 11
			if (lmodetype < REAL_LINEMODE) {
E 11
I 11
			if (lmodetype < NO_AUTOKLUDGE) {
E 11
				lmodetype = NO_LINEMODE;
				clientstat(TELOPT_LINEMODE, WONT, 0);
				send_will(TELOPT_SGA, 1);
D 8
/*@*/				send_will(TELOPT_ECHO, 1);
E 8
I 8
				send_will(TELOPT_ECHO, 1);
E 8
			}
#endif	/* defined(LINEMODE) && defined(KLUDGELINEMODE) */
I 9
			break;

D 11
#if	defined(AUTHENTICATE)
E 11
I 11
#if	defined(AUTHENTICATION)
E 11
		case TELOPT_AUTHENTICATION:
			auth_finished(0, AUTH_REJECT);
			break;
#endif
E 9
		default:
			break;
		}
	    }
E 4
E 3
	}
I 3
D 7
	hisopts[option] = OPT_NO;
E 7
I 7
	set_his_state_wont(option);
E 7
E 3

I 3
}  /* end of wontoption */
E 3

I 9
	void
E 9
D 3
	if (request) {
		if (!((resp[option] == 0 && hisopts[option] == OPT_NO) ||
			hiswants[option] == OPT_NO)) {
			hiswants[option] = OPT_NO;
			fmt = dont;
			resp[option]++;
		}
	} else {
		if (resp[option]) {
			resp[option]--;
			if (resp[option] && hisopts[option] == OPT_NO)
				resp[option]--;
		}
		if ((resp[option] == 0) && (hiswants[option] != OPT_NO)) {
			/* it is always ok to change to negative state */
			hiswants[option] = OPT_NO;
			fmt = dont;
		}
		hisopts[option] = OPT_NO;
E 3
I 3
send_will(option, init)
	int option, init;
{
	if (init) {
D 7
		if ((will_wont_resp[option] == 0 && myopts[option] == OPT_YES)||
		    mywants[option] == OPT_YES)
E 7
I 7
		if ((will_wont_resp[option] == 0 && my_state_is_will(option))||
		    my_want_state_is_will(option))
E 7
			return;
D 7
		mywants[option] = OPT_YES;
E 7
I 7
		set_my_want_state_will(option);
E 7
		will_wont_resp[option]++;
E 3
	}
I 3
D 16
	(void) sprintf(nfrontp, will, option);
E 16
I 16
	(void) sprintf(nfrontp, (char *)will, option);
E 16
	nfrontp += sizeof (doopt) - 2;
I 7
D 9
#ifdef DIAGNOSTICS
	/*
	 * Report sending option to other side.
	 */
	if (diagnostic & TD_OPTIONS) {
		printoption("td: send will", option);
	}
#endif /* DIAGNOSTICS */
E 9
I 9

	DIAG(TD_OPTIONS, printoption("td: send will", option));
E 9
E 7
}
E 3

I 8
#if	!defined(LINEMODE) || !defined(KLUDGELINEMODE)
/*
 * When we get a DONT SGA, we will try once to turn it
 * back on.  If the other side responds DONT SGA, we
 * leave it at that.  This is so that when we talk to
 * clients that understand KLUDGELINEMODE but not LINEMODE,
 * we'll keep them in char-at-a-time mode.
 */
int turn_on_sga = 0;
#endif

I 9
	void
E 9
E 8
D 3
	if (fmt) {
		(void) sprintf(nfrontp, fmt, option);
		nfrontp += sizeof (doopt) - 2;
	}

}  /* end of wontoption */

dooption(option, request)
	int option, request;
E 3
I 3
dooption(option)
	int option;
E 3
{
	int changeok = 0;
D 3
	char *fmt = (char *)0;
E 3

	/*
	 * Process client input.
	 */
D 3
	if (!request) {
E 3
I 3

I 7
D 9
#ifdef DIAGNOSTICS
	/*
	 * Report receiving option from other side.
	 */
	if (diagnostic & TD_OPTIONS) {
		printoption("td: recv do", option);
	}
#endif /* DIAGNOSTICS */
E 9
I 9
	DIAG(TD_OPTIONS, printoption("td: recv do", option));
E 9

E 7
	if (will_wont_resp[option]) {
		will_wont_resp[option]--;
D 7
		if (will_wont_resp[option] && myopts[option] == OPT_YES)
E 7
I 7
		if (will_wont_resp[option] && my_state_is_will(option))
E 7
			will_wont_resp[option]--;
	}
D 7
	if ((will_wont_resp[option] == 0) && (mywants[option] != OPT_YES)) {
E 7
I 7
	if ((will_wont_resp[option] == 0) && (my_want_state_is_wont(option))) {
E 7
E 3
		switch (option) {
		case TELOPT_ECHO:
#ifdef	LINEMODE
D 3
			if (hisopts[TELOPT_LINEMODE] == OPT_NO) {
E 3
I 3
D 8
			if (lmodetype == NO_LINEMODE) {
E 8
I 8
# ifdef	KLUDGELINEMODE
			if (lmodetype == NO_LINEMODE)
# else
			if (his_state_is_wont(TELOPT_LINEMODE))
# endif
E 8
E 3
#endif
I 8
			{
E 8
				init_termbuf();
				tty_setecho(1);
				set_termbuf();
D 8
#ifdef	LINEMODE
E 8
			}
D 8
#endif
E 8
			changeok++;
			break;

		case TELOPT_BINARY:
			init_termbuf();
			tty_binaryout(1);
			set_termbuf();
			changeok++;
			break;

		case TELOPT_SGA:
#if	defined(LINEMODE) && defined(KLUDGELINEMODE)
			/*
D 3
			 * If kludge linemode is in use, then we must process
			 * an incoming do SGA for linemode purposes.
E 3
I 3
			 * If kludge linemode is in use, then we must
			 * process an incoming do SGA for linemode
			 * purposes.
E 3
			 */
			if (lmodetype == KLUDGE_LINEMODE) {
				/*
D 3
				 * Receipt of "do SGA" in kludge linemode
				 * is the peer asking us to turn off linemode.
				 * Make note of the request.
E 3
I 3
				 * Receipt of "do SGA" in kludge
				 * linemode is the peer asking us to
				 * turn off linemode.  Make note of
				 * the request.
E 3
				 */
				clientstat(TELOPT_LINEMODE, WONT, 0);
				/*
D 3
				 * If linemode did not get turned off then
				 * don't tell peer that we did.  Breaking
				 * here forces a wont SGA to be returned.
E 3
I 3
				 * If linemode did not get turned off
				 * then don't tell peer that we did.
				 * Breaking here forces a wont SGA to
				 * be returned.
E 3
				 */
				if (linemode)
					break;
			}
I 8
#else
			turn_on_sga = 0;
E 8
#endif	/* defined(LINEMODE) && defined(KLUDGELINEMODE) */
			changeok++;
			break;

		case TELOPT_STATUS:
			changeok++;
			break;

		case TELOPT_TM:
I 3
			/*
			 * Special case for TM.  We send a WILL, but
			 * pretend we sent a WONT.
			 */
			send_will(option, 0);
D 7
			mywants[option] = OPT_NO;
			myopts[option] = OPT_NO;
E 7
I 7
			set_my_want_state_wont(option);
			set_my_state_wont(option);
E 7
			return;

I 9
		case TELOPT_LOGOUT:
			/*
			 * When we get a LOGOUT option, respond
			 * with a WILL LOGOUT, make sure that
			 * it gets written out to the network,
			 * and then just go away...
			 */
			set_my_want_state_will(TELOPT_LOGOUT);
			send_will(TELOPT_LOGOUT, 0);
			set_my_state_will(TELOPT_LOGOUT);
			(void)netflush();
			cleanup(0);
			/* NOT REACHED */
			break;

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
		case TELOPT_ENCRYPT:
			changeok++;
			break;
D 14
#endif
E 14
I 14
#endif	/* ENCRYPTION */
E 14
E 9
E 3
		case TELOPT_LINEMODE:
		case TELOPT_TTYPE:
		case TELOPT_NAWS:
		case TELOPT_TSPEED:
		case TELOPT_LFLOW:
I 7
		case TELOPT_XDISPLOC:
D 16
		case TELOPT_ENVIRON:
E 16
I 16
#ifdef	TELOPT_ENVIRON
		case TELOPT_NEW_ENVIRON:
#endif
		case TELOPT_OLD_ENVIRON:
E 16
E 7
		default:
			break;
		}
D 3
	}

	if (request) {
		if (!((resp[option] == 0 && myopts[option] == OPT_YES) ||
		    mywants[option] == OPT_YES)) {
E 3
I 3
		if (changeok) {
E 3
D 7
			mywants[option] = OPT_YES;
E 7
I 7
			set_my_want_state_will(option);
E 7
D 3
			fmt = will;
			resp[option]++;
E 3
I 3
			send_will(option, 0);
		} else {
			will_wont_resp[option]++;
			send_wont(option, 0);
E 3
		}
D 3
	} else {
		if (resp[option]) {
			resp[option]--;
			if (resp[option] && myopts[option] == OPT_YES)
				resp[option]--;
		}
		if ((resp[option] == 0) && (mywants[option] != OPT_YES)) {
			if (changeok)
				mywants[option] = OPT_YES;
			else
				resp[option]++;
			fmt = (mywants[option] ? will : wont);
		}
		myopts[option] = OPT_YES;
E 3
	}
I 3
D 7
	myopts[option] = OPT_YES;
E 7
I 7
	set_my_state_will(option);
E 7
E 3

D 3
	if (fmt) {
		(void) sprintf(nfrontp, fmt, option);
		nfrontp += sizeof (doopt) - 2;
	}

E 3
}  /* end of dooption */

I 9
	void
E 9
D 3

dontoption(option, request)
	int option, request;
E 3
I 3
send_wont(option, init)
	int option, init;
E 3
{
D 3
	char *fmt = (char *)0;
E 3
I 3
	if (init) {
D 7
		if ((will_wont_resp[option] == 0 && myopts[option] == OPT_NO) ||
		    mywants[option] == OPT_NO)
E 7
I 7
		if ((will_wont_resp[option] == 0 && my_state_is_wont(option)) ||
		    my_want_state_is_wont(option))
E 7
			return;
D 7
		mywants[option] = OPT_NO;
E 7
I 7
		set_my_want_state_wont(option);
E 7
		will_wont_resp[option]++;
	}
D 16
	(void) sprintf(nfrontp, wont, option);
E 16
I 16
	(void) sprintf(nfrontp, (char *)wont, option);
E 16
	nfrontp += sizeof (wont) - 2;
I 7
D 9
#ifdef DIAGNOSTICS
	/*
	 * Report sending option to other side.
	 */
	if (diagnostic & TD_OPTIONS) {
		printoption("td: send wont", option);
	}
#endif /* DIAGNOSTICS */
E 9
I 9

	DIAG(TD_OPTIONS, printoption("td: send wont", option));
E 9
E 7
}
E 3

I 9
	void
E 9
I 3
dontoption(option)
	int option;
{
E 3
	/*
	 * Process client input.
	 */
I 7
D 9
#ifdef DIAGNOSTICS
	/*
	 * Report receiving option from other side.
	 */
	if (diagnostic & TD_OPTIONS) {
		printoption("td: recv dont", option);
	}
#endif /* DIAGNOSTICS */
E 9
E 7
I 5

I 9

	DIAG(TD_OPTIONS, printoption("td: recv dont", option));

E 9
E 5
D 3
	if (!request) {
E 3
I 3
	if (will_wont_resp[option]) {
		will_wont_resp[option]--;
D 7
		if (will_wont_resp[option] && myopts[option] == OPT_NO)
E 7
I 7
		if (will_wont_resp[option] && my_state_is_wont(option))
E 7
			will_wont_resp[option]--;
	}
D 7
	if ((will_wont_resp[option] == 0) && (mywants[option] != OPT_NO)) {
E 7
I 7
	if ((will_wont_resp[option] == 0) && (my_want_state_is_will(option))) {
E 7
E 3
		switch (option) {
		case TELOPT_BINARY:
			init_termbuf();
			tty_binaryout(0);
			set_termbuf();
			break;

D 3
		case TELOPT_ECHO:		/* we should stop echoing */
E 3
I 3
		case TELOPT_ECHO:	/* we should stop echoing */
E 3
#ifdef	LINEMODE
D 3
			if (hisopts[TELOPT_LINEMODE] == OPT_NO) {
E 3
I 3
D 8
			if (lmodetype == NO_LINEMODE) {
E 8
I 8
# ifdef	KLUDGELINEMODE
D 11
			if (lmodetype == NO_LINEMODE)
E 11
I 11
			if ((lmodetype != REAL_LINEMODE) &&
			    (lmodetype != KLUDGE_LINEMODE))
E 11
# else
			if (his_state_is_wont(TELOPT_LINEMODE))
# endif
E 8
E 3
#endif
I 8
			{
E 8
				init_termbuf();
				tty_setecho(0);
				set_termbuf();
D 8
#ifdef	LINEMODE
E 8
			}
D 8
#endif
E 8
			break;

		case TELOPT_SGA:
#if	defined(LINEMODE) && defined(KLUDGELINEMODE)
			/*
D 3
			 * If kludge linemode is in use, then we must process an
			 * incoming do SGA for linemode purposes.
E 3
I 3
			 * If kludge linemode is in use, then we
			 * must process an incoming do SGA for
			 * linemode purposes.
E 3
			 */
D 11
			if (lmodetype == KLUDGE_LINEMODE) {
E 11
I 11
			if ((lmodetype == KLUDGE_LINEMODE) ||
			    (lmodetype == KLUDGE_OK)) {
E 11
				/*
D 3
				 * The client is asking us to turn linemode
				 * on.
E 3
I 3
				 * The client is asking us to turn
				 * linemode on.
E 3
				 */
I 11
				lmodetype = KLUDGE_LINEMODE;
E 11
				clientstat(TELOPT_LINEMODE, WILL, 0);
				/*
D 3
				 * If we did not turn line mode on, then what do
				 * we say?  Will SGA?  This violates design of
				 * telnet.  Gross.  Very Gross.
E 3
I 3
				 * If we did not turn line mode on,
				 * then what do we say?  Will SGA?
				 * This violates design of telnet.
				 * Gross.  Very Gross.
E 3
				 */
			}
I 8
			break;
#else
			set_my_want_state_wont(option);
			if (my_state_is_will(option))
				send_wont(option, 0);
			set_my_state_wont(option);
			if (turn_on_sga ^= 1)
D 11
				send_will(option);
E 11
I 11
				send_will(option, 1);
E 11
			return;
E 8
#endif	/* defined(LINEMODE) && defined(KLUDGELINEMODE) */

		default:
			break;
		}
D 3
	}
E 3

D 3
	if (request) {
		if (!((resp[option] == 0 && myopts[option] == OPT_NO) ||
		    mywants[option] == OPT_NO)) {
			mywants[option] = OPT_NO;
			fmt = wont;
			resp[option]++;
		}
	} else {
		if (resp[option]) {
			resp[option]--;
			if (resp[option] && myopts[option] == OPT_NO)
				resp[option]--;
		}
		if ((resp[option] == 0) && (mywants[option] != OPT_NO)) {
			mywants[option] = OPT_NO;
			fmt = wont;
		}
		myopts[option] = OPT_NO;
E 3
I 3
D 7
		mywants[option] = OPT_NO;
		send_wont(option, 0);
E 7
I 7
		set_my_want_state_wont(option);
		if (my_state_is_will(option))
			send_wont(option, 0);
E 7
E 3
	}
D 3

	if (fmt) {
	    (void) sprintf(nfrontp, fmt, option);
	    nfrontp += sizeof (wont) - 2;
	}
E 3
I 3
D 7
	myopts[option] = OPT_NO;
E 7
I 7
	set_my_state_wont(option);
E 7
E 3

}  /* end of dontoption */

I 13
#ifdef	ENV_HACK
D 16
int env_var = -1;
int env_value = -1;
E 16
I 16
int env_ovar = -1;
int env_ovalue = -1;
E 16
#else	/* ENV_HACK */
D 16
# define env_var ENV_VAR
# define env_value ENV_VALUE
E 16
I 16
# define env_ovar OLD_ENV_VAR
# define env_ovalue OLD_ENV_VALUE
E 16
#endif	/* ENV_HACK */

E 13
/*
 * suboption()
 *
 *	Look at the sub-option buffer, and try to be helpful to the other
 * side.
 *
 *	Currently we recognize:
 *
 *	Terminal type is
 *	Linemode
 *	Window size
 *	Terminal speed
 */
I 9
	void
E 9
suboption()
{
    register int subchar;
I 7
D 9
    extern void unsetenv();
E 9
E 7

I 7
D 9
#ifdef DIAGNOSTICS
	/*
	 * Report receiving option from other side.
	 */
	if (diagnostic & TD_OPTIONS) {
		netflush();	/* get rid of anything waiting to go out */
		printsub("td: recv", subpointer, SB_LEN()+2);
	}
#endif	DIAGNOSTIC
E 9
I 9
    DIAG(TD_OPTIONS, {netflush(); printsub('<', subpointer, SB_LEN()+2);});

E 9
E 7
    subchar = SB_GET();
    switch (subchar) {
    case TELOPT_TSPEED: {
	register int xspeed, rspeed;

D 7
	if (hisopts[TELOPT_TSPEED] == OPT_NO)	/* Ignore if option disabled */
E 7
I 7
	if (his_state_is_wont(TELOPT_TSPEED))	/* Ignore if option disabled */
E 7
		break;

	settimer(tspeedsubopt);

	if (SB_EOF() || SB_GET() != TELQUAL_IS)
		return;

D 9
	xspeed = atoi(subpointer);
E 9
I 9
	xspeed = atoi((char *)subpointer);
E 9

	while (SB_GET() != ',' && !SB_EOF());
	if (SB_EOF())
		return;

D 9
	rspeed = atoi(subpointer);
E 9
I 9
	rspeed = atoi((char *)subpointer);
E 9
	clientstat(TELOPT_TSPEED, xspeed, rspeed);

	break;

    }  /* end of case TELOPT_TSPEED */

    case TELOPT_TTYPE: {		/* Yaaaay! */
D 7
	static char terminalname[5+41] = "TERM=";
E 7
I 7
	static char terminalname[41];
E 7

D 2
	if (hisopts[TELOPT_TSPEED] == OPT_NO)	/* Ignore if option disabled */
E 2
I 2
D 7
	if (hisopts[TELOPT_TTYPE] == OPT_NO)	/* Ignore if option disabled */
E 7
I 7
	if (his_state_is_wont(TELOPT_TTYPE))	/* Ignore if option disabled */
E 7
E 2
		break;
	settimer(ttypesubopt);

D 9
	if (SB_GET() != TELQUAL_IS) {
E 9
I 9
	if (SB_EOF() || SB_GET() != TELQUAL_IS) {
E 9
	    return;		/* ??? XXX but, this is the most robust */
	}

D 7
	terminaltype = terminalname+sizeof("TERM=")-1;
E 7
I 7
	terminaltype = terminalname;
E 7

	while ((terminaltype < (terminalname + sizeof terminalname-1)) &&
								    !SB_EOF()) {
	    register int c;

	    c = SB_GET();
	    if (isupper(c)) {
		c = tolower(c);
	    }
	    *terminaltype++ = c;    /* accumulate name */
	}
	*terminaltype = 0;
	terminaltype = terminalname;
	break;
    }  /* end of case TELOPT_TTYPE */

    case TELOPT_NAWS: {
	register int xwinsize, ywinsize;

D 7
	if (hisopts[TELOPT_NAWS] == OPT_NO)	/* Ignore if option disabled */
E 7
I 7
	if (his_state_is_wont(TELOPT_NAWS))	/* Ignore if option disabled */
E 7
		break;

	if (SB_EOF())
		return;
	xwinsize = SB_GET() << 8;
	if (SB_EOF())
		return;
	xwinsize |= SB_GET();
	if (SB_EOF())
		return;
	ywinsize = SB_GET() << 8;
	if (SB_EOF())
		return;
	ywinsize |= SB_GET();
	clientstat(TELOPT_NAWS, xwinsize, ywinsize);

	break;

    }  /* end of case TELOPT_NAWS */

#ifdef	LINEMODE
    case TELOPT_LINEMODE: {
	register int request;

D 7
	if (hisopts[TELOPT_LINEMODE] == OPT_NO)	/* Ignore if option disabled */
E 7
I 7
	if (his_state_is_wont(TELOPT_LINEMODE))	/* Ignore if option disabled */
E 7
		break;
	/*
	 * Process linemode suboptions.
	 */
D 9
	if (SB_EOF()) break;  /* garbage was sent */
	request = SB_GET();  /* get will/wont */
	if (SB_EOF()) break;  /* another garbage check */
E 9
I 9
	if (SB_EOF())
	    break;		/* garbage was sent */
	request = SB_GET();	/* get will/wont */
E 9

I 9
	if (SB_EOF())
	    break;		/* another garbage check */

E 9
	if (request == LM_SLC) {  /* SLC is not preceeded by WILL or WONT */
		/*
		 * Process suboption buffer of slc's
		 */
		start_slc(1);
		do_opt_slc(subpointer, subend - subpointer);
D 9
		end_slc(0);

E 9
I 9
		(void) end_slc(0);
		break;
E 9
	} else if (request == LM_MODE) {
I 9
		if (SB_EOF())
		    return;
E 9
		useeditmode = SB_GET();  /* get mode flag */
		clientstat(LM_MODE, 0, 0);
I 9
		break;
E 9
	}

I 9
	if (SB_EOF())
	    break;
E 9
	switch (SB_GET()) {  /* what suboption? */
	case LM_FORWARDMASK:
		/*
		 * According to spec, only server can send request for
		 * forwardmask, and client can only return a positive response.
		 * So don't worry about it.
		 */

	default:
		break;
	}
D 5

E 5
I 5
	break;
E 5
    }  /* end of case TELOPT_LINEMODE */
#endif
    case TELOPT_STATUS: {
	int mode;

I 9
	if (SB_EOF())
	    break;
E 9
	mode = SB_GET();
	switch (mode) {
	case TELQUAL_SEND:
D 7
	    if (myopts[TELOPT_STATUS] == OPT_YES)
E 7
I 7
	    if (my_state_is_will(TELOPT_STATUS))
E 7
		send_status();
	    break;

	case TELQUAL_IS:
	    break;

	default:
	    break;
	}
D 5
    }
E 5
I 5
	break;
    }  /* end of case TELOPT_STATUS */
E 5

I 7
    case TELOPT_XDISPLOC: {
	if (SB_EOF() || SB_GET() != TELQUAL_IS)
		return;
	settimer(xdisplocsubopt);
	subpointer[SB_LEN()] = '\0';
D 9
	setenv("DISPLAY", subpointer, 1);
E 9
I 9
	(void)setenv("DISPLAY", (char *)subpointer, 1);
E 9
	break;
    }  /* end of case TELOPT_XDISPLOC */

D 16
    case TELOPT_ENVIRON: {
E 16
I 16
#ifdef	TELOPT_NEW_ENVIRON
    case TELOPT_NEW_ENVIRON:
#endif
    case TELOPT_OLD_ENVIRON: {
E 16
	register int c;
	register char *cp, *varp, *valp;

	if (SB_EOF())
		return;
	c = SB_GET();
D 16
	if (c == TELQUAL_IS)
		settimer(environsubopt);
	else if (c != TELQUAL_INFO)
E 16
I 16
	if (c == TELQUAL_IS) {
		if (subchar == TELOPT_OLD_ENVIRON)
			settimer(oenvironsubopt);
		else
			settimer(environsubopt);
	} else if (c != TELQUAL_INFO) {
E 16
		return;
I 16
	}
E 16

I 16
#ifdef	TELOPT_NEW_ENVIRON
	if (subchar == TELOPT_NEW_ENVIRON) {
	    while (!SB_EOF()) {
		c = SB_GET();
		if ((c == NEW_ENV_VAR) || (c == ENV_USERVAR))
			break;
	    }
	} else
#endif
	{
E 16
I 13
#ifdef	ENV_HACK
D 16
	/*
	 * We only want to do this if we haven't already decided
	 * whether or not the other side has its VALUE and VAR
	 * reversed.
	 */
	if (env_var < 0) {
E 16
I 16
	    /*
	     * We only want to do this if we haven't already decided
	     * whether or not the other side has its VALUE and VAR
	     * reversed.
	     */
	    if (env_ovar < 0) {
E 16
		register int last = -1;		/* invalid value */
		int empty = 0;
		int got_var = 0, got_value = 0, got_uservar = 0;

		/*
		 * The other side might have its VALUE and VAR values
		 * reversed.  To be interoperable, we need to determine
		 * which way it is.  If the first recognized character
		 * is a VAR or VALUE, then that will tell us what
		 * type of client it is.  If the fist recognized
		 * character is a USERVAR, then we continue scanning
		 * the suboption looking for two consecutive
		 * VAR or VALUE fields.  We should not get two
		 * consecutive VALUE fields, so finding two
		 * consecutive VALUE or VAR fields will tell us
		 * what the client is.
		 */
		SB_SAVE();
		while (!SB_EOF()) {
			c = SB_GET();
			switch(c) {
D 16
			case ENV_VAR:
				if (last < 0 || last == ENV_VAR
				    || (empty && (last == ENV_VALUE)))
					goto env_var_ok;
E 16
I 16
			case OLD_ENV_VAR:
				if (last < 0 || last == OLD_ENV_VAR
				    || (empty && (last == OLD_ENV_VALUE)))
					goto env_ovar_ok;
E 16
				got_var++;
D 16
				last = ENV_VAR;
E 16
I 16
				last = OLD_ENV_VAR;
E 16
				break;
D 16
			case ENV_VALUE:
				if (last < 0 || last == ENV_VALUE
				    || (empty && (last == ENV_VAR)))
					goto env_var_wrong;
E 16
I 16
			case OLD_ENV_VALUE:
				if (last < 0 || last == OLD_ENV_VALUE
				    || (empty && (last == OLD_ENV_VAR)))
					goto env_ovar_wrong;
E 16
				got_value++;
D 16
				last = ENV_VALUE;
E 16
I 16
				last = OLD_ENV_VALUE;
E 16
				break;
			case ENV_USERVAR:
				/* count strings of USERVAR as one */
				if (last != ENV_USERVAR)
					got_uservar++;
				if (empty) {
D 16
					if (last == ENV_VALUE)
						goto env_var_ok;
					if (last == ENV_VAR)
						goto env_var_wrong;
E 16
I 16
					if (last == OLD_ENV_VALUE)
						goto env_ovar_ok;
					if (last == OLD_ENV_VAR)
						goto env_ovar_wrong;
E 16
				}
				last = ENV_USERVAR;
				break;
			case ENV_ESC:
				if (!SB_EOF())
					c = SB_GET();
				/* FALL THROUGH */
			default:
				empty = 0;
				continue;
			}
			empty = 1;
		}
		if (empty) {
D 16
			if (last == ENV_VALUE)
				goto env_var_ok;
			if (last == ENV_VAR)
				goto env_var_wrong;
E 16
I 16
			if (last == OLD_ENV_VALUE)
				goto env_ovar_ok;
			if (last == OLD_ENV_VAR)
				goto env_ovar_wrong;
E 16
		}
		/*
		 * Ok, the first thing was a USERVAR, and there
		 * are not two consecutive VAR or VALUE commands,
		 * and none of the VAR or VALUE commands are empty.
		 * If the client has sent us a well-formed option,
		 * then the number of VALUEs received should always
		 * be less than or equal to the number of VARs and
		 * USERVARs received.
		 *
		 * If we got exactly as many VALUEs as VARs and
		 * USERVARs, the client has the same definitions.
		 *
D 14
		 * If we get more VARs than the total number of VALUEs
		 * and USERVARs, the client has the same definitions.
		 *
E 14
		 * If we got exactly as many VARs as VALUEs and
		 * USERVARS, the client has reversed definitions.
D 14
		 *
		 * If we get more VALUEs than the total number of VARs
		 * and USERVARs, the client has reversed definitions
E 14
		 */
D 14
		if ((got_uservar + got_var == got_value) ||
		    (got_var > got_uservar + got_value)) {
E 14
I 14
		if (got_uservar + got_var == got_value) {
E 14
D 16
	    env_var_ok:
			env_var = ENV_VAR;
			env_value = ENV_VALUE;
E 16
I 16
	    env_ovar_ok:
			env_ovar = OLD_ENV_VAR;
			env_ovalue = OLD_ENV_VALUE;
E 16
D 14
		} else if ((got_uservar + got_value == got_var) ||
			   (got_value > got_uservar + got_var)) {
E 14
I 14
		} else if (got_uservar + got_value == got_var) {
E 14
D 16
	    env_var_wrong:
			env_var = ENV_VALUE;
			env_value = ENV_VAR;
E 16
I 16
	    env_ovar_wrong:
			env_ovar = OLD_ENV_VALUE;
			env_ovalue = OLD_ENV_VAR;
E 16
			DIAG(TD_OPTIONS, {sprintf(nfrontp,
				"ENVIRON VALUE and VAR are reversed!\r\n");
				nfrontp += strlen(nfrontp);});

		}
D 16
	}
	SB_RESTORE();
E 16
I 16
	    }
	    SB_RESTORE();
E 16
#endif

E 13
D 11
	while (!SB_EOF() && SB_GET() != ENV_VAR)
		;
E 11
I 11
D 16
	while (!SB_EOF()) {
E 16
I 16
	    while (!SB_EOF()) {
E 16
		c = SB_GET();
D 13
		if ((c == ENV_VAR) || (c == ENV_USERVAR))
E 13
I 13
D 16
		if ((c == env_var) || (c == ENV_USERVAR))
E 16
I 16
		if ((c == env_ovar) || (c == ENV_USERVAR))
E 16
E 13
			break;
I 16
	    }
E 16
	}
E 11

	if (SB_EOF())
		return;

D 9
	cp = varp = subpointer;
E 9
I 9
	cp = varp = (char *)subpointer;
E 9
	valp = 0;

	while (!SB_EOF()) {
D 13
		switch (c = SB_GET()) {
E 13
I 13
		c = SB_GET();
D 16
#ifdef	ENV_HACK
		if (c == env_var)
			c = ENV_VAR;
		else if (c == env_value)
			c = ENV_VALUE;
#endif
E 16
I 16
		if (subchar == TELOPT_OLD_ENVIRON) {
			if (c == env_ovar)
				c = NEW_ENV_VAR;
			else if (c == env_ovalue)
				c = NEW_ENV_VALUE;
		}
E 16
		switch (c) {

E 13
D 16
		case ENV_VALUE:
E 16
I 16
		case NEW_ENV_VALUE:
E 16
			*cp = '\0';
D 9
			cp = valp = subpointer;
E 9
I 9
			cp = valp = (char *)subpointer;
E 9
			break;

D 16
		case ENV_VAR:
E 16
I 16
		case NEW_ENV_VAR:
E 16
I 11
		case ENV_USERVAR:
E 11
			*cp = '\0';
			if (valp)
D 9
				setenv(varp, valp, 1);
E 9
I 9
				(void)setenv(varp, valp, 1);
E 9
			else
				unsetenv(varp);
D 9
			cp = varp = subpointer;
E 9
I 9
			cp = varp = (char *)subpointer;
E 9
			valp = 0;
			break;

		case ENV_ESC:
			if (SB_EOF())
				break;
			c = SB_GET();
			/* FALL THROUGH */
		default:
			*cp++ = c;
			break;
		}
	}
	*cp = '\0';
	if (valp)
D 9
		setenv(varp, valp, 1);
E 9
I 9
		(void)setenv(varp, valp, 1);
E 9
	else
		unsetenv(varp);
	break;
D 16
    }  /* end of case TELOPT_ENVIRON */
E 16
I 16
    }  /* end of case TELOPT_NEW_ENVIRON */
E 16
I 9
D 11
#if	defined(AUTHENTICATE)
E 11
I 11
#if	defined(AUTHENTICATION)
E 11
    case TELOPT_AUTHENTICATION:
	if (SB_EOF())
		break;
	switch(SB_GET()) {
	case TELQUAL_SEND:
	case TELQUAL_REPLY:
		/*
		 * These are sent by us and cannot be sent by
		 * the client.
		 */
		break;
	case TELQUAL_IS:
		auth_is(subpointer, SB_LEN());
		break;
I 10
	case TELQUAL_NAME:
		auth_name(subpointer, SB_LEN());
		break;
E 10
	}
	break;
#endif
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
    case TELOPT_ENCRYPT:
	if (SB_EOF())
		break;
	switch(SB_GET()) {
	case ENCRYPT_SUPPORT:
		encrypt_support(subpointer, SB_LEN());
		break;
	case ENCRYPT_IS:
		encrypt_is(subpointer, SB_LEN());
		break;
	case ENCRYPT_REPLY:
		encrypt_reply(subpointer, SB_LEN());
		break;
	case ENCRYPT_START:
D 10
		encrypt_start();
E 10
I 10
		encrypt_start(subpointer, SB_LEN());
E 10
		break;
	case ENCRYPT_END:
		encrypt_end();
		break;
	case ENCRYPT_REQSTART:
D 10
		encrypt_request_start();
E 10
I 10
		encrypt_request_start(subpointer, SB_LEN());
E 10
		break;
	case ENCRYPT_REQEND:
		/*
		 * We can always send an REQEND so that we cannot
		 * get stuck encrypting.  We should only get this
		 * if we have been able to get in the correct mode
		 * anyhow.
		 */
		encrypt_request_end();
I 10
		break;
	case ENCRYPT_ENC_KEYID:
		encrypt_enc_keyid(subpointer, SB_LEN());
		break;
	case ENCRYPT_DEC_KEYID:
		encrypt_dec_keyid(subpointer, SB_LEN());
E 10
		break;
	default:
		break;
	}
	break;
D 14
#endif
E 14
I 14
#endif	/* ENCRYPTION */
E 14
E 9

E 7
    default:
	break;
    }  /* end of switch */

}  /* end of suboption */

I 9
	void
doclientstat()
{
	clientstat(TELOPT_LINEMODE, WILL, 0);
}

E 9
D 17
#define	ADD(c)	 *ncp++ = c;
#define	ADD_DATA(c) { *ncp++ = c; if (c == SE) *ncp++ = c; }
E 17
I 17
#define	ADD(c)	 *ncp++ = c
#define	ADD_DATA(c) { *ncp++ = c; if (c == SE || c == IAC) *ncp++ = c; }
E 17
I 9
	void
E 9
send_status()
{
D 7
	char statusbuf[256];
	register char *ncp;
	register int i;
E 7
I 7
	unsigned char statusbuf[256];
	register unsigned char *ncp;
	register unsigned char i;
E 7

	ncp = statusbuf;

	netflush();	/* get rid of anything waiting to go out */

	ADD(IAC);
	ADD(SB);
	ADD(TELOPT_STATUS);
	ADD(TELQUAL_IS);

I 9
	/*
	 * We check the want_state rather than the current state,
	 * because if we received a DO/WILL for an option that we
	 * don't support, and the other side didn't send a DONT/WONT
	 * in response to our WONT/DONT, then the "state" will be
	 * WILL/DO, and the "want_state" will be WONT/DONT.  We
	 * need to go by the latter.
	 */
E 9
D 16
	for (i = 0; i < NTELOPTS; i++) {
E 16
I 16
	for (i = 0; i < (unsigned char)NTELOPTS; i++) {
E 16
D 7
		if (myopts[i] == OPT_YES) {
E 7
I 7
D 9
		if (my_state_is_will(i)) {
E 9
I 9
		if (my_want_state_is_will(i)) {
E 9
E 7
			ADD(WILL);
			ADD_DATA(i);
D 17
			if (i == IAC)
				ADD(IAC);
E 17
		}
D 7
		if (hisopts[i] == OPT_YES) {
E 7
I 7
D 9
		if (his_state_is_will(i)) {
E 9
I 9
		if (his_want_state_is_will(i)) {
E 9
E 7
			ADD(DO);
			ADD_DATA(i);
D 17
			if (i == IAC)
				ADD(IAC);
E 17
		}
	}

I 9
	if (his_want_state_is_will(TELOPT_LFLOW)) {
		ADD(SB);
		ADD(TELOPT_LFLOW);
D 11
		ADD(flowmode);
E 11
I 11
		if (flowmode) {
			ADD(LFLOW_ON);
		} else {
			ADD(LFLOW_OFF);
		}
E 11
		ADD(SE);
I 11

		if (restartany >= 0) {
D 17
			ADD(SB)
E 17
I 17
			ADD(SB);
E 17
			ADD(TELOPT_LFLOW);
			if (restartany) {
				ADD(LFLOW_RESTART_ANY);
			} else {
				ADD(LFLOW_RESTART_XON);
			}
D 17
			ADD(SE)
			ADD(SB);
E 17
I 17
			ADD(SE);
E 17
		}
E 11
	}

E 9
#ifdef	LINEMODE
D 7
	if (hisopts[TELOPT_LINEMODE] == OPT_YES) {
		char *cp, *cpe;
E 7
I 7
D 9
	if (his_state_is_will(TELOPT_LINEMODE)) {
E 9
I 9
	if (his_want_state_is_will(TELOPT_LINEMODE)) {
E 9
		unsigned char *cp, *cpe;
E 7
		int len;

		ADD(SB);
		ADD(TELOPT_LINEMODE);
		ADD(LM_MODE);
		ADD_DATA(editmode);
D 17
		if (editmode == IAC)
			ADD(IAC);
E 17
		ADD(SE);

		ADD(SB);
		ADD(TELOPT_LINEMODE);
		ADD(LM_SLC);
		start_slc(0);
		send_slc();
		len = end_slc(&cp);
		for (cpe = cp + len; cp < cpe; cp++)
			ADD_DATA(*cp);
		ADD(SE);
	}
#endif	/* LINEMODE */

	ADD(IAC);
	ADD(SE);

	writenet(statusbuf, ncp - statusbuf);
	netflush();	/* Send it on its way */
I 7
D 9
#ifdef DIAGNOSTICS
	/*
	 * Report sending status suboption.
	 */
	if (diagnostic & TD_OPTIONS) {
		printsub("td: send", statusbuf, ncp - statusbuf);
		netflush();	/* Send it on its way */
	}
#endif	DIAGNOSTIC
E 7
}
E 9
I 7

D 9
#ifdef	NO_SETENV
#include "setenv.c"
#endif
E 9
I 9
	DIAG(TD_OPTIONS,
		{printsub('>', statusbuf, ncp - statusbuf); netflush();});
}
E 9
E 7
E 1
