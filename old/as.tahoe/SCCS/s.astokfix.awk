h20298
s 00009/00000/00000
d D 5.1 90/03/23 09:45:06 bostic 1 0
c date and time created 90/03/23 09:45:06 by bostic
e
u
U
t
T
I 1
#
#	Copyright (c) 1982 Regents of the University of California */
#	@(#)astokfix.awk 4.4 6/30/83
#
/AWKFIXESME/{
	if ($4 == "AWKFIXESME"){
		print $1 " " $2 " " $3 " " count++;
	}
}
E 1
