h10659
s 00001/00001/00021
d D 8.2 95/04/21 08:49:24 eric 2 1
c have to quote DOMAIN in comment (sigh)
e
s 00022/00000/00000
d D 8.1 95/04/21 07:35:20 eric 1 0
c date and time created 95/04/21 07:35:20 by eric
e
u
U
t
T
I 1
divert(-1)
#
# Copyright (c) 1983 Eric P. Allman
# Copyright (c) 1988, 1993
#	The Regents of the University of California.  All rights reserved.
#
# %sccs.include.redist.sh%
#

#
#  The following is a generic domain file.  You should be able to
#  use it anywhere.  If you want to customize it, copy it to a file
#  named with your domain and make the edits; then, copy the appropriate
D 2
#  .mc files and change DOMAIN(generic) to reference your updated domain
E 2
I 2
#  .mc files and change `DOMAIN(generic)' to reference your updated domain
E 2
#  files.
#
divert(0)
VERSIONID(`%W% (Berkeley) %G%')
define(`confFORWARD_PATH', `$z/.forward.$w:$z/.forward')dnl
define(`confCW_FILE', `-o /etc/sendmail.cw')dnl
FEATURE(redirect)dnl
FEATURE(use_cw_file)dnl
E 1
