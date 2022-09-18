h39227
s 00001/00001/00324
d D 8.3 95/04/28 14:38:39 bostic 9 8
c `id username' was printing the wrong primary group name.
c From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00009/00006/00316
d D 8.2 94/02/16 12:28:55 bostic 8 7
c fix types of arguments to match function prototype
c From: ralphc@pyramid.com (Ralph Campbell)
e
s 00005/00005/00317
d D 8.1 93/06/06 14:51:11 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00033/00044/00289
d D 5.6 91/11/12 18:45:39 mckusick 6 5
c use new library function getgrouplist
e
s 00009/00007/00324
d D 5.5 91/11/11 17:46:46 bostic 5 4
c dumb coding mistake, id -p wasn't calling group() correctly
e
s 00010/00004/00321
d D 5.4 91/11/11 17:29:20 bostic 4 3
c fix formatting, "id -G" was broken
e
s 00109/00117/00216
d D 5.3 91/11/11 15:34:07 bostic 3 2
c add -p option, rearrangement/cleanup
e
s 00009/00001/00324
d D 5.2 91/11/10 09:57:50 bostic 2 1
c cleanup in lots of ways, no real modifications of behavior
e
s 00325/00000/00000
d D 5.1 91/06/29 13:30:03 bostic 1 0
c date and time created 91/06/29 13:30:03 by bostic
e
u
U
t
T
I 1
/*-
D 7
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
D 7
char copyright[] =
"%Z% Copyright (c) 1991 The Regents of the University of California.\n\
 All rights reserved.\n";
E 7
I 7
static char copyright[] =
"%Z% Copyright (c) 1991, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 7
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/param.h>
D 8
#include <pwd.h>
#include <grp.h>
E 8
I 8

E 8
#include <errno.h>
D 8
#include <unistd.h>
#include <stdlib.h>
E 8
I 8
#include <grp.h>
#include <pwd.h>
E 8
#include <stdio.h>
I 8
#include <stdlib.h>
E 8
#include <string.h>
I 8
#include <unistd.h>
E 8

D 3
typedef struct passwd PW;
typedef struct group GR;

E 3
void	current __P((void));
void	err __P((const char *, ...));
D 3
int	gcmp __P((const void *, const void *));
void	sgroup __P((PW *));
void	ugroup __P((PW *));
E 3
I 3
void	pretty __P((struct passwd *));
void	group __P((struct passwd *, int));
E 3
void	usage __P((void));
D 3
void	user __P((PW *));
PW     *who __P((char *));
E 3
I 3
void	user __P((struct passwd *));
struct passwd *
	who __P((char *));
E 3

D 3
int Gflag, gflag, nflag, rflag, uflag;

E 3
I 3
int
E 3
main(argc, argv)
	int argc;
	char *argv[];
{
D 3
	GR *gr;
	PW *pw;
	int ch, id;
E 3
I 3
	struct group *gr;
	struct passwd *pw;
	int Gflag, ch, gflag, id, nflag, pflag, rflag, uflag;
E 3

D 3
	while ((ch = getopt(argc, argv, "Ggnru")) != EOF)
E 3
I 3
	Gflag = gflag = nflag = pflag = rflag = uflag = 0;
	while ((ch = getopt(argc, argv, "Ggnpru")) != EOF)
E 3
		switch(ch) {
		case 'G':
			Gflag = 1;
			break;
		case 'g':
			gflag = 1;
			break;
		case 'n':
			nflag = 1;
			break;
I 3
		case 'p':
			pflag = 1;
			break;
E 3
		case 'r':
			rflag = 1;
			break;
		case 'u':
			uflag = 1;
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

D 3
	pw = *argv ? who(*argv) : NULL;

D 2
	if (Gflag + gflag + uflag > 1)
E 2
I 2
	switch(Gflag + gflag + uflag) {
E 3
I 3
	switch(Gflag + gflag + pflag + uflag) {
E 3
	case 1:
		break;
	case 0:
		if (!nflag && !rflag)
			break;
		/* FALLTHROUGH */
	default:
E 2
		usage();
I 2
	}
E 2

D 3
	if (Gflag) {
		if (nflag)
			sgroup(pw);
		else
			ugroup(pw);
		exit(0);
	}
E 3
I 3
	pw = *argv ? who(*argv) : NULL;
E 3

	if (gflag) {
		id = pw ? pw->pw_gid : rflag ? getgid() : getegid();
D 3
		if (nflag && (gr = getgrgid(id))) {
E 3
I 3
		if (nflag && (gr = getgrgid(id)))
E 3
			(void)printf("%s\n", gr->gr_name);
D 3
			exit(0);
		}
		(void)printf("%u\n", id);
E 3
I 3
		else
			(void)printf("%u\n", id);
E 3
		exit(0);
	}

	if (uflag) {
		id = pw ? pw->pw_uid : rflag ? getuid() : geteuid();
D 3
		if (nflag && (pw = getpwuid(id))) {
E 3
I 3
		if (nflag && (pw = getpwuid(id)))
E 3
			(void)printf("%s\n", pw->pw_name);
D 3
			exit(0);
		}
		(void)printf("%u\n", id);
E 3
I 3
		else
			(void)printf("%u\n", id);
E 3
		exit(0);
	}

I 3
	if (Gflag) {
		group(pw, nflag);
		exit(0);
	}

	if (pflag) {
		pretty(pw);
		exit(0);
	}

E 3
	if (pw)
		user(pw);
	else
		current();
	exit(0);
}

void
D 3
sgroup(pw)
	PW *pw;
E 3
I 3
pretty(pw)
	struct passwd *pw;
E 3
{
D 3
	register int id, lastid;
	char *fmt;
E 3
I 3
	struct group *gr;
	u_int eid, rid;
	char *login;
E 3

D 3
	if (pw) {
		register GR *gr;
		register char *name, **p;
E 3
I 3
D 5
	if (pw)
E 5
I 5
	if (pw) {
E 5
		(void)printf("uid\t%s\n", pw->pw_name);
D 5
	else {
E 5
I 5
		(void)printf("groups\t");
		group(pw, 1);
	} else {
E 5
		if ((login = getlogin()) == NULL)
			err("getlogin: %s", strerror(errno));
E 3

D 3
		name = pw->pw_name;
		for (fmt = "%s", lastid = -1; gr = getgrent(); lastid = id) {
			for (p = gr->gr_mem; p && *p; p++)
				if (!strcmp(*p, name)) {
					(void)printf(fmt, gr->gr_name);
					fmt = " %s";
					break;
				}
		}
	} else {
		GR *gr;
		register int ngroups;
		int groups[NGROUPS + 1];

		groups[0] = getgid();
		ngroups = getgroups(NGROUPS, groups + 1) + 1;
		heapsort(groups, ngroups, sizeof(groups[0]), gcmp);
		for (fmt = "%s", lastid = -1; --ngroups >= 0;) {
			if (lastid == (id = groups[ngroups]))
				continue;
			if (gr = getgrgid(id))
				(void)printf(fmt, gr->gr_name);
E 3
I 3
		pw = getpwuid(rid = getuid());
		if (pw == NULL || strcmp(login, pw->pw_name))
			(void)printf("login\t%s\n", login);
		if (pw)
			(void)printf("uid\t%s\n", pw->pw_name);
		else
			(void)printf("uid\t%u\n", rid);
		
		if ((eid = geteuid()) != rid)
			if (pw = getpwuid(eid))
				(void)printf("euid\t%s", pw->pw_name);
E 3
			else
D 3
				(void)printf(*fmt == ' ' ? " %u" : "%u", id);
			fmt = " %s";
			lastid = id;
		}
E 3
I 3
				(void)printf("euid\t%u", eid);
		if ((rid = getgid()) != (eid = getegid()))
			if (gr = getgrgid(rid))
				(void)printf("rgid\t%s\n", gr->gr_name);
			else
				(void)printf("rgid\t%u\n", rid);
I 5
		(void)printf("groups\t");
		group(NULL, 1);
E 5
E 3
	}
D 3
	(void)printf("\n");
E 3
I 3
D 5
	(void)printf("groups\t");
	group(pw, 1);
E 5
E 3
}

void
D 3
ugroup(pw)
	PW *pw;
{
	register int id, lastid;
	register char *fmt;

	if (pw) {
		register GR *gr;
		register char *name, **p;

		name = pw->pw_name;
		for (fmt = "%u", lastid = -1; gr = getgrent(); lastid = id) {
			for (p = gr->gr_mem; p && *p; p++)
				if (!strcmp(*p, name)) {
					(void)printf(fmt, gr->gr_gid);
					fmt = " %u";
					break;
				}
		}
	} else {
		register int ngroups;
		int groups[NGROUPS + 1];

		groups[0] = getgid();
		ngroups = getgroups(NGROUPS, groups + 1) + 1;
		heapsort(groups, ngroups, sizeof(groups[0]), gcmp);
		for (fmt = "%u", lastid = -1; --ngroups >= 0;) {
			if (lastid == (id = groups[ngroups]))
				continue;
			(void)printf(fmt, id);
			fmt = " %u";
			lastid = id;
		}
	}
	(void)printf("\n");
}

void
E 3
current()
{
D 3
	GR *gr;
	PW *pw;
E 3
I 3
	struct group *gr;
	struct passwd *pw;
E 3
D 6
	int id, eid, lastid, ngroups, groups[NGROUPS];
E 6
I 6
D 8
	int cnt, id, eid, lastid, ngroups, groups[NGROUPS];
E 8
I 8
	int cnt, id, eid, lastid, ngroups;
	gid_t groups[NGROUPS];
E 8
E 6
	char *fmt;

	id = getuid();
	(void)printf("uid=%u", id);
	if (pw = getpwuid(id))
		(void)printf("(%s)", pw->pw_name);
	if ((eid = geteuid()) != id) {
		(void)printf(" euid=%u", eid);
		if (pw = getpwuid(eid))
			(void)printf("(%s)", pw->pw_name);
	}
	id = getgid();
	(void)printf(" gid=%u", id);
	if (gr = getgrgid(id))
		(void)printf("(%s)", gr->gr_name);
	if ((eid = getegid()) != id) {
		(void)printf(" egid=%u", eid);
		if (gr = getgrgid(eid))
			(void)printf("(%s)", gr->gr_name);
	}
	if (ngroups = getgroups(NGROUPS, groups)) {
D 3
		heapsort(groups, ngroups, sizeof(groups[0]), gcmp);
E 3
D 6
		for (fmt = " groups=%u", lastid = -1; --ngroups >= 0;
E 6
I 6
		for (fmt = " groups=%u", lastid = -1, cnt = 0; cnt < ngroups;
E 6
		    fmt = ", %u", lastid = id) {
D 6
			id = groups[ngroups];
E 6
I 6
			id = groups[cnt++];
E 6
			if (lastid == id)
				continue;
			(void)printf(fmt, id);
			if (gr = getgrgid(id))
				(void)printf("(%s)", gr->gr_name);
		}
	}
	(void)printf("\n");
}

void
user(pw)
D 3
	register PW *pw;
E 3
I 3
	register struct passwd *pw;
E 3
{
D 3
	register GR *gr;
E 3
I 3
	register struct group *gr;
E 3
D 6
	register int id, lastid;
E 6
	register char *fmt, **p;
I 6
	int cnt, id, lastid, ngroups, groups[NGROUPS + 1];
E 6

	id = pw->pw_uid;
	(void)printf("uid=%u(%s)", id, pw->pw_name);
	(void)printf(" gid=%u", pw->pw_gid);
D 9
	if (gr = getgrgid(id))
E 9
I 9
	if (gr = getgrgid(pw->pw_gid))
E 9
		(void)printf("(%s)", gr->gr_name);
D 6
	for (fmt = " groups=%u(%s)", lastid = -1; gr = getgrent();
	    lastid = id) {
		if (pw->pw_gid == gr->gr_gid)
E 6
I 6
	ngroups = NGROUPS + 1;
	(void) getgrouplist(pw->pw_name, pw->pw_gid, groups, &ngroups);
	fmt = " groups=%u";
	for (lastid = -1, cnt = 0; cnt < ngroups; ++cnt) {
		if (lastid == (id = groups[cnt]))
E 6
			continue;
D 6
		for (p = gr->gr_mem; p && *p; p++)
			if (!strcmp(*p, pw->pw_name)) {
				(void)printf(fmt, gr->gr_gid, gr->gr_name);
				fmt = ", %u(%s)";
				break;
			}
E 6
I 6
		(void)printf(fmt, id);
		fmt = " %u";
		if (gr = getgrgid(id))
			(void)printf("(%s)", gr->gr_name);
		lastid = id;
E 6
	}
	(void)printf("\n");
}

D 3
PW *
E 3
I 3
void
group(pw, nflag)
	struct passwd *pw;
	int nflag;
{
	struct group *gr;
D 5
	int id, lastid, ngroups, groups[NGROUPS + 1];
E 5
I 5
D 8
	int cnt, id, lastid, ngroups, groups[NGROUPS + 1];
E 8
I 8
	int cnt, id, lastid, ngroups;
	gid_t groups[NGROUPS + 1];
E 8
E 5
D 6
	char *fmt, *name, **p;
E 6
I 6
	char *fmt;
E 6

D 6
	fmt = nflag ? "%s" : "%u";
E 6
	if (pw) {
D 6
		name = pw->pw_name;
		while (gr = getgrent()) {
			for (p = gr->gr_mem; p && *p; p++)
				if (!strcmp(*p, name)) {
					if (nflag) {
						(void)printf(fmt, gr->gr_name);
						fmt = " %s";
					} else {
						(void)printf(fmt, gr->gr_gid);
						fmt = " %u";
					}
					break;
				}
		}
E 6
I 6
		ngroups = NGROUPS + 1;
		(void) getgrouplist(pw->pw_name, pw->pw_gid, groups, &ngroups);
E 6
	} else {
		groups[0] = getgid();
		ngroups = getgroups(NGROUPS, groups + 1) + 1;
D 5
		for (lastid = -1; --ngroups >= 0;) {
			if (lastid == (id = groups[ngroups]))
E 5
I 5
D 6
		for (lastid = -1, cnt = 0; cnt < ngroups; ++cnt) {
			if (lastid == (id = groups[cnt]))
E 5
				continue;
D 4
			if (nflag && (gr = getgrgid(id))) {
				(void)printf(fmt, gr->gr_name);
E 4
I 4
			if (nflag) {
				if (gr = getgrgid(id))
					(void)printf(fmt, gr->gr_name);
				else
					(void)printf(*fmt == ' ' ? " %u" : "%u",
					    id);
E 4
				fmt = " %s";
D 4
			} else
				(void)printf(*fmt == ' ' ? " %u" : "%u", id);
E 4
I 4
			} else {
				(void)printf(fmt, id);
				fmt = " %u";
			}
E 4
			lastid = id;
E 6
I 6
	}
	fmt = nflag ? "%s" : "%u";
	for (lastid = -1, cnt = 0; cnt < ngroups; ++cnt) {
		if (lastid == (id = groups[cnt]))
			continue;
		if (nflag) {
			if (gr = getgrgid(id))
				(void)printf(fmt, gr->gr_name);
			else
				(void)printf(*fmt == ' ' ? " %u" : "%u",
				    id);
			fmt = " %s";
		} else {
			(void)printf(fmt, id);
			fmt = " %u";
E 6
		}
I 6
		lastid = id;
E 6
	}
	(void)printf("\n");
}

struct passwd *
E 3
who(u)
	char *u;
{
D 3
	PW *pw;
E 3
I 3
	struct passwd *pw;
E 3
	long id;
	char *ep;

	/*
	 * Translate user argument into a pw pointer.  First, try to
	 * get it as specified.  If that fails, try it as a number.
	 */
	if (pw = getpwnam(u))
		return(pw);
	id = strtol(u, &ep, 10);
	if (*u && !*ep && (pw = getpwuid(id)))
		return(pw);
	err("%s: No such user", u);
	/* NOTREACHED */
D 3
}

gcmp(a, b)
	const void *a, *b;
{
	return(*(int *)b - *(int *)a);
E 3
}

#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

void
#if __STDC__
err(const char *fmt, ...)
#else
err(fmt, va_alist)
	char *fmt;
        va_dcl
#endif
{
	va_list ap;
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	(void)fprintf(stderr, "id: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	exit(1);
	/* NOTREACHED */
}

void
usage()
{
	(void)fprintf(stderr, "usage: id [user]\n");
	(void)fprintf(stderr, "       id -G [-n] [user]\n");
	(void)fprintf(stderr, "       id -g [-nr] [user]\n");
	(void)fprintf(stderr, "       id -u [-nr] [user]\n");
	exit(1);
}
E 1
