/*
 * original:	Rob Petterson		attunix!rcp2
 * example:	Glenn Fowler		ulysses!gsf
 *
 * This is the rewritten (gsf) version of polo.old.mk.
 * The NOTES describe the motivation of the rewrite.
 *
 * NOTES:
 *
 *	name new makefiles Makefile and old makefiles makefile so
 *		both nmake and /bin/make can be run without -f args
 *		nmake checks Makefile first, /bin/make checks makefile
 *		first
 *	put the -g option in one spot, this way one variable
 *		PROFILE can propagate the -g option to all related
 *		commands and targets, i.e., `make PROFILE=-g'.
 *		Don't define PROFILE in the makefile for portability
 *		reasons.  It is just as easy to export PROFILE.
 *	.PRECIOUS is not necessary for *.[chy] files or any other
 *		source files.  Only generated targets are deleted
 *		on interrupts.
 *	The "*.o : *.c" rule now implicitly contains dependencies
 *		on (CC) and (CCFLAGS) and the same goes for the
 *		other builtin rules.
 *	.BACKUP is a good candidate for a local builtin action.
 *		This could be placed in a global rules file
 *		and compiled into "/mydirs/myrules.mo" and accessed
 *		by alias make="nmake -g /mydirs/myrules.mo".  This would
 *		give friendly users the utility of local backup procedures
 *		without burdening the rest of the community who must
 *		use the makefile on foreign (hostile!) systems.
 *	Localized options and command names should be set and exported
 *		in the environment, especially things like LPFLAGS
 *		which are almost sure to change from system to system
 *		(even from user to user on the same system).
 *
 * The basic idea is to write new makefiles with as much parameterization
 * as possible.  Notice here that if .BACKUP were placed in a global makefile
 * then the original makefile condenses to one (logical) line.
 */

polo :: bldgr.c block.h blocks.h call.h dreloc.h fentry.h \
	fentrys.h func.c func.h get.c get.h ibrpos.h infile.c infile.h \
	inst.c inst.h ispec.c ispec.h ld.c ldtbread.c misc.c oper.c \
	oper.h order.c outfile.c polo.h polostruct.h print.c rmunch.c \
	sdi.c sdi.h vol.h -lld -lmalloc (PROFILE)

/*
 * .BACKUP might be placed in a global -g makefile
 * the source files are copied to BACKUPDIR using BACKUP
 * and CPIO.
 */

#if release(bsd)
BACKUP = rcp
BACKUPFLAGS = -C
#elif release(research)
BACKUP = $(CP)
BACKUPFLAGS = $(CPFLAGS)
#else
BACKUP = uucp
BACKUPFLAGS = -C
#endif
BACKUPDIR = $(ROOT|HOME)/backup

.BACKUP : .CPIO
	$(BACKUP) $(BACKUPFLAGS) $(.OUTPUT:PBS=.cpio) $(.OUTPUT:D=$(BACKUPDIR):PBS=.bak)
