h45839
s 00001/00001/00013
d D 8.2 93/08/09 21:25:56 eric 2 1
c fix other cases of -o following file name
e
s 00014/00000/00000
d D 8.1 93/07/08 09:19:26 eric 1 0
c date and time created 93/07/08 09:19:26 by eric
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

divert(0)
VERSIONID(`%W% (Berkeley) %G%')
divert(-1)

D 2
define(`DOMAIN_TABLE', ifelse(_ARG_, `', `hash /etc/domaintable -o', `_ARG_'))dnl
E 2
I 2
define(`DOMAIN_TABLE', ifelse(_ARG_, `', `hash -o /etc/domaintable', `_ARG_'))dnl
E 2
E 1
