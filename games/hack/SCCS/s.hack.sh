h19477
s 00014/00000/00000
d D 5.1 90/05/02 08:40:30 bostic 1 0
c date and time created 90/05/02 08:40:30 by bostic
e
u
U
t
T
I 1
#!/bin/sh
HACKDIR=/usr/games/lib/hackdir
HACK=$HACKDIR/hack
MAXNROFPLAYERS=4

cd $HACKDIR
case $1 in
	-s*)
		exec $HACK $@
		;;
	*)
		exec $HACK $@ $MAXNROFPLAYERS
		;;
esac
E 1
