/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	config.h,v $
 * Revision 2.8.1.1  90/02/01  13:37:27  rvb
 * 	Do not declare sprintf() anymore.  It should be treated in code
 * 	as void.
 * 	[90/01/22            rvb]
 * 
 * Revision 2.8  89/03/09  21:12:11  rpd
 * 	More cleanup.
 * 
 * Revision 2.7  89/02/25  19:17:57  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.6  89/02/19  18:39:45  rpd
 * 	Added fopenp, get_VPATH, VPATH declarations.
 * 
 * Revision 2.5  89/02/07  22:56:06  mwyoung
 * Code cleanup cataclysm.
 * 
 * Revision 2.4  89/01/23  22:21:35  af
 * 	Changes for MIPS and I386: MACHINE_<name> and
 * 		THE REAL MIPS MACHINE uses 4 bit MINORS
 * 	Purge FORCE_VOLATILE/VOLATILE and replace it with f_extra.
 * 	[89/01/09            rvb]
 * 
 * 31-Mar-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Add source, object, and configuration directory variables.
 *
 * 03-Mar-88  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Defined MACHINE_SUN4.
 *
 * 08-Jan-87  Robert Beck (beck) at Sequent Computer Systems, Inc.
 *	Add MACHINE_SQT and SEDIT, FASTOBJ options flags.
 *	Add NFIELDS, and d_fields,d_bin to struct device.
 *
 * 27-Oct-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Merged in David Black's changes for the Multimax.
 *
 * 21-Oct-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Merged in changes for Sun 2 and 3.
 *
 *  4-Oct-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Changed all references of CMUCS to CMU.
 *
 * 25-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3.
 *
 * 17-Oct-85  Operating System (sys) at Carnegie-Mellon University
 *	Added OPTIONSDEF definition.
 *
 */

/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)config.h	5.3 (Berkeley) 4/18/86
 */

/*
 * Config.
 */

#include <stdio.h>
#include <sys/types.h>

#define NODEV	((dev_t)-1)

struct file_list {
	struct	file_list *f_next;	
	char	*f_fn;			/* the name */
	u_char	f_type;			/* see below */
	u_char	f_flags;		/* see below */
	short	f_special;		/* requires special make rule */
	char	*f_needs;
	char	*f_extra;		/* stuff to add to make line */
	/*
	 * Random values:
	 *	swap space parameters for swap areas
	 *	root device, etc. for system specifications
	 */
	union {
		struct {		/* when swap specification */
			dev_t	fuw_swapdev;
			int	fuw_swapsize;
		} fuw;
		struct {		/* when system specification */
			dev_t	fus_rootdev;
			dev_t	fus_argdev;
			dev_t	fus_dumpdev;
		} fus;
	} fun;
#define f_swapdev	fun.fuw.fuw_swapdev
#define f_swapsize	fun.fuw.fuw_swapsize
#define f_rootdev	fun.fus.fus_rootdev
#define f_argdev	fun.fus.fus_argdev
#define f_dumpdev	fun.fus.fus_dumpdev
};

/*
 * Types.
 */
#define DRIVER		1
#define NORMAL		2
#define INVISIBLE	3
#define PROFILING	4
#define SYSTEMSPEC	5
#define SWAPSPEC	6

/*
 * Attributes (flags).
 */
#define CONFIGDEP	1
#define OPTIONSDEF	2	/* options definition entry */
#define ORDERED		0x04	/* don't list in OBJ's, keep "files" order */
#define SEDIT		0x08	/* run sed filter (SQT) */
/*
 * Maximum number of fields for variable device fields (SQT).
 */
#define NFIELDS		10

struct	idlst {
	char	*id;
	struct	idlst *id_next;
	int	id_vec;		/* Sun interrupt vector number */
};

struct device {
	int	d_type;			/* CONTROLLER, DEVICE, UBA or MBA */
	struct	device *d_conn;		/* what it is connected to */
	char	*d_name;		/* name of device (e.g. rk11) */
	struct	idlst *d_vec;		/* interrupt vectors */
	int	d_pri;			/* interrupt priority */
	int	d_addr;			/* address of csr */
	int	d_unit;			/* unit number */
	int	d_drive;		/* drive number */
	int	d_slave;		/* slave number */
#define QUES	-1	/* -1 means '?' */
#define UNKNOWN -2	/* -2 means not set yet */
	int	d_dk;			/* if init 1 set to number for iostat */
	int	d_flags;		/* nlags for device init */
	struct	device *d_next;		/* Next one in list */
        u_short d_mach;                 /* Sun - machine type (0 = all)*/
        u_short d_bus;                  /* Sun - bus type (0 = unknown) */
	u_long	d_fields[NFIELDS];	/* fields values (SQT) */
	int	d_bin;			/* interrupt bin (SQT) */
	int	d_addrmod;		/* address modifier (MIPS) */
};
#define TO_NEXUS	(struct device *)-1
#define TO_SLOT		(struct device *)-1

struct config {
	char	*c_dev;
	char	*s_sysname;
};

/*
 * Config has a global notion of which machine type is
 * being used.  It uses the name of the machine in choosing
 * files and directories.  Thus if the name of the machine is ``vax'',
 * it will build from ``Makefile.vax'' and use ``../vax/inline''
 * in the makerules, etc.
 */
int	machine;
char	*machinename;
#define MACHINE_VAX	1
#define MACHINE_SUN	2
#define MACHINE_ROMP	3
#define MACHINE_SUN2	4
#define MACHINE_SUN3	5
#define MACHINE_MMAX	6
#define MACHINE_SQT	7
#define MACHINE_SUN4	8
#define MACHINE_I386	9
#define MACHINE_IX	10
#define MACHINE_MIPSY	11
#define MACHINE_MIPS	12

/*
 * For each machine, a set of CPU's may be specified as supported.
 * These and the options (below) are put in the C flags in the makefile.
 */
struct cputype {
	char	*cpu_name;
	struct	cputype *cpu_next;
} *cputype;

/*
 * In order to configure and build outside the kernel source tree,
 * we may wish to specify where the source tree lives.
 */
char *source_directory;
char *config_directory;
char *object_directory;

FILE *fopenp();
char *get_VPATH();
#define VPATH	get_VPATH()

/*
 * A set of options may also be specified which are like CPU types,
 * but which may also specify values for the options.
 * A separate set of options may be defined for make-style options.
 */
struct opt {
	char	*op_name;
	char	*op_value;
	struct	opt *op_next;
}  *opt,
   *mkopt,
   *opt_tail,
   *mkopt_tail;

char	*ident;
char	*ns();
char	*tc();
char	*qu();
char	*get_word();
char	*path();
char	*raise();

int	do_trace;

char	*index();
char	*rindex();
char	*malloc();
char	*strcpy();
char	*strcat();

#if	MACHINE_VAX
int	seen_mba, seen_uba;
#endif

int	seen_vme, seen_mbii;

struct	device *connect();
struct	device *dtab;
dev_t	nametodev();
char	*devtoname();

char	errbuf[80];
int	yyline;

struct	file_list *ftab, *conf_list, **confp;
char	*PREFIX;

int	timezone, hadtz;
int	dst;
int	profiling;

int	maxusers;
int	maxdsiz;

#define eq(a,b)	(!strcmp(a,b))

#ifdef	mips
#define DEV_MASK 0xf
#define DEV_SHIFT  4
#else	mips
#define DEV_MASK 0x7
#define DEV_SHIFT  3
#endif	mips
