h42919
s 00013/00002/00305
d D 8.7 95/05/11 19:54:30 mckusick 11 10
c involve the preprocessor so that incorrect argument counts are detected
e
s 00010/00008/00297
d D 8.6 95/02/14 10:32:51 cgd 10 9
c include the copyright in the output files.
e
s 00012/00012/00293
d D 8.5 94/10/09 20:40:25 mckusick 9 8
c update for cleaner operation from cgd
e
s 00008/00006/00297
d D 8.4 94/08/11 14:40:41 mckusick 8 7
c better formatting (from cgd)
e
s 00238/00342/00065
d D 8.3 94/08/10 22:41:36 mckusick 7 6
c more portable version (from cgd)
e
s 00001/00001/00406
d D 8.2 94/08/05 16:41:00 mckusick 6 5
c inline => __inline (from cgd)
e
s 00002/00002/00405
d D 8.1 93/06/10 21:57:38 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00155/00071/00252
d D 7.4 92/07/17 17:16:54 heideman 4 3
c put redundant stuff in subroutines; add WILLRELE support
e
s 00004/00004/00319
d D 7.3 92/07/06 17:16:50 bostic 3 2
c make header clearer
e
s 00193/00013/00130
d D 7.2 92/07/06 17:12:48 bostic 2 1
c generate vnode_if.c as well
e
s 00143/00000/00000
d D 7.1 92/07/03 01:41:03 mckusick 1 0
c date and time created 92/07/03 01:41:03 by mckusick
e
u
U
t
T
I 1
#!/bin/sh -
D 10
#
D 5
# Copyright (c) 1992 The Regents of the University of California.
# All rights reserved.
E 5
I 5
D 9
# Copyright (c) 1992, 1993
E 9
I 9
# Copyright (c) 1992, 1993, 1994
E 9
#	The Regents of the University of California.  All rights reserved.
E 5
#
# %sccs.include.redist.sh%
#
D 7
#	%W% (Berkeley) %G%
E 7
I 7
D 9
# from: $NetBSD: vnode_if.sh,v 1.4.2.1 1994/07/15 22:32:01 cgd Exp $
E 9
I 9
# from: $NetBSD: vnode_if.sh,v 1.7 1994/08/25 03:04:28 cgd Exp $
E 9
E 7
#
E 10
I 10
copyright='
/*
D 11
 * Copyright (c) 1992, 1993, 1994
E 11
I 11
 * Copyright (c) 1992, 1993, 1994, 1995
E 11
 *	The Regents of the University of California.  All rights reserved.
 *
 * %sccs.include.redist.sh%
 *
 * from: NetBSD: vnode_if.sh,v 1.7 1994/08/25 03:04:28 cgd Exp $
 */
'
E 10
I 7
SCRIPT_ID='%W% (Berkeley) %G%'
E 7

# Script to produce VFS front-end sugar.
I 2
#
# usage: vnode_if.sh srcfile
#	(where srcfile is currently /sys/kern/vnode_if.src)
#
D 7
# These awk scripts are not particularly well written, specifically they
# don't use arrays well and figure out the same information repeatedly.
# Please rewrite them if you actually understand how to use awk.  Note,
D 4
# they use nawk extensions.
E 4
I 4
# they use nawk extensions and gawk's toupper.
E 7
E 4
E 2

D 2
cat << END_OF_LEADING_COMMENT
E 2
I 2
if [ $# -ne 1 ] ; then
D 4
	printf 'usage: vnode_if.sh srcfile\n'
E 4
I 4
	echo 'usage: vnode_if.sh srcfile'
E 4
	exit 1
fi

# Name of the source file.
D 7
SRC=$1
E 7
I 7
src=$1
E 7

# Names of the created files.
D 7
CFILE=vnode_if.c
HEADER=vnode_if.h
E 7
I 7
out_c=vnode_if.c
out_h=vnode_if.h
E 7

I 4
D 7
# Awk program (must support nawk extensions and gawk's "toupper")
# Use "awk" at Berkeley, "gawk" elsewhere.
AWK=awk
E 7
I 7
# Awk program (must support nawk extensions)
# Use "awk" at Berkeley, "nawk" or "gawk" elsewhere.
awk=${AWK:-awk}
E 7

E 4
D 7
# Print out header information for vnode_if.h.
cat << END_OF_LEADING_COMMENT > $HEADER
E 7
I 7
# Does this awk have a "toupper" function? (i.e. is it GNU awk)
isgawk=`$awk 'BEGIN { print toupper("true"); exit; }' 2>/dev/null`

# If this awk does not define "toupper" then define our own.
if [ "$isgawk" = TRUE ] ; then
	# GNU awk provides it.
	toupper=
else
	# Provide our own toupper()
	toupper='
function toupper(str) {
	_toupper_cmd = "echo "str" |tr a-z A-Z"
	_toupper_cmd | getline _toupper_str;
	close(_toupper_cmd);
	return _toupper_str;
}'
fi

#
# This is the common part of all awk programs that read $src
# This parses the input for one function into the arrays:
#	argdir, argtype, argname, willrele
# and calls "doit()" to generate output for the function.
#
# Input to this parser is pre-processed slightly by sed
# so this awk parser doesn't have to work so hard.  The
# changes done by the sed pre-processing step are:
#	insert a space beween * and pointer name
#	replace semicolons with spaces
#
sed_prep='s:\*\([^\*/]\):\* \1:g
s/;/ /'
awk_parser='
# Comment line
/^#/	{ next; }
# First line of description
/^vop_/	{
	name=$1;
	argc=0;
	next;
}
# Last line of description
/^}/	{
	doit();
	next;
}
# Middle lines of description
{
	argdir[argc] = $1; i=2;
	if ($2 == "WILLRELE") {
		willrele[argc] = 1;
		i++;
	} else
		willrele[argc] = 0;
D 8
	argtype[argc] = $i; i++;
E 8
I 8
D 9
	argtype[argc] = "";
E 9
I 9
	argtype[argc] = $i; i++;
E 9
E 8
	while (i < NF) {
D 8
		argtype[argc] = argtype[argc]" "$i;
E 8
I 8
D 9
		argtype[argc] = argtype[argc]$i;
		if (substr($i, length($i), 1) != "*")
			argtype[argc] = argtype[argc]" ";
E 9
I 9
		argtype[argc] = argtype[argc]" "$i;
E 9
E 8
		i++;
	}
	argname[argc] = $i;
	argc++;
	next;
}
'

# This is put after the copyright on each generated file.
warning="
E 7
E 2
/*
D 3
 * This file is produced by the script /sys/kern/vnode_if.sh.
E 3
I 3
D 7
 * This file is produced automatically.
E 3
 * Do not modify anything in here by hand.
E 7
I 7
 * Warning: This file is generated automatically.
 * (Modifications made here may easily be lost!)
E 7
 *
D 3
 *	%W% (Berkeley) %G%
E 3
I 3
D 7
 * Created from %W% (Berkeley) %G%
E 7
I 7
 * Created by the script:
 *	${SCRIPT_ID}
E 7
E 3
 */
I 7
"
E 7
I 2

I 9
# Get rid of ugly spaces
space_elim='s:\([^/]\*\) :\1:g'
E 9
I 7

#
# Redirect stdout to the H file.
#
echo "$0: Creating $out_h" 1>&2
exec > $out_h

# Begin stuff
echo "$copyright"
echo "$warning"
echo '
E 7
E 2
extern struct vnodeop_desc vop_default_desc;
D 7
END_OF_LEADING_COMMENT
E 7
I 7
'
E 7

D 7
# Awk script to take vnode_if.src and turn it into vnode_if.h.
D 2
#
# This script is not particularly well written, it figures out the
# same stuff repeatedly.  Feel free to fix it.  Note, it uses nawk
# extensions.

E 2
D 4
awk '
E 4
I 4
$AWK '
E 4
	NF == 0 || $0 ~ "^#" {
		next;
E 7
I 7
# Body stuff
# This awk program needs toupper() so define it if necessary.
sed -e "$sed_prep" $src | $awk "$toupper"'
function doit() {
	# Declare arg struct, descriptor.
	printf("\nstruct %s_args {\n", name);
D 8
	printf("\tstruct vnodeop_desc * a_desc;\n");
E 8
I 8
D 9
	printf("\tstruct vnodeop_desc *a_desc;\n");
E 9
I 9
	printf("\tstruct vnodeop_desc * a_desc;\n");
E 9
E 8
	for (i=0; i<argc; i++) {
D 8
		printf("\t%s a_%s;\n", argtype[i], argname[i]);
E 8
I 8
D 9
		printf("\t%sa_%s;\n", argtype[i], argname[i]);
E 9
I 9
		printf("\t%s a_%s;\n", argtype[i], argname[i]);
E 9
E 8
E 7
	}
D 7
	{
D 2
		# get the function name
E 2
I 2
		# Get the function name.
E 2
		name = $1;
		uname = toupper(name);
E 7
I 7
	printf("};\n");
	printf("extern struct vnodeop_desc %s_desc;\n", name);
	# Define inline function.
D 11
	printf("static __inline int %s(", toupper(name));
E 11
I 11
	printf("#define %s(", toupper(name));
	for (i=0; i<argc; i++) {
		printf("%s", argname[i]);
		if (i < (argc-1)) printf(", ");
	}
	printf(") _%s(", toupper(name));
	for (i=0; i<argc; i++) {
		printf("%s", argname[i]);
		if (i < (argc-1)) printf(", ");
	}
	printf(")\n");
	printf("static __inline int _%s(", toupper(name));
E 11
	for (i=0; i<argc; i++) {
		printf("%s", argname[i]);
		if (i < (argc-1)) printf(", ");
	}
	printf(")\n");
	for (i=0; i<argc; i++) {
D 8
		printf("\t%s %s;\n", argtype[i], argname[i]);
E 8
I 8
D 9
		printf("\t%s%s;\n", argtype[i], argname[i]);
E 9
I 9
		printf("\t%s %s;\n", argtype[i], argname[i]);
E 9
E 8
	}
D 8
	printf("{\n\tstruct %s_args a;\n", name);
E 8
I 8
D 9
	printf("{\n\tstruct %s_args a;\n\n", name);
E 9
I 9
	printf("{\n\tstruct %s_args a;\n", name);
E 9
E 8
	printf("\ta.a_desc = VDESC(%s);\n", name);
	for (i=0; i<argc; i++) {
		printf("\ta.a_%s = %s;\n", argname[i], argname[i]);
	}
	printf("\treturn (VCALL(%s%s, VOFFSET(%s), &a));\n}\n",
		argname[0], arg0special, name);
}
BEGIN	{
	arg0special="";
}
END	{
	printf("\n/* Special cases: */\n#include <sys/buf.h>\n");
	argc=1;
	argtype[0]="struct buf *";
	argname[0]="bp";
	arg0special="->b_vp";
	name="vop_strategy";
	doit();
	name="vop_bwrite";
	doit();
}
D 9
'"$awk_parser"
E 9
I 9
'"$awk_parser" | sed -e "$space_elim"
E 9
E 7

D 2
		# get the function arguments
E 2
I 2
D 7
		# Get the function arguments.
E 2
		for (c1 = 0;; ++c1) {
			if (getline <= 0)
				exit
			if ($0 ~ "^};")
				break;
			a[c1] = $0;
		}
E 7
I 7
# End stuff
echo '
/* End of special cases. */'
E 7

D 2
		# print out the vop_F_args structure
E 2
I 2
D 7
		# Print out the vop_F_args structure.
E 2
		printf("struct %s_args {\n\tstruct vnodeop_desc *a_desc;\n",
		    name);
		for (c2 = 0; c2 < c1; ++c2) {
			c3 = split(a[c2], t);
			printf("\t");
D 4
			for (c4 = 2; c4 < c3; ++c4)
E 4
I 4
			if (t[2] ~ "WILLRELE")
				c4 = 3;
			else 
				c4 = 2;
			for (; c4 < c3; ++c4)
E 4
				printf("%s ", t[c4]);
			beg = match(t[c3], "[^*]");
			printf("%sa_%s\n",
			    substr(t[c4], 0, beg - 1), substr(t[c4], beg));
		}
		printf("};\n");
E 7

D 2
		# print out extern declaration
E 2
I 2
D 7
		# Print out extern declaration.
E 2
		printf("extern struct vnodeop_desc %s_desc;\n", name);
E 7
I 7
#
# Redirect stdout to the C file.
#
echo "$0: Creating $out_c" 1>&2
exec > $out_c
E 7

D 2
		# print out inline struct
E 2
I 2
D 7
		# Print out inline struct.
E 2
D 6
		printf("static inline int %s(", uname);
E 6
I 6
		printf("static __inline int %s(", uname);
E 6
		sep = ", ";
		for (c2 = 0; c2 < c1; ++c2) {
			if (c2 == c1 - 1)
				sep = ")\n";
			c3 = split(a[c2], t);
			beg = match(t[c3], "[^*]");
			end = match(t[c3], ";");
			printf("%s%s", substr(t[c3], beg, end - beg), sep);
		}
		for (c2 = 0; c2 < c1; ++c2) {
			c3 = split(a[c2], t);
			printf("\t");
D 4
			for (c4 = 2; c4 < c3; ++c4)
E 4
I 4
			if (t[2] ~ "WILLRELE")
				c4 = 3;
			else
				c4 = 2;
			for (; c4 < c3; ++c4)
E 4
				printf("%s ", t[c4]);
			beg = match(t[c3], "[^*]");
			printf("%s%s\n",
			    substr(t[c4], 0, beg - 1), substr(t[c4], beg));
		}
		printf("{\n\tstruct %s_args a;\n\n", name);
		printf("\ta.a_desc = VDESC(%s);\n", name);
		for (c2 = 0; c2 < c1; ++c2) {
			c3 = split(a[c2], t);
			printf("\t");
			beg = match(t[c3], "[^*]");
			end = match(t[c3], ";");
			printf("a.a_%s = %s\n",
			    substr(t[c3], beg, end - beg), substr(t[c3], beg));
		}
		c1 = split(a[0], t);
		beg = match(t[c1], "[^*]");
		end = match(t[c1], ";");
		printf("\treturn (VCALL(%s, VOFFSET(%s), &a));\n}\n",
		    substr(t[c1], beg, end - beg), name);
D 2
	}'
E 2
I 2
	}' < $SRC >> $HEADER
E 2

I 2
# Print out header information for vnode_if.c.
cat << END_OF_LEADING_COMMENT > $CFILE
/*
D 3
 * This file is produced by the script /sys/kern/vnode_if.sh.
E 3
I 3
 * This file is produced automatically.
E 3
 * Do not modify anything in here by hand.
 *
D 3
 *	%W% (Berkeley) %G%
E 3
I 3
 * Created from %W% (Berkeley) %G%
E 3
 */

E 7
I 7
# Begin stuff
echo "$copyright"
echo "$warning"
echo '
E 7
#include <sys/param.h>
#include <sys/mount.h>
#include <sys/vnode.h>

struct vnodeop_desc vop_default_desc = {
	0,
	"default",
	0,
	NULL,
	VDESC_NO_OFFSET,
	VDESC_NO_OFFSET,
	VDESC_NO_OFFSET,
I 4
	VDESC_NO_OFFSET,
E 4
	NULL,
};
I 7
'
E 7

D 7
END_OF_LEADING_COMMENT
E 7
I 7
# Body stuff
sed -e "$sed_prep" $src | $awk '
function do_offset(typematch) {
	for (i=0; i<argc; i++) {
		if (argtype[i] == typematch) {
			printf("\tVOPARG_OFFSETOF(struct %s_args, a_%s),\n",
				name, argname[i]);
			return i;
		};
	};
	print "\tVDESC_NO_OFFSET,";
	return -1;
}
E 7

D 7
# Awk script to take vnode_if.src and turn it into vnode_if.c.
D 4
awk '
E 4
I 4
$AWK 'function kill_surrounding_ws (s) {
		sub (/^[ \t]*/, "", s);
		sub (/[ \t]*$/, "", s);
		return s;
E 7
I 7
function doit() {
	# Define offsets array
	printf("\nint %s_vp_offsets[] = {\n", name);
	for (i=0; i<argc; i++) {
		if (argtype[i] == "struct vnode *") {
			printf ("\tVOPARG_OFFSETOF(struct %s_args,a_%s),\n",
				name, argname[i]);
		}
E 7
	}
D 7

	function read_args() {
		numargs = 0;
		while (getline ln) {
			if (ln ~ /}/) {
				break;
			};
	
			# Delete comments, if any.
			gsub (/\/\*.*\*\//, "", ln);
			
			# Delete leading/trailing space.
			ln = kill_surrounding_ws(ln);
	
			# Pick off direction.
			if (1 == sub(/^INOUT[ \t]+/, "", ln))
				dir = "INOUT";
			else if (1 == sub(/^IN[ \t]+/, "", ln))
				dir = "IN";
			else if (1 == sub(/^OUT[ \t]+/, "", ln))
				dir = "OUT";
			else
				bail("No IN/OUT direction for \"" ln "\".");

			# check for "WILLRELE"
			if (1 == sub(/^WILLRELE[ \t]+/, "", ln)) {
				rele = "WILLRELE";
E 7
I 7
	print "\tVDESC_NO_OFFSET";
	print "};";
	# Define F_desc
	printf("struct vnodeop_desc %s_desc = {\n", name);
	# offset
	printf ("\t0,\n");
	# printable name
	printf ("\t\"%s\",\n", name);
	# flags
	printf("\t0");
	vpnum = 0;
	for (i=0; i<argc; i++) {
		if (willrele[i]) {
			if (argdir[i] ~ /OUT/) {
				printf(" | VDESC_VPP_WILLRELE");
E 7
			} else {
D 7
				rele = "WONTRELE";
E 7
I 7
				printf(" | VDESC_VP%s_WILLRELE", vpnum);
E 7
			};
D 7
	
			# kill trailing ;
			if (1 != sub (/;$/, "", ln)) {
				bail("Missing end-of-line ; in \"" ln "\".");
			};
	
			# pick off variable name
			if (!(i = match(ln, /[A-Za-z0-9_]+$/))) {
				bail("Missing var name \"a_foo\" in \"" ln "\".");
			};
			arg = substr (ln, i);
			# Want to <<substr(ln, i) = "";>>, but nawk cannot.
			# Hack around this.
			ln = substr(ln, 1, i-1);
	
			# what is left must be type
			# (put clean it up some)
			type = ln;
			gsub (/[ \t]+/, " ", type);   # condense whitespace
			type = kill_surrounding_ws(type);
	
			# (boy this was easier in Perl)
	
			numargs++;
			dirs[numargs] = dir;
			reles[numargs] = rele;
			types[numargs] = type;
			args[numargs] = arg;
		};
E 7
I 7
			vpnum++;
		}
E 7
	}
I 7
	print ",";
	# vp offsets
	printf ("\t%s_vp_offsets,\n", name);
	# vpp (if any)
	do_offset("struct vnode **");
	# cred (if any)
	do_offset("struct ucred *");
	# proc (if any)
	do_offset("struct proc *");
	# componentname
	do_offset("struct componentname *");
	# transport layer information
	printf ("\tNULL,\n};\n");
}
END	{
	printf("\n/* Special cases: */\n");
	argc=1;
	argdir[0]="IN";
	argtype[0]="struct buf *";
	argname[0]="bp";
	willrele[0]=0;
	name="vop_strategy";
	doit();
	name="vop_bwrite";
	doit();
}
D 9
'"$awk_parser"
E 9
I 9
'"$awk_parser" | sed -e "$space_elim"
E 9
E 7

D 7
	function generate_operation_vp_offsets() {
		printf ("int %s_vp_offsets[] = {\n", name);
		# as a side effect, figure out the releflags
		releflags = "";
		vpnum = 0;
		for (i=1; i<=numargs; i++) {
			if (types[i] == "struct vnode *") {
				printf ("\tVOPARG_OFFSETOF(struct %s_args,a_%s),\n",
					name, args[i]);
				if (reles[i] == "WILLRELE") {
					releflags = releflags "|VDESC_VP" vpnum "_WILLRELE";
				};
				vpnum++;
			};
		};
		sub (/^\|/, "", releflags);
		print "\tVDESC_NO_OFFSET";
		print "};";
	}
	
	function find_arg_with_type (type) {
		for (i=1; i<=numargs; i++) {
			if (types[i] == type) {
				return "VOPARG_OFFSETOF(struct " name "_args,a_" args[i] ")";
			};
		};
		return "VDESC_NO_OFFSET";
	}
	
	function generate_operation_desc() {
		printf ("struct vnodeop_desc %s_desc = {\n", name);
		# offset
		printf ("\t0,\n");
		# printable name
		printf ("\t\"%s\",\n", name);
		# flags
		vppwillrele = "";
		for (i=1; i<=numargs; i++) {
			if (types[i] == "struct vnode **" &&
				(reles[i] == "WILLRELE")) {
				vppwillrele = "|VDESC_VPP_WILLRELE";
			};
		};
		if (releflags == "") {
			printf ("\t0%s,\n", vppwillrele);
		} else {
			printf ("\t%s%s,\n", releflags, vppwillrele);
		};
		# vp offsets
		printf ("\t%s_vp_offsets,\n", name);
		# vpp (if any)
		printf ("\t%s,\n", find_arg_with_type("struct vnode **"));
		# cred (if any)
		printf ("\t%s,\n", find_arg_with_type("struct ucred *"));
		# proc (if any)
		printf ("\t%s,\n", find_arg_with_type("struct proc *"));
		# componentname
		printf ("\t%s,\n", find_arg_with_type("struct componentname *"));
		# transport layer information
		printf ("\tNULL,\n};\n");
	}
E 7
I 7
# End stuff
echo '
/* End of special cases. */'
E 7

E 4
D 7
	NF == 0 || $0 ~ "^#" {
		next;
	}
	{
		# get the function name
		name = $1;
E 7
I 7
# Add the vfs_op_descs array to the C file.
# Begin stuff
echo '
struct vnodeop_desc *vfs_op_descs[] = {
	&vop_default_desc,	/* MUST BE FIRST */
	&vop_strategy_desc,	/* XXX: SPECIAL CASE */
	&vop_bwrite_desc,	/* XXX: SPECIAL CASE */
'
E 7

D 7
		# get the function arguments
D 4
		for (c1 = 0;; ++c1) {
			if (getline <= 0)
				exit
			if ($0 ~ "^};")
				break;
			a[c1] = $0;
		}
E 4
I 4
		read_args();
E 4

		# Print out the vop_F_vp_offsets structure.  This all depends
		# on naming conventions and nothing else.
D 4
		printf("int %s_vp_offsets[] = {\n", name);
		for (c2 = 0; c2 < c1; ++c2) {
			c3 = split(a[c2], t);
			if (c3 != 4 || t[1] !~ /^IN$/ || t[2] !~ /^struct$/ ||
			    t[3] !~ /^vnode$/ || t[4] !~ /.*vp;$/)
				continue;
			beg = match(t[c3], "[^*]");
			end = match(t[c3], ";");
			printf("\tVOPARG_OFFSETOF(struct %s_args, a_%s),\n",
			    name, substr(t[4], beg, end - beg));
		}
		printf("\tVDESC_NO_OFFSET\n};\n");
E 4
I 4
		generate_operation_vp_offsets();
E 4

		# Print out the vnodeop_desc structure.
D 4
		printf("struct vnodeop_desc %s_desc = {\n", name);
		printf("\t0,\n\t\"%s\",\n\t0,\n\t%s_vp_offsets,\n", name, name);
E 4
I 4
		generate_operation_desc();
E 4

D 4
		# Print out return vpp entry, if any.
		for (found = c2 = 0; c2 < c1; ++c2) {
			c3 = split(a[c2], t);
			if (c3 != 4 || t[1] !~ /^OUT$/ || t[2] !~ /^struct$/ ||
			    t[3] !~ /^vnode$/)
				continue;
			printf("\tVOPARG_OFFSETOF(struct %s_args, a_vpp),\n",
			    name);
			found = 1;
			break;
		}
		if (found == 0)
			printf("\tVDESC_NO_OFFSET,\n");
E 4
I 4
		printf "\n";
E 4

D 4
		# Print out cred entry, if any.
		for (found = c2 = 0; c2 < c1; ++c2) {
			c3 = split(a[c2], t);
			if (c3 != 4 || t[1] !~ /^IN$/ || t[2] !~ /^struct$/ ||
			    t[3] !~ /^ucred$/)
				continue;
			printf("\tVOPARG_OFFSETOF(struct %s_args, a_cred),\n",
			    name);
			found = 1;
			break;
		}
		if (found == 0)
			printf("\tVDESC_NO_OFFSET,\n");

		# Print out proc entry, if any.
		for (found = c2 = 0; c2 < c1; ++c2) {
			c3 = split(a[c2], t);
			if (c3 != 4 || t[1] !~ /^IN$/ || t[2] !~ /^struct$/ ||
			    t[3] !~ /^proc$/)
				continue;
			printf("\tVOPARG_OFFSETOF(struct %s_args, a_p),\n",
			    name);
			found = 1;
			break;
		}
		if (found == 0)
			printf("\tVDESC_NO_OFFSET,\n");
		printf("\tNULL,\n};\n");
E 4
	}' < $SRC >> $CFILE
D 4

E 4
E 2
# THINGS THAT DON'T WORK RIGHT YET.
# 
# Two existing BSD vnodeops (bwrite and strategy) don't take any vnodes as
# arguments.  This means that these operations can't function successfully
# through a bypass routine.
#
# Bwrite and strategy will be replaced when the VM page/buffer cache
# integration happens.
#
# To get around this problem for now we handle these ops as special cases.

D 2
cat << END_OF_SPECIAL_CASES
E 2
I 2
cat << END_OF_SPECIAL_CASES >> $HEADER
E 2
#include <sys/buf.h>
struct vop_strategy_args {
	struct vnodeop_desc *a_desc;
	struct buf *a_bp;
};
extern struct vnodeop_desc vop_strategy_desc;
static inline int VOP_STRATEGY(bp)
	struct buf *bp;
{
	struct vop_strategy_args a;

	a.a_desc = VDESC(vop_strategy);
	a.a_bp = bp;
	return (VCALL((bp)->b_vp, VOFFSET(vop_strategy), &a));
E 7
I 7
# Body stuff
sed -e "$sed_prep" $src | $awk '
function doit() {
	printf("\t&%s_desc,\n", name);
E 7
}
I 7
'"$awk_parser"
E 7

D 7
struct vop_bwrite_args {
	struct vnodeop_desc *a_desc;
	struct buf *a_bp;
E 7
I 7
# End stuff
echo '	NULL
E 7
};
D 7
extern struct vnodeop_desc vop_bwrite_desc;
static inline int VOP_BWRITE(bp)
	struct buf *bp;
{
	struct vop_bwrite_args a;
E 7
I 7
'
E 7

D 7
	a.a_desc = VDESC(vop_bwrite);
	a.a_bp = bp;
	return (VCALL((bp)->b_vp, VOFFSET(vop_bwrite), &a));
}
END_OF_SPECIAL_CASES
E 7
I 7
exit 0
E 7
I 2

D 7
cat << END_OF_SPECIAL_CASES >> $CFILE
int vop_strategy_vp_offsets[] = {
	VDESC_NO_OFFSET
};
struct vnodeop_desc vop_strategy_desc = {
	0,
	"vop_strategy",
	0,
	vop_strategy_vp_offsets,
	VDESC_NO_OFFSET,
	VDESC_NO_OFFSET,
	VDESC_NO_OFFSET,
I 4
	VDESC_NO_OFFSET,
E 4
	NULL,
};
int vop_bwrite_vp_offsets[] = {
	VDESC_NO_OFFSET
};
struct vnodeop_desc vop_bwrite_desc = {
	0,
	"vop_bwrite",
	0,
	vop_bwrite_vp_offsets,
	VDESC_NO_OFFSET,
	VDESC_NO_OFFSET,
	VDESC_NO_OFFSET,
I 4
	VDESC_NO_OFFSET,
E 4
	NULL,
};
END_OF_SPECIAL_CASES

# Add the vfs_op_descs array to the C file.
D 4
awk '
E 4
I 4
$AWK '
E 4
	BEGIN {
D 4
		printf("struct vnodeop_desc *vfs_op_descs[] = {\n");
E 4
I 4
		printf("\nstruct vnodeop_desc *vfs_op_descs[] = {\n");
E 4
		printf("\t&vop_default_desc,	/* MUST BE FIRST */\n");
		printf("\t&vop_strategy_desc,	/* XXX: SPECIAL CASE */\n");
		printf("\t&vop_bwrite_desc,	/* XXX: SPECIAL CASE */\n");
	}
	END {
		printf("\tNULL\n};\n");
	}
	NF == 0 || $0 ~ "^#" {
		next;
	}
	{
		# Get the function name.
		printf("\t&%s_desc,\n", $1);

		# Skip the function arguments.
		for (;;) {
			if (getline <= 0)
				exit
			if ($0 ~ "^};")
				break;
		}
	}' < $SRC >> $CFILE
I 4

E 7
I 7
# Local Variables:
# tab-width: 4
# End:
E 7
E 4
E 2
E 1
