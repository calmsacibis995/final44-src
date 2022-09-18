h30159
s 00005/00002/00029
d D 1.5 87/08/08 17:11:15 pc 5 4
c Working version for 4.3
e
s 00001/00001/00030
d D 1.4 84/08/06 12:35:18 pc 4 3
c The original version did not delete line 1, this version starts
c searching from $, then looks for the line to delete.
e
s 00004/00002/00027
d D 1.3 84/08/01 15:35:08 pc 3 2
c Fix it so that it works!
e
s 00002/00001/00027
d D 1.2 84/08/01 10:33:54 pc 2 1
c Make into a runnable entity on /etc
e
s 00028/00000/00000
d D 1.1 84/07/31 12:40:08 pc 1 0
c date and time created 84/07/31 12:40:08 by pc
e
u
U
t
T
I 1
#!/bin/sh
#	%M%	%I%	%G%
D 5
#	shell script to clean dumplog file
E 5
I 5
#	shell script to clean dumpvolumes file
#	This ensures that only the last entry for a
#	particular tape is retained on the log
#	Caveat Tape labels MUST not contain a colon
E 5
#
I 2
PATH=:/etc/:/bin:/usr/bin:
E 2
#	Name of	logfile
D 2
DL=dumplog
E 2
I 2
D 5
DL=/etc/dumplog
E 5
I 5
DL=/etc/dumpvolumes
E 5
E 2
#	Name of tmp files
DT=/tmp/dumpclean$$
DE=/tmp/dumpedit$$
I 3
export DT
export DE
E 3
trap "rm -f $DT $DE" 1 2 3 15
sed -e 's/:.*$//' $DL |
	sort |
	uniq -c |
	awk	'{	if ($1 != 1)
			{	
				for (i = 0; i < $1-1; i++)
D 4
					printf "1\n/%s/d\n", $2
E 4
I 4
					printf "$\n/%s/d\n", $2
E 4
			}
		}' > $DE
if [ -s $DE ]
then
	cp $DL $DT
	echo "w" >> $DE
	echo "q" >> $DE
	ed $DT < $DE > /dev/null
I 3
	mv $DT $DL
E 3
fi
D 3
mv $DT $DL
rm $DE
E 3
I 3
rm -f $DE
E 3
E 1
