/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
/*
 * C preprocessor configuration switches
 *
 * AT&T Bell Laboratories
 *
 * the proliferation of compile switches allows individual features
 * of the moving draft to be independently tested and permits all
 * versions of the preprocessor to originate from a single source
 *
 * the A column represents ANSI X3J11/85-008 draft settings
 * the U column represents UNIX `standard' settings
 * the P column represents preferred settings (gsf)
 */

				/* AUP					*/
#define CHANGE_DIR	0	/* 010 : check dir of #include file 1st	*/
#define CHECK_COMMENT	1	/* 001 : check for munged comments	*/
#define COMMENT_BLANK	0	/* 100 : comment translates to blank	*/
#define DEBUG		0	/* --- : enable debugging output	*/
#define DEFAULT_INCLUDE	1	/* 101 : init with include <default.h>	*/
#define DISABLE_MACRO	1	/* 001 : disable macro in its own body	*/
#define FLEXNAMES	1	/* 111 : long symbol names		*/
#define JOIN_LINES	0	/* 100 : \\n joins before tokenizing	*/
#define MACRO_FORMAL	1	/* --- : cross reference formal args	*/
#define MATCH_EXTRA	1	/* 001 : match #endif X with #ifn*def X	*/
#define NEWLINE_BLANK	0	/* 010 : \\n in macro is blank		*/
#define ONCE_INCLUDE	1	/* 001 : include each include file once	*/
#define PLUS_SEP	1	/* 001 : \+ is token separator		*/
#define QUOTE_ESCAPE	1	/* 101 : expand within \".." and \'..'	*/
#define QUOTE_FORMAL	1	/* 010 : expand formals within quotes	*/
#define SALT_MACRO	0	/* 100 : # and ## special in macro defs	*/
#define SCAN		1	/* 001 : enable -S dependency output	*/
#define SPACE_SALT	0	/* 100 : allow space before SALT	*/
#define TRIGRAPH	0	/* 100 : expand ANSI ??* trigraphs	*/
#define UNDEF_MACRO	0	/* 100 : undef macro in its expansion	*/

/*
 * these switches are not implemented yet
 */

#undef	JOIN_LINES

/*
 * interacting switches are resolved here
 */

#if JOIN_LINES
#undef	NEWLINE_BLANK
#endif

#if !ONCE_INCLUDE
#undef	SCAN
#endif

#if SALT_MACRO
#undef	QUOTE_ESCAPE
#define QUOTE_ESCAPE	1
#endif

#if UNDEF_MACRO
#undef	DISABLE_MACRO
#endif
