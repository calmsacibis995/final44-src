h16924
s 00005/00001/00174
d D 5.4 93/06/12 15:15:06 bostic 4 3
c get the X libraries from the standard place; from Mike Hibler
e
s 00018/00005/00157
d D 5.3 93/05/26 10:08:56 hibler 3 2
c one last unpdate
e
s 00035/00001/00127
d D 5.2 93/05/24 15:51:14 hibler 2 1
c reflect current state of 4.4
e
s 00128/00000/00000
d D 5.1 93/05/08 09:25:51 hibler 1 0
c date and time created 93/05/08 09:25:51 by hibler
e
u
U
t
T
I 1
D 3
/* Definitions file for GNU Emacs running on bsd 4.3
E 3
I 3
/* Definitions file for GNU Emacs running on bsd 4.4
E 3
   Copyright (C) 1985, 1986 Free Software Foundation, Inc.

This file is part of GNU Emacs.

GNU Emacs is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 1, or (at your option)
any later version.

GNU Emacs is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU Emacs; see the file COPYING.  If not, write to
the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.  */


I 2
D 3
/* This is brutal but we must get BIG_ENDIAN/LITTLE_ENDIAN defined now
   so we can be careful not to override the value in the m- file.
   Defining BIG_ENDIAN/LITTLE_ENDIAN with no value in that file will
   break, e.g. sys/wait.h.  */
E 3
I 3
/* Unfortunately, 4.4 and emacs have conflicting uses of BIG_ENDIAN
   and LITTLE_ENDIAN.  Emacs assumes BIG_ENDIAN will be defined for
   big endian machines and not defined for little endian machines.
   endian.h in 4.4 defines both as values with BYTE_ORDER taking on
   the appropriate one.  I see no way to reconcile the two.  Just
   using the values from endian.h will break a little endian machine
   since BIG_ENDIAN is also defined.  Undef'ing the values from
   endian.h (in the m- file) and redefining only one won't work since,
   for example, wait.h requires both be defined and have values.
   At the current time this is not a problem as we can hack around
   it.  Emacs' only use of BIG_ENDIAN is in lisp.h and then only
   if NO_UNION_TYPE is not defined.  By ensuring that NO_UNION_TYPE
   is defined, we avoid the issue.  We also include endian.h now to
   make sure that the m- file doesn't override the correct value (in
   the big endian case).  */

#define NO_UNION_TYPE
E 3
#ifndef YMAKEFILE
#include <machine/endian.h>
#endif

E 2
/*
 *	Define symbols to identify the version of Unix this is.
 *	Define all the symbols that apply correctly.
 */

#ifndef BSD4_4
D 2
#define BSD4_4
E 2
I 2
#define BSD4_4	1
E 2
#endif /* BSD4_4 */

#ifndef BSD4_3
#define BSD4_3
#endif /* BSD4_3 */

#ifndef BSD
#define BSD
#endif /* BSD */

/* SYSTEM_TYPE should indicate the kind of system you are using.
 It sets the Lisp variable system-type.  */

#define SYSTEM_TYPE "berkeley-unix"

/* nomultiplejobs should be defined if your system's shell
 does not have "job control" (the ability to stop a program,
 run some other program, then continue the first one).  */

/* #define NOMULTIPLEJOBS */

/* Do not use interrupt_input = 1 by default, because in 4.3
   we can make noninterrupt input work properly.  */

#undef INTERRUPT_INPUT

/* First pty name is /dev/ptyp0.  */

#define FIRST_PTY_LETTER 'p'
/*
 *	Define HAVE_TIMEVAL if the system supports the BSD style clock values.
 *	Look in <sys/time.h> for a timeval structure.
 */

#define HAVE_TIMEVAL
 
/*
 *	Define HAVE_SELECT if the system supports the `select' system call.
 */

#define HAVE_SELECT

/*
 *	Define HAVE_PTYS if the system supports pty devices.
 */

#define HAVE_PTYS

/* Define HAVE_SOCKETS if system supports 4.2-compatible sockets.  */

#define HAVE_SOCKETS

/*
 *	Define NONSYSTEM_DIR_LIBRARY to make Emacs emulate
 *      The 4.2 opendir, etc., library functions.
 */

/* #define NONSYSTEM_DIR_LIBRARY */

/* Define this symbol if your system has the functions bcopy, etc. */

#define BSTRING

/* subprocesses should be defined if you want to
   have code for asynchronous subprocesses
   (as used in M-x compile and M-x shell).
   This is generally OS dependent, and not supported
   under most USG systems. */

#define subprocesses

/* If your system uses COFF (Common Object File Format) then define the
   preprocessor symbol "COFF". */

/* #define COFF */

/* define MAIL_USE_FLOCK if the mailer uses flock
   to interlock access to /usr/spool/mail/$USER.
   The alternative is that a lock file named
   /usr/spool/mail/$USER.lock.  */

#define MAIL_USE_FLOCK

/* Define CLASH_DETECTION if you want lock files to be written
   so that Emacs can tell instantly when you try to modify
   a file that someone else has modified in his Emacs.  */

#define CLASH_DETECTION

/* We use the Berkeley (and usg5.2.2) interface to nlist.  */

#define NLIST_STRUCT

/* The file containing the kernel's symbol table is called /vmunix.  */

#define KERNEL_FILE "/vmunix"

/* The symbol in the kernel where the load average is found
   is named _avenrun.  */

#define LDAV_SYMBOL "_avenrun"
I 2

/* This macro determines the number of bytes waiting to be written
   in a FILE buffer.  */

D 4
#define PENDING_OUTPUT_COUNT(FILE) ((FILE)->_w - (FILE)->_bf._size)
E 4
I 4
#define PENDING_OUTPUT_COUNT(FILE) ((FILE)->_p - (FILE)->_bf._base)
E 4

/* Have POSIX setsid().  */

#define HAVE_SETSID

/* Have BSD getloadavg() library routine.  */

#define HAVE_GETLOADAVG

/* Use dkstat.h in loadst.  */

#define DKSTAT_HEADER_FILE

/* No special libg for debugging.  */

#define LIBS_DEBUG
I 4

/* X11 libraries, use R5.  */

#define LIB_X11_LIB -L/usr/X11R5/lib -lX11
E 4

/* Debugging unexec()ed code is hard enough as is, so why
   not make it a little harder.  */

#define C_DEBUG_SWITCH -g -traditional -O2
E 2
E 1
