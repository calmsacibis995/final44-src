#ifndef lint
#ifndef NOID
static char	elsieid[] = "@(#)link.c	4.2";
#endif /* !defined NOID */
#endif /* !defined lint */

/*LINTLIBRARY*/

#ifndef HAVELINK
#ifndef WANTLINK
#ifndef unix
#define WANTLINK
#endif /* !defined unix */
#endif /* !defined WANTLINK */
#endif /* !defined HAVELINK */

#ifdef WANTLINK

/*
** Fake link by copying.
*/

#include "stdio.h"
#include "nonstd.h"

link(fromname, toname)
const char * const	fromname;
const char * const	toname;
{
	register FILE *	fromfp;
	register FILE *	tofp;
	register int	c;
	register int	ok;

	if ((fromfp = fopen(fromname, "rb")) == NULL)
		return -1;
	if ((tofp = fopen(toname, "wb")) == NULL) {
		(void) fclose(fromfp);
		return -1;
	}
	while ((c = getc(fromfp)) != EOF) {
		if (ferror(fromfp))
			break;
		(void) putc(c, tofp);
		if (ferror(tofp))
			break;
	}
	ok = !ferror(fromfp) && feof(fromfp) && !ferror(tofp);
	ok = fclose(fromfp) == 0 && ok;
	ok = fclose(tofp) == 0 && ok;
	return ok ? 0 : -1;
}

#endif /* defined WANTLINK */

/*
** UNIX is a registered trademark of AT&T.
*/
