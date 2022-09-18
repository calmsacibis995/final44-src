h09018
s 00023/00015/00085
d D 1.5 87/08/11 22:23:54 pc 5 4
c Fix for new labelling system
e
s 00013/00001/00087
d D 1.4 85/04/29 14:39:08 pc 4 3
c Add debugging information into the command
e
s 00001/00001/00087
d D 1.3 84/08/01 16:13:46 pc 3 2
c Add auto-rewind hooks
e
s 00004/00002/00084
d D 1.2 84/08/01 10:54:37 pc 2 1
c Make into real running commands
e
s 00086/00000/00000
d D 1.1 84/07/31 23:51:51 pc 1 0
c date and time created 84/07/31 23:51:51 by pc
e
u
U
t
T
I 1
#!/bin/sh
#	%M%	%I%	%G%
#	shell script to dump a single device
#	the script is called with a single
#	parameter - which is the device to be dumped
#
I 4
#	A second parameter (if set) sets the debug switch which will
#	simply print the parameters to dump and not alter any state
E 4
D 2
dumpdata=dumpdata
E 2
I 2
PATH=:/etc:/bin:/usr/bin:
#
dumpdata=/etc/dumpdata
E 2
dumpcycle=${dumpdata}/dumpcycle
D 2
dump=one
E 2
I 2
dump=/etc/dump
E 2
labelchk="t"
#
dev=$1
if [ "$1" = "" ]
then
D 4
	echo	Usage: doadump device-name
E 4
I 4
D 5
	echo	'Usage: doadump device-name'
E 5
I 5
	echo	'Usage: dumpdev device-name'
E 5
E 4
	exit 1
fi
I 4
chkflg=no
if [ "$2" != "" ]
then
	chkflg=yes
fi
E 4
#	device can be /dev/<name>
#	so we'll look for that and split it off
dev=`echo $dev|sed -e 's/\/dev\///'`
#	Now lets see if the device exists in the dumpcycle file
gstr=`grep "^$dev" $dumpcycle` 2> /dev/null
if [ "$gstr" = "" ]
then
#	it might be a raw device
	altdev=`expr $dev : 'r\(.*\)'`
	if [ "$altdev" = "" ]
	then
		echo Sorry, cannot find device $1 in $dumpcycle
		exit 1
	fi
	dev=$altdev
	gstr=`grep "^$dev" $dumpcycle` 2> /dev/null
	if [ "$gstr" = "" ]
	then
		echo Sorry, cannot find device $1 in $dumpcycle
		exit 1
	fi
fi
#	Now we look for existing dump state
#	stored in a file called devicename.state on /etc/dumpdata
statefile=${dumpdata}/${dev}.state
if [ ! -s $statefile ]
then
#	we ain't got one
	STATE="0"
else
	STATE=`cat $statefile`
fi
#
#	Get the next state from the cycle file
#
awkprog="/^$dev/ { if ($STATE == \$2) print \$3	}"
NEXTSTATE=`awk "$awkprog" < $dumpcycle`
if [ "$NEXTSTATE" = "" ]
then
	echo "Dump state problem"
	echo "State file $statefile contents giving current state = $STATE"
	echo "cannot be found in $dumpcycle"
	exit 1
fi
#
#	Now we need the dump information from the cycle file
#
D 5
awkprog="/^$dev/ { if ($NEXTSTATE == \$2) print \$4,\$5	}"
E 5
I 5
awkprog="/^$dev/ { if ($NEXTSTATE == \$2) print \$4,\$5,\$6	}"
E 5
decodethis=`awk "$awkprog" < $dumpcycle`
if [ "$decodethis" = "" ]
then
	echo "Dump state problem"
	echo "Cannot find state $NEXTSTATE in $dumpcycle"
	exit 1
fi
#
#	This is really nasty - but
#	now finally set the dump level and the tape range
D 5
LEVEL=`expr "$decodethis" : '^\(.*\) '`
TAPE=`expr "$decodethis" : '^.* \(.*\)$'`
I 4
if [ "$chkflg" = yes ]
then
	echo "DUMP of /dev/$dev at level ${LEVEL} to tapes $TAPE"
	exit 1
fi
E 4
D 3
$dump u${labelchk}${LEVEL} $TAPE /dev/$dev
E 3
I 3
$dump ou${labelchk}${LEVEL} $TAPE /dev/$dev
E 5
I 5
echo $decodethis | (
	read LEVEL TAPESTEM TAPECYCLE
	if [ "$chkflg" = yes ]
	then
		echo "DUMP of /dev/$dev at level ${LEVEL} to tapes $TAPESTEM $TAPECYCLE"
		exit 1
	fi
	if [ "$TAPECYCLE" = "" ]
	then
		$dump oul${labelchk}${LEVEL} $TAPESTEM /dev/$dev
		retval=$?
	else
		$dump oulm${labelchk}${LEVEL} $TAPESTEM $TAPECYCLE /dev/$dev
		retval=$?
	fi
E 5
E 3
#
D 5
#	dump returns 1 on a successful dump
E 5
I 5
#	dump returns 0 on a successful dump
E 5
#
D 5
if [ $? = 1 ]
then
	echo $NEXTSTATE > $statefile
fi
E 5
I 5
	if [ $retval = 0 ]
	then
		echo $NEXTSTATE > $statefile
	fi
)
E 5
exit 0
E 1
