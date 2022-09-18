#!/bin/sh
#
# 
# Mach Operating System
# Copyright (c) 1989 Carnegie-Mellon University
# All rights reserved.  The CMU software License Agreement specifies
# the terms and conditions for use and redistribution.
#
# HISTORY
# $Log:	sizecheck.sh,v $
# Revision 2.2  89/07/12  00:11:54  jjc
# 	Picked up from SunOS 4.0.
# 	[89/07/03            jjc]
# 
###########################################################################
# @(#)sizecheck 1.4 88/02/08 SMI
#
size=`size $1 | tail -1 | awk ' { print $1 + $2; } '`
if [ $size -ge 7680 ]
then
	echo Boot block `expr $size - 7680` bytes too big!!
	exit 1
fi
echo Boot block is `expr 100 '*' $size '/' 7680`% full.
exit 0
