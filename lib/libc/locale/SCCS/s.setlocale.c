h63460
s 00002/00002/00206
d D 8.1 93/07/04 09:03:30 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00207
d D 5.4 93/07/04 09:03:23 bostic 6 3
c sprintf -> snprintf (gcc lint)
e
s 00002/00002/00206
d R 8.1 93/06/27 19:22:38 bostic 5 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00206
d R 8.1 93/06/04 12:43:29 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00184/00008/00024
d D 5.3 93/05/26 20:27:49 bostic 3 2
c rune support from Paul Borman
e
s 00004/00006/00028
d D 5.2 91/02/24 10:41:20 bostic 2 1
c Add include files to get prototype declarations, and fix bugs found.
e
s 00034/00000/00000
d D 5.1 91/02/18 00:45:07 torek 1 0
c date and time created 91/02/18 00:45:07 by torek
e
u
U
t
T
I 1
/*
D 7
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
I 3
 * This code is derived from software contributed to Berkeley by
 * Paul Borman at Krystal Technologies.
 *
E 3
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

I 3
#include <limits.h>
E 3
#include <locale.h>
I 3
#include <rune.h>
#include <stdlib.h>
E 3
I 2
#include <string.h>
E 2

D 3
static char C[] = "C";
E 3
I 3
/*
 * Category names for getenv()
 */
static char *categories[_LC_LAST] = {
    "LC_ALL",
    "LC_COLLATE",
    "LC_CTYPE",
    "LC_MONETARY",
    "LC_NUMERIC",
    "LC_TIME",
};
E 3

/*
D 3
 * The setlocale function.
 *
 * Sorry, for now we only accept the C locale.
E 3
I 3
 * Current locales for each category
E 3
 */
I 3
static char current_categories[_LC_LAST][32] = {
    "C",
    "C",
    "C",
    "C",
    "C",
    "C",
};

/*
 * The locales we are going to try and load
 */
static char new_categories[_LC_LAST][32];

static char current_locale_string[_LC_LAST * 33];
static char *PathLocale;

static char	*currentlocale __P((void));
static char	*loadlocale __P((int));

E 3
char *
setlocale(category, locale)
	int category;
D 2
	char *locale;
E 2
I 2
	const char *locale;
E 2
{
D 2

	if ((unsigned)category >= _LC_LAST)
E 2
I 2
D 3
	if ((unsigned int)category >= _LC_LAST)
E 3
I 3
	int found, i, len;
	char *env, *r;

	if (!PathLocale && !(PathLocale = getenv("PATH_LOCALE")))
		PathLocale = _PATH_LOCALE;

	if (category < 0 || category >= _LC_LAST)
E 3
E 2
		return (NULL);
D 3
	if (locale == NULL)
		return (C);
D 2
	if (strcmp(locale, C) == 0)
		return (C);
	return (NULL);
E 2
I 2
	return(strcmp(locale, C) ? NULL : C);
E 3
I 3

	if (!locale)
		return (category ?
		    current_categories[category] : currentlocale());

	/*
	 * Default to the current locale for everything.
	 */
	for (i = 1; i < _LC_LAST; ++i)
		(void)strcpy(new_categories[i], current_categories[i]);

	/*
	 * Now go fill up new_categories from the locale argument
	 */
	if (!*locale) {
		env = getenv(categories[category]);

		if (!env)
			env = getenv(categories[0]);

		if (!env)
			env = getenv("LANG");

		if (!env)
			env = "C";

		(void) strncpy(new_categories[category], env, 31);
		new_categories[category][31] = 0;
		if (!category) {
			for (i = 1; i < _LC_LAST; ++i) {
				if (!(env = getenv(categories[i])))
					env = new_categories[0];
				(void)strncpy(new_categories[i], env, 31);
				new_categories[i][31] = 0;
			}
		}
	} else if (category)  {
		(void)strncpy(new_categories[category], locale, 31);
		new_categories[category][31] = 0;
	} else {
		if ((r = strchr(locale, '/')) == 0) {
			for (i = 1; i < _LC_LAST; ++i) {
				(void)strncpy(new_categories[i], locale, 31);
				new_categories[i][31] = 0;
			}
		} else {
			for (i = 1; r[1] == '/'; ++r);
			if (!r[1])
				return (NULL);	/* Hmm, just slashes... */
			do {
				len = r - locale > 31 ? 31 : r - locale;
				(void)strncpy(new_categories[i++], locale, len);
				new_categories[i++][len] = 0;
				locale = r;
				while (*locale == '/')
				    ++locale;
				while (*++r && *r != '/');
			} while (*locale);
			while (i < _LC_LAST)
				(void)strcpy(new_categories[i],
				    new_categories[i-1]);
		}
	}

	if (category)
		return (loadlocale(category));

	found = 0;
	for (i = 1; i < _LC_LAST; ++i)
		if (loadlocale(i) != NULL)
			found = 1;
	if (found)
	    return (currentlocale());
	return (NULL);
}

static char *
currentlocale()
{
	int i;

	(void)strcpy(current_locale_string, current_categories[1]);

	for (i = 2; i < _LC_LAST; ++i)
		if (strcmp(current_categories[1], current_categories[i])) {
			(void)snprintf(current_locale_string,
			    sizeof(current_locale_string), "%s/%s/%s/%s/%s",
			    current_categories[1], current_categories[2],
			    current_categories[3], current_categories[4],
			    current_categories[5]);
			break;
		}
	return (current_locale_string);
}

static char *
loadlocale(category)
	int category;
{
	char name[PATH_MAX];

	if (strcmp(new_categories[category],
	    current_categories[category]) == 0)
		return (current_categories[category]);

	if (category == LC_CTYPE) {
		if (setrunelocale(new_categories[LC_CTYPE]))
			return (NULL);
		(void)strcpy(current_categories[LC_CTYPE],
		    new_categories[LC_CTYPE]);
		return (current_categories[LC_CTYPE]);
	}

	if (!strcmp(new_categories[category], "C") ||
		!strcmp(new_categories[category], "POSIX")) {

		/*
		 * Some day this will need to reset the locale to the default
		 * C locale.  Since we have no way to change them as of yet,
		 * there is no need to reset them.
		 */
		(void)strcpy(current_categories[category],
		    new_categories[category]);
		return (current_categories[category]);
	}

	/*
	 * Some day we will actually look at this file.
	 */
D 6
	(void)sprintf(name, sizeof(name), "%s/%s/%s",
E 6
I 6
	(void)snprintf(name, sizeof(name), "%s/%s/%s",
E 6
	    PathLocale, new_categories[category], categories[category]);

	switch (category) {
		case LC_COLLATE:
		case LC_MONETARY:
		case LC_NUMERIC:
		case LC_TIME:
			return (NULL);
	}
E 3
E 2
}
E 1
