h56633
s 00005/00002/00014
d D 4.3 91/04/18 16:36:25 bostic 3 2
c new copyright; att/bsd/shared
e
s 00001/00001/00015
d D 4.2 89/04/28 17:56:15 mckusick 2 1
c file system reorganization
e
s 00016/00000/00000
d D 4.1 83/05/08 15:08:38 mckusick 1 0
c date and time created 83/05/08 15:08:38 by mckusick
e
u
U
t
T
I 1
D 3
#! /bin/sh
E 3
I 3
#!/bin/sh -
E 3
#
D 3
#	%W%	(Berkeley)	%E%
E 3
I 3
# %sccs.include.proprietary.sh%
E 3
#
I 3
#	%W% (Berkeley) %G%
#

E 3
#	indxbib sh script
#
if test $1
D 2
	then /usr/lib/refer/mkey $* | /usr/lib/refer/inv _$1
E 2
I 2
	then /usr/libexec/mkey $* | /usr/libexec/inv _$1
E 2
	mv _$1.ia $1.ia
	mv _$1.ib $1.ib
	mv _$1.ic $1.ic
else
	echo 'Usage:  indxbib database [ ... ]
	first argument is the basename for indexes
	indexes will be called database.{ia,ib,ic}'
fi
E 1
