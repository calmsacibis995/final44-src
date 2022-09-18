h63899
s 00003/00003/00035
d D 8.4 94/04/03 11:59:16 pendry 10 9
c fix _ parsing
e
s 00004/00004/00034
d D 8.3 94/03/19 10:20:19 bostic 9 8
c makewhatis.sed should handle '.', '+', and '-' in names
c (config.new, g++, send-pr)
c From: "Chris G. Demetriou" <cgd@sun-lamp.cs.berkeley.edu>
e
s 00002/00002/00036
d D 8.2 93/11/16 11:33:38 bostic 8 7
c Craig Leres' patches to 4.4BSD
e
s 00002/00002/00036
d D 8.1 93/06/05 13:15:44 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00037
d D 5.6 91/09/26 15:08:28 bostic 6 5
c delete anything followed by a backspace
e
s 00003/00012/00034
d D 5.5 91/04/17 13:19:48 bostic 5 4
c new copyright; att/bsd/shared
e
s 00003/00002/00043
d D 5.4 88/09/19 10:48:57 bostic 4 3
c emboldening fix in nroff broke the old version
e
s 00010/00005/00035
d D 5.3 88/07/09 11:24:34 bostic 3 2
c install approved copyright notice
e
s 00002/00000/00038
d D 5.2 88/03/27 14:28:07 bostic 2 1
c handle underlining in command name in manual pages
e
s 00038/00000/00000
d D 5.1 88/03/27 14:21:17 bostic 1 0
c date and time created 88/03/27 14:21:17 by bostic
e
u
U
t
T
I 1
D 10
#!/bin/sh -
E 10
I 10
#!/usr/bin/sed -nf
E 10
#
D 5
# Copyright (c) 1988 Regents of the University of California.
E 5
I 5
D 7
# Copyright (c) 1988 The Regents of the University of California.
E 5
# All rights reserved.
E 7
I 7
D 10
# Copyright (c) 1988, 1993
E 10
I 10
# Copyright (c) 1988, 1993, 1994
E 10
#	The Regents of the University of California.  All rights reserved.
E 7
#
D 5
# Redistribution and use in source and binary forms are permitted
D 3
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific prior written permission. This software
# is provided ``as is'' without express or implied warranty.
E 3
I 3
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
E 5
I 5
# %sccs.include.redist.sh%
E 5
E 3
#
#	%W% (Berkeley) %G%
#
I 5

E 5
D 8
/(\([a-zA-Z0-9]*\).*UNIX Programmer's Manual/ {
	s;.*(\([a-zA-Z0-9]*\).*UNIX.*;\1;
E 8
I 8
D 9
/^[a-zA-Z][a-zA-Z0-9]*(\([a-zA-Z0-9]*\).*/ {
	s;^[a-zA-Z0-9]*(\([a-zA-Z0-9]*\).*;\1;
E 9
I 9
/^[a-zA-Z][a-zA-Z0-9\._+\-]*(\([a-zA-Z0-9\._+\-]*\).*/ {
D 10
	s;^[a-zA-Z0-9]*(\([a-zA-Z0-9\._+\-]*\).*;\1;
E 10
I 10
	s;^[a-zA-Z0-9\._+\-]*(\([a-zA-Z0-9\._+\-]*\).*;\1;
E 10
E 9
E 8
	h
	d
}
D 4
/^NAME/!d
E 4

I 4
/^NNAAMMEE/!d

E 4
:name
	s;.*;;
	N
	s;\n;;
I 2
	# some twits underline the command name
	s;_;;g
E 2
	/^[^	 ]/b print
	H
	b name

:print
	x
	s;\n;;g
	/-/!d
I 6
	s;.;;g
E 6
	s;\([a-z][A-z]\)-[	 ][	 ]*;\1;
D 9
	s;\([a-zA-Z0-9,]\)[	 ][	 ]*;\1 ;g
	s;[^a-zA-Z0-9]*\([a-zA-Z0-9]*\)[^a-zA-Z0-9]*\(.*\) - \(.*\);\2 (\1) - \3;
E 9
I 9
	s;\([a-zA-Z0-9,\._+\-]\)[	 ][	 ]*;\1 ;g
	s;[^a-zA-Z0-9\._+\-]*\([a-zA-Z0-9\._+\-]*\)[^a-zA-Z0-9\._+\-]*\(.*\) - \(.*\);\2 (\1) - \3;
E 9
	p
D 4
	d
E 4
I 4
	q
E 4
E 1
