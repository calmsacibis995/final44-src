#!/bin/sh 
# $XConsortium: inspex.sh,v 5.6 91/07/08 18:12:04 hersh Exp $
###################################################################
# Copyright (c) 1989, 1990, 1991 by Sun Microsystems, Inc. and the X Consortium.
# 
#                         All Rights Reserved
# 
# Permission to use, copy, modify, and distribute this software and its 
# documentation for any purpose and without fee is hereby granted, 
# provided that the above copyright notice appear in all copies and that
# both that copyright notice and this permission notice appear in 
# supporting documentation, and that the names of Sun Microsystems,
# the X Consortium, and MIT not be used in advertising or publicity 
# pertaining to distribution of the software without specific, written 
# prior permission.  
# 
# SUN MICROSYSTEMS DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, 
# INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT 
# SHALL SUN MICROSYSTEMS BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL 
# DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
# WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
# ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
# SOFTWARE.
#
##################################################################




#============================================================
# inspex.sh - execution script for InsPEX, the PEX test suite
#============================================================

# Options:
# -display <display-name> makes the test run on the named display's server.
# -a <test-area-names>	The user may specify one or more specific test areas;
#			all subsequent arguments up to the next option flag
#			or the end of the line are taken to be test areas.
# -t <individ-tests>	Only runs specified tests - all following arguments
#			up to the next option flag are taken to be test
#			script names (with or without .c or .pi extension),
#			complete pathnames of tests, or of the form
#			areaname/testname.
# -keep			Keep executables for C-based tests after execution,
#			rather than removing them.  If executables are
#			very large, this option may eat up a lot of disk
#			space, but may be desireable for debugging.
# -clean		Before beginning test execution, empty out
#			the bin, lib, and tmp directories under
#			$INSPEXDEST in order to get a clean run.
#			This option is recommended if testing a new
#			version of the PEX library.
# -clean_all		This does all of the above, plus deletes
#			everything under $INSPEXDEST/include, where
#			pdt.h and wdt.h live.  This should only be
#			used if the user has not customized these files
#			under $INSPEXDEST to suit particular phigs
#			and workstation capabilities.
# -server_side, -client_side  These options will force server-side or
#			client-side structure storage, respectively,
#			in most tests.	The same result can be obtained by 
#			using the environment variables described below
#			(though these switches override the variables).


# Required Environment Variables:
#
# INSPEXHOME - Path to the InsPEX test suite's directory, where inspex.sh
#	and the associated subdirectories are.
# INSPEXDEST - Destination directory for test suite output.  Compilations,
#	new images, and log files are placed under this directory by
#	the test suite.  
# These are in addition to the other variables required for execution
# of a PEX or X program, such as PEXAPIDIR and DISPLAY.  Also 
# note: the suite requires that the X utility xdpyinfo is in the path
# (this is used strictly to diagnose the health of the server).

# Optional Environment Variables:
#
# INSPEXLOG - full pathname of log file, default "$INSPEXDEST/ilog.<date>"
# INSPEXIMAGEREF - master reference directory, default INSPEXHOME/refimages
# PEXLIBDIR, PEXINCDIR - directories containing the PEX includes and libs. 
#	These default to "../../lib/PEX" and "../../lib/PEX/include"
#	respectively (absolute paths are derived from these relative ones).
# XLIBDIR, XINCDIR - the directory containing the X library
#	libX11.a, and the directory containing the include
#	directory "X11".
# SERVER_RESTART_CMD - if the server dies during test execution,
#	and this variable is set, the script will attempt to use
#	the command to restart the server before continuing.
#	The command should exit after starting the server, since
#	the test script does not run it in the background.
#	Example: 
#	    csh% setenv SERVER_RESTART_CMD "mystartpex.csh; sleep 15"
# I_CFLAGS, I_LDFLAGS - these variables can be set to any required
#	additional compiler flags, for the compile & link phases
#	respectively; they will be used in the compilation of the
#	interpreter and C-based tests.  If there are multiple
#	words in these variables, they should be enclosed in both
#	single and double quotes so that the grouping isn't lost
#	when these are passed to make.
#	Example: csh% setenv I_LDFLAGS "'-Bstatic -f68881'"
#
# Optional environment variables used by many test programs
# (described more fully in the documentation):
#
# MAXFAIL - number of failures a test will accept before aborting
# VERBOSITY - Can be set to 0, 1, 2, or 3; specifies various
#	levels of tracing and diagnostic output.  The user guide
#	details the different values; The default (0) and 1 are
#	useful
# PAUSE - if set, rendering tests will pause after drawing and
# 	wait for a carriage return.  Not recommended if running 
#	tests through this script, but useful when running
#	a test program by itself.
# SHOWPIX - if set, some automatic rendering tests will show which pixels
# 	are being sampled.
# MACROPATH - interpreter scripts search this path for macros files.
#	default is .:$INSPEXHOME/testcases/shared, causing it to check
#	the current directory and then the directory containing
#	shared macro files.  You shouldn't need to set this unless
#	you want to substitute different macro definitions.
# I_CLIENT_SIDE - if set, will direct most tests to 
#	call popen_pex() with appropriate arguments to specify
#	client-side structure storage, rather than popen_phigs(),
#	which would give the default behavior, server-side storage.
# I_NO_MONITOR - although single-process execution (without phigsmon) is
#	not yet implemented, I_NO_MONITOR will cause most
#	tests to call popen_pex() with the flags set to
#	force this behavior, in a manner similar to I_CLIENT_SIDE.




#################################################
#		Test Area Functions		#	
#################################################

#set -x
#set -v

i_statectl()
{
	cd $INSPEXHOME/testcases/statectl
	list="systemst.pi wsst[12].pi structst.pi archivest.pi"
	for t in $list
	do
		i_exec $t
	done
}

i_utils()
{
	cd $INSPEXHOME/testcases/utils
	list="translate.pi scale.pi rotate.pi compmtx.pi buildtran.pi \
		comptran.pi tranpt.pi evalori.pi evalmap.pi"
	for t in $list
	do
		i_exec $t
	done
}

i_filter()
{
	cd $INSPEXHOME/testcases/filter
	list="highl.pi invis.pi pick.pi"
	for t in $list
	do
		i_exec $t
	done
}

i_archive()
{
	cd $INSPEXHOME/testcases/archive
	list="confres.pi archive.pi archstr.pi archnet.pi archall.pi \
		retrieve.pi retrstr.pi retrnet.pi retrall.pi deletear.pi \
		delstrar.pi delnetar.pi delallar.pi specar[1-4].pi \
		inqcfnet.pi inqallcf.pi retrances.pi retrdesc.pi"
	for t in $list
	do
		i_exec $t
	done
}

i_face()
{
	cd $INSPEXHOME/testcases/face
	list="cull1.pi cull2.pi"
	for t in $list
	do
		i_exec $t
	done
}

i_dcue()
{
	cd $INSPEXHOME/testcases/dcue
	list="dcue1.pi dcue2.pi"
	for t in $list
	do
		i_exec $t
	done
}

i_nurbs()
{
	cd $INSPEXHOME/testcases/nurbs
	list="nurbsc[1-3].pi nurbss[1-6].pi"
	for t in $list
	do
		i_exec $t
	done
}

i_triquad()
{
	cd $INSPEXHOME/testcases/triquad
	list="ts[1-6].pi qm[1-4].pi faswd[1-4].pi sofas[1-4].pi"
	for t in $list
	do
		i_exec $t
	done
}

i_light()
{
	cd $INSPEXHOME/testcases/light
	list="light[1-5].pi" 
	for t in $list
	do
		i_exec $t
	done
}

i_iss()
{
	cd $INSPEXHOME/testcases/iss
	list="iss[1-6].pi"
	for t in $list
	do
		i_exec $t
	done
}

i_search()
{
	cd $INSPEXHOME/testcases/search

 	list="elemsrch[1-4].pi" 
	for t in $list
	do
		i_exec $t 
	done
}

i_rep()
{
	cd $INSPEXHOME/testcases/rep

	list="edgerep.pi linerep.pi markerrep.pi colrep.pi textrep.pi \
		viewrep.pi patrep.pi interrep.pi dcuerep.pi lightrep.pi" 
	for t in $list
	do
		i_exec $t 
	done
}


i_pdtwdt()
{
	cd $INSPEXHOME/testcases/pdtwdt

	i_comp_and_run pdt 

	list="wdt1 wdt2 wdt3 wdt4 wdt5 wdt6"
	for t in $list
	do
		i_comp_and_run $t "CPPFLAGS=-DPHIGS_WS_TYPE_X_TOOL"
	done
}


i_xform()
{
	cd $INSPEXHOME/testcases/xform

 	list="wsxf[1-5].pi viewxf[1-5].pi modelxf[1-9].pi primxf[123].pi" 
	for t in $list
	do
		i_exec $t 
	done
}

i_dispctl()
{
	cd $INSPEXHOME/testcases/dispctl

 	list="redrawstr.pi updatews.pi dispupst[1-3].pi dccolrep.pi \
	      dcdelstr.pi dclinerep.pi dcrefmod.pi \
	      dcviewrep.pi"
	for t in $list
	do
		i_exec $t 
	done
}

i_fillarea()
{ 
	cd $INSPEXHOME/testcases/fillarea

 	list="fa[1-4].pi fas[1-8].pi"
	for t in $list
	do
		i_exec $t 
	done
}

i_text()
{
	cd $INSPEXHOME/testcases/text

 	list="tx[1-9].pi tx1[01].pi atx[1-9].pi atx1[01].pi"
	for t in $list
	do
		i_exec $t 
	done
}

i_input()
{
	cd $INSPEXHOME/testcases/input

 	list="loc[1-5].pi event[1-6].pi viewpri[12].pi val[12].pi stroke[12].pi\
		pick[1-9].pi pick10.pi string[12].pi choice[12].pi"
	for t in $list
	do
		i_exec $t 
	done
}

i_error()
{
	cd $INSPEXHOME/testcases/error

	list="errhandle1 errhandle2"
	for t in $list
	do
		i_comp_and_run $t 
	done
}

i_strcon()
{
	cd $INSPEXHOME/testcases/strcon
	list="*[1-9].pi"
	for t in $list
	do
		i_exec $t
	done

	list="copyall2"
	for t in $list
	do
		i_comp_and_run $t
	done

	# elemcon9 is compiled once and executed multiple times,
	# so that a core dump in one primitive doesn't kill
	# the whole set of tests.  These can be broken up differently
	# if core dumps do occur, so that all structure elements get
	# tested.

	# exit function if compile fails
	i_compile elemcon9  ||  return

	# Save value of I_KEEP_EXEC, set it to 1 so that
	# the executable is not deleted in between each run.
	OLD_KEEP_EXEC=$I_KEEP_EXEC
	I_KEEP_EXEC=1

	# test inquiry of element content for each structure element.
	i_run_executable elemcon9 1 2 3 4 5 6 
	i_run_executable elemcon9 7 8
	i_run_executable elemcon9 9 
	i_run_executable elemcon9 10 11
	i_run_executable elemcon9 12 13 14 15 16 17 18 19 20 
	i_run_executable elemcon9 21
	i_run_executable elemcon9 22 23 24 25 26 27 28 29 30 
	i_run_executable elemcon9 31 32 33 34 35 36 37 38 39 40
	i_run_executable elemcon9 41 42 
	i_run_executable elemcon9 43 44 
	i_run_executable elemcon9 45 46 47 48 49 50 
	i_run_executable elemcon9 51 52 53 54 55 56 57 59 60 
	i_run_executable elemcon9 58
	i_run_executable elemcon9 61 62 63 64 65 66 67 68
	i_run_executable elemcon9 69 70 71 72 73 74 75 76 77 78 79 80
	i_run_executable elemcon9 81
	i_run_executable elemcon9 82 83 84
	i_run_executable elemcon9 85 86
	i_run_executable elemcon9 87
	i_run_executable elemcon9 88
	i_run_executable elemcon9 89 90 91 92
	
	# restore old value before last testcase is run
	I_KEEP_EXEC=$OLD_KEEP_EXEC

	i_run_executable elemcon9 93
}

i_strman()
{
	cd $INSPEXHOME/testcases/strman
	list="delallst[12].pi delstnet[12].pi delstr[1-5].pi poststr[123].pi"
	for t in $list
	do
		i_exec $t
	done
}

i_poly()
{
	cd $INSPEXHOME/testcases/poly
	list="polyline[1234].pi pl_inher.pi \
	      polymark[1234].pi pm_inher.pi"
	for t in $list
	do
		i_exec $t
	done
}


i_plinedata()
{
	cd $INSPEXHOME/testcases/plinedata
	list="pldata1.pi pldata2.pi pldata3.pi pldata4.pi pld_inher.pi"
	for t in $list
	do
		i_exec $t
	done
}

#################################################
#      		Utility Functions		#	
#################################################


#
# i_server_check() - check that the server is still alive.
# Takes a single argument: name of the last test executed.
# if server doesn't respond and SERVER_RESTART_CMD is
# defined, attempt to use it to restart the server.  If it
# isn't defined, just abort.
# Return exit status 1 if server is restarted
#
i_server_check()
{
	if xdpyinfo >/dev/null
	then
	    echo server still alive >/dev/null
	else
	    echolog ERROR: server $DISPLAY not responding after test $*
	    # if a method for restarting the server is defined, use it.
	    if [ "$SERVER_RESTART_CMD" ]
	    then
		echolog attempting restart of server with command: $SERVER_RESTART_CMD
		echo $SERVER_RESTART_CMD | sh -s
		if xdpyinfo >/dev/null
		then
		    echolog server successfully restarted after $1 
		    return 1
		else
		    echolog ERROR: Attempt to restart server after $1 failed - aborting at `date`
		    exit
		fi
	    else
		echolog Aborting test suite at `date`
		exit
	    fi
		    
	fi

}


#
# i_exec() -  execute an interpreted test.
# Takes one argument, the name of a test script.
# (including extension)
i_exec()
{
	# remove any pre-existing core file
	rm -f core

	# test for existence of file
	if [ ! -f $1 ]
	then
	    echolog ERROR: could not find script !$
	    return 1
	fi

	# Execute the interpreter on the supplied script
	#echo "$INSPEXDEST/bin/pexint $1 2>&1 | tee -a $INSPEXLOG"
	$INSPEXDEST/bin/pexint $1 2>&1 | tee -a $INSPEXLOG

	# test for existence of core file
	if [ -f core ]
	then
	    echolog $1 FAILED: core dumped
	fi

	# test that server is still alive
	i_server_check $1
}

#
# i_comp_and_run() --  compile and execute a C-based test
# The first argument is the name of a C-based test
# (with or without .c extension).  Any additional arguments
# are passed along as additional "make" arguments.
#
i_comp_and_run()
{
	test_basename=`basename $1 .c`
	if i_compile $* 
	then
		i_run_executable $test_basename
	fi

}

# i_compile() - compile a C-based test.  A single argument
# is required, the name of the test (with or without .c extension).
# Any additional arguments are passed on as args to make.
# Note that it cleans up after itself, even removing the .c file.
i_compile()
{
	test_basename=`basename $1 .c`
	if [ ! -f $INSPEXDEST/tmp/${test_basename}.c ]
	then
	    case $1 in
	    *.c)
		cp $1 $INSPEXDEST/tmp
		;;
	   *)
	    	cp $1.c $INSPEXDEST/tmp
		;;
	    esac
	fi
	startdir=`pwd`
	cd  $INSPEXDEST/tmp
	if [ ! -f Makefile ] 
	then
		cp $INSPEXHOME/testcases/shared/Makefile .
	fi
	shift   # so that any remaining args (make flags) are $*

	# don't crowd the log file with successful make commands
	pwd
	make_cmd="make $CDEBUGFLAGS $test_basename $* PEXINCDIR=$PEXINCDIR PEXLIBDIR=$PEXLIBDIR XINCDIR=$XINCDIR XLIBDIR=$XLIBDIR I_CFLAGS=$I_CFLAGS I_LDFLAGS=$I_LDFLAGS "
	echo "cd $INSPEXDEST/tmp ; $make_cmd"
	if sh -c "$make_cmd" > make.out 2>&1
	then
		#rm -f make.out ${test_basename}.o ${test_basename}.c
		cd $startdir
	else
		echolog "Make of $test_basename FAILED, with output:"
		cat make.out | tee -a $INSPEXLOG
		#rm -f $test_basename.o $test_basename.c $test_basename
		cd $startdir
		return 1
	fi
}

# i_run_executable() - run an already-compiled executable,
# check whether it dumped core or killed the server.
# First argument should be the program; any others
# are passed on as arguments.
i_run_executable()
{
	startdir=`pwd`

	# execute the command
	cd $INSPEXDEST/tmp
	$* 2>&1 | tee -a $INSPEXLOG

	# remove the .o and .c file, and the executable if required
	# rm -f $1.o $1.c 
	#if [ $I_KEEP_EXEC = 0 ]
	#then
	#	rm -f $1
	#fi

	# test for existence of core file
	if [ -f core ]
	then
	    echolog $* "FAILED: core dumped (removing)"
	    rm core
	fi

	# test that server is still alive
	i_server_check $1

	cd $startdir

}

# i_testfind() - used in i_individual_test() below.  Given
# a wild-carded path, i_testfind will determine whether it expanded
# to more than one path (ambiguous test name), or failed to expand
# (meaning test not found using wildcarded path).
i_testfind()
{
	if [ $# = 1 ]
	then
		if [ -f $1 ]
		then    # a single file was found
			return 0
		else	# wildcard did not expand to real filename
			return 1
		fi
	else   # wildcard expanded to more than one
		echolog ERROR: ambiguous test name could be any of: $*
		return 2
	fi
}

# i_individual_test() - run an individual test script or program.
# Single argument is the test name, with our without extension,
# and may be either an absolute path, testname alone, or of the form
# areadir/testname, where areadir is the name of a test area.
i_individual_test()
{
	indtest=$1

	case $indtest in
	*/*.pi)  
	    # interpreter script with specified path
	    if [ -f $indtest ]
	    then 
		i_exec $indtest   # path was complete
	    elif [ -f $INSPEXHOME/testcases/$indtest ]
	    then
		i_exec $INSPEXHOME/testcases/$indtest  # was areaname/testname
	    else
		echolog ERROR: could not find test $indtest - skipping
	    fi
	    ;;
	*.pi)    
	    # script with no path: find it here or in testcases dir
	    if [ -f $indtest]
	    then
	       i_exec $indtest  # was in current directory
	    elif i_testfind $INSPEXHOME/testcases/*/$indtest
	    then
		i_exec $INSPEXHOME/testcases/*/$indtest
	    else
		   echolog ERROR: could not find test $indtest - skipping
	    fi
	    ;;
	*/*.c)
	    # C test with specified path
	    if [ -f $indtest ]
	    then   # path was complete
		i_comp_and_run $indtest   "CPPFLAGS=-DPHIGS_WS_TYPE_X_TOOL"
	    elif [ -f $INSPEXHOME/testcases/$indtest ]
	    then   # was in form areaname/testname
		i_comp_and_run $INSPEXHOME/testcases/$indtest "CPPFLAGS=-DPHIGS_WS_TYPE_X_TOOL"
	    else
		echolog ERROR: could not find test $indtest - skipping
	    fi
	    ;;
	*.c)
	    # C prog with no path: find it here or in testcases dir
	    if [ -f $indtest ]
	    then   # was in current directory
	       i_comp_and_run $indtest  "CPPFLAGS=-DPHIGS_WS_TYPE_X_TOOL"
	    elif i_testfind $INSPEXHOME/testcases/*/$indtest
	    then   # was in a testcase directory
		i_comp_and_run $INSPEXHOME/testcases/*/$indtest "CPPFLAGS=-DPHIGS_WS_TYPE_X_TOOL"
	    else
		echolog ERROR: could not find test $indtest - skipping
	    fi	   
	    ;;
	*)  
	    # test of unknown filetype - we will look for scripts
	    # first, since auto translation can leave .c's around
	    # with same name.
	    if [ -f ${indtest}.pi ]
	    then   # script in current dir or with full path
		i_exec ${indtest}.pi
	    elif [ -f ${indtest}.c ]
	    then   # C prog in current dir or with full path
		i_exec ${indtest}.c
	    elif [ -f $INSPEXHOME/testcases/${indtest}.pi ]
	    then   # script in areaname/testcase form
		i_exec $INSPEXHOME/testcases/${indtest}.pi
	    elif [ -f $INSPEXHOME/testcases/${indtest}.c ]
	    then   # C program in areaname/testcase form
		i_comp_and_run $INSPEXHOME/testcases/${indtest}.c "CPPFLAGS=-DPHIGS_WS_TYPE_X_TOOL"
	    elif i_testfind $INSPEXHOME/testcases/*/${indtest}.pi
	    then   # script in testcase dir
		i_exec $INSPEXHOME/testcases/*/${indtest}.pi
	    elif [ $? = 2 ]
	    then   # more than one script matches
		echolog ERROR: skipping ambiguous test $indtest
	    elif i_testfind $INSPEXHOME/testcases/*/${indtest}.c 
	    then   # C program in testcase dir
		i_comp_and_run $INSPEXHOME/testcases/*/${indtest}.c "CPPFLAGS=-DPHIGS_WS_TYPE_X_TOOL"
	    elif [ $? = 2 ]
	    then
		echolog ERROR: skipping ambiguous test $indtest
	    else
		echolog ERROR: could not find test $indtest - skipping
	    fi
	    ;;
	esac
}

#outputs month and day
smalldate()
{
	echo `date +%m\.%d\.%H""%M`
}

#prints message on terminal and in log
echolog()
{
	echo "$*" | tee -a $INSPEXLOG
}

#################################################
#      		Main Procedure			#	
#################################################
# main() 

INSPEXVERSION="5.2" ; export INSPEXVERSION
umask 0
RM=/bin/rm ; export RM

#
# Test for required environment variables
#
if [ ! "$INSPEXDEST" ] ; then
	echo Must define environment variable INSPEXDEST
	exit 1
elif [ ! "$INSPEXHOME" ] ; then
	echo Must define environment variable INSPEXHOME
	exit 1
fi

if [ ! "$INSPEXIMAGEREF" ] ; then
	INSPEXIMAGEREF=$INSPEXHOME/refimages ; export INSPEXIMAGEREF
fi



#
# initialize flags
#
DEBUG_OPT= ; export DEBUG_OPT
I_KEEP_EXEC=0; export I_KEEP_EXEC
unset ADDING_AREAS
unset ADDING_TESTS

#
# process cmd line args
#
while [ "$*" ]
do
    case $1 in
    -display)
        shift
        DISPLAY=$1; export DISPLAY
	unset ADDING_TESTS ; unset ADDING_AREAS
        shift
	;;
    -a)
	# subsequent non-flag arguments will be added to AREALIST
	unset ADDING_TESTS
	ADDING_AREAS=1
        shift
	;;
    -t)
	# subsequent non-flag arguments will be added to TESTLIST
	unset ADDING_AREAS
	ADDING_TESTS=1
        shift
	;;
    -clean)
	# dirs bin, lib, & tmp will be cleaned out under INSPEXDEST
	I_CLEAN=1; export I_CLEAN
	unset ADDING_TESTS ; unset ADDING_AREAS
	shift
	;;
    -clean_all)
	# above, plus include dir under INSPEXDEST will be cleaned out.
	I_CLEAN_ALL=1; export I_CLEAN_ALL
	unset ADDING_TESTS ; unset ADDING_AREAS
	shift
	;;
    -keep)
	# C-based test executables will be kept
	I_KEEP_EXEC=1; export I_KEEP_EXEC
	unset ADDING_TESTS ; unset ADDING_AREAS
	shift
	;;
    -server_side)
	unset I_CLIENT_SIDE
	unset ADDING_TESTS ; unset ADDING_AREAS
	shift
	;;
    -client_side)
	I_CLIENT_SIDE=1; export I_CLIENT_SIDE
	unset ADDING_TESTS ; unset ADDING_AREAS
	shift
	;;
    -*)
	echo ERROR -- unknown flag, $1
	exit 1
	;;
    *)
	if [ $ADDING_AREAS ] ; then
		# add this argument to test area list
		AREALIST="$AREALIST $1"; export AREALIST
	elif [ $ADDING_TESTS ] ; then
		# add this argument to test list
		TESTLIST="$TESTLIST $1"; export TESTLIST
	else
		echo ERROR -- unknown argument, $1
		exit 1
	fi
	shift
	;;
    esac;
done

DATE=`date`
export DATE

# Set a macropath if none defined; interpreter will use
# this path to search for macro files loaded with "source" command.
if [ ! "$MACROPATH" ]
then
	MACROPATH=.:$INSPEXHOME/testcases/shared ; export MACROPATH
fi

# create name for log file if not set; if the file already
# exists, name it to <name>.old
if [ ! "$INSPEXLOG" ]
then
	INSPEXLOG=$INSPEXDEST/ilog`smalldate` 
fi
export INSPEXLOG

if [ -f $INSPEXLOG ]
then
	mv $INSPEXLOG $INSPEXLOG.old
fi


echolog "The InsPEX Test Suite $INSPEXVERSION" 
echolog "Run started on "`date`
echolog  Running on client machine `hostname`
if [ "$DISPLAY" ]
then
	echolog Using display $DISPLAY
else
	echolog Using default display, unix:0 
	DISPLAY=unix:0 ; export DISPLAY
fi
echolog Test results going into log file $INSPEXLOG


# The X utility xdpyinfo is used to test for existence of server.
# To see whether the command itself was actually found, we
# check whether the output file was ever created.  This
# requires deleting any pre-existing copy.
rm -f $INSPEXDEST/display_info
if [ -f $INSPEXDEST/display_info ] 
then
	echolog ERROR - could not delete file $INSPEXDEST/display_info
	echolog please delete it and restart suite
	exit 1
fi

if xdpyinfo -display $DISPLAY > $INSPEXDEST/display_info
then
	echolog server is responding - xdpyinfo output in display_info
else
	if [ -f $INSPEXDEST/display_info ] 
	then
		# the program ran but failed
		echolog ERROR - server $DISPLAY not responding: aborting
		exit 1
	else
		# xdpyinfo didn't generate any output so didn't run
		echolog ERROR - could not execute required X utility xdpyinfo
		exit 1
	fi
fi

# record presence of I_CLIENT_SIDE in log
if [ -n "$I_CLIENT_SIDE" ]
then
	echolog I_CLIENT_SIDE is set - client side storage will be used
else
	echolog I_CLIENT_SIDE is not set - server side storage will be used
fi

# create directories in $INSPEXDEST if they don't exist
dirlist="bin lib tmp include currimages localrefimages"
for d in $dirlist
do
	if [ ! -d $INSPEXDEST/$d ]
	then
		mkdir $INSPEXDEST/$d
	fi
done

# clean out directories if requested
if [ -n "$I_CLEAN_ALL" -o -n "$I_CLEAN" ]
then
	echolog emptying dirs bin, lib, tmp under INSPEXDEST
	rm -f $INSPEXDEST/bin/*
	rm -f $INSPEXDEST/lib/*
	rm -f $INSPEXDEST/tmp/*
	if [ -n "$I_CLEAN_ALL" ]
	then
		echolog emptying directory include under INSPEXDEST
		rm -f $INSPEXDEST/include/*
	fi
fi

# copy pdt.h and wdt.h into $INSPEXEST/include if they
# aren't already there
for incfile in pdt.h wdt.h
do
	if [ ! -f $INSPEXDEST/include/$incfile ]
	then	
		cp $INSPEXHOME/include/$incfile $INSPEXDEST/include
	fi
done

#
# Set or confirm required directory variables
#
if [ ! "$PEXINCDIR" ]
then
	default=../../../X11
	if [ -d $default ]
	then
		if [ -d $default/phigs ]
		then
			# it's good - get an absolute path
			PEXINCDIR=`cd $default; pwd`; export PEXINCDIR
		else
			echolog ERROR - no directory phigs found under default PEXINCDIR $default - must be set manually
			exit 1
		fi
	else 
	     echolog ERROR - default PEXINCDIR not found - must be set manually
	     exit 1
	fi
else  			# make sure phigs directory exists
	if [ ! -d $PEXINCDIR/phigs ]
	then
	    echolog ERROR - value for PEXINCDIR incorrect - no directory phigs found under $PEXINCDIR
	    exit 1
	fi
fi

if [ ! "$PEXLIBDIR" ]
then
	default=../../lib/PEX
	if [ -d $default ]
	then
		# get an absolute path
		PEXLIBDIR=`cd $default; pwd`; export PEXLIBDIR
	else 
	     echolog ERROR - default PEXLIBDIR $default not found - must be set manually
	     exit 1
	fi
else  # make sure directory exists
	if [ ! -d $PEXLIBDIR ]
	then
	    echolog ERROR - value for PEXLIBDIR incorrect - $PEXLIBDIR not found
	    exit 1
	fi
fi

# X directories default to the PEX ones...
if [ ! "$XINCDIR" ]
then
	default=$PEXINCDIR
	if [ -d $default ]
	then
		if [ -d $default ]
		then
			# it's good -get an absolute path
			XINCDIR=`cd $default; pwd`; export XINCDIR
		else
			echolog ERROR - no directory X11 found under default XINCDIR $default - must be set manually
			exit 1
		fi
	else 
	     echolog ERROR - default XINCDIR not found - must be set manually
	     exit 1
	fi
else  			# make sure X11 directory exists
	if [ ! -d $XINCDIR ]
	then
	    echolog ERROR - value for XINCDIR incorrect - no directory X11 found under $XINCDIR
	    exit 1
	fi
fi

if [ ! "$XLIBDIR" ]
then
	default=$PEXLIBDIR
	if [ -d $default ]
	then
		# get an absolute path
		XLIBDIR=`cd $default; pwd`; export XLIBDIR
	else 
	     echolog ERROR - default XLIBDIR $default not found - must be set manually
	     exit 1
	fi
else  # make sure directory exists
	if [ ! -d $XLIBDIR ]
	then
	    echolog ERROR - value for XLIBDIR incorrect - directory $XLIBDIR not found
	    exit 1
	fi
fi

echolog "PEX include directory:       " $PEXINCDIR
echolog "PEX lib directory:           " $PEXLIBDIR
echolog "X include directory:         " $XINCDIR
echolog "X lib directory:             " $XLIBDIR
echolog "InsPEX home directory:       " $INSPEXHOME
echolog "InsPEX destination directory:" $INSPEXDEST
echolog "Image reference directory:   " $INSPEXIMAGEREF

# User may use these to add to compiler flags if desired.
if [ -n "$I_CFLAGS" ]
then
	echolog User-supplied CFLAGS: $I_CFLAGS
else
	I_CFLAGS= ; export I_CFLAGS
fi
if [ -n "$I_LDFLAGS" ]
then
	echolog User-supplied LDFLAGS: $I_LDFLAGS
else
	I_LDFLAGS= ; export I_LDFLAGS
fi

cd $INSPEXHOME/tools/pexint
# the CPPFLAGS=-DNEWT is required when compiling interpreter!
MAKE_CMD="make CPPFLAGS='-DNEWT' PEXINCDIR=$PEXINCDIR PEXLIBDIR=$PEXLIBDIR XINCDIR=$XINCDIR XLIBDIR=$XLIBDIR I_CFLAGS=$I_CFLAGS I_LDFLAGS=$I_LDFLAGS pexint"
echolog $MAKE_CMD 
# We would pipe the make output into "tee", but it masks the return status.
if sh -c "$MAKE_CMD" > $INSPEXDEST/bin/make.out  2>&1
then
	echo removing log of make >/dev/null
	#rm $INSPEXDEST/bin/make.out
else
	echolog ERROR: make of pexint failed, with output:
	cat $INSPEXDEST/bin/make.out | tee -a $INSPEXLOG
	echolog ABORTING -- could not make interpreter 
	exit 1
fi


cd $INSPEXDEST
rm -f core

if [ "$TESTLIST" ]
then
    echolog -------------- Running Individual Tests --------------
    echolog "test list: $TESTLIST" 
    for indtest in $TESTLIST
    do
	i_individual_test $indtest
    done
fi

if [ -n "$AREALIST" -o -z "$TESTLIST" ] 
then
    # some or all test areas are to be executed
    if [ "$AREALIST" ]
    then
	echolog Test will include test areas:  $AREALIST 
    else
	AREALIST="statectl utils rep xform dispctl fillarea search \
                 text strcon strman poly plinedata archive face dcue \
		 nurbs triquad light iss error pdtwdt filter input";\
		 export AREALIST
    fi

    for a in $AREALIST
    do
        echolog "-------- Starting test area $a --------" 
        case $a in
        search)
	    i_search
	    ;;
        statectl)
	    i_statectl
	    ;;
	utils)
	    i_utils
	    ;;
	filter)
	    i_filter
	    ;;
	xform)
	    i_xform
	    ;;
	archive)
	    i_archive
	    ;;
	face)
	    i_face
	    ;;
	dcue)
	    i_dcue
	    ;;
	nurbs)
	    i_nurbs
	    ;;
	triquad)
	    i_triquad
	    ;;
	light)
	    i_light
	    ;;
	iss)
	    i_iss
	    ;;
	pdtwdt)
	    i_pdtwdt
	    ;;
	rep)
	    i_rep
	    ;;
	dispctl)
	    i_dispctl
	    ;;
	fillarea)
	    i_fillarea
	    ;;
	text)
	    i_text
	    ;;
	input)
	    i_input
	    ;;
	error)
	    i_error
	    ;;
	strcon)
	    i_strcon
	    ;;
	strman)
	    i_strman
	    ;;
	poly)
	    i_poly
	    ;;
	plinedata)
	    i_plinedata
	    ;;
         *)
            echo "Unknown test area: $a"
            exit 1;
    	;;
        esac
    done        
fi

echolog "InsPEX run completed on " `date`  
