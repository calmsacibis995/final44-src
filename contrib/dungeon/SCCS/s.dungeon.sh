h26925
s 00007/00000/00000
d D 5.1 88/10/20 18:35:33 bostic 1 0
c from UUNET; applied patches 1-3
e
u
U
t
T
I 1
: sh script to invoke the dungeon game on the pdp
DLIB=/usr/games/lib/dunlib
case $# in
	0) $DLIB/listen| $DLIB/dungpdp| $DLIB/speak;;
	1) $DLIB/listen dungeon.sav| $DLIB/dungpdp| $DLIB/speak;;
	*) $DLIB/listen $2| $DLIB/dungpdp| $DLIB/speak;;
esac
E 1
