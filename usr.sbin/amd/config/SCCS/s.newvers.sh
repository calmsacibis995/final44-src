h04980
s 00000/00000/00062
d D 8.1 93/06/06 11:52:11 bostic 7 6
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00060
d D 5.6 93/06/06 11:51:41 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00061
d D 5.5 92/02/09 08:31:00 pendry 5 4
c merge in new release
e
s 00003/00003/00059
d D 5.4 91/05/12 15:58:42 pendry 4 3
c checkpoint for network tape
e
s 00032/00011/00030
d D 5.3 91/03/17 13:51:05 pendry 3 2
c from amd5.3 alpha11
e
s 00002/00002/00039
d D 5.2 90/07/29 07:47:12 pendry 2 1
c Works with new make
e
s 00041/00000/00000
d D 5.1 90/06/29 12:42:21 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
#!/bin/sh -
#
D 3
# $Id: newvers.sh,v 5.2 90/06/23 22:21:21 jsp Rel $
E 3
I 3
D 4
# $Id: newvers.sh,v 5.2.1.2 91/03/17 17:41:03 jsp Alpha $
E 3
#
E 4
# Copyright (c) 1989 Jan-Simon Pendry
# Copyright (c) 1989 Imperial College of Science, Technology & Medicine
D 6
# Copyright (c) 1989 The Regents of the University of California.
# All Rights Reserved.
E 6
I 6
# Copyright (c) 1989, 1993
#	The Regents of the University of California.  All Rights Reserved.
E 6
#
# This code is derived from software contributed to Berkeley by
# Jan-Simon Pendry at Imperial College, London.
#
# %sccs.include.redist.sh%
#
#	%W% (Berkeley) %G%
#
I 4
D 5
# $Id: newvers.sh,v 5.2.1.4 91/05/07 22:20:29 jsp Alpha $
E 5
I 5
# $Id: newvers.sh,v 5.2.2.1 1992/02/09 15:11:19 jsp beta $
E 5
#
E 4
D 3
PATH=/usr/ucb:/bin:/usr/bin
if [ $# -ne 1 ]; then echo "Usage: newvers program" >&2; exit 1; fi
E 3
I 3
PATH=/usr/ucb:/bin:/usr/bin:$PATH
if [ $# -ne 3 ]; then echo "Usage: newvers program arch os" >&2; exit 1; fi
E 3
version="version.$1"
if [ ! -r $version ]; then echo 0 > $version; chmod 444 $version; fi
v=`cat $version`
u=${USER-${LOGNAME-root}}
h=`hostname`
#h=`expr "$h" : '\([^.]*\)'`
t=`date`
D 2
r=`cat ../config/RELEASE`
c=`sed 's/$/\\\\n\\\\/' ../text/COPYRIGHT`
E 2
I 2
D 3
r=`cat $d../config/RELEASE`
c=`sed 's/$/\\\\n\\\\/' $d../text/COPYRIGHT`
E 2
if [ -z "$r" -o -z "$c" ]; then
E 3
I 3
D 4
if [ ! -s "$d../config/RELEASE" -o ! -s "$d../text/COPYRIGHT" ]; then
E 4
I 4
if [ ! -s "$d../config/RELEASE"  -o ! -s "$d../text/COPYRIGHT" ]; then
E 4
E 3
	echo ERROR: config file missing >&2
	exit 1
fi
rm -f vers.$1.c
D 3
cat > vers.$1.c << %%
E 3
I 3
(
cat << %%
char copyright[] = "\\
%%
sed 's/$/\\n\\/' $d../text/COPYRIGHT
cat << %%
";
E 3
char version[] = "\\
D 3
${c}
$1 ${r} #${v}: ${t}\\n\\
Built by ${u}@${h}";
E 3
%%
I 3
cat << %%
$1 \\
%%
sed \
	-e 's/\$//g' \
	-e 's/[A-Z][a-z]*://g' \
	-e 's/  */ /g' \
	-e 's/^ //' \
	-e 's/$/\\/' \
	$d../config/RELEASE
cat << %%
 #${v}: ${t}\\n\\
Built by ${u}@${h} for \\
%%
case "$2" in
[aeiou]*) echo "an \\" ;;
*) echo "a \\";;
esac
echo "$2 running $3\";"
) > vers.$1.c
E 3
rm -f $version
D 3
/bin/echo `expr ${v} + 1` > $version
E 3
I 3
expr ${v} + 1 > $version
E 3
chmod 444 $version
E 1
