h10176
s 00002/00002/00409
d D 8.1 93/06/04 16:51:57 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00107/00102/00304
d D 5.2 92/07/03 00:23:52 christos 2 1
c Up-to-date with cornell's last RCS version
e
s 00406/00000/00000
d D 5.1 92/06/22 18:08:31 bostic 1 0
c date and time created 92/06/22 18:08:31 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Christos Zoulas of Cornell University.
 *
 * %sccs.include.redist.c%
 */

D 2
#ifndef lint
E 2
I 2
#if !defined(lint) && !defined(SCCSID)
E 2
static char sccsid[] = "%W% (Berkeley) %G%";
D 2
#endif /* not lint */
E 2

I 2
#endif /* not lint && not SCCSID */
E 2
/*
D 2
 * el.read.c: Clean this junk up! This is horrible code.
 *	      Terminal read functions
E 2
I 2
 * read.c: Clean this junk up! This is horrible code.
 *	   Terminal read functions
E 2
 */
#include "sys.h"
#include <sys/errno.h>
#include <unistd.h>
#include <stdlib.h>
extern int errno;
#include "el.h"

#define OKCMD -1

I 2
private int read__fixio		__P((int, int));
private int read_preread	__P((EditLine *));
private int read_getcmd		__P((EditLine *, el_action_t *, char *));

E 2
#ifdef DEBUG_EDIT
private void
read_debug(el)
    EditLine *el;
{

    if (el->el_line.cursor > el->el_line.lastchar)
	(void) fprintf(el->el_errfile, "cursor > lastchar\r\n");
    if (el->el_line.cursor < el->el_line.buffer)
	(void) fprintf(el->el_errfile, "cursor < buffer\r\n");
    if (el->el_line.cursor > el->el_line.limit)
	(void) fprintf(el->el_errfile, "cursor > limit\r\n");
    if (el->el_line.lastchar > el->el_line.limit)
	(void) fprintf(el->el_errfile, "lastchar > limit\r\n");
    if (el->el_line.limit != &el->el_line.buffer[EL_BUFSIZ - 2])
	(void) fprintf(el->el_errfile, "limit != &buffer[EL_BUFSIZ-2]\r\n");
D 2
#ifdef notyet
    if ((!DoingArg) && (Argument != 1))
	(void) fprintf(el->el_errfile, "(!DoingArg) && (Argument != 1)\r\n");
    if (CcKeyMap[0] == 0)
	(void) fprintf(el->el_errfile, "CcKeyMap[0] == 0 (maybe not inited)\r\n");
#endif
E 2
}
D 2
#endif
E 2
I 2
#endif /* DEBUG_EDIT */
E 2

D 2
#ifdef notyet
int
el_preread(el)
E 2
I 2
/* read__fixio():
 *	Try to recover from a read error
 */
private int
read__fixio(fd, e)
    int fd, e;
E 2
{
D 2
    long    chrs = 0;
    static Char *Input_Line = NULL;
E 2
I 2
    switch (e) {
    case -1:	/* Make sure that the code is reachable */
E 2

D 2
    if (Input_Line)
	xfree((ptr_t) Input_Line);
    Input_Line = NULL;
E 2
I 2
#ifdef EWOULDBLOCK
    case EWOULDBLOCK:
# define TRY_AGAIN
#endif /* EWOULDBLOCK */
E 2

D 2
    if (Tty_raw_mode)
E 2
I 2
#if defined(POSIX) && defined(EAGAIN)
# if defined(EWOULDBLOCK) && EWOULDBLOCK != EAGAIN
    case EAGAIN:
#  define TRY_AGAIN
# endif /* EWOULDBLOCK && EWOULDBLOCK != EAGAIN */
#endif /* POSIX && EAGAIN */

	e = 0;
#ifdef TRY_AGAIN
# if defined(F_SETFL) && defined(O_NDELAY)
	if ((e = fcntl(fd, F_GETFL, 0)) == -1)
	    return -1;

	if (fcntl(fd, F_SETFL, e & ~O_NDELAY) == -1)
	    return -1;
	else 
	    e = 1;
# endif /* F_SETFL && O_NDELAY */

# ifdef FIONBIO
	if (ioctl(fd, FIONBIO, (ioctl_t) &e) == -1)
	    return -1;
	else
	    e = 1;
# endif	/* FIONBIO */

#endif /* TRY_AGAIN */
	return e ? 0 : -1;

    case EINTR:
E 2
	return 0;

I 2
    default:
	return -1;
    }
}


/* read_preread():
 *	Try to read the stuff in the input queue;
 */
private int
read_preread(el)
    EditLine *el;
{
    int    chrs = 0;

    if (el->el_chared.c_macro.nline) {
	el_free((ptr_t) el->el_chared.c_macro.nline);
	el->el_chared.c_macro.nline = NULL;
    }

    if (el->el_tty.t_mode == ED_IO)
	return 0;

E 2
#ifdef FIONREAD
D 2
    (void) ioctl(SHIN, FIONREAD, &chrs);
E 2
I 2
    (void) ioctl(el->el_infd, FIONREAD, (ioctl_t) &chrs);
E 2
    if (chrs > 0) {
D 2
	char    buf[BUFSIZE];
E 2
I 2
	char    buf[EL_BUFSIZ];
E 2

D 2
	chrs = read(SHIN, buf, (size_t) min(chrs, BUFSIZE - 1));
E 2
I 2
	chrs = read(el->el_infd, buf, (size_t) MIN(chrs, EL_BUFSIZ - 1));
E 2
	if (chrs > 0) {
	    buf[chrs] = '\0';
D 2
	    Input_Line = Strsave(str2short(buf));
	    PushMacro(Input_Line);
E 2
I 2
	    el->el_chared.c_macro.nline = strdup(buf);
	    el_push(el->el_chared.c_macro.nline);
E 2
	}
    }
#endif  /* FIONREAD */
I 2

E 2
    return chrs > 0;
}
D 2
#endif
E 2


D 2

E 2
/* el_push():
 *	Push a macro
 */
public void
el_push(el, str)
    EditLine *el;
    const char   *str;
{
    c_macro_t *ma = &el->el_chared.c_macro;

    if (str != NULL && ma->level + 1 < EL_MAXMACRO) {
	ma->level++;
	ma->macro[ma->level] = (char *) str;
    }
    else {
	term_beep(el);
	term__flush();
    }
}

I 2

/* read_getcmd():
 *	Return next command from the input stream.
 */
E 2
private int
D 2
el_getcmd(el, cmdnum, ch)
E 2
I 2
read_getcmd(el, cmdnum, ch)
E 2
    EditLine *el;
    el_action_t *cmdnum;
    char *ch;
{
    el_action_t  cmd = 0;
    int     num;

    while (cmd == 0 || cmd == ED_SEQUENCE_LEAD_IN) {
	if ((num = el_getc(el, ch)) != 1)	/* if EOF or error */
	    return num;

#ifdef	KANJI
	if ((*ch & 0200)) {
	    el->el_state.metanext = 0;
	    cmd = CcViMap[' '];
	    break;
	}
	else
#endif /* KANJI */

	if (el->el_state.metanext) {
	    el->el_state.metanext = 0;
	    *ch |= 0200;
	}
	cmd = el->el_map.current[(unsigned char) *ch];
	if (cmd == ED_SEQUENCE_LEAD_IN) {
	    key_value_t val;
	    switch (key_get(el, ch, &val)) {
	    case XK_CMD:
		cmd = val.cmd;
		break;
	    case XK_STR:
		el_push(el, val.str);
		break;
#ifdef notyet
	    case XK_EXE:
		/* XXX: In the future to run a user function */
		RunCommand(val.str);
		break;
#endif
	    default:
		abort();
		break;
	    }
	}
	if (el->el_map.alt == NULL) 
	    el->el_map.current = el->el_map.key;
    }
    *cmdnum = cmd;
    return OKCMD;
}


/* el_getc():
 *	Read a character
 */
public int
el_getc(el, cp)
    EditLine *el;
    char *cp;
{
    int num_read;
D 2
#if defined(EWOULDBLOCK) || (defined(POSIX) && defined(EAGAIN))
# if defined(FIONBIO) || (defined(F_SETFL) && defined(O_NDELAY))
#  define TRY_AGAIN
    int     tried = 0;
# endif /* FIONBIO || (F_SETFL && O_NDELAY) */
#endif /* EWOULDBLOCK || (POSIX && EAGAIN) */
E 2
    unsigned char tcp;
I 2
    int tried = 0;
E 2

    c_macro_t *ma = &el->el_chared.c_macro;

    term__flush();
    for (;;) {
D 2
#ifdef notyet
E 2
	if (ma->level < 0) {
D 2
	    if (!el_preread(el))
E 2
I 2
	    if (!read_preread(el))
E 2
		break;
	}
D 2
#endif
E 2
	if (ma->level < 0) 
	    break;
   
	if (*ma->macro[ma->level] == 0) {
	    ma->level--;
	    continue;
	}
	*cp = *ma->macro[ma->level]++ & 0377;
	if (*ma->macro[ma->level] == 0) {	/* Needed for QuoteMode On */
	    ma->level--;
	}
	return 1;
    }

#ifdef DEBUG_READ
    (void) fprintf(el->el_errfile, "Turning raw mode on\n");
D 2
#endif
E 2
I 2
#endif /* DEBUG_READ */
E 2
    if (tty_rawmode(el) < 0)	/* make sure the tty is set up correctly */
D 2
	return 0;		/* oops: SHIN was closed */
E 2
I 2
	return 0;
E 2

#ifdef DEBUG_READ
    (void) fprintf(el->el_errfile, "Reading a character\n");
D 2
#endif
E 2
I 2
#endif /* DEBUG_READ */
E 2
    while ((num_read = read(el->el_infd, (char *) &tcp, 1)) == -1)
D 2
	switch (errno) {
	    /*
	     * Someone might have set our file descriptor to non blocking From
	     * Gray Watson (gray%antr.uucp@med.pitt.edu), Thanks!!!
	     */
#ifdef EWOULDBLOCK
	case EWOULDBLOCK:
#endif /* EWOULDBLOCK */
#if defined(POSIX) && defined(EAGAIN)
# if defined(EWOULDBLOCK) && EAGAIN != EWOULDBLOCK
	case EAGAIN:
# endif /* EWOULDBLOCK && EAGAIN != EWOULDBLOCK */
#endif /* POSIX && EAGAIN */
#ifdef TRY_AGAIN
	    if (!tried) {
# if defined(F_SETFL) && defined(O_NDELAY)
		(void) fcntl(SHIN, F_SETFL,
			     fcntl(SHIN, F_GETFL, 0) & ~O_NDELAY);
# endif /* F_SETFL && O_NDELAY */
# ifdef FIONBIO
		(void) ioctl(SHIN, FIONBIO, (ioctl_t) & tried);
# endif /* FIONBIO */
		tried = 1;
		break;
	    }
	    *cp = tcp;
	    return (num_read);
#endif /* TRY_AGAIN */
	case EINTR:
	    break;
	default:
#ifdef DEBUG_EDIT
	    (void) fprintf(el->el_errfile, "GetNextChar(): errno == %d\n", errno);
#endif /* DEBUG_EDIT */
	    *cp = tcp;
	    return num_read;
E 2
I 2
	if (!tried && read__fixio(el->el_infd, errno) == 0)
	    tried = 1;
	else {
	    *cp = '\0';
	    return -1;
E 2
	}
#ifdef DEBUG_READ
    (void) fprintf(el->el_errfile, "Got it %c\n", tcp);
D 2
#endif
E 2
I 2
#endif /* DEBUG_READ */
E 2
    *cp = tcp;
    return num_read;
}



public const char *
el_gets(el, nread)
    EditLine *el;
    int *nread;
{
    int retval;
    el_action_t  cmdnum = 0;
    int     num;		/* how many chars we have read at NL */
    char    ch;

    if (el->el_flags & HANDLE_SIGNALS)
	sig_set(el);

    re_clear_display(el);		/* reset the display stuff */
    ch_reset(el);

D 2
#ifdef notyet
E 2
#ifdef FIONREAD
D 2
    if (!Tty_raw_mode && ma->level < 0) {
E 2
I 2
    if (el->el_tty.t_mode == EX_IO && ma->level < 0) {
E 2
	long    chrs = 0;

D 2
	(void) ioctl(SHIN, FIONREAD, (ioctl_t) & chrs);
E 2
I 2
	(void) ioctl(el->el_infd, FIONREAD, (ioctl_t) &chrs);
E 2
	if (chrs == 0) {
	    if (tty_rawmode(el) < 0) {
		if (nread)
			*nread = 0;
		return NULL;
	    }
	}
    }
D 2
#endif
#endif
E 2
I 2
#endif /* FIONREAD */
E 2

    re_refresh(el);			/* print the prompt */

    for (num = OKCMD; num == OKCMD;) {	/* while still editing this line */
#ifdef DEBUG_EDIT
	read_debug(el);
D 2
#endif
E 2
I 2
#endif /* DEBUG_EDIT */
E 2
	/* if EOF or error */
D 2
	if ((num = el_getcmd(el, &cmdnum, &ch)) != OKCMD) {
E 2
I 2
	if ((num = read_getcmd(el, &cmdnum, &ch)) != OKCMD) {
E 2
#ifdef DEBUG_READ
	    (void) fprintf(el->el_errfile, "Returning from el_gets %d\n", num);
D 2
#endif
E 2
I 2
#endif /* DEBUG_READ */
E 2
	    break;
	}

	if (cmdnum >= el->el_map.nfunc) {	/* BUG CHECK command */
#ifdef DEBUG_EDIT
D 2
	    (void) fprintf(el->el_errfile, "ERROR: illegal command from key 0%o\r\n", ch);
#endif
E 2
I 2
	    (void) fprintf(el->el_errfile, 
			   "ERROR: illegal command from key 0%o\r\n", ch);
#endif /* DEBUG_EDIT */
E 2
	    continue;		/* try again */
	}

	/* now do the real command */
#ifdef DEBUG_READ
	{
	    el_bindings_t *b;
	    for (b = el->el_map.help; b->name; b++)
		if (b->func == cmdnum)
		    break;
	    if (b->name)
		(void) fprintf(el->el_errfile, "Executing %s\n", b->name);
	    else
		(void) fprintf(el->el_errfile, "Error command = %d\n", cmdnum);
	}
D 2
#endif
E 2
I 2
#endif /* DEBUG_READ */
E 2
	retval = (*el->el_map.func[cmdnum])(el, ch);

	/* save the last command here */
	el->el_state.lastcmd = cmdnum;

	/* use any return value */
	switch (retval) {
	case CC_CURSOR:
	    el->el_state.argument = 1;
	    el->el_state.doingarg = 0;
	    re_refresh_cursor(el);
	    break;

	case CC_REFRESH:
	    el->el_state.argument = 1;
	    el->el_state.doingarg = 0;
	    re_refresh(el);
	    break;

	case CC_NORM:		/* normal char */
	    el->el_state.argument = 1;
	    el->el_state.doingarg = 0;
	    break;

	case CC_ARGHACK:	/* Suggested by Rich Salz */
	    /* <rsalz@pineapple.bbn.com> */
	    break;		/* keep going... */

	case CC_EOF:		/* end of file typed */
	    num = 0;
	    break;

	case CC_NEWLINE:	/* normal end of line */
	    num = el->el_line.lastchar - el->el_line.buffer;	
D 2
	    /* return the number of chars read */
#ifdef notyet
	    /*
	     * For continuation lines, we set the prompt to prompt 2
	     */
	    if (imode) {
		if (!Strcmp(*(imode->vec), STRinsert))
		    inputmode = MODE_INSERT;
		else if (!Strcmp(*(imode->vec), STRoverwrite))
		    inputmode = MODE_REPLACE;
	    }
	    printprompt(1, NULL);
#endif
E 2
	    break;

	case CC_FATAL:		/* fatal error, reset to known state */
#ifdef DEBUG_READ
	    (void) fprintf(el->el_errfile, "*** editor fatal ERROR ***\r\n\n");
#endif /* DEBUG_READ */
	    /* put (real) cursor in a known place */
	    re_clear_display(el);	/* reset the display stuff */
	    ch_reset(el);		/* reset the input pointers */
	    re_refresh(el);		/* print the prompt again */
	    el->el_state.argument = 1;
	    el->el_state.doingarg = 0;
	    break;

	case CC_ERROR:
	default:		/* functions we don't know about */
#ifdef DEBUG_READ
	    (void) fprintf(el->el_errfile, "*** editor ERROR ***\r\n\n");
D 2
#endif
E 2
I 2
#endif /* DEBUG_READ */
E 2
	    el->el_state.argument = 1;
	    el->el_state.doingarg = 0;
	    term_beep(el);
	    term__flush();
	    break;
	}
    }

    (void) tty_cookedmode(el);	/* make sure the tty is set up correctly */
    term__flush();		/* flush any buffered output */
    if (el->el_flags & HANDLE_SIGNALS)
	sig_clr(el);
    if (nread)
	    *nread = num;
    return num ? el->el_line.buffer : NULL;
}
E 1
