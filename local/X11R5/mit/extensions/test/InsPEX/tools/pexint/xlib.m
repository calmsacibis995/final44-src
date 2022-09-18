
/* $XConsortium: xlib.m,v 5.1 91/02/16 10:00:13 rws Exp $ */

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


/*** these are the one's I've put arguments into ****/

Display* XOpenDisplay(char*)
Colormap XDefaultColormap(Display*,int)
GC XDefaultGC(Display*,int)
Window XCreateWindow(Display*,Window,int,int,unsigned int,unsigned int, int, unsigned int, Visual*, unsigned long, XSetWindowAttributes); 
void XSync(Display*,int)
void XDestroyWindow(Display*,Window)

/****** have to get the argument types into these... ******
char *XFetchBytes();
char *XFetchBuffer();
char *XGetAtomName();
char *XGetDefault();
char *XDisplayName();
char *XKeysymToString();

int (*XSynchronize())();
int (*XSetAfterFunction())();
Atom XInternAtom();
Colormap XCopyColormapAndFree(), XCreateColormap();
Cursor XCreatePixmapCursor(), XCreateGlyphCursor(), XCreateFontCursor();
Font XLoadFont();
GC XCreateGC();
GContext XGContextFromGC();
Pixmap XCreatePixmap();
Pixmap XCreateBitmapFromData(), XCreatePixmapFromBitmapData();
Window XCreateSimpleWindow(), XGetSelectionOwner();
Colormap *XListInstalledColormaps();
char **XListFonts(), **XListFontsWithInfo(), **XGetFontPath();
char **XListExtensions();
Atom *XListProperties();
XImage *XCreateImage(), *XGetImage(), *XGetSubImage();
XHostAddress *XListHosts();
KeySym XKeycodeToKeysym(), XLookupKeysym(), *XGetKeyboardMapping();
KeySym XStringToKeysym();
long XMaxRequestSize();
char *XResourceManagerString();
unsigned long XDisplayMotionBufferSize();
VisualID XVisualIDFromVisual();
Status XGetSizeHints();

XExtCodes *XInitExtension();
int (*XESetCreateGC())(), (*XESetCopyGC())(), (*XESetFlushGC())(),
    (*XESetFreeGC())(), (*XESetCreateFont())(), (*XESetFreeFont())(), 
    (*XESetCloseDisplay())(),
    (*XESetError())(), (*XESetErrorString())();
Bool (*XESetWireToEvent())();
Status (*XESetEventToWire())();
XExtCodes *XAddExtension();
XExtData *XFindOnExtensionList();
XExtData **XEHeadOfExtensionList();

Window XRootWindow(), XDefaultRootWindow(), XRootWindowOfScreen();
Visual *XDefaultVisual(), *XDefaultVisualOfScreen();
GC XDefaultGCOfScreen();
unsigned long XBlackPixel(), XWhitePixel(), XAllPlanes();
unsigned long XBlackPixelOfScreen(), XWhitePixelOfScreen();
unsigned long XNextRequest(), XLastKnownRequestProcessed();
char *XServerVendor(), *XDisplayString();
Colormap XDefaultColormapOfScreen();
Display *XDisplayOfScreen();
Screen *XScreenOfDisplay(), *XDefaultScreenOfDisplay();
long XEventMaskOfScreen();

int XScreenNumberOfScreen();
int (*XSetErrorHandler())(), (*XSetIOErrorHandler())();
XPixmapFormatValues *XListPixmapFormats();
Status XReconfigureWMWindow();
int XWMGeometry();
Status XGetWMSizeHints(), XGetWMNormalHints();
Status XGetRGBColormaps();
Status XGetTextProperty(), XGetWMName(), XGetWMIconName();
Status XGetWMClientMachine(), XGetWMCommand();
Status XGetWMColormapWindows(), XSetWMColormapWindows();
Status XGetWMProtocols(), XSetWMProtocols();
Status XGetWMState(), XSetWMState();
Status XIconifyWindow(), XWithdrawWindow();
Status XGetCommand();
void XSetWMProperties(), XSetWMSizeHints(), XSetWMNormalHints();
void XSetRGBColormaps();
void XSetTextProperty(), XSetWMName(), XSetWMIconName();
void XSetWMClientMachine(), XSetWMCommand();
Status XStringListToTextProperty(), XTextPropertyToStringList();
void XFreeStringList();

*******/
