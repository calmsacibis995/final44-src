# 
# Mach Operating System
# Copyright (c) 1991,1990,1989 Carnegie Mellon University
# All Rights Reserved.
# 
# Permission to use, copy, modify and distribute this software and its
# documentation is hereby granted, provided that both the copyright
# notice and this permission notice appear in all copies of the
# software, derivative works or modified versions, and any portions
# thereof, and that both notices appear in supporting documentation.
# 
# CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
# CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
# ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
# 
# Carnegie Mellon requests users of this software to return to
# 
#  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
#  School of Computer Science
#  Carnegie Mellon University
#  Pittsburgh PA 15213-3890
# 
# any improvements or extensions that they make and grant Carnegie Mellon
# the rights to redistribute these changes.
#
#
# HISTORY
# $Log:	cthread_inline.awk,v $
# Revision 2.5  91/10/09  16:21:21  af
# 	Revision 2.4.1.1  91/09/16  10:26:21  rpd
# 		Removed inappropriate RCS keywords.
# 
# Revision 2.4.1.1  91/09/16  10:26:21  rpd
# 	Removed inappropriate RCS keywords.
# 
# Revision 2.4  91/05/14  18:00:22  mrt
# 	Correcting copyright
# 
# Revision 2.3  91/02/14  14:21:48  mrt
# 	Added new Mach copyright
# 	[91/02/13  12:39:55  mrt]
# 
# Revision 2.2  89/12/08  19:55:20  rwd
# 	Only spins are simple locks
# 	[89/10/23            rwd]
# 
# 	vax/cthread_inline.awk
# 
#
# Awk script to inline critical C Threads primitives on VAX.

NF == 2 && $1 == "calls" && $2 == "$1,_spin_try_lock" {
	print	"#	BEGIN INLINE spin_try_lock"
	print	"	bbssi	$0,*(sp)+,1f"
	print	"	movl	$1,r0		# yes"
	print	"	jbr	2f"
	print	"1:	clrl	r0		# no"
	print	"2:"
	print	"#	END INLINE spin_try_lock"
	continue
}
NF == 2 && $1 == "calls" && $2 == "$1,_spin_unlock" {
	print	"#	BEGIN INLINE " $2
	print	"	bbcci	$0,*(sp)+,1f"
	print	"1:"
	print	"#	END INLINE " $2
	continue
}
NF == 2 && $1 == "calls" && $2 == "$0,_cthread_sp" {
	print	"#	BEGIN INLINE cthread_sp"
	print	"	movl	sp,r0"
	print	"#	END INLINE cthread_sp"
	continue
}
# default:
{
	print
}
