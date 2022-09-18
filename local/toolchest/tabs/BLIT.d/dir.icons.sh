
#
#      Copyright (c) 1984, 1985 AT&T
#      All Rights Reserved
#
#      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
#      CODE OF AT&T.
#      The copyright notice above does not 
#      evidence any actual or intended
#      publication of such source code.
#
echo "\014"
count=1
ls -d $* | while read line
do
	letter=`echo $count | tr "0123456789" "@ABCDEFGHI"`
	echo "		$letter	- $line"

	send_netty -i $count $line < /dev/tty
	send_netty -p $count $count $letter "ls -l $line\r"

	count=`expr $count + 1`
	if test $count -eq 10
	then
		count=1
		echo "Continue (hit break to exit)?\c"
		read wait < /dev/tty
		echo
	fi
done
