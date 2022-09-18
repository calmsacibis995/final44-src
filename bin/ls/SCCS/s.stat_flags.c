h20690
s 00005/00000/00122
d D 8.2 94/07/28 03:38:21 pendry 4 3
c changes for whiteouts and union filesystem
e
s 00002/00002/00120
d D 8.1 93/05/31 14:46:02 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00023/00023/00099
d D 5.2 93/03/04 15:56:36 bostic 2 1
c rename file flags to UF_* and SF_*, minimize name space problems
e
s 00122/00000/00000
d D 5.1 93/03/03 20:37:50 bostic 1 0
c two new routines for file flags: flags_to_string and string_to_flags
c currently used by chflags(1) and install(1)
c date and time created 93/03/03 20:37:50 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1993 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
#include <sys/stat.h>

#include <stddef.h>
#include <string.h>

#define	SAPPEND(s) {							\
	if (prefix != NULL)						\
		(void)strcat(string, prefix);				\
	(void)strcat(string, s);					\
	prefix = ",";							\
}

/*
 * flags_to_string --
 *	Convert stat flags to a comma-separated string.  If no flags
 *	are set, return the default string.
 */
char *
flags_to_string(flags, def)
	u_long flags;
	char *def;
{
	static char string[128];
	char *prefix;

	string[0] = '\0';
	prefix = NULL;
D 2
	if (flags & ARCHIVED)
		SAPPEND("arch");
	if (flags & NODUMP)
		SAPPEND("nodump");
	if (flags & USR_IMMUTABLE)
		SAPPEND("uchg");
	if (flags & USR_APPEND)
E 2
I 2
	if (flags & UF_APPEND)
E 2
		SAPPEND("uappnd");
D 2
	if (flags & SYS_IMMUTABLE)
		SAPPEND("schg");
	if (flags & SYS_APPEND)
E 2
I 2
	if (flags & UF_IMMUTABLE)
		SAPPEND("uchg");
	if (flags & UF_NODUMP)
		SAPPEND("nodump");
I 4
	if (flags & UF_OPAQUE)
		SAPPEND("opaque");
E 4
	if (flags & SF_APPEND)
E 2
		SAPPEND("sappnd");
I 2
	if (flags & SF_ARCHIVED)
		SAPPEND("arch");
	if (flags & SF_IMMUTABLE)
		SAPPEND("schg");
E 2
	return (prefix == NULL && def != NULL ? def : string);
}

#define	TEST(a, b, f) {							\
	if (!memcmp(a, b, sizeof(b))) {					\
		if (clear) {						\
			if (clrp)					\
				*clrp |= (f);				\
		} else if (setp)					\
			*setp |= (f);					\
		break;							\
	}								\
}

/*
 * string_to_flags --
 *	Take string of arguments and return stat flags.  Return 0 on
 *	success, 1 on failure.  On failure, stringp is set to point
 *	to the offending token.
 */
int
string_to_flags(stringp, setp, clrp)
	char **stringp;
	u_long *setp, *clrp;
{
	int clear;
	char *string, *p;

	clear = 0;
	if (setp)
		*setp = 0;
	if (clrp)
		*clrp = 0;
	string = *stringp;
	while ((p = strsep(&string, "\t ,")) != NULL) {
		*stringp = p;
		if (*p == '\0')
			continue;
		if (p[0] == 'n' && p[1] == 'o') {
			clear = 1;
			p += 2;
		}
		switch (p[0]) {
		case 'a':
D 2
			TEST(p, "arch", ARCHIVED);
			TEST(p, "archived", ARCHIVED);
E 2
I 2
			TEST(p, "arch", SF_ARCHIVED);
			TEST(p, "archived", SF_ARCHIVED);
E 2
			return (1);
		case 'd':
			clear = !clear;
D 2
			TEST(p, "dump", NODUMP);
E 2
I 2
			TEST(p, "dump", UF_NODUMP);
I 4
			return (1);
		case 'o':
			TEST(p, "opaque", UF_OPAQUE);
E 4
E 2
			return (1);
		case 's':
D 2
			TEST(p, "sappnd", SYS_APPEND);
			TEST(p, "sappend", SYS_APPEND);
			TEST(p, "schg", SYS_IMMUTABLE);
			TEST(p, "schange", SYS_IMMUTABLE);
			TEST(p, "simmutable", SYS_IMMUTABLE);
E 2
I 2
			TEST(p, "sappnd", SF_APPEND);
			TEST(p, "sappend", SF_APPEND);
			TEST(p, "schg", SF_IMMUTABLE);
			TEST(p, "schange", SF_IMMUTABLE);
			TEST(p, "simmutable", SF_IMMUTABLE);
E 2
			return (1);
		case 'u':
D 2
			TEST(p, "uappnd", USR_APPEND);
			TEST(p, "uappend", USR_APPEND);
			TEST(p, "uchg", USR_IMMUTABLE);
			TEST(p, "uchange", USR_IMMUTABLE);
			TEST(p, "uimmutable", SYS_IMMUTABLE);
E 2
I 2
			TEST(p, "uappnd", UF_APPEND);
			TEST(p, "uappend", UF_APPEND);
			TEST(p, "uchg", UF_IMMUTABLE);
			TEST(p, "uchange", UF_IMMUTABLE);
			TEST(p, "uimmutable", UF_IMMUTABLE);
E 2
			/* FALLTHROUGH */
		default:
			return (1);
		}
	}
	return (0);
}
E 1
