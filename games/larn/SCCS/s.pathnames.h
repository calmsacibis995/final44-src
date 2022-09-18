h11716
s 00001/00001/00014
d D 5.2 95/04/27 16:28:19 bostic 3 1
c /usr/share shouldn't be written to during normal use, and has the wrong
c permissions to allow it anyway.
c From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00001/00006/00009
d R 5.2 91/06/18 17:52:23 sellgren 2 1
c old files moved into code/manpage etc, only score file changes
e
s 00010/00000/00000
d D 5.1 90/05/02 10:32:36 bostic 1 0
c date and time created 90/05/02 10:32:36 by bostic
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#define	_PATH_LOG		"/var/games/larn/llog12.0"
#define	_PATH_SCORE		"/var/games/larn/lscore12.0"
#define	_PATH_HELP		"/usr/share/games/larn/larn.help"
#define	_PATH_LEVELS		"/usr/share/games/larn/larnmaze"
#define	_PATH_FORTS		"/usr/share/games/larn/lfortune"
D 3
#define	_PATH_PLAYERIDS		"/usr/share/games/larn/playerids"
E 3
I 3
#define	_PATH_PLAYERIDS		"/var/games/larn/playerids"
E 3
E 1
