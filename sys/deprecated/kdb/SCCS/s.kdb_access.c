h61180
s 00006/00006/00028
d D 7.4 90/05/03 17:47:55 sklower 4 3
c first crack at torek changes, may need bug fixes
e
s 00011/00003/00023
d D 7.3 86/12/15 20:26:44 sam 3 2
c lint
e
s 00001/00001/00025
d D 7.2 86/11/20 14:42:23 sam 2 1
c put check back in
e
s 00026/00000/00000
d D 7.1 86/11/20 12:22:01 sam 1 0
c date and time created 86/11/20 12:22:01 by sam
e
u
U
t
T
I 1
D 3
/*	%M%	%I%	%E%	*/
E 3
I 3
/*
 * Copyright (c) 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	%W% (Berkeley) %G%
 */
E 3

/*
 * Access data in kernel address space.
 */

#include "../kdb/defs.h"

/*
 * Primitives: put a value in a space, get a value from a space
 * and get a word or byte not returning if an error occurred.
 */
I 3
/*ARGSUSED*/
E 3
D 4
put(addr, space, value) 
E 4
I 4
kdbput(addr, space, value) 
E 4
D 3
    off_t addr; { (void) kdbpoke(addr, value); }
E 3
I 3
    off_t addr; long value; { (void) kdbpoke((caddr_t)addr, value); }
E 3

I 3
/*ARGSUSED*/
E 3
u_int
D 4
get(addr, space)
E 4
I 4
kdbget(addr, space)
E 4
D 3
    off_t addr; { return (kdbpeek(addr)); };
E 3
I 3
    off_t addr; { return (kdbpeek((caddr_t)addr)); };
E 3

u_int
D 4
chkget(addr, space)
D 2
    off_t addr; { return (get(addr, space)); }
E 2
I 2
    off_t addr; { u_int w = get(addr, space); chkerr(); return (w); }
E 4
I 4
kdbchkget(addr, space)
    off_t addr; { u_int w = kdbget(addr, space); kdbchkerr(); return (w); }
E 4
E 2

u_int
D 4
bchkget(addr, space) 
    off_t addr; { return (byte(chkget(addr, space))); }
E 4
I 4
kdbbchkget(addr, space) 
    off_t addr; { return (byte(kdbchkget(addr, space))); }
E 4
E 1
