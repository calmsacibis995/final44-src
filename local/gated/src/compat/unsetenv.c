/*
 *
 *	$Id: unsetenv.c,v 1.10 1993/07/20 11:18:04 jch Exp $
 *
 * Copyright (c) 1987 Regents of the University of California.
 * This file may be freely redistributed provided that this
 * notice remains attached.
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "@(#)setenv.c	1.3 (Berkeley) 6/16/87";
#endif /* LIBC_SCCS and not lint */

#include "include.h"

#if	__GNUC__ >= 2
PROTOTYPE(unsetenv,
	  void,
	  (char *));
#endif	/* __GNUC__ >= 2*/

/*
 * _findenv --
 *      Returns pointer to value associated with name, if any, else NULL.
 *      Sets offset to be the offset of the name/value combination in the
 *      environmental array, for use by setenv(3) and unsetenv(3).
 *      Explicitly removes '=' in argument name.
 *
 *      This routine *should* be a static; don't use it.
 */

static char *
_findenv __PF2(name, register char *,
	       offset, int *)
{
        extern char **ENVIRON;
        register size_t len;
        register char **P, *C;

        for (C = name, len = 0; *C && *C != '='; ++C, ++len);
        for (P = ENVIRON; *P; ++P)
                if (!strncmp(*P, name, len))
                        if (*(C = *P + len) == '=') {
                                *offset = P - ENVIRON;
                                return(++C);
                        }
        return(NULL);
}


/*
 * unsetenv(name) --
 *	Delete environmental variable "name".
 */
void
unsetenv(name)
	char	*name;
{
	extern	char	**ENVIRON;
	register char	**P;
	int	offset;

	while (_findenv(name,&offset))		/* if set multiple times */
		for (P = &ENVIRON[offset];;++P)
			if (!(*P = *(P + 1)))
				break;
}
