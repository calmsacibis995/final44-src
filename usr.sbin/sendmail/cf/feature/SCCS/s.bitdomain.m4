h17056
s 00001/00001/00022
d D 8.6 94/02/19 07:56:19 eric 9 8
c patches to handle trailing dot properly
e
s 00001/00001/00022
d D 8.5 94/02/16 08:44:42 eric 8 7
c move bitdomain and uudomain maps up in ruleset 3
e
s 00001/00001/00022
d D 8.4 93/11/30 09:01:06 eric 7 6
c add dot on pseudo-domains for consistency
e
s 00001/00001/00022
d D 8.3 93/08/07 12:04:12 eric 6 5
c don't include .db on the end of map names -- this is added automatically
e
s 00001/00001/00022
d D 8.2 93/07/28 10:17:51 eric 5 4
c fix botch with -o flag on default maps; also, add .db on them
e
s 00002/00002/00021
d D 8.1 93/06/07 10:10:24 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00022
d D 6.3 93/05/21 19:49:41 eric 3 2
c don't include .db on database file names
e
s 00002/00002/00021
d D 6.2 93/04/10 11:06:19 eric 2 1
c change map name for consistency with UUCP
e
s 00023/00000/00000
d D 6.1 93/04/10 10:50:17 eric 1 0
c date and time created 93/04/10 10:50:17 by eric
e
u
U
t
T
I 1
divert(-1)
#
# Copyright (c) 1983 Eric P. Allman
D 4
# Copyright (c) 1988 The Regents of the University of California.
# All rights reserved.
E 4
I 4
# Copyright (c) 1988, 1993
#	The Regents of the University of California.  All rights reserved.
E 4
#
# %sccs.include.redist.sh%
#

divert(0)
VERSIONID(`%W% (Berkeley) %G%')
divert(-1)


PUSHDIVERT(6)
D 2
Kbitnet ifelse(_ARG_, `', `hash /etc/bitdomain.db -o', `_ARG_')
E 2
I 2
D 3
Kbitdomain ifelse(_ARG_, `', `hash /etc/bitdomain.db -o', `_ARG_')
E 3
I 3
D 5
Kbitdomain ifelse(_ARG_, `', `hash /etc/bitdomain -o', `_ARG_')
E 5
I 5
D 6
Kbitdomain ifelse(_ARG_, `', `hash -o /etc/bitdomain.db', `_ARG_')
E 6
I 6
Kbitdomain ifelse(_ARG_, `', `hash -o /etc/bitdomain', `_ARG_')
E 6
E 5
E 3
E 2
POPDIVERT


D 8
PUSHDIVERT(8)
E 8
I 8
PUSHDIVERT(2)
E 8
# handle BITNET mapping
D 2
R$* < @ $+ .BITNET > $*		$: $1 < @ $(bitnet $2 $: $2.BITNET $) > $3
E 2
I 2
D 7
R$* < @ $+ .BITNET > $*		$: $1 < @ $(bitdomain $2 $: $2.BITNET $) > $3
E 7
I 7
D 9
R$* < @ $+ .BITNET. > $*	$: $1 < @ $(bitdomain $2 $: $2.BITNET. $) > $3
E 9
I 9
R$* < @ $+ .BITNET > $*		$: $1 < @ $(bitdomain $2 $: $2.BITNET $) > $3
E 9
E 7
E 2
POPDIVERT
E 1
