h32422
s 00002/00002/00027
d D 8.1 93/06/06 16:06:53 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00003/00023
d D 5.2 91/04/16 16:27:58 bostic 6 5
c new copyright; att/bsd/shared
e
s 00007/00002/00019
d D 5.1 85/06/05 16:02:28 dist 5 4
c Add copyright
e
s 00000/00000/00021
d D 2.4 84/02/08 20:50:35 aoki 4 3
c synchronize to version 2
e
s 00001/00003/00020
d D 2.3 83/04/07 15:11:25 peter 3 2
c makefiles live in ../src, and are symbolically linked from ../pi and ../pc0.
e
s 00002/00002/00021
d D 2.2 83/02/06 16:04:11 mckusick 2 1
c update for new source layout
e
s 00023/00000/00000
d D 2.1 83/02/06 15:54:55 mckusick 1 0
c date and time created 83/02/06 15:54:55 by mckusick
e
u
U
t
T
I 1
D 5
# !/bin/csh
E 5
I 5
#!/bin/csh -f
E 5
#
D 5
#	%W% (Berkeley) %E%
E 5
I 5
D 6
# Copyright (c) 1980 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 6
I 6
D 7
# Copyright (c) 1980 The Regents of the University of California.
# All rights reserved.
E 7
I 7
# Copyright (c) 1980, 1993
#	The Regents of the University of California.  All rights reserved.
E 7
E 6
#
I 6
# %sccs.include.redist.sh%
#
E 6
#	%W% (Berkeley) %G%
#
I 6

E 6
E 5
#	update the version number of your argument makefile, etc.
#
I 6

E 6
if ( $#argv != 2 ) then
    echo "usage: /bin/csh newversion.csh whoami directory"
    exit(1)
endif
set whoami = $1
set dir = $2
set makefile = ${whoami}makefile
sccs edit $makefile
set oldversion = `grep "VERSION = " $makefile | sed "s/VERSION = //"`
cp $makefile /tmp/$$; awk -f newversion.awk < /tmp/$$ > $makefile ; rm /tmp/$$
set newversion = `grep "VERSION = " $makefile | sed "s/VERSION = //"`
echo version $oldversion becomes $newversion automagically.
D 3
sccs delta $makefile << EOF
E 3
I 3
sccs delget $makefile << EOF
E 3
version $oldversion becomes $newversion automagically.
EOF
D 2
rm -f $dir/makefile
sccs get -p $makefile > $dir/makefile
E 2
I 2
D 3
rm -f $dir/$makefile
sccs get -p $makefile > $dir/$makefile
E 3
E 2
mv $dir/${whoami}${oldversion}strings $dir/${whoami}${newversion}strings
E 1
