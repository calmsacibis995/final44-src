
#define ROOT_QUIT	 (caddr_t)1
#define ROOT_KILL	 (caddr_t)2
#define ROOT_TTY	 (caddr_t)3
#define ROOT_CRT	 (caddr_t)4
#define ROOT_REFRESH	 (caddr_t)5


/* #define DEBUGABLE		/* Debugable?.. */
#define	NFONTS	60		/* total number of fonts useable */
#define	MAXSTATE 6		/* number of environments rememberable */
#define OPENREAD 0		/* mode for openning files */
#define RESTART	1		/* upon exit, return either RESTART */
#define ABORT	2		/*     or ABORT */
#define	FATAL	1		/* type of error */
#define	BMASK	0377		/* byte grabber */
#define DEVNAME	10		/* maximum characters in devicename */
#define FONTDIR	"/usr/lib/font"	/* default place to find font descriptions */
#define BITDIR "/usr/lib/font"	/* default place to look for font rasters */

#define  hmot(n)	h_pos += n
#define  hgoto(n)	h_pos = n
#define  vmot(n)	v_pos += n
#define  vgoto(n)	v_pos = n

#define  CLEAR_PR(clr_pr, basex, basey) pr_rop(clr_pr, basex, basey,\
					RASTER_LENGTH - basex, NLINES - basey,\
				        PIX_SRC^PIX_DST, clr_pr, basex, basey)
