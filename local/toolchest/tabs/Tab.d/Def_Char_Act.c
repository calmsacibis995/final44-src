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
#include "vt.h"
#include "windows.h"
#include "fields.h"

Def_Char_Action (c, type, function, break_type)
char c;
int type;
int (*function) ();
int break_type;
{
	if (type == BREAK)
	{
		punc_list = remove_brk_item (punc_list, c);

		switch (break_type)
		{
		case CM_LIST:
			cm_list = insert_brk_item (cm_list, c);
			btab_list = remove_brk_item (btab_list, c);
			tab_list = remove_brk_item (tab_list, c);
			cfm_list = remove_brk_item (cfm_list, c);
			eof_list = remove_brk_item (eof_list, c);
			break;
		case BTAB_LIST:
			btab_list = insert_brk_item (btab_list, c);
			cm_list = remove_brk_item (cm_list, c);
			tab_list = remove_brk_item (tab_list, c);
			cfm_list = remove_brk_item (cfm_list, c);
			eof_list = remove_brk_item (eof_list, c);
			break;
		case TAB_LIST:
			tab_list = insert_brk_item (tab_list, c);
			cm_list = remove_brk_item (cm_list, c);
			btab_list = remove_brk_item (btab_list, c);
			cfm_list = remove_brk_item (cfm_list, c);
			eof_list = remove_brk_item (eof_list, c);
			break;
		case CFM_LIST:
			cfm_list = insert_brk_item (cfm_list, c);
			cm_list = remove_brk_item (cm_list, c);
			btab_list = remove_brk_item (btab_list, c);
			tab_list = remove_brk_item (tab_list, c);
			eof_list = remove_brk_item (eof_list, c);
			break;
		case EOF_LIST:
			eof_list = insert_brk_item (eof_list, c);
			cm_list = remove_brk_item (cm_list, c);
			btab_list = remove_brk_item (btab_list, c);
			tab_list = remove_brk_item (tab_list, c);
			cfm_list = remove_brk_item (cfm_list, c);
			break;
		case UTIL_LIST:	/* No List maintained for ESC and ? */
			eof_list = remove_brk_item (eof_list, c);
			cm_list = remove_brk_item (cm_list, c);
			btab_list = remove_brk_item (btab_list, c);
			tab_list = remove_brk_item (tab_list, c);
			cfm_list = remove_brk_item (cfm_list, c);
			break;
		}
	}
	else
	{
		if (type == PUNC)
			punc_list = insert_brk_item (punc_list, c);
		else
			punc_list = remove_brk_item (punc_list, c);

		cm_list = remove_brk_item (cm_list, c);
		btab_list = remove_brk_item (btab_list, c);
		tab_list = remove_brk_item (tab_list, c);
		cfm_list = remove_brk_item (cfm_list, c);
		eof_list = remove_brk_item (eof_list, c);
	}

	chartyp[c & 0377] = type;
	f_chartyp[c & 0377] = function;
}
