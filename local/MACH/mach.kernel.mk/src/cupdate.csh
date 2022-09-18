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
# $Log:	cupdate.csh,v $
# Revision 2.5  89/04/07  15:59:28  rvb
# 	Changed name of the kernel rcs directory to
# 	/afs/cs.cmu.edu/mach/rcs/kernel.
# 	[89/04/05            mrt]
# 
# Revision 2.4  89/02/25  19:25:09  gm0w
# 	Changes for cleanup.
# 
# Revision 2.3  89/02/07  22:56:28  mwyoung
# Code cleanup cataclysm.
# 
# Revision 2.2  88/09/15  12:19:41  mrt
# Who knows...
# 
# Revision 2.1  88/09/15  11:03:29  mrt
# Created.
#

# script to checkout all the files in a set of snapshot files
# or all the files that are different between two snaphots
# usage cupdate -snew [-sold] namelist
#   eg. cupdate -sX41 -sX40 MI vax sun3 ca
#
# Assumes that all the required snapshot files are checked
# in in /afs/cs.cmu.edu/mach/rcs/kernel/SNAPSHOTS with the version
# names corresponding to kernel version.
#

if ( $#argv == 0 ) then
	echo "usage is $0 -s<newsnapfile> [-s<oldsnapfile>] dirlist"
	exit 1
endif
set noold=0
set coll=""
set snapshotsource="/afs/cs.cmu.edu/mach/rcs/kernel/SNAPSHOTS"
set TD=`pwd`
set SSD=$TD/SNAPSHOTS

if ( "$argv[1]" =~ -s*) then
    set snapnew=`echo "$argv[1]" | sed 's/^..//'`
else 
    echo "first argument must be a -s<newsnapfile>"
    exit 1
endif
shift argv
if ( "$argv[1]" =~ -s* ) then
    set snapold=`echo "$argv[1]" | sed 's/^..//'`
    shift argv
else
   set noold=1
   touch $TD/tmpold
endif
if ( ! -d $SSD ) then
    rm -rf $SSD
    mkdir $SSD
endif
if ( ! -d $SSD/$snapnew ) then
    (cd $SSD; rm -rf $snapnew; mkdir $snapnew)
endif
cd $SSD/$snapnew
while ($#argv != 0 )
    rcsco -r$snapnew $snapshotsource/$argv[1],v
    set coll="$coll $argv[1]"
    shift argv
end
if ( $noold == 0 ) then
    if ( ! -d $SSD/$snapold ) then
	(cd $SSD; rm -rf $snapold; mkdir $snapold)
    endif
    cd $SSD/$snapold
    foreach file ( $coll )
	rcsco -r$snapold $snapshotsource/$file,v
    end
endif

rm -f $TD/$snapnew.upd
rm -f $TD/$snapnew.tmp
touch $TD/$snapnew.upd
cd $snapshotsource/..
foreach file ( $coll )
    if ( $noold == 1 ) then
	coconfig -P$TD -s$SSD/$snapnew/$file \
	    -s$TD/tmpold -f$TD/$snapnew.tmp -t
    else
	coconfig -P$TD -s$SSD/$snapnew/$file \
	    -s$SSD/$snapold/$file \
	    -f$TD/$snapnew.tmp -t
    endif
    rm -f $TD/$snapnew.tmp
    cat $TD/$snapnew.upd $TD/$snapnew.tmp.upd > $TD/$snapnew.tmp
    cp $TD/$snapnew.tmp $TD/$snapnew.upd
    rm -f $TD/$snapnew.{tmp,tmp.upd}
end
if ( $noold == 1 ) rm $TD/tmpold

