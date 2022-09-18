h50386
s 00004/00004/00045
d D 1.4 94/04/04 12:17:27 bostic 4 3
c one more try, with feeling
e
s 00006/00006/00043
d D 1.3 94/04/04 11:48:44 bostic 3 2
c match the real 4.4BSD include file for recv, recvfrom, recvmsg,
c send, sendto, sedmsg
e
s 00006/00006/00043
d D 1.2 93/05/25 15:31:56 elan 2 1
c support for 4.4BDS
e
s 00049/00000/00000
d D 1.1 93/02/24 15:26:40 elan 1 0
c date and time created 93/02/24 15:26:40 by elan
e
u
U
t
T
I 1
#ifndef __libgxx_sys_socket_h

#include <_G_config.h>

extern "C"
{
#ifdef __sys_socket_h_recursive
#include_next <sys/socket.h>
#else
#define __sys_socket_h_recursive
#include <time.h>

#ifdef VMS
#include "GNU_CC_INCLUDE:[sys]socket.h"
#else
#include_next <sys/socket.h>
#endif

#define __libgxx_sys_socket_h 1

// void* in select, since different systems use int* or fd_set*
D 2
int       select _G_ARGS((int, void*, void*, void*, struct timeval*));
E 2
I 2
int       select _G_ARGS((int, fd_set*, fd_set*, fd_set*, struct timeval*));
E 2

int       accept _G_ARGS((int, struct sockaddr*, int*));
D 2
int       bind _G_ARGS((int, const void*, int));
int       connect _G_ARGS((int, struct sockaddr*, int));
E 2
I 2
int       bind _G_ARGS((int, const struct sockaddr*, int));
int       connect _G_ARGS((int, const struct sockaddr*, int));
E 2
int       getsockname _G_ARGS((int, struct sockaddr*, int*));
int       getpeername _G_ARGS((int, struct sockaddr*, int*));
int       getsockopt(int, int, int, void*, int*);
int       listen(int, int);
#ifndef hpux
int       rcmd _G_ARGS((char**, int, const char*, const char*, const char*, int*));
#endif
D 3
int       recv(int, void*, int, int);
D 2
int       recvfrom _G_ARGS((int, void*, int, int, void*, int *));
E 2
I 2
int       recvfrom _G_ARGS((int, void*, int, int, struct sockaddr *, int *));
E 2
int       recvmsg(int, struct msghdr*, int);
E 3
I 3
D 4
ssize_t	  recv(int, void*, int, int);
ssize_t	  recvfrom _G_ARGS((int, void*, int, int, struct sockaddr *, int *));
E 4
I 4
ssize_t	  recv(int, void*, size_t, int);
ssize_t	  recvfrom _G_ARGS((int, void*, size_t, int, struct sockaddr *, int *));
E 4
ssize_t	  recvmsg(int, struct msghdr*, int);
E 3
int       rexec(char**, int, const char*, const char*, const char*, int*);
int       rresvport(int*);
D 3
int       send _G_ARGS((int, const void*, int, int));
D 2
int       sendto _G_ARGS((int, const void*, int, int, void*, int));
E 2
I 2
int       sendto _G_ARGS((int, const void*, int, int, const struct sockaddr*, int));
E 2
int       sendmsg _G_ARGS((int, const struct msghdr*, int));
E 3
I 3
D 4
ssize_t	  send _G_ARGS((int, const void*, int, int));
ssize_t	  sendto _G_ARGS((int, const void*, int, int, const struct sockaddr*, int));
E 4
I 4
ssize_t	  send _G_ARGS((int, const void*, size_t, int));
ssize_t	  sendto _G_ARGS((int, const void*, size_t, int, const struct sockaddr*, int));
E 4
ssize_t	  sendmsg _G_ARGS((int, const struct msghdr*, int));
E 3
D 2
int       setsockopt _G_ARGS((int, int, int, const char*, int));
E 2
I 2
int       setsockopt _G_ARGS((int, int, int, const void *, int));
E 2
int       shutdown(int, int);
int       socket(int, int, int);
int       socketpair(int, int, int, int sv[2]);
#endif
}

#endif
E 1
