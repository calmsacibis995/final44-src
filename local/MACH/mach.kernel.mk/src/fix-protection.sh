#!/bin/sh
#
# Mach Operating System
# Copyright (c) 1989 Carnegie-Mellon University
# All rights reserved.  The CMU software License Agreement specifies
# the terms and conditions for use and redistribution.
#
#
# HISTORY
# $Log:	fix-protection.sh,v $
# Revision 2.4  89/02/25  19:25:41  gm0w
# 	Changes for cleanup.
# 
# Revision 2.3  89/02/20  14:17:21  rpd
# 	Greatly simplified extraction of #ifndef/#define symbols.
# 	Now if the last code line is "#endif KERNEL" (or ASSEMBLER)
# 	then we omit the blank line between it and the final #endif.
# 
# Revision 2.2  89/02/19  21:35:45  rpd
# 	Created.
# 	[89/02/19  21:29:42  rpd]
# 

ident="${1-_FOOBAR_}"

# Protects header files against multiple inclusion.
# This means adding
#	#ifndef	SYMBOL
#	#define SYMBOL
#	...
#	#endif	SYMBOL
# around the code in the file.  The SYMBOL is given
# as an argument, and defaults to _FOOBAR_.
#
# If the header file is already protected, then
# the existing SYMBOL is just changed.  If the file
# doesn't contain code, but just comments, then
# no protection is added.
#
# Other desirable side effects:
#	Lines with just whitespace are changed into blank lines.
#	Blank lines at the beginning of the file are removed.
#	Blank lines at the end of the file are removed.
#
# Bugs:
#	The header file can't have code following a comment
#	and on the same line as the comment.  For example,
#		/*
#		 * comment
#		 */ int a = 0;
#	Actually, this is only a problem if the code is the
#	first code line in the file.
#
#	The header file must have balanced #if/#ifdef and #endif
#	cpp commands.  If this isn't true, we return non-zero.
#
#	If the header file's first code lines are
#		#ifndef	SYMBOL	/* possible stuff */
#		#define SYMBOL	/* possible stuff */
#	then this is interpreted as the start of protection,
#	without checking that no code lines follow the
#	corresponding #endif.  If this happens, we return non-zero.
#
# In general, we return zero if everything looks OK
# and non-zero if something is fishy.

awk '
BEGIN { scanstart = 1; ident = "'"$ident"'"; }
scanstart == 1 && /^[ 	]*\/\*/ {
	if (sawcomment) {
	    for (i = 0; i < blanklines; i++)
		printf("\n");
	}
	blanklines = 0;
	incomment = 1; sawcomment = 1;
	scanstart = 0;
    }
incomment == 1 { print; }
incomment == 1 && /\*\/[ 	]*$/ {
	incomment = 0; scanstart = 1;
	next;
    }
incomment == 1 { next; }
scanstart == 1 && /^[ 	]*$/ { blanklines++; next; }
scanstart == 1 && /^#ifndef/ {
	posident = $2;
	scanstart = 0;
	next;
    }
posident != 0 && /^#define/ {
	if (sawcomment)
	    printf("\n");
	printf("#ifndef\t%s\n", ident); ifcount++;
	printf("#define %s\n", ident);
	printf("\n");

	if ($2 != posident) {
	    printf("#ifndef\t%s\n", posident); ifcount++;
	    print;
	    sawcode = 1;
	}
	posident = 0; scancode = 1;
	blanklines = 0;
	next;
    }
posident != 0 {
	if (sawcomment)
	    printf("\n");
	printf("#ifndef\t%s\n", ident); ifcount++;
	printf("#define %s\n", ident);
	printf("\n");
	printf("#ifndef\t%s\n", posident); ifcount++;
	posident = 0; scancode = 1; sawcode = 1;
	blanklines = 0;
    }
scanstart == 1 {
	if (sawcomment)
	    printf("\n");
	printf("#ifndef\t%s\n", ident); ifcount++;
	printf("#define %s\n", ident);
	printf("\n");
	scanstart = 0; scancode = 1;
	blanklines = 0;
    }
scancode == 1 && /^#if/ { ifcount++; }
scancode == 1 && /^#endif/ {
	ifcount--;
	if (ifcount == 0) {
	    if (sawcode && !oldsawspecial)
		printf("\n");
	    printf("#endif\t%s\n", ident);
	    wanteof = 1; scancode = 0;
	    blanklines = 0;
	    next;
	} else if ($2 == "KERNEL" || $2 == "ASSEMBLER") {
	    sawspecial = 1;
	}
    }
scancode == 1 && /^[ 	]*$/ { blanklines++; next; }
scancode == 1 {
	if (sawcode) {
	    for (i = 0; i < blanklines; i++)
		printf("\n");
	}
	blanklines = 0;

	sawcode = 1;
	oldsawspecial = sawspecial;
	sawspecial = 0;

	print;
	next;
    }
wanteof == 1 && /^[ 	]*$/ { blanklines++; next; }
wanteof == 1 {
	barfed = 1;
	for (i = 0; i < blanklines; i++)
	    printf("\n");
	blanklines = 0;
	print;
	next;
    }
{
	barfed = 1;
	print;
}
END {
	if (ifcount == 1) {
	    if (sawcode && !oldsawspecial)
		printf("\n");
	    printf("#endif\t%s\n", ident); ifcount--;
	}
	if (ifcount != 0)
	    barfed = 1;
	exit barfed;
    }
'
