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
 * $Log:	kern_exec.c,v $
 * Revision 2.30.3.6  91/07/15  00:15:25  rvb
 * 	i386: support for 410 and 407 images.  Note: we are slightly
 * 		different than everyone for 410.  ld aligns the virtual 
 * 		data_start even though there is no gap in the file.  Also
 * 		note: for both 407 & 410, we read in the struct exec; like
 * 		we do for 413's.
 * 	[91/07/09            rvb]
 * 
 * Revision 2.30.3.5  90/04/15  11:45:06  rvb
 * 	Hack to make -T 0 work.
 * 	[90/04/10            rvb]
 * 
 * Revision 2.30.3.4  90/03/28  08:30:01  rvb
 * 	i386:	Use low 2 bytes for magic tests.  The high byte is a flag;
 * 	0x01 indicate that a_trsize is really the text relocation which
 * 	is used vs USRTEXT.
 * 	[90/03/26            rvb]
 * 
 * Revision 2.30.3.3  90/03/07  13:25:59  rvb
 * 	af: This ones for you.  i386 coff no longer sets loc 0 to 0.
 * 	[90/03/07            rvb]
 * 
 * Revision 2.30.3.2  90/02/28  15:46:13  rvb
 * 	I386: USRTEXT is now defined in machparam.h [kupfer]
 * 
 * Revision 2.30.3.1  90/02/01  13:33:27  rvb
 *	docoff must always be defined even if SYSV_COFF is off.
 *	[90/01/31            rvb]
 *   
 * Revision 2.30  89/09/09  15:17:56  rvb
 * 	i386: Locking around suiword was incorrect.
 * 	[89/09/07            rvb]
 * 
 * Revision 2.29  89/08/28  22:31:50  af
 * 	In coff_getxfile(), use a current permission of read/write for data
 * 	and only provide execute permission in max protection.
 * 	Besides being semantically more accurate, it helps a lot those architectures
 * 	(mips) with large and incoherent I/D caches, as the I cache does not need
 * 	to be flushed when mapping data pages.
 * 	[89/08/28  17:56:44  af]
 * 
 * Revision 2.28  89/08/08  21:45:17  jsb
 * 	Fix execve to allow both SYSV_COFF and BSD_A_OUT, simultaneously.
 * 	[89/07/31            rvb]
 * 
 * 	Fixed OMAGIC images for mips.
 * 	[89/07/26            af]
 * 
 * Revision 2.27  89/07/17  16:50:34  rvb
 * 	Two small fixes for i386 coff.
 * 
 * Revision 2.28  89/07/17  10:49:44  rvb
 * 	Fix one small i386 typo.
 * 
 * 
 * Revision 2.27  89/07/14  15:25:43  rvb
 * 	Forgot to round size when allocating bss, in coff_getxfile.
 * 	[89/07/07            af]
 * 
 * Revision 2.26  89/07/11  13:07:22  jjc
 * 	Changed execve() for sparc to flush user register windows
 * 	and make sure that stack is aligned.
 * 	Modified sun_getxfile() to start data on next page boundary
 * 	after the text for the Sun 4.
 * 	[88/09/24            jjc]
 * 
 * Revision 2.25  89/05/30  10:32:23  rvb
 * 	My version of coff_getxfile.  Integrates mips in the existing,
 * 	makes it more readable, avoids extra allocation for the text
 * 	segment, does not give up if the front of the bss is larger
 * 	than a page size, uprints more useful warnings if it fails.
 * 	And handles 407 images like they should (the Berkeley way)
 * 	for Mips.
 * 
 * 	Removed useless duplicated program_loader(s) code for BSD_A_OUT.
 * 	Use RCS if you'd like to see what they looked like.
 * 	[89/04/10            af]
 * 
 * Revision 2.24  89/05/09  15:45:37  gm0w
 * 	Replaced vax/sun/ibmrt program loaders with a common version.
 * 	[89/05/08            gm0w]
 * 
 * Revision 2.23  89/04/22  15:19:58  gm0w
 * 	Changed to use new inode macros for manipulation of inodes.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.22  89/03/10  01:27:03  rpd
 * 	More cleanup.
 * 
 * Revision 2.21  89/03/04  17:10:40  rpd
 * 	loader_{round,trunc}_page are used for COFF and BSD with
 * 	LOADER_PAGE_SIZE defined as SECTALIGN for the former.
 * 	[89/03/02            rvb]
 * 
 * Revision 2.20  89/02/27  21:02:16  mrt
 * 	dlb version
 * 	[89/02/26  18:38:02  mrt]
 * 
 * Revision 2.18  89/02/09  04:30:48  mwyoung
 * Code cleanup cataclysm.
 * 
 * Revision 2.17  89/01/30  22:02:37  rpd
 * 	Removed "JSB XXXX STUPIDHEAD BOZO LOSER" code.
 * 	[89/01/26  19:19:06  rpd]
 * 
 * Revision 2.16  89/01/27  10:20:32  rvb
 * 	A few minor fixes to make compilation under i386 work.
 * 	[89/01/27  10:06:53  rvb]
 * 
 * Revision 2.15  89/01/23  22:03:00  af
 * 	Changes for I386: add i386 into mmax coff processing
 * 	[89/01/09            rvb]
 * 
 * Revision 2.14.2.2  89/02/07  00:26:08  dlb
 * 	Remerge and cleanup multimax and i386 code.
 * 	
 * 	Removed "JSB XXXX STUPIDHEAD BOZO LOSER" code.
 * 	[89/01/26  19:19:06  rpd]
 * 	
 * 	Changes for I386: add i386 into mmax coff processing
 * 	[89/01/09            rvb]
 * 	[89/01/31            dlb]
 * 
 * Revision 2.14.2.1  89/01/30  15:07:37  dlb
 * 	Correct zeroing of front of bss on all architectures.
 * 	[89/01/30            dlb]
 * 	
 * 	mmax_getxfile:  Must check aouthdr to figure out what page size
 * 	was used by the loader.
 * 	[88/11/23            dlb]
 * 	
 * 	MACH_VFS: duplicate credentials for setuid/setgid programs in
 * 	mmax_getxfile.
 * 	[88/10/27            dlb]
 * 	
 * 	mmax_getxfile: fix bss base calculation,  Handle bss that fits
 * 	into end of last page of data.
 * 	[88/10/14            dlb]
 * 
 * Revision 2.14  89/01/18  15:10:31  jsb
 * 	Blindly surround with #else/#endif MACH_VFS's all the new
 * 	ilocks/iunlocks that appeared after the merge.
 * 
 * Revision 2.13  89/01/18  00:35:13  jsb
 * 	Vnode support. NOTE: someone still needs to write the code to support
 * 	non-demand-paged executables under vnodes!
 * 	[89/01/13            jsb]
 * 
 * Revision 2.12  88/12/19  02:33:31  mwyoung
 * 	ca, sun3: Removed lint.
 * 	[88/12/17            mwyoung]
 * 	
 * 	Removed old MACH conditionals.
 * 	[88/12/13            mwyoung]
 * 	
 * 	Use copyout on *all* architectures to zero the partial page at
 * 	the end of the data region, to prevent a pagein error from being
 * 	improperly attributed to the kernel.
 * 	[88/11/15            mwyoung]
 * 	
 * 	Apply inode locking changes to all architectures.
 * 	[88/11/03  19:19:47  mwyoung]
 * 	
 * 	Unlock the inode after calling inode_pager_setup(), so that
 * 	the subsequent vm_map call and the copyout of zeroes can
 * 	take faults.
 * 	[88/11/03            mwyoung]
 * 
 * Revision 2.11  88/10/18  03:14:11  mwyoung
 * 	Watch out for zero return value from kmem_alloc_wait.
 * 	[88/09/13            mwyoung]
 * 
 * Revision 2.10  88/10/18  00:27:36  mwyoung
 * 	Oct-10-88 Mary Thompson (mrt) @ Carnegie Mellon
 * 	Changed program_loader for ibmrt to use USRTEXT for
 * 	the start of the text area.
 * 	[88/10/17  16:51:54  mrt]
 * 
 * Revision 2.9  88/10/11  12:06:17  rpd
 * 	Removed the reserving of segment 0 on the RT
 * 	when ROMP+SHARED_SEG option is enabled. Lisp
 * 	counts on using that space. (From sanzi.)
 * 	[88/10/11  12:00:15  rpd]
 * 
 * Revision 2.8  88/08/25  18:09:48  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22            mwyoung]
 * 	
 * 	Fix up arguments to vm_protect.
 * 	[88/08/17  19:54:11  mwyoung]
 * 	
 * 	Convert all architectures to use vm_map.  Correctly release
 * 	inode_pager when errors occur.  Use only user-visible VM calls.
 * 	Reserve all of segment 0 on the RT/PC regardless whether
 * 	the ROMP_SHARED_SEG option is enabled.
 * 	[88/08/15  02:24:35  mwyoung]
 * 	
 * 	Changed Vax getxfile to use vm_map.  Other architectures will
 * 	follow shortly.
 * 	Add inode_pager_release() calls to relinquish port
 * 	rights/reference acquired by inode_pager_setup().
 * 	[88/08/11  18:42:13  mwyoung]
 * 
 * Revision 2.7  88/07/17  17:47:33  mwyoung
 * Use new memory object types.
 * 
 * Revision 2.6  88/07/15  15:28:16  mja
 * Flushed obsolete cs_security.h include.
 * 
 * 16-Jun-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Record stack start, end, and direction of growth.
 *
 * 18-Apr-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Handle zero-size data regions on Sun, Multimax, RT/PC.  [Vax and
 *	Balance both map in text and data together.]  It's unclear to me
 *	why there are two vm_allocate_with_pager's in those getxfile's;
 *	it's probably just for historical reasons.
 *
 *  1-Mar-88  David Black (dlb) at Carnegie-Mellon University
 *	Changed for updated sysV header files.  Use cpp symbols for
 *	multimax and balance.
 *
 * 19-Jan-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	sun3 only: Force page 0 to be allocated and VM_PROTECT_NONE so
 *	noone can use it.  Also change vm_map_find's to vm_allocate.
 *
 * 30-Dec-87  David Golub (dbg) at Carnegie-Mellon University
 *	Delinted.
 *
 *  6-Dec-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Changed inode_pager_setup() calling sequence again.
 *	
 *	Removed ancient history.  Contributors so far: avie, dbg,
 *	mwyoung, bolosky, jjc, dlb, rvb, beck, jjk.
 *
 *  4-Nov-87  David Black (dlb) at Carnegie-Mellon University
 *	Changed multimax to copyout an array of zeroes instead of using
 *	user_zero.
 *
 * 28-Oct-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Added check for security of kernel ports before allowing
 *	setuid/gid changes.
 *
 * 24-Sep-87  David Black (dlb) at Carnegie-Mellon University
 *	Added unix_master(), unix_release() to load_init_program() so it
 *	stays on master throughout exec.
 *
 *  6-Apr-87  David Golub (dbg) at Carnegie-Mellon University
 *	MACH: In vax_getxfile, round up text size separately from data+bss
 *	size.  Some text files (410 format) don't round up sizes
 *	correctly in the image file, but expect exec to do it for them.
 *
 * 05-Mar-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Modified execve() to save a.out header in pcb so it can be
 *	dumped into a core file and used by the debuggers.
 *
 * 12-Jan-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Added "load_init_program()" routine to set up and exec /etc/init.
 *
 *  8-Jan-87  Robert Beck (beck) at Sequent Computer Systems, Inc.
 *	Changed most "#ifdef ns32000"'s to multimax -- COFF stuff.
 *	Mods for balance a.out's -- add balance_getxfile() case and
 *	ZMAGIC magic number recognition.
 *
 *  2-Dec-86  Jay Kistler (jjk) at Carnegie-Mellon University
 *	VICE:  added hooks for ITC/Andrew remote file system.
 *
 *  21-Oct-86  Jonathan J. Chew (jjc) and David Golub (dbg)
 *		at Carnegie-Mellon University
 *	Merged in changes for Sun:
 *		1) Created version of getxfile() for the Sun 3.
 *		2) Don't need signal trampoline code in execve() for Sun.
 *
 *  7-Oct-86  David L. Black (dlb) at Carnegie-Mellon University
 *	ns32000: Merged in Multimax changes; Multimax uses coff format.
 *
 * 11-Jun-86  Bill Bolosky (bolosky) at Carnegie-Mellon University
 *	ibmrt: Added stupid exect() call for adb on the RT.
 *
 * 28-Mar-86  David Golub (dbg) at Carnegie-Mellon University
 *	Remember that the loader's page-size is still
 *	(CLSIZE*NBPG), and that text, data and bss end on the old
 *	page boundaries, not the new ones (or we'd have to relink all
 *	programs whenever we changed the page size!).
 *
 * 23-Nov-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_RFS:  enabled remote namei() processing for all
 *	routines in this module.
 *	[V1(1)]
 *
 * 21-May-85  Glenn Marcy (gm0w) at Carnegie-Mellon University
 *	Upgraded from 4.1BSD.  Carried over changes below.
 *
 *	CMUCS:  Added setting of execute only bit and clearing of
 *	trace bit in process status if image is not readable (V3.00).
 *	[V1(1)]
 *
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)kern_exec.c	7.1 (Berkeley) 6/5/86
 */
 
#include <cputypes.h>
#include <mach_rfs.h>
#include <vice.h>
#include <bsd_a_out.h>
#include <sysv_coff.h>

#include <machine/reg.h>
#ifdef	ibmrt
#include <ca/scr.h>
#endif	ibmrt

#if	defined(vax) || defined(i386)
#include <machine/psl.h>
#endif	defined(vax) || defined(i386)

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/map.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/kernel.h>
#include <sys/proc.h>
#include <sys/buf.h>
#include <sys/inode.h>
#include <sys/vm.h>
#include <sys/file.h>
#include <sys/uio.h>
#include <sys/acct.h>
#include <sys/exec.h>


#if	SYSV_COFF
/*
 *	Fileheaders for coff files.
 */
#include <sysV/scnhdr.h>
#include <sysV/aouthdr.h>
#include <sysV/filehdr.h>
#endif	SYSV_COFF

#ifdef	mips
#include <sys/ptrace.h>
#endif	mips


/*
 *  Force all namei() calls to permit remote names since this module has
 *  been updated.
 */
#if	MACH_RFS
#undef	namei
#define namei	rnamei
#endif	MACH_RFS

#ifdef	ibmrt
#include <ca/debug.h>
#endif	ibmrt

#ifdef	sun4
#include <sun4/asm_linkage.h>
#endif	sun4

#include <sys/signal.h>
#include <kern/task.h>
#include <kern/thread.h>

#include <mach/vm_param.h>
#include <vm/vm_map.h>
#include <vm/vm_object.h>
#include <mach/memory_object.h>
#include <builtin/inode_pager.h>
#include <vm/vm_kern.h>
#include <vm/vm_user.h>
#include <kern/zalloc.h>

#include <kern/parallel.h>


#if	BSD_A_OUT
/*
 * All of these silly loader_page_size's should be moved into a machine
 * dependent directory, for obvious reasons.  -BB
 */
#ifdef	vax
#define LOADER_PAGE_SIZE	(1024)
#endif	vax
#if	defined(ibmrt) || defined(balance)
#define LOADER_PAGE_SIZE	(2048)
#endif	defined(ibmrt) || defined(balance)
#ifdef	sun
#define LOADER_PAGE_SIZE	(8192)
#endif	sun
#ifdef	i386
#define	LOADER_PAGE_SIZE	SECTALIGN
#endif	i386
#endif	BSD_A_OUT

#if	SYSV_COFF
/*
 *	Corresponding definitions are in coff_getxfile because the
 *	section size (SECTALIGN, corresponds to LOADER_PAGE_SIZE)
 *	must be obtained from the file header for some architectures.
 */

#define LOADER_PAGE_SIZE	SECTALIGN
#endif	SYSV_COFF

#define loader_round_page(x)	((vm_offset_t)((((vm_offset_t)(x)) \
						+ LOADER_PAGE_SIZE - 1) \
					& ~(LOADER_PAGE_SIZE-1)))
#define loader_trunc_page(x)	((vm_offset_t)(((vm_offset_t)(x)) \
					& ~(LOADER_PAGE_SIZE-1)))

#ifdef	i386
int SECTALIGN;	/* coff: ((vm_offset_t)4096); bsd: ((vm_offset_t)4096)*/
#endif	i386

/*
 *	A corrupted fileheader can cause getxfile to decide to bail
 *	out without setting up the address space correctly.  It is
 *	essential in this case that control never get back to the
 *	user.  The following error code is used by getxfile to tell
 *	execve that the process must be killed.
 */

#define EGETXFILE	126

/*
 * exec system call, with and without environments.
 */
struct execa {
	char	*fname;
	char	**argp;
	char	**envp;
};

execv()
{
	((struct execa *)u.u_ap)->envp = NULL;
	execve();
}

#ifdef	ibmrt
exect()	/* New RXTUnix system call for execve with single step active */
{
	execve();
	if( u.u_error );
	else u.u_ar0[ICSCS] |= ICSCS_INSTSTEP;
}
#endif	ibmrt

execve()
{
	register nc;
	register char *cp;
	register struct execa *uap;
	int na, ne, ucp, ap, cc;
	unsigned len;
	int indir, uid, gid;
	char *sharg, *dirp;
	struct inode *ip;
	DECLARE_EXECVE_LOCALS;
#if	VICE
	struct file *fp = NULL;
#endif	VICE
	vm_offset_t exec_args;
#define SHSIZE	32
	char cfarg[SHSIZE];
	union {
		char	ex_shell[SHSIZE];  /* #! and name of interpreter */
#if	SYSV_COFF
		/* 
		 * Coff fileheader structures.
		 */
		struct {
			struct filehdr fhdr;
			struct aouthdr ohdr;
#define ahdr exdata.coff.ohdr
		} coff;
		struct {
			short	magic;
		} coff_hdr;
#endif	SYSV_COFF
#if	BSD_A_OUT
		struct	exec ex_exec;
#endif	BSD_A_OUT
	} exdata;
	int resid, error;
#if	SYSV_COFF
	int	aouthdr_offset;
#endif	SYSV_COFF
	int	docoff = 0;

	uap = (struct execa *)u.u_ap;
	LOOKUP_EXECVE_NAME(uap->fname, ip);
	exec_args = 0;
	indir = 0;
	uid = u.u_uid;
	gid = u.u_gid;
	VERIFY_SETUID(ip);

  again:
	if (CHECK_ACCESS(ip, IEXEC))
		goto bad;
	if ((u.u_procp->p_flag&STRC) && CHECK_ACCESS(ip, IREAD))
		goto bad;
	if (!INODE_TYPE(ip,REG) ||
	   (INODE_MODE(ip) & (IEXEC|(IEXEC>>3)|(IEXEC>>6))) == 0) {
		u.u_error = EACCES;
		goto bad;
	}

	/*
	 *	Read in the header to get magic number.
	 *	This magic number is architecture-dependent.
	 */
	exdata.ex_shell[0] = '\0';	/* for zero length files */
	u.u_error = RDWRI(UIO_READ, ip, (caddr_t)&exdata,
			SHSIZE, (off_t)0, UIO_SYSSPACE, &resid);
	if (u.u_error)
		goto bad;
	if (resid && exdata.ex_shell[0] != '#') {
		u.u_error = ENOEXEC;
		goto bad;
	}

#if	BSD_A_OUT
	/*
	 * Read in first few bytes of file for segment sizes, magic number:
	 *	407 = plain executable
	 *	410 = RO text
	 *	413 = demand paged RO text
	 * Also an ASCII line beginning with #! is
	 * the file name of a ``shell'' and arguments may be prepended
	 * to the argument list if given here.
	 *
	 * SHELL NAMES ARE LIMITED IN LENGTH.
	 *
	 * ONLY ONE ARGUMENT MAY BE PASSED TO THE SHELL FROM
	 * THE ASCII LINE.
	 */
#ifdef	i386
#define MAGIC(x) (((x).a_magic) & 0xffff)
#else	i386
#define MAGIC(x)  ((x).a_magic)
#endif	i386
	if (MAGIC(exdata.ex_exec) == 0413 ||
	    MAGIC(exdata.ex_exec) == 0410) {
		if (exdata.ex_exec.a_text == 0) {
			u.u_error = ENOEXEC;
			goto bad;
		}
		goto gotbsd;
	} else
	if (MAGIC(exdata.ex_exec) == 0407) {
		exdata.ex_exec.a_data += exdata.ex_exec.a_text;
		exdata.ex_exec.a_text = 0;
		goto gotbsd;
	} else
#ifdef	balance
	if (MAGIC(exdata.ex_exec) == 0x10ea) {	/* ZMAGIC: 0@0 */
						/* no XMAGIC yet */
		exdata.ex_exec.a_magic &= ~0xffff;/* make other code easier */
		exdata.ex_exec.a_magic |= 0413;	/* make other code easier */
		if (exdata.ex_exec.a_text == 0) {
			u.u_error = ENOEXEC;
			goto bad;
		}
		goto gotbsd;
	} else
#endif	balance
#endif	BSD_A_OUT
#if	SYSV_COFF
#ifdef	i386
	if (exdata.coff_hdr.magic == I386MAGIC) {
		aouthdr_offset = sizeof(struct filehdr);
		goto gotcoff;
	} else
#endif	i386
#ifdef	multimax
	if (exdata.coff_hdr.magic == N16WRMAGIC ||
	    exdata.coff_hdr.magic == N16ROMAGIC) {
		aouthdr_offset = N16FILHSZ;
		goto gotcoff;
	} else if (exdata.coff_hdr.magic == NS32GMAGIC ||
		   exdata.coff_hdr.magic == NS32SMAGIC) {
		aouthdr_offset = FILHSZ;
		goto gotcoff;
	} else
#endif	multimax
#ifdef	mips
	if (exdata.coff_hdr.magic == MIPSMAGIC) {
		aouthdr_offset = FILHSZ;
		goto gotcoff;
	} else
#endif	mips
#endif	SYSV_COFF
	/*
	 *	Common code for handling shell scripts.
	 */
	{
		if (exdata.ex_shell[0] != '#' ||
		    exdata.ex_shell[1] != '!' ||
		    indir) {
			u.u_error = ENOEXEC;
			goto bad;
		}
		cp = &exdata.ex_shell[2];		/* skip "#!" */
		while (cp < &exdata.ex_shell[SHSIZE]) {
			if (*cp == '\t')
				*cp = ' ';
			else if (*cp == '\n') {
				*cp = '\0';
				break;
			}
			cp++;
		}
		if (*cp != '\0') {
			u.u_error = ENOEXEC;
			goto bad;
		}
		cp = &exdata.ex_shell[2];
		while (*cp == ' ')
			cp++;
		dirp = cp;
		while (*cp && *cp != ' ')
			cp++;
		cfarg[0] = '\0';
		if (*cp) {
			*cp++ = '\0';
			while (*cp == ' ')
				cp++;
			if (*cp)
				bcopy((caddr_t)cp, (caddr_t)cfarg, SHSIZE);
		}
		indir = 1;
		FINISH_WITH_INODE(ip);
		ip = (struct inode *)0;
		LOOKUP_SHELL_NAME(dirp, ip);
		goto again;
	}

#if	SYSV_COFF
gotcoff:
	/*
	 * Now read in the second (a.out) header for segment sizes
	 * and magic number:
	 *	407 = plain executable
	 *	410 = RO text
	 *	413 = demand paged RO text
	 *
	 * XXX On some machines, 407 here does not
	 * XXX mean what 407 means under BSD_A_OUT.  This code
	 * XXX may need to be fixed for those machines.
	 */
	docoff = 1;
	u.u_error = RDWRI(UIO_READ, ip, (caddr_t)&ahdr,
		sizeof(struct aouthdr), aouthdr_offset, UIO_SYSSPACE, &resid);
	if (u.u_error)
		goto bad;

#ifdef	mips
	/*
	 * check for unaligned entry point
	 */
	if (ahdr.entry & (sizeof(int)-1)) {
		u.u_error = ENOEXEC;
		goto bad;
	}
#endif	mips

	switch (ahdr.magic) {
	    case 0407: /* XXX */
#ifdef	mips
		/* We do it right:
		 * Do not make text read-only, e.g. put it in the data section
		 * Note that by definition text and data are contiguous both
		 * in the file and in memory.
		 */
		ahdr.data_start = ahdr.text_start;
		ahdr.dsize += ahdr.tsize;
		ahdr.tsize = 0;
		break;
#endif	mips
	    case 0410:
	    case 0413:
		if (ahdr.tsize == 0) {
			u.u_error = ENOEXEC;
			goto bad;
		}
		break;

	    default:
		u.u_error = ENOEXEC;
		goto bad;
	}
#ifdef mips
	/*
	 * Enforce (artificial) addressability limit: this covers
	 * a chip bug.
	 */
	if ((ahdr.text_start < VM_MIN_ADDRESS) || 
	      (ahdr.data_start < VM_MIN_ADDRESS)) {
		u.u_error = ENOEXEC;
		goto bad;
	}
#endif	mips
#ifdef	multimax
	/*
	 *	XXX Alignment flags don't get set in N16 fileheaders.
	 */
	if (aouthdr_offset == N16FILHSZ)
		ahdr.flags |= U_AL_1024;
#endif	multimax
#endif	SYSV_COFF

gotbsd:

#ifdef	i386
	SECTALIGN = docoff ? ((vm_offset_t)4096) : ((vm_offset_t)4096);
#endif	i386

	/*
	 * Collect arguments on "file" in swap space.
	 */
	na = 0;
	ne = 0;
	nc = 0;
	cc = 0;
	UNLOCK_INODE(ip);
	exec_args = kmem_alloc_wait(kernel_pageable_map, NCARGS);
	if (exec_args == 0)
		panic("execve: cannot allocate arguments");
	cp = (char *) exec_args;	/* running pointer for copy */
	cc = NCARGS;			/* size of exec_args */
	/*
	 * Copy arguments into file in argdev area.
	 */
	if (uap->argp) for (;;) {
		ap = NULL;
		sharg = NULL;
		if (indir && na == 0) {
			sharg = EXECVE_SHARG;
			ap = (int)sharg;
			uap->argp++;		/* ignore argv[0] */
		} else if (indir && (na == 1 && cfarg[0])) {
			sharg = cfarg;
			ap = (int)sharg;
		} else if (indir && (na == 1 || na == 2 && cfarg[0]))
			ap = (int)uap->fname;
		else if (uap->argp) {
			ap = fuword((caddr_t)uap->argp);
			uap->argp++;
		}
		if (ap == NULL && uap->envp) {
			uap->argp = NULL;
			if ((ap = fuword((caddr_t)uap->envp)) != NULL)
				uap->envp++, ne++;
		}
		if (ap == NULL)
			break;
		na++;
		if (ap == -1) {
			u.u_error = EFAULT;
			break;
		}
		do {
			if (nc >= NCARGS-1) {
				error = E2BIG;
				break;
			}
			if (sharg) {
				error = copystr(sharg, cp, (unsigned)cc, &len);
				sharg += len;
			} else {
				error = copyinstr((caddr_t)ap, cp, (unsigned)cc,
				    &len);
				ap += len;
			}
			cp += len;
			nc += len;
			cc -= len;
		} while (error == ENOENT);
		if (error) {
			u.u_error = error;
			LOCK_INODE(ip);
			goto badarg;
		}
	}
	LOCK_INODE(ip);
	nc = (nc + NBPW-1) & ~(NBPW-1);
#ifdef	sun
	/*
	 *	Save a.out header for Sun debuggers
	 */
	current_thread()->pcb->pcb_exec = exdata.ex_exec;
#endif	sun

#if	SYSV_COFF
	if (docoff)
		coff_getxfile(ip, &exdata.coff.fhdr, &ahdr, nc + (na+4)*NBPW, uid, gid);
	else {
#endif	SYSV_COFF

#if	BSD_A_OUT
#ifdef	sparc
	/*
	 * Make sure user register windows are empty before attempting to
	 * make a new stack.
	 */
		flush_user_windows();
		getxfile(ip, &exdata.ex_exec, 
			SA(nc + (na+4)*NBPW + sizeof (struct rwindow)), uid, gid);
#else	sparc
		getxfile(ip, &exdata.ex_exec, nc + (na+4)*NBPW, uid, gid);
#endif	sparc
#endif	BSD_A_OUT
#if	SYSV_COFF
	}
#endif	SYSV_COFF

	if (u.u_error) {
badarg:
	/*
	 *	NOTE: to prevent a race condition, getxfile had
	 *	to temporarily unlock the inode.  If new code needs to
	 *	be inserted here before the iput below, and it needs
	 *	to deal with the inode, keep this in mind.
	 */
		goto bad;
	}
	FINISH_WITH_INODE(ip);
	ip = NULL;
#if	VICE
	if (u.u_textfile)
		closef(u.u_textfile);
	u.u_textfile = fp;
	fp = NULL;
#endif	VICE

	/*
	 * Copy back arglist.
	 */
#ifdef mips
	ucp = USRSTACK - nc - NBPW - EA_SIZE;
	ap = ucp - na*NBPW - 3*NBPW;
	if (ap & 0xf) {
		int fudge;

		fudge = ap - (ap & ~0xf);
		ap -= fudge;
		ucp -= fudge;
	}
	u.u_ar0[EF_SP] = ap;
#else	mips
	ucp = USRSTACK - nc - NBPW;
#ifdef sparc
        /*
         * Keep stack aligned and leave room for initial reg window on sparc.
         */
        ap = USRSTACK - SA(nc + (na+4)*NBPW);
        u.u_ar0[SP] = ap - sizeof (struct rwindow);
#else	sparc
	ap = ucp - na*NBPW - 3*NBPW;
#ifdef	i386
	u.u_ar0[UESP] = ap;
#else	i386
	u.u_ar0[SP] = ap;
#endif	i386
#endif	sparc
#endif mips
	(void) suword((caddr_t)ap, na-ne);
	nc = 0;
	cc = 0;
	cp = (char *) exec_args;
	cc = NCARGS;
	for (;;) {
		ap += NBPW;
		if (na == ne) {
			(void) suword((caddr_t)ap, 0);
			ap += NBPW;
		}
		if (--na < 0)
			break;
		(void) suword((caddr_t)ap, ucp);
		do {
			error = copyoutstr(cp, (caddr_t)ucp, (unsigned)cc,
			    &len);
			ucp += len;
			cp += len;
			nc += len;
			cc -= len;
		} while (error == ENOENT);
		if (error == EFAULT)
			panic("exec: EFAULT");
	}
	(void) suword((caddr_t)ap, 0);

	/*
	 * Reset caught signals.  Held signals
	 * remain held through p_sigmask.
	 */
	while (u.u_procp->p_sigcatch) {
		nc = ffs((long)u.u_procp->p_sigcatch);
		u.u_procp->p_sigcatch &= ~sigmask(nc);
		u.u_signal[nc] = SIG_DFL;
	}
	/*
	 * Reset stack state to the user stack.
	 * Clear set of signals caught on the signal stack.
	 */
	u.u_onstack = 0;
	u.u_sigsp = 0;
	u.u_sigonstack = 0;

	for (nc = u.u_lastfile; nc >= 0; --nc) {
		if (u.u_pofile[nc] & UF_EXCLOSE) {
			closef(u.u_ofile[nc]);
			u.u_ofile[nc] = NULL;
			u.u_pofile[nc] = 0;
		}
		u.u_pofile[nc] &= ~UF_MAPPED;
	}
	while (u.u_lastfile >= 0 && u.u_ofile[u.u_lastfile] == NULL)
		u.u_lastfile--;
#if	SYSV_COFF
	if (docoff)
#ifdef	multimax
		setregs(ahdr.entry, ahdr.mod_start);
#endif	multimax
#if	defined(i386) || defined(mips)
		setregs(ahdr.entry);
#endif	defined(i386) || defined(mips)
	else {
#endif	SYSV_COFF
#if	BSD_A_OUT
		setregs(exdata.ex_exec.a_entry);
#endif	BSD_A_OUT
#if	SYSV_COFF
	}
#endif	SYSV_COFF
#ifdef	vax
	{
		/*
		 *	This belongs in vax.setregs()
		 */
		extern int nsigcode[5];

		bcopy((caddr_t)nsigcode,
		      (caddr_t)(VM_MAX_ADDRESS - sizeof(nsigcode)),
		      sizeof(nsigcode));
	}
#endif	vax
#ifdef	ibmrt
	{
	    	/*
		 *	sigcode[] must agree with declaration in pcb.h
		 *
		 *	sigcode goes at the bottom of the user_stack,
		 *	where, of course, the user's stack can grow
		 *	down on top of it, but this seems unlikely.
		 *	Putting it at the top makes ps(1) unhappy.
		 */
		extern int sigcode[3];
		bcopy((caddr_t)sigcode,
		      (caddr_t)SIGCODE_ADDRESS,
		      sizeof(sigcode));
	}
#endif	ibmrt

	/*
	 * Remember file name for accounting.
	 */
	u.u_acflag &= ~AFORK;
	SET_COMM_NAME();
bad:
	error = u.u_error;
	EXECVE_FREE_PATH();
	if (exec_args != 0)
		kmem_free_wakeup(kernel_pageable_map, exec_args, NCARGS);
	if (ip)
		FINISH_WITH_INODE(ip);
	if (u.u_error == 0)
		u.u_error = error;
#if	VICE
	if (fp)
		closef(fp);
#endif	VICE
	if (u.u_error == EGETXFILE) {
		struct proc	*p;

		/* 
		 *	getxfile failed, kill the current process.
		 *	Send SIGKILL, blow away other pending signals.
		 */
		p = u.u_procp;
		p->p_sig = sigmask(SIGKILL);
		p->p_cursig = SIGKILL;
		u.u_sig = 0;
		u.u_cursig = 0;
		psig();		/* Bye */
	}
}

#if	BSD_A_OUT
/*
 * Read in and set up memory for executed file.
 */
getxfile(ip, ep, nargc, uid, gid)
	struct inode *ip;
	struct exec *ep;
	int nargc, uid, gid;
{
	size_t ts, ds, ss;
	int pagi;
	vm_size_t	text_size, data_size;

	if (MAGIC(*ep) == 0413)
		pagi = SPAGI;
	else
		pagi = 0;

	/*
	 *	The vm system handles text that is modified
	 *	for tracing - we don't have to worry about it.
	 */

	if (MAGIC(*ep) != 0407 && (ip->i_flag&ITEXT) == 0 &&
	    ip->i_count != 1) {
		register struct file *fp;

		for (fp = file; fp < fileNFILE; fp++) {
#if	VICE
			if ((fp->f_type == DTYPE_INODE ||
			     fp->f_type == DTYPE_VICEINO) &&
#else	VICE
			if (fp->f_type == DTYPE_INODE &&
#endif	VICE
			    fp->f_count > 0 &&
			    (struct inode *)fp->f_data == ip &&
			    (fp->f_flag&FWRITE)) {
				u.u_error = ETXTBSY;
				goto bad;
			}
		}
	}

	/*
	 * Compute text and data sizes and make sure not too large.
	 * NB - Check data and bss separately as they may overflow 
	 * when summed together.
	 */
	text_size = loader_round_page(ep->a_text);	/* bytes */
	ts = btoc(text_size);				/* machine pages */
	data_size = loader_round_page(ep->a_data + ep->a_bss);
							/* bytes */
	ds = btoc(data_size);				/* machine pages */
	ss = SSIZE + btoc(loader_round_page(nargc));
	u.u_procp->p_flag &= ~(SPAGI|SSEQL|SUANOM|SOUSIG|SXONLY);
	if (INODE_ACCESS(ip,READ))
	{
		u.u_procp->p_flag |= SXONLY;
		u.u_procp->p_flag &= ~STRC;
		u.u_error = 0;
	}
	u.u_procp->p_flag |= pagi;
#define unix_stack_size	(u.u_rlimit[RLIMIT_STACK].rlim_cur)

	program_loader(ip, ep, pagi);
	/*
	 * set SUID/SGID protections, if no tracing
	 */
	if ((u.u_procp->p_flag&STRC)==0) {
		if (uid != u.u_uid || gid != u.u_gid)
			u.u_identity = change_identity(u.u_identity);
		u.u_uid = uid;
		u.u_procp->p_uid = uid;
		u.u_gid = gid;
	} else
		psignal(u.u_procp, SIGTRAP);
	u.u_tsize = ts;
	u.u_dsize = ds;
	u.u_ssize = ss;
	u.u_prof.pr_scale = 0;
bad:
	return;
}
#endif	BSD_A_OUT

#if	SYSV_COFF
/*
 * Version of getxfile for machines that use the Common Object File Format.
 * Some vendors have their own idea of what COFF is supposed to be, so
 * we have still machine-dependencies here.
 */
coff_getxfile(ip, fhd, ap, nargc, uid, gid)
	struct inode *ip;
	struct filehdr *fhd;
	struct aouthdr *ap;
	int nargc, uid, gid;
{
	size_t ts, ds, ss;
	int pagi;
	vm_offset_t	addr;
	vm_size_t	size;
	vm_map_t	my_map;
	vm_offset_t	offset;
	vm_offset_t	vm_text_start, vm_text_end;
	vm_offset_t	vm_data_start, vm_data_end;
	vm_offset_t	vm_end;

#ifdef	multimax
	vm_offset_t	sectalign;

	/*
	 *	Page size used by loader is encoded in flags field.
	 *	Only 1024 and 4096 are supported currently.
	 */
	if (ap->flags & U_AL_1024)
		sectalign = 1024;
	else if (ap->flags & U_AL_4096)
		sectalign = 4096;
	else {
		u.u_error = ENOEXEC;
		goto bad;
	}

#define SECTALIGN		sectalign
#define NOPAGI_TEXT_OFFSET	SECTALIGN
#define NOPAGI_DATA_OFFSET	(SECTALIGN + ap->tsize)
#define PAGI_TEXT_OFFSET	SECTALIGN
#define PAGI_DATA_OFFSET	(SECTALIGN + loader_round_page(ap->tsize))
#endif	multimax

#ifdef	i386
#define NOPAGI_TEXT_OFFSET	((fhd->f_nscns * sizeof(struct scnhdr)) + \
				 sizeof(struct filehdr) + fhd->f_opthdr)
#define NOPAGI_DATA_OFFSET	(NOPAGI_TEXT_OFFSET + ap->tsize)
#define PAGI_TEXT_OFFSET	0
#define PAGI_DATA_OFFSET	trunc_page(ap->text_start + ap->tsize)
#endif	i386

#ifdef	mips
#define SECTALIGN		((vm_offset_t)4096)
#define NOPAGI_TEXT_OFFSET	N_TXTOFF(*fhd, *ap)
#define NOPAGI_DATA_OFFSET	(N_TXTOFF(*fhd, *ap) + ap->tsize)
#define PAGI_TEXT_OFFSET	NOPAGI_TEXT_OFFSET
#define PAGI_DATA_OFFSET	NOPAGI_DATA_OFFSET
#endif	mips

	/*
	 *	Check pageability.
	 */
	if (ap->magic == 0413)
		pagi = SPAGI;
	else
		pagi = 0;

	/*
	 *	The vm system handles text that is modified
	 *	for tracing - we do not have to worry about it.
	 */

	if (ap->magic != 0407 && (ip->i_flag&ITEXT) == 0 &&
	    ip->i_count != 1) {
		register struct file *fp;

		for (fp = file; fp < fileNFILE; fp++) {
			if (fp->f_type == DTYPE_INODE &&
			    fp->f_count > 0 &&
			    (struct inode *)fp->f_data == ip &&
			    (fp->f_flag&FWRITE))
			{
				u.u_error = ETXTBSY;
				goto bad;
			}
		}
	}

	/*
	 * Compute text, data and stack sizes.
	 */

	ts = btoc(loader_round_page(ap->tsize));
	ds = btoc(loader_round_page(ap->bsize + ap->dsize));
	ss = SSIZE + btoc(loader_round_page(nargc));

	u.u_procp->p_flag &= ~(SPAGI|SSEQL|SUANOM|SOUSIG|SXONLY);
	if (INODE_ACCESS(ip,READ))
	{
		u.u_procp->p_flag |= SXONLY;
		u.u_procp->p_flag &= ~STRC;
		u.u_error = 0;
	}
	u.u_procp->p_flag |= pagi;

#define unix_stack_size	(u.u_rlimit[RLIMIT_STACK].rlim_cur)

	my_map = current_task()->map;
	/*
	 *	Even if we are execing the same image (the RFS server
	 *	does this, for example), we do not have to unlock the
	 *	inode; deallocating it does not require it to be locked.
	 */
	(void) vm_deallocate(my_map, vm_map_min(my_map),
		vm_map_max(my_map)-vm_map_min(my_map));
	
	/*
	 *	Allocate low-memory stuff: text, data, bss.
	 *	Read text and data into lowest part, then make text read-only.
	 */

	/*
	 *	Remember where text and data start.
	 */
	u.u_text_start = (caddr_t) ap->text_start;
	u.u_data_start = (caddr_t) trunc_page(ap->data_start);

	/*
	 *	Note vm boundaries for data and text segments.  If data
	 *	and text overlap a page, that is considered data.
	 *
	 */
	vm_text_start = trunc_page(ap->text_start);
	vm_text_end = round_page(ap->text_start + ap->tsize);
	vm_data_start = trunc_page(ap->data_start);
	vm_data_end = round_page(ap->data_start + ap->dsize);
	vm_end = round_page(ap->data_start + ap->dsize + ap->bsize);
#ifdef	i386
	ds = btoc(round_page(ap->data_start + ap->dsize + ap->bsize) - vm_data_start);
#endif	i386
	if (vm_text_end > vm_data_start)
		vm_text_end = vm_data_start;

	u.u_error = 0;

	if (pagi == 0) {
		/*
		 * Not demand paged.
		 * In 407 images the code is not read-protected.
		 */
		/*
		 *	Allocate and read in the data segment (0407 & 0410).
		 */
		if (ap->dsize <= 0)
			goto read_text;	/* pure text and sanity */
		addr = vm_data_start;
		size = vm_end - vm_data_start;	/* include bss */
		if (vm_allocate(my_map, &addr, size, FALSE) != KERN_SUCCESS) {
			uprintf("%s: Data section too big.\n", u.u_comm);
			goto suicide;
		}

		/*
		 *	Read in the data segment (0407 & 0410).  It goes on
		 *	the next loader_page boundary after the text.
		 */
		u.u_error = RDWRI(UIO_READ, ip,
				(caddr_t) ap->data_start,
				(int) ap->dsize,
				NOPAGI_DATA_OFFSET,
				UIO_USERSPACE, (int *)0);
		/*
		 *	Allocate and read in text segment, and read-protect it
		 *	if necessary (0410).
		 */
read_text:
		if ((u.u_error == 0) && (ap->tsize > 0)) {
			addr = vm_text_start;
			size = vm_text_end - vm_text_start;
			if (vm_allocate(my_map, &addr, size, FALSE) != KERN_SUCCESS) {
				uprintf("%s: Text section too big.\n", u.u_comm);
				goto suicide;
			}
			u.u_error = RDWRI(UIO_READ, ip,
				(caddr_t) ap->text_start,
				(int) ap->tsize,
				NOPAGI_TEXT_OFFSET,
				UIO_USERISPACE, (int *) 0);
			if ((u.u_error == 0) && (ap->magic != 0407)) {
				(void) vm_protect(my_map,
					vm_text_start,
					vm_text_end - vm_text_start,
					FALSE,
					VM_PROT_READ|VM_PROT_EXECUTE);
			}
		}
	}
	else {
		memory_object_t	pager;

		/*
		 *	Allocate a region backed by the execed inode.
		 */

		pager = (memory_object_t)inode_pager_setup(ip, TRUE, TRUE);
		UNLOCK_INODE(ip);

		/*
		 *	Map the text segment.
		 */
		if (ap->tsize <= 0)
			goto map_data;	/* sanity */
		if (vm_map(my_map, &vm_text_start,
			vm_text_end - vm_text_start, 0, FALSE,
			pager, PAGI_TEXT_OFFSET, TRUE,
			VM_PROT_READ|VM_PROT_EXECUTE,
			VM_PROT_ALL, VM_INHERIT_COPY)
		          != KERN_SUCCESS) {
				uprintf("%s: Cannot map text.\n",u.u_comm);
				inode_pager_release(pager);
				LOCK_INODE(ip);
				goto suicide;
		}
		/*
		 *	Map the data segment, if any.
		 */
map_data:
		if (vm_data_end > vm_data_start) {
			if (vm_map(my_map, &vm_data_start,
			    vm_data_end - vm_data_start, 0, FALSE, pager,
			    PAGI_DATA_OFFSET,
			    TRUE, VM_PROT_READ|VM_PROT_WRITE,
			    VM_PROT_ALL, VM_INHERIT_COPY)
			      != KERN_SUCCESS) {
				uprintf("%s: Cannot map data.\n", u.u_comm);
				inode_pager_release(pager);
				LOCK_INODE(ip);
				goto suicide;
			}
		}

		inode_pager_release(pager);
		LOCK_INODE(ip);

		/*
		 *	Allocate bss.  First check whether any more is needed.
		 */

		
		size =  vm_end - vm_data_end;
		if ( (long)size > 0 ) {			/* == missing     */
			addr = vm_data_end;
			if (vm_allocate(my_map, &addr, size, FALSE)
			    != KERN_SUCCESS) {
				    uprintf("%s: Cannot allocate space for bss.\n", u.u_comm);
				    goto suicide;
			}
			vm_protect(my_map, addr, size, FALSE, VM_PROT_READ|VM_PROT_WRITE);
		}

		/*
		 *	If the data segment does not end on a VM page
		 *	boundary, we have to clear the remainder of the VM
		 *	page it ends on so that the bss segment will
		 *	(correctly) be zero.
		 */
		addr = ap->data_start + ap->dsize;
		if (vm_data_end > addr) {
			UNLOCK_INODE(ip);
			{ vm_size_t num_zeroes;
			  do {
				num_zeroes = MIN( PAGE_SIZE, vm_data_end - addr);
				if (copyout(vm_kern_zero_page, (caddr_t)addr,  num_zeroes)) {
					LOCK_INODE(ip);
					uprintf("%s: Cannot zero front of BSS.\n", u.u_comm);
					goto suicide;
				}
				addr += num_zeroes;
			  } while (addr < vm_data_end);
			}
			LOCK_INODE(ip);
		}
	}

	/*
	 *	Create the stack.  (Deallocate the old one and create a 
	 *	new one).
	 */

	size = round_page(unix_stack_size);
	u.u_stack_start = (caddr_t) (addr = trunc_page(VM_MAX_ADDRESS - size));
	u.u_stack_end = u.u_stack_start + size;
	u.u_stack_grows_up = FALSE;
	(void) vm_deallocate(my_map, addr, size);
	if (vm_allocate(my_map, &addr, size, FALSE) != KERN_SUCCESS) {
		uprintf("%s: Cannot find space for stack.\n", u.u_comm);
		goto suicide;
	}

	/*
	 * set SUID/SGID protections, if no tracing
	 */
	if ((u.u_procp->p_flag&STRC)==0) {
		if (uid != u.u_uid || gid != u.u_gid)
			u.u_identity = change_identity(u.u_identity);
		u.u_uid = uid;
		u.u_procp->p_uid = uid;
		u.u_gid = gid;
	} else {
#ifdef	mips
		current_thread()->pcb->trapcause = CAUSEEXEC;
#endif	mips
		psignal(u.u_procp, SIGTRAP);
	}
	u.u_tsize = ts;
	u.u_dsize = ds;
	u.u_ssize = ss;
	u.u_prof.pr_scale = 0;
bad:
	return;
suicide:
	u.u_error = EGETXFILE;
	return;
}
#endif	SYSV_COFF

/*
 *	BSD_A_OUT program loaders follow.
 */

#if	BSD_A_OUT
#if	defined(vax) || defined(sun) || defined(ibmrt) || defined(i386)

/*
 *	FILE_OFFSET is how much of the file to skip when the page
 *	containing the a.out header is not part of the loaded image.
 *	This is not true on the SUN.
 */
#if	defined(vax) || defined(ibmrt)
#define	FILE_OFFSET	LOADER_PAGE_SIZE
#endif	vax || ibmrt
#if	defined(sun) || defined(i386)
#define	FILE_OFFSET	0	/* beware - not LOADER_PAGE_SIZE on SUN */

int allow_0_reference = 0;
#endif	defined(sun) || defined(i386)

program_loader(ip, ep, pagi)
	struct inode	*ip;
	struct exec	*ep;
	int		pagi;
{
	memory_object_t	pager;
	vm_map_t	my_map;
	vm_offset_t	addr;
	vm_size_t	size;
	vm_offset_t	text_start;
	vm_offset_t	data_start;
	vm_size_t	loader_text_size;
	vm_size_t	loader_data_size;
	vm_size_t	text_size;
	vm_size_t	data_size;
	vm_size_t	data_bss_size;
	vm_size_t	real_text_size;
	vm_size_t	real_data_size;

	my_map = current_task()->map;

	/*
	 *	Even if we are exec'ing the same image (the RFS server
	 *	does this, for example), we don't have to unlock the
	 *	inode; deallocating it doesn't require it to be locked.
	 */
	(void) vm_deallocate(my_map, vm_map_min(my_map),
			vm_map_max(my_map) - vm_map_min(my_map));
	
	/*
	 *	Make copy of exec header fields that we might want
	 *	to modify.
	 */
	real_text_size = ep->a_text;
	real_data_size = ep->a_data;
#ifdef	i386
	if (ep->a_text)		/* == 0 => 407 */
		real_text_size += sizeof (struct exec);
#define	BELIEVE_A_OUT 1
#endif	i386

	/*
	 *	On the VAX, the loader aligns the text and data so
	 *	that we cannot protect all of the text.  Therefore,
	 *	we adjust the text/data sizes so that the text size
	 *	corresponds to the part we can protect and the data
	 *	size includes the text we cannot protect.
	 */
#if	defined(vax)
	if (pagi) {
		size = loader_round_page(real_text_size)-
		    trunc_page(real_text_size);
		real_text_size -= size;
		real_data_size += size;
	}
#endif	defined(vax)
#ifdef	BELIEVE_A_OUT
	loader_text_size = real_text_size;
	loader_data_size = real_data_size;
#else	BELIEVE_A_OUT
	loader_text_size = loader_round_page(real_text_size);
	loader_data_size = loader_round_page(real_data_size);
#endif	BELIEVE_A_OUT

	/*
	 *	Since the data starts immediately on the next loader
	 *	page boundary, we cannot round the text size up to
	 *	the next memory size on the VAX.
	 */
#ifdef	vax
	text_size = loader_text_size;
#endif	vax
#if	defined(sun) || defined(ibmrt) || defined(i386)
	text_size = round_page(real_text_size);
#endif	defined(sun) || defined(ibmrt) || defined(i386)

	data_size = round_page(real_data_size);
	data_bss_size = round_page(real_data_size+ep->a_bss);
	text_start = USRTEXT;
#ifdef	i386
#define A_RELOC 0x01000000
	if (ep->a_magic & A_RELOC) {
		if (!ep->a_trsize) {
			uprintf("strange text relocation\n");
		}
		text_start = ep->a_trsize;
	}
#endif	i386
	if (pagi == 0 && ep->a_text == 0)
		data_start = text_start;
	else {
#ifdef	vax
		/* data immediately after text */
		data_start = text_size;
#endif	vax
#ifdef	sun3
		/* data into next segment boundary after text */
		data_start = ((text_start+text_size+SGOFSET)&~SGOFSET);
#endif	sun3
#ifdef	sun4
		if (pagi == 0)
			data_start = ((text_start+text_size+SGOFSET)&~SGOFSET);
		else
			data_start = round_page(text_start + text_size);
#endif	sun4
#ifdef	ibmrt
		/* data into fixed data segment */
		data_start = 0x10000000;
#endif	ibmrt
#ifdef	i386
		data_start = ((text_start+text_size+(PAGE_SIZE-1))&~(PAGE_SIZE-1));
		if ((ep->a_magic & A_RELOC) && ep->a_drsize)
			data_start = ep->a_drsize;
#endif	i386
	}

#ifdef	sun
	if (pagi && trunc_page(text_start) != text_start) {
		uprintf("text doesn't start on page boundary.\n");
		goto suicide;
	}
#endif	sun

	/*
	 *	Remember text and data starting points.
	 */
	u.u_text_start = (caddr_t)text_start;
	u.u_data_start = (caddr_t)data_start;
#ifdef	vax
	if (pagi) u.u_data_start += size; /* adjust for change above */
#endif	vax

	u.u_error = 0;

	if (pagi == 0) {
#ifdef	i386
		int offset = 0;
#		define TEXT_SIZE_410(x) round_page(x)
#else	i386
		int offset = sizeof (struct exec);
#		define TEXT_SIZE_410(x) trunc_page(x)
#endif	i386
		/*
		 *	Not demand paged.
		 *
		 *	Allocate space for image.
		 */
		if (text_size + data_bss_size > 0) {
			addr = trunc_page(data_start);
			size = data_bss_size + data_start - addr;
			if (size > 0 &&
			    vm_allocate(my_map, &addr, size, FALSE)
			    != KERN_SUCCESS) {
				uprintf("Cannot find space for data+bss.\n");
				goto suicide;
			}
			addr = text_start;
			size = TEXT_SIZE_410(text_size);
			if (size > 0 &&
			    vm_allocate(my_map, &addr, size, FALSE)
			    != KERN_SUCCESS) {
				uprintf("Cannot find space for text.\n");
				goto suicide;
			}
		}

		/*
		 *	Read in the data segment (0407 & 0410).
		 */
		if (real_data_size) {
			u.u_error = RDWRI(UIO_READ, ip,
					(caddr_t)data_start,
					(int)real_data_size,
					(off_t)offset+real_text_size,
					0, (int *)0);
		}

		/*
		 *	Read in text segment if necessary (0410),
		 *	and read-protect it.
		 */
		if ((u.u_error == 0) && (real_text_size > 0)) {
			u.u_error = RDWRI(UIO_READ, ip,
				(caddr_t) text_start,
				(int)real_text_size,
				(off_t)offset, 2, (int *) 0);
			if (u.u_error == 0 && TEXT_SIZE_410(text_size) > 0) {
				(void) vm_protect(my_map,
					 text_start,
					 TEXT_SIZE_410(text_size),
					 FALSE,
					 VM_PROT_READ|VM_PROT_EXECUTE);
			}
		}
	}
	else {
		/*
		 *	Allocate a region backed by the exec'ed inode.
		 */
		pager = (memory_object_t)inode_pager_setup(ip, TRUE, TRUE);
		UNLOCK_INODE(ip);

		/*
		 *	Map the text segment.
		 */
		addr = text_start;
		if (text_size != 0) {
			if (vm_map(my_map, &addr, text_size, 0, FALSE,
			    pager, (vm_offset_t) FILE_OFFSET, TRUE,
			    VM_PROT_READ|VM_PROT_EXECUTE, VM_PROT_ALL, VM_INHERIT_COPY)
			    != KERN_SUCCESS) {
				inode_pager_release(pager);
				uprintf("Cannot map text into user address space\n");
				LOCK_INODE(ip);
				goto suicide;
			}
		}

		/*
		 *	Now map in the data segment.
		 */
		addr = data_start;
		if (data_size != 0) {
			if (vm_map(my_map, &addr, data_size, 0, FALSE,
				pager, (vm_offset_t) loader_text_size+FILE_OFFSET,
				TRUE, VM_PROT_ALL, VM_PROT_ALL, VM_INHERIT_COPY)
			     != KERN_SUCCESS) {
				inode_pager_release(pager);
				uprintf("Cannot map data into user space.\n");
				LOCK_INODE(ip);
				goto suicide;
			}
			addr += data_size;
		}

		inode_pager_release(pager);
		LOCK_INODE(ip);

		/*
		 *	Allocate the remainder of the BSS segment.
		 */
		size = data_bss_size - data_size;
		if (size != 0 &&
		    vm_allocate(my_map, &addr, size, FALSE)!= KERN_SUCCESS) {
		    	uprintf("Cannot allocate BSS in user address space\n");
			goto suicide;
		}

		/*
		 *	If the data segment does not end on a VM page
		 *	boundary, we have to clear the remainder of the VM
		 *	page it ends on so that the bss segment will
		 *	(correctly) be zero.
		 *	The loader has already guaranteed that the (text+data)
		 *	segment ends on a loader_page boundary.
		 */
		addr = data_start + loader_data_size;
		size = data_size - loader_data_size;
		if (size > 0) {
			UNLOCK_INODE(ip);
			if (copyout(vm_kern_zero_page, (caddr_t)addr, size)) {
				uprintf("Cannot zero partial data page\n");
				LOCK_INODE(ip);
				goto suicide;
			}
			LOCK_INODE(ip);
		}
	}

	/*
	 *	Reprotect just text page 0 to NONE.  (Actually, for an 
	 *	i386, it's everything below the start of text.)
	 */
#if	defined(sun) || defined(i386)
#define PROT (allow_0_reference ? VM_PROT_READ : VM_PROT_NONE)
	addr = 0;
	if (text_start && vm_map(my_map, &addr, text_start, 0, FALSE,
		MEMORY_OBJECT_NULL, (vm_offset_t) 0, FALSE,
		VM_PROT_NONE, VM_PROT_NONE, VM_INHERIT_SHARE)
	     != KERN_SUCCESS) {
		uprintf("Cannot reserve [0 .. %x].\n", text_start);
		goto suicide;
	}
#endif	defined(sun) || defined(i386)

	/*
	 *	Create the stack.
	 *	(Deallocate the old one and create a new one).
	 */
	size = round_page(unix_stack_size);
	addr = trunc_page(VM_MAX_ADDRESS - size);
	u.u_stack_start = (caddr_t) addr;
	u.u_stack_end = u.u_stack_start + size;
	u.u_stack_grows_up = FALSE;
	(void) vm_deallocate(my_map, addr, size);
	if (vm_allocate(my_map, &addr, size, FALSE) != KERN_SUCCESS) {
		uprintf("Cannot find space for stack.\n");
		goto suicide;
	}

	return;

suicide:
	u.u_error = EGETXFILE;
	return;
}
#endif	vax || sun || ibmrt || i386

#ifdef	balance
/*
 * balance_getxfile()
 *	Loader for Sequent Balance (ns32000) object files.
 *
 * Code derived from VAX version in getxfile().
 *
 * Magic number ZMAGIC has already been converted to 0413.  No XMAGIC yet.
 * Assumes "pagi".
 *
 * Balance a.out's assume the code is loaded at 0x800, and text/data are
 * rounded to 2k boundaries.  The header is loaded at 0x800 as part of the
 * text, to avoid wasting space.  0 -> 0x7ff are filled with read-only
 * zero pages (ZMAGIC).  When/if there is XMAGIC, 0->0x7ff needs to
 * be totally invalid.
 *
 * ep->a_text includes the low 2k of address space; the file doesn't, however.
 */

#define LOADER_LOWBYTES	LOADER_PAGE_SIZE	/* start of address space not */
						/* backed by file */

program_loader(ip, ep, pagi)
	struct inode	*ip;
	struct exec	*ep;
	int		pagi;
{
	register vm_map_t	my_map;
	register kern_return_t	ret;
	register vm_size_t	copy_size;
	register vm_offset_t	copy_end;
	register vm_offset_t	data_end;
	vm_size_t	bss_size;
	memory_object_t	pager;
	vm_offset_t	addr;
	vm_offset_t	low_delta;
	long		size;

#ifdef	lint
	pagi++;
#endif	lint

	/*
	 * Need to know how much larger MACH page is than LOADER_LOWBYTES.
	 */

	if (PAGE_SIZE > LOADER_LOWBYTES)
		low_delta = PAGE_SIZE - LOADER_LOWBYTES;
	else
		low_delta = 0;

	my_map = current_task()->map;

	(void) vm_deallocate(my_map, vm_map_min(my_map),
			vm_map_max(my_map) - vm_map_min(my_map));
	
	/*
	 *	Remember text and data starting points
	 */
	u.u_text_start = USRTEXT;
	u.u_data_start = (caddr_t) loader_round_page(ep->a_text);

	u.u_error = 0;

	/*
	 * Allocate a region backed by the exec'ed inode.
	 *
	 * copy_size is set to that part of the file that will be page-aligned
	 * in the addresss space (ie, after LOADER_LOWBYTES).  Thus, if
	 * LOADER_LOWBYTES < PAGE_SIZE, the beginning of the file is not
	 * part of the "copy" map.
	 */

	copy_size = round_page(ep->a_text + ep->a_data - PAGE_SIZE);
	if (ep->a_text+ep->a_data > PAGE_SIZE) {
		pager = (memory_object_t)inode_pager_setup(ip, TRUE, TRUE);
		iunlock(ip);
		addr = VM_MIN_ADDRESS + round_page(LOADER_LOWBYTES),
		ret = vm_map(my_map, &addr, copy_size, 0, FALSE,
			     pager, low_delta, TRUE,
			     VM_PROT_ALL, VM_PROT_ALL, VM_INHERIT_COPY);

		ilock(ip);
		inode_pager_release(pager);

		if (ret != KERN_SUCCESS) {
			uprintf("Unable to map text/data.\n");
			goto suicide;
		}
	}

	/*
	 *	Allocate the blank area preceding the text
	 */

	addr = VM_MIN_ADDRESS;
	if (vm_allocate(my_map, &addr, round_page(LOADER_LOWBYTES), FALSE)
	    != KERN_SUCCESS) {
	    	uprintf("Cannot allocate low bytes region\n");
		goto suicide;
	}

	/*
	 * If the loader page-size < PAGE_SIZE, need to read the
	 * first part of the file into place.  Do this before write-protext
	 * the text, since we must write on it.
	 */

	if (low_delta) {
		int	resid;
		ret = RDWRI(UIO_READ, ip,
				(caddr_t) LOADER_LOWBYTES, (int) low_delta,
				(off_t) 0, UIO_USERISPACE, &resid);
		if (ret != KERN_SUCCESS) {
			uprintf("Could not read first page of text.\n");
			goto suicide;
		}
	}

	/*
	 * Read-protect just the text region.  Do this before we zero
	 * the bss area, so that we have only one copy of the text.
	 */

	(void) vm_protect(my_map,
		 VM_MIN_ADDRESS,
		 trunc_page(ep->a_text),
		 FALSE,
		 VM_PROT_READ|VM_PROT_EXECUTE);

	/*
	 * If the data segment does not end on a VM page boundary,
	 * we have to clear the remainder of the VM page it ends
	 * on so that the bss segment will (correctly) be zero.
	 * The loader has already guaranteed that the (text+data)
	 * segment ends on a loader_page boundary.
	 */

	data_end = VM_MIN_ADDRESS + loader_round_page(ep->a_text + ep->a_data);
	copy_end = VM_MIN_ADDRESS + round_page(LOADER_LOWBYTES) + copy_size;
	if (copy_end > data_end) {
		if(copy_end-data_end > PAGE_SIZE) {
			uprintf("Cannot clear front of bss segment.\n");
			goto suicide;
		}
		iunlock(ip);
		if (copyout(vm_kern_zero_page, (caddr_t)data_end, copy_end - data_end)) {
			ilock(ip);
			uprintf("Cannot zero partial data page\n");
			goto suicide;
		}
		ilock(ip);
	}

	/*
	 *	Allocate the BSS region
	 */

	bss_size = round_page(ep->a_text + ep->a_data + ep->a_bss) - copy_end;
	addr = copy_end;
	if (bss_size != 0) {
		if (vm_allocate(my_map, &addr, bss_size, FALSE) != KERN_SUCCESS) {
			uprintf("Cannot allocate BSS region\n");
			goto suicide;
		}
	}

	/*
	 * Create the stack.  (Deallocate the old one and create a new one).
	 *
	 * Is it really necessary to deallocate the old stack?  The
	 * vm_map_remove() done above should have deleted the entire
	 * address space.  This one might make some data/bss dissappear,
	 * though.
	 */

	size = round_page(unix_stack_size);
	u.u_stack_start = (caddr_t) (addr = trunc_page(VM_MAX_ADDRESS - size));
	u.u_stack_end = u.u_stack_start + size;
	u.u_stack_grows_up = FALSE;
	(void) vm_deallocate(my_map, addr, size);
	if (vm_allocate(my_map, &addr, size, FALSE) != KERN_SUCCES) {
		uprintf("Cannot create stack.\n");
		goto suicide;
	}
	return;

suicide:
	u.u_error = EGETXFILE;
	return;
}
#endif	balance

#endif	BSD_A_OUT

#include <sys/reboot.h>

char		init_program_name[128] = "/etc/mach_init\0";

char		init_args[128] = "-sa\0";
struct execa	init_exec_args;
int		init_attempts = 0;

void load_init_program()
{
	vm_offset_t	init_addr;
	vm_size_t	init_size;
	int		*old_ap;
	char		*argv[3];

	unix_master();

	u.u_error = 0;

#ifndef	mips
	init_args[1] = (boothowto & RB_SINGLE) ? 's' : 'x';
	init_args[2] = (boothowto & RB_ASKNAME) ? 'a' : 'x';
#endif	mips
	
	do {
#if	defined(balance) || defined(multimax) || defined(i386)
		if (init_attempts == 2)
			panic("Can't load init");
#else	defined(balance) || defined(multimax) || defined(i386)
		if (boothowto & RB_INITNAME) {
			printf("init program? ");
			gets(init_program_name);
		}
#endif	defined(balance) || defined(multimax) || defined(i386)

		if (u.u_error && ((boothowto & RB_INITNAME) == 0) &&
					(init_attempts == 1)) {
			static char other_init[] = "/etc/init";
			u.u_error = 0;
			bcopy(other_init, init_program_name,
							sizeof(other_init));
		}

		init_attempts++;

		if (u.u_error) {
			printf("Load of %s failed, errno %d\n",
					init_program_name, u.u_error);
			u.u_error = 0;
			boothowto |= RB_INITNAME;
		}

		/*
		 *	Copy out program name.
		 */

		init_size = round_page(sizeof(init_program_name) + 1);
		init_addr = VM_MIN_ADDRESS;
		(void) vm_allocate(current_task()->map, &init_addr, init_size, TRUE);
		if (init_addr == 0)
			init_addr++;
		(void) copyout((caddr_t) init_program_name,
				(caddr_t) (init_addr),
				(unsigned) sizeof(init_program_name));

		argv[0] = (char *) init_addr;

		/*
		 *	Put out first (and only) argument, similarly.
		 */

		init_size = round_page(sizeof(init_args) + 1);
		init_addr = VM_MIN_ADDRESS;
		(void) vm_allocate(current_task()->map, &init_addr, init_size, TRUE);
		if (init_addr == 0)
			init_addr++;
		(void) copyout((caddr_t) init_args,
				(caddr_t) (init_addr),
				(unsigned) sizeof(init_args));

		argv[1] = (char *) init_addr;

		/*
		 *	Null-end the argument list
		 */

		argv[2] = (char *) 0;
		
		/*
		 *	Copy out the argument list.
		 */
		
		init_size = round_page(sizeof(argv));
		init_addr = VM_MIN_ADDRESS;
		(void) vm_allocate(current_task()->map, &init_addr, init_size, TRUE);
		(void) copyout((caddr_t) argv,
				(caddr_t) (init_addr),
				(unsigned) sizeof(argv));

		/*
		 *	Set up argument block for fake call to execve.
		 */

		init_exec_args.fname = argv[0];
		init_exec_args.argp = (char **) init_addr;
		init_exec_args.envp = 0;

		old_ap = u.u_ap;
		u.u_ap = (int *) &init_exec_args;
		execve();
		u.u_ap = old_ap;
	} while (u.u_error);

	unix_release();
}

