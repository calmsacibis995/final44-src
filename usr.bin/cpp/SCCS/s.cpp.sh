h45494
s 00002/00002/00063
d D 8.1 93/06/06 14:29:11 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00064
d D 6.6 93/05/03 21:10:31 bostic 6 5
c gcc2; cpp now in /usr/libexec/gcc2/cpp
e
s 00015/00002/00050
d D 6.5 91/04/01 12:10:35 donn 5 4
c Oops -- forgot that we still have to be able to read standard in!
e
s 00013/00011/00039
d D 6.4 91/03/19 21:47:03 donn 4 3
c Permit multiple source files to be supplied (for use with cpp -M).
e
s 00002/00001/00048
d D 6.3 91/03/19 12:24:20 donn 3 2
c Make the shell happy (new syntax??)
e
s 00001/00001/00048
d D 6.2 91/03/08 11:54:10 donn 2 1
c Don't permit '$' in identifiers, for the sake of the 386 assembler.
e
s 00049/00000/00000
d D 6.1 91/02/01 11:21:14 donn 1 0
c date and time created 91/02/01 11:21:14 by donn
e
u
U
t
T
I 1
#!/bin/sh
#
D 7
# Copyright (c) 1990 The Regents of the University of California.
# All rights reserved.
E 7
I 7
# Copyright (c) 1990, 1993
#	The Regents of the University of California.  All rights reserved.
E 7
#
# This code is derived from software contributed to Berkeley by
# the Systems Programming Group of the University of Utah Computer
# Science Department.
#
# %sccs.include.redist.sh%
#
#	%W% (Berkeley) %G%
#
# Transitional front end to CCCP to make it behave like (Reiser) CCP:
#	specifies -traditional
#	doesn't search gcc-include
#
D 4
cpp="eval exec /usr/libexec/cpp"
E 4
I 4
D 5
cpp="eval /usr/libexec/cpp"
E 5
I 5
PATH=/usr/bin:/bin
D 6
CPP=/usr/libexec/cpp
E 6
I 6
CPP=/usr/libexec/gcc2/cpp
E 6
E 5
E 4
D 2
ALST="-traditional -D__GNUC__"
E 2
I 2
ALST="-traditional -D__GNUC__ -$ "
E 2
NSI=no
D 4
ARGS=""
INCS=""
E 4
I 4
OPTS=""
INCS="-nostdinc"
I 5
FOUNDFILES=no
E 5
E 4

D 3
for A do
E 3
I 3
for A
do
E 3
	case $A in
	-nostdinc)
		NSI=yes
		;;
	-traditional)
		;;
	-I*)
		INCS="$INCS $A"
		;;
	-U__GNUC__)
		ALST=`echo $ALST | sed -e 's/-D__GNUC__//'`
		;;
I 4
	-*)
		OPTS="$OPTS '$A'"
		;;
E 4
	*)
I 5
		FOUNDFILES=yes
E 5
D 4
		ARGS="$ARGS '$A'"
E 4
I 4
		if [ $NSI = "no" ]
		then
			INCS="$INCS -I/usr/include"
			NSI=skip
		fi
D 5
		$cpp $ALST $INCS $LIBS $CSU $OPTS $A || exit $?
E 5
I 5
		eval $CPP $ALST $INCS $LIBS $CSU $OPTS $A || exit $?
E 5
E 4
		;;
	esac
done
I 5

if [ $FOUNDFILES = "no" ]
then
	# read standard input
	if [ $NSI = "no" ]
	then
		INCS="$INCS -I/usr/include"
	fi
	eval exec $CPP $ALST $INCS $LIBS $CSU $OPTS
fi
E 5

D 4
INCS="-nostdinc $INCS"
if [ $NSI = "no" ]
then
	INCS="$INCS -I/usr/include"
fi
$cpp $ALST $INCS $LIBS $CSU $ARGS $GLIB $CLIB
exit $?
E 4
I 4
exit 0
E 4
E 1
