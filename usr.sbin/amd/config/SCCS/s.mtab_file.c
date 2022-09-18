h10410
s 00002/00002/00444
d D 8.1 93/06/06 11:50:58 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00033/00007/00413
d D 5.4 92/02/09 08:30:57 pendry 4 3
c merge in new release
e
s 00003/00002/00417
d D 5.3 91/05/12 15:58:49 pendry 3 2
c checkpoint for network tape
e
s 00146/00115/00273
d D 5.2 91/03/17 13:49:11 pendry 2 1
c from amd5.3 alpha11
e
s 00388/00000/00000
d D 5.1 90/06/29 12:40:59 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
/*
D 2
 * $Id: mtab_file.c,v 5.2 90/06/23 22:20:54 jsp Rel $
E 2
I 2
D 3
 * $Id: mtab_file.c,v 5.2.1.2 91/03/03 20:51:24 jsp Alpha $
E 2
 *
E 3
 * Copyright (c) 1990 Jan-Simon Pendry
 * Copyright (c) 1990 Imperial College of Science, Technology & Medicine
D 5
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
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
 * $Id: mtab_file.c,v 5.2.1.3 91/05/07 22:19:58 jsp Alpha $
E 4
I 4
 * $Id: mtab_file.c,v 5.2.2.1 1992/02/09 15:10:42 jsp beta $
E 4
 *
E 3
 */

#include "am.h"

#ifdef READ_MTAB_FROM_FILE

#ifdef USE_FCNTL
#include <fcntl.h>
#else
#include <sys/file.h>
#endif /* USE_FCNTL */

#ifdef UPDATE_MTAB

/*
 * Do strict /etc/mtab locking
 */
#define	MTAB_LOCKING

/*
 * Firewall mtab entries
 */
#define	MTAB_STRIPNL

#include <sys/stat.h>
static FILE *mnt_file;

/*
 * If the system is being trashed by something, then
 * opening mtab may fail with ENFILE.  So, go to sleep
 * for a second and try again. (Yes - this has happened to me.)
 *
 * Note that this *may* block the automounter, oh well. 
 * If we get to this state then things are badly wrong anyway...
 *
 * Give the system 10 seconds to recover but then give up.
 * Hopefully something else will exit and free up some file
 * table slots in that time.
 */
#define	NFILE_RETRIES	10 /* seconds */

#ifdef MTAB_LOCKING
#ifdef LOCK_FCNTL
static int lock(fd)
{
	int rc;
	struct flock lk;

	lk.l_type = F_WRLCK;
	lk.l_whence = 0;
	lk.l_start = 0;
	lk.l_len = 0;

again:
	rc = fcntl(fd, F_SETLKW, (caddr_t) &lk);
	if (rc < 0 && (errno == EACCES || errno == EAGAIN)) {
#ifdef DEBUG
		dlog("Blocked, trying to obtain exclusive mtab lock");
#endif /* DEBUG */
		sleep(1);
		goto again;
	}
	return rc;
}
#else
#define lock(fd) (flock((fd), LOCK_EX))
#endif /* LOCK_FCNTL */
#endif /* MTAB_LOCKING */

I 2
static FILE *open_locked_mtab(mtab_file, mode, fs)
char *mtab_file;
char *mode;
char *fs;
{
	FILE *mfp = 0;

#ifdef UPDATE_MTAB
	/*
	 * There is a possible race condition if two processes enter
	 * this routine at the same time.  One will be blocked by the
	 * exclusive lock below (or by the shared lock in setmntent)
	 * and by the time the second process has the exclusive lock
	 * it will be on the wrong underlying object.  To check for this
	 * the mtab file is stat'ed before and after all the locking
	 * sequence, and if it is a different file then we assume that
	 * it may be the wrong file (only "may", since there is another
	 * race between the initial stat and the setmntent).
	 *
	 * Simpler solutions to this problem are invited...
	 */
	int racing = 2;
#ifdef MTAB_LOCKING
	int rc;
	int retries = 0;
	struct stat st_before, st_after;
#endif /* MTAB_LOCKING */

	if (mnt_file) {
#ifdef DEBUG
		dlog("Forced close on %s in read_mtab", mtab_file);
#endif /* DEBUG */
		endmntent(mnt_file);
		mnt_file = 0;
	}

#ifdef MTAB_LOCKING
again:
	if (mfp) {
		endmntent(mfp);
		mfp = 0;
	}

	clock_valid = 0;
	if (stat(mtab_file, &st_before) < 0) {
		plog(XLOG_ERROR, "%s: stat: %m", mtab_file);
		if (errno == ESTALE) {
			/* happens occasionally */
			sleep(1);
			goto again;
		}
		return 0;
	}
#endif /* MTAB_LOCKING */
#endif /* UPDATE_MTAB */

eacces:
	mfp = setmntent(mtab_file, mode);
	if (!mfp) {
		/*
		 * Since setmntent locks the descriptor, it
		 * is possible it can fail... so retry if
		 * needed.
		 */
		if (errno == EACCES || errno == EAGAIN) {
#ifdef DEBUG
			dlog("Blocked, trying to obtain exclusive mtab lock");
#endif /* DEBUG */
			goto eacces;
		} else if (errno == ENFILE && retries++ < NFILE_RETRIES) {
			sleep(1);
			goto eacces;
		}

		plog(XLOG_ERROR, "setmntent(\"%s\", \"%s\"): %m", mtab_file, mode);
		return 0;
	}

#ifdef MTAB_LOCKING
#ifdef UPDATE_MTAB
	/*
	 * At this point we have an exclusive lock on the mount list,
	 * but it may be the wrong one so...
	 */

	/*
	 * Need to get an exclusive lock on the current
	 * mount table until we have a new copy written
	 * out, when the lock is released in free_mntlist.
	 * flock is good enough since the mount table is
	 * not shared between machines.
	 */
	do
		rc = lock(fileno(mfp));
	while (rc < 0 && errno == EINTR);
	if (rc < 0) {
		plog(XLOG_ERROR, "Couldn't lock %s: %m", mtab_file);
		endmntent(mfp);
		return 0;
	}
	/*
	 * Now check whether the mtab file has changed under our feet
	 */
	if (stat(mtab_file, &st_after) < 0) {
		plog(XLOG_ERROR, "%s: stat", mtab_file);
		goto again;
	}

	if (st_before.st_dev != st_after.st_dev ||
		st_before.st_ino != st_after.st_ino) {
			struct timeval tv;
			if (racing == 0) {
				/* Sometimes print a warning */
				plog(XLOG_WARNING,
					"Possible mount table race - retrying %s", fs);
			}
			racing = (racing+1) & 3;
			/*
			 * Take a nap.  From: Doug Kingston <dpk@morgan.com>
			 */
			tv.tv_sec = 0;
			tv.tv_usec = (mypid & 0x07) << 17;
			if (tv.tv_usec)
				if (select(0, (voidp) 0, (voidp) 0, (voidp) 0, &tv) < 0)
					plog(XLOG_WARNING, "mtab nap failed: %m");

			goto again;
	}
#endif /* UPDATE_MTAB */
#endif /* MTAB_LOCKING */

	return mfp;
}

E 2
/*
 * Unlock the mount table
 */
I 2
void unlock_mntlist P((void));
E 2
void unlock_mntlist()
{
	/*
	 * Release file lock, by closing the file
	 */
	if (mnt_file) {
		endmntent(mnt_file);
		mnt_file = 0;
	}
}

/*
 * Write out a mount list
 */
void rewrite_mtab(mp)
mntlist *mp;
{
	FILE *mfp;
I 4
	int error = 0;
E 4

	/*
	 * Concoct a temporary name in the same
	 * directory as the target mount table
	 * so that rename() will work.
	 */
	char tmpname[64];
	int retries;
	int tmpfd;
	char *cp;
	char *mcp = mtab;
	cp = strrchr(mcp, '/');
	if (cp) {
		bcopy(mcp, tmpname, cp - mcp);
		tmpname[cp-mcp] = '\0';
	} else {
		plog(XLOG_WARNING, "No '/' in mtab (%s), using \".\" as tmp directory", mtab);
		tmpname[0] = '.'; tmpname[1] = '\0';
	}
	strcat(tmpname, "/mtabXXXXXX");
	mktemp(tmpname);
	retries = 0;
enfile1:
	if ((tmpfd = open(tmpname, O_RDWR|O_CREAT|O_TRUNC, 0644)) < 0) {
		if (errno == ENFILE && retries++ < NFILE_RETRIES) {
			sleep(1);
			goto enfile1;
		}
		plog(XLOG_ERROR, "%s: open: %m", tmpname);
		return;
	}
	if (close(tmpfd) < 0)
		plog(XLOG_ERROR, "Couldn't close tmp file descriptor: %m");

	retries = 0;
enfile2:
	mfp = setmntent(tmpname, "w");
	if (!mfp) {
		if (errno == ENFILE && retries++ < NFILE_RETRIES) {
			sleep(1);
			goto enfile2;
		}
		plog(XLOG_ERROR, "setmntent(\"%s\", \"w\"): %m", tmpname);
D 4
		return;
E 4
I 4
		error = 1;
		goto out;
E 4
	}

	while (mp) {
D 4
		if (mp->mnt)
			if (addmntent(mfp, mp->mnt))
E 4
I 4
		if (mp->mnt) {
			if (addmntent(mfp, mp->mnt)) {
E 4
				plog(XLOG_ERROR, "Can't write entry to %s", tmpname);
I 4
				error = 1;
				goto out;
			}
		}
E 4
		mp = mp->mnext;
	}

D 4
	endmntent(mfp);
E 4
I 4
	/*
	 * SunOS 4.1 manuals say that the return code from entmntent()
	 * is always 1 and to treat as a void.  That means we need to
	 * call fflush() to make sure the new mtab file got written.
	 */
	if (fflush(mfp)) {
		plog(XLOG_ERROR, "flush new mtab file: %m");
		error = 1;
		goto out;
	}
E 4

I 4
	(void) endmntent(mfp);

E 4
	/*
	 * Rename temporary mtab to real mtab
	 */
D 4
	if (rename(tmpname, mtab) < 0)
E 4
I 4
	if (rename(tmpname, mtab) < 0) {
E 4
		plog(XLOG_ERROR, "rename %s to %s: %m", tmpname, mtab);
I 4
		error = 1;
		goto out;
	}

out:
	if (error)
		(void) unlink(tmpname);
E 4
}

#ifdef MTAB_STRIPNL
static void mtab_stripnl(s)
char *s;
{
	do {
		s = strchr(s, '\n');
		if (s)
			*s++ = ' ';
	} while (s);
}
#endif /* MTAB_STRIPNL */

/*
 * Append a mntent structure to the
 * current mount table.
 */
void write_mntent(mp)
struct mntent *mp;
{
	int retries = 0;
	FILE *mfp;
enfile:
D 2
	mfp = setmntent(mtab, "a");
E 2
I 2
	mfp = open_locked_mtab(mtab, "a", mp->mnt_dir);
E 2
	if (mfp) {
#ifdef MTAB_STRIPNL
		mtab_stripnl(mp->mnt_opts);
#endif /* MTAB_STRIPNL */
		if (addmntent(mfp, mp))
			plog(XLOG_ERROR, "Couldn't write %s: %m", mtab);
D 4
		endmntent(mfp);
E 4
I 4
		if (fflush(mfp))
			plog(XLOG_ERROR, "Couldn't flush %s: %m", mtab);
		(void) endmntent(mfp);
E 4
	} else {
		if (errno == ENFILE && retries < NFILE_RETRIES) {
			sleep(1);
			goto enfile;
		}
		plog(XLOG_ERROR, "setmntent(\"%s\", \"a\"): %m", mtab);
	}
}

#endif /* UPDATE_MTAB */

static struct mntent *mnt_dup(mp)
struct mntent *mp;
{
	struct mntent *new_mp = ALLOC(mntent);

	new_mp->mnt_fsname = strdup(mp->mnt_fsname);
	new_mp->mnt_dir = strdup(mp->mnt_dir);
	new_mp->mnt_type = strdup(mp->mnt_type);
	new_mp->mnt_opts = strdup(mp->mnt_opts);

	new_mp->mnt_freq = mp->mnt_freq;
	new_mp->mnt_passno = mp->mnt_passno;

I 2
#ifdef FIXUP_MNTENT_DUP
	/*
	 * Additional fields get dup'ed here
	 */
	FIXUP_MNTENT_DUP(new_mp, mp);
#endif

E 2
	return new_mp;
}

/*
 * Read a mount table into memory
 */
mntlist *read_mtab(fs)
char *fs;
{
	mntlist **mpp, *mhp;

	struct mntent *mep;
D 2
	FILE *mfp = 0;
E 2
I 2
	FILE *mfp = open_locked_mtab(mtab, "r+", fs);
E 2

D 2
#ifdef UPDATE_MTAB
	/*
	 * There is a possible race condition if two processes enter
	 * this routine at the same time.  One will be blocked by the
	 * exclusive lock below (or by the shared lock in setmntent)
	 * and by the time the second process has the exclusive lock
	 * it will be on the wrong underlying object.  To check for this
	 * the mtab file is stat'ed before and after all the locking
	 * sequence, and if it is a different file then we assume that
	 * it may be the wrong file (only "may", since there is another
	 * race between the initial stat and the setmntent).
	 *
	 * Simpler solutions to this problem are invited...
	 */
	int racing = 0;
#ifdef MTAB_LOCKING
	int rc;
	int retries = 0;
	struct stat st_before, st_after;
#endif /* MTAB_LOCKING */

	if (mnt_file) {
#ifdef DEBUG
		dlog("Forced close on %s in read_mtab", mtab);
#endif /* DEBUG */
		endmntent(mnt_file);
		mnt_file = 0;
	}

#ifdef MTAB_LOCKING
again:
	if (mfp) {
		endmntent(mfp);
		mfp = 0;
	}

	clock_valid = 0;
	if (stat(mtab, &st_before) < 0) {
		plog(XLOG_ERROR, "%s: stat: %m", mtab);
		if (errno == ESTALE) {
			/* happens occasionally */
			sleep(1);
			goto again;
		}
E 2
I 2
	if (!mfp)
E 2
		return 0;
D 2
	}
#endif /* MTAB_LOCKING */
#endif /* UPDATE_MTAB */

eacces:
	mfp = setmntent(mtab, "r+");
	if (!mfp) {
		/*
		 * Since setmntent locks the descriptor, it
		 * is possible it can fail... so retry if
		 * needed.
		 */
		if (errno == EACCES || errno == EAGAIN) {
#ifdef DEBUG
			dlog("Blocked, trying to obtain exclusive mtab lock");
#endif /* DEBUG */
			goto eacces;
		} else if (errno == ENFILE && retries++ < NFILE_RETRIES) {
			sleep(1);
			goto eacces;
		}

		plog(XLOG_ERROR, "setmntent(\"%s\", \"r+\"): %m", mtab);
		return 0;
	}

#ifdef MTAB_LOCKING
#ifdef UPDATE_MTAB
	/*
	 * At this point we have an exclusive lock on the mount list,
	 * but it may be the wrong one so...
	 */

	/*
	 * Need to get an exclusive lock on the current
	 * mount table until we have a new copy written
	 * out, when the lock is released in free_mntlist.
	 * flock is good enough since the mount table is
	 * not shared between machines.
	 */
	do
		rc = lock(fileno(mfp));
	while (rc < 0 && errno == EINTR);
	if (rc < 0) {
		plog(XLOG_ERROR, "Couldn't lock %s: %m", mtab);
		endmntent(mfp);
		return 0;
	}
	/*
	 * Now check whether the mtab file has changed under our feet
	 */
	if (stat(mtab, &st_after) < 0) {
		plog(XLOG_ERROR, "%s: stat", mtab);
		goto again;
	}

	if (st_before.st_dev != st_after.st_dev ||
		st_before.st_ino != st_after.st_ino) {
			if (racing == 0) {
				/* Sometimes print a warning */
				plog(XLOG_WARNING,
					"Possible mount table race - retrying %s", fs);
			}
			racing = (racing+1) & 3;
			goto again;
	}
#endif /* UPDATE_MTAB */
#endif /* MTAB_LOCKING */
E 2

	mpp = &mhp;

/*
 * XXX - In SunOS 4 there is (yet another) memory leak
 * which loses 1K the first time getmntent is called.
 * (jsp)
 */
	while (mep = getmntent(mfp)) {
		/*
		 * Allocate a new slot
		 */
		*mpp = ALLOC(mntlist);

		/*
		 * Copy the data returned by getmntent
		 */
		(*mpp)->mnt = mnt_dup(mep);

		/*
		 * Move to next pointer
		 */
		mpp = &(*mpp)->mnext;
	}
	*mpp = 0;

#ifdef UPDATE_MTAB
	/*
	 * If we are not updating the mount table then we
	 * can free the resources held here, otherwise they
	 * must be held until the mount table update is complete
	 */
	mnt_file = mfp;
#else
	endmntent(mfp);
#endif /* UPDATE_MTAB */

	return mhp;
}

#endif /* READ_MTAB_FROM_FILE */
E 1
