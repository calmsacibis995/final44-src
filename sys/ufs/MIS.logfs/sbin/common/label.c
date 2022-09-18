/*
 * Copyright (c) 1994
 * 	The Preident and Fellows of Harvard University
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
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
 * $Id: label.c,v 1.1 1994/10/04 19:58:13 margo Exp margo $
 */

static char rcsid[] = "$Id: label.c,v 1.1 1994/10/04 19:58:13 margo Exp margo $";
#include <sys/types.h>
#include <sys/ioctl.h>
#ifdef AIX
#include <sys/devinfo.h>
#include "sys/bsd_param.h"
#include "sys/disklabel.h"
#include "ufs/ffs/fs.h"
#else
#include <sys/param.h>
#include <sys/disklabel.h>
#include <ufs/ffs/fs.h>
#endif
#include <errno.h>
#include <stdio.h>
#include <syslog.h>
#include <fcntl.h>
#include <unistd.h>

#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif


#ifdef COMPAT
char lmsg[] = "%s: can't read disk label; disk type must be specified";
#else
char lmsg[] = "%s: can't read disk label";
#endif

extern char * progname;
extern int disktype, unlabeled;

void fatal();

struct disklabel *
getdisklabel(s, fd)
	char *s;
	int fd;
{
	static struct disklabel lab;

#ifdef AIX
	if (ioctl_emul(fd, DIOCGDINFO, (char *)&lab) < 0) {
#else
	if (ioctl(fd, DIOCGDINFO, (char *)&lab) < 0) {
#endif
#ifdef AIX
		int	rc;
		rc = getlvinfo(fd, &lab);
		if (rc == 0) { return(&lab); }
#endif
#ifdef COMPAT
		if (disktype) {
			struct disklabel *lp, *getdiskbyname();

			unlabeled++;
			lp = getdiskbyname(disktype);
			if (lp == NULL)
				fatal("%s: unknown disk type", disktype);
			return (lp);
		}
#endif
		warn("ioctl (GDINFO)");
		fatal(lmsg, s);
	}
	return (&lab);
}


#ifdef AIX

char label_buf[DEV_BSIZE];

int
ioctl_emul(fd, cmd, labp)
	int fd;
	int cmd;
	char *labp;
{
	int rc;

	switch (cmd) {
	case DIOCGDINFO: rc = diocgdinfo(fd, labp);
			break;

	default: 	fprintf(stderr,"ioctl_emul: unsupp ioctl\n");
			rc = -1;
			break;
	}
	return(rc);
}


#define AIXLABELOFF	((LABELSECTOR * DEV_BSIZE) + AIXRESVSIZE)

int
diocgdinfo(fd, labp) 
	int fd;
	char *labp;
{
	int rc;
	int size = sizeof(struct disklabel);

	rc = lseek(fd, AIXLABELOFF, SEEK_SET);
	if (rc < 0) {
		(void)fprintf(stderr,
		    "%s: lseek %s\n", progname, strerror(errno));
		fatal("bad special file seek\n");
	}
	rc = read(fd, &label_buf[0], DEV_BSIZE);
	if (rc <= 0) {
		(void)fprintf(stderr,
		    "%s: lseek %s\n", progname, strerror(errno));
		fatal("bad special file read\n");
	}
	bcopy( &label_buf[LABELOFFSET], labp, size);

	if (((struct disklabel *)labp)->d_magic != DISKMAGIC)
		return(-1);
	else
		return(0);
}		

int
getlvinfo(fd, lp)
int fd;
struct disklabel * lp;
{
	struct devinfo di;
	int rc;

	/* do ioctl to see if this is a logical volume */
	rc = ioctl(fd, IOCINFO, &di);
	if (rc == 0) {
		if ((di.devtype == DD_DISK) && (di.devsubtype == DS_LV)) {
		    /* This is a logical volume.  Fill in appropriate info in
		    ** disklabel.
		    */
			bzero(lp, sizeof(*lp));
			lp->d_magic = DISKMAGIC;
			lp->d_type = DTYPE_LV; /* STUB: must define somewhere */
			lp->d_subtype = 0; /* STUB: mtr says use for size of PP */
			strcpy(lp->d_typename, "lv");
			lp->d_packname[0] = '\0';
			lp->d_secsize =  di.un.dk.bytpsec; /* bytes/sector */
			lp->d_nsectors = 1; /* sectors per track */
			lp->d_ntracks = di.un.dk.secptrk; /* tracks/cylinder */
			lp->d_ncylinders = di.un.dk.trkpcyl; /* cyls/c.g. */
			lp->d_secpercyl = lp->d_nsectors * lp->d_ntracks;
			lp->d_secperunit = di.un.dk.numblks;
			
			/*
			 * We define one partition which is the whole LV.
			 * However, we use the third slot in the array, so
			 * we can assume that we are using the "c" partition.
			 */
			lp->d_npartitions = 3;
			lp->d_bbsize = BBSIZE;
			lp->d_sbsize = SBSIZE;
			lp->d_partitions['c' - 'a'].p_size = lp->d_secperunit;
			lp->d_partitions['c' - 'a'].p_offset = 0;
			lp->d_partitions['c' - 'a'].p_fsize = lp->d_secsize;
							/* STUB: is this ok? */
			lp->d_partitions['c' - 'a'].p_fstype = FS_BSDFFS;
			lp->d_partitions['c' - 'a'].p_frag = MAXFRAG;
			lp->d_partitions['c' - 'a'].p_cpg = lp->d_ncylinders;
		}
		else { rc = -1; }
	}
	return(rc);
}
#endif /* AIX */
