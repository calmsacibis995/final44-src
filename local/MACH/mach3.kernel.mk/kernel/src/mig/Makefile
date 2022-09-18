#
# Mach Operating System
# Copyright (c) 1993,1992 Carnegie Mellon University
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
# $Log:	Makefile,v $
# Revision 2.13  93/02/04  13:46:32  mrt
# 	Updated for ODE make.
# 	[93/01/16            mrt]
# 
# 
#    File:	Makefile
#    Author:	Richard Draves, Carnegie Mellon University
#    Date:	Mar, 1990    
#

DEPENDENCIES		=

SETUP_PROGRAMS		= migcom
PROGRAMS		= migcom
SCRIPTS			= mig

CCTYPE			= host

EXPINC_SUBDIRS		= include
ILIST			=  migcom mig
IDIR			= /lib/
mig_IDIR		= /bin/

EXPBIN_TARGETS		= export_migcom export_mig

migcom_OFILES		= parser.o lexxer.o migcom.o \
			  error.o string.o type.o routine.o \
			  statement.o global.o vprint.o \
			  header.o user.o server.o utils.o
LIBS			= ${LIBL}
GARBAGE			= parser.c parser.h

.include <${RULES_MK}>

parser.c: parser.h
lexxer.o: parser.h

parser.h: parser.y
	${YACC} -d ${_YFLAGS_} ${parser.y:P}
	${MV} -f y.tab.c parser.c
	${MV} -f y.tab.h parser.h

