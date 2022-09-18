h22578
s 00001/00002/00064
d D 8.4 94/08/20 16:02:58 mckusick 7 6
c update to use LIST macros for hash table
e
s 00000/00001/00066
d D 8.3 94/01/21 19:55:28 bostic 6 5
c copyright typo
e
s 00007/00005/00060
d D 8.2 94/01/05 01:02:22 pendry 5 4
c handle wide uid/gid.  lint, KNF
e
s 00002/00002/00063
d D 8.1 93/06/10 23:47:24 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00001/00065
d D 7.1 92/07/12 15:21:15 mckusick 3 2
c move to rev 7
e
s 00006/00031/00060
d D 1.2 92/07/11 15:28:21 heideman 2 1
c Porting from null layer
e
s 00091/00000/00000
d D 1.1 92/07/11 09:21:14 heideman 1 0
c date and time created 92/07/11 09:21:14 by heideman
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1992 The Regents of the University of California
 * Copyright (c) 1990, 1992 Jan-Simon Pendry
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
D 6
 * All rights reserved.
E 6
 *
 * This code is derived from software donated to Berkeley by
D 2
 * Jan-Simon Pendry.
E 2
I 2
 * the UCLA Ficus project.
E 2
 *
D 2
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
E 2
I 2
 * %sccs.include.redist.c%
E 2
 *
D 2
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
E 2
I 2
 *	%W% (Berkeley) %G%
E 2
 *
D 2
 *	@(#)lofs.h	1.1 (Berkeley) 6/3/92
 *
 * $Id: lofs.h,v 1.8 1992/05/30 10:05:43 jsp Exp jsp $
E 2
I 2
 * @(#)null_vnops.c       1.5 (Berkeley) 7/10/92
E 2
 */

#define MAPFILEENTRIES 64
#define GMAPFILEENTRIES 16
#define NOBODY 32767
D 2
#define UMAPGROUP 65534
E 2
I 2
#define NULLGROUP 65534
E 2

struct umap_args {
	char		*target;	/* Target of loopback  */
	int 		nentries;       /* # of entries in user map array */
	int 		gnentries;	/* # of entries in group map array */
D 5
	int 		*mapdata;       /* pointer to array of user mappings */
	int 		*gmapdata;	/* pointer to array of group mappings */
E 5
I 5
	u_long 		(*mapdata)[2];	/* pointer to array of user mappings */
	u_long 		(*gmapdata)[2];	/* pointer to array of group mappings */
E 5
};

struct umap_mount {
	struct mount	*umapm_vfs;
	struct vnode	*umapm_rootvp;	/* Reference to root umap_node */
	int             info_nentries;  /* number of uid mappings */
D 5
	int		info_gnentries; /* number of gid mappings */
	int             info_mapdata[MAPFILEENTRIES][2]; /* mapping data for 
E 5
I 5
	int		info_gnentries;	/* number of gid mappings */
	u_long		info_mapdata[MAPFILEENTRIES][2]; /* mapping data for 
E 5
	    user mapping in ficus */
D 5
	int		info_gmapdata[GMAPFILEENTRIES] [2]; /*mapping data for 
E 5
I 5
	u_long		info_gmapdata[GMAPFILEENTRIES][2]; /*mapping data for 
E 5
	    group mapping in ficus */
};

#ifdef KERNEL
/*
 * A cache of vnode references
 */
struct umap_node {
D 7
	struct umap_node	*umap_forw;	/* Hash chain */
	struct umap_node	*umap_back;
E 7
I 7
	LIST_ENTRY(umap_node) umap_hash;	/* Hash list */
E 7
	struct vnode	*umap_lowervp;	/* Aliased vnode - VREFed once */
	struct vnode	*umap_vnode;	/* Back pointer to vnode/umap_node */
};

extern int umap_node_create __P((struct mount *mp, struct vnode *target, struct vnode **vpp));
I 5
extern u_long umap_reverse_findid __P((u_long id, u_long map[][2], int nentries));
extern void umap_mapids __P((struct mount *v_mount, struct ucred *credp));
E 5

#define	MOUNTTOUMAPMOUNT(mp) ((struct umap_mount *)((mp)->mnt_data))
#define	VTOUMAP(vp) ((struct umap_node *)(vp)->v_data)
I 2
#define UMAPTOV(xp) ((xp)->umap_vnode)
E 2
#ifdef UMAPFS_DIAGNOSTIC
extern struct vnode *umap_checkvp __P((struct vnode *vp, char *fil, int lno));
#define	UMAPVPTOLOWERVP(vp) umap_checkvp((vp), __FILE__, __LINE__)
#else
#define	UMAPVPTOLOWERVP(vp) (VTOUMAP(vp)->umap_lowervp)
#endif

extern int (**umap_vnodeop_p)();
extern struct vfsops umap_vfsops;
#endif /* KERNEL */
D 3

E 3
E 1
