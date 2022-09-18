/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
/* ioctl_hack.c */

#include <termio.h>
#include <stdio.h>

#define TRUE		1
#define FALSE		0
#define STTYRAW		1
#define STTYNORM	0

struct termio nttybuf;		/* ioctl buffers */
struct termio rttybuf;
static int set_tty;

/*
 *
 *	cp_start()
 *
 *	This routine initiates the terminal interaction with
 *	comnd.  This is done by getting the terminal mode and
 *	setting up the structures for subsequent calls to cp_stty().
 *
 *	Return: TRUE or FALSE
 *
 */
cp_start()
{

	if(ioctl(0, TCGETA, &nttybuf) < 0)	/* Assume ENOTTY */
	{
		set_tty = FALSE;

	} else {

		set_tty = TRUE;

	/* Setup raw mode struct */

	/* Don't map c/r to newline and Don't map newline to c/r on input */
	/* Disable parity checking on input, and break int.s. */

		rttybuf.c_iflag = nttybuf.c_iflag;
		rttybuf.c_iflag &= ~(IGNPAR | PARMRK | INPCK
				     | INLCR | IGNCR | ICRNL | IGNBRK);
		rttybuf.c_iflag |= (ISTRIP | BRKINT | IXON | IXANY);

		/*	extra flags or assumed from user's stty
		 *	&= ~IUCLC;
		 *	|= IXOFF;
		 */

		/* Map newline to newline c/r on output */
		/* Postprocess the output
		rttybuf.c_oflag = nttybuf.c_oflag;
		rttybuf.c_oflag |= (ONLCR|OPOST);
		rttybuf.c_oflag &= ~OCRNL;
		*/
		rttybuf.c_oflag = 0;

		rttybuf.c_cflag = nttybuf.c_cflag;

		/* Echo newline and flush after int. or quit */
		/* This may cause trouble if you use a lot of */
		/* interrupts - NOFLSH */
		rttybuf.c_lflag = ECHONL | ISIG;

		rttybuf.c_line = nttybuf.c_line;

		rttybuf.c_cc[VINTR] = nttybuf.c_cc[VINTR];
		rttybuf.c_cc[VQUIT] = 0377;

		rttybuf.c_cc[VERASE] = nttybuf.c_cc[VERASE];
		rttybuf.c_cc[VKILL] = nttybuf.c_cc[VKILL];
	
		/* MIN characters to be read */
		rttybuf.c_cc[VMIN] = (unsigned char)1;

		/* MAX time value to wait */
		rttybuf.c_cc[VTIME] = (unsigned char)0;
		rttybuf.c_cc[6] = nttybuf.c_cc[6];
		rttybuf.c_cc[7] = nttybuf.c_cc[7];
	}

	return(set_tty);
}

/*
 *
 *	cp_stty is the routine that handles switching back and forth
 *	from cannonical (cooked) to non-cannonical (raw) modes.
 *
 *	flag is the mode to be instantiated
 *
 *	Return: TRUE or FALSE
 *
 */
cp_stty(flag)
int flag;
{
	register int	cnt = 0;

	if(set_tty)
	{
		while(cnt < 5)
		{
			if(flag == STTYRAW)
			{
				ioctl(0, TCXONC, 1);
				if(ioctl(0, TCSETAW, &rttybuf) == 0) break;
			} else {
				ioctl(0, TCXONC, 1);
				if(ioctl(0, TCSETAW, &nttybuf) == 0) break;
			}
		       cnt++;
		}

		if(cnt == 5)
		{
			return(FALSE);
		}

		return(TRUE);
	}

	return(FALSE);
}
