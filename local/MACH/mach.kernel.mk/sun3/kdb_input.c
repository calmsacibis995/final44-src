/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	kdb_input.c,v $
 * Revision 2.4  89/03/09  21:35:56  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:43:23  gm0w
 * 	Added new copyright, fixed includes, and removed else leg
 * 	of CMU and MACH conditionals as part of kernel cleanup.
 * 	[89/02/10            jjc]
 * 
 * 29-Mar-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Change types.h to param.h so that the spl macro's are defined.
 *
 * 26-Oct-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Added initial key mappings for Sun 3 keyboard (from Sun's
 *	keytables.c) so kdb can reset the key mappings on entry
 *	just in case some user program like X has changed the mappings.
 *	Reset the key  mappings in kdb_grab_console().
 *	Restore old key mappings in kdb_release_console().
 *
 * 11-Sep-86  David Golub (dbg) at Carnegie-Mellon University
 *	Hacked up for SUN3 because we can't figure out how to get
 *	characters from the PROM.
 */

#include <sys/param.h>
#include <sys/conf.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
#include <sun/consdev.h>
#include <sundev/kbd.h>
#include <sundev/kbio.h>

/* handy way to define control characters in the tables */
#define C(char)	(char&0x1F)
#define ESC 0x1B


/* Unshifted keyboard table for Sun-3 keyboard */

static struct keymap kdb_keytab_s3_lc = {
/*  0 */	HOLE,	BUCKYBITS+SYSTEMBIT,
				HOLE,	LF(2),	HOLE,	TF(1),	TF(2),	HOLE,
/*  8 */	TF(3), 	HOLE,	TF(4),	HOLE,	TF(5),	HOLE,	TF(6),	HOLE,
/* 16 */	TF(7),	TF(8),	TF(9),	ALT,	HOLE,	RF(1),	RF(2),	RF(3),
/* 24 */	HOLE, 	LF(3), 	LF(4),	HOLE,	HOLE,	C('['),	'1',	'2',
/* 32 */	'3',	'4',	'5',	'6',	'7',	'8',	'9',	'0',
/* 40 */	'-',	'=',	'`',	'\b',	HOLE,	RF(4),	RF(5),	RF(6),
/* 48 */	HOLE,	LF(5),	HOLE,	LF(6),	HOLE,	'\t',	'q',	'w',
/* 56 */	'e',	'r',	't',	'y',	'u',	'i',	'o',	'p',
/* 64 */	'[',	']',	0x7F,	HOLE,	RF(7),	STRING+UPARROW,
								RF(9),	HOLE,
/* 72 */	LF(7),	LF(8),	LF(14),	HOLE,	SHIFTKEYS+LEFTCTRL,
							'a', 	's',	'd',
/* 80 */	'f',	'g',	'h',	'j',	'k',	'l',	';',	'\'',
/* 88 */	'\\',	'\r',	HOLE,	STRING+LEFTARROW,
						RF(11),	STRING+RIGHTARROW,
								HOLE,	LF(9),
/* 96 */	LF(15),	LF(10),	HOLE,	SHIFTKEYS+LEFTSHIFT,
						'z',	'x',	'c',	'v',
/*104 */	'b',	'n',	'm',	',',	'.',	'/',	SHIFTKEYS+RIGHTSHIFT,
									'\n',
/*112 */	RF(13),	STRING+DOWNARROW,
				RF(15),	HOLE,	HOLE,	HOLE,	HOLE,	SHIFTKEYS+CAPSLOCK,
/*120 */	BUCKYBITS+METABIT,
			' ',	BUCKYBITS+METABIT,
					HOLE,	HOLE,	HOLE,	ERROR,	IDLE,
};

/* Shifted keyboard table for Sun-3 keyboard */

static struct keymap kdb_keytab_s3_uc = {
/*  0 */	HOLE,	BUCKYBITS+SYSTEMBIT,
				HOLE,	LF(2),	HOLE,	TF(1),	TF(2),	HOLE,
/*  8 */	TF(3), 	HOLE,	TF(4),	HOLE,	TF(5),	HOLE,	TF(6),	HOLE,
/* 16 */	TF(7),	TF(8),	TF(9),	ALT,	HOLE,	RF(1),	RF(2),	RF(3),
/* 24 */	HOLE, 	LF(3), 	LF(4),	HOLE,	HOLE,	C('['),	'!',    '@',
/* 32 */	'#',	'$',	'%',	'^',	'&',	'*',	'(',	')',
/* 40 */	'_',	'+',	'~',	'\b',	HOLE,	RF(4),	RF(5),	RF(6),
/* 48 */	HOLE,	LF(5),	HOLE,	LF(6),	HOLE,	'\t',	'Q',	'W',
/* 56 */	'E',	'R',	'T',	'Y',	'U',	'I',	'O',	'P',
/* 64 */	'{',	'}',	0x7F,	HOLE,	RF(7),	STRING+UPARROW,
								RF(9),	HOLE,
/* 72 */	LF(7),	LF(8),	HOLE,	HOLE,	SHIFTKEYS+LEFTCTRL,
							'A', 	'S',	'D',
/* 80 */	'F',	'G',	'H',	'J',	'K',	'L',	':',	'"',
/* 88 */	'|',	'\r',	HOLE,	STRING+LEFTARROW,
						RF(11),	STRING+RIGHTARROW,
								HOLE,	LF(9),
/* 96 */	LF(15),	LF(10),	HOLE,	SHIFTKEYS+LEFTSHIFT,
						'Z',	'X',	'C',	'V',
/*104 */	'B',	'N',	'M',	'<',	'>',	'?',	SHIFTKEYS+RIGHTSHIFT,
									'\n',
/*112 */	RF(13),	STRING+DOWNARROW,
				RF(15),	HOLE,	HOLE,	HOLE,	HOLE,	SHIFTKEYS+CAPSLOCK,
/*120 */	BUCKYBITS+METABIT,
			' ',	BUCKYBITS+METABIT,
					HOLE,	HOLE,	HOLE,	ERROR,	IDLE,
};


/* Caps Locked keyboard table for Sun-3 keyboard */

static struct keymap kdb_keytab_s3_cl = {
/*  0 */	HOLE,	BUCKYBITS+SYSTEMBIT,
				HOLE,	LF(2),	HOLE,	TF(1),	TF(2),	HOLE,
/*  8 */	TF(3), 	HOLE,	TF(4),	HOLE,	TF(5),	HOLE,	TF(6),	HOLE,
/* 16 */	TF(7),	TF(8),	TF(9),	ALT,	HOLE,	RF(1),	RF(2),	RF(3),
/* 24 */	HOLE, 	LF(3), 	LF(4),	HOLE,	HOLE,	C('['),	'1',	'2',
/* 32 */	'3',	'4',	'5',	'6',	'7',	'8',	'9',	'0',
/* 40 */	'-',	'=',	'`',	'\b',	HOLE,	RF(4),	RF(5),	RF(6),
/* 48 */	HOLE,	LF(5),	HOLE,	LF(6),	HOLE,	'\t',	'Q',	'W',
/* 56 */	'E',	'R',	'T',	'Y',	'U',	'I',	'O',	'P',
/* 64 */	'[',	']',	0x7F,	HOLE,	RF(7),	STRING+UPARROW,
								RF(9),	HOLE,
/* 72 */	LF(7),	LF(8),	HOLE,	HOLE,	SHIFTKEYS+LEFTCTRL,
							'A', 	'S',	'D',
/* 80 */	'F',	'G',	'H',	'J',	'K',	'L',	';',	'\'',
/* 88 */	'\\',	'\r',	HOLE,	STRING+LEFTARROW,
						RF(11),	STRING+RIGHTARROW,
								HOLE,	LF(9),
/* 96 */	LF(15),	LF(10),	HOLE,	SHIFTKEYS+LEFTSHIFT,
						'Z',	'X',	'C',	'V',
/*104 */	'B',	'N',	'M',	',',	'.',	'/',	SHIFTKEYS+RIGHTSHIFT,
									'\n',
/*112 */	RF(13),	STRING+DOWNARROW,
				RF(15),	HOLE,	HOLE,	HOLE,	HOLE,	SHIFTKEYS+CAPSLOCK,
/*120 */	BUCKYBITS+METABIT,
			' ',	BUCKYBITS+METABIT,
					HOLE,	HOLE,	HOLE,	ERROR,	IDLE,
};

/* Controlled keyboard table for Sun-3 keyboard */

static struct keymap kdb_keytab_s3_ct = {
/*  0 */	HOLE,	BUCKYBITS+SYSTEMBIT,
				HOLE,	LF(2),	HOLE,	TF(1),	TF(2),	HOLE,
/*  8 */	TF(3), 	HOLE,	TF(4),	HOLE,	TF(5),	HOLE,	TF(6),	HOLE,
/* 16 */	TF(7),	TF(8),	TF(9),	ALT,	HOLE,	RF(1),	RF(2),	RF(3),
/* 24 */	HOLE, 	LF(3), 	LF(4),	HOLE,	HOLE,	C('['),	'1',	C('@'),
/* 32 */	'3',	'4',	'5',	C('^'),	'7',	'8',	'9',	'0',
/* 40 */	C('_'),	'=',	C('^'),	'\b',	HOLE,	RF(4),	RF(5),	RF(6),
/* 48 */	HOLE,	LF(5),	HOLE,	LF(6),	HOLE,	'\t',   C('q'),	C('w'),
/* 56 */	C('e'),	C('r'),	C('t'),	C('y'),	C('u'),	C('i'),	C('o'),	C('p'),
/* 64 */	C('['),	C(']'),	0x7F,	HOLE,	RF(7),	STRING+UPARROW,
								RF(9),	HOLE,
/* 72 */	LF(7),	LF(8),	HOLE,	HOLE,	SHIFTKEYS+LEFTCTRL,
							C('a'),	C('s'),	C('d'),
/* 80 */	C('f'),	C('g'),	C('h'),	C('j'),	C('k'),	C('l'),	';',	'\'',
/* 88 */	C('\\'),
			'\r',	HOLE,	STRING+LEFTARROW,
						RF(11),	STRING+RIGHTARROW,
								HOLE,	LF(9),
/* 96 */	LF(15),	LF(10),	HOLE,	SHIFTKEYS+LEFTSHIFT,
						C('z'),	C('x'),	C('c'),	C('v'),
/*104 */	C('b'),	C('n'),	C('m'),	',',	'.',	C('_'),	SHIFTKEYS+RIGHTSHIFT,
									'\n',
/*112 */	RF(13),	STRING+DOWNARROW,
				RF(15),	HOLE,	HOLE,	HOLE,	HOLE,	SHIFTKEYS+CAPSLOCK,
/*120 */	BUCKYBITS+METABIT,
			C(' '),	BUCKYBITS+METABIT,
					HOLE,	HOLE,	HOLE,	ERROR,	IDLE,
};



/* "Key Up" keyboard table for Sun-3 keyboard */

static struct keymap kdb_keytab_s3_up = {
/*  0 */	HOLE,	BUCKYBITS+SYSTEMBIT,
				HOLE,	OOPS,	HOLE,	OOPS,	OOPS,	HOLE,
/*  8 */	OOPS, 	HOLE, 	OOPS,	HOLE,	OOPS,	HOLE,	OOPS,	HOLE,
/* 16 */	OOPS, 	OOPS, 	OOPS,	OOPS,	HOLE,	OOPS,	OOPS,	NOP,
/* 24 */	HOLE, 	OOPS, 	OOPS,	HOLE,	HOLE,	NOP,	NOP,	NOP,
/* 32 */	NOP,	NOP,	NOP,	NOP,	NOP,	NOP,	NOP,	NOP,
/* 40 */	NOP,	NOP,	NOP,	NOP,	HOLE,	OOPS,	OOPS,	NOP,
/* 48 */	HOLE,	OOPS,	HOLE,	OOPS,	HOLE,	NOP,	NOP,	NOP,
/* 56 */	NOP,	NOP,	NOP,	NOP,	NOP,	NOP,	NOP,	NOP,
/* 64 */	NOP,	NOP,	NOP,	HOLE,	OOPS,	OOPS,	NOP,	HOLE,
/* 72 */	OOPS,	OOPS,	HOLE,	HOLE,	SHIFTKEYS+LEFTCTRL,
							NOP, 	NOP,	NOP,
/* 80 */	NOP,	NOP,	NOP,	NOP,	NOP,	NOP,	NOP,	NOP,
/* 88 */	NOP,	NOP,	HOLE,	OOPS,	OOPS,	NOP,	HOLE,	OOPS,
/* 96 */	OOPS,	OOPS,	HOLE,	SHIFTKEYS+LEFTSHIFT,
						NOP,	NOP,	NOP,	NOP,
/*104 */	NOP,	NOP,	NOP,	NOP,	NOP,	NOP,	SHIFTKEYS+RIGHTSHIFT,
									NOP,
/*112 */	OOPS,	OOPS,	NOP,	HOLE,	HOLE,	HOLE,	HOLE,	NOP,
/*120 */	BUCKYBITS+METABIT,
			NOP,	BUCKYBITS+METABIT,
					HOLE,	HOLE,	HOLE,	HOLE,	RESET,
};

/* Index to keymaps for Sun-3 keyboard */
static struct keyboard kdb_keyindex_s3 = {
	&kdb_keytab_s3_lc,
	&kdb_keytab_s3_uc,
	&kdb_keytab_s3_cl,
	&kdb_keytab_s3_ct,
	&kdb_keytab_s3_up,
	0x0000,		/* Shift bits which stay on with idle keyboard */
	0x0000,		/* Bucky bits which stay on with idle keyboard */
	1,	77,	/* abort keys */
	CAPSMASK,	/* Shift bits which toggle on down event */
};
#undef	c


struct tty	*kdb_tp = (struct tty *)0;	/* console tty structure */
int		kdb_save_nblock;
int		kdb_old_trans;
int		(*kdb_save_usecode)();
struct keyboard	*oldkb;		/* ptr to old keyboard structure */
extern struct keyboard	*keytables[];

/*
 *	buffer for keyboard input
 */
#define KDBRINGSIZE	80
char		kdb_charbuf[KDBRINGSIZE];
int		kdb_readptr,	/* next character */
		kdb_writeptr;	/* next free spot */

/*
 *	Grab console for input
 */
kdb_grab_console()
{

	int	data;
	int	error;

	int	kbdusekdb();	/* forward decl. */

	/*
	 *	Get tty structure for console
	 */
	kdb_tp = cdevsw[major(kbddev)].d_ttys + minor(kbddev);

	/*
	 *	Save whether non-blocking, then set
	 */
	kdb_save_nblock = kdb_tp->t_state & TS_NBIO;
	kdb_tp->t_state |= TS_NBIO;

	/*
	 *	Flush characters, save old key mappings,
	 *	and then reset key mappings
	 */
	data = 0;
	error = kbdioctl(kdb_tp, TIOCFLUSH, &data, 0);

	oldkb = keytables[KB_SUN3];
	keytables[KB_SUN3] = &kdb_keyindex_s3;

	/*
	 *	Set translation to ASCII
	 */
	error = kbdioctl(kdb_tp, KIOCGTRANS, (int *)&kdb_old_trans, 0);

	data = TR_ASCII;
	error = kbdioctl(kdb_tp, KIOCTRANS, &data, 0);

	/*
	 *	Grab characters before they get to the console
	 *	'tty'
	 */
	kbdioctl(kdb_tp, KIOCGUSECODE, (caddr_t)&kdb_save_usecode, 0);
	kbdioctl(kdb_tp, KIOCSUSECODE, kbdusekdb, 0);

	/*
	 *	Initialize circular buffer
	 */
	kdb_readptr = kdb_writeptr = 0;
}

/*
 *	Release console
 */
kdb_release_console()
{

	int	data;
	int	error;

	/*
	 *	Get tty structure for console
	 */
	if (kdb_tp == (struct tty *)0)
		panic("kdb_release_console: don't have console");

	/*
	 *	Flush characters
	 */
	data = 0;
	error = kbdioctl(kdb_tp, TIOCFLUSH, &data, 0);

	/*
	 *	Restore whether non-blocking
	 */
	kdb_tp->t_state |= kdb_save_nblock;

	/*
	 *	Restore old translation and old key mappings
	 */
	error = kbdioctl(kdb_tp, KIOCTRANS, (caddr_t)&kdb_old_trans, 0);
	keytables[KB_SUN3] = oldkb;
	/*
	 *	And give characters to whoever was listening
	 */
	error = kbdioctl(kdb_tp, KIOCSUSECODE, (caddr_t)kdb_save_usecode, 0);

}


/*
 *	Call keyboard translate routine
 */
kbdusekdb(tp, keycode, k)
	struct tty	*tp;
	u_char		keycode;
	struct keyboardstate	*k;
{
	int	kdb_rint();

	kbdtranslate(tp, keycode, kdb_rint);
}

/*
 *	Receive character from keyboard
 *
 */
kdb_rint(c, tp)
	char	c;
	struct tty *tp;
{
	kdb_charbuf[kdb_writeptr++] = c;
	if (kdb_writeptr >= KDBRINGSIZE)
		kdb_writeptr = 0;
	if (kdb_writeptr == kdb_readptr) {
		/*
		 *	overflow
		 */
		if (--kdb_writeptr < 0)
			kdb_writeptr = KDBRINGSIZE - 1;
	}
}

char kdb_readchar()
{
	int	spl;
	char	c;

	/*
	 *	Drop interrupt priority to 0 to let
	 *	keyboard interrupts in.
	 */
	spl = spl0();
	for (;;) {
		/*
		 *	But test the circular buffer at
		 *	level 5 (spltty?)
		 */
		(void) spl5();
		if (kdb_readptr != kdb_writeptr) {
			c = kdb_charbuf[kdb_readptr];
			kdb_readptr++;
			if (kdb_readptr >= KDBRINGSIZE)
				kdb_readptr = 0;
			splx(spl);
			return(c);
		}
		(void) spl0();
		/* spin */
	}
}
