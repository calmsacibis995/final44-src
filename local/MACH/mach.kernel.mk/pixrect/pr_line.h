/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	pr_line.h,v $
 * Revision 2.4  89/03/09  20:57:24  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:12:39  gm0w
 * 	Added new copyright and #ifndef <filename>_H_ around whole
 * 	file as part of kernel cleanup.
 * 	[89/02/13            jjc]
 * 
 */
/*	@(#)pr_line.h 1.3 86/10/08 SMI	*/

/* 
 * Copyright 1986 by Sun Microsystems, Inc.
 */
 

#ifndef	PR_LINE_H_
#define PR_LINE_H_ 

#define POLY_CLOSE	((u_char *) 1)	
#define POLY_DONTCLOSE	((u_char *) 0)

extern short pr_tex_dotted[]; 
extern short pr_tex_dashed[]; 
extern short pr_tex_dashdot[]; 
extern short pr_tex_dashdotdotted[];
extern short pr_tex_longdashed[]; 


typedef 
    struct pr_texture {
	short *pattern;
	short offset;
	struct pr_texture_options {
	    unsigned startpoint : 1,
	    endpoint : 1,
	    balanced : 1, 
	    givenpattern : 1,
	    res_fat : 1,
	    res_poly : 1,
	    res_mvlist : 1,
	    res_right : 1,
	    res_close : 1,
	    res_cliprt : 1;
	} options;
	short res_polyoff;
	short res_oldpatln;
	short res_fatoff;
	short *res_patfat;
	short res_numsegs;
    } Pr_texture;
    
    
typedef
    struct pr_brush {
	int width;
    } Pr_brush;

#endif	PR_LINE_H_ 



