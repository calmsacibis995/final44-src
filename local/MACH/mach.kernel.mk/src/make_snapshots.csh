#!/bin/csh -fb
# 
# Mach Operating System
# Copyright (c) 1989 Carnegie-Mellon University
# Copyright (c) 1988 Carnegie-Mellon University
# All rights reserved.  The CMU software License Agreement specifies
# the terms and conditions for use and redistribution.
#
#
# HISTORY
# $Log:	make_snapshots.csh,v $
# Revision 2.14  89/11/18  19:07:03  mja
# 	Undo omission of "." from subset files.  We can't find anyone
# 	who knows why this used to be a feature and it is currently
# 	breaking things for the Makefile and Makeconf files.
# 
# Revision 2.13  89/04/05  18:09:29  rvb
# 	The snapshot program processes all the files in a directory and its
# 	subdirectories so we must eliminate . and all subdirectories from the
# 	Directories/ALL list.
# 
# Revision 2.12  89/02/25  19:26:18  gm0w
# 	Changes for cleanup.
# 
# Revision 2.11  88/11/15  18:30:37  gm0w
# 	One more time...
# 	[88/11/15            gm0w]
# 
# Revision 2.9.1.1  88/11/15  18:15:04  gm0w
# 	Invoke snapshot with -v (verbose) switch.
# 	[88/11/15            gm0w]
# 
# Revision 2.7.1.1  88/11/15  17:45:23  gm0w
# 	Restored some missing code removed in previous change.
# 	Reorganized to use incremental snapshots.
# 	[88/11/15            gm0w]
# 
# Revision 2.8  88/10/28  16:41:28  mrt
# 	 28-Oct-88 Mary Thompson (mrt)
# 	Renamed tempory directory from RCSTMP which no long
# 	exist to $SS. Removed the version name before checking
# 	in new version in case this is the second time thru.
# 
# Revision 2.7  88/09/15  12:20:22  mrt
# 	 14-Sep-88 Mary Thompson (mrt) @ Carnegie-Mellon University
# 	Create snapshot files in SS directory rather than
# 	SS/$version as they are now rcs'ed
# 	
# 	 8-Sep-88  Michael Young (mwyoung) @ Carnegie-Mellon University
# 		Be more careful to not accept subset matches (e.g., don't get
# 		"./standca" files when looking for "./stand" files).
# 	[88/09/15  11:00:21  mrt]
# 
# Revision 2.6  88/09/01  16:35:36  mwyoung
# 	Fix the ending loop to try to avoid the mysterious "Child
# 	exited" failure.
# 	[88/09/01            mwyoung]
# 
# Revision 2.5  88/08/30  00:49:20  mwyoung
# 	Another typo.
# 	[88/08/30            mwyoung]
# 
# Revision 2.4  88/08/30  00:29:39  mwyoung
# 	Corrected typo.
# 	[88/08/30            mwyoung]
# 
# Revision 2.3  88/08/30  00:20:04  mwyoung
# 	Move snapshot file directory, so that the merge script doesn't
# 	think it contains files that should be checked in.  Use a
# 	variable, in case someone finds it necessary to move it again.
# 	[88/08/30            mwyoung]
# 
# Revision 2.2  88/08/30  00:10:20  mwyoung
# 	Created.
# 	[88/08/29            mwyoung]
# 
#

#
# A script to create snapshots of the entire kernel source
# tree, and of selected subsets.
#
# Takes no arguments.  Must be run from the root of the source tree,
# where an RCS directory tree (or symbolic link) must exist with the same
# structure as the sources themselves.  [Uses the directory lists in
# "Directories/" to enumerate the directories in the full set of
# sources and in the subsets.]

set SS=SNAPSHOTS

if ($#argv != 0) then
	echo 'This script takes no arguments.'
	exit 1
 endif

if ( ! -d RCS || ! -r RCS || ! -d Directories || ! -r Directories ) then
	echo 'This script must be run at the root of the kernel source tree.'
	exit 1
 endif

if ( ! -d $SS || ! -w $SS ) then
	echo 'You also must be able to write the snapshots directory.'
 endif

#
#	Condense the version string into something usable
#

set version = ("`cat conf/version.variant`" "`cat  conf/version.edit`")
set version = "$version[1]$version[2]"

#
#	If the snapshot directory doesn't exist, create it
#

#if ( ! -d $SS/$version ) then
#	(cd $SS; rm -rf $version; mkdir $version)
# endif

#
#	Get the list of all top-level directories out of "ALL", and the list
#	of top-level files (other than RCSset and RCSlock) out of the RCS tree
#
#	The snapshot program cannot cope with non-existent files, so we
#	must build the list of top-level files carefully. The snapshot
#	program processes all the files in a directory and its subdirectories
#	so we must eliminate . and all subdirectories from the Directories/ALL
#	list.
#	
set dirs = (`sed -n -e '/^#/d' -e '/^\.$/d' -e '/^$/d' -e 's/^\.\///' -e '/\//d' -e 's/^/\.\//p' < Directories/ALL`)
set topfiles = (./Makeconf,v ./Makefile,v)

#
#	Create the master snapshot
#
mv -f $SS/ALL $SS/.ALL
rm -f $SS/*
set here=`pwd`
(cd RCS; $here/src/snapshot.csh -v -r'<>' -F$here/$SS/.ALL -f$here/$SS/ALL $topfiles $dirs)
rm -f $SS/.ALL

#
#	Create the subset snapshots
#
#	The snapshot program is pretty slow, so we use text processing
#	to save us the work.
#
#	[Feature: the ALL file contains top-level files, but none of
#	the subsets will, regardless whether they contain ".".]
#
foreach file ( Directories/* )
 set collection = $file:t
 if ("$collection" != "ALL") then

	#
	# These lines, in order
	#   eliminate comments and directory "."
	#   convert "." and "/" into "\." and "\/"
	#   add "^/" to the front and "\/[^\/]*$/p" to the end
	#
	# This gives us a file full of lines that look like:
	#	/^\.\/kern\/[^/]*$/p
	#	/^\.\/vax\/kdb\/[^/]*$/p
	#
	# That is, print lines that start with the appropriate
	# directory name, but contain no further directory
	# components.
	#
	sed -n -e '/^#/d' \
		-e 's/\./\\\./g' -e 's/\//\\\//g' \
		-e 's/^/\/\^/' -e 's/$/\\\/\[^\\\/\]\*\$\/p/p' \
		< Directories/$collection \
		> $SS/Snapshot.sed

	#
	# Use our new sed script to make the subset
	#
	sed -f $SS/Snapshot.sed -n \
		 < $SS/ALL \
		 > $SS/$collection \

	#
	# Clean up
	#
	rm -f $SS/Snapshot.sed

  endif

  # Check in snapshot file including ALL
  #
  rcs -l ./RCS/$SS/$collection,v
  rcs -N$version ./RCS/$SS/$collection,v
  rcsci -f -u -n$version -m"kernel version $version" ./RCS/$SS/$collection,v \
	$SS/$collection
 
 end
