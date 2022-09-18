h51383
s 00000/00000/00022
d D 8.1 94/04/20 09:53:00 mckusick 18 17
c pull to 8.1 for 4.4BSD-Lite release
e
s 00002/00002/00020
d D 7.9 94/04/20 09:52:10 mckusick 17 16
c update osrelease to 4.4BSD-Lite
e
s 00002/00003/00020
d D 7.8 93/06/10 21:16:36 bostic 16 14
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00021
d R 8.1 93/06/10 21:15:36 bostic 15 14
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00021
d D 7.7 93/05/22 14:45:52 bostic 14 13
c it's not alpha anymore
e
s 00006/00004/00017
d D 7.6 93/02/10 19:41:22 mckusick 13 12
c additional information for uname
e
s 00002/00002/00019
d D 7.5 92/08/23 08:57:25 bostic 12 11
c update to 4.4BSD-Alpha
e
s 00006/00003/00015
d D 7.4 90/12/07 15:19:38 bostic 11 10
c add Berkeley specific copyright
e
s 00002/00002/00016
d D 7.3 90/07/01 10:55:35 karels 10 9
c it's Reno
e
s 00004/00004/00014
d D 7.2 89/04/25 10:09:35 mckusick 9 8
c do not use absolute pathname for echo
e
s 00001/00001/00017
d D 7.1 86/06/05 01:47:02 mckusick 8 7
c 4.3BSD release version
e
s 00004/00004/00014
d D 1.7 86/01/09 19:42:20 mckusick 7 6
c use /bin/echo (from Doug Kingston <mcvax!dpk@seismo.CSS.GOV>)
e
s 00009/00014/00009
d D 1.6 85/08/29 17:55:27 bloom 6 5
c fix 2 field timezones from date (from mcvax!jim)
e
s 00008/00001/00015
d D 1.5 85/06/08 12:07:16 mckusick 5 4
c Add copyright
e
s 00013/00005/00003
d D 1.4 85/06/03 08:38:47 karels 4 3
c separate sccs line
e
s 00003/00002/00005
d D 1.3 85/05/08 21:48:55 karels 3 2
c add sccs hack for what; bump version!
e
s 00001/00001/00006
d D 1.2 84/08/28 12:15:09 bloom 2 1
c Add info about who compiled the kernel and where
e
s 00007/00000/00000
d D 1.1 84/08/28 12:06:05 bloom 1 0
c date and time created 84/08/28 12:06:05 by bloom
e
u
U
t
T
I 1
D 5
#sccsid	%M%	%I%	%E%
E 5
I 5
#!/bin/sh -
#
D 8
# Copyright (c) 1980 Regents of the University of California.
E 8
I 8
D 11
# Copyright (c) 1980, 1986 Regents of the University of California.
E 8
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 11
I 11
D 13
# Copyright (c) 1984, 1986, 1990 The Regents of the University of California.
E 13
I 13
D 16
# Copyright (c) 1984,1986,1990,1993 The Regents of the University of California.
E 13
# All rights reserved.
E 16
I 16
# Copyright (c) 1984, 1986, 1990, 1993
#	The Regents of the University of California.  All rights reserved.
E 16
E 11
#
I 11
# %sccs.include.redist.sh%
#
E 11
#	%W% (Berkeley) %G%
D 16
#
E 16
I 11

E 11
E 5
D 6
if [ ! -r version ]; then echo 0 > version; fi
E 6
I 6
if [ ! -r version ]
then
D 7
	echo 0 > version
E 7
I 7
D 9
	/bin/echo 0 > version
E 9
I 9
	echo 0 > version
E 9
E 7
fi
I 11

E 11
E 6
touch version
D 4
awk '	{	version = $1 + 1; }\
D 3
END	{	printf "char version[] = \"4.2 BSD UNIX #%d: ", version > "vers.c";\
		printf "%d\n", version > "version"; }' < version
E 3
I 3
END	{	printf "static char sccs[4] = '"{'@', '(', '#', ')'}"';\n";\
		printf "char version[] = \"4.3 BSD UNIX #%d: ", version ;\
		printf "%d\n", version > "version"; }' > vers.c < version
E 3
D 2
echo `date`'\n";' >> vers.c
E 2
I 2
echo `date`'\n    '$USER'@'`hostname`':'`pwd`'\n";' >> vers.c
E 4
I 4
D 6
echo `cat version` ${USER-root} `pwd` `date` `hostname` | \
awk ' {
	version = $1 + 1; user = $2; host = $10; dir = $3; \
	date = $4 " " $5 " " $6 " " $7 " " $8 " " $9;
}\
END {
	printf "char sccs[] = \"@(#)4.3 BSD #%d: %s (%s@%s:%s)\\n\";\n",\
		version, date, user, host, dir ;\
	printf "char version[] = \"4.3 BSD UNIX #%d: %s\\n", \
		version, date; \
	printf "    %s@%s:%s\\n\";\n", user, host, dir;
	printf "%d\n", version > "version";
}' > vers.c
E 6
I 6
v=`cat version` u=${USER-root} d=`pwd` h=`hostname` t=`date`
D 7
( echo "char sccs[] = \"@(#)4.3 BSD #${v}: ${t} (${u}@${h}:${d})\\n\";" ;
  echo "char version[] = \"4.3 BSD UNIX #${v}: ${t}\\n    ${u}@${h}:${d}\\n\";"
E 7
I 7
D 9
( /bin/echo "char sccs[] = \"@(#)4.3 BSD #${v}: ${t} (${u}@${h}:${d})\\n\";" ;
  /bin/echo "char version[] = \"4.3 BSD UNIX #${v}: ${t}\\n    ${u}@${h}:${d}\\n\";"
E 9
I 9
D 10
( echo "char sccs[] = \"@(#)4.3 BSD #${v}: ${t} (${u}@${h}:${d})\\n\";" ;
  echo "char version[] = \"4.3 BSD UNIX #${v}: ${t}\\n    ${u}@${h}:${d}\\n\";"
E 10
I 10
D 12
( echo "char sccs[] = \"@(#)4.3 BSD Reno #${v}: ${t} (${u}@${h}:${d})\\n\";" ;
  echo "char version[] = \"4.3 BSD Reno UNIX #${v}: ${t}\\n    ${u}@${h}:${d}\\n\";"
E 12
I 12
D 13
( echo "char sccs[] = \"@(#)4.4BSD-Alpha #${v}: ${t} (${u}@${h}:${d})\\n\";" ;
  echo "char version[] = \"4.4BSD-Alpha UNIX #${v}: ${t}\\n    ${u}@${h}:${d}\\n\";"
E 12
E 10
E 9
E 7
) > vers.c
E 13
I 13
echo "char ostype[] = \"4.4BSD\";" > vers.c
D 14
echo "char osrelease[] = \"4.4BSD-Alpha\";" >> vers.c
E 14
I 14
D 17
echo "char osrelease[] = \"4.4BSD\";" >> vers.c
E 17
I 17
echo "char osrelease[] = \"4.4BSD-Lite\";" >> vers.c
E 17
E 14
echo "char sccs[4] = { '@', '(', '#', ')' };" >>vers.c
D 14
echo "char version[] = \"4.4BSD-Alpha UNIX #${v}: ${t}\\n    ${u}@${h}:${d}\\n\";" >>vers.c
E 14
I 14
D 17
echo "char version[] = \"4.4BSD UNIX #${v}: ${t}\\n    ${u}@${h}:${d}\\n\";" >>vers.c
E 17
I 17
echo "char version[] = \"4.4BSD-Lite #${v}: ${t}\\n    ${u}@${h}:${d}\\n\";" >>vers.c
E 17
E 14

E 13
D 7
echo `expr ${v} + 1` > version
E 7
I 7
D 9
/bin/echo `expr ${v} + 1` > version
E 9
I 9
echo `expr ${v} + 1` > version
E 9
E 7
E 6
E 4
E 2
E 1
