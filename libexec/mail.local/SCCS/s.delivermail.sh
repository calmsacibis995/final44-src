h23590
s 00006/00000/00000
d D 5.1 89/04/21 09:49:19 bostic 1 0
c date and time created 89/04/21 09:49:19 by bostic
e
u
U
t
T
I 1
#! /bin/sh
# delivermail hack thanks to Jay Lepreau
echo "Subject: delivermail $*" >/tmp/foo.$$
echo "---------------------------------" >>/tmp/foo.$$
cat /tmp/foo.$$ - | /bin/mail postmaster
rm /tmp/foo.$$
E 1
