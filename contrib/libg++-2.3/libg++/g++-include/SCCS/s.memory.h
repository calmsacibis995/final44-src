h34226
s 00001/00001/00041
d D 1.2 93/05/25 15:30:18 elan 2 1
c support for 4.4BSD
e
s 00042/00000/00000
d D 1.1 93/02/23 15:57:03 elan 1 0
c date and time created 93/02/23 15:57:03 by elan
e
u
U
t
T
I 1

#ifndef _memory_h
#define _memory_h 1

#include "_G_config.h"
#include <stddef.h>

extern "C" {

void*     memalign _G_ARGS((_G_size_t, _G_size_t));
void*     memccpy _G_ARGS((void*, const void*, int, _G_size_t));
void*     memchr _G_ARGS((const void*, int, _G_size_t));
int       memcmp _G_ARGS((const void*, const void*, _G_size_t));
void*     memcpy _G_ARGS((void*, const void*, _G_size_t));
void*     memmove _G_ARGS((void*, const void*, _G_size_t));
void*     memset _G_ARGS((void*, int, _G_size_t));
int       ffs _G_ARGS((int));
#ifdef __OSF1__
int	  getpagesize _G_ARGS((void));
#else
D 2
_G_size_t    getpagesize _G_ARGS((void));
E 2
I 2
const int    getpagesize _G_ARGS((void));
E 2
#endif
void*     valloc _G_ARGS((_G_size_t));

void      bcopy _G_ARGS((const void*, void*, _G_size_t));
int       bcmp _G_ARGS((const void*, const void*, int));
void      bzero _G_ARGS((void*, int));
}

#ifdef __GNUG__
#ifndef alloca
#define alloca(x)  __builtin_alloca(x)
#endif
#else
#ifndef IV
extern "C" void* alloca(_G_size_t);
#else
extern "C" void* alloca(unsigned long);
#endif /* IV */
#endif

#endif
E 1
