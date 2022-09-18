/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	gp1cmds.h,v $
 * Revision 2.4  89/03/09  20:56:01  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:11:16  gm0w
 * 	Added new copyright and #ifndef <filename>_H_ around whole
 * 	file as part of kernel cleanup.
 * 	[89/02/13            jjc]
 * 
 */
/*	@(#)gp1cmds.h 1.6 87/10/19 SMI	*/

/*
 * Copyright 1986, 1987 by Sun Microsystems, Inc.
 */

#ifndef	GP1CMDS_H_
#define GP1CMDS_H_

/* GP low level command set */

#define GP1_EOCL			(0 << 8)
#define GP1_USE_CONTEXT			(1 << 8)
#define GP1_PR_VEC			(2 << 8)
#define GP1_PR_ROP_NF			(3 << 8)
#define GP1_PR_ROP_FF			(4 << 8)

#define GP1_PR_PGON_SOL			(5 << 8)
#define GP1_SET_ZBUF			(6 << 8)
#define GP1_SET_HIDDEN_SURF		(7 << 8)
#define GP1_SET_MAT_NUM			(8 << 8)
#define GP1_MUL_POINT_FLT_2D		(9 << 8)

#define GP1_MUL_POINT_FLT_3D		(10 << 8)
#define GP1_XF_PGON_FLT_3D		(11 << 8)
#define GP1_XF_PGON_FLT_2D		(12 << 8)

#define GP1_SET_CLIP_LIST		(15 << 8)
#define GP1_SET_FB_NUM			(16 << 8)
#define GP1_SET_VWP_3D			(17 << 8)
#define GP1_SET_VWP_2D			(18 << 8)
#define GP1_SET_ROP			(19 << 8)

#define GP1_SET_CLIP_PLANES		(20 << 8)
#define GP1_MUL_POINT_INT_2D		(21 << 8)
#define GP1_MUL_POINT_INT_3D		(22 << 8)
#define GP1_SET_FB_PLANES		(23 << 8)
#define GP1_SET_MAT_3D			(24 << 8)

#define GP1_SET_COLOR			(28 << 8)
#define GP1_SET_MAT_2D			(29 << 8)

#define GP1_XF_PGON_INT_3D		(30 << 8)
#define GP1_MUL_MAT_2D			(32 << 8)
#define GP1_MUL_MAT_3D			(33 << 8)
#define GP1_GET_MAT_2D			(34 << 8)

#define GP1_GET_MAT_3D			(35 << 8)
#define GP1_PROC_LINE_FLT_3D		(36 << 8)
#define GP1_PROC_PGON_FLT_3D		(37 << 8)
#define GP1_PROC_PGON_FLT_2D		(38 << 8)

#define GP1_PR_LINE			(40 << 8)
#define GP1_PR_POLYLINE			(41 << 8)
#define GP1_SET_LINE_TEX		(42 << 8)
#define GP1_SET_LINE_WIDTH		(43 << 8)
#define GP1_CGI_LINE			(44 << 8)

#define GP1_XF_LINE_FLT_2D		(45 << 8)
#define GP1_XF_LINE_FLT_3D		(46 << 8)
#define GP1_XF_LINE_INT_3D		(47 << 8)
#define GP1_PR_PGON_TEX			(48 << 8)

#define GP1_PR_ROP_TEX			(50 << 8)
#define GP1_SET_PGON_TEX_BLK		(51 << 8)
#define GP1_SET_PGON_TEX		(52 << 8)
#define GP1_SET_PGON_TEX_ORG_SCR	(53 << 8)
#define GP1_SET_PGON_TEX_ORG_XF_2D	(54 << 8)

#define GP1_SET_PGON_TEX_ORG_XF_3D	(55 << 8)
#define GP1_XF_LINE_INT_2D		(57 << 8)
#define GP1_XF_PGON_INT_2D		(58 << 8)
#define GP1_PROC_PGON_INT_2D		(59 << 8)

#define GP1_PROC_LINE_FLT_2D		(60 << 8)
#define GP1_PROC_LINE_INT_2D		(61 << 8)
#define GP1_PROC_LINE_INT_3D		(62 << 8)
#define GP1_PROC_PGON_INT_3D		(63 << 8)

/* number of commands defined so far */
#define GP1_NCMDS			64


/* Constants for option field of commands */
#define GP1_FREEBLKS		0x80	/* for EOCL */

#define GP1_NOHIDDENSURF	0	/* for SET_HIDDENSURF */
#define GP1_ZBHIDDENSURF	1

#define GP1_SHADE_CONSTANT	0	/* for XF_POLYGON */
#define GP1_SHADE_GOURAUD	1
#define GP1_SHADE_TEX		2

#define GP1_CLIP_PLANE_LEFT	0x20	/* for SET_CLIP_PLANES */
#define GP1_CLIP_PLANE_RIGHT	0x10
#define GP1_CLIP_PLANE_BOTTOM	0x8
#define GP1_CLIP_PLANE_TOP	0x4
#define GP1_CLIP_PLANE_HITHER	0x2
#define GP1_CLIP_PLANE_YON	0x1


/* Constants for size limits on commands */

/* maximum # of 16 bit texture words for PR_PGON_TEX, PR_ROP_TEX* */
#define GP1_MAXPRTEXSHORTS	2048

/* limits for PR_LINE, PR_POLYLINE */
#define GP1_MAX_BRUSH_WIDTH	181
#define GP1_MAX_PAT_SEGS	16


/* Constant to indicate version information is available
   in 3.2FCS and later releases of the pixrect library */
#define GP1_VERSION_QUERY 1


/* Old command names still available for compatibility */

#define GP1_USEFRAME (1 << 8)
#define GP1_PRVEC (2 << 8)
#define GP1_PRROPNF (3 << 8)
#define GP1_PRROPFF (4 << 8)
#define GP1_PRPOLYSOL (5 << 8)
#define GP1_SETZBUF (6 << 8)
#define GP1_SETHIDDENSURF (7 << 8)
#define GP1_SELECTMATRIX (8 << 8)
#define GP1_XFORMPT_2D (9 << 8)
#define GP1_XFORMPT_3D (10 << 8)
#define GP1_XFPOLYGON_3D (11 << 8)
#define GP1_XFPOLYGON_2D (12 << 8)
#define GP1_CORENDCVEC_3D (13 << 8)
#define GP1_CGIVEC (14 << 8)
#define GP1_SETCLPLST (15 << 8)
#define GP1_SETFBINDX (16 << 8)
#define GP1_SETVWP_3D (17 << 8)
#define GP1_SETVWP_2D (18 << 8)
#define GP1_SETROP (19 << 8)
#define GP1_SETCLIPPLANES (20 << 8)
#define GP1_SETPIXPLANES (23 << 8)
#define GP1_SET_MATRIX_3D (24 << 8)
#define GP1_XFVEC_3D (25 << 8)
#define GP1_XFVEC_2D (27 << 8)
#define GP1_SETCOLOR (28 << 8)
#define GP1_SET_MATRIX_2D (29 << 8)
#define GP1_CORENDCPOLY_3D (30 << 8)
#define GP1_MATMUL_2D (32 << 8)
#define GP1_MATMUL_3D (33 << 8)
#define GP1_GETMATRIX_2D (34 << 8)
#define GP1_GETMATRIX_3D (35 << 8)
#define GP1_COREWLDVECNDC_3D (36 << 8)
#define GP1_COREWLDPOLYNDC_3D (37 << 8)
#define GP1_SET_EF_TEX (39 << 8)

/*
 * Macros for 32 bit accesses to GP shared memory.
 *
 * "p" is a pointer and "a" is a float or int argument.
 */

#ifdef	mc68000

#define GP1_PUT_F(p, a)	(* (float *) (p) = (a), \
				(p) += sizeof (float) / sizeof *(p))
#define GP1_PUT_I(p, a)	(* (int *) (p) = (a), \
				(p) += sizeof (int) / sizeof *(p))
#define GP1_GET_F(p, a)	((a) = * (float *) (p), \
				(p) += sizeof (float) / sizeof *(p))
#define GP1_GET_I(p, a)	((a) = * (int *) (p), \
				(p) += sizeof (int) / sizeof *(p))

#else	mc68000

#define GP1_PUT_F(p, a)	(((short *) (p))[0] = ((short *)&(a))[0], \
				((short *) (p))[1] = ((short *) &(a))[1] , \
				(p) += sizeof (float) / sizeof *(p))

#define GP1_PUT_I(p, a)	(((short *) (p))[0] = ((short *)&(a))[0], \
				((short *) (p))[1] = ((short *) &(a))[1], \
				(p) += sizeof (int) / sizeof *(p))

#define GP1_GET_F(p, a)	(((short *) &(a))[0] = ((short *)(p))[0], \
				((short *) &(a))[1] = ((short *) (p))[1], \
				(p) += sizeof (float) / sizeof *(p))

#define GP1_GET_I(p, a)	(((short *) &(a))[0] = ((short *)(p))[0], \
				((short *) &(a))[1] = ((short *) (p))[1], \
				(p) += sizeof (int) / sizeof *(p))

#endif	mc68000

#endif	GP1CMDS_H_
