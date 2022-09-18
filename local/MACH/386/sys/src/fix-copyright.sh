#!/bin/sh
#
# Mach Operating System
# Copyright (c) 1989 Carnegie-Mellon University
# All rights reserved.  The CMU software License Agreement specifies
# the terms and conditions for use and redistribution.
#
#
# HISTORY
# $Log:	fix-copyright.sh,v $
# Revision 2.4  89/02/25  19:25:23  gm0w
# 	Changes for cleanup.
# 
# Revision 2.3  89/02/20  13:38:09  rpd
# 	Added the ability to deduce the current current year from "date"
# 	or take it as a command-line argument.
# 
# Revision 2.2  89/02/19  21:35:06  rpd
# 	Created.
# 	[89/02/19  21:28:18  rpd]
# 

# Takes a file containing
#
#/* 
# * Mach Operating System
# * Copyright (c) 1987 Carnegie-Mellon University
# * All rights reserved.  The CMU software License Agreement specifies
# * the terms and conditions for use and redistribution.
# */
#
# and turns it into
#
#/* 
# * Mach Operating System
# * Copyright (c) 1989 Carnegie-Mellon University
# * Copyright (c) 1988 Carnegie-Mellon University
# * Copyright (c) 1987 Carnegie-Mellon University
# * All rights reserved.  The CMU software License Agreement specifies
# * the terms and conditions for use and redistribution.
# */
#
# We deduce the proper comment leader, but as a sanity check it must
# be less than four characters long.  (This is why the above sample
# copyrights stay intact.)
#
# Takes an optional command line argument which specifies the current year;
# this defaults to the current year as returned by "date".
#
# Will also turn old-style copyrights into new-style ones.

year="${1-`date | awk '{ print $NF; }'`}"

awk '
BEGIN { curyear = 0 + "'"$year"'"; lowyear = curyear; }
sawcopy == 0 { print; }
/Mach Operating System$/ {
	for (i=1; substr($0, i, 4) != "Mach"; i++);
	if (i <= 4) {
	    sawcopy = 1;
	    leader = substr($0, 1, i-1);
	}
    }
sawcopy == 1 && /Copyright / { if ($4 < lowyear) lowyear = $4; }
sawcopy == 1 && (/the terms and conditions/ || /All other rights/) {
	for (year = curyear; lowyear <= year; year--)
	    printf("%sCopyright (c) %d Carnegie-Mellon University\n", leader, year);
	printf("%sAll rights reserved.  The CMU software License Agreement specifies\n", leader);
	printf("%sthe terms and conditions for use and redistribution.\n", leader);
	sawcopy = 0;
    }
'
