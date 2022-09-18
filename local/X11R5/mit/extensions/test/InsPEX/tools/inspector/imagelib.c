/* $XConsortium: imagelib.c,v 5.1 91/02/16 09:59:41 rws Exp $ */

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
 * imagelib.c - image library.
 * image utilities library for comparison tool
 */

/* 
 * header files
 */
#include "stdio.h"
#include "fcntl.h"
#include "X11/Xlib.h"
#include "X11/Xutil.h"
#include "imagelib.h"
#include "varargs.h"

/*
 * constants
 */
#define SIZECMAPENTRY 4
#define MAXCMAPDATASIZE  (MAXCOLOR * SIZECMAPENTRY + 2)
                /* extra 2 bytes to store number of bytes of cmap data */

#define PSEUDOCOLOR 1


/* 
 * global variables 
 */
static Unsign8 cmapdata[MAXCMAPDATASIZE]; /* image data to be saved */

/*
 * extern funcitons
 */
char *malloc();

/*
 * table of contents
 */

/* exported routines */
void i_diff_image();
void i_load_image();
void i_load_image2();
void i_display_image();
void i_free_image();
void i_free_cmap();

/* local routines */
static void i_retrieve_image();
static void i_retrieve_cmap();
static void i_convert_image();
static void i_read();
static void i_8_to_16();
static void i_8_to_32();
static unsigned short i_scale_uchar_to_ushort();
static int i_get_bits_per_rgb();
static void fatal();
static char *emalloc();

/*
 Image file format:
<1 byte : flag indicating monochrome or pseudocolor type>
<2 bytes: number of bytes of ascii text to follow>
<n bytes: ascii text>
<2 bytes: width of image>
<2 bytes: height of image>
<2 bytes: number of colormap data entries>
<n bytes: colormap data of the form
        (pixel[1 byte],red[1 byte],green[1 byte],blue[1 byte]) quadriples >
<4 bytes: number of bytes of image data>
<n bytes: image data of the form (number[1 byte],pixel[1 byte]) pairs >
*/

/*
 * i_load_image(filename,display,visual,imagestr,cmapstr,text,err) 
 * load an image from a file 
 */
void
i_load_image(filename,display,visual,imagestr,cmapstr,text,err)
	char *filename;		/* image file name */
	Display *display;	/* X display */
	Visual *visual;		/* visual type */
	I_image *imagestr;	/* OUT image structure */
        I_cmap *cmapstr;       	/* OUT colormap structure */
        char *text;             /* OUT image description */
	int *err;		/* OUT error flag */
{
	/*
	To load an image from file to X's image structure.
	Create and store necessary colors in the color map.
	*/
        int fd;
	Unsign32 nbyte;
	static Unsign8 cmaptbl[MAXCOLOR];
	Unsign16 ntext,ncol;
	Unsign8 buf[6];
        Window rootwindow;

	*err = 0;
        rootwindow = DefaultRootWindow(display);
        if ((fd = open(filename,O_RDONLY)) == -1) {
                printf("ERROR: i_loadimage: can't open file %s\n",filename);
		*err = 1;
		return;
	}
	i_read(fd,3,(char*)buf);
	if (buf[0] != PSEUDOCOLOR)
		fatal("ABORT: i_loadimage: unknown image file type\n");
	i_8_to_16(&buf[1],&ntext); /* get number of bytes of text */
	i_read(fd,(int)ntext,text);
	text[ntext] = '\0';
	i_read(fd,6,(char*)buf);
	i_8_to_16(&buf[0],&imagestr->width); 	
	i_8_to_16(&buf[2],&imagestr->height); 	
	i_8_to_16(&buf[4],&ncol); 	
	if (ncol > MAXCOLOR) {
		printf("ERROR: i_loadimage: invalid data: number of colors > %d\n",MAXCOLOR);
		*err = 1;
		return;
	}
	i_read(fd,(int)(ncol*SIZECMAPENTRY),(char*)cmapdata);
	i_retrieve_cmap(display,rootwindow,visual,1,ncol,cmapdata,cmapstr,cmaptbl);
	i_read(fd,4,(char*)buf);
	i_8_to_32(&buf[0],&nbyte);
	imagestr->imagedata = (unsigned char*) emalloc(nbyte);
	i_read(fd,(int)nbyte,(char*)imagestr->imagedata);
	i_retrieve_image(display,visual,cmaptbl,nbyte,imagestr,err);
}

/*
 * i_load_image2(filename1,filename2,display,visual,imagestr1,imagestr2,cmapstr1,
 *	cmapstr2,text1,text2,singlecmap,err) load 2 images from 2 files
 *      This has the advantage of sharing a single colormap if the total
 *      number of color used is less than MAXCOLOR-1 (1 less for background)
 */
void
i_load_image2(filename1,filename2,display,visual,imagestr1,imagestr2,cmapstr1,
	cmapstr2,text1,text2,istwocmap,err) 
	char *filename1;	/* image file name */
	char *filename2;	/* image file name */
	Display *display;	/* X display */
	Visual *visual;		/* visual type */
	I_image *imagestr1;	/* OUT image structure */
	I_image *imagestr2;	/* OUT image structure */
        I_cmap *cmapstr1;      	/* OUT colormap structure */
        I_cmap *cmapstr2;      	/* OUT colormap structure */
        char *text1;            /* OUT image description */
        char *text2;            /* OUT image description */
	int *istwocmap;		/* OUT 1 if 2 cmap is used, 0 otherwise */
	int *err;		/* OUT error flag */
{
        int fd1,fd2;
	Unsign32 nbyte;
	static Unsign8 cmaptbl1[MAXCOLOR],cmaptbl2[MAXCOLOR];
	Unsign16 ntext,ncol1,ncol2;
	Unsign8 buf1[6],buf2[6];
        Window rootwindow;


	*err = 0;
        rootwindow = DefaultRootWindow(display);

        if ((fd1 = open(filename1,O_RDONLY)) == -1) {
                printf("ERROR: i_readimage: can't open file %s\n",filename1);
		*err = 1;
		return;
	}
        if ((fd2 = open(filename2,O_RDONLY)) == -1) {
                printf("ERROR: i_readimage: can't open file %s\n",filename2);
		*err = 1;
		return;
	}

	i_read(fd1,3,(char*)buf1);
	if (buf1[0] != PSEUDOCOLOR)
		fatal("ABORT: i_loadimage2: unknown image file type\n");
	i_8_to_16(&buf1[1],&ntext); /* get number of bytes of text */
	i_read(fd1,(int)ntext,text1);
	text1[ntext] = '\0';

	i_read(fd2,3,(char*)buf2);
	if (buf2[0] != PSEUDOCOLOR)
		fatal("ABORT: i_loadimage2: unknown image file type\n");
	i_8_to_16(&buf2[1],&ntext); /* get number of bytes of text */
	i_read(fd2,(int)ntext,text2);
	text2[ntext] = '\0';

	i_read(fd1,6,(char*)buf1);
	i_8_to_16(&buf1[0],&imagestr1->width); 	
	i_8_to_16(&buf1[2],&imagestr1->height); 	
	i_8_to_16(&buf1[4],&ncol1); 	
	i_read(fd2,6,(char*)buf2);
	i_8_to_16(&buf2[0],&imagestr2->width); 	
	i_8_to_16(&buf2[2],&imagestr2->height); 	
	i_8_to_16(&buf2[4],&ncol2); 	

	if (ncol1 > MAXCOLOR || ncol2 > MAXCOLOR) {
		printf("ERROR: i_loadimage2: invalid data\n");
		*err = 1;
		return;
	}
	/* 1 less than MAXCOLOR because of background color */
	*istwocmap = (ncol1 + ncol2 < MAXCOLOR -1)? 0 : 1; 

	i_read(fd1,(int)(ncol1*SIZECMAPENTRY),(char*)cmapdata);
	i_retrieve_cmap(display,rootwindow,visual,1,ncol1,cmapdata,cmapstr1, cmaptbl1);
	i_read(fd2,(int)(ncol2*SIZECMAPENTRY),(char*)cmapdata);
	if (*istwocmap) { /* can not share colormap */
		i_retrieve_cmap(display,rootwindow,visual,1,ncol2,cmapdata,
			cmapstr2,cmaptbl2);
	} else { /* can share colormap */
		i_retrieve_cmap(display,rootwindow,visual,0,ncol2,cmapdata,
			cmapstr1,cmaptbl2);
	}

	i_read(fd1,4,(char*)buf1);
	i_8_to_32(&buf1[0],&nbyte);
	imagestr1->imagedata = (unsigned char*) emalloc(nbyte);
	i_read(fd1,(int)nbyte,(char*)imagestr1->imagedata);
	i_retrieve_image(display,visual,cmaptbl1,nbyte,imagestr1,err);
	if (*err) return;
	i_read(fd2,4,(char*)buf2);
	i_8_to_32(&buf2[0],&nbyte);
	imagestr2->imagedata = (unsigned char*) emalloc(nbyte);
	i_read(fd2,(int)nbyte,(char*)imagestr2->imagedata);
	i_retrieve_image(display,visual,cmaptbl2,nbyte,imagestr2,err);
}


/*
 * i_retrieve_cmap(display,window,visual,iscreatecmap,ncol,cmapdata,cmapstr,cmaptbl)
 *  read cmap data from "cmapdata" buffer and create and store cmap
 *  if "iscreatecmap" is 0, do not create cmap but add color to the cmap
 *  from "cmapstr".
 */
static void
i_retrieve_cmap(display,window,visual,iscreatecmap,ncol,cmapdata,cmapstr,cmaptbl)
	Display *display;	/* X display */
	Window window;		/* X window */
	Visual *visual;		/* visual type */
	int iscreatecmap;	/* 1 if a new cmap is needed */
        Unsign16 ncol;    	/* number of colors */
        Unsign8 *cmapdata;	/* cmap data */
        I_cmap *cmapstr;        /* OUT colormap str */
        Unsign8 *cmaptbl; 	/* OUT color mapping table */
{
	int i;
	int extrapix=0;
	Unsign8 *cp;
	static unsigned long pixels[MAXCOLOR];
	static XColor cols[MAXCOLOR];
	static char rgb = DoRed | DoGreen | DoBlue;
	int bits_per_rgb;  	/* bits_per_rgb for display */

	/* given PSEUDOCOLOR visual */
	bits_per_rgb = i_get_bits_per_rgb(display);
	if (iscreatecmap) {
        	cmapstr->cmap = XCreateColormap(display,window,visual,
			AllocNone);
		if (ncol < MAXCOLOR) {
			extrapix = 1;		
			ncol++;  /* extra entry for background color */
		}
	}
	if (XAllocColorCells(display,cmapstr->cmap,False,(unsigned long*)NULL,
		0,pixels,(unsigned int)ncol)==0)
		fatal("ABORT: i_retrieve_cmap: XAllocColorCells failed\n");
	if (iscreatecmap) { /* initialize zero'th entry for background pixel */
		cmapstr->blackpixel = cols[0].pixel = pixels[0]; 
		if (extrapix) { 
			/* if there is space for extra background color */
			/* initialize it as black */
			cols[0].red=cols[0].green=cols[0].blue=0;
			cols[0].flags = rgb;
		}
	}
        for (cp=cmapdata,i=extrapix?1:0;i<ncol;++i,cp+=4) {
                cmaptbl[cp[0]] = pixels[i];
                cmapstr->ctbl[pixels[i]][0] = cp[1];
                cmapstr->ctbl[pixels[i]][1] = cp[2];
                cmapstr->ctbl[pixels[i]][2] = cp[3];
                cols[i].pixel = pixels[i];
                cols[i].flags = rgb;
                cols[i].red = i_scale_uchar_to_ushort(bits_per_rgb,cp[1]);
                cols[i].green = i_scale_uchar_to_ushort(bits_per_rgb,cp[2]);
                cols[i].blue = i_scale_uchar_to_ushort(bits_per_rgb,cp[3]);
	} 
	XStoreColors(display,cmapstr->cmap,cols,(int)ncol);
}

/*
 *  i_scale_uchar_to_ushort(bits_per_rgb,value)
 */
static unsigned short
i_scale_uchar_to_ushort(bits_per_rgb,value)
        int bits_per_rgb;
        Unsign8 value;
{
	switch (sizeof(unsigned short)) {
	case 1:
                return( (unsigned short) value );
	case 2:
		switch (bits_per_rgb) {
                case 8:
                case 16:
                	return( (unsigned short) (value << 8));
                default:
                        fatal("ABORT: i_scale_uchar_to_ushort: unknown bits_per_rgb %d\n",bits_per_rgb);
		}
        default:
                fatal("ABORT: i_scale_uchar_to_ushort: unknown size of unsigned short %d\n",sizeof(unsigned short));
        }
}
	

/*
 * i_retrieve_image(display,visual,cmaptbl,nbyte,imagestr,err)  read image data 
 * 	from file and create image
 */
static void
i_retrieve_image(display,visual,cmaptbl,nbyte,imagestr,err)
	Display *display;	/* X display */
	Visual *visual;		/* visual type */
	Unsign8 *cmaptbl;	/* color mapping table */
	Unsign32 nbyte;		/* length of image data */
	I_image *imagestr;	/* OUT image structure */
	int *err;		/* OUT error flag */
{
	int i,j;
	Unsign8 *ip,pixelcount;
	unsigned long pixel,bytecount;
	int pad;
	int defdepth;

	/* given PSEUDOCOLOR visual */
	defdepth = DefaultDepth(display,DefaultScreen(display));
	*err = 0;
	pad = 8;
	imagestr->image = XCreateImage(display,visual,defdepth,ZPixmap,0,
		(char*)NULL, (unsigned int)imagestr->width,
		(unsigned int)imagestr->height,pad,0);
	(imagestr->image)->data = emalloc((imagestr->image)->bytes_per_line * imagestr->height);
	i_convert_image(cmaptbl,nbyte,imagestr->imagedata);
	for (ip=imagestr->imagedata, pixelcount = 0, bytecount = 0, 
		j=0;j<imagestr->height;++j) {
		for (i=0;i<imagestr->width;++i) {
			if (pixelcount == 0) {
				if (++bytecount > nbyte) {
					printf("ERROR: i_retrieve_image: image data corrupted\n");
					*err = 1;
					return;
				}
				pixelcount = *ip++;
				pixel = (Unsign32) *ip++;
			}
			if (XPutPixel(imagestr->image,i,j,pixel) > 0)
				pixelcount--;
			else
				fatal("ABORT: i_retrieve_image: XPutPixel failed\n");
		}
	}
}

/*
 * i_convert_image(tbl,nbyte,imagedata) correct imagedata
 * image data read from image file uses pixel values which are not
 * the same as the pixel values allocated from i_retrieve_cmap. This
 * procedure maps the imagedata to the correct values.
 */
static void
i_convert_image(tbl,nbyte,imagedata)
        Unsign32 nbyte;    	/* number of bytes */
        Unsign8 *tbl;     	/* color mapping table */
        Unsign8 *imagedata;	/* image data */
{
        int i;
        Unsign8 *ip;

        for (ip = &imagedata[1],i=0;i<nbyte/2;i++,ip+=2) {
                *ip = tbl[(int)*ip];
        }
}


/*
 * i_diff_image(display,cstr1,cstr2;istr1,istr2,istr3,istr4,err)
 * generate output 2 images that captures the difference of 2 input images
 */
void
i_diff_image(display,cstr1,cstr2,istr1,istr2,istr3,istr4,err)
	Display *display;	/* X display */
	I_cmap *cstr1;		/* colormap structure */
	I_cmap *cstr2;		/* colormap structure */
	I_image *istr1;		/* image strucuture */
	I_image *istr2;		/* image strucuture */
	I_image *istr3;		/* OUT image strucuture */
	I_image *istr4;		/* OUT image strucuture */
	int *err;		/* OUT error flag */
{
	/*
	Show the difference of two images in the given windows
	*/
	int eqtbl[MAXCOLOR];
	int i,j;
	Unsign8 p1,p2,n1,n2;
	Unsign8 *ip1,*ip2;
	Unsign32 npixel;
	Unsign16 w,h;
	static GC gc = NULL;
	XGCValues gcvals;

	Pixmap pixmap1,pixmap2;
	Window rootwindow;
	unsigned int defdepth;

	/* given PSEUDOCOLOR visual */
	*err = 0;
	if (istr1->width != istr2->width ||
	    istr1->height != istr2->height ) {
		printf("ERROR: i_diff_image: image1's dim (%d,%d) != image2's (%d,%d)\n",
			istr1->width,istr1->height,istr2->width,istr2->height);
		*err = 1;
		return;
	} 
	w = istr1->width;
	h = istr1->height;
	for (i=0;i<MAXCOLOR;++i)
		eqtbl[i] = -1;
	istr3->width = istr4->width = w;
	istr3->height = istr4->height = h;
        rootwindow = DefaultRootWindow(display);
	defdepth = DefaultDepth(display,DefaultScreen(display));
	pixmap1 = XCreatePixmap(display,rootwindow,(unsigned int)w,
			(unsigned int)h,defdepth);
	pixmap2 = XCreatePixmap(display,rootwindow,(unsigned int)w,
			(unsigned int)h,defdepth);
	if (gc == NULL) {  /* hasn't been created yet */
	    gcvals.foreground = cstr1->blackpixel;
	    gc = XCreateGC(display,pixmap1, GCForeground, &gcvals);
	} else {
	    XSetForeground(display,gc,cstr1->blackpixel);
	}
	XFillRectangle(display,pixmap1,gc,0,0,(unsigned int)w,(unsigned int)h);
	XSetForeground(display,gc,cstr2->blackpixel);
	XFillRectangle(display,pixmap2,gc,0,0,(unsigned int)w,(unsigned int)h);
	istr3->image = XGetImage(display,pixmap1,0,0,(int)w,(int)h,-1,ZPixmap);
	istr4->image = XGetImage(display,pixmap2,0,0,(int)w,(int)h,-1,ZPixmap);
	if (! istr3->image || ! istr4->image)
                fatal("ABORT: i_diff_image: XGetImage failed\n");
	for (npixel=0,n1=0,n2=0,i=0,j=0,ip1=istr1->imagedata,
		ip2=istr2-> imagedata;
		npixel<w*h;npixel++,n1--,n2--) {
		if (n1==0) {
			n1 = *ip1++;
			p1 = *ip1++;
		}
		if (n2==0) {
			n2 = *ip2++;
			p2 = *ip2++;
		}
		if (eqtbl[p1] != (int)p2) { 
			if (cstr1->ctbl[p1][0] == cstr2->ctbl[p2][0] &&
			    cstr1->ctbl[p1][1] == cstr2->ctbl[p2][1] &&
			    cstr1->ctbl[p1][2] == cstr2->ctbl[p2][2]) {
				eqtbl[p1] = (int)p2;
			} else {
				if (XPutPixel(istr3->image,i,j,
					(unsigned long)p1) == 0)
			    		fatal("ABORT: i_diff_image: XPutPixel failed\n");
				if (XPutPixel(istr4->image,i,j,
					(unsigned long)p2) == 0)
			    		fatal("ABORT: i_diff_image: XPutPixel failed\n");
		    	}
		}
		if (++i == w) {
			i = 0;
			j++;
		}
	}
	XFreePixmap(display,pixmap1);
	XFreePixmap(display,pixmap2);
}

/*
 * i_display_image(display,window,imagestr) display an image on a window 
 */
void
i_display_image(display,window,imagestr)
	Display *display;	/* X display */
	Window window;		/* X window */
	I_image *imagestr;	/* image structure */
{
	/*
	 * To display an image on window
	 * given: window is created for pseudo color visual
	*/
	XPutImage(display,(Drawable)window,
		DefaultGC(display,DefaultScreen(display)),
		imagestr->image, 0,0,0,0,(unsigned int) imagestr->width,
		(unsigned int) imagestr->height);
}

/*
 * i_free_image(imagestr) free image resources
 */
void
i_free_image(imagestr)
	I_image *imagestr;	/* image structure */
{
	/*
	To free up image resources 
	*/
	XDestroyImage(imagestr->image);
	if (imagestr->imagedata) free(imagestr->imagedata);
}

/*
 * i_free_cmap(display,cmapstr) free cmap resources
 */
void
i_free_cmap(display,cmapstr)
	Display *display;	/* X display */
	I_cmap *cmapstr;	/* colormap structure */
{
	/*
	To free up colormap resources 
	*/
	XFreeColormap(display,cmapstr->cmap);
}

/*
 * i_get_bits_per_rgb(display)
 */
static int
i_get_bits_per_rgb(display)
        Display *display;       /* X display */
{
        int defdepth,defscreen;
        Visual *visual;
        int bits_per_rgb;

        defscreen = DefaultScreen(display);
        defdepth = DefaultDepth(display,defscreen);
        visual = DefaultVisual(display,defscreen);
        bits_per_rgb = visual->bits_per_rgb;
        if (bits_per_rgb != 8 && bits_per_rgb != 16)
                fatal("ABORT: i_get_bits_per_rgb: bits_per_rgb = %d, currently only support 8 or 16\n",bits_per_rgb);
        return(bits_per_rgb);
}

/*
 * fatal(fmt,va_alist)
 * prints out error message and abort program
 */
static void
fatal(fmt,va_alist)
        char *fmt;              /* message fmt */
        va_dcl                  /* variable data */
{
        va_list ap;

        va_start(ap);
        vprintf(fmt,ap);
        va_end(ap);
        exit(1);
}


/*
 * i_8_to_16(buf,n) convert 2 8-bit to 1 16-bit data
 */
static void
i_8_to_16(buf,n)
        Unsign8 *buf;     /* buffer */
        Unsign16 *n;
{
	/* add up low & high byte */
	*n = (Unsign16) buf[0] + (((Unsign16) buf[1]) << 8); 
}

/*
 * i_8_to_32(buf,n) convert 4 8-bit to 1 32-bit data
 */
static void
i_8_to_32(buf,n)
        Unsign8 *buf;     /* buffer */
        Unsign32 *n;
{
	/* add up all bytes */
	*n = (Unsign32) buf[0] + (((Unsign32) buf[1]) << 8) +
	     (((Unsign32) buf[2]) << 16) + (((Unsign32) buf[3]) << 24)
; 
}


/*
 * i_read(fd,n,buf)  read n bytes of data to buffer
 */
static void
i_read(fd,n,buf) 
	int fd;		/* file descritor */
	int n;		/* number of bytes */
	char *buf; 	/* OUT value */
{
	if (read(fd,buf,n)!= n)
               	fatal("ABORT: i_read: read failed\n");
}


/*
 * emalloc(size) allocate memory.
 */
static char *
emalloc(size)
        int size;
{
        char *p; 
 
        if (! (p=malloc(size)))
                fatal("ABORT: emalloc: malloc failed\n");
        return(p);
}
