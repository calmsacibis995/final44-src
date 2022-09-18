h54962
s 00004/00004/00034
d D 1.3 94/08/13 13:56:09 bostic 3 2
c more types problems, make it compile again
e
s 00001/00001/00037
d D 1.2 93/05/25 15:31:57 elan 2 1
c support for 4.4BDS
e
s 00038/00000/00000
d D 1.1 93/02/25 13:55:11 elan 1 0
c date and time created 93/02/25 13:55:11 by elan
e
u
U
t
T
I 1
#ifndef __libgxx_sys_wait_h

#include <_G_config.h>

extern "C" {
#ifdef __sys_wait_h_recursive
#include_next <sys/wait.h>
#else
#define __sys_wait_h_recursive


#if _G_HAVE_SYS_WAIT
#ifdef VMS
#include "GNU_CC_INCLUDE:[sys]wait.h"
#else
#include_next <sys/wait.h>
#endif
#else /* !_G_HAVE_SYS_WAIT */
/* Traditional definitions. */
#define WEXITSTATUS(status) (((x) >> 8) & 0xFF)
#define WIFSTOPPED(x) (((x) & 0xFF) == 0177)
#define WIFEXITED(x) (! WIFSTOPPED(x) && WTERMSIG(x) == 0)
#define WIFSIGNALED(x) (! WIFSTOPPED(x) && WTERMSIG(x) != 0)
#define WTERMSIG(status) ((x) & 0x7F)
#define WSTOPSIG(status) (((x) >> 8) & 0xFF)
#endif /* !_G_HAVE_SYS_WAIT */

#define __libgxx_sys_wait_h 1

struct rusage;
D 3
extern _G_pid_t wait _G_ARGS((int*));
extern _G_pid_t waitpid _G_ARGS((_G_pid_t, int*, int));
extern _G_pid_t wait3 _G_ARGS((int*, int options, struct rusage*));
D 2
extern _G_pid_t wait4 _G_ARGS((int, int*, int, struct rusage*));
E 2
I 2
extern _G_pid_t wait4 _G_ARGS((_G_pid_t, int*, int, struct rusage*));
E 3
I 3
extern pid_t wait _G_ARGS((int*));
extern pid_t waitpid _G_ARGS((pid_t, int*, int));
extern pid_t wait3 _G_ARGS((int*, int options, struct rusage*));
extern pid_t wait4 _G_ARGS((pid_t, int*, int, struct rusage*));
E 3
E 2
#endif
}

#endif
E 1
