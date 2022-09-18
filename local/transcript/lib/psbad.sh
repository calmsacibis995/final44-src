#! /bin/sh
# dummy entry for unavailable filters
# RCSID: $Header: psbad.sh,v 1.1 85/11/24 12:14:02 shore Exp $

# argv is: psbad filtername user host
prog=`basename $0`
filter=$1
printer=$2
user=$3
host=$4

cat <<bOGUSfILTER
%!
72 720 moveto /Courier-Bold findfont 10 scalefont setfont
(lpd: ${printer}: filter \"$filter\" not available [$user $host].)show 
showpage

bOGUSfILTER
exit 0
