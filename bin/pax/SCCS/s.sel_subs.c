h45928
s 00002/00002/00629
d D 8.1 93/05/31 14:53:23 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00010/00629
d D 1.3 93/01/16 14:41:46 muller 3 2
c was testing artyp before it was set. test was not needed.
e
s 00102/00029/00537
d D 1.2 93/01/12 02:59:22 muller 2 1
c updated -T time ranges for both inode change and mod time checks.
e
s 00566/00000/00000
d D 1.1 92/12/17 19:22:21 muller 1 0
c date and time created 92/12/17 19:22:21 by muller
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1992 Keith Muller.
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
 * Keith Muller of the University of California, San Diego.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include "pax.h"
#include "sel_subs.h"
#include "extern.h"

static int str_sec __P((register char *, time_t *));
static int usr_match __P((register ARCHD *));
static int grp_match __P((register ARCHD *));
static int trng_match __P((register ARCHD *));

static TIME_RNG *trhead = NULL;		/* time range list head */
static TIME_RNG *trtail = NULL;		/* time range list tail */
static USRT **usrtb = NULL;		/* user selection table */
static GRPT **grptb = NULL;		/* group selection table */

/*
 * Routines for selection of archive members
 */

/*
 * sel_chk()
D 2
 *	check if this files matches a specfied uid, gid and time range
E 2
I 2
 *	check if this file matches a specfied uid, gid or time range
E 2
 * Return:
 *	0 if this archive member should be processed, 1 if it should be skipped
 */

#if __STDC__
int
sel_chk(register ARCHD *arcn)
#else
int
sel_chk(arcn)
	register ARCHD *arcn;
#endif
{
	if (((usrtb != NULL) && usr_match(arcn)) ||
	    ((grptb != NULL) && grp_match(arcn)) ||
	    ((trhead != NULL) && trng_match(arcn)))
		return(1);
	return(0);
}

/*
 * User/group selection routines
 *
D 2
 * Routine that handle user selection of files based on the file uid/gid. To
 * add an entry the user supplies either then name or the uid/gid starting with
 * a #. A \# will eascape the #.
E 2
I 2
 * Routines to handle user selection of files based on the file uid/gid. To
 * add an entry, the user supplies either then name or the uid/gid starting with
 * a # on the command line. A \# will eascape the #.
E 2
 */

/*
 * usr_add()
 *	add a user match to the user match hash table
 * Return:
 *	0 if added ok, -1 otherwise;
 */

#if __STDC__
int
usr_add(register char *str)
#else
int
usr_add(str)
	register char *str;
#endif
{
	register u_int indx;
	register USRT *pt;
	register struct passwd *pw;
	register uid_t uid;

	/*
	 * create the table if it doesn't exist
	 */
	if ((str == NULL) || (*str == '\0'))
		return(-1);
	if ((usrtb == NULL) &&
 	    ((usrtb = (USRT **)calloc(USR_TB_SZ, sizeof(USRT *))) == NULL)) {
                warn(1, "Unable to allocate memory for user selection table");
                return(-1);
	}

	/*
	 * figure out user spec
	 */
	if (str[0] != '#') {
		/*
		 * it is a user name, \# escapes # as first char in user name
		 */
		if ((str[0] == '\\') && (str[1] == '#'))
			++str;
		if ((pw = getpwnam(str)) == NULL) {
                	warn(1, "Unable to find uid for user: %s", str);
                	return(-1);
		}
		uid = (uid_t)pw->pw_uid;
        } else
#		ifdef NET2_STAT
		uid = (uid_t)atoi(str+1);
#		else
		uid = (uid_t)strtoul(str+1, (char **)NULL, 10);
#		endif
	endpwent();

	/*
	 * hash it and go down the hash chain (if any) looking for it
	 */
	indx = ((unsigned)uid) % USR_TB_SZ;
	if ((pt = usrtb[indx]) != NULL) {
                while (pt != NULL) {
                        if (pt->uid == uid)
				return(0);
                        pt = pt->fow;
                }
	}

	/*
D 2
	 * uid not already in the table, add it to the front of the chain
E 2
I 2
	 * uid is not yet in the table, add it to the front of the chain
E 2
	 */
	if ((pt = (USRT *)malloc(sizeof(USRT))) != NULL) {
		pt->uid = uid;
		pt->fow = usrtb[indx];
		usrtb[indx] = pt;
		return(0);
	}
        warn(1, "User selection table out of memory");
        return(-1);
}

/*
 * usr_match()
 *	check if this files uid matches a selected uid.
 * Return:
 *	0 if this archive member should be processed, 1 if it should be skipped
 */

#if __STDC__
static int
usr_match(register ARCHD *arcn)
#else
static int
usr_match(arcn)
	register ARCHD *arcn;
#endif
{
	register USRT *pt;

	/*
	 * hash and look for it in the table
	 */
	pt = usrtb[((unsigned)arcn->sb.st_uid) % USR_TB_SZ];
	while (pt != NULL) {
		if (pt->uid == arcn->sb.st_uid)
			return(0);
		pt = pt->fow;
	}

	/*
	 * not found
	 */
	return(1);
}

/*
 * grp_add()
 *	add a group match to the group match hash table
 * Return:
 *	0 if added ok, -1 otherwise;
 */

#if __STDC__
int
grp_add(register char *str)
#else
int
grp_add(str)
	register char *str;
#endif
{
	register u_int indx;
	register GRPT *pt;
	register struct group *gr;
	register gid_t gid;

	/*
	 * create the table if it doesn't exist
	 */
	if ((str == NULL) || (*str == '\0'))
		return(-1);
	if ((grptb == NULL) &&
 	    ((grptb = (GRPT **)calloc(GRP_TB_SZ, sizeof(GRPT *))) == NULL)) {
                warn(1, "Unable to allocate memory fo group selection table");
                return(-1);
	}

	/*
	 * figure out user spec
	 */
	if (str[0] != '#') {
		/*
		 * it is a group name, \# escapes # as first char in group name
		 */
		if ((str[0] == '\\') && (str[1] == '#'))
			++str;
		if ((gr = getgrnam(str)) == NULL) {
                	warn(1,"Cannot determine gid for group name: %s", str);
                	return(-1);
		}
		gid = (gid_t)gr->gr_gid;
        } else
#		ifdef NET2_STAT
		gid = (gid_t)atoi(str+1);
#		else
		gid = (gid_t)strtoul(str+1, (char **)NULL, 10);
#		endif
	endgrent();

	/*
	 * hash it and go down the hash chain (if any) looking for it
	 */
	indx = ((unsigned)gid) % GRP_TB_SZ;
	if ((pt = grptb[indx]) != NULL) {
                while (pt != NULL) {
                        if (pt->gid == gid)
				return(0);
                        pt = pt->fow;
                }
	}

	/*
D 2
	 * gid not already in the table, add it to the front of the chain
E 2
I 2
	 * gid not in the table, add it to the front of the chain
E 2
	 */
	if ((pt = (GRPT *)malloc(sizeof(GRPT))) != NULL) {
		pt->gid = gid;
		pt->fow = grptb[indx];
		grptb[indx] = pt;
		return(0);
	}
        warn(1, "Group selection table out of memory");
        return(-1);
}

/*
 * grp_match()
 *	check if this files gid matches a selected gid.
 * Return:
 *	0 if this archive member should be processed, 1 if it should be skipped
 */

#if __STDC__
static int
grp_match(register ARCHD *arcn)
#else
static int
grp_match(arcn)
	register ARCHD *arcn;
#endif
{
	register GRPT *pt;

	/*
	 * hash and look for it in the table
	 */
	pt = grptb[((unsigned)arcn->sb.st_gid) % GRP_TB_SZ];
	while (pt != NULL) {
		if (pt->gid == arcn->sb.st_gid)
			return(0);
		pt = pt->fow;
	}

	/*
	 * not found
	 */
	return(1);
}

/*
 * Time range selection routines
 *
D 2
 * Routines to handle user selection of files based on the modification time
 * being within a specified time range (the non-standard -T flag). The user
 * may specify any number of different file modification time ranges. The
 * ranges are checked one at a time until a match is found (if at all).
 * If the file has a mtime that lies within one of the time ranges, the file
 * is selected. Time ranges may have a lower and/or a upper value. Ranges are
 * inclusive. If no time ranges are supplied to pax, all members in the archive
 * will be selected. If only a lower range is supplied, all files with a mtime
 * equal to or younger are selected. If only an upper range is supplied, all
 * files with a mtime equal to or older will be selected. When the lower value
 * is equal to the upper value, only files with a mtime of exactly that time
 * will be selected.
E 2
I 2
 * Routines to handle user selection of files based on the modification and/or
 * inode change time falling within a specified time range (the non-standard
 * -T flag). The user may specify any number of different file time ranges.
 * Time ranges are checked one at a time until a match is found (if at all).
 * If the file has a mtime (and/or ctime) which lies within one of the time
 * ranges, the file is selected. Time ranges may have a lower and/or a upper
 * value. These ranges are inclusive. When no time ranges are supplied to pax
 * with the -T option, all members in the archive will be selected by the time
 * range routines. When only a lower range is supplied, only files with a
 * mtime (and/or ctime) equal to or younger are selected. When only a upper
 * range is supplied, only files with a mtime (and/or ctime) equal to or older
 * are selected. When the lower time range is equal to the upper time range,
 * only files with a mtime (or ctime) of exactly that time are selected.
E 2
 */

/*
 * trng_add()
 *	add a time range match to the time range list.
 *	This is a non-standard pax option. Lower and upper ranges are in the
 *	format: [yy[mm[dd[hh]]]]mm[.ss] and are comma separated.
 *	Time ranges are based on current time, so 1234 would specify a time of
 *	12:34 today.
 * Return:
 *	0 if the time range was added to the list, -1 otherwise
 */

#if __STDC__
int
trng_add(register char *str)
#else
int
trng_add(str)
	register char *str;
#endif
{
	register TIME_RNG *pt;
	register char *up_pt = NULL;
	register char *stpt;
I 2
	register char *flgpt;
E 2
	register int dot = 0;

	/*
	 * throw out the badly formed time ranges
	 */
	if ((str == NULL) || (*str == '\0')) {
		warn(1, "Empty time range string");
		return(-1);
	}

I 2
	/*
D 3
	 * locate optional flags suffix /{cm}. We only allow a flag suffix(s)
	 * in write and copy (as none of the formats stores inode change time;
	 * currently inode change time cannot be set to a specific value by
	 * any system call).
E 3
I 3
	 * locate optional flags suffix /{cm}.
E 3
	 */
D 3
	if ((flgpt = rindex(str, '/')) != NULL) {
E 3
I 3
	if ((flgpt = rindex(str, '/')) != NULL)
E 3
		*flgpt++ = '\0';
D 3
		if ((act == LIST) || (act == EXTRACT)) {
			warn(1,"Time suffix only valid in write or copy modes");
			return(-1);
		}
	}
E 3

E 2
	for (stpt = str; *stpt != '\0'; ++stpt) {
		if ((*stpt >= '0') && (*stpt <= '9'))
			continue;
		if ((*stpt == ',') && (up_pt == NULL)) {
			*stpt = '\0';
			up_pt = stpt + 1;
			dot = 0;
			continue;
		}

		/*
		 * allow only one dot per range (secs)
		 */
		if ((*stpt == '.') && (!dot)) {
			++dot;
			continue;
		}
		warn(1, "Improperly specified time range: %s", str);
		goto out;
	}

	/*
	 * allocate space for the time range and store the limits
	 */
	if ((pt = (TIME_RNG *)malloc(sizeof(TIME_RNG))) == NULL) {
		warn(1, "Unable to allocate memory for time range");
		return(-1);
	}
D 2
	pt->flags = 0;
E 2

	/*
I 2
	 * by default we only will check file mtime, but usee can specify
	 * mtime, ctime (inode change time) or both.
	 */
	if ((flgpt == NULL) || (*flgpt == '\0'))
		pt->flgs = CMPMTME;
	else {
		pt->flgs = 0;
		while (*flgpt != '\0') {
			switch(*flgpt) {
			case 'M':
			case 'm':
				pt->flgs |= CMPMTME;
				break;
			case 'C':
			case 'c':
				pt->flgs |= CMPCTME;
				break;
			default:
				warn(1, "Bad option %c with time range %s",
				    *flgpt, str);
				goto out;
			}
			++flgpt;
		}
	}

	/*
E 2
	 * start off with the current time
	 */
	pt->low_time = pt->high_time = time((time_t *)NULL);
	if (*str != '\0') {
		/*
		 * add lower limit
		 */
		if (str_sec(str, &(pt->low_time)) < 0) {
			warn(1, "Illegal lower time range %s", str);
			(void)free((char *)pt);
			goto out;
		}
D 2
		pt->flags |= HASLOW;
E 2
I 2
		pt->flgs |= HASLOW;
E 2
	}

	if ((up_pt != NULL) && (*up_pt != '\0')) {
		/*
		 * add upper limit
		 */
		if (str_sec(up_pt, &(pt->high_time)) < 0) {
			warn(1, "Illegal upper time range %s", up_pt);
			(void)free((char *)pt);
			goto out;
		}
D 2
		pt->flags |= HASHIGH;
E 2
I 2
		pt->flgs |= HASHIGH;
E 2

		/*
		 * check that the upper and lower do not overlap
		 */
D 2
		if (pt->flags & HASLOW) {
E 2
I 2
		if (pt->flgs & HASLOW) {
E 2
			if (pt->low_time > pt->high_time) {
				warn(1, "Upper %s and lower %s time overlap",
					up_pt, str);
				(void)free((char *)pt);
				return(-1);
			}
		}
	}

	pt->fow = NULL;
	if (trhead == NULL) {
		trtail = trhead = pt;
		return(0);
	}
	trtail->fow = pt;
	trtail = pt;
	return(0);
I 2

E 2
    out:
D 2
	warn(0, "Time range format is: [yy[mm[dd[hh]]]]mm[.ss]");
E 2
I 2
	warn(1, "Time range format is: [yy[mm[dd[hh]]]]mm[.ss][/[c][m]]");
E 2
	return(-1);
}

/*
 * trng_match()
D 2
 *	check if this files mtime falls within any supplied time range.
E 2
I 2
 *	check if this files mtime/ctime falls within any supplied time range.
E 2
 * Return:
 *	0 if this archive member should be processed, 1 if it should be skipped
 */

#if __STDC__
static int
trng_match(register ARCHD *arcn)
#else
static int
trng_match(arcn)
	register ARCHD *arcn;
#endif
{
	register TIME_RNG *pt;

	/*
	 * have to search down the list one at a time looking for a match.
	 * remember time range limits are inclusive.
	 */
	pt = trhead;
	while (pt != NULL) {
D 2
		if (pt->flags & HASLOW) {
			if (arcn->sb.st_mtime < pt->low_time) {
E 2
I 2
		switch(pt->flgs & CMPBOTH) {
		case CMPBOTH:
			/*
			 * user wants both mtime and ctime checked for this
			 * time range
			 */
			if (((pt->flgs & HASLOW) &&
			    (arcn->sb.st_mtime < pt->low_time) &&
			    (arcn->sb.st_ctime < pt->low_time)) ||
			    ((pt->flgs & HASHIGH) &&
			    (arcn->sb.st_mtime > pt->high_time) &&
			    (arcn->sb.st_ctime > pt->high_time))) {
E 2
				pt = pt->fow;
				continue;
			}
D 2
		}
		if (pt->flags & HASHIGH) {
			if (arcn->sb.st_mtime > pt->high_time) {
E 2
I 2
			break;
		case CMPCTME:
			/*
			 * user wants only ctime checked for this time range
			 */
			if (((pt->flgs & HASLOW) &&
			    (arcn->sb.st_ctime < pt->low_time)) ||
			    ((pt->flgs & HASHIGH) &&
			    (arcn->sb.st_ctime > pt->high_time))) {
E 2
				pt = pt->fow;
				continue;
			}
I 2
			break;
		case CMPMTME:
		default:
			/*
			 * user wants only mtime checked for this time range
			 */
			if (((pt->flgs & HASLOW) &&
			    (arcn->sb.st_mtime < pt->low_time)) ||
			    ((pt->flgs & HASHIGH) &&
			    (arcn->sb.st_mtime > pt->high_time))) {
				pt = pt->fow;
				continue;
			}
			break;
E 2
		}
		break;
	}

	if (pt == NULL)
		return(1);
	return(0);
}

/*
 * str_sec()
 *	Convert a time string in the format of [yy[mm[dd[hh]]]]mm[.ss] to gmt
 *	seconds. Tval already has current time loaded into it at entry.
 * Return:
 *	0 if converted ok, -1 otherwise
 */

#if __STDC__
static int
str_sec(register char *str, time_t *tval)
#else
static int
str_sec(str, tval)
	register char *str;
	time_t *tval;
#endif
{
	register struct tm *lt;
	register char *dot = NULL;

	lt = localtime(tval);
	if ((dot = index(str, '.')) != NULL) {
		/*
		 * seconds (.ss)
		 */
		*dot++ = '\0';
		if (strlen(dot) != 2)
			return(-1);
		if ((lt->tm_sec = ATOI2(dot)) > 61)
			return(-1);
	} else
		lt->tm_sec = 0;

	switch (strlen(str)) {
	case 10:
		/*
		 * year (yy)
		 * watch out for year 2000
		 */
		if ((lt->tm_year = ATOI2(str)) < 69)
			lt->tm_year += 100;
		str += 2;
		/* FALLTHROUGH */
	case 8:
		/*
		 * month (mm)
		 * watch out months are from 0 - 11 internally
		 */
		if ((lt->tm_mon = ATOI2(str)) > 12)
			return(-1);
		--lt->tm_mon;
		str += 2;
		/* FALLTHROUGH */
	case 6:
		/*
		 * day (dd)
		 */
		if ((lt->tm_mday = ATOI2(str)) > 31)
			return(-1);
		str += 2;
		/* FALLTHROUGH */
	case 4:
		/*
		 * hour (hh)
		 */
		if ((lt->tm_hour = ATOI2(str)) > 23)
			return(-1);
		str += 2;
		/* FALLTHROUGH */
	case 2:
		/*
		 * minute (mm)
		 */
		if ((lt->tm_min = ATOI2(str)) > 59)
			return(-1);
		break;
	default:
		return(-1);
	}
	/*
	 * convert broken-down time to GMT clock time seconds
	 */
	if ((*tval = mktime(lt)) == -1)
		return(-1);
	return(0);
}
E 1
