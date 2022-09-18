
/* $XConsortium: xfutils.c,v 5.2 91/07/24 18:42:02 hersh Exp $ */

/*****************************************************************
Copyright (c) 1989,1990, 1991 by Sun Microsystems, Inc. and the X Consortium.

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



/* 
 * This file contains transformation utilties 
 */

#include "phigs/phigs.h"
#include "math.h"
#include "imath.h"
#include "logmsg.h"
#include "xfutils.h"

/*
 * global variables
 */

/*
 * forward declaration
 */
/*
 * export routines 
 */
void i_translate();
void i_translate3();
void i_scale3();
void i_scale();
void i_rotate();
void i_rotatex();
void i_rotatey();
void i_rotatez();
void i_buildtran3();
void i_buildtran();
void i_composetran3();
void i_composetran();
void i_composematrix();
void i_composematrix3();
void i_evalvieworientationmtx3();
void i_evalvieworientationmtx();
void i_evalviewmappingmtx3();
void i_evalviewmappingmtx();
void i_tranpt();
void i_tranpt3();
void i_identity();
void i_identity3();
/*
 * local routines 
 */
static void i_vectprod();
static void i_vectnorm();
static void i_vectnorm3();
static Pfloat i_vectlen();
static Pfloat i_vectlen3();
static void i_multmat();
static void i_multmat3();


/*
 * i_translate(vec,mtx)
 */
void
i_translate(vec,mtx)
	Pvec vec;		/* vector */
	Pmatrix mtx;		/* OUT matrix */
{
	i_identity(mtx);
	mtx[0][2] = vec.delta_x;
	mtx[1][2] = vec.delta_y;
}

/*
 * i_translate3(vec,mtx)
 */
void 
i_translate3(vec,mtx) 
        Pvec3 vec;            /* vector */ 
        Pmatrix3 mtx;           /* OUT matrix */
{ 
	i_identity3(mtx);
	mtx[0][3] = vec.delta_x;
	mtx[1][3] = vec.delta_y;
	mtx[2][3] = vec.delta_z;
} 

/*
 * i_scale(vec,mtx)
 */
void
i_scale(vec,mtx)
	Pvec vec;		/* vector */
	Pmatrix mtx;		/* OUT matrix */
{
	i_identity(mtx);
	mtx[0][0] = vec.delta_x;
	mtx[1][1] = vec.delta_y;
}

/*
 * i_scale3(vec,mtx)
 */
void 
i_scale3(vec,mtx) 
        Pvec3 vec;            /* vector */ 
        Pmatrix3 mtx;           /* OUT matrix */
{ 
	i_identity3(mtx);
        mtx[0][0] = vec.delta_x;
        mtx[1][1] = vec.delta_y;
        mtx[2][2] = vec.delta_z;
} 

/*
 * i_rotate(angle,mtx)
 */
void
i_rotate(angle,mtx)
	Pfloat angle;		/* angle */
	Pmatrix mtx;		/* OUT matrix */
{
	i_identity(mtx);
	mtx[0][0] = mtx[1][1] = cos(angle);
	mtx[0][1] = - (mtx[1][0] = sin(angle));
}

/*
 * i_rotatex(angle,mtx)
 */
void
i_rotatex(angle,mtx)
	Pfloat angle;		/* angle */
	Pmatrix3 mtx;		/* OUT matrix */
{
	i_identity3(mtx);
	mtx[1][1] = mtx[2][2] = cos(angle);
	mtx[1][2] = - (mtx[2][1] = sin(angle));
}

/*
 * i_rotatey(angle,mtx)
 */
void
i_rotatey(angle,mtx)
	Pfloat angle;		/* angle */
	Pmatrix3 mtx;		/* OUT matrix */
{
	i_identity3(mtx);
	mtx[0][0] = mtx[2][2] = cos(angle);
	mtx[2][0] = - (mtx[0][2] = sin(angle));
}

/*
 * i_rotatez(angle,mtx)
 */
void
i_rotatez(angle,mtx)
	Pfloat angle;		/* angle */
	Pmatrix3 mtx;		/* OUT matrix */
{
	i_identity3(mtx);
	mtx[0][0] = mtx[1][1] = cos(angle);
	mtx[0][1] = - (mtx[1][0] = sin(angle));
}


/*
 * i_buildtran3(ref,xlate,xrot,yrot,zrot,scale,mtx) build a 3d matrix
 */
void
i_buildtran3(ref,xlate,xrot,yrot,zrot,scale,mtx)
	Ppoint3 ref;		/* reference pt */
	Pvec3 xlate;		/* xlate factor */
	Pfloat xrot;		/* x-axis rotation */
	Pfloat yrot;		/* y-axis rotation */
	Pfloat zrot;		/* z-axis rotation */
	Pvec3 scale;		/* scaling factor */
	Pmatrix3 mtx;		/* OUT matrix */
{
        Pmatrix3 tempmat1, tempmat2, tempmat3;

        i_identity3(tempmat1);
        tempmat1[0][3] = ref.x + xlate.delta_x;
        tempmat1[1][3] = ref.y + xlate.delta_y;
        tempmat1[2][3] = ref.z + xlate.delta_z;

        i_identity3(tempmat2);
        tempmat2[0][0] = tempmat2[1][1] = cos(zrot);
        tempmat2[0][1] = -sin(zrot);
        tempmat2[1][0] = sin(zrot);

        i_multmat3(tempmat1,tempmat2,tempmat3);

        i_identity3(tempmat2);
        tempmat2[0][0] = tempmat2[2][2] = cos(yrot);
        tempmat2[0][2] = sin(yrot);
        tempmat2[2][0] = -sin(yrot);

        i_multmat3(tempmat3,tempmat2,tempmat1);

        i_identity3(tempmat2);
        tempmat2[1][1] = tempmat2[2][2] = cos(xrot);
        tempmat2[1][2] = -sin(xrot);
        tempmat2[2][1] = sin(xrot);
 
        i_multmat3(tempmat1,tempmat2,tempmat3);
 
        i_identity3(tempmat2);
        tempmat2[0][0] = scale.delta_x;
        tempmat2[1][1] = scale.delta_y;
        tempmat2[2][2] = scale.delta_z;

        i_multmat3(tempmat3,tempmat2,tempmat1);

        i_identity3(tempmat2);
        tempmat2[0][3] = -ref.x;
        tempmat2[1][3] = -ref.y;
        tempmat2[2][3] = -ref.z;

        i_multmat3(tempmat1,tempmat2,mtx);


}

/*
 * i_buildtran(ref,xlate,rot,scale,mtx) build a 2d matrix
 */
void
i_buildtran(ref,xlate,rot,scale,mtx)
        Ppoint ref;		/* reference pt */ 
        Pvec xlate;		/* xlate factor */
        Pfloat rot;		/* rotation */
        Pvec scale;		/* scaling factor */ 
        Pmatrix mtx;		/* OUT matrix */
{
        Pmatrix tempmat1, tempmat2, tempmat3;

        i_identity(tempmat1);
        tempmat1[0][2] = ref.x + xlate.delta_x;
        tempmat1[1][2] = ref.y + xlate.delta_y;

        i_identity(tempmat2);
        tempmat2[0][0] = tempmat2[1][1] = cos(rot);
        tempmat2[0][1] = -sin(rot);
        tempmat2[1][0] = sin(rot);

        i_multmat(tempmat1,tempmat2,tempmat3);

        i_identity(tempmat2);
        tempmat2[0][0] = scale.delta_x;
        tempmat2[1][1] = scale.delta_y;

        i_multmat(tempmat3,tempmat2,tempmat1);

        i_identity(tempmat2);
        tempmat2[0][2] = -ref.x;
        tempmat2[1][2] = -ref.y;

        i_multmat(tempmat1,tempmat2,mtx);

} 
 
/*
 * i_composetran(mtx1,ref,xlate,angle,scale,mtx2)
 */
void
i_composetran(mtx1,ref,xlate,angle,scale,mtx2) 
	Pmatrix mtx1;		/* matrix */
        Ppoint ref;		/* reference pt */ 
        Pvec xlate;		/* xlate factor */
        Pfloat angle;		/* rotation */
        Pvec scale;		/* scaling factor */ 
	Pmatrix mtx2;		/* OUT matrix */
{
	Pmatrix mtx3;

	i_buildtran(ref,xlate,angle,scale,mtx3);
	i_multmat(mtx3,mtx1,mtx2);
}

/*
 * i_composetran3(mtx1,ref,xlate,xangle,yangle,zangle,scale,mtx2) 
 */
void
i_composetran3(mtx1,ref,xlate,xangle,yangle,zangle,scale,mtx2) 
	Pmatrix3 mtx1;		/* matrix */
        Ppoint3 ref;		/* reference pt */ 
        Pvec3 xlate;		/* xlate factor */
        Pfloat xangle;		/* x rotation */
        Pfloat yangle;		/* y rotation */
        Pfloat zangle;		/* z rotation */
        Pvec3 scale;		/* scaling factor */ 
	Pmatrix3 mtx2;		/* OUT matrix */
{
	Pmatrix3 mtx3;

	i_buildtran3(ref,xlate,xangle,yangle,zangle,scale,mtx3);
	i_multmat3(mtx3,mtx1,mtx2);
}

/*
 * i_composematrix(mtx1,mtx2,mtx3) compose two 2D matrix
 */
void
i_composematrix(mtx1,mtx2,mtx3)
	Pmatrix mtx1;		/* matrix */
	Pmatrix mtx2;		/* matrix */
	Pmatrix mtx3;		/* OUT matrix */
{
	i_multmat(mtx1,mtx2,mtx3);
}

/*
 * i_composematrix3(mtx1,mtx2,mtx3) compose two 3D matrix
 */
void
i_composematrix3(mtx1,mtx2,mtx3)
	Pmatrix3 mtx1;		/* matrix */
	Pmatrix3 mtx2;		/* matrix */
	Pmatrix3 mtx3;		/* OUT matrix */
{
	i_multmat3(mtx1,mtx2,mtx3);
}

/*
 * i_evalvieworientationmtx3(mapping,mtx) evaluate the 3D view mapping matrix
 */
void
i_evalvieworientationmtx3(vrp,vpn,vup,mtx)
	Ppoint3 vrp;		/* view reference point */
	Pvec3 vpn;		/* view plane normal */
	Pvec3 vup;		/* view up vector */
	Pmatrix3 mtx;		/* OUT matrix */
{
        Pvec3 v1, v2, v3;
        Pmatrix3 tempmat1, tempmat2;

        i_vectprod(&vup,&vpn,&v1);

        i_identity3(tempmat1);
        i_vectnorm3(&v1);
        tempmat1[0][0] = v1.delta_x;
        tempmat1[0][1] = v1.delta_y;
        tempmat1[0][2] = v1.delta_z;

        v3 = vpn;
        i_vectnorm3(&v3);
        tempmat1[2][0] = v3.delta_x;
        tempmat1[2][1] = v3.delta_y;
        tempmat1[2][2] = v3.delta_z;
 
        i_vectprod(&v3,&v1,&v2);
        tempmat1[1][0] = v2.delta_x;
        tempmat1[1][1] = v2.delta_y;
        tempmat1[1][2] = v2.delta_z;
 
        i_identity3(tempmat2);
        tempmat2[0][3] = -vrp.x;
        tempmat2[1][3] = -vrp.y;
        tempmat2[2][3] = -vrp.z;
 
        i_multmat3(tempmat1,tempmat2,mtx);
}

/*
 * i_evalvieworientationmtx(mapping,mtx) evaluate the 2D view mapping matrix
 */
void
i_evalvieworientationmtx(vrp,vup,mtx)
	Ppoint vrp;		/* view reference point */
	Pvec vup;		/* view up vector */
	Pmatrix mtx;		/* OUT matrix */
{
        Pvec v;
        Pmatrix tempmat1, tempmat2;
 
        v = vup;
        i_identity(tempmat1);
        i_vectnorm(&v);
 
        tempmat1[0][0] = v.delta_y;
        tempmat1[0][1] = -v.delta_x;
 
        tempmat1[1][0] = v.delta_x;
        tempmat1[1][1] = v.delta_y;
 
        i_identity(tempmat2);
        tempmat2[0][2] = -vrp.x;
        tempmat2[1][2] = -vrp.y;

        i_multmat(tempmat1,tempmat2,mtx);

}

/*
 * i_evalviewmappingmtx3(viewmap,mtx) evaluate the 3D view mapping matrix
 */
void
i_evalviewmappingmtx3(viewmap,mtx)
	Pview_map3 viewmap;	/* view mapping */
	Pmatrix3 mtx;		/* OUT matrix */
{
        Pmatrix3 tempmat1, tempmat2, tempmat3;
        Pfloat perp, perp1, scalex, scaley, shearx, sheary;

        if (viewmap.proj_type == PTYPE_PARAL) {
            i_identity3(tempmat1);
            tempmat1[0][3] = viewmap.proj_vp.x_min;
            tempmat1[1][3] = viewmap.proj_vp.y_min;
            tempmat1[2][3] = viewmap.proj_vp.z_max;

            i_identity3(tempmat2);
            tempmat2[0][0] = (viewmap.proj_vp.x_max - viewmap.proj_vp.x_min) / 
		(viewmap.win.x_max - viewmap.win.x_min);
            tempmat2[1][1] = (viewmap.proj_vp.y_max - viewmap.proj_vp.y_min) / 
		(viewmap.win.y_max - viewmap.win.y_min);
            if (feq(viewmap.front_plane,viewmap.back_plane))
                tempmat2[2][2] = 0.0;
            else
                tempmat2[2][2] = (viewmap.proj_vp.z_max-viewmap.proj_vp.z_min)/
		 (viewmap.front_plane - viewmap.back_plane);

            i_multmat3(tempmat1,tempmat2,tempmat3);

            i_identity3(tempmat1);
            tempmat1[0][3] = -viewmap.win.x_min;
            tempmat1[1][3] = -viewmap.win.y_min;
            tempmat1[2][3] = -viewmap.front_plane;
            i_multmat3(tempmat3,tempmat1,tempmat2);

            i_identity3(tempmat1);
            tempmat1[0][2] = (0.5 * (viewmap.win.x_min + viewmap.win.x_max)
		- viewmap.proj_ref_point.x) / (viewmap.proj_ref_point.z - viewmap.view_plane);
            tempmat1[1][2] = (0.5 * (viewmap.win.y_min + viewmap.win.y_max)
		- viewmap.proj_ref_point.y) / (viewmap.proj_ref_point.z - viewmap.view_plane);
	    tempmat1[0][3] = tempmat1[0][2] * -viewmap.view_plane;
            tempmat1[1][3] = tempmat1[1][2] * -viewmap.view_plane;
            i_multmat3(tempmat2,tempmat1,mtx);
        }
        else {
            /* Perspective projection */
            perp = -1.0 / (viewmap.back_plane - viewmap.proj_ref_point.z);
            shearx = (0.5 * (viewmap.win.x_max + viewmap.win.x_min) - 
		viewmap.proj_ref_point.x) / (viewmap.proj_ref_point.z - viewmap.view_plane);
            sheary = (0.5 * (viewmap.win.y_max + viewmap.win.y_min) - 
		viewmap.proj_ref_point.y) / (viewmap.proj_ref_point.z - viewmap.view_plane);
            scalex = 2.0 * perp * (viewmap.proj_ref_point.z - viewmap.view_plane) /
                     (viewmap.win.x_max - viewmap.win.x_min);
            scaley = 2.0 * perp * (viewmap.proj_ref_point.z - viewmap.view_plane) /
                     (viewmap.win.y_max - viewmap.win.y_min);

            i_identity3(mtx);
            mtx[0][0] = 0.5 * scalex * (viewmap.proj_vp.x_max - 
		viewmap.proj_vp.x_min);
            mtx[0][2] = 0.5 * (viewmap.proj_vp.x_max-viewmap.proj_vp.x_min) 
		* (scalex * shearx - perp) - perp * viewmap.proj_vp.x_min;
            mtx[0][3] = 0.5 * (viewmap.proj_vp.x_max - viewmap.proj_vp.x_min)
		* (perp * viewmap.proj_ref_point.z - scalex *
                (viewmap.proj_ref_point.x + shearx * viewmap.proj_ref_point.z)) +
                perp * viewmap.proj_ref_point.z * viewmap.proj_vp.x_min;
            mtx[1][1] = 0.5 * scaley * (viewmap.proj_vp.y_max - 
		viewmap.proj_vp.y_min);
            mtx[1][2] = 0.5 * (viewmap.proj_vp.y_max - viewmap.proj_vp.y_min)
		 * (scaley * sheary - perp) - perp * viewmap.proj_vp.y_min;
            mtx[1][3] = 0.5 * (viewmap.proj_vp.y_max - viewmap.proj_vp.y_min)		 * (perp * viewmap.proj_ref_point.z - scaley *
                 (viewmap.proj_ref_point.y + sheary * viewmap.proj_ref_point.z)) +
                 perp * viewmap.proj_ref_point.z * viewmap.proj_vp.y_min;
 
            perp1 = (viewmap.front_plane - viewmap.proj_ref_point.z) /
                    (viewmap.back_plane - viewmap.proj_ref_point.z);
            if (feq(perp1,1.0)) {
                mtx[2][2] = 0.0;
                mtx[2][3] = perp * viewmap.proj_ref_point.z * viewmap.proj_vp.z_max;
            }
            else {
                mtx[2][2]=perp*((viewmap.proj_vp.z_max-viewmap.proj_vp.z_min) /
			 (1.0 - perp1) - viewmap.proj_vp.z_max);
                mtx[2][3] = (-(viewmap.proj_vp.z_max - viewmap.proj_vp.z_min) /
                               (1.0 - perp1)) * (perp * viewmap.proj_ref_point.z - perp1)+
                               perp * viewmap.proj_ref_point.z * viewmap.proj_vp.z_max;
            }

            mtx[3][2] = -perp;
            mtx[3][3] = perp * viewmap.proj_ref_point.z;
        }
}

/*
 * i_evalviewmappingmtx(mapping,mtx) evaluate the 2D view mapping matrix
 */
void
i_evalviewmappingmtx(viewmap,mtx)
	Pview_map viewmap;	/* view mapping */
	Pmatrix mtx;		/* OUT matrix */
{
        Pmatrix tempmat1, tempmat2, tempmat3;

        i_identity(tempmat1);
        tempmat1[0][2] = viewmap.proj_vp.x_min;
        tempmat1[1][2] = viewmap.proj_vp.y_min;

        i_identity(tempmat2);
        tempmat2[0][0] = (viewmap.proj_vp.x_max - viewmap.proj_vp.x_min) /
                       (viewmap.win.x_max - viewmap.win.x_min);
        tempmat2[1][1] = (viewmap.proj_vp.y_max - viewmap.proj_vp.y_min) /
                       (viewmap.win.y_max - viewmap.win.y_min);
        i_multmat(tempmat1,tempmat2,tempmat3);
 
        i_identity(tempmat1);
        tempmat1[0][2] = -viewmap.win.x_min;
        tempmat1[1][2] = -viewmap.win.y_min;
        i_multmat(tempmat3,tempmat1,mtx);

}

/*
 * i_tranpt(point,matrix,oupt)
 */
void
i_tranpt(point,matrix,outpt)
	Ppoint point,*outpt;
	Pmatrix matrix;
{
        int i;
        float sum, mult;

        for (i = 0; i < 3; i++) {
                sum = 0.0;
                sum += matrix[i][0] * point.x;
                sum += matrix[i][1] * point.y;
                sum += matrix[i][2];
                switch (i) {
                        case 0:
                                outpt->x = sum;
                                break;
                        case 1:
                                outpt->y = sum;
                                break;
                        case 2:
                                mult = sum;
                                break;
                }
        }
        outpt->x = outpt->x / mult;
        outpt->y = outpt->y / mult;
}

/*
 * i_tranpt3(point,matrix,oupt)
 */
void
i_tranpt3(point,matrix,outpt)
	Ppoint3 point,*outpt;
	Pmatrix3 matrix;
{
        int i;
        float sum, mult;

        for (i = 0; i < 4; i++) {
                sum = 0.0;
                sum += matrix[i][0] * point.x;
                sum += matrix[i][1] * point.y;
                sum += matrix[i][2] * point.z;
                sum += matrix[i][3];
                switch (i) {
                        case 0:
                                outpt->x = sum;
                                break;
                        case 1:
                                outpt->y = sum;
                                break;
                        case 2:
                                outpt->z = sum;
                                break;
                        case 3:
                                mult = sum;
                                break;
                }
        }
        outpt->x = outpt->x / mult;
        outpt->y = outpt->y / mult;
        outpt->z = outpt->z / mult;
}


void
i_identity3(mat)
Pmatrix3 mat;
{
	int i,j;

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			mat[i][j] = 0.0;
	for (i = 0; i < 4; i++)
		mat[i][i] = 1.0;
}

void
i_identity(mat)
Pmatrix mat;
{
	int i,j;

	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			mat[i][j] = 0.0;
	for (i = 0; i < 3; i++)
		mat[i][i] = 1.0;
}

static void
i_multmat3(mat1,mat2,mat3)
Pmatrix3 mat1, mat2, mat3;
{
	int i,j,k;
	Pfloat sum;

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++) {
			sum = 0.0;
			for (k = 0; k < 4; k++) {
				sum += mat1[i][k] * mat2[k][j];
			}
			mat3[i][j] = sum;
		}
}

static void
i_multmat(mat1,mat2,mat3)
Pmatrix mat1, mat2, mat3;
{
	int i,j,k;
	Pfloat sum;

	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++) {
			sum = 0.0;
			for (k = 0; k < 3; k++) {
				sum += mat1[i][k] * mat2[k][j];
			}
			mat3[i][j] = sum;
		}
}


static Pfloat
i_vectlen3(v)
Pvec3 v;
{
	return((Pfloat) sqrt(v.delta_x * v.delta_x + v.delta_y * 
		v.delta_y + v.delta_z * v.delta_z));
}

static Pfloat
i_vectlen(v)
Pvec v;
{
	return((Pfloat) sqrt(v.delta_x * v.delta_x + v.delta_y * v.delta_y));
}

static void
i_vectprod(v1,v2,v3)
Pvec3 *v1,*v2,*v3;
{
	v3->delta_x = v1->delta_y * v2->delta_z - v1->delta_z * v2->delta_y;
	v3->delta_y = v1->delta_z * v2->delta_x - v1->delta_x * v2->delta_z;
	v3->delta_z = v1->delta_x * v2->delta_y - v1->delta_y * v2->delta_x;
}

static void
i_vectnorm3(v)
Pvec3 *v;
{
	Pfloat len;

	len = i_vectlen3(*v);
	v->delta_x = v->delta_x / len;
	v->delta_y = v->delta_y / len;
	v->delta_z = v->delta_z / len;
}

static void
i_vectnorm(v)
Pvec *v;
{
	Pfloat len;

	len = i_vectlen(*v);
	v->delta_x = v->delta_x / len;
	v->delta_y = v->delta_y / len;
}


