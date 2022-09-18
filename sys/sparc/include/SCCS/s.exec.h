h29268
s 00002/00002/00099
d D 8.1 93/06/11 15:11:51 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00099
d D 7.4 93/04/20 18:48:49 torek 4 3
c spelling
e
s 00004/00004/00097
d D 7.3 92/09/05 18:36:35 torek 3 2
c rewire N_TXTOFF and N_DATOFF expressions to avoid gcc warning and/or
c improve clarity
e
s 00005/00000/00096
d D 7.2 92/07/21 16:41:27 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00096/00000/00000
d D 7.1 92/07/13 00:43:00 torek 1 0
c date and time created 92/07/13 00:43:00 by torek
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 2
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
D 4
 *	California, Lawrence Berkeley Laboratories.
E 4
I 4
 *	California, Lawrence Berkeley Laboratory.
E 4
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 3
 * from: $Header: exec.h,v 1.7 92/07/01 23:51:32 torek Exp $
E 3
I 3
D 4
 * from: $Header: exec.h,v 1.8 92/09/06 01:35:41 torek Exp $
E 4
I 4
 * from: $Header: exec.h,v 1.9 93/04/20 11:14:45 torek Exp $
E 4
E 3
 */

/*
 * __LDPGSZ is the page size used by the linker and by exec().
 * It may be some multiple of the ``normal'' page size, so that, e.g.,
 * the same binaries can be run on hardware with different page sizes
 * that otherwise use the same instruction set.  It must be no larger
 * than CLBYTES (in param.h).
 */
#define	__LDPGSZ	8192

/* Valid magic number check. */
#define	N_BADMAG(ex) \
	((ex).a_magic != ZMAGIC && (ex).a_magic != NMAGIC && \
	    (ex).a_magic != OMAGIC)

/*
 * N_TXTADDR is the address of the first executable instruction: that is,
 * the place the pc could begin after an a.out is loaded, in order to run
 * the instructions in that a.out.  The pc will actually be set to ex.a_entry
 * but this is the first place it could possibly reference.
 *
 * On the SPARC, binaries begin at __LDPGSZ, i.e., page 1.
 */
#define N_TXTADDR(ex)	8192

/* Address of the bottom of the data segment. */
#define N_DATADDR(ex) \
D 3
	(N_TXTADDR(ex) + ((ex).a_magic == OMAGIC ? (ex).a_text \
	: __LDPGSZ + ((ex).a_text - 1 & ~(__LDPGSZ - 1))))
E 3
I 3
	(N_TXTADDR(ex) + ((ex).a_magic == OMAGIC ? (ex).a_text : \
	    (((ex).a_text + __LDPGSZ - 1) & ~(__LDPGSZ - 1))))
E 3

/*
 * N_TXTOFF is the offset within an a.out file of the first executable
 * instruction: that is, the offset in the a.out of the byte that winds
 * up at N_TXTADDR.
 *
 * On the SPARC, the a.out header is included in the executable when running
 * a ZMAGIC file (but not for OMAGIC and NMAGIC).
 */
#define	N_TXTOFF(ex)	((ex).a_magic == ZMAGIC ? 0 : sizeof(struct exec))

/* Data segment offset. */
#define	N_DATOFF(ex) \
	(N_TXTOFF(ex) + ((ex).a_magic != ZMAGIC ? (ex).a_text : \
D 3
	__LDPGSZ + ((ex).a_text - 1 & ~(__LDPGSZ - 1))))
E 3
I 3
	    (((ex).a_text + __LDPGSZ - 1) & ~(__LDPGSZ - 1))))
E 3

/* Symbol table offset. */
#define N_SYMOFF(ex) \
	(N_TXTOFF(ex) + (ex).a_text + (ex).a_data + (ex).a_trsize + \
	    (ex).a_drsize)

/* String table offset. */
#define	N_STROFF(ex) 	(N_SYMOFF(ex) + (ex).a_syms)

/* Description of the object file header (a.out format). */
struct exec {
	u_char	a_dynamic:1;	/* dynamically linked */
	u_char	a_toolversion:7;/* Sun toolset version	XXX */

#define	MID_ZERO	0	/* unknown - implementation dependent */
#define	MID_SUN010	1	/* sun 68010/68020 binary */
#define	MID_SUN020	2	/* sun 68020-only binary */
#define	MID_SUN_SPARC	3	/* sparc binary */
#define	MID_HP200	200	/* hp200 (68010) BSD binary */
#define	MID_HP300	300	/* hp300 (68020+68881) BSD binary */
#define	MID_HPUX	0x20C	/* hp200/300 HP-UX binary */
#define	MID_HPUX800     0x20B   /* hp800 HP-UX binary */
	u_char	a_mid;		/* machine ID */

#define	OMAGIC	0407		/* old impure format */
#define	NMAGIC	0410		/* read-only text */
#define	ZMAGIC	0413		/* demand load format */
	u_short	a_magic;	/* magic number */

	u_long	a_text;		/* text segment size */
	u_long	a_data;		/* initialized data size */
	u_long	a_bss;		/* uninitialized data size */
	u_long	a_syms;		/* symbol table size */
	u_long	a_entry;	/* entry point */
	u_long	a_trsize;	/* text relocation size */
	u_long	a_drsize;	/* data relocation size */
};
#define	a_machtype	a_mid	/* SUN compatibility */
E 1
