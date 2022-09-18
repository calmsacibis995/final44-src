/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	win_syscall.c,v $
 * Revision 2.5  89/04/22  15:30:54  gm0w
 * 	Fixed up includes/conditionals.
 * 	[89/04/18            gm0w]
 * 
 * Revision 2.4  89/03/09  22:00:18  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  20:07:43  gm0w
 * 	Added new copyright and fixed includes as part of kernel cleanup.
 * 	[89/02/12            jjc]
 * 
 * Revision 2.2  89/01/18  01:13:23  jsb
 * 	Vnode support: keep code that MACH otherwise undefines.
 * 	[89/01/17  10:59:50  jsb]
 * 
 *
 * 23-Sep-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Modified for Mach.
 *
 */
#ifndef	lint
static	char sccsid[] = "@(#)win_syscall.c 1.1 86/02/03 Copyr 1985 Sun Micro";
#endif

/*
 * Copyright (c) 1985 by Sun Microsystems, Inc.
 */

#include <mach_vfs.h>

/*
 * SunWindows kernel equivalents of selected user process level calls,
 * i.e, open and read.
 */
#include <sys/param.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/uio.h>
#include <sys/file.h>
#if	MACH
#include <sys/inode.h>
#else	MACH
#include <sys/vnode.h>
#endif	MACH

/*
 * The kernel_internal_read_workaround flag gets around a problem with kernel
 * internal reads.  The problem is that the read path assumes a user process
 * read and therefore accesses the u structure (e.g., rwip.ufs_vnodeops.c).
 * This messes up the return values from real user level reads so that
 * errno and read(2)'s return value was not set reliably.  The workaround is
 * to save and restore u's read related fields.
 */
int	kernel_internal_read_workaround = 1;

/*
 * Open device for kernel use that user has already opened.
 */
int
kern_openfd(fd, fpp, flag)
	int	fd;
	struct	file **fpp;
	int	flag;
{
	register struct file *fp;
	register int	err = 0;

	*fpp = NULL;
	fp = getf(fd);
	if (fp == 0) {
		printf("getf fp == 0\n");
		return (EINVAL);
	}
#if	MACH && !MACH_VFS
	if (setjmp(&u.u_qsave)) {
		printf("open interrupted\n");
		return(EINTR);
	}
	err = openi((struct inode *)fp->f_data, flag);
	if (err) {
		printf("kern_openfd returned %d\n", err);
		return(err);
	}
#else	MACH && !MACH_VFS
	err = VOP_OPEN((struct vnode **)&fp->f_data, flag, u.u_cred);
	if (err) {
		printf("VOP_OPEN err %d\n", err);
		return (err);
	}
#endif	MACH && !MACH_VFS
	*fpp = fp;
	fp->f_count++;
	return (0);
}

int
kern_read(fp, buf, len_ptr)
	struct	file *fp;
	caddr_t	buf;
	int	*len_ptr;
{
	struct uio auio;
	struct iovec aiov;
	int error;

	aiov.iov_base = buf;
	aiov.iov_len = *len_ptr;
	auio.uio_iov = &aiov;
	auio.uio_iovcnt = 1;
#if	MACH
	auio.uio_segflg = UIO_SYSSPACE;
#else	MACH
	auio.uio_seg = UIOSEG_KERNEL;
#endif	MACH
	auio.uio_resid = *len_ptr;
	auio.uio_offset = fp->f_offset;
	if (kernel_internal_read_workaround) {
		int u_error_save, u_val1_save, u_val2_save;

		u_error_save = u.u_error;
		u_val1_save = u.u_r.r_val1;
		u_val2_save = u.u_r.r_val2;
		error = (*fp->f_ops->fo_rw)(fp, UIO_READ, &auio);
		u.u_error = u_error_save;
		u.u_r.r_val1 = u_val1_save;
		u.u_r.r_val2 = u_val2_save;
	} else
		error = (*fp->f_ops->fo_rw)(fp, UIO_READ, &auio);
	*len_ptr -= auio.uio_resid;
	return (error);
}


