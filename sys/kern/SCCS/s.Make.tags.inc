h23679
s 00001/00000/00018
d D 8.2 94/11/23 11:26:42 mckusick 7 6
c add isofs filesystems
e
s 00000/00000/00018
d D 8.1 93/06/11 17:39:05 bostic 6 5
c 4.4BSD snapshot (revision 8.1)
e
s 00009/00005/00009
d D 7.4 93/06/11 17:38:27 bostic 5 3
c make tags, links work for 4.4BSD
e
s 00000/00000/00014
d R 8.1 93/06/10 21:54:58 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00007/00008/00007
d D 7.3 92/07/24 15:53:02 bostic 3 2
c fix? tags
e
s 00007/00002/00008
d D 7.2 92/03/18 18:20:12 karels 2 1
c new way of doing tags
e
s 00010/00000/00000
d D 7.1 91/12/05 12:09:30 karels 1 0
c include file for per-architecture Makefiles
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

D 3
# common files for "make tags"
# included by makefile for each architecture
E 3
I 3
# Common files for "make tags".
# Included by the Makefile for each architecture.
E 3

D 2
COMM=	../kern/*.c ../vm/*.[ch] ../sys/*.h \
E 2
I 2
# Put the ../sys stuff near the end so that subroutine definitions win when
# there is a struct tag with the same name (eg., vmmeter).  The real
# solution would probably be for ctags to generate "struct vmmeter" tags.

D 3
COMM=	../kern/*.c ../vm/*.c ../vm/*.h \
E 2
	../net/*.[ch] ../netimp/*.[ch] ../netinet/*.[ch] ../netns/*.[ch] \
	../netiso/*.[ch] ../netccitt/*.[ch] \
	../ufs/ufs/*.[ch] ../ufs/ffs/*.[ch] ../ufs/lfs/*.[ch] \
D 2
	../ufs/mfs/*.[ch] ../nfs/*.[ch]
E 2
I 2
	../ufs/mfs/*.[ch] ../nfs/*.[ch] \
	../sys/*.h
E 3
I 3
D 5
COMM=	/sys/conf/*.[ch] /sys/dev/*.[ch] /sys/dev/scsi/*.[ch] \
	/sys/kern/*.[ch] /sys/libkern/*.[ch] /sys/miscfs/*/*.[ch] \
	/sys/net/*.[ch] /sys/netccitt/*.[ch] /sys/netimp/*.[ch] \
	/sys/netinet/*.[ch] /sys/netiso/*.[ch] /sys/netns/*.[ch] \
	/sys/nfs/*.[ch] /sys/sys/*.[ch] /sys/ufs/*/*.[ch] /sys/vm/*.[ch]
E 5
I 5
COMM=	/sys/conf/*.[ch] \
	/sys/dev/*.[ch] /sys/dev/scsi/*.[ch] \
I 7
	/sys/isofs/*/*.[ch] \
E 7
	/sys/kern/*.[ch] /sys/libkern/*.[ch] \
	/sys/miscfs/*/*.[ch] \
	/sys/net/*.[ch] /sys/netccitt/*.[ch] /sys/netinet/*.[ch] \
	/sys/netiso/*.[ch] /sys/netns/*.[ch] \
	/sys/nfs/*.[ch] /sys/sys/*.[ch] \
	/sys/ufs/*/*.[ch] \
	/sys/vm/*.[ch]
E 5
E 3
E 2
E 1
