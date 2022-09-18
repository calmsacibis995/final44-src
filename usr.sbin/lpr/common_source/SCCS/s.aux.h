h36783
s 00007/00032/00034
d D 8.2 95/04/28 16:35:01 tef 2 1
c Add std copyright.
e
s 00066/00000/00000
d D 8.1 95/04/28 16:11:06 tef 1 0
c date and time created 95/04/28 16:11:06 by tef
e
u
U
t
T
I 1
/*
D 2
 * Auxillary stuff from 4.4BSD not found in some other systems
E 2
I 2
 * Copyright (c) 1995
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
D 2
 * !!!USE THIS FILE ONLY IF YOU ARE NOT RUNNING 4.4BSD!!!
E 2
I 2
 * %sccs.include.redist.c%
E 2
 */

D 2
/*-
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
I 2
/*
 * Auxillary functions to aid portability to other systems.
 * These are 4.4BSD routines that are often not found on other systems.
E 2
 *
D 2
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
E 2
I 2
 * !!!USE THIS FILE ONLY IF YOU ARE NOT RUNNING 4.4BSD!!!
E 2
 */

#ifdef PREPOSIX
#define dirent direct
extern int errno;
#endif

#ifdef NO_RINDEX
#define index strchr
#define rindex strrchr
#endif

#ifdef BSDWAIT
#define WAITARG_T(a)    ((int *)(a))
#else
#define WAITARG_T(a)    (a)
#endif

#ifdef SETPGID
#define setpgrp(a, b)   setpgid((pid_t)(a), (pid_t)(b))
#endif

#ifndef FD_COPY
#define FD_COPY(f, t) memcpy((char *)t, (char *)f, sizeof(*(f)))
#endif

#ifdef NO_SNPRINTF
int snprintf __P((char *str, size_t n, const char *fmt, ...));
#endif
E 1
