/*
 * example:	David Korn		ulysses!dgk
 *		Glenn Fowler		ulysses!gsf
 *
 * makefile for 3b2 UNIX
 *
 * NOTE:  os/prf.c must be linked or moved to os/osprf.c
 *        io/prf.c must be linked or moved to io/ioprf.c
 *        vuifile must be linked or moved to unix.ld
 */

#undef unix

SRC =		$(ROOT)/usr/src/uts/3b2

NODE =		kernel
CACHE =		1
REM =		1
INKERNEL =	1
VERSIONS =	1
PROFILE =
OSDEBUG	=	YES
DUDEBUG	=	YES
N3BNETVERSION = "3BNET # closing "

M4 =		m4
M4FLAGS =	m4.defs -DMCOUNT=#
MKBOOT =	/etc/mkboot
MKBOOTFLAGS =	-m $(SRC)/master.d -d .

CCFLAGS += -Du3b2 -Uvax -Updp11 -Uu3b -Uu3b5

ARFLAGS = rl

.SOURCE.h : . $(SRC) $(ROOT)/usr/include

.SOURCE : $(SRC)/debug $(SRC)/io $(SRC)/ml $(SRC)/os $(SRC)/nudnix $(SRC) \
		$(SRC)/fs/s5 $(SRC)/fs/proc

.OPTIONS : -u

all : .ALL

(LOGNAME) : .NOEXPAND

$(NODE) :: start.o gate.c locore.o getsizes.c libio.a libos.a \
	unix.ld (INKERNEL) (PROFILE) (CACHE) (VERSIONS) (LOGNAME)
	if	test ! -r version.$(LOGNAME)
	then	echo 0 > version.$(LOGNAME)
	fi
	version=`<version.$(LOGNAME)`
	(( version = version + 1 ))
	echo "char *version = \"$(LOGNAME:F=L%.4s)#$version\";" > name.c
	$(CC) -c name.c
	$(RM) $(RMFLAGS) $(<)
	$(LD) $(LDFLAGS) -r -o $(<) -u ttopen $(*:N=*.ld) $(*:N=*.o) name.o $(*:N=*.a)
	echo $version > version.$(LOGNAME)
	$(MKBOOT) $(MKBOOTFLAGS) -k $(<)

getsizes.o : .IMPLICIT
	$(CC) $(CCFLAGS:/-O//) -g -c $(>)

start.o :: uprt.s pstart.c cdump.c
	$(LD) $(LDFLAGS) -r -o $(<) $(*)

locore.o : .sed ttrap.s cswitch.s misc.s kpcbs.o (INKERNEL) (PROFILE)

uprt.o : .sed

CLONE :: .boot clone.c (CACHE) (VERSIONS) (INKERNEL) (PROFILE)

CPACK :: .boot cpack.c (CACHE) (VERSIONS) (INKERNEL) (PROFILE)

CTC :: .boot ct.c ct_lla.c (CACHE) (VERSIONS) (INKERNEL) (PROFILE)

DEBUG :: .boot ctype.c data.c disasm.c doprnt.s prtabs.c sprintf.s tables.c \
		trace.c utils.s (CACHE) (VERSIONS) (INKERNEL) (PROFILE)

DISP :: .boot disp.c (CACHE) (VERSIONS) (INKERNEL) (PROFILE)

EMD :: .boot n3bemdmain.c n3bemd_3b2.c emd_lla.c (N3BNETVERSION) (INKERNEL) (PROFILE)

ESM :: .boot esm.c (N3BNETVERSION) (INKERNEL) (PROFILE)

GENTTY :: .boot gentty.c (CACHE) (VERSIONS) (INKERNEL) (PROFILE)

HDELOG :: .boot hde.c (CACHE) (VERSIONS) (INKERNEL) (PROFILE)

IDISK :: .boot id.c if.c sddrv.c physdsk.c (CACHE) (VERSIONS) (INKERNEL) (PROFILE)

IPC :: .boot ipc.c (CACHE) (VERSIONS) (INKERNEL) (PROFILE)

IUART :: .boot iu.c (CACHE) (VERSIONS) (INKERNEL) (PROFILE)

LOG :: .boot log.c (INKERNEL) (PROFILE)

MAU :: .boot mau.c (CACHE) (VERSIONS) (INKERNEL) (PROFILE)

MEM :: .boot mem.c (CACHE) (VERSIONS) (INKERNEL) (PROFILE)

MNT :: .boot n3bmaint.c n3butil.c (CACHE) (VERSIONS) (N3BNETVERSION) (INKERNEL) (PROFILE)

MSG :: .boot msg.c (CACHE) (VERSIONS) (INKERNEL) (PROFILE)

NI :: .boot ni2.c nisubr.c ni_lla.c (INKERNEL) (PROFILE)

OMNINET :: .boot omni.c omnisubr.c omni_lla.c (CACHE) (VERSIONS) (INKERNEL) (PROFILE)

PACK :: .boot dupack.c protocol.c (DUDEBUG) (CACHE) (VERSIONS) (INKERNEL) (PROFILE)

PORTS :: .boot ppc.c lla_ppc.c (CACHE) (VERSIONS) (INKERNEL) (PROFILE)

PRF :: .boot ioprf.c (CACHE) (VERSIONS) (INKERNEL) (PROFILE)

SEM :: .boot sem.c (CACHE) (VERSIONS) (INKERNEL) (PROFILE)

SHM :: .boot shm.c (CACHE) (VERSIONS) (INKERNEL) (PROFILE)

STUBS :: .boot stubs.c (INKERNEL) (PROFILE)

SXT :: .boot sxt.c (CACHE) (VERSIONS) (INKERNEL) (PROFILE)

TIMOD :: .boot timod.c (CACHE) (VERSIONS) (INKERNEL) (PROFILE)

TRTAB :: .boot trtab.c (CACHE) (VERSIONS) (INKERNEL) (PROFILE)

XT :: xt.c (CACHE) (VERSIONS) (INKERNEL) (PROFILE)
	$(CC) $(CCFLAGS:/-O//) -c $(>)
	$(MKBOOT) $(MKBOOTFLAGS) $(<:F=L:BS=.o)

libio.a :: clist.c partab.c stream.c tt1.c tty.c \
		(INKERNEL) (PROFILE) (CACHE) (VERSIONS)

libos.a :: Icache.c acct.c bio.c bitmasks.c clock.c exec.c \
		exit.c fault.c fio.c flock.c fork.c fstyp.c getpages.c \
		grow.c iget.c lock.c machdep.c main.c \
		malloc.c mmgt.c move.c nami.c page.c physio.c \
		pipe.c osprf.c probe.c region.c sched.c sdt.c \
		sig.c slp.c space.c startup.c streamio.c subr.c \
		swapalloc.c swtch.c sys2.c sys3.c sys3b.c sys4.c \
		sysent.c text.c todc.c trap.c utssys.c \
		(INKERNEL) (PROFILE) (CACHE) (VERSIONS)

streamio.o osprf.o : .IMPLICIT
	$(CC) $(CCFLAGS:/-O//) -c $(>)

/* distributed UNIX */
DU :: .boot adv.c fileop.c netboot.c remcall.c rmount.c fumount.c rmove.c \
	rsc.c cirmgr.c serve.c queue.c que.c serv_ctrl.c sysdu.c recover.c \
	rdebug.c string.c comm.c (OSDEBUG) (DUDEBUG) (CACHE) (VERSIONS) \
	(INKERNEL) (PROFILE)

/* file system types */
PROC :: .boot proca.c (CACHE) (VERSIONS) (INKERNEL) (PROFILE)

S5 :: .boot s5alloc.c s5blklist.c s5iget.c s5nami.c s5pipe.c s5rdwri.c \
	s5subr.c s5sys2.c s5sys3.c (CACHE) (VERSIONS) (INKERNEL) (PROFILE)

*.o : *.s
	dir=`pwd`
	cd $(>:D)
	$(M4) $(M4FLAGS) $(>:BS) > $(>:D=$dir:BS=.m.s)
	cd $dir
	$(CC) $(CCFLAGS) -c $(>:BS=.m.s)
	$(RM) $(RMFLAGS) $(>:BS=.m.s)
	$(MV) $(>:BS=.m.o) $(>:BS=.o)

.boot : .USE
	case "$(*)" in
	$(<:F=L:BS=.o));;
	*\ *)	$(LD) -r -o $(<:F=L:BS=.o) $(*)
		;;
	*)	if	test ! $(*) -ef $(<:F=L:BS=.o)
		then	$(LN) $(*) $(<:F=L:BS=.o)
		fi
		;;
	esac
	$(MKBOOT) $(MKBOOTFLAGS) $(<:F=L:BS=.o)

.sed : .USE
	cat $(*:N=*.s) | sed \
		-e 's/^#/?/' \
		-e 's/?\([ 	]*ifdef.*\)/#\1/' \
		-e 's/?\([ 	]*ifndef.*\)/#\1/' \
		-e 's/?\([ 	]*else.*\)/#\1/' \
		-e 's/?\([ 	]*endif.*\)/#\1/' \
		-e '/^?/d' > ${!:-$$}.c
	$(CC) $(CCFLAGS) -P ${!:-$$}.c
	$(MV) ${!:-$$}.i ${!:-$$}.s
	$(CC) -c ${!:-$$}.s
	if	test "$(*:N=*.o)" != ""
	then	$(LD) $(LDFLAGS) -r -o $(<) ${!:-$$}.o $(*:N=*.o)
	else	$(MV) ${!:-$$}.o $(<)
	fi
	$(RM) $(RMFLAGS) ${!:-$$}.?
