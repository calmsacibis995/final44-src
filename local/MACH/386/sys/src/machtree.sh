#!/bin/sh
#
# Mach Operating System
# Copyright (c) 1989 Carnegie-Mellon University
# Copyright (c) 1988 Carnegie-Mellon University
# All rights reserved.  The CMU software License Agreement specifies
# the terms and conditions for use and redistribution.
#
#
# HISTORY
# $Log:	machtree.sh,v $
# Revision 2.14  89/08/28  22:46:01  af
# 	Added PMAX to machine case stmt.
# 	[89/08/28            af]
# 
# 	*** empty log message ***
# 	[89/08/28  22:37:59  af]
# 
# Revision 2.13  89/06/14  13:28:11  mrt
# 	Added -U switch  which causes the dates on the working files to
# 	match the dates in the archived files rather than be the current
# 	date.
# 	[89/06/14		mrt]
# 
# Revision 2.12  89/04/08  23:33:20  rpd
# 	Put back code to link sys to h, for pre-X77 kernels.
# 	Removed a bunch of progress messages from MACHINE creation;
# 	made it create MACHINE/mach and MACHINE/mach_debug.
# 	Create mach/machine and mach_debug/machine links.
# 	[89/03/14  15:00:25  rpd]
# 
# Revision 2.11  89/04/05  18:07:36  rvb
# 	The tree moved.
# 
# Revision 2.9  89/03/07  00:45:39  rpd
# 	Removed code that sets up the sys/ or h/ link;
# 	only sys/ exists now.
# 
# Revision 2.8  89/02/25  19:26:09  gm0w
# 	Changes for cleanup.
# 
# Revision 2.7  89/02/07  22:55:45  mwyoung
# Code cleanup cataclysm.
# 
# Revision 2.6  89/01/30  22:07:59  rpd
# 	Work around rcsco problem/bug when checking out Directories/.
# 	[89/01/23  15:15:18  rpd]
# 
# Revision 2.5  89/01/04  13:38:05  rpd
# 	Eliminated refs to unused ForceDirCheckOut variable.
# 	Fixed bug with specifying multiple dir sets.
# 	[88/12/30  21:38:42  rpd]
# 
# Revision 2.4  88/12/20  13:53:22  rpd
# 	Added -dir processing.  Won't create a custom Makeconf if one
# 	already exists.  Doesn't check out Directories if it already exists.
# 	[88/12/08  15:24:06  rpd]
# 	
# 	Changed KernelRCS/KernelLatest to reflect new locations.
# 	Changed default directories (ALL -> MI).
# 	Changed subdirectories of OBJS to be @sys types.
# 	Changed ibmrt_mach to rt_mach, leaving ibmrt_mach symlink.
# 	[88/12/08  11:33:36  rpd]
# 	
# 	Condensed log.  Changed -{no,}vice to -{no,}afs.
# 	Default CONFIG is STD+WS+EXP instead of STD+M+ANY+EXTRA.
# 	Sets up .BCSVBASE, .BCSBRANCH, .BCSconfig files.
# 	Uses @sys instead of @cputype.
# 	Gives warning message if dir name doesn't end in "/kernel".
# 	[88/11/26  21:37:08  rpd]
# 
# Revision 2.3  88/10/01  21:58:01  rpd
# 	Link RCSCONFIG to RCSconfig before checking out Directories.
# 	[88/09/29  01:08:41  rpd]
# 
# Revision 2.2  88/09/07  15:48:59  rpd
#	Bunches of modifications.
# 	
# 	Created from mwyoung's machtree.csh, with massive revisions.
# 	[88/09/07  01:55:42  rpd]
#

#
# A script to generate a complete set of kernel sources for any RCS
# configuration.  The result is a ready-to-compile directory, populated
# with RCS links, sources, and symbolic links for "machine" and "sys" (or "h").
#

# Our name, for warnings.
ProgName="`expr \"$0\" : '.*/\(.*\)' '|' \"$0\"`"

# Location of kernel RCS tree
KernelRCS=/afs/cs.cmu.edu/mach/rcs/kernel

# Location of kernel latest tree
KernelLatest=/afs/cs.cmu.edu/mach/src/kernel/latest

# Location of VERSIONS file
Versions="$KernelLatest/VERSIONS"

# Directories that we will process.
# -dir adds to this list.
# Normals args are sets of dirs from Directories/
# Defaults to "."
Dirs=

# -co sets CheckOut on; -noco sets CheckOut off
# -co is the default
CheckOut=yes

# -q sets Quiet on; -v sets Quiet off
# -v is the default
Quiet=

# -afs makes a AFS tree; -noafs makes a non-AFS tree
# if neither is specified, the script determines this
TreeInAFSSpecified=
TreeInAFS=

# -vpath <path> specifies a VPATH value to add to Makeconf
# the default is no VPATH
VPath=

# -i specifies interactice prompting; -f forces the default
# the default is -i
Force=

# -csuf <suffix> specifies a CONFIG_SUFFIX value to add to Makeconf
# the default is no CONFIG_SUFFIX
# -a specifies a suffix of .always
ConfigSuffix=

# -c <config> specifies a default configuration
# the default is STD+WS+EXP
DefaultConfig=STD+WS+EXP

# -b <version> specifies a base version
# the default is to prompt the user (unless Force)
BaseVersion=

# -n <name> specifies a branch name
# the default is to prompt the user (unless Force)
BranchName=

# -U sets date to date of file in rcs archive
# the default is to set the date to the current date and time
SetDate=

while [ "$#" -gt 0 ]; do
	case "$1" in
	  -help) echo "$ProgName: Summary of switches:";
		 echo "  -dir <dir>: specify a dir to process";
		 echo "  -co: check out subdirectories (default)";
		 echo "  -noco: don't check out subdirectories";
		 echo "  -q: be quiet";
		 echo "  -v: be verbose (default)";
		 echo "  -i: ask questions (default)";
		 echo "  -f: don't ask questions; use default answer";
		 echo "  -afs: make a AFS tree";
		 echo "  -noafs: make a non-AFS tree";
		 echo "  -vpath <path>: specify a VPATH";
		 echo "  -csuf <suffix>: specify a CONFIG_SUFFIX";
		 echo "  -a: specify CONFIG_SUFFIX=.always";
		 echo "  -c <config>: specify default CONFIG";
		 echo "  -b <version>: specify a base version";
		 echo "  -n <name>: specify a branch name";
		 echo "  -U: set date to date in rcs archive";
		 echo "  -help: this summary";
		 exit 0;;
	  -dir) shift;
		if [ "$1" = "." ]; then
			Dirs="$Dirs $1";
		elif expr "$1" : '\./' > /dev/null; then
			Dirs="$Dirs $1";
		else
			Dirs="$Dirs ./$1";
		fi
		shift;;
	  -co) CheckOut=yes; shift;;
	  -noco) CheckOut=; shift;;
	  -q) Quiet=yes; shift;;
	  -v) Quiet=; shift;;
	  -i) Force=; shift;;
	  -f) Force=yes; shift;;
	  -afs) TreeInAFSSpecified=yes; TreeInAFS=yes; shift;;
	  -noafs) TreeInAFSSpecified=yes; TreeInAFS=; shift;;
	  -vpath) shift; VPath="$1"; shift;;
	  -csuf) shift; ConfigSuffix="$1"; shift;;
	  -a) ConfigSuffix=.always; shift;;
	  -c) shift; DefaultConfig="$1"; shift;;
	  -b) shift; BaseVersion="$1"; shift;;
	  -n) shift; BranchName="$1"; shift;;
	  -U) shift; SetDate="-U"; shift;;
	  -*) echo "$ProgName: unrecognized switch $1 (try -help)" 1>&2; exit 1;;
	  *) break;;
	esac
done

#
# The b-style rcs cover program doesn't work properly
# unless the last component of the directory name is "kernel".
#

if [ "`expr \"\`pwd\`\" : '.*/\(.*\)'`" != kernel ]; then
	echo "$ProgName: WARNING: directory name not 'kernel'" 1>&2
fi

if [ ! "$TreeInAFSSpecified" ]; then
	if fs la . > /dev/null 2>&1; then
		if [ ! "$Quiet" ]; then echo "[ making an AFS tree ]"; fi
		TreeInAFS=yes
	else
		if [ ! "$Quiet" ]; then echo "[ making a non-AFS tree ]"; fi
		TreeInAFS=
	fi
fi

if [ -d RCS ]; then
	if [ ! "$Quiet" ]; then echo "[ RCS already exists ]"; fi
else
	default=yes;
	if [ "$Force" ]; then answer="$default"; else
		echo -n "Link RCS to $KernelRCS? [$default] "
		read answer
		if [ -z "$answer" ]; then answer="$default"; fi
	fi

	if [ "$answer" = "yes" ] || [ "$answer" = "y" ]; then
		if [ ! "$Quiet" ]; then echo "[ linking RCS to $KernelRCS ]"; fi
		ln -s "$KernelRCS" RCS
	fi

	if [ ! -d RCS ]; then
		echo "$ProgName: You must have an RCS directory" 1>&2
		exit 1
	fi
fi

if [ ! -d RCS/Directories ]; then
	echo "$ProgName: You must have an RCS/Directories directory" 1>&2
	exit 1
fi

if [ -r RCSconfig ]; then
	if [ ! "$Quiet" ]; then echo "[ RCSconfig already exists ]"; fi
else
	if [ ! "$BaseVersion" ]; then
		default="`awk '{ v = $1; } END { print v; }' \"$Versions\"`"
		if [ "$Force" ]; then answer="$default"; else
			echo -n "Base version? [$default] "
			read answer
			if [ -z "$answer" ]; then answer="$default"; fi
		fi
		BaseVersion="$answer"
	fi

	# for some reason, can't put "" around `awk ...`

	date=`awk 'BEGIN { mon["Jan"] = "01"; mon["Feb"] = "02"; mon["Mar"] = "03";
                           mon["Apr"] = "04"; mon["May"] = "05"; mon["Jun"] = "06";
                           mon["Jul"] = "07"; mon["Aug"] = "08"; mon["Sep"] = "09";
                           mon["Oct"] = "10"; mon["Nov"] = "11"; mon["Dec"] = "12"; }
                    $1 == "'"$BaseVersion"'" {
printf("%s/%s/%02d,%s\n", substr($8, 3, 2), mon[$4], $5, $6); }' "$Versions"`

	if [ -z "$date" ]; then
		echo "$ProgName: Unknown version $answer specified" 1>&2
		exit 1
	fi

	if [ ! "$BranchName" ]; then
		default="${USER}_${BaseVersion}"
		if [ "$Force" ]; then answer="$default"; else
			echo -n "Branch name? [$default] "
			read answer
			if [ -z "$answer" ]; then answer="$default"; fi
		fi
		BranchName="$answer"
	fi

	if [ ! "$Quiet" ]; then
		echo "[ creating RCSconfig ]"
		echo "[   branch: $BranchName ]"
		echo "[   date:   $date ($BaseVersion) ]"
		echo "[   vbase:  $KernelRCS ]"
	fi
	rm -f RCSconfig
	echo "$BranchName" >> RCSconfig
	echo "<$date" >> RCSconfig
	echo "-relative_to $KernelRCS" >> RCSconfig

	if [ ! "$Quiet" ]; then echo "[ linking RCSCONFIG to RCSconfig ]"; fi
	rm -f RCSCONFIG
	ln -s RCSconfig RCSCONFIG

	if [ ! "$Quiet" ]; then echo "[ creating .BCSVBASE ]"; fi
	rm -f .BCSVBASE
	echo "$KernelRCS" > .BCSVBASE

	if [ ! "$Quiet" ]; then echo "[ creating .BCSBRANCH ]"; fi
	rm -f .BCSBRANCH
	echo "$BranchName" > .BCSBRANCH

	if [ ! "$Quiet" ]; then echo "[ linking .BCSconfig-$BranchName to RCSconfig ]"; fi
	rm -f ".BCSconfig-$BranchName"
	ln -s RCSconfig ".BCSconfig-$BranchName"
fi

if [ -d Directories ]; then
	if [ ! "$Quiet" ]; then echo "[ Directories already exists ]"; fi
else
	if [ ! "$Quiet" ]; then echo "[ creating Directories ]"; fi
	rm -rf Directories
	mkdir Directories

	if [ ! "$Quiet" ]; then echo "[ linking Directories/RCSconfig to ../RCSCONFIG ]"; fi
	ln -s ../RCSCONFIG Directories/RCSconfig

	if [ ! "$Quiet" ]; then echo "[ linking Directories/RCS to ../RCS/Directories ]"; fi
	ln -s ../RCS/Directories Directories/RCS

	if [ ! "$Quiet" ]; then echo "[ checking out Directories ]"; fi
	(cd Directories; rcsco -q $SetDate RCS/*,v)
fi

if [ "$*" ]; then
	Dirs="$Dirs `(cd Directories; cat $@) | egrep -v '^#'`"
fi

if [ ! "$Dirs" ]; then
	Dirs="."
fi

echo "$Dirs" | tr -s ' ' '\12' | sort -u | awk '
{
  if (NF == 0) next;

  dots=""; dir = $1;
  for (i=0; i < length(dir); i++)
    if (substr(dir,i,1) == "/")
      dots = "../" dots;
  if (dots == "")
    dots = "/";
  if (substr(dir,1,2) == "./")
    dir = substr(dir,3,length(dir)-2);

  printf("%s %s\n", dots, dir);
}' | while read dots dir; do
	if [ -d "$dir" ]; then
		if [ "$dir" != "." ]; then
			if [ ! "$Quiet" ]; then echo "[ $dir already exists ]"; fi
		fi
	else
		if [ ! "$Quiet" ]; then echo "[ creating $dir ]"; fi
		rm -rf "$dir"
		mkdir "$dir"

		if [ ! "$Quiet" ]; then echo "[ linking $dir/RCSconfig to ${dots}RCSCONFIG ]"; fi
		ln -s "${dots}RCSCONFIG" "$dir/RCSconfig"

		if [ ! "$Quiet" ]; then echo "[ linking $dir/RCS to ${dots}RCS/$dir ]"; fi
		ln -s "${dots}RCS/$dir" "$dir/RCS"
	fi

	if [ "$CheckOut" ]; then
		(cd "$dir" &&
		 if [ ! -d RCS ]; then
			echo "$ProgName: WARNING: no access to $dir" 1>&2
			if [ ! "$Quiet" ]; then echo "[ skipping check out of $dir ]"; fi
		 elif [ "`echo RCS/*,v`" = "RCS/*,v" ]; then
			if [ ! "$Quiet" ]; then echo "[ no *,v files in $dir ]"; fi
		 else
			if [ ! "$Quiet" ]; then echo "[ checking out $dir ]"; fi
			rcsco -q $SetDate RCS/*,v
		 fi)
	else
		if [ ! "$Quiet" ]; then echo "[ skipping check out of $dir ]"; fi
	fi
done

if [ -f RCSlog ]; then
	if [ ! "$Quiet" ]; then echo "[ removing RCSlog ]"; fi
	rm -f RCSlog
fi
if [ -f RCSset ]; then
	if [ ! "$Quiet" ]; then echo "[ removing RCSset ]"; fi
	rm -f RCSset
fi

if [ -w Makeconf ]; then
	if [ ! "$Quiet" ]; then echo "[ custom Makeconf already exists ]"; fi
else
	if [ ! "$Quiet" ]; then echo "[ creating custom Makeconf ]"; fi
	rm -f Makeconf
	> Makeconf
	chmod o+w Makeconf

	if [ "$TreeInAFS" ]; then
		echo 'OBJECTDIR=OBJS/@sys' >> Makeconf
	fi
	if [ "$VPath" ]; then
		echo "VPATH=$VPath" >> Makeconf
	fi
	if [ "$ConfigSuffix" ]; then
		echo "CONFIG_SUFFIX=$ConfigSuffix" >> Makeconf
	fi
	if [ "$DefaultConfig" ]; then
		echo "CONFIG=$DefaultConfig" >> Makeconf
	fi
fi

if [ "$TreeInAFS" ]; then
	if [ ! -d OBJS ]; then
		if [ ! "$Quiet" ]; then echo "[ creating OBJS ]"; fi
		rm -rf OBJS
		mkdir OBJS
	fi
	if [ ! -d OBJS/vax_mach ]; then
		if [ ! "$Quiet" ]; then echo "[ creating OBJS/vax_mach ]"; fi
		rm -rf OBJS/vax_mach
		mkdir OBJS/vax_mach
	fi
	if [ ! -d OBJS/sun3_mach ]; then
		if [ ! "$Quiet" ]; then echo "[ creating OBJS/sun3_mach ]"; fi
		rm -rf OBJS/sun3_mach
		mkdir OBJS/sun3_mach
	fi
	if [ ! -d OBJS/rt_mach ]; then
		if [ ! "$Quiet" ]; then echo "[ creating OBJS/rt_mach ]"; fi
		rm -rf OBJS/rt_mach
		mkdir OBJS/rt_mach
		ln -s rt_mach OBJS/ibmrt_mach
	fi
fi

if [ -d h ] && [ ! -d sys ]; then
	if [ ! "$Quiet" ]; then echo "[ linking sys to h ]"; fi
	rm -f sys
	ln -s h sys
fi

if [ ! -d RCSTMP ]; then
	if [ ! "$Quiet" ]; then echo "[ creating RCSTMP ]"; fi
	rm -rf RCSTMP
	mkdir RCSTMP
	if [ "$TreeInAFS" ]; then
		fs sa RCSTMP kernel write
	else
		chmod a+w RCSTMP
	fi
fi

if [ "$TreeInAFS" ] && [ ! -d MACHINE ]; then
	if [ ! "$Quiet" ]; then echo "[ creating MACHINE ]"; fi
	rm -rf MACHINE
	mkdir MACHINE

	ln -s ../vax MACHINE/vax_mach
	ln -s ../ca MACHINE/rt_mach
	ln -s rt_mach MACHINE/ibmrt_mach
	ln -s ../sun3 MACHINE/sun3_mach

	if [ ! "$Quiet" ]; then echo "[ creating MACHINE/mach ]"; fi
	mkdir MACHINE/mach

	ln -s ../../mach/vax MACHINE/mach/vax_mach
	ln -s ../../mach/ca MACHINE/mach/rt_mach
	ln -s rt_mach MACHINE/mach/ibmrt_mach
	ln -s ../../mach/sun3 MACHINE/mach/sun3_mach

	if [ ! "$Quiet" ]; then echo "[ creating MACHINE/mach_debug ]"; fi
	mkdir MACHINE/mach_debug

	ln -s ../../mach_debug/vax MACHINE/mach_debug/vax_mach
	ln -s ../../mach_debug/ca MACHINE/mach_debug/rt_mach
	ln -s rt_mach MACHINE/mach_debug/ibmrt_mach
	ln -s ../../mach_debug/sun3 MACHINE/mach_debug/sun3_mach
fi

if [ ! "$TreeInAFS" ]; then
	case `/etc/machine` in
		VAX) machine_dir="vax";;

		IBMRT) machine_dir="ca";;

		SUN) machine_dir="sun3";;

		PMAX) machine_dir="mips";;

		*) echo "$ProgName: WARNING: current machine type unknown; using vax" 1>&2;
		   machine_dir="vax";;
	esac
fi

if [ ! -d machine ]; then
	if [ "$TreeInAFS" ]; then
		machine_dir="MACHINE/@sys"
	fi

	echo "[ linking machine to ${machine_dir} ]"
	rm -f machine
	ln -s "${machine_dir}" machine

	if [ ! -d machine ]; then
		echo "$ProgName: WARNING: proper 'machine' directory nonexistent" 1>&2
	fi
fi

if [ -d mach ] && [ ! -d mach/machine ]; then
	if [ "$TreeInAFS" ]; then
		machine_dir="../MACHINE/mach/@sys"
	fi

	echo "[ linking mach/machine to ${machine_dir} ]"
	rm -f mach/machine
	ln -s "${machine_dir}" mach/machine

	if [ ! -d mach/machine ]; then
		echo "$ProgName: WARNING: proper 'mach/machine' directory nonexistent" 1>&2
	fi
fi

if [ -d mach_debug ] && [ ! -d mach_debug/machine ]; then
	if [ "$TreeInAFS" ]; then
		machine_dir="../MACHINE/mach_debug/@sys"
	fi

	echo "[ linking mach_debug/machine to ${machine_dir} ]"
	rm -f mach_debug/machine
	ln -s "${machine_dir}" mach_debug/machine

	if [ ! -d mach_debug/machine ]; then
		echo "$ProgName: WARNING: proper 'mach_debug/machine' directory nonexistent" 1>&2
	fi
fi

exit 0
