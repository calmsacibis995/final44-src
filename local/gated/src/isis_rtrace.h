/*
 *  isis_rtrace.h,v 1.11 1993/01/07 22:39:54 jch Exp
 */

/* %(Copyright.header) */


#ifndef _trace_h
#define _trace_h

/*
 *	Trace events
 */

typedef struct {
	u_int	flags;
	FILE	*fp;
} Logger;

#define	T_ISISALL	0xffff
#define	T_DUMPIIH	0x0001
#define T_DUMPLSP	0x0002
#define T_EVENTS	0x0004
#define	T_LANADJ	0x0008
#define T_FLOODING	0x0010
#define	T_BUILDLSP	0x0020
#define	T_CSNP		0x0040
#define	T_PSNP		0x0080
#define	T_LSPINPUT	0x0100
#define	T_P2PADJ	0x0200
#define T_TRSPF		0x0400
#define T_DUMPDB	0x0800
#define T_ROUTE1 	0x1000 		/* route changes only */
#define T_ROUTE2 	0x2000 		/* all routes; 1st hop only */
#define T_ROUTE3 	0x4000 		/* all routes + path back from dest */
#define T_LSPCONTENT 	0x8000 		/* dump contents of LSPs */

#define IFTRACE(t) if (debugLog.flags & (t)) {
#define ENDTRACE	}

#endif 	/* _trace_h */


/*
 * %(Copyright)
 * %(Copyright.ISIS)
 */
