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
# $Log:	hinstall.csh,v $
# Revision 2.8  90/08/08  17:57:20  mrt
# 	Added coda directory to machine independent directories.
# 	Added SUN4 case.
# 	[90/08/08            mrt]
# 
# Revision 2.7  89/11/20  18:17:43  mja
# 	Added PMAX and MMAX machine types. Changed so the common
# 	files were only installed on the dist since they are part
# 	of the cs.common-dist collection. Removed kern and vm from
# 	the common list, Added mach_types.defs, std_types.defs and
# 	mach_debug_types.defs
# 	[89/11/16            mrt]
# 
# Revision 2.6  89/02/25  19:25:48  gm0w
# 	Changes for cleanup.
# 
# Revision 2.5  89/02/07  22:55:43  mwyoung
# Code cleanup cataclysm.
# 
# Revision 2.4  89/01/30  22:07:47  rpd
# 	Removed sysV from Sun directories.
# 	[89/01/30  21:39:58  rpd]
# 
# 03-Oct-88  Glenn Marcy (gm0w) at Carnegie-Mellon University
#	Updated for new kernel organization.
#
# 23-May-88  Mike Accetta (mja) at Carnegie-Mellon University
#	Updated for current source and distribution environment.
#	[ V5.1(XF26) ]
#

set echocmd=""
if ($#argv > 0 && $1 == "-test") then
    set echocmd=echo
    shift
endif

set prog=$0
set prog="$prog:t"

set cmudir=/usr/cs/include

if (! $?DIST) then
    set DIST=/dist/ALPHA
endif

if (! $?DISTPATH) then
    set DISTPATH="/dist/ALPHA /dist/BETA /dist/DEFAULT"
endif
set distpath=($DISTPATH)

if ($?KERNELBASE) then
    set srcdir="$KERNELBASE"
else
    set srcdir=/afs/cs/mach/src/kernel/alpha
endif

unsetenv MORE

set common=(cfs mach mach_debug net netimp netinet netns rfs sys)

switch ("`/etc/machine`")
case VAX:
    set machine=($common vax vaxif vaxmba vaxuba mach/vax)
    breaksw
case SUN:
case SUN3:
    set machine=(mon sun sun3 sundev sunif sunwindow sunwindowdev mach/sun3)
    breaksw
case SUN4:
    set machine=(mon sun sun4 sundev sunif sunwindow sunwindowdev mach/sun4)
    breaksw
case IBMRT:
    set machine=(ca cacons caif caio mach/ca mach_debug/ca)
    breaksw
case PMAX:
    set machine=(mips mips/PMAX mach/mips )
    breaksw
case MMAX:
    set machine=(mmax mmaxio mmaxif mach/mmax )
    breaksw
default:
    echo "${prog}: unknown machine type"
    set machine=()
    breaksw
endsw

if ($#argv == 0) then
    set argv= ($machine)
endif

cp /dev/null /tmp/hinstall.list

foreach d ($argv)
    if ($d == "mach") then
	set defs=(mach_types.defs std_types.defs)
    else if ($d == "mach_debug") then
	set defs="mach_debug_types.defs"
    else
	set defs=""
    endif
    cd $srcdir/$d
    foreach f (*.h $defs)
	set curdir="$DIST$cmudir"
	foreach dp ($distpath)
	    if (-e "$dp/$cmudir/$d/$f") then
		set curdir="$dp$cmudir"
		break
	    endif
	end
	if (-e $curdir/$d/$f) then
	    cmp -s $f $curdir/$d/$f
	    set stat=$status
	    if ($stat == 0) then
		echo $d/$f >>/tmp/hinstall.list
		continue
	    endif
	else
	    set stat=0
	endif
	echo ""
	echo "[ $d/$f ]"
	if ("$stat" != "0") then
	    echo "[ comparing $curdir/$d/$f and $f ]"
	    diff $curdir/$d/$f $f | more
	    set what="updat"
	else
	    set what="creat"
	endif
	echo "[ cs version of $d/$f needs to be ${what}ed ]"
	echo -n "${what}e $cmudir/$d/$f ?  [yes] "
	set ans="$<"
	if ("$ans" == "" || "$ans" =~ [yY] || "$ans" =~ [yY][eE][sS]) then
	    echo $d/$f >>/tmp/hinstall.list
	    if (! -d ${DIST}${cmudir}/$d) then
		set mkdir=("${DIST}${cmudir}/$d")
		set dir="$mkdir:h"
		while (! -d "$dir")
		    set mkdir=("$dir" $mkdir)
		    set dir="$dir:h"
		end
		echo "[ making $mkdir ]"
		${echocmd} mkdir $mkdir
		${echocmd} /etc/chown cmu.cmu $mkdir
		${echocmd} chmod 755 $mkdir
	    endif
	    echo "[ ${what}ing ${DIST}$cmudir/$d/$f ]"
	    ${echocmd} cp $f ${DIST}$cmudir/$d/$f
	    ${echocmd} /etc/chown cmu.cmu ${DIST}$cmudir/$d/$f
	    ${echocmd} chmod 644 ${DIST}$cmudir/$d/$f
	endif
    end
end
