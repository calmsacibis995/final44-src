h18486
s 00002/00002/00177
d D 8.1 93/06/06 15:37:39 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00012/00178
d D 5.5 90/06/01 17:05:17 bostic 5 4
c new copyright notice
e
s 00008/00009/00182
d D 5.4 88/11/22 16:51:54 bostic 4 3
c less -> more
e
s 00002/00004/00189
d D 5.3 88/07/25 12:05:28 bostic 3 2
c update copyright notice
e
s 00000/00004/00193
d D 5.2 88/07/21 19:13:49 bostic 2 1
c rip out TAGS option, make default
e
s 00197/00000/00000
d D 5.1 88/07/21 18:53:27 bostic 1 0
c distribution by Mark Nudleman
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 Mark Nudleman
D 6
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
D 3
 * This code is derived from software contributed to Berkeley by
 * Mark Nudleman.
 * 
E 3
D 5
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
D 3
 * by the University of California, Berkeley.  The name of the
E 3
I 3
 * by Mark Nudleman and the University of California, Berkeley.  The
 * name of Mark Nudleman or the
E 3
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 5
I 5
 * %sccs.include.redist.c%
E 5
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

I 4
#include <sys/types.h>
E 4
#include <stdio.h>
D 4
#include "less.h"
E 4
I 4
#include <less.h>
E 4

#define	WHITESP(c)	((c)==' ' || (c)=='\t')

D 2
#if TAGS

E 2
D 4
public char *tagfile;
public char *tagpattern;
E 4
I 4
char *tagfile;
char *tagpattern;
E 4

static char *tags = "tags";

extern int linenums;
extern int sigs;
extern char *line;

/*
 * Find a tag in the "tags" file.
 * Sets "tagfile" to the name of the file containing the tag,
 * and "tagpattern" to the search pattern which should be used
 * to find the tag.
 */
D 4
	public int
E 4
findtag(tag)
	register char *tag;
{
	register char *p;
	register FILE *f;
	register int taglen;
	int search_char;
	static char tline[200];

	if ((f = fopen(tags, "r")) == NULL)
	{
		error("No tags file");
		tagfile = NULL;
		return;
	}

	taglen = strlen(tag);

	/*
	 * Search the tags file for the desired tag.
	 */
	while (fgets(tline, sizeof(tline), f) != NULL)
	{
		if (strncmp(tag, tline, taglen) != 0 || !WHITESP(tline[taglen]))
			continue;

		/*
		 * Found it.
		 * The line contains the tag, the filename and the
		 * pattern, separated by white space.
		 * The pattern is surrounded by a pair of identical
		 * search characters.
		 * Parse the line and extract these parts.
		 */
		tagfile = tagpattern = NULL;

		/*
		 * Skip over the whitespace after the tag name.
		 */
		for (p = tline;  !WHITESP(*p) && *p != '\0';  p++)
			continue;
		while (WHITESP(*p))
			p++;
		if (*p == '\0')
			/* File name is missing! */
			continue;

		/*
		 * Save the file name.
		 * Skip over the whitespace after the file name.
		 */
		tagfile = p;
		while (!WHITESP(*p) && *p != '\0')
			p++;
		*p++ = '\0';
		while (WHITESP(*p))
			p++;
		if (*p == '\0')
			/* Pattern is missing! */
			continue;

		/*
		 * Save the pattern.
		 * Skip to the end of the pattern.
		 * Delete the initial "^" and the final "$" from the pattern.
		 */
		search_char = *p++;
		if (*p == '^')
			p++;
		tagpattern = p;
		while (*p != search_char && *p != '\0')
			p++;
		if (p[-1] == '$')
			p--;
		*p = '\0';

D 4
		fclose(f);
E 4
I 4
		(void)fclose(f);
E 4
		return;
	}
D 4
	fclose(f);
E 4
I 4
	(void)fclose(f);
E 4
	error("No such tag in tags file");
	tagfile = NULL;
}

/*
 * Search for a tag.
 * This is a stripped-down version of search().
 * We don't use search() for several reasons:
 *   -	We don't want to blow away any search string we may have saved.
 *   -	The various regular-expression functions (from different systems:
 *	regcmp vs. re_comp) behave differently in the presence of 
 *	parentheses (which are almost always found in a tag).
 */
D 4
	public int
E 4
tagsearch()
{
D 4
	POSITION pos, linepos;
E 4
I 4
	off_t pos, linepos, forw_raw_line();
E 4
	int linenum;

D 4
	pos = (POSITION)0;
E 4
I 4
	pos = (off_t)0;
E 4
	linenum = find_linenum(pos);

	for (;;)
	{
		/*
		 * Get lines until we find a matching one or 
		 * until we hit end-of-file.
		 */
		if (sigs)
			return (1);

		/*
		 * Read the next line, and save the 
		 * starting position of that line in linepos.
		 */
		linepos = pos;
		pos = forw_raw_line(pos);
		if (linenum != 0)
			linenum++;

		if (pos == NULL_POSITION)
		{
			/*
			 * We hit EOF without a match.
			 */
			error("Tag not found");
			return (1);
		}

		/*
		 * If we're using line numbers, we might as well
		 * remember the information we have now (the position
		 * and line number of the current line).
		 */
		if (linenums)
			add_lnum(linenum, pos);

		/*
		 * Test the line to see if we have a match.
		 */
		if (strcmp(tagpattern, line) == 0)
			break;
	}

	jump_loc(linepos);
	return (0);
}
D 2

#endif
E 2
E 1
