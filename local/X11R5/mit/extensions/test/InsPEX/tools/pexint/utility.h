
/* $XConsortium: utility.h,v 5.1 91/02/16 10:00:10 rws Exp $ */

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


#ifndef _utility_h
#define _utility_h

#include "stdio.h"
#ifdef SYSV  
#include <string.h> 
#else
#include <strings.h> 
#endif
#include "malloc.h"
#include "imath.h"

extern char* getenv();

extern int plus();
extern int minus();
extern int multiply();
extern int divide();
extern int equal();
extern int ifval();
extern int and();
extern int or();
extern int not();
extern int bitand();
extern int bitor();
extern int bitnot();
extern double ftod();
extern int fequal();
extern float fplus();
extern float fminus();
extern float fmultiply();
extern float fdivide();
extern void _printf();
extern void beep();
extern void unlink();

#endif /* _utility_h */
