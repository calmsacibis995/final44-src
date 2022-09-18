h39650
s 00002/00002/00902
d D 8.2 95/04/29 13:09:07 christos 26 25
c Fixes from Chris Demetriou and Charles Hannum 
e
s 00002/00002/00902
d D 8.1 93/05/31 16:41:39 bostic 25 24
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00020/00020/00884
d D 5.20 93/05/22 19:06:22 christos 24 23
c Fixed gcc -Wall warnings
e
s 00001/00002/00903
d D 5.19 93/03/08 18:04:45 ralph 23 22
c fix null pointer bug.
e
s 00004/00002/00901
d D 5.18 92/02/12 20:07:11 christos 22 21
c Fixed directory printing in case there was both a ~user and a ~user1.
e
s 00005/00005/00898
d D 5.17 91/11/06 16:09:30 christos 21 20
c Added support for displaying non-printable characters
e
s 00056/00032/00847
d D 5.16 91/10/28 21:27:52 leres 20 19
c Fix gcc "bodyless for/while" warnings.
e
s 00001/00001/00878
d D 5.15 91/10/27 15:59:54 christos 19 18
c dinit() would pass to dcanon() an unallocated pointer
e
s 00001/00008/00878
d D 5.14 91/08/02 03:49:03 christos 18 17
c Fixed incorrect string splicing code.
e
s 00025/00017/00861
d D 5.13 91/07/19 17:30:32 christos 17 16
c stdio based version; brace glob fix; builtin prototypes
e
s 00003/00001/00875
d D 5.12 91/06/26 23:45:10 christos 16 15
c Wrong reason was reported for cd'ing to a directory with no permission
e
s 00001/00001/00875
d D 5.11 91/06/24 21:54:17 christos 15 14
c Don't canonicalize home directories that don't start with a slash
e
s 00005/00000/00871
d D 5.10 91/06/08 17:08:37 christos 14 13
c More prototype fixes, Removed TERMIOS define
e
s 00007/00000/00864
d D 5.9 91/06/08 12:20:11 bostic 13 12
c include file pass, csh.h no longer include every .h in the system
c rename sigmast_t to sigset_t to match signal.h; minor pointer cleanups
e
s 00014/00013/00850
d D 5.8 91/06/07 20:57:14 christos 12 11
c static function prototypes
e
s 00005/00005/00858
d D 5.7 91/06/07 11:13:17 bostic 11 10
c rename all the files (they weren't going to diff anyway)
c add function prototypes for extern functions, decls.h -> extern.h
c delete btell function, VFORK #define, lots of other minor cleanups
e
s 00745/00357/00118
d D 5.6 91/06/04 13:31:17 bostic 10 9
c new version from Christos -- 8-bit clean, lots of bug fixes
c massive changes, including a pass of indent.
e
s 00007/00006/00468
d D 5.5 91/04/04 18:17:33 bostic 9 8
c new copyright; att/bsd/shared
e
s 00002/00001/00472
d D 5.4 88/04/14 09:56:08 bostic 8 7
c use SHDIAG, not "2", already mucked with descriptors
e
s 00002/00002/00471
d D 5.3 85/06/11 18:59:44 edward 7 6
c cd <varname> bug reported by Jay Lapreau
e
s 00003/00003/00470
d D 5.2 85/06/06 13:11:17 edward 6 5
c cleaning up after bozos
e
s 00008/00002/00465
d D 5.1 85/06/04 10:55:50 dist 5 4
c Add copyright
e
s 00147/00041/00320
d D 4.4 85/05/02 17:51:13 edward 4 3
c expand symbolic link before ..
e
s 00014/00012/00347
d D 4.3 84/12/13 14:42:16 edward 3 2
c performance
e
s 00006/00001/00353
d D 4.2 83/02/03 09:12:14 sam 2 1
c getwd moved to libc.a and error return changed
e
s 00354/00000/00000
d D 4.1 80/10/09 12:40:27 bill 1 0
c date and time created 80/10/09 12:40:27 by bill
e
u
U
t
T
I 5
D 9
/*
 * Copyright (c) 1980 Regents of the University of California.
D 6
 * All rights reserved.  The Berkeley software License Agreement
E 6
I 6
 * All rights reserved.  The Berkeley Software License Agreement
E 6
 * specifies the terms and conditions for redistribution.
E 9
I 9
/*-
D 25
 * Copyright (c) 1980, 1991 The Regents of the University of California.
 * All rights reserved.
E 25
I 25
 * Copyright (c) 1980, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 25
 *
 * %sccs.include.redist.c%
E 9
 */

E 5
I 1
D 3
static	char *sccsid = "%Z%%M% %I% %G%";
E 3
I 3
#ifndef lint
D 5
static	char *sccsid = "%W% (Berkeley) %G%";
#endif
E 5
I 5
D 6
static char sccsid[] = "%W% (Berkeley) %G%";
#endif not lint
E 6
I 6
D 9
static char *sccsid = "%W% (Berkeley) %G%";
#endif
E 9
I 9
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 9
E 6
E 5
E 3

I 13
#include <sys/param.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
I 14
#if __STDC__
# include <stdarg.h>
#else
# include <varargs.h>
#endif
E 14

E 13
D 11
#include "sh.h"
#include "sh.dir.h"
D 10

E 10
/*
 * C Shell - directory management
 */
E 11
I 11
#include "csh.h"
#include "dir.h"
#include "extern.h"

/* Directory management. */
E 11

D 10
struct	directory *dfind();
char	*dfollow();
I 4
char	*dcanon();
E 4
struct	directory dhead;		/* "head" of loop */
int	printd;				/* force name to be printed */
static	char *fakev[] = { "dirs", NOSTR };
E 10
I 10
D 12
static struct directory *dfind();
static Char *dfollow();
static void printdirs();
static Char *dgoto();
static void dnewcwd();
static void dset();
E 12
I 12
D 20
static struct directory 	
E 20
I 20
static struct directory
E 20
		*dfind __P((Char *));
D 20
static Char 	*dfollow __P((Char *));
static void 	 printdirs __P((void));
static Char 	*dgoto __P((Char *));
static void 	 dnewcwd __P((struct directory *));
static void 	 dset __P((Char *));
E 20
I 20
static Char	*dfollow __P((Char *));
static void	 printdirs __P((void));
static Char	*dgoto __P((Char *));
static void	 dnewcwd __P((struct directory *));
static void	 dset __P((Char *));
E 20
E 12
E 10

I 10
struct directory dhead;		/* "head" of loop */
int     printd;			/* force name to be printed */

static int dirflag = 0;

E 10
/*
 * dinit - initialize current working directory
 */
I 10
void
E 10
dinit(hp)
D 10
	char *hp;
E 10
I 10
    Char   *hp;
E 10
{
D 10
	register char *cp;
	register struct directory *dp;
D 4
	char path[BUFSIZ];
E 4
I 4
	char path[MAXPATHLEN];
E 10
I 10
    register char *tcp;
    register Char *cp;
    register struct directory *dp;
    char    path[MAXPATHLEN];
    static char *emsg = "csh: Trying to start from \"%s\"\n";
E 10
E 4

D 10
	if (loginsh && hp)
E 10
I 10
    /* Don't believe the login shell home, because it may be a symlink */
D 26
    tcp = getwd(path);		/* see ngetwd.c for System V version */
E 26
I 26
    tcp = getcwd(path, MAXPATHLEN);
E 26
    if (tcp == NULL || *tcp == '\0') {
D 17
	(void) xprintf("csh: %s\n", path);
E 17
I 17
D 26
	(void) fprintf(csherr, "csh: %s\n", path);
E 26
I 26
	(void) fprintf(csherr, "csh: %s\n", strerror(errno));
E 26
E 17
	if (hp && *hp) {
	    tcp = short2str(hp);
D 17
	    (void) xprintf(emsg, tcp);
E 17
I 17
D 21
	    (void) fprintf(csherr, emsg, tcp);
E 21
E 17
	    if (chdir(tcp) == -1)
D 12
		cp = (Char *) 0;
E 12
I 12
		cp = NULL;
E 12
	    else
E 10
		cp = hp;
I 21
	    (void) fprintf(csherr, emsg, vis_str(hp));
E 21
I 10
	}
	else
D 12
	    cp = (Char *) 0;
	if (cp == (Char *) 0) {
E 12
I 12
	    cp = NULL;
	if (cp == NULL) {
E 12
D 17
	    (void) xprintf(emsg, "/");
E 17
I 17
	    (void) fprintf(csherr, emsg, "/");
E 17
	    if (chdir("/") == -1)
		/* I am not even try to print an error message! */
		xexit(1);
	    cp = SAVE("/");
	}
    }
    else {
	struct stat swd, shp;

	/*
	 * See if $HOME is the working directory we got and use that
	 */
	if (hp && *hp &&
	    stat(tcp, &swd) != -1 && stat(short2str(hp), &shp) != -1 &&
	    swd.st_dev == shp.st_dev && swd.st_ino == shp.st_ino)
	    cp = hp;
E 10
D 2
	else
E 2
I 2
	else {
E 2
D 10
		cp = getwd(path);
I 2
		if (cp == NULL) {
D 3
			write(2, path, strlen(path));
E 3
I 3
D 8
			(void) write(2, path, strlen(path));
E 8
I 8
#define	WDERR	"csh: can't get current directory.\n"
			(void) write(SHDIAG, WDERR, strlen(WDERR));
E 8
E 3
			exit(1);
		}
E 10
I 10
	    char   *cwd;

	    /*
	     * use PWD if we have it (for subshells)
	     */
D 24
	    if (cwd = getenv("PWD")) {
E 24
I 24
	    if ((cwd = getenv("PWD")) != NULL) {
E 24
		if (stat(cwd, &shp) != -1 && swd.st_dev == shp.st_dev &&
		    swd.st_ino == shp.st_ino)
		    tcp = cwd;
	    }
D 19
	    cp = dcanon(str2short(tcp), STRNULL);
E 19
I 19
	    cp = dcanon(SAVE(tcp), STRNULL);
E 19
E 10
	}
E 2
D 10
	dp = (struct directory *)calloc(sizeof (struct directory), 1);
	dp->di_name = savestr(cp);
	dp->di_count = 0;
	dhead.di_next = dhead.di_prev = dp;
	dp->di_next = dp->di_prev = &dhead;
	printd = 0;
	dnewcwd(dp);
E 10
I 10
    }

    dp = (struct directory *) xcalloc(sizeof(struct directory), 1);
    dp->di_name = Strsave(cp);
    dp->di_count = 0;
    dhead.di_next = dhead.di_prev = dp;
    dp->di_next = dp->di_prev = &dhead;
    printd = 0;
    dnewcwd(dp);
E 10
}

I 10
static void
dset(dp)
Char *dp;
{
    /*
     * Don't call set() directly cause if the directory contains ` or
D 20
     * other junk characters glob will fail. 
E 20
I 20
     * other junk characters glob will fail.
E 20
     */
    register Char **vec = (Char **) xmalloc((size_t) (2 * sizeof(Char **)));

    vec[0] = Strsave(dp);
    vec[1] = 0;
    setq(STRcwd, vec, &shvhed);
    Setenv(STRPWD, dp);
}

#define DIR_LONG 1
#define DIR_VERT 2
#define DIR_LINE 4

static void
skipargs(v, str)
    Char ***v;
    char   *str;
{
    Char  **n = *v, *s;

    dirflag = 0;
    for (n++; *n != NULL && (*n)[0] == '-'; n++)
	for (s = &((*n)[1]); *s; s++)
	    switch (*s) {
	    case 'l':
		dirflag |= DIR_LONG;
		break;
	    case 'v':
		dirflag |= DIR_VERT;
		break;
	    case 'n':
		dirflag |= DIR_LINE;
		break;
	    default:
D 21
		stderror(ERR_DIRUS, short2str(**v), str);
E 21
I 21
		stderror(ERR_DIRUS, vis_str(**v), str);
E 21
		break;
	    }
    *v = n;
}

E 10
/*
 * dodirs - list all directories in directory loop
 */
I 10
void
E 10
D 17
dodirs(v)
D 10
	char **v;
E 10
I 10
    Char  **v;
E 17
I 17
/*ARGSUSED*/
dodirs(v, t)
    Char **v;
    struct command *t;
E 17
E 10
{
D 10
	register struct directory *dp;
	bool lflag;
	char *hp = value("home");
E 10
I 10
    skipargs(&v, "");
E 10

D 10
	if (*hp == '\0')
		hp = NOSTR;
	if (*++v != NOSTR)
		if (eq(*v, "-l") && *++v == NOSTR)
			lflag = 1;
		else
			error("Usage: dirs [ -l ]");
E 10
I 10
    if (*v != NULL)
	stderror(ERR_DIRUS, "dirs", "");
    printdirs();
}

static void
printdirs()
{
    register struct directory *dp;
    Char   *s, *hp = value(STRhome);
    int     idx, len, cur;

    if (*hp == '\0')
	hp = NULL;
    dp = dcwd;
    idx = 0;
    cur = 0;
    do {
	if (dp == &dhead)
	    continue;
	if (dirflag & DIR_VERT) {
D 17
	    xprintf("%d\t", idx++);
E 17
I 17
	    (void) fprintf(cshout, "%d\t", idx++);
E 17
	    cur = 0;
	}
I 22
D 23
	len = Strlen(hp);
E 23
E 22
	if (!(dirflag & DIR_LONG) && hp != NULL && !eq(hp, STRslash) &&
D 22
	    prefix(hp, dp->di_name))
	    len = Strlen(s = (dp->di_name + Strlen(hp))) + 2;
E 22
I 22
D 23
	    Strncmp(hp, dp->di_name, len) == 0 &&
E 23
I 23
	    (len = Strlen(hp), Strncmp(hp, dp->di_name, len) == 0) &&
E 23
	    (dp->di_name[len] == '\0' || dp->di_name[len] == '/')) 
	    len = Strlen(s = (dp->di_name + len)) + 2;
E 22
E 10
	else
D 10
		lflag = 0;
	dp = dcwd;
	do {
		if (dp == &dhead)
			continue;
		if (!lflag && hp != NOSTR) {
			dtildepr(hp, dp->di_name);
		} else
			printf("%s", dp->di_name);
		printf(" ");
	} while ((dp = dp->di_prev) != dcwd);
	printf("\n");
E 10
I 10
	    len = Strlen(s = dp->di_name) + 1;

	cur += len;
	if ((dirflag & DIR_LINE) && cur >= 80 - 1 && len < 80) {
D 17
	    xprintf("\n");
E 17
I 17
	    (void) fprintf(cshout, "\n");
E 17
	    cur = len;
	}
D 17
	xprintf(s != dp->di_name ? "~%s%c" : "%s%c",
E 17
I 17
	(void) fprintf(cshout, s != dp->di_name ? "~%s%c" : "%s%c",
E 17
D 21
		short2str(s), (dirflag & DIR_VERT) ? '\n' : ' ');
E 21
I 21
		vis_str(s), (dirflag & DIR_VERT) ? '\n' : ' ');
E 21
    } while ((dp = dp->di_prev) != dcwd);
    if (!(dirflag & DIR_VERT))
D 17
	xprintf("\n");
E 17
I 17
	(void) fprintf(cshout, "\n");
E 17
E 10
}

I 10
void
E 10
dtildepr(home, dir)
D 10
	register char *home, *dir;
E 10
I 10
    register Char *home, *dir;
E 10
{

D 10
	if (!eq(home, "/") && prefix(home, dir))
		printf("~%s", dir + strlen(home));
	else
		printf("%s", dir);
E 10
I 10
    if (!eq(home, STRslash) && prefix(home, dir))
D 17
	xprintf("~%s", short2str(dir + Strlen(home)));
E 17
I 17
D 21
	(void) fprintf(cshout, "~%s", short2str(dir + Strlen(home)));
E 21
I 21
	(void) fprintf(cshout, "~%s", vis_str(dir + Strlen(home)));
E 21
E 17
    else
D 17
	xprintf("%s", short2str(dir));
E 17
I 17
D 21
	(void) fprintf(cshout, "%s", short2str(dir));
E 21
I 21
	(void) fprintf(cshout, "%s", vis_str(dir));
E 21
E 17
E 10
}

I 10
void
dtilde()
{
    struct directory *d = dcwd;

    do {
	if (d == &dhead)
	    continue;
	d->di_name = dcanon(d->di_name, STRNULL);
    } while ((d = d->di_prev) != dcwd);

    dset(dcwd->di_name);
}


/* dnormalize():
 *	If the name starts with . or .. then we might need to normalize
 *	it depending on the symbolic link flags
 */
Char   *
dnormalize(cp)
    Char   *cp;
{

#define UC (unsigned char)
#define ISDOT(c) (UC(c)[0] == '.' && ((UC(c)[1] == '\0') || (UC(c)[1] == '/')))
#define ISDOTDOT(c) (UC(c)[0] == '.' && ISDOT(&((c)[1])))

    if ((unsigned char) cp[0] == '/')
	return (Strsave(cp));

    if (adrof(STRignore_symlinks)) {
	int     dotdot = 0;
	Char   *dp, *cwd;

	cwd = (Char *) xmalloc((size_t) ((Strlen(dcwd->di_name) + 3) *
					 sizeof(Char)));
	(void) Strcpy(cwd, dcwd->di_name);

	/*
	 * Ignore . and count ..'s
	 */
	while (*cp) {
	    if (ISDOT(cp)) {
		if (*++cp)
		    cp++;
	    }
	    else if (ISDOTDOT(cp)) {
		dotdot++;
		cp += 2;
		if (*cp)
		    cp++;
	    }
	    else
		break;
	}
	while (dotdot > 0)
	    if ((dp = Strrchr(cwd, '/'))) {
		*dp = '\0';
		dotdot--;
	    }
	    else
		break;

	if (*cp) {
	    cwd[dotdot = Strlen(cwd)] = '/';
	    cwd[dotdot + 1] = '\0';
	    dp = Strspl(cwd, cp);
	    xfree((ptr_t) cwd);
	    return dp;
	}
	else {
	    if (!*cwd) {
		cwd[0] = '/';
		cwd[1] = '\0';
	    }
	    return cwd;
	}
    }
    return Strsave(cp);
}

E 10
/*
 * dochngd - implement chdir command.
 */
I 10
void
E 10
D 17
dochngd(v)
D 10
	char **v;
E 10
I 10
    Char  **v;
E 17
I 17
/*ARGSUSED*/
dochngd(v, t)
    Char **v;
    struct command *t;
E 17
E 10
{
D 10
	register char *cp;
	register struct directory *dp;
E 10
I 10
    register Char *cp;
    register struct directory *dp;
E 10

D 10
	printd = 0;
	if (*++v == NOSTR) {
		if ((cp = value("home")) == NOSTR || *cp == 0)
			bferr("No home directory");
		if (chdir(cp) < 0)
			bferr("Can't change to home directory");
		cp = savestr(cp);
	} else if ((dp = dfind(*v)) != 0) {
		printd = 1;
		if (chdir(dp->di_name) < 0)
			Perror(dp->di_name);
		dcwd->di_prev->di_next = dcwd->di_next;
		dcwd->di_next->di_prev = dcwd->di_prev;
		goto flushcwd;
	} else
		cp = dfollow(*v);
	dp = (struct directory *)calloc(sizeof (struct directory), 1);
	dp->di_name = cp;
	dp->di_count = 0;
	dp->di_next = dcwd->di_next;
	dp->di_prev = dcwd->di_prev;
	dp->di_prev->di_next = dp;
	dp->di_next->di_prev = dp;
flushcwd:
E 10
I 10
    skipargs(&v, " [<dir>]");
    printd = 0;
    if (*v == NULL) {
	if ((cp = value(STRhome)) == NULL || *cp == 0)
	    stderror(ERR_NAME | ERR_NOHOMEDIR);
	if (chdir(short2str(cp)) < 0)
	    stderror(ERR_NAME | ERR_CANTCHANGE);
	cp = Strsave(cp);
    }
    else if (v[1] != NULL) {
	stderror(ERR_NAME | ERR_TOOMANY);
	/* NOTREACHED */
	return;
    }
    else if ((dp = dfind(*v)) != 0) {
	char   *tmp;

	printd = 1;
	if (chdir(tmp = short2str(dp->di_name)) < 0)
	    stderror(ERR_SYSTEM, tmp, strerror(errno));
	dcwd->di_prev->di_next = dcwd->di_next;
	dcwd->di_next->di_prev = dcwd->di_prev;
E 10
	dfree(dcwd);
	dnewcwd(dp);
I 10
	return;
    }
    else
	cp = dfollow(*v);
    dp = (struct directory *) xcalloc(sizeof(struct directory), 1);
    dp->di_name = cp;
    dp->di_count = 0;
    dp->di_next = dcwd->di_next;
    dp->di_prev = dcwd->di_prev;
    dp->di_prev->di_next = dp;
    dp->di_next->di_prev = dp;
    dfree(dcwd);
    dnewcwd(dp);
E 10
}

I 10
static Char *
dgoto(cp)
    Char   *cp;
{
    Char   *dp;

    if (*cp != '/') {
	register Char *p, *q;
	int     cwdlen;

D 20
	for (p = dcwd->di_name; *p++;);
E 20
I 20
	for (p = dcwd->di_name; *p++;)
	    continue;
E 20
	if ((cwdlen = p - dcwd->di_name - 1) == 1)	/* root */
	    cwdlen = 0;
D 20
	for (p = cp; *p++;);
E 20
I 20
	for (p = cp; *p++;)
	    continue;
E 20
	dp = (Char *) xmalloc((size_t)((cwdlen + (p - cp) + 1) * sizeof(Char)));
D 20
	for (p = dp, q = dcwd->di_name; *p++ = *q++;);
E 20
I 20
D 24
	for (p = dp, q = dcwd->di_name; *p++ = *q++;)
E 24
I 24
	for (p = dp, q = dcwd->di_name; (*p++ = *q++) != '\0';)
E 24
	    continue;
E 20
	if (cwdlen)
	    p[-1] = '/';
	else
	    p--;		/* don't add a / after root */
D 20
	for (q = cp; *p++ = *q++;);
E 20
I 20
D 24
	for (q = cp; *p++ = *q++;)
E 24
I 24
	for (q = cp; (*p++ = *q++) != '\0';)
E 24
	    continue;
E 20
	xfree((ptr_t) cp);
	cp = dp;
	dp += cwdlen;
    }
    else
	dp = cp;

    cp = dcanon(cp, dp);
    return cp;
}

E 10
/*
 * dfollow - change to arg directory; fall back on cdpath if not valid
 */
D 10
char *
E 10
I 10
static Char *
E 10
dfollow(cp)
D 10
	register char *cp;
E 10
I 10
    register Char *cp;
E 10
{
D 4
	register char **cdp;
E 4
I 4
D 10
	register char *dp;
E 4
	struct varent *c;
E 10
I 10
    register Char *dp;
    struct varent *c;
    char    ebuf[MAXPATHLEN];
I 16
    int serrno;
E 16
E 10
D 4
	
E 4
I 4

E 4
D 10
	cp = globone(cp);
D 4
	if (chdir(cp) == 0)
E 4
I 4
	if (chdir(cp) >= 0)
E 4
		goto gotcha;
	if (cp[0] != '/' && !prefix("./", cp) && !prefix("../", cp)
	    && (c = adrof("cdpath"))) {
D 4
		for (cdp = c->vec; *cdp; cdp++) {
			char buf[BUFSIZ];
E 4
I 4
		char **cdp;
		register char *p;
		char buf[MAXPATHLEN];
E 10
I 10
    cp = globone(cp, G_ERROR);
    /*
     * if we are ignoring symlinks, try to fix relatives now.
     */
    dp = dnormalize(cp);
    if (chdir(short2str(dp)) >= 0) {
	xfree((ptr_t) cp);
	return dgoto(dp);
    }
    else {
	xfree((ptr_t) dp);
	if (chdir(short2str(cp)) >= 0)
	    return dgoto(cp);
I 16
	serrno = errno;
E 16
    }
E 10
E 4

D 3
			strcpy(buf, *cdp);
			strcat(buf, "/");
			strcat(buf, cp);
E 3
I 3
D 4
			(void) strcpy(buf, *cdp);
			(void) strcat(buf, "/");
			(void) strcat(buf, cp);
E 4
I 4
D 10
		for (cdp = c->vec; *cdp; cdp++) {
			for (dp = buf, p = *cdp; *dp++ = *p++;)
				;
			dp[-1] = '/';
			for (p = cp; *dp++ = *p++;)
				;
E 4
E 3
			if (chdir(buf) >= 0) {
				printd = 1;
				xfree(cp);
				cp = savestr(buf);
				goto gotcha;
			}
		}
	}
D 4
	if (adrof(cp)) {
		char *dp = value(cp);

		if (dp[0] == '/' || dp[0] == '.')
			if (chdir(dp) >= 0) {
				xfree(cp);
				cp = savestr(dp);
				printd = 1;
				goto gotcha;
			}
E 4
I 4
D 7
	if ((dp = value(cp))[0] &&
	    (dp[0] == '/' || dp[0] == '.' && chdir(dp) >= 0)) {
E 7
I 7
	dp = value(cp);
	if ((dp[0] == '/' || dp[0] == '.') && chdir(dp) >= 0) {
E 7
		xfree(cp);
		cp = savestr(dp);
E 10
I 10
    if (cp[0] != '/' && !prefix(STRdotsl, cp) && !prefix(STRdotdotsl, cp)
	&& (c = adrof(STRcdpath))) {
	Char  **cdp;
	register Char *p;
	Char    buf[MAXPATHLEN];

	for (cdp = c->vec; *cdp; cdp++) {
D 20
	    for (dp = buf, p = *cdp; *dp++ = *p++;);
E 20
I 20
D 24
	    for (dp = buf, p = *cdp; *dp++ = *p++;)
E 24
I 24
	    for (dp = buf, p = *cdp; (*dp++ = *p++) != '\0';)
E 24
		continue;
E 20
	    dp[-1] = '/';
D 20
	    for (p = cp; *dp++ = *p++;);
E 20
I 20
D 24
	    for (p = cp; *dp++ = *p++;)
E 24
I 24
	    for (p = cp; (*dp++ = *p++) != '\0';)
E 24
		continue;
E 20
	    if (chdir(short2str(buf)) >= 0) {
E 10
		printd = 1;
D 10
		goto gotcha;
E 10
I 10
		xfree((ptr_t) cp);
		cp = Strsave(buf);
		return dgoto(cp);
	    }
E 10
E 4
	}
D 4
	xfree(cp);
E 4
I 4
D 10
	xfree(cp);			/* XXX, use after free */
E 4
	Perror(cp);

gotcha:
	if (*cp != '/') {
D 3
		char *dp = calloc(strlen(cp) + strlen(dcwd->di_name) + 2, 1);
		strcpy(dp, dcwd->di_name);
		strcat(dp, "/");
		strcat(dp, cp);
E 3
I 3
D 4
		char *dp = calloc((unsigned) (strlen(cp) + strlen(dcwd->di_name) + 2), 1);
		(void) strcpy(dp, dcwd->di_name);
		(void) strcat(dp, "/");
		(void) strcat(dp, cp);
E 4
I 4
		register char *p, *q;
		int cwdlen;

		/*
		 * All in the name of efficiency?
		 */
		for (p = dcwd->di_name; *p++;)
			;
		if ((cwdlen = p - dcwd->di_name - 1) == 1)	/* root */
			cwdlen = 0;
		for (p = cp; *p++;)
			;
		dp = xalloc((unsigned) (cwdlen + (p - cp) + 1));
		for (p = dp, q = dcwd->di_name; *p++ = *q++;)
			;
		if (cwdlen)
			p[-1] = '/';
		else
			p--;			/* don't add a / after root */
		for (q = cp; *p++ = *q++;)
			;
E 4
E 3
		xfree(cp);
		cp = dp;
D 4
	}
	dcanon(cp);
	return (cp);
E 4
I 4
		dp += cwdlen;
	} else
		dp = cp;
	return dcanon(cp, dp);
E 10
I 10
    }
    dp = value(cp);
    if ((dp[0] == '/' || dp[0] == '.') && chdir(short2str(dp)) >= 0) {
	xfree((ptr_t) cp);
	cp = Strsave(dp);
	printd = 1;
	return dgoto(cp);
    }
    (void) strcpy(ebuf, short2str(cp));
    xfree((ptr_t) cp);
D 16
    stderror(ERR_SYSTEM, ebuf, strerror(errno));
E 16
I 16
    stderror(ERR_SYSTEM, ebuf, strerror(serrno));
E 16
    return (NULL);
E 10
E 4
}

I 10

E 10
/*
 * dopushd - push new directory onto directory stack.
 *	with no arguments exchange top and second.
 *	with numeric argument (+n) bring it to top.
 */
I 10
void
E 10
D 17
dopushd(v)
D 10
	char **v;
E 10
I 10
    Char  **v;
E 17
I 17
/*ARGSUSED*/
dopushd(v, t)
    Char **v;
    struct command *t;
E 17
E 10
{
D 10
	register struct directory *dp;
E 10
I 10
    register struct directory *dp;
E 10

D 10
	printd = 1;
	if (*++v == NOSTR) {
		if ((dp = dcwd->di_prev) == &dhead)
			dp = dhead.di_prev;
		if (dp == dcwd)
			bferr("No other directory");
		if (chdir(dp->di_name) < 0)
			Perror(dp->di_name);
		dp->di_prev->di_next = dp->di_next;
		dp->di_next->di_prev = dp->di_prev;
		dp->di_next = dcwd->di_next;
		dp->di_prev = dcwd;
		dcwd->di_next->di_prev = dp;
		dcwd->di_next = dp;
	} else if (dp = dfind(*v)) {
		if (chdir(dp->di_name) < 0)
			Perror(dp->di_name);
	} else {
		register char *cp;
E 10
I 10
    skipargs(&v, " [<dir>|+<n>]");
    printd = 1;
    if (*v == NULL) {
	char   *tmp;
E 10

D 10
		cp = dfollow(*v);
		dp = (struct directory *)calloc(sizeof (struct directory), 1);
		dp->di_name = cp;
		dp->di_count = 0;
		dp->di_prev = dcwd;
		dp->di_next = dcwd->di_next;
		dcwd->di_next = dp;
		dp->di_next->di_prev = dp;
	}
	dnewcwd(dp);
E 10
I 10
	if ((dp = dcwd->di_prev) == &dhead)
	    dp = dhead.di_prev;
	if (dp == dcwd)
	    stderror(ERR_NAME | ERR_NODIR);
	if (chdir(tmp = short2str(dp->di_name)) < 0)
	    stderror(ERR_SYSTEM, tmp, strerror(errno));
	dp->di_prev->di_next = dp->di_next;
	dp->di_next->di_prev = dp->di_prev;
	dp->di_next = dcwd->di_next;
	dp->di_prev = dcwd;
	dcwd->di_next->di_prev = dp;
	dcwd->di_next = dp;
    }
    else if (v[1] != NULL) {
	stderror(ERR_NAME | ERR_TOOMANY);
	/* NOTREACHED */
	return;
    }
D 24
    else if (dp = dfind(*v)) {
E 24
I 24
    else if ((dp = dfind(*v)) != NULL) {
E 24
	char   *tmp;

	if (chdir(tmp = short2str(dp->di_name)) < 0)
	    stderror(ERR_SYSTEM, tmp, strerror(errno));
    }
    else {
	register Char *ccp;

	ccp = dfollow(*v);
	dp = (struct directory *) xcalloc(sizeof(struct directory), 1);
	dp->di_name = ccp;
	dp->di_count = 0;
	dp->di_prev = dcwd;
	dp->di_next = dcwd->di_next;
	dcwd->di_next = dp;
	dp->di_next->di_prev = dp;
    }
    dnewcwd(dp);
E 10
}

/*
 * dfind - find a directory if specified by numeric (+n) argument
 */
D 10
struct directory *
E 10
I 10
static struct directory *
E 10
dfind(cp)
D 10
	register char *cp;
E 10
I 10
    register Char *cp;
E 10
{
D 10
	register struct directory *dp;
	register int i;
	register char *ep;
E 10
I 10
    register struct directory *dp;
    register int i;
    register Char *ep;
E 10

D 10
	if (*cp++ != '+')
		return (0);
	for (ep = cp; digit(*ep); ep++)
		continue;
	if (*ep)
		return (0);
	i = getn(cp);
	if (i <= 0)
		return (0);
	for (dp = dcwd; i != 0; i--) {
		if ((dp = dp->di_prev) == &dhead)
			dp = dp->di_prev;
		if (dp == dcwd)
			bferr("Directory stack not that deep");
	}
	return (dp);
E 10
I 10
    if (*cp++ != '+')
	return (0);
    for (ep = cp; Isdigit(*ep); ep++)
	continue;
    if (*ep)
	return (0);
    i = getn(cp);
    if (i <= 0)
	return (0);
    for (dp = dcwd; i != 0; i--) {
	if ((dp = dp->di_prev) == &dhead)
	    dp = dp->di_prev;
	if (dp == dcwd)
	    stderror(ERR_NAME | ERR_DEEP);
    }
    return (dp);
E 10
}

/*
 * dopopd - pop a directory out of the directory stack
 *	with a numeric argument just discard it.
 */
I 10
void
E 10
D 17
dopopd(v)
D 10
	char **v;
E 10
I 10
    Char  **v;
E 17
I 17
/*ARGSUSED*/
dopopd(v, t)
    Char **v;
    struct command *t;
E 17
E 10
{
D 10
	register struct directory *dp, *p;
E 10
I 10
    register struct directory *dp, *p = NULL;
E 10

D 10
	printd = 1;
	if (*++v == NOSTR)
		dp = dcwd;
	else if ((dp = dfind(*v)) == 0)
		bferr("Bad directory");
	if (dp->di_prev == &dhead && dp->di_next == &dhead)
		bferr("Directory stack empty");
	if (dp == dcwd) {
		if ((p = dp->di_prev) == &dhead)
			p = dhead.di_prev;
		if (chdir(p->di_name) < 0)
			Perror(p->di_name);
	}
	dp->di_prev->di_next = dp->di_next;
	dp->di_next->di_prev = dp->di_prev;
	if (dp == dcwd)
		dnewcwd(p);
	else
		dodirs(fakev);
	dfree(dp);
E 10
I 10
    skipargs(&v, " [+<n>]");
    printd = 1;
    if (*v == NULL)
	dp = dcwd;
    else if (v[1] != NULL) {
	stderror(ERR_NAME | ERR_TOOMANY);
	/* NOTREACHED */
	return;
    }
    else if ((dp = dfind(*v)) == 0)
	stderror(ERR_NAME | ERR_BADDIR);
    if (dp->di_prev == &dhead && dp->di_next == &dhead)
	stderror(ERR_NAME | ERR_EMPTY);
    if (dp == dcwd) {
	char   *tmp;

	if ((p = dp->di_prev) == &dhead)
	    p = dhead.di_prev;
	if (chdir(tmp = short2str(p->di_name)) < 0)
	    stderror(ERR_SYSTEM, tmp, strerror(errno));
    }
    dp->di_prev->di_next = dp->di_next;
    dp->di_next->di_prev = dp->di_prev;
    if (dp == dcwd)
	dnewcwd(p);
    else {
	printdirs();
    }
    dfree(dp);
E 10
}

/*
 * dfree - free the directory (or keep it if it still has ref count)
 */
I 10
void
E 10
dfree(dp)
D 10
	register struct directory *dp;
E 10
I 10
    register struct directory *dp;
E 10
{

D 10
	if (dp->di_count != 0)
		dp->di_next = dp->di_prev = 0;
	else
		xfree(dp->di_name), xfree((char *)dp);
E 10
I 10
    if (dp->di_count != 0) {
	dp->di_next = dp->di_prev = 0;
    }
    else {
	xfree((char *) dp->di_name);
	xfree((ptr_t) dp);
    }
E 10
}

/*
 * dcanon - canonicalize the pathname, removing excess ./ and ../ etc.
 *	we are of course assuming that the file system is standardly
 *	constructed (always have ..'s, directories have links)
 */
D 4
dcanon(cp)
	char *cp;
E 4
I 4
D 10
char *
E 10
I 10
Char   *
E 10
dcanon(cp, p)
D 10
	register char *cp, *p;
E 10
I 10
    register Char *cp, *p;
E 10
E 4
{
D 4
	register char *p, *sp;
	register bool slash;
E 4
I 4
D 10
	register char *sp;
	register char *p1, *p2;		/* general purpose */
	bool slash;
E 10
I 10
    register Char *sp;
    register Char *p1, *p2;	/* general purpose */
    bool    slash;
E 10
E 4

D 10
	if (*cp != '/')
		abort();
D 4
	for (p = cp; *p; ) {		/* for each component */
E 4
I 4
	while (*p) {			/* for each component */
E 4
		sp = p;			/* save slash address */
D 4
		while(*++p == '/')	/* flush extra slashes */
E 4
I 4
		while (*++p == '/')	/* flush extra slashes */
E 4
			;
		if (p != ++sp)
D 3
			strcpy(sp, p);
E 3
I 3
D 4
			(void) strcpy(sp, p);
E 4
I 4
			for (p1 = sp, p2 = p; *p1++ = *p2++;)
				;
E 4
E 3
		p = sp;			/* save start of component */
		slash = 0;
D 4
		while(*++p)		/* find next slash or end of path */
E 4
I 4
		while (*++p)		/* find next slash or end of path */
E 4
			if (*p == '/') {
				slash = 1;
				*p = 0;
				break;
			}
		if (*sp == '\0')	/* if component is null */
			if (--sp == cp)	/* if path is one char (i.e. /) */
				break;
			else
				*sp = '\0';
D 4
		else if (eq(".", sp)) {
E 4
I 4
		else if (sp[0] == '.' && sp[1] == 0) {
E 4
			if (slash) {
D 3
				strcpy(sp, ++p);
E 3
I 3
D 4
				(void) strcpy(sp, ++p);
E 4
I 4
				for (p1 = sp, p2 = p + 1; *p1++ = *p2++;)
					;
E 4
E 3
				p = --sp;
			} else if (--sp != cp)
				*sp = '\0';
D 4
		} else if (eq("..", sp)) {
			if (--sp != cp)
E 4
I 4
		} else if (sp[0] == '.' && sp[1] == '.' && sp[2] == 0) {
			char link[MAXPATHLEN];
			int cc;
			char *newcp;
E 10
I 10
    Char    link[MAXPATHLEN];
    char    tlink[MAXPATHLEN];
    int     cc;
    Char   *newcp;
E 10

D 10
			/*
			 * We have something like "yyy/xxx/..", where "yyy"
			 * can be null or a path starting at /, and "xxx"
			 * is a single component.
			 * Before compressing "xxx/..", we want to expand
			 * "yyy/xxx", if it is a symbolic link.
			 */
			*--sp = 0;	/* form the pathname for readlink */
			if (sp != cp &&
			    (cc = readlink(cp, link, sizeof link)) >= 0) {
				link[cc] = '\0';
				if (slash)
					*p = '/';
				/*
				 * Point p to the '/' in "/..", and restore
				 * the '/'.
				 */
				*(p = sp) = '/';
				/*
				 * find length of p
				 */
				for (p1 = p; *p1++;)
					;
				if (*link != '/') {
					/*
					 * Relative path, expand it between
					 * the "yyy/" and the "/..".
					 * First, back sp up to the character
					 * past "yyy/".
					 */
					while (*--sp != '/')
						;
					sp++;
					*sp = 0;
					/*
					 * New length is
					 * "yyy/" + link + "/.." and rest
					 */
					p1 = newcp = xalloc((unsigned)
						((sp - cp) + cc + (p1 - p)));
					/*
					 * Copy new path into newcp
					 */
					for (p2 = cp; *p1++ = *p2++;)
						;
					for (p1--, p2 = link; *p1++ = *p2++;)
						;
					for (p1--, p2 = p; *p1++ = *p2++;)
						;
					/*
					 * Restart canonicalization at
					 * expanded "/xxx".
					 */
					p = sp - cp - 1 + newcp;
				} else {
					/*
					 * New length is link + "/.." and rest
					 */
					p1 = newcp = xalloc((unsigned)
						(cc + (p1 - p)));
					/*
					 * Copy new path into newcp
					 */
					for (p2 = link; *p1++ = *p2++;)
						;
					for (p1--, p2 = p; *p1++ = *p2++;)
						;
					/*
					 * Restart canonicalization at beginning
					 */
					p = newcp;
				}
				xfree(cp);
				cp = newcp;
				continue;	/* canonicalize the link */
			}
			*sp = '/';
			if (sp != cp)
E 4
				while (*--sp != '/')
					;
			if (slash) {
D 3
				strcpy(++sp, ++p);
E 3
I 3
D 4
				(void) strcpy(++sp, ++p);
E 3
				p = --sp;
E 4
I 4
				for (p1 = sp + 1, p2 = p + 1; *p1++ = *p2++;)
					;
				p = sp;
E 4
			} else if (cp == sp)
				*++sp = '\0';
			else
				*sp = '\0';
		} else if (slash)
			*p = '/';
E 10
I 10
    /*
     * christos: if the path given does not start with a slash prepend cwd. If
     * cwd does not start with a path or the result would be too long abort().
     */
    if (*cp != '/') {
	Char    tmpdir[MAXPATHLEN];

	p1 = value(STRcwd);
D 12
	if (p1 == (Char *) 0 || *p1 != '/')
E 12
I 12
	if (p1 == NULL || *p1 != '/')
E 12
	    abort();
	if (Strlen(p1) + Strlen(cp) + 1 >= MAXPATHLEN)
	    abort();
	(void) Strcpy(tmpdir, p1);
	(void) Strcat(tmpdir, STRslash);
	(void) Strcat(tmpdir, cp);
	xfree((ptr_t) cp);
	cp = p = Strsave(tmpdir);
    }

    while (*p) {		/* for each component */
	sp = p;			/* save slash address */
	while (*++p == '/')	/* flush extra slashes */
D 20
	    ;
E 20
I 20
	    continue;
E 20
	if (p != ++sp)
D 20
	    for (p1 = sp, p2 = p; *p1++ = *p2++;);
E 20
I 20
D 24
	    for (p1 = sp, p2 = p; *p1++ = *p2++;)
E 24
I 24
	    for (p1 = sp, p2 = p; (*p1++ = *p2++) != '\0';)
E 24
		continue;
E 20
	p = sp;			/* save start of component */
	slash = 0;
	while (*++p)		/* find next slash or end of path */
	    if (*p == '/') {
		slash = 1;
		*p = 0;
		break;
	    }

	if (*sp == '\0')	/* if component is null */
	    if (--sp == cp)	/* if path is one char (i.e. /) */
		break;
	    else
		*sp = '\0';
	else if (sp[0] == '.' && sp[1] == 0) {
	    if (slash) {
D 20
		for (p1 = sp, p2 = p + 1; *p1++ = *p2++;);
E 20
I 20
D 24
		for (p1 = sp, p2 = p + 1; *p1++ = *p2++;)
E 24
I 24
		for (p1 = sp, p2 = p + 1; (*p1++ = *p2++) != '\0';)
E 24
		    continue;
E 20
		p = --sp;
	    }
	    else if (--sp != cp)
		*sp = '\0';
E 10
	}
I 4
D 10
	return cp;
E 10
I 10
	else if (sp[0] == '.' && sp[1] == '.' && sp[2] == 0) {
	    /*
	     * We have something like "yyy/xxx/..", where "yyy" can be null or
	     * a path starting at /, and "xxx" is a single component. Before
	     * compressing "xxx/..", we want to expand "yyy/xxx", if it is a
	     * symbolic link.
	     */
	    *--sp = 0;		/* form the pathname for readlink */
	    if (sp != cp && !adrof(STRignore_symlinks) &&
		(cc = readlink(short2str(cp), tlink,
			       sizeof tlink)) >= 0) {
		(void) Strcpy(link, str2short(tlink));
		link[cc] = '\0';

		if (slash)
		    *p = '/';
		/*
		 * Point p to the '/' in "/..", and restore the '/'.
		 */
		*(p = sp) = '/';
		/*
		 * find length of p
		 */
D 20
		for (p1 = p; *p1++;);
E 20
I 20
		for (p1 = p; *p1++;)
		    continue;
E 20
		if (*link != '/') {
		    /*
		     * Relative path, expand it between the "yyy/" and the
		     * "/..". First, back sp up to the character past "yyy/".
		     */
D 20
		    while (*--sp != '/');
E 20
I 20
		    while (*--sp != '/')
			continue;
E 20
		    sp++;
		    *sp = 0;
		    /*
		     * New length is "yyy/" + link + "/.." and rest
		     */
		    p1 = newcp = (Char *) xmalloc((size_t)
						(((sp - cp) + cc + (p1 - p)) *
						 sizeof(Char)));
		    /*
		     * Copy new path into newcp
		     */
D 20
		    for (p2 = cp; *p1++ = *p2++;);
		    for (p1--, p2 = link; *p1++ = *p2++;);
		    for (p1--, p2 = p; *p1++ = *p2++;);
E 20
I 20
D 24
		    for (p2 = cp; *p1++ = *p2++;)
E 24
I 24
		    for (p2 = cp; (*p1++ = *p2++) != '\0';)
E 24
			continue;
D 24
		    for (p1--, p2 = link; *p1++ = *p2++;)
E 24
I 24
		    for (p1--, p2 = link; (*p1++ = *p2++) != '\0';)
E 24
			continue;
D 24
		    for (p1--, p2 = p; *p1++ = *p2++;)
E 24
I 24
		    for (p1--, p2 = p; (*p1++ = *p2++) != '\0';)
E 24
			continue;
E 20
		    /*
		     * Restart canonicalization at expanded "/xxx".
		     */
		    p = sp - cp - 1 + newcp;
		}
		else {
		    /*
		     * New length is link + "/.." and rest
		     */
		    p1 = newcp = (Char *) xmalloc((size_t)
					    ((cc + (p1 - p)) * sizeof(Char)));
		    /*
		     * Copy new path into newcp
		     */
D 20
		    for (p2 = link; *p1++ = *p2++;);
		    for (p1--, p2 = p; *p1++ = *p2++;);
E 20
I 20
D 24
		    for (p2 = link; *p1++ = *p2++;)
E 24
I 24
		    for (p2 = link; (*p1++ = *p2++) != '\0';)
E 24
			continue;
D 24
		    for (p1--, p2 = p; *p1++ = *p2++;)
E 24
I 24
		    for (p1--, p2 = p; (*p1++ = *p2++) != '\0';)
E 24
			continue;
E 20
		    /*
		     * Restart canonicalization at beginning
		     */
		    p = newcp;
		}
		xfree((ptr_t) cp);
		cp = newcp;
		continue;	/* canonicalize the link */
	    }
	    *sp = '/';
	    if (sp != cp)
D 20
		while (*--sp != '/');
E 20
I 20
		while (*--sp != '/')
		    continue;
E 20
	    if (slash) {
D 20
		for (p1 = sp + 1, p2 = p + 1; *p1++ = *p2++;);
E 20
I 20
D 24
		for (p1 = sp + 1, p2 = p + 1; *p1++ = *p2++;)
E 24
I 24
		for (p1 = sp + 1, p2 = p + 1; (*p1++ = *p2++) != '\0';)
E 24
		    continue;
E 20
		p = sp;
	    }
	    else if (cp == sp)
		*++sp = '\0';
	    else
		*sp = '\0';
	}
	else {			/* normal dir name (not . or .. or nothing) */

	    if (sp != cp && adrof(STRchase_symlinks) &&
		!adrof(STRignore_symlinks) &&
		(cc = readlink(short2str(cp), tlink,
			       sizeof tlink)) >= 0) {
		(void) Strcpy(link, str2short(tlink));
		link[cc] = '\0';

		/*
		 * restore the '/'.
		 */
		if (slash)
		    *p = '/';

		/*
		 * point sp to p (rather than backing up).
		 */
		sp = p;

		/*
		 * find length of p
		 */
D 20
		for (p1 = p; *p1++;);
E 20
I 20
		for (p1 = p; *p1++;)
		    continue;
E 20
		if (*link != '/') {
		    /*
		     * Relative path, expand it between the "yyy/" and the
		     * remainder. First, back sp up to the character past
		     * "yyy/".
		     */
D 20
		    while (*--sp != '/');
E 20
I 20
		    while (*--sp != '/')
			continue;
E 20
		    sp++;
		    *sp = 0;
		    /*
		     * New length is "yyy/" + link + "/.." and rest
		     */
		    p1 = newcp = (Char *) xmalloc((size_t)
						  (((sp - cp) + cc + (p1 - p))
						   * sizeof(Char)));
		    /*
		     * Copy new path into newcp
		     */
D 20
		    for (p2 = cp; *p1++ = *p2++;);
		    for (p1--, p2 = link; *p1++ = *p2++;);
		    for (p1--, p2 = p; *p1++ = *p2++;);
E 20
I 20
D 24
		    for (p2 = cp; *p1++ = *p2++;)
E 24
I 24
		    for (p2 = cp; (*p1++ = *p2++) != '\0';)
E 24
			continue;
D 24
		    for (p1--, p2 = link; *p1++ = *p2++;)
E 24
I 24
		    for (p1--, p2 = link; (*p1++ = *p2++) != '\0';)
E 24
			continue;
D 24
		    for (p1--, p2 = p; *p1++ = *p2++;)
E 24
I 24
		    for (p1--, p2 = p; (*p1++ = *p2++) != '\0';)
E 24
			continue;
E 20
		    /*
		     * Restart canonicalization at expanded "/xxx".
		     */
		    p = sp - cp - 1 + newcp;
		}
		else {
		    /*
		     * New length is link + the rest
		     */
		    p1 = newcp = (Char *) xmalloc((size_t)
					    ((cc + (p1 - p)) * sizeof(Char)));
		    /*
		     * Copy new path into newcp
		     */
D 20
		    for (p2 = link; *p1++ = *p2++;);
		    for (p1--, p2 = p; *p1++ = *p2++;);
E 20
I 20
D 24
		    for (p2 = link; *p1++ = *p2++;)
E 24
I 24
		    for (p2 = link; (*p1++ = *p2++) != '\0';)
E 24
			continue;
D 24
		    for (p1--, p2 = p; *p1++ = *p2++;)
E 24
I 24
		    for (p1--, p2 = p; (*p1++ = *p2++) != '\0';)
E 24
			continue;
E 20
		    /*
		     * Restart canonicalization at beginning
		     */
		    p = newcp;
		}
		xfree((ptr_t) cp);
		cp = newcp;
		continue;	/* canonicalize the link */
	    }
	    if (slash)
		*p = '/';
	}
    }

    /*
     * fix home...
     */
    p1 = value(STRhome);
    cc = Strlen(p1);
    /*
     * See if we're not in a subdir of STRhome
     */
D 15
    if (p1 && *p1 &&
E 15
I 15
    if (p1 && *p1 == '/' &&
E 15
	(Strncmp(p1, cp, cc) != 0 || (cp[cc] != '/' && cp[cc] != '\0'))) {
	static ino_t home_ino = -1;
	static dev_t home_dev = -1;
D 12
	static Char *home_ptr = (Char *) 0;
E 12
I 12
	static Char *home_ptr = NULL;
E 12
	struct stat statbuf;

	/*
	 * Get dev and ino of STRhome
	 */
	if (home_ptr != p1 &&
	    stat(short2str(p1), &statbuf) != -1) {
	    home_dev = statbuf.st_dev;
	    home_ino = statbuf.st_ino;
	    home_ptr = p1;
	}
	/*
	 * Start comparing dev & ino backwards
	 */
	p2 = Strcpy(link, cp);
D 12
	for (sp = (Char *) 0; *p2 && stat(short2str(p2), &statbuf) != -1;) {
E 12
I 12
	for (sp = NULL; *p2 && stat(short2str(p2), &statbuf) != -1;) {
E 12
	    if (statbuf.st_dev == home_dev &&
		statbuf.st_ino == home_ino) {
		sp = (Char *) - 1;
		break;
	    }
D 24
	    if (sp = Strrchr(p2, '/'))
E 24
I 24
	    if ((sp = Strrchr(p2, '/')) != NULL)
E 24
		*sp = '\0';
	}
	/*
	 * See if we found it
	 */
D 12
	if (*p2 && sp == (Char *) - 1) {
E 12
I 12
	if (*p2 && sp == (Char *) -1) {
E 12
	    /*
	     * Use STRhome to make '~' work
	     */
D 18
	    p2 = cp + Strlen(p2);
	    sp = newcp = (Char *) xmalloc((size_t)
					  ((cc + Strlen(p2)) * sizeof(Char)));
	    while (*p1)
		*sp++ = *p1++;
	    while (*p2)
		*sp++ = *p2++;
	    *sp = '\0';
E 18
I 18
	    newcp = Strspl(p1, cp + Strlen(p2));
E 18
	    xfree((ptr_t) cp);
	    cp = newcp;
	}
    }
    return cp;
E 10
E 4
}

I 10

E 10
/*
 * dnewcwd - make a new directory in the loop the current one
 */
I 10
static void
E 10
dnewcwd(dp)
D 10
	register struct directory *dp;
E 10
I 10
    register struct directory *dp;
E 10
{
D 10

	dcwd = dp;
	set("cwd", savestr(dcwd->di_name));
	if (printd)
		dodirs(fakev);
E 10
I 10
    dcwd = dp;
    dset(dcwd->di_name);
    if (printd && !(adrof(STRpushdsilent)))
	printdirs();
E 10
}
E 1
