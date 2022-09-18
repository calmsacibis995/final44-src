h06679
s 00002/00002/00017
d D 8.1 93/05/31 18:02:22 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00012/00017
d D 5.4 90/06/01 13:22:46 bostic 4 3
c new copyright notice
e
s 00005/00070/00024
d D 5.3 90/05/03 11:39:59 bostic 3 2
c generalize for all games (fish wasn't a wargame anyway...)
e
s 00014/00003/00080
d D 5.2 89/02/17 17:26:47 bostic 2 1
c add Berkeley specific copyright
e
s 00083/00000/00000
d D 5.1 85/06/23 15:40:00 mckusick 1 0
c date and time created 85/06/23 15:40:00 by mckusick
e
u
U
t
T
I 1
#!/bin/sh -
#
D 2
# Copyright (c) 1980 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 2
I 2
D 4
# Copyright (c) 1980 The Regents of the University of California.
E 4
I 4
D 5
# Copyright (c) 1985 The Regents of the University of California.
E 4
# All rights reserved.
E 5
I 5
# Copyright (c) 1985, 1993
#	The Regents of the University of California.  All rights reserved.
E 5
#
D 4
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
E 4
I 4
# %sccs.include.redist.sh%
E 4
E 2
#
#	%W% (Berkeley) %G%
#
echo -n "Would you like to play a game? "
read x

D 3
case $x in

adventure)
E 3
I 3
if [ -f /usr/games/$x ] ; then
	tput cl
E 3
	exec /usr/games/$x
D 3
	;;

backgammon)
	exec /usr/games/$x
	;;

boggle)
	exec /usr/games/$x
	;;

canfield)
	exec /usr/games/$x
	;;

chess)
	exec /usr/games/$x
	;;

cribbage)
	exec /usr/games/$x
	;;

fish)
	exec /usr/games/$x
	;;

fortune)
	exec /usr/games/$x
	;;

hangman)
	exec /usr/games/$x
	;;

mille)
	exec /usr/games/$x
	;;

monop)
	exec /usr/games/$x
	;;

rogue)
	exec /usr/games/$x
	;;

snake)
	exec /usr/games/$x
	;;


trek)
	exec /usr/games/$x
	;;

wump)
	exec /usr/games/$x
	;;

zork)
	exec /usr/games/$x
	;;

*)
	echo "Funny, the only way to win is not to play at all"
	;;
esac
E 3
I 3
else
	echo "Funny, the only way to win is not to play at all."
fi
E 3
exit 0
E 1
