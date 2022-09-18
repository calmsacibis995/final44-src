h47401
s 00002/00002/00219
d D 8.1 93/06/04 16:51:45 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00005/00216
d D 5.2 92/07/03 00:23:50 christos 2 1
c Up-to-date with cornell's last RCS version
e
s 00221/00000/00000
d D 5.1 92/06/22 18:08:27 bostic 1 0
c date and time created 92/06/22 18:08:27 by bostic
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
 * el.parse.c: parse an editline extended command
E 2
I 2
 * parse.c: parse an editline extended command
E 2
 *
 * commands are:
 *
 *	bind
 *	echotc
 *	settc
 *	gettc
 */
#include "sys.h"
#include "el.h"
#include "tokenizer.h"

private struct {
    char *name;
    int (*func) __P((EditLine *, int, char **));
} cmds[] = {
    {	"bind",		map_bind 	},
    {	"echotc",	term_echotc 	},
    {	"history",	hist_list	},
    {	"telltc",	term_telltc 	},
    {	"settc",	term_settc	},
    {	"setty",	tty_stty	},
    {	NULL,		NULL		}
};


/* parse_line():
 *	Parse a line and dispatch it
 */
protected int
parse_line(el, line)
    EditLine *el;
    const char *line;
{
    char **argv;
    int argc;
    Tokenizer *tok;

    tok = tok_init(NULL);
    tok_line(tok, line, &argc, &argv);
    argc = el_parse(el, argc, argv);
    tok_end(tok);
    return argc;
}

/* el_parse():
 *	Command dispatcher
 */
public int
el_parse(el, argc, argv)
    EditLine *el;
    int argc;
    char *argv[];
{
    char *ptr;
    int i;

    for (ptr = argv[0]; *ptr && *ptr != ':'; ptr++)
	continue;

    if (*ptr == ':') {
	*ptr = '\0';
D 2
	if (strcmp(ptr, el->el_prog) != 0)
E 2
I 2
	if (el_match(el->el_prog, ptr))
E 2
	    return 0;
    }
    else
	ptr = argv[0];

    for (i = 0; cmds[i].name != NULL; i++)
	if (strcmp(cmds[i].name, ptr) == 0) {
	    i = (*cmds[i].func)(el, argc, argv);
	    return -i;
	}

    return -1;
}


/* parse__escape():
 *	Parse a string of the form ^<char> \<odigit> \<char> and return
 *	the appropriate character or -1 if the escape is not valid
 */
protected int
parse__escape(ptr)
    const char  ** const ptr;
{
    const char   *p;
    int   c;

    p = *ptr;

    if (p[1] == 0) 
	return -1;

    if (*p == '\\') {
	p++;
	switch (*p) {
	case 'a':
	    c = '\007';		/* Bell */
	    break;
	case 'b':
	    c = '\010';		/* Backspace */
	    break;
	case 't':
	    c = '\011';		/* Horizontal Tab */
	    break;
	case 'n':
	    c = '\012';		/* New Line */
	    break;
	case 'v':
	    c = '\013';		/* Vertical Tab */
	    break;
	case 'f':
	    c = '\014';		/* Form Feed */
	    break;
	case 'r':
	    c = '\015';		/* Carriage Return */
	    break;
	case 'e':
	    c = '\033';		/* Escape */
	    break;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	    {
		int cnt, ch;

		for (cnt = 0, c = 0; cnt < 3; cnt++) {
		    ch = *p++;
		    if (ch < '0' || ch > '7') {
			p--;
			break;
		    }
		    c = (c << 3) | (ch - '0');
		}
		if ((c & 0xffffff00) != 0) 
		    return -1;
		--p;
	    }
	    break;
	default:
	    c = *p;
	    break;
	}
    }
D 2
    else if (*p == '^') {
E 2
I 2
    else if (*p == '^' && isalpha((unsigned char) *p)) {
E 2
	p++;
	c = (*p == '?') ? '\177' : (*p & 0237);
    }
    else
	c = *p;
    *ptr = ++p;
    return c;
}

/* parse__string():
 *	Parse the escapes from in and put the raw string out
 */
protected char *
parse__string(out, in)
    char *out;
    const char *in;
{
    char *rv = out;
    int n;
    for (;;)
	switch (*in) {
	case '\0':
	    *out = '\0';
	    return rv;

	case '\\':
	case '^':
	    if ((n = parse__escape(&in)) == -1)
		return NULL;
	    *out++ = n;
	    break;

	default:
	    *out++ = *in++;
	    break;
	}
}

/* parse_cmd():
 *	Return the command number for the command string given
 *	or -1 if one is not found
 */
protected int
parse_cmd(el, cmd)
    EditLine *el;
    const char *cmd;
{
    el_bindings_t *b;

    for (b = el->el_map.help; b->name != NULL; b++)
	if (strcmp(b->name, cmd) == 0)
	    return b->func;
    return -1;
}
E 1
