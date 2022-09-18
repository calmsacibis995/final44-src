h50278
s 00000/00000/00013
d D 8.1 93/06/04 15:33:28 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00000/00011
d D 5.3 93/06/04 15:33:20 bostic 3 2
c add sccs keyword line
e
s 00010/00001/00001
d D 5.2 93/05/24 10:02:43 bostic 2 1
c update for Margo
e
s 00002/00000/00000
d D 5.1 92/07/19 14:30:33 bostic 1 0
c date and time created 92/07/19 14:30:33 by bostic
e
u
U
t
T
I 1
#!/bin/sh
I 3
#
#	%W% (Berkeley) %G%
E 3
D 2
awk '{i++; print $0; print i;}' /usr/share/dict/words > words
E 2
I 2

awk '{i++; print $0; print i;}' /usr/share/dict/words > WORDS
ls /bin /usr/bin /usr/ucb /etc | egrep '^(...|....|.....|......)$' | \
sort | uniq | \
awk '{
	printf "%s\n", $0
	for (i = 0; i < 1000; i++)
		printf "%s+", $0
	printf "\n"
}' > LONG.DATA
E 2
E 1
