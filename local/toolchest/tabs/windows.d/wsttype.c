/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
#include <stdio.h>
#include "vt.h"
#include "windows.h"

/*
 *	This is the windowed version of sttype from the vt.d directory.
 *	The only difference between the two files is the _create_map()
 *	at the end of the file.  It creates window specific data.
 *
 *	wsttype (terminal_name)
 *
 *	Please pardon the mess that follows.  This is the main place
 *	where virtual terminal database dependencies raise their
 *	ugly heads.  What follows is three separate copies of sttype().
 *	The first one is for termcap, the second is for Warren's EMACS,
 *	and the third is for terminfo.  Warren setup the general scheme
 *	here and it seems to work quite well.
 *
 */

#ifdef VT_TERMINFO

#undef TRUE
#undef FALSE

#include <curses.h>
#include <term.h>

#else

#include <sys/jioctl.h>		/* CDB for Blit stuff */

#ifndef TERMCAP

char   *termdir = SDIR/terminals/%s";

#endif TERMCAP

#endif VT_TERMINFO

#ifndef VT_TERMINFO


/*
 *		BEGIN TERMCAP VERSION
 *
 */

#ifdef TERMCAP


extern char    PC;
extern char   *BC;
char   *TE;

wsttype (mp)
register char  *mp;
{
	char    tbuf[1024];
	static char     bufspace[512];
	char   *xp;
	char   *pt = bufspace;
	char   *tgetstr ();
	register int	i;

	if (tgetent (tbuf, mp) < 1)
	{
		return (0);
	}
	UP = tgetstr ("up", &pt);
	DOWN = tgetstr ("do", &pt);
	if (DOWN == NULL)
		DOWN = "\n";
	BACK = tgetstr ("bc", &pt);
	if (BACK == NULL && tgetflag ("bs"))
		BACK = "\b";
	BC = BACK;
	FORWARD = tgetstr ("nd", &pt);
	CLEAR = tgetstr ("cl", &pt);
	CLINE = tgetstr ("ce", &pt);
	BELL = "\7";
	CURAD = tgetstr ("cm", &pt);
	NOP = tgetstr ("pc", &pt);	PC = *NOP;
	LOPEN = tgetstr ("al", &pt);
	CLOPEN = tgetstr ("AL", &pt);
	LDEL = tgetstr ("dl", &pt);
	CLDEL = tgetstr ("DL", &pt);
	INSERTC = tgetstr ("ic", &pt);
	INSERTM = tgetstr ("im", &pt);
	OSERTC = tgetstr ("ei", &pt);
	INSERTP = tgetstr ("ip", &pt);
	IN = tgetflag ("in", &pt);
	DELMODE = (int) tgetstr ("dm", &pt);	/* Note that DM is a flag in emacs */
	DELC = tgetstr ("dc", &pt);	RSCROLL = tgetstr ("sr", &pt);
	SSCROLL = tgetstr ("nl", &pt);
	if (SSCROLL == NULL)
		SSCROLL = tgetstr ("sf", &pt);
	if ((SSCROLL == NULL) && (tgetflag ("xn") == NULL))
		SSCROLL = "\n";
	SCREG = tgetstr ("cs", &pt);

	NESTANDOUT = tgetflag ("xs");

/* UNDERLINING */
	if (tgetflag ("ul"))
	{
		ULINE = "%c_";		/* underline this way */
		EOVER = tgetflag ("eo");
		TUNDER = 1;
	}
	else
		if (xp = tgetstr ("uc", &pt))
		{
		/* underscore by magic word */
			ULINE = pt;
			pt = cpy_ret (pt, "%c");
			pt = cpy_ret (pt, xp);
			EOVER = (tgetflag ("xs") == 0);
			pt++;
		}
		else
			if (xp = tgetstr ("us", &pt))
			{		/* underscore mode */
				ULINE = xp;
				UEND = tgetstr ("ue", &pt);
				EOVER = (tgetflag ("xs") == 0);
			}
	CR = tgetstr ("cr", &pt);
	if (CR == NULL)
	{
		if (tgetflag ("nc") == 0)
			CR = "\r";
	}
	SCINIT = tgetstr ("ti", &pt);
	VEXIT = tgetstr ("te", &pt);

	_Key( K_HOME ) = tgetstr ("kh", &pt);
	_Key( K_UP ) = tgetstr ("ku", &pt);
	_Key( K_DOWN ) = tgetstr ("kd", &pt);
	_Key( K_RIGHT ) = tgetstr ("kr", &pt);
	_Key( K_LEFT ) = tgetstr ("kl", &pt);
	_Key( K_F0 ) = tgetstr ("k0", &pt);
	_Key( K_F1 ) = tgetstr ("k1", &pt);
	_Key( K_F2 ) = tgetstr ("k2", &pt);
	_Key( K_F3 ) = tgetstr ("k3", &pt);
	_Key( K_F4 ) = tgetstr ("k4", &pt);
	_Key( K_F5 ) = tgetstr ("k5", &pt);
	_Key( K_F6 ) = tgetstr ("k6", &pt);
	_Key( K_F7 ) = tgetstr ("k7", &pt);
	_Key( K_F8 ) = tgetstr ("k8", &pt);
	_Key( K_F9 ) = tgetstr ("k9", &pt);
	_Key( K_FA ) = tgetstr ("k;", &pt);
	for( i = K_BOTTOM; i < K_HOME + _NKEYS; i++ )
		_Key( i ) = 0;

	get_leadin();

	TE = tgetstr ("up", &pt);
	MI = tgetnum ("mi", &pt);
	SCRWID = tgetnum ("co") - 1;
	SCRNLIN = tgetnum ("li");

#ifdef JWINSIZE

	/*
	 * Courtesy of Mark Horton
	 *
	 * ioctls for Blit - you may need to #include <jioctl.h>
	 * This ioctl defines the window size and overrides what
	 * it says in terminfo.
	 */
	{
		struct jwinsize w;

		if (ioctl(2, JWINSIZE, &w) != -1) {
			SCRNLIN = w.bytesy;
			SCRWID = w.bytesx - 1;
		}
	}
	if (getenv ("LINES"))
		nscan (getenv ("LINES"), &SCRNLIN);
	if (getenv ("COLUMNS"))
	{
		nscan (getenv ("COLUMNS"), &SCRWID);
		SCRWID--;
	}

#endif

	SCRWRAP = tgetflag ("am");
	if (SCRNLIN > NSCRLIN)
	{
		SCRNLIN = NSCRLIN;
	}
	if (SCRWID > NSCRCOL - 1)
	{
		SCRWID = NSCRCOL - 1;
	}
	if (VCOST == 0)
		VCOST = 1;

	if (CURAD) {
		acost = dcost(CURAD);
	} else {
		acost = dcost(RELUP)+dcost(RELFORW);
	}
	lUP = dcost (UP);
	lDOWN = dcost (DOWN);
	lBAK = dcost (BACK);
	if (FORWARD)
		lFORWARD = dcost (FORWARD);
	else
		lFORWARD = 1;
	lCR = dcost (CR);
	if (SCREG)
		LOPEN = SCREG;		/* make sure we use SCREG */
	if ((NOP == NULL) || (*NOP == 0))
		NOP = "\200";		/* null pads get lost */

	_create_map ();

}

/* Like putchar but a function which can be passed to putpad */
pchar (c)
{
	putchar (c);
}

/* 
 * Print out string str with padding.
 */

putpad (str)
char   *str;
{
	if (str)
		tputs (str, SREGION, pchar);
}

#else

/*
 *		BEGIN EMACS VERSION
 *
 */

int     ttyptr = 0;

/* terminal description file parser:
 *
 * terminal description file contains lines with 
 *
 *	parameter=data
 *
 * where data is either a number of a string
 */

ttyparse (mp)
char   *mp;
{
	register        FILE * file;
	char    xbuf[128];
#define OPTSIZE 256
	char optbuf[OPTSIZE];
	register char  *cp;
	register int    c;
	struct sparm   *parmp;
	int     parm;

 /* find the terminal file and open it */

	seprintf (xbuf, termdir, mp);	/* terminal file */

	file = fopen (xbuf, "r");

	if (file == NULL) file = fopen(mp,"r");
	
	if (file == NULL)
	{
badterm:
		eprintf ("Can't find terminal type %s\n", mp);
		cook ();
		exit (1);
	}

 /* first find what option we are setting */

nextparm: 
	cp = optbuf;
	while ((c = getc (file)) != '=')
	{
		if (c == '\n')
			goto nextparm;	/* comment line */
		if (c == EOF)
		{
			fclose (file);
			return (1);	/* abort during option scan */
		}
		if (cp-optbuf >= OPTSIZE) goto badterm; /* OOPS! */
		*cp++ = c;
	}
	*cp = 0;

 /* look up parameter in parameter table */

	for (parmp = ttydata; parmp -> t_pname; parmp++)
	{
		if ((optbuf[0] == parmp -> t_pname[0]) &&
		    (optbuf[1] == parmp -> t_pname[1]))
		{

			c = getc (file);
			if ((c >= '0') && (c <= '9'))
			{
				parm = 0;
				while ((c >= '0') && (c <= '9'))
				{
					parm = 10 * parm + (c - '0');
					c = getc (file);
				}
				*(parmp -> t_padd) = parm;
				if (c != EOF)
					goto nextparm;
				fclose (file);
				return (1);
			}
			*(parmp -> t_padd) = ((int) & ttystrings[ttyptr]);

			while ((c != EOF) && (c != EOL))
			{
				if (c == '\\')
				{
					c = getc (file);
					if (c == 'n')
						c = '\n';
				}

				ttystrings[ttyptr++] = c;
				c = getc (file);
			}
			ttystrings[ttyptr++] = 0;
			if (c != EOF)
				goto nextparm;
		}
	}
	goto nextparm;
}

wsttype (mp)
register char  *mp;
{
	register struct sparm  *parmp;

 /* First, initialize the tty data */

	ttyptr = 0;
	for (parmp = ttydata; parmp -> t_pname; parmp++)
	{
		*(parmp -> t_padd) = 0;
	}
	SCRWID = 80;			/* so we won't bomb */

	if (ttyparse (mp))
	{

		SCRWID--;

#ifdef JWINSIZE

	/*
	 * Courtesy of Mark Horton
	 *
	 * ioctls for Blit - you may need to #include <jioctl.h>
	 * This ioctl defines the window size and overrides what
	 * it says in terminfo.
	 */
	{
		struct jwinsize w;

		if (ioctl(2, JWINSIZE, &w) != -1) {
			SCRNLIN = w.bytesy;
			SCRWID = w.bytesx - 1;
		}
	}
	if (getenv ("LINES"))
		nscan (getenv ("LINES"), &SCRNLIN);
	if (getenv ("COLUMNS"))
	{
		nscan (getenv ("COLUMNS"), &SCRWID);
		SCRWID--;
	}

#endif

		if (SCRNLIN > NSCRLIN)
		{
			SCRNLIN = NSCRLIN;
		}
		if (SCRWID > NSCRCOL - 1)
		{
			SCRWID = NSCRCOL - 1;
		}
		if (VCOST == 0)
			VCOST = 1;

		acost = dcost (CURAD);
		lUP = dcost (UP);
		lDOWN = dcost (DOWN);
		lBAK = dcost (BACK);
		if (FORWARD)
			lFORWARD = dcost (FORWARD);
		else
			lFORWARD = 1;
		lCR = dcost (CR);
/*		if (ULINE) BACKP = 1;		/* Set backspace mode if terminal underscores */

		if (ULINE)	/* This is a poor way to do it */
		{
			TUNDER = 1;
			NESTANDOUT = EOVER;
		}
		if (OSERTC && (INSERTM == 0))
		{
			INSERTM = INSERTC;/* old style insert modes */
			INSERTC = 0;
		}
		if (SCREG)
			LOPEN = SCREG;	/* make sure we use SCREG */
		if ((NOP == NULL) || (*NOP == 0))
			NOP = "\200";	/* null pads get lost */

		if (JQTYPE)
		{
			UPLEFT = CTL(X);
			UPRIGHT = CTL(Y);
			LORIGHT = CTL(Z);
			LOLEFT = CTL(\\);
			HORIX = CTL(]);
			VERTX = CTL(^);
		}

		_create_map ();

	}
}

/* length of a string */

lng (sp)
char   *sp;
{
	register char  *spo;

	spo = sp;
	while (*spo++);
	return (spo - sp - 1);
}

#endif

#else VT_TERMINFO

/*
 *		BEGIN TERMINFO VERSION
 *
 */

#ifndef MXTRA
#define MXTRA 8
#endif

wsttype (mp)
register char  *mp;
{
	int len;
	int old_len;
	register int	i;

	len = 1;
	if (setupterm (mp, 1, &len))
	{
		write (1, "Cannot setup your terminal.\r\n", 30);
		die (0);
	}

	if ((len != 1) || (lines < 2) || (columns < 2))
	{
		write (1, "Cannot setup your terminal - odd description.\r\n", 47);
		die (0);
	}

	/*	"up", (int *) & UP, */
	UP = cursor_up;
	/*	"do", (int *) & DOWN, */
	DOWN = cursor_down;
	if (DOWN == 0)
		DOWN = "\n";
	/*	"bc", (int *) & BACK, */
	BACK = cursor_left;
	/*	"nd", (int *) & FORWARD, */
	FORWARD = cursor_right;
	/*	"ho", (int *) & HOME, */
	HOME = cursor_home;
	/*	"cl", (int *) & CLEAR, */
	CLEAR = clear_screen;
	/*	"cd", (int *) & CLREST, */
	CLREST = clr_eos;
	/*	"ce", (int *) & CLINE, */
	CLINE = clr_eol;
	/*	"bl", (int *) & BELL, */
	BELL = bell;
	/*	"cm", (int *) & CURAD, */
	CURAD = cursor_address;
	/*	"tm", (int *) & TMAP, */
	/*	"tM",(int *) &SMAP, */
	/*	"pc", (int *) & NOP, */
	NOP = pad_char;
	if ((NOP == NULL) || (*NOP == 0))
		NOP = "\200";	/* null pads get lost */

	/*	"al", (int *) & LOPEN, */
	LOPEN = insert_line;
	/*	"dl", (int *) & LDEL, */
	LDEL = delete_line;
	/*	"ic", (int *) & INSERTC, */
	INSERTC = insert_character;
	/*	"im", (int *) & INSERTM, */
	INSERTM = enter_insert_mode;
	/*	"ei", (int *) & OSERTC, */
	OSERTC = exit_insert_mode;
	/*	"ip", (int *) & INSERTP, */
	INSERTP = insert_padding;
	/*	"dc", (int *) & DELC, */
	DELC = delete_character;
	/*	"sf", (int *) & SSCROLL, */
	SSCROLL = scroll_forward;
	/*	"sr", (int *) & RSCROLL, */
	RSCROLL = scroll_reverse;
	/*	"cr", (int *) & CR, */
	CR = carriage_return;
	/*	"cs", (int *) & SCREG, */
	SCREG = change_scroll_region;
	if (SCREG)
		LOPEN = SCREG;	/* make sure we use SCREG */
	/*	"ul", (int *) & ULINE, */
	ULINE = enter_underline_mode;
	/*	"ue", (int *) & UEND, */
	UEND = exit_underline_mode;
	/*	"eo", (int *) & EOVER, */
	EOVER = erase_overstrike;
	TUNDER = transparent_underline;
	NESTANDOUT = ceol_standout_glitch;
	/*	"vs", (int *) & SCINIT, */
	len = 0;
	SCINIT = ttystrings;
	if (enter_ca_mode)
		len = sprintf (SCINIT, "%s", enter_ca_mode);
	if (init_2string)
		len += sprintf (&SCINIT[len], "%s", init_2string);
	if (keypad_xmit)
		len += sprintf (&SCINIT[len], "%s", keypad_xmit);

	if (len)
		ttystrings[len++] = '\0';
	else
		SCINIT = 0;

	/*	"ve", (int *) & VEXIT, */
	VEXIT = &ttystrings[len];
	old_len = len;
	if (keypad_local)
	{
		len += sprintf (&ttystrings[len], "%s", keypad_local);
	}
	if (exit_ca_mode)
	{
		len += sprintf (&ttystrings[len], "%s", exit_ca_mode);
	}
	if (len == old_len)
	{
		VEXIT = 0;
	}
	else
	{
		ttystrings[len++] = '\0';
	}

	/*	"bx", (int *) & XBASE, */
	XBASE = 0;
	/*	"by", (int *) & YBASE, */
	YBASE = 0;

	/*	"co", (int *) & SCRWID, */
	SCRWID = columns;
	if (SCRWID == 0)
		SCRWID = 80;
	SCRWID--;
	if (SCRWID > NSCRCOL - 1)
		SCRWID = NSCRCOL - 1;

	/*	"li", (int *) & SCRNLIN, */
	SCRNLIN = lines;
	if (SCRNLIN > NSCRLIN)
		SCRNLIN = NSCRLIN;

	/*	"am", (int *) & SCRWRAP, */
	SCRWRAP = auto_right_margin;
	/*	"vc", (int *) & VCOST, */
	/*	"rc", (int *) & SRCADD, */
	/*	"mi", (int *) & MI, */
	MI = move_insert_mode;
	/*	"in", (int *) & IN, */
	IN = insert_null_glitch;
	/*	"dm", (int *) & DELMODE, */
	if (enter_delete_mode)			/* Punt DELMODE */
		DELC = 0;
	
	/*	"ru",(int *) &RELUP, */
	/*	"rd",(int *) &RELDOWN, */
	/*	"rl",(int *) &RELFORW, */
	/*	"rr",(int *) &RELBACK, */
	
	/*	"DL", (int *) & CLDEL,		/* Count line movement stuff */
	CLDEL = parm_delete_line;
	/*	"SF", (int *) & CLSCROLL, */
	CLSCROLL = parm_index;
	/*	"AL", (int *) & CLOPEN, */
	CLOPEN = parm_insert_line;
	
	/*	"kh", (int *) & _Key( K_HOME ),		/* Cursor Pad and Mouse Stuff */
	_Key( K_HOME ) = key_home;
	/*	"kz", (int *) & KBOTTOM, */
	_Key( K_BOTTOM ) = key_ll;
	/*	"ku", (int *) & _Key( K_UP ), */
	_Key( K_UP ) = key_up;
	/*	"kd", (int *) & _Key( K_DOWN ), */
	_Key( K_DOWN ) = key_down;
	/*	"kl", (int *) & _Key( K_LEFT ), */
	_Key( K_LEFT ) = key_left;
	/*	"kr", (int *) & _Key( K_RIGHT ), */
	_Key( K_RIGHT ) = key_right;	
	_Key( K_F0 ) = key_f0;
	_Key( K_F1 ) = key_f1;
	_Key( K_F2 ) = key_f2;
	_Key( K_F3 ) = key_f3;
	_Key( K_F4 ) = key_f4;
	_Key( K_F5 ) = key_f5;
	_Key( K_F6 ) = key_f6;
	_Key( K_F7 ) = key_f7;
	_Key( K_F8 ) = key_f8;
	_Key( K_F9 ) = key_f9;
	_Key( K_FA ) = key_f10;
	for( i = K_BTAB; i < K_HOME + _NKEYS; i++ )
		_Key( i ) = 0;

	/*	"kB", (int *) & KBKTAB,		/* BACK TAB and Mouse */
	/*	"km", (int *) & KMOUSE, */
	/*	"kM", (int *) & KMOUSE2, */
	
	/*	"CW", (int *) & CWINDOW,	/* Create a Window */
	CWINDOW = set_window;
	
	/*	"JQ", (int *) & JQTYPE,		/* HACK for Blits */

	term_dep( mp );
	
	acost = dcost (CURAD);
	lUP = dcost (UP);
	lDOWN = dcost (DOWN);
	lBAK = dcost (BACK);
	if (FORWARD)
		lFORWARD = dcost (FORWARD);
	else
		lFORWARD = 1;
	lCR = dcost (CR);

	get_leadin();

	_create_map ();

	/* Avoid the curses stuff */
}


#endif VT_TERMINFO

static int
_create_map ()
{
	register int index;
	register char   *tp;
	register CHAR   *cmap_ptr;
	unsigned int    *kmap_ptr;

	tp = (char *) sbrk (
		((((SCRWID + 1) * (sizeof (CHAR))) + MXTRA) * SCRNLIN * 2) +
		(((SCRWID * (sizeof (unsigned int))) + MXTRA) * SCRNLIN) );

	if (tp == 0)
	{
		cook ();
		tp =  "Not enough memory to create windows.\n";
		write (1, tp, strlen (tp));
		die ();
	}

	for (index = 0; index < SCRNLIN; index++)
	{
		cmap_ptr = (CHAR *) tp;
		cmap[index] = (CHAR *) tp;
		tp += ((SCRWID + 1) * (sizeof (CHAR)));
		while (cmap_ptr < (CHAR *) tp)
		{
			*cmap_ptr++ = 0;
		}
		tp += MXTRA;
	}

	for (index = 0; index < SCRNLIN; index++)
	{
		cmap_ptr = (CHAR *) tp;
		cmap2[index] = (CHAR *) tp;
		tp += ((SCRWID + 1) * (sizeof (CHAR)));
		while (cmap_ptr < (CHAR *) tp)
		{
			*cmap_ptr++ = 0;
		}
		tp += MXTRA;
	}

	for (index = 0; index < SCRNLIN; index++)
	{
		kmap_ptr = kmap[index] = (unsigned int *) tp;
		tp += (SCRWID * (sizeof (unsigned int)));
		while (kmap_ptr < (unsigned int *) tp)
		{
			*kmap_ptr++ = 0;
		}
		tp += MXTRA;
	}
}
