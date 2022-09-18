h29133
s 00000/00000/00066
d D 8.2 95/04/28 17:08:01 christos 12 11
c Updated to the latest version from the NetBSD source
e
s 00002/00002/00064
d D 8.1 93/06/06 15:14:36 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00000/00062
d D 5.10 93/05/24 14:45:32 bostic 10 9
c update, bug fix, ANSI C, lint from Christos Zoulas
c see SCCS/README.christos for details
e
s 00001/00011/00061
d D 5.9 90/06/01 17:07:29 bostic 9 8
c new copyright notice
e
s 00000/00003/00072
d D 5.8 90/03/17 14:28:03 bostic 8 7
c add pathnames.h, redefining some paths
e
s 00000/00008/00075
d D 5.7 90/03/12 09:54:55 bostic 7 6
c wire in DEF_OLD_VARS, still needs more work (oldVars variable)
e
s 00000/00007/00083
d D 5.6 90/03/12 09:37:24 bostic 6 5
c wire in '.' as include/define intro character
e
s 00002/00028/00088
d D 5.5 90/03/12 09:30:09 bostic 5 4
c Remove NEED_FD_SET, FD_SETSIZE, NO_WAIT3, NO_VFORK, LIBTOC
e
s 00000/00011/00116
d D 5.4 90/03/12 08:52:46 bostic 4 3
c remove directory locking, including the -l flag
e
s 00004/00042/00123
d D 5.3 90/03/12 08:42:35 bostic 3 2
c redo system makefile configuration for BSD
e
s 00024/00013/00141
d D 5.2 90/03/11 15:43:59 bostic 2 1
c add Berkeley specific copyright notice
e
s 00154/00000/00000
d D 5.1 90/03/11 15:43:07 bostic 1 0
c release 2.1 of pmake
e
u
U
t
T
I 1
D 2
/*-
 * config.h --
 *	Configuration constants for the local site.
E 2
I 2
/*
D 11
 * Copyright (c) 1988, 1989, 1990 The Regents of the University of California.
 * Copyright (c) 1988, 1989 by Adam de Boor
E 11
I 11
 * Copyright (c) 1988, 1989, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 * Copyright (c) 1989 by Berkeley Softworks
 * All rights reserved.
E 2
 *
D 2
 * Copyright (c) 1988 by the Regents of the University of California
 * Copyright (c) 1988 by Adam de Boor
E 2
I 2
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
E 2
 *
D 2
 * Permission to use, copy, modify, and distribute this
 * software and its documentation for any purpose and without
 * fee is hereby granted, provided that the above copyright
 * notice appears in all copies.  Neither the University of California nor
 * Adam de Boor makes any representations about the suitability of this
 * software for any purpose.  It is provided "as is" without
 * express or implied warranty.
E 2
I 2
D 9
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 9
I 9
 * %sccs.include.redist.c%
E 9
E 2
 *
D 2
 *	"$Id: config.h,v 1.4 89/11/14 17:54:56 adam Exp $ SPRITE (Berkeley)"
E 2
I 2
 *	%W% (Berkeley) %G%
 */

D 3
/*-
 * config.h --
 *	Configuration constants for the local site.
E 2
 */

/*
 * DEFSYSPATH
 *	Is the absolute path of the location of system makefiles.
 * SYSPATHDOC
 *	Documentation string to tell what the directory is.
 */
#define DEFSYSPATH	"/usr/public/lib/pmake"
#define SYSPATHDOC	"\tDirectory for system makefiles: /usr/public/lib/pmake"

/*
 * DEFSHELL
 *	The index of the default shell description in job.c. It indexes the
 *	'shells' table:
 *	    0	  	C Shell
 *	    1	  	Bourne Shell
 *	    2	  	Unknown
 * SHELLDOC
 *	Documentation string to tell what shell is used by default.
 */
#define DEFSHELL  	1
#define SHELLDOC  	"\tDefault shell: Bourne"

/*
 * DEFSHELLDIR
 *	The directory in which the C Shell and Bourne Shell are to be found.
 */
#define DEFSHELLDIR	"/bin"

/*
 * DEFSYSMK
 *	The absolute path of the default system makefile. It should probably
 *	be in DEFSYSPATH.
 * SYSMKDOC
 *	Documentation string to tell where the system makefile is.
 */
#define DEFSYSMK  	"/usr/public/lib/pmake/system.mk"
#define SYSMKDOC  	"\tSystem makefile: /usr/public/lib/pmake/system.mk"
E 3
I 3
#define	DEFSHELL	1			/* Bourne shell */
D 8
#define	DEFSHELLDIR	"/bin"			/* Bourne shell directory */
#define	DEFSYSMK  	"/usr/share/mk/sys.mk"	/* system makefile */
#define	DEFSYSPATH	"/usr/share/mk"		/* system makefile directory */
E 8
E 3

/*
 * DEFMAXJOBS
 * DEFMAXLOCAL
 *	These control the default concurrency. On no occasion will more
 *	than DEFMAXJOBS targets be created at once (locally or remotely)
 *	DEFMAXLOCAL is the highest number of targets which will be
 *	created on the local machine at once. Note that if you set this
 *	to 0, nothing will ever happen...
 */
#define DEFMAXJOBS	4
#define DEFMAXLOCAL	1

/*
 * INCLUDES
 * LIBRARIES
 *	These control the handling of the .INCLUDES and .LIBS variables.
 *	If INCLUDES is defined, the .INCLUDES variable will be filled
 *	from the search paths of those suffixes which are marked by
 *	.INCLUDES dependency lines. Similarly for LIBRARIES and .LIBS
 *	See suff.c for more details.
 */
#define INCLUDES
#define LIBRARIES

/*
D 4
 * LOCKFILE
 *	This is the name of the lock file which is created in the current
 *	directory if the -l flag isn't given.
 * DONT_LOCK
 *	If this is defined, directory locking will be off by default. The
 *	-l flag will then turn locking on.
 */
#define LOCKFILE  	"LOCK.make"
/*#define DONT_LOCK*/

/*
E 4
D 6
 * SPECIAL_CHAR
 *	The character that leads into conditionals and include directives
 *	and the like.
 */
#define SPECIAL_CHAR '#'

/*
E 6
D 7
 * DEF_OLD_VARS
 *	If defined, variable substitution follows the make style. PMake-style
 *	substitution cannot be turned on. In addition, pmake will never
 *	generate a warning for an undefined variable.
 */
/*#define DEF_OLD_VARS*/

/*
E 7
D 5
 * NEED_FD_SET
 *	Define this if your system doesn't define the fd_set type for select
 *	masks in <sys/types.h>
 *
 * FD_SETSIZE
 *	Define this to be the maximum number of files a process can have
 *	open at once. It defaults to 256.
 *
 * NO_WAIT3
 *	Define this if your system doesn't support the non-blocking wait3
 *	system call of BSD UNIX. This is not implemented yet.
 *
 * NO_VFORK
 *	Define this if your system doesn't support (or you shouldn't use)
 *	the vfork system call found in BSD UNIX.
 *
 * LIBTOC
 *	This is the name by which the table of contents in a ranlib'ed
 *	library is known. Some systems have changed it from __.SYMDEF,
 *	for whatever reason.
 *
E 5
 * LIBSUFF
 *	Is the suffix used to denote libraries and is used by the Suff module
 *	to find the search path on which to seek any -l<xx> targets.
 *
 * RECHECK
 *	If defined, Make_Update will check a target for its current
 *	modification time after it has been re-made, setting it to the
 *	starting time of the make only if the target still doesn't exist.
 *	Unfortunately, under NFS the modification time often doesn't
 *	get updated in time, so a target will appear to not have been
 *	re-made, causing later targets to appear up-to-date. On systems
 *	that don't have this problem, you should defined this. Under
 *	NFS you probably should not, unless you aren't exporting jobs.
 *
 * POSIX
 *	If the POSIX standard for Make is to be followed. There are
 *	several areas that I dislike, hence this constant.
 */
D 5
/*#define NEED_FD_SET*/
/*#define FD_SETSIZE 32*/
/*#define NO_WAIT3*/
/*#define NO_VFORK*/
#define LIBTOC	"__.SYMDEF"
#define LIBSUFF	".a"
#define RECHECK
E 5
I 5
#define	LIBSUFF	".a"
#define	RECHECK
I 10

#ifndef RANLIBMAG
#define RANLIBMAG "__.SYMDEF"
#endif
E 10
E 5
/*#define POSIX*/
E 1
