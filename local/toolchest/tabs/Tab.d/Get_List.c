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

/*
 *	Get_List (Field_List, Count, ok_to_back, ok_to_forward)
 *
 *	The procedure collects input for an array of fields.  The array
 *	is Count items long.
 *
 *	Show_List (Field_List, Count)
 *
 *	The procedure performs a Show_Field () for an array of fields.
 *	The array is Count items long.
 */

#define POP_ARGS() \
	GL_Arg_Stack = GL_Arg_Stack -> previous; \
	if (GL_Arg_Stack) \
		GL_Arg_Stack -> next = 0;

#define FIELD_X Field_List[index]->x_pos
#define FIELD_Y Field_List[index]->y_pos

Get_List (Field_List, Count, ok_to_back, ok_to_forward)
register struct field_item     *Field_List[];
int     Count;
boole     ok_to_back;
boole     ok_to_forward;
{
	Get_SI_List (Field_List, Count, 0, ok_to_back, ok_to_forward);
}

Get_SI_List (Field_List, Count, S_Index, ok_to_back, ok_to_forward)
register struct field_item     *Field_List[];
register int     Count;
int     S_Index;
boole     ok_to_back;
boole     ok_to_forward;
{
	register int    match;
	unsigned int *kptr;
	unsigned int key;
	int     index;
	int     xstart;
	int     vis;
	int     old_index;
	int     rc;
	int     line;
	int     x;
	int     y;
	int     mouse_x;
	int     mouse_y;
	int     value;
	int     last_value;
	struct	arg_stack	Current_Args;
	char   *err_str;

	index = S_Index;
	rc = 0;

	/* push list of fields onto field_list stack */
	if (GL_Arg_Stack)
		GL_Arg_Stack -> next = &Current_Args;
	Current_Args.previous = GL_Arg_Stack;
	Current_Args.next = 0;
	Current_Args.f = Field_List;
	Current_Args.count = Count;
	Current_Args.ptr_index = &index;
	Current_Args.ptr_rc = &rc;
	GL_Arg_Stack = &Current_Args;

	while ((index < Count) && (index > -1))
	{
Next_Field:
		while (gl_touchedp (Field_List[index]))
		{
			index++;
			if (index >= Count)
			{
				POP_ARGS();
				return (0);
			}
		}

		if (Field_List[index] -> type == CMREGN)
		{
			if (Field_List[index] -> pre_action)
			{
				x = Field_List[index] -> pre_action (Field_List, Count, index, rc);
				if (x != index)
				{
					if (x != -1)
						index = x;
					continue;
				}
			}

			rc = Get_List (Field_List[index] -> fnalt,
					Field_List[index] -> length,
					index, (Count-index-1));

			Field_List[index] -> cmflg &= ~(CMABU);
			strcpy (Field_List[index] -> txbuf, "DONE");

			if (Field_List[index] -> post_action)
			{
				x = Field_List[index] -> post_action (Field_List, Count, index, rc);
				if (x != index)
				{
					if (x != -1)
						index = x;
					continue;
				}
			}

			switch (rc)
			{
				case CMUP: 
				case CMBTAB: 
				case CMLEFT: 
					index--;
					if (index < 0)
						index = 0;
					continue;

				case CMFTAB:
				case CMRIGHT:
				case CMDOWN:
				case CMEOF:
				case CMMOUSE:
				default:
					index++;
					continue;
			}
		}

		x = 0;

		if (FIELD_X < 0)
			x = FIELD_X;

		if (FIELD_X >= 512)
			x = FIELD_X - 512 -
				(Field_List[index] -> window -> _bot_x -
					Field_List[index] -> window -> _top_x - 2);
		if (x)
			slide_region (Field_List, Count, -x);


		if (Glbl_pre_action)
		{
			x = Glbl_pre_action (Field_List, Count, index, rc);
			if (x != index)
			{
				if (Field_List[index] -> pre_action)
					Field_List[index] -> pre_action (Field_List, Count, index, rc);
				if (x != -1)
					index = x;
				continue;
			}
		}

		if (Field_List[index] -> pre_action)
		{
			x = Field_List[index] -> pre_action (Field_List, Count, index, rc);
			if (x != index)
			{
				if (x != -1)
					index = x;
				continue;
			}
		}

/*
 *
 *	Get_Field
 *
 */
		rc = Get_Field (Field_List[index]);

		switch (rc)
		{
			case CMEOF:
				if (Field_List[index] -> txflg & TXEFVFY)
					goto Format;
				break;
			case CMBTAB: 
				if (Field_List[index] -> txflg & TXBTVFY)
					goto Format;
				break;
			case CMFTAB: 
			case CMMOUSE: 
			case CMRIGHT: 
			case CMLEFT: 
			case CMDOWN: 
			case CMUP: 
			case CMBOTTOM: 
			case CMHOME: 
				if ((Field_List[index] -> txflg & TXCPVFY) == 0)
					break;
			default: 
		Format: 
				Field_List[index] -> cmflg &= ~(CMABU);
				if (Field_List[index] -> attribute & FALEFT)
				{
					Left_Field (Field_List[index]);
				}
				else
				if (Field_List[index] -> attribute & FARIGHT)
				{
					Right_Field (Field_List[index]);
				}
				else
				if (Field_List[index] -> attribute & FACENTER)
				{
					Center_Field (Field_List[index]);
				}
		}

		if (Glbl_post_action)
		{
			x = Glbl_post_action (Field_List, Count, index, rc);
			if (x != index)
			{
				if (Field_List[index] -> post_action)
					Field_List[index] -> post_action (Field_List, Count, index, rc);
				if (x != -1)
					index = x;
				continue;
			}
		}
		if (Field_List[index] -> post_action)
		{
			x = Field_List[index] -> post_action (Field_List, Count, index, rc);
			if (x != index)
			{
				if (x != -1)
					index = x;
				continue;
			}
		}

		switch (rc)
		{
			case CMEOF:
				POP_ARGS();
				return (CMEOF);

			case CMHOME: 
				old_index = index;
				index = 0;
				while (gl_touchedp (Field_List[index]))
				{
					index++;
					if (index >= Count)
					{
						index = old_index;
						beep ();
						Print_Message (Field_List[index] -> meswin, Mess_Attribute,
								"Cannot move to HOME at this time.");
						goto Next_Field;
					}
				}
				continue;

			case CMBOTTOM: 
				old_index = index;
				index = Count - 1;
				while (gl_touchedp (Field_List[index]))
				{
					index--;
					if (index < 0)
					{
						index = old_index;
						beep ();
						Print_Message (Field_List[index] -> meswin, Mess_Attribute,
								"Cannot move to BOTTOM at this time.");
						goto Next_Field;
					}
				}
				continue;

			case CMUP: 
				old_index = index;
				match = index;
				line = Field_List[index] -> x_pos;
				index = -1;
				while (TRUE)
				{
					index++;
					if (index == Count)
					{
						if (match != old_index)
							break;
						if (ok_to_back)
						{
							POP_ARGS();
							return (CMUP);
						}
						index = old_index;
						beep ();
						Print_Message (Field_List[index] -> meswin, Mess_Attribute,
								"Cannot move UP to another field at this time.");
						goto Next_Field;
					}
					if (gl_touchedp (Field_List[index]))
						continue;
					if (index == old_index)
						continue;
					if (Field_List[index] -> x_pos <
						Field_List[old_index] -> x_pos)
					{
						if (match == old_index)
						{
							match = index;
							continue;
						}
						if (Field_List[index] -> x_pos < Field_List[match] -> x_pos)
							continue;
						if (closer (Field_List[index],
								Field_List[match],
								Field_List[old_index]))
							match = index;
					}
				}
				index = match;
				continue;

			case CMDOWN: 
				old_index = index;
				match = index;
				line = Field_List[index] -> x_pos;
				index = -1;
				while (TRUE)
				{
					index++;
					if (index == Count)
					{
						if (match != old_index)
							break;
						if (ok_to_back)
						{
							POP_ARGS();
							return (CMUP);
						}
						index = old_index;
						beep ();
						Print_Message (Field_List[index] -> meswin, Mess_Attribute,
								"Cannot move DOWN to another field at this time.");
						goto Next_Field;
					}
					if (gl_touchedp (Field_List[index]))
						continue;
					if (index == old_index)
						continue;

					if (Field_List[index] -> x_pos >
						Field_List[old_index] -> x_pos)
					{
						if (match == old_index)
						{
							match = index;
							continue;
						}
						if (Field_List[index] -> x_pos > Field_List[match] -> x_pos)
							continue;
						if (closer (Field_List[index],
								Field_List[match],
								Field_List[old_index]))
							match = index;
					}
				}
				index = match;
				continue;

			case CMLEFT: 
				old_index = index;
				match = index;
				line = Field_List[index] -> x_pos;
				index = -1;
				while (TRUE)
				{
					index++;
					if (index == Count)
					{
						if (match != old_index)
							break;
						err_str = "Cannot move LEFT to another field at this time.";
						index = old_index;
						goto Cmbtab;
					}
					if (gl_touchedp (Field_List[index]))
						continue;
					if (index == old_index)
						continue;
					line = Field_List[match] -> x_pos;
					if (Field_List[index] -> x_pos ==
						Field_List[old_index] -> x_pos)
					{
						if (match != old_index && Field_List
							[index] -> y_pos <= 
							Field_List[match] -> y_pos)
							continue;
						if (Field_List[index]->y_pos <
						Field_List[old_index]->y_pos)
						{
							match = index;
						}
					}
				}
				index = match;
				continue;

			case CMRIGHT: 
				old_index = index;
				match = index;
				line = Field_List[index] -> x_pos;
				index = -1;
				while (TRUE)
				{
					index++;
					if (index == Count)
					{
						if (match != old_index)
							break;
						index = old_index;
						err_str = "Cannot move RIGHT to another field at this time.";
						goto Cmftab;
					}
					if (gl_touchedp (Field_List[index]))
						continue;
					if (index == old_index)
						continue;
					line = Field_List[match] -> x_pos;
					if (Field_List[index] -> x_pos ==
						Field_List[old_index] -> x_pos)
					{
						if (match != old_index &&
							Field_List[index]->y_pos >
							Field_List[match]->y_pos)
							continue;
						if (Field_List[index]->y_pos >
						Field_List[old_index]->y_pos)
						{
							match = index;
						}
					}
				}
				index = match;
				continue;

			case CMMOUSE: 	/* Smallest X squared + Y squared */
				last_value = 32000;
				match = index;
				old_index = index;
				for (index = 0; index < Count; index++)
				{
					if (gl_touchedp (Field_List[index]))
						continue;
					if (Field_List[index] -> x_pos < 0)
						continue;
					if (Field_List[index] -> x_pos >= 512)
						continue;
					if (Field_List[index] -> window -> _depth >= INVISIBLE)
						continue;

					/* convert to absolute coordinates */
					mouse_x = FIELD_X + Field_List[index] -> window -> _top_x;
					mouse_y = FIELD_Y + Field_List[index] -> window -> _top_y;
					if (Field_List[index] -> type == CMREGN)
					{
						line = 0;
					}
					else
					{
						line = Field_List[index] -> length;
						for (xstart = mouse_y, vis = FALSE,
						    kptr = &kmap[mouse_x][mouse_y],
						    key = Field_List[index] -> window -> _key;
						    		xstart <= mouse_y + line; xstart++)
						{
							if (key & *kptr++)
							{
								vis = TRUE;
								break;
							}
						}
						if (vis == FALSE)
							continue;
					}
					if (in_field (Field_List[index], 
						MOUSE_X - Field_List[index] -> window -> _top_x,
						MOUSE_Y - Field_List[index] -> window -> _top_y))
					{
						match = index;
						break;
					}
					x = mouse_x - MOUSE_X;
					/* check distance to beginning of field */
					y = mouse_y - MOUSE_Y;
					x = (x*2)*(x*2);
					value = x + y * y;
					if (value < last_value)
					{
						match = index;
						last_value = value;
					}

					/* check distance to end of field */
					y += line;
					value = x + y * y;
					if (value < last_value)
					{
						match = index;
						last_value = value;
					}

					/* check distance to middle of field */
					y -= line/2;
					value = x + y * y;
					if (value < last_value)
					{
						match = index;
						last_value = value;
					}
				}
				index = match;
				if (index == old_index)
				{
					if ((ok_to_back) && (index == 0))
					{
						POP_ARGS();
						return (CMUP);
					}
					if ((ok_to_forward) &&
						(index == (Count - 1)))
					{
						POP_ARGS();
						return (CMDOWN);
					}
				}
				continue;

			case CMBTAB: 
				err_str = "Cannot move BACK to another field at this time.";
Cmbtab:
				old_index = index;
				index--;
				if (index < 0)
				{
					if (ok_to_back)
					{
						POP_ARGS();
						return (rc);
					}
					index = old_index;
					beep ();
					Print_Message (Field_List[index] -> meswin, Mess_Attribute,
							err_str);
					goto Next_Field;
				}
				while (gl_touchedp (Field_List[index]))
				{
					index--;
					if (index < 0)
					{
						index = old_index;
						beep ();
						Print_Message (Field_List[index] -> meswin, Mess_Attribute,
								err_str);
						goto Next_Field;
					}
				}
				continue;

			case CMFTAB: 
				err_str = "Cannot move FORWARD to another field at this time.";
Cmftab:
				old_index = index;
				index++;
				if (index >= Count)
				{
					if (ok_to_forward)
					{
						POP_ARGS();
						return (rc);
					}
					index = old_index;
					beep ();
					Print_Message (Field_List[index] -> meswin, Mess_Attribute,
							err_str);
					goto Next_Field;
				}
				while (gl_touchedp (Field_List[index]))
				{
					index++;
					if (index >= Count)
					{
						index = old_index;
						beep ();
						Print_Message (Field_List[index] -> meswin, Mess_Attribute,
								err_str);
						goto Next_Field;
					}
				}
				continue;

			default: 
				index++;
		}
	}
	POP_ARGS();
	return (0);
}

gl_touchedp (field_ptr)
struct field_item *field_ptr;
{
	return ((field_ptr -> txflg & TXONET) &&
			((field_ptr -> txbuf[0] != '\0') ||
			 ((field_ptr -> cmflg & CMABU) == 0)));
}

Show_List (Field_List, Count)
register struct field_item     *Field_List[];
int     Count;
{
	struct field_item **f;

	ReShow_List( Field_List, Count, TRUE );
}

static int
closer (f1, f2, standard)
register struct field_item *f1;
register struct field_item *f2;
register struct field_item *standard;
{
	int a;
	int b;

	a = overlap (f1, standard);
	b = overlap (f2, standard);

	if ((a == 0) && (b == 0))
	{
		return (abs (f1 -> y_pos  - standard -> y_pos) <=
			abs (f2 -> y_pos  - standard -> y_pos));
	}

	return (a >= b);
}

static int
overlap (f1, f2)
struct field_item *f1;
struct field_item *f2;
{
	register int a, b, c, d;

	a = f1 -> y_pos;
	b = a + f_length (a, f1 -> fill_char);

	c = f2 -> y_pos;
	d = c + f_length (c, f2 -> fill_char);

    if ((a < c) && (b < c))
    	return (0);
    if ((a > d) && (b > d))
    	return (0);

	if (a < c)
		a = c;
	if (b > d)
		b = d;

	return (b - a);
}
