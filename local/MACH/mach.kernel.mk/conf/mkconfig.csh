#!/bin/csh -f
#
# Mach Operating System
# Copyright (c) 1989 Carnegie-Mellon University
# All rights reserved.  The CMU software License Agreement specifies
# the terms and conditions for use and redistribution.
#
#
# HISTORY
# $Log:	mkconfig.csh,v $
# Revision 2.2  89/04/22  15:24:08  gm0w
# 	Created from root Makefile.
# 	[89/04/14            gm0w]
# 

set CONFIG="${argv[1]}"

shift argv

echo +${CONFIG} \
| \
cat ${argv} - ${argv} \
| \
sed -n \
    -e "/^+/{" \
      -e "s;[-+];#&;gp" \
        -e 't loop' \
      -e ': loop' \
	-e 'n' \
        -e '/^#/b loop' \
        -e '/^$/b loop' \
        -e 's;^\([^#]*\).*#[ 	]*<\(.*\)>[ 	]*$;\2#\1;' \
          -e 't not' \
        -e 's;\([^#]*\).*;#\1;' \
          -e 't not' \
      -e ': not' \
        -e 's;[ 	]*$;;' \
        -e 's;^\!\(.*\);\1#\!;' \
        -e 'p' \
        -e 't loop' \
	-e 'b loop' \
    -e '}' \
    -e "/^[^#]/d" \
    -e 's;	; ;g' \
    -e "s;^# *\([^ ]*\)[ ]*=[ ]*\[\(.*\)\].*;\1#\2;p" \
| \
awk '-F#' '\
part == 0 && $1 != "" {\
    m[$1]=m[$1] " " $2;\
    next;\
}\
part == 0 && $1 == "" {\
    for (i=NF;i>1;i--){\
	s=substr($i,2);\
	c[++na]=substr($i,1,1);\
	a[na]=s;\
    }\
    while (na > 0){\
	s=a[na];\
	d=c[na--];\
	if (m[s] == "") {\
	    f[s]=d;\
	} else {\
	    nx=split(m[s],x," ");\
	    for (j=nx;j>0;j--) {\
		z=x[j];\
		a[++na]=z;\
		c[na]=d;\
	    }\
	}\
    }\
    part=1;\
    next;\
}\
part != 0 {\
    if ($1 != "") {\
	n=split($1,x,",");\
	ok=0;\
	for (i=1;i<=n;i++) {\
	    if (f[x[i]] == "+") {\
		ok=1;\
	    }\
	}\
	if (NF > 2 && ok == 0 || NF <= 2 && ok != 0) {\
	    print $2; \
	}\
    } else { \
	print $2; \
    }\
}'
