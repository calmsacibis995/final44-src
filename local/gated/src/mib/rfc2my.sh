: run this script through /bin/sh
#
#	$Id: rfc2my.sh,v 1.8 1992/08/12 21:22:33 jch Exp $
#

cat $* | awk '
BEGIN	{
	    prefix = "";
	    started = 0;
	}
/MIB [ ]*DEFINITIONS[ ]*::=[ ]*BEGIN/ {
	    prefix = "";
	}
/SMI [ ]*DEFINITIONS[ ]*::=[ ]*BEGIN/ {
	    prefix = "";
	}
/DEFINITIONS[ ]*::=[ ]*BEGIN/ {
	    if (length(prefix) > 0) {
		print prefix;
		prefix = "";
	    }
	    started = 1;
	}
/MIB/ && !/--.*MIB/ {
	    if (!started) {
		prefix = $0;
		next;
	    }
	}
/\[Page [1-9][0-9]*\]?$/ {
	    eating = 1;
	    next;
	}
//	{
	    if (eating)
		next;
	}
/^[ ]*$/ {
	    if (eating)
		next;
	}
	{
	    if (eating)
		eating = 0;
	    else
		if (started)
		    print $0;
		else
		    if (length(prefix) > 0)
			prefix = prefix "\n" $0;
	}
/END$/	{
	    if (started)
		exit(0);
	}
'

exit
