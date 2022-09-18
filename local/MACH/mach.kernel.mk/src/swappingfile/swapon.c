/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */

/*
 * HISTORY
 * $Log:	swapon.c,v $
 * Revision 1.3  91/03/28  12:01:36  mbj
 * 	Don't truncate existing paging files.  Allow the pager's low water mark
 * 	code to do that when appropriate.  Tweaked "Adding %s as paging file"
 * 	message to normally fit on an 80 character line.
 * 	[91/03/28  11:59:07  mbj]
 * 
 * Revision 1.2  90/01/24  17:27:31  berman
 * 	Added code to parse new fstab fields and use for paging
 * 	directives.  Also picked up user interface for mach_swapon from
 * 	Rich Draves.  This now replaces all earlier versions of swapon.
 * 	[90/01/23            berman]
 * 
 */
#ifndef lint
char copyright[] =
"@(#) Copyright (c) 1980 Regents of the University of California.\n\
 All rights reserved.\n";
#endif not lint

#ifndef lint
static char sccsid[] = "@(#)swapon.c	5.2 (Berkeley) 3/4/86";
#endif not lint

#include <stdio.h>
#include <fstab.h>
#include <errno.h>
#if MACH
#include <sys/table.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <stdio.h>
#include <strings.h>
#include <mach/std_types.h>
#include <mach_init.h>
#include <mach_error.h>
#define PAGEFILE  	"/pagingfile"
#define PFLEN		sizeof(PAGEFILE)
#define NEWPAGER	26
#define MS_NONE		0x0000
#define MS_PREFER	0x0001		/* Prefer this file. */
#define streql(a, b)	(strcmp((a), (b)) == 0)

extern char *nxtarg();
extern kern_return_t mach_swapon();
void do_mach_swap();
vm_size_t numarg();
void mach_swap();
kern_return_t set_paging();
#endif 	/* MACH */
extern int errno;

main(argc, argv)
	int argc;
	char *argv[];
{
	int stat = 0;
#if MACH
	int cel, inclv;

	/* 
	 * Check kernel revision.   Branch around to mach_swapon if necessary 
	 */
	cel = table(TBL_INCLUDE_VERSION, 0, (char *)&inclv, 1, sizeof(int));
	if (cel && inclv >= NEWPAGER) {
		do_mach_swap(argc, argv);
		exit(0);
	}
#endif	/* MACH */

	--argc, argv++;
	if (argc == 0) {
		fprintf(stderr, "usage: swapon name...\n");
		exit(1);
	}
	if (argc == 1 && !strcmp(*argv, "-a")) {
		struct	fstab	*fsp;
		if (setfsent() == 0)
			perror(FSTAB), exit(1);
		while ( (fsp = getfsent()) != 0){
			if (strcmp(fsp->fs_type, FSTAB_SW) != 0)
				continue;
			if (swapon(fsp->fs_spec) == -1) {
				switch(errno) {
				case EINVAL:
					fprintf(stderr,
						"%s: Device not configured\n",
						fsp->fs_spec);
					stat = 1;
					break;

				case EBUSY:	/* ignore already in use */
					break;

				default:
					perror(fsp->fs_spec);
					stat = 1;
					break;
				}
			} else
				printf("Adding %s as swap device\n",
				    fsp->fs_spec);
		}
		endfsent();
		exit(stat);
	}
	do {
		if (swapon(*argv++) == -1) {
			stat = 1;
			switch (errno) {
			case EINVAL:
				fprintf(stderr, "%s: Device not configured\n",
						argv[-1]);
				break;

			case EBUSY:
				fprintf(stderr, "%s: Device already in use\n",
						argv[-1]);
				break;

			default:
				perror(argv[-1]);
				break;
			}
		}
		argc--;
	} while (argc > 0);
	exit(stat);
}

#if MACH
void do_mach_swap(argc,argv)
	int argc;
	char *argv[];
{
	unsigned int flags = MS_NONE;
	vm_size_t lowat = 0, hiwat = 0;
	kern_return_t kr;
	char filename[BUFSIZ], *opt, *p, *bdev, found_area;
	extern char _argbreak;

	if (argc == 1) {
		fprintf(stderr, "       swapon [-a]\n");
		fprintf(stderr, "       swapon [-v] [-p] [-l size] [-h size] name\n");
		exit(1);
	}
	if (argc == 2 && !strcmp(argv[1],"-a")) {
		struct	fstab	*fsp;
		if (setfsent() == 0)
			perror(FSTAB), exit(1);
		while ( (fsp = getfsent()) != 0) {
			found_area = lowat = hiwat = 0;
			flags = MS_NONE;
			bzero(filename, BUFSIZ);

			if (!fsp->fs_name || !fsp->fs_opts)
				continue;

			if (strcmp(fsp->fs_type, FSTAB_RW) == 0) {
				if (strcmp(fsp->fs_name, "ufs") == 0)
					bdev = fsp->fs_spec;
				else
					bdev = NULL;

				opt = fsp->fs_opts;
				do {
					p = nxtarg(&opt, ",");
					if (strcmp(p, "paging") == 0) {
					    found_area++;
					    strncpy(filename,
					    	    fsp->fs_file,
						    BUFSIZ-PFLEN);
					    strcat(filename, PAGEFILE);
					}
					if (strcmp(p, "pageprefer") == 0) {
					    flags |= MS_PREFER;
					}
					if (strncmp(p, "pagehiwat=",10) == 0) {
					    hiwat = numarg(p+10);
					}
					if (strncmp(p, "pagelowat=",10) == 0) {
					    lowat = numarg(p+10);
					}
				} while (*p);
			}
			if (found_area) {
				 kr = set_paging(bdev, filename,
					   	 flags, lowat, hiwat);
				if (kr != KERN_SUCCESS)
					quit(1, "mach_swapon: %s\n",
					     mach_error_string(kr));
				else
					printf("Adding %s as paging file hiwat=%d lowat=%d%s\n", filename, hiwat, lowat, flags&MS_PREFER?" preferred":"");
			}
		}
		endfsent();
	} else {
		mach_swap(argc,argv);	/* Parse arguments like mach_swapon */
	}
}

vm_size_t
numarg(arg)
    char *arg;
{
    int i, len = strlen(arg);
    vm_size_t size = 0;

    for (i = 0; i < len; i++)
    {
	char c = arg[i];

	if (('0' <= c) && (c <= '9'))
	{
	    size = 10*size + (c - '0');
	    continue;
	}

	if ((i == 0) || (i != len-1)) {
		fprintf(stderr, "       swapon [-a]\n");
		fprintf(stderr, "       swapon [-v] [-p] [-l size] [-h size] name\n");
		exit(2);
	}

	switch (c)
	{
	  case 'p': case 'P':
	    size *= vm_page_size;
	    break;
	  case 'k': case 'K':
	    size *= 1024;
	    break;
	  case 'm': case 'M':
	    size *= 1024*1024;
	    break;
	  case 'g': case 'G':
	    size *= 1024*1024*1024;
	    break;

	  default:
		fprintf(stderr, "       swapon [-a]\n");
		fprintf(stderr, "       swapon [-v] [-p] [-l size] [-h size] name\n");
		exit(2);
	}
    }
    return size;
}

/*
 * Parse the command line like the mach_swapon program.
 */
void
mach_swap(argc, argv)
    int argc;
    char *argv[];
{
    int i;
    boolean_t verbose = FALSE;
    unsigned int flags = MS_NONE;
    vm_size_t lowat, hiwat;
    char *filename;
    kern_return_t kr;

    lowat = 0;	/* allow to shrink  */
    hiwat = 0;	/* unbounded growth */

    for (i = 1; i < argc; i++)
	if (streql(argv[i], "-v"))
	    verbose = TRUE;
	else if (streql(argv[i], "-p"))
	    flags |= MS_PREFER;
	else if (streql(argv[i], "-l") && i < argc-1)
	    lowat = numarg(argv[++i]);
	else if (streql(argv[i], "-h") && i < argc-1)
	    hiwat = numarg(argv[++i]);
	else if (streql(argv[i], "--"))
	{
	    i++;
	    break;
	}
	else if (argv[i][0] == '-') {
		fprintf(stderr, "       swapon [-a]\n");
		fprintf(stderr, "       swapon [-v] [-p] [-l size] [-h size] name\n");
		exit(2);
	} else
	    break;

    if (i != argc-1) {
	fprintf(stderr, "       swapon [-a]\n");
	fprintf(stderr, "       swapon [-v] [-p] [-l size] [-h size] name\n");
	exit(2);
    }

    filename = argv[i];

    if (verbose)
	printf("mach_swapon(%s, %s, %u, %u)\n",
	       filename, (flags & MS_PREFER) ? "MS_PREFER" : "MS_NONE",
	       lowat, hiwat);

    if ((kr = set_paging(0, filename, flags, lowat, hiwat)) != KERN_SUCCESS)
	quit(1, "mach_swapon: %s\n", mach_error_string(kr));
}


/*
 * Set up paging file on given blockdev and filename.
 */
kern_return_t
set_paging(blockdev, filename, flags, lowat, hiwat)
    char *blockdev, *filename;
    unsigned int flags;
    vm_size_t lowat, hiwat;
{
	struct stat statbuf1, statbuf2;

	if (open(filename, O_CREAT, 0700) < 0) {
		perror("creat");
		return(KERN_FAILURE);
	}

	if (stat(filename, &statbuf1) < 0) {
		printf("Could not stat %s\n",filename);
		perror("stat");		
		return(KERN_FAILURE);
	}

	if (blockdev) {
		if (stat(blockdev, &statbuf2) < 0) {
			printf("Could not stat %s\n",blockdev);
			perror("stat");
			return(KERN_FAILURE);
		}

		if (statbuf1.st_dev != statbuf2.st_rdev) {
			fprintf(stderr, "swapon: %s not mounted!\n",blockdev);
			unlink(filename);
			return(KERN_FAILURE);
		}
	}
	return(mach_swapon(filename, flags, lowat, hiwat));
}
#endif	/* MACH */
