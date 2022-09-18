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
#include <termio.h>

/* terminal type tester.  exercises terminal capabilities to dest
 * their definition and use. */

extern char *UP;					/* cursor up line */
extern char *DOWN;
extern char *BACK;
extern char *FORWARD;
extern char *HOME;
extern char *CLEAR;
extern char *CLREST;
extern char *CLINE;
extern char *BELL;
extern char *CURAD;
extern char *TMAP;
extern char *NOP;
extern char *LOPEN;
extern char *LDEL;
extern char *INSERTC;
extern char *INSERTM;
extern char *OSERTC;
extern char *INSERTP;
extern char *DELC;
extern char *SSCROLL;
extern char *RSCROLL;
extern char *CR;
extern char *SCREG;
extern char *ULINE;
extern int EOVER;
extern char *SCINIT;
extern char *VEXIT;
extern int XBASE;
extern int YBASE;
extern int SCRWID;
extern int SCRNLIN;
extern int SCRWRAP;
extern int VCOST;
extern int SRCADD;
extern int MI;
extern int IN;
extern int DELMODE;

extern int scrlin,scrcol;

#undef clear

pause()
{
	mgetchar();
}

main()
{
	char buf[2];
	int i;

	ttystart();			/* start terminal processing */

	clear ();
	mgo (5, 0);
	uprint ("Write some stuff");
	pause ();
	mgo (5, 5);
	vputch ('x' | 0400);
	pause ();
	mgo (5, 0);
	pause ();
	vputch ('x' | 0400);
	pause ();

	clear ();
	xprintf ("___");
	uprint ("WOW");
	pause();
	mgo (0, 0);
	xprintf ("___");
	xprintf ("WOW");
	pause();
	refresh ();
	pause ();
	die (0);

/* Clear screen test */
	
	clear ();
	mgo (0, 0);
	xprintf ("Clear Screen Test");
	pause();

	clear();
	xprintf ("\nScreen was cleared");
	pause();

/* Cursor addressing: */

	clear();

	if (CURAD) {
		for (i = 0; i <= SCRWID;  i++) {
			scrlin = -100;		/* make sure we do cursor movement */
			mgo(10,i);
			xprintf ("%c", (i&07)+'0');
		}
		mgo(12,10);
		xprintf ("Above line should count accross the screen 0-7");
		pause();

		clear();
		for (i = 0; i < SCRNLIN; i++) {
			scrlin = -100;
			mgo(i,SCRWID/2);
			xprintf ("%d",i);
		}
		mgo(0,0);
		xprintf ("Screen should");
		mgo(1,0);
		xprintf ("have a line");
		mgo(2,0);
		xprintf ("counting down");
		mgo(3,0);
		xprintf ("the middle");
		pause();

		mgo(4,0);
		axprintf (3 << 7, "testing the refresh");
		pause ();

		refresh ();
		pause ();

		clear();
	}

/* RELATIVE SCREEN MOTION */
	
	if (BACK) {
		mgo(5,0);
		xprintf ("Drawing backwards from 10,20 to 10,0");
		mgo(10,20);
		for (i = 0; i < 20; i++) {
			xprintf ("x");
			mgo (mline, mcol - 2);
		}
		pause();
		clear();
	}
	if (FORWARD) {
		mgo(5,0);
		xprintf ("Drawing Forwards from 10,0 to 10,20");
		mgo(10,0);
		for (i = 0; i < 20; i++) {
			xprintf ("x");
			eprintf(BACK);
			eprintf(FORWARD);
		}
		putchar('x');
		eprintf(BACK);
		pause();
		clear();
	}
	if (DOWN) {
		mgo(0,5);
		xprintf ("Drawing down from 1,20 to 21,20");
		mgo(1,20);
		for (i = 0; i < 20; i++) {
			putchar('x');
			eprintf(BACK);
			eprintf(DOWN);
		}
		putchar('x');
		eprintf(BACK);
		pause();
		clear();
	}
	if (UP) {
		mgo(0,5);
		xprintf ("Drawing UP from 21,20 to 1,20");
		mgo(21,20);
		for (i = 0; i < 20; i++) {
			putchar('x');
			eprintf(BACK);
			eprintf(UP);
		}
		putchar('x');
		eprintf(BACK);
		pause();
		clear();
	}
/* Carriage Return  */
	
	if (CR) {
		mgo(10,25);
		xprintf ("Carriage");
		mgo(10,0);
		xprintf ("Return");
		pause();
		clear();
	}
	
/* HOME */
	
	if (HOME) {
		mgo(10,20);
		xprintf ("Going");
		pause ();
		eprintf (HOME);
		printf("Home");
		pause();
		clear();
	}
	
/* Wrapping */
	
	if (SCRWRAP) {
		mgo(5,SCRWID-6);
		printf("cursor wraps");
		if (CURAD) {
			scrlin = -100;
			mgo(7,0);
		} else {
			printf("\r\n"); /* PUNT for terminal with no CM */
		}
		printf("wraps under wraps");
		pause();
		clear();
	}
	
	if (CLINE) {
		mgo(10,0);
		xprintf ("clearing everything after clear");
		mgo(11,0);
		xprintf ("clearing everything after clear");
		mgo(10,5);
		clrl();
		pause();
		clear();
	}
/* BELL */
	
	if (BELL) {
		xprintf ("beep beep beep");
		beep();
		beep();
		beep();
		pause ();
		clear();
	}
	if (SSCROLL){
		mgo(SCRNLIN-1,0);
		printf ("scrolling");
		eprintf(SSCROLL);
		mgo(SCRNLIN-1,0);
		printf("up");
		eprintf(SSCROLL);
		mgo(SCRNLIN-1,0);
		printf("the");
		eprintf(SSCROLL);
		mgo(SCRNLIN-1,0);
		printf("screen");
		pause();
		clear();
	}
	if (INSERTC||INSERTM) { 
		
		mgo(10,0);
		printf("Testing insert character.");
		if (IN) {
			printf ("		These won't move unless pushed\r\n");
			printf("These move when you push them\r\n");
		}
		else printf ("		These move too\r\n");
		printf("  all characters except ^G insert after test");
		scrlin = -100;
		mgo(10,4);
		if (INSERTM) {
			eprintf(INSERTM);
		}
		while ((i = mgetchar()) != '') {
			if (INSERTC) eprintf(INSERTC);
			putchar(i);
			if (INSERTP) eprintf(INSERTP);
		}
		if (OSERTC) eprintf(OSERTC);
		clear();
	}
	if (DELC) { 
		mgo(10,0);
		printf("Testing delete character.");
		if (IN) {
			printf(" All of these characters, including the wrap to the new line, should move");
			printf ("		These won't move\r\n");
		}
		else printf ("		These move too\r\n");
		printf("  all characters except ^G delete after test");
		scrlin = -100;
		mgo(10,4);
		if (DELMODE) {
			eprintf(INSERTM);
		}
		while ((i = mgetchar()) != '') {
			eprintf(DELC);
		}
		if (DELMODE) eprintf(OSERTC);
		clear();
	}
	if (LOPEN) {
		for (i = 0; i < SCRNLIN; i++) {
			mgo(i,0);
			xprintf ("Line %d",i);
		}
		mgo(0,10);
		xprintf("u to scroll lines %d through %d up",2,SCRNLIN-2);
		mgo(1,10);
		xprintf("d to scroll down");
again:		i = mgetchar();
		if (i == 'u') {
			vadjust(2,SCRNLIN-2,-1);
			goto again;
		}
		if (i == 'd') {
			vadjust(2,SCRNLIN-2,1);
			goto again;
		}
		refresh ();
		pause ();
		clear();
	}
	if (ULINE) {
		
		if (EOVER) {
			mgo(4,0);
			uprint("Underlined_Characters");
			mgo(6,0);
			uprint("These won't wind up underlined");
			mgo(6,0);
			xprintf("These won't wind up underlined");
		} else {
			mgo(6,0);
			uprint("These characters are underlined");
			mgo(7,0);
			xprintf("These won't wind up underlined");
		}
		pause();

		refresh ();
		pause ();
	}

	die(0);
}

uprint(sp)
register char *sp;
{
	axprintf (0400, sp);
}
