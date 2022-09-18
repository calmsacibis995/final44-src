h28548
s 00002/00002/00245
d D 8.1 93/06/06 11:40:35 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00245
d D 5.5 92/05/31 10:42:22 pendry 5 4
c code refresh
e
s 00001/00001/00246
d D 5.4 92/02/09 08:48:36 pendry 4 3
c merge in new release
e
s 00003/00002/00244
d D 5.3 91/05/12 15:55:52 pendry 3 2
c checkpoint for network tape
e
s 00025/00143/00221
d D 5.2 91/03/17 13:33:36 pendry 2 1
c from amd5.3 alpha11
e
s 00364/00000/00000
d D 5.1 90/06/29 12:01:10 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
/*
D 2
 * $Id: mount_fs.c,v 5.2 90/06/23 22:19:42 jsp Rel $
E 2
I 2
D 3
 * $Id: mount_fs.c,v 5.2.1.3 91/03/03 20:43:32 jsp Alpha $
E 2
 *
E 3
 * Copyright (c) 1990 Jan-Simon Pendry
 * Copyright (c) 1990 Imperial College of Science, Technology & Medicine
D 6
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
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
 * $Id: mount_fs.c,v 5.2.1.4 91/05/07 22:18:13 jsp Alpha $
E 4
I 4
D 5
 * $Id: mount_fs.c,v 5.2.2.1 1992/02/09 15:08:43 jsp beta $
E 5
I 5
 * $Id: mount_fs.c,v 5.2.2.2 1992/05/31 16:35:45 jsp Exp $
E 5
E 4
 *
E 3
 */

#include "am.h"
#ifdef NFS_3
typedef nfs_fh fhandle_t;
#endif /* NFS_3 */
#include <sys/mount.h>

D 2
/*
 * System Vr4 / SunOS 4.1 compatibility
 * - put dev= in the options list
 *
 * From: Brent Callaghan <brent@eng.sun.com>
 */
#define	MNTINFO_DEV	"dev"
E 2
#include <sys/stat.h>

/*
 * Standard mount flags
 */
#ifdef hpux
/*
 * HP-UX has an annoying feature of printing
 * error msgs on /dev/console
 */
#undef M_NOSUID
#endif /* hpux */

struct opt_tab mnt_flags[] = {
	{ "ro", M_RDONLY },
#ifdef M_CACHE
	{ "nocache", M_NOCACHE },
#endif /* M_CACHE */
#ifdef M_GRPID
	{ "grpid", M_GRPID },
#endif /* M_GRPID */
#ifdef M_MULTI
	{ "multi", M_MULTI },
#endif /* M_MULTI */
#ifdef M_NODEV
	{ "nodev", M_NODEV },
#endif /* M_NODEV */
#ifdef M_NOEXEC
	{ "noexec", M_NOEXEC },
#endif /* M_NOEXEC */
#ifdef M_NOSUB
	{ "nosub", M_NOSUB },
#endif /* M_NOSUB */
#ifdef M_NOSUID
	{ "nosuid", M_NOSUID },
#endif /* M_NOSUID */
#ifdef M_SYNC
	{ "sync", M_SYNC },
#endif /* M_SYNC */
	{ 0, 0 }
};

int compute_mount_flags(mnt)
struct mntent *mnt;
{
	struct opt_tab *opt;
	int flags;
#ifdef NFS_4
	flags = M_NEWTYPE;
#else
	flags = 0;
#endif /* NFS_4 */

	/*
	 * Crack basic mount options
	 */
	for (opt = mnt_flags; opt->opt; opt++)
		flags |= hasmntopt(mnt, opt->opt) ? opt->flag : 0;

	return flags;
}

I 2
int mount_fs P((struct mntent *mnt, int flags, caddr_t mnt_data, int retry, MTYPE_TYPE type));
E 2
int mount_fs(mnt, flags, mnt_data, retry, type)
struct mntent *mnt;
int flags;
caddr_t mnt_data;
int retry;
MTYPE_TYPE type;
{
	int error = 0;
D 2
	int automount = 0;
E 2
#ifdef MNTINFO_DEV
	struct stat stb;
	char *xopts = 0;
#endif /* MNTINFO_DEV */

#ifdef DEBUG
#ifdef NFS_4
	dlog("%s fstype %s (%s) flags %#x (%s)",
		mnt->mnt_dir, type, mnt->mnt_type, flags, mnt->mnt_opts);
#else
	dlog("%s fstype %d (%s) flags %#x (%s)",
		mnt->mnt_dir, type, mnt->mnt_type, flags, mnt->mnt_opts);
#endif /* NFS_4 */
#endif /* DEBUG */

	/*
	 * Fake some mount table entries for the automounter
	 */
I 2
#ifdef FASCIST_DF_COMMAND
	/*
	 * Some systems have a df command which blows up when
	 * presented with an unknown mount type.
	 */
E 2
	if (STREQ(mnt->mnt_type, MNTTYPE_AUTO)) {
D 2
		automount = 1;
		mnt->mnt_fsname = pid_fsname;
E 2
		/*
		 * Try it with the normal name
		 */
D 2
#ifdef notdef
		/*
		 * This is notdef'ed because some systems use
		 * the mount table in getwd() (esp. SunOS4) and
		 * if all the mount points are not marked it can
		 * cause major confusion.  This can probably
		 * be changed when no-one is running SunOS 4.0
		 * any more.
		 */
		mnt->mnt_type = MNTTYPE_IGNORE;
#endif /* notdef */
E 2
D 5
		mnt->mnt_type = MNTTYPE_NFS;
E 5
I 5
		mnt->mnt_type = FASCIST_DF_COMMAND;
E 5
D 2
		/*
		 * Background the mount, so that the stat of the
		 * mountpoint is done in a background process.
		 */
		if (background())
			return 0;
E 2
	}
I 2
#endif /* FASCIST_DF_COMMAND */
E 2

again:
	clock_valid = 0;
	error = MOUNT_TRAP(type, mnt, flags, mnt_data);
	if (error < 0)
		plog(XLOG_ERROR, "%s: mount: %m", mnt->mnt_dir);
	if (error < 0 && --retry > 0) {
		sleep(1);
		goto again;
	}
	if (error < 0) {
I 2
#ifdef notdef
E 2
		if (automount)
			going_down(errno);
I 2
#endif
E 2
		return errno;
	}

#ifdef UPDATE_MTAB
#ifdef MNTINFO_DEV
	/*
	 * Add the extra dev= field to the mount table.
	 */
	if (lstat(mnt->mnt_dir, &stb) == 0) {
		char *zopts = (char *) xmalloc(strlen(mnt->mnt_opts) + 32);
		xopts = mnt->mnt_opts;
		if (sizeof(stb.st_dev) == 2) {
D 2
			/* SunOS 4.1 */
			sprintf(zopts, "%s,%s=%04lx", xopts, MNTINFO_DEV,
					(u_long) stb.st_dev & 0xffff);
E 2
I 2
			/* e.g. SunOS 4.1 */
			sprintf(zopts, "%s,%s=%s%04lx", xopts, MNTINFO_DEV,
					MNTINFO_PREF, (u_long) stb.st_dev & 0xffff);
E 2
		} else {
D 2
			/* System Vr4 */
			sprintf(zopts, "%s,%s=%08lx", xopts, MNTINFO_DEV,
					(u_long) stb.st_dev);
E 2
I 2
			/* e.g. System Vr4 */
			sprintf(zopts, "%s,%s=%s%08lx", xopts, MNTINFO_DEV,
					MNTINFO_PREF, (u_long) stb.st_dev);
E 2
		}
		mnt->mnt_opts = zopts;
	}
#endif /* MNTINFO_DEV */

D 2
#ifdef hpux
E 2
I 2
#ifdef FIXUP_MNTENT
E 2
	/*
D 2
	 * Yet another gratuitously incompatible change in HP-UX
E 2
I 2
	 * Additional fields in struct mntent
	 * are fixed up here
E 2
	 */
D 2
	mnt->mnt_time = clocktime();
#endif /* hpux */
E 2
I 2
	FIXUP_MNTENT(mnt);
#endif

E 2
	write_mntent(mnt);
#ifdef MNTINFO_DEV
	if (xopts) {
		free(mnt->mnt_opts);
		mnt->mnt_opts = xopts;
	}
#endif /* MNTINFO_DEV */
#endif /* UPDATE_MTAB */

D 2
	/*
	 * Needed this way since mnt may contain a pointer
	 * to a local variable in this stack frame.
	 */
	if (automount)
		going_down(0);
E 2
	return 0;
}

#ifdef NEED_MNTOPT_PARSER
/*
 * Some systems don't provide these to the user,
 * but amd needs them, so...
 *
 * From: Piete Brooks <pb@cl.cam.ac.uk>
 */

#include <ctype.h>

static char *nextmntopt(p)
char **p;
{
	char *cp = *p;
	char *rp;
	/*
	 * Skip past white space
	 */
	while (*cp && isspace(*cp))
		cp++;
	/*
	 * Word starts here
	 */
	rp = cp;
	/*
	 * Scan to send of string or separator
	 */
	while (*cp && *cp != ',')
		cp++;
	/*
	 * If separator found the overwrite with nul char.
	 */
	if (*cp) {
		*cp = '\0';
		cp++;
	}
	/*
	 * Return value for next call
	 */
	*p = cp;
	return rp;
}

char *hasmntopt(mnt, opt)
struct mntent *mnt;
char *opt;
{
	char t[MNTMAXSTR];
	char *f;
	char *o = t;
	int l = strlen(opt);
	strcpy(t, mnt->mnt_opts);

	while (*(f = nextmntopt(&o)))
		if (strncmp(opt, f, l) == 0)
			return f - t + mnt->mnt_opts;

	return 0;
}
#endif /* NEED_MNTOPT_PARSER */

D 2
#ifdef MOUNT_AIX3

#include "aix3-nfs.h"

static int aix3_mkvp(p, gfstype, flags, object, stub, host, info, info_size, args)
char *p;
int gfstype;
int flags;
char *object;
char *stub;
char *host;
char *info;
int info_size;
char *args;
{
	struct vmount *vp = (struct vmount *) p;
	bzero((voidp) vp, sizeof(*vp));
	/*
	 * Fill in standard fields
	 */
	vp->vmt_revision = VMT_REVISION;
	vp->vmt_flags = flags;
	vp->vmt_gfstype = gfstype;

#define	VMT_ROUNDUP(len) (4 * ((len + 3) / 4))
#define VMT_ASSIGN(vp, idx, data, size) \
	vp->vmt_data[idx].vmt_off = p - (char *) vp; \
	vp->vmt_data[idx].vmt_size = size; \
	bcopy(data, p, size); \
	p += VMT_ROUNDUP(size);

	/*
	 * Fill in all variable length data
	 */
	p += sizeof(*vp);

	VMT_ASSIGN(vp, VMT_OBJECT, object, strlen(object) + 1);
	VMT_ASSIGN(vp, VMT_STUB, stub, strlen(stub) + 1);
	VMT_ASSIGN(vp, VMT_HOST, host, strlen(host) + 1);
	VMT_ASSIGN(vp, VMT_HOSTNAME, host, strlen(host) + 1);
	VMT_ASSIGN(vp, VMT_INFO, info, info_size);
	VMT_ASSIGN(vp, VMT_ARGS, args, strlen(args) + 1);

#undef VMT_ASSIGN
#undef VMT_ROUNDUP

	/*
	 * Return length
	 */
	return vp->vmt_length = p - (char *) vp;
}

/*
 * Map from conventional mount arguments
 * to AIX 3-style arguments.
 */
aix3_mount(fsname, dir, flags, type, data, args)
char *fsname;
char *dir;
int flags;
int type;
void *data;
char *args;
{
	char buf[4096];
	int size;

#ifdef DEBUG
	dlog("aix3_mount: fsname %s, dir %s, type %d", fsname, dir, type);
#endif /* DEBUG */

/* aix3_mkvp(p, gfstype, flags, object, stub, host, info, info_size, args) */

	switch (type) {

	case MOUNT_TYPE_NFS: {
		char *host = strdup(fsname);
		char *rfs = strchr(host, ':');
		*rfs++ = '\0';

		size = aix3_mkvp(buf, type, flags, rfs, dir, host, data, sizeof(struct nfs_args), args);
		free(host);

		} break;

	case MOUNT_TYPE_UFS:
		/* Need to open block device and extract log device info from sblk. */
		return EINVAL;

	default:
		return EINVAL;
	}
#ifdef DEBUG
	/*dlog("aix3_mkvp: flags %#x, size %d, args %s", flags, size, args);*/
#endif /* DEBUG */

	return vmount(buf, size);
}
#endif /* MOUNT_AIX3 */
E 2
I 2
#ifdef MOUNT_HELPER_SOURCE
#include MOUNT_HELPER_SOURCE
#endif /* MOUNT_HELPER_SOURCE */
E 2
E 1
