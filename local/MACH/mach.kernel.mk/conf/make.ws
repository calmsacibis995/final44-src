#! /bin/sh
#
# Mach Operating System
# Copyright (c) 1989 Carnegie-Mellon University
# All rights reserved.  The CMU software License Agreement specifies
# the terms and conditions for use and redistribution.
#
#
# HISTORY
# $Log:	make.ws,v $
# Revision 2.5  89/02/25  17:41:39  gm0w
# 	Changes for cleanup.
# 
# Revision 2.4  88/07/20  16:23:26  rpd
# Don't change PATH.  Instead, pick up omerge & makesym as arguments.
# (Default location is ../bin/.)  Note new version of makesym is needed
# for longer names in the symbol table.
# 
# Revision 2.3  88/07/15  15:56:05  mja
# Import ../conf/fixsyms in $4 and ../mach/rdb.h on $5 so that they can be
# sought by make along VPATH when necessary.
# 
# 11-Jun-88  Michael Young (mwyoung) at Carnegie-Mellon University
#	Take source directory name as a fifth argument.
#
# 23-Jun-87  William Bolosky (bolosky) at Carnegie-Mellon University
#	Changed completion message.
#
# 27-Apr-87  Bill Bolosky (bolosky) at Carnegie-Mellon University
#	Removed useless acis "cross-compile" code, and also now look
#	at the contents of "romp_rdb.h" to decide if we really need
#	to do a debugger merge.
#
# 11-Nov-86  Robert Baron (rvb) at Carnegie-Mellon University
#	set kernel back to segment e
#

#set -x$-
#$ Source: /afs/cs.cmu.edu/unix/source/rcs/kernel/conf/make.ws,v $
#
# shell script to generate a workstation binary with the debugger and
# symbol table merged in.
#
#
# this version deals with only the native compile case.
#
input=${1-vmunix}
output=${3-$input.ws}
fixsyms=${4-../conf/fixsyms}
rdbh=${5-../machine/rdb.h}
omerge=${6-../bin/omerge}
makesym=${7-../bin/makesym}

rm -f $output

case `cat romp_rdb.h` in
*0*)
		# no debugger merge needed
	ln $input $output
	echo "Debugger not configured, so not merged."
	exec true
	;;
*)		# native compile
	VMRDB=${2-../standca/rdb.out}
	nm -n $input > $input.nm || exit 1
	;;

esac

	echo "symbol table produced in $input.nm"

	rm -f $input.out
	cp $input $input.out
#
# get the offsets and positions of the debugger 
#
eval `awk ' $1 == "#define" { print $2 "=" substr($3,3) } ' $rdbh `
# make a vmunix.out that is -N format (vax compatible)
	$omerge -p2048 -o0x${RDB_RELOC?} -e0x${RDB_END?} ${VMRDB} $input.out || exit 1
# convert NCS symbols if necessary
$fixsyms $input.nm $input.snm
# following sed makes the 'int' routines visable and also changes the
# virtual kernel addresses back into real addresses
	( sed -e 's;^e;0;' -e 's; int; _int;' $input.snm ) |
		$makesym -h > $input.sym
	$omerge -p2048 -o0x${RDB_SYMTAB?} -l0x${RDB_SYMLEN?} $input.sym $input.out || exit 1
	echo "debugger (from ${VMRDB}) merged into $input.out"

	ln $input.out $output

	echo "Mach kernel with debugger now in $output"

