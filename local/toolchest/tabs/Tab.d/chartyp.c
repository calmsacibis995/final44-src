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
#include <setjmp.h>
#include "fields.h"

/*
 *	This table governs the way character input is handled.
 *	DSCARD characters are discarded.  NORMAL characters are
 *	stored in the input string.  CORRECT characters cause
 *	various editing functions to occur.  BREAK characters
 *	terminate input.  PUNC characters are handled exactly
 *	the same as NORMAL characters as far as input is concerned.
 *	They are used to delimit fields by comnd ().
 */

char    chartyp[0233] =	/* add a spare */
{
	CORRECT,		/* Null - also BREAK	*/
	BREAK,			/* ^A -- HOME		*/
	CORRECT,		/* ^B -- Beginning of field	*/
	BREAK,			/* ^C -- Clear the messgaes */
	NORMAL,			/* ^D */
	CORRECT,		/* ^E -- End of field	*/
	NORMAL,			/* ^F */
	BREAK,			/* ^G -- Down		*/
	NORMAL,			/* ^H */
	BREAK,			/* ^I -- Tab		*/
	BREAK,			/* ^J -- Line Feed (nl)	*/
	NORMAL,			/* ^K */
	CORRECT,		/* ^L -- Left in the field	*/
	BREAK,			/* ^M -- Carriage Return	*/
	BREAK,			/* ^N -- Next field - FTABC forward tab	*/
	CORRECT,		/* ^O -- Overlay the last line	*/
	BREAK,			/* ^P -- Previous field	- BTABC back tab*/
	NORMAL,			/* ^Q */
	CORRECT,		/* ^R -- Right in the field	*/
	NORMAL,			/* ^S */
	BREAK,			/* ^T -- Left		*/
	NORMAL,			/* ^U */
	BREAK,			/* ^V -- Verify the screen - refresh	*/
	CORRECT,		/* ^W -- Delete word	*/
	NORMAL,			/* ^X */
	BREAK,			/* ^Y -- Right		*/
	BREAK,			/* ^Z -- Bottom		*/
	BREAK,			/* ^[ -- Escape		*/
	NORMAL,			/* ^\ */
	NORMAL,			/* ^] */
	BREAK,			/* ^^ -- Up		*/
	NORMAL,			/* ^_ -- IF CORRECT dump screen	*/
	PUNC,			/* Space */
	NORMAL,			/* ! */
	NORMAL,			/* " */
	NORMAL,			/* # */
	NORMAL,			/* $ */
	NORMAL,			/* % */
	NORMAL,			/* & */
	NORMAL,			/* ' */
	NORMAL,			/* ( */
	NORMAL,			/* ) */
	NORMAL,			/* * */
	NORMAL,			/* + */
	NORMAL,			/* , */
	NORMAL,			/* - */
	NORMAL,			/* . */
	NORMAL,			/* / */
	NORMAL,			/* 0 */
	NORMAL,			/* 1 */
	NORMAL,			/* 2 */
	NORMAL,			/* 3 */
	NORMAL,			/* 4 */
	NORMAL,			/* 5 */
	NORMAL,			/* 6 */
	NORMAL,			/* 7 */
	NORMAL,			/* 8 */
	NORMAL,			/* 9 */
	NORMAL,			/* : */
	NORMAL,			/* ; */
	NORMAL,			/* < */
	NORMAL,			/* = */
	NORMAL,			/* > */
	BREAK,			/* ? -- Help		*/
	NORMAL,			/* @ */
	NORMAL,			/* A */
	NORMAL,			/* B */
	NORMAL,			/* C */
	NORMAL,			/* D */
	NORMAL,			/* E */
	NORMAL,			/* F */
	NORMAL,			/* G */
	NORMAL,			/* H */
	NORMAL,			/* I */
	NORMAL,			/* J */
	NORMAL,			/* K */
	NORMAL,			/* L */
	NORMAL,			/* M */
	NORMAL,			/* N */
	NORMAL,			/* O */
	NORMAL,			/* P */
	NORMAL,			/* Q */
	NORMAL,			/* R */
	NORMAL,			/* S */
	NORMAL,			/* T */
	NORMAL,			/* U */
	NORMAL,			/* V */
	NORMAL,			/* W */
	NORMAL,			/* X */
	NORMAL,			/* Y */
	NORMAL,			/* Z */
	NORMAL,			/* [ */
	NORMAL,			/* \ */
	NORMAL,			/* ] */
	NORMAL,			/* ^ */
	NORMAL,			/* _ */
	NORMAL,			/* ` */
	NORMAL,			/* a */
	NORMAL,			/* b */
	NORMAL,			/* c */
	NORMAL,			/* d */
	NORMAL,			/* e */
	NORMAL,			/* f */
	NORMAL,			/* g */
	NORMAL,			/* h */
	NORMAL,			/* i */
	NORMAL,			/* j */
	NORMAL,			/* k */
	NORMAL,			/* l */
	NORMAL,			/* m */
	NORMAL,			/* n */
	NORMAL,			/* o */
	NORMAL,			/* p */
	NORMAL,			/* q */
	NORMAL,			/* r */
	NORMAL,			/* s */
	NORMAL,			/* t */
	NORMAL,			/* u */
	NORMAL,			/* v */
	NORMAL,			/* w */
	NORMAL,			/* x */
	NORMAL,			/* y */
	NORMAL,			/* z */
	NORMAL,			/* { */
	NORMAL,			/* | */
	NORMAL,			/* } */
	NORMAL,			/* ~ */
	DSCARD,			/* Rub Out - also generates a signal */

/* Generic BREAK character types - Discarded on read - included in getatm */
	DSCARD,			/* 0200 HOME */

	DSCARD,			/* 0201 UP */
	DSCARD,			/* 0202 DOWN */
	DSCARD,			/* 0203 RIGHT */
	DSCARD,			/* 0204 LEFT */
	DSCARD,			/* 0205 F0 */
	DSCARD,			/* 0206 F1 */
	DSCARD,			/* 0207 F2 */

	DSCARD,			/* 0210 F3 */
	DSCARD,			/* 0211 F4 */
	DSCARD,			/* 0212 F5 */
	DSCARD,			/* 0213 F6 */
	DSCARD,			/* 0214 F7 */
	DSCARD,			/* 0215 F8 */
	DSCARD,			/* 0216 F9 */
	DSCARD,			/* 0217 F10 */

	DSCARD,			/* 0220 BOTTOM */
	DSCARD,			/* 0221 BACK TAB */
	DSCARD,			/* 0222 MOUSE START */
	DSCARD,			/* 0223 MOUSE END */
	DSCARD,			/* 0224 FORWARD TAB */
	DSCARD,			/* 0225 TAB */
	DSCARD,			/* 0226 NULL */
	DSCARD,			/* 0227 ESCAPE */
	DSCARD,			/* 0230 HELP */
	DSCARD,			/* 0231 EOL */
	DSCARD			/* 0232 EOF */
};

/*	typedef int (*PFI) (); */

PFI    f_chartyp [0233] =
{
	corchar,		/* Null - also BREAK */
	brkchar,		/* ^A -- HOME		*/
	corchar,		/* ^B -- Beginning of field	*/
	corchar,		/* ^C -- Clear the messgaes */
	regchar,		/* ^D */
	corchar,		/* ^E -- End of field	*/
	regchar,		/* ^F */
	brkchar,		/* ^G -- Down		*/
	regchar,		/* ^H */
	brkchar,		/* ^I -- Tab		*/
	brkchar,		/* ^J -- Line Feed (nl)	*/
	regchar,		/* ^K */
	corchar,		/* ^L -- Left in the field	*/
	brkchar,		/* ^M -- Carriage Return	*/
	brkchar,		/* ^N -- Next field - FTABC forward tab	*/
	corchar,		/* ^O -- Overlay the last line	*/
	brkchar,		/* ^P -- Previous field	- BTABC back tab*/
	regchar,		/* ^Q */
	corchar,		/* ^R -- Right in the field	*/
	regchar,		/* ^S */
	brkchar,		/* ^T -- Left		*/
	regchar,		/* ^U */
	corchar,		/* ^V -- Verify the screen - refresh	*/
	corchar,		/* ^W -- Delete word	*/
	regchar,		/* ^X */
	brkchar,		/* ^Y -- Right		*/
	brkchar,		/* ^Z -- Bottom		*/
	brkchar,		/* ^[ -- Escape		*/
	regchar,		/* ^\ */
	regchar,		/* ^] */
	brkchar,		/* ^^ -- Up		*/
	regchar,		/* ^_ -- IF CORRECT dump screen	*/
	regchar,		/* Space */
	regchar,		/* ! */
	regchar,		/* " */
	regchar,		/* # */
	regchar,		/* $ */
	regchar,		/* % */
	regchar,		/* & */
	regchar,		/* ' */
	regchar,		/* ( */
	regchar,		/* ) */
	regchar,		/* * */
	regchar,		/* + */
	regchar,		/* , */
	regchar,		/* - */
	regchar,		/* . */
	regchar,		/* / */
	regchar,		/* 0 */
	regchar,		/* 1 */
	regchar,		/* 2 */
	regchar,		/* 3 */
	regchar,		/* 4 */
	regchar,		/* 5 */
	regchar,		/* 6 */
	regchar,		/* 7 */
	regchar,		/* 8 */
	regchar,		/* 9 */
	regchar,		/* : */
	regchar,		/* ; */
	regchar,		/* < */
	regchar,		/* = */
	regchar,		/* > */
	brkchar,		/* ? */
	regchar,		/* @ */
	regchar,		/* A */
	regchar,		/* B */
	regchar,		/* C */
	regchar,		/* D */
	regchar,		/* E */
	regchar,		/* F */
	regchar,		/* G */
	regchar,		/* H */
	regchar,		/* I */
	regchar,		/* J */
	regchar,		/* K */
	regchar,		/* L */
	regchar,		/* M */
	regchar,		/* N */
	regchar,		/* O */
	regchar,		/* P */
	regchar,		/* Q */
	regchar,		/* R */
	regchar,		/* S */
	regchar,		/* T */
	regchar,		/* U */
	regchar,		/* V */
	regchar,		/* W */
	regchar,		/* X */
	regchar,		/* Y */
	regchar,		/* Z */
	regchar,		/* [ */
	regchar,		/* \ */
	regchar,		/* ] */
	regchar,		/* ^ */
	regchar,		/* _ */
	regchar,		/* ` */
	regchar,		/* a */
	regchar,		/* b */
	regchar,		/* c */
	regchar,		/* d */
	regchar,		/* e */
	regchar,		/* f */
	regchar,		/* g */
	regchar,		/* h */
	regchar,		/* i */
	regchar,		/* j */
	regchar,		/* k */
	regchar,		/* l */
	regchar,		/* m */
	regchar,		/* n */
	regchar,		/* o */
	regchar,		/* p */
	regchar,		/* q */
	regchar,		/* r */
	regchar,		/* s */
	regchar,		/* t */
	regchar,		/* u */
	regchar,		/* v */
	regchar,		/* w */
	regchar,		/* x */
	regchar,		/* y */
	regchar,		/* z */
	regchar,		/* { */
	regchar,		/* | */
	regchar,		/* } */
	regchar,		/* ~ */
	corchar,		/* Rub Out - also generates a signal */

/* Generic BREAK character types - Discarded on read - included in getatm */
	brkchar,		/* 0200 HOME */

	brkchar,		/* 0201 UP */
	brkchar,		/* 0202 DOWN */
	brkchar,		/* 0203 RIGHT */
	brkchar,		/* 0204 LEFT */
	brkchar,		/* 0205 F0 */
	brkchar,		/* 0206 F1 */
	brkchar,		/* 0207 F2 */

	brkchar,		/* 0210 F3 */
	brkchar,		/* 0211 F4 */
	brkchar,		/* 0212 F5 */
	brkchar,		/* 0213 F6 */
	brkchar,		/* 0214 F7 */
	brkchar,		/* 0215 F8 */
	brkchar,		/* 0216 F9 */
	brkchar,		/* 0217 F10 */

	brkchar,		/* 0220 BOTTOM */
	brkchar,		/* 0221 BACK TAB */
	brkchar,		/* 0222 MOUSE START */
	brkchar,		/* 0223 MOUSE END */
	brkchar,		/* 0224 FORWARD TAB */
	brkchar,		/* 0225 TAB */
	brkchar,		/* 0226 NULL */
	brkchar,		/* 0227 ESCAPE */
	brkchar,		/* 0230 HELP */
	brkchar,		/* 0231 EOL */
	brkchar			/* 0232 EOF */
};
