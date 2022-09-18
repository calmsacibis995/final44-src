/*-
 * Copyright (c) 1992, 1993, 1994
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
 */

#ifndef lint
static char sccsid[] = "@(#)v_search.c	8.25 (Berkeley) 4/13/94";
#endif /* not lint */

#include <sys/types.h>
#include <sys/queue.h>
#include <sys/time.h>

#include <bitstring.h>
#include <errno.h>
#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>

#include "compat.h"
#include <db.h>
#include <regex.h>

#include "vi.h"
#include "vcmd.h"

static int correct __P((SCR *, EXF *, VICMDARG *, u_int));
static int getptrn __P((SCR *, EXF *, ARG_CHAR_T, char **));
static int search __P((SCR *, EXF *, VICMDARG *, char *, int, enum direction));

/*
 * v_searchn -- n
 *	Repeat last search.
 */
int
v_searchn(sp, ep, vp)
	SCR *sp;
	EXF *ep;
	VICMDARG *vp;
{
	return (search(sp, ep, vp, NULL, SEARCH_MSG, sp->searchdir));
}

/*
 * v_searchN -- N
 *	Reverse last search.
 */
int
v_searchN(sp, ep, vp)
	SCR *sp;
	EXF *ep;
	VICMDARG *vp;
{
	enum direction dir;

	switch (sp->searchdir) {
	case BACKWARD:
		dir = FORWARD;
		break;
	case FORWARD:
		dir = BACKWARD;
		break;
	default:			/* NOTSET handled in search(). */
		dir = sp->searchdir;
		break;
	}
	return (search(sp, ep, vp, NULL, SEARCH_MSG, dir));
}

/*
 * v_searchb -- [count]?RE[? offset]
 *	Search backward.
 */
int
v_searchb(sp, ep, vp)
	SCR *sp;
	EXF *ep;
	VICMDARG *vp;
{
	char *ptrn;

	if (F_ISSET(vp, VC_ISDOT))
		ptrn = NULL;
	else {
		if (getptrn(sp, ep, CH_BSEARCH, &ptrn))
			return (1);
		if (ptrn == NULL) {
			F_SET(vp, VM_NOMOTION);
			return (0);
		}
	}
	return (search(sp, ep, vp, ptrn,
	    SEARCH_MSG | SEARCH_PARSE | SEARCH_SET | SEARCH_TERM, BACKWARD));
}

/*
 * v_searchf -- [count]/RE[/ offset]
 *	Search forward.
 */
int
v_searchf(sp, ep, vp)
	SCR *sp;
	EXF *ep;
	VICMDARG *vp;
{
	char *ptrn;

	if (F_ISSET(vp, VC_ISDOT))
		ptrn = NULL;
	else {
		if (getptrn(sp, ep, CH_FSEARCH, &ptrn))
			return (1);
		if (ptrn == NULL) {
			F_SET(vp, VM_NOMOTION);
			return (0);
		}
	}
	return (search(sp, ep, vp, ptrn,
	    SEARCH_MSG | SEARCH_PARSE | SEARCH_SET | SEARCH_TERM, FORWARD));
}

/*
 * v_searchw -- [count]^A
 *	Search for the word under the cursor.
 */
int
v_searchw(sp, ep, vp)
	SCR *sp;
	EXF *ep;
	VICMDARG *vp;
{
	size_t blen, len;
	int rval;
	char *bp;

	len = vp->kbuflen + sizeof(RE_WSTART) + sizeof(RE_WSTOP);
	GET_SPACE_RET(sp, bp, blen, len);
	(void)snprintf(bp, blen, "%s%s%s", RE_WSTART, vp->keyword, RE_WSTOP);

	rval = search(sp, ep, vp, bp, SEARCH_MSG, FORWARD);

	FREE_SPACE(sp, bp, blen);
	return (rval);
}

static int
search(sp, ep, vp, ptrn, flags, dir)
	SCR *sp;
	EXF *ep;
	VICMDARG *vp;
	int flags;
	char *ptrn;
	enum direction dir;
{
	if (ISMOTION(vp))
		flags |= SEARCH_EOL;
	switch (dir) {
	case BACKWARD:
		if (b_search(sp, ep,
		    &vp->m_start, &vp->m_stop, ptrn, NULL, &flags))
			return (1);
		/* Non-motion commands move to the end of the range. */
		if (!ISMOTION(vp))
			vp->m_final = vp->m_stop;
		else if (correct(sp, ep, vp, flags))
			return (1);
		break;
	case FORWARD:
		if (f_search(sp, ep,
		    &vp->m_start, &vp->m_stop, ptrn, NULL, &flags))
			return (1);
		/* Non-motion commands move to the end of the range. */
		if (!ISMOTION(vp))
			vp->m_final = vp->m_stop;
		else if (correct(sp, ep, vp, flags))
			return (1);
		break;
	case NOTSET:
		msgq(sp, M_ERR, "No previous search pattern.");
		return (1);
	default:
		abort();
	}
	return (0);
}

/*
 * getptrn --
 *	Get the search pattern.
 */
static int
getptrn(sp, ep, prompt, storep)
	SCR *sp;
	EXF *ep;
	ARG_CHAR_T prompt;
	char **storep;
{
	TEXT *tp;

	if (sp->s_get(sp, ep, sp->tiqp, prompt,
	    TXT_BS | TXT_CR | TXT_ESCAPE | TXT_PROMPT) != INP_OK)
		return (1);

	/* Len is 0 if backspaced over the prompt, 1 if only CR entered. */
	tp = sp->tiqp->cqh_first;
	if (tp->len == 0)
		*storep = NULL;
	else
		*storep = tp->lb;
	return (0);
}

/*
 * correct --
 *	Handle command with a search as the motion.
 *
 * !!!
 * Historically, commands didn't affect the line searched to/from if the
 * motion command was a search and the final position was the start/end
 * of the line.  There were some special cases and vi was not consistent;
 * it was fairly easy to confuse it.  For example, given the two lines:
 *
 *	abcdefghi
 *	ABCDEFGHI
 *
 * placing the cursor on the 'A' and doing y?$ would so confuse it that 'h'
 * 'k' and put would no longer work correctly.  In any case, we try to do
 * the right thing, but it's not going to exactly match historic practice.
 */
static int
correct(sp, ep, vp, flags)
	SCR *sp;
	EXF *ep;
	VICMDARG *vp;
	u_int flags;
{
	enum direction dir;
	MARK m;
	size_t len;

	/*
	 * !!!
	 * Searches become line mode operations if there was a delta
	 * specified to the search pattern.
	 */
	if (LF_ISSET(SEARCH_DELTA))
		F_SET(vp, VM_LMODE);

	/*
	 * If the motion is in the reverse direction, switch the start and
	 * stop MARK's so that it's in a forward direction.  (There's no
	 * reason for this other than to make the tests below easier.  The
	 * code in vi.c:vi() would have done the switch.)  Both forward
	 * and backward motions can happen for any kind of search command
	 * because of the wrapscan option.
	 */
	if (vp->m_start.lno > vp->m_stop.lno ||
	    vp->m_start.lno == vp->m_stop.lno &&
	    vp->m_start.cno > vp->m_stop.cno) {
		dir = BACKWARD;
		m = vp->m_start;
		vp->m_start = vp->m_stop;
		vp->m_stop = m;
	} else
		dir = FORWARD;

	/*
	 * BACKWARD:
	 *	VC_D commands move to the end of the range.  VC_Y stays at
	 *	the start unless the end of the range is on a different line,
	 *	when it moves to the end of the range.  Ignore VC_C and VC_S.
	 *
	 * FORWARD:
	 *	VC_D and VC_Y commands don't move.  Ignore VC_C and VC_S.
	 */
	if (dir == BACKWARD)
		if (F_ISSET(vp, VC_D) ||
		    F_ISSET(vp, VC_Y) && vp->m_start.lno != vp->m_stop.lno)
			vp->m_final = vp->m_start;
		else
			vp->m_final = vp->m_stop;
	else
		vp->m_final = vp->m_start;

	/*
	 * !!!
	 * Backward searches starting at column 0, and forward searches ending
	 * at column 0 are corrected to the last column of the previous line.
	 * Otherwise, adjust the starting/ending point to the character before
	 * the current one (this is safe because we know the search had to move
	 * to succeed).
	 *
	 * Searches become line mode operations if they start at column 0 and
	 * end at column 0 of another line.
	 */
	if (vp->m_start.lno < vp->m_stop.lno && vp->m_stop.cno == 0) {
		if (file_gline(sp, ep, --vp->m_stop.lno, &len) == NULL) {
			GETLINE_ERR(sp, vp->m_stop.lno);
			return (1);
		}
		if (vp->m_start.cno == 0)
			F_SET(vp, VM_LMODE);
		vp->m_stop.cno = len ? len - 1 : 0;
	} else
		--vp->m_stop.cno;

	return (0);
}
