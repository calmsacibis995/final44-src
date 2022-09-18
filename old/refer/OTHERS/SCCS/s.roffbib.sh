h62661
s 00005/00002/00043
d D 4.2 91/04/18 16:36:26 bostic 2 1
c new copyright; att/bsd/shared
e
s 00045/00000/00000
d D 4.1 83/05/08 15:08:39 mckusick 1 0
c date and time created 83/05/08 15:08:39 by mckusick
e
u
U
t
T
I 1
D 2
#! /bin/sh
E 2
I 2
#!/bin/sh -
E 2
#
D 2
#	%W%	(Berkeley)	%E%
E 2
I 2
# %sccs.include.proprietary.sh%
E 2
#
I 2
#	%W% (Berkeley) %G%
#

E 2
#	roffbib sh script
#
flags=
abstr=
headr=BIBLIOGRAPHY
xroff=nroff
macro=-mbib

for i
do case $1 in
	-[onsrT]*|-[qeh])
		flags="$flags $1"
		shift ;;
	-x)
		abstr=-x
		shift ;;
	-m)
		shift
		macro="-i $1"
		shift ;;
	-V)
		xroff=vtroff
		shift ;;
	-Q)
		xroff="troff -Q"
		shift ;;
	-H)
		shift
		headr="$1"
		shift ;;
	-*)
		echo "roffbib: unknown flag: $1"
		shift
	esac
done
if test $1
then
	(echo .ds TL $headr; refer -a1 -B$abstr $*) | $xroff $flags $macro
else
	(echo .ds TL $headr; refer -a1 -B$abstr) | $xroff $flags $macro
fi
E 1
