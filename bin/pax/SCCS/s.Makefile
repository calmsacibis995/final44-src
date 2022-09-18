h13379
s 00000/00000/00032
d D 8.1 93/05/31 14:59:59 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00021/00030/00011
d D 1.3 93/05/31 14:59:54 bostic 4 2
c Makefiles don't get copyright notices
e
s 00000/00000/00041
d R 8.1 93/05/31 14:58:14 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00030/00005/00011
d D 1.2 93/01/14 15:36:21 muller 2 1
c improved comments to be more useful.
e
s 00016/00000/00000
d D 1.1 92/12/17 18:43:20 muller 1 0
c date and time created 92/12/17 18:43:20 by muller
e
u
U
t
T
I 2
D 4
#	Copyright (c) 1992 Keith Muller.
#	Copyright (c) 1992 The Regents of the University of California.
#	All rights reserved.
#
#	This code is derived from software contributed to Berkeley by
#	Keith Muller of the University of California, San Diego.
#
E 4
E 2
I 1
#       %W% (Berkeley) %G%
I 4

# To install on versions prior to BSD 4.4 the following may have to be
# defined with CFLAGS +=
E 4
#
D 4
#	Makefile for Pax
E 4
I 4
# -DNET2_STAT	Use NET2 or older stat structure. The version of the
# 		stat structure is easily determined by looking at the
# 		basic type of an off_t (often defined in the file:
# 		/usr/include/sys/types.h). If off_t is a long (and is
# 		NOT A quad) then you must define NET2_STAT.
# 		This define is important, as if you do have a quad_t
# 		off_t and define NET2_STAT, pax will compile but will
# 		NOT RUN PROPERLY.
E 4
#
D 2
#	To install on versions prior to BSD4.4 the following may be defined
#	with CFLAGS:	
#	-DNET2_STAT	Use net2 or older stat structure
#	-DNET2_FTS	use older NET2 fts 
#	-DNET2_REGEX	use older regexp.h not regex.h
E 2
I 2
D 4
#	To install on versions prior to BSD 4.4 the following may have to be
#	defined with CFLAGS +=
E 4
I 4
# -DNET2_FTS	Use the older NET2 fts. To identify the version,
# 		examine the file: /usr/include/fts.h. If FTS_COMFOLLOW
# 		is not defined then you must define NET2_FTS.
# 		Pax may not compile if this not (un)defined properly.
E 4
#
D 4
#	-DNET2_STAT	Use NET2 or older stat structure. The version of the
#			stat structure is easily determined by looking at the
#			basic type of an off_t (often defined in the file:
#			/usr/include/sys/types.h). If off_t is a long (and is
#			NOT A quad) then you must define NET2_STAT.
#			This define is important, as if you do have a quad_t
#			off_t and define NET2_STAT, pax will compile but will
#			NOT RUN PROPERLY.
#
#	-DNET2_FTS	Use the older NET2 fts. To identify the version,
#			examine the file: /usr/include/fts.h. If FTS_COMFOLLOW
#			is not defined then you must define NET2_FTS.
#			Pax may not compile if this not (un)defined properly.
#
#	-DNET2_REGEX	Use the older regexp.h not regex.h. The regex version
#			is determined by looking at the value returned by
#			regexec() (man 3 regexec). If regexec return a 1 for
#			success (and NOT a 0 for success) you have the older
#			regex routines and must define NET2_REGEX.
#			Pax may not compile if this not (un)defined properly.
E 4
I 4
# -DNET2_REGEX	Use the older regexp.h not regex.h. The regex version
# 		is determined by looking at the value returned by
# 		regexec() (man 3 regexec). If regexec return a 1 for
# 		success (and NOT a 0 for success) you have the older
# 		regex routines and must define NET2_REGEX.
# 		Pax may not compile if this not (un)defined properly.
E 4
E 2

PROG=   pax
SRCS=	ar_io.c ar_subs.c buf_subs.c cache.c cpio.c file_subs.c ftree.c\
	gen_subs.c options.c pat_rep.c pax.c sel_subs.c tables.c tar.c\
	tty_subs.c

.include <bsd.prog.mk>
E 1
