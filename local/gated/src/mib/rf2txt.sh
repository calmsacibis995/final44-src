: Run this through /bin/sh
#
#	$Id: rf2txt.sh,v 1.7 1992/07/29 03:09:59 jch Exp $
#

files=${*} ;

DATE=`date | awk '
BEGIN {
	month["Jan"] = "January" ;
	month["Feb"] = "Feburary" ;
	month["Mar"] = "March" ;
	month["Apr"] = "April" ;
	month["May"] = "May" ;
	month["Jun"] = "June" ;
	month["Jul"] = "July" ;
	month["Aug"] = "August" ;
	month["Sep"] = "September" ;
	month["Oct"] = "October" ;
	month["Nov"] = "November" ;
	month["Dec"] = "December" ;
}
{
	printf "%s %d, %d", month[$2], $3 + 0, $6 ;
}'`

sed -e "s/%%TODAY%%/${DATE}/" ${files} | \
nroff -me | \
col -b | \
#sed -e 's/^/     /' -e 's/^ *$//' |\
awk '
BEGIN {
	linecount = 1;
	pagesize = 58 ;
}

{
	if (strlen($0)) {
		printf "     %s\n", $0;
	} else {
		printf " %s\n", $0;
	}
	if (linecount++ >= pagesize) {
		printf "\f\n" ;
		linecount = 1;
	}
}'


