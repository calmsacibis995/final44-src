
#
#      Copyright (c) 1984, 1985 AT&T
#      All Rights Reserved
#
#      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
#      CODE OF AT&T.
#      The copyright notice above does not 
#      evidence any actual or intended
#      publication of such source code.
#
#
# G. S. Fowler
# AT&T Bell Laboratories
#
# old-new makefile converter
# this glues the two passes together
#
# @(#)mkcv (AT&T Bell Laboratories) 08/30/85a
#
${LIBDIR}/mkcv1 "$@" | ${LIBDIR}/mkcv2
