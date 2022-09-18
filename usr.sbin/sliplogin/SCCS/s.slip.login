h36128
s 00000/00000/00012
d D 8.1 93/06/06 14:06:19 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00012/00000/00000
d D 5.1 90/07/01 14:54:44 bostic 1 0
c date and time created 90/07/01 14:54:44 by bostic
e
u
U
t
T
I 1
#!/bin/sh -
#
#	%W% (Berkeley) %G%

#
# generic login file for a slip line.  sliplogin invokes this with
# the parameters:
#      1        2         3        4          5         6     7-n
#   slipunit ttyspeed loginname local-addr remote-addr mask opt-args
#
/sbin/ifconfig sl$1 inet $4 $5 netmask $6 
exit
E 1
