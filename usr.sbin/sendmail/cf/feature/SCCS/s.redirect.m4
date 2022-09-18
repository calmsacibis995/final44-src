h28069
s 00001/00001/00021
d D 8.3 95/04/22 11:59:33 eric 5 4
c use DSN-style error codes instead of sysexit codes for $#error mailer
e
s 00001/00001/00021
d D 8.2 93/12/27 14:48:46 eric 4 3
c pseudo-domains are now dot-terminated
e
s 00002/00002/00020
d D 8.1 93/06/07 10:10:45 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00000/00018
d D 6.2 93/05/21 19:49:28 eric 2 1
c add REDIRECT to list of top-level pseudo-domains
e
s 00018/00000/00000
d D 6.1 93/02/20 15:22:24 eric 1 0
c date and time created 93/02/20 15:22:24 by eric
e
u
U
t
T
I 1
divert(-1)
#
# Copyright (c) 1983 Eric P. Allman
D 3
# Copyright (c) 1988 The Regents of the University of California.
# All rights reserved.
E 3
I 3
# Copyright (c) 1988, 1993
#	The Regents of the University of California.  All rights reserved.
E 3
#
# %sccs.include.redist.sh%
#

divert(0)
VERSIONID(`%W% (Berkeley) %G%')
divert(-1)


PUSHDIVERT(3)
# addresses sent to foo@host.REDIRECT will give a 551 error code
D 4
R$* < @ $+ .REDIRECT >	$# error $@ NOUSER $: "551 User not local; please try " <$1@$2>
E 4
I 4
D 5
R$* < @ $+ .REDIRECT. >	$# error $@ NOUSER $: "551 User not local; please try " <$1@$2>
E 5
I 5
R$* < @ $+ .REDIRECT. >	$# error $@ 5.1.1 $: "551 User not local; please try " <$1@$2>
E 5
E 4
POPDIVERT
I 2

PUSHDIVERT(6)
CPREDIRECT
POPDIVERT
E 2
E 1
