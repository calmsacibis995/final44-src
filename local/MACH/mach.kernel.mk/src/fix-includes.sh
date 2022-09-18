#!/bin/sh
#
# Mach Operating System
# Copyright (c) 1989 Carnegie-Mellon University
# All rights reserved.  The CMU software License Agreement specifies
# the terms and conditions for use and redistribution.
#
#
# HISTORY
# $Log:	fix-includes.sh,v $
# Revision 2.5  89/03/09  03:47:53  rpd
# 	Added many rules for "user.h", etc.  Now ignores lines
# 	with whitespace before #, because cpp ignores them.
# 	Leaves includes with "" instead of using #%#.
# 
# Revision 2.4  89/03/06  23:55:04  rpd
# 	Convert '#if MACH' and '#if CMUCS' to #ifdef.
# 	Only convert whitespace after #define to a single space
# 	if it was a single tab.
# 
# Revision 2.3  89/02/25  19:25:29  gm0w
# 	Changes for cleanup.
# 
# Revision 2.2  89/02/19  21:35:20  rpd
# 	Created.
# 	[89/02/19  21:28:47  rpd]
# 

# Puts #include (and other cpp) lines into a canonical format.
# Transforms
#	#include "user.h"
# to
#	#include <sys/user.h>
# but leaves
#	#include "unrecognized.h"
# alone.
#
# It will preserve comments like
#	#include <sys/foo.h>	/* for struct foo */

sed -e 's;^#[ 	]*include[ 	][ 	]*"\([^"]*\)"\(.*\)$;#include "\1"\2;'\
    -e 's;^#[ 	]*include[ 	][ 	]*<\([^>]*\)>\(.*\)$;#include <\1>\2;'\
    -e 's;^#include "\(cpus\.h\)"\(.*\)$;#include <\1>\2;' \
    -e 's;^#include "\(mach\.h\)"\(.*\)$;#include <\1>\2;' \
    -e 's;^#include "\(mach_[^"]*\.h\)"\(.*\)$;#include <\1>\2;' \
    -e 's;^#include "\(cmucs\.h\)"\(.*\)$;#include <\1>\2;' \
    -e 's;^#include "\(cmucs_[^"]*\.h\)"\(.*\)$;#include <\1>\2;' \
    -e 's;^#include "\(romp_[^"]*\.h\)"\(.*\)$;#include <\1>\2;' \
    -e 's;^#include "acct.h"\(.*\)$;#include <sys/acct.h>\1;' \
    -e 's;^#include "bkmac.h"\(.*\)$;#include <sys/bkmac.h>\1;' \
    -e 's;^#include "buf.h"\(.*\)$;#include <sys/buf.h>\1;' \
    -e 's;^#include "callout.h"\(.*\)$;#include <sys/callout.h>\1;' \
    -e 's;^#include "clist.h"\(.*\)$;#include <sys/clist.h>\1;' \
    -e 's;^#include "cmap.h"\(.*\)$;#include <sys/cmap.h>\1;' \
    -e 's;^#include "cmupty.h"\(.*\)$;#include <sys/cmupty.h>\1;' \
    -e 's;^#include "conf.h"\(.*\)$;#include <sys/conf.h>\1;' \
    -e 's;^#include "dir.h"\(.*\)$;#include <sys/dir.h>\1;' \
    -e 's;^#include "dk.h"\(.*\)$;#include <sys/dk.h>\1;' \
    -e 's;^#include "dkbad.h"\(.*\)$;#include <sys/dkbad.h>\1;' \
    -e 's;^#include "domain.h"\(.*\)$;#include <sys/domain.h>\1;' \
    -e 's;^#include "enet.h"\(.*\)$;#include <sys/enet.h>\1;' \
    -e 's;^#include "errno.h"\(.*\)$;#include <sys/errno.h>\1;' \
    -e 's;^#include "exec.h"\(.*\)$;#include <sys/exec.h>\1;' \
    -e 's;^#include "fe.h"\(.*\)$;#include <sys/fe.h>\1;' \
    -e 's;^#include "file.h"\(.*\)$;#include <sys/file.h>\1;' \
    -e 's;^#include "filsys.h"\(.*\)$;#include <sys/filsys.h>\1;' \
    -e 's;^#include "fpsconf.h"\(.*\)$;#include <sys/fpsconf.h>\1;' \
    -e 's;^#include "fpsreg.h"\(.*\)$;#include <sys/fpsreg.h>\1;' \
    -e 's;^#include "fs.h"\(.*\)$;#include <sys/fs.h>\1;' \
    -e 's;^#include "gprof.h"\(.*\)$;#include <sys/gprof.h>\1;' \
    -e 's;^#include "ild.h"\(.*\)$;#include <sys/ild.h>\1;' \
    -e 's;^#include "inode.h"\(.*\)$;#include <sys/inode.h>\1;' \
    -e 's;^#include "ioctl.h"\(.*\)$;#include <sys/ioctl.h>\1;' \
    -e 's;^#include "jioctl.h"\(.*\)$;#include <sys/jioctl.h>\1;' \
    -e 's;^#include "kernel.h"\(.*\)$;#include <sys/kernel.h>\1;' \
    -e 's;^#include "map.h"\(.*\)$;#include <sys/map.h>\1;' \
    -e 's;^#include "mbuf.h"\(.*\)$;#include <sys/mbuf.h>\1;' \
    -e 's;^#include "mman.h"\(.*\)$;#include <sys/mman.h>\1;' \
    -e 's;^#include "mount.h"\(.*\)$;#include <sys/mount.h>\1;' \
    -e 's;^#include "msgbuf.h"\(.*\)$;#include <sys/msgbuf.h>\1;' \
    -e 's;^#include "mtio.h"\(.*\)$;#include <sys/mtio.h>\1;' \
    -e 's;^#include "namei.h"\(.*\)$;#include <sys/namei.h>\1;' \
    -e 's;^#include "param.h"\(.*\)$;#include <sys/param.h>\1;' \
    -e 's;^#include "proc.h"\(.*\)$;#include <sys/proc.h>\1;' \
    -e 's;^#include "protosw.h"\(.*\)$;#include <sys/protosw.h>\1;' \
    -e 's;^#include "ptrace.h"\(.*\)$;#include <sys/ptrace.h>\1;' \
    -e 's;^#include "quota.h"\(.*\)$;#include <sys/quota.h>\1;' \
    -e 's;^#include "reboot.h"\(.*\)$;#include <sys/reboot.h>\1;' \
    -e 's;^#include "resource.h"\(.*\)$;#include <sys/resource.h>\1;' \
    -e 's;^#include "rfs.h"\(.*\)$;#include <sys/rfs.h>\1;' \
    -e 's;^#include "signal.h"\(.*\)$;#include <sys/signal.h>\1;' \
    -e 's;^#include "socket.h"\(.*\)$;#include <sys/socket.h>\1;' \
    -e 's;^#include "socketvar.h"\(.*\)$;#include <sys/socketvar.h>\1;' \
    -e 's;^#include "stat.h"\(.*\)$;#include <sys/stat.h>\1;' \
    -e 's;^#include "syscall.h"\(.*\)$;#include <sys/syscall.h>\1;' \
    -e 's;^#include "syslog.h"\(.*\)$;#include <sys/syslog.h>\1;' \
    -e 's;^#include "systm.h"\(.*\)$;#include <sys/systm.h>\1;' \
    -e 's;^#include "table.h"\(.*\)$;#include <sys/table.h>\1;' \
    -e 's;^#include "tablet.h"\(.*\)$;#include <sys/tablet.h>\1;' \
    -e 's;^#include "time.h"\(.*\)$;#include <sys/time.h>\1;' \
    -e 's;^#include "timeb.h"\(.*\)$;#include <sys/timeb.h>\1;' \
    -e 's;^#include "times.h"\(.*\)$;#include <sys/times.h>\1;' \
    -e 's;^#include "trace.h"\(.*\)$;#include <sys/trace.h>\1;' \
    -e 's;^#include "tty.h"\(.*\)$;#include <sys/tty.h>\1;' \
    -e 's;^#include "ttychars.h"\(.*\)$;#include <sys/ttychars.h>\1;' \
    -e 's;^#include "ttydev.h"\(.*\)$;#include <sys/ttydev.h>\1;' \
    -e 's;^#include "ttyloc.h"\(.*\)$;#include <sys/ttyloc.h>\1;' \
    -e 's;^#include "types.h"\(.*\)$;#include <sys/types.h>\1;' \
    -e 's;^#include "uio.h"\(.*\)$;#include <sys/uio.h>\1;' \
    -e 's;^#include "un.h"\(.*\)$;#include <sys/un.h>\1;' \
    -e 's;^#include "unpcb.h"\(.*\)$;#include <sys/unpcb.h>\1;' \
    -e 's;^#include "user.h"\(.*\)$;#include <sys/user.h>\1;' \
    -e 's;^#include "vadvise.h"\(.*\)$;#include <sys/vadvise.h>\1;' \
    -e 's;^#include "vcmd.h"\(.*\)$;#include <sys/vcmd.h>\1;' \
    -e 's;^#include "version.h"\(.*\)$;#include <sys/version.h>\1;' \
    -e 's;^#include "viceioctl.h"\(.*\)$;#include <sys/viceioctl.h>\1;' \
    -e 's;^#include "vicermt.h"\(.*\)$;#include <sys/vicermt.h>\1;' \
    -e 's;^#include "vlimit.h"\(.*\)$;#include <sys/vlimit.h>\1;' \
    -e 's;^#include "vm.h"\(.*\)$;#include <sys/vm.h>\1;' \
    -e 's;^#include "vmmac.h"\(.*\)$;#include <sys/vmmac.h>\1;' \
    -e 's;^#include "vmparam.h"\(.*\)$;#include <sys/vmparam.h>\1;' \
    -e 's;^#include "vsio.h"\(.*\)$;#include <sys/vsio.h>\1;' \
    -e 's;^#include "vtimes.h"\(.*\)$;#include <sys/vtimes.h>\1;' \
    -e 's;^#include "wait.h"\(.*\)$;#include <sys/wait.h>\1;' \
    -e 's;^#include "\.\./\([^"]*\)"\(.*\)$;#include <\1>\2;' \
    -e 's;^#include "\([^"/]*\)/\([^"]*\)"\(.*\)$;#include <\1/\2>\3;' \
    -e 's;^#include <h/\([^>]*\)>\(.*\)$;#include <sys/\1>\2;' \
    -e 's;^#[ 	]*define\(.*\)$;#define\1;' \
    -e 's;^#define	\([^ 	].*\)$;#define \1;' \
    -e 's;^#[ 	]*if[ 	][ 	]*\(.*\)$;#if	\1;' \
    -e 's;^#[ 	]*ifdef[ 	][ 	]*\(.*\)$;#ifdef	\1;' \
    -e 's;^#[ 	]*ifndef[ 	][ 	]*\(.*\)$;#ifndef	\1;' \
    -e 's;^#[ 	]*elif[ 	][ 	]*\(.*\)$;#elif	\1;' \
    -e 's;^#[ 	]*else$;#else;' \
    -e 's;^#[ 	]*else[ 	][ 	]*\(.*\)$;#else	\1;' \
    -e 's;^#[ 	]*endif$;#endif;' \
    -e 's;^#[ 	]*endif[ 	][ 	]*\(.*\)$;#endif	\1;' \
    -e 's;^#if	MACH$;#ifdef	MACH;' \
    -e 's;^#if	CMUCS;#ifdef	CMUCS;'
