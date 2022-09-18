
/* $XConsortium: datautils.c,v 5.2 91/07/24 18:41:05 hersh Exp $ */

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



#include "datautils.h"

#define eqstring(a,b)  !strcmp((a),(b))    /* compare text string */

#ifdef NEWT
#include "NewTvararg.h"
#else
#include "varargs.h"
#endif


/* BEG: initialize array of data 
   IA_...(number, list of structure members composing the specified type) */

Ppoint4 *
IA_Ppoint4(n,va_alist)
	int n;
	va_dcl
{
	Ppoint4  *p;
	int i;
	va_list ap;

	va_start(ap);
	p = (Ppoint4*) malloc(sizeof(Ppoint4) * n);
	for (i=0;i<n;++i) {
		p[i].x = va_arg(ap,double);
		p[i].y = va_arg(ap,double);
		p[i].z = va_arg(ap,double);
		p[i].w = va_arg(ap,double);
	}
	va_end(ap);
	return(p);
}

Ppoint3 *
IA_Ppoint3(n,va_alist)
	int n;
	va_dcl
{
	Ppoint3  *p;
	int i;
	va_list ap;

	va_start(ap);
	p = (Ppoint3*) malloc(sizeof(Ppoint3) * n);
	for (i=0;i<n;++i) {
		p[i].x = va_arg(ap,double);
		p[i].y = va_arg(ap,double);
		p[i].z = va_arg(ap,double);
	}
	va_end(ap);
	return(p);
}

Ppoint *
IA_Ppoint(n,va_alist)
	int n;
	va_dcl
{
	Ppoint  *p;
	int i;
	va_list ap;

	va_start(ap);
	p = (Ppoint*) malloc(sizeof(Ppoint) * n);
	for (i=0;i<n;++i) {
		p[i].x = va_arg(ap,double);
		p[i].y = va_arg(ap,double);
	}
	va_end(ap);
	return(p);
}

Pvec3 *
IA_Pvec3(n,va_alist)
        int n;
        va_dcl
{
        Pvec3  *p;
        int i;
        va_list ap;

        va_start(ap);
        p = (Pvec3*) malloc(sizeof(Pvec3) * n);
        for (i=0;i<n;++i) {
                p[i].delta_x = va_arg(ap,double);
                p[i].delta_y = va_arg(ap,double);
                p[i].delta_z = va_arg(ap,double);
        }
        va_end(ap);
        return(p);
}

Pptconorm3 * 
IA_Pptconorm3(n,va_alist) 
        int n; 
        va_dcl   
{
        Pptconorm3  *p; 
        int i; 
        va_list ap; 
  
        va_start(ap); 
        p = (Pptconorm3*) malloc(sizeof(Pptconorm3) * n); 
        for (i=0;i<n;++i) { 
                p[i].point = va_arg(ap,Ppoint3); 
                p[i].colr = va_arg(ap,Pcoval); 
                p[i].norm = va_arg(ap,Pvec3); 
        } 
        va_end(ap); 
        return(p); 
} 
Pptnorm3 *
IA_Pptnorm3(n,va_alist)
        int n;
        va_dcl  
{
        Pptnorm3  *p;
        int i;
        va_list ap;
 
        va_start(ap);
        p = (Pptnorm3*) malloc(sizeof(Pptnorm3) * n);
        for (i=0;i<n;++i) {
                p[i].point = va_arg(ap,Ppoint3);
                p[i].norm = va_arg(ap,Pvec3);
        }
        va_end(ap);
        return(p);
}
Pptco3 *
IA_Pptco3(n,va_alist)
        int n;
        va_dcl
{
        Pptco3  *p;
	int i;
        va_list ap;

        va_start(ap);
        p = (Pptco3*) malloc(sizeof(Pptco3) * n);
	for (i=0;i<n;++i) {
		p[i].point = va_arg(ap,Ppoint3);
		p[i].colr = va_arg(ap,Pcoval);
	}
	va_end(ap);
	return(p);
}

Pconorm3 *
IA_Pconorm3(n,va_alist)
        int n;
        va_dcl
{
        Pconorm3  *p;
        int i;
        va_list ap;
 
        va_start(ap);
        p = (Pconorm3*) malloc(sizeof(Pconorm3) * n);
        for (i=0;i<n;++i) {
                p[i].colr = va_arg(ap,Pcoval);
                p[i].norm = va_arg(ap,Pvec3);
        }
        va_end(ap);
        return(p);
}

/* BEG: initialize array of data 
   IA_...(number, list of the specified type) */

Pint_list *
IA_Pint_list(n,va_alist)
        int n;
        va_dcl
{
        Pint_list  *p;
        int i;
        va_list ap;

        va_start(ap);
        p = (Pint_list*) malloc(sizeof(Pint_list) * n);
        for (i=0;i<n;++i) {
                p[i] = va_arg(ap,Pint_list);
        }
        va_end(ap);
        return(p);
}       

Ptrimcurve_list *
IA_Ptrimcurve_list(n,va_alist)
        int n;
        va_dcl
{
        Ptrimcurve_list  *p;
        int i;
        va_list ap;

        va_start(ap);
        p = (Ptrimcurve_list*) malloc(sizeof(Ptrimcurve_list) * n);
        for (i=0;i<n;++i) {
                p[i] = va_arg(ap,Ptrimcurve_list);
        }
        va_end(ap);
        return(p);
}       

Ptrimcurve *
IA_Ptrimcurve(n,va_alist)
        int n;
        va_dcl
{
        Ptrimcurve  *p;
        int i;
        va_list ap;

        va_start(ap);
        p = (Ptrimcurve*) malloc(sizeof(Ptrimcurve) * n);
        for (i=0;i<n;++i) {
                p[i] = va_arg(ap,Ptrimcurve);
        }
        va_end(ap);
        return(p);
}       



Ppoint_list3 *
IA_Ppoint_list3(n,va_alist)
	int n;
	va_dcl
{
	Ppoint_list3  *p;
	int i;
	va_list ap;

	va_start(ap);
	p = (Ppoint_list3*) malloc(sizeof(Ppoint_list3) * n);
	for (i=0;i<n;++i) {
		p[i] = va_arg(ap,Ppoint_list3);
	}
	va_end(ap);
	return(p);
}

Ppoint_list *
IA_Ppoint_list(n,va_alist)
	int n;
	va_dcl
{
	Ppoint_list  *p;
	int i;
	va_list ap;

	va_start(ap);
	p = (Ppoint_list*) malloc(sizeof(Ppoint_list) * n);
	for (i=0;i<n;++i) {
		p[i] = va_arg(ap,Ppoint_list);
	}
	va_end(ap);
	return(p);
}

Pelem_type *
IA_Pelem_type(n,va_alist)
	int n;
	va_dcl
{
	Pelem_type  *p;
	int i;
	va_list ap;

	va_start(ap);
	p = (Pelem_type*) malloc(sizeof(Pelem_type) * n);
	for (i=0;i<n;++i) {
		p[i] = va_arg(ap,Pelem_type);
	}
	va_end(ap);
	return(p);
}


Pint *
IA_Pint(n,va_alist)
	int n;
	va_dcl
{
	Pint  *p;
	int i;
	va_list ap;

	va_start(ap);
	p = (Pint*) malloc(sizeof(Pint) * n);
	for (i=0;i<n;++i) {
		p[i] = va_arg(ap,Pint);
	}
	va_end(ap);
	return(p);
}

Pfloat *
IA_Pfloat(n,va_alist)
	int n;
	va_dcl
{
	Pfloat  *p;
	int i;
	va_list ap;

	va_start(ap);
	p = (Pfloat*) malloc(sizeof(Pfloat) * n);
	for (i=0;i<n;++i) {
		p[i] = va_arg(ap,double);
	}
	va_end(ap);
	return(p);
}

Pline_vdata_list3 *
IA_Pline_vdata_list3(n,va_alist)
	int n;
	va_dcl
{
	Pline_vdata_list3  *p;
	int i;
	va_list ap;

	va_start(ap);
	p = (Pline_vdata_list3*) malloc(sizeof(Pline_vdata_list3) * n);
	for (i=0;i<n;++i) {
		p[i] = va_arg(ap,Pline_vdata_list3);
	}
	va_end(ap);
	return(p);
}
Pedge_data_list*
IA_Pedge_data_list(n,va_alist)
        int n;
        va_dcl
{
        Pedge_data_list*p;
        int i;
        va_list ap;
 
        va_start(ap);
        p = (Pedge_data_list*) malloc(sizeof(Pedge_data_list) * n);
        for (i=0;i<n;++i) {
                p[i] = va_arg(ap,Pedge_data_list);
        }
        va_end(ap);
        return(p);
}
Pedge_data_list_list*
IA_Pedge_data_list_list(n,va_alist)
	int n;
	va_dcl
{
	Pedge_data_list_list  *p;
	int i;
	va_list ap;

	va_start(ap);
	p = (Pedge_data_list_list*) malloc(sizeof(Pedge_data_list_list) * n);
	for (i=0;i<n;++i) {
		p[i] = va_arg(ap,Pedge_data_list_list);
	}
	va_end(ap);
	return(p);
}

Pfacet_vdata_list3 *
IA_Pfacet_vdata_list3(n,va_alist)
	int n;
	va_dcl
{
	Pfacet_vdata_list3  *p;
	int i;
	va_list ap;

	va_start(ap);
	p = (Pfacet_vdata_list3*) malloc(sizeof(Pfacet_vdata_list3) * n);
	for (i=0;i<n;++i) {
		p[i] = va_arg(ap,Pfacet_vdata_list3);
	}
	va_end(ap);
	return(p);
}

Pint_list_list*
IA_Pint_list_list(n,va_alist)
	int n;
	va_dcl
{
	Pint_list_list  *p;
	int i;
	va_list ap;

	va_start(ap);
	p = (Pint_list_list*) malloc(sizeof(Pint_list_list) * n);
	for (i=0;i<n;++i) {
		p[i] = va_arg(ap,Pint_list_list);
	}
	va_end(ap);
	return(p);
}

Pelem_ref_list*
IA_Pelem_ref_list(n,va_alist)
	int n;
	va_dcl
{
	Pelem_ref_list  *p;
	int i;
	va_list ap;

	va_start(ap);
	p = (Pelem_ref_list*) malloc(sizeof(Pelem_ref_list) * n);
	for (i=0;i<n;++i) {
		p[i] = va_arg(ap,Pelem_ref_list);
	}
	va_end(ap);
	return(p);
}

Pelem_ref*
IA_Pelem_ref(n,va_alist)
	int n;
	va_dcl
{
	Pelem_ref *p;
	int i;
	va_list ap;

	va_start(ap);
	p = (Pelem_ref*) malloc(sizeof(Pelem_ref) * n);
	for (i=0;i<n;++i) {
		p[i] = va_arg(ap,Pelem_ref);
	}
	va_end(ap);
	return(p);
}

Pfilter*
IA_Pfilter(n,va_alist)
	int n;
	va_dcl
{
	Pfilter *p;
	int i;
	va_list ap;

	va_start(ap);
	p = (Pfilter*) malloc(sizeof(Pfilter) * n);
	for (i=0;i<n;++i) {
		p[i] = va_arg(ap,Pfilter);
	}
	va_end(ap);
	return(p);
}

Par_file*
IA_Par_file(n,va_alist)
	int n;
	va_dcl
{
	Par_file *p;
	int i;
	va_list ap;

	va_start(ap);
	p = (Par_file*) malloc(sizeof(Par_file) * n);
	for (i=0;i<n;++i) {
		p[i] = va_arg(ap,Par_file);
	}
	va_end(ap);
	return(p);
}

Ppick_path_elem*
IA_Ppick_path_elem(n,va_alist)
	int n;
	va_dcl
{
	Ppick_path_elem *p;
	int i;
	va_list ap;

	va_start(ap);
	p = (Ppick_path_elem*) malloc(sizeof(Ppick_path_elem) * n);
	for (i=0;i<n;++i) {
		p[i] = va_arg(ap,Ppick_path_elem);
	}
	va_end(ap);
	return(p);
}

Ppick_path*
IA_Ppick_path(n,va_alist)
	int n;
	va_dcl
{
	Ppick_path *p;
	int i;
	va_list ap;

	va_start(ap);
	p = (Ppick_path*) malloc(sizeof(Ppick_path) * n);
	for (i=0;i<n;++i) {
		p[i] = va_arg(ap,Ppick_path);
	}
	va_end(ap);
	return(p);
}


/* BEG: initialize array of data 
   IA_...(number, union_type,list of data whose format depends on union_type) */

Pcoval *
IA_Pcoval(n,type,va_alist)
	int n,type;
        va_dcl
{
        Pcoval  *p;
        int i;
        va_list ap;

        va_start(ap);
        p = (Pcoval*) malloc(sizeof(Pcoval) * n);
	switch(type) {
	case PMODEL_RGB:
        	for (i=0;i<n;++i) {
                	p[i].direct.rgb.red = va_arg(ap,double);
                	p[i].direct.rgb.green = va_arg(ap,double);
                	p[i].direct.rgb.blue = va_arg(ap,double);
		}
		break;
	case PINDIRECT:
        	for (i=0;i<n;++i) {
                	p[i].ind = va_arg(ap,Pint);
		}
		break;
	case PMODEL_CIELUV:
        	for (i=0;i<n;++i) {
                	p[i].direct.cieluv.cieluv_x = va_arg(ap,double);
                	p[i].direct.cieluv.cieluv_y = va_arg(ap,double);
                	p[i].direct.cieluv.cieluv_y_lum = va_arg(ap,double);
		}
	case PMODEL_HSV:
        	for (i=0;i<n;++i) {
                	p[i].direct.hsv.hue = va_arg(ap,double);
                	p[i].direct.hsv.satur = va_arg(ap,double);
                	p[i].direct.hsv.value = va_arg(ap,double);
		}
	case PMODEL_HLS:
        	for (i=0;i<n;++i) {
                	p[i].direct.hls.hue = va_arg(ap,double);
                	p[i].direct.hls.lightness = va_arg(ap,double);
                	p[i].direct.hls.satur = va_arg(ap,double);
		}
	default: 
		puts("IA_Pcoval: invalid type");
	}
        va_end(ap);
        return(p);
}

/* Pline_vdata_list3
 * I_Pline_vdata_list3_from_data(num_vertices, vdata_type, [color_type,] DATA...)
 *
 * Build a Pline_vdata_list3 from raw coordinate and color data.
 * The data for the points should follow the number of vertices, the type
 * of vertex data, and the color type of the color data.
 *
 * for vdata_type==PVERT_COORD, data should be floats for x, y, and z.
 * for vdata_type== PVERT_COORD_COLOR, the next argument should
 * be the color_type (PINDIRECT, PMODEL_RGB,...) followed by vertex data
 * for each vertex, in the form:
 *     if color_type==PINDIRECT: (float) x, y, z, (int) index
 *     if color_type==PMODEL_RGB: (float) x, y, z, red, green, blue 
 *     if color_type==PMODEL_HSV: (float) x, y, z, hue, satur, value
 *     etc...
 */
Pline_vdata_list3 
I_Pline_vdata_list3_from_data(va_alist)
	va_dcl
{
	int vdata_type;
        Pline_vdata_list3  tmp;
	Pline_vdata_arr3   arr;
	int color_type;
	int i;
	va_list ap;

	va_start(ap);
        tmp.num_vertices = va_arg(ap, int);
	vdata_type = va_arg(ap, int);
	switch(vdata_type) {
	case PVERT_COORD:
	    /* ignore color_type - no color data */
	    arr.points = (Ppoint3 *) malloc((sizeof(Ppoint3) * tmp.num_vertices));
	    for (i=0; i<tmp.num_vertices; i++) {
		arr.points[i].x = va_arg(ap, double);
		arr.points[i].y = va_arg(ap, double);
		arr.points[i].z = va_arg(ap, double);
	    }
	    break;
	case PVERT_COORD_COLOUR:
	    arr.ptcolrs = (Pptco3 *) malloc((sizeof(Pptco3) * tmp.num_vertices));
	    color_type = va_arg(ap, int);
	    switch (color_type) {
	    case PINDIRECT:
		for (i=0; i<tmp.num_vertices; i++) {
		    arr.ptcolrs[i].point.x = va_arg(ap, double);
		    arr.ptcolrs[i].point.y = va_arg(ap, double);
		    arr.ptcolrs[i].point.z = va_arg(ap, double);
		    arr.ptcolrs[i].colr.ind = va_arg(ap,Pint);
		}
		break;
	    case PMODEL_RGB:
		for (i=0; i<tmp.num_vertices; i++) {
		    arr.ptcolrs[i].point.x = va_arg(ap, double);
		    arr.ptcolrs[i].point.y = va_arg(ap, double);
		    arr.ptcolrs[i].point.z = va_arg(ap, double);
		    arr.ptcolrs[i].colr.direct.rgb.red = va_arg(ap, double);
		    arr.ptcolrs[i].colr.direct.rgb.green = va_arg(ap, double);
		    arr.ptcolrs[i].colr.direct.rgb.blue = va_arg(ap, double);
		}
		break;
	    case PMODEL_CIELUV:
		for (i=0; i<tmp.num_vertices; i++) {
		    arr.ptcolrs[i].point.x = va_arg(ap, double);
		    arr.ptcolrs[i].point.y = va_arg(ap, double);
		    arr.ptcolrs[i].point.z = va_arg(ap, double);
		    arr.ptcolrs[i].colr.direct.cieluv.cieluv_x = va_arg(ap, double);
		    arr.ptcolrs[i].colr.direct.cieluv.cieluv_y = va_arg(ap, double);
		    arr.ptcolrs[i].colr.direct.cieluv.cieluv_y_lum = va_arg(ap, double);
		}
		break;
	    case PMODEL_HSV:
		for (i=0; i<tmp.num_vertices; i++) {
		    arr.ptcolrs[i].point.x = va_arg(ap, double);
		    arr.ptcolrs[i].point.y = va_arg(ap, double);
		    arr.ptcolrs[i].point.z = va_arg(ap, double);
		    arr.ptcolrs[i].colr.direct.hsv.hue = va_arg(ap, double);
		    arr.ptcolrs[i].colr.direct.hsv.satur = va_arg(ap, double);
		    arr.ptcolrs[i].colr.direct.hsv.value = va_arg(ap, double);
		}
		break;
	    case PMODEL_HLS:
		for (i=0; i<tmp.num_vertices; i++) {
		    arr.ptcolrs[i].point.x = va_arg(ap, double);
		    arr.ptcolrs[i].point.y = va_arg(ap, double);
		    arr.ptcolrs[i].point.z = va_arg(ap, double);
		    arr.ptcolrs[i].colr.direct.hls.hue = va_arg(ap, double);
		    arr.ptcolrs[i].colr.direct.hls.lightness = va_arg(ap, double);
		    arr.ptcolrs[i].colr.direct.hls.satur = va_arg(ap, double);
		}
		break;
	    }						
	    break;
	}
        tmp.vertex_data = arr;
        return(tmp);
}


/* takes a number of points, and however many floats are
 * required to fill them, and returns a Ppoint_list with
 * the number of points and the point data.
 */
Ppoint_list
I_Ppoint_list_from_data(n,va_alist)
	int n;
	va_dcl
{
        Ppoint_list tmp;
	int i;
	va_list ap;

	va_start(ap);
	tmp.num_points = n;
	tmp.points = (Ppoint*) malloc(sizeof(Ppoint) * n);
	for (i=0;i<n;++i) {
		tmp.points[i].x = va_arg(ap, double);
		tmp.points[i].y = va_arg(ap, double);
	}
	va_end(ap);
	return(tmp);
}

/* takes a number of point3s, and however many floats are
 * required to fill them, and returns a Ppoint_list3
 * with the data.
 */
Ppoint_list3
I_Ppoint_list3_from_data(n,va_alist)
	int n;
	va_dcl
{
        Ppoint_list3 tmp;
	int i;
	va_list ap;

	va_start(ap);
	tmp.num_points = n;
	tmp.points = (Ppoint3*) malloc(sizeof(Ppoint3) * n);
	for (i=0;i<n;++i) {
		tmp.points[i].x = va_arg(ap, double);
		tmp.points[i].y = va_arg(ap, double);
		tmp.points[i].z = va_arg(ap, double);
	}
	va_end(ap);
	return(tmp);
}

/* BEG: initialize array of data 
   IA_...(... special cases) */


Ppoint *
IA_2_Ppoint(x0,y0,x1,y1)
	Pfloat x0,y0,x1,y1;
{
	Ppoint  *p;

	p = (Ppoint*) malloc(sizeof(Ppoint) * 2);
	p[0].x= x0; p[0].y= y0;
	p[1].x = x1; p[1].y = y1;
	return(p);
}

Ppoint *
IA_3_Ppoint(x0,y0,x1,y1,x2,y2)
	Pfloat x0,y0,x1,y1,x2,y2;
{
	Ppoint  *p;

	p = (Ppoint*) malloc(sizeof(Ppoint) * 3);
	p[0].x = x0; p[0].y = y0;
	p[1].x = x1; p[1].y = y1;
	p[2].x = x2; p[2].y = y2;
	return(p);
}

Ppoint *
IA_5_Ppoint(x0,y0,x1,y1,x2,y2,x3,y3,x4,y4)
	Pfloat x0,y0,x1,y1,x2,y2,x3,y3,x4,y4;
{
	Ppoint  *p;

	p = (Ppoint*) malloc(sizeof(Ppoint) * 5);
	p[0].x = x0; p[0].y = y0;
	p[1].x = x1; p[1].y = y1;
	p[2].x = x2; p[2].y = y2;
	p[3].x = x3; p[3].y = y3;
	p[4].x = x4; p[4].y = y4;
	return(p);
}

Ppoint3 *
IA_2_Ppoint3(x0,y0,z0,x1,y1,z1)
	Pfloat x0,y0,z0,x1,y1,z1;
{
	Ppoint3  *p;

	p = (Ppoint3*) malloc(sizeof(Ppoint3) * 2);
	p[0].x = x0; p[0].y = y0; p[0].z = z0;
	p[1].x = x1; p[1].y = y1; p[1].z = z1;
	return(p);
}

Ppoint3 *
IA_3_Ppoint3(x0,y0,z0,x1,y1,z1,x2,y2,z2)
	Pfloat x0,y0,z0,x1,y1,z1,x2,y2,z2;
{
	Ppoint3  *p;

	p = (Ppoint3*) malloc(sizeof(Ppoint3) * 3);
	p[0].x = x0; p[0].y = y0; p[0].z = z0;
	p[1].x = x1; p[1].y = y1; p[1].z = z1;
	p[2].x = x2; p[2].y = y2; p[2].z = z2;
	return(p);
}

Ppoint3 *
IA_5_Ppoint3(x0,y0,z0,x1,y1,z1,x2,y2,z2,x3,y3,z3,x4,y4,z4)
	Pfloat x0,y0,z0,x1,y1,z1,x2,y2,z2,x3,y3,z3,x4,y4,z4;
{
	Ppoint3  *p;

	p = (Ppoint3*) malloc(sizeof(Ppoint3) * 5);
	p[0].x = x0; p[0].y = y0; p[0].z = z0;
	p[1].x = x1; p[1].y = y1; p[1].z = z1;
	p[2].x = x2; p[2].y = y2; p[2].z = z2;
	p[3].x = x3; p[3].y = y3; p[3].z = z3;
	p[4].x = x4; p[4].y = y4; p[4].z = z4;
	return(p);
}

/* BEG: initialize simple data 
   I_...(list of structure members composing the specified type) */

Ptrimcurve
I_Ptrimcurve(visible,rationality,order,approx_type,approx_val,knots,tmin,tmax,cpts)
        Pedge_flag         visible;
        Prational           rationality;
        Pint                order;
        Pint                approx_type;
        Pfloat              approx_val;
        Pfloat_list         knots;
        Pfloat              tmin, tmax;
        Ppoint_list23       cpts;
{
        Ptrimcurve tmp;
 
        tmp.visible = visible;
        tmp.rationality = rationality;
        tmp.order = order;
	tmp.approx_type = approx_type;
	tmp.approx_val = approx_val;
        tmp.knots = knots;
        tmp.tmin = tmin;
        tmp.tmax = tmax;
        tmp.cpts = cpts;
        return(tmp);
}
 
Ptrimcurve_list
I_Ptrimcurve_list(n,curves)
        Pint n;
        Ptrimcurve *curves;
{
        Ptrimcurve_list tmp;
 
        tmp.num_curves = n;
        tmp.curves = curves;
        return(tmp);
}

Pparal
I_Pparal(p,q,r)
	Ppoint3 p,q,r;
{
	Pparal tmp;

	tmp.p = p;
	tmp.q = q;
	tmp.r = r;
	return(tmp);
}

Ppoint_list3
I_Ppoint_list3(n,points)
        Pint n;
	Ppoint3 *points;
{
	Ppoint_list3 tmp;

	tmp.num_points = n;
	tmp.points = points;
	return(tmp);
}

Ppoint_list
I_Ppoint_list(n,points)
        Pint n;
	Ppoint *points;
{
	Ppoint_list tmp;

	tmp.num_points = n;
	tmp.points = points;
	return(tmp);
}

Ppoint_list_list3
I_Ppoint_list_list3(n,points)
        Pint n;
	Ppoint_list3 *points;
{
	Ppoint_list_list3 tmp;

	tmp.num_point_lists = n;
	tmp.point_lists = points;
	return(tmp);
}

Ppoint_list_list
I_Ppoint_list_list(n,points)
        Pint n;
	Ppoint_list *points;
{
	Ppoint_list_list tmp;

	tmp.num_point_lists = n;
	tmp.point_lists = points;
	return(tmp);
}

Pelem_type_list
I_Pelem_type_list(n,selems)
        Pint n;
	Pelem_type *selems;
{
	Pelem_type_list tmp;

	tmp.num_elem_types = n;
	tmp.elem_types = selems;
	return(tmp);
}

Par_file_list
I_Par_file_list(n,ar_files)
        Pint n;
	Par_file *ar_files;
{
	Par_file_list tmp;

	tmp.num_ar_files = n;
	tmp.ar_files = ar_files;
	return(tmp);
}

Pint_list
I_Pint_list(n,ip)
        int n;
	Pint *ip;
{
        Pint_list  tmp; 

	tmp.num_ints = n;
	tmp.ints = ip;
        return(tmp);
}

Pfloat_list
I_Pfloat_list(n,fp)
        int n;
        Pfloat *fp;
{ 
        Pfloat_list  tmp; 

        tmp.num_floats = n;  
        tmp.floats = fp; 
        return(tmp);  
}  

Pdata
I_Pdata(size,data)
	Pint size;
	char *data;
{
	Pdata tmp;

	tmp.size = size;
	tmp.data = data;
	return(tmp);
}


Ppoint3
I_Ppoint3(x,y,z)
	Pfloat x,y,z;
{
	Ppoint3 tmp;

	tmp.x = x;
	tmp.y = y;
	tmp.z = z;
	return(tmp);
}


Ppoint
I_Ppoint(x,y)
	Pfloat x,y;
{
	Ppoint tmp;

	tmp.x = x;
	tmp.y = y;
	return(tmp);
}

Pvec3
I_Pvec3(x,y,z)
        Pfloat x,y,z;
{
        Pvec3 tmp;
 
        tmp.delta_x = x;
        tmp.delta_y = y;
        tmp.delta_z = z;
        return(tmp);
}

Pvec
I_Pvec(x,y)
        Pfloat x,y;
{
        Pvec tmp;
 
        tmp.delta_x = x;
        tmp.delta_y = y;
        return(tmp);
}

Pint_size
I_Pint_size(x_dim,y_dim)
        Pint x_dim,y_dim;
{
        Pint_size tmp;

        tmp.size_x = x_dim;
        tmp.size_y = y_dim;
        return(tmp);
}

Phalf_space3
I_Phalf_space3(pt,normal)
        Ppoint3 pt;
	Pvec3 normal;
{
        Phalf_space3 tmp;

        tmp.point = pt;
        tmp.norm = normal;
        return(tmp);
}


Phalf_space
I_Phalf_space(pt,normal)
        Ppoint pt;
        Pvec normal;
{
        Phalf_space tmp;
 
        tmp.point = pt;
        tmp.norm = normal;
        return(tmp);
}

Ptext_align
I_Ptext_align(hor,ver)
	Phor_text_align hor;
	Pvert_text_align ver;
{
        Ptext_align tmp;

        tmp.hor = hor;
        tmp.vert = ver;
        return(tmp);
}

Prect
I_Prect(ll,ur)
	Ppoint ll,ur;
{
        Prect  tmp;
 
	tmp.p = ll;
	tmp.q = ur;
        return(tmp); 
} 

Pint_list_list
I_Pint_list_list(number,ils)
        int number;
	Pint_list *ils;
{
        Pint_list_list  tmp;
 
        tmp.num_lists = number;
        tmp.lists = ils;
        return(tmp);
}

Plimit3
I_Plimit3(xmin,xmax,ymin,ymax,zmin,zmax)
        Pfloat xmin,xmax,ymin,ymax,zmin,zmax;
{
        Plimit3  tmp;
 
        tmp.x_min = xmin;
        tmp.x_max = xmax;
        tmp.y_min = ymin;
        tmp.y_max = ymax;
        tmp.z_min = zmin;
        tmp.z_max = zmax;
        return(tmp);
}

Plimit
I_Plimit(xmin,xmax,ymin,ymax)
	Pfloat xmin,xmax,ymin,ymax;
{
        Plimit  tmp;

        tmp.x_min = xmin;
        tmp.x_max = xmax;
        tmp.y_min = ymin;
        tmp.y_max = ymax;
        return(tmp);
} 

/*
Ppcs_limit
I_Ppcs_limit(umin,umax,vmin,vmax)
	Pfloat umin,umax,vmin,vmax;
{
        Ppcs_limit  tmp;

        tmp.u_min = umin;
        tmp.u_max = umax;
        tmp.v_min = vmin;
        tmp.v_max = vmax;
        return(tmp);
} 
*/

Pconorm3 
I_Pconorm3(colour,normal)
	Pcoval colour;
	Pvec3 normal;
{
        Pconorm3  tmp;

        tmp.colr = colour;
        tmp.norm = normal;
        return(tmp);
}

Pfacet_vdata_list3 
I_Pfacet_vdata_list3(number,vertexdata)
        int number;   
        Pfacet_vdata_arr3 vertexdata;
{
        Pfacet_vdata_list3  tmp;
 
        tmp.num_vertices = number;
        tmp.vertex_data = vertexdata;
        return(tmp);
}


Pedge_data_list_list
I_Pedge_data_list_list(number,edgelst)
        int number;
	Pedge_data_list *edgelst;
{
        Pedge_data_list_list  tmp;
 
        tmp.num_lists = number;
        tmp.edgelist = edgelst;
        return(tmp);
}
 
Pedge_data_list
I_Pedge_data_list(number,edgedata)
        int number;   
        Pedge_data_arr edgedata;
{
        Pedge_data_list  tmp;
 
        tmp.num_edges = number;
        tmp.edgedata = edgedata;
        return(tmp);
}


Pline_vdata_list3 
I_Pline_vdata_list3(number,vertexdata)
	int number;
	Pline_vdata_arr3 vertexdata;
{
        Pline_vdata_list3  tmp;
 
        tmp.num_vertices = number;
        tmp.vertex_data = vertexdata;
        return(tmp);
}


Prefl_props
I_Prefl_props(ambcoe,difcoe,specoe,specol,speexp,tracoe)
	Pfloat ambcoe,difcoe,specoe,speexp,tracoe;
        Pgcolr specol;
{
        Prefl_props  tmp;

	tmp.ambient_coef = ambcoe;
	tmp.diffuse_coef = difcoe;
	tmp.specular_coef = specoe;
	tmp.specular_colr = specol;
	tmp.specular_exp = speexp;
        return(tmp); 
} 


Pcolr_rep
I_Pcolr_rep(type,x,y,z)
	Pint type;
        Pfloat x,y,z;
{
        Pcolr_rep tmp;

	switch(type) {
	case PMODEL_RGB:
                tmp.rgb.red = x;
                tmp.rgb.green = y; 
                tmp.rgb.blue = z;
		break;
	case PMODEL_CIELUV:
                tmp.cieluv.cieluv_x = x;
                tmp.cieluv.cieluv_y = y;
                tmp.cieluv.cieluv_y_lum = z;
	case PMODEL_HSV:
                tmp.hsv.hue = x;
                tmp.hsv.satur = y; 
                tmp.hsv.value = z;
	case PMODEL_HLS:
                tmp.hls.hue = x;
                tmp.hls.lightness = y;
                tmp.hls.satur = z;
	default: 
		puts("I_Pcolr_rep: invalid type");
	}
        return(tmp);
}

Pline_bundle
I_Pline_bundle(type,width,colour)
        Pint type,colour;
        Pfloat width;
{ 
        Pline_bundle tmp; 
 
        tmp.type = type; 
        tmp.width = width;
        tmp.colr_ind = colour;
        return(tmp); 
} 

Pmarker_bundle 
I_Pmarker_bundle(type,size,colour)
        Pint type,colour;
        Pfloat size;
{  
        Pmarker_bundle tmp;  
  
        tmp.type = type; 
        tmp.size = size; 
        tmp.colr_ind = colour; 
        return(tmp);  
} 

Pint_bundle  
I_Pint_bundle(style,style_ind,colour) 
        Pint_style style;
	Pint style_ind,colour;
{  
        Pint_bundle tmp;   
   
        tmp.style = style;  
        tmp.style_ind = style_ind;  
        tmp.colr_ind = colour;  
        return(tmp);   
}  

Ptext_bundle   
I_Ptext_bundle(font,prec,exp,space,colour)
        Pint font,colour; 
	Ptext_prec prec;
	Pfloat exp,space;
{   
        Ptext_bundle tmp;    
    
        tmp.font = font;   
        tmp.prec = prec;   
        tmp.char_expan = exp;   
        tmp.char_space = space;   
        tmp.colr_ind = colour;   
        return(tmp);    
}   

Pedge_bundle   
I_Pedge_bundle(flag,type,width,colour)
	Pedge_flag flag;
        Pint type,colour;  
        Pfloat width; 
{    
        Pedge_bundle tmp;     
     
        tmp.flag = flag;    
        tmp.type = type;    
        tmp.width = width;   
        tmp.colr_ind = colour;
        return(tmp);   
}  

Ppat_rep
I_Ppat_rep(dims,array)
        Pint_size dims;
	Pint *array;
{
        Ppat_rep tmp;

        tmp.dims = dims;
        tmp.colr_array = array;
        return(tmp);
}

Pline_bundle_plus
I_Pline_bundle_plus(type,width,colour,shading,approx_type,approx_value)
        Pint type;
        Pfloat width;
	Pgcolr colour;
	Pint shading,approx_type;
	Pfloat approx_value;
{ 
        Pline_bundle_plus tmp; 
 
        tmp.type = type; 
        tmp.width = width;
        tmp.colr = colour;
        tmp.shad_meth = shading;
        tmp.approx_type = approx_type;
        tmp.approx_val = approx_value;
        return(tmp); 
} 

Pmarker_bundle_plus 
I_Pmarker_bundle_plus(type,size,colour)
        Pint type;
        Pfloat size;
	Pgcolr colour;
{  
        Pmarker_bundle_plus tmp;  
  
        tmp.type = type; 
        tmp.size = size; 
        tmp.colr = colour; 
        return(tmp);  
} 

Pint_bundle_plus  
I_Pint_bundle_plus(style,style_ind,colour,refl_eqn,shading,area_props, 
              bstyle,bstyle_ind,bcolour,brefl_eqn,bshading,barea_props, 
	      approx_type,approx_value0,approx_value1)
        Pint_style style;
	Pint style_ind;
	Pgcolr colour;
	Pint refl_eqn,shading;
	Prefl_props area_props;
        Pint_style bstyle;
	Pint bstyle_ind;
	Pgcolr bcolour;
	Pint brefl_eqn,bshading;
	Prefl_props barea_props;
	Pint approx_type;
	Pfloat approx_value0;
	Pfloat approx_value1;
{  
        Pint_bundle_plus tmp;   
   
        tmp.style = style;  
        tmp.style_ind = style_ind;  
        tmp.colr = colour;  
        tmp.refl_eqn = refl_eqn;  
        tmp.shad_meth = shading;  
        tmp.refl_props = area_props;  
        tmp.back_style = bstyle;  
        tmp.back_style_ind = bstyle_ind;  
        tmp.back_colr = bcolour;  
        tmp.back_refl_eqn = brefl_eqn;  
        tmp.back_shad_meth = bshading;  
        tmp.back_refl_props = barea_props;  
        tmp.approx_type = approx_type;  
        tmp.approx_val[0] = approx_value0;  
        tmp.approx_val[1] = approx_value1;  
        return(tmp);   
}  

Ptext_bundle_plus   
I_Ptext_bundle_plus(font,prec,exp,space,colour)
        Pint font; 
	Ptext_prec prec;
	Pfloat exp,space;
	Pgcolr colour;
{   
        Ptext_bundle_plus tmp;    
    
        tmp.font = font;   
        tmp.prec = prec;   
        tmp.char_expan = exp;   
        tmp.char_space = space;   
        tmp.colr = colour;   
        return(tmp);    
}   

Pedge_bundle_plus   
I_Pedge_bundle_plus(flag,type,width,colour)
	Pedge_flag flag;
        Pint type;  
        Pfloat width; 
	Pgcolr colour;
{    
        Pedge_bundle_plus tmp;     
     
        tmp.flag = flag;    
        tmp.type = type;    
        tmp.width = width;   
        tmp.colr = colour;
        return(tmp);   
}  

Ppat_rep_plus
I_Ppat_rep_plus(dims,type,array)
        Pint_size dims;
	Pint type;
	Pcoval *array;
{
        Ppat_rep_plus tmp;

        tmp.dims = dims;
        tmp.type = type;
        tmp.colr_array = array;
        return(tmp);
}



Pview_rep3
I_Pview_rep3(orientation_matrix,mapping_matrix,clip_limit,xy_clip,back_clip,front_clip)
	Pmatrix3 orientation_matrix;
	Pmatrix3 mapping_matrix;
	Plimit3 clip_limit;
	Pclip_ind xy_clip,back_clip,front_clip;
{
	Pview_rep3 tmp;

	bcopy((char*)orientation_matrix,tmp.ori_matrix,sizeof(Pmatrix3));
	bcopy((char*)mapping_matrix,tmp.map_matrix,sizeof(Pmatrix3));
	tmp.clip_limit = clip_limit;
	tmp.xy_clip = xy_clip;
	tmp.back_clip = back_clip;
	tmp.front_clip = front_clip;
	return(tmp);
}

Pview_rep
I_Pview_rep(orientation_matrix,mapping_matrix,clip_limit,xy_clip)
        Pmatrix orientation_matrix;
        Pmatrix mapping_matrix;
        Plimit clip_limit;
        Pclip_ind xy_clip;
{
        Pview_rep tmp; 
 
	bcopy((char*)orientation_matrix,tmp.ori_matrix,sizeof(Pmatrix));
	bcopy((char*)mapping_matrix,tmp.map_matrix,sizeof(Pmatrix));
        tmp.clip_limit = clip_limit;
        tmp.xy_clip = xy_clip;
	return(tmp);
}
 
Pview_map
I_Pview_map(window,viewport)
	Plimit window,viewport;
{
        Pview_map tmp;

        tmp.win = window;
        tmp.proj_vp = viewport;
        return(tmp);
}

Pview_map3
I_Pview_map3(window,viewport,proj,prp,view_plane,back_plane,front_plane)
        Plimit window;
	Plimit3 viewport; 
	Pproj_type proj;
	Ppoint3 prp;
	Pfloat view_plane,back_plane,front_plane;
{
        Pview_map3 tmp;
 
        tmp.win = window;
        tmp.proj_vp = viewport;
        tmp.proj_type = proj;
        tmp.proj_ref_point = prp;
        tmp.view_plane = view_plane;
        tmp.back_plane = back_plane;
        tmp.front_plane = front_plane;
        return(tmp);
}


/*
Ploc
I_Ploc(view_index,position)
        Pint view_index;
        Ppoint position;
{
        Ploc tmp;

        tmp.view_index = view_index;
        tmp.position = position;
        return(tmp);
}
*/

/*
Ploc3
I_Ploc3(view_index,position)
        Pint view_index;
        Ppoint3 position;
{
        Ploc tmp;

        tmp.view_index = view_index;
        tmp.position = position;
        return(tmp);
}
*/

/*
Pstroke
I_Pstroke(view_index,n_points,points)
        Pint view_index,n_points;
        Ppoint *points;
{
        Pstroke tmp;
 
        tmp.view_index = view_index;
        tmp.num_points = n_points;
        tmp.points = points;
        return(tmp);
}
*/

Pelem_ref_list_list
I_Pelem_ref_list_list(n,erls)
        Pint n;
        Pelem_ref_list *erls;
{
        Pelem_ref_list_list tmp;
 
        tmp.num_elem_ref_lists = n;
        tmp.elem_ref_lists = erls;
        return(tmp);
}

Pelem_ref_list
I_Pelem_ref_list(n,ers)
        Pint n;
        Pelem_ref *ers;
{
        Pelem_ref_list tmp;
 
        tmp.num_elem_refs = n;
        tmp.elem_refs = ers;
        return(tmp);
}

Pelem_ref
I_Pelem_ref(struct_id,elem_num)
        Pint struct_id;
        Pint elem_num;
{
        Pelem_ref tmp;
 
        tmp.struct_id = struct_id;
        tmp.elem_pos = elem_num;
        return(tmp);
}

Pfilter
I_Pfilter(incl_set,excl_set)
        Pint_list incl_set,excl_set;
{
        Pfilter tmp;
 
        tmp.incl_set = incl_set;
        tmp.excl_set = excl_set;
        return(tmp);
}

Pfilter_list
I_Pfilter_list(num_filters,filters)
        Pint num_filters;
	Pfilter* filters;
{
        Pfilter_list tmp;
 
        tmp.num_filters = num_filters;
        tmp.filters = filters;
        return(tmp);
}

Par_file
I_Par_file(id,name)
        Pint id;
	char* name;
{
        Par_file tmp;
 
        tmp.id = id;
        tmp.name = name;
        return(tmp);
}

Ppick_path_elem
I_Ppick_path_elem(struct_id,pick_id,elem_num)
        Pint struct_id,pick_id,elem_num ;
{
        Ppick_path_elem tmp;
 
        tmp.struct_id = struct_id;
        tmp.pick_id = pick_id;
        tmp.elem_pos = elem_num;
        return(tmp);
}

Ppick_path
I_Ppick_path(depth,path)
        Pint depth;
	Ppick_path_elem* path;
{
        Ppick_path tmp;
 
        tmp.depth = depth;
        tmp.path_list = path;
        return(tmp);
}



/* BEG: initialize simple data 
   I_...(union_type, list of data whose format depends on union_type) */

Ppara_surf_characs
I_Ppara_surf_characs(type,va_alist)
        int type;
        va_dcl
{
        Ppara_surf_characs  tmp;
        va_list ap;
 
        va_start(ap);
	switch(type) {
	case 1:
	case 2:
		break;
	case 3:
		tmp.psc_3.placement = va_arg(ap,Pcurve_placement);
		tmp.psc_3.u_count = va_arg(ap,Pint);
		tmp.psc_3.v_count = va_arg(ap,Pint);
		break;
	case 4:
		tmp.psc_4.origin = va_arg(ap,Ppoint3);
		tmp.psc_4.direction = va_arg(ap,Pvec3);
		tmp.psc_4.params = va_arg(ap,Pfloat_list);
		break;
	case 5:
		tmp.psc_5.origin = va_arg(ap,Ppoint3);
		tmp.psc_5.direction = va_arg(ap,Pvec3);
		tmp.psc_5.params = va_arg(ap,Pfloat_list);
		break;
	default:
		puts("I_Ppara_surf_characs: invalid type");
	}
        va_end(ap); 
        return(tmp); 
} 
Pval_data
I_Pval_data(pet,low,high,va_alist)
        int pet;
	Pfloat low,high;
        va_dcl
{
        Pval_data  tmp;
        va_list ap;
 
        va_start(ap);
	switch(pet) {
	case 1:
		break;
	case -1:
		tmp.pets.pet_u1.label = va_arg(ap,char*);
		tmp.pets.pet_u1.format = va_arg(ap,char*);
		tmp.pets.pet_u1.low_label = va_arg(ap,char*);
		tmp.pets.pet_u1.high_label = va_arg(ap,char*);
		break;
	default:
		puts("I_Pval_data: invalid pet");
	}
        va_end(ap); 
        return(tmp); 
} 

Pgcolr
I_Pgcolr(type,va_alist)
        int type;
        va_dcl
{
        Pgcolr  tmp;
        va_list ap;
 
        va_start(ap);
	switch(type) {
	case PINDIRECT:
		tmp.type = PINDIRECT;
		tmp.val.ind = va_arg(ap,Pint);
		break;
	case PMODEL_RGB:
		tmp.type = PMODEL_RGB;
		tmp.val.general.x = va_arg(ap,double);
		tmp.val.general.y = va_arg(ap,double);
		tmp.val.general.z = va_arg(ap,double);
		break;
	default:
		puts("I_Pgcolr: invalid type");
	}
        va_end(ap); 
        return(tmp); 
} 


Plight_src_bundle
I_Plight_src_bundle(type,va_alist)
        int type;
	va_dcl
{
        Plight_src_bundle  tmp;
        va_list ap; 
  
        va_start(ap); 
	tmp.type = type;
        switch(type) {
        case PLIGHT_AMBIENT:
		tmp.rec.ambient.colr = va_arg(ap,Pgcolr);
                break;
        case PLIGHT_DIRECTIONAL:
		tmp.rec.directional.colr = va_arg(ap,Pgcolr);
		tmp.rec.directional.dir = va_arg(ap,Pvec3);
                break;
        case PLIGHT_POSITIONAL:
		tmp.rec.positional.colr = va_arg(ap,Pgcolr);
		tmp.rec.positional.pos = va_arg(ap,Ppoint3);
		tmp.rec.positional.coef[0] = va_arg(ap,double);
		tmp.rec.positional.coef[1] = va_arg(ap,double);
                break;
        case PLIGHT_SPOT:
		tmp.rec.spot.colr = va_arg(ap,Pgcolr);
		tmp.rec.spot.pos = va_arg(ap,Ppoint3);
		tmp.rec.spot.dir = va_arg(ap,Pvec3);
		tmp.rec.spot.exp = va_arg(ap,double);
		tmp.rec.spot.coef[0] = va_arg(ap,double);
		tmp.rec.spot.coef[1] = va_arg(ap,double);
		tmp.rec.spot.angle = va_arg(ap,double);
                break;
        default:
                puts("I_Plight_src_bundle: invalid type");
        }
        va_end(ap); 
        return(tmp); 
} 

Pline_vdata_arr3 
I_Pline_vdata_arr3(type,va_alist)
	int type;
	va_dcl
{
	Pline_vdata_arr3  tmp;
	va_list ap;

	va_start(ap);
        switch(type) {
        case PVERT_COORD:
		tmp.points = va_arg(ap,Ppoint3*);
                break;
        case PVERT_COORD_COLOUR:
                tmp.ptcolrs = va_arg(ap,Pptco3*);
                break;
        default:
                puts("I_Pline_vdata_arr3: invalid type");
        }
	va_end(ap);
	return(tmp);
}

Pedge_data_arr 
I_Pedge_data_arr(n,va_alist)
	int n;
	va_dcl
{
	Pedge_data_arr  tmp;
	Pedge_flag *p;
	int i;
	va_list ap;

	va_start(ap);
	p = (Pedge_flag*) malloc(sizeof(Pedge_flag) * n);
	for (i=0;i<n;++i) {
		p[i] = va_arg(ap,Pedge_flag);
	}
	tmp.edges = p;
	va_end(ap);
	return(tmp);
}
Pfacet_data_arr3
I_Pfacet_data_arr3(type,va_alist)
        int type;
        va_dcl
{
        Pfacet_data_arr3  tmp;
        va_list ap;
 
        va_start(ap);
        switch(type) {
        case PFACET_NONE:
                break;
        case PFACET_COLOUR:
                tmp.colrs = va_arg(ap,Pcoval*);
                break;
        case PFACET_NORMAL:
                tmp.norms = va_arg(ap,Pvec3*);
                break;
        case PFACET_COLOUR_NORMAL:
                tmp.conorms = va_arg(ap,Pconorm3*);
                break;
        default:
                puts("I_Pfacet_data_arr3: invalid type");
        }
        va_end(ap);
        return(tmp);
}

Pfacet_data3
I_Pfacet_data3(type,va_alist)
	int type;
        va_dcl
{
        Pfacet_data3  tmp;
        va_list ap;
 
        va_start(ap);
        switch(type) {
        case PFACET_NONE:
                break;
        case PFACET_COLOUR:
                tmp.colr = va_arg(ap,Pcoval);
                break;
        case PFACET_NORMAL:
                tmp.norm = va_arg(ap,Pvec3);
                break;
        case PFACET_COLOUR_NORMAL:
                tmp.conorm = va_arg(ap,Pconorm3);
                break;
        default:
                puts("I_Pfacet_data_arr3: invalid type");
        }
        va_end(ap);
        return(tmp);
}

Pfacet_vdata_arr3
I_Pfacet_vdata_arr3(type,va_alist)
        int type;
        va_dcl
{
        Pfacet_vdata_arr3  tmp;
        va_list ap;
 
        va_start(ap);
        switch(type) {
        case PVERT_COORD:
		tmp.points = va_arg(ap,Ppoint3*);
                break;
        case PVERT_COORD_COLOUR:
                tmp.ptcolrs = va_arg(ap,Pptco3*);
                break;
        case PVERT_COORD_NORMAL:
                tmp.ptnorms = va_arg(ap,Pptnorm3*);
                break;
        case PVERT_COORD_COLOUR_NORMAL:
                tmp.ptconorms = va_arg(ap,Pptconorm3*);
                break;
        default:
                puts("I_Pfacet_vdata_arr3: invalid type");
        }
        va_end(ap);
        return(tmp);
}

Pcoval
I_Pcoval(type,va_alist)
        int type;
        va_dcl
{
        Pcoval  tmp;
        va_list ap;
 
        va_start(ap);
	switch(type) {
	case PINDIRECT:
		tmp.ind = va_arg(ap,Pint);
		break;
	case PMODEL_RGB:
                tmp.direct.rgb.red = va_arg(ap,double);
                tmp.direct.rgb.green = va_arg(ap,double);
                tmp.direct.rgb.blue = va_arg(ap,double);
		break;
	case PMODEL_CIELUV:
                tmp.direct.cieluv.cieluv_x = va_arg(ap,double);
                tmp.direct.cieluv.cieluv_y = va_arg(ap,double);
                tmp.direct.cieluv.cieluv_y_lum = va_arg(ap,double);
	case PMODEL_HSV:
                tmp.direct.hsv.hue = va_arg(ap,double);
                tmp.direct.hsv.satur = va_arg(ap,double);
                tmp.direct.hsv.value = va_arg(ap,double);
	case PMODEL_HLS:
                tmp.direct.hls.hue = va_arg(ap,double);
                tmp.direct.hls.lightness = va_arg(ap,double);
                tmp.direct.hls.satur = va_arg(ap,double);
	default: 
		puts("I_Pcoval: invalid type");
	}
        va_end(ap); 
        return(tmp); 
} 

Pelem_data
I_Pelem_data(type,va_alist)
        int type;
        va_dcl
{
        Pelem_data  tmp;
	int i,j;
        va_list ap;
 
        va_start(ap);
	switch(type) {
    	case PELEM_MARKER_IND:
   	case PELEM_MARKER_COLR_IND:
    	case PELEM_MARKER_TYPE:
    	case PELEM_LINE_IND:
    	case PELEM_LINETYPE:
    	case PELEM_LINE_COLR_IND:
    	case PELEM_TEXT_COLR_IND:
    	case PELEM_TEXT_IND:
    	case PELEM_TEXT_FONT:
    	case PELEM_ANNO_STYLE:
    	case PELEM_EDGE_COLR_IND:
    	case PELEM_EDGETYPE:
    	case PELEM_EDGE_IND:
    	case PELEM_INT_IND:
    	case PELEM_INT_STYLE_IND:
    	case PELEM_INT_COLR_IND:
    	case PELEM_VIEW_IND:
    	case PELEM_EXEC_STRUCT:
    	case PELEM_LABEL:
    	case PELEM_HLHSR_ID:
		tmp.int_data = va_arg(ap,Pint);
		break;
    	case PELEM_MARKER_SIZE:
    	case PELEM_LINEWIDTH:
    	case PELEM_CHAR_EXPAN:
    	case PELEM_CHAR_SPACE:
    	case PELEM_CHAR_HT:
    	case PELEM_ANNO_CHAR_HT:
    	case PELEM_EDGEWIDTH:
		tmp.float_data = va_arg(ap,double);
		break;
	case PELEM_POLYLINE3:
		tmp.point_list3.num_points = va_arg(ap,Pint);
		for (i=0;i<tmp.point_list3.num_points;++i) {
			tmp.point_list3.points[i].x = va_arg(ap,double);
			tmp.point_list3.points[i].y = va_arg(ap,double);
			tmp.point_list3.points[i].z = va_arg(ap,double);
		}
		break;
	default:
		puts("I_Pelem_data: invalid type");
	}
        va_end(ap); 
        return(tmp); 
} 

/* BEG: initialize simple of data:
   I_...(number, list of specified type */

Phalf_space_list 
I_Phalf_space_list(n,va_alist)
        int n;
        va_dcl
{
        Phalf_space_list  tmp;
        Phalf_space  *p;
        int i;
        va_list ap;
 
        va_start(ap);
        p = (Phalf_space*) malloc(sizeof(Phalf_space) * n);
        for (i=0;i<n;++i) {
                p[i] = va_arg(ap,Phalf_space);
        }
	tmp.num_half_spaces = n;
	tmp.half_spaces = p;
        va_end(ap);
        return(tmp);
}

Phalf_space_list3 
I_Phalf_space_list3(n,va_alist)
        int n;
        va_dcl
{
        Phalf_space_list3  tmp;
        Phalf_space3  *p;
        int i;
        va_list ap;

        va_start(ap);
        p = (Phalf_space3*) malloc(sizeof(Phalf_space3) * n);
        for (i=0;i<n;++i) {
                p[i] = va_arg(ap,Phalf_space3);
        }
	tmp.num_half_spaces = n;
	tmp.half_spaces = p;
        va_end(ap);
        return(tmp);
}

/* BEG: initialize simple of data:
   I_...(special cases)  */

void
I_Pmatrix(tmp,a00,a01,a02,a10,a11,a12,a20,a21,a22)
	Pmatrix tmp;
	float a00,a01,a02,a10,a11,a12,a20,a21,a22;
{
	tmp[0][0] = a00;
	tmp[0][1] = a01;
	tmp[0][2] = a02;
	tmp[1][0] = a10;
	tmp[1][1] = a11;
	tmp[1][2] = a12;
	tmp[2][0] = a20;
	tmp[2][1] = a21;
	tmp[2][2] = a22;
}

void
I_Pmatrix3(tmp,a00,a01,a02,a03,a10,a11,a12,a13,a20,a21,a22,a23,a30,a31,a32,a33)
	Pmatrix3 tmp;
	float a00,a01,a02,a03,a10,a11,a12,a13,a20,a21,a22,a23,a30,a31,a32,a33;
{
	tmp[0][0] = a00;
	tmp[0][1] = a01;
	tmp[0][2] = a02;
	tmp[0][3] = a03;
	tmp[1][0] = a10;
	tmp[1][1] = a11;
	tmp[1][2] = a12;
	tmp[1][3] = a13;
	tmp[2][0] = a20;
	tmp[2][1] = a21;
	tmp[2][2] = a22;
	tmp[2][3] = a23;
	tmp[3][0] = a30;
	tmp[3][1] = a31;
	tmp[3][2] = a32;
	tmp[3][3] = a33;
}

Ppoint_list23
I_Ppoint_list23(n,type,va_alist) 
        int n; 
	char *type;
	va_dcl
	
{  
        Ppoint_list23  tmp;  
        va_list ap;
   
        tmp.num_points = n;   
	va_start(ap);
	if (eqstring(type,"2D")) {
        	tmp.points.point2d = va_arg(ap,Ppoint*);  
	} else if (eqstring(type,"3D")) {
        	tmp.points.point3d = va_arg(ap,Ppoint3*);  
	} else
		puts("I_Ppoint_list23: invalid type");
	va_end(ap);
        return(tmp);   
}  

Ppoint_list34
I_Ppoint_list34(n,type,va_alist) 
        int n; 
	char *type;
	va_dcl
	
{  
        Ppoint_list34  tmp;  
        va_list ap;
   
        tmp.num_points = n;   
	va_start(ap);
	if (eqstring(type,"3D")) {
        	tmp.points.point3d = va_arg(ap,Ppoint3*);  
	} else if (eqstring(type,"4D")) {
        	tmp.points.point4d = va_arg(ap,Ppoint4*);  
	} else
		puts("I_Ppoint_list34: invalid type");
	va_end(ap);
        return(tmp);   
}  


Ppoint_grid34 
I_Ppoint_grid34(u_dim,v_dim,type,va_alist)
        int u_dim,v_dim;
	char *type;
	va_dcl
{
        Ppoint_grid34  tmp;
        va_list ap;

        tmp.num_points.u_dim = u_dim;
        tmp.num_points.v_dim = v_dim;
	va_start(ap);
	if (eqstring(type,"3D")) {
        	tmp.points.point3d = va_arg(ap,Ppoint3*);  
	} else if (eqstring(type,"4D")) {
        	tmp.points.point4d = va_arg(ap,Ppoint4*);  
	} else
		puts("I_Ppoint_list34: invalid type");
	va_end(ap);
        return(tmp);
} 

Pdcue_bundle
I_Pdcue_bundle(mode,ref0,ref1,scale0,scale1,col)
        Pfloat ref0,ref1,scale0,scale1;
        Pgcolr col;
	Pdcue_mode mode;
{
        Pdcue_bundle  tmp;

        tmp.mode = mode;
        tmp.ref_planes[0] = ref0;
        tmp.ref_planes[1] = ref1;
        tmp.scaling[0] = scale0;
        tmp.scaling[1] = scale1;
        tmp.colr = col;
        return(tmp);
}
