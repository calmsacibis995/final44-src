#!/bin/csh -f
#
# Mach Operating System
# Copyright (c) 1989 Carnegie-Mellon University
# Copyright (c) 1988 Carnegie-Mellon University
# All rights reserved.  The CMU software License Agreement specifies
# the terms and conditions for use and redistribution.
#
#
# HISTORY
# $Log:	islocked.csh,v $
# Revision 2.3  89/02/25  19:25:55  gm0w
# 	Changes for cleanup.
# 
# Revision 2.2  89/02/07  22:55:42  mwyoung
# Code cleanup cataclysm.
# 

set result=0
foreach file ($argv)
	set rcsfile=RCS/"$file",v
	switch ($file)
		case "*,v":
			breaksw
		default:
			if (! -r $rcsfile) then
				echo "$file"': no RCS file'
				set result=2
			 else
				sed '/^[ 	]*$/,$d' < $rcsfile | egrep '^locks    ; strict;$' > /dev/null
				if ($status) then
					set result=$status
					echo -n "$file"': locked by '
					egrep '^locks    ' < $rcsfile | sed 's/locks    \([^ :]*\):.*/\1/' | head -1
				endif
			endif
			breaksw
	endsw
end
exit $result
