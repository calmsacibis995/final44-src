h63679
s 00001/00001/00022
d D 8.6 94/02/19 07:56:19 eric 8 7
c patches to handle trailing dot properly
e
s 00001/00001/00022
d D 8.5 94/02/16 08:44:42 eric 7 6
c move bitdomain and uudomain maps up in ruleset 3
e
s 00001/00001/00022
d D 8.4 93/11/30 09:01:07 eric 6 5
c add dot on pseudo-domains for consistency
e
s 00001/00001/00022
d D 8.3 93/08/07 12:04:14 eric 5 4
c don't include .db on the end of map names -- this is added automatically
e
s 00001/00001/00022
d D 8.2 93/07/28 10:17:52 eric 4 3
c fix botch with -o flag on default maps; also, add .db on them
e
s 00002/00002/00021
d D 8.1 93/06/07 10:10:53 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00022
d D 6.2 93/05/21 19:49:42 eric 2 1
c don't include .db on database file names
e
s 00023/00000/00000
d D 6.1 93/04/10 11:05:41 eric 1 0
c date and time created 93/04/10 11:05:41 by eric
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


PUSHDIVERT(6)
D 2
Kuudomain ifelse(_ARG_, `', `hash /etc/uudomain.db -o', `_ARG_')
E 2
I 2
D 4
Kuudomain ifelse(_ARG_, `', `hash /etc/uudomain -o', `_ARG_')
E 4
I 4
D 5
Kuudomain ifelse(_ARG_, `', `hash -o /etc/uudomain.db', `_ARG_')
E 5
I 5
Kuudomain ifelse(_ARG_, `', `hash -o /etc/uudomain', `_ARG_')
E 5
E 4
E 2
POPDIVERT


D 7
PUSHDIVERT(8)
E 7
I 7
PUSHDIVERT(2)
E 7
# handle UUCP mapping
D 6
R$* < @ $+ .UUCP > $*		$: $1 < @ $(uudomain $2 $: $2.UUCP $) > $3
E 6
I 6
D 8
R$* < @ $+ .UUCP. > $*		$: $1 < @ $(uudomain $2 $: $2.UUCP. $) > $3
E 8
I 8
R$* < @ $+ .UUCP > $*		$: $1 < @ $(uudomain $2 $: $2.UUCP $) > $3
E 8
E 6
POPDIVERT
E 1
