h29548
s 00005/00005/00272
d D 8.1 93/06/09 22:54:17 bostic 37 36
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00009/00273
d D 5.22 93/02/11 15:34:46 elan 36 35
c Changed entry processing since termcap entries no longer have 
c the prefix of 2 characters.
e
s 00001/00000/00281
d D 5.21 92/07/08 12:01:02 pendry 35 34
c need to include <sys/ioctl.h> to get definition of TIOCGWINSZ et al.
e
s 00034/00031/00247
d D 5.20 91/12/28 16:47:18 bostic 34 33
c add -S option back in
e
s 00036/00022/00242
d D 5.19 91/12/24 10:33:36 bostic 33 32
c add the -a, -d, -p and -r options back in
e
s 00172/01462/00092
d D 5.18 91/12/22 18:57:38 bostic 32 31
c broken up into multiple modules -- rewrite lots of it, reorganize the
c rest.  No longer diffable, but hopefully at least understandable
e
s 00808/01312/00746
d D 5.17 91/12/18 13:13:35 marc 31 30
c checked in for Marc (Keith Bostic)
e
s 00002/00003/02056
d D 5.16 91/03/02 23:38:39 donn 30 29
c Fixed pinhead code that went out of its way to write on a string.
e
s 00002/00001/02057
d D 5.15 91/03/02 10:24:56 bostic 29 28
c ANSI
e
s 00002/00002/02056
d D 5.14 90/06/18 12:06:23 bostic 28 27
c CFLUSH -> CDISCARD
e
s 00001/00011/02057
d D 5.13 90/06/01 17:48:20 bostic 27 26
c new copyright notice
e
s 00001/00001/02067
d D 5.12 88/07/22 16:41:09 bostic 26 25
c ANSIfication
e
s 00010/00005/02058
d D 5.11 88/06/29 18:54:56 bostic 25 24
c install approved copyright notice
e
s 00010/00004/02053
d D 5.10 88/05/05 18:05:32 bostic 24 23
c written by Eric Allman; add Berkeley specific header
e
s 00002/00002/02055
d D 5.9 88/01/03 00:46:50 bostic 23 22
c fix external declarations for ANSI C
e
s 00002/00006/02055
d D 5.8 86/04/28 08:24:37 lepreau 22 21
c local mode word wasn't getting fixed on reset
e
s 00064/00056/01997
d D 5.7 86/03/29 12:50:15 bloom 21 20
c make it lint as we compile it (I should get rid of the other junk.  Maybe
c I could find the code we are using then.)
e
s 00097/00063/01956
d D 5.6 86/03/29 11:34:45 bloom 20 19
c change macro for control characters, use system predefined values as much as
c possible, fix usage message for settable interrupt, merge in reset code from
c /usr/ucb/reset (from when different), change defaults to agree with kernel
c defaults, always set window size if not previously set, use initialization
c information from termcap if reset info doesn't exist (rs->is, rf->if)
c 	(Major portion of work done by Serge)
e
s 00006/00006/02013
d D 5.5 85/09/16 14:45:36 mckusick 19 18
c interrupt has two r's
e
s 00064/00007/01955
d D 5.4 85/09/15 15:54:43 bloom 18 17
c don't set window size if both rows and columns are not specified,
c add setable interupt character
e
s 00002/00000/01960
d D 5.3 85/08/05 11:17:49 bloom 17 16
c define UCB_NTTY
e
s 00006/00003/01954
d D 5.2 85/06/19 13:51:35 bloom 16 14
c only set window size if not previously set
e
s 00005/00002/01955
d R 5.2 85/06/19 13:44:19 bloom 15 14
c only set window size if not set
e
s 00013/00001/01944
d D 5.1 85/06/06 09:26:15 dist 14 13
c Add copyright
e
s 00003/00006/01942
d D 1.13 85/05/11 01:26:26 edward 13 12
c don't check for row == 0 col == 0 before setting window size
e
s 00015/00003/01933
d D 1.12 85/02/21 11:30:12 bloom 12 11
c set window size when setting environment
e
s 00004/00002/01932
d D 1.11 85/01/10 17:03:48 serge 11 10
c if doing setenv keep prompting while terminal type is unknown
e
s 00001/00001/01933
d D 1.10 84/06/04 13:26:20 ralph 10 9
c fix parameter type of flags to setdelay().
e
s 00017/00046/01917
d D 1.9 84/05/07 11:57:09 root 9 8
c uses new getttyent(3) routines.
e
s 00005/00000/01958
d D 1.8 84/03/15 14:53:36 edward 8 7
c use aliases in -m mapping
e
s 00001/00001/01957
d D 1.7 83/12/19 15:27:49 ralph 7 6
c fixed to read environment if no default type.
e
s 00003/00002/01955
d D 1.6 83/08/11 22:47:06 sam 6 5
c standardize sccs keyword lines
e
s 00001/00001/01956
d D 1.5 83/06/07 12:56:07 mckusick 5 4
c increase size of typebuf per Bob Gray
e
s 00003/00003/01954
d D 1.4 83/03/10 19:20:56 sam 4 3
c from shannon
e
s 00001/00000/01956
d D 1.3 82/12/13 21:04:33 sam 3 2
c shutup CTRL redefined
e
s 00745/00178/01211
d D 1.2 81/11/22 16:58:14 root 2 1
c new version with tabs, CB virt term, other enhancements (MRH)
e
s 01389/00000/00000
d D 1.1 81/11/22 16:52:50 root 1 0
c date and time created 81/11/22 16:52:50 by root
e
u
U
t
T
I 14
D 32
/*
 * Copyright (c) 1980 Regents of the University of California.
E 32
I 32
/*-
D 37
 * Copyright (c) 1980, 1991 The Regents of the University of California.
E 32
D 24
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 24
I 24
 * All rights reserved.
E 37
I 37
 * Copyright (c) 1980, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 37
 *
D 27
 * Redistribution and use in source and binary forms are permitted
D 25
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 25
I 25
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 27
I 27
 * %sccs.include.redist.c%
E 27
E 25
E 24
 */

E 14
I 2
D 6
#
D 4
	char	id_tset[] = "@(#)tset.c	1.2";
E 4
I 4
	char	id_tset[] = "%W% %G%";
E 6
I 6
#ifndef lint
I 14
D 37
char copyright[] =
D 32
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 32
I 32
"%Z% Copyright (c) 1980, 1991 The Regents of the University of California.\n\
E 32
 All rights reserved.\n";
E 37
I 37
static char copyright[] =
"%Z% Copyright (c) 1980, 1991, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 37
D 24
#endif not lint
E 24
I 24
#endif /* not lint */
E 24

#ifndef lint
E 14
D 31
static char sccsid[] = "%W% (Berkeley) %G%";
E 31
I 31
D 32
static char sccsid[] = "@(#)tset.c	5.13 (Berkeley) 6/1/90";
E 32
I 32
static char sccsid[] = "%W% (Berkeley) %G%";
E 32
E 31
D 14
#endif
E 14
I 14
D 24
#endif not lint
E 24
I 24
#endif /* not lint */
E 24
E 14
E 6
E 4

E 2
I 1
D 32
/*
D 2
# define DEB
/*
E 2
**  TSET -- set terminal modes
**
**	This program does sophisticated terminal initialization.
D 20
**	I recommend that you include it in your .start_up or .login
E 20
I 20
**	I recommend that you include it in your .profile or .login
E 20
**	file to initialize whatever terminal you are on.
**
**	There are several features:
**
D 20
**	A special file or sequence (as controlled by the ttycap file)
E 20
I 20
**	A special file or sequence (as controlled by the termcap file)
E 20
**	is sent to the terminal.
**
D 31
**	Mode bits are set on a per-terminal_type basis (much better
**	than UNIX itself).  This allows special delays, automatic
**	tabs, etc.
E 31
I 31
**	Mode bits are set on a per-terminal_type basis.
**	This allows special delays, automatic tabs, etc.
E 31
**
**	Erase and Kill characters can be set to whatever you want.
**	Default is to change erase to control-H on a terminal which
**	can overstrike, and leave it alone on anything else.  Kill
**	is always left alone unless specifically requested.  These
**	characters can be represented as "^X" meaning control-X;
**	X is any character.
**
**	Terminals which are dialups or plugboard types can be aliased
**	to whatever type you may have in your home or office.  Thus,
**	if you know that when you dial up you will always be on a
**	TI 733, you can specify that fact to tset.  You can represent
**	a type as "?type".  This will ask you what type you want it
**	to be -- if you reply with just a newline, it will default
**	to the type given.
**
D 20
**	The htmp file, used by ex, etc., can be updated.
**
E 20
**	The current terminal type can be queried.
**
**	Usage:
D 20
**		tset [-] [-EC] [-eC] [-kC] [-s] [-h] [-u] [-r]
E 20
I 20
D 31
**		tset [-] [-EC] [-eC] [-kC] [-iC] [-s] [-h] [-u] [-r]
E 20
**			[-m [ident] [test baudrate] :type]
**			[-Q] [-I] [-S] [type]
E 31
I 31
**		tset [-] [-hnrsIQS] [-eC] [-iC] [-kC] [-EC]
**		[-m [port-type][test baudrate]:terminal-type] [terminal-type]
E 31
**
**		In systems with environments, use:
D 2
**			`tset -s ...`
**		Actually, this doesn't work because of a shell bug.
E 2
I 2
**			eval `tset -s ...`
**		Actually, this doesn't work in old csh's.
E 2
**		Instead, use:
**			tset -s ... > tset.tmp
**			source tset.tmp
**			rm tset.tmp
**		or:
**			set noglob
**			set term=(`tset -S ....`)
**			setenv TERM $term[1]
**			setenv TERMCAP "$term[2]"
**			unset term
**			unset noglob
**
**	Positional Parameters:
**		type -- the terminal type to force.  If this is
**			specified, initialization is for this
**			terminal type.
**
**	Flags:
**		- -- report terminal type.  Whatever type is
**			decided on is reported.  If no other flags
**			are stated, the only affect is to write
**			the terminal type on the standard output.
**		-r -- report to user in addition to other flags.
**		-EC -- set the erase character to C on all terminals
**			except those which cannot backspace (e.g.,
D 31
**			a TTY 33).  C defaults to control-H.
E 31
I 31
**			a TTY 33).
E 31
**		-eC -- set the erase character to C on all terminals.
D 20
**			C defaults to control-H.  If neither -E or -e
**			are specified, the erase character is set to
**			control-H if the terminal can both backspace
**			and not overstrike (e.g., a CRT).  If the erase
**			character is NULL (zero byte), it will be reset
**			to '#' if nothing else is specified.
E 20
I 20
D 31
**			C defaults to control-H.  If not specified,
E 31
I 31
**			If not specified,
E 31
**			the erase character is untouched; however, if
**			not specified and the erase character is NULL
**			(zero byte), the erase character  is set to delete.
E 20
**		-kC -- set the kill character to C on all terminals.
D 31
**			Default for C is control-X.  If not specified,
E 31
I 31
**			If not specified,
E 31
**			the kill character is untouched; however, if
**			not specified and the kill character is NULL
D 20
**			(zero byte), the kill character is set to '@'.
E 20
I 20
**			(zero byte), the kill character is set to control-U.
E 20
D 18
**		-iC -- reserved for setable interrupt character.
E 18
I 18
D 19
**		-iC -- set the interupt character to C on all terminals.
E 19
I 19
**		-iC -- set the interrupt character to C on all terminals.
E 19
D 20
			Default for C is Delete.  If not specified, the
D 19
			interupt character is untouched; however, if
E 19
I 19
			interrupt character is untouched; however, if
E 19
			not specified and the kill character is NULL
D 19
			(zero byte), the interupt character is set to
E 19
I 19
			(zero byte), the interrupt character is set to
E 19
			Delete.
E 20
I 20
D 31
**			Default for C is control-C.  If not specified, the
E 31
I 31
**			If not specified, the
E 31
**			interrupt character is untouched; however, if
**			not specified and the interrupt character is NULL
**			(zero byte), the interrupt character is set to
**			control-C.
E 20
E 18
D 31
**		-qC -- reserved for setable quit character.
E 31
I 31
**		-qC -- reserved for settable quit character.
E 31
**		-m -- map the system identified type to some user
**			specified type. The mapping can be baud rate
**			dependent. This replaces the old -d, -p flags.
**			(-d type  ->  -m dialup:type)
**			(-p type  ->  -m plug:type)
**			Syntax:	-m identifier [test baudrate] :type
D 9
**			where: ``identifier'' is whatever is found in
**			/etc/ttytype for this port, (abscence of an identifier
E 9
I 9
**			where: ``identifier'' is terminal type found in
D 31
**			/etc/ttys for this port, (abscence of an identifier
E 9
**			matches any identifier); ``test'' may be any combination
**			of  >  =  <  !  @; ``baudrate'' is as with stty(1);
**			``type'' is the actual terminal type to use if the
**			mapping condition is met. Multiple maps are scanned
**			in order and the first match prevails.
I 2
**		-n -- If the new tty driver from UCB is available, this flag
**			will activate the new options for erase and kill
**			processing. This will be different for printers
**			and crt's. For crts, if the baud rate is < 1200 then
**			erase and kill don't remove characters from the screen.
E 2
**		-h -- don't read htmp file.  Normally the terminal type
**			is determined by reading the htmp file or the
**			environment (unless some mapping is specified).
**			This forces a read of the ttytype file -- useful
D 2
**			when htmp is somehow wrong.
E 2
I 2
**			when htmp is somehow wrong. (V6 only)
E 2
**		-u -- don't update htmp.  It seemed like this should
**			be put in.  Note that htmp is never actually
**			written if there are no changes, so don't bother
**			bother using this for efficiency reasons alone.
E 31
I 31
**			/etc/ttys for this port, (absence of an identifier
**			matches any identifier); ``test'' may be any
**			combination of  >  =  <  !  @; ``baudrate'' is as with
**			stty (1); ``type'' is the actual terminal type to use
**			if the mapping condition is met. Multiple maps are
**			scanned in order and the first match prevails.
**		-h -- don't read terminal type from environment.
E 31
**		-s -- output setenv commands for TERM.  This can be
**			used with
**				`tset -s ...`
**			and is to be prefered to:
**				setenv TERM `tset - ...`
**			because -s sets the TERMCAP variable also.
**		-S -- Similar to -s but outputs 2 strings suitable for
**			use in csh .login files as follows:
**				set noglob
**				set term=(`tset -S .....`)
**				setenv TERM $term[1]
**				setenv TERMCAP "$term[2]"
**				unset term
**				unset noglob
**		-Q -- be quiet.  don't output 'Erase set to' etc.
**		-I -- don't do terminal initialization (is & if
**			strings).
I 2
D 31
**		-v -- On virtual terminal systems, don't set up a
**			virtual terminal.  Otherwise tset will tell
**			the operating system what kind of terminal you
**			are on (if it is a known terminal) and fix up
**			the output of -s to use virtual terminal sequences.
E 31
E 2
**
**	Files:
D 9
**		/etc/ttytype
E 9
I 9
**		/etc/ttys
E 9
**			contains a terminal id -> terminal type
**			mapping; used when any user mapping is specified,
**			or the environment doesn't have TERM set.
**		/etc/termcap
**			a terminal_type -> terminal_capabilities
**			mapping.
**
D 31
**	Return Codes:
**		-1 -- couldn't open ttycap.
**		1 -- bad terminal type, or standard output not tty.
E 31
I 31
**	Exit Codes:
**		2 -- couldn't open termcap.
**		1 -- invalid terminal type, or standard error not tty.
E 31
**		0 -- ok.
**
D 31
**	Defined Constants:
D 2
**		DIALUP -- the type code for a dialup port
**		PLUGBOARD -- the code for a plugboard port.
**		ARPANET -- the code for an arpanet port.
E 2
I 2
**		DIALUP -- the type code for a dialup port.
**		PLUGBOARD -- the type code for a plugboard port.
**		ARPANET -- the type code for an arpanet port.
E 2
**		BACKSPACE -- control-H, the default for -e.
D 2
**		CONTROLX -- control-X, the default for -k.
E 2
I 2
D 20
**		CTRL('X') -- control-X, the default for -k.
E 20
I 20
**		CNTL('X') -- control-X, the default for -k.
E 20
E 2
**		OLDERASE -- the system default erase character.
**		OLDKILL -- the system default kill character.
**		FILEDES -- the file descriptor to do the operation
**			on, nominally 1 or 2.
**		STDOUT -- the standard output file descriptor.
**		UIDMASK -- the bit pattern to mask with the getuid()
**			call to get just the user id.
**		GTTYN -- defines file containing generalized ttynames
**			and compiles code to look there.
**
**	Requires:
D 9
**		Routines to handle htmp, ttytype, and ttycap.
E 9
I 9
**		Routines to handle htmp, ttys, and ttycap.
E 9
**
**	Compilation Flags:
D 2
**		OLDDIALUP -- accept the -d flag. Map "sd" to "dialup".
**		OLDPLUGBOARD -- accept the -p flag. Map "sp" to "plugboard".
**		OLDARPANET -- accept the -a flag. Map "sa" to "arpanet".
E 2
**		OLDFLAGS -- must be defined to compile code for any of
**			the -d, -p, or -a flags.
I 2
**		OLDDIALUP -- accept the -d flag.
**		OLDPLUGBOARD -- accept the -p flag.
**		OLDARPANET -- accept the -a flag.
E 2
D 9
**		FULLLOGIN -- if defined, login sets the ttytype from
**			/etc/ttytype file.
E 9
**		V6 -- if clear, use environments, not htmp.
**			also use TIOCSETN rather than stty to avoid flushing
D 9
**		GTTYN -- if set, compiles code to look at /etc/ttytype.
E 9
I 9
**		GTTYN -- if set, compiles code to look at /etc/ttys.
E 9
I 2
**		UCB_NTTY -- set to handle new tty driver modes.
E 2
**
**	Trace Flags:
**		none
**
**	Diagnostics:
**		Bad flag
**			An incorrect option was specified.
**		Too few args
**			more command line arguments are required.
**		Unexpected arg
**			wrong type of argument was encountered.
**		Cannot open ...
**			The specified file could not be openned.
**		Type ... unknown
**			An unknown terminal type was specified.
**		Cannot update htmp
**			Cannot update htmp file when the standard
**			output is not a terminal.
**		Erase set to ...
**			Telling that the erase character has been
**			set to the specified character.
**		Kill set to ...
**			Ditto for kill
**		Erase is ...    Kill is ...
**			Tells that the erase/kill characters were
**			wierd before, but they are being left as-is.
**		Not a terminal
**			Set if FILEDES is not a terminal.
**
**	Compilation Instructions:
**		cc -n -O tset.c -ltermlib
**		mv a.out tset
**		chown bin tset
**		chmod 4755 tset
**
**		where 'bin' should be whoever owns the 'htmp' file.
**		If 'htmp' is 666, then tset need not be setuid.
**
I 2
**		For version 6 the compile command should be:
**		cc -n -O -I/usr/include/retrofit tset.c -ltermlib -lretro -lS
**
E 31
E 2
**	Author:
**		Eric Allman
**		Electronics Research Labs
**		U.C. Berkeley
**
**	History:
D 2
**		7/80 -- '-S' added. -m mapping added. TERMCAP string
E 2
I 2
**		1/81 -- Added alias checking for mapping identifiers.
**		9/80 -- Added UCB_NTTY mods to setup the new tty driver.
**			Added the 'reset ...' invocation.
**		7/80 -- '-S' added. '-m' mapping added. TERMCAP string
E 2
**			cleaned up.
**		3/80 -- Changed to use tputs.  Prc & flush added.
**		10/79 -- '-s' option extended to handle TERMCAP
**			variable, set noglob, quote the entry,
**			and know about the Bourne shell.  Terminal
**			initialization moved to before any information
**			output so screen clears would not screw you.
**			'-Q' option added.
**		8/79 -- '-' option alone changed to only output
**			type.  '-s' option added.  'VERSION7'
**			changed to 'V6' for compatibility.
**		12/78 -- modified for eventual migration to VAX/UNIX,
**			so the '-' option is changed to output only
**			the terminal type to STDOUT instead of
D 9
**			FILEDES.  FULLLOGIN flag added.
E 9
I 9
**			FILEDES.
E 9
**		9/78 -- '-' and '-p' options added (now fully
**			compatible with ttytype!), and spaces are
**			permitted between the -d and the type.
**		8/78 -- The sense of -h and -u were reversed, and the
**			-f flag is dropped -- same effect is available
**			by just stating the terminal type.
**		10/77 -- Written.
*/

E 32
I 17
D 31
#define UCB_NTTY
E 31
I 31
#include <sys/types.h>
I 35
#include <sys/ioctl.h>
E 35
D 32
#include <stdio.h>
#include <ttyent.h>
E 32
#include <termios.h>
I 32
#include <errno.h>
E 32
#include <unistd.h>
#include <stdlib.h>
D 32
#include <signal.h>
E 32
I 32
#include <stdio.h>
E 32
#include <ctype.h>
#include <string.h>
D 32
#include <memory.h>
#include <fcntl.h>
E 32
I 32
#include "extern.h"
E 32
E 31

E 17
I 2
D 31
# ifdef USG
#  define index strchr
#  define rindex strrchr
#  define curerase mode.c_cc[VERASE]
#  define curkill mode.c_cc[VKILL]
I 18
#  define curintr mode.c_cc[VINTR]
E 18
#  define olderase oldmode.c_cc[VERASE]
#  define oldkill oldmode.c_cc[VKILL]
I 18
#  define oldintr oldmode.c_cc[VINTR]
E 18
# else
#  define curerase mode.sg_erase
#  define curkill mode.sg_kill
I 18
#  define curintr tchar.t_intrc
E 18
#  define olderase oldmode.sg_erase
#  define oldkill oldmode.sg_kill
I 18
#  define oldintr oldtchar.t_intrc
E 18
# endif

E 2
D 9
/*
# define	FULLLOGIN	1
D 2
*/
E 2
I 2
/*/
E 9
E 2
# ifndef V6
D 9
# define	GTTYN		"/etc/ttytype"
E 9
I 9
# define	GTTYN
# include	<ttyent.h>
E 9
# endif

D 2
# include	<ctype.h>
# include	<sgtty.h>
E 2
I 2
# ifndef USG
#  include	<sgtty.h>
# else
#  include	<termio.h>
# endif

E 2
# include	<stdio.h>
I 2
# include	<signal.h>
# ifdef	V6
# include	<retrofit.h>
# endif
E 2

D 2
# define	BACKSPACE	('H' & 037)
# define	CONTROLX	('X' & 037)
E 2
I 2
# define	YES		1
# define	NO		0
I 3
D 20
#undef CTRL
E 3
# define	CTRL(x)		(x ^ 0100)
# define	BACKSPACE	(CTRL('H'))
E 20
I 20
#undef CNTL
# define	CNTL(c)		((c)&037)
# define	BACKSPACE	(CNTL('H'))
E 20
# define	CHK(val, dft)	(val<=0 ? dft : val)
# define	isdigit(c)	(c >= '0' && c <= '9')
D 21
# define	isalnum(c)	(c > ' ' && !(index("<@=>!:|\177", c)) )
E 21
I 21
# define	isalnum(c)	(c > ' ' && (index("<@=>!:|\177", c) == NULL))
E 21
E 2
# define	OLDERASE	'#'
# define	OLDKILL		'@'
I 18
# define	OLDINTR		'\177'	/* del */
E 18

I 20
/* default special characters */
#ifndef CERASE
#define	CERASE	'\177'
#endif
#ifndef CKILL
#define	CKILL	CNTL('U')
#endif
#ifndef CINTR
#define	CINTR	CNTL('C')
#endif
#ifndef CDSUSP
E 31
I 31
D 32
/* Default values for control characters. */
#ifndef CEOF
#define	_CTRL(c) ((c) & 0x1f)
#define	CEOF	_CTRL('d')
#define	CERASE	0177		/* DEL, ^? */
#define	CINTR	_CTRL('c')
#define CFLUSH  _CTRL('o')
#define	CKILL	_CTRL('u')
#define	CLNEXT	_CTRL('v')
E 31
#define	CQUIT	034		/* FS, ^\ */
D 31
#define	CSTART	CNTL('Q')
#define	CSTOP	CNTL('S')
#define	CEOF	CNTL('D')
#define	CEOT	CEOF
#define	CBRK	0377
#define	CSUSP	CNTL('Z')
#define	CDSUSP	CNTL('Y')
#define	CRPRNT	CNTL('R')
D 28
#define	CFLUSH	CNTL('O')
E 28
I 28
#define	CDISCARD	CNTL('O')
E 28
#define	CWERASE	CNTL('W')
#define	CLNEXT	CNTL('V')
E 31
I 31
#define	CRPRNT	_CTRL('r')
#define	CSTART	_CTRL('q')
#define	CSTOP	_CTRL('s')
#define	CSUSP	_CTRL('z')
#define	CWERASE	_CTRL('w')
E 31
#endif
E 32
I 32
void	obsolete __P((char *[]));
void	report __P((char *, int, u_int));
void	usage __P((void));
E 32

E 20
D 2
# define	FILEDES		2
# define	STDOUT		1
E 2
I 2
D 31
# define	FILEDES		2	/* do gtty/stty on this descriptor */
# define	STDOUT		1	/* output of -s/-S to this descriptor */
E 31
I 31
D 32
/* This should be in <termcap.h> instead. */
int tgetent();
int tgetnum();
int tgetflag();
char *tgetstr();
int tputs();
char *tgoto();
E 32
I 32
struct termios mode, oldmode;
E 32
E 31
E 2

D 2
# ifdef V6
E 2
I 2
D 31
# ifdef	V6
E 2
# define	UIDMASK		0377
# else
# define	UIDMASK		-1
# endif
E 31
I 31
D 32
extern char PC;
extern short ospeed;
E 32
I 32
D 34
int	dosetenv;		/* output TERMCAP strings */
E 34
int	erasechar;		/* new erase character */
int	intrchar;		/* new interrupt character */
int	isreset;		/* invoked as reset */
int	killchar;		/* new kill character */
D 34
int	noinit;			/* don't output initialization string */
int	noset;			/* only report term type */
int	quiet;			/* don't display ctrl key settings */
I 33
int	showterm;		/* display term on stderr */
E 33
E 32
E 31

E 34
D 2
# define	DEFTYPE		"unknown"
# define	USAGE\
"usage: tset [-] [-hrsuIQS] [-eC] [-kC] [-m [ident][test speed]:type] [type]\n"
E 2
I 2
D 31
# ifdef UCB_NTTY
D 20
# define	USAGE	"usage: tset [-] [-nrsIQS] [-eC] [-kC] [-m [ident][test speed]:type] [type]\n"
E 20
I 20
# define	USAGE	"usage: tset [-] [-nrsIQS] [-eC] [-kC] [-iC] [-m [ident][test speed]:type] [type]\n"
E 20
# else
D 20
# define	USAGE	"usage: tset [-] [-rsIQS] [-eC] [-kC] [-m [ident][test speed]:type] [type]\n"
E 20
I 20
# define	USAGE	"usage: tset [-] [-rsIQS] [-eC] [-kC] [-iC] [-m [ident][test speed]:type] [type]\n"
E 20
# endif
E 31
I 31
D 32
/* This should be in <getopt.h> instead. */
int getopt();
E 32
I 32
int	lines, columns;		/* window size */
E 32
E 31
E 2

I 2
D 31
# define	OLDFLAGS
E 2
# define	DIALUP		"dialup"
# define	OLDDIALUP	"sd"
# define	PLUGBOARD	"plugboard"
# define	OLDPLUGBOARD	"sp"
/***
# define	ARPANET		"arpanet"
# define	OLDARPANET	"sa"
D 2
***/
# define	OLDFLAGS
E 2
I 2
/***/
E 31
I 31
D 32
extern int optind;
extern char *optarg;
E 31
E 2

I 2
D 31
# define	DEFTYPE		"unknown"
E 31
I 31
char *mapped();
char *putbuf();
char *stypeof();
int baudrate();
int cancelled();
int isalias();
int prc();
int settabs();
void add_mapping();
void cat();
void flush();
void set_control_chars();
void get_termcap_entry();
void get_tty_type();
void makealias();
void output_initializations();
void prs();
void reportek();
void reset_mode();
void set_conversions();
void setdelay();
void set_mode();
void usage();
void wrtermcap();
E 31
E 2

I 31
#define curerase mode.c_cc[VERASE]
#define curkill mode.c_cc[VKILL]
#define curintr mode.c_cc[VINTR]
#define olderase oldmode.c_cc[VERASE]
#define oldkill oldmode.c_cc[VKILL]
#define oldintr oldmode.c_cc[VINTR]
E 31

D 31
# ifdef GTTYN
D 2
typedef char	*ttyid_t;
E 2
# define	NOTTY		0
# else
D 2
typedef char	ttyid_t;
E 2
# define	NOTTY		'x'
# endif
E 31
I 31
#define	YES		1
#define	NO		0
#define	CNTL(c)		((c)&037)
#define	BACKSPACE	(CNTL('H'))
#define	CHK(val, dft)	(val<=0 ? dft : val)
E 31

D 31
/*
 * Baud Rate Conditionals
 */
# define	ANY		0
# define	GT		1
# define	EQ		2
# define	LT		4
# define	GE		(GT|EQ)
# define	LE		(LT|EQ)
# define	NE		(GT|LT)
# define	ALL		(GT|EQ|LT)
E 31
I 31
#define	FILEDES		2	/* change attrs on this descriptor */
#define	STDOUT		1	/* output -s/-S to this descriptor */
E 31

I 31
/* Last resort default term type. */
#define	DEFTYPE		"unknown"
E 31

I 31
/* Baud rate conditionals for mapping. */
#define	ANY		0
#define	GT		1
#define	EQ		2
#define	LT		4
#define	GE		(GT|EQ)
#define	LE		(LT|EQ)
#define	NE		(GT|LT)
#define	ALL		(GT|EQ|LT)
E 31

D 31
# define	NMAP		10
E 31
I 31
/* Maximum number of mappings allowed. */
#define	NMAP		10
E 31

struct	map {
D 31
	char *Ident;
	char Test;
	char Speed;
	char *Type;
} map[NMAP];
E 31
I 31
	char *Ident;		/* Port type, or "" for any. */
	char Test;		/* Baud rate conditionals bitmask. */
	char Speed;		/* Baud rate to compare against. */
	char *Type;		/* Terminal type to select. */
};
E 31

I 31
struct map map[NMAP];

/* Next available element of `map'. */
E 31
struct map *Map = map;

I 2
D 31
/* This should be available in an include file */
E 31
E 2
struct
{
D 31
	char	*string;
	int	speed;
I 2
	int	baudrate;
E 31
I 31
	char	*string;	/* ASCII representation. */
	int	speed;		/* Internal form. */
	int	baudrate;	/* Numeric value. */
E 31
E 2
} speeds[] = {
D 2
	"0",	B0,
	"50",	B50,
	"75",	B75,
	"110",	B110,
	"134",	B134,
	"134.5",B134,
	"150",	B150,
	"200",	B200,
	"300",	B300,
	"600",	B600,
	"1200",	B1200,
	"1800",	B1800,
	"2400",	B2400,
	"4800",	B4800,
	"9600",	B9600,
	"exta",	EXTA,
	"extb",	EXTB,
E 2
I 2
	"0",	B0,	0,
	"50",	B50,	50,
	"75",	B75,	75,
	"110",	B110,	110,
	"134",	B134,	134,
	"134.5",B134,	134,
	"150",	B150,	150,
	"200",	B200,	200,
	"300",	B300,	300,
	"600",	B600,	600,
	"1200",	B1200,	1200,
	"1800",	B1800,	1800,
	"2400",	B2400,	2400,
	"4800",	B4800,	4800,
	"9600",	B9600,	9600,
I 20
D 31
	"19200",EXTA,	19200,
E 20
	"exta",	EXTA,	19200,
	"extb",	EXTB,	38400,
E 2
	0,
E 31
I 31
	"19200",B19200,	19200,
	"38400",B38400,	38400,
	"exta",	B19200,	19200,
	"extb",	B38400,	38400,
	NULL
E 31
};

I 2
D 31
#ifdef CBVIRTTERM
struct vterm {
	char cap[2];
	char *value;
} vtab [] = {
	"al",	"\033\120",
	"cd",	"\033\114",
	"ce",	"\033\113",
	"cm",	"\033\107%r%.%.",
	"cl",	"\033\112",
	"dc",	"\033\115",
	"dl",	"\033\116",
	"ic",	"\033\117",
	"kl",	"\033\104",
	"kr",	"\033\103",
	"ku",	"\033\101",
	"kd",	"\033\102",
	"kh",	"\033\105",
	"nd",	"\033\103",
	"se",	"\033\142\004",
	"so",	"\033\141\004",
	"ue",	"\033\142\001",
	"up",	"\033\101",
	"us",	"\033\141\001",
	"\0\0", NULL,
};

int VirTermNo = -2;
I 21
int	HasAM;			/* True if terminal has automatic margins */
E 21
# endif CBVIRTTERM

E 31
E 2
char	Erase_char;		/* new erase character */
char	Kill_char;		/* new kill character */
I 18
D 19
char	Intr_char;		/* new interupt character */
E 19
I 19
char	Intr_char;		/* new interrupt character */
E 19
E 18
D 31
char	Specialerase;		/* set => Erase_char only on terminals with backspace */
E 31
I 31
char	Specialerase;		/* set => Erase_char only on terminals with backspace (-E) */
E 31

D 2
ttyid_t	Ttyid = NOTTY;		/* terminal identifier */
E 2
I 2
D 31
# ifdef	GTTYN
char	*Ttyid = NOTTY;		/* terminal identifier */
# else
char	Ttyid = NOTTY;		/* terminal identifier */
# endif
E 2
char	*TtyType;		/* type of terminal */
char	*DefType;		/* default type if none other computed */
char	*NewType;		/* mapping identifier based on old flags */
E 31
I 31
char	*TtyPath = NULL;	/* terminal device */
char	*TtyType = NULL;	/* type of terminal */
char	*DefType = NULL;	/* default type if none other computed */
E 31
I 2
int	Mapped;			/* mapping has been specified */
E 2
D 31
int	Dash_u;			/* don't update htmp */
int	Dash_h;			/* don't read htmp */
int	DoSetenv;		/* output setenv commands */
int	BeQuiet;		/* be quiet */
int	NoInit;			/* don't output initialization string */
E 31
I 31
int	NoTermFromEnv;		/* don't get terminal type from environ (-h) */
int	DoSetenv;		/* output TERMCAP strings (-s, -S) */
int	CmndLine;		/* output setenv command lines (-s) */
int	BeQuiet;		/* Don't say ctrl key settings (-Q, reset) */
int	NoInit;			/* don't output initialization string (-I) */
E 31
I 2
int	IsReset;		/* invoked as reset */
E 2
D 31
int	Report;			/* report current type */
int	Ureport;		/* report to user */
int	RepOnly;		/* report only */
int	CmndLine;		/* output full command lines (-s option) */
E 31
I 31
int	Report;			/* report term type on stdout (-) */
int	Ureport;		/* report term type to user on stderr (-r) */
int	RepOnly;		/* only report term type (- & no other args) */
E 31
int	Ask;			/* ask user for termtype */
I 2
D 31
int	DoVirtTerm = YES;	/* Set up a virtual terminal */
D 21
int	New = NO;		/* use new tty discipline */
int	HasAM;			/* True if terminal has automatic margins */
E 21
int	PadBaud;		/* Min rate of padding needed */
E 31
I 31
int	PadBaud;		/* Min rate of padding needed, -1 if none */
E 31
I 12
int	lines, columns;
E 12
E 2

D 31
# define CAPBUFSIZ	1024
E 31
I 31
#define CAPBUFSIZ	1024
E 31
char	Capbuf[CAPBUFSIZ];	/* line from /etc/termcap for this TtyType */
char	*Ttycap;		/* termcap line from termcap or environ */

I 2
char	Aliasbuf[128];
I 31
/* Null-terminated array of alternative names for the terminal.
   The first element is the terminal's two-letter V6 short name.
   The elements are pointers into 'Aliasbuf'. */
E 31
char	*Alias[16];

I 21
D 31
extern char *strcpy();
extern char *index();
I 23
extern char *tgetstr();
extern int prc();
E 31
I 31
struct termios mode;
struct termios oldmode;
E 31
E 23

E 21
E 2
D 31
struct delay
{
	int	d_delay;
	int	d_bits;
};
E 31
I 31
/* The name this program was run with. */
char *program_name;
E 31

D 31
# include	"tset.delays.h"

I 2
# ifndef USG
struct sgttyb	mode;
struct sgttyb	oldmode;
I 18
struct tchars	tchar;
struct tchars	oldtchar;
E 18
# else
struct termio	mode;
struct termio	oldmode;
# endif
# ifdef CBVIRTTERM
struct termcb block = {0, 2, 0, 0, 0, 20};
# endif CBVIRTTERM
E 2


E 31
I 31
void
E 32
I 32
int
E 32
E 31
main(argc, argv)
D 32
int	argc;
char	*argv[];
E 32
I 32
	int argc;
	char *argv[];
E 32
{
D 2
	struct sgttyb	mode;
	struct sgttyb	oldmode;
E 2
D 11
	char		buf[256];
E 11
I 11
D 31
	char		buf[CAPBUFSIZ];
E 11
I 2
	char		termbuf[32];
E 2
	auto char	*bufp;
	register char	*p;
E 31
D 32
	char		*command;
	register int	i;
I 21
D 31
# ifdef CBVIRTTERM
E 21
I 2
	int		j;
I 21
# endif CBVIRTTERM
E 21
E 2
	int		Break;
	int		Not;
D 2
	int		Mapped;
	extern char	*nextarg();
	extern char	*mapped();
E 2
I 2
	char		*nextarg();
	char		*mapped();
	extern char	*rindex();
E 31
I 31
	int		optc;
	int		csh = NO;
E 32
#ifdef TIOCGWINSZ
E 31
I 12
D 32
	struct winsize	win;
E 32
I 32
	struct winsize win;
E 32
E 12
E 2
D 31
# ifdef V6
	extern char	*hsgettype();
# else
	extern char	*getenv();
# endif
# ifdef GTTYN
D 2
	extern char	*stypeof();
E 2
I 2
	char		*stypeof();
E 2
	extern char	*ttyname();
D 23
	extern char	*tgetstr();
E 23
# endif
	char		bs_char;
	int		csh;
I 2
	int		settle;
D 29
	int		setmode();
E 29
I 29
	void		setmode();
E 29
E 2
D 23
	extern		prc();
E 23
	extern char	PC;
I 2
# ifdef	V6
	extern int	ospeed;
# else
E 2
	extern short	ospeed;
I 2
# endif
# ifdef UCB_NTTY
	int		lmode;
	int		ldisc;
E 31
I 31
#endif
I 32
D 34
	int ch, csh, usingupper;
E 34
I 34
	int ch, noinit, noset, quiet, Sflag, sflag, showterm, usingupper;
E 34
	char savech, *p, *t, *tcapbuf, *ttype;
E 32
E 31
E 2

I 2
D 21
	ioctl(FILEDES, TIOCLGET, &lmode);
	ioctl(FILEDES, TIOCGETD, &ldisc);
E 21
I 21
D 31
	(void) ioctl(FILEDES, TIOCLGET, (char *)&lmode);
	(void) ioctl(FILEDES, TIOCGETD, (char *)&ldisc);
E 21
# endif
E 31
I 31
D 32
	program_name = argv[0];
E 32
I 32
	if (tcgetattr(STDERR_FILENO, &mode) < 0)
		err("standard error: %s", strerror(errno));
E 32
E 31

D 31
# ifndef USG
E 2
	if (gtty(FILEDES, &mode) < 0)
I 2
# else
D 21
	if (ioctl(FILEDES, TCGETA, &mode) < 0)
E 21
I 21
	if (ioctl(FILEDES, TCGETA, (char *)&mode) < 0)
E 21
# endif
E 31
I 31
D 32
	if (tcgetattr(FILEDES, &mode) < 0)
E 31
E 2
	{
D 31
		prs("Not a terminal\n");
E 31
I 31
		fprintf(stderr, "%s: standard error must be a terminal\n",
			program_name);
E 31
		exit(1);
	}
E 32
D 21
	bmove(&mode, &oldmode, sizeof mode);
E 21
I 21
D 31
	bmove((char *)&mode, (char *)&oldmode, sizeof mode);
E 21
I 18
# ifdef TIOCGETC
D 21
	(void)ioctl(FILEDES, TIOCGETC, &tchar);
	bmove(&tchar, &oldtchar, sizeof tchar);
E 21
I 21
	(void) ioctl(FILEDES, TIOCGETC, (char *)&tchar);
	bmove((char *)&tchar, (char *)&oldtchar, sizeof tchar);
E 21
# endif
E 18
D 2
	ospeed = mode.sg_ospeed;
E 2
I 2
# ifndef USG
	ospeed = mode.sg_ospeed & 017;
# else
	ospeed = mode.c_cflag & CBAUD;
# endif
D 21
	signal(SIGINT, setmode);
	signal(SIGQUIT, setmode);
	signal(SIGTERM, setmode);
E 21
I 21
	(void) signal(SIGINT, setmode);
	(void) signal(SIGQUIT, setmode);
	(void) signal(SIGTERM, setmode);
E 31
I 31
	oldmode = mode;
E 31
E 21
E 2
D 32

E 32
D 2
	/* scan argument list and collect flags */
	command = argv[0];
	if (argc == 2 && argv[1][0] == '-' && argv[1][1] == '\0')
E 2
I 2
D 31
	if (command = rindex(argv[0], '/'))
E 31
I 31
	ospeed = cfgetospeed(&mode);

D 32
	(void) signal(SIGINT, set_mode);
	(void) signal(SIGQUIT, set_mode);
	(void) signal(SIGTERM, set_mode);

	command = strrchr(argv[0], '/');
	if (command)
E 31
		command++;
E 32
I 32
	if (p = strrchr(*argv, '/'))
		++p;
E 32
	else
D 32
		command = argv[0];
D 31
	if (sequal(command, "reset") )
E 31
I 31
	if (!strcmp(command, "reset") )
E 31
E 2
	{
E 32
I 32
		p = *argv;
	usingupper = isupper(*p);
	if (!strcasecmp(p, "reset")) {
		isreset = 1;
E 32
D 2
		RepOnly++;
		Dash_u++;
E 2
I 2
D 31
	/*
	 * reset the teletype mode bits to a sensible state.
	 * Copied from the program by Kurt Shoens & Mark Horton.
	 * Very useful after crapping out in raw.
	 */
# ifndef V6
D 20
#  ifdef TIOCGETC
		struct tchars tbuf;
#  endif TIOCGETC
E 20
#  ifdef UCB_NTTY
		struct ltchars ltc;
I 20
D 22
#ifdef TIOCLBIC
		static int lclear = LMDMBUF|LLITOUT|LPASS8;
#endif TIOCLBIC
E 22
E 20

		if (ldisc == NTTYDISC)
		{
D 21
			ioctl(FILEDES, TIOCGLTC, &ltc);
E 21
I 21
			(void) ioctl(FILEDES, TIOCGLTC, (char *)&ltc);
E 21
D 20
			ltc.t_suspc = CHK(ltc.t_suspc, CTRL('Z'));
			ltc.t_dsuspc = CHK(ltc.t_dsuspc, CTRL('Y'));
			ltc.t_rprntc = CHK(ltc.t_rprntc, CTRL('R'));
			ltc.t_flushc = CHK(ltc.t_flushc, CTRL('O'));
			ltc.t_werasc = CHK(ltc.t_werasc, CTRL('W'));
			ltc.t_lnextc = CHK(ltc.t_lnextc, CTRL('V'));
E 20
I 20
			ltc.t_suspc = CHK(ltc.t_suspc, CSUSP);
			ltc.t_dsuspc = CHK(ltc.t_dsuspc, CDSUSP);
			ltc.t_rprntc = CHK(ltc.t_rprntc, CRPRNT);
D 28
			ltc.t_flushc = CHK(ltc.t_flushc, CFLUSH);
E 28
I 28
			ltc.t_flushc = CHK(ltc.t_flushc, CDISCARD);
E 28
			ltc.t_werasc = CHK(ltc.t_werasc, CWERASE);
			ltc.t_lnextc = CHK(ltc.t_lnextc, CLNEXT);
E 20
D 21
			ioctl(FILEDES, TIOCSLTC, &ltc);
E 21
I 21
			(void) ioctl(FILEDES, TIOCSLTC, (char *)&ltc);
E 21
		}
#  endif UCB_NTTY
#  ifndef USG
#   ifdef TIOCGETC
D 20
		ioctl(FILEDES, TIOCGETC, &tbuf);
		tbuf.t_intrc = CHK(tbuf.t_intrc, CTRL('?'));
		tbuf.t_quitc = CHK(tbuf.t_quitc, CTRL('\\'));
		tbuf.t_startc = CHK(tbuf.t_startc, CTRL('Q'));
		tbuf.t_stopc = CHK(tbuf.t_stopc, CTRL('S'));
		tbuf.t_eofc = CHK(tbuf.t_eofc, CTRL('D'));
E 20
I 20
		tchar.t_intrc = CHK(tchar.t_intrc, CINTR);
		tchar.t_quitc = CHK(tchar.t_quitc, CQUIT);
		tchar.t_startc = CHK(tchar.t_startc, CSTART);
		tchar.t_stopc = CHK(tchar.t_stopc, CSTOP);
		tchar.t_eofc = CHK(tchar.t_eofc, CEOF);
E 20
		/* brkc is left alone */
D 20
		ioctl(FILEDES, TIOCSETC, &tbuf);
E 20
I 20
D 21
		ioctl(FILEDES, TIOCSETC, &tchar);
E 21
I 21
		(void) ioctl(FILEDES, TIOCSETC, (char *)&tchar);
E 21
D 22
#ifdef TIOCLBIC
D 21
		ioctl(FILEDES, TIOCLBIC, &lclear);
E 21
I 21
		(void) ioctl(FILEDES, TIOCLBIC, (char *)&lclear);
E 21
#endif TIOCLBIC
E 22
E 20
#   endif TIOCGETC
		mode.sg_flags &= ~(RAW
#   ifdef CBREAK
					|CBREAK
#   endif CBREAK
						|VTDELAY|ALLDELAY);
		mode.sg_flags |= XTABS|ECHO|CRMOD|ANYP;
D 20
		curerase = CHK(curerase, OLDERASE);
		curkill = CHK(curkill, OLDKILL);
E 20
I 20
		curerase = CHK(curerase, CERASE);
		curkill = CHK(curkill, CKILL);
		curintr = CHK(curintr, CINTR);
E 20
#  else USG
D 21
		ioctl(FILEDES, TCGETA, &mode);
E 21
I 21
		(void) ioctl(FILEDES, TCGETA, (char *)&mode);
E 21
		curerase = CHK(curerase, OLDERASE);
		curkill = CHK(curkill, OLDKILL);
D 18
		mode.c_cc[VINTR] = CHK(mode.c_cc[VINTR], CTRL('?'));
E 18
I 18
D 20
		curintr = CHK(curintr, CTRL('?'));
E 18
		mode.c_cc[VQUIT] = CHK(mode.c_cc[VQUIT], CTRL('\\'));
		mode.c_cc[VEOF] = CHK(mode.c_cc[VEOF], CTRL('D'));
E 20
I 20
		curintr = CHK(curintr, OLDINTR);
		mode.c_cc[VQUIT] = CHK(mode.c_cc[VQUIT], CQUIT);
		mode.c_cc[VEOF] = CHK(mode.c_cc[VEOF], CEOF);
E 20

		mode.c_iflag |= (BRKINT|ISTRIP|ICRNL|IXON);
		mode.c_iflag &= ~(IGNBRK|PARMRK|INPCK|INLCR|IGNCR|IUCLC|IXOFF);
		mode.c_oflag |= (OPOST|ONLCR);
		mode.c_oflag &= ~(OLCUC|OCRNL|ONOCR|ONLRET|OFILL|OFDEL|
				NLDLY|CRDLY|TABDLY|BSDLY|VTDLY|FFDLY);
		mode.c_cflag |= (CS7|CREAD);
		mode.c_cflag &= ~(CSIZE|PARODD|CLOCAL);
		mode.c_lflag |= (ISIG|ICANON|ECHO|ECHOK);
		mode.c_lflag &= ~(XCASE|ECHONL|NOFLSH);
D 21
		ioctl(FILEDES, TCSETAW, &mode);
E 21
I 21
		(void) ioctl(FILEDES, TCSETAW, (char *)&mode);
E 21
#  endif USG
# endif V6
		Dash_u = YES;
E 31
I 31
		reset_mode();
E 31
D 32
		BeQuiet = YES;
		IsReset = YES;
E 32
E 2
	}
I 2
D 31
	else if (argc == 2 && sequal(argv[1], "-"))
	{
		RepOnly = YES;
		Dash_u = YES;
	}
E 2
	argc--;
E 31
I 2

D 31
	/* scan argument list and collect flags */
E 2
	while (--argc >= 0)
E 31
I 31
D 32
	while ((optc = getopt(argc, argv, "e:hi:k:m:nrsE:IQS")) != EOF)
E 31
	{
D 31
		p = *++argv;
		if (*p == '-')
		{
			if (*++p == NULL)
D 2
				Report++; /* report current terminal type */
E 2
I 2
				Report = YES; /* report current terminal type */
E 2
			else while (*p) switch (*p++)
E 31
I 31
			switch (optc)
E 31
			{
I 31
			  case 'n':	/* obsolete -- ignore */
				break;
E 31

I 2
D 31
# ifdef UCB_NTTY
			  case 'n':
				ldisc = NTTYDISC;
D 21
				if (ioctl(FILEDES, TIOCSETD, &ldisc)<0)
E 21
I 21
				if (ioctl(FILEDES, TIOCSETD, (char *)&ldisc)<0)
E 21
					fatal("ioctl ", "new");
				continue;
# endif

E 31
E 2
			  case 'r':	/* report to user */
D 2
				Ureport++;
E 2
I 2
				Ureport = YES;
E 2
D 31
				continue;
E 31
I 31
				break;
E 31

			  case 'E':	/* special erase: operate on all but TTY33 */
D 2
				Specialerase++;
E 2
I 2
				Specialerase = YES;
E 2
				/* explicit fall-through to -e case */

			  case 'e':	/* erase character */
D 31
				if (*p == NULL)
					Erase_char = -1;
				else
E 31
I 31
				if (optarg[0] == '^' && optarg[1] != '\0')
E 31
				{
D 31
					if (*p == '^' && p[1] != NULL)
D 2
						Erase_char = *++p & 037;
E 2
I 2
D 20
						Erase_char = CTRL(*++p);
E 20
I 20
						if (*++p == '?')
							Erase_char = '\177';
						else
							Erase_char = CNTL(*p);
E 31
I 31
					if (optarg[1] == '?')
						Erase_char = '\177';
E 31
E 20
E 2
					else
D 31
						Erase_char = *p;
					p++;
E 31
I 31
						Erase_char = CNTL(optarg[1]);
E 31
				}
D 31
				continue;
E 31
I 31
				else
					Erase_char = optarg[0];
				break;
E 31

I 18
D 31
# if defined(USG) || defined(TIOCGETC)
E 31
D 20
			  case 'i':	/* erase character */
E 20
I 20
			  case 'i':	/* interrupt character */
E 20
D 31
				if (*p == NULL)
D 20
					Intr_char = CTRL('C');
E 20
I 20
					Intr_char = CNTL('C');
E 20
				else
E 31
I 31
				if (optarg[0] == '^' && optarg[1] != '\0')
E 31
				{
D 31
					if (*p == '^' && p[1] != NULL)
D 20
						Intr_char = CTRL(*++p);
E 20
I 20
						if (*++p == '?')
							Intr_char = '\177';
						else
							Intr_char = CNTL(*p);
E 31
I 31
					if (optarg[1] == '?')
						Intr_char = '\177';
E 31
E 20
					else
D 31
						Intr_char = *p;
					p++;
E 31
I 31
						Intr_char = CNTL(optarg[1]);
E 31
				}
D 31
				continue;
# endif
E 31
I 31
				else
					Intr_char = optarg[0];
				break;
E 31

E 18
			  case 'k':	/* kill character */
D 31
				if (*p == NULL)
D 2
					Kill_char = CONTROLX;
E 2
I 2
D 20
					Kill_char = CTRL('X');
E 20
I 20
					Kill_char = CNTL('X');
E 20
E 2
				else
E 31
I 31
				if (optarg[0] == '^' && optarg[1] != '\0')
E 31
				{
D 31
					if (*p == '^' && p[1] != NULL)
D 2
						Kill_char = *++p & 037;
E 2
I 2
D 20
						Kill_char = CTRL(*++p);
E 20
I 20
						if (*++p == '?')
							Kill_char = '\177';
						else
							Kill_char = CNTL(*p);
E 31
I 31
					if (optarg[1] == '?')
						Kill_char = '\177';
E 31
E 20
E 2
					else
D 31
						Kill_char = *p;
					p++;
E 31
I 31
						Kill_char = CNTL(optarg[1]);
E 31
				}
D 31
				continue;
E 31
I 31
				else
					Kill_char = optarg[0];
				break;
E 31

D 31
# ifdef OLDFLAGS
# ifdef	OLDDIALUP
			  case 'd':	/* dialup type */
				NewType = DIALUP;
				goto mapold;
# endif

# ifdef OLDPLUGBOARD
			  case 'p':	/* plugboard type */
				NewType = PLUGBOARD;
				goto mapold;
# endif

# ifdef OLDARPANET
			  case 'a':	/* arpanet type */
				Newtype = ARPANET;
				goto mapold;
# endif

mapold:				Map->Ident = NewType;
				Map->Test = ALL;
				if (*p == NULL)
				{
					p = nextarg(argc--, argv++);
				}
				Map->Type = p;
				Map++;
D 2
				Mapped++;
E 2
I 2
				Mapped = YES;
E 2
				p = "";
				continue;
# endif

E 31
			  case 'm':	/* map identifier to type */
D 31
				/* This code is very loose. Almost no
				** syntax checking is done!! However,
				** illegal syntax will only produce
				** weird results.
				*/
				if (*p == NULL)
				{
					p = nextarg(argc--, argv++);
				}
				if (isalnum(*p))
				{
					Map->Ident = p;	/* identifier */
					while (isalnum(*p)) p++;
				}
				else
					Map->Ident = "";
D 2
				Break = 0;
				Not = 0;
E 2
I 2
				Break = NO;
				Not = NO;
E 2
				while (!Break) switch (*p)
				{
					case NULL:
						p = nextarg(argc--, argv++);
						continue;
E 31
I 31
				add_mapping(optarg);
				break;
E 31

D 31
					case ':':	/* mapped type */
						*p++ = NULL;
D 2
						Break++;
E 2
I 2
						Break = YES;
E 2
						continue;
E 31
I 31
			  case 'h':	/* don't get type from env */
				NoTermFromEnv = YES;
				break;
E 31

D 31
					case '>':	/* conditional */
						Map->Test |= GT;
						*p++ = NULL;
						continue;

					case '<':	/* conditional */
						Map->Test |= LT;
						*p++ = NULL;
						continue;

					case '=':	/* conditional */
					case '@':
						Map->Test |= EQ;
						*p++ = NULL;
						continue;
					
					case '!':	/* invert conditions */
						Not = ~Not;
						*p++ = NULL;
						continue;

					case 'B':	/* Baud rate */
						p++;
						/* intentional fallthru */
					default:
						if (isdigit(*p) || *p == 'e')
						{
							Map->Speed = baudrate(p);
							while (isalnum(*p) || *p == '.')
								p++;
						}
						else
D 2
							Break++;
E 2
I 2
							Break = YES;
E 2
						continue;
				}
				if (Not)	/* invert sense of test */
				{
					Map->Test = (~(Map->Test))&ALL;
				}
				if (*p == NULL)
				{
					p = nextarg(argc--, argv++);
				}
				Map->Type = p;
				p = "";
				Map++;
D 2
				Mapped++;
E 2
I 2
				Mapped = YES;
E 2
				continue;

			  case 'h':	/* don't get type from htmp or env */
D 2
				Dash_h++;
E 2
I 2
				Dash_h = YES;
E 2
				continue;

			  case 'u':	/* don't update htmp */
D 2
				Dash_u++;
E 2
I 2
				Dash_u = YES;
E 2
				continue;

E 31
			  case 's':	/* output setenv commands */
D 2
				DoSetenv++;
				CmndLine++;
E 2
I 2
				DoSetenv = YES;
				CmndLine = YES;
E 2
D 31
				continue;
E 31
I 31
				break;
E 31

			  case 'S':	/* output setenv strings */
D 2
				DoSetenv++;
				CmndLine=0;
E 2
I 2
				DoSetenv = YES;
				CmndLine = NO;
E 2
D 31
				continue;
E 31
I 31
				break;
E 31

			  case 'Q':	/* be quiet */
D 2
				BeQuiet++;
E 2
I 2
				BeQuiet = YES;
E 2
D 31
				continue;
E 31
I 31
				break;
E 31

			  case 'I':	/* no initialization */
D 2
				NoInit++;
E 2
I 2
				NoInit = YES;
E 2
D 31
				continue;
E 31
I 31
				break;
E 31

D 31
			  case 'A':	/* Ask user */
D 2
				Ask++;
E 2
I 2
				Ask = YES;
E 2
				continue;
I 2
			
			  case 'v':	/* no virtual terminal */
				DoVirtTerm = NO;
				continue;
E 2

E 31
			  default:
D 31
				*p-- = NULL;
				fatal("Bad flag -", p);
E 31
I 31
				usage();
E 31
			}
E 32
I 32
	obsolete(argv);
D 33
	while ((ch = getopt(argc, argv, "-e:Ii:k:m:nQs")) != EOF) {
E 33
I 33
D 34
	while ((ch = getopt(argc, argv, "-a:d:e:Ii:k:m:np:Qrs")) != EOF) {
E 34
I 34
	noinit = noset = quiet = Sflag = sflag = showterm = 0;
	while ((ch = getopt(argc, argv, "-a:d:e:Ii:k:m:np:QSrs")) != EOF) {
E 34
E 33
		switch (ch) {
D 33
		case '-':
E 33
I 33
D 34
		case '-':		/* OBSOLETE: display term only */
E 34
I 34
		case '-':		/* display term only */
E 34
E 33
			noset = 1;
			break;
I 33
		case 'a':		/* OBSOLETE: map identifier to type */
			add_mapping("arpanet", optarg);
			break;
		case 'd':		/* OBSOLETE: map identifier to type */
			add_mapping("dialup", optarg);
			break;
E 33
		case 'e':		/* erase character */
			erasechar = optarg[0] == '^' && optarg[1] != '\0' ?
			    optarg[1] == '?' ? '\177' : CTRL(optarg[1]) :
			    optarg[0];
			break;
D 34
		case 'I':		/* no initialization */
E 34
I 34
		case 'I':		/* no initialization strings */
E 34
			noinit = 1;
			break;
		case 'i':		/* interrupt character */
			intrchar = optarg[0] == '^' && optarg[1] != '\0' ?
			    optarg[1] == '?' ? '\177' : CTRL(optarg[1]) :
			    optarg[0];
			break;
		case 'k':		/* kill character */
			killchar = optarg[0] == '^' && optarg[1] != '\0' ?
			    optarg[1] == '?' ? '\177' : CTRL(optarg[1]) :
			    optarg[0];
			break;
		case 'm':		/* map identifier to type */
D 33
			add_mapping(optarg);
E 33
I 33
			add_mapping(NULL, optarg);
E 33
			break;
D 33
		case 'n':		/* Undocumented (obsolete). */
			break;		/* set newtty driver */
E 33
I 33
		case 'n':		/* OBSOLETE: set new tty driver */
			break;
		case 'p':		/* OBSOLETE: map identifier to type */
			add_mapping("plugboard", optarg);
			break;
E 33
D 34
		case 'Q':		/* be quiet */
E 34
I 34
		case 'Q':		/* don't output control key settings */
E 34
			quiet = 1;
			break;
I 34
		case 'S':		/* output TERM/TERMCAP strings */
			Sflag = 1;
			break;
E 34
I 33
		case 'r':		/* display term on stderr */
			showterm = 1;
			break;
E 33
D 34
		case 's':		/* print commands to set environment */
			dosetenv = 1;
E 34
I 34
		case 's':		/* output TERM/TERMCAP strings */
			sflag = 1;
E 34
			break;
		case '?':
		default:
			usage();
		}
E 32
D 31
		}
		else
		{
			/* terminal type */
			DefType = p;
		}
E 31
	}
I 32
	argc -= optind;
	argv += optind;
E 32

D 31
	if (DefType)
E 31
I 31
D 32
	if (optind < argc && !strcmp(argv[optind], "-"))
E 31
	{
D 31
		if (Mapped)
		{
			Map->Ident = "";	/* means "map any type" */
			Map->Test = ALL;	/* at all baud rates */
			Map->Type = DefType;	/* to the default type */
		}
		else
			TtyType = DefType;
E 31
I 31
		Report = YES;
		if (argc == 2)
			RepOnly = YES;
		++optind;
E 31
	}

D 31
# ifndef V6
I 2
	/*
	 * Get rid of $TERMCAP, if it's there, so we get a real
	 * entry from /etc/termcap.  This prevents us from being
	 * fooled by out of date stuff in the environment, and
	 * makes tabs work right on CB/Unix.
	 */
	bufp = getenv("TERMCAP");
	if (bufp && *bufp != '/')
D 4
		strcpy(bufp-8, "NOTHING=nothing");
E 4
I 4
D 21
		strcpy(bufp-8, "NOTHING");	/* overwrite only "TERMCAP" */
E 21
I 21
		(void) strcpy(bufp-8, "NOTHING"); /* overwrite only "TERMCAP" */
E 21
E 4
E 2
	/* get current idea of terminal type from environment */
D 7
	if (!Dash_h && !Mapped && TtyType == 0)
E 7
I 7
	if (!Dash_h && TtyType == 0)
E 7
		TtyType = getenv("TERM");
# endif

	/* determine terminal id if needed */
# ifdef V6
	if (Ttyid == NOTTY && (TtyType == 0 || !Dash_h || !Dash_u))
		Ttyid = ttyn(FILEDES);
# else
	if (!RepOnly && Ttyid == NOTTY && (TtyType == 0 || !Dash_h))
		Ttyid = ttyname(FILEDES);
# endif

# ifdef V6
	/* get htmp if ever used */
	if (!Dash_u || (TtyType == 0 && !Dash_h))
E 31
I 31
	if (optind < argc)
E 31
	{
D 31
		/* get htmp entry -- if error or wrong user use ttytype */
		if (Ttyid == NOTTY || hget(Ttyid) < 0 ||
		    hgettype() == 0 || hgetuid() != (getuid() & UIDMASK))
			Dash_h++;
E 31
I 31
		/* Terminal type. */
		DefType = argv[optind];
		++optind;
E 31
	}

D 31
	/* find terminal type (if not already known) */
	if (TtyType == 0 && !Dash_h)
E 31
I 31
	if (optind < argc)
E 31
	{
D 31
		/* get type from /etc/htmp */
		TtyType = hsgettype();
E 31
I 31
		fprintf(stderr, "%s: extra arguments\n", program_name);
E 32
I 32
	if (argc > 1)
E 32
		usage();
E 31
D 32
	}
E 32
D 31
# endif
E 31

D 31
# ifdef GTTYN
	/* If still undefined, look at /etc/ttytype */
	if (TtyType == 0)
	{
		TtyType = stypeof(Ttyid);
	}
# endif
E 31
I 31
D 32
	get_tty_type();
E 32
I 32
	ttype = get_termcap_entry(*argv, &tcapbuf);
E 32
E 31

D 31
	/* If still undefined, use DEFTYPE */
	if (TtyType == 0)
	{
		TtyType = DEFTYPE;
	}
E 31
I 31
D 32
	get_termcap_entry();
E 31

D 31
	/* check for dialup or other mapping */
	if (Mapped)
I 8
	{
		if (!(Alias[0] && isalias(TtyType)))
			if (tgetent(Capbuf, TtyType) > 0)
				makealias(Capbuf);
E 8
D 2
		TtyType = mapped(TtyType, ospeed);
E 2
I 2
		TtyType = mapped(TtyType);
I 8
	}
E 8
E 2

	/* TtyType now contains a pointer to the type of the terminal */
	/* If the first character is '?', ask the user */
	if (TtyType[0] == '?')
	{
D 2
		Ask++;
E 2
I 2
		Ask = YES;
E 2
		TtyType++;
		if (TtyType[0] == '\0')
			TtyType = DEFTYPE;
	}
	if (Ask)
	{
I 11
ask:
E 11
		prs("TERM = (");
		prs(TtyType);
		prs(") ");
		flush();

		/* read the terminal.  If not empty, set type */
D 2
		i = read(2, buf, sizeof buf - 1);
		if (i >= 0)
E 2
I 2
		i = read(2, termbuf, sizeof termbuf - 1);
		if (i > 0)
E 2
		{
D 2
			if (buf[i - 1] == '\n')
E 2
I 2
			if (termbuf[i - 1] == '\n')
E 2
				i--;
D 2
			buf[i] = '\0';
			if (buf[0] != '\0')
				TtyType = buf;
E 2
I 2
			termbuf[i] = '\0';
			if (termbuf[0] != '\0')
				TtyType = termbuf;
E 2
		}
	}

D 2
	if (Ttycap == 0)
	{
		/* get terminal capabilities */
E 2
I 2
	/* get terminal capabilities */
	if (!(Alias[0] && isalias(TtyType))) {
E 2
		switch (tgetent(Capbuf, TtyType))
		{
		  case -1:
D 2
			prs("Cannot open termcap file\n");
E 2
I 2
			prs("Cannot find termcap\n");
E 2
			flush();
			exit(-1);

		  case 0:
			prs("Type ");
			prs(TtyType);
			prs(" unknown\n");
			flush();
D 2
			exit(1);
E 2
I 2
			if (DoSetenv)
			{
				TtyType = DEFTYPE;
D 11
				tgetent(Capbuf, TtyType);
E 11
I 11
				Alias[0] = '\0';
				goto ask;
E 11
			}
			else
				exit(1);
E 2
		}
D 2
		Ttycap = Capbuf;
E 2
	}
I 2
	Ttycap = Capbuf;
E 2

E 31
	if (!RepOnly)
	{
D 31
		/* determine erase and kill characters */
		if (Specialerase && !tgetflag("bs"))
			Erase_char = 0;
		bufp = buf;
		p = tgetstr("kb", &bufp);
		if (p == NULL || p[1] != '\0')
			p = tgetstr("bc", &bufp);
		if (p != NULL && p[1] == '\0')
			bs_char = p[0];
		else if (tgetflag("bs"))
			bs_char = BACKSPACE;
		else
			bs_char = 0;
D 2
		if (Erase_char == 0 && !tgetflag("os") && mode.sg_erase == OLDERASE)
E 2
I 2
		if (Erase_char == 0 && !tgetflag("os") && curerase == OLDERASE)
E 2
		{
			if (tgetflag("bs") || bs_char != 0)
				Erase_char = -1;
		}
		if (Erase_char < 0)
			Erase_char = (bs_char != 0) ? bs_char : BACKSPACE;
E 31
I 31
		set_control_chars();
E 31

D 2
		if (mode.sg_erase == 0)
			mode.sg_erase = OLDERASE;
E 2
I 2
D 31
		if (curerase == 0)
D 20
			curerase = OLDERASE;
E 20
I 20
			curerase = CERASE;
E 20
E 2
		if (Erase_char != 0)
D 2
			mode.sg_erase = Erase_char;
E 2
I 2
			curerase = Erase_char;
E 31
I 31
		set_conversions(command);
E 31
E 2

E 32
I 32
	if (!noset) {
E 32
I 18
D 31
		if (curintr == 0)
D 20
			curintr = OLDKILL;
E 20
I 20
			curintr = CINTR;
E 20
		if (Intr_char != 0)
			curintr = Intr_char;

E 18
D 2
		if (mode.sg_kill == 0)
			mode.sg_kill = OLDKILL;
E 2
I 2
		if (curkill == 0)
D 20
			curkill = OLDKILL;
E 20
I 20
			curkill = CKILL;
E 20
E 2
		if (Kill_char != 0)
D 2
			mode.sg_kill = Kill_char;
E 2
I 2
			curkill = Kill_char;
E 2

		/* set modes */
I 2
		PadBaud = tgetnum("pb");	/* OK if fails */
		for (i=0; speeds[i].string; i++)
			if (speeds[i].baudrate == PadBaud) {
				PadBaud = speeds[i].speed;
				break;
			}
# ifndef USG
E 2
		setdelay("dC", CRdelay, CRbits, &mode.sg_flags);
		setdelay("dN", NLdelay, NLbits, &mode.sg_flags);
		setdelay("dB", BSdelay, BSbits, &mode.sg_flags);
		setdelay("dF", FFdelay, FFbits, &mode.sg_flags);
		setdelay("dT", TBdelay, TBbits, &mode.sg_flags);
D 2
		if (tgetflag("UC") || command[0] == 'T')
E 2
I 2
		if (tgetflag("UC") || (command[0] & 0140) == 0100)
E 2
			mode.sg_flags |= LCASE;
		else if (tgetflag("LC"))
			mode.sg_flags &= ~LCASE;
		mode.sg_flags &= ~(EVENP | ODDP | RAW);
D 2
# ifndef V6
E 2
I 2
# ifdef CBREAK
E 2
		mode.sg_flags &= ~CBREAK;
# endif
		if (tgetflag("EP"))
			mode.sg_flags |= EVENP;
		if (tgetflag("OP"))
			mode.sg_flags |= ODDP;
		if ((mode.sg_flags & (EVENP | ODDP)) == 0)
			mode.sg_flags |= EVENP | ODDP;
		mode.sg_flags |= CRMOD | ECHO | XTABS;
		if (tgetflag("NL"))	/* new line, not line feed */
			mode.sg_flags &= ~CRMOD;
		if (tgetflag("HD"))	/* half duplex */
			mode.sg_flags &= ~ECHO;
		if (tgetflag("pt"))	/* print tabs */
			mode.sg_flags &= ~XTABS;
D 2
		if (!bequal(&mode, &oldmode, sizeof mode))
# ifndef V6
			ioctl(FILEDES, TIOCSETN, &mode);
E 2
# else
D 2
			stty(FILEDES, &mode);
E 2
I 2
		setdelay("dC", CRdelay, CRbits, &mode.c_oflag);
		setdelay("dN", NLdelay, NLbits, &mode.c_oflag);
		setdelay("dB", BSdelay, BSbits, &mode.c_oflag);
		setdelay("dF", FFdelay, FFbits, &mode.c_oflag);
		setdelay("dT", TBdelay, TBbits, &mode.c_oflag);
		setdelay("dV", VTdelay, VTbits, &mode.c_oflag);

		if (tgetflag("UC") || (command[0] & 0140) == 0100) {
			mode.c_iflag |= IUCLC;
			mode.c_oflag |= OLCUC;
		}
		else if (tgetflag("LC")) {
			mode.c_iflag &= ~IUCLC;
			mode.c_oflag &= ~OLCUC;
		}
		mode.c_iflag &= ~(PARMRK|INPCK);
		mode.c_lflag |= ICANON;
		if (tgetflag("EP")) {
			mode.c_cflag |= PARENB;
			mode.c_cflag &= ~PARODD;
		}
		if (tgetflag("OP")) {
			mode.c_cflag |= PARENB;
			mode.c_cflag |= PARODD;
		}

		mode.c_oflag |= ONLCR;
		mode.c_iflag |= ICRNL;
		mode.c_lflag |= ECHO;
		mode.c_oflag |= TAB3;
		if (tgetflag("NL")) {	/* new line, not line feed */
			mode.c_oflag &= ~ONLCR;
			mode.c_iflag &= ~ICRNL;
		}
		if (tgetflag("HD"))	/* half duplex */
			mode.c_lflag &= ~ECHO;
		if (tgetflag("pt"))	/* print tabs */
			mode.c_oflag &= ~TAB3;
		
		mode.c_lflag |= (ECHOE|ECHOK);
E 2
# endif
I 2
# ifdef CBVIRTTERM
		HasAM = tgetflag("am");
# endif CBVIRTTERM
# ifdef UCB_NTTY
		if (ldisc == NTTYDISC)
		{
			lmode |= LCTLECH;	/* display ctrl chars */
			if (tgetflag("hc"))
			{	/** set printer modes **/
				lmode &= ~(LCRTBS|LCRTERA|LCRTKIL);
				lmode |= LPRTERA;
			}
			else
			{	/** set crt modes **/
				if (!tgetflag("os"))
				{
					lmode &= ~LPRTERA;
					lmode |= LCRTBS;
					if (mode.sg_ospeed >= B1200)
						lmode |= LCRTERA|LCRTKIL;
				}
			}
		}
I 22
		if (IsReset)
			lmode &= ~(LMDMBUF|LLITOUT|LPASS8);
E 22
D 21
		ioctl(FILEDES, TIOCLSET, &lmode);
E 21
I 21
		(void) ioctl(FILEDES, TIOCLSET, (char *)&lmode);
E 21
# endif
E 2

		/* get pad character */
		bufp = buf;
		if (tgetstr("pc", &bufp) != 0)
			PC = buf[0];

E 31
I 12
		columns = tgetnum("co");
		lines = tgetnum("li");

I 31
#ifdef TIOCGWINSZ
E 31
		/* Set window size */
D 20
		if (DoSetenv) {
D 13
			ioctl(FILEDES, TIOCGWINSZ, &win);
			if (win.ws_row == 0 && win.ws_col == 0) {
				win.ws_row = lines;
				win.ws_col = columns;
				ioctl(FILEDES, TIOCSWINSZ, &win);
			}
E 13
I 13
D 16
			win.ws_row = lines;
			win.ws_col = columns;
			ioctl(FILEDES, TIOCSWINSZ, &win);
E 16
I 16
			ioctl(FILEDES, TIOCGWINSZ, &win);
D 18
			if (win.ws_row == 0 && win.ws_col == 0) {
E 18
I 18
			if (win.ws_row == 0 && win.ws_col == 0 &&
			    lines > 0 && columns > 0) {
E 18
				win.ws_row = lines;
				win.ws_col = columns;
				ioctl(FILEDES, TIOCSWINSZ, &win);
			}
E 20
I 20
D 21
		ioctl(FILEDES, TIOCGWINSZ, &win);
E 21
I 21
D 32
		(void) ioctl(FILEDES, TIOCGWINSZ, (char *)&win);
E 32
I 32
		(void)ioctl(STDERR_FILENO, TIOCGWINSZ, &win);
E 32
E 21
		if (win.ws_row == 0 && win.ws_col == 0 &&
		    lines > 0 && columns > 0) {
			win.ws_row = lines;
			win.ws_col = columns;
D 21
			ioctl(FILEDES, TIOCSWINSZ, &win);
E 21
I 21
D 32
			(void) ioctl(FILEDES, TIOCSWINSZ, (char *)&win);
E 32
I 32
			(void)ioctl(STDERR_FILENO, TIOCSWINSZ, &win);
E 32
E 21
E 20
E 16
E 13
		}
E 12
D 31
		/* output startup string */
E 31
I 31
#endif
I 32
		set_control_chars();
		set_conversions(usingupper);
E 32

E 31
D 32
		if (!NoInit)
D 31
		{
I 2
# ifndef USG
			if (oldmode.sg_flags&(XTABS|CRMOD))
			{
				oldmode.sg_flags &= ~(XTABS|CRMOD);
				setmode(-1);
			}
# else
			if (oldmode.c_oflag&(TAB3|ONLCR|OCRNL|ONLRET))
			{
				oldmode.c_oflag &= (TAB3|ONLCR|OCRNL|ONLRET);
				setmode(-1);
			}
# endif
# ifdef CBVIRTTERM
			block.st_termt = 0;
D 21
			ioctl(FILEDES, LDSETT, &block);
E 21
I 21
			(void) ioctl(FILEDES, LDSETT, (char *)&block);
E 21
# endif CBVIRTTERM
			if (settabs()) {
				settle = YES;
				flush();
			}
E 2
			bufp = buf;
D 2
			if (tgetstr("is", &bufp) != 0)
E 2
I 2
D 20
			if (tgetstr(IsReset? "rs" : "is", &bufp) != 0)
E 20
I 20
			if (IsReset && tgetstr("rs", &bufp) != 0 || 
			    tgetstr("is", &bufp) != 0)
E 20
			{
E 2
				tputs(buf, 0, prc);
D 2
			flush();
E 2
I 2
				settle = YES;
				flush();
			}
E 2
			bufp = buf;
D 2
			if (tgetstr("if", &bufp) != 0)
E 2
I 2
D 20
			if (tgetstr(IsReset? "rf" : "if", &bufp) != 0)
E 20
I 20
			if (IsReset && tgetstr("rf", &bufp) != 0 ||
			    tgetstr("if", &bufp) != 0)
E 20
			{
E 2
				cat(buf);
D 2
			sleep(1);	/* let terminal settle down */
E 2
I 2
				settle = YES;
			}
			if (settle)
			{
				prc('\r');
				flush();
				sleep(1);	/* let terminal settle down */
			}
E 2
		}
E 31
I 31
			output_initializations();
E 32
I 32
		if (!noinit)
			set_init();
E 32
E 31

I 2
D 31
# ifdef CBVIRTTERM
		if (DoVirtTerm) {
			j = tgetnum("vt");
			VirTermNo = -1;
			for (i=0; vt_map[i].stdnum; i++)
				if (vt_map[i].stdnum == j)
					VirTermNo = vt_map[i].localnum;
		} else
			VirTermNo = -1;
# endif CBVIRTTERM
E 31
I 31
D 32
		set_mode(0);	/* set new modes, if they've changed */
E 32
I 32
		/* Set the modes if they've changed. */
		if (memcmp(&mode, &oldmode, sizeof(mode)))
			tcsetattr(STDERR_FILENO, TCSADRAIN, &mode);
E 32
E 31
D 33

D 31
		setmode(0);	/* set new modes, if they've changed */

E 2
		/* set up environment for the shell we are using */
D 2
		/* (this code is rather heuristic) */
		csh = 0;
E 2
I 2
		/* (this code is rather heuristic, checking for $SHELL */
		/* ending in the 3 characters "csh") */
		csh = NO;
E 31
I 31
D 32
		/* set up environment for the shell we are using
		   (this code is rather heuristic, checking for $SHELL
		   ending in the 3 characters "csh") */
E 31
E 2
		if (DoSetenv)
		{
D 31
# ifndef V6
E 31
			char *sh;

D 31
			if ((sh = getenv("SHELL")) && (i = strlen(sh)) >= 3)
E 31
I 31
			sh = getenv("SHELL");
			if (sh != NULL)
E 31
			{
D 2
				p = &sh[i-3];
				if ((csh = sequal(p, "csh")) && CmndLine)
E 2
I 2
D 21
				if ((csh = sequal(&sh[i-3], "csh")) && CmndLine)
E 2
					write(STDOUT, "set noglob;\n", 12);
E 21
I 21
D 31
			    if ((csh = sequal(&sh[i-3], "csh")) && CmndLine)
				(void) write(STDOUT, "set noglob;\n", 12);
E 31
I 31
				i = strlen(sh);
				if (i >= 3)
				{
					csh = !strcmp(&sh[i - 3], "csh");
					if (csh && CmndLine)
					  puts("set noglob;");
				}
E 31
E 21
			}
			if (!csh)
D 31
# endif
E 31
D 2
				/* running system shell */
E 2
I 2
D 21
				/* running Bourne shell */
E 2
				write(STDOUT, "export TERMCAP TERM;\n", 21);
E 21
I 21
			    /* running Bourne shell */
D 31
			    (void) write(STDOUT, "export TERMCAP TERM;\n", 21);
E 31
I 31
			    puts("export TERMCAP TERM;");
E 32
I 32
		/*
		 * If erase, kill and interrupt characters have potentially
		 * been modified and not -Q, display the changes.
		 */
		if (!quiet) {
			report("Erase", VERASE, CERASE);
			report("Kill", VKILL, CKILL);
			report("Interrupt", VINTR, CINTR);
E 32
E 31
E 21
		}
E 33
	}

D 32
	/* report type if appropriate */
	if (DoSetenv || Report || Ureport)
	{
D 2
		/* find first alias (if any) */
		for (p = Ttycap; *p != 0 && *p != '|' && *p != ':'; p++)
			continue;
		if (*p == 0 || *p == ':')
			p = Ttycap;
		else
			p++;
		bufp = p;
		while (*p != '|' && *p != ':' && *p != 0)
			p++;
		i = *p;
E 2
I 2
D 31
		/* if type is the short name, find first alias (if any) */
E 31
I 31
		/* If 'TtyType' is the short name, use the first alias
		   (if any) instead. */
E 31
		makealias(Ttycap);
D 31
		if (sequal(TtyType, Alias[0]) && Alias[1]) {
E 31
I 31
		if (!strcmp(TtyType, Alias[0]) && Alias[1])
E 31
			TtyType = Alias[1];
E 32
I 32
D 33
	if (!dosetenv && !noset)
		exit(0);
E 32
D 31
		}
E 31

E 33
E 2
D 32
		if (DoSetenv)
		{
			if (csh)
			{
				if (CmndLine)
D 21
					write(STDOUT, "setenv TERM ", 12);
D 2
				write(STDOUT, bufp, p - bufp);
E 2
I 2
				write(STDOUT, TtyType, strlen(TtyType));
E 2
				write(STDOUT, " ", 1);
E 21
I 21
D 31
				    (void) write(STDOUT, "setenv TERM ", 12);
				(void) write(STDOUT, TtyType, strlen(TtyType));
				(void) write(STDOUT, " ", 1);
E 31
I 31
				    fputs("setenv TERM ", stdout);
				fputs(TtyType, stdout);
				putchar(' ');
E 31
E 21
				if (CmndLine)
D 21
					write(STDOUT, ";\n", 2);
E 21
I 21
D 31
				    (void) write(STDOUT, ";\n", 2);
E 31
I 31
				    puts(";");
E 31
E 21
			}
			else
			{
D 21
				write(STDOUT, "TERM=", 5);
D 2
				write(STDOUT, bufp, p - bufp);
E 2
I 2
				write(STDOUT, TtyType, strlen(TtyType));
E 2
				write(STDOUT, ";\n", 2);
E 21
I 21
D 31
				(void) write(STDOUT, "TERM=", 5);
				(void) write(STDOUT, TtyType, strlen(TtyType));
				(void) write(STDOUT, ";\n", 2);
E 31
I 31
				fputs("TERM=", stdout);
				fputs(TtyType, stdout);
				puts(";");
E 31
E 21
			}
E 32
I 32
D 36
	/*
	 * The termcap file generally has a two-character name first in each
	 * entry followed by more descriptive names.  If we ended up with the
	 * first one, we switch to the second one for setting or reporting
	 * information.
	 */
	p = strpbrk(tcapbuf, "|:");
	if (p && *p != ':' && !strncmp(ttype, tcapbuf, p - tcapbuf)) {
		t = ++p;
E 36
I 36
	/* Get the terminal name from the entry. */
	p = tcapbuf;
	if (p != NULL && *p != ':') {
		t = p;
E 36
		if (p = strpbrk(p, "|:")) {
			savech = *p;
			*p = '\0';
			if ((ttype = strdup(t)) == NULL)
				err("%s", strerror(errno));
			*p = savech;
E 32
		}
D 2
		if (Report && !DoSetenv)
E 2
I 2
D 32
		else if (Report)
E 2
		{
D 2
			write(STDOUT, bufp, p - bufp);
E 2
I 2
D 21
			write(STDOUT, TtyType, strlen(TtyType));
E 2
			write(STDOUT, "\n", 1);
E 21
I 21
D 31
			(void) write(STDOUT, TtyType, strlen(TtyType));
			(void) write(STDOUT, "\n", 1);
E 31
I 31
			puts(TtyType);
E 31
E 21
		}
		if (Ureport)
		{
D 2
			*p = '\0';
E 2
			prs("Terminal type is ");
D 2
			prs(bufp);
E 2
I 2
			prs(TtyType);
E 2
			prs("\n");
			flush();
		}
D 2
		*p = i;
E 2
I 2

E 2
		if (DoSetenv)
		{
			if (csh)
			{
D 21
				if (CmndLine)
					write(STDOUT, "setenv TERMCAP '", 16);
E 21
I 21
			    if (CmndLine)
D 31
				(void) write(STDOUT, "setenv TERMCAP '", 16);
E 31
I 31
				fputs("setenv TERMCAP '", stdout);
E 31
E 21
			}
			else
D 21
				write(STDOUT, "TERMCAP='", 9);
E 21
I 21
D 31
			    (void) write(STDOUT, "TERMCAP='", 9);
E 31
I 31
			    fputs("TERMCAP='", stdout);
			fflush(stdout);
E 31
E 21
			wrtermcap(Ttycap);
			if (csh)
			{
				if (CmndLine)
				{
D 21
					write(STDOUT, "';\n", 3);
					write(STDOUT, "unset noglob;\n", 14);
E 21
I 21
D 31
				    (void) write(STDOUT, "';\n", 3);
				    (void) write(STDOUT, "unset noglob;\n", 14);
E 31
I 31
				    puts("';\nunset noglob;");
E 31
E 21
				}
			}
			else
D 21
				write(STDOUT, "';\n", 3);
E 21
I 21
D 31
				(void) write(STDOUT, "';\n", 3);
E 31
I 31
				puts("';");
E 31
E 21
		}
E 32
	}

D 31
	if (RepOnly)
		exit(0);

E 31
I 31
D 32
	if(!RepOnly && !BeQuiet) {
E 31
D 18
	/* tell about changing erase and kill characters */
E 18
I 18
D 19
	/* tell about changing erase, kill and interupt characters */
E 19
I 19
	/* tell about changing erase, kill and interrupt characters */
E 19
E 18
D 2
	reportek("Erase", mode.sg_erase, oldmode.sg_erase, OLDERASE);
	reportek("Kill", mode.sg_kill, oldmode.sg_kill, OLDKILL);
E 2
I 2
D 31
	reportek("Erase", curerase, olderase, OLDERASE);
	reportek("Kill", curkill, oldkill, OLDKILL);
I 18
D 19
	reportek("Interupt", curintr, oldintr, OLDINTR);
E 19
I 19
	reportek("Interrupt", curintr, oldintr, OLDINTR);
E 31
I 31
	reportek("Erase", curerase, olderase, CERASE);
	reportek("Kill", curkill, oldkill, CKILL);
	reportek("Interrupt", curintr, oldintr, CINTR);
E 32
I 32
D 33
	if (noset) {
E 33
I 33
	if (noset)
E 33
		(void)printf("%s\n", ttype);
D 33
		exit(0);
E 33
I 33
	else {
		if (showterm)
			(void)fprintf(stderr, "Terminal type is %s.\n", ttype);
		/*
		 * If erase, kill and interrupt characters could have been
		 * modified and not -Q, display the changes.
		 */
		if (!quiet) {
			report("Erase", VERASE, CERASE);
			report("Kill", VKILL, CKILL);
			report("Interrupt", VINTR, CINTR);
		}
E 33
E 32
	}
E 31
E 19
E 18
E 2

I 33
D 34
	if (!dosetenv)
		exit(0);
E 34
I 34
	if (Sflag) {
		(void)printf("%s ", ttype);
		wrtermcap(tcapbuf);
	}
E 34

E 33
D 31
# ifdef V6
	/* update htmp */
	if (!Dash_u)
E 31
I 31
D 32
	exit(0);
}

/* Syntax for P: [port-type][test baudrate]:terminal-type
   The baud rate tests are: > < @/= ! 
   The baudrate number can be preceded by a 'B', which is ignored.
   The baudrate number can also be `exta' or `extb'.
   This code is very loose. Almost no syntax checking is done!
   However, invalid syntax will only produce weird results. */

void
add_mapping(p)
char *p;
{
	int Break = NO;
	int Not = NO;

	if (isalnum (*p))
E 31
	{
D 31
		if (Ttyid == 0)
			Ttyid = ttyn(FILEDES);
		if (Ttyid == 'x')
E 31
I 31
		Map->Ident = p;	/* Port-type identifier. */
		while (isalnum (*p))
		  p++;
	}
E 32
I 32
D 34
	/*
	 * Figure out what shell we're using.  A hack, we look for a $SHELL
	 * ending in "csh".
	 */
	csh = (p = getenv("SHELL")) && !strcmp(p + strlen(p) - 3, "csh");
	if (csh)
		(void)printf("set noglob;\nsetenv TERM %s;\nsetenv TERMCAP '",
		    ttype);
E 32
	else
D 32
		Map->Ident = "";

	/* Scan for optional test and baudrate. */
	while (Break == NO)
	{
		switch (*p)
E 31
		{
D 31
			prs("Cannot update htmp\n");
			flush();
E 31
I 31
		      case '\0':
			Break = YES;
			continue;
	  
		      case ':':	/* Mapped type. */
			*p++ = '\0';
			Break = YES;
			continue;
	  
		      case '>':	/* Conditional. */
			Map->Test |= GT;
			*p++ = '\0';
			continue;
	  
		      case '<':	/* Conditional. */
			Map->Test |= LT;
			*p++ = '\0';
			continue;
	  
		      case '=':	/* Conditional. */
		      case '@':
			Map->Test |= EQ;
			*p++ = '\0';
			continue;
	  
		      case '!':	/* Invert conditions. */
			Not = ~Not;
			*p++ = '\0';
			continue;
	  
		      case 'B':	/* Baud rate */
			p++;
			/* Intentional fallthru. */

		      default:
			if (isdigit(*p) || *p == 'e')
			{
				Map->Speed = baudrate (p);
				while (isalnum(*p) || *p == '.')
				  p++;
			}
			else
				Break = YES;
			continue;
E 31
		}
I 31
	}
	if (Not)		/* Invert sense of test. */
		Map->Test = (~(Map->Test)) & ALL;
	Map->Type = p;
	Map++;
	Mapped = YES;
}

/* Reset the terminal mode bits to a sensible state.
   Very useful after crapping out in raw mode. */

void
reset_mode()
{
	tcgetattr(FILEDES, &mode);
	curintr = CHK(curintr, CINTR);
	mode.c_cc[VQUIT] = CHK(mode.c_cc[VQUIT], CQUIT);
	curerase = CHK(curerase, CERASE);
	curkill = CHK(curkill, CKILL);
	mode.c_cc[VEOF] = CHK(mode.c_cc[VEOF], CEOF);
	mode.c_cc[VSTART] = CHK(mode.c_cc[VSTART], CSTART);
	mode.c_cc[VSTOP] = CHK(mode.c_cc[VSTOP], CSTOP);
	mode.c_cc[VSUSP] = CHK(mode.c_cc[VSUSP], CSUSP);
#if defined(VREPRINT) && defined(CRPRNT)
	mode.c_cc[VREPRINT] = CHK(mode.c_cc[VREPRINT], CRPRNT);
#endif
#if defined(VWERASE) && defined(CWERASE)
	mode.c_cc[VWERASE] = CHK(mode.c_cc[VWERASE], CWERASE);
#endif
#if defined(VLNEXT) && defined(CLNEXT)
	mode.c_cc[VLNEXT] = CHK(mode.c_cc[VLNEXT], CLNEXT);
#endif
#if defined(VFLUSH) && defined(CFLUSH)
	mode.c_cc[VFLUSH] = CHK(mode.c_cc[VFLUSH], CFLUSH);
#endif
#if defined(VDISCARD) && defined(CDISCARD)
	mode.c_cc[VDISCARD] = CHK(mode.c_cc[VDISCARD], CDISCARD);
#endif
	mode.c_iflag &= ~(IGNBRK | PARMRK | INPCK | ISTRIP | INLCR | IGNCR
#ifdef IUCLC
			  | IUCLC
#endif
#ifdef IXANY
			  | IXANY
#endif
			  | IXOFF);
	mode.c_iflag |= (BRKINT | IGNPAR | ICRNL | IXON
#ifdef IMAXBEL
			 | IMAXBEL
#endif
			 );
	mode.c_oflag &= ~(0
#ifdef OLCUC
			  | OLCUC
#endif
#ifdef OCRNL
			  | OCRNL
#endif
#ifdef ONOCR
			  | ONOCR
#endif
#ifdef ONLRET
			  | ONLRET
#endif
#ifdef OFILL
			  | OFILL
#endif
#ifdef OFDEL
			  | OFDEL
#endif
#ifdef NLDLY
			  | NLDLY | CRDLY | TABDLY | BSDLY | VTDLY | FFDLY
#endif
			  );
	mode.c_oflag |= (OPOST
#ifdef ONLCR
			 | ONLCR
#endif
			 );
	mode.c_cflag &= ~(CSIZE | CSTOPB | PARENB | PARODD | CLOCAL);
	mode.c_cflag |= (CS8 | CREAD);
	mode.c_lflag &= ~(ECHONL | NOFLSH | TOSTOP
#ifdef ECHOPTR
			  | ECHOPRT
#endif
#ifdef XCASE
			  | XCASE
#endif
			  );
	mode.c_lflag |= (ISIG | ICANON | ECHO | ECHOE | ECHOK
#ifdef ECHOCTL
			 | ECHOCTL
#endif
#ifdef ECHOKE
			 | ECHOKE
#endif
 			 );
	tcsetattr(FILEDES, TCSADRAIN, &mode);
}

/* Determine the terminal type and place it in 'TtyType'. */

void
get_tty_type()
{
	char *bufp;

	if (DefType)
	{
		if (Mapped)
		{
			Map->Ident = "";	/* means "map any type" */
			Map->Test = ALL;	/* at all baud rates */
			Map->Type = DefType;	/* to the default type */
		}
E 31
		else
I 31
			TtyType = DefType;
	}

	/* Get rid of $TERMCAP, if it's there, so we get a real
	   entry from /etc/termcap.  This prevents us from being
	   fooled by out of date stuff in the environment. */
	bufp = getenv("TERMCAP");
	if (bufp != NULL && *bufp != '/')
		strcpy(bufp - 8, "NOTHING"); /* Overwrite only "TERMCAP". */

	/* Get current idea of terminal type from environment. */
	if (!NoTermFromEnv && TtyType == NULL)
		TtyType = getenv("TERM");

	/* Determine terminal id if needed. */
	if (!RepOnly && TtyPath == NULL && (TtyType == NULL || !NoTermFromEnv))
		TtyPath = ttyname(FILEDES);

	/* If still undefined, look at /etc/ttytype. */
	if (TtyType == NULL)
		TtyType = stypeof(TtyPath);

	/* If still undefined, use DEFTYPE. */
	if (TtyType == NULL)
		TtyType = DEFTYPE;

	/* Check for dialup or other mapping. */
	if (Mapped)
	{
		if (Alias[0] == NULL || !isalias(TtyType))
E 31
		{
D 31
			/* update htmp file only if changed */
			if (!bequal(Capbuf, hsgettype(), 2))
			{
				hsettype(Capbuf[0] | (Capbuf[1] << 8));
				hput(Ttyid);
			}
E 31
I 31
			if (tgetent(Capbuf, TtyType) > 0)
			  makealias(Capbuf);
E 31
		}
I 31
		TtyType = mapped(TtyType);
E 31
	}
D 31
# endif
E 31

D 31
	exit(0);
E 31
I 31
	/* TtyType now contains a pointer to the type of the terminal.
	   If the first character is '?', ask the user. */
	if (TtyType[0] == '?')
	{
		Ask = YES;
		TtyType++;
		if (TtyType[0] == '\0')
		  TtyType = DEFTYPE;
	}
E 31
}

I 31
/* Query the user for TtyType if needed, then
   read the termcap entry for TtyType into Capbuf and TTycap. */

void
get_termcap_entry()
{
	static char termbuf[32];
	int i;

	if (Ask)
	{
	      ask:
		prs("TERM = (");
		prs(TtyType);
		prs(") ");
		flush();

		/* Read the terminal.  If not empty, set type. */
		i = read(2, termbuf, sizeof termbuf - 1);
		if (i > 0)
		{
			if (termbuf[i - 1] == '\n')
				i--;
			termbuf[i] = '\0';
			if (termbuf[0] != '\0')
				TtyType = termbuf;
		}
	}

	/* Get terminal capabilities. */
	if (Alias[0] == NULL || !isalias(TtyType))
	{
		switch (tgetent(Capbuf, TtyType))
		{
		      case -1:
			prs(program_name);
			prs(": cannot find termcap\n");
			flush();
			exit(2);

		      case 0:
			prs(program_name);
			prs(": type ");
			prs(TtyType);
			prs(" is unknown\n");
			flush();
			if (!DoSetenv)
				exit(1);
			TtyType = DEFTYPE;
			Alias[0] = NULL;
			goto ask;
		}
	}
	Ttycap = Capbuf;
}

/* Determine the erase, interrupt, and kill characters
   from the termcap entry and command line
   and update their values in 'mode'. */

void
set_control_chars()
{
	char buf[CAPBUFSIZ];
	char *bufp;
	char bs_char;
	char *p;

	if (Specialerase && !tgetflag("bs"))
		Erase_char = 0;
	bufp = buf;
	p = tgetstr("kb", &bufp);
	if (p == NULL || p[1] != '\0')
		p = tgetstr("bc", &bufp);
	if (p != NULL && p[1] == '\0')
		bs_char = p[0];
	else if (tgetflag("bs"))
		bs_char = BACKSPACE;
E 32
I 32
		(void)printf("TERM=%s;\nTERMCAP='", ttype);
	wrtermcap(tcapbuf);
	if (csh)
		(void)printf("';\nunset noglob;\n");
E 32
	else
D 32
		bs_char = 0;
	if (Erase_char == 0 && !tgetflag("os") && curerase == CERASE)
	{
		if (tgetflag("bs") || bs_char != 0)
			Erase_char = -1;
	}
	if (Erase_char < 0)
		Erase_char = (bs_char != 0) ? bs_char : BACKSPACE;
  
	if (curerase == 0)
		curerase = CERASE;
	if (Erase_char != 0)
		curerase = Erase_char;
  
	if (curintr == 0)
		curintr = CINTR;
	if (Intr_char != 0)
		curintr = Intr_char;
  
	if (curkill == 0)
		curkill = CKILL;
	if (Kill_char != 0)
		curkill = Kill_char;
E 32
I 32
		(void)printf("';\nexport TERMCAP TERM;\n");
E 34
I 34
	if (sflag) {
		/*
		 * Figure out what shell we're using.  A hack, we look for an
		 * environmental variable SHELL ending in "csh".
		 */
		if ((p = getenv("SHELL")) &&
		    !strcmp(p + strlen(p) - 3, "csh")) {
			p = "set noglob;\nsetenv TERM %s;\nsetenv TERMCAP '";
			t = "';\nunset noglob;\n";
		} else {
			p = "TERM=%s;\nTERMCAP='";
			t = "';\nexport TERMCAP TERM;\n";
		}
		(void)printf(p, ttype);
		wrtermcap(tcapbuf);
		(void)printf(t);
	}

E 34
	exit(0);
E 32
}

D 32
/* Set up various conversions in 'mode', including
   parity, tabs, returns, echo, and case, according to
   the termcap entry.
   if 'command' starts with uppercase, map external uppercase
   to internal lowercase. */

void
set_conversions(command)
char *command;
{
	if (tgetflag("UC") || (command[0] & 0140) == 0100)
	{
#ifdef IUCLC
		mode.c_iflag |= IUCLC;
		mode.c_oflag |= OLCUC;
#endif
	}
	else if (tgetflag("LC"))
	{
#ifdef IUCLC
		mode.c_iflag &= ~IUCLC;
		mode.c_oflag &= ~OLCUC;
#endif
	}
	mode.c_iflag &= ~(PARMRK | INPCK);
	mode.c_lflag |= ICANON;
	if (tgetflag("EP"))
	{
		mode.c_cflag |= PARENB;
		mode.c_cflag &= ~PARODD;
	}
	if (tgetflag("OP"))
	{
		mode.c_cflag |= PARENB;
		mode.c_cflag |= PARODD;
	}
  
#ifdef ONLCR
	mode.c_oflag |= ONLCR;
#endif
	mode.c_iflag |= ICRNL;
	mode.c_lflag |= ECHO;
	mode.c_oflag |= OXTABS;
	if (tgetflag("NL"))
	{
		/* Newline, not linefeed. */
#ifdef ONLCR
		mode.c_oflag &= ~ONLCR;
#endif
		mode.c_iflag &= ~ICRNL;
	}
	if (tgetflag("HD"))
		/* Half duplex. */
		mode.c_lflag &= ~ECHO;
	if (tgetflag("pt"))
		/* Print tabs. */
		mode.c_oflag &= ~OXTABS;
	mode.c_lflag |= (ECHOE | ECHOK);
}

E 32
E 31
I 2
/*
D 32
 * Set the hardware tabs on the terminal, using the ct (clear all tabs),
 * st (set one tab) and ch (horizontal cursor addressing) capabilities.
 * This is done before if and is, so they can patch in case we blow this.
I 31
 * Return nonzero if we set any tab stops, zero if not.
E 32
I 32
 * Tell the user if a control key has been changed from the default value.
E 32
E 31
 */
I 31
D 32
int
E 31
settabs()
{
	char caps[100];
	char *capsp = caps;
D 31
	char *clear_tabs, *set_tab, *set_column, *set_pos;
	char *tg_out, *tgoto();
E 31
I 31
	char *clear_tabs, *set_tab, *set_column, *set_pos = NULL;
	char *tg_out;
E 31
D 12
	int columns, lines, c;
E 12
I 12
	int c;
E 12

	clear_tabs = tgetstr("ct", &capsp);
	set_tab = tgetstr("st", &capsp);
	set_column = tgetstr("ch", &capsp);
D 31
	if (set_column == 0)
E 31
I 31
	if (set_column == NULL)
E 31
		set_pos = tgetstr("cm", &capsp);
D 12
	columns = tgetnum("co");
	lines = tgetnum("li");
E 12

	if (clear_tabs && set_tab) {
		prc('\r');	/* force to be at left margin */
		tputs(clear_tabs, 0, prc);
	}
	if (set_tab) {
		for (c=8; c<columns; c += 8) {
			/* get to that column. */
			tg_out = "OOPS";	/* also returned by tgoto */
			if (set_column)
				tg_out = tgoto(set_column, 0, c);
			if (*tg_out == 'O' && set_pos)
				tg_out = tgoto(set_pos, c, lines-1);
			if (*tg_out != 'O')
				tputs(tg_out, 1, prc);
			else {
D 31
				prc(' '); prc(' '); prc(' '); prc(' ');
				prc(' '); prc(' '); prc(' '); prc(' ');
E 31
I 31
				prs("        ");
E 31
			}
			/* set the tab */
			tputs(set_tab, 0, prc);
		}
		prc('\r');
		return 1;
	}
	return 0;
}

I 31
/* Output startup string. */

E 32
E 31
I 29
void
E 29
D 31
setmode(flag)
int	flag;
/* flag serves several purposes:
 *	if called as the result of a signal, flag will be > 0.
 *	if called from terminal init, flag == -1 means reset "oldmode".
 *	called with flag == 0 at end of normal mode processing.
 */
E 31
I 31
D 32
output_initializations()
E 32
I 32
report(name, which, def)
	char *name;
	int which;
	u_int def;
E 32
E 31
{
D 31
# ifndef USG
	struct sgttyb *ttymode;
# else
	struct termio *ttymode;
# endif
I 18
# ifdef TIOCGETC
	struct tchars *ttytchars;
# endif
E 31
I 31
D 32
	char buf[CAPBUFSIZ];
	char *bufp;
	int settle = NO;
E 32
I 32
	u_int old, new;
	char *bp, buf[1024];
E 32
E 31
E 18

D 18
	if (flag < 0)	/* unconditionally reset oldmode (called from init) */
E 18
I 18
D 31
	if (flag < 0) { /* unconditionally reset oldmode (called from init) */
E 18
		ttymode = &oldmode;
D 18
	else if (!bequal(&mode, &oldmode, sizeof mode))
E 18
I 18
# ifdef TIOCGETC
		ttytchars = &oldtchar;
# endif
D 21
	} else if (!bequal(&mode, &oldmode, sizeof mode)) {
E 21
I 21
	} else if (!bequal((char *)&mode, (char *)&oldmode, sizeof mode)) {
E 21
E 18
		ttymode = &mode;
D 18
	else		/* don't need it */
E 18
I 18
# ifdef TIOCGETC
		ttytchars = &tchar;
# endif
	} else	{	/* don't need it */
E 18
# ifndef USG
	ttymode = (struct sgttyb *)0;
# else
	ttymode = (struct termio *)0;
# endif
I 18
# ifdef TIOCGETC
	ttytchars = (struct tchars *)0;
# endif
E 31
I 31
D 32
	/* Get pad character. */
	bufp = buf;
	if (tgetstr("pc", &bufp) != 0)
		PC = buf[0];
E 32
I 32
	new = mode.c_cc[which];
	old = oldmode.c_cc[which];
E 32

D 32
#ifdef TAB3
	if (oldmode.c_oflag & (TAB3 | ONLCR | OCRNL | ONLRET))
	{
		oldmode.c_oflag &= (TAB3 | ONLCR | OCRNL | ONLRET);
		set_mode(-1);
E 31
	}
E 18
D 31
	
	if (ttymode)
E 31
I 31
#endif
	if (settabs())
E 31
	{
D 31
# ifdef USG
D 21
		ioctl(FILEDES, TCSETAW, ttymode);
E 21
I 21
		(void) ioctl(FILEDES, TCSETAW, (char *)ttymode);
E 21
# else
#  ifndef V6
D 21
		ioctl(FILEDES, TIOCSETN, ttymode);     /* don't flush */
E 21
I 21
		/* don't flush */
		(void) ioctl(FILEDES, TIOCSETN, (char *)ttymode);
E 21
#  else
		stty(FILEDES, ttymode);
#  endif
# endif
E 31
I 31
		settle = YES;
		flush ();
E 31
	}
I 18
D 31
# ifdef TIOCGETC
	if (ttytchars) {
D 21
		ioctl(FILEDES, TIOCSETC, ttytchars);
E 21
I 21
		(void) ioctl(FILEDES, TIOCSETC, (char *)ttytchars);
E 31
I 31
	bufp = buf;
	if (IsReset && tgetstr("rs", &bufp) != 0 || tgetstr("is", &bufp) != 0)
	{
		tputs(buf, 0, prc);
		settle = YES;
		flush();
E 31
E 21
	}
D 31
# endif
E 18
# ifdef CBVIRTTERM
	if (VirTermNo != -2) {
		int r1, r2;
		extern int errno;

D 21
		r1 = ioctl(FILEDES, LDGETT, &block);
E 21
I 21
		r1 = ioctl(FILEDES, LDGETT, (char *)&block);
E 21
		block.st_flgs |= TM_SET;
		block.st_termt = VirTermNo;
		if (block.st_termt < 0)
			block.st_termt = 0;
		if (!HasAM)
			block.st_flgs |= TM_ANL;
		else
			block.st_flgs &= ~TM_ANL;
D 21
		r2 = ioctl(FILEDES, LDSETT, &block);
E 21
I 21
		r2 = ioctl(FILEDES, LDSETT, (char *)&block);
E 31
I 31
	bufp = buf;
	if (IsReset && tgetstr("rf", &bufp) != 0 || tgetstr("if", &bufp) != 0)
	{
		cat(buf);
		settle = YES;
E 31
E 21
	}
D 31
# endif
E 31
I 31
  
	if (settle)
	{
		prc('\r');
		flush();
		sleep(1);	/* Let the terminal settle down. */
	}
}
E 31

I 31
/* Set the terminal processing according to 'mode' or 'oldmode'.
   If called as the result of a signal, flag is > 0.
   If called from terminal init, flag == -1 means reset 'oldmode'.
   If called at end of normal mode processing, flag == 0. */

void
set_mode(flag)
int	flag;
{
	if (flag < 0)
		tcsetattr(FILEDES, TCSADRAIN, &oldmode);
	else if (memcmp((char *) &mode, (char *) &oldmode, sizeof mode))
		tcsetattr(FILEDES, TCSADRAIN, &mode);

E 31
	if (flag > 0)	/* trapped signal */
		exit(1);
}

I 31
/* Tell the user the value that a control key is set to,
   if it has been changed from the default value.
   'new', 'old', and 'def' are the current, previous, and default
   ASCII values for the control key called 'name' in English. */

void
E 31
E 2
reportek(name, new, old, def)
char	*name;
D 31
char	old;
char	new;
char	def;
E 31
I 31
unsigned char	new;
unsigned char	old;
unsigned char	def;
E 31
{
D 31
	register char	o;
	register char	n;
	register char	*p;
I 2
	char		buf[32];
E 31
I 31
	register unsigned char	o;
	register unsigned char	n;
	char		buf[CAPBUFSIZ];
E 31
	char		*bufp;
E 2

D 31
	if (BeQuiet)
		return;
E 31
	o = old;
	n = new;

	if (o == n && n == def)
E 32
I 32
	if (old == new && old == def)
E 32
		return;
D 32
	prs(name);
	if (o == n)
		prs(" is ");
	else
		prs(" set to ");
D 2
	if (n < 040)
E 2
I 2
	bufp = buf;
D 26
	if (tgetstr("kb", &bufp) > 0 && n == buf[0] && buf[1] == NULL)
E 26
I 26
D 31
	if (tgetstr("kb", &bufp) && n == buf[0] && buf[1] == NULL)
E 31
I 31
	if (tgetstr("kb", &bufp) && n == buf[0] && buf[1] == '\0')
E 31
E 26
		prs("Backspace\n");
	else if (n == 0177)
		prs("Delete\n");
	else
E 2
	{
D 2
		prs("control-");
		n = (n & 037) | 0100;
	} else if (n == 0177) {
		prs("delete\n");
		flush();
		return;
E 2
I 2
		if (n < 040)
		{
			prs("Ctrl-");
			n ^= 0100;
		}
D 30
		p = "x\n";
		p[0] = n;
		prs(p);
E 30
I 30
		prc(n);
		prc('\n');
E 30
E 2
	}
D 2
	p = "x\n";
	p[0] = n;
	prs(p);
E 2
	flush();
}
E 32

I 31
D 32
/* Print string 's' to stderr, buffered. */
E 32
I 32
	(void)fprintf(stderr, "%s %s ", name, old == new ? "is" : "set to");
E 32
E 31

D 31


setdelay(cap, dtab, bits, flags)
char		*cap;
struct delay	dtab[];
int		bits;
D 10
int		*flags;
E 10
I 10
short		*flags;
E 10
{
	register int	i;
	register struct delay	*p;
I 2
# ifdef	V6
	extern int	ospeed;
# else
	extern short	ospeed;
# endif
E 2

	/* see if this capability exists at all */
	i = tgetnum(cap);
	if (i < 0)
		i = 0;
I 2
	/* No padding at speeds below PadBaud */
	if (PadBaud > ospeed)
		i = 0;
E 2

	/* clear out the bits, replace with new ones */
	*flags &= ~bits;

	/* scan dtab for first entry with adequate delay */
	for (p = dtab; p->d_delay >= 0; p++)
	{
		if (p->d_delay >= i)
		{
			p++;
			break;
		}
	}

	/* use last entry if none will do */
	*flags |= (--p)->d_bits;
}


E 31
I 31
D 32
void
E 31
prs(s)
char	*s;
{
	while (*s != '\0')
		prc(*s++);
E 32
I 32
	bp = buf;
	if (tgetstr("kb", &bp) && new == buf[0] && buf[1] == '\0')
		(void)fprintf(stderr, "backspace.\n");
	else if (new == 0177)
		(void)fprintf(stderr, "delete.\n");
	else if (new < 040) {
		new ^= 0100;
		(void)fprintf(stderr, "control-%c (^%c).\n", new, new);
	} else
		(void)fprintf(stderr, "%c.\n", new);
E 32
}

D 31

char	OutBuf[256];
E 31
I 31
D 32
char	OutBuf[512];
E 31
int	OutPtr;

I 31
/* Print character 'c' to stderr, buffered. */

int
E 31
prc(c)
D 2
	char c;
E 2
I 2
char	c;
E 2
{
D 31
	OutBuf[OutPtr++] = c;
E 31
I 31
	OutBuf[OutPtr++] = c & 0x7f;
E 31
	if (OutPtr >= sizeof OutBuf)
		flush();
I 31
	return c;
E 31
}

I 31
/* Write out and empty the buffer used by prs and prc. */

E 32
I 32
/*
 * Convert the obsolete argument form into something that getopt can handle.
 * This means that -e, -i and -k get default arguments supplied for them.
 */
E 32
void
E 31
D 32
flush()
E 32
I 32
obsolete(argv)
	char *argv[];
E 32
{
D 32
	if (OutPtr > 0)
D 21
		write(2, OutBuf, OutPtr);
E 21
I 21
		(void) write(2, OutBuf, OutPtr);
E 21
	OutPtr = 0;
}

I 31
/* Print file 'file' to STDERR. */
E 31

I 31
void
E 31
cat(file)
char	*file;
{
	register int	fd;
	register int	i;
	char		buf[BUFSIZ];

	fd = open(file, 0);
	if (fd < 0)
	{
D 31
		prs("Cannot open ");
E 31
I 31
		prs(program_name);
		prs(": cannot open ");
E 31
		prs(file);
		prs("\n");
		flush();
D 2
		exit(-1);
E 2
I 2
		return;
E 2
	}

D 2
	flush();
E 2
	while ((i = read(fd, buf, BUFSIZ)) > 0)
D 21
		write(FILEDES, buf, i);
E 21
I 21
D 31
		(void) write(FILEDES, buf, i);
E 31
I 31
		(void) write(2, buf, i);
E 31
E 21

D 21
	close(fd);
E 21
I 21
	(void) close(fd);
E 21
}

I 31
/* Put each of the alternative names for the terminal
   described by the termcap entry 'buf' into an element of 'Alias'.
   Make the final element a NULL. */
E 31

D 31

bmove(from, to, length)
char	*from;
char	*to;
int	length;
{
	register char	*p, *q;
	register int	i;

	i = length;
	p = from;
	q = to;

	while (i-- > 0)
		*q++ = *p++;
}



D 2
bequal(a, b, len)
E 2
I 2
bequal(a, b, len)	/* must be same thru len chars */
E 2
char	*a;
char	*b;
int	len;
{
	register char	*p, *q;
	register int	i;

	i = len;
	p = a;
	q = b;

D 4
	while (*p && *q && (*p == *q) && --i > 0)
E 4
I 4
	while ((*p == *q) && --i > 0)
E 4
	{
		p++; q++;
	}
	return ((*p == *q) && i >= 0);
}

D 2
sequal(a, b)
E 2
I 2
sequal(a, b)	/* must be same thru NULL */
E 2
char	*a;
char	*b;
{
	register char *p = a, *q = b;

	while (*p && *q && (*p == *q))
	{
		p++; q++;
	}
	return (*p == *q);
}

E 31
I 31
void
E 31
I 2
makealias(buf)
char	*buf;
{
D 31
	register int i;
	register char *a;
	register char *b;
E 31
I 31
	register int i;		/* Index into 'Alias'. */
	register char *a;	/* Pointer into 'Aliasbuf'. */
	register char *b;	/* Pointer into 'buf'. */
E 31

	Alias[0] = a = Aliasbuf;
	b = buf;
	i = 1;
	while (*b && *b != ':') {
		if (*b == '|') {
D 31
			*a++ = NULL;
E 31
I 31
			*a++ = '\0';
E 31
			Alias[i++] = a;
			b++;
		}
		else
			*a++ = *b++;
	}
D 31
	*a = NULL;
E 31
I 31
	*a = '\0';
E 31
	Alias[i] = NULL;
D 31
# ifdef	DEB
	for(i = 0; Alias[i]; printf("A:%s\n", Alias[i++]));
# endif
E 31
}

D 31
isalias(ident)	/* is ident same as one of the aliases? */
E 31
I 31
/* Return YES if 'ident' is the same as one of the aliases,
   NO if not. */

int
isalias(ident)
E 31
char	*ident;
{
D 31
	char **a = Alias;
E 31
I 31
	char **a;
E 31

D 31
	if (*a)
		while (*a)
			if (sequal(ident, *a))
				return(YES);
			else
				a++;
	return(NO);
E 31
I 31
	for (a = Alias; *a; ++a)
		if (!strcmp(ident, *a))
			return YES;
	return NO;
E 31
}

E 2
D 31
# ifdef GTTYN
E 31
I 31
/* Return the default type of terminal for line 'ttyid'. */

E 31
char *
stypeof(ttyid)
char	*ttyid;
{
D 5
	static char	typebuf[50];
E 5
I 5
D 9
	static char	typebuf[BUFSIZ];
E 9
E 5
	register char	*PortType;
D 21
	register char	*PortName;
E 21
	register char	*TtyId;
D 9
	register char	*p;
	register FILE	*f;
E 9
I 9
	struct ttyent *t;
E 9

D 31
	if (ttyid == NOTTY)
E 31
I 31
	if (ttyid == NULL)
E 31
		return (DEFTYPE);
D 9
	f = fopen(GTTYN, "r");
	if (f == NULL)
		return (DEFTYPE);
E 9

D 31
	/* split off end of name */
E 31
I 31
	/* Set TtyId to the basename of ttyid. */
E 31
	TtyId = ttyid;
	while (*ttyid)
		if (*ttyid++ == '/')
			TtyId = ttyid;

D 31
	/* scan the file */
D 9
	while (fgets(typebuf, sizeof typebuf, f) != NULL)
E 9
I 9
	if ((t = getttynam(TtyId)) != NULL)
E 9
	{
D 9
		p = PortType = typebuf;
		while (*p && isalnum(*p))
			p++;
		*p++ = NULL;

		/* skip separator */
		while (*p && !isalnum(*p))
			p++;

		PortName = p;
		/* put NULL at end of name */
		while (*p && isalnum(*p))
			p++;
		*p = NULL;

		/* check match on port name */
		if (sequal(PortName, TtyId))	/* found it */
		{
D 2
# ifdef OLDDIALUP
			if (sequal(PortType, OLDDIALUP))
				PortType = DIALUP;
# endif

# ifdef OLDPLUGBOARD
			if (sequal(PortType, OLDPLUGBOARD))
				PortType = PLUGBOARD;
# endif

# ifdef OLDARPANET
			if (sequal(PortType, OLDARPANET))
				PortType = ARPANET;
# endif
E 2
			fclose (f);
I 2
			/* get aliases from termcap entry */
			if (Mapped && tgetent(Capbuf, PortType) > 0) {
				makealias(Capbuf);
				if (sequal(Alias[0], PortType) && Alias[1])
					PortType = Alias[1];
			}
E 2
			return(PortType);
E 9
I 9
		PortType = t->ty_type;
		/* get aliases from termcap entry */
		if (Mapped && tgetent(Capbuf, PortType) > 0) {
			makealias(Capbuf);
			if (sequal(Alias[0], PortType) && Alias[1])
				PortType = Alias[1];
E 9
		}
I 9
		return (PortType);
E 31
I 31
	t = getttynam(TtyId);
	if (t == NULL)
		return DEFTYPE;

	PortType = t->ty_type;
	/* get aliases from termcap entry */
	if (Mapped && tgetent(Capbuf, PortType) > 0) {
		makealias(Capbuf);
		if (!strcmp(Alias[0], PortType) && Alias[1])
			PortType = Alias[1];
E 31
E 9
	}
D 9
	fclose (f);
E 9
D 31
	return (DEFTYPE);
E 31
I 31
	return (PortType);
E 31
}
D 31
# endif
E 31

D 2
#define	YES	1
#define	NO	0
E 2
D 31
/*
 * routine to output the string for the environment TERMCAP variable
 */
E 31
#define	WHITE(c)	(c == ' ' || c == '\t')
D 31
char delcap[128][2];
int ncap = 0;
E 31

I 31
/* Output termcap entry 'bp' to stdout, quoting characters that
   would give the shell problems and omitting empty fields. */

void
E 31
wrtermcap(bp)
char *bp;
{
	char buf[CAPBUFSIZ];
I 2
D 21
	register int i;
E 21
E 2
	char *p = buf;
	char *tp;
D 31
	char *putbuf();
E 31
	int space, empty;
I 21
D 31
# ifdef CBVIRTTERM
	register int i;
# endif CBVIRTTERM
E 31
E 21

D 31
	/* discard names with blanks */
/** May not be desireable ? **/
E 31
I 31
	/* Copy the terminal names in 'bp' into 'buf',
	   discarding (verbose) names that contain blanks. */
E 31
	while (*bp && *bp != ':') {
		if (*bp == '|') {
			tp = bp+1;
			space = NO;
			while (*tp && *tp != '|' && *tp != ':') {
				space = (space || WHITE(*tp) );
				tp++;
			}
			if (space) {
				bp = tp;
				continue;
			}
		}
		*p++ = *bp++;
	}
D 31
/**/
E 31

I 2
D 31
# ifdef CBVIRTTERM
	if (VirTermNo > 0) {
		p = putbuf(p, ":am");	/* All virt terms have auto margins */
		cancelled("am");
	}
# endif
E 31
E 2
	while (*bp) {
		switch (*bp) {
		case ':':	/* discard empty, cancelled  or dupl fields */
			tp = bp+1;
			empty = YES;
			while (*tp && *tp != ':') {
				empty = (empty && WHITE(*tp) );
				tp++;
			}
I 2
D 31
# ifdef CBVIRTTERM
			/*
			 * Virtual terminals use ic, not im or ei.  Turn
			 * any of them into ic - duplicates will be cancelled
			 * below.  I assume that terminals needing im+ic+ei
			 * are handled by the kernel.
			 */
			if (VirTermNo > 0 && !HasAM &&
			    (bp[1]=='i' && bp[2]=='m' ||
			     bp[1]=='e' && bp[2]=='i')) {
				bp[1] = 'i';
				bp[2] = 'c';
			}
			if (VirTermNo > 0 && !HasAM &&
			    (bp[1]=='c' && bp[2]=='s')) {
				bp[1] = 'd';
				bp[2] = 'l';
				/* Also need al, so kludge: */
				if (!cancelled("al"))
				    p = putbuf(p, ":al=\033\120");
			}
# endif CBVIRTTERM
E 31
E 2
			if (empty || cancelled(bp+1)) {
				bp = tp;
				continue;
			}
I 2
D 31
# ifdef CBVIRTTERM
			if (VirTermNo > 0 && !HasAM)
				for (i = 0; vtab[i].value; i++) {
					if (vtab[i].cap[0] == bp[1] &&
					    vtab[i].cap[1] == bp[2]) {
						*p++ = *bp++;	/* colon */
						*p++ = *bp++;	/* first char */
						*p++ = *bp++;	/* second "   */
						*p++ = *bp++;	/* = sign */
						p = putbuf(p, vtab[i].value);
						bp = tp;
						goto contin;
					}
				}
# endif CBVIRTTERM
E 31
E 2
			break;

		case ' ':	/* no spaces in output */
			p = putbuf(p, "\\040");
			bp++;
E 32
I 32
	for (; *argv; ++argv) {
		if (argv[0][0] != '-' || argv[1] && argv[1][0] != '-' ||
		    argv[0][1] != 'e' && argv[0][1] != 'i' &&
		    argv[0][1] != 'k' || argv[0][2] != '\0')
E 32
			continue;
D 32

I 2
		case '!':	/* the shell thinks this is history */
			p = putbuf(p, "\\041");
			bp++;
			continue;

		case ',':	/* the shell thinks this is history */
			p = putbuf(p, "\\054");
			bp++;
			continue;

E 2
		case '"':	/* no quotes in output */
			p = putbuf(p, "\\042");
			bp++;
			continue;

		case '\'':	/* no quotes in output */
			p = putbuf(p, "\\047");
			bp++;
			continue;

I 2
		case '`':	/* no back quotes in output */
			p = putbuf(p, "\\140");
			bp++;
			continue;

E 2
		case '\\':
		case '^':	/* anything following is OK */
			*p++ = *bp++;
I 2
D 31
# ifdef CBVIRTTERM
			if (*bp == 'E' && VirTermNo > 0 &&
				(bp[-3]!='\\'||bp[-2]!='E') &&
				(bp[1]!='\\'||bp[2]!='E'))
				p = putbuf(p, "E\\");
# endif CBVIRTTERM
E 31
E 2
		}
		*p++ = *bp++;
I 21
D 31
# ifdef CBVIRTTERM
E 21
I 2
contin:		;
I 21
# endif CBVIRTTERM
E 31
E 21
E 2
	}
I 2
	*p++ = ':';	/* we skipped the last : with the : lookahead hack */
E 2
D 21
	write (STDOUT, buf, p-buf);
E 21
I 21
	(void) write (STDOUT, buf, p-buf);
E 21
}

I 31
/* Array of termcap entries processed so far by 'cancelled',
   for omitting duplicates from the output. */
char delcap[128][2];

/* Number of valid entries in 'delcap'. */
int ncap = 0;

/* Return YES if 'cap' is a commented-out or duplicate capability,
   NO if not. */

int
E 31
cancelled(cap)
char	*cap;
{
	register int i;

	for (i = 0; i < ncap; i++)
	{
		if (cap[0] == delcap[i][0] && cap[1] == delcap[i][1])
			return (YES);
	}
	/* delete a second occurrance of the same capability */
	delcap[ncap][0] = cap[0];
	delcap[ncap][1] = cap[1];
	ncap++;
	return (cap[2] == '@');
}

I 31
/* Append a printable representation of 'str' to 'ptr' and
   return a pointer to the next available character after 'ptr'. */

E 31
char *
putbuf(ptr, str)
char	*ptr;
char	*str;
{
D 2
	while (*str)
		*ptr++ = *str++;
E 2
I 2
	char buf[20];

	while (*str) {
		switch (*str) {
		case '\033':
			ptr = putbuf(ptr, "\\E");
			str++;
E 32
I 32
		switch(argv[0][1]) {
		case 'e':
			argv[0] = "-e^H";
E 32
			break;
D 32
		default:
			if (*str <= ' ') {
D 21
				sprintf(buf, "\\%03o", *str);
E 21
I 21
				(void) sprintf(buf, "\\%03o", *str);
E 21
				ptr = putbuf(ptr, buf);
				str++;
			} else
				*ptr++ = *str++;
E 32
I 32
		case 'i':
			argv[0] = "-i^C";
			break;
		case 'k':
			argv[0] = "-k^U";
			break;
E 32
		}
	}
E 2
D 32
	return (ptr);
E 32
}
D 32

I 31
/* Return the internal form of ASCII baud rate 'p',
   or -1 if 'p' does not represent a valid baud rate. */
E 31

I 31
int
E 31
baudrate(p)
char	*p;
{
	char buf[8];
	int i = 0;

	while (i < 7 && (isalnum(*p) || *p == '.'))
		buf[i++] = *p++;
	buf[i] = NULL;
	for (i=0; speeds[i].string; i++)
D 31
		if (sequal(speeds[i].string, buf))
E 31
I 31
		if (!strcmp(speeds[i].string, buf))
E 31
			return (speeds[i].speed);
	return (-1);
}

I 31
/* Return the type of terminal to use for a port of type 'type',
   as specified by the first applicable mapping in 'map'.
   If no mappings apply, return 'type'. */

E 31
char *
D 2
mapped(type, speed)
E 2
I 2
mapped(type)
E 2
char	*type;
D 2
short	speed;
E 2
{
I 2
D 31
# ifdef	V6
	extern int	ospeed;
# else
	extern short	ospeed;
# endif
E 31
E 2
	int	match;

D 31
# ifdef DEB
D 2
	printf ("spd:%d\n", speed);
E 2
I 2
	printf ("spd:%d\n", ospeed);
E 2
	prmap();
# endif
E 31
	Map = map;
	while (Map->Ident)
	{
D 2
		if (*(Map->Ident) == NULL || bequal(Map->Ident, type, 4))
E 2
I 2
D 31
		if (*(Map->Ident) == NULL || sequal(Map->Ident, type) || isalias(Map->Ident))
E 31
I 31
		if (*(Map->Ident) == '\0'
		    || !strcmp(Map->Ident, type) || isalias(Map->Ident))
E 31
E 2
		{
			match = NO;
			switch (Map->Test)
			{
				case ANY:	/* no test specified */
				case ALL:
					match = YES;
					break;
				
				case GT:
D 2
					match = (speed > Map->Speed);
E 2
I 2
					match = (ospeed > Map->Speed);
E 2
					break;

				case GE:
D 2
					match = (speed >= Map->Speed);
E 2
I 2
					match = (ospeed >= Map->Speed);
E 2
					break;

				case EQ:
D 2
					match = (speed == Map->Speed);
E 2
I 2
					match = (ospeed == Map->Speed);
E 2
					break;

				case LE:
D 2
					match = (speed <= Map->Speed);
E 2
I 2
					match = (ospeed <= Map->Speed);
E 2
					break;

				case LT:
D 2
					match = (speed < Map->Speed);
E 2
I 2
					match = (ospeed < Map->Speed);
E 2
					break;

				case NE:
D 2
					match = (speed != Map->Speed);
E 2
I 2
					match = (ospeed != Map->Speed);
E 2
					break;
			}
			if (match)
				return (Map->Type);
		}
		Map++;
	}
	/* no match found; return given type */
	return (type);
}

E 32
I 32
D 33
		
E 33
I 33

E 33
E 32
D 31
# ifdef DEB
prmap()
E 31
I 31
void
usage()
E 31
{
D 31
	Map = map;
	while (Map->Ident)
	{
	printf ("%s t:%d s:%d %s\n",
		Map->Ident, Map->Test, Map->Speed, Map->Type);
	Map++;
	}
}
# endif

char *
nextarg(argc, argv)
int	argc;
char	*argv[];
{
	if (argc <= 0)
		fatal ("Too few args: ", *argv);
	if (*(*++argv) == '-')
		fatal ("Unexpected arg: ", *argv);
	return (*argv);
}

fatal (mesg, obj)
char	*mesg;
char	*obj;
{
	prs (mesg);
	prs (obj);
	prc ('\n');
	prs (USAGE);
	flush();
E 31
I 31
D 32
	fprintf(stderr, "\
Usage: %s [-] [-hnrsIQS] [-eC] [-iC] [-kC] [-EC]\n\
       [-m [port-type][test baudrate]:terminal-type] [terminal-type]\n",
		program_name);
E 32
I 32
	(void)fprintf(stderr,
D 33
"usage: tset [-IQs] [-] [-e ch] [-i ch] [-k ch] [-m mapping] [terminal]\n");
E 33
I 33
D 34
"usage: tset [-IQrs] [-] [-e ch] [-i ch] [-k ch] [-m mapping] [terminal]\n");
E 34
I 34
"usage: tset [-IQrSs] [-] [-e ch] [-i ch] [-k ch] [-m mapping] [terminal]\n");
E 34
E 33
E 32
E 31
	exit(1);
}
E 1
