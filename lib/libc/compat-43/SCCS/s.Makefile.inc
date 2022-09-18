h20410
s 00000/00000/00013
d D 8.1 93/06/02 17:26:11 bostic 14 13
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00011
d D 5.11 93/06/02 17:25:11 bostic 13 11
c man pages are section 2, not section 3
e
s 00000/00000/00013
d R 8.1 93/06/02 00:03:27 bostic 12 11
c 4.4BSD snapshot (revision 8.1)
e
s 00005/00004/00008
d D 5.10 93/04/04 13:38:48 mckusick 11 9
c {get,set}hostid moves in from sys
e
s 00005/00004/00008
d R 5.10 93/04/04 13:30:57 mckusick 10 9
c {get,set}hostid moves in from sys
e
s 00006/00004/00006
d D 5.9 93/02/26 19:01:47 mckusick 9 8
c add setruid.3 manual page
e
s 00003/00002/00007
d D 5.8 93/02/26 18:36:56 staelin 8 7
c add setregid
e
s 00002/00001/00007
d D 5.7 93/02/03 15:41:54 mckusick 7 6
c seruid and setrgid move to compat-43; setuid.3 moves to setuid.2
e
s 00002/00002/00006
d D 5.6 92/07/09 14:41:02 mckusick 6 5
c add setreuid
e
s 00001/00001/00007
d D 5.5 92/03/30 10:40:48 bostic 5 4
c don't put regex.c in for now
e
s 00001/00001/00007
d D 5.4 92/03/29 11:48:05 bostic 4 3
c add regex compatibility routines
e
s 00001/00001/00007
d D 5.3 91/02/20 08:15:59 bostic 3 2
c add getwd(3)
e
s 00001/00001/00007
d D 5.2 91/02/19 14:58:06 bostic 2 1
c rename setpgrp to setpgid, add setpgrp compat call, update man page
e
s 00008/00000/00000
d D 5.1 90/06/23 16:23:14 bostic 1 0
c date and time created 90/06/23 16:23:14 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

# compat-43 sources
.PATH: ${.CURDIR}/${MACHINE}/compat-43 ${.CURDIR}/compat-43

D 2
SRCS+=	creat.c killpg.c sigcompat.c
E 2
I 2
D 3
SRCS+=	creat.c killpg.c setpgrp.c sigcompat.c
E 3
I 3
D 4
SRCS+=	creat.c getwd.c killpg.c setpgrp.c sigcompat.c
E 4
I 4
D 5
SRCS+=	creat.c getwd.c killpg.c regex.c setpgrp.c sigcompat.c
E 5
I 5
D 6
SRCS+=	creat.c getwd.c killpg.c setpgrp.c sigcompat.c
E 6
I 6
D 7
SRCS+=	creat.c getwd.c killpg.c setpgrp.c setreuid.c sigcompat.c
E 7
I 7
D 9
SRCS+=	creat.c getwd.c killpg.c setpgrp.c setreuid.c sigcompat.c \
D 8
	setruid.c setrgid.c
E 8
I 8
	setruid.c setrgid.c setregid.c
E 9
I 9
D 11
SRCS+=	creat.c getwd.c killpg.c setpgrp.c setregid.c setreuid.c \
	setrgid.c setruid.c sigcompat.c
E 11
I 11
SRCS+=	creat.c gethostid.c getwd.c killpg.c sethostid.c setpgrp.c \
	setregid.c setreuid.c setrgid.c setruid.c sigcompat.c
E 11
E 9
E 8
E 7
E 6
E 5
E 4
E 3
E 2

D 6
MAN2+=	creat.0 killpg.0 sigblock.0 sigpause.0 sigsetmask.0 sigvec.0
E 6
I 6
D 8
MAN2+=	creat.0 killpg.0 setreuid.0 sigblock.0 sigpause.0 sigsetmask.0 sigvec.0
E 8
I 8
D 9
MAN2+=	creat.0 killpg.0 setreuid.0 sigblock.0 sigpause.0 sigsetmask.0 \
	sigvec.0 setregid.0
E 9
I 9
D 11
MAN2+=	creat.0 killpg.0 setregid.0 setreuid.0 setruid.0 sigblock.0 \
	sigpause.0 sigsetmask.0 sigvec.0
E 11
I 11
MAN2+=	creat.0 gethostid.0 killpg.0 setregid.0 setreuid.0 setruid.0 \
	sigblock.0 sigpause.0 sigsetmask.0 sigvec.0
E 11

D 13
MLINKS+=setruid.3 setrgid.3
I 11
MLINKS+=gethostid.3 sethostid.3
E 13
I 13
MLINKS+=setruid.2 setrgid.2
MLINKS+=gethostid.2 sethostid.2
E 13
E 11
E 9
E 8
E 6
E 1
