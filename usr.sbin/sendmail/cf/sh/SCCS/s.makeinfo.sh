h65343
s 00001/00000/00051
d D 8.5 95/04/21 08:43:11 eric 8 7
c define __HOST__ from current host name
e
s 00002/00002/00049
d D 8.4 94/03/04 07:32:59 eric 7 6
c patch to handle automounter
e
s 00002/00002/00049
d D 8.3 93/07/23 14:55:51 eric 6 5
c fix Ultrix incompatibility
e
s 00040/00002/00011
d D 8.2 93/07/22 13:03:49 eric 5 4
c portability for SVR4
e
s 00002/00002/00011
d D 8.1 93/06/07 10:12:44 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00001/00013
d D 6.2 93/06/07 10:12:40 bostic 3 2
c typo
e
s 00000/00000/00014
d D 6.1 92/12/21 16:12:29 eric 2 1
c Release 6
e
s 00014/00000/00000
d D 2.1 91/10/02 14:51:25 eric 1 0
c date and time created 91/10/02 14:51:25 by eric
e
u
U
t
T
I 1
#!/bin/sh
D 3

E 3
#
# Copyright (c) 1983 Eric P. Allman
D 4
# Copyright (c) 1988 The Regents of the University of California.
# All rights reserved.
E 4
I 4
# Copyright (c) 1988, 1993
#	The Regents of the University of California.  All rights reserved.
E 4
#
# %sccs.include.redist.sh%
#
#	%W% (Berkeley) %G%
#

D 5
echo '#####' built by `whoami` on `date`
echo '#####' in `pwd` on `hostname`
E 5
I 5
usewhoami=0
usehostname=0
for p in `echo $PATH | sed 's/:/ /g'`
do
	if [ "x$p" = "x" ]
	then
		p="."
	fi
D 6
	if [ -x $p/whoami ]
E 6
I 6
	if [ -f $p/whoami ]
E 6
	then
		usewhoami=1
		if [ $usehostname -ne 0 ]
		then
			break;
		fi
	fi
D 6
	if [ -x $p/hostname ]
E 6
I 6
	if [ -f $p/hostname ]
E 6
	then
		usehostname=1
		if [ $usewhoami -ne 0 ]
		then
			break;
		fi
	fi
done
if [ $usewhoami -ne 0 ]
then
	user=`whoami`
else
	user=$LOGNAME
fi

if [ $usehostname -ne 0 ]
then
	host=`hostname`
else
	host=`uname -n`
fi
D 7
echo '#####' built by $user on `date`
echo '#####' in `pwd` on $host
E 7
I 7
echo '#####' built by $user@$host on `date`
echo '#####' in `pwd` | sed 's/\/tmp_mnt//'
I 8
echo "define(\`__HOST__', $host)dnl"
E 8
E 7
E 5
E 1
