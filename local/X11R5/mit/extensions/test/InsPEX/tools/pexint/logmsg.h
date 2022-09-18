
/* $XConsortium: logmsg.h,v 5.1 91/02/16 10:00:15 rws Exp $ */

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
 * Message logging utilities
 */
extern char    *testname;	/* current test name */
extern char    *testdesc;	/* test description */
extern int      maxfail;    	/* max failures before abort */
extern int      numfail;    	/* current number of failures */
extern int      verbosity;  	/* verbosity level */
extern int      pausebetweenframe;  	/* pause flag */
extern int      clientside;  	/* 1 for client side storage testing */
extern char    *inspexdest;  	/* path for inspex destination directory */
extern char    *inspeximageref;	/* path for inspex image directory */
extern int      showpix;	/* 1 for showing where pixels are sampled */
extern int      nomonitor;	/* 1 for no monitor testing */
extern int      xtoolws;	/* 1 for x tool ws testing */
extern int      grid;		/* 1 for showing grid in some tests */
extern int      winxoffset;	/* x offset for putting window */
extern int      winyoffset;	/* y offset for putting window */

extern void tbegintest();
extern void tfprintf();
extern void tvprintf();
extern void tendtest();
extern void tabort();

