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
# $Log:	mksysprogs.csh,v $
# Revision 2.5  89/02/25  19:26:38  gm0w
# 	Changes for cleanup.
# 
# Revision 2.4  89/02/07  22:55:41  mwyoung
# Code cleanup cataclysm.
# 
# Revision 2.3  88/07/15  16:13:18  mja
# Check for existence of sources in destination area as well as
# original source area.
# Updated for new RCS source tree organization;  added absolute
# command names to speed execution.
# 

set prog="$0"
set prog="${prog:t}"

set SRC=/afs/cs.cmu.edu/bsd4.3/source/rcs
set syslink_dat=/usr/cs/lib/syslink.dat
set I=()
set DST="$cwd"
set DESTDIR=/dist/ALPHA

set AWK=/bin/awk
set RM=/bin/rm
set LN=/bin/ln

set auxfiles=(/bin/as)

unset build_flag install_flag

set configs=()
set makeopts=()
set clean=""

while ($#argv > 0)
    if ("$1" !~ -*) break
    switch ("$1")
	case "-b":
	case "-build":
	    set build_flag; breaksw
	case "-i":
	case "-install":
	    set install_flag; breaksw
	case "-c":
	case "-config":
	    if ($#argv < 2) then
	        echo "${prog}: missing configuration name for $1"; exit 1
	    endif
	    set configs=($configs $2)
	    shift
	    breaksw
	case "-destdir":
	    if ($#argv < 2) then
	        echo "${prog}: missing destination directory for $1"; exit 1
	    endif
	    set DESTDIR="$2"
	    shift
	    breaksw
	case -M:
	    if ($#argv < 2) then
	        echo "${prog}: missing destination directory for $1"; exit 1
	    endif
	    set makeopts=($makeopts:q $2)
	    shift
	    breaksw
	case "-I":
	    if ($#argv < 2) then
	        echo "${prog}: missing destination directory for $1"; exit 1
	    endif
	    set I=($I:q -I$2)
	    shift
	    breaksw
	case "-noclean":
	    set noclean
	    breaksw
	case "-src":
	    if ($#argv < 2) then
	        echo "${prog}: missing argument to $1"; exit 1
	    endif
	    set SRC="$2"
	    shift
	    breaksw
	case "-syslink":
	    if ($#argv < 2) then
	        echo "${prog}: missing argument to $1"; exit 1
	    endif
	    set syslink_dat="$2"
	    shift
	    breaksw
	default:
	    echo "${prog}: unknown switch: $1"; exit 1
    endsw
    shift
end

if ($#argv > 0) then
    set files=($argv)
else
    set files=(`$AWK <$syslink_dat '$0 !~ /^#/{print $1;}'`)
endif

if ($#configs == 0) set configs=(DEFAULT)

set failed=()

if (-e $SRC/RCS) then
   set SLASH_RCS="/RCS"
else
   set SLASH_RCS=""
endif

foreach file ($auxfiles CONFIGS $files)
    if ("$file" == "CONFIGS") then
	set CONFIGS=($configs)
	continue
    endif
    set dir=${file}
    set program=${file:t}
    set DIR=${SRC}${dir}
    if (-d "$DIR" || -d "${DST}/${dir}") then
	set target="" #${program:t}
	set install=install
	if (! $?noclean) set clean="make clean"
    else
	set dir=${dir:h}
	set DIR=${SRC}${dir}
	if (! -f "${DIR}${SLASH_RCS}/${program}.c,v" && ! -f "${DST}/${dir}/${program}.c") then
	    echo "[ no source for $file - skipped ]"
	    continue
	endif
	set target=${program}.x
	set install=${program}.install
	if (! $?noclean) set clean="$RM -f $target"
    endif
    set RCS=${dir}/RCS
    /usr/cs/etc/makepath $DST$RCS
    $RM -f $DST$RCS
    $LN -s $SRC$dir${SLASH_RCS} $DST$RCS
    foreach f (VAX SUN IBMRT)
	set LINK=${dir}/$f/RCS
	if (-d $SRC$dir/$f${SLASH_RCS}) then
	    /usr/cs/etc/makepath $DST$LINK
	    $RM -f $DST$LINK
	    $LN -s $SRC${dir}/$f${SLASH_RCS} $DST$LINK
	endif
    end
    set build=$DST${dir}

    if (! $?CONFIGS) then
	continue
    endif

    foreach config ($CONFIGS)
 	set ok
	set makeflags='CENV='"$I"' -DCONFIG_'"$config"'="" -DKERNEL_FEATURES'
	if ($?build_flag) then
	    echo "[ Executing 'make $target' in $build ]"
	    (cd $build; $clean; exec make $makeflags:q $makeopts $target)
	    if ("$status" != 0) then
	        unset ok
		echo "*** ${file}: $config configuration failed ***"
		set failed=($failed $file)
	    endif
	endif
	if ($?install_flag && $?ok) then
	    echo "[ Executing 'make $install' from $build ]"
	    (cd $build; exec make DESTDIR=$DESTDIR $makeflags:q $makeopts $install)
	    if ("$status" != 0) then
		echo "*** ${file}: $config configuration not installed ***"
		set failed=($failed $file)
	    endif
	endif
    end
end

if ($#failed > 0) then
    echo "*** Failures: $failed ***"
endif
