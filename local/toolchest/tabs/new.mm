.ds HF 3 3 3 3 3 3
.nr Hb 6
.nr Cl 5
.de cW
.ie \\n(.$ .nr ;G \\n(.f
.el .ft CW
.if \\n(.$ .if !\\n(.$-2 \&\f(CW\\$1\fP\\$2
.if \\n(.$-2 \{.ds }i
.if \\n(.f 2 .ds }i \^
.ds }I \&\f(CW\\$1\fP\\$2\\*(}i
'br\}
.if \\n(.$-2 .if !\\n(.$-4 \\*(}I\f(CW\\$3\fP\\$4
.if \\n(.$-4 .if !\\n(.$-6 \\*(}I\f(CW\\$3\fP\\$4\\*(}i\f(CW\\$5\fP\\$6
.if \\n(.$ .ft \\n(;G
..
.de CW
.DS L N
.cW
..
.de CN
.DE
.R
..
.PF "'Copyright (c) 1984, 1985, 1986, 1987''AT&T All Rights Reserved'"
.H 2 "Defining Character Directives for Inter-Field Editing and Control"
.P
This section describes how to create characters actions
that result in inter-field interaction or movement.
Page-up and page-down characters for scrollable regions are examples of
this type of character.
The following example contains character-action and post-action
routines that define CTRL(U) and CTRL(D) to do page-up and
page_down.
The scrollable region field,
.I reg_field,
can be created the same way f[2] is
created in Appendix F.
Only the relevant portions of the main routine are shown here.
.CW
main()
{
	...
	Def_Char_Action (CTRL(D), BREAK, mybrkchar, CM_LIST);	/* Page Down */
	Def_Char_Action (CTRL(U), BREAK, mybrkchar, CM_LIST);	/* Page Up */
	...
	/* create scrollable region field, reg_field */
	...
	Set_Actions (reg_field, 0, reg_post); /* set pre/post action routines */
	...
	/* display field(s) and collect user's response(s) */
	...
}
.CN
.CW
/*
 *	This is a sample BREAK character action routine.
 *	It uses the standard Tabs brkchar() routine to set the appropriate
 *	flags, etc.  All BREAK routines should return TRUE.
 */

mybrkchar (field_ptr, rc)
struct field_item *field_ptr;
char    rc;
{
	switch (rc)
	{
	case CTRL(U):	/* Page Up */
		brkchar (field_ptr, K_HOME);
		field_ptr -> user_mask = CTRL(U);
		break;
	case CTRL(D):	/* Page Down */
		brkchar (field_ptr, K_HOME);
		field_ptr -> user_mask = CTRL(D);
		break;
	default:
		brkchar (field_ptr, rc);
	}

	return (TRUE);
}
.CN
.CW
/*
 *	This is a sample post action routine.  The return value (int) is 
 *	the index of the next field to be read.  An index of -1 indicates 
 *	that the current field should be re-read.
 */
#define REPEAT -1    /* repeat a character */
#define NUM_LINES 4  /* number of lines to scroll the region */

reg_post (f, count, index, rc)
struct field_item     **f;
int     count;
int index;
int     rc;
{
	int new_index;

	switch (f[index] -> user_mask)	/* Oh those side effects!!! */
	{
	case CTRL(U):	/* Page Up */
		new_index = index - NUM_LINES;
		break;
	case CTRL(D):	/* Page Down */
		new_index = index + NUM_LINES;
		break;
	default:
		return (index);
	}
	f[index] -> user_mask = 0;
	if (new_index < 0)              /* above top? */
		new_index = 0;
	if (new_index >= count)         /* below bottom? */
		new_index = count - 1;
	if (new_index == index)         /* same field? */
		new_index = REPEAT;
	return (new_index);
}
.CN
.P
Both character-action and post-action routines are necessary because
the BREAK character entered by the user is normally not known in a post-action
routine.
Here ``mybrkchar'' sets 
.I user_mask
in the 
.I field_item
structure (see 
.I "The Field Structure"
below) to the appropriate BREAK character.
The post-action routine then uses this value to determine whether to
page up or down.
This use of 
.I user_mask 
is quite straightforward.
The interesting parts are the calls to brkchar() in mybrkchar().
.P
The way we recommend to write a BREAK character action routine is to model
the new BREAK character after another BREAK character.
That is, find a BREAK character that does something similar to what you
want to do then call brkchar() with that character as an argument
so that the appropriate flags are set, etc.
.P
But why use K_HOME in this instance?
One might expect that calling brkchar() with K_HOME would
cause CTRL(D) and CTRL(U) to have the same action as K_HOME.
Instead, they page the scrollable region.
How is this possible?
To answer this question we have to understand why the above example
works.
The following reduces the flow of control, function calls and
arguments in Tabs to only what is needed to understand this example.
.CW
Get_List (field_list)   /* controls inter-field movement and editing */
{
	next = 0;
	while (next < count)
	{
		index = next;
		ret_code = Get_Field (field_list[index]);
		if (post_action) /* e.g.,  reg_post */
			next = post_action (ret_code,index); 
		if (next == index)
			/* determine ``next'' from ret_code and field_flags*/
	}
}
.CN
.CW
Get_Field (field)   /* controls intra-field movement and editing */.
{
	while (TRUE)
	{
		ch = read_a_char();
		flag = character_action(); /* e.g. mybrkchar */
		if (flag == TRUE)
		{
			switch (some_variable) 
			{
			...
			
			case K_HOME:
				/* set field_flags and ret_code */
				return (ret_code);
			...
			}
		}
	}
}
.CN
.P
Assume the end-user has just entered a CTRL(D) and 
read_a_char()
returns it.
mybrkchar()
is then called as the character action routine.
.I user_mask
is set to CTRL(D), the field_dependent flags
are set appropriately for K_HOME and mybrkchar() returns TRUE.
The return code is determined in Get_Field() based 
on the fact that brkchar() was called with K_HOME as an argument.
Get_Field() returns to Get_List() with the appropriate return code
for K_HOME.
.P
Get_List() then calls
reg_post().
Ann index to the next field is returned.
If the index to the next field is not equal to the current index,
the return code and field flags (appropriate for K_HOME
in this instance) have no effect.
.I brkchar
actions have a lower priority than
those of post-action routines.
The reg_post() routine takes advantage of this so that 
CTRL(D) and CTRL(U) will page and
K_HOME will not have its normal effect if the suer_mask has been set.
That is, if a CTRL(D) or CTRL(U) has been entered by the user,
reg_post() always returns an index that is different from the one that
is passed to it, the index to the current field.
.P
K_HOME is only one type of BREAK character.
See the description of Def_Char_Action() for the complete list of standard
BREAK characters and break character types.
K_HOME was used as the model because it caused
control to be moved to another field within the same list of fields.
K_DOWN, K_UP, etc. would have been just as good a model.
.P
The type of interactions action routines shown here can be used
between character-action routines and any type of pre-action or post-action
routine.
This extensibility provides a powerful mechanism for creating a wide 
variety of special character directives.
