/*-
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
 * Copyright (c) 1994 Harvard University
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef lint
static char copyright[] =
"@(#) Copyright (c) 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
#endif /* not lint */

#ifndef lint
static char sccsid[] = "@(#)mount_lffs.c	8.1 (Berkeley) 6/8/93";
#endif /* not lint */

#include <sys/param.h>
#include <sys/mount.h>
#include <sys/wait.h>

#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "pathnames.h"

#define DEFAULT_ROOTUID -2	/* copied from mount's UFS code */

void usage __P((void));
int mountlog __P((char *, char *, char *, char *, char **));

int debug;
int verbose;

int
main(argc, argv, envp)
	int argc;
	char *argv[];
	char *envp[];
{
	struct ufs_args args;
	caddr_t argp;
	int ch, mntflags;
	int noclean;
	char *fs_name;
	char *log_fs;
	char *log_device;
	char *mnt_chflags;

	debug = 0;
	verbose = 0;
	mntflags = 0;
	log_fs = NULL;
	mnt_chflags = NULL;
	while ((ch = getopt(argc, argv, "dvD:F:L:")) != EOF)
		switch(ch) {
		case 'd':
			debug = 1;
			break;
		case 'v':
			verbose = 1;
			break;
		case 'D':
			log_device = optarg;
			break;
		case 'F':
			mntflags = atoi(optarg);
			mnt_chflags = optarg;
			break;
		case 'L': /* Name of logging partition */
			log_fs = optarg;
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (argc != 2)
		usage();

        args.fspec = argv[0];	/* the name of the device file */
	fs_name = argv[1];	/* the mount point */

	/* First, mount the FFS part Read only */
	/* This part is copied from UFS mount code. */
	args.log_fs = NULL;
	args.export.ex_root = DEFAULT_ROOTUID;
	if (mntflags & MNT_RDONLY)
		args.export.ex_flags = MNT_EXRDONLY;
	else
		args.export.ex_flags = 0;

	argp = (caddr_t)&args;

	/* This mount MUST be readonly */
	if (verbose)
		fprintf(stderr, "About to mount FFS %s readonly on %s\n",
		    args.fspec, fs_name);
	if (!debug && mount(MOUNT_UFS, fs_name, mntflags | MNT_RDONLY, argp)) {
		(void) fprintf(stderr, "mount_lffs: %s on %s: ",
		    args.fspec, fs_name);
		switch (errno) {
		case EMFILE:
			(void) fprintf(stderr,
			    "mount_lffs: Mount table full\n");
			break;
		case EINVAL:
			if (mntflags & MNT_UPDATE)
				(void) fprintf(stderr,
				    "mount_lffs: Specified device %s\n",
				    "does not match mounted device");
			else
				perror((char *)NULL);
			break;
		default:
			perror((char *)NULL);
			break;
		}
		exit(1);
	}
	if (verbose)
		fprintf(stderr, "mount_lffs: FFS mounted readonly\n");

	/* Now, mount the wafs */
	if (verbose)
		fprintf(stderr, "mount_lffs: About to mount log\n");

	if (!debug)
		if (mountlog(log_device, log_fs, fs_name, mnt_chflags, envp)) {
			if (verbose)
				fprintf(stderr, "mount_lffs: unmount %s\n",
				    fs_name);
			if (unmount(fs_name, MNT_FORCE))
				perror("mount_lffs/unmount");
			exit(1);
		}

	/* Now, update the FFS to read/write with an associated log */
	
	args.log_fs = log_fs;
	mntflags &= ~MNT_RDONLY;
	mntflags |= MNT_UPDATE;
	if (verbose)
		fprintf(stderr, "About to update ffs\n");
	if (!debug && mount(MOUNT_UFS, fs_name, mntflags, &args)) {
		(void)fprintf(stderr, "mount_lffs: %s\n", strerror(errno));
		unmount(fs_name, MNT_FORCE);
		unmount(log_fs, MNT_FORCE);
		exit(1);
	}

	exit(0);
}

int
mountlog(logdevice, logname, fsname, flags, envp)
	char *logdevice;
	char *logname;
	char *fsname;
	char *flags;
	char *envp[];
{
	pid_t pid;
	int status;
	char execname[MAXPATHLEN + 1];
	char **cp;
	char *argv[50];
	int argc;

	if (verbose)
		fprintf(stderr, "mount_lffs: entering mountlog\n");

	if (logdevice == NULL || logname == NULL)
		return(1);

	if (verbose)
		fprintf(stderr, "mount_lffs: mounting %s on %s\n",
		    logdevice, logname);
	argc = 0;
	sprintf(execname, "%s/mount_wafs", _PATH_EXECDIR);
	argv[argc++] = execname;
	argv[argc++] = "-f";
	argv[argc++] = fsname;
	if (flags)
		argv[argc++] = flags;
	argv[argc++] = logdevice;
	argv[argc++] = logname;
	argv[argc++] = NULL;
	if (verbose) {
		for (cp = argv; *cp != NULL; cp++)
			fprintf(stderr, "%s ", *cp);
		fprintf(stderr, "\n");
	}
	if (pid = vfork()) {
		if (pid == -1) {
			perror("mount_lffs: vfork starting file system");
			return (1);
		}
		if (waitpid(pid, (int *)&status, 0) != -1 &&
		    WIFEXITED(status) &&
		    WEXITSTATUS(status) != 0)
			return (WEXITSTATUS(status));
		return(0);
	}
	execve(execname, argv, envp);
	(void) fprintf(stderr, "mount_lffs: cannot exec %s for %s: ",
		execname, fsname);
	perror((char *)NULL);
	return(0);
}

void
usage()
{
	(void)fprintf(stderr,
	    "usage: mount_lffs [-D logdevice] [-L logpartition ] [ -F fsoptions ] device mount_point\n");
	exit(1);
}
