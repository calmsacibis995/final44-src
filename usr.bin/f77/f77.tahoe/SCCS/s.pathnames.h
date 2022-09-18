h57115
s 00003/00003/00068
d D 5.6 91/11/15 15:30:59 bostic 6 5
c move pcc into /usr/old
e
s 00009/00000/00062
d D 5.5 91/04/12 14:32:23 bostic 5 4
c new copyright; att/bsd/shared
e
s 00017/00018/00045
d D 5.4 90/09/05 17:41:49 sklower 4 3
c resolve differences with vax version
e
s 00019/00013/00044
d D 5.3 90/08/30 12:21:40 bostic 3 2
c add libcompat to library list; needed for [efg]cvt routines
e
s 00018/00012/00039
d D 5.2 89/05/10 22:22:02 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00051/00000/00000
d D 5.1 89/04/12 21:26:00 bostic 1 0
c date and time created 89/04/12 21:26:00 by bostic
e
u
U
t
T
I 5
/*-
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.proprietary.c%
 *
 *	%W% (Berkeley) %G%
 */

E 5
I 1
/*
 * drivedefs.h
 *
 * Definitions for Fortran 77 Compiler driver
 * For the VAX, running on the VAX
 *
 * UCSD Chemistry modification history:
 *
 * $Log:	drivedefs.h,v $
 * Revision 1.4  85/02/12  19:25:05  donn
 * Added 'CATNAME' to define the name of the concatenation command.
 * 
 * Revision 1.3  85/01/14  06:42:01  donn
 * Changed to use c2 as the peephole optimizer.
 * 
 * Revision 1.2  84/04/11  19:02:16  donn
 * Added Dave Wasley's fix to load the Unix library (libU77.a) first.
 * 
 */

D 4
#if HERE!=TAHOE || TARGET!=TAHOE|| FAMILY!=PCC
E 4
I 4
#if HERE!=TARGET || FAMILY!=PCC || (HERE!=VAX && HERE!=TAHOE)
E 4
	Wrong Definitions File!
#endif

D 2
#define PASS1NAME	"/usr/lib/f77pass1"
#define PASS2NAME	"/lib/f1"
E 2
I 2
#define	PASS1NAME	"/usr/libexec/f77pass1"
#define	PASS2NAME	"/usr/libexec/f1"
E 2
#ifdef INLINE
D 2
#define	PASS2INAME	"/usr/lib/if1"
#endif INLINE
#define PASS2OPT	"/lib/c2"
#define ASMNAME		"/bin/as"
#define LDNAME		"/bin/ld"
E 2
I 2
#define	PASS2INAME	"/usr/libexec/if1"
#endif
D 6
#define	PASS2OPT	"/usr/libexec/c2"
#define	ASMNAME		"/usr/bin/as"
#define	LDNAME		"/usr/bin/ld"
E 6
I 6
#define	PASS2OPT	"/usr/old/libexec/c2"
#define	ASMNAME		"/usr/old/bin/as"
#define	LDNAME		"/usr/old/bin/ld"
E 6
D 4
#define	_PATH_UBIN	"/usr/bin"
E 4
E 2
#define	CATNAME		"/bin/cat"
D 2
#define FOOTNAME	"/lib/crt0.o"
#define PROFFOOT	"/lib/mcrt0.o"
#define	GPRFFOOT	"/usr/lib/gcrt0.o"
#define TEMPPREF	"fort"
E 2
I 2
D 4
#define FOOTNAME	"/usr/lib/crt0.o"
E 4
I 4
#define	FOOTNAME	"/usr/lib/crt0.o"
E 4
#define	PROFFOOT	"/usr/lib/mcrt0.o"
#define	GPRFFOOT	"/usr/lib/gcrt0.o"
#define	TEMPPREF	"fort"
E 2

D 3
static char *liblist [ ] =
		{ "/usr/lib/libU77.a", 
		  "/usr/lib/libF77.a", 
		  "/usr/lib/libI77.a", 
		  "/usr/lib/libm.a", 
D 2
		  "/lib/libc.a",NULL };
E 2
I 2
		  "/usr/lib/libc.a",NULL };
E 2
static char *p_liblist [ ] =
		{ "/usr/lib/libU77_p.a", 
		  "/usr/lib/libF77_p.a", 
		  "/usr/lib/libI77_p.a", 
		  "/usr/lib/libF77_p.a", 
		  "/usr/lib/libm_p.a", 
		  "/usr/lib/libc_p.a",NULL };
E 3
I 3
D 4
static char *liblist [ ] = {
	"/usr/lib/libU77.a",
	"/usr/lib/libF77.a",
	"/usr/lib/libI77.a",
	"/usr/lib/libm.a",
	"/usr/lib/libc.a",
	"/usr/lib/libcompat.a",
E 4
I 4
static char *liblist [] = {
	"-lU77",
	"-lF77",
	"-lI77",
	"-lm",
	"-lcompat",
	"-lc",
E 4
	NULL
};
D 4
static char *p_liblist [ ] = {
	"/usr/lib/libU77_p.a",
	"/usr/lib/libF77_p.a",
	"/usr/lib/libI77_p.a",
	"/usr/lib/libF77_p.a",
	"/usr/lib/libm_p.a",
	"/usr/lib/libc_p.a",
	"/usr/lib/libcompat_p.a",
E 4
I 4
static char *p_liblist [] = {
	"-lU77_p",
	"-lF77_p",
	"-lI77_p",
	"-lm_p",
	"-lcompat_p",
	"-lc_p",
E 4
	NULL
};
E 3
I 2

#include <paths.h>

#define	_PATH_BSHELL	"/bin/sh"
#define	_PATH_CPP	"/usr/bin/cpp"
I 4
#define	_PATH_UBIN	"/usr/bin"
E 4
E 2
E 1
