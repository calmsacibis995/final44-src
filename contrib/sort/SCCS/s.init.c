h33143
s 00002/00002/00298
d D 8.1 93/06/06 16:22:59 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00300/00000/00000
d D 5.1 93/06/01 16:44:49 bostic 1 0
c date and time created 93/06/01 16:44:49 by bostic
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1993 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * Peter McIlroy.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include "sort.h"

#include <ctype.h>
#include <string.h>

extern struct coldesc clist[(ND+1)*2];
extern int ncols;
u_char gweights[NBINS];

/*
 * clist (list of columns which correspond to one or more icol or tcol)
 * is in increasing order of columns.
 * Fields are kept in increasing order of fields.
 */

/* 
 * keep clist in order--inserts a column in a sorted array
 */
static void
insertcol(field)
	struct field *field;
{
	int i;
	for (i = 0; i < ncols; i++)
		if (field->icol.num <= clist[i].num)
			break;
	if (field->icol.num != clist[i].num) {
		memmove(clist+i+1, clist+i, sizeof(COLDESC)*(ncols-i));
		clist[i].num = field->icol.num;
		ncols++;
	}
	if (field->tcol.num && field->tcol.num != field->icol.num) {
		for (i = 0; i < ncols; i++)
			if (field->tcol.num <= clist[i].num)
				break;
		if (field->tcol.num != clist[i].num) {
			memmove(clist+i+1, clist+i,sizeof(COLDESC)*(ncols-i));
			clist[i].num = field->tcol.num;
			ncols++;
		}
	}
}

/*
 * matches fields with the appropriate columns--n^2 but who cares?
 */
void
fldreset(fldtab)
	struct field *fldtab;
{
	int i;
	fldtab[0].tcol.p = clist+ncols-1;
	for (++fldtab; fldtab->icol.num; ++fldtab) {
		for (i = 0; fldtab->icol.num != clist[i].num; i++);
		fldtab->icol.p = clist + i;
		if (!fldtab->tcol.num)
			continue;
		for (i = 0; fldtab->tcol.num != clist[i].num; i++);
		fldtab->tcol.p = clist + i;
	}
}

/*
 * interprets a column in a -k field
 */
char *
setcolumn(pos, cur_fld, gflag)
	char *pos;
	struct field *cur_fld;
	int gflag;
{
	struct column *col;
	int tmp;
	col = cur_fld->icol.num ? (&(*cur_fld).tcol) : (&(*cur_fld).icol);
	pos += sscanf(pos, "%d", &(col->num));
	while (isdigit(*pos))
		pos++;
	if (col->num <= 0 && !(col->num == 0 && col == &(cur_fld->tcol)))
		errx(2, "field numbers must be positive");
	if (*pos == '.') {
		if (!col->num)
			errx(2, "cannot indent end of line");
		pos += sscanf(++pos, "%d", &(col->indent));
		while (isdigit(*pos))
			pos++;
		if (&cur_fld->icol == col)
			col->indent--;
		if (col->indent < 0)
			errx(2, "illegal offset");
	}
	if (optval(*pos, cur_fld->tcol.num))	
		while (tmp = optval(*pos, cur_fld->tcol.num)) {
			cur_fld->flags |= tmp;
			pos++;
	}
	if (cur_fld->icol.num == 0)
		cur_fld->icol.num = 1;
	return (pos);
}

int
setfield(pos, cur_fld, gflag)
	char *pos;
	struct field *cur_fld;
	int gflag;
{
	static int nfields = 0;
	int tmp;
	char *setcolumn();
	if (++nfields == ND)
		errx(2, "too many sort keys. (Limit is %d)", ND-1);
	cur_fld->weights = ascii;
	cur_fld->mask = alltable;
	pos = setcolumn(pos, cur_fld, gflag);
	if (*pos == '\0')			/* key extends to EOL. */
		cur_fld->tcol.num = 0;
	else {
		if (*pos != ',')
			errx(2, "illegal field descriptor");
		setcolumn((++pos), cur_fld, gflag);
	}
	if (!cur_fld->flags)
		cur_fld->flags = gflag;
	tmp = cur_fld->flags;

	/*
	 * Assign appropriate mask table and weight table.
	 * If the global weights are reversed, the local field
	 * must be "re-reversed".
	 */
	if (((tmp & R) ^ (gflag & R)) && tmp & F)
		cur_fld->weights = RFtable;
	else if (tmp & F)
		cur_fld->weights = Ftable;
	else if ((tmp & R) ^ (gflag & R))
		cur_fld->weights = Rascii;
	if (tmp & I)
		cur_fld->mask = itable;
	else if (tmp & D)
		cur_fld->mask = dtable;
	cur_fld->flags |= (gflag & (BI | BT));
	if (!cur_fld->tcol.indent)	/* BT has no meaning at end of field */
		cur_fld->flags &= (D|F|I|N|R|BI);
	if (cur_fld->tcol.num && !(!(cur_fld->flags & BI)
	    && cur_fld->flags & BT) && (cur_fld->tcol.num <= cur_fld->icol.num
	    && cur_fld->tcol.indent < cur_fld->icol.indent))
		errx(2, "fields out of order");
	insertcol(cur_fld);
	return (cur_fld->tcol.num);
}

int
optval(desc, tcolflag)
	int desc, tcolflag;
{
	switch(desc) {
		case 'b':
			if (!tcolflag)
				return(BI);
			else
				return(BT);
		case 'd': return(D);
		case 'f': return(F);
		case 'i': return(I);
		case 'n': return(N);
		case 'r': return(R);
		default:  return(0);
	}
}

void
fixit(argc, argv)
	int *argc;
	char **argv;
{
	int i, j, v, w, x;
	static char vbuf[ND*20], *vpos, *tpos;
	vpos = vbuf;

	for (i = 1; i < *argc; i++) {
		if (argv[i][0] == '+') {
			tpos = argv[i]+1;
			argv[i] = vpos;
			vpos += sprintf(vpos, "-k");
			tpos += sscanf(tpos, "%d", &v);
			while (isdigit(*tpos))
				tpos++;
			vpos += sprintf(vpos, "%d", v+1);
			if (*tpos == '.') {
				tpos += sscanf(++tpos, "%d", &x);
				vpos += sprintf(vpos, ".%d", x+1);
			}
			while (*tpos)
				*vpos++ = *tpos++;
			vpos += sprintf(vpos, ",");
			if (argv[i+1] &&
			    argv[i+1][0] == '-' && isdigit(argv[i+1][1])) {
				tpos = argv[i+1] + 1;
				tpos += sscanf(tpos, "%d", &w);
				while (isdigit(*tpos))
					tpos++;
				x = 0;
				if (*tpos == '.') {
					tpos += sscanf(++tpos, "%d", &x);
					while (isdigit(*tpos))
						*tpos++;
				}
				if (x) {
					vpos += sprintf(vpos, "%d", w+1);
					vpos += sprintf(vpos, ".%d", x);
				} else
					vpos += sprintf(vpos, "%d", w);
				while (*tpos)
					*vpos++ = *tpos++;
				for (j= i+1; j < *argc; j++)
					argv[j] = argv[j+1];
				*argc -= 1;
			}
		}
	}
}

/*
 * ascii, Rascii, Ftable, and RFtable map
 * REC_D -> REC_D;  {not REC_D} -> {not REC_D}.
 * gweights maps REC_D -> (0 or 255); {not REC_D} -> {not gweights[REC_D]}.
 * Note: when sorting in forward order, to encode character zero in a key,
 * use \001\001; character 1 becomes \001\002.  In this case, character 0
 * is reserved for the field delimiter.  Analagously for -r (fld_d = 255).
 * Note: this is only good for ASCII sorting.  For different LC 's,
 * all bets are off.  See also num_init in number.c
 */
void
settables(gflags)
	int gflags;
{
	u_char *wts;
	int i, incr;
	for (i=0; i < 256; i++) {
		ascii[i] = i;
		if (i > REC_D && i < 255 - REC_D+1)
			Rascii[i] = 255 - i + 1;
		else
			Rascii[i] = 255 - i;
		if (islower(i)) {
			Ftable[i] = Ftable[i- ('a' -'A')];
			RFtable[i] = RFtable[i - ('a' - 'A')];
		} else if (REC_D>= 'A' && REC_D < 'Z' && i < 'a' && i > REC_D) {
			Ftable[i] = i + 1;
			RFtable[i] = Rascii[i] - 1;
		} else {
			Ftable[i] = i;
			RFtable[i] = Rascii[i];
		}
		alltable[i] = 1;
		if (i == '\n' || isprint(i))
			itable[i] = 1;
		else itable[i] = 0;
		if (i == '\n' || i == '\t' || i == ' ' || isalnum(i))
			dtable[i] = 1;
		else dtable[i] = 0;
	}
	Rascii[REC_D] = RFtable[REC_D] = REC_D;
	if (REC_D >= 'A' && REC_D < 'Z')
		++Ftable[REC_D + ('a' - 'A')];
	if (gflags & R && (!(gflags & F) || !SINGL_FLD))
		wts = Rascii;
	else if (!(gflags & F) || !SINGL_FLD)
		wts = ascii;
	else if (gflags & R)
		wts = RFtable;
	else
		wts = Ftable;
	memmove(gweights, wts, sizeof(gweights));
	incr = (gflags & R) ? -1 : 1;
	for (i = 0; i < REC_D; i++)
		gweights[i] += incr;
	gweights[REC_D] = ((gflags & R) ? 255 : 0);
	if (SINGL_FLD && gflags & F) {
		for (i = 0; i < REC_D; i++) {
			ascii[i] += incr;
			Rascii[i] += incr;
		}
		ascii[REC_D] = Rascii[REC_D] = gweights[REC_D];
	}
}
E 1
