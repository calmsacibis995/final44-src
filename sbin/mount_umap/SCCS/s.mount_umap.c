h50621
s 00002/00002/00204
d D 8.5 95/04/26 13:12:34 mckusick 9 8
c update for new kernel filesystem structure (vfsconf)
e
s 00004/00004/00202
d D 8.4 94/06/14 16:46:56 mkm 8 7
c mixup of uid and gid mapping files
e
s 00109/00116/00097
d D 8.3 94/03/27 11:50:09 bostic 7 6
c Jan-Simon Pendry's and my new mount code
e
s 00031/00036/00182
d D 8.2 94/01/05 01:01:50 pendry 6 5
c handle wide uid/gid.  lint, KNF
e
s 00002/00002/00216
d D 8.1 93/06/05 11:04:44 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00217
d D 5.4 92/07/12 15:55:13 bostic 4 3
c move misc file systems to miscfs
e
s 00006/00000/00212
d D 5.3 92/07/11 15:26:49 heideman 3 2
c Removed some debugging printfs
e
s 00019/00009/00193
d D 5.2 92/07/11 14:49:06 heideman 2 1
c Converted from null layer to umap layer
e
s 00202/00000/00000
d D 5.1 92/07/10 16:29:35 heideman 1 0
c date and time created 92/07/10 16:29:35 by heideman
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1992 The Regents of the University of California
 * Copyright (c) 1990, 1992 Jan-Simon Pendry
E 5
I 5
D 7
 * Copyright (c) 1992, 1993
E 7
I 7
 * Copyright (c) 1992, 1993, 1994
E 7
 *	The Regents of the University of California.  All rights reserved.
E 5
D 7
 * All rights reserved.
E 7
 *
 * This code is derived from software donated to Berkeley by
 * Jan-Simon Pendry.
 *
 * %sccs.include.redist.c%
D 7
 *
 *	%W% (Berkeley) %G%
E 7
 */

I 7
#ifndef lint
char copyright[] =
"%Z% Copyright (c) 1992, 1993, 1994\n\
	The Regents of the University of California.  All rights reserved.\n";
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 7
#include <sys/param.h>
#include <sys/mount.h>
D 2
#include <umapfs/umap_info.h>
E 2
I 2
#include <sys/stat.h>
D 7
#include <sys/types.h>
E 7
I 7

E 7
D 4
#include <umapfs/umap.h>
E 4
I 4
#include <miscfs/umapfs/umap.h>
E 4
E 2

D 7
#include <errno.h>
E 7
I 7
#include <err.h>
E 7
#include <stdio.h>
D 7
#include <unistd.h>
E 7
#include <stdlib.h>
#include <string.h>
I 7
#include <unistd.h>
E 7

D 7
void usage __P((void));
E 7
I 7
#include "mntopts.h"
E 7

#define ROOTUSER 0
D 7

I 2
/* This define controls whether any user but the superuser can own and
E 7
I 7
/*
 * This define controls whether any user but the superuser can own and
E 7
 * write mapfiles.  If other users can, system security can be gravely
 * compromised.  If this is not a concern, undefine SECURITY.
 */
D 7

E 7
#define MAPSECURITY 1

E 2
D 7
/* This routine provides the user interface to mounting a umap layer.
E 7
I 7
/*
 * This routine provides the user interface to mounting a umap layer.
E 7
 * It takes 4 mandatory parameters.  The mandatory arguments are the place 
 * where the next lower level is mounted, the place where the umap layer is to
 * be mounted, the name of the user mapfile, and the name of the group
 * mapfile.  The routine checks the ownerships and permissions on the
 * mapfiles, then opens and reads them.  Then it calls mount(), which
 * will, in turn, call the umap version of mount. 
 */

I 7
struct mntopt mopts[] = {
	MOPT_STDOPTS,
	{ NULL }
};

void	usage __P((void));

E 7
int
main(argc, argv)
	int argc;
	char *argv[];
{
D 7
	int ch, mntflags;
	int e, i, nentries, gnentries, count;
D 6
        int mapdata[MAPFILEENTRIES][2];
        int gmapdata[GMAPFILEENTRIES][2];
E 6
I 6
        u_long mapdata[MAPFILEENTRIES][2];
        u_long gmapdata[GMAPFILEENTRIES][2];
E 6
D 2
	int  flags = M_NEWTYPE;
E 2
	char *fs_type="umap";
	char *source, *target;
	char *mapfile, *gmapfile;
D 2
        struct _iobuf *fp, *gfp, *fopen();
E 2
I 2
        FILE *fp, *gfp, *fopen();
E 7
I 7
	static char not[] = "; not mounted.";
E 7
E 2
	struct stat statbuf;
D 2
	struct umap_mountargs args;
E 2
I 2
	struct umap_args args;
I 7
        FILE *fp, *gfp;
        u_long gmapdata[GMAPFILEENTRIES][2], mapdata[MAPFILEENTRIES][2];
	int ch, count, gnentries, mntflags, nentries;
	char *gmapfile, *mapfile, *source, *target, buf[20];
E 7
E 2

	mntflags = 0;
D 7
	while ((ch = getopt(argc, argv, "F:")) != EOF)
		switch(ch) {
		case 'F':
			mntflags = atoi(optarg);
E 7
I 7
	mapfile = gmapfile = NULL;
	while ((ch = getopt(argc, argv, "g:o:u:")) != EOF)
		switch (ch) {
		case 'g':
			gmapfile = optarg;
E 7
			break;
I 7
		case 'o':
D 9
			getmntopts(optarg, mopts, &mntflags);
E 9
I 9
			getmntopts(optarg, mopts, &mntflags, 0);
E 9
			break;
		case 'u':
			mapfile = optarg;
			break;
E 7
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

D 7
	if (argc != 4)
E 7
I 7
	if (argc != 2 || mapfile == NULL || gmapfile == NULL)
E 7
		usage();

D 7
	source = argv[i++];
	target = argv[i++];
	mapfile = argv[i++];
	gmapfile = argv[i++];
E 7
I 7
	source = argv[0];
	target = argv[1];
E 7

I 7
	/* Read in uid mapping data. */
	if ((fp = fopen(mapfile, "r")) == NULL)
		err(1, "%s%s", mapfile, not);

E 7
I 2
#ifdef MAPSECURITY
E 2
	/*
	 * Check that group and other don't have write permissions on
	 * this mapfile, and that the mapfile belongs to root. 
	 */
D 6
	if ( stat(mapfile, &statbuf) )
	{
		printf("mount_umap: can't stat %s\n",mapfile);
		perror("mount_umap: error status");
E 6
I 6
D 7
	if (stat(mapfile, &statbuf)) {
		fprintf(stderr, "mount_umap: can't stat %s: %s\n",
			mapfile, strerror(errno));
E 6
		notMounted();
	}

E 7
I 7
	if (fstat(fileno(fp), &statbuf))
		err(1, "%s%s", mapfile, not);
E 7
D 6
	if (statbuf.st_mode & S_IWGRP || statbuf.st_mode & S_IWOTH)
	{
		printf("mount_umap: Improper write permissions for %s, mode %x\n",
E 6
I 6
	if (statbuf.st_mode & S_IWGRP || statbuf.st_mode & S_IWOTH) {
D 7
		fprintf(stderr, "mount_umap: Improper write permissions for %s, mode %x\n",
E 6
		    mapfile, statbuf.st_mode);
		notMounted();
E 7
I 7
		strmode(statbuf.st_mode, buf);
		err(1, "%s: improper write permissions (%s)%s",
		    mapfile, buf, not);
E 7
	}
I 7
	if (statbuf.st_uid != ROOTUSER)
		errx(1, "%s does not belong to root%s", mapfile, not);
#endif /* MAPSECURITY */
E 7

D 6
	if ( statbuf.st_uid != ROOTUSER )
	{
		printf("mount_umap: %s does not belong to root\n", mapfile);
E 6
I 6
D 7
	if (statbuf.st_uid != ROOTUSER) {
		fprintf(stderr, "mount_umap: %s does not belong to root\n", mapfile);
E 6
		notMounted();
	}
I 2
#endif MAPSECURITY
E 2

	/*
	 * Read in uid mapping data.
	 */

	if ((fp = fopen(mapfile, "r")) == NULL) {
D 6
		printf("mount_umap: can't open %s\n",mapfile);
E 6
I 6
		fprintf(stderr, "mount_umap: can't open %s: %s\n",
			mapfile, strerror(errno));
E 6
		notMounted();
	}
	fscanf(fp, "%d\n", &nentries);
E 7
I 7
	if ((fscanf(fp, "%d\n", &nentries)) != 1)
		errx(1, "%s: nentries not found%s", mapfile, not);
E 7
	if (nentries > MAPFILEENTRIES)
D 6
		printf("mount_umap: nentries exceeds maximum\n");
E 6
I 6
D 7
		fprintf(stderr, "mount_umap: nentries exceeds maximum\n");
E 7
I 7
		errx(1,
		    "maximum number of entries is %d%s", MAPFILEENTRIES, not);
E 7
E 6
I 3
#if 0
E 3
D 7
	else
		printf("reading %d entries\n", nentries);
E 7
I 7
	(void)printf("reading %d entries\n", nentries);
E 7
I 3
#endif
E 3
D 7

D 6
	for(count = 0; count<nentries;count++) {
		if ((fscanf(fp, "%d %d\n", &(mapdata[count][0]),
E 6
I 6
	for(count = 0; count < nentries;count++) {
		if ((fscanf(fp, "%lu %lu\n", &(mapdata[count][0]),
E 6
		    &(mapdata[count][1]))) == EOF) {
D 6
			printf("mount_umap: %s, premature eof\n",mapfile);
E 6
I 6
			fprintf(stderr, "mount_umap: %s, premature eof\n",mapfile);
E 6
			notMounted();
E 7
I 7
	for (count = 0; count < nentries; ++count) {
		if ((fscanf(fp, "%lu %lu\n",
		    &(mapdata[count][0]), &(mapdata[count][1]))) != 2) {
			if (ferror(fp))
				err(1, "%s%s", mapfile, not);
			if (feof(fp))
				errx(1, "%s: unexpected end-of-file%s",
				    mapfile, not);
			errx(1, "%s: illegal format (line %d)%s",
			    mapfile, count + 2, not);
E 7
		}
#if 0
D 7
		/* fix a security hole */
		if (mapdata[count][1] == 0) {
D 6
			printf("mount_umap: Mapping to UID 0 not allowed\n");
E 6
I 6
			fprintf(stderr, "mount_umap: Mapping to UID 0 not allowed\n");
E 6
			notMounted();
		}
E 7
I 7
		/* Fix a security hole. */
		if (mapdata[count][1] == 0)
			errx(1, "mapping id 0 not permitted (line %d)%s",
			    count + 2, not);
E 7
#endif
	}

I 7
	/* Read in gid mapping data. */
	if ((gfp = fopen(gmapfile, "r")) == NULL)
		err(1, "%s%s", gmapfile, not);

#ifdef MAPSECURITY
E 7
	/*
	 * Check that group and other don't have write permissions on
	 * this group mapfile, and that the file belongs to root. 
	 */
D 6
	if ( stat(gmapfile, &statbuf) )
	{
		printf("mount_umap: can't stat %s\n",gmapfile);
		perror("mount_umap: error status");
E 6
I 6
D 7
	if (stat(gmapfile, &statbuf)) {
		fprintf(stderr, "mount_umap: can't stat %s: %s\n",
			gmapfile, strerror(errno));
E 6
		notMounted();
	}

E 7
I 7
	if (fstat(fileno(gfp), &statbuf))
		err(1, "%s%s", gmapfile, not);
E 7
D 6
	if (statbuf.st_mode & S_IWGRP || statbuf.st_mode & S_IWOTH)
	{
		printf("mount_umap: Improper write permissions for %s, mode %x\n",
E 6
I 6
	if (statbuf.st_mode & S_IWGRP || statbuf.st_mode & S_IWOTH) {
D 7
		fprintf(stderr, "mount_umap: Improper write permissions for %s, mode %x\n",
E 6
		    gmapfile, statbuf.st_mode);
E 7
I 7
		strmode(statbuf.st_mode, buf);
		err(1, "%s: improper write permissions (%s)%s",
		    gmapfile, buf, not);
E 7
	}
I 7
	if (statbuf.st_uid != ROOTUSER)
		errx(1, "%s does not belong to root%s", gmapfile, not);
#endif /* MAPSECURITY */
E 7

D 6
	if ( statbuf.st_uid != ROOTUSER )
	{
		printf("mount_umap: %s does not belong to root\n", mapfile);
E 6
I 6
D 7
	if (statbuf.st_uid != ROOTUSER) {
		fprintf(stderr, "mount_umap: %s does not belong to root\n", mapfile);
E 6
	}

	/*
	 * Read in gid mapping data.
	 */
	if ((gfp = fopen(gmapfile, "r")) == NULL) {
D 6
		printf("mount_umap: can't open %s\n",gmapfile);
E 6
I 6
		fprintf(stderr, "mount_umap: can't open %s\n",gmapfile);
E 6
		notMounted();
	}
	fscanf(gfp, "%d\n", &gnentries);
	if (gnentries > GMAPFILEENTRIES)
D 6
		printf("mount_umap: gnentries exceeds maximum\n");
E 6
I 6
		fprintf(stderr, "mount_umap: gnentries exceeds maximum\n");
E 7
I 7
D 8
	if ((fscanf(fp, "%d\n", &gnentries)) != 1)
E 8
I 8
	if ((fscanf(gfp, "%d\n", &gnentries)) != 1)
E 8
		errx(1, "nentries not found%s", gmapfile, not);
	if (gnentries > MAPFILEENTRIES)
		errx(1,
		    "maximum number of entries is %d%s", GMAPFILEENTRIES, not);
E 7
E 6
I 3
#if 0
E 3
D 7
	else
		printf("reading %d group entries\n", gnentries);
E 7
I 7
	(void)printf("reading %d group entries\n", gnentries);
E 7
I 3
#endif
E 3

D 6
	for(count = 0; count<gnentries;count++) {
		if ((fscanf(gfp, "%d %d\n", &(gmapdata[count][0]),
E 6
I 6
D 7
	for (count = 0; count < gnentries;count++) {
		if ((fscanf(gfp, "%lu %lu\n", &(gmapdata[count][0]),
E 6
		    &(gmapdata[count][1]))) == EOF) {
D 6
			printf("mount_umap: %s, premature eof on group mapfile\n",
E 6
I 6
			fprintf(stderr, "mount_umap: %s, premature eof on group mapfile\n",
E 6
			    gmapfile);
			notMounted();
E 7
I 7
	for (count = 0; count < gnentries; ++count)
D 8
		if ((fscanf(fp, "%lu %lu\n",
E 8
I 8
		if ((fscanf(gfp, "%lu %lu\n",
E 8
		    &(gmapdata[count][0]), &(gmapdata[count][1]))) != 2) {
D 8
			if (ferror(fp))
E 8
I 8
			if (ferror(gfp))
E 8
				err(1, "%s%s", gmapfile, not);
D 8
			if (feof(fp))
E 8
I 8
			if (feof(gfp))
E 8
				errx(1, "%s: unexpected end-of-file%s",
				    gmapfile, not);
			errx(1, "%s: illegal format (line %d)%s",
			    gmapfile, count + 2, not);
E 7
		}
D 7
	}
E 7


D 7
	/*
	 * Setup mount call args.
	 */
E 7
I 7
	/* Setup mount call args. */
E 7
D 2
	args.source = source;
E 2
I 2
	args.target = source;
E 2
	args.nentries = nentries;
D 6
	args.mapdata = &(mapdata[0][0]);
E 6
I 6
	args.mapdata = mapdata;
E 6
	args.gnentries = gnentries;
D 6
	args.gmapdata = &(gmapdata[0][0]);
E 6
I 6
	args.gmapdata = gmapdata;
E 6

I 3
D 7
#if 0
E 3
D 2
	printf("calling mount_umap(%s,%d,<%s>)\n",target,flags,
	       args.source);
E 2
I 2
D 6
	printf("calling mount_umap(%s,%d,<%s>)\n",target,mntflags,
E 6
I 6
	printf("calling mount_umap(%s,%d,<%s>)\n", target, mntflags,
E 6
	       args.target);
I 3
#endif
E 3
E 2
	if (mount(MOUNT_UMAP, argv[1], mntflags, &args)) {
		(void)fprintf(stderr, "mount_umap: %s\n", strerror(errno));
	}
E 7
I 7
D 9
	if (mount(MOUNT_UMAP, argv[1], mntflags, &args))
E 9
I 9
	if (mount("umap", argv[1], mntflags, &args))
E 9
		err(1, NULL);
E 7
	exit(0);
}

void
usage()
{
	(void)fprintf(stderr,
D 2
	    "usage: mount_umap [ -F fsoptions ] target_fs mount_point\n");
E 2
I 2
D 7
	    "usage: mount_umap [ -F fsoptions ] target_fs mount_point user_mapfile group_mapfile\n");
E 7
I 7
"usage: mount_umap [-o options] -u usermap -g groupmap target_fs mount_point\n");
E 7
E 2
	exit(1);
D 7
}

D 2
void
E 2
I 2
int
E 2
notMounted()
{
	(void)fprintf(stderr, "file system not mounted\n");
E 7
}
E 1
