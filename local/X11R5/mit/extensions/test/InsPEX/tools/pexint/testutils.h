
/* $XConsortium: testutils.h,v 5.2 91/05/06 11:23:18 hersh Exp $ */

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


#ifndef _testutils_h
#define _testutils_h

#include <phigs/phigs.h>
#include "portable.h"

extern void i_open_phigs();
extern void i_open_ws();
extern void i_open_x_ws();
extern void i_fake_button();
extern Ppoint3* i_generate_n_Ppoint3();
extern Ppoint_list3* i_generate_n_Ppoint_list3();
extern int i_check_line3();
extern int i_check_pixel3();
extern void i_viewxform_point3();
extern void i_wsxform_point3();
extern void i_get_window_dim();
extern void i_make_xwindow();
extern Pint i_get_ws_type();
extern void i_print_var();
extern void i_pause();
extern int i_bogus_error();
extern Pdyn_mod i_get_ws_dyn_mod();
extern Pdyn_mod i_get_struct_dyn_mod();
extern int i_get_phigs_info();
extern int i_is_posted_struct();

/*
 * the interpreter version of tfprintf and tvprintf
 */
#ifdef NEWT
extern void _tfprintf();
extern void _tvprintf();
extern void _tabort();
#endif NEWT

#endif /* _testutils_h */
