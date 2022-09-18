/* $XConsortium: mat_utils.h,v 5.1 91/02/16 09:49:05 rws Exp $ */

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
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT 
SHALL SUN MICROSYSTEMS BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL 
DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.
******************************************************************/

extern	void	phg_mat_scale();		/* matrix	m;
					   float	x, y, z; */

extern	void	phg_mat_trans();		/* matrix	m;
					   float	x, y, z; */

extern	void	phg_mat_shear_z();		/* matrix	m;
					   float	a, b; */

extern	void	phg_mat_rot_x();		/* matrix	m;
					   float	theta; */
					   
extern	void	phg_mat_rot_y();		/* matrix	m;
					   float	theta; */

extern	void	phg_mat_rot_z();		/* matrix	m;
					   float	theta; */

extern	void	phg_mat_mul_pt();		/* point3d	new_pt;
					   point3d	pt;
					   matrix	mat; */

extern	void	phg_mat_copy();	/* matrix	to, from;  */


extern	void	phg_mat_mul();		/* matrix	result;
					   matrix	mat1;
					   matrix	mat2; */

extern	void	phg_mat_identity ();	/* matrix	mat;  */

extern	float	phg_vector_dot_prod();	/* point3d	a;
					   point3d	b; */
					   
extern	void	phg_vector_cross_prod();	/* point3d	result;
					   point3d	a;
					   point3d	b; */
					   
extern	float	phg_vector_length();	/* point3d	a; */

extern	void	phg_vector_normalize();	/* point3d	a; */

extern	void	phg_mat_print();		/* matrix 	m  */
extern	void	phg_vector_print();		/* point3d	p  */



