#	@(#)SPARC	8.3 (Berkeley) 4/24/94
#
# SPARCstation 1, 1+, 2, etc.

include	"std.sparc"

# needs to be set per system
options		TIMEZONE="'8*60'"	# minutes west of GMT (for param.c)
options		DST=1			# daylight savings rules (for param.c)

# Standard system options
options		SWAPPAGER, VNODEPAGER, DEVPAGER	# paging
options		DEBUG, DIAGNOSTIC	# extra kernel debugging
options		KTRACE			# system call tracing support
options		KGDB			# support for kernel gdb
options		KGDBDEV=0xc01, KGDBRATE=38400	# device & baud rate
makeoptions	DEBUG="-g"		# symbols for kgdb
options		RCONSOLE		# fast rasterop console
#options	SYSVSHM, SHMMAXPGS=1024	# System V shared memory

# Filesystem options
options		FIFO		# POSIX fifo support (in all filesystems)
options		FFS, QUOTA	# fast filesystem with user and group quotas
options		MFS		# memory-based filesystem
options		NFS		# Sun NFS-compatible filesystem
options		"CD9660"	# ISO 9660 (CDROM) filesystem
options		UNION		# Union filesystem
options		KERNFS		# kernel data-structure filesystem
options		FDESC		# user file descriptor filesystem
#options	PROCFS		# /proc filesystem
#options	UMAPFS		# uid/gid remapping filesystem
#options	NULLFS		# null layer filesystem
#options	LFS		# Log-based filesystem (still experimental)
#options	PORTAL		# portal filesystem (still experimental)

# Networking options
options		INET
#options	TCP_COMPAT_42	# compatibility with 4.2BSD TCP/IP
#options	GATEWAY		# IP packet forwarding
#options	ISO		# OSI networking
#options	TPIP
#options	EON

# Options for SPARCstation hardware
options		COMPAT_SUNOS		# compatibility with SunOS binaries

config		vmunix	root on sd0 swap on sd0 and sd1 and sd2 and sd3

dma*	at sbus0 slot ? offset ?
esp*	at sbus0 slot ? offset ?	# nb., esp is a `scsi'

tg0	at esp? target 0
tg*	at scsi? target ?
sd0	at tg0 drive 0
sd*	at tg? drive ?

bwtwo*	at sbus? slot ? offset ?
cgthree* at sbus? slot ? offset ?
cgsix*	at sbus? slot ? offset ?

le*	at sbus? slot ? offset ?

pseudo-device	loop
pseudo-device	pty
pseudo-device	sl
