h40402
s 00007/00000/00150
d D 8.12 95/04/27 13:58:45 bostic 48 47
c move getopt information from stdlib.h to unistd.h
c as decreed by IEEE Std 1003.2-1992
e
s 00001/00000/00149
d D 8.11 94/07/28 03:38:28 pendry 47 46
c changes for whiteouts and union filesystem
e
s 00001/00001/00148
d D 8.10 94/04/16 12:26:44 bostic 46 45
c setgroups now takes gid_t's, they are 32-bits
e
s 00001/00001/00148
d D 8.9 94/04/16 08:43:18 bostic 45 44
c add 1994 to the copyright
e
s 00002/00002/00147
d D 8.8 94/04/16 08:41:05 bostic 44 43
c make setreuid and setregid take uid_t/gid_t's, for
c consistency with the C library source code.
c From: "Chris G. Demetriou" <cgd@vangogh.CS.Berkeley.EDU>
e
s 00001/00001/00148
d D 8.7 94/02/22 13:51:40 bostic 43 42
c second argument to nfssvc is a void *argstructp
e
s 00000/00004/00149
d D 8.6 94/02/21 17:01:39 bostic 42 41
c readv and writev are in <sys/uio.h>; delete them, but leave the
c struct forward; fix
e
s 00006/00004/00147
d D 8.5 94/02/21 16:35:53 bostic 41 40
c add prototypes for readv, writev
c use forward declarations instead of including a header file
e
s 00001/00001/00150
d D 8.4 94/01/04 13:28:13 bostic 40 39
c getgroups now takes gid_t's, they are 32-bits
e
s 00001/00001/00150
d D 8.3 94/01/03 17:58:15 bostic 39 38
c use latest BSDI version of <sys/cdefs.h>, change to __keyword
e
s 00001/00001/00150
d D 8.2 93/11/20 05:50:15 bostic 38 37
c return of vfork is a pid_t, not an int
e
s 00002/00002/00149
d D 8.1 93/06/06 21:57:33 bostic 37 33
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00148
d R 8.1 93/06/06 11:11:49 bostic 36 35
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00001/00150
d R 5.32 93/06/06 11:11:31 bostic 35 33
c delete extern declarations of sys_errlist, sys_nerr, sys_signame, and
c sys_siglist; they caused nothing but problems as they invariably clashed with
c declarations by the programs; delete unnecessary externs from ctype.h
e
s 00002/00002/00149
d R 8.1 93/06/02 20:07:27 bostic 34 33
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00005/00151
d D 5.31 93/05/25 17:47:39 bostic 33 32
c __lseek => lseek, __{f,}truncate => {f,}truncate
e
s 00001/00001/00155
d D 5.30 93/05/07 09:39:25 bostic 32 31
c make the sys_ arrays all `const char *const []' (for consistency,
c and for compatibility with GNU/Cygnus)
e
s 00001/00000/00155
d D 5.29 93/05/07 09:38:25 bostic 31 30
c add confstr(3)
e
s 00003/00003/00152
d D 5.28 93/05/03 15:26:20 bostic 30 29
c add fpathconf, pathconf, sysconf to the C library
e
s 00002/00000/00153
d D 5.27 93/05/02 00:53:44 mckusick 29 28
c protect against lseek definition in types.h
e
s 00000/00002/00153
d D 5.26 93/03/03 18:28:23 bostic 28 27
c chflags is in <sys/stat.h>
e
s 00006/00006/00149
d D 5.25 93/02/10 20:25:49 bostic 27 26
c u_short, u_long aren't POSIX, so may not be typdef'd
e
s 00001/00001/00154
d D 5.24 93/02/03 15:05:49 elan 26 25
c sys_signame and sys_siglist are const's.
e
s 00000/00001/00155
d D 5.23 93/01/12 10:28:41 bostic 25 24
c move cuserid to libcompat, POSIX no longer requires it
e
s 00001/00001/00155
d D 5.22 92/10/04 11:50:36 bostic 24 23
c nfssvc has two arguments, second is a caddr_t
e
s 00000/00001/00156
d D 5.21 92/06/29 14:41:36 bostic 23 22
c move function prototype to fnmatch.h
e
s 00001/00000/00156
d D 5.20 92/06/29 11:48:03 bostic 22 21
c add iruserok
e
s 00000/00006/00156
d D 5.19 92/06/28 13:02:41 bostic 21 20
c POSIX 1003.2, D11.2 moves fnmatch #defines into fnmatch.h
e
s 00001/00001/00161
d D 5.18 92/06/19 15:16:59 bostic 20 19
c lseek returns a quad
e
s 00004/00001/00158
d D 5.17 92/05/27 20:21:03 mckusick 19 18
c programs that include this file get new truncate and lseek interface
e
s 00001/00001/00158
d D 5.16 92/04/22 11:34:22 mckusick 18 17
c for now lseek takes and returns a long
e
s 00004/00002/00155
d D 5.15 92/03/02 20:32:18 torek 17 15
c declare dead and pure functions as such
e
s 00002/00001/00156
d R 5.15 92/03/02 20:22:51 torek 16 15
c declare dead and pure functions as such
e
s 00000/00002/00157
d D 5.14 91/12/06 14:04:32 bostic 15 14
c put ssize_t in <sys/types.h>, as specified by POSIX
e
s 00046/00046/00113
d D 5.13 91/06/17 08:21:27 bostic 14 13
c don't define _exit as "void volatile"; it's a GCC extension, and may
c cause problems with other compilers
e
s 00004/00004/00155
d D 5.12 91/05/18 14:56:41 bostic 13 12
c add return values to setkey, encrypt, des_setkey, des_cipher to
c distinguish failure (no hardware support or foreign distribution)
e
s 00001/00001/00158
d D 5.11 91/04/21 15:03:15 donn 12 11
c des_cipher takes a long, not u_long; see rev 5.6 of libc/gen/crypt.c
e
s 00005/00000/00154
d D 5.10 91/04/03 16:42:29 bostic 11 10
c protect all user-level include files against reinclusion
e
s 00002/00000/00152
d D 5.9 91/03/06 13:51:55 bostic 10 9
c add des_cipher(3), des_setkey(3)
e
s 00000/00001/00152
d D 5.8 91/03/03 16:28:29 donn 9 8
c Move the fchmod() declaration to stat.h.
e
s 00001/00001/00152
d D 5.7 91/02/26 11:56:42 bostic 8 7
c getgroups takes a pointer to int's for now
e
s 00000/00009/00153
d D 5.6 91/02/24 15:26:18 bostic 7 6
c move insque/remque to libcompat, no longer need structure/prototypes
e
s 00005/00005/00157
d D 5.5 91/02/24 14:18:21 bostic 6 5
c lots of prototype corrections
e
s 00002/00001/00160
d D 5.4 91/02/22 22:50:02 donn 5 3
c Tweaks for psignal().
e
s 00001/00000/00161
d R 5.4 91/02/22 22:37:49 donn 4 3
c Declare sys_siglist[] to go with psignal().
e
s 00001/00001/00160
d D 5.3 91/02/22 15:19:22 donn 3 2
c Make exect()'s prototype more like the (correct) one for execv().
e
s 00007/00002/00154
d D 5.2 91/02/22 15:15:46 bostic 2 1
c add sys/time.h, prototype for select needs it.
e
s 00156/00000/00000
d D 5.1 91/02/22 11:34:25 bostic 1 0
c date and time created 91/02/22 11:34:25 by bostic
e
u
U
t
T
I 1
/*-
D 37
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 37
I 37
D 45
 * Copyright (c) 1991, 1993
E 45
I 45
 * Copyright (c) 1991, 1993, 1994
E 45
 *	The Regents of the University of California.  All rights reserved.
E 37
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

I 11
#ifndef _UNISTD_H_
#define	_UNISTD_H_

E 11
#include <sys/cdefs.h>
#include <sys/types.h>
#include <sys/unistd.h>

#define	 STDIN_FILENO	0	/* standard input file descriptor */
#define	STDOUT_FILENO	1	/* standard output file descriptor */
#define	STDERR_FILENO	2	/* standard error file descriptor */

D 21
/* fnmatch(3) defines */
#define	FNM_PATHNAME	0x01	/* match pathnames, not filenames */
#ifndef _POSIX_SOURCE
#define	FNM_QUOTE	0x02	/* escape special chars with \ */
#endif

E 21
#ifndef NULL
#define	NULL		0	/* null pointer constant */
#endif

D 15
typedef	int ssize_t;		/* count of bytes or error indication */

E 15
__BEGIN_DECLS
D 14
void volatile	 _exit __P((int));
int		 access __P((const char *, int));
u_int		 alarm __P((u_int));
int		 chdir __P((const char *));
int		 chown __P((const char *, uid_t, gid_t));
int		 close __P((int));
D 6
char		*cuserid __P((const char *));
E 6
I 6
char		*cuserid __P((char *));
E 6
int		 dup __P((int));
int		 dup2 __P((int, int));
int		 execl __P((const char *, const char *, ...));
int		 execle __P((const char *, const char *, ...));
int		 execlp __P((const char *, const char *, ...));
int		 execv __P((const char *, char * const *));
int		 execve __P((const char *, char * const *, char * const *));
int		 execvp __P((const char *, char * const *));
pid_t		 fork __P((void));
long		 fpathconf __P((int, int));		/* not yet */
char		*getcwd __P((char *, size_t));
gid_t		 getegid __P((void));
uid_t		 geteuid __P((void));
gid_t		 getgid __P((void));
D 8
int		 getgroups __P((int, gid_t *));
E 8
I 8
int		 getgroups __P((int, int *));		/* XXX (gid_t *) */
E 8
char		*getlogin __P((void));
pid_t		 getpgrp __P((void));
pid_t		 getpid __P((void));
pid_t		 getppid __P((void));
uid_t		 getuid __P((void));
int		 isatty __P((int));
int		 link __P((const char *, const char *));
off_t		 lseek __P((int, off_t, int));
long		 pathconf __P((const char *, int));	/* not yet */
int		 pause __P((void));
int		 pipe __P((int *));
ssize_t		 read __P((int, void *, size_t));
int		 rmdir __P((const char *));
int		 setgid __P((gid_t));
int		 setpgid __P((pid_t, pid_t));
pid_t		 setsid __P((void));
int		 setuid __P((uid_t));
u_int		 sleep __P((u_int));
long		 sysconf __P((int));			/* not yet */
pid_t		 tcgetpgrp __P((int));
D 6
pid_t		 tcsetpgrp __P((int, pid_t));
E 6
I 6
int		 tcsetpgrp __P((int, pid_t));
E 6
char		*ttyname __P((int));
int		 unlink __P((const char *));
ssize_t		 write __P((int, const void *, size_t));
E 14
I 14
D 17
void	 _exit __P((int));
E 17
I 17
__dead void
	 _exit __P((int));
E 17
int	 access __P((const char *, int));
D 27
u_int	 alarm __P((u_int));
E 27
I 27
unsigned int	 alarm __P((unsigned int));
E 27
int	 chdir __P((const char *));
int	 chown __P((const char *, uid_t, gid_t));
int	 close __P((int));
I 31
size_t	 confstr __P((int, char *, size_t));
E 31
D 25
char	*cuserid __P((char *));
E 25
int	 dup __P((int));
int	 dup2 __P((int, int));
int	 execl __P((const char *, const char *, ...));
int	 execle __P((const char *, const char *, ...));
int	 execlp __P((const char *, const char *, ...));
int	 execv __P((const char *, char * const *));
int	 execve __P((const char *, char * const *, char * const *));
int	 execvp __P((const char *, char * const *));
pid_t	 fork __P((void));
D 30
long	 fpathconf __P((int, int));		/* not yet */
E 30
I 30
long	 fpathconf __P((int, int));
E 30
char	*getcwd __P((char *, size_t));
gid_t	 getegid __P((void));
uid_t	 geteuid __P((void));
gid_t	 getgid __P((void));
D 40
int	 getgroups __P((int, int *));		/* XXX (gid_t *) */
E 40
I 40
int	 getgroups __P((int, gid_t []));
E 40
char	*getlogin __P((void));
pid_t	 getpgrp __P((void));
pid_t	 getpid __P((void));
pid_t	 getppid __P((void));
uid_t	 getuid __P((void));
int	 isatty __P((int));
int	 link __P((const char *, const char *));
I 29
D 33
#ifndef lseek
E 29
D 18
off_t	 lseek __P((int, off_t, int));
E 18
I 18
D 19
long	 lseek __P((int, long, int));
E 19
I 19
#define	 lseek __lseek
E 33
D 20
long	 lseek __P((int, off_t, int));
E 20
I 20
off_t	 lseek __P((int, off_t, int));
I 29
D 33
#endif
E 33
E 29
E 20
E 19
E 18
D 30
long	 pathconf __P((const char *, int));	/* not yet */
E 30
I 30
long	 pathconf __P((const char *, int));
E 30
int	 pause __P((void));
int	 pipe __P((int *));
ssize_t	 read __P((int, void *, size_t));
int	 rmdir __P((const char *));
int	 setgid __P((gid_t));
int	 setpgid __P((pid_t, pid_t));
pid_t	 setsid __P((void));
int	 setuid __P((uid_t));
D 27
u_int	 sleep __P((u_int));
E 27
I 27
unsigned int	 sleep __P((unsigned int));
E 27
D 30
long	 sysconf __P((int));			/* not yet */
E 30
I 30
long	 sysconf __P((int));
E 30
pid_t	 tcgetpgrp __P((int));
int	 tcsetpgrp __P((int, pid_t));
char	*ttyname __P((int));
int	 unlink __P((const char *));
ssize_t	 write __P((int, const void *, size_t));
E 14

I 48
extern char *optarg;			/* getopt(3) external variables */
extern int optind, opterr, optopt;
int	 getopt __P((int, char * const [], const char *));

E 48
#ifndef	_POSIX_SOURCE
D 41

I 2
/* structure timeval required for select() */
#include <sys/time.h>

E 41
I 41
#ifdef	__STDC__
struct timeval;				/* select(2) */
D 42
struct iovec;				/* readv(2), writev(2) */
E 42
#endif
E 41
D 7
/* structure qelem required for insque() and remque() */
E 2
struct qelem {
	struct	qelem *q_forw;
	struct	qelem *q_back;
	char	q_data[1];	/* arbitrary amount of data */
};
D 2
void	 insque __P((struct qelem *, struct qelem *));
void	 remque __P((struct qelem *));
E 2

E 7
int	 acct __P((const char *));
int	 async_daemon __P((void));
char	*brk __P((const char *));
D 28
int	 chflags __P((const char *, long));
E 28
int	 chroot __P((const char *));
char	*crypt __P((const char *, const char *));
I 10
D 12
void	 des_cipher __P((const char *, char *, u_long, int));
E 12
I 12
D 13
void	 des_cipher __P((const char *, char *, long, int));
E 12
void	 des_setkey __P((const char *key));
E 10
void	 encrypt __P((char *, int));
E 13
I 13
int	 des_cipher __P((const char *, char *, long, int));
int	 des_setkey __P((const char *key));
int	 encrypt __P((char *, int));
E 13
void	 endusershell __P((void));
D 3
int	 exect __P((const char *, const char * const *, const char * const *));
E 3
I 3
int	 exect __P((const char *, char * const *, char * const *));
E 3
int	 fchdir __P((int));
D 28
int	 fchflags __P((int, long));
E 28
D 9
int	 fchmod __P((int, mode_t));
E 9
int	 fchown __P((int, int, int));
D 23
int	 fnmatch __P((const char *, const char *, int));
E 23
int	 fsync __P((int));
I 19
D 33
#define	 ftruncate __ftruncate
E 33
E 19
int	 ftruncate __P((int, off_t));
int	 getdtablesize __P((void));
long	 gethostid __P((void));
int	 gethostname __P((char *, int));
D 6
mode_t	 getmode __P((const mode_t *, mode_t));
E 6
I 6
mode_t	 getmode __P((const void *, mode_t));
E 6
D 17
int	 getpagesize __P((void));
E 17
I 17
__pure int
	 getpagesize __P((void));
E 17
char	*getpass __P((const char *));
char	*getusershell __P((void));
char	*getwd __P((char *));			/* obsoleted by getcwd() */
int	 initgroups __P((const char *, int));
I 22
D 27
int	 iruserok __P((u_long, int, const char *, const char *));
E 27
I 27
int	 iruserok __P((unsigned long, int, const char *, const char *));
E 27
E 22
I 2
D 7
void	 insque __P((struct qelem *, struct qelem *));
E 7
E 2
int	 mknod __P((const char *, mode_t, dev_t));
int	 mkstemp __P((char *));
char	*mktemp __P((char *));
D 24
int	 nfssvc __P((int));
E 24
I 24
D 43
int	 nfssvc __P((int, caddr_t));
E 43
I 43
int	 nfssvc __P((int, void *));
E 43
E 24
int	 nice __P((int));
I 2
D 5
int	 psignal __P((u_int, const char *));
E 5
I 5
D 27
void	 psignal __P((u_int, const char *));
E 27
I 27
void	 psignal __P((unsigned int, const char *));
E 27
D 26
extern char *sys_siglist[];
E 26
I 26
D 32
extern char *const sys_siglist[];
E 32
I 32
D 39
extern const char *const sys_siglist[];
E 39
I 39
extern __const char *__const sys_siglist[];
E 39
E 32
E 26
E 5
E 2
int	 profil __P((char *, int, int, int));
I 41
D 42
ssize_t	 readv __P((int, struct iovec *, int));
E 42
E 41
int	 rcmd __P((char **, int, const char *,
		const char *, const char *, int *));
char	*re_comp __P((const char *));
int	 re_exec __P((const char *));
int	 readlink __P((const char *, char *, int));
int	 reboot __P((int));
I 2
D 7
void	 remque __P((struct qelem *));
E 7
E 2
int	 revoke __P((const char *));
D 6
int	 rresvport __P((const int *));
E 6
I 6
int	 rresvport __P((int *));
E 6
int	 ruserok __P((const char *, int, const char *, const char *));
char	*sbrk __P((int));
int	 select __P((int, fd_set *, fd_set *, fd_set *, struct timeval *));
int	 setegid __P((gid_t));
int	 seteuid __P((uid_t));
D 46
int	 setgroups __P((int, const int *));
E 46
I 46
int	 setgroups __P((int, const gid_t *));
E 46
void	 sethostid __P((long));
int	 sethostname __P((const char *, int));
D 13
void	 setkey __P((const char *));
E 13
I 13
int	 setkey __P((const char *));
E 13
int	 setlogin __P((const char *));
D 6
mode_t	 setmode __P((const char *));
E 6
I 6
void	*setmode __P((const char *));
E 6
int	 setpgrp __P((pid_t pid, pid_t pgrp));	/* obsoleted by setpgid() */
D 44
int	 setregid __P((int, int));
int	 setreuid __P((int, int));
E 44
I 44
int	 setregid __P((gid_t, gid_t));
int	 setreuid __P((uid_t, uid_t));
E 44
int	 setrgid __P((gid_t));
int	 setruid __P((uid_t));
void	 setusershell __P((void));
int	 swapon __P((const char *));
int	 symlink __P((const char *, const char *));
void	 sync __P((void));
int	 syscall __P((int, ...));
I 19
D 33
#define	 truncate __truncate
E 33
E 19
int	 truncate __P((const char *, off_t));
int	 ttyslot __P((void));
D 27
u_int	 ualarm __P((u_int, u_int));
void	 usleep __P((u_int));
E 27
I 27
unsigned int	 ualarm __P((unsigned int, unsigned int));
I 47
int	 unwhiteout __P((const char *));
E 47
void	 usleep __P((unsigned int));
E 27
void	*valloc __P((size_t));			/* obsoleted by malloc() */
D 38
int	 vfork __P((void));
E 38
I 38
pid_t	 vfork __P((void));
I 48

extern char *suboptarg;			/* getsubopt(3) external variable */
int	 getsubopt __P((char **, char * const *, char **));
E 48
I 41
D 42
ssize_t	 writev __P((int, struct iovec *, int));
E 41
E 38

E 42
#endif /* !_POSIX_SOURCE */
__END_DECLS
I 11

#endif /* !_UNISTD_H_ */
E 11
E 1
