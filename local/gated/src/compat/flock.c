/*
 *  $Id: flock.c,v 1.9 1993/02/11 03:59:23 jch Exp $
 */

/* %(Copyright.header) */

#define	INCLUDE_FILE
#define	INCLUDE_STAT

#include "include.h"

/* Emulation of flock() using lockf() */

#if	__GNUC__ >= 2
PROTOTYPE(flock,
	  int,
	  (int,
	   int));
#endif	/* __GNUC__ >= 2 */
int
flock(fd, flags)
int fd;
int flags;
{
#ifdef	F_LOCK
    int rc;
    int cmd = 0;

    switch (BIT_TEST(flags, LOCK_EX|LOCK_SH|LOCK_UN)) {

    case LOCK_SH|LOCK_EX:
    case LOCK_EX:
	cmd = BIT_TEST(flags, LOCK_NB) ? F_TLOCK : F_LOCK;

	break;

    case LOCK_UN:
	cmd = F_ULOCK;
	break;

    case LOCK_SH:
	/* We don`t do shared locks */
    default:
	errno = EINVAL;
	return -1;
    }
    
    lseek(fd, 0L, 0);

    NON_INTR(rc, lockf(fd, cmd, 0L));
    if (rc < 0) {
	switch (errno) {
	case EACCES:
	case EAGAIN:
	    errno = EWOULDBLOCK;
	    break;

	default:
	    break;
	}
    }

    return rc;
#else	/* F_LOCK */
    return 0;
#endif	/* F_LOCK */
}


/*
 * %(Copyright)
 */
