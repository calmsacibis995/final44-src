
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
#!/bin/sh
umask 077
T=/usr/tmp/asd$$
trap 'rm -f $T.[12]; exit 0' 1 2 3
if mkpkg $* >$T.1
then	seal -k $T.1 >$T.2
	rm -f $T.1
	(trap '' 1
	for i in ${dest:=`comm -23 /etc/asd/machines /etc/whoami`}
	do uux - -r "$i!asdrcv ${source:=`cat /etc/whoami` `getuid`}" <$T.2
	done
	/usr/lib/uucp/uuco
	rm -f $T.2)&
else	rm -f $T.[12]
fi
trap 1 2 3
