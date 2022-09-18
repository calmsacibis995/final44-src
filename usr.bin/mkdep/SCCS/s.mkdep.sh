h09681
s 00002/00002/00083
d D 8.1 93/06/06 15:31:15 bostic 23 22
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00084
d D 5.21 92/09/02 13:25:08 bostic 22 21
c don't pick up a.out.h
e
s 00001/00001/00084
d D 5.20 91/11/14 10:18:31 bostic 21 20
c look in /usr/old/bin, too, for pcc
e
s 00003/00012/00082
d D 5.19 91/04/12 16:43:44 bostic 20 19
c new copyright; att/bsd/shared
e
s 00006/00000/00088
d D 5.18 89/03/05 11:58:16 bostic 19 18
c if compile fails, don't build .depend file
e
s 00012/00001/00076
d D 5.17 88/10/24 11:43:11 bostic 18 17
c add -a flag
e
s 00000/00008/00077
d D 5.16 88/10/22 15:22:30 bostic 17 16
c remove old "no -M hack", install Chris's real one
e
s 00001/00000/00084
d D 5.15 88/10/21 12:07:57 bostic 16 15
c SunOS 3.2, cc -M, when run on multiple .c files, prints
c "foo.c:" on a line by itself.
e
s 00001/00003/00083
d D 5.14 88/08/30 10:55:00 bostic 15 14
c don't worry about permissions, just move the file into place
e
s 00006/00026/00080
d D 5.13 88/08/19 10:24:59 bostic 14 13
c put dependency list into .depend, not Makefile
e
s 00010/00006/00096
d D 5.12 88/06/30 14:41:05 bostic 13 12
c install approved copyright notice
e
s 00008/00000/00094
d D 5.11 88/05/05 20:33:37 bostic 12 11
c add hack for compilers not having -M flag
e
s 00024/00017/00070
d D 5.10 88/01/14 10:33:17 bostic 11 10
c make it prettier
e
s 00019/00014/00068
d D 5.9 88/01/01 16:04:38 bostic 10 9
c allow both -f and -p at the same time
e
s 00012/00002/00070
d D 5.8 87/12/31 12:18:05 bostic 9 8
c add Berkeley header
e
s 00002/00001/00070
d D 5.7 87/10/13 13:31:47 bostic 8 7
c fix PATH
e
s 00001/00001/00070
d D 5.6 87/09/11 12:30:50 bostic 7 6
c flags are optional
e
s 00001/00001/00070
d D 5.5 87/06/18 12:23:17 bostic 6 5
c when remove ./, replace with space
e
s 00009/00006/00062
d D 5.4 87/06/05 12:27:55 bostic 5 4
c use copy to preserve permissions, make -f work, add PATH
e
s 00018/00005/00050
d D 5.3 87/06/04 17:16:16 bostic 4 3
c add -f, -p flags
e
s 00012/00002/00043
d D 5.2 87/06/02 18:36:33 bostic 3 1
c disallow no args, missing or not-writeable Makefile
e
s 00010/00000/00045
d R 5.2 87/06/02 18:17:02 bostic 2 1
c disallow no args, or missing "Makefile"
e
s 00045/00000/00000
d D 5.1 87/06/02 17:54:28 bostic 1 0
c date and time created 87/06/02 17:54:28 by bostic
e
u
U
t
T
I 1
D 9
#! /bin/sh
E 9
I 9
#!/bin/sh -
E 9
#
D 9
#	%W%	(Berkeley)	%G%
E 9
I 9
D 20
# Copyright (c) 1987 Regents of the University of California.
E 20
I 20
D 23
# Copyright (c) 1991 The Regents of the University of California.
E 20
# All rights reserved.
E 23
I 23
# Copyright (c) 1991, 1993
#	The Regents of the University of California.  All rights reserved.
E 23
#
D 20
# Redistribution and use in source and binary forms are permitted
D 13
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific prior written permission. This software
# is provided ``as is'' without express or implied warranty.
E 13
I 13
# provided that the above copyright notice and this paragraph are
# duplicated in all such forms and that any documentation,
# advertising materials, and other materials related to such
# distribution and use acknowledge that the software was developed
# by the University of California, Berkeley.  The name of the
# University may not be used to endorse or promote products derived
# from this software without specific prior written permission.
# THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
# WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 20
I 20
# %sccs.include.redist.sh%
E 20
E 13
#
#	%W% (Berkeley) %G%
E 9
#
I 20

E 20
D 13

E 13
I 5
D 8
PATH=:/bin:/usr/bin:/usr/ucb
E 8
I 8
D 21
PATH=/bin:/usr/bin:/usr/ucb
E 21
I 21
PATH=/bin:/usr/bin:/usr/ucb:/usr/old/bin
E 21
export PATH
E 8

I 10
D 14
MAKE=Makefile			# default makefile name is "Makefile"
E 14
I 14
D=.depend			# default dependency file is .depend
I 18
append=0
E 18
E 14

while :
	do case "$1" in
I 18
		# -a appends to the depend file
		-a)
			append=1
			shift ;;

E 18
		# -f allows you to select a makefile name
		-f)
D 14
			MAKE=$2
E 14
I 14
			D=$2
E 14
			shift; shift ;;

		# the -p flag produces "program: program.c" style dependencies
		# so .o's don't get produced
		-p)
D 11
			SED='-e s;\.o;;'
E 11
I 11
D 22
			SED='s;\.o;;'
E 22
I 22
			SED='s;\.o ; ;'
E 22
E 11
			shift ;;
		*)
			break ;;
	esac
done

E 10
E 5
I 3
if [ $# = 0 ] ; then
D 4
	echo 'usage: mkdep flags file ...'
E 4
I 4
D 7
	echo 'usage: mkdep [-p] [-f makefile] flags file ...'
E 7
I 7
D 14
	echo 'usage: mkdep [-p] [-f makefile] [flags] file ...'
E 14
I 14
	echo 'usage: mkdep [-p] [-f depend_file] [cc_flags] file ...'
E 14
E 7
E 4
	exit 1
fi
D 10

D 4
if [ ! -w Makefile ]; then
	echo 'mkdep: no writeable file "Makefile"'
E 4
I 4
MAKE=Makefile			# default makefile name is "Makefile"
case $1 in
	# -f allows you to select a makefile name
	-f)
		MAKE=$2
		shift; shift ;;

	# the -p flag produces "program: program.c" style dependencies
	# so .o's don't get produced
	-p)
		SED='-e s;\.o;;'
		shift ;;
esac
E 10

D 14
if [ ! -w $MAKE ]; then
	echo "mkdep: no writeable file \"$MAKE\""
E 4
	exit 1
fi

E 14
E 3
D 4
CC="/bin/cc -M"
E 4
TMP=/tmp/mkdep$$

D 5
trap '/bin/rm -f $TMP ; exit 1' 1 2 3 13 15
E 5
I 5
trap 'rm -f $TMP ; exit 1' 1 2 3 13 15
E 5

D 5
cp Makefile Makefile.bak
E 5
I 5
D 14
cp $MAKE ${MAKE}.bak
E 5

D 5
sed -e '/DO NOT DELETE THIS LINE/,$d' < Makefile > $TMP
E 5
I 5
sed -e '/DO NOT DELETE THIS LINE/,$d' < $MAKE > $TMP
E 5

cat << _EOF_ >> $TMP
D 3
# DON'T DELETE THIS LINE -- mkdep uses it.
# DON'T PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.
E 3
I 3
# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.
E 3

_EOF_

E 14
I 12
D 17
# If your compiler doesn't have -M, add it.  If you can't, the next two
# lines will try and replace the "cc -M".  The real problem is that this
# hack can't deal with anything that requires a search path, and doesn't
# even try for anything using bracket (<>) syntax.
#
# egrep '^#include[ 	]*".*"' /dev/null $* |
# sed -e 's/:[^"]*"\([^"]*\)".*/: \1/' -e 's/\.c/.o/' |

E 17
E 12
D 4
$CC $* | sed -e 's, ./, ,g' | \
E 4
I 4
D 5
/bin/cc -M $* | /bin/sed -e "s; \./;;g" $SED | \
E 5
I 5
D 6
cc -M $* | /bin/sed -e "s; \./;;g" $SED | \
E 6
I 6
D 11
cc -M $* | /bin/sed -e "s; \./; ;g" $SED | \
E 6
E 5
E 4
	awk ' { \
		if ($1 != prev) { \
			if (rec != "") \
				print rec; rec = $0; prev = $1; \
		} \
		else { \
			if (length(rec $2) > 78) { \
				print rec; rec = $0; \
			} else \
				rec = rec " " $2 \
		} \
	} \
	END { \
		print rec \
	} ' >> $TMP
E 11
I 11
cc -M $* |
sed "
	s; \./; ;g
I 16
	/\.c:$/d
E 16
	$SED" |
awk '{
	if ($1 != prev) {
		if (rec != "")
			print rec;
		rec = $0;
		prev = $1;
	}
	else {
		if (length(rec $2) > 78) {
			print rec;
			rec = $0;
		}
		else
			rec = rec " " $2
	}
}
END {
	print rec
D 14
}' >> $TMP
E 14
I 14
}' > $TMP
E 14
E 11

I 19
if [ $? != 0 ]; then
	echo 'mkdep: compile failed.'
	rm -f $TMP
	exit 1
fi

E 19
D 14
cat << _EOF_ >> $TMP

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
_EOF_

E 14
D 5
mv $TMP Makefile
rm -f Makefile.bak
E 5
I 5
D 15
# copy to preserve permissions
D 14
cp $TMP $MAKE
rm -f ${MAKE}.bak $TMP
E 14
I 14
cp $TMP $D
rm -f $TMP
E 15
I 15
D 18
mv $TMP $D
E 18
I 18
if [ $append = 1 ]; then
	cat $TMP >> $D
	rm -f $TMP
else
	mv $TMP $D
fi
E 18
E 15
E 14
E 5
exit 0
E 1
