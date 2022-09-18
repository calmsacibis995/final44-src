h07970
s 00006/00004/00222
d D 8.2 95/04/27 13:37:50 bostic 12 11
c :a in 'more' causes null dereference
c ex: more /root/.cshrc<CR>:a<CR>
c From: "Chris G. Demetriou" <cgd@sun-lamp.cs.berkeley.edu>
e
s 00002/00002/00224
d D 8.1 93/06/06 15:37:07 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00224
d D 5.10 91/07/24 21:15:24 cael 10 9
c fix off-by-one column errors (needs more work, this gets
c most of the ugliness away from *my* man pages, harumph)
e
s 00001/00012/00225
d D 5.9 90/06/01 17:04:39 bostic 9 8
c new copyright notice
e
s 00009/00003/00228
d D 5.8 88/12/06 15:16:37 bostic 8 7
c add ":a[rgs]" command from vi
e
s 00009/00000/00222
d D 5.7 88/12/03 16:24:54 sam 7 6
c purge pending output when fielding SIGINT (signal handling still 
c is not right -- need to watch out for partial writes?)
e
s 00008/00007/00214
d D 5.6 88/11/26 12:19:03 bostic 6 5
c on error, allow command character as well as return to continue
e
s 00020/00064/00201
d D 5.5 88/11/22 16:51:42 bostic 5 4
c less -> more
e
s 00002/00004/00263
d D 5.4 88/07/25 12:05:10 bostic 4 3
c update copyright notice
e
s 00000/00009/00267
d D 5.3 88/07/22 12:06:35 bostic 3 2
c dropout function never used
e
s 00000/00005/00276
d D 5.2 88/07/21 19:22:40 bostic 2 1
c rip out ONLY_RETURN define
e
s 00281/00000/00000
d D 5.1 88/07/21 18:53:18 bostic 1 0
c distribution by Mark Nudleman
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 Mark Nudleman
D 11
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
D 4
 * This code is derived from software contributed to Berkeley by
 * Mark Nudleman.
 * 
E 4
D 9
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
D 4
 * by the University of California, Berkeley.  The name of the
E 4
I 4
 * by Mark Nudleman and the University of California, Berkeley.  The
 * name of Mark Nudleman or the
E 4
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 9
I 9
 * %sccs.include.redist.c%
E 9
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
 * High level routines dealing with the output to the screen.
 */

D 5
#include "less.h"
E 5
I 5
#include <stdio.h>
#include <less.h>
E 5

D 5
public int errmsgs;	/* Count of messages displayed by error() */
E 5
I 5
int errmsgs;	/* Count of messages displayed by error() */
E 5

extern int sigs;
extern int sc_width, sc_height;
extern int ul_width, ue_width;
extern int so_width, se_width;
extern int bo_width, be_width;
extern int tabstop;
D 5
extern int twiddle;
E 5
extern int screen_trashed;
extern int any_display;
extern char *line;
D 5
extern char *first_cmd;
E 5

D 6
/*
 * Display the line which is in the line buffer.
 */
E 6
I 6
/* display the line which is in the line buffer. */
E 6
D 5
	public void
E 5
put_line()
{
	register char *p;
	register int c;
	register int column;
	extern int auto_wrap, ignaw;

	if (sigs)
	{
		/*
		 * Don't output if a signal is pending.
		 */
		screen_trashed = 1;
		return;
	}

	if (line == NULL)
D 5
		line = (twiddle) ? "~" : "";
E 5
I 5
		line = "";
E 5

	column = 0;
	for (p = line;  *p != '\0';  p++)
	{
		switch (c = *p)
		{
		case UL_CHAR:
			ul_enter();
D 10
			column += ul_width;
E 10
I 10
			column += ul_width +1;
E 10
			break;
		case UE_CHAR:
			ul_exit();
			column += ue_width;
			break;
		case BO_CHAR:
			bo_enter();
D 10
			column += bo_width;
E 10
I 10
			column += bo_width +1;
E 10
			break;
		case BE_CHAR:
			bo_exit();
			column += be_width;
			break;
		case '\t':
			do
			{
				putchr(' ');
				column++;
			} while ((column % tabstop) != 0);
			break;
		case '\b':
			putbs();
			column--;
			break;
		default:
			if (c & 0200)
			{
				/*
				 * Control characters arrive here as the
D 5
				 * normal character [carat_char(c)] with
E 5
I 5
				 * normal character [CARAT_CHAR(c)] with
E 5
				 * the 0200 bit set.  See pappend().
				 */
				putchr('^');
				putchr(c & 0177);
				column += 2;
			} else
			{
				putchr(c);
				column++;
			}
		}
	}
	if (column < sc_width || !auto_wrap || ignaw)
		putchr('\n');
}

D 5
/*
 * Is a given character a "control" character?
 * {{ ASCII DEPENDENT }}
 */
	public int
control_char(c)
	int c;
{
	return (c < ' ' || c == '\177');
}

/*
 * Return the printable character used to identify a control character
 * (printed after a carat; e.g. '\3' => "^C").
 * {{ ASCII DEPENDENT }}
 */
	public int
carat_char(c)
	int c;
{
	return ((c == '\177') ? '?' : (c | 0100));
}


E 5
static char obuf[1024];
static char *ob = obuf;

/*
 * Flush buffered output.
 */
D 5
	public void
E 5
flush()
{
	register int n;

	n = ob - obuf;
	if (n == 0)
		return;
	if (write(1, obuf, n) != n)
		screen_trashed = 1;
	ob = obuf;
}

/*
I 7
 * Purge any pending output.
 */
purge()
{

	ob = obuf;
}

/*
E 7
D 3
 * Discard buffered output.
 */
	public void
dropout()
{
	ob = obuf;
}

/*
E 3
 * Output a character.
 */
D 5
	public void
E 5
putchr(c)
	int c;
{
	if (ob >= &obuf[sizeof(obuf)])
		flush();
	*ob++ = c;
}

/*
 * Output a string.
 */
D 5
	public void
E 5
putstr(s)
	register char *s;
{
	while (*s != '\0')
		putchr(*s++);
}

I 6
int cmdstack;
D 8
static char return_to_continue[] = "  (press RETURN)";
E 8
I 8
static char return_to_continue[] = "(press RETURN)";
E 8

E 6
/*
 * Output a message in the lower left corner of the screen
 * and wait for carriage return.
 */
D 6

static char return_to_continue[] = "  (press RETURN)";

E 6
D 5
	public void
E 5
error(s)
	char *s;
{
I 6
	int ch;

E 6
D 5
	register int c;
	static char buf[2];

	errmsgs++;
	if (!any_display)
	{
E 5
I 5
	++errmsgs;
	if (!any_display) {
E 5
		/*
D 5
		 * Nothing has been displayed yet.
		 * Output this message on error output (file
		 * descriptor 2) and don't wait for a keystroke
		 * to continue.
E 5
I 5
		 * Nothing has been displayed yet.  Output this message on
		 * error output (file descriptor 2) and don't wait for a
		 * keystroke to continue.
E 5
		 *
D 5
		 * This has the desirable effect of producing all
		 * error messages on error output if standard output
		 * is directed to a file.  It also does the same if
		 * we never produce any real output; for example, if
		 * the input file(s) cannot be opened.  If we do
		 * eventually produce output, code in edit() makes
		 * sure these messages can be seen before they are
		 * overwritten or scrolled away.
E 5
I 5
		 * This has the desirable effect of producing all error
		 * messages on error output if standard output is directed
		 * to a file.  It also does the same if we never produce
		 * any real output; for example, if the input file(s) cannot
		 * be opened.  If we do eventually produce output, code in
		 * edit() makes sure these messages can be seen before they
		 * are overwritten or scrolled away.
E 5
		 */
D 5
		write(2, s, strlen(s));
		write(2, "\n", 1);
E 5
I 5
D 12
		(void)write(2, s, strlen(s));
		(void)write(2, "\n", 1);
E 12
I 12
		if (s != NULL) {
			(void)write(2, s, strlen(s));
			(void)write(2, "\n", 1);
		}
E 12
E 5
		return;
	}

	lower_left();
	clear_eol();
	so_enter();
D 8
	putstr(s);
E 8
I 8
D 12
	if (s) {
E 12
I 12
	if (s != NULL) {
E 12
		putstr(s);
		putstr("  ");
	}
E 8
	putstr(return_to_continue);
	so_exit();

D 2
#if ONLY_RETURN
	while ((c = getchr()) != '\n' && c != '\r')
		bell();
#else
E 2
D 5
	c = getchr();
	if (c != '\n' && c != '\r' && c != ' ' && c != READ_INTR)
	{
		buf[0] = c;
		first_cmd = buf;
	}
E 5
I 5
D 6
	(void)getchr();
E 6
I 6
D 8
	if ((ch = getchr()) != '\n')
E 8
I 8
	if ((ch = getchr()) != '\n') {
		if (ch == 'q')
			quit();
E 8
		cmdstack = ch;
I 8
	}
E 8
E 6
E 5
D 2
#endif
E 2
	lower_left();

D 12
	if (strlen(s) + sizeof(return_to_continue) + 
E 12
I 12
	if ((s != NULL ? strlen(s) : 0) + sizeof(return_to_continue) + 
E 12
		so_width + se_width + 1 > sc_width)
		/*
		 * Printing the message has probably scrolled the screen.
		 * {{ Unless the terminal doesn't have auto margins,
		 *    in which case we just hammered on the right margin. }}
		 */
		repaint();
D 5

E 5
	flush();
}

static char intr_to_abort[] = "... (interrupt to abort)";

D 5
	public void
E 5
ierror(s)
	char *s;
{
D 5

E 5
	lower_left();
	clear_eol();
	so_enter();
	putstr(s);
	putstr(intr_to_abort);
	so_exit();
	flush();
}
E 1
