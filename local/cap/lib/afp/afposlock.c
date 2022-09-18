/*
 *  Author: cck    Date: 88/03/28 17:25:35  
 *  Header: afposlock.c,v 1.13 88/03/28 17:25:35 cck Rel  
 *  Revision: 1.13  
*/

/*
 * afposlock.c - Appletalk Filing Protocol OS Interface for Byte Range Lock
 * and other file lock routines
 *
 * Three cases: (a) have flock, (b) have lockf, and have (c) lockf and flock
 * For A: can't do byte range lock
 * For B: can't lock out writers on read-only files
 * For C: just right
 *
 * AppleTalk package for UNIX (4.2 BSD).
 *
 * Copyright (c) 1986, 1987, 1988 by The Trustees of Columbia University in the
 * City of New York.
 *
 * Edit History:
 *
 *  July 1987     CCKim	Created.
 *
*/
#ifndef NOLOCKF
/* on convex, lockf requires fcntl.h */
# ifndef LOCKFUSESFCNTL
#  include <unistd.h>
   /* unistd defines these unnecessarily (and problematically) */
#  ifdef ultrix
#   undef R_OK
#   undef W_OK
#   undef X_OK
#   undef F_OK
#  endif
#  ifdef pyr
#   undef R_OK
#   undef W_OK
#   undef X_OK
#   undef F_OK
#  endif
# else
#  include <fcntl.h>
# endif
#endif
#include <errno.h>
#include <sys/types.h>
#include <sys/file.h>
#include <netat/appletalk.h>
#include <netat/afp.h>
#include <netat/afpcmd.h>

#ifdef NOFLOCK
# ifndef NOLOCKF
#  ifndef LOCKF_ONLY
#   define LOCKF_ONLY
#  endif
# endif
#endif

/*
 * The following routines define Byte Range Locking
 * 
 * The following system calls (that only exist on some machines) will
 * do the right thing:
 *  lockf - system V routine 
 *
 * For systems without lockf, etc., someone has to hack together
 * some system daemon or kernel driver.
 *
*/

#ifdef NOLOCKF
/* These are here for systems that can't do byte range lock */

OSByteRangeLock(fd, offset, length, unlockflag, startendflag, fpos)
int fd;
sdword offset, length;
int unlockflag, startendflag;
sdword *fpos;
{
#ifdef DEBUG
  printf("OS Byte Range lock: unimplemented on this OS\n");
#endif
  return(aeMiscErr);
}  

OSErr
OSTestLock(fd, length)
int fd;
sdword length;
{
  return(noErr);
}
#else
/*
 * Institute a byte range lock on a file
 *
 * offset can be negative if startendflag = 1 and then denotes
 * offset relative from end of fork
 * length must be positive
 * unlockflag is set if want unlock
 *
 * Unlike AFP Spec: multiple ranges may overlap and unlock thusly
 * may return NoMoreLocks as an error.
 *
*/
OSErr
OSByteRangeLock(fd, offset, length, flags, fpos)
int fd;
sdword offset, length;
byte flags;
sdword *fpos;
{
  int pos;
  int startendflag = (BRL_START & flags);
  int unlockflag = (BRL_UNLOCK & flags);
  extern int errno;

#ifdef DEBUG
  printf("OSBRL: %slocking offset %ld, length %x (%ld), from %s\n",
	 unlockflag ? "un" : "", offset, length, length,
	 startendflag ? "end" : "start");
#endif
  if (length < 0)		/* can only be -1 */
    length = 0;			/* length zero means entire file! */

  if ((pos = lseek(fd, (off_t)offset, (startendflag ? L_XTND : L_SET)))  < 0) {
    *fpos = -1;			/* unknown */
    return(aeParamErr);
  }
  *fpos = pos;

  if (lockf(fd, unlockflag ? F_ULOCK : F_TLOCK, length) < 0) {
    switch (errno) {
#ifdef EREMOTE
      /* not sure if this is the best thing to do */
    case EREMOTE:
      return(noErr);
#endif
#ifdef notdef
      return(aeRangeNotLocked);
      return(aeRangeOverlap);
#endif
    case EACCES:
    case EAGAIN:
#ifdef EINTR
    case EINTR:
#endif
      return(aeLockErr);
#ifdef EBADF
    case EBADF:			/* SunOS */
#endif
    /* really permission denied (or, unlikely: bad file) */
#ifdef ENOLCK			/* sunos */
    case ENOLCK:
#endif
#ifdef EDEADLK
    case EDEADLK:
#endif
      return(aeNoMoreLocks);
    default:
      return(aeParamErr);
    }
  }
  return(noErr);
}

/*
 * returns noErr if the range starting at the current file position
 * for length "length" is not locked.
 *
*/
OSErr
OSTestLock(fd, length)
int fd;
sdword length;
{
  extern int errno;

  if (lockf(fd, F_TEST, length) < 0) {
#ifdef EREMOTE
    if (errno == EREMOTE)
      return(noErr);
#endif
#ifdef DEBUG
    printf("File is locked\n");
#endif
    return(aeLockErr);
  }
  return(noErr);
}
#endif

/* 
 * The following calls are used to coordinate read/writes for various
 * files used by aufs.
 *
 * The basic primatives are:
 *   Lock File for Read - lock a file for reading (others may do the
 *     same).  Do it if no write locks are in effect.
 *   Lock File for Write - lock a file for writing (other may not at the
 *     same time).  Do it if no read or write locks are in effect.
 *   Unlock file
 *
 *  Note, lffr is essentially a shared lock while lffw is an exclusive
 *     lock.
 *
 *  Since most unix systems only issue advisory locks, the deal is that
 *   you call the routines before you do any reading or writing - this
 *   should be sufficient.
 *  Note: the lock calls are assumed to block - routines must be "good"
 *   about unlocking or things will break in a big way.
 *
 * Implementations:
 *  flock - implements shared and exclusive locks: perfect
 *  lockf - implements exclusive locks only (and only on writable fds):
 *           okay, but reads can get "out of date" or "bad" data
 *
 *
*/
boolean
OSLockFileforRead(fd)
int fd;
{
#ifndef NOFLOCK
  if (flock(fd, LOCK_SH) < 0)
    return(FALSE);		/* problem!!! */
#else
# ifdef LOCKF_ONLY
  if (lockf(fd, F_LOCK, 0) < 0) {
#  ifdef EREMOTE
    if (errno == EREMOTE)
      return(TRUE);
#  endif
    if (errno == EBADF)		/* file is open read-only */
      return(TRUE);		/* can't do lock, so let it go on */
    return(FALSE);
  }
# endif
#endif
  return(TRUE);
}

boolean
OSLockFileforWrite(fd)
{
#ifndef NOFLOCK
  if (flock(fd, LOCK_EX) < 0)
    return(FALSE);		/* problem!!! */
#else
# ifdef LOCKF_ONLY
  if (lockf(fd, F_LOCK, 0) < 0) {
#  ifdef EREMOTE
    if (errno == EREMOTE)
      return(TRUE);
#  endif /* EREMOTE */
    return(FALSE);
  }
# endif /* LOCKF ONLY */
#endif
  return(TRUE);
}

/*
 * This implements an exclusive lock on the file.  It differs from
 * OSLockFileforRead in that it doesn't block
 *
*/
#ifdef notdef			/* not used */
boolean
OSMaybeLockFile(fd)
{
#ifndef NOFLOCK
  if (flock(fd, LOCK_EX|LOCK_NB) < 0)
    return(FALSE);		/* problem!!! */
# else
# ifdef LOCKF_ONLY
  if (lockf(fd, F_TLOCK, 0) < 0) {
#  ifdef EREMOTE
    if (errno == EREMOTE)
      return(TRUE);
#  endif
    return(FALSE);
  }
# endif 
#endif
  return(true);
}
#endif

boolean
OSUnlockFile(fd)
{
#ifndef NOFLOCK
  if (flock(fd, LOCK_UN) < 0)
    return(FALSE);
#else /* NOFLOCK */
# ifdef LOCKF_ONLY
  if (lockf(fd, F_ULOCK, 0) < 0) {
# ifdef EREMOTE
    if (errno == EREMOTE)
      return(TRUE);
# endif /* EREMOTE */
    return(FALSE);
  }
# endif /* LOCKF_ONLY */
#endif /* end else NOFLOCK */
  return(TRUE);
}

getlockinfo(haveflock,havelockf)
int *haveflock;
int *havelockf;
{
#ifdef NOFLOCK
  *haveflock = 0;
#else
  *haveflock = 1;
#endif
#ifdef NOLOCKF
  *havelockf = 0;
#else
  *havelockf = 1;
#endif
}
