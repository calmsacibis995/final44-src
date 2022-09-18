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
# $Log:	setacl.csh,v $
# Revision 2.7  89/08/23  16:38:08  berman
# 	Added mips, rfs and sun4 directories. Added system:AnyUser access to .
# 	and mach and mach_debug subdirectories.
# 	[89/08/11            mrt]
# 
# Revision 2.6  89/04/07  16:00:26  rvb
# 	Added new directories: builtin, mach, mach_debug, dialupip, i386,
# 	i386at, i386exl, and standi386. Added System:AnyUser read access
# 	to: builtin, mach, mach_debug, kern, src, sys, vm.
# 	[89/04/05            mrt]
# 
# Revision 2.5  89/02/25  19:26:53  gm0w
# 	Changes for cleanup.
# 
# Revision 2.4  89/02/07  22:55:39  mwyoung
# Code cleanup cataclysm.
# 
# Revision 2.3  89/02/04  21:41:06  mja
# 	Only set read permissions by default, any other optional general
# 	permission (like "kernel:updateSource all" should be specified on the
# 	command line); add NFS set, initially "krpc nfs rpc specfs vfs"; add
# 	"afs afsint" to IBM set;  move "sysV" from SUN set to ENCORE set.
# 
# Revision 2.2  88/08/30  00:06:51  mwyoung
# 	Created by someone else.  I got stuck checking it in.
#

#
# completely resets the vice access to all the directories
# in /afs/cs/mach/src/kernel/{latest,CSi...}
# to use cd to the kernel directory in question and setacls

set all_al="kernel:View read $*"
set sqt_al='kernel:View.SEQUENT read'
set mmx_al='kernel:View.ENCORE read'
set dec_al='kernel:View.ULTRIX read'
set pmax_al='kernel:View.PMAX read'
set sun_al='kernel:View.SUN read'
set ibm_al='kernel:View.IBM read'
set bsd_al='kernel:View.4BSD read'
set nfs_al='kernel:View.NFS read'
set cmu_al='kernel:View.Local read'
set i386_al='kernel:View.I386 read'

set table=(\
    cmu "builtin compat inline kern lib mach mach_debug man mdb rfs src sup vm" \
    bsd "RCS bsd cassette conf consolerl dialupip dist floppy h mdec net netimp netinet netns stand src/config sys vax vaxif vaxmba vaxuba" \
    dec "emul ultrix" \
    pmax "mips" \
    sun "mon pixrect sun sun3 sun4 sundev sunif sunstand sunwindow sunwindowdev" \
    ibm "afs afsint standca ca cacons caif caio vice" \
    mmx "mmax mmaxif mmaxio sysV" \
    sqt "sqt sqtconf sqtif sqtmbad sqtsec sqtzdc" \
    nfs "krpc nfs rpc specfs vfs" \
    i386 "i386 i386at i386exl standi386at" \
)
set world_read=(builtin mach mach_debug kern sys vm)

if ( $#argv == 0 ) then
   echo "Directories will have no write access."
   echo "If you want write access put it on the command line e.g."
   echo ' "kernel:updateSource all"'
   echo -n "Do you want to continue? [y] "
   set ans="$<"
   if ($ans:q =~ [Nn]) exit 1
endif

fs sac . kernel:View.Local read kernel:View.Any l System:AnyUser rl $all_al

foreach type ($table:q)
    if (! $?class) then
	set class="$type"
    else
	echo "[ $class ]"
	eval 'set al=($'${class}_al')'
	find $type -type d -print -exec fs sac {} $all_al $al \;
	unset class
    endif
end

# Give System:AnyUser read access to code written by CMU
echo "add System:AnyUser read permission"
find $world_read -type d -print -exec fs sa {} System:AnyUser read \;
fs sa sys System:AnyUser read



