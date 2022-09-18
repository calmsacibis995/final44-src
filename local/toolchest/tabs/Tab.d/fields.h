/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
 /* Expensive but fast */
#define boole	int

#ifndef TRUE
#define TRUE	1
#define FALSE	0
#endif

struct field_item
{
	int	x_pos;			/* Field location within the window  */
	int	y_pos;
	int     (*type) ();		/* Field type			     */
	int	(*type_used) ();	/* Field type used when fnalts exist */
	int     length;			/* Length in characters of the field */
	char   *fill_char;		/* Blank fill character mask	     */
	char   *ext_fill_char;		/* Field extension fill_char	     */
	char   *keywords;		/* Keyword list for keyword fields   */

	struct window  *window;		/* Stdout window		     */
	struct window  *errwin;		/* Error window			     */
	struct window  *meswin;		/* Quick Message window		     */

	int     attribute;		/* Visual attributes and formatted   */
	int     user_mask;		/* User Mask for use by application  */
	char	*user_pointer;		/* Pointer for use by the application*/

	int     (*read_routine) ();	/* Routine used to read input	     */
	int     (*pre_action) ();	/* Pre-action routine		     */
	int     (*post_action) ();	/* Post-action routine		     */
	int     (*help_routine) ();	/* Help Routine			     */

	int     txflg;			/* Texti () flags		     */
	char   *txbuf;			/* Text buffer			     */
	char   *txend;			/* End of text buffer		     */
	char   *txptr;			/* Text pointer			     */
	char   *txcursor;		/* Text cursor - character position  */

	int     fnflg;			/* Function flags		     */
	char   *fnhlp;			/* Help string			     */
	char   *fnerr;			/* Error message string		     */
	char   *fndfs;			/* Default string		     */
	int     fndfv;			/* Default value		     */
	struct field_item      *fnalt;	/* Alternate field description	     */

	int     cmflg;			/* getam flags - MUST be 32 bits     */

	struct label_item *label;
	char	_field_check;	/* Sanity check */
};

struct label_item
{
	char where;
	char _label_check;	/* Sanity check */
	char *string;
	int  attribute;
	struct label_item *next;
};

struct keys
{
	char   *kstr;			/* Keyword string		     */
	int     kval;			/* Value to return on a match	     */
};

struct break_item
{
	char which;
	struct break_item *next;
};

/*	Structure for accessing the values from the expansion routine	     */
/*	from Bourne							     */
struct argnod
{
	struct argnod *argnxt;		/* Pointer to next argnod	     */
	char   argval[1];		/* Pointer to file name		     */
};

 /* Sanity check value - must fit in a char - every other bit */
#define GOOD_FIELD	0125

 /* Standard buffer size for forms */
#define FORM_BUF	256

 /* MAX number of keys for keyword fields */
#define MAX_KEYS	128

 /* Field Attributes - visual and for USER formatting */
#define FANORMAL	0

#define FARIGHT		01
#define FACENTER	02
#define FALEFT		04
#define FACASE		010		/* Caseless comparisons for keywords */
#define FAPROTECT	020		/* Protected field		     */
#define FAFIELD		VT_AREA		/* writing to a field		     */

#define FAUNDER		VT_UNDER	/* A_UNDERLINE from curses	     */
#define FABLINK		VT_BLINK	/* A_BLINK from curses		     */
#define FAREVV		VT_REVV		/* A_REVERSE from curses	     */
#define FAHALF		VT_HALF		/* A_DIM from curses		     */
#define FABOLD		VT_BOLD		/* A_BOLD from curses		     */
#define FAINVISIBLE	VT_INVISIBLE	/* A_INVISIBLE from curses	     */
#define FAALTCHAR	VT_ALTCHAR	/* A_ALTCHARSET from curses	     */

 /* Flag bits in TXFLG */
#define	TXEOF	01			/* Set by TEXTI on end of file	     */
#define	TXBRK	02			/* Set by TEXTI on break char	     */
#define	TXBLR	04			/* Set by TEXTI if backup>txbuf	     */
#define	TXAUTO	010			/* Tell's TEXTI auto EOL full fields */
#define	TXBTAB	020			/* Back Tab used for movement	     */
#define	TXBTVFY	040			/* Verify on Back Tab movement	     */
#define TXCPM	0100			/* Allow cursor pad and mouse keys   */
#define TXCPVFY	0200			/* Verify cursor pad movement	     */
#define TXONET	0400			/* Don't re-enter the field	     */
#define TXSEOF	01000			/* Allow eof for exiting the field   */
#define TXEFVFY	02000			/* Verify eof when exiting the field */
#define TXEXT	04000			/* Extend field when reach end       */

 /* Flag bits in FNFLG */
#define	FNHLP	01			/* User help message supplied	     */
#define	FNSDH	02			/* Suppress default help message     */
#define	FNDEF	04			/* Default supplied		     */
#define	FNALT	010			/* Alternative supplied		     */
#define FNHLST	020			/* Help output in cols ~rows	     */
#define FNHPAGE	040			/* Help output is to be paged	     */
#define FNSNUC	0100			/* Stop on non-unique chains	     */
#define FNLINK	0200			/* Linked Field			     */
#define FNLNSZ	8
#define FNLNMSK	0377

 /* Help Flags for Internal Comnd/Prhlp Use */
#define HLP_OPTIONS	1
#define HLP_OR		2

 /* Character types for fields */
#define	NORMAL	0			/* Normal character		     */
#define	PUNC	1			/* Punctuation character	     */
#define	BREAK	2			/* Break character		     */
#define	CORRECT	3			/* Correction character		     */
#define	DSCARD	4			/* Characters to ignore		     */

 /* Flag bits in CMFLG */
#define CMNORM	0
#define	CMNOP	01			/* Parse failed			     */
#define	CMREP	02			/* Reparsing required		     */
#define	CMHLP	04			/* Help message requested	     */
#define	CMCMP	010			/* Command completion requested	     */
#define	CMEOL	020			/* End of input line reached	     */
#define	CMABO	040			/* Scratch storage overflow	     */
#define CMIBO	0100			/* Input buffer has overflowed	     */
#define CMABU	0200			/* Atom buffer unused		     */
#define	CMEOF	0400			/* EOF on standard input	     */
#define CMNUQ	01000			/* Not a Unique Atom		     */
#define CMFTAB	02000			/* Tab (forward field)		     */
#define CMBTAB	04000			/* Back Tab (forward field)	     */

#define CMHOME	010000			/* HOME function key		     */
#define CMBOTTOM 020000			/* BOTTOM function key		     */
#define CMUP	040000			/* UP function key		     */
#define CMDOWN	0100000			/* DOWN function key		     */
#define CMLEFT	0200000			/* LEFT function key		     */
#define CMRIGHT	0400000			/* RIGHT function key		     */
#define CMMOUSE	01000000		/* MOUSE or touch screen	     */

#define CMTAMPR	02000000		/* Field tampered (i.e. Set_Def*())  */
#define CMVERIFY 04000000		/* Field was verified in comnd */

 /* Builtin field types */
extern int cmini ();
extern int cmkey ();
extern int cmkey_list ();
extern int cmcfm ();
extern int cmcfm2 ();
extern int cmstr ();
extern int cmnum ();
extern int cmfile ();
extern int cmenv ();

 /* Builtin read routines */
extern int getachar ();
extern int read_num ();

typedef int (*PFI) ();
#define	CMINI	cmini			/* Initialize command parsing	     */
#define	CMKEY	cmkey			/* Parse a keyword		     */
#define	CMKEY_LIST	cmkey_list	/* Parse a keyword		     */
#define	CMCFM	cmcfm			/* Confirm a command (new line)	     */
#define	CMCFM2	cmcfm2			/* Internal Confirm tab or new line  */
#define	CMSTR	cmstr			/* Accept an arbitrary string	     */
#define	CMNUM	cmnum			/* A decimal number		     */
#define	CMFILE	cmfile			/* A file specification		     */
#define	CMENV	cmenv			/* An environmental variable	     */
#define	CMREGN	((PFI)19)		/* NOT a FIELD - Scrollable Region   */

 /* BREAK character list types */
#define CM_LIST		1
#define BTAB_LIST	2
#define TAB_LIST	3
#define CFM_LIST	4
#define EOF_LIST	5
#define UTIL_LIST	6

 /* Controlify Function */
#define CTRL(x)		('x' & 037)

 /* Misc. characters that have a common meaning in more than one place */
#ifndef ESC
#define	ESC		033
#endif
#define	SPACE		040
#define	NL		CTRL(J)
#define	CRET		CTRL(M)
#define	TABC		CTRL(I)
#define	FTABC		CTRL(N)
#define	BTABC		CTRL(P)
#define	CLEARC		CTRL(C)
#define	REFRESHC	CTRL(V)

 /* Extra bit for malloc's */
#ifndef MXTRA
#define MXTRA	8
#endif

 /* Size of the Expansion Buffer - Allocated the first time it is used */
#define EXP_BUFFER	(8*1024)

 /* Display the first SHOW_FILES matches upon a help request */
#define SHOW_FILES	64

 /* Entry_Type Values */
#define FAR_RIGHT	0
#define FAR_LEFT	1

 /* Editing_Type Values */
#define INSERT		0
#define OVERLAY		1

struct arg_stack
{
	struct	field_item	**f;
	int	count;
	int    *ptr_index;
	int    *ptr_rc;
	struct	arg_stack	*next;
	struct	arg_stack	*previous;
};
extern struct arg_stack	*GL_Arg_Stack;

extern int	Auto_Position;	/* positioning flag for txcursor within field */

 /* Expand Globals */
extern struct argnod   *gchain;
extern int  cnt_gchain;

extern jmp_buf lab_com_re;		/* Longjump storeage		     */
#define	reset()		longjmp(lab_com_re, 1)
#define	setexit()	setjmp(lab_com_re)

extern struct break_item *cm_list;	/* Break characters lists	     */
extern struct break_item *btab_list;
extern struct break_item *tab_list;
extern struct break_item *cfm_list;
extern struct break_item *eof_list;
extern struct break_item *punc_list;

extern struct break_item *remove_brk_item ();
extern struct break_item *insert_brk_item ();

extern char     chartyp[];		/* A table of character types	     */
extern int regchar ();			/* Bulitin character interpreters    */
extern int corchar ();
extern int brkchar ();
extern PFI     f_chartyp[];		/* A table of character interpreters */

extern struct window   *stdwindow;	/* Standard windows for fields	     */
extern struct window   *errwindow;

extern char *error_fields;		/* Error message for clean_err ()    */

extern int MOUSE_BUTTON;		/* Mouse facts - only when CMMOUSE   */
extern int MOUSE_X;
extern int MOUSE_Y;
extern int MOUSE_TYPE;

extern int (*Glbl_pre_action) ();	/* Global pre & post action routines */
extern int (*Glbl_post_action) ();

/* Most of the other routines are voids posing as ints */
extern struct field_item       *New_Field ();
extern struct field_item       *Dup_Field ();
extern struct field_item       *New_Scroll_Region();

/* Sanity Values */
extern struct field_item *_F_Field;
extern struct field_item *_L_Field;
extern struct label_item *_F_Label;
extern struct label_item *_L_Label;

/* Editing type */
extern int _Editing_Type;

/* Enter fields at the front or back */
extern int _Entry_Type;

/* Position cursor where last used within the field (where txcursor set) */
extern int Auto_Pos;

/* Auto Position cursor one time only */
extern int	Keep_Cursor_Pos;

/* field_list pointers */
extern struct arg_stack	*GL_Arg_Stack;

/* Overflow action for texti() */
extern int (*Glbl_Overflow_Action) ();

/* Attribute for error messages */
extern int	Mess_Attribute;

/* String for how to get help */
extern char	*Help_Help_String;

/* linked list for line in scratchpad, editor, etc. */
struct line
{
	struct line	*next;
	struct line	*previous;
	char	*txbuf;
};

/* Automatic positioning arguments */
#define C_NOADJ		00
#define C_RIGHT		01
#define C_SKIPCOL	02
#define C_CENTER	03
#define C_SKIPCEN	04
#define C_STARTROW	05
#define C_SKIPROW	06
