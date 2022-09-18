h27870
s 00002/00002/00132
d D 8.1 93/05/31 16:41:24 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00134
d D 5.7 93/05/22 19:06:17 christos 7 6
c Fixed gcc -Wall warnings
e
s 00002/00001/00132
d D 5.6 92/03/02 00:13:23 christos 6 5
c Fixed and documented $histfile
e
s 00002/00000/00131
d D 5.5 91/11/04 18:20:53 christos 5 4
c Added noambiguous
e
s 00001/00000/00130
d D 5.4 91/07/28 14:13:37 christos 4 3
c Added STRret for dowhich()
e
s 00000/00001/00130
d D 5.3 91/07/19 17:30:21 christos 3 2
c stdio based version; brace glob fix; builtin prototypes
e
s 00001/00001/00130
d D 5.2 91/06/07 11:13:46 bostic 2 1
c rename all the files (they weren't going to diff anyway)
c add function prototypes for extern functions, decls.h -> extern.h
c delete btell function, VFORK #define, lots of other minor cleanups
e
s 00131/00000/00000
d D 5.1 91/06/04 16:55:42 christos 1 0
c date and time created 91/06/04 16:55:42 by christos
e
u
U
t
T
I 1
/*-
D 8
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
 * tc.const.c: String constants for csh.
 */

D 2
#include "sh.h"
E 2
I 2
#include "csh.h"
E 2

Char STR0[]             = { '0', '\0' };
Char STR1[]             = { '1', '\0' };
Char STRHOME[]		= { 'H', 'O', 'M', 'E', '\0' };
Char STRLANG[]  	= { 'L', 'A', 'N', 'G', '\0' };
Char STRLC_CTYPE[]	= { 'L', 'C', '_', 'C', 'T', 'Y', 'P', 'E' ,'\0' };
Char STRLOGNAME[]	= { 'L', 'O', 'G', 'N', 'A', 'M', 'E', '\0' };
Char STRLbrace[]	= { '{', '\0' };
Char STRLparen[]	= { '(', '\0' };
Char STRLparensp[]	= { '(', ' ', '\0' };
Char STRNULL[]          = { '\0' };
Char STRPATH[] 		= { 'P', 'A', 'T', 'H', '\0' };
Char STRPWD[]		= { 'P', 'W', 'D', '\0' };
Char STRQNULL[]		= { '\0' | QUOTE, '\0' };
Char STRRbrace[]	= { '}', '\0' };
Char STRspRparen[]	= { ' ', ')', '\0' };
Char STRTERM[]		= { 'T', 'E', 'R', 'M', '\0' };
Char STRUSER[]		= { 'U', 'S', 'E', 'R', '\0' };
Char STRalias[]         = { 'a', 'l', 'i', 'a', 's', '\0' };
D 3
Char STRampm[]		= { 'a', 'm', 'p', 'm', '\0' };
E 3
Char STRand[]		= { '&', '\0' };
Char STRand2[]		= { '&', '&', '\0' };
Char STRaout[]          = { 'a', '.', 'o', 'u', 't', '\0' };
Char STRargv[]          = { 'a', 'r', 'g', 'v', '\0' };
Char STRbang[]		= { '!', '\0' };
Char STRcaret[]		= { '^', '\0' };
Char STRcdpath[]	= { 'c', 'd', 'p', 'a', 't', 'h', '\0' };
Char STRcent2[] 	= { '%', '%', '\0' };
Char STRcenthash[] 	= { '%', '#', '\0' };
Char STRcentplus[] 	= { '%', '+', '\0' };
Char STRcentminus[] 	= { '%', '-', '\0' };
Char STRchase_symlinks[] = { 'c', 'h', 'a', 's', 'e', '_', 's', 'y', 'm', 'l', 
			    'i', 'n', 'k', 's', '\0' };
Char STRchild[]		= { 'c', 'h', 'i', 'l', 'd', '\0' };
Char STRcolon[]		= { ':', '\0' };
Char STRcwd[]           = { 'c', 'w', 'd', '\0' };
Char STRdefault[]	= { 'd', 'e', 'f', 'a', 'u', 'l', 't', '\0' };
Char STRdot[]           = { '.', '\0' };
Char STRdotdotsl[]	= { '.', '.', '/', '\0' };
Char STRdotsl[]		= { '.', '/', '\0' };
Char STRecho[]          = { 'e', 'c', 'h', 'o', '\0' };
Char STRequal[]		= { '=', '\0' };
Char STRfakecom[]	= { '{', ' ', '.', '.', '.', ' ', '}', '\0' };
Char STRfakecom1[]	= { '`', ' ', '.', '.', '.', ' ', '`', '\0' };
Char STRfignore[]	= { 'f', 'i', 'g', 'n', 'o', 'r', 'e', '\0' };
#ifdef FILEC
Char STRfilec[] = { 'f', 'i', 'l', 'e', 'c', '\0' };
#endif /* FILEC */
Char STRhistchars[]	= { 'h', 'i', 's', 't', 'c', 'h', 'a', 'r', 's', '\0' };
D 6
Char STRhistfile[]      = { '~', '/', '.', 'h', 'i', 's', 't', 'o', 'r', 
E 6
I 6
Char STRtildothist[]    = { '~', '/', '.', 'h', 'i', 's', 't', 'o', 'r', 
E 6
		            'y', '\0' };
I 6
Char STRhistfile[]	= { 'h', 'i', 's', 't', 'f', 'i', 'l', 'e', '\0' };
E 6
Char STRhistory[] 	= { 'h', 'i', 's', 't', 'o', 'r', 'y', '\0' };
Char STRhome[]          = { 'h', 'o', 'm', 'e', '\0' };
Char STRignore_symlinks[] = { 'i', 'g', 'n', 'o', 'r', 'e', '_', 's', 'y', 'm',
			    'l', 'i', 'n', 'k', 's', '\0' };
Char STRignoreeof[]	= { 'i', 'g', 'n', 'o', 'r', 'e', 'e', 'o', 'f', '\0' };
Char STRjobs[]          = { 'j', 'o', 'b', 's', '\0' };
Char STRlistjobs[]	= { 'l', 'i', 's', 't', 'j', 'o', 'b', 's', '\0' };
Char STRlogout[]        = { 'l', 'o', 'g', 'o', 'u', 't', '\0' };
Char STRlong[]		= { 'l', 'o', 'n', 'g', '\0' };
Char STRmail[]		= { 'm', 'a', 'i', 'l', '\0' };
Char STRmh[]            = { '-', 'h', '\0' };
Char STRminus[]		= { '-', '\0' };
Char STRml[]		= { '-', 'l', '\0' };
Char STRmn[]		= { '-', 'n', '\0' };
Char STRmquestion[]     = { '?' | QUOTE, ' ', '\0' };
Char STRnice[]		= { 'n', 'i', 'c', 'e', '\0' };
I 5
Char STRnoambiguous[]	= { 'n', 'o', 'a', 'm', 'b', 'i', 'g', 'u', 'o', 'u', 
			    's', '\0' };
E 5
Char STRnobeep[]	= { 'n', 'o', 'b', 'e', 'e', 'p', '\0' };
Char STRnoclobber[]	= { 'n', 'o', 'c', 'l', 'o', 'b', 'b', 'e', 'r', '\0' };
Char STRnoglob[]	= { 'n', 'o', 'g', 'l', 'o', 'b', '\0' };
Char STRnohup[]		= { 'n', 'o', 'h', 'u', 'p', '\0' };
Char STRnonomatch[]	= { 'n', 'o', 'n', 'o', 'm', 'a', 't', 'c', 'h', '\0' };
Char STRnormal[]        = { 'n', 'o', 'r', 'm', 'a', 'l', '\0' };
Char STRnotify[]	= { 'n', 'o', 't', 'i', 'f', 'y', '\0' };
Char STRor[]		= { '|', '\0' };
Char STRor2[]		= { '|', '|', '\0' };
Char STRpath[]          = { 'p', 'a', 't', 'h', '\0' };
Char STRprintexitvalue[] = { 'p', 'r', 'i', 'n', 't', 'e', 'x', 'i', 't', 'v', 
			    'a', 'l', 'u', 'e', '\0' };
Char STRprompt[]        = { 'p', 'r', 'o', 'm', 'p', 't', '\0' };
Char STRprompt2[]       = { 'p', 'r', 'o', 'm', 'p', 't', '2', '\0' };
Char STRpushdsilent[]	= { 'p', 'u', 's', 'h', 'd', 's', 'i', 'l', 'e', 'n',
			    't', '\0' };
I 4
Char STRret[]		= { '\n', '\0' };
E 4
Char STRsavehist[]      = { 's', 'a', 'v', 'e', 'h', 'i', 's', 't', '\0' };
Char STRsemisp[]	= { ';', ' ', '\0' };
Char STRshell[]         = { 's', 'h', 'e', 'l', 'l', '\0' };
Char STRslash[]		= { '/', '\0' };
Char STRsldotcshrc[]	= { '/', '.', 'c', 's', 'h', 'r', 'c', '\0' };
Char STRsldotlogin[]	= { '/', '.', 'l', 'o', 'g', 'i', 'n', '\0' };
Char STRsldthist[]      = { '/', '.', 'h', 'i', 's', 't', 'o', 'r', 'y', '\0' };
Char STRsldtlogout[]    = { '/', '.', 'l', 'o', 'g', 'o', 'u', 't', '\0' };
Char STRsource[]        = { 's', 'o', 'u', 'r', 'c', 'e', '\0' };
Char STRsp3dots[]	= { ' ', '.', '.', '.', '\0' };
Char STRspLarrow2sp[]	= { ' ', '<', '<', ' ', '\0' };
Char STRspLarrowsp[]	= { ' ', '<', ' ', '\0' };
Char STRspRarrow[]	= { ' ', '>', '\0' };
Char STRspRarrow2[]	= { ' ', '>', '>', '\0' };
Char STRRparen[]	= { ')', '\0' };
Char STRspace[]		= { ' ', '\0' };
Char STRspand2sp[]	= { ' ', '&', '&', ' ', '\0' };
Char STRspor2sp[]	= { ' ', '|', '|', ' ', '\0' };
Char STRsporsp[]	= { ' ', '|', ' ', '\0' };
Char STRstar[]          = { '*', '\0' };
Char STRstatus[]        = { 's', 't', 'a', 't', 'u', 's', '\0' };
Char STRsymcent[]       = { '%', ' ', '\0' };
Char STRsymhash[]       = { '#', ' ', '\0' };
Char STRterm[]          = { 't', 'e', 'r', 'm', '\0' };
Char STRthen[]		= { 't', 'h', 'e', 'n', '\0' };
Char STRtilde[]		= { '~', '\0' };
Char STRtime[]		= { 't', 'i', 'm', 'e', '\0' };
Char STRtmpsh[]         = { '/', 't', 'm', 'p', '/', 's', 'h', '\0' };
Char STRunalias[]       = { 'u', 'n', 'a', 'l', 'i', 'a', 's', '\0' };
Char STRuser[]          = { 'u', 's', 'e', 'r', '\0' };
Char STRverbose[]       = { 'v', 'e', 'r', 'b', 'o', 's', 'e', '\0' };
Char STRwordchars[]	= { 'w', 'o', 'r', 'd', 'c', 'h', 'a', 'r', 's', '\0' };
E 1
