h27996
s 00068/00000/00000
d D 1.1 84/10/21 15:03:55 opcode 1 0
c date and time created 84/10/21 15:03:55 by opcode
e
u
U
t
T
I 1
/*
 * %W%	%G%
 *
 * Picture subwindow routines for the SUN Gremlin picture editor.
 *
 * Mark Opperman (opcode@monet.BERKELEY)
 *
 */

#include <suntool/tool_hs.h>
#include "gremlin.h"
#include "icondata.h"

/* imports from graphics.c */

extern GRCurrentSetOn();

/* imports from text.c */

extern TxMsgOK();

/* imports from main.c */

extern ELT *cset;
extern float PX, PY;
extern struct pixwin *pix_pw;
extern struct rect pix_size;
extern struct pixrect *cset_pr;
extern SUN_XORIGIN;
extern SUN_YORIGIN;

/* imports from help.c */

extern pixsw_help();


pix_left(ie)
register struct inputevent *ie;
{
    TxMsgOK();
    PX = winx_to_db(ie->ie_locx);
    PY = winy_to_db(ie->ie_locy);
    LGPoint();
}


pix_middle(ie)
register struct inputevent *ie;
{
    TxMsgOK();
    LGDeletePoint();
}


pix_right(ie)
register struct inputevent *ie;
{
    TxMsgOK();
    pixsw_help();
}


pix_winexit(ie)
register struct inputevent *ie;
{
    if ((ie->ie_locx >= pix_size.r_width)||(ie->ie_locy >= pix_size.r_height))
	GRCurrentSetOn();
}
E 1
