: run this script through /bin/sh
#
#	$Id: mib-checker.sh,v 1.7 1992/07/29 03:09:52 jch Exp $
#

PERSON="$1"

MHL="/usr/local/lib/mh/mhl -nobell -noclear -nomoreproc"
GAWK="awk"
MOSY="/usr/local/bin/mosy"
SNMPI="/usr/local/bin/snmpi"
SMI="/usr/include/isode/snmp/smi.defs"
MHMAIL="/usr/local/bin/mhmail"
SCAN="/usr/local/bin/scan -noclear -noheader"
RFC2MY="`pwd`/rfc2my.sh"

F=/tmp/mib$$ 	   M=1                R=/tmp/mib$$.reply       L=/tmp/mib$$.log
I=$F/$M
Y=/tmp/mib$$.my    D=/tmp/mib$$.defs  Z=/tmp/mib$$a.defs
P=/tmp/mib$$.prf   C=/tmp/mib$$.ctx
trap "rm -rf $F $R $L $Y $D $Z $P $C" 0 1 2 3 13 15

cd /tmp

echo "Path: /tmp" > $P
MH="$P" export MH

echo "Current-Folder: $F" > $C
MHCONTEXT="$C" export MHCONTEXT

mkdir $F
cat > $I

FROM=`$SCAN -format "%<{reply-to}%{reply-to}%|%<{from}%{from}%|%<{sender}%{sender}%|%<{return-path}%{return-path}%>%>%>%>" $M`

SUBJECT=`$SCAN -format "%<{subject}Re: %{subject}%>" $M`

${RFC2MY} < $I > $Y

echo "% mosy $Y" >> $R
if $MOSY $Y >> $R 2>&1; then
    cat $SMI $D > $Z

    echo "" >> $R
    echo "% snmpi -f $Z quit" >> $R
    if $SNMPI -f $Z quit >> $R 2>&1; then
	echo "" >> $R
	if [ -z "$PERSON" ]; then
	    echo "# No errors were detected in your MIB" >> $R
	else
	    echo "# Your MIB is being sent to $PERSON for further checking" >> $R
	    $MHL -form mhl.body < $I \
		| $MHMAIL "$PERSON" -subject "MIB for checking" -from "$FROM"
	fi
    else
	echo "" >> $R
	echo "# Pass two (snmpi) failed" >> $R
    fi
else
    echo "" >> $R
    echo "# Pass one (mosy) failed" >> $R
fi

if [ -z "$PERSON" ]; then
    $MHMAIL "$FROM" -subject "$SUBJECT" < $R
else
    $MHMAIL "$FROM" -subject "$SUBJECT" -from "$PERSON" -cc "$PERSON" < $R
fi

date | $GAWK '
BEGIN	{
	    months["Jan"] =  1;
	    months["Feb"] =  2;
	    months["Mar"] =  3;
	    months["Apr"] =  4;
	    months["May"] =  5;
	    months["Jun"] =  6;
	    months["Jul"] =  7;
	    months["Aug"] =  8;
	    months["Sep"] =  9;
	    months["Oct"] = 10;
	    months["Nov"] = 11;
	    months["Dec"] = 12;
	}
	{ printf "%2d/%2d %s mib-chec ", months[$2], $3, $4; }
'						 > $L
echo $$	| $GAWK '{ printf "%05d ", $1; }'	>> $L
whoami	| $GAWK '{ printf "(%-8s)  ", $1; }'	>> $L
echo "$FROM" "$SUBJECT"				>> $L
cat $L >> /var/tmp/mosy.log

exit 0
