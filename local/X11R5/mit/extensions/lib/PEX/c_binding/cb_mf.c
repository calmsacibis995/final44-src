/* $XConsortium: cb_mf.c,v 5.1 91/02/16 09:47:53 rws Exp $ */

/***********************************************************
Copyright 1989, 1990, 1991 by Sun Microsystems, Inc. and the X Consortium.

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


#include "phg.h"
#include "cp.h"
#include "cb_priv.h"

void
pwrite_item(ws, type, length, record)
Pint		ws;		/* workstation identifier	*/
Pint		type;		/* item type	*/
Pint		length;		/* item data record length	*/
Pitem_data	*record;	/* item data record	*/
{
    if (CB_ENTRY_CHECK( phg_cur_cph, ERR3, Pfn_write_item))
	/* NOT IMPLEMENTED */
	ERR_REPORT( phg_cur_cph->erh, ERRN152);
}

void
pget_item_type(ws, type, length)
Pint	ws;		/* workstation identifier	*/
Pint	*type;		/* OUT item type	*/
Pint	*length;	/* OUT item data record length	*/
{
    if (CB_ENTRY_CHECK( phg_cur_cph, ERR3, Pfn_get_item_type))
	/* NOT IMPLEMENTED */
	ERR_REPORT( phg_cur_cph->erh, ERRN152);
}

void
pread_item(ws, max_length, record)
Pint		ws;		/* workstation identifier	*/
Pint		max_length;	/* max item data record length	*/
Pitem_data	*record;	/* OUT item data record	*/
{
    if (CB_ENTRY_CHECK( phg_cur_cph, ERR3, Pfn_read_item))
	/* NOT IMPLEMENTED */
	ERR_REPORT( phg_cur_cph->erh, ERRN152);
}

void
pinterpret_item    (type, length, record)
Pint		type;		/* item type	*/
Pint		length;		/* item data record length	*/
Pitem_data	*record;	/* item data record	*/
{
    if (CB_ENTRY_CHECK( phg_cur_cph, ERR2, Pfn_interpret_item))
	/* NOT IMPLEMENTED */
	ERR_REPORT( phg_cur_cph->erh, ERRN152);
}
