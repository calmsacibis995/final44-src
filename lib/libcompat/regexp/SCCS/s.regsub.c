h61747
s 00000/00000/00081
d R 8.2 93/06/04 16:31:53 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00000/00081
d D 8.1 93/06/04 16:31:34 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00005/00004/00076
d D 5.2 91/02/24 14:14:51 bostic 2 1
c Add include files to get prototype declarations, and fix bugs found.
e
s 00080/00000/00000
d D 5.1 90/05/03 17:47:46 bostic 1 0
c date and time created 90/05/03 17:47:46 by bostic
e
u
U
t
T
I 1
/*
 * regsub
 *
 *	Copyright (c) 1986 by University of Toronto.
 *	Written by Henry Spencer.  Not derived from licensed software.
 *
 *	Permission is granted to anyone to use this software for any
 *	purpose on any computer system, and to redistribute it freely,
 *	subject to the following restrictions:
 *
 *	1. The author is not responsible for the consequences of use of
 *		this software, no matter how awful, even if they arise
 *		from defects in it.
 *
 *	2. The origin of this software must not be misrepresented, either
 *		by explicit claim or by omission.
 *
 *	3. Altered versions must be plainly marked as such, and must not
 *		be misrepresented as being the original software.
 */
D 2
#include <stdio.h>
E 2
#include <regexp.h>
I 2
#include <stdio.h>
#include <string.h>
E 2
#include "regmagic.h"

#ifndef CHARBITS
#define	UCHARAT(p)	((int)*(unsigned char *)(p))
#else
#define	UCHARAT(p)	((int)*(p)&CHARBITS)
#endif

/*
 - regsub - perform substitutions after a regexp match
 */
void
regsub(prog, source, dest)
D 2
regexp *prog;
char *source;
E 2
I 2
const regexp *prog;
const char *source;
E 2
char *dest;
{
	register char *src;
	register char *dst;
	register char c;
	register int no;
	register int len;
	extern char *strncpy();

	if (prog == NULL || source == NULL || dest == NULL) {
		regerror("NULL parm to regsub");
		return;
	}
	if (UCHARAT(prog->program) != MAGIC) {
		regerror("damaged regexp fed to regsub");
		return;
	}

D 2
	src = source;
E 2
I 2
	src = (char *)source;
E 2
	dst = dest;
	while ((c = *src++) != '\0') {
		if (c == '&')
			no = 0;
		else if (c == '\\' && '0' <= *src && *src <= '9')
			no = *src++ - '0';
		else
			no = -1;
 		if (no < 0) {	/* Ordinary character. */
 			if (c == '\\' && (*src == '\\' || *src == '&'))
 				c = *src++;
 			*dst++ = c;
 		} else if (prog->startp[no] != NULL && prog->endp[no] != NULL) {
			len = prog->endp[no] - prog->startp[no];
			(void) strncpy(dst, prog->startp[no], len);
			dst += len;
			if (len != 0 && *(dst-1) == '\0') {	/* strncpy hit NUL. */
				regerror("damaged match string");
				return;
			}
		}
	}
	*dst++ = '\0';
}
E 1
