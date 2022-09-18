h25235
s 00023/00006/00260
d D 1.2 85/01/03 19:39:36 opcode 2 1
c misc updates
e
s 00266/00000/00000
d D 1.1 84/10/21 15:04:20 opcode 1 0
c date and time created 84/10/21 15:04:20 by opcode
e
u
U
t
T
I 1
/*
 * %W%	%G%
 *
 * Text subwindow routines for the SUN Gremlin picture editor.
 *
 * Mark Opperman (opcode@monet.BERKELEY)
 *
 */

#include <suntool/tool_hs.h>
#include <sgtty.h>
#include "gremlin.h"
#include "icondata.h"

/* imports from main.c */

extern struct pixwin *text_pw;
extern struct rect text_size;
extern TOOLINSTALLED;
I 2
extern (*lastcommand)();
extern lasttext;
E 2

/* imports from long.c */

extern LGTextSW();

/* imports from graphics.c */

extern GRCurrentSetOn();

/* imports from help.c */

extern textsw_help();
extern get_any_button();

/* locals */

struct pixfont *text_pf;

#define TEXT_LEFT 96		/* start of text input */
#define TEXT_FIRST  ' '
#define TEXT_LAST  '~'
#define CTRL_W  '\027'
#define RETURN  '\r'
#define MSGLINE 17

#define text_width  (text_pf->pf_defaultsize.x)
#define text_height  (text_pf->pf_defaultsize.y)

D 2
static char text_buf[TEXT_BUFMAX];
static char mesg_buf[TEXT_BUFMAX];
E 2
I 2
static char text_buf[TEXT_BUFMAX] = "";
static char mesg_buf[TEXT_BUFMAX] = "";
static char save_buf[TEXT_BUFMAX] = "";
E 2
static char text_erase;
static char text_kill;
static char text_erase_word;
static text_length;
static mesg_length;	/* length of last message displayed */
static putmsg = FALSE;	/* TRUE if TxPutMsg called since last button input. */


void
text_cursor(op)
int op;
{
    pw_write(text_pw, TEXT_LEFT + text_length * text_width, 0,
		text_width, text_height, op, &bigblack_pr, 0, 0);
}


void
text_output(c)
register c;
{
    register count;

    TxMsgOK();

    if ((c>=TEXT_FIRST) && (c<=TEXT_LAST) && (text_length<TEXT_BUFMAX-1)) {
	text_buf[text_length] = c;
	text_buf[text_length+1] = '\0';
	pw_char(text_pw, TEXT_LEFT + text_length * text_width, TEXT_BASELINE, 
			PIX_SRC, text_pf, c);
	text_length++;
	text_cursor(PIX_SRC);
    }

    else if ((c == text_erase) && (text_length > 0)) {
	text_cursor(PIX_NOT(PIX_SRC));
	text_length--;
	pw_char(text_pw, TEXT_LEFT + text_length * text_width,
		TEXT_BASELINE, PIX_SRC^PIX_DST, text_pf, text_buf[text_length]);
	text_buf[text_length] = '\0';
	text_cursor(PIX_SRC);
    }

    else if (c == text_kill) {
	TxKillLine();
    }

    else if ((c == text_erase_word) && (text_length > 0)) {
	text_cursor(PIX_NOT(PIX_SRC));
	count = 0;
	while ((text_length > 0) && (text_buf[text_length-1] == ' ')) {
	    text_length--;
	    count++;
	}
	while ((text_length > 0) && (text_buf[text_length-1] != ' ')) {
	    text_length--;
	    count++;
	}
	text_buf[text_length] = '\0';
	pw_replrop(text_pw, TEXT_LEFT + text_length * text_width, 0, 
			count * text_width, text_height, PIX_NOT(PIX_SRC), 
			&bigblack_pr, 0, 0);
	text_cursor(PIX_SRC);
    }

D 2
    else if (c == RETURN)	/* new text entry method */
E 2
I 2
    else if (c == RETURN) {	/* new text entry method */
	lastcommand = LGTextSW;
	lasttext = TRUE;
E 2
	LGTextSW();
I 2
    }
E 2
}


text_getvalue(s)
register char *s;
{
    register i = 0;

    while (text_buf[i] == ' ')
	i++;

I 2
    (void) strcpy(save_buf, &text_buf[i]);
E 2
    (void) strcpy(s, &text_buf[i]);
}


text_putvalue()
{
    pw_text(text_pw, 2, TEXT_BASELINE, PIX_SRC, 
				text_pf, "text input:");
    pw_text(text_pw, TEXT_LEFT, TEXT_BASELINE, PIX_SRC, 
				text_pf, text_buf);
    text_cursor(PIX_SRC);
    pw_text(text_pw, 0, MSGLINE + TEXT_BASELINE, PIX_NOT(PIX_SRC), 
				text_pf, mesg_buf);
}


I 2
text_restorebuf()
{
    register char *s;

    TxKillLine();
    s = save_buf;
    while (*s)
	text_output(*s++);
}


E 2
text_left(ie)
register struct inputevent *ie;
{
    TxMsgOK();
}


text_middle(ie)
register struct inputevent *ie;
{
    TxMsgOK();
I 2
    text_restorebuf();
E 2
}


text_right(ie)
register struct inputevent *ie;
{
    TxMsgOK();
    textsw_help();
}


text_winexit(ie)
register struct inputevent *ie;
{
    /* check for leaving tool */
    if ((ie->ie_locy < 0) || (ie->ie_locx < 0) || 
			     (ie->ie_locx >= text_size.r_width))
	GRCurrentSetOn();
}


TxInit()
{
    struct sgttyb sgtty_buf;

    ioctl(fileno(stdin), TIOCGETP, &sgtty_buf);
    text_erase = sgtty_buf.sg_erase;
    text_kill = sgtty_buf.sg_kill;
    text_erase_word = CTRL_W;

    text_length = mesg_length = 0;
    text_buf[0] = mesg_buf[0] = '\0';

    text_pf = pf_open("/usr/suntool/fixedwidthfonts/gacha.r.7");

    if (text_pf == (struct pixfont*) NULL) {
	printf("TxInit: error opening text_pf font file\n");
	exit(1);
    }
}  /* end TxInit */


/*
 * This routine marks it OK to output messages again
 * just as if a button had been pressed.
D 2
 * mro 7/14/84
E 2
 */
TxMsgOK()
{
    if (putmsg) {        /* message on the screen to be blanked */
	TxClearMsg();
    }

    putmsg = FALSE;
}  /* end TxMsgOK */


/*
D 2
 * TPutMsg outputs a one line message into the text subwindow.
E 2
I 2
 * Output a one line message into the text subwindow.
E 2
 * If the message follows another without intervening user input,
 * the prompt "More" is output and we wait for a button input event
 * before displaying the new message.
D 2
 * mro 9/10/84
E 2
 */
TxPutMsg(msg)
register char *msg;
{
    if (!TOOLINSTALLED) {		/* tool not displayed yet */
	fprintf(stderr, "%s\n", msg);
	return;
    }

    if (putmsg) {
	pw_text(text_pw, mesg_length * text_width, MSGLINE+TEXT_BASELINE, 
		    PIX_SRC, text_pf, " --More--");
	get_any_button();
	TxClearMsg();
    }

    pw_text(text_pw, 0, MSGLINE+TEXT_BASELINE, PIX_NOT(PIX_SRC), text_pf, msg);

    putmsg = TRUE;
    mesg_length = strlen(msg);
    (void) strcpy(mesg_buf, msg);
}  /* end TxPutMsg */


/*
 * Clear current message.
 */
TxClearMsg()
{
    pw_replrop(text_pw, 0, MSGLINE, 2000, text_height, 
				PIX_NOT(PIX_SRC), &bigblack_pr, 0, 0);
    mesg_length = 0;
    mesg_buf[0] = '\0';
}


/*
 * Consume user text parameter - don't touch message area.
 */
TxKillLine()
{
    if (text_length > 0) {
	pw_replrop(text_pw, TEXT_LEFT, 0, 2000, text_height, 
					PIX_NOT(PIX_SRC), &bigblack_pr, 0, 0);
	text_length = 0;
	text_buf[0] = '\0';
	text_cursor(PIX_SRC);
    }
}
E 1
