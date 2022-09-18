h24787
s 00002/00002/00079
d D 8.1 93/06/06 22:33:12 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00081/00000/00000
d D 3.1 92/08/16 18:26:33 edward 1 0
c date and time created 92/08/16 18:26:33 by edward
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1982 Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1982, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * Edward Wang at The University of California, Berkeley.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#ifdef TERMINFO

#include "ww.h"
#include <stdio.h>
#include <paths.h>
#include "local.h"

/*
 * Terminfo support
 *
 * Written by Brian Buhrow
 *
 * Subsequently modified by Edward Wang
 */

/*
 * Initialize the working terminfo directory
 */
wwterminfoinit()
{
	FILE *fp;
	char buf[2048];

		/* make the directory */
	(void) sprintf(wwterminfopath, "%swwinXXXXXX", _PATH_TMP);
	mktemp(wwterminfopath);
	if (mkdir(wwterminfopath, 0755) < 0 ||
	    chmod(wwterminfopath, 00755) < 0) {
		wwerrno = WWE_SYS;
		return -1;
	}
	(void) setenv("TERMINFO", wwterminfopath, 1);
		/* make a termcap entry and turn it into terminfo */
	(void) sprintf(buf, "%s/cap", wwterminfopath);
	if ((fp = fopen(buf, "w")) == NULL) {
		wwerrno = WWE_SYS;
		return -1;
	}
	(void) fprintf(fp, "%sco#%d:li#%d:%s\n",
		WWT_TERMCAP, wwncol, wwnrow, wwwintermcap);
	(void) fclose(fp);
	(void) sprintf(buf,
		"cd %s; %s cap >info 2>/dev/null; %s info >/dev/null 2>&1",
		wwterminfopath, _PATH_CAPTOINFO, _PATH_TIC);
	(void) system(buf);
	return 0;
}

/*
 * Delete the working terminfo directory at shutdown
 */
wwterminfoend()
{

	switch (vfork()) {
	case -1:
		/* can't really do (or say) anything about errors */
		return -1;
	case 0:
		execl(_PATH_RM, _PATH_RM, "-rf", wwterminfopath, 0);
		return -1;
	default:
		return 0;
	}
}

#endif /* TERMINFO */
E 1
