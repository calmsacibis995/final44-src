
/* $XConsortium: xfutils.m,v 5.1 91/02/16 10:00:32 rws Exp $ */

/*****************************************************************
Copyright (c) 1989, 1990, 1991,1990 by Sun Microsystems, Inc. and the X Consortium.

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


/* transformation utility routines */
void		i_translate(Pvec,Pmatrix)
void		i_translate3(Pvec3,Pmatrix3)
void		i_scale(Pvec,Pmatrix)
void		i_scale3(Pvec3,Pmatrix3)
void		i_rotate(Pfloat,Pmatrix)
void		i_rotatex(Pfloat,Pmatrix3)
void		i_rotatey(Pfloat,Pmatrix3)
void		i_rotatez(Pfloat,Pmatrix3)
void		i_composematrix(Pmatrix,Pmatrix,Pmatrix)
void		i_composematrix3(Pmatrix3,Pmatrix3,Pmatrix3)
void		i_buildtran(Ppoint,Pvec,Pfloat,Pvec,Pmatrix)
void		i_buildtran3(Ppoint3,Pvec3,Pfloat,Pfloat,Pfloat,Pvec3,Pmatrix3)
void		i_composetran(Pmatrix,Ppoint,Pvec,Pfloat,Pvec,Pmatrix)
void		i_composetran3(Pmatrix3,Ppoint3,Pvec3,Pfloat,Pfloat,Pfloat,Pvec3,Pmatrix3)
void		i_evalvieworientationmtx(Ppoint,Pvec,Pmatrix)
void		i_evalvieworientationmtx3(Ppoint3,Pvec3,Pvec3,Pmatrix3)
void		i_evalviewmappingmtx(Pview_map,Pmatrix)
void		i_evalviewmappingmtx3(Pview_map3,Pmatrix3)
void		i_tranpt(Ppoint,Pmatrix,Ppoint*)
void		i_tranpt3(Ppoint3,Pmatrix3,Ppoint3*)
void		i_identity(Pmatrix)
void		i_identity3(Pmatrix3)
