h05910
s 00003/00003/00037
d D 1.7 87/08/11 22:27:40 pc 7 6
c Fix for 4.3
e
s 00007/00003/00033
d D 1.6 85/04/29 15:06:34 pc 6 5
c Add more informative information
e
s 00025/00010/00011
d D 1.5 85/04/29 13:45:38 pc 5 4
c Give better control in selecting which dump is to be done.
e
s 00001/00001/00020
d D 1.4 84/08/01 15:23:54 pc 4 3
c Make question a bit prettier
e
s 00001/00000/00020
d D 1.3 84/08/01 14:00:27 pc 3 2
c Add a dumplogclean call
e
s 00001/00000/00019
d D 1.2 84/08/01 10:54:41 pc 2 1
c Make into real running commands
e
s 00019/00000/00000
d D 1.1 84/07/31 23:51:00 pc 1 0
c date and time created 84/07/31 23:51:00 by pc
e
u
U
t
T
I 1
#!/bin/sh
#	%M%	%I%	%G%
#	shell script to do all pending dumps
#	Asks for confirmation before proceeding
I 2
PATH=:/etc:/bin:/usr/bin:
E 2
list=`dump w|sed -e '/^ /!d
	/^ /s/^  //
	s/	.*$//'`
I 5
echo 'File systems which require dumping are:-'
echo $list
E 5
for fi in $list
do
D 5
	echo "File system to dump is $fi"
D 4
	echo -n "Do you wish to continue"
E 4
I 4
	echo -n "Do you wish to continue? "
E 4
	read ans
	if [ "$ans" = "yes" -o "$ans" = "y" -o "$ans" = "Y" ]
	then
		doadump $fi
I 3
		/etc/dumplogclean
E 3
	else
		exit 1
	fi
E 5
I 5
	askagain=yes
	while  [ $askagain = yes ]
	do
D 6
		echo -n "Dump file system $fi [yne]? "
E 6
I 6
		echo -n "Dump file system $fi [ynle]? "
E 6
		read ans
		case $ans in
		yes|y|Y)
D 7
			doadump $fi
			/etc/dumplogclean
E 7
I 7
			dumpdev $fi
			/etc/cleanvolumes
E 7
			askagain=no
			;;
I 6
		list|l|L)
D 7
			doadump $fi T
E 7
I 7
			dumpdev $fi T
E 7
			;;
E 6
		exit|e|E)
			exit 1
			;;
		no|n|N)
D 6
			echo "Abandoned dump of $fi"
E 6
I 6
			echo "Skipped dump of $fi"
E 6
			askagain=no
			;;
		*)
D 6
			echo 'Answer "y" to do a dump, "n" to skip this filesystem, "e" to exit from dumpall'
E 6
I 6
			echo 'Answer "y" to do a dump, "n" to skip this filesystem'
			echo '"l" to list level and tapes, "e" to exit from dumpall'
E 6
			;;
		esac
	done
E 5
done
E 1
