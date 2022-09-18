/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	vfs_sysnames.c,v $
 * Revision 2.4  92/02/05  22:25:29  mja
 * 	Call VOP_RMDIR with the translation of @sys rather than
 * 	VOP_REMOVE in vop_rmdir() to fix "rmdir @sys" bug.
 * 	[92/02/05            lily]
 * 
 * Revision 2.3  91/09/24  19:56:04  mja
 * 	Modified for AFS 3.1
 * 	[91/07/19  16:39:17  dimitris]
 * 
 * Revision 2.2  89/09/05  20:45:43  jsb
 * 	Created from vfs/vfs_vnode.c. Implements @sys for all filesystems,
 * 	with semantics less bogus than those of AFS.
 * 	[89/09/05  15:13:03  jsb]
 * 
 */
#include <mach_afs.h>
#include <mach_nfs.h>

#include <sys/user.h>
#include <sys/inode.h>

#include <vfs/vfs_sysnames.h>
#define	get_sysname()	SYS_NAME

/*
 *  Namestublen is length of name with trailing "@sys" removed.
 */
#define	NO_SYSNAME(name)	\
	( ((namestublen = strlen(name) - 4) < 0) \
	|| (strcmp(name + namestublen, "@sys")))

char *
vop_handle_sysname(name, namestublen)
	char *name;
	int namestublen;
{
	char *sysname;
	char *newname;
	int sysnamelen;

	sysname = get_sysname();
	sysnamelen = strlen(sysname);
	ZALLOC(vfs_name_zone, newname, char *);
	bcopy(name, newname, namestublen);
	bcopy(sysname, newname + namestublen, sysnamelen + 1);
	return newname;
}

#undef	VOP_LOOKUP
#undef	VOP_CREATE
#undef	VOP_REMOVE
#undef	VOP_LINK
#undef	VOP_RENAME
#undef	VOP_MKDIR
#undef	VOP_RMDIR
#undef	VOP_SYMLINK

#define VOP_LOOKUP(VP,NM,VPP,C)		(*_VOP_(VP)->vn_lookup)(VP,NM,VPP,C)
#define VOP_CREATE(VP,NM,VA,E,M,VPP,C)	(*_VOP_(VP)->vn_create) \
						(VP,NM,VA,E,M,VPP,C)
#define VOP_REMOVE(VP,NM,C)		(*_VOP_(VP)->vn_remove)(VP,NM,C)
#define VOP_LINK(VP,TDVP,TNM,C)		(*_VOP_(VP)->vn_link)(VP,TDVP,TNM,C)
#define VOP_RENAME(VP,NM,TDVP,TNM,C)	(*_VOP_(VP)->vn_rename) \
						(VP,NM,TDVP,TNM,C)
#define VOP_MKDIR(VP,NM,VA,VPP,C)	(*_VOP_(VP)->vn_mkdir)(VP,NM,VA,VPP,C)
#define VOP_RMDIR(VP,NM,C)		(*_VOP_(VP)->vn_rmdir)(VP,NM,C)
#define VOP_SYMLINK(VP,LNM,VA,TNM,C)	(*_VOP_(VP)->vn_symlink) \
						(VP,LNM,VA,TNM,C)

/*
 *  The following operations will retry with @sys unexpanded if operation
 *  on expanded name fails with ENOENT:
 *
 *	VOP_LOOKUP
 *	VOP_REMOVE
 *	VOP_RMDIR
 *	VOP_RENAME
 */
vop_lookup(dvp, name, vpp, cred)
	struct vnode *dvp;
	char *name;
	struct vnode **vpp;
	struct ucred *cred;
{
	char *newname;
	int namestublen, rv;

	if (NO_SYSNAME(name)) {
		return VOP_LOOKUP(dvp, name, vpp, cred);
	}
	newname = vop_handle_sysname(name, namestublen);
	rv = VOP_LOOKUP(dvp, newname, vpp, cred);
	ZFREE(vfs_name_zone, newname);
	if (rv == ENOENT) {
		rv = VOP_LOOKUP(dvp, name, vpp, cred);
	}
	return rv;
}

vop_remove(vp, name, cred)
	struct vnode *vp;
	char *name;
	struct ucred *cred;
{
	char *newname;
	int namestublen, rv;

	if (NO_SYSNAME(name)) {
		return VOP_REMOVE(vp, name, cred);
	}
	newname = vop_handle_sysname(name, namestublen);
	rv = VOP_REMOVE(vp, newname, cred);
	ZFREE(vfs_name_zone, newname);
	if (rv == ENOENT) {
		rv = VOP_REMOVE(vp, name, cred);
	}
	return rv;
}

vop_rmdir(vp, name, cred)
	struct vnode *vp;
	char *name;
	struct ucred *cred;
{
	char *newname;
	int namestublen, rv;

	if (NO_SYSNAME(name)) {
		return VOP_RMDIR(vp, name, cred);
	}
	newname = vop_handle_sysname(name, namestublen);
	rv = VOP_RMDIR(vp, newname, cred);
	ZFREE(vfs_name_zone, newname);
	if (rv == ENOENT) {
		rv = VOP_RMDIR(vp, name, cred);
	}
	return rv;
}

vop_rename(sdvp, name1, tdvp, name2, cred)
	struct vnode *sdvp;
	char *name1;
	struct vnode *tdvp;
	char *name2;
	struct ucred *cred;
{
	char *newname1, *newname2;
	int namestublen, rv;

	if (NO_SYSNAME(name1)) {
		newname1 = name1;
	} else {
		newname1 = vop_handle_sysname(name1, namestublen);
	}
	if (NO_SYSNAME(name2)) {
		newname2 = name2;
	} else {
		newname2 = vop_handle_sysname(name2, namestublen);
	}
	rv = VOP_RENAME(sdvp, newname1, tdvp, newname2, cred);
	if (rv == ENOENT) {
		rv = VOP_RENAME(sdvp, name1, tdvp, newname2, cred);
	}
	if (name1 != newname1) {
		ZFREE(vfs_name_zone, newname1);
	}
	if (name2 != newname2) {
		ZFREE(vfs_name_zone, newname2);
	}
	return rv;
}

/*
 *  The following operations will always expand @sys:
 *
 *	VOP_CREATE
 *	VOP_LINK
 *	VOP_MKDIR
 *	VOP_SYMLINK
 */

vop_create(dvp, name, vap, excl, mode, vpp, cred)
	struct vnode *dvp;
	char *name;
	struct vattr *vap;
	enum vcexcl excl;
	int mode;
	struct vnode **vpp;
	struct ucred *cred;
{
	char *newname;
	int namestublen, rv;

	if (NO_SYSNAME(name)) {
		return VOP_CREATE(dvp, name, vap, excl, mode, vpp, cred);
	}
	newname = vop_handle_sysname(name, namestublen);
	rv = VOP_CREATE(dvp, newname, vap, excl, mode, vpp, cred);
	ZFREE(vfs_name_zone, newname);
	return rv;
}

vop_link(vp, tdvp, name, cred)
	struct vnode *vp;
	struct vnode *tdvp;
	char *name;
	struct ucred *cred;
{
	char *newname;
	int namestublen, rv;

	if (NO_SYSNAME(name)) {
		return VOP_LINK(vp, tdvp, name, cred);
	}
	newname = vop_handle_sysname(name, namestublen);
	rv = VOP_LINK(vp, tdvp, newname, cred);
	ZFREE(vfs_name_zone, newname);
	return rv;
}

vop_mkdir(dvp, name, vap, vpp, cred)
	struct vnode *dvp;
	char *name;
	register struct vattr *vap;
	struct vnode **vpp;
	struct ucred *cred;
{
	char *newname;
	int namestublen, rv;

	if (NO_SYSNAME(name)) {
		return VOP_MKDIR(dvp, name, vap, vpp, cred);
	}
	newname = vop_handle_sysname(name, namestublen);
	rv = VOP_MKDIR(dvp, newname, vap, vpp, cred);
	ZFREE(vfs_name_zone, newname);
	return rv;
}

vop_symlink(dvp, name, vap, tname, cred)
	struct vnode *dvp;
	char *name;
	struct vattr *vap;
	char *tname;
	struct ucred *cred;
{
	char *newname;
	int namestublen, rv;

	if (NO_SYSNAME(name)) {
		return VOP_SYMLINK(dvp, name, vap, tname, cred);
	}
	newname = vop_handle_sysname(name, namestublen);
	rv = VOP_SYMLINK(dvp, newname, vap, tname, cred);
	ZFREE(vfs_name_zone, newname);
	return rv;
}
