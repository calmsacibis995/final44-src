/* $XConsortium: miLight.h,v 5.3 93/01/25 17:20:52 hersh Exp $ */

/***********************************************************
Copyright 1989, 1990, 1991 by Sun Microsystems, Inc. and the X Consortium.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its
documentation for any purpose and without fee is hereby granted,
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in
supporting documentation, and that the names of Sun Microsystems,
the X Consortium, and MIT not be used in advertising or publicity
pertaining to distribution of the software without specific, written
prior permission.

SUN MICROSYSTEMS DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVE
NT
SHALL SUN MICROSYSTEMS BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIA
L
DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROF
ITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/

#ifndef MI_LIGHT_H
#define MI_LIGHT_H

/* Macros for lighting calculations */

/****
 *
 * Name:        NEAR_ZERO
 * Synopsis:    determine if a floating point ia approximately 0.
 *
 ****/
#define		ZERO_TOLERANCE	1.0e-30
#define		NEAR_ZERO(a) 			\
	( ((a) < 0) ? ((a) > -ZERO_TOLERANCE) : ((a) < ZERO_TOLERANCE) )

/****
 *
 * Name:        DOT_PRODUCT
 * Synopsis:    Compute the Dot (or inner) product of two vectors
 *
 ****/
#define		DOT_PRODUCT(v1, v2, v1_dot_v2)	\
{						\
    ddFLOAT  *t1, *t2;				\
    t1 = (ddFLOAT *) (v1);			\
    t2 = (ddFLOAT *) (v2);			\
    (v1_dot_v2) =  (*(t1++) * *(t2++));		\
    (v1_dot_v2) += (*(t1++) * *(t2++));		\
    (v1_dot_v2) += (*(t1  ) * *(t2  ));		\
}


/****
 *
 * Name:        CROSS_PRODUCT
 * Synopsis:    Give three points p0, p1, p2, compute the cross product
 *		of the two vectors (p1p0)x(p1p2). This corresponds to 
 *		computing the geomtric normal of a facet whose coordinates
 *		are specified in counter-clockwise order.
 *
 ****/
#define		CROSS_PRODUCT(p0, p1, p2, v)				     \
{									     \
    register  ddFLOAT  *t;						     \
    t = (ddFLOAT *) (v);							     \
    *(t++) =  (((p2->y-p1->y)*(p0->z-p1->z))-((p0->y-p1->y)*(p2->z-p1->z))); \
    *(t++) = -(((p2->x-p1->x)*(p0->z-p1->z))-((p0->x-p1->x)*(p2->z-p1->z))); \
    *(t  ) =  (((p2->x-p1->x)*(p0->y-p1->y))-((p0->x-p1->x)*(p2->y-p1->y))); \
}


/****
 *
 * Name:        COPY_VECTOR
 * Synopsis:    Copy a 3-component vector.
 *
 ****/
#define		COPY_VECTOR(dest, src)	\
{					\
    register  ddFLOAT  *d, *s;		\
    d = (ddFLOAT *) (dest);		\
    s = (ddFLOAT *) (src);		\
    *(d++) = *(s++);			\
    *(d++) = *(s++);			\
    *(d  ) = *(s  );			\
}


/****
 *
 * Name:        NEGATE_VECTOR
 * Synopsis:    Reverse direction of a 3-component vector.
 *
 ****/
#define		NEGATE_VECTOR(dest, src)	\
{					\
    register  ddFLOAT  *d, *s;		\
    d = (ddFLOAT *) (dest);		\
    s = (ddFLOAT *) (src);		\
    *(d++) = -(*(s++));			\
    *(d++) = -(*(s++));			\
    *(d  ) = -(*(s  ));			\
}


/****
 *
 * Name:        NORMALIZE_VECTOR
 * Synopsis:    Normalize a 3-component vector.
 * Description:	Replace arbitrary vector with unit vector (same direction)
 *		and also return the original length.
 *
 ****/
#define		NORMALIZE_VECTOR(vector, length)	\
{							\
    double sqrt();					\
    ddFLOAT  *v;					\
    v = (ddFLOAT *) (vector);				\
    DOT_PRODUCT(v, v, (length));			\
    (length) = sqrt ((length));				\
    if (length != 0.0) {				\
      *(v++) /= (length);				\
      *(v++) /= (length);				\
      *(v  ) /= (length);				\
    }							\
}


/****
 *
 * Name:        CALCULATE_REFLECTION_VECTOR
 * Synopsis:    Calculates the reflection vector as determined by
 *		the laws of geometrical optics.
 *
 ****/
#define		CALCULATE_REFLECTION_VECTOR(refl, n_dot_l, normal, light)  \
{						\
    ddFLOAT  *r, *n, *l;			\
    ddFLOAT  temp;				\
    r = (ddFLOAT *) (refl);			\
    temp = 2.0 * (n_dot_l);			\
    n = (ddFLOAT *) (normal);			\
    l = (ddFLOAT *) (light);			\
    *(r++) = temp * (*(n++)) - *(l++);		\
    *(r++) = temp * (*(n++)) - *(l++);		\
    *(r  ) = temp * (*(n  )) - *(l  );		\
}


/****
 *
 * Name:        CALCULATE_DIRECTION_VECTOR
 * Synopsis:    Calculates the direction vector (without normalization) 
 *		from one position to another.
 *
 ****/
#define		CALCULATE_DIRECTION_VECTOR(to, from, dir)	\
{								\
    register  ddFLOAT  *d, *t, *f;				\
    d = (ddFLOAT *) (dir);					\
    t = (ddFLOAT *) (to);					\
    f = (ddFLOAT *) (from);					\
    *(d++) = *(t++) - *(f++);					\
    *(d++) = *(t++) - *(f++);					\
    *(d  ) = *(t  ) - *(f  );					\
}

/****
 *
 * Name:        APPLY_DEPTH_CUING 
 * Synopsis:    Applies depth cueing calculation to a colour
 *		value according to the suggested equations of
 *		the PHIGS spec, "Annex E - Informative"
 *
 ****/
#define	APPLY_DEPTH_CUEING(dcue_entry, pt_depth, in_color, out_color)	\
{									\
    float tmp1, tmp2;							\
									\
    if ((pt_depth) > (dcue_entry).frontPlane) {				\
      tmp1 = (1.0 - ((dcue_entry).frontScaling));			\
      (out_color)->red = 						\
	   ((dcue_entry).frontScaling * (in_color)->red) +		\
	   ((tmp1) * (dcue_entry).depthCueColour.colour.rgbFloat.red);	\
									\
      (out_color)->green = 						\
	   ((dcue_entry).frontScaling * (in_color)->green) +		\
	   ((tmp1) * (dcue_entry).depthCueColour.colour.rgbFloat.green);\
									\
      (out_color)->blue = 						\
	   ((dcue_entry).frontScaling * (in_color)->blue) +		\
	   ((tmp1) * (dcue_entry).depthCueColour.colour.rgbFloat.blue);	\
									\
    } else if  ((pt_depth) < (dcue_entry).backPlane) {			\
      tmp1 = (1.0 - ((dcue_entry).backScaling));			\
      (out_color)->red = 						\
           ((dcue_entry).backScaling * (in_color)->red) +		\
           ((tmp1) * (dcue_entry).depthCueColour.colour.rgbFloat.red);	\
 									\
      (out_color)->green = 						\
           ((dcue_entry).backScaling * (in_color)->green) +		\
           ((tmp1) * (dcue_entry).depthCueColour.colour.rgbFloat.green);\
									\
      (out_color)->blue =						\
           ((dcue_entry).backScaling * (in_color)->blue) +		\
           ((tmp1) * (dcue_entry).depthCueColour.colour.rgbFloat.blue);	\
									\
    } else {  /* between front and back planes */			\
									\
        tmp1 = ((dcue_entry).backScaling + 				\
		(((pt_depth) - (dcue_entry).backPlane) * 		\
		(((dcue_entry).frontScaling-(dcue_entry).backScaling) / \
		((dcue_entry).frontPlane-(dcue_entry).backPlane)) ) );	\
									\
	tmp2 = (1.0 - tmp1);						\
									\
        (out_color)->red = (((tmp1) * (in_color)->red) + 		\
	  (tmp2 * (dcue_entry).depthCueColour.colour.rgbFloat.red));	\
 									\
        (out_color)->green = (((tmp1) * (in_color)->green) + 		\
	  (tmp2 * (dcue_entry).depthCueColour.colour.rgbFloat.green));	\
 									\
        (out_color)->blue = (((tmp1) * (in_color)->blue) + 		\
	  (tmp2 * (dcue_entry).depthCueColour.colour.rgbFloat.blue));	\
    }									\
}

/*
 *
 * Name:       AVERAGE 
 * Synopsis:    Give three points p0, p1, p2, compute the average 
 *              position in world coordinates
 *
 ****/
#define         AVERAGE(p0, p1, p2, avg)  		\
{                                               	\
    register  ddFLOAT  *t;                      	\
    t = (ddFLOAT *) (avg);				\
    *(t++) =  ((p0->x) + (p1->x) + (p2->x)) / 3.0;	\
    *(t++) =  ((p0->y) + (p1->y) + (p2->y)) / 3.0; 	\
    *(t  ) =  ((p0->z) + (p1->z) + (p2->z)) / 3.0; 	\
}



#endif
