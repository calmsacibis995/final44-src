h33440
s 00005/00005/00182
d D 8.1 93/06/04 16:52:47 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00003/00178
d D 5.3 92/07/03 00:24:03 christos 3 2
c Up-to-date with cornell's last RCS version
e
s 00001/00002/00180
d D 5.2 92/06/22 18:25:17 marc 2 1
c merge editline.h and history.h
e
s 00182/00000/00000
d D 5.1 92/06/22 18:08:42 bostic 1 0
c date and time created 92/06/22 18:08:42 by bostic
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

#ifndef lint
D 4
char copyright[] =
"%Z% Copyright (c) 1992 The Regents of the University of California.\n\
 All rights reserved.\n";
E 4
I 4
static char copyright[] =
"%Z% Copyright (c) 1992, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 4
#endif /* not lint */

D 3
#ifndef lint
E 3
I 3
#if !defined(lint) && !defined(SCCSID)
E 3
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif /* not lint */
E 3
I 3
#endif /* not lint && not SCCSID */
E 3

/*
D 3
 * el.test.c: A little test program
E 3
I 3
 * test.c: A little test program
E 3
 */
#include "sys.h"
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>

D 2
#include "editline.h"
E 2
I 2
#include "histedit.h"
E 2
#include "tokenizer.h"
D 2
#include "history.h"
E 2

static int continuation = 0;
static EditLine *el = NULL;

static char *
/*ARGSUSED*/
prompt(el)
    EditLine *el;
{
    static char a[] = "Edit$";
    static char b[] = "Edit>";
    return continuation ? b : a;
}

static void
sig(i)
    int i;
{
    (void) fprintf(stderr, "Got signal %d.\n", i);
    el_reset(el);
}

static unsigned char
/*ARGSUSED*/
complete(el, ch)
    EditLine *el;
    int ch;
{
    DIR *dd = opendir("."); 
    struct dirent *dp;
    const char* ptr;
    const LineInfo *lf = el_line(el);
    int len;

    /*
     * Find the last word
     */
    for (ptr = lf->cursor - 1; !isspace(*ptr) && ptr > lf->buffer; ptr--)
	continue;
    len = lf->cursor - ++ptr;

    for (dp = readdir(dd); dp != NULL; dp = readdir(dd)) {
	if (len > strlen(dp->d_name))
	    continue;
	if (strncmp(dp->d_name, ptr, len) == 0) {
	    closedir(dd);
	    if (el_insertstr(el, &dp->d_name[len]) == -1)
		return CC_ERROR;
	    else
		return CC_REFRESH;
	}
    }

    closedir(dd);
    return CC_ERROR;
}

int
/*ARGSUSED*/
main(argc, argv)
    int argc;
    char *argv[];
{
    int num;
    const char *buf;
    Tokenizer *tok;
    History *hist;

    (void) signal(SIGINT, sig);
    (void) signal(SIGQUIT, sig);
    (void) signal(SIGHUP, sig);
    (void) signal(SIGTERM, sig);

    hist = history_init();		/* Init the builtin history	*/
    history(hist, H_EVENT, 100);	/* Remember 100 events		*/

    tok  = tok_init(NULL);		/* Initialize the tokenizer	*/

    el = el_init(*argv, stdin, stdout);	/* Initialize editline		*/

    el_set(el, EL_EDITOR, "vi");	/* Default editor is vi 	*/
    el_set(el, EL_SIGNAL, 1);		/* Handle signals gracefully	*/
    el_set(el, EL_PROMPT, prompt);	/* Set the prompt function	*/

    /* Tell editline to use this history interface			*/
    el_set(el, EL_HIST, history, hist);

    /* Add a user-defined function 					*/
    el_set(el, EL_ADDFN, "ed-complete", "Complete argument", complete);

    el_set(el, EL_BIND, "^I", "ed-complete", NULL);/* Bind tab to it 	*/
I 3

E 3
    /*
     * Bind j, k in vi command mode to previous and next line, instead
     * of previous and next history.
     */
    el_set(el, EL_BIND, "-a", "k", "ed-prev-line", NULL);
    el_set(el, EL_BIND, "-a", "j", "ed-next-line", NULL);
I 3

    /*
     * Source the user's defaults file.
     */
    el_source(el, NULL);
E 3

    while ((buf = el_gets(el, &num)) != NULL && num != 0)  {
	int ac;
	char **av;
#ifdef DEBUG
	(void) fprintf(stderr, "got %d %s", num, buf);
#endif
	if (!continuation && num == 1)
	    continue;
	if (tok_line(tok, buf, &ac, &av) > 0) {
	    history(hist, continuation ? H_ADD : H_ENTER, buf);
	    continuation = 1;
	    continue;
	}
	history(hist, continuation ? H_ADD : H_ENTER, buf);

	continuation = 0;
	if (el_parse(el, ac, av) != -1) {
	    tok_reset(tok);
	    continue;
	}

	switch (fork()) {
	case 0:
	    execvp(av[0], av);
	    perror(av[0]);
	    _exit(1);
	    /*NOTREACHED*/
	    break;

	case -1:
	    perror("fork");
	    break;

	default:
	    if (wait(&num) == -1)
		perror("wait");
	    (void) fprintf(stderr, "Exit %x\n", num);
	    break;
	}
	tok_reset(tok);
    }

    el_end(el);
    tok_end(tok);
    history_end(hist);

    return 0;
}
E 1
