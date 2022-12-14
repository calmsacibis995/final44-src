/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	pixrect.h,v $
 * Revision 2.5  89/03/09  20:56:52  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/25  19:12:09  gm0w
 * 	Added new copyright and #ifndef <filename>_H_ around whole
 * 	file as part of kernel cleanup.
 * 	[89/02/13            jjc]
 * 
 *  4-Jan-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Add 4th field to singlecolor to force 4 byte alignment for gnu cc
 *
 */
/*	@(#)pixrect.h 1.3 86/10/08 SMI	*/

/*
 * Copyright 1986 by Sun Microsystems, Inc.
 */

#ifndef	pixrect_DEFINED
#define pixrect_DEFINED

/*
 * This file defines the programmer interface to the pixrect abstraction.
 * A pixrect is a rectangular array of pixels on which a number of
 * operations are defined.
 *
 * Each pixrect has as visible attributes its height and width in
 * pixels and the number of bits stored for each pixel.  It also supports
 * several operations.  The proper way to think of the operations is
 * that they are messages sent to the pixrect.  The operations are:
 *
 *	pr_destroy	destroy a pixrect
 *	pr_rop		raster operation from another pixrect to the
 *			destination pixrect.  the case where the source
 *			and destination overlap is properly handled.
 *	pr_stencil	raster operation from source pixrect to the
 *			dest pixrect using a stencil pixrect as a 'cookie
 *			cutter' to perform a spatial write enable.
 *	pr_batchrop	like pr_rop, but source is an array of pixrects,
 *			and an offset to be applied before each pixrect.
 *			overlapping source and destination not allowed.
 *			this is specifically designed for operations like
 *			putting up text, which consists of a number of
 *			characters from a font, each given by a pixrect.
 *	pr_get		get the value of a single pixel from a pixrect
 *	pr_put		change a single pixel value in a pixrect
 *	pr_vector	draws a vector in a pixrect
 *	pr_region	create a new pixrect which describes a rectangular
 *			sub-region of an existing pixrect
 *	pr_putcolormap	writes a portion of the colormap alias intensity
 *			transformation table.
 *	pr_getcolormap	reads a portion of the colormap
 *	pr_putattributes set the bitplanes attributes.
 *	pr_getattributes get the bitplanes attributes.
 *			
 * Abbreviations:
 *	src, s			source
 *	dst, dest, d		destination
 *	sten, st		stencil
 *	b, bp			batch or batch pointer
 *	pr			pixrect
 *	pos			position
 */

/*
 * There are a number of structures used in the arguments to pixrects:
 *
 *	struct pr_pos		a position within a pixrect is a pair of
 *				integers giving the offset from the upper
 *				left corner.  the pixels within a pixrect
 *				are numbered with (0,0) at the upper left
 *				and (width-1,height-1) at the lower right.
 *	struct pr_prpos		is a pixrect and a position within it.
 *	struct pr_size		is a pair of integers representing the
 *				size of a rectangle within a pixrect.
 *	struct pr_subregion	is a pixrect, a position and a size,
 *				specifying a rectangular sub-region.
 */

struct pr_size {
	int	x, y;
};

typedef struct pixrect {
	struct	pixrectops *pr_ops;	/* operations appropriate to this pr */
	struct	pr_size pr_size;	/* pixels per dimension */
	int	pr_depth;		/* bits per pixel */
	caddr_t	pr_data;		/* device-dependent pixel-access */
} Pixrect;
#define pr_width	pr_size.x
#define pr_height	pr_size.y

struct pr_pos {
	int	x, y;
};

struct pr_prpos {
	Pixrect *pr;
	struct	pr_pos pos;
};

struct pr_subregion {
	Pixrect *pr;
	struct	pr_pos pos;
	struct	pr_size size;
};


/* structure used to specify a single color */
struct	singlecolor {
	u_char	red, green, blue, iot;
};

#ifndef	KERNEL
/*
 * Takes device file name.  This is how first pixrect is created.
 */
extern Pixrect *pr_open();
#endif	!KERNEL

/*
 * The general pixrect operations, defined on all pixrects, are as follows.
 * They are obtained from the pr_ops attribute of the pixrect being operated
 * on.  Where two pixrects are involved the operations are obtained from
 * the destination pixrect.
 */
struct pixrectops {
	int	(*pro_rop)();		/* raster-op pixrect to pixrect */
#ifndef	KERNEL
	int	(*pro_stencil)();	/* raster-op with stencil to pixrect */
	int	(*pro_batchrop)();	/* raster-op batch to pixrect */
	int	(*pro_nop)();		/* place holder */
	int	(*pro_destroy)();	/* destroy this pixrect */
	int	(*pro_get)();		/* get value from pixrect */
	int	(*pro_put)();		/* store value in pixrect */
	int	(*pro_vector)();	/* write vector to pixrect */
	Pixrect *
		(*pro_region)();	/* make pixrect for region */
#endif	!KERNEL
	int	(*pro_putcolormap)();	/* write intensity xform table */
#ifndef	KERNEL
	int	(*pro_getcolormap)();	/* read intensity xform table */
#endif	!KERNEL
	int	(*pro_putattributes)();	/* write pr color attributes */
#ifndef	KERNEL
	int	(*pro_getattributes)();	/* read pr color attributes */
#endif	!KERNEL
};

#if	!defined(lint) || defined(KERNEL)

#define pr_rop(dpr, dx, dy, w, h, op, spr, sx, sy)		\
	(*(dpr)->pr_ops->pro_rop)(dpr, dx, dy, w, h, op, spr, sx, sy)
#define pr_putcolormap(pr, ind, cnt, red, grn, blu)		\
	(*(pr)->pr_ops->pro_putcolormap)(pr, ind, cnt, red, grn, blu)
#define pr_putattributes(pr, planes)					\
	(*(pr)->pr_ops->pro_putattributes)(pr, planes)

#ifndef	KERNEL

#define pr_stencil(dpr, dx, dy, w, h, op, stpr, stx, sty, spr, sx, sy)	\
	(*(dpr)->pr_ops->pro_stencil)(dpr,dx,dy,w,h,op,stpr,stx,sty,spr,sx,sy)
#define pr_batchrop(dpr, x, y, op, sbp, n)			\
	(*(dpr)->pr_ops->pro_batchrop)(dpr, x, y, op, sbp, n)
#define pr_destroy(pr)							\
	(*(pr)->pr_ops->pro_destroy)(pr)
#define pr_get(pr, x, y)						\
	(*(pr)->pr_ops->pro_get)(pr, x, y)
#define pr_put(pr, x, y, val)						\
	(*(pr)->pr_ops->pro_put)(pr, x, y, val)
#define pr_vector(pr, x0, y0, x1, y1, op, color)			\
	(*(pr)->pr_ops->pro_vector)(pr, x0, y0, x1, y1, op, color)
#define pr_region(pr, x, y, w, h)					\
	(*(pr)->pr_ops->pro_region)(pr, x, y, w, h)
#define pr_getcolormap(pr, ind, cnt, red, grn, blu)		\
	(*(pr)->pr_ops->pro_getcolormap)(pr, ind, cnt, red, grn, blu)
#define pr_getattributes(pr, planes)					\
	(*(pr)->pr_ops->pro_getattributes)(pr, planes)

#endif	!KERNEL

#else	!lint || KERNEL

extern pr_rop();
extern pr_stencil();
extern pr_batchrop();
extern pr_destroy();
extern pr_get();
extern pr_put();
extern pr_vector();
extern Pixrect *pr_region();
extern pr_putcolormap();
extern pr_getcolormap();
extern pr_putattributes();
extern pr_getattributes();

#endif	lint

/*
 * Several of the above operations return a common, distinguished value when
 * an error arises.  That value is defined as follows:
 */
#define PIX_ERR	-1

/*
 * Operations.  In the case of depth=1 pixrects the 'op' in 'rasterop' may be
 * any binary Boolean function, encoded as a non-negative integer < 16,
 * the op code.  The function is applied per-pixel.  
 *
 * The following permit the op to be expressed as Boolean combinations
 * of the two inputs 'source' and 'dest'.  Thus oring the source and destination
 * together is written as PIX_SRC|PIX_DST, while xoring the source with the
 * destination is PIX_SRC^PIX_DST.  Since ~op is negative, the macro PIX_NOT
 * is provided for use in place of ~.  For bit plane mask operations
 * PIX_PLN may be included in the boolean combination for depth 8 pixrects.
 */
#define PIX_SRC		(0xC << 1)
#define PIX_DST		(0xA << 1)
#define PIX_NOT(op)	((0xf<<1)&(~(op)))		/* clean ~op */
#define PIX_CLR		(PIX_SRC&PIX_NOT(PIX_SRC))	/* background */
#define PIX_SET		(PIX_SRC|PIX_NOT(PIX_SRC))	/* foreground */
#define PIX_COLOR(c)	((c)<<5)
#define PIX_OPCOLOR(op)	((op)>>5)

/*
 * Macro which tells whether a rasterop needs a SRC or DST.
 */

#define PIXOP_NEEDS_DST(op)		( (((op)>>1)^(op)) & PIX_NOT(PIX_DST))
#define PIXOP_NEEDS_SRC(op)		( (((op)>>2)^(op)) & PIX_NOT(PIX_SRC))

/*
 * The pseudo-operation PIX_DONTCLIP specifies that clipping should not
 * be performed.  PIX_CLIP is also provided, although unnecessary.
 */
#define PIX_DONTCLIP		0x1
#define PIX_CLIP		0x0

/*
 * The following structured definitions, all prefixed with prs_, correspond
 * to the unstructured definitions above prefixed with pr_.
 */

#if	!defined(lint) || defined(KERNEL)

#define prs_rop(dstreg, op, srcprpos) \
	pr_rop((dstreg).pr, (dstreg).pos.x, (dstreg).pos.y, \
		(dstreg).size.x, (dstreg).size.y, op, \
		(srcprpos).pr, (srcprpos).pos.x, (srcprpos).pos.y)
#define prs_stencil(dstreg, op, stenprpos, srcprpos) \
	pr_stencil((dstreg).pr, (dstreg).pos.x, (dstreg).pos.y, \
		(dstreg).size.x, (dstreg).size.y, op, \
		(stenprpos).pr, (stenprpos).pos.x, (stenprpos).pos.y, \
		(srcprpos).pr, (srcprpos).pos.x, (srcprpos).pos.y)
#define prs_batchrop(dstprpos, op, items, n) \
	pr_batchrop((dstprpos).pr, (dstprpos).pos.x, (dstprpos).pos.y, \
		op, items, n)
#define prs_destroy(pr)		pr_destroy(pr)
#define prs_get(srcprpos) \
	pr_get((srcprpos).pr, (srcprpos).pos.x, (srcprpos).pos.y)
#define prs_put(dstprpos, val) \
	pr_get((dstprpos).pr, (dstprpos).pos.x, (dstprpos).pos.y)
#define prs_vector(pr, pos0, pos1, op, color) \
	pr_vector(pr, (pos0).x, (pos0).y, (pos1).x, (pos1).y, op, color)
#define prs_region(dstreg) \
	pr_region((dstreg).pr, (dstreg).pos.x, (dstreg).pos.y, \
		(dstreg).size.x, (dstreg).size.y)
#define prs_putcolormap(pr, ind, cnt, red, grn, blu) \
	pr_putcolormap(pr, ind, cnt, red, grn, blu)
#define prs_getcolormap(pr, ind, cnt, red, grn, blu) \
	pr_getcolormap(pr, ind, cnt, red, grn, blu)
#define prs_putattributes(pr, planes)	pr_putattributes(pr, planes)
#define prs_getattributes(pr, planes)	pr_getattributes(pr, planes)

/* pr_replrop is not currently in the ops vector */
#define prs_replrop(dstreg, op, srcprpos) \
	pr_replrop((dstreg).pr, (dstreg).pos.x, (dstreg).pos.y, \
		(dstreg).size.x, (dstreg).size.y, op, \
		(srcprpos).pr, (srcprpos).pos.x , (srcprpos).pos.y )

/* pr_close is a synonym for pr_destroy */
#define pr_close(pr)	pr_destroy(pr)

/* textured line macro */
#define pr_line(pr, x0, y0, x1, y1, brush, tex, op) \
	pro_line(pr, x0, y0, x1, y1, brush, tex, op, 0) 

#else	!lint || KERNEL

extern prs_rop();
extern prs_stencil();
extern prs_batchrop();
extern prs_destroy();
extern prs_get();
extern prs_put();
extern prs_vector();
extern Pixrect *prs_region();
extern prs_putcolormap();
extern prs_getcolormap();
extern prs_putattributes();
extern prs_getattributes();

extern prs_replrop();
extern pr_close();
extern pr_line();

#endif	lint

#endif	pixrect_DEFINED
