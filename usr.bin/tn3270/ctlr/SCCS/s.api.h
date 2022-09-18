h62357
s 00002/00002/00375
d D 8.1 93/06/06 16:39:18 bostic 23 22
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00013/00374
d D 4.4 91/04/26 15:40:43 bostic 22 21
c new copyright; att/bsd/shared
e
s 00002/00002/00385
d D 4.3 89/09/23 16:08:20 minshall 21 20
c This version works for i386 sequent's and for mips (like 3100) 
c (I'm hoping the mips stuff with MIPSEB and MIPSEL is correct...)
e
s 00022/00004/00365
d D 4.2 89/02/06 19:07:53 minshall 20 19
c Re-do the byte ordering thing, using the new macros if available.
e
s 00000/00000/00369
d D 4.1 88/12/04 15:12:04 minshall 19 18
c Release 4.1
e
s 00021/00015/00348
d D 3.5 88/08/28 17:57:56 minshall 18 17
c Lint (and, maybe, copyrights).
e
s 00010/00005/00353
d D 3.4 88/06/29 19:49:43 bostic 17 16
c install approved copyright notice
e
s 00014/00002/00344
d D 3.3 88/03/28 12:34:10 bostic 16 15
c add Berkeley specific header
e
s 00001/00001/00345
d D 3.2 88/01/05 15:01:31 minshall 15 14
c Changes for pyramid from sbanner1@cheops (S. John Banner).
e
s 00000/00000/00346
d D 3.1 87/08/11 10:18:41 minshall 14 13
c New version numbering.
e
s 00002/00000/00344
d D 1.13 87/07/17 10:03:15 minshall 13 12
c Install sccs headers and copyright notices.
e
s 00003/00003/00341
d D 1.12 87/07/09 10:40:09 minshall 12 11
c 1.  Fix (signed) char bug.  2.  Add in ibm032 to rational machines.
e
s 00010/00001/00334
d D 1.11 87/06/16 17:20:28 minshall 11 10
c Add PS_OR_OIA_MODIFIED (in the Unix environment).
e
s 00012/00000/00323
d D 1.10 87/06/15 23:33:38 minshall 10 9
c Add new machine types (tahoe, sun).  RT is missing.
e
s 00016/00009/00307
d D 1.9 87/06/15 09:21:00 minshall 9 8
c Mostly make 8086 register pieces unsigned.
e
s 00009/00006/00307
d D 1.8 87/05/25 16:27:35 minshall 8 7
c Various fixes.  No copy string yet, though.
e
s 00003/00000/00310
d D 1.7 87/05/24 16:50:39 minshall 7 6
c Fix "write_keystroke" (untested).
e
s 00008/00094/00302
d D 1.6 87/05/24 14:36:08 minshall 6 5
c New OIA.
e
s 00055/00001/00341
d D 1.5 87/05/22 12:00:41 minshall 5 4
c This version compiles on the PC.
e
s 00002/00002/00340
d D 1.4 87/05/21 21:29:58 minshall 4 3
c This version compiles.
e
s 00309/00012/00033
d D 1.3 87/05/21 20:40:49 minshall 3 2
c A version (probably doesn't even compile).
e
s 00006/00000/00039
d D 1.2 87/05/21 11:28:03 minshall 2 1
c A version.
e
s 00039/00000/00000
d D 1.1 87/05/20 15:33:46 minshall 1 0
c date and time created 87/05/20 15:33:46 by minshall
e
u
U
t
T
I 1
D 22
/*
D 16
 * This file contains header information used by the PC API routines.
E 16
I 16
 * Copyright (c) 1988 Regents of the University of California.
E 22
I 22
/*-
D 23
 * Copyright (c) 1988 The Regents of the University of California.
E 22
 * All rights reserved.
E 23
I 23
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 23
E 16
I 13
 *
D 16
 * %W% (Berkeley) %G%
E 16
I 16
D 22
 * Redistribution and use in source and binary forms are permitted
D 17
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 17
I 17
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 22
I 22
 * %sccs.include.redist.c%
E 22
E 17
 *
 *	%W% (Berkeley) %G%
 */

/*
 * This file contains header information used by the PC API routines.
E 16
E 13
 */

I 5
#if	!defined(MSDOS)
#define far			/* For 'far *' checks */
#endif	/* !defined(MSDOS) */

E 5
#define	API_INTERRUPT_NUMBER	0x7A		/* API Interrupt Number */

/*
 * Define the gate numbers.  These are returned via the Name Resolution
 * service.
 */

D 8
#define	GATE_SESSMGR	1
#define	GATE_KEYBOARD	2
#define	GATE_COPY	3
#define	GATE_OIAM	4
E 8
I 8
#define	GATE_SESSMGR	1234
#define	GATE_KEYBOARD	5678
#define	GATE_COPY	9101
#define	GATE_OIAM	1121
E 8

I 2
D 3
#define	NAME_SESSMGR	"SESSMGR"
E 3
I 3
/*
 * The names which correspond to the above gate numbers.
 */

#define	NAME_SESSMGR	"SESSMGR "
E 3
#define	NAME_KEYBOARD	"KEYBOARD"
D 3
#define	NAME_COPY	"COPY"
#define	NAME_OIAM	"OIAM"
E 3
I 3
#define	NAME_COPY	"COPY    "
#define	NAME_OIAM	"OIAM    "
E 3


E 2
/*
 * Name Resolution is specified in AH.
 */

D 11
#define	NAME_RESOLUTION	0x81
E 11
I 11
#define	NAME_RESOLUTION		0x81

#if	defined(unix)
/*
 * In unix, we offer a service to allow the application to keep from
 * having to poll us constantly.
 */
#define	PS_OR_OIA_MODIFIED	0x99

#endif	/* defined(unix) */
E 11

/*
 * Codes specified in AL for various services.
 */

D 3
#define	QUERY_SESSION_ID	0x01
#define	QUERY_SESSION_PARMS	0x02
#define	QUERY_SESSION_CURSOR	0x0b
E 3
I 3
#define	QUERY_SESSION_ID		0x01
D 8
#define	QUERY_SESSION_PARMS		0x02
E 8
I 8
#define	QUERY_SESSION_PARAMETERS	0x02
E 8
#define	QUERY_SESSION_CURSOR		0x0b
E 3

D 3
#define	CONNECT_TO_KEYBOARD	0x01
E 3
I 3
#define	CONNECT_TO_KEYBOARD		0x01
E 3
#define	DISCONNECT_FROM_KEYBOARD	0x02
D 3
#define	WRITE_KEYSTROKE		0x04
#define	DISABLE_INPUT		0x05
#define	ENABLE_INPUT		0x06
E 3
I 3
#define	WRITE_KEYSTROKE			0x04
#define	DISABLE_INPUT			0x05
#define	ENABLE_INPUT			0x06
E 3

D 3
#define	COPY_STRING		0x01
E 3
I 3
#define	COPY_STRING			0x01
E 3

D 3
#define	READ_OIA_GROUP		0x02
E 3
I 3
#define	READ_OIA_GROUP			0x02

/*
 * For each service, we define the assoicated parameter blocks.
 */

/*
 * Supervisor Services
 */

typedef struct {
    char	gate_name[8];
} NameResolveParms;


/*
 * Session Information Services
 */

typedef struct {
    char
	short_name,
	type,
	session_id,
	reserved,
	long_name[8];
} NameArrayElement;

typedef struct {
D 12
    char
E 12
I 12
    unsigned char
E 12
	length,
	number_matching_session;
    NameArrayElement
	name_array_element;		/* Variable number */
} NameArray;

typedef struct {
    char
	rc,
	function_id,
	option_code,
	data_code;
    NameArray far
	*name_array;
    char
	long_name[8];
} QuerySessionIdParms;

I 8
#define	ID_OPTION_BY_NAME	0x01		/* By short (or long) name */
#define	ID_OPTION_ALL		0x00		/* All (of specified type */

E 8
typedef struct {
    char
	rc,
	function_id,
	session_id,
	reserved,
	session_type,
	session_characteristics,
	rows,
	columns;
    char far
	*presentation_space;
D 4
} QuerySessionParmetersParms;
E 4
I 4
} QuerySessionParametersParms;
E 4

#define	TYPE_WSCTL		0x01		/* Work Station Control */
#define	TYPE_DFT		0x02		/* DFT Host Session */
#define	TYPE_CUT		0x03		/* CUT Host Session */
#define	TYPE_NOTEPAD		0x04		/* Notepad Session */
#define	TYPE_PC			0x05		/* Personal Computer Session */

#define	CHARACTERISTIC_EAB	0x80		/* Extended Attribute Buffer */
#define	CHARACTERISTIC_PSS	0x40		/* Program Symbols Supported */

typedef struct {
    char
	rc,
	function_id,
	session_id,
	cursor_type,
	row_address,				/* from 0 */
	column_address;				/* from 0 */
} QuerySessionCursorParms;

#define	CURSOR_INHIBITED_AUTOSCROLL	0x10
#define	CURSOR_INHIBITED		0x04
#define	CURSOR_BLINKING			0x02
#define	CURSOR_BOX			0x01
typedef struct {
    char
	rc,
	function_id,
	session_id,
	reserved;
D 18
    int
E 18
I 18
    short
E 18
	event_queue_id,
	input_queue_id;
    char
	intercept_options,
	first_connection_identifier;
} ConnectToKeyboardParms;

typedef struct {
    char
	rc,
	function_id,
	session_id,
	reserved;
D 18
    int
E 18
I 18
    short
E 18
D 4
	connector_task_id;
E 4
I 4
	connectors_task_id;
E 4
} DisconnectFromKeyboardParms;

typedef struct {
D 18
    char
E 18
I 18
    unsigned char
E 18
	scancode,
	shift_state;
} KeystrokeEntry;

typedef struct {
D 18
    int
E 18
I 18
    short
E 18
	length;			/* Length (in bytes) of list */
    KeystrokeEntry keystrokes;	/* Variable size */
} KeystrokeList;

typedef struct {
    char
	rc,
	function_id,
	session_id,
	reserved;
D 18
    int
E 18
I 18
    short
E 18
	connectors_task_id;
    char
	options,
	number_of_keys_sent;
    union {
	KeystrokeEntry
	    keystroke_entry;
	KeystrokeList far
	    *keystroke_list;
    } keystroke_specifier;
} WriteKeystrokeParms;

I 7
#define	OPTION_SINGLE_KEYSTROKE		0x20
#define	OPTION_MULTIPLE_KEYSTROKES	0x30

E 7
typedef struct {
    char
	rc,
	function_id,
	session_id,
	reserved;
D 18
    int
E 18
I 18
    short
E 18
	connectors_task_id;
} DisableInputParms;

typedef DisableInputParms EnableInputParms;

typedef struct {
    char
	session_id,
	reserved;
    char far
	*buffer;
    char
	characteristics,
	session_type;
D 18
    int
E 18
I 18
    short
E 18
	begin;			/* Offset within buffer */
} BufferDescriptor;
    
typedef struct {
    char
	rc,
	function_id;
    BufferDescriptor
	source;
D 18
    int
E 18
I 18
    short
E 18
	source_end;		/* Offset within source buffer */
    BufferDescriptor
	target;
    char
	copy_mode,
	reserved;
} CopyStringParms;

#define	COPY_MODE_7_COLOR		0x80	/* Else 4 color mode */
#define	COPY_MODE_FIELD_ATTRIBUTES	0x40	/* Else don't copy attributes */

typedef struct {
    char
	rc,
	function_id,
	session_id,
	reserved;
    char far
	*oia_buffer;
    char
	oia_group_number;
} ReadOiaGroupParms;

D 6
#define	OIA_ALL_GROUPS				0xFF
#define	OIA_ONLINE_OWNERSHIP			0x01
#	define	OIA_SETUP		0x80
#	define	OIA_TEST		0x40
#	define	OIA_SSCP_LU		0x20
#	define	OIA_LU_LU		0x10
#	define	OIA_UNOWNED		0x08
#	define	OIA_SUBSYSTEM_READY	0x04
E 6
I 6
/* If the user wants all groups, we return API_OIA_BYTES_ALL_GROUPS bytes */
D 8
#define	API_OIA_ALL_GROUPS		0xFF
E 8
I 8
#define	API_OIA_ALL_GROUPS		'\377'
E 8
#define	API_OIA_BYTES_ALL_GROUPS	22	/* 22 bytes of data */
E 6

D 6
#define	OIA_CHARACTER_SELECTION			0x02
#	define	OIA_EXTENDED_SELECT	0x80
#	define	OIA_APL			0x40
#	define	OIA_KANA		0x20
#	define	OIA_ALPHA		0x10
#	define	OIA_TEXT		0x08
E 6
I 6
/* API_OIA_INPUT_INHIBITED is special.  It returns more than on byte of data */
#define	API_OIA_INPUT_INHIBITED		8
E 6

D 6
#define	OIA_SHIFT_STATE				0x03
#	define	OIA_NUMERIC		0x80
#	define	OIA_UPPER_SHIFT		0x40
E 6
I 6
#define	API_OIA_LAST_LEGAL_GROUP	18	/* Highest legal number */
E 6

D 6
#define	OIA_PSS_GROUP_1				0x04
#define	OIA_HIGHLIGHT_GROUP_1			0x05
#define	OIA_COLOR_GROUP_1			0x06
#	define	OIA_SELECTABLE		0x80
#	define	OIA_FIELD_INHERIT	0x40
E 6

D 6
#define	OIA_INSERT				0x07
#	define	OIA_INSERT_MODE		0x80
E 6

D 6
/* We define this to be a 'long' followed by a 'char' (5 bytes) */

#define	OIA_INPUT_INHIBITED			0x08

#	define	OIA_NON_RESETTABLE	0x80000000
#	define	OIA_SECURITY_KEY	0x40000000
#	define	OIA_MACHINE_CHECK	0x20000000
#	define	OIA_COMM_CHECK		0x10000000
#	define	OIA_PROGRAM_CHECK	0x08000000
#	define	OIA_RETRY		0x04000000
#	define	OIA_DEVICE_NOT_WORKING	0x02000000
#	define	OIA_DEVICE_VERY_BUSY	0x01000000

#	define	OIA_DEVICE_BUSY		0x00800000
#	define	OIA_TERMINAL_WAIT	0x00400000
#	define	OIA_MINUS_SYMBOL	0x00200000
#	define	OIA_MINUS_FUNCTION	0x00100000
#	define	OIA_TOO_MUCH_ENTERED	0x00080000
#	define	OIA_NOT_ENOUGH_ENTERED	0x00040000
#	define	OIA_WRONG_NUMBER	0x00020000
#	define	OIA_NUMERIC_FIELD	0x00010000

#	define	OIA_OP_UNAUTHORIZED	0x00008000
#	define	OIA_OP_UNAUTHORIZED_MIN	0x00004000
#	define	OIA_INVALID_DEAD_KEY_COMBO 0x00002000
#	define	OIA_WRONG_PLACE		0x00001000

#	define	OIA_MESSAGE_PENDING	0x00000080
#	define	OIA_PARTITION_WAIT	0x00000040
#	define	OIA_SYSTEM_WAIT		0x00000020
#	define	OIA_HARDWARE_MISMATCH	0x00000010
#	define	OIA_LOGICAL_TERM_NOT_CONF 0x00000008


#	define	OIA_AUTOKEY_INHIBIT	0x80
#	define	OIA_API_INHIBIT		0x40

#define	OIA_PSS_GROUP_2				0x09
#	define	OIA_PS_SELECTED		0x80
#	define	OIA_PC_DISPLAY_DISABLE	0x40

#define	OIA_HIGHLIGHT_GROUP_2			0x0a
#define	OIA_COLOR_GROUP_2			0x0b
#	define	OIA_SELECTED		0x80

D 5
#define	OIA_COMMUNICATION_ERROR_REMINDER	0x0c
E 5
I 5
#define	OIA_COMM_ERROR_REMINDER		0x0c
E 5
#	define	OIA_COMM_ERROR		0x80
#	define	OIA_RTM			0x40

#define	OIA_PRINTER_STATUS			0x0d
#	define	OIA_PRINT_NOT_CUSTOM	0x80
#	define	OIA_PRINTER_MALFUNCTION	0x40
#	define	OIA_PRINTER_PRINTING	0x20
#	define	OIA_ASSIGN_PRINTER	0x10
#	define	OIA_WHAT_PRINTER	0x08
#	define	OIA_PRINTER_ASSIGNMENT	0x04

#define	OIA_AUTOKEY_PLAY_RECORD_STATUS		0x10
#	define	OIA_PLAY		0x80
#	define	OIA_RECORD		0x40

#define	OIA_AUTOKEY_ABORT_PAUSE_STATUS		0x11
#	define	OIA_RECORDING_OVERFLOW	0x80
#	define	OIA_PAUSE		0x40

#define	OIA_ENLARGE_STATE			0x12
#	define	OIA_WINDOW_IS_ENLARGED	0x80



E 6
I 5
#if	defined(MSDOS)

#if	!defined(FP_SEG)
#include <dos.h>
#endif	/* !defined(FP_SEG) */

#else	/* defined(MSDOS) */

/*
 * These definitions are here to provide the descriptions of
 * some registers which are, normally, defined in <dos.h> on
 * a dos system.
 */

I 6
D 18
#define	FP_SEG(x)	(x)
#define	FP_OFF(y)	(y)
E 18
I 18
#define	FP_SEG(x)	((unsigned int)(((unsigned long)(x))>>16))
#define	FP_OFF(y)	((unsigned int)(((unsigned long)(y))&0xFFFF))
E 18
E 6

I 9
/*
I 18
 * Undo the preceeding.
 */

#define	SEG_OFF_BACK(x,y)	(((x)<<16)|(y))

/*
E 18
 * Now, it is somewhat of a pain, but we need to keep
 * 8086 conventions about which of the "highlow"'s map
 * into which of the "words".
 */

I 20
#include <sys/param.h>		/* Get ENDIAN from machine/endian.h */

/* Determine endian'ess (if necessary) */

#if	!(defined(BYTE_ORDER) && defined(BIG_ENDIAN))
#define	LITTLE_ENDIAN	1234	/* least-significant byte first (vax) */
#define	BIG_ENDIAN	4321	/* most-significant byte first (IBM, net) */

D 21
#if	defined(vax) || defined(ns32000)
E 21
I 21
#if	defined(vax) || defined(ns32000) || defined(i386) || (defined(mips)&&defined(MIPSEL))
E 21
#define	BYTE_ORDER	LITTLE_ENDIAN
#endif	/* defined(vax) || defined(ns32000) */ 

D 21
#if	defined(sun) || defined(tahoe) || defined(ibm032) || defined(pyr) || defined(gould)
E 21
I 21
#if	defined(sun) || defined(tahoe) || defined(ibm032) || defined(pyr) || defined(gould) || (defined(mips)&&defined(MIPSEB))
E 21
#define	BYTE_ORDER	BIG_ENDIAN
#endif	/* defined(sun) || defined(tahoe) || defined(ibm032) || defined(pyr) || defined(gould) */

#endif	/* !(defined(BYTE_ORDER) && defined(BIG_ENDIAN)) */

E 20
E 9
struct highlow {
D 9
    char
	ah,
E 9
I 9
    unsigned char
I 10
D 18
#if	defined(vax)
E 18
I 18
D 20
#if	defined(vax) || defined(ns32000)
E 20
I 20
#if	BYTE_ORDER == LITTLE_ENDIAN
E 20
E 18
E 10
E 9
	al,
D 9
	bh,
E 9
I 9
	ah,
E 9
	bl,
D 9
	ch,
E 9
I 9
	bh,
E 9
	cl,
D 9
	dh,
	dl;
E 9
I 9
	ch,
	dl,
	dh;
I 10
D 18
#endif	/* defined(vax) */
E 18
I 18
D 20
#endif	/* defined(vax) || defined(ns32000) */ 
E 18
D 12
#if	defined(sun) || defined(tahoe)
E 12
I 12
D 15
#if	defined(sun) || defined(tahoe) || defined(ibm032)
E 15
I 15
#if	defined(sun) || defined(tahoe) || defined(ibm032) || defined(pyr)
E 20
I 20
#endif	/* BYTE_ORDER == LITTLE_ENDIAN */
#if	BYTE_ORDER == BIG_ENDIAN
E 20
E 15
E 12
	ah,
	al,
	bh,
	bl,
	ch,
	cl,
	dh,
	dl;
D 12
#endif	/* defined(sun) || defined(tahoe) */
E 12
I 12
D 18
#endif	/* defined(sun) || defined(tahoe) || defined(ibm032) */
E 18
I 18
D 20
#endif	/* defined(sun) || defined(tahoe) || defined(ibm032) || defined(pyr) */
E 20
I 20
#endif	/* BYTE_ORDER == BIG_ENDIAN */
E 20
E 18
E 12
E 10
E 9
};

struct words {
D 9
    int
E 9
I 9
    unsigned short
E 9
	ax,
	bx,
	cx,
D 9
	dx,
E 9
I 9
	dx;
D 18
    unsigned int
E 18
I 18
    unsigned short
E 18
E 9
	si,
	di;
};

union REGS {
    struct highlow h;
    struct words x;
};

struct SREGS {
D 9
    int
E 9
I 9
D 18
    unsigned int
E 18
I 18
    unsigned short
E 18
E 9
	cs,
	ds,
	es,
	ss;
};
#endif	/* defined(MSDOS) (else section) */
E 5
E 3
E 1
