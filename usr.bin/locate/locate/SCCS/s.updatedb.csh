h44112
s 00001/00001/00050
d D 8.4 94/10/27 13:01:49 mckusick 22 21
c setenv syntax does not use an =
e
s 00002/00001/00049
d D 8.3 94/03/19 13:35:49 bostic 21 20
c To get sort and the other processes called by this script to use
c /var/tmp rather than /tmp for their temporary files, the TMPDIR variable
c must be in the environment rather than private to the shell.
c From: Paul A Vixie <vixie@vix.com>
e
s 00003/00031/00047
d D 8.2 94/01/02 13:34:21 bostic 20 19
c There are some hardwired /var/tmp's in the locate database script.
c There are also an unexplain 28 blank lines at the end.
c From: Craig Leres <leres@ee.lbl.gov>
e
s 00002/00002/00076
d D 8.1 93/06/06 15:00:11 bostic 19 18
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00077
d D 5.4 93/01/25 18:33:43 mckusick 18 17
c prune off NFS filesystems, not slowly descend (from hibler)
e
s 00029/00001/00049
d D 5.3 92/06/01 13:10:43 elan 17 16
c Changed find(1) primaries to more logical evaluation.
e
s 00000/00000/00050
d D 5.2 92/05/27 16:55:46 elan 16 15
c Search globally -- locate(1) is fixed.
e
s 00006/00005/00044
d D 5.1 91/04/02 10:37:39 bostic 15 14
c add sort flag to usr /var/tmp; only search locally
e
s 00014/00020/00035
d D 4.13 90/10/10 09:57:51 bostic 14 13
c insert code to only search locally
e
s 00004/00004/00051
d D 4.12 90/03/11 12:16:48 bostic 13 12
c move fast lookup from find to locate
e
s 00001/00003/00054
d D 4.11 89/09/12 07:53:31 bostic 12 11
c set nice and do mail in weekly script or crontab; change error msg
e
s 00007/00006/00050
d D 4.10 89/08/28 09:23:50 karels 11 10
c update path; use /var/tmp by default, import from environ
e
s 00001/00001/00055
d D 4.9 89/05/19 19:10:31 bostic 10 9
c find.database moves to /var
e
s 00019/00001/00037
d D 4.8 89/05/04 16:11:21 bostic 9 7
c add Berkeley specific copyright notices
e
s 00002/00002/00036
d R 4.8 89/05/04 10:50:26 jak 8 7
c work formerly done inside code module now done with tr
e
s 00002/00002/00036
d D 4.7 89/05/03 17:21:29 bostic 7 6
c file system reorg
e
s 00002/00001/00036
d D 4.6 85/04/22 18:36:49 mckusick 6 5
c break up pipeline to reduce space needs in /tmp
e
s 00001/00000/00036
d D 4.5 85/03/24 18:24:14 serge 5 4
c chmod database world-readable after completion
e
s 00001/00001/00035
d D 4.4 83/07/21 12:06:06 mckusick 4 3
c generate complete database
e
s 00005/00004/00031
d D 4.3 83/07/21 11:22:57 mckusick 3 2
c move database to /usr/lib/find; restrict database to /usr
e
s 00001/00001/00034
d D 4.2 83/07/21 00:34:41 mckusick 2 1
c must use csh, not sh
e
s 00035/00000/00000
d D 4.1 83/07/21 00:15:12 mckusick 1 0
c date and time created 83/07/21 00:15:12 by mckusick
e
u
U
t
T
I 1
D 2
#! /bin/sh
E 2
I 2
#!/bin/csh -f
E 2
#
D 9
#	%W%	(Berkeley)	%E%
E 9
I 9
D 19
# Copyright (c) 1989 The Regents of the University of California.
# All rights reserved.
E 19
I 19
# Copyright (c) 1989, 1993
#	The Regents of the University of California.  All rights reserved.
E 19
#
# This code is derived from software contributed to Berkeley by
# James A. Woods.
#
D 14
# Redistribution and use in source and binary forms are permitted
# provided that the above copyright notice and this paragraph are
# duplicated in all such forms and that any documentation,
# advertising materials, and other materials related to such
# distribution and use acknowledge that the software was developed
# by the University of California, Berkeley.  The name of the
# University may not be used to endorse or promote products derived
# from this software without specific prior written permission.
# THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 14
I 14
# %sccs.include.redist.sh%
E 14
#
#	%W% (Berkeley) %G%
E 9
#
I 14

E 14
D 3
set LIBDIR = /usr/lib/find	# for subprograms
set FINDHONCHO = root		# for error messages
set FCODES = /etc/find.codes	# the database 
E 3
I 3
D 4
set SRCHPATHS = "/usr /bin /etc /lib"	# directories to be put in the database
E 4
I 4
set SRCHPATHS = "/"			# directories to be put in the database
E 4
D 7
set LIBDIR = /usr/lib/find		# for subprograms
E 7
I 7
set LIBDIR = /usr/libexec		# for subprograms
I 11
D 21
if (! $?TMPDIR) set TMPDIR = /var/tmp	# for temp files
E 21
I 21
					# for temp files
D 22
if (! $?TMPDIR) setenv TMPDIR = /var/tmp
E 22
I 22
if (! $?TMPDIR) setenv TMPDIR /var/tmp
E 22
E 21
E 11
E 7
D 12
set FINDHONCHO = root			# for error messages
E 12
D 7
set FCODES = /usr/lib/find/find.codes	# the database 
E 7
I 7
D 10
set FCODES = /usr/libdata/find.database	# the database
E 10
I 10
D 13
set FCODES = /var/db/find.database	# the database
E 13
I 13
set FCODES = /var/db/locate.database	# the database
E 13
E 10
E 7
E 3

D 11
set path = ( $LIBDIR /usr/ucb /bin /usr/bin )
set bigrams = /tmp/f.bigrams$$
set filelist = /tmp/f.list$$
set errs = /tmp/f.errs$$
E 11
I 11
set path = ( /bin /usr/bin )
D 14
set bigrams = $TMPDIR/f.bigrams$$
set filelist = $TMPDIR/f.list$$
set errs = $TMPDIR/f.errs$$
E 14
I 14
set bigrams = $TMPDIR/locate.bigrams.$$
set filelist = $TMPDIR/locate.list.$$
set errs = $TMPDIR/locate.errs.$$
E 14
E 11

# Make a file list and compute common bigrams.
# Alphabetize '/' before any other char with 'tr'.
# If the system is very short of sort space, 'bigram' can be made
# smarter to accumulate common bigrams directly without sorting
# ('awk', with its associative memory capacity, can do this in several
# lines, but is too slow, and runs out of string space on small machines).

D 12
nice +10
E 12
D 3
find / -print | tr '/' '\001' | \
E 3
I 3
D 14
find ${SRCHPATHS} -print | tr '/' '\001' | \
E 3
   (sort -f; echo $status > $errs) | \
D 6
   tr '\001' '/' | tee $filelist | $LIBDIR/bigram | \
E 6
I 6
   tr '\001' '/' >$filelist
D 11
$LIBDIR/bigram <$filelist | \
E 11
I 11
D 13
$LIBDIR/find.bigram <$filelist | \
E 13
I 13
$LIBDIR/locate.bigram <$filelist | \
E 13
E 11
E 6
   (sort; echo $status >> $errs) | uniq -c | sort -nr | \
   awk '{ if (NR <= 128) print $2 }' | tr -d '\012' > $bigrams
E 14
I 14
D 15
# only search locally
# find ${SRCHPATHS} ! -fstype local -a -prune -o -print | \
find ${SRCHPATHS} -print | \
E 15
I 15
# search locally or everything
# find ${SRCHPATHS} -print | \
D 17
find ${SRCHPATHS} ! -fstype local -a -prune -o -print | \
E 17
I 17
D 18
find ${SRCHPATHS} -fstype local -print | \
E 18
I 18
find ${SRCHPATHS} \! -fstype local -prune -or -print | \
E 18
E 17
E 15
	tr '/' '\001' | \
D 15
	(sort -f; echo $status > $errs) | tr '\001' '/' > $filelist
E 15
I 15
D 20
	(sort -T /var/tmp -f; echo $status > $errs) | tr '\001' '/' > $filelist
E 20
I 20
	(sort -T $TMPDIR -f; echo $status > $errs) | tr '\001' '/' > $filelist
E 20
E 15

$LIBDIR/locate.bigram < $filelist | \
D 15
	(sort; echo $status >> $errs) | uniq -c | sort -nr | \
E 15
I 15
D 20
	(sort -T /var/tmp; echo $status >> $errs) | \
	uniq -c | sort -T /var/tmp -nr | \
E 20
I 20
	(sort -T /$TMPDIR; echo $status >> $errs) | \
	uniq -c | sort -T /$TMPDIR -nr | \
E 20
E 15
	awk '{ if (NR <= 128) print $2 }' | tr -d '\012' > $bigrams
E 14

# code the file list

if { grep -s -v 0 $errs } then
D 12
	echo 'squeeze error: out of sort space' | mail $FINDHONCHO
E 12
I 12
D 13
	printf 'find: updatedb failed\n\n'
E 13
I 13
	printf 'locate: updatedb failed\n\n'
E 13
E 12
else
D 11
	$LIBDIR/code $bigrams < $filelist > $FCODES
E 11
I 11
D 13
	$LIBDIR/find.code $bigrams < $filelist > $FCODES
E 13
I 13
	$LIBDIR/locate.code $bigrams < $filelist > $FCODES
E 13
E 11
I 5
	chmod 644 $FCODES
E 5
	rm $bigrams $filelist $errs
endif
I 17
D 20




























E 20
E 17
E 1
