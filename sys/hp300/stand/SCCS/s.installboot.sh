h05371
s 00008/00002/00022
d D 8.2 94/03/21 13:56:46 bostic 3 2
c add a copyright notice
e
s 00000/00000/00024
d D 8.1 93/06/10 21:48:37 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00024/00000/00000
d D 7.1 93/03/14 13:56:39 mckusick 1 0
c date and time created 93/03/14 13:56:39 by mckusick
e
u
U
t
T
I 1
D 3
#!/bin/sh
# compatibility with old installboot program
E 3
I 3
#!/bin/sh -
E 3
#
I 3
# Copyright (c) 1994
#	The Regents of the University of California.  All rights reserved.
#
# %sccs.include.redist.sh%
#
E 3
#	%W% (Berkeley) %G%
I 3
#
# compatibility with old installboot program
E 3
#
if [ $# != 2 ]
then
	echo "Usage: installboot bootprog device"
	exit 1
fi
if [ ! -f $1 ]
then
	echo "Usage: installboot bootprog device"
	echo "${1}: bootprog must be a regular file"
	exit 1
fi
if [ ! -c $2 ]
then
	echo "Usage: installboot bootprog device"
	echo "${2}: device must be a char special file"
	exit 1
fi
/sbin/disklabel -B -b $1 $2
exit $?
E 1
