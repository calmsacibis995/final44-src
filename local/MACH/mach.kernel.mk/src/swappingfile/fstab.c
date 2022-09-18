/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */
/*
 * HISTORY
 * $Log:	fstab.c,v $
 * Revision 1.2  90/01/23  17:23:12  berman
 * 	Added code to read extra fs_name and fs_opts fields.
 * 	[90/01/23            berman]
 * 
 */
#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "@(#)fstab.c	5.2 (Berkeley) 3/9/86";
#endif LIBC_SCCS and not lint

#include <fstab.h>
#include <stdio.h>
#include <ctype.h>

static	struct fstab fs;
static	char line[BUFSIZ+1];
static	FILE *fs_file = 0;

static char *
fsskip(p)
	register char *p;
{

#if CMUCS
	while (*p && *p != ':' && *p != '\n')
#else /* CMUCS */
	while (*p && *p != ':')
#endif /* CMUCS */
		++p;
	if (*p)
		*p++ = 0;
	return (p);
}

static char *
fsdigit(backp, string, end)
	int *backp;
	char *string, end;
{
	register int value = 0;
	register char *cp;

	for (cp = string; *cp && isdigit(*cp); cp++) {
		value *= 10;
		value += *cp - '0';
	}
	if (*cp == '\0')
		return ((char *)0);
	*backp = value;
	while (*cp && *cp != end)
		cp++;
	if (*cp == '\0')
		return ((char *)0);
	return (cp+1);
}

static
fstabscan(fs)
	struct fstab *fs;
{
	register char *cp;
#if CMUCS
	register char *ocp;
#endif /* CMUCS */

	cp = fgets(line, 256, fs_file);
	if (cp == NULL)
		return (EOF);
	fs->fs_spec = cp;
	cp = fsskip(cp);
	fs->fs_file = cp;
	cp = fsskip(cp);
	fs->fs_type = cp;
	cp = fsskip(cp);
	cp = fsdigit(&fs->fs_freq, cp, ':');
	if (cp == 0)
		return (3);
#if CMUCS
	ocp = cp;		/* Save a pointer in case of old style fstab */
	fs->fs_opts = fs->fs_name = NULL;	    /* Clear optional fields */
	cp = fsdigit(&fs->fs_passno, cp, ':');
	if (cp) {
		fs->fs_name = cp;
		cp = fsskip(cp);
		if (cp == 0)
			return (5);
		fs->fs_opts = cp;
		cp = fsskip(cp);
		if (cp == 0)
			return (6);
		return (7);
	} else {	/* Looks like an old style fstab line */
		cp = fsdigit(&fs->fs_passno, ocp, '\n');
		if (cp == 0)
			return (4);
		return (5);
	}
#else /* CMUCS */
	cp = fsdigit(&fs->fs_passno, cp, '\n');
	if (cp == 0)
		return (4);
	return (5);
#endif /* CMUCS */
}
	
setfsent()
{

	if (fs_file)
		endfsent();
	if ((fs_file = fopen(FSTAB, "r")) == NULL) {
		fs_file = 0;
		return (0);
	}
	return (1);
}

endfsent()
{

	if (fs_file) {
		fclose(fs_file);
		fs_file = 0;
	}
	return (1);
}

struct fstab *
getfsent()
{
	int nfields;

	if ((fs_file == 0) && (setfsent() == 0))
		return ((struct fstab *)0);
	nfields = fstabscan(&fs);
#if CMUCS
	if (nfields == EOF || nfields < 5)
#else /* CMUCS */
	if (nfields == EOF || nfields != 5)
#endif /* CMUCS */
		return ((struct fstab *)0);
	return (&fs);
}

struct fstab *
getfsspec(name)
	char *name;
{
	register struct fstab *fsp;

	if (setfsent() == 0)	/* start from the beginning */
		return ((struct fstab *)0);
	while((fsp = getfsent()) != 0)
		if (strcmp(fsp->fs_spec, name) == 0)
			return (fsp);
	return ((struct fstab *)0);
}

struct fstab *
getfsfile(name)
	char *name;
{
	register struct fstab *fsp;

	if (setfsent() == 0)	/* start from the beginning */
		return ((struct fstab *)0);
	while ((fsp = getfsent()) != 0)
		if (strcmp(fsp->fs_file, name) == 0)
			return (fsp);
	return ((struct fstab *)0);
}

struct fstab *
getfstype(type)
	char *type;
{
	register struct fstab *fs;

	if (setfsent() == 0)
		return ((struct fstab *)0);
	while ((fs = getfsent()) != 0)
		if (strcmp(fs->fs_type, type) == 0)
			return (fs);
	return ((struct fstab *)0);
}
