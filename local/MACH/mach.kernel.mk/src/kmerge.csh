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
# $Log:	kmerge.csh,v $
# Revision 2.32  91/11/05  23:50:26  mja
# 	Add PMAX and SUN4 to build/test prompt;  always post to unix-changelog
# 	and also to mach-changelog for the trunk release;  add a final lock
# 	release confirmation prompt after the post process.
# 	[91/11/05  23:06:16  mja]
# 
# Revision 2.31  90/02/09  22:09:42  berman
# 	Added -f to mv when replacing the UpdateLog with the new one.
# 	Added set nonomatch  before trying to remove .BCS*~
# 	[90/02/09            berman]
# 
# Revision 2.30  89/12/25  13:51:34  rpd
# 	After creating new UpdateLog, make it non-writable so that
# 	the next kmerge will ignore it.
# 
# Revision 2.29  89/11/20  18:18:54  mja
# 	Check for error updating VERSION file.
# 
# Revision 2.28  89/11/18  19:04:44  mja
# 	Support merges against non-latest source areas by:
# 	- moving argument parsing to the top and adding -release switch to
# 	  specify the branch name;
# 	- creating base directory and control file names based on the branch; 
# 	- incrementing patch instead of edit level for non-trunk branches; 
# 	- suppressing snapshots and reverse sup's for non-TRUNK releases;
# 	- posting to unix-changelog rather than mach-kernellog for non-trunk
# 	  branches;
# 	- checking-in the .BCSset-<branch> file as ./UpdateSet so that the
# 	  same name can be used for all branches;
# 	- appending the .BCSlog-<branch> file to ./UpdateLog to maintain a
# 	  branch history;
# 	- creating new $vlocal variable to contain the local part of the
# 	  version number (used in multiple places).
# 	[89/11/17  14:49:02  mja]
# 
# Revision 2.27  89/10/15  13:09:42  rpd
# 	Trigger increment of the version number on .BCSmerge-TRUNK
# 	instead of .BCSlog-TRUNK.  This saves people who use bci
# 	before the first use of kmerge.
# 
# Revision 2.26  89/04/09  14:12:15  rpd
# 	Glenn says AUTHCOVER_TESTDIR should be BCSVBASE, not BCSBBASE.
# 
# Revision 2.25  89/04/08  23:26:01  rpd
# 	Fixed test of BCSRELEASE.
# 
# Revision 2.24  89/04/05  18:07:50  rvb
# 	Changed BCSBBASE, BCSSBASE and BCSVBASE to new names.
# 	setenv AUTHCOVER_USER, AUTHCOVER_TESTDIR and AUTHCOVER and
# 	then call bc* programs in ../usr/misc/.rcs/bin, instead of
# 	the ones in ../usr/misc/.sdm/bin.
# 	[89/04/04            mrt]
# 
# Revision 2.23  89/03/17  16:26:50  mrt
# 	Changed bgraft to bmerge which is  the new program
# 	[89/03/17            mrt]
# 
# Revision 2.22  89/03/17  15:34:47  mrt
# 	Fixed delete of .BCSset-TRUNK, .BCSlog-TRUNK and .BCSlock to
# 	be unconditional.
# 	[89/03/17            mrt]
# 
# Revision 2.21  89/02/25  19:26:01  gm0w
# 	Changes for cleanup.
# 
# Revision 2.20  89/02/07  22:56:24  mwyoung
# Code cleanup cataclysm.
# 
# Revision 2.19  89/01/30  22:07:52  rpd
# 	Set BCSSBASE in addition to BCSBBASE and BCSVBASE.
# 	[89/01/30  21:49:28  rpd]
# 
# Revision 2.18  89/01/05  13:10:18  rpd
# 	Now kmerge defaults to "-auto".  Possible arguments to kmerge are
# 	-auto, -fast (passed to bci) and -manual.
# 
# Revision 2.17  88/12/19  06:11:24  mwyoung
# 	Correct BCS[VB]ASE to new location.
# 	[88/12/19            mwyoung]
# 
# Revision 2.16  88/10/21  13:57:26  mwyoung
# 	Fix typo.
# 	[88/10/21            mwyoung]
# 
# Revision 2.15  88/10/21  13:12:23  mwyoung
# 	Change the sense of the default when asking whether to look
# 	for modified files in the tree.
# 	Removed uninteresting history.
# 	[88/10/21            mwyoung]
# 
# Revision 2.13  88/10/18  03:47:45  mwyoung
# 	Convert to newest branch-script technology.
# 	[88/10/18            mwyoung]
# 
# Revision 2.12  88/10/11  10:22:59  rpd
# 	No longer gives -auto by default to bgraft/bci,
# 	but kmerge can take a -auto arg itself now.
# 	[88/10/11  09:33:17  rpd]
# 
# Revision 2.9  88/09/15  17:21:19  mrt
# 	15-Sep-88 Mary Thompson (mrt) @ Carnegie-Mellon
# 	Chmod the post temporary file to  a+r, so that
# 	your own userid does not have to be in the same
# 	group as the first kernsrc group.
# 	Added queries before doing time consuming portions of
# 	the script, so that if you are retrying after an abort
# 	it won't take so long.
# 
# Revision 2.7  88/08/23  00:32:24  mja
# 	Add "./RCSset" to itself in the right order so that it stays
# 	non-writeable after check-in and we can tell that it is safe to
# 	remove the lock.
# 
# Revision 2.6  88/08/22  22:58:25  mja
# 	Added some additional guide statements;  changed to check for
# 	RCSlog instead of RCSset to begin the version sequence so that
# 	the updated file can be checked back in immediately and force
# 	an authentication as 'kernel' as a side effect;  modify graft
# 	and check-in to run in automatic mode to simplify the formal
# 	procedure (especially if everything has already been merged
# 	against the trunk in a private branch);  change to use renamed
# 	-xlog and -xhistory switches (which replace -rlog and -whist);
# 	changed to preserve template post files until a message is
# 	successfully posted;  hacked to change to the real user before
# 	running the post program so that the message gets the right
# 	author for now.
# 
# Revision 2.2  88/07/15  23:58:32  mja
# Created.
# 

# arguments to the bmerge/bci that merge in changes
# defaults to "-auto"
set BArgs = (-auto)

unset release

while ($#argv > 0)
    switch ("$1")
      case "-release":
	if ($#argv < 2) then
	    echo "[ missing argument to $1 ]"
	    exit 1
	endif
	set release = "$2"
	shift; shift
	breaksw
      case "-auto":
	set BArgs = (-auto)
	shift
	breaksw
      case "-fast":
	set BArgs = (-fast)
	shift
	breaksw
      case "-manual":
	set BArgs = ()
	shift
	breaksw
      default:
	break
    endsw
end

#  Double-check to prevent accidental access to latest source area from
#  other releases:  If no -release switch is used, we must be running the
#  script from the "latest" source area, or the current directory
#  must end with "latest".
if (! $?release) then
    set x="$0"
    set x="${x:h}"
    set x="${x:h}"
    if ("${x:t}" != "latest") then
        set x="`pwd`"
	if ("${x:t}" != "latest") then
	    echo "[ Unable to confirm that you intended the 'latest' release by checking the ]"
 	    echo "[ program name ($0) or the ]"
	    echo "[ current directory ($x). ]"
	    echo ""
	    echo "[ Fix one of these or use '-release latest' to confirm. ]"
	    exit 1
	endif
    endif
else
    if ("$release" == "latest") then
	unset release
    endif
endif


setenv BCSBBASE /afs/cs.cmu.edu/mach/src/kernel
if (! $?release) then
    setenv BCSBBASE $BCSBBASE/latest
    setenv BCSBRANCH TRUNK
else
    setenv BCSBBASE "$BCSBBASE/$release"
    setenv BCSBRANCH "$release"
endif
setenv BCSSBASE "$BCSBBASE"
set BCSmerge=".BCSmerge-$BCSBRANCH"
set BCSlog=".BCSlog-$BCSBRANCH"
set BCSset=".BCSset-$BCSBRANCH"
set UPDATEset="UpdateSet"
set UPDATElog="UpdateLog"

setenv BCSVBASE /afs/cs.cmu.edu/mach/rcs/kernel
setenv AUTHCOVER_USER kernel
setenv AUTHCOVER_TESTDIR $BCSVBASE
setenv RCS_AUTHCOVER /usr/misc/.sdm/lib/authcover

setenv RCSBBASE $BCSBBASE

if ( $?BCSRELEASE ) then
    set bcsrelpath="/afs/cs.cmu.edu/@sys/$BCSRELEASE/usr/misc/.rcs/bin"
else
    set bcsrelpath="/usr/misc/.rcs/bin"
endif

if (! -w $BCSBBASE ) then
    echo "[ you do not have write permission in $BCSBBASE ]"
    echo '[ please authenticate yourself as kernsrc and try again ]'
    exit 1
endif

umask 27

if (! -d /afs/cs/user/$USER) then
    echo '[ missing your user name in $USER ]'
    exit 1
endif

echo "[ changing directory to $BCSBBASE ]"
cd $BCSBBASE
if ($status:q != 0) exit 1

echo ''
echo '[ confirming lock ]'
$bcsrelpath/bco
if ($status:q != 0) exit 1

set who=`awk -F: </etc/passwd '$1 == "'$USER'"{printf "%s (%s)\n", $5, $1;exit 123;}'`
if ($status != 123) then
    echo '[ unable to find user $USER in /etc/passwd ]'
    exit 1
endif
echo "[ merge by $who ]"

if (! -f $BCSmerge) then
    echo ''
    if (! $?release) then
	set versionfile=conf/version.edit
    else
	set versionfile=conf/version.patch
    endif
    echo "[ checking-out current $versionfile ]"
    $bcsrelpath/bco -nowrite $versionfile
    if ($status:q != 0) exit 1
    echo ''
    echo "[ incrementing $versionfile ]"
    if (! $?release) then
	awk '{ print $0+1; }' <$versionfile >$versionfile.new
    else
	if (-z $versionfile || ! -f $versionfile) then
	    echo 'a' >$versionfile.new
	else
	    tr '[a-z]' '[b-zA]' <$versionfile >$versionfile.new
	endif
    endif
    if ($status:q != 0) exit 1
    diff $versionfile $versionfile.new
    if ($status:q != 1) exit 1
    mv -f $versionfile.new $versionfile
    if ($status:q != 0) exit 1
    echo ''
    echo "[ checking-in new $versionfile ]"
    $bcsrelpath/bci -auto -m`cat $versionfile` $versionfile
    if ($status:q != 0) exit 1
    date > $BCSmerge
endif

if ($#argv > 0) then

    set def=yes
    echo -n "Are your changes already in a branch?  [$def]  "
    set ans="$<"
    if ($ans:q == "") set ans=$def:q
    if ($ans:q !~ [Yy] && $ans:q !~ [Yy][Ee][Ss]) then
	echo "[ please check them in using 'bci' first ]"
	exit 1
    endif

    unset branch
    set def=$user:q
    while (! $?branch)
	echo -n "What is the branch name?  [$def]  "
	set ans="$<"
	if ($ans:q != "") set def=$ans:q
	if ($ans:q == "" && $def:q != "") set branch=$def:q
    end

    echo ""
    echo "[ merging branch '$branch' with trunk ]"
    $bcsrelpath/bmerge $BArgs:q -r$branch:q $argv:q
    if ($status:q != 0) exit 1

    echo ""
    echo "[ checking merged branch '$branch' into trunk ]"
    $bcsrelpath/bci $BArgs:q -xlog $branch:q -wall
    if ($status:q != 0) exit 1

    echo ""
    echo "[ now build and test this merged kernel for the IBMRT, SUN and VAX ]"
    exit 0
endif

set def=no
echo -n "Are you sure that there are no files in $BCSBBASE that have not been checked in? [$def] "
set ans="$<"
if ($ans:q == "") set ans=$def:q
if ($ans:q =~ [Nn] || $ans:q =~ [Nn][Oo]) then
    echo "[ searching for writeable working files for check-in to trunk ]"
    $bcsrelpath/bci -xhistory `find [a-z]* [A-Z]*[a-z] -type f ! -name 'RCS*' -perm -200 -print`
    if ($status:q != 0) exit 1
endif

set def=no
echo ""
echo -n "Has this kernel been built and tested for the IBMRT, PMAX, SUN3, SUN4 and VAX?  [$def]  "
set ans="$<"
if ($ans:q == "") set ans=$def:q
if ($ans:q !~ [Yy] && $ans:q !~ [Yy][Ee][Ss]) then
    echo "[ please do so now ]"
    exit 1
endif

set def=yes
echo -n "Are you ready to begin the release procedures?  [$def]  "
set ans="$<"
if ($ans:q == "") set ans=$def:q
if ($ans:q !~ [Yy] && $ans:q !~ [Yy][Ee][Ss]) exit 0

if (! $?release) then
    set def=no
    echo -n "Have the snapshot files already been created?  [$def]  "
    set ans="$<"
    if ($ans:q == "") set ans=$def:q
else
    set ans=yes
endif
if ($ans:q !~ [Yy] && $ans:q !~ [Yy][Ee][Ss]) then
    echo ""
    echo "[ making snapshot files ]"
    echo ""
    csh -f src/make_snapshots.csh
endif

if (! $?release) then
    set def=no
    echo -n "Has the sup to wb1 already been successfully completed?  [$def]  "
    set ans="$<"
    if ($ans:q == "") set ans=$def:q
else
    set ans=yes
endif
if ($ans:q !~ [Yy] && $ans:q !~ [Yy][Ee][Ss]) then
    echo ""
    echo "[ updating working area to WB1.CS.CMU.EDU ]"
    cat <<!

WARNING: If you need to abort out of this reverse SUP do not do so
until you see the '/bin/sh: nnnn Killed' diagnostic.  
The script allows 1 minute
for the remote SUP client on WB1.CS.CMU.EDU to connect back to the
temporary file server listener which is started here and then kills
it so that it is not left running to interfere with later connections.
If you abort out of this script before this diagnostic is printed, you
must manually kill the 'supfilesrv -P' process you will find running
on this terminal before invoking the script again.

!
    /bin/sh -c '(trap \"\" 18; exec /usr/cs/etc/supfilesrv -P)&\
       p=$'\!';\
       /usr/cs/etc/supfilesrv -H wb1.cs.cmu.edu kernel sup/xpatch.key -vP /usr/kernel/latest/sup/kernel/`hostname`.supfile </dev/tty& \
       sleep 60; \
       kill -9 $p; \
       wait'
    echo "[ sup status = $status ]"
endif

if (! $?release) then
    set def=yes
    echo -n "Continue?  [$def]  "
    set ans="$<"
    if ($ans:q == "") set ans=$def:q
else
    set ans=yes
endif
if ($ans:q !~ [Yy] && $ans:q !~ [Yy][Ee][Ss]) exit 0

set vlocal="`cat conf/version.variant``cat conf/version.edit``cat conf/version.patch`"
if ($status:q != 0) exit 1
set version="`cat conf/version.major`.`cat conf/version.minor`($vlocal)"
if ($status:q != 0) exit 1

if (! $?release) then
    set bboard=(unix-changelog mach-kernellog)
else
    set bboard=(unix-changelog)
endif

set def=no
echo -n "Has a post already been completed to the $bboard[1] bboard?  [$def]  "
set ans="$<"
if ($ans:q == "") set ans=$def:q
if ($ans:q !~ [Yy] && $ans:q !~ [Yy][Ee][Ss]) then
    echo ""
    echo "[ please draft a post for the $bboard[1] bulletin board ]"
    set KMERGE_POST=/tmp/kmerge-$USER.post
    if (-r $KMERGE_POST) then
        echo "[ re-using existed $KMERGE_POST template ]"
    else
        echo "[ creating new $KMERGE_POST template ]"
	cat src/log-template.post $BCSlog >$KMERGE_POST
        if ($status:q != 0) exit 1
    endif

    set def=EDIT
    while (1)
	if ("$def" =~ [A-Z]*) then
	    set ans=$def:q
	else
	    echo -n "Abort, edit, post, type  [$def]  "
	    set ans="$<"
	   if ($ans:q == "") set ans=$def:q
	endif

	switch ($ans:q)
	case [Aa][Bb]:
	case [Aa][Bb][Oo]:
	case [Aa][Bb][Oo][Rr]:
 	case [Aa][Bb][Oo][Rr][Tt]:
	    exit 1
	    breaksw

	case [Ee]:
	case [Ee][Dd]:
	case [Ee][Dd][Ii]:
	case [Ee][Dd][Ii][Tt]:
	    $EDITOR $KMERGE_POST
	    set def=type
	    breaksw

	case [Pp]:
	case [Pp][Oo]:
	case [Pp][Oo][Ss]:
	case [Pp][Oo][Ss][Tt]:
	    break
	    breaksw

	case [Tt]:
	case [Tt][Yy]:
	case [Tt][Yy][Pp]:
	case [Tt][Yy][Pp][Ee]:
	    more $KMERGE_POST
	    breaksw

	default:
	    cat <<!
[
  One of the following:

  ab[ort] - abort lock release process
  e[dit]  - edit the log message for post
  t[ype]  - display the log message 
  p[ost]  - post the log message to '$bboard[1]'
]
!
	    breaksw

	endsw
	chmod a+r $KMERGE_POST
    end

    echo "[ Please login as '$USER' to provide the proper name for your post ]"
    su -f $USER <<!
    exec post - -who "$who" -subject "Version $version" $bboard <$KMERGE_POST
!
    if ($status != 0) exit 1
    rm -f $KMERGE_POST
endif

set def=no
echo -n "Are you ready to close out this version and release the lock?  [$def]  "
set ans="$<"
if ($ans:q == "") set ans=$def:q
if ($ans:q !~ [Yy] && $ans:q !~ [Yy][Ee][Ss]) exit 0

echo "[ checking $BCSset into trunk as $UPDATEset ]"
rm -f $UPDATEset
cp -p $BCSset $UPDATEset
if ($status:q != 0) exit 1
$bcsrelpath/bcs -l $UPDATEset
$bcsrelpath/bci -m"Version $version" -auto $UPDATEset
if ($status:q != 0) exit 1

echo "[ prepending $BCSlog to $UPDATElog ]"
echo "----- $vlocal -----" >${UPDATElog}-new
cat $BCSlog >>${UPDATElog}-new
if ($status:q != 0) exit 1
if (-e ${UPDATElog}) then
    echo "" >>${UPDATElog}-new
    cat ${UPDATElog} >>${UPDATElog}-new
    if ($status:q != 0) exit 1
endif
mv -f ${UPDATElog}-new ${UPDATElog}
if ($status:q != 0) exit 1
chmod 444 ${UPDATElog}
if ($status:q != 0) exit 1

echo "[ updating VERSIONS for $vlocal ]"
(echo -n "$vlocal = "; \
 date; \
 echo -n "") >> VERSIONS
if ($status:q != 0) exit 1


echo "[ removing $BCSmerge $BCSlog $BCSset *** .BCSlock *** ]"
set nonomatch
rm -f $BCSmerge $BCSlog $BCSset .BCSlock
rm -f .BCS*.BAK .BCS*.CKP .BCS*~
