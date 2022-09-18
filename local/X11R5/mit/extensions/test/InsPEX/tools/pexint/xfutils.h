
/* $XConsortium: xfutils.h,v 5.1 91/02/16 10:00:23 rws Exp $ */

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


extern void i_translate();
extern void i_translate3();
extern void i_scale3();
extern void i_scale();
extern void i_rotate();
extern void i_rotatex();
extern void i_rotatey();
extern void i_rotatez();
extern void i_buildtran3();
extern void i_buildtran();
extern void i_composetran3();
extern void i_composetran();
extern void i_composematrix();
extern void i_composematrix3();
extern void i_evalvieworientationmtx3();
extern void i_evalvieworientationmtx();
extern void i_evalviewmappingmtx3();
extern void i_evalviewmappingmtx();
extern void i_tranpt();
extern void i_tranpt3();
extern void i_identity();
extern void i_identity3();
