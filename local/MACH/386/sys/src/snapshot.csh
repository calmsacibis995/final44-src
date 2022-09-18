#!/bin/csh  -f
#
# Mach Operating System
# Copyright (c) 1989 Carnegie-Mellon University
# Copyright (c) 1988 Carnegie-Mellon University
# All rights reserved.  The CMU software License Agreement specifies
# the terms and conditions for use and redistribution.
#
#
# HISTORY
# $Log:	snapshot.csh,v $
# Revision 2.7  89/03/04  17:11:36  rpd
# 	Sometimes a complete snapshot is faster than the incremental stuff.
# 	[89/02/28            rvb]
# 
# Revision 2.6  89/02/25  19:26:59  gm0w
# 	Changed to create and use an awk script instead of sed
# 	as sed ran out of space. Also changed to use whenis -M
# 	instead of ls-l to find date of old snapshot file.
# 	[89/01/01            mrt]
# 
# Revision 2.5  89/02/07  22:56:17  mwyoung
# Code cleanup cataclysm.
# 
# Revision 2.4  89/01/04  15:19:21  rpd
# 	Changed to create and use an awk script instead of sed
# 	as sed ran out of space. Also changed to use whenis -M
# 	instead of ls-l to find date of old snapshot file.
# 	[mrt 1/1/89]
# 
# Revision 2.3  88/11/15  18:19:47  gm0w
# 	Finish adding -v (verbose) switch.
# 	[88/11/15            gm0w]
# 
# Revision 2.1  88/11/15  17:44:44  gm0w
# 	Created from RCS snapshot source.
# 	[88/11/15            gm0w]
# 

# set echo verbose


set prog=$0
set prog=$prog:t

set usage="usage: $prog [-rrev] [-q] [-Foldsnapfile] [-fsnapfile] dir1 ..."

set rev=""
set quiet=""
set filename="RCSSNAP"
unset oldsnap verboseflag

while ($#argv != 0)
    if ("${argv[1]:q}" !~ -*) break
    switch ("$argv[1]")
    case -r*:
	set rev=${argv[1]:q}
	breaksw
    case -F*:
	set oldsnap=`echo "$argv[1]" | sed 's/^..//'`
	breaksw
    case -f*:
	set filename=`echo "$argv[1]" | sed 's/^..//'`
	breaksw
    case -q:
	set quiet=-q
	breaksw
    case -v:
	set verboseflag
	breaksw
    default:
	echo "$usage"
	exit 1
    endsw
    shift
end

if ($#argv == 0) then
    echo "$usage"
    exit 1
endif

if (! $?oldsnap) then
    set f1=/tmp/snap.$$
    find $argv -follow -name "*,v" -print | \
	rcsstat - -R -V ${rev:q} | \
	sort > $f1
    set finalstatus=$status
    mv -f $f1 $filename
    exit $finalstatus
endif

if (! -f $oldsnap) then
    echo "${prog}: could not find $oldsnap"
    exit 1
endif
set oldsnaptime=`whenis -p -n -M $oldsnap`
if ($oldsnaptime !~ [0-9]*) then
    echo "${prog}: bad time for $oldsnap"
    exit 1
endif
set now=`whenis -n`
if ($oldsnaptime > $now) then
    echo "${prog}: future time for $oldsnap"
    exit 1
endif
@ secsago = $now - $oldsnaptime
@ daysago = $secsago / 86400
@ daysago = $daysago + 2

set f1=/tmp/snap1.$$
set f2=/tmp/snap2.$$
set f3=/tmp/snap3.$$
set f4=/tmp/snap4.$$
set fawk=/tmp/snapawk.$$

find $argv -follow -name "*,v" -ctime -$daysago -print | sort > $f1

set wcl = `(wc -l $f1)`
if ($wcl[1] > 500 ) then
# complete snapshot is quicker than humoungous awk script
    echo "$wcl[1] rcs files have changed, doing entire snapshot"
    find $argv -follow -name "*,v" -print | \
	rcsstat - -R -V ${rev:q} | \
	sort > $f1
    set finalstatus=$status
    mv -f $f1 $filename
    exit $finalstatus
endif

sed -n -e '/^\.$/d' \
       -e 's;\.;\\\.;g' -e 's;/;\\/;g' \
       -e 's;^;$0 ~ /^;' \
       -e 's;$;	\[0-9\]\*\\.\[0-9\]\*\$/ { next\; };p' \
	< $f1 > $fawk
echo '{ print $0; }' >> $fawk

awk -f $fawk $oldsnap > $f2

cat $f1 | rcsstat - -R -V ${rev:q} > $f3

sort $f2 $f3 > $f4

set finalstatus=$status

if ($?verboseflag) then
    echo "[ differences between old and new snapshots ]"
    diff $oldsnap $f4
endif

cp $f4 $filename.tmp
mv -f $filename.tmp $filename

rm -f $f1 $f2 $f3 $f4 $fawk

exit $finalstatus
