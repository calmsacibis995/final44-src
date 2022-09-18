h31342
s 00001/00001/00011
d D 1.3 87/09/10 09:54:03 epg 3 2
c changed reference to awk to "nawk"
e
s 00002/00000/00010
d D 1.2 87/03/31 16:50:18 jaap 2 1
c now a real shell program
e
s 00010/00000/00000
d D 1.1 87/03/31 16:32:28 jaap 1 0
c date and time created 87/03/31 16:32:28 by jaap
e
u
U
t
T
I 2
#!/bin/sh
E 2
I 1
# %I%	(CWI)	%E%
I 2

E 2
for i in $*
do
	if test ! -r $i
	then
		echo "chem: can't open file $i" 1>&2
		exit 1
	fi
done
D 3
awk -f chem.awk $*
E 3
I 3
nawk -f chem.awk $*
E 3
E 1
