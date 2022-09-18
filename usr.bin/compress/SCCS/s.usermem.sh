h47663
s 00002/00002/00092
d D 5.6 89/05/11 10:48:27 bostic 6 5
c file reorg, pathnames.h, paths.h
e
s 00015/00000/00075
d D 5.5 88/10/15 09:00:12 bostic 5 4
c add Berkeley specific copyright
e
s 00002/00001/00073
d D 5.4 85/09/17 17:49:16 lepreau 4 3
c Make it work on on /nbsd.  It was returning 0, which with the Makefile's
c SACREDMEM caused BITS to be 12.  Yech.
e
s 00016/00015/00058
d D 5.3 85/09/17 16:43:33 lepreau 3 2
c Reorder so that 'limit' determination works.
e
s 00014/00003/00059
d D 5.2 85/09/17 15:43:09 lepreau 2 1
c Compress 4.0
e
s 00062/00000/00000
d D 5.1 85/06/06 18:48:02 mckusick 1 0
c 4.3 beta version
e
u
U
t
T
I 1
#!/bin/sh -
#
I 5
# Copyright (c) 1985 The Regents of the University of California.
# All rights reserved.
#
# This code is derived from software contributed to Berkeley by
# James A. Woods, derived from original work by Spencer Thomas
# and Joseph Orost.
#
# Redistribution and use in source and binary forms are permitted
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
#
E 5
#	%W% (Berkeley) %G%
#
: This shell script snoops around to find the maximum amount of available
: user memory.  These variables need to be set only if there is no
: /usr/adm/messages.  KMEM, UNIX, and CLICKSIZE can be set on the command
: line, if desired, e.g. UNIX=/unix
KMEM=/dev/kmem		# User needs read access to KMEM
UNIX=
# VAX			CLICKSIZE=512,	UNIX=/vmunix
# PDP-11		CLICKSIZE=64,	UNIX=/unix
# CADLINC 68000		CLICKSIZE=4096,	UNIX=/unix
# Perkin-Elmer 3205	CLICKSIZE=4096,	UNIX=/edition7
# Perkin-Elmer all others, CLICKSIZE=2048, UNIX=/edition7
CLICKSIZE=512
eval $*

I 3
if test -n "$UNIX"
then
    : User must have specified it already.
elif test -r /vmunix
then
    UNIX=/vmunix
    CLICKSIZE=512	# Probably VAX
elif test -r /edition7
then
    UNIX=/edition7
    CLICKSIZE=2048	# Perkin-Elmer: change to 4096 on a 3205
elif test -r /unix
then
    UNIX=/unix		# Could be anything
fi

E 3
SIZE=0
D 4
if test -r /usr/adm/messages	# probably the most transportable
E 4
I 4
# messages: probably the most transportable
D 6
if test -r /usr/adm/messages -a -s /usr/adm/messages
E 6
I 6
if test -r /var/log/messages -a -s /var/log/messages
E 6
E 4
then
D 6
    SIZE=`grep avail /usr/adm/messages | sed -n '$s/.*[ 	]//p'`
E 6
I 6
    SIZE=`grep avail /var/log/messages | sed -n '$s/.*[ 	]//p'`
E 6
fi

if test 0$SIZE -le 0		# no SIZE in /usr/adm/messages
then
    if test -r $KMEM		# Readable KMEM
    then
D 3
	if test -n "$UNIX"
	then
	    : User must have specified it already.
	elif test -r /vmunix
	then
	    UNIX=/vmunix
	    CLICKSIZE=512	# Probably VAX
	elif test -r /edition7
	then
	    UNIX=/edition7
	    CLICKSIZE=2048	# Perkin-Elmer: change to 4096 on a 3205
	elif test -r /unix
	then
	    UNIX=/unix		# Could be anything
	fi
E 3
	if test -n "$UNIX"
	then
	    SIZE=`echo maxmem/D | adb $UNIX $KMEM | sed -n '$s/.*[ 	]//p'`
	    if test 0$SIZE -le 0
	    then
D 2
		SIZE=`echo physmem/D | adb $UNIX $KMEM | sed -n '$s/.*[ 
	]//p'`
E 2
I 2
		SIZE=`echo physmem/D | adb $UNIX $KMEM | sed -n '$s/.*[ 	]//p'`
E 2
	    fi
	    SIZE=`expr 0$SIZE '*' $CLICKSIZE`
	fi
    fi
fi

I 2
case $UNIX in
    /vmunix)		# Assume 4.2bsd: check for resource limits
	MAXSIZE=`csh -c limit | awk 'BEGIN	{ MAXSIZE = 1000000 }
/datasize|memoryuse/ && NF == 3	{ if ($2 < MAXSIZE) MAXSIZE = $2 }
END	{ print MAXSIZE * 1000 }'`
	if test $MAXSIZE -lt $SIZE
	then
	    SIZE=$MAXSIZE
	fi
	;;
esac

E 2
if test 0$SIZE -le 0
then
D 2
    echo 0
E 2
I 2
    echo 0;exit 1
E 2
else
    echo $SIZE
fi
E 1
