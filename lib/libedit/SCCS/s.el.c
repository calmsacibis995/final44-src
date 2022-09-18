h27480
s 00001/00001/00308
d D 8.2 94/01/03 09:48:12 bostic 5 4
c rename fgetline -> fgetln, the semantics have changed
e
s 00002/00002/00307
d D 8.1 93/06/04 16:51:07 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00003/00305
d D 5.3 93/03/04 14:39:54 bostic 3 2
c rework fgetline(3) to be 8-bit clean; it no longer replace \n with \0
e
s 00051/00006/00257
d D 5.2 92/07/03 00:23:40 christos 2 1
c Up-to-date with cornell's last RCS version
e
s 00263/00000/00000
d D 5.1 92/06/22 18:08:13 bostic 1 0
c date and time created 92/06/22 18:08:13 by bostic
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
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
 * el.c: EditLine interface functions
 */
#include "sys.h"

I 2
#include <sys/types.h>
#include <sys/param.h>
#include <string.h>
E 2
#include <stdlib.h>
#if __STDC__
# include <stdarg.h>
#else
# include <varargs.h>
#endif
#include "el.h"

/* el_init():
 *	Initialize editline and set default parameters.
 */
public EditLine *
el_init(prog, fin, fout)
    const char *prog;
    FILE *fin, *fout;
{
    EditLine *el = (EditLine *) el_malloc(sizeof(EditLine));
#ifdef DEBUG
    char *tty;
#endif

    if (el == NULL)
	return NULL;

    memset(el, 0, sizeof(EditLine));

    el->el_infd  = fileno(fin);
    el->el_outfile = fout;
    el->el_prog = strdup(prog);

#ifdef DEBUG
    if ((tty = getenv("DEBUGTTY")) != NULL) {
	el->el_errfile = fopen(tty, "w");
	if (el->el_errfile == NULL) {
		extern errno;
		(void) fprintf(stderr, "Cannot open %s (%s).\n",
			       tty, strerror(errno));
		return NULL;
	}
    }
    else 
#endif
	el->el_errfile = stderr;

    /*
     * Initialize all the modules. Order is important!!!
     */
    (void) term_init(el);
    (void) tty_init(el);
    (void) key_init(el);
    (void) map_init(el);
    (void) ch_init(el);
    (void) search_init(el);
    (void) hist_init(el);
    (void) prompt_init(el);
    (void) sig_init(el);
    el->el_flags = 0;

    return el;
} /* end el_init */


/* el_end():
 *	Clean up.
 */
public void
el_end(el)
    EditLine *el;
{
    if (el == NULL)
	return;

    el_reset(el);

    term_end(el);
    tty_end(el);
    key_end(el);
    map_end(el);
    ch_end(el);
    search_end(el);
    hist_end(el);
    prompt_end(el);
    sig_end(el);

    el_free((ptr_t) el->el_prog);
    el_free((ptr_t) el);
} /* end el_end */ 


/* el_reset():
 *	Reset the tty and the parser
 */
public void
el_reset(el)
    EditLine *el;
{
    tty_cookedmode(el);
    ch_reset(el);	/* XXX: Do we want that? */
}


/* el_set():
 *	set the editline parameters
 */
public int
#if __STDC__
el_set(EditLine *el, int op, ...)
#else
el_set(va_alist)
    va_dcl
#endif
{
    va_list va;
    int rv;
#if __STDC__
    va_start(va, op);
#else
    EditLine *el;
    int op;

    va_start(va);
    el = va_arg(va, EditLine *);
    op = va_arg(va, int);
#endif
    
    switch (op) {
    case EL_PROMPT:
	rv = prompt_set(el, va_arg(va, el_pfunc_t));
	break;

I 2
    case EL_TERMINAL:
	rv = term_set(el, va_arg(va, char *));
	break;

E 2
    case EL_EDITOR:
	rv = map_set_editor(el, va_arg(va, char *));
	break;

    case EL_SIGNAL:
	if (va_arg(va, int))
	    el->el_flags |= HANDLE_SIGNALS;
	else
	    el->el_flags &= ~HANDLE_SIGNALS;
	rv = 0;
	break;

    case EL_BIND:
    case EL_TELLTC:
    case EL_SETTC:
    case EL_ECHOTC:
    case EL_SETTY:
	{
	    char *argv[20];
	    int i;
	    for (i = 1; i < 20; i++)
		if ((argv[i] = va_arg(va, char *)) == NULL)
		     break;

	    switch (op) {
	    case EL_BIND:
		argv[0] = "bind";
		rv = map_bind(el, i, argv);
		break;

	    case EL_TELLTC:
		argv[0] = "telltc";
D 2
		rv = term_telltc(el, i, va_arg(va, char **));
E 2
I 2
		rv = term_telltc(el, i, argv);
E 2
		break;

	    case EL_SETTC:
		argv[0] = "settc";
D 2
		rv = term_settc(el, i, va_arg(va, char **));
E 2
I 2
		rv = term_settc(el, i, argv);
E 2
		break;

	    case EL_ECHOTC:
		argv[0] = "echotc";
D 2
		rv = term_echotc(el, i, va_arg(va, char **));
E 2
I 2
		rv = term_echotc(el, i, argv);
E 2
		break;

	    case EL_SETTY:
		argv[0] = "setty";
D 2
		rv = tty_stty(el, i, va_arg(va, char **));
E 2
I 2
		rv = tty_stty(el, i, argv);
E 2
		break;

	    default:
		rv = -1;
		abort();
		break;
	    }
	}
	break;
    
    case EL_ADDFN:
	{
	    char 	*name = va_arg(va, char *);
	    char 	*help = va_arg(va, char *);
	    el_func_t    func = va_arg(va, el_func_t);
	    rv = map_addfunc(el, name, help, func);
	}
	break;

    case EL_HIST:
	{
	    hist_fun_t func = va_arg(va, hist_fun_t);
	    ptr_t      ptr = va_arg(va, char *);
	    rv = hist_set(el, func, ptr);
	}
	break;

    default:
	rv = -1;
    }

    va_end(va);
    return rv;
} /* end el_set */


/* el_line():
 *	Return editing info
 */
public const LineInfo *
el_line(el)
    EditLine *el;
{
    return (const LineInfo *) &el->el_line;
I 2
}

static const char elpath[] = "/.editrc";

/* el_source():
 *	Source a file
 */
public int
el_source(el, fname)
    EditLine *el;
    const char *fname;
{
D 3
    char path[MAXPATHLEN];
E 3
    FILE *fp;
D 3
    char *ptr;
E 3
I 3
    size_t len;
    char *ptr, path[MAXPATHLEN];
E 3

    if (fname == NULL) {
	fname = &elpath[1];
	if ((fp = fopen(fname, "r")) == NULL) {
	    if ((ptr = getenv("HOME")) == NULL) 
		return -1;
	    fname = strncpy(path, ptr, MAXPATHLEN);
	    (void) strncat(path, elpath, MAXPATHLEN);
	    path[MAXPATHLEN-1] = '\0';
	}
    }

    if ((fp = fopen(fname, "r")) == NULL) 
	return -1;

D 3
    while ((ptr = fgetline(fp, NULL)) != NULL)
E 3
I 3
D 5
    while ((ptr = fgetline(fp, &len)) != NULL)
E 5
I 5
    while ((ptr = fgetln(fp, &len)) != NULL)
E 5
	ptr[len - 1] = '\0';
E 3
	if (parse_line(el, ptr) == -1) {
	    (void) fclose(fp);
	    return -1;
	}

    (void) fclose(fp);
    return 0;
E 2
}


/* el_resize():
 *	Called from program when terminal is resized
 */
public void
el_resize(el)
    EditLine *el;
{
    int lins, cols;
    sigset_t oset, nset;
    (void) sigemptyset(&nset);
    (void) sigaddset(&nset, SIGWINCH);
    (void) sigprocmask(SIG_BLOCK, &nset, &oset);

    /* get the correct window size */
    if (term_get_size(el, &lins, &cols))
	term_change_size(el, lins, cols);

    (void) sigprocmask(SIG_SETMASK, &oset, NULL);
}
E 1
