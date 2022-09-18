h46107
s 00016/00016/00128
d D 1.6 94/08/13 13:56:28 bostic 6 5
c more types problems, make it compile again   
e
s 00002/00002/00142
d D 1.5 94/04/17 08:58:57 bostic 5 4
c make setreuid and setregid take uid_t/gid_t's, for
c consistency with the C library source code.
c From: "Chris G. Demetriou" <cgd@vangogh.CS.Berkeley.EDU>
e
s 00001/00001/00143
d D 1.4 94/01/22 13:37:19 bostic 4 3
c update getgroups declaratoin
e
s 00001/00001/00143
d D 1.3 94/01/22 05:29:40 bostic 3 2
c change vfork to return a pid_t, not an int
e
s 00010/00019/00134
d D 1.2 93/05/25 15:30:21 elan 2 1
c support for 4.4BSD
e
s 00153/00000/00000
d D 1.1 93/02/23 15:37:16 elan 1 0
c date and time created 93/02/23 15:37:16 by elan
e
u
U
t
T
I 1
#ifndef _G_unistd_h
#define _G_unistd_h 1

#include <_G_config.h>

extern "C" {

#if _G_HAVE_UNISTD
#ifndef _G_USE_PROTOS
#define chmod __hide_chmod
#define chown __hide_chown
#define execl __hide_execl
#define execlp __hide_execlp
#define execle __hide_execle
#define fchown __hide_fchown
#define ioctl __hide_ioctl
#define setgid __hide_setgid
#define setuid __hide_setuid
#endif
#ifdef _AIX
// AIX's unistd.h defines int rename (const char *old, const char *new).
// This is not legal ANSI.  It causes a C++ syntax error (because of 'new').
#define new __new
#endif
#include_next <unistd.h>
#ifdef _AIX
#undef new
#endif
#ifndef _G_USE_PROTOS
#undef chmod
#undef chown
#undef execl
#undef execle
#undef execlp
#undef fchown
#undef ioctl
#undef setgid
#undef setuid
#endif
#else
#ifndef SEEK_SET
#define SEEK_SET        0
#define SEEK_CUR        1
#define SEEK_END        2
#endif

#ifndef F_OK
#define F_OK            0
#endif
#ifndef X_OK
#define X_OK            1
#endif
#ifndef W_OK
#define W_OK            2
#endif
#ifndef R_K
#define R_OK            4
#endif
#endif

#ifdef __GNUG__
extern void volatile _exit(int);
#else
void _exit(int);
#endif

extern unsigned alarm _G_ARGS((unsigned));
D 2
extern int      brk _G_ARGS((void*));
E 2
I 2
extern char    *brk _G_ARGS((const char *));
E 2
extern int      chdir _G_ARGS((const char*));
extern int      chmod  _G_ARGS((const char*, _G_mode_t));
extern int      chown (const char*, _G_uid_t, _G_gid_t);
extern int      close _G_ARGS((int));
extern char*    crypt _G_ARGS((const char*, const char*));
extern int      dup _G_ARGS((int));
extern int      dup2 _G_ARGS((int, int));
D 2
extern void	encrypt _G_ARGS((char*, int));
E 2
I 2
extern int	encrypt _G_ARGS((char*, int));
E 2
extern int      execl (const char*, const char *, ...);
extern int      execle (const char*, const char *, ...);
extern int      execlp (const char*, const char*, ...);
D 2
extern int      exect _G_ARGS((const char*,  const char**,  char**));
extern int      execv _G_ARGS((const char*,  const char * const *));
extern int      execve _G_ARGS((const char*, const char * const *, const char * const *));
extern int      execvp _G_ARGS((const char*,  const char * const *));
E 2
I 2
extern int      exect _G_ARGS((const char*, char * const *, char * const *));
extern int      execv _G_ARGS((const char*,  char * const *));
extern int      execve _G_ARGS((const char*, char * const *, char * const *));
extern int      execvp _G_ARGS((const char*,  char * const *));
E 2
extern int      fchown (int, _G_uid_t, _G_gid_t);
D 6
extern _G_pid_t fork _G_ARGS((void));
E 6
I 6
extern pid_t	fork _G_ARGS((void));
E 6
extern int      fsync _G_ARGS((int));
extern int      ftruncate _G_ARGS((int, _G_off_t));
extern char*    getcwd _G_ARGS((char*, _G_size_t));
extern int      getdomainname _G_ARGS((char*, int));
extern int      getdtablesize _G_ARGS((void));
D 2
extern int      getgroups _G_ARGS((int, _G_gid_t*));
E 2
I 2
D 4
extern int      getgroups _G_ARGS((int, int *));
E 4
I 4
extern int      getgroups _G_ARGS((int, gid_t []));
E 4
E 2
D 6
extern _G_uid_t geteuid _G_ARGS((void));
extern _G_gid_t getegid _G_ARGS((void));
extern _G_gid_t getgid _G_ARGS((void));
E 6
I 6
extern uid_t geteuid _G_ARGS((void));
extern gid_t getegid _G_ARGS((void));
extern gid_t getgid _G_ARGS((void));
E 6
extern long     gethostid _G_ARGS((void));
extern int      gethostname _G_ARGS((char*, int));
D 6
extern _G_pid_t getpgrp _G_ARGS((...));
extern _G_pid_t getpid _G_ARGS((void));
extern _G_pid_t getppid _G_ARGS((void));
E 6
I 6
extern pid_t getpgrp _G_ARGS((...));
extern pid_t getpid _G_ARGS((void));
extern pid_t getppid _G_ARGS((void));
E 6
extern char*    getlogin _G_ARGS((void));
extern char*    getpass _G_ARGS((const char*));
D 6
extern _G_uid_t getuid _G_ARGS((void));
E 6
I 6
extern uid_t getuid _G_ARGS((void));
E 6
extern int      ioctl (int, int, ... );
extern int      isatty _G_ARGS((int));
extern int      link _G_ARGS((const char*, const char*));
extern int      mkstemp _G_ARGS((char*));
extern char*    mktemp _G_ARGS((char*));
extern int      nice _G_ARGS((int));
extern int      pause _G_ARGS((void));
extern int      pipe _G_ARGS((int*));
extern int      readlink _G_ARGS((const char*, char*, int));
extern int      rename _G_ARGS((const char*, const char*));
extern int      rmdir _G_ARGS((const char*)); 
D 2
#ifdef __OSF1__
E 2
extern char*	sbrk _G_ARGS((int));
D 2
#else
extern void*    sbrk _G_ARGS((int)); 
#endif
E 2
extern int      syscall _G_ARGS((int, ...));
D 6
extern int      setgid (_G_gid_t);
E 6
I 6
extern int      setgid (gid_t);
E 6
extern int      sethostname _G_ARGS((const char*, int));
D 2
#ifdef _G_SYSV
extern _G_pid_t setpgrp _G_ARGS((void));
extern _G_pid_t setsid _G_ARGS((void));
#else
extern _G_pid_t setpgrp _G_ARGS((_G_pid_t, _G_pid_t));
#endif
E 2
I 2
D 6
extern int	setpgrp _G_ARGS((_G_pid_t, _G_pid_t));
E 2
D 5
extern int      setregid _G_ARGS((int, int));
extern int      setreuid _G_ARGS((int, int));
E 5
I 5
extern int      setregid _G_ARGS((_G_gid_t, _G_gid_t));
extern int      setreuid _G_ARGS((_G_uid_t, _G_uid_t));
E 5
extern int      setuid (_G_uid_t);
E 6
I 6
extern int	setpgrp _G_ARGS((pid_t, pid_t));
extern int      setregid _G_ARGS((gid_t, gid_t));
extern int      setreuid _G_ARGS((uid_t, uid_t));
extern int      setuid (uid_t);
E 6
extern unsigned sleep _G_ARGS((unsigned));
extern void     swab _G_ARGS((void*, void*, int));
extern int      symlink _G_ARGS((const char*, const char*));
extern long     sysconf _G_ARGS((int));
D 6
extern int      truncate _G_ARGS((const char*, _G_off_t));
E 6
I 6
extern int      truncate _G_ARGS((const char*, off_t));
E 6
extern char*    ttyname _G_ARGS((int));
extern int      ttyslot _G_ARGS((void));
//extern int   umask _G_ARGS((int)); /* commented out for now; wrong for SunOs4.1 */
extern int      unlink _G_ARGS((const char*));
D 2
extern _G_pid_t vfork _G_ARGS((void));
E 2
I 2
D 3
extern int 	vfork _G_ARGS((void));
E 3
I 3
D 6
extern _G_pid_t vfork _G_ARGS((void));
E 6
I 6
extern pid_t	vfork _G_ARGS((void));
E 6
E 3
E 2
extern int      vadvise _G_ARGS((int));
extern int      vhangup _G_ARGS((void));
D 2
extern _G_off_t lseek _G_ARGS((int, long, int));
E 2
I 2
D 6
extern _G_off_t lseek _G_ARGS((int, long long, int));
E 6
I 6
extern off_t lseek _G_ARGS((int, long long, int));
E 6
E 2
extern _G_ssize_t read _G_ARGS((int, void*, _G_size_t));
extern _G_ssize_t write _G_ARGS((int, const void*, _G_size_t));
extern int      access _G_ARGS((const char*, int));
#ifndef hpux
extern int      flock _G_ARGS((int, int));
#endif

}

#endif
E 1
