h05343
s 00008/00008/00111
d D 8.3 95/05/30 20:13:27 dab 4 3
c Code cleanup, use mem*() instead of b*()
e
s 00003/00000/00116
d D 8.2 93/12/15 11:31:53 dab 3 2
c The lastest Kerberos V code from MIT
e
s 00002/00002/00114
d D 8.1 93/06/04 17:37:15 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00116/00000/00000
d D 5.1 93/01/20 12:52:10 dab 1 0
c date and time created 93/01/20 12:52:10 by dab
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
 * $Source: /mit/kerberos/src/lib/des/RCS/read_password.c,v $
 * $Author: jon $
 *
 * Copyright 1985, 1986, 1987, 1988 by the Massachusetts Institute
 * of Technology.
 *
 * For copying and distribution information, please see the file
 * <mit-copyright.h>.
 *
 * This routine prints the supplied string to standard
 * output as a prompt, and reads a password string without
 * echoing.
 */

I 3
#if	defined(RSA_ENCPWD) || defined(KRB4_ENCPWD)

E 3
#include <stdio.h>
#include <strings.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <setjmp.h>

static jmp_buf env;

/*** Routines ****************************************************** */
/*
 * This version just returns the string, doesn't map to key.
 *
 * Returns 0 on success, non-zero on failure.
 */

int
local_des_read_pw_string(s,max,prompt,verify)
    char *s;
    int	max;
    char *prompt;
    int	verify;
{
    int ok = 0;
    char *ptr;
D 4
    
E 4
I 4

E 4
    jmp_buf old_env;
    struct sgttyb tty_state;
    char key_string[BUFSIZ];

    if (max > BUFSIZ) {
	return -1;
    }

    /* XXX assume jmp_buf is typedef'ed to an array */
D 4
    bcopy((char *)old_env, (char *)env, sizeof(env));
E 4
I 4
    memmove((char *)env, (char *)old_env, sizeof(env));
E 4
    if (setjmp(env))
	goto lose;

    /* save terminal state*/
D 4
    if (ioctl(0,TIOCGETP,(char *)&tty_state) == -1) 
E 4
I 4
    if (ioctl(0,TIOCGETP,(char *)&tty_state) == -1)
E 4
	return -1;
/*
    push_signals();
*/
    /* Turn off echo */
    tty_state.sg_flags &= ~ECHO;
    if (ioctl(0,TIOCSETP,(char *)&tty_state) == -1)
	return -1;
    while (!ok) {
	(void) printf(prompt);
	(void) fflush(stdout);
	while (!fgets(s, max, stdin));

D 4
	if ((ptr = index(s, '\n')))
E 4
I 4
	if ((ptr = strchr(s, '\n')))
E 4
	    *ptr = '\0';
	if (verify) {
	    printf("\nVerifying, please re-enter %s",prompt);
	    (void) fflush(stdout);
	    if (!fgets(key_string, sizeof(key_string), stdin)) {
		clearerr(stdin);
		continue;
	    }
D 4
            if ((ptr = index(key_string, '\n')))
E 4
I 4
	    if ((ptr = strchr(key_string, '\n')))
E 4
	    *ptr = '\0';
	    if (strcmp(s,key_string)) {
		printf("\n\07\07Mismatch - try again\n");
		(void) fflush(stdout);
		continue;
	    }
	}
	ok = 1;
    }

lose:
    if (!ok)
D 4
	bzero(s, max);
E 4
I 4
	memset(s, 0, max);
E 4
    printf("\n");
    /* turn echo back on */
    tty_state.sg_flags |= ECHO;
    if (ioctl(0,TIOCSETP,(char *)&tty_state))
	ok = 0;
/*
    pop_signals();
*/
D 4
    bcopy((char *)env, (char *)old_env, sizeof(env));
E 4
I 4
    memmove((char *)old_env, (char *)env, sizeof(env));
E 4
    if (verify)
D 4
	bzero(key_string, sizeof (key_string));
E 4
I 4
	memset(key_string, 0, sizeof (key_string));
E 4
    s[max-1] = 0;		/* force termination */
    return !ok;			/* return nonzero if not okay */
}
I 3
#endif	/* defined(RSA_ENCPWD) || defined(KRB4_ENCPWD) */
E 3
E 1
