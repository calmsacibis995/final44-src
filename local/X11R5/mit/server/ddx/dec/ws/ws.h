/***********************************************************
Copyright 1991 by Digital Equipment Corporation, Maynard, Massachusetts,
and the Massachusetts Institute of Technology, Cambridge, Massachusetts.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the names of Digital or MIT not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.  

DIGITAL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
DIGITAL BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/
/* $XConsortium: ws.h,v 1.2 91/07/08 11:16:30 keith Exp $ */

#define NOMAPYET        (ColormapPtr) 1

#define  ARG_DPIX	(1 << 0)
#define  ARG_DPIY	(1 << 1)
#define  ARG_DPI	(1 << 2)
#define  ARG_BLACKVALUE	(1 << 3)
#define  ARG_WHITEVALUE	(1 << 4)
#define	 ARG_CLASS	(1 << 5)
#define	 ARG_EDGE_L	(1 << 6)
#define	 ARG_EDGE_R	(1 << 7)
#define	 ARG_EDGE_T	(1 << 8)
#define	 ARG_EDGE_B	(1 << 9)
#define  ARG_MONITOR	(1 << 10)

typedef struct  {
	int flags;
	int dpix;
	int dpiy;
	int dpi;
	int class;
	char  *blackValue;
	char  *whiteValue;
	int edge_left;
	int edge_right;
	int edge_top;
	int edge_bottom;
	ws_monitor monitor;
} ScreenArgsRec;

typedef struct {
	unsigned int		currentmask; 	/* saved plane mask */
	BoxPtr			cursorConstraint;
	ws_screen_descriptor	*screenDesc;
	ColormapPtr		pInstalledMap;
	ScreenArgsRec 		*args;
	Bool			(*CloseScreen)();
} wsScreenPrivate;

typedef struct {
	char *moduleID;	/* graphic module ID */
	Bool (*createProc)();	/* create procedure for this hardware type */
} wsAcceleratorTypes;

extern void wsStoreColors();
extern void wsInstallColormap();
extern void wsUninstallColormap();
extern int wsListInstalledColormaps();
extern int wsScreenPrivateIndex;
extern Bool wsSaveScreen();
extern int dpix, dpiy, dpi;

extern ScreenArgsRec screenArgs[];

extern ScreenPtr wsScreens[];
extern int class;
extern int fdPM;   /* this is the file descriptor for screen so
		    can do IOCTL to colormap */
extern int ws_cpu;

