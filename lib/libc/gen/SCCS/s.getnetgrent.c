h23283
s 00002/00000/00313
d D 8.2 95/04/27 16:51:06 bostic 4 3
c Null pointer dereference
c From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00002/00002/00311
d D 8.1 93/06/04 12:03:02 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00077/00064/00236
d D 5.2 92/04/14 18:07:00 mckusick 2 1
c update from Rick Macklem for new Sun-compatible syntax
e
s 00300/00000/00000
d D 5.1 92/04/09 19:17:36 mckusick 1 0
c from Rick Macklem
e
u
U
t
T
I 1
/*
D 3
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Rick Macklem at The University of Guelph.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <stdio.h>
#include <strings.h>

#define _PATH_NETGROUP "/etc/netgroup"

/*
 * Static Variables and functions used by setnetgrent(), getnetgrent() and
 * endnetgrent().
 * There are two linked lists:
 * - linelist is just used by setnetgrent() to parse the net group file via.
 *   parse_netgrp()
 * - netgrp is the list of entries for the current netgroup
 */
struct linelist {
	struct linelist	*l_next;	/* Chain ptr. */
	int		l_parsed;	/* Flag for cycles */
	char		*l_groupname;	/* Name of netgroup */
	char		*l_line;	/* Netgroup entrie(s) to be parsed */
};

struct netgrp {
	struct netgrp	*ng_next;	/* Chain ptr */
D 2
	char		*ng_host;	/* Host name */
	char		*ng_user;	/* User name */
	char		*ng_dom;	/* and Domain name */
E 2
I 2
	char		*ng_str[3];	/* Field pointers, see below */
E 2
};
I 2
#define NG_HOST		0	/* Host name */
#define NG_USER		1	/* User name */
#define NG_DOM		2	/* and Domain name */
E 2

static struct linelist	*linehead = (struct linelist *)0;
static struct netgrp	*nextgrp = (struct netgrp *)0;
static struct {
	struct netgrp	*gr;
	char		*grname;
} grouphead = {
	(struct netgrp *)0,
	(char *)0,
};
static FILE *netf = (FILE *)0;
static int parse_netgrp();
static struct linelist *read_for_group();
void setnetgrent(), endnetgrent();
int getnetgrent(), innetgr();

#define	LINSIZ	1024	/* Length of netgroup file line */

/*
 * setnetgrent()
 * Parse the netgroup file looking for the netgroup and build the list
 * of netgrp structures. Let parse_netgrp() and read_for_group() do
 * most of the work.
 */
void
setnetgrent(group)
	char *group;
{

	if (grouphead.gr == (struct netgrp *)0 ||
		strcmp(group, grouphead.grname)) {
		endnetgrent();
		if (netf = fopen(_PATH_NETGROUP, "r")) {
			if (parse_netgrp(group))
				endnetgrent();
			else {
				grouphead.grname = (char *)
					malloc(strlen(group) + 1);
				strcpy(grouphead.grname, group);
			}
			fclose(netf);
		}
	}
	nextgrp = grouphead.gr;
}

/*
 * Get the next netgroup off the list.
 */
int
getnetgrent(hostp, userp, domp)
	char **hostp, **userp, **domp;
{

	if (nextgrp) {
D 2
		*hostp = nextgrp->ng_host;
		*userp = nextgrp->ng_user;
		*domp = nextgrp->ng_dom;
E 2
I 2
		*hostp = nextgrp->ng_str[NG_HOST];
		*userp = nextgrp->ng_str[NG_USER];
		*domp = nextgrp->ng_str[NG_DOM];
E 2
		nextgrp = nextgrp->ng_next;
		return (1);
	}
	return (0);
}

/*
 * endnetgrent() - cleanup
 */
void
endnetgrent()
{
	register struct linelist *lp, *olp;
	register struct netgrp *gp, *ogp;

	lp = linehead;
	while (lp) {
		olp = lp;
		lp = lp->l_next;
		free(olp->l_groupname);
		free(olp->l_line);
		free((char *)olp);
	}
	linehead = (struct linelist *)0;
	if (grouphead.grname) {
		free(grouphead.grname);
		grouphead.grname = (char *)0;
	}
	gp = grouphead.gr;
	while (gp) {
		ogp = gp;
		gp = gp->ng_next;
D 2
		if (ogp->ng_host)
			free(ogp->ng_host);
		if (ogp->ng_user)
			free(ogp->ng_user);
		if (ogp->ng_dom)
			free(ogp->ng_dom);
E 2
I 2
		if (ogp->ng_str[NG_HOST])
			free(ogp->ng_str[NG_HOST]);
		if (ogp->ng_str[NG_USER])
			free(ogp->ng_str[NG_USER]);
		if (ogp->ng_str[NG_DOM])
			free(ogp->ng_str[NG_DOM]);
E 2
		free((char *)ogp);
	}
	grouphead.gr = (struct netgrp *)0;
}

/*
 * Search for a match in a netgroup.
 */
int
innetgr(group, host, user, dom)
	char *group, *host, *user, *dom;
{
	char *hst, *usr, *dm;

	setnetgrent(group);
	while (getnetgrent(&hst, &usr, &dm))
		if ((host == (char *)0 || !strcmp(host, hst)) &&
		    (user == (char *)0 || !strcmp(user, usr)) &&
		    (dom == (char *)0 || !strcmp(dom, dm))) {
			endnetgrent();
			return (1);
		}
	endnetgrent();
	return (0);
}

/*
 * Parse the netgroup file setting up the linked lists.
 */
static int
parse_netgrp(group)
	char *group;
{
D 2
	register char *pos, *spos;
	register int len;
E 2
I 2
	register char *spos, *epos;
	register int len, strpos;
	char *pos, *gpos;
E 2
	struct netgrp *grp;
	struct linelist *lp = linehead;

	/*
	 * First, see if the line has already been read in.
	 */
	while (lp) {
		if (!strcmp(group, lp->l_groupname))
			break;
		lp = lp->l_next;
	}
	if (lp == (struct linelist *)0 &&
	    (lp = read_for_group(group)) == (struct linelist *)0)
		return (1);
	if (lp->l_parsed) {
		fprintf(stderr, "Cycle in netgroup %s\n", lp->l_groupname);
		return (1);
	} else
		lp->l_parsed = 1;
	pos = lp->l_line;
	while (*pos != '\0') {
		if (*pos == '(') {
			grp = (struct netgrp *)malloc(sizeof (struct netgrp));
			bzero((char *)grp, sizeof (struct netgrp));
			grp->ng_next = grouphead.gr;
			grouphead.gr = grp;
D 2
			spos = ++pos;
			while (*pos != ',' && *pos != '\0')
				pos++;
			if (*pos == '\0')
				goto errout;
			len = pos - spos;
			if (len > 0) {
				grp->ng_host = (char *)malloc(len + 1);
				bcopy(spos, grp->ng_host, len);
				*(grp->ng_host + len) = '\0';
E 2
I 2
			pos++;
			gpos = strsep(&pos, ")");
			for (strpos = 0; strpos < 3; strpos++) {
				if (spos = strsep(&gpos, ",")) {
					while (*spos == ' ' || *spos == '\t')
						spos++;
					if (epos = strpbrk(spos, " \t")) {
						*epos = '\0';
						len = epos - spos;
					} else
						len = strlen(spos);
					if (len > 0) {
						grp->ng_str[strpos] =  (char *)
							malloc(len + 1);
						bcopy(spos, grp->ng_str[strpos],
							len + 1);
					}
				} else
					goto errout;
E 2
			}
D 2
			spos = ++pos;
			while (*pos != ',' && *pos != '\0')
				pos++;
			if (*pos == '\0')
				goto errout;
			len = pos - spos;
			if (len > 0) {
				grp->ng_user = (char *)malloc(len + 1);
				bcopy(spos, grp->ng_user, len);
				*(grp->ng_user + len) = '\0';
			}
			spos = ++pos;
			while (*pos != ')' && *pos != '\0')
				pos++;
			if (*pos == '\0')
				goto errout;
			len = pos - spos;
			if (len > 0) {
				grp->ng_dom = (char *)malloc(len + 1);
				bcopy(spos, grp->ng_dom, len);
				*(grp->ng_dom + len) = '\0';
			}
			if (*++pos != '\0' &&
				(*pos != ',' || *++pos == ',' || *pos == '\0'))
				goto errout;
E 2
		} else {
D 2
			spos = pos;
			while (*pos != ',' && *pos != '\0')
				pos++;
			if (*pos == ',')
				*pos++ = '\0';
E 2
I 2
			spos = strsep(&pos, ", \t");
E 2
			if (parse_netgrp(spos))
				return (1);
		}
I 4
		if (pos == NULL)
			break;
E 4
I 2
		while (*pos == ' ' || *pos == ',' || *pos == '\t')
			pos++;
E 2
	}
	return (0);
errout:
	fprintf(stderr, "Bad netgroup %s at ..%s\n", lp->l_groupname,
		spos);
	return (1);
}

/*
 * Read the netgroup file and save lines until the line for the netgroup
 * is found. Return 1 if eof is encountered.
 */
static struct linelist *
read_for_group(group)
	char *group;
{
D 2
	register char *pos, *spos;
	register int len;
E 2
I 2
	register char *pos, *spos, *linep, *olinep;
	register int len, olen;
	int cont;
E 2
	struct linelist *lp;
	char line[LINSIZ + 1];

	while (fgets(line, LINSIZ, netf) != NULL) {
		pos = line;
I 2
		if (*pos == '#')
			continue;
E 2
		while (*pos == ' ' || *pos == '\t')
			pos++;
		spos = pos;
		while (*pos != ' ' && *pos != '\t' && *pos != '\n' &&
			*pos != '\0')
			pos++;
		len = pos - spos;
		while (*pos == ' ' || *pos == '\t')
			pos++;
		if (*pos != '\n' && *pos != '\0') {
			lp = (struct linelist *)malloc(sizeof (*lp));
			lp->l_parsed = 0;
			lp->l_groupname = (char *)malloc(len + 1);
			bcopy(spos, lp->l_groupname, len);
			*(lp->l_groupname + len) = '\0';
D 2
			spos = lp->l_line = (char *)malloc(LINSIZ);
			while (*pos != '\n' && *pos != '\0') {
				if (*pos != ' ' && *pos != '\t')
					*spos++ = *pos++;
				else
					pos++;
			}
			*spos = '\0';
E 2
I 2
			len = strlen(pos);
			olen = 0;

			/*
			 * Loop around handling line continuations.
			 */
			do {
				if (*(pos + len - 1) == '\n')
					len--;
				if (*(pos + len - 1) == '\\') {
					len--;
					cont = 1;
				} else
					cont = 0;
				if (len > 0) {
					linep = (char *)malloc(olen + len + 1);
					if (olen > 0) {
						bcopy(olinep, linep, olen);
						free(olinep);
					}
					bcopy(pos, linep + olen, len);
					olen += len;
					*(linep + olen) = '\0';
					olinep = linep;
				}
				if (cont) {
					if (fgets(line, LINSIZ, netf)) {
						pos = line;
						len = strlen(pos);
					} else
						cont = 0;
				}
			} while (cont);
			lp->l_line = linep;
E 2
			lp->l_next = linehead;
			linehead = lp;

			/*
			 * If this is the one we wanted, we are done.
			 */
			if (!strcmp(lp->l_groupname, group))
				return (lp);
		}
	}
	return ((struct linelist *)0);
}
E 1
