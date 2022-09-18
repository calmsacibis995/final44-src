h36860
s 00016/00000/00000
d D 5.1 88/10/22 16:11:20 bostic 1 0
c date and time created 88/10/22 16:11:20 by bostic
e
u
U
t
T
I 1
#!/bin/sh -
#
# Copyright (c) 1988 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
#	%W% (Berkeley) %G%
#

trap "" 1 15
if test -t 2>&1  ; then
	echo "Sending output to 'nohup.out'"
	exec nice -5 $* >>nohup.out 2>&1
else
	exec nice -5 $* 2>&1
fi
E 1
