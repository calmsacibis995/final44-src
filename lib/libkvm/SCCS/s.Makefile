h25346
s 00002/00003/00012
d D 8.3 95/05/04 17:10:39 mckusick 8 6
c kvm_getvfsbyname moves to libc
e
s 00002/00002/00013
d R 8.3 95/05/04 17:08:32 mckusick 7 6
c kvm_getvfsbyname => getvfsbyname
e
s 00003/00002/00012
d D 8.2 95/04/03 17:46:43 mckusick 6 5
c add kvm_getvfsbyname
e
s 00000/00000/00014
d D 8.1 93/06/04 16:53:08 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00006/00005/00008
d D 5.4 93/04/27 15:23:20 bostic 4 3
c add kvm_getloadavg(3)
e
s 00003/00002/00010
d D 5.3 92/05/26 15:45:09 bostic 3 2
c add kvm_read (link to kvm_write)
e
s 00002/00002/00010
d D 5.2 92/05/18 18:48:02 sklower 2 1
c add kvm_proc.c, kvm_getfiles.3 (checking by torek for sklower)
e
s 00012/00000/00000
d D 5.1 92/04/08 08:25:36 bostic 1 0
c date and time created 92/04/08 08:25:36 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

LIB=	kvm
CFLAGS+=-DLIBC_SCCS -I/sys
D 2
SRCS=	kvm.c kvm_${MACHINE}.c kvm_proc.c
MAN3=	kvm.0 kvm_geterr.0 kvm_getprocs.0 kvm_nlist.0 kvm_open.0
E 2
I 2
D 4
SRCS=	kvm.c kvm_${MACHINE}.c kvm_proc.c kvm_file.c
D 3
MAN3=	kvm.0 kvm_geterr.0 kvm_getprocs.0 kvm_nlist.0 kvm_open.0 kvm_getfiles.0
E 3
I 3
MAN3=	kvm.0 kvm_geterr.0 kvm_getprocs.0 kvm_nlist.0 kvm_open.0 \
	kvm_getfiles.0 kvm_read.0
E 4
I 4
D 6
SRCS=	kvm.c kvm_${MACHINE}.c kvm_file.c kvm_getloadavg.c kvm_proc.c
E 6
I 6
D 8
SRCS=	kvm.c kvm_${MACHINE}.c kvm_file.c kvm_getloadavg.c \
	kvm_getvfsbyname.c kvm_proc.c
E 8
I 8
SRCS=	kvm.c kvm_${MACHINE}.c kvm_file.c kvm_getloadavg.c kvm_proc.c
E 8
E 6
E 4
E 3
E 2

D 3
MLINKS+=kvm.3 kvm_read.3 kvm.3 kvm_write.3
E 3
I 3
D 4
MLINKS+=kvm_read.3 kvm_write.3
E 3
MLINKS+=kvm_open.3 kvm_openfiles.3 kvm_open.3 kvm_close.3
E 4
I 4
MAN3=	kvm.0 kvm_geterr.0 kvm_getfiles.0 kvm_getloadavg.0 kvm_getprocs.0 \
D 6
	kvm_nlist.0 kvm_open.0 kvm_read.0
E 6
I 6
D 8
	kvm_getvfsbyname.0 kvm_nlist.0 kvm_open.0 kvm_read.0
E 8
I 8
	kvm_nlist.0 kvm_open.0 kvm_read.0
E 8
E 6

E 4
MLINKS+=kvm_getprocs.3 kvm_getargv.3 kvm_getprocs.3 kvm_getenvv.3
I 4
MLINKS+=kvm_open.3 kvm_openfiles.3 kvm_open.3 kvm_close.3
MLINKS+=kvm_read.3 kvm_write.3
E 4

.include <bsd.lib.mk>
E 1
