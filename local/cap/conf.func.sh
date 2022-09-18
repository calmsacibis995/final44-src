#!/bin/sh
# $Author: cck $ $Date: 88/05/19 13:09:24 $
# $Header: conf.func.sh,v 1.9 88/05/19 13:09:24 cck Rel $
# $Revision: 1.9 $
#
# CAP function configuration script.  This ain't perfect, but it's a start
# execute with /bin/sh Configure if your system won't run it (ksh is okay
# too).
#
# Takes a function description list and outputs a set of cpp or m4 defines
#  that tell us whether the various items are defined
# 
# Usage: Conf.func.sh <name list> <function list> ["m4"|"cpp] <output>
#  m4 - causes m4 output, cpp - cpp output
#  <namelist> of library or libraries to search for function defs
#  function list file in following format:
#  comments start with "# "
#   First field: type - see below
#   Second field: define name
#   Third field: name of include file
#   Fourth field: function name to lookup in name list
#   Fifth field: Reason for needing it
#
# type is one of:
# AND condition
#  A+ - postive match: must match conditions
#  A- - negative match: mustn't match conditions
# OR condition
#  O+ - postive match: must match conditions
#  O- - negative match: mustn't match conditions
# negative and postive matches are conditions on a "N" line
#  N+ - last entry in a list of needed matches: output true definition
#  N- - last entry in a list of needed matches: output false definition
#  N+- - says to output a true if match else false definition
#  N-+ - is the reverse of N+-
# by outputting true or false - it means outputting an uncommented
# vs. commented definition
#  N - last entry in a list of needed matches: output nothing
#  E - End of list - default value: don't output definition
#  
# Conf.func.sh does the following:
#   If C, then keep going until next N line matching "N" line
#   iff all preceeding "C" lines match
#   If "N" line has matched, scan to next "E" line
#   If no "N" lines match, then put commented defintion out and
#     tell via comment
#
NLIST=$1
FLIST=$2
OTYPE=$3
OFILE=$4
# debug option - don't bother compiling if set
FULLCHECK=$5
fullcheck=1
if [ -n "${FULLCHECK}" ]; then fullcheck=0; fi
# see if they gave us a grep
if [ -z "$PGREP" ]; then
  PGREP=grep
fi
if [ -z "${OFILE}" ]; then
  echo "No output file"
  exit 255
fi
if [ "$OTYPE" != "m4" -a "$OTYPE" != "cpp" ]; then
  echo "Type out of output must be m4 or cpp"
  exit 255
fi
if [ "$OTYPE" = "m4" ]; then
 m4out=1
fi
if [ ! -f ${FLIST} ]; then
  echo "Function list ${FLIST} not found"
  exit 255
fi
if [ ! -f ${NLIST} ]; then
  echo "Name list ${NLIST} not found"
  exit 255
fi
echo
echo "Conf.func.sh - find what functions cap wants are available"
echo "Tries to do this by reading the list ${FLIST} that tells"
echo "what functions to look for and the necessary include files."
echo
echo "Names are searched from the namelist passed in ${NLIST}"
echo "produced by nm.  If a function is found in the name list,"
echo "a simple program is compiled and loaded to ensure that it is there."
echo
echo "Analyzing name list output"
grep "Symbols from" < ${NLIST} > /dev/null 2>/dev/null
rc=$?
if [ $rc -eq 0 ]; then
 echo "nm output has \"Symbols from\" in it, assuming"
 echo "System V style, will grep for function name followed by space"
 gc=" "
else
 echo "BSD style, will grep for function name at end of the line"
 gc="$"
fi
echo
if [ $fullcheck -eq 1 ]; then
 echo "Temporary files: /tmp/cfs$$.c, /tmp/cfs$$"
else
 echo "Won't compile, because we are testing"
fi
if [ -f ${OFILE} ]; then
 echo Will overwrite ${OFILE}
else
 echo Will create ${OFILE}
fi
echo
echo "[Hit carriage return to continue]"
read ans
trap "
echo Exiting... Wait
if [ -f /tmp/cfs$$.c ]; then rm -f /tmp/cfs$$.c; fi
if [ -f /tmp/cfs$$ ]; then rm -f /tmp/cfs$$; fi
exec < /dev/tty
IFS=$oldifs
exit 255
" 2
exec < ${FLIST}
# save file seperators
oldifs=$IFS
IFS="${IFS},"
# foundit takes three values:
#  0 - include and/or call not found
#  1 - found a "N" entry
#  2 - found entry for a "C+","C-" line
#  3 - bad match on a "C+" or "C-"
foundit=0
echo
if [ -f ${OFILE} ]; then
 rm ${OFILE}
 echo Overwriting ${OFILE}
else
 echo Creating ${OFILE}
fi
echo
while read type what inc call comment
do
# comment
 if [ -z "$type" -o "$type" = "#" ]; then
  continue;
 fi
# map x to empty
 if [ "$call" = "x" ]; then call=""; fi
 if [ "$inc" = "x" ]; then inc=""; fi
 if [ -n "$call" ]; then callmsg="${call} - "; else callmsg="" ; fi
# end of list
 if [ "$type" = "E" ]; then
  if [ $fullcheck -eq 0 ]; then echo "At end: $foundit"; fi
   if [ $foundit -ne 1 ]; then
         echo Defaulting to "$comment"
   fi
   foundit=0
   continue
 fi
 case "$type" in
  "N"|"N+"|"N-"|"N+-"|"N-+")
    ;;
  "A+"|"A-")
# check conditions failed
     if [ ${foundit} -eq 3 -o ${foundit} -eq 1 ]; then continue; fi
    ;;
  "O-"|"O+")
# if foundit is 2, then a matching condition, since we are or
# we just continue.  1 implies previous n match in group and so
# continue there too
     if [ ${foundit} -eq 2 -o ${foundit} -eq 1 ]; then continue; fi
    ;;
  *) continue;;
 esac
# if foundit is 2, then we have a good continuation sequence
 if [ $foundit -eq 2 ]; then
   also="Also c"
 else
   also="C"
 fi
# if foundit is one, then we have matched a previous "N" line
# and output is always commented
# also the case when the previous line was a condition that failed
# if foundit 3 and we have "N" then reset foundit
 if [ $foundit -eq 3 -o $foundit -eq 1 ]; then
   case "$type" in
    "N+"*|"N-"*)
     if [ $m4out ]; then
       echo "# ${callmsg}${comment}" >> ${OFILE}
       echo "# define([X_${what}],1)" >> ${OFILE}
     else
       echo "/* # define ${what} */ /* ${callmsg}${comment} */" >> ${OFILE}
     fi
     if [ $foundit -eq 3 ]; then foundit=0 ; fi
     continue
   esac
 fi
# now to the guts
# just to pretty print
 if [ -n "${inc}" -o -n "${call}" ]; then
  if [ -n "${call}" -a -n "${inc}" ]; then
   echo "${also}hecking for existence of ${call} and ${inc}"
  else
   echo "${also}hecking for existence of ${call}${inc}"
  fi
 fi
# if include there or empty
 good=1
 if [ -z "${inc}" -o -f "${inc}" ]; then good=0; fi
# if call and include okay
 if [ $good -eq 0 ]; then
   if [ -n "${call}" ]; then 
     ${PGREP} "${call}${gc}" < ${NLIST} 2>/dev/null >/dev/null
     good=$?
     if [ $fullcheck -eq 1 ]; then
       if [ $good -eq 0 ]; then
 	 echo "main(){$call();}" > /tmp/cfs$$.c
	 cc -o /tmp/cfs$$ /tmp/cfs$$.c >/dev/null 2>/dev/null
	 good=$?
       else
	echo "$call not found in namelist"
       fi
     fi
   else
    good=0
   fi
 fi
 msg=""
 if [ -n "$call" ]; then msg="$call "; fi
 if [ -n "$msg" ]; then msg="${msg}and "; fi
 if [ -n "$inc" ]; then msg="${msg}${inc} "; fi
 if [ -n "$msg" ]; then msg="${msg}for "; fi
 if [ $good -eq 0 ]; then
   case "${type}" in
    "A+"|"O+") echo "TRUE: match $msg$comment"; foundit=2;;
    "A-"|"O-") echo "FALSE: match $msg$comment"; foundit=3;;
    *) echo "Found $msg$comment"; foundit=1 ;;
   esac
 else
   case "${type}" in
    "A+"|"O+") echo "FALSE: no match $msg$comment"; foundit=3;;
    "A-"|"O-") echo "TRUE: no match $msg$comment"; foundit=2;;
    *) ;;
   esac
 fi
# output match
 if [ $foundit -eq 1 ]; then
   case "$type" in 
     "N+"*)
       if [ $m4out ]; then
         echo "# ${callmsg}${comment}" >> ${OFILE}
         echo "define([X_${what}],1)" >> ${OFILE}
       else
         echo "# define ${what}	/* ${callmsg}${comment} */" >> ${OFILE}
       fi
     ;;
     "N-"*)
       if [ $m4out ]; then
         echo "# ${callmsg}${comment}" >> ${OFILE}
         echo "# define([X_${what}],1)" >> ${OFILE}
       else
         echo "/* # define ${what} */	/* ${callmsg}${comment} */" >> ${OFILE}
       fi
     ;;
   esac
   continue
 else
# failed: output second
   if [ "$type" = "N-+" ]; then
     if [ $m4out ]; then
       echo "# ${callmsg}${comment}" >> ${OFILE}
       echo "define([X_${what}],1)" >> ${OFILE}
     else
       echo "# define ${what}	/* ${callmsg}${comment} */" >> ${OFILE}
     fi
   fi
   if [ "$type" = "N+-" ]; then
     if [ $m4out ]; then
       echo "# ${callmsg}${comment}" >> ${OFILE}
       echo "# define([X_${what}],1)" >> ${OFILE}
     else
       echo "/* # define ${what} */	/* ${callmsg}${comment} */" >> ${OFILE}
     fi
   fi
 fi
done
IFS=$oldifs
trap 2
rm -f /tmp/cfs$$.c /tmp/cfs$$
exec < /dev/tty
