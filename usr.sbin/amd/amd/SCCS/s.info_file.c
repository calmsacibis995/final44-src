h22115
s 00002/00002/00248
d D 8.1 93/06/06 11:40:01 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00249
d D 5.4 92/02/09 08:48:11 pendry 4 3
c merge in new release
e
s 00004/00002/00246
d D 5.3 91/05/12 15:55:40 pendry 3 2
c checkpoint for network tape
e
s 00049/00013/00199
d D 5.2 91/03/17 13:33:15 pendry 2 1
c from amd5.3 alpha11
e
s 00212/00000/00000
d D 5.1 90/06/29 12:01:04 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
/*
D 2
 * $Id: info_file.c,v 5.2 90/06/23 22:19:29 jsp Rel $
E 2
I 2
D 3
 * $Id: info_file.c,v 5.2.1.2 91/03/03 20:39:34 jsp Alpha $
E 2
 *
E 3
 * Copyright (c) 1990 Jan-Simon Pendry
 * Copyright (c) 1990 Imperial College of Science, Technology & Medicine
D 5
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * Jan-Simon Pendry at Imperial College, London.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
I 3
 *
D 4
 * $Id: info_file.c,v 5.2.1.4 91/05/07 22:17:57 jsp Alpha $
E 4
I 4
 * $Id: info_file.c,v 5.2.2.1 1992/02/09 15:08:28 jsp beta $
E 4
 *
E 3
 */

/*
 * Get info from file
 */

#include "am.h"

#ifdef HAS_FILE_MAPS
#include <ctype.h>
#include <sys/stat.h>

#define	MAX_LINE_LEN	2048

I 2
static int read_line P((char *buf, int size, FILE *fp));
E 2
static int read_line(buf, size, fp)
char *buf;
int size;
FILE *fp;
{
	int done = 0;

	do {
		while (fgets(buf, size, fp)) {
			int len = strlen(buf);
			done += len;
			if (len > 1 && buf[len-2] == '\\' &&
					buf[len-1] == '\n') {
				int ch;
				buf += len - 2;
				size -= len - 2;
I 3
				*buf = '\n'; buf[1] = '\0';
E 3
				/*
				 * Skip leading white space on next line
				 */
				while ((ch = getc(fp)) != EOF &&
					isascii(ch) && isspace(ch))
						;
				(void) ungetc(ch, fp);
			} else {
				return done;
			}
		}
	} while (size > 0 && !feof(fp));

	return done;
}

/*
 * Try to locate a key in a file
 */
I 2
static int search_or_reload_file P((FILE *fp, char *map, char *key, char **val, mnt_map *m, void (*fn)(mnt_map *m, char*, char*)));
E 2
static int search_or_reload_file(fp, map, key, val, m, fn)
FILE *fp;
char *map;
char *key;
char **val;
mnt_map *m;
void (*fn) P((mnt_map*, char*, char*));
{
	char key_val[MAX_LINE_LEN];
	int chuck = 0;
	int line_no = 0;

	while (read_line(key_val, sizeof(key_val), fp)) {
		char *kp;
		char *cp;
		char *hash;
		int len = strlen(key_val);
		line_no++;

		/*
		 * Make sure we got the whole line
		 */
		if (key_val[len-1] != '\n') {
			plog(XLOG_WARNING, "line %d in \"%s\" is too long", line_no, map);
			chuck = 1;
		} else {
			key_val[len-1] = '\0';
		}

		/*
		 * Strip comments
		 */
		hash = strchr(key_val, '#');
		if (hash)
			*hash = '\0';

		/*
		 * Find start of key
		 */
		for (kp = key_val; *kp && isascii(*kp) && isspace(*kp); kp++)
			;

		/*
		 * Ignore blank lines
		 */
		if (!*kp)
			goto again;

		/*
		 * Find end of key
		 */
		for (cp = kp; *cp&&(!isascii(*cp)||!isspace(*cp)); cp++)
			;

		/*
		 * Check whether key matches
		 */
		if (*cp)
			*cp++ = '\0';

D 2
		if ((*key == *kp && strcmp(key, kp) == 0) || fn) {
E 2
I 2
		if (fn || (*key == *kp && strcmp(key, kp) == 0)) {
E 2
			while (*cp && isascii(*cp) && isspace(*cp))
				cp++;
			if (*cp) {
				/*
				 * Return a copy of the data
				 */
				char *dc = strdup(cp);
D 2
				if (fn)
					(*fn)(m, kp, dc);
				else
E 2
I 2
				if (fn) {
					(*fn)(m, strdup(kp), dc);
				} else {
E 2
					*val = dc;
#ifdef DEBUG
D 2
				dlog("%s returns %s", key, dc);
E 2
I 2
					dlog("%s returns %s", key, dc);
E 2
#endif /* DEBUG */
I 2
				}
E 2
				if (!fn)
					return 0;
			} else {
				plog(XLOG_USER, "%s: line %d has no value field", map, line_no);
			}
		}

again:
		/*
		 * If the last read didn't get a whole line then
		 * throw away the remainder before continuing...
		 */
		if (chuck) {
			while (fgets(key_val, sizeof(key_val), fp) &&
				!strchr(key_val, '\n'))
					;
			chuck = 0;
		}
	}

	return fn ? 0 : ENOENT;
}

D 2
int file_init(map)
E 2
I 2
static FILE *file_open P((char *map, time_t *tp));
static FILE *file_open(map, tp)
E 2
char *map;
I 2
time_t *tp;
E 2
{
	FILE *mapf = fopen(map, "r");
I 2
	if (mapf && tp) {
		struct stat stb;
		if (fstat(fileno(mapf), &stb) < 0)
			*tp = clocktime();
		else
			*tp = stb.st_mtime;
	}
	return mapf;
}

int file_init P((char *map, time_t *tp));
int file_init(map, tp)
char *map;
time_t *tp;
{
	FILE *mapf = file_open(map, tp);
E 2
	if (mapf) {
		(void) fclose(mapf);
		return 0;
	}
	return errno;
}

I 2
int file_reload P((mnt_map *m, char *map, void (*fn)()));
E 2
int file_reload(m, map, fn)
mnt_map *m;
char *map;
void (*fn)();
{
D 2
	FILE *mapf = fopen(map, "r");
E 2
I 2
	FILE *mapf = file_open(map, (time_t *) 0);
E 2
	if (mapf) {
		int error = search_or_reload_file(mapf, map, 0, 0, m, fn);
		(void) fclose(mapf);
		return error;
	}

	return errno;
}

I 2
int file_search P((mnt_map *m, char *map, char *key, char **pval, time_t *tp));
E 2
int file_search(m, map, key, pval, tp)
mnt_map *m;
char *map;
char *key;
char **pval;
time_t *tp;
{
D 2
	FILE *mapf = fopen(map, "r");
E 2
I 2
	time_t t;
	FILE *mapf = file_open(map, &t);
E 2
	if (mapf) {
D 2
		struct stat stb;
E 2
		int error;
D 2
		error = fstat(fileno(mapf), &stb);
		if (!error && *tp < stb.st_mtime) {
			*tp = stb.st_mtime;
E 2
I 2
		if (*tp < t) {
			*tp = t;
E 2
			error = -1;
		} else {
			error = search_or_reload_file(mapf, map, key, pval, 0, 0);
		}
		(void) fclose(mapf);
		return error;
I 2
	}

	return errno;
}

int file_mtime P((char *map, time_t *tp));
int file_mtime(map, tp)
char *map;
time_t *tp;
{
	FILE *mapf = file_open(map, tp);
	if (mapf) {
		(void) fclose(mapf);
		return 0;
E 2
	}

	return errno;
}
#endif /* HAS_FILE_MAPS */
E 1
