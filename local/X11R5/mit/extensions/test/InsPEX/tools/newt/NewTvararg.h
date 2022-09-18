
/* $XConsortium: NewTvararg.h,v 5.2 91/02/16 09:59:49 rws Exp $ */

/*
 * Copyright (c) 1988-1991 by Sun Microsystems, Inc.
 */

/*
 * NewTvarargs.h - The NewT version of varargs.h
 */
typedef char** 		va_list;
#define va_dcl	char  	**va_alist;
#define va_start(list)  list = va_alist;
#define va_end(list)
#define va_arg(list,mode) *((mode*)(*list++))
