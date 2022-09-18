h04019
s 00002/00002/00058
d D 8.1 93/05/31 16:03:52 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00012/00000/00048
d D 5.3 90/04/30 21:24:09 bostic 3 2
c Berkeley headers, SCCS id's
e
s 00000/00002/00048
d D 5.2 89/03/05 20:28:46 bostic 2 1
c pwd.h needs sys/types.h 
e
s 00050/00000/00000
d D 5.1 89/03/05 20:28:25 bostic 1 0
c date and time created 89/03/05 20:28:25 by bostic
e
u
U
t
T
I 3
/*-
D 4
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * Ed James.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 3
I 1
/*
 * Copyright (c) 1987 by Ed James, UC Berkeley.  All rights reserved.
 *
 * Copy permission is hereby granted provided that this notice is
 * retained on all partial or complete copies.
 *
 * For more info on this and all of my stuff, mail edjames@berkeley.edu.
 */

#include <stdio.h>
#include <ctype.h>
D 2
#ifdef SYSV
E 2
#include <sys/types.h>
D 2
#endif
E 2
#include <pwd.h>

#ifdef BSD
#include <sgtty.h>
#include <sys/time.h>
#include <sys/file.h>
#endif

#ifdef SYSV
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/utsname.h>
#endif

#include <signal.h>
#include <math.h>

#include <curses.h>

#ifdef SYSV
#define	index	strchr
#define	rindex	strrchr
#define bcopy(a,b,c)	memcpy((b), (a), (c))
#define	bzero(a,b)	memset((a), '\0', (b))
#define	srandom	srand
#define	random	rand
#define	sgttyb	termio
#define	sg_erase c_cc[2]
#define	sg_kill c_cc[3]
#endif

#include "def.h"
#include "struct.h"
#include "extern.h"
#include "tunable.h"
E 1
