#!/bin/sh -
#
# Copyright (c) 1994 Jan-Simon Pendry
# Copyright (c) 1994
#	The Regents of the University of California.  All rights reserved.
#
# %sccs.include.redist.sh%
#
#	%W% (Berkeley) %G%
#

whatdb=whatis.db
manconf=/etc/man.conf
augment=
manpath=

while getopts m:C:M:P: optch
do
	case $optch in
	m) augment=$OPTARG;;
	C) manconf=$OPTARG;;
	M) MANPATH=$OPTARG;;
	P) MANPATH=$OPTARG;;
	?) echo 'usage: apropos [-m dir ] [-C config] [-M dirpath] key ...' >&2
	   exit 1;;
	esac
done
shift $(($OPTIND - 1))

if test -z "$MANPATH"
then
	mfiles=$(sed -n -e 's/*#.*//' -e 's/^_whatdb[	 ]*//p' "$manconf")
else
	OIFS=$IFS IFS=":$IFS"
	for i in $MANPATH; do mfiles="$mfiles $i/$whatdb"; done
	IFS=$OIFS
fi

test -n "$augment" && mfiles="$augment/$whatdb $mfiles"

for i
do
	fgrep -h -i -e "$i" $mfiles
done
