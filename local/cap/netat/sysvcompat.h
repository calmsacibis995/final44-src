/*
 *  Author: cck    Date: 88/03/22 16:58:51  
 *  Header: sysvcompat.h,v 1.10 88/03/22 16:58:51 cck Rel  
 *  Revision: 1.10  
*/

/*
 * sysvcompat.h - header file to allow us to port to sys v system machines
 *  without building a library of "compatible function" for functions that
 *  have slightly different name, etc.
 *
 * AppleTalk package for UNIX (4.2 BSD).
 *
 * Copyright (c) 1986, 1987, 1988 by The Trustees of Columbia University in the
 * City of New York.
 *
 * Edit History:
 *
 *  June, 1987 	CCKim    Created
 *
 */

/*
 * Mappings from bsd to sysv string and bytestring function
 *
*/
#ifdef hpux
# define B2S_STRING_MAPON	/* map strings */
# define B2S_BSTRING_MAPON	/* map byte string instructions */
# define USECHOWN		/* sysv allows us */
# define NEEDFCNTLDOTH		/* if need fcntl.h for O_... */

# define USETIMES		/* use times instead of getrusage */
# define NOWAIT3		/* no wait3 */
/* some versions may have this */
# define NODUP2			/* no dup2 */
# define NOLSTAT		/* no symbolic links */
# define USERAND		/* use srand, rand */
# define USEGETCWD		/* use getcwd instead of bsd getwd */
# define NOUTIMES		/* no utimes - use utime */
# define NOPGRP			/* no process groups (setpgrp, killpg) */
#endif

#ifdef aux
# define B2S_STRING_MAPON	/* map strings */
# define B2S_BSTRING_MAPON	/* map byte string instructions */
# define USECHOWN		/* sysv allows us */

# define USETIMES		/* use times instead of getrusage */
# define USERAND		/* use srand, rand */
# define NOVFORK		/* no vfork in system */
#endif



/* FIXED CONFIGURATION -- ALL NEW CONFIGURATIONS MUST PRECEED */

/* map sigcld to sigchld if sigchld isn't there */
#ifndef SIGCHLD
# ifdef SIGCLD
#  define SIGCHLD SIGCLD
# endif
#endif

#ifdef B2S_STRING_MAPON
# ifndef USESTRINGDOTH
#  define USESTRINGDOTH		/*  must use string.h */
# endif
# define index(s,c) strchr((s),(c))
# define rindex(s,c) strrchr((s),(c))
#endif

#ifdef B2S_BSTRING_MAPON
# define bcopy(s,d,l) memcpy((d),(s),(l))
# define bcmp(b1,b2,l) memcmp((b1),(b2),(l))
# define bzero(b,l) memset((b),0,(l))
#endif

#ifdef NOWAIT3
# define WIFSTOPPED(status) (((status) & 0xff) == 0177)
# define WIFSIGNALED(status) (((status) & 0177) != 0)
# define W_TERMSIG(status) ((status) & 0177)
# define W_COREDUMP(status) ((status) & 0200)
# define W_RETCODE(status) ((status) >> 8)
#else
# define W_TERMSIG(status) (status).w_termsig
# define W_COREDUMP(status) (status).w_coredump
# define W_RETCODE(status) (status).w_retcode
#endif


