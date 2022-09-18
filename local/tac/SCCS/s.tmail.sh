h02890
s 00004/00004/00018
d D 1.3 91/04/03 19:30:08 sklower 3 2
c /usr/new->/usr/contrib/bin and /usr/spool/mail -> /var/mail
e
s 00002/00001/00020
d D 1.2 85/10/17 01:58:18 lepreau 2 1
c set PATH so can find tac when run remotely
e
s 00021/00000/00000
d D 1.1 85/06/09 01:42:37 lepreau 1 0
c date and time created 85/06/09 01:42:37 by lepreau
e
u
U
t
T
I 1
#! /bin/sh
#	%W% %G%
# Print out mail backwards.
# Author: Jay Lepreau, Univ of Utah
#
I 2
D 3
PATH=/usr/new:/bin:/usr/bin:/usr/ucb
E 3
I 3
PATH=/usr/contrib/bin:/bin:/usr/bin:/usr/ucb
E 3
E 2
case $# in
D 3
	0) file=/usr/spool/mail/$USER
E 3
I 3
	0) file=/var/mail/$USER
E 3
	   ;;
D 3
	1) if [ -r /usr/spool/mail/$1 ]
E 3
I 3
	1) if [ -r /var/mail/$1 ]
E 3
	   then
D 3
		file=/usr/spool/mail/$1
E 3
I 3
		file=/var/mail/$1
E 3
	   else
	   	file=$1
	   fi
	   ;;
D 2
	*) echo "Usage: $0 [ username ] [ mboxfile ]"
E 2
I 2
	*) echo "Usage: `basename $0` [ username ] [ mboxfile ]"
E 2
	   exit 1
	   ;;
esac	
exec tac '-
From ' $file
E 1
