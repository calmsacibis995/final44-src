h07662
s 00000/00001/00225
d D 8.5 95/05/11 20:15:24 mckusick 9 8
c vclean is static to vfs_subr.c
e
s 00011/00005/00215
d D 8.4 95/03/30 14:12:18 mckusick 8 7
c replace initialization of vfssw with vfsconf
e
s 00001/00002/00219
d D 8.3 94/01/04 18:45:12 bostic 7 6
c lint
e
s 00004/00000/00217
d D 8.2 93/12/30 16:22:45 mckusick 6 5
c add hook to initialize vnode table data structures
e
s 00002/00002/00216
d D 8.1 93/06/10 22:00:37 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00001/00218
d D 7.4 92/07/21 01:04:50 mckusick 4 3
c no need to define vfreeh and vfreet
e
s 00000/00001/00219
d D 7.3 92/07/12 23:41:49 pendry 3 2
c no longer need specdev
e
s 00037/00056/00183
d D 7.2 92/07/06 17:12:56 mckusick 2 1
c put into KNF
e
s 00239/00000/00000
d D 7.1 92/06/23 15:33:10 mckusick 1 0
c date and time created 92/06/23 15:33:10 by mckusick
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed
 * to Berkeley by John Heidemann of the UCLA Ficus project.
 *
 * Source: * @(#)i405_init.c 2.10 92/04/27 UCLA Ficus project
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */


#include <sys/param.h>
#include <sys/mount.h>
#include <sys/time.h>
#include <sys/vnode.h>
#include <sys/stat.h>
D 3
#include <sys/specdev.h>
E 3
#include <sys/namei.h>
#include <sys/ucred.h>
#include <sys/buf.h>
#include <sys/errno.h>
#include <sys/malloc.h>

D 2

/* Sigh, such primitive tools are these... */
E 2
I 2
/*
 * Sigh, such primitive tools are these...
 */
E 2
#if 0
#define DODEBUG(A) A
#else
#define DODEBUG(A)
#endif

D 2


E 2
extern struct vnodeopv_desc *vfs_opv_descs[];
				/* a list of lists of vnodeops defns */
extern struct vnodeop_desc *vfs_op_descs[];
				/* and the operations they perform */
/*
 * This code doesn't work if the defn is **vnodop_defns with cc.
 * The problem is because of the compiler sometimes putting in an
 * extra level of indirection for arrays.  It's an interesting
 * "feature" of C.
 */
int vfs_opv_numops;

typedef (*PFI)();   /* the standard Pointer to a Function returning an Int */

D 2


E 2
/*
 * A miscellaneous routine.
 * A generic "default" routine that just returns an error.
 */
int
vn_default_error()
{
D 2
	return EOPNOTSUPP;
E 2
I 2

	return (EOPNOTSUPP);
E 2
}

D 2



E 2
/*
 * vfs_init.c
 *
 * Allocate and fill in operations vectors.
 *
D 2
 * An undocumented feature of this approach to defining
 * operations is that there can be multiple entries in
 * vfs_opv_descs for the same operations vector.
 * This allows third parties to extend the set of operations
 * supported by another layer in a binary compatibile way.
 * For example, assume that NFS needed to be modified to support
 * Ficus.  NFS has an entry (probably nfs_vnopdeop_decls)
 * declaring all the operations NFS supports by default.
 * Ficus could add another entry (ficus_nfs_vnodeop_decl_entensions)
 * listing those new operations Ficus adds to NFS, all without
 * modifying the NFS code.  (Of couse, the OTW NFS protocol
 * still needs to be munged, but that's a(whole)nother story.)
 * This is a feature.
E 2
I 2
 * An undocumented feature of this approach to defining operations is that
 * there can be multiple entries in vfs_opv_descs for the same operations
 * vector. This allows third parties to extend the set of operations
 * supported by another layer in a binary compatibile way. For example,
 * assume that NFS needed to be modified to support Ficus. NFS has an entry
 * (probably nfs_vnopdeop_decls) declaring all the operations NFS supports by
 * default. Ficus could add another entry (ficus_nfs_vnodeop_decl_entensions)
 * listing those new operations Ficus adds to NFS, all without modifying the
 * NFS code. (Of couse, the OTW NFS protocol still needs to be munged, but
 * that is a(whole)nother story.) This is a feature.
E 2
 */
D 2

E 2
void
vfs_opv_init()
{
	int i, j, k;
D 7
	struct vnodeop_defn *defnp;
E 7
	int (***opv_desc_vector_p)();
	int (**opv_desc_vector)();
	struct vnodeopv_entry_desc *opve_descp;

	/*
	 * Allocate the dynamic vectors and fill them in.
	 */
	for (i=0; vfs_opv_descs[i]; i++) {
		opv_desc_vector_p = vfs_opv_descs[i]->opv_desc_vector_p;
		/*
		 * Allocate and init the vector, if it needs it.
		 * Also handle backwards compatibility.
		 */
		if (*opv_desc_vector_p == NULL) {
			/* XXX - shouldn't be M_VNODE */
			MALLOC(*opv_desc_vector_p, PFI*,
			       vfs_opv_numops*sizeof(PFI), M_VNODE, M_WAITOK);
			bzero (*opv_desc_vector_p, vfs_opv_numops*sizeof(PFI));
D 2
			DODEBUG(printf("vector at %x allocated\n", opv_desc_vector_p));
		};
E 2
I 2
			DODEBUG(printf("vector at %x allocated\n",
			    opv_desc_vector_p));
		}
E 2
		opv_desc_vector = *opv_desc_vector_p;
		for (j=0; vfs_opv_descs[i]->opv_desc_ops[j].opve_op; j++) {
			opve_descp = &(vfs_opv_descs[i]->opv_desc_ops[j]);

			/*
			 * Sanity check:  is this operation listed
			 * in the list of operations?  We check this
			 * by seeing if its offest is zero.  Since
			 * the default routine should always be listed
			 * first, it should be the only one with a zero
			 * offset.  Any other operation with a zero
			 * offset is probably not listed in
D 2
			 * vfs_op_descs,
			 * and so is probably an error.
E 2
I 2
			 * vfs_op_descs, and so is probably an error.
E 2
			 *
			 * A panic here means the layer programmer
			 * has committed the all-too common bug
			 * of adding a new operation to the layer's
			 * list of vnode operations but
			 * not adding the operation to the system-wide
			 * list of supported operations.
			 */
			if (opve_descp->opve_op->vdesc_offset == 0 &&
				    opve_descp->opve_op->vdesc_offset !=
				    	VOFFSET(vop_default)) {
D 2
				printf ("error: operation %s not listed in vfs_op_descs.\n", opve_descp->opve_op->vdesc_name);
E 2
I 2
				printf("operation %s not listed in %s.\n",
				    opve_descp->opve_op->vdesc_name,
				    "vfs_op_descs");
E 2
				panic ("vfs_opv_init: bad operation");
D 2
			};
E 2
I 2
			}
E 2
			/*
			 * Fill in this entry.
			 */
D 2
			opv_desc_vector[opve_descp->opve_op->vdesc_offset]=
E 2
I 2
			opv_desc_vector[opve_descp->opve_op->vdesc_offset] =
E 2
					opve_descp->opve_impl;
D 2
		};
	};

E 2
I 2
		}
	}
E 2
	/*
	 * Finally, go back and replace unfilled routines
	 * with their default.  (Sigh, an O(n^3) algorithm.  I
	 * could make it better, but that'd be work, and n is small.)
	 */
D 2
	for (i=0; vfs_opv_descs[i]; i++) {
E 2
I 2
	for (i = 0; vfs_opv_descs[i]; i++) {
E 2
		opv_desc_vector = *(vfs_opv_descs[i]->opv_desc_vector_p);
		/*
		 * Force every operations vector to have a default routine.
		 */
		if (opv_desc_vector[VOFFSET(vop_default)]==NULL) {
			panic("vfs_opv_init: operation vector without default routine.");
D 2
		};
		for (k=0; k<vfs_opv_numops; k++)
E 2
I 2
		}
		for (k = 0; k<vfs_opv_numops; k++)
E 2
			if (opv_desc_vector[k] == NULL)
				opv_desc_vector[k] = 
					opv_desc_vector[VOFFSET(vop_default)];
D 2
	};
E 2
I 2
	}
E 2
}

D 2



E 2
I 2
/*
 * Initialize known vnode operations vectors.
 */
E 2
void
vfs_op_init()
{
D 7
	int i, j;
E 7
I 7
	int i;
E 7

D 2
	DODEBUG(printf ("Vnode_interface_init.\n"));

E 2
I 2
	DODEBUG(printf("Vnode_interface_init.\n"));
E 2
	/*
	 * Set all vnode vectors to a well known value.
	 */
D 2
	for (i=0; vfs_opv_descs[i]; i++)
E 2
I 2
	for (i = 0; vfs_opv_descs[i]; i++)
E 2
		*(vfs_opv_descs[i]->opv_desc_vector_p) = NULL;
D 2

	vfs_opv_numops = 0;

E 2
	/*
	 * Figure out how many ops there are by counting the table,
	 * and assign each its offset.
	 */
D 2
	for (i=0; vfs_op_descs[i]; i++) {
E 2
I 2
	for (vfs_opv_numops = 0, i = 0; vfs_op_descs[i]; i++) {
E 2
		vfs_op_descs[i]->vdesc_offset = vfs_opv_numops;
		vfs_opv_numops++;
D 2
	};

E 2
I 2
	}
E 2
	DODEBUG(printf ("vfs_opv_numops=%d\n", vfs_opv_numops));
}
D 2






E 2

/*
 * Routines having to do with the management of the vnode table.
 */
D 4
struct vnode *vfreeh, **vfreet;
E 4
extern struct vnodeops dead_vnodeops;
extern struct vnodeops spec_vnodeops;
D 9
extern void vclean();
E 9
struct vattr va_null;

/*
 * Initialize the vnode structures and initialize each file system type.
 */
vfsinit()
{
D 8
	struct vfsops **vfsp;
E 8
I 8
	struct vfsconf *vfsp;
	int i, maxtypenum;
E 8

	/*
I 6
	 * Initialize the vnode table
	 */
	vntblinit();
	/*
E 6
	 * Initialize the vnode name cache
	 */
	nchinit();
	/*
	 * Build vnode operation vectors.
	 */
	vfs_op_init();
	vfs_opv_init();   /* finish the job */
	/*
	 * Initialize each file system type.
	 */
	vattr_null(&va_null);
D 8
	for (vfsp = &vfssw[0]; vfsp <= &vfssw[MOUNT_MAXTYPE]; vfsp++) {
		if (*vfsp == NULL)
			continue;
		(*(*vfsp)->vfs_init)();
E 8
I 8
	maxtypenum = 0;
	for (vfsp = vfsconf, i = 1; i <= maxvfsconf; i++, vfsp++) {
		if (i < maxvfsconf)
			vfsp->vfc_next = vfsp + 1;
		if (maxtypenum <= vfsp->vfc_typenum)
			maxtypenum = vfsp->vfc_typenum + 1;
		(*vfsp->vfc_vfsops->vfs_init)(vfsp);
E 8
	}
I 8
	/* next vfc_typenum to be used */
	maxvfsconf = maxtypenum;
E 8
}
E 1
