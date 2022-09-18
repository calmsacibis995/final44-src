h43847
s 00002/00002/00140
d D 8.1 93/06/10 22:38:31 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00015/00000/00127
d D 7.3 93/04/05 21:35:30 ralph 3 2
c use vm_mmap instead of X kluge to map display into user address space.
e
s 00001/00000/00126
d D 7.2 93/03/23 18:49:55 ralph 2 1
c changes from Rick Macklem
e
s 00126/00000/00000
d D 7.1 92/11/15 15:47:47 ralph 1 0
c date and time created 92/11/15 15:47:47 by ralph
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * Ralph Campbell and Rick Macklem.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Data for fb.c generic frame buffer routines that are called by the
 * various frame buffer drivers.
 */
struct fbuaccess {
	PM_Info		scrInfo;
	pmEvent		events[PM_MAXEVQ];	
	pmTimeCoord	tcs[MOTION_BUFFER_SIZE];
};

struct pmax_fb {
	int	GraphicsOpen;		/* Open yet? */
	int	initialized;		/* Set up yet? */
	int	isMono;			/* Monochrome fb? */
	int	row, col;		/* Screen pos for glass tty */
	struct	fbuaccess *fbu;		/* X event stuff */
	char	*fr_addr;		/* Frame buffer address */
I 3
	size_t	fr_size;		/* Frame buffer size */
E 3
I 2
	char	*fr_chipaddr;		/* Base address for chips */
E 2
	void	(*posCursor)();		/* Position cursor func */
	void	(*KBDPutc)();		/* Send char to keyboard func */
	dev_t	kbddev;			/* Device for KBDPutc */
	struct	selinfo selp;		/* Select structure */
};

/*
 * Definitions for the Keyboard and mouse.
 */
/*
 * Special key values.
 */
#define	KEY_R_SHIFT	0xab
#define KEY_SHIFT	0xae
#define KEY_CONTROL	0xaf
#define	KEY_R_ALT	0xb2
#define KEY_UP		0xb3
#define KEY_REPEAT	0xb4
#define KEY_F1		0x56
#define KEY_COMMAND	KEY_F1

/*
 * Lk201/301 keyboard
 */
#define LK_UPDOWN	0x86		/* bits for setting lk201 modes */
#define LK_AUTODOWN	0x82
#define LK_DOWN		0x80
#define LK_DEFAULTS	0xd3		/* reset mode settings          */
#define LK_AR_ENABLE	0xe3		/* global auto repeat enable	*/
#define LK_CL_ENABLE	0x1b		/* keyclick enable		*/
#define LK_KBD_ENABLE	0x8b		/* keyboard enable		*/
#define LK_BELL_ENABLE	0x23		/* the bell			*/
#define LK_LED_ENABLE	0x13		/* light led			*/
#define LK_LED_DISABLE	0x11		/* turn off led			*/
#define LK_RING_BELL	0xa7		/* ring keyboard bell		*/
#define LED_1		0x81		/* led bits			*/
#define LED_2		0x82
#define LED_3		0x84
#define LED_4		0x88
#define LED_ALL		0x8f
#define LK_HELP		0x7c		/* help key			*/
#define LK_DO		0x7d		/* do key			*/
#define LK_KDOWN_ERROR	0x3d		/* key down on powerup error	*/
#define LK_POWER_ERROR	0x3e		/* keyboard failure on pwrup tst*/
#define LK_OUTPUT_ERROR 0xb5		/* keystrokes lost during inhbt */
#define LK_INPUT_ERROR	0xb6		/* garbage command to keyboard	*/
#define LK_LOWEST	0x56		/* lowest significant keycode	*/

/* max volume is 0, lowest is 0x7 */
#define	LK_PARAM_VOLUME(v)		(0x80|((v)&0x7))

/* mode command details */
#define	LK_CMD_MODE(m,div)		((m)|((div)<<3))

/*
 * Command characters for the mouse.
 */
#define MOUSE_SELF_TEST		'T'
#define MOUSE_INCREMENTAL	'R'

/*
 * Mouse output bits.
 *
 *     	MOUSE_START_FRAME	Start of report frame bit.
 *	MOUSE_X_SIGN		Sign bit for X.
 *	MOUSE_Y_SIGN		Sign bit for Y.
 *	MOUSE_X_OFFSET		X offset to start cursor at.
 *	MOUSE_Y_OFFSET		Y offset to start cursor at.
 */
#define MOUSE_START_FRAME	0x80
#define MOUSE_X_SIGN		0x10
#define MOUSE_Y_SIGN		0x08

/*
 * Definitions for mouse buttons
 */
#define EVENT_LEFT_BUTTON	0x01
#define EVENT_MIDDLE_BUTTON	0x02
#define EVENT_RIGHT_BUTTON	0x03
#define RIGHT_BUTTON		0x01
#define MIDDLE_BUTTON		0x02
#define LEFT_BUTTON		0x04

/*
 * Mouse report structure definition
 */
typedef struct {
	char state;			/* buttons and sign bits	*/
	short dx;			/* delta X since last change	*/
	short dy;			/* delta Y since last change	*/
	char byteCount;			/* mouse report byte count	*/
} MouseReport;

/*
 * Macro to translate from a time struct to milliseconds.
 */
#define TO_MS(tv) ((tv.tv_sec * 1000) + (tv.tv_usec / 1000))
I 3

extern void fbKbdEvent __P((int, struct pmax_fb *));
extern void fbMouseEvent __P((MouseReport *, struct pmax_fb *));
extern void fbMouseButtons __P((MouseReport *, struct pmax_fb *));
extern void fbScroll __P((struct pmax_fb *));
extern void fbPutc __P((dev_t, int));
extern void fbBlitc __P((int, struct pmax_fb *));
extern void fbBlitc __P((int, struct pmax_fb *));
extern int kbdMapChar __P((int));
extern void KBDReset __P((dev_t, void (*)(dev_t, int)));
extern void MouseInit __P((dev_t, void (*)(dev_t, int), int (*)(dev_t)));
extern int KBDGetc __P((void));
extern int tb_kbdmouseconfig __P((struct pmax_fb *));
extern int fbmmap __P((struct pmax_fb *, dev_t, caddr_t, struct proc *));
E 3
E 1
