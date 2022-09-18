#
/* action.h
 *
 * Copyright (c) 1985 Adobe Systems Incorporated
 *
 * action table types for pscat/pscatmap/ptroff character mapping
 *
 * RCSID: $Header: action.h,v 2.1 85/11/24 12:07:51 shore Rel $
 *
 * Edit History:
 * Andrew Shore: Tue May 14 10:09:10 1985
 * End Edit History.
 *
 * RCSLOG:
 * $Log:	action.h,v $
 * Revision 2.1  85/11/24  12:07:51  shore
 * Product Release 2.0
 * 
 * Revision 1.2  85/05/14  11:21:08  shore
 * 
 * 
 *
 */

#define PFONT 1
#define PLIG 2
#define PPROC 3
#define PNONE 4

struct chAction {
    unsigned char	actCode;
    char *		actName;
};


struct map {
	int	wid;
	int	x,y;
	int	font;
	int	pschar;
	int	action;
	int	pswidth;
};
