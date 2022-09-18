h12714
s 00000/00000/00026
d D 8.1 93/06/06 16:30:12 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00005/00002/00021
d D 4.4 91/04/16 16:45:16 bostic 4 3
c new copyright; att/bsd/shared
e
s 00003/00003/00020
d D 4.3 89/05/10 22:31:05 bostic 3 2
c file reorg, pathnames.h, paths.h
e
s 00001/00000/00022
d D 4.2 83/12/19 11:02:18 karels 2 1
c execute with sh!
e
s 00022/00000/00000
d D 4.1 83/02/11 15:45:15 rrh 1 0
c date and time created 83/02/11 15:45:15 by rrh
e
u
U
t
T
I 2
D 4
#! /bin/sh
E 4
I 4
#!/bin/sh -
E 4
E 2
I 1
#
D 4
#	%W%	(Berkeley)	%E%
E 4
I 4
# %sccs.include.proprietary.sh%
E 4
#
I 4
#	%W% (Berkeley) %G%
#

E 4
trap "rm -f /tmp/struct*$$" 0 1 2 3 13 15
files=no
for i
do
	case $i in
	-*)	;;
	*)	files=yes
	esac
done

case $files in
yes)
D 3
	/usr/lib/struct/structure $* >/tmp/struct$$
E 3
I 3
	/usr/libexec/structure $* >/tmp/struct$$
E 3
	;;
no)
	cat >/tmp/structin$$
D 3
	/usr/lib/struct/structure /tmp/structin$$ $* >/tmp/struct$$
E 3
I 3
	/usr/libexec/structure /tmp/structin$$ $* >/tmp/struct$$
E 3
esac &&
D 3
	/usr/lib/struct/beautify</tmp/struct$$
E 3
I 3
	/usr/libexec/beautify</tmp/struct$$
E 3
E 1
