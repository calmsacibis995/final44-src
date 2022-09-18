#! /bin/csh -f
#
# Mach Operating System
# Copyright (c) 1989 Carnegie-Mellon University
# Copyright (c) 1988 Carnegie-Mellon University
# All rights reserved.  The CMU software License Agreement specifies
# the terms and conditions for use and redistribution.
#
#
# HISTORY
# $Log:	buildconf.csh,v $
# Revision 2.11  90/06/12  17:43:21  mja
# 	Add -latest and -dist switches;  change installations from
# 	group `sys' to group `kmem'.
# 	[90/06/12  15:49:27  mja]
# 
# Revision 2.10  89/10/15  02:06:27  rpd
# 	Minor cleanups.
# 
# Revision 2.9  89/08/08  15:36:43  gm0w
# 	Changed code to find best config to start with when a choice exists.
# 	[89/08/08            gm0w]
# 
# Revision 2.8  89/08/07  17:08:24  gm0w
# 	Changed to create a symlink instead of renaming config directories
# 	when sharing occurs between two configurations.
# 	[89/08/07            gm0w]
# 
# Revision 2.7  89/03/05  00:41:06  rpd
# 	Add -gamma
# 	[89/02/13  21:35:57  mja]
# 	
# 	Add -default and -beta switches; fix to create non-empty
# 	"CLEAN" files with mode 750.
# 	[88/12/19  12:46:48  mja]
# 
# Revision 2.6  89/02/25  19:17:36  gm0w
# 	Changes for cleanup.
# 
# Revision 2.5  89/02/07  22:56:15  mwyoung
# Code cleanup cataclysm.
# 
# Revision 2.4  88/10/26  05:35:29  mwyoung
# 	Don't bother continuing after a "make" run fails.
# 	[88/10/25            mwyoung]
# 
# Revision 2.3  88/07/15  16:08:56  mja
# Update to reconfigure using new top-level makefile;  eliminate
# wired-in knowledge of configuration file (now always provided
# by caller) for VPATH;  install everything in build area rather
# than trying to intuit the "current" version string.
# 
# 18-May-88  Mike Accetta (mja) at Carnegie-Mellon University
#	Created.
#	[ V5.1(XF25) ]
#

set prog="$0"
set prog="$prog:t"

set nonomatch

unset install
set conf
set keep
set make
unset MACHINE

set DIST=/dist/ALPHA

while ($#argv > 0)
    if ($argv[1] !~ -*) break
    switch ("$argv[1]")
    case "-default":
	set DIST=/dist/DEFAULT
	breaksw
    case "-gamma":
	set DIST=/dist/GAMMA
	breaksw
    case "-beta":
	set DIST=/dist/BETA
	breaksw
    case "-latest":
	set DIST=/dist/LATEST
	breaksw
    case "-dist":
	if ($#argv < 2) then
	    echo "${prog}: missing argument to ${argv[1]}"
	    exit 1
	endif
	set DIST="$argv[2]"
	shift
	breaksw
    case "-install":
	set install
	breaksw
    case "-noconf":
	unset conf
	breaksw
    case "-nokeep":
	unset keep
	breaksw
    case "-nomake":
	unset make
	breaksw
    case "-cpu":
	if ($#argv < 2) then
	    echo "${prog}: missing argument to ${argv[1]}"
	    exit 1
	endif
	set MACHINE="$argv[2]"
	shift
	breaksw
    default:
	echo "${prog}: no such switch $argv[1]"
	exit 1
    endsw
    shift
end

if ($#argv == 0) then
    if (! $?MACHINE) then
	if (-f /etc/machine) then
		set MACHINE="`/etc/machine`"
	else
		echo "${prog}: no /etc/machine, specify machine type with -cpu"
		echo "${prog}: e.g. ${prog} -cpu VAX CONFIGURATION"
		exit 1
	endif
    endif

    switch ("$MACHINE")
	case IBMRT:
	    set cpu=ca
	    breaksw
	case SUN:
	    set cpu=sun3
	    breaksw
	default:
	    set cpu=`echo $MACHINE | tr A-Z a-z`
	    breaksw
    endsw
endif

#  Make sure the sets array is big enough
set sets=()
foreach f ($argv)
   set sets=($sets EMPTY)
end

#  Create the similar system configuration partition sets
set index=1
foreach f ($argv)
    if ("$f" == "=" || "$f" == '+') then
	@ index = $index - 1
	continue
    endif
    if ("$sets[$index]" == "EMPTY") then
	set sets[$index]="$f"
    else
        if (-d "$f") then
	    if (-f "$f/vers.suffix") then
		set conf=`sed -e 's/^\.[^\.]*\.//' $f/vers.suffix`
		if ("$conf" == "$f") then
		    set sets[$index]="$f $sets[$index]"
		else
		    set sets[$index]="$sets[$index] $f"
		endif
	    else
		if (-d "$sets[$index]") then
		    set sets[$index]="$sets[$index] $f"
		else
		    set sets[$index]="$f $sets[$index]"
		endif
	    endif
	else
	    set sets[$index]="$sets[$index] $f"
	endif
    endif
    @ index = $index + 1
end

foreach set ($sets:q)
    if ("$set" == EMPTY) then
	break
    endif
    unset primary
    foreach CONFIG ($set)
	echo ""
	echo "****************** $CONFIG *******************"

	# Reconfigure and build system
	if (! -d "$CONFIG" && $?primary) then
	     echo "[ linking $CONFIG to $primary ]"
	     ln -s "$primary" "$CONFIG"
	endif
	set primary="$CONFIG"
	if ($?make) then
	    make CONFIG="$CONFIG" CONFIG_SUFFIX=.always
	    set savestatus = $status
	    (cd $CONFIG; rm -f vmunix vmunix.sys vmunix.sys.out)
	    if ($savestatus != 0) exit $savestatus
	endif
	if ($?install) then
	    foreach kernel ($CONFIG/vmunix.*.$CONFIG)
		set vers="$kernel:t"
		set vers="$vers:r" 
		set vers="$vers:e" 
		set KERNEL="$DIST/KERNEL.$vers.$CONFIG"
		set CLEAN="$DIST/CLEAN.$vers.$CONFIG"
		if (-e "$kernel") then
		    set ret = 0
		    cp $kernel "$KERNEL"
		    @ ret = ( "$ret" || "$status" )
		    echo -n x > "$CLEAN"
		    @ ret = ( "$ret" || "$status" )
		    /etc/chown sys.kmem "$KERNEL" "$CLEAN"
		    @ ret = ( "$ret" || "$status" )
		    chmod 640 "$KERNEL"
		    @ ret = ( "$ret" || "$status" )
		    chmod 750 "$CLEAN"
		    @ ret = ( "$ret" || "$status" )
		    if ("$ret" == 0) then
			echo "[ installed $KERNEL and $CLEAN ]"
			if (! $?keep) then
			    rm -f "$kernel"
			    echo "[ removed $kernel ]"
			endif
		    else
			echo "[ problem(s) installing $kernel ]"
		    endif
		else
		    echo "[ no $kernel found ]"
		endif
	    end
	endif
    end
end
