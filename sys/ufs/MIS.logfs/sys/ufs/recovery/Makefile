#	@(#)Makefile	8.1 (Berkeley) 6/18/93

PROG=	lffs_roll
PROG:	$(OBJS)
CFLAGS+=-g -I. -I.. -I../ffs -I/usr/src/sbin/fsck
LOGDIR = ../logging
FSCKDIR = /usr/src/sbin/fsck/obj
FSCK_OBJS = $(FSCKDIR)/setup.o $(FSCKDIR)/utilities.o $(FSCKDIR)/inode.o 
LOG_OBJS = $(LOGDIR)/lffs_read.o $(LOGDIR)/lffs_read_utils.o \
	$(LOGDIR)/lffs_print.o $(LOGDIR)/lffs_recover.o	\
	$(LOGDIR)/lffs_strings.o
OBJS = $(FSCK_OBJS) $(LOG_OBJS)
SRCS=	lffs_roll.c lffs_globs.c lffs_support.c lffs_dirops.c ffs_subr.c \
	ffs_tables.c
.include <bsd.prog.mk>
