/*-
 * Copyright (c) 1993, 1994
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)gs.h	8.32 (Berkeley) 4/14/94
 */

struct _gs {
	CIRCLEQ_HEAD(_dqh, _scr) dq;	/* Displayed screens. */
	CIRCLEQ_HEAD(_hqh, _scr) hq;	/* Hidden screens. */

	mode_t	 origmode;		/* Original terminal mode. */
	struct termios
		 original_termios;	/* Original terminal values. */

	MSGH	 msgq;			/* User message list. */

	char	*tmp_bp;		/* Temporary buffer. */
	size_t	 tmp_blen;		/* Size of temporary buffer. */

#ifdef DEBUG
	FILE	*tracefp;		/* Trace file pointer. */
#endif

/* INFORMATION SHARED BY ALL SCREENS. */
	IBUF	*tty;			/* Key input buffer. */

	CB	*dcbp;			/* Default cut buffer pointer. */
	CB	*dcb_store;		/* Default cut buffer storage. */
	LIST_HEAD(_cuth, _cb) cutq;	/* Linked list of cut buffers. */

#define	MAX_BIT_SEQ	128		/* Max + 1 fast check character. */
	LIST_HEAD(_seqh, _seq) seqq;	/* Linked list of maps, abbrevs. */
	bitstr_t bit_decl(seqb, MAX_BIT_SEQ);

#define	MAX_FAST_KEY	254		/* Max fast check character.*/
#define	KEY_LEN(sp, ch)							\
	((ch) <= MAX_FAST_KEY ?						\
	    sp->gp->cname[ch].len : __key_len(sp, ch))
#define	KEY_NAME(sp, ch)						\
	((ch) <= MAX_FAST_KEY ?						\
	    sp->gp->cname[ch].name : __key_name(sp, ch))
	struct {
		CHAR_T	 name[MAX_CHARACTER_COLUMNS + 1];
		u_int8_t len;
	} cname[MAX_FAST_KEY + 1];	/* Fast lookup table. */

#define	KEY_VAL(sp, ch)							\
	((ch) <= MAX_FAST_KEY ? sp->gp->special_key[ch] :		\
	    (ch) > sp->gp->max_special ? 0 : __key_val(sp, ch))
	CHAR_T	 max_special;		/* Max special character. */
	u_char				/* Fast lookup table. */
	    special_key[MAX_FAST_KEY + 1];

#define	G_ABBREV	0x00001		/* If have abbreviations. */
#define	G_BELLSCHED	0x00002		/* Bell scheduled. */
#define	G_CURSES_INIT	0x00004		/* Curses: initialized. */
#define	G_RECOVER_SET	0x00008		/* Recover system initialized. */
#define	G_SETMODE	0x00010		/* Tty mode changed. */
#define	G_SIGALRM	0x00020		/* SIGALRM arrived. */
#define	G_SIGHUP	0x00040		/* SIGHUP arrived. */
#define	G_SIGTERM	0x00080		/* SIGTERM arrived. */
#define	G_SIGWINCH	0x00100		/* SIGWINCH arrived. */
#define	G_SLEEPING	0x00200		/* Asleep (die on signal). */
#define	G_SNAPSHOT	0x00400		/* Always snapshot files. */
#define	G_STDIN_TTY	0x00800		/* Standard input is a tty. */
#define	G_TERMIOS_SET	0x01000		/* Termios structure is valid. */
#define	G_TMP_INUSE	0x02000		/* Temporary buffer in use. */

	u_int	 flags;
};

extern GS *__global_list;		/* List of screens. */
