#!/bin/sh
#
# Mach Operating System
# Copyright (c) 1989 Carnegie-Mellon University
# All rights reserved.  The CMU software License Agreement specifies
# the terms and conditions for use and redistribution.
#
#
# HISTORY
# $Log:	fix-log.sh,v $
# Revision 2.4  89/02/25  19:25:35  gm0w
# 	Changes for cleanup.
# 
# Revision 2.3  89/02/20  15:32:06  rpd
# 	No longer writes warning messages to /dev/tty; look at exit status
# 	instead.  Now handles whist entries between HISTORY and Log.
# 
# Revision 2.2  89/02/19  21:35:33  rpd
# 	Created.
# 	[89/02/19  21:29:15  rpd]
# 

# In the following discussion, replace % with $.
#
# Adds %Log% after HISTORY lines, if it isn't already present.
# Deduces the proper prefix from the HISTORY line.
# Will fix the following broken forms:
#
# Bob Baron style:
# * HISTORY
# *%Log: foo%
#
# Another Bob Baron style:
# * HISTORY
# * %Log:
#
# Rich Sanzi style:
# * HISTORY %Log: msg%
#
# If everything looks OK, we exit with status code zero.
# If there is some problem with the resulting file, then
# we exit with a non-zero status code.

awk '
/HISTORY.*\$Log[:$]/ {
	if (sawhistory || wrotelog) {
	    barf = 1;
	} else {
	    len = length($0);
	    for (i = 1; substr($0, i, 7) != "HISTORY"; i++);
	    prefix = substr($0, 1, i-1);

	    if (substr(prefix, i-1, 1) == " ") {
		sprefix = substr(prefix, 1, i-2);
		tprefix = sprefix "\t";
	    }

	    for (i = 1; substr($0, i, 4) != "$Log"; i++);
	    for (j = i+1; j<=len && substr($0, j, 1) != "$"; j++);
	    savedlogmsg = substr($0, i, j-i+1);
	    if (substr(savedlogmsg, length(savedlogmsg), 1) != "$")
		savedlogmsg = savedlogmsg "$";
	    if (savedlogmsg == "$""Log:$")
		savedlogmsg = "$""Log$";

	    printf("%sHISTORY\n", prefix);
	    sawhistory = 1;
	    next;
	}
    }
/HISTORY/ {
	if (sawhistory || wrotelog) {
	    for (i = 1; substr($0, i, 7) != "HISTORY"; i++);
	    if (prefix == substr($0, 1, i-1))
		barf = 1;
	} else {
	    for (i = 1; substr($0, i, 7) != "HISTORY"; i++);
	    prefix = substr($0, 1, i-1);

	    if (substr(prefix, i-1, 1) == " ") {
		sprefix = substr(prefix, 1, i-2);
		tprefix = sprefix "\t";
	    }

	    printf("%sHISTORY\n", prefix);
	    sawhistory = 1;
	    next;
	}
    }
sawhistory == 1 && /\$Log[:$]/ {
	len = length($0);
	for (i = 1; substr($0, i, 4) != "$""Log"; i++);
	for (j = i+1; j<=len && substr($0, j, 1) != "$"; j++);
	logmsg = substr($0, i, j-i+1);
	if (substr(logmsg, length(logmsg), 1) != "$")
	    logmsg = logmsg "$";
	if (logmsg == "$""Log:$")
	    logmsg = "$""Log$";

	for (i = 0; i < buflen; i++)
	    printf("%s\n", histbuf[i]);
	printf("%s%s\n", prefix, logmsg);
	sawhistory = 0;
	wrotelog = 1;
	next;
    }
sawhistory == 1 {
	cprefix = substr($0, 1, length(prefix));
	if (cprefix == prefix || cprefix == tprefix || cprefix == sprefix) {
	    histbuf[buflen++] = $0;
	} else {
	    if (savedlogmsg)
		printf("%s%s\n", prefix, savedlogmsg);
	    else
		printf("%s$""Log$\n", prefix);
	    for (i = 0; i < buflen; i++)
		printf("%s\n", histbuf[i]);
	    sawhistory = 0;
	    wrotelog = 1;
	    print;
	}
	next;
    }
/\$Log[:$]/ { barf = 1; }
{ print; }
END {
	if (sawhistory) {
	    if (savedlogmsg)
		printf("%s%s\n", prefix, savedlogmsg);
	    else
		printf("%s$""Log$\n", prefix);
	    for (i = 0; i < buflen; i++)
		printf("%s\n", histbuf[i]);
	    wrotelog = 1;
	}
	if (!wrotelog)
	    barf = 1;
	exit barf;
    }
'
