h47322
s 00001/00001/00023
d D 5.2 93/05/25 15:47:44 elan 2 1
c fix errlist for 4.4BSD compatibility
e
s 00024/00000/00000
d D 5.1 93/05/25 15:47:01 elan 1 0
c date and time created 93/05/25 15:47:01 by elan
e
u
U
t
T
I 1
#ifndef errno_h

extern "C" {

#ifdef __errno_h_recursive
#include_next <errno.h>
#else
#define __errno_h_recursive
#include_next <errno.h>

#define errno_h 1

D 2
extern char*    sys_errlist[];
E 2
I 2
extern const char* const    sys_errlist[];
E 2
extern int      sys_nerr;
#ifndef errno                  
extern int      errno;
#endif
void      perror(const char*);
char*     strerr(int);

#endif
}

#endif
E 1
