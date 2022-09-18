h52791
s 00002/00002/00038
d D 8.1 93/06/04 18:46:36 bostic 16 15
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00039
d D 5.12 92/07/25 16:44:03 bostic 15 14
c update bugs address
e
s 00001/00000/00039
d D 5.11 90/07/25 21:56:45 bostic 14 13
c make sure the file's writeable
e
s 00004/00013/00035
d D 5.10 90/07/25 21:51:28 bostic 13 12
c new copyright notice
e
s 00010/00007/00038
d D 5.9 89/05/11 09:57:31 bostic 12 11
c file reorg, pathnames.h, paths.h
e
s 00010/00005/00035
d D 5.8 88/06/29 21:43:16 bostic 11 10
c install approved copyright notice
e
s 00009/00004/00031
d D 5.7 88/02/01 16:16:38 bostic 10 9
c add Berkeley specific header
e
s 00001/00001/00034
d D 5.6 86/02/12 19:01:58 bloom 9 8
c mv bugformat to /usr/lib
e
s 00003/00001/00032
d D 5.5 85/09/07 18:12:28 serge 8 7
c handle interrupts correctly
e
s 00002/00001/00031
d D 5.4 85/08/09 17:17:45 kre 7 6
c changed default address to 4bsd-bugs@berkeley.edu, and
c added a comment to show uup sites what to change it to.
e
s 00023/00015/00009
d D 5.3 85/08/09 16:45:04 kre 6 5
c rewrite in sh (hooray!) and add copyright
e
s 00001/00001/00023
d D 5.2 85/07/29 09:10:35 bloom 5 4
c people adding copyrights didn't look at what they were doing
e
s 00007/00003/00017
d D 5.1 85/06/06 08:59:40 dist 4 3
c Add copyright
e
s 00005/00001/00015
d D 4.3 84/03/26 11:48:40 ralph 3 2
c check EDITOR environment variable to use different editor.
e
s 00001/00001/00015
d D 4.2 83/05/23 15:54:17 ralph 2 1
c fixed path of bugformat
e
s 00016/00000/00000
d D 4.1 83/05/11 13:55:06 ralph 1 0
c date and time created 83/05/11 13:55:06 by ralph
e
u
U
t
T
I 1
D 4
#! /bin/csh -f
E 4
I 4
D 5
#!/bin/sh -
E 5
I 5
D 6
#!/bin/csh -f
E 6
I 6
#!/bin/sh -
E 6
E 5
E 4
#
D 4
#	%M%	%I%	%E%
# Create a bug report and mail to '4bsd-bugs'.
E 4
I 4
D 13
# Copyright (c) 1983 Regents of the University of California.
E 13
I 13
D 16
# Copyright (c) 1983 The Regents of the University of California.
E 13
D 10
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 10
I 10
# All rights reserved.
E 16
I 16
# Copyright (c) 1983, 1993
#	The Regents of the University of California.  All rights reserved.
E 16
E 10
E 4
#
I 4
D 6
#	%W% (Berkeley) %G%
E 6
I 6
D 10
#	%W% (Berkeley) %E%
E 10
I 10
D 13
# Redistribution and use in source and binary forms are permitted
D 11
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific prior written permission. This software
# is provided ``as is'' without express or implied warranty.
E 11
I 11
# provided that the above copyright notice and this paragraph are
# duplicated in all such forms and that any documentation,
# advertising materials, and other materials related to such
# distribution and use acknowledge that the software was developed
# by the University of California, Berkeley.  The name of the
# University may not be used to endorse or promote products derived
# from this software without specific prior written permission.
# THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
# WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 13
I 13
# %sccs.include.redist.sh%
E 13
E 11
E 10
E 6
#
D 10
# Create a bug report and mail to '4bsd-bugs'.
E 10
I 10
#	%W% (Berkeley) %G%
E 10
I 6
#
I 10
D 13
# Create a bug report and mail to '4bsd-bugs'.
E 13
I 13

# create a bug report and mail it to '4bsd-bugs'.
E 13
E 10
E 6
E 4

I 12
PATH=/bin:/sbin:/usr/sbin:/usr/bin
export PATH

E 12
D 6
onintr clean
D 2
/bin/cp bugformat /tmp/bug$$
E 2
I 2
/bin/cp /usr/ucb/bugformat /tmp/bug$$
E 2
D 3
/usr/ucb/vi /tmp/bug$$
E 3
I 3
if ( ! $?EDITOR ) then
	set EDITOR = /usr/ucb/vi
endif
$EDITOR /tmp/bug$$
E 3
if ($#argv == 0) then
	/usr/lib/sendmail -t 4bsd-bugs\@BERKELEY < /tmp/bug$$
else
	/usr/lib/sendmail -t $argv[1] < /tmp/bug$$
endif
E 6
I 6
TEMP=/tmp/bug$$
D 9
FORMAT=/usr/ucb/bugformat
E 9
I 9
D 12
FORMAT=/usr/lib/bugformat
E 12
I 12
FORMAT=/usr/share/misc/bugformat
E 12
E 9
E 6
I 3

E 3
D 6
clean:
/bin/rm -f /tmp/bug$$
E 6
I 6
D 7
: ${BUGADDR=4bsd-bugs@ucbarpa.BERKELEY.EDU}
E 7
I 7
# uucp sites should use ": ${BUGADDR=ucbvax!4bsd-bugs}" with a suitable path.
D 15
: ${BUGADDR=4bsd-bugs@BERKELEY.EDU}
E 15
I 15
: ${BUGADDR=4bsd-bugs@CS.Berkeley.EDU}
E 15
E 7
D 12
: ${EDITOR=/usr/ucb/vi}
E 12
I 12
: ${EDITOR=vi}
E 12

D 8
trap '/bin/rm -f $TEMP' 0 1 2 3 13 15
E 8
I 8
D 12
trap '/bin/rm -f $TEMP ; exit 1' 1 2 3 13 15
E 12
I 12
trap 'rm -f $TEMP ; exit 1' 1 2 3 13 15
E 12
E 8

D 12
/bin/cp $FORMAT $TEMP
E 12
I 12
cp $FORMAT $TEMP
I 14
chmod u+w $TEMP
E 14
E 12
if $EDITOR $TEMP
then
	if cmp -s $FORMAT $TEMP
	then
		echo "File not changed, no bug report submitted."
		exit
	fi
	case "$#" in
D 12
	0) /usr/lib/sendmail -t -oi $BUGADDR  < $TEMP ;;
	*) /usr/lib/sendmail -t -oi "$@" < $TEMP ;;
E 12
I 12
	0) sendmail -t -oi $BUGADDR  < $TEMP ;;
	*) sendmail -t -oi "$@" < $TEMP ;;
E 12
	esac
fi
I 8

D 12
/bin/rm -f $TEMP
E 12
I 12
rm -f $TEMP
E 12
E 8
E 6
E 1
