h59005
s 00002/00002/00369
d D 8.1 93/06/06 22:28:58 bostic 29 28
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00005/00365
d D 3.26 92/11/10 11:49:55 edward 28 27
c checkpointing stuff
e
s 00001/00000/00369
d D 3.25 92/06/25 15:48:49 bostic 27 26
c <sys/resource.h> needs <sys/types.h>
e
s 00003/00003/00366
d D 3.24 92/06/24 14:54:43 edward 26 25
c input error correction stuff
e
s 00005/00002/00364
d D 3.23 90/06/17 18:06:11 edward 25 24
c report compression ratio as well (in l_iostat)
e
s 00003/00000/00363
d D 3.22 90/06/06 21:43:51 bostic 24 23
c fix contrib notice (Edward Wang)
e
s 00001/00011/00362
d D 3.21 90/06/02 15:20:14 bostic 23 22
c new copyright notice
e
s 00013/00008/00360
d D 3.20 90/05/06 02:51:33 edward 22 21
c l_time(): give the rss fields more room
e
s 00003/00003/00365
d D 3.19 89/08/24 04:57:46 edward 21 19
c new compresson algorithm
e
s 00002/00002/00366
d R 3.19 89/08/24 04:42:11 edward 20 19
c new compression algorithm
e
s 00008/00004/00360
d D 3.18 89/08/02 19:12:54 edward 19 18
c data compression and some other stuff
e
s 00007/00001/00357
d D 3.17 89/05/11 17:01:42 edward 18 17
c the xx layer added, handle "ic" differently, compression added to zapple
e
s 00017/00015/00341
d D 3.16 88/08/04 18:09:18 edward 17 16
c use clreos and always try clreol in wwupdate1
e
s 00010/00005/00346
d D 3.15 88/06/29 21:36:06 bostic 16 15
c install approved copyright notice
e
s 00013/00007/00338
d D 3.14 88/02/21 13:37:03 bostic 15 14
c written by Edward Wang; attach Berkeley specific copyright
e
s 00005/00005/00340
d D 3.13 87/10/02 19:36:58 edward 14 13
c changes from mips!dce, most compatibility stuff
e
s 00001/00001/00344
d D 3.12 87/05/18 12:20:37 edward 13 12
c added keepopen and smooth flags, added + and - window selections
e
s 00006/00000/00339
d D 3.11 85/04/24 16:23:20 edward 12 11
c copyright messages
e
s 00002/00002/00337
d D 3.10 85/04/03 20:39:32 edward 11 10
c removed some compatibility with old window, and some clean up
e
s 00003/00002/00336
d D 3.9 84/11/20 23:18:16 edward 10 8
c lint
e
s 00001/00001/00337
d R 3.9 84/11/20 23:03:12 edward 9 8
c lint
e
s 00028/00000/00310
d D 3.8 84/07/19 17:34:55 edward 8 7
c the echo command
e
s 00039/00015/00271
d D 3.7 84/07/12 13:38:59 edward 7 6
c new ARG_LIST flag for commands
e
s 00001/00001/00285
d D 3.6 84/06/02 18:16:45 edward 6 5
c spelling
e
s 00001/00001/00285
d D 3.5 84/05/23 02:00:58 edward 5 4
c new sccs id
e
s 00063/00001/00223
d D 3.4 84/05/06 17:56:17 edward 4 3
c alias macros
e
s 00035/00001/00189
d D 3.3 84/04/08 19:23:47 edward 3 2
c new options to "window": shell, pty, frame
c and stuff to support them
e
s 00073/00005/00117
d D 3.2 84/04/07 00:02:25 edward 2 1
c l_variable and l_list added
e
s 00122/00000/00000
d D 3.1 84/04/05 17:34:40 edward 1 0
c date and time created 84/04/05 17:34:40 by edward
e
u
U
t
T
I 1
D 15
#ifndef lint
D 5
static	char *sccsid = "%W% %E%";
E 5
I 5
static char sccsid[] = "%W% %G%";
E 5
#endif

E 15
I 12
/*
D 15
 * Copyright (c) 1983 Regents of the University of California,
 * All rights reserved.  Redistribution permitted subject to
 * the terms of the Berkeley Software License Agreement.
E 15
I 15
D 29
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.
E 29
I 29
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 29
 *
I 24
 * This code is derived from software contributed to Berkeley by
 * Edward Wang at The University of California, Berkeley.
 *
E 24
D 23
 * Redistribution and use in source and binary forms are permitted
D 16
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 16
I 16
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
E 23
I 23
 * %sccs.include.redist.c%
E 23
E 16
E 15
 */
I 15

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 15

I 27
D 28
#include <sys/types.h>
E 28
E 27
E 12
#include "defs.h"
#include "string.h"
#include "value.h"
I 2
#include "var.h"
E 2
#include "lcmd.h"
D 28
#include <sys/resource.h>
E 28
I 4
#include "alias.h"
I 28
#include <sys/types.h>
#include <sys/resource.h>
E 28
E 4

D 2
struct lcmd_arg arg_iostat[] = {
	0
};

E 2
I 2
/*ARGSUSED*/
E 2
l_iostat(v, a)
struct value *v, *a;
{
	register struct ww *w;

D 18
	if ((w = openiwin(14, "IO Statistics")) == 0) {
E 18
I 18
	if ((w = openiwin(16, "IO Statistics")) == 0) {
E 18
		error("Can't open statistics window: %s.", wwerror());
		return;
	}
	wwprintf(w, "ttflush\twrite\terror\tzero\tchar\n");
	wwprintf(w, "%d\t%d\t%d\t%d\t%d\n",
		wwnflush, wwnwr, wwnwre, wwnwrz, wwnwrc);
I 18
D 21
	wwprintf(w, "token\tuse\tsaving\ttotal\tbaud\n");
	wwprintf(w, "%d\t%d\t%d\t%d\t%d/%d\n",
D 19
		wwzc0, wwzc1, wwzcsave, wwzctotal,
		wwzctotal - wwzcsave ?
			wwbaud * wwzctotal / (wwzctotal - wwzcsave) : wwbaud,
		wwnwrc ? wwbaud * (wwnwrc + wwzcsave) / wwnwrc : wwbaud);
E 19
I 19
		wwntokdef, wwntokuse, wwntoksave, wwntokc,
E 21
I 21
	wwprintf(w, "token\tuse\tbad\tsaving\ttotal\tbaud\n");
D 25
	wwprintf(w, "%d\t%d\t%d\t%d\t%d\t%d/%d\n",
E 25
I 25
	wwprintf(w, "%d\t%d\t%d\t%d\t%d\t%d/%d (%.1f/%.1f)\n",
E 25
		wwntokdef, wwntokuse, wwntokbad, wwntoksave, wwntokc,
E 21
		wwntokc - wwntoksave ?
			(int) ((float) wwbaud * wwntokc /
					(wwntokc - wwntoksave)) :
			wwbaud,
		wwnwrc ? (int) ((float) wwbaud * (wwnwrc + wwntoksave) /
					wwnwrc) :
D 25
			wwbaud);
E 25
I 25
			wwbaud,
		wwntokc - wwntoksave ?
			(float) wwntokc / (wwntokc - wwntoksave) : 1.0,
		wwnwrc ? (float) (wwnwrc + wwntoksave) / wwnwrc : 1.0);
E 25
E 19
E 18
D 6
	wwprintf(w, "wwwrite\tattmpt\tchar\n");
E 6
I 6
	wwprintf(w, "wwwrite\tattempt\tchar\n");
E 6
	wwprintf(w, "%d\t%d\t%d\n",
		wwnwwr, wwnwwra, wwnwwrc);
D 17
	wwprintf(w, "wwupdat\tline\tmiss\tmajor\tmiss\n");
	wwprintf(w, "%d\t%d\t%d\t%d\t%d\n",
		wwnupdate, wwnupdline, wwnupdmiss, wwnmajline, wwnmajmiss);
E 17
I 17
	wwprintf(w, "wwupdat\tline\tmiss\tscan\tclreol\tclreos\tmiss\tline\n");
	wwprintf(w, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
		wwnupdate, wwnupdline, wwnupdmiss, wwnupdscan, wwnupdclreol,
		wwnupdclreos, wwnupdclreosmiss, wwnupdclreosline);
E 17
	wwprintf(w, "select\terror\tzero\n");
	wwprintf(w, "%d\t%d\t%d\n",
		wwnselect, wwnselecte, wwnselectz);
D 26
	wwprintf(w, "read\terror\tzero\tchar\n");
	wwprintf(w, "%d\t%d\t%d\t%d\n",
		wwnread, wwnreade, wwnreadz, wwnreadc);
E 26
I 26
D 28
	wwprintf(w, "read\terror\tzero\tchar\terrorc\n");
	wwprintf(w, "%d\t%d\t%d\t%d\t%d\n",
		wwnread, wwnreade, wwnreadz, wwnreadc, wwnreadec);
E 28
I 28
	wwprintf(w, "read\terror\tzero\tchar\tack\tnack\tstat\terrorc\n");
	wwprintf(w, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
		wwnread, wwnreade, wwnreadz, wwnreadc, wwnreadack, wwnreadnack,
		wwnreadstat, wwnreadec);
E 28
E 26
	wwprintf(w, "ptyread\terror\tzero\tcontrol\tdata\tchar\n");
	wwprintf(w, "%d\t%d\t%d\t%d\t%d\t%d\n",
		wwnwread, wwnwreade, wwnwreadz,
		wwnwreadp, wwnwreadd, wwnwreadc);
	waitnl(w);
	closeiwin(w);
}

struct lcmd_arg arg_time[] = {
D 3
	{ "who",	1,	V_STR },
E 3
I 3
	{ "who",	1,	ARG_STR },
E 3
	0
};

I 2
/*ARGSUSED*/
E 2
l_time(v, a)
struct value *v;
register struct value *a;
{
	register struct ww *w;
	struct rusage rusage;
	struct timeval timeval;
D 2
	int flag;
E 2
	char *strtime();

D 22
	if ((w = openiwin(6, "Timing and Resource Usage")) == 0) {
E 22
I 22
	if ((w = openiwin(8, "Timing and Resource Usage")) == 0) {
E 22
		error("Can't open time window: %s.", wwerror());
		return;
	}

	(void) gettimeofday(&timeval, (struct timezone *)0);
	timeval.tv_sec -= starttime.tv_sec;
	if ((timeval.tv_usec -= starttime.tv_usec) < 0) {
		timeval.tv_sec--;
		timeval.tv_usec += 1000000;
	}
	(void) getrusage(a->v_type == V_STR
			&& str_match(a->v_str, "children", 1)
		? RUSAGE_CHILDREN : RUSAGE_SELF, &rusage);

D 22
	wwprintf(w, "time\t\tutime\t\tstime\t\tmaxrss\tixrss\tidrss\tisrss\n");
	wwprintf(w, "%-16s", strtime(&timeval));
	wwprintf(w, "%-16s", strtime(&rusage.ru_utime));
	wwprintf(w, "%-16s", strtime(&rusage.ru_stime));
D 14
	wwprintf(w, "%D\t%D\t%D\t%D\n",
E 14
I 14
	wwprintf(w, "%ld\t%ld\t%ld\t%ld\n",
E 22
I 22
	wwprintf(w, "%-15s %-15s %-15s\n",
		"time", "utime", "stime");
	wwprintf(w, "%-15s ", strtime(&timeval));
	wwprintf(w, "%-15s ", strtime(&rusage.ru_utime));
	wwprintf(w, "%-15s\n", strtime(&rusage.ru_stime));
	wwprintf(w, "%-15s %-15s %-15s %-15s\n",
		"maxrss", "ixrss", "idrss", "isrss");
	wwprintf(w, "%-15ld %-15ld %-15ld %-15ld\n",
E 22
E 14
		rusage.ru_maxrss, rusage.ru_ixrss,
		rusage.ru_idrss, rusage.ru_isrss);
D 22
	wwprintf(w, "minflt\tmajflt\tnswap\tinblk\toublk\tmsgsnd\tmsgrcv\tnsigs\tnvcsw\tnivcsw\n");
D 14
	wwprintf(w, "%D\t%D\t%D\t%D\t%D\t%D\t%D\t%D\t%D\t%D\n",
E 14
I 14
	wwprintf(w, "%ld\t%ld\t%ld\t%ld\t%ld\t%ld\t%ld\t%ld\t%ld\t%ld\n",
E 22
I 22
	wwprintf(w, "%-7s %-7s %-7s %-7s %-7s %-7s %-7s %-7s %-7s %-7s\n",
		"minflt", "majflt", "nswap", "inblk", "oublk",
		"msgsnd", "msgrcv", "nsigs", "nvcsw", "nivcsw");
	wwprintf(w, "%-7ld %-7ld %-7ld %-7ld %-7ld %-7ld %-7ld %-7ld %-7ld %-7ld\n",
E 22
E 14
		rusage.ru_minflt, rusage.ru_majflt, rusage.ru_nswap,
		rusage.ru_inblock, rusage.ru_oublock,
		rusage.ru_msgsnd, rusage.ru_msgrcv, rusage.ru_nsignals,
		rusage.ru_nvcsw, rusage.ru_nivcsw);

	waitnl(w);
	closeiwin(w);
}

char *
strtime(t)
register struct timeval *t;
{
	char fill = 0;
	static char buf[20];
	register char *p = buf;

	if (t->tv_sec > 60*60) {
D 14
		(void) sprintf(p, "%D:", t->tv_sec / (60*60));
E 14
I 14
		(void) sprintf(p, "%ld:", t->tv_sec / (60*60));
E 14
		while (*p++)
			;
		p--;
		t->tv_sec %= 60*60;
		fill++;
	}
	if (t->tv_sec > 60) {
D 14
		(void) sprintf(p, fill ? "%02D:" : "%D:", t->tv_sec / 60);
E 14
I 14
		(void) sprintf(p, fill ? "%02ld:" : "%ld:", t->tv_sec / 60);
E 14
		while (*p++)
			;
		p--;
		t->tv_sec %= 60;
		fill++;
	}
D 14
	(void) sprintf(p, fill ? "%02D.%02d" : "%D.%02D",
E 14
I 14
	(void) sprintf(p, fill ? "%02ld.%02d" : "%ld.%02ld",
E 14
		t->tv_sec, t->tv_usec / 10000);
	return buf;
I 2
}

/*ARGSUSED*/
l_list(v, a)
struct value *v, *a;
{
	register struct ww *w, *wp;
	register i;
	int n;

	for (n = 0, i = 0; i < NWINDOW; i++)
		if (window[i] != 0)
			n++;
	if (n == 0) {
		error("No windows.");
		return;
	}
	if ((w = openiwin(n + 2, "Windows")) == 0) {
		error("Can't open listing window: %s.", wwerror());
		return;
	}
	for (i = 0; i < NWINDOW; i++) {
		if ((wp = window[i]) == 0)
			continue;
		wwprintf(w, "%c %c %-13s %-.*s\n",
D 13
			wp == selwin ? '*' : ' ',
E 13
I 13
			wp == selwin ? '+' : (wp == lastselwin ? '-' : ' '),
E 13
			i + '1',
			wp->ww_state == WWS_HASPROC ? "" : "(No process)",
			wwncol - 20,
			wp->ww_label ? wp->ww_label : "(No label)");
	}
	waitnl(w);
	closeiwin(w);
}

/*ARGSUSED*/
l_variable(v, a)
struct value *v, *a;
{
	register struct ww *w;
	int printvar();

	if ((w = openiwin(wwnrow - 3, "Variables")) == 0) {
		error("Can't open variable window: %s.", wwerror());
		return;
	}
	if (var_walk(printvar, (int)w) >= 0)
		waitnl(w);
	closeiwin(w);
}

printvar(w, r)
register struct ww *w;
register struct var *r;
{
	if (more(w, 0) == 2)
		return -1;
D 4
	wwprintf(w, "%16s\t", r->r_name);
E 4
I 4
	wwprintf(w, "%16s    ", r->r_name);
E 4
	switch (r->r_val.v_type) {
	case V_STR:
		wwprintf(w, "%s\n", r->r_val.v_str);
		break;
	case V_NUM:
		wwprintf(w, "%d\n", r->r_val.v_num);
		break;
	case V_ERR:
		wwprintf(w, "ERROR\n");
		break;
	}
	return 0;
I 3
}

D 17
struct lcmd_arg arg_shell[] = {
E 17
I 17
struct lcmd_arg arg_def_shell[] = {
E 17
D 7
	{ "shell",	1,	ARG_STR },
E 7
I 7
	{ "",	0,		ARG_ANY|ARG_LIST },
E 7
	0
};

D 17
l_shell(v, a)
E 17
I 17
l_def_shell(v, a)
E 17
D 7
struct value *v, *a;
E 7
I 7
	struct value *v, *a;
E 7
{
D 7
	register char **pp;
E 7
I 7
D 10
	register char **pp, *p;
E 10
I 10
	register char **pp;
E 10
	register struct value *vp;
E 7

	if (a->v_type == V_ERR) {
D 17
		if ((v->v_str = str_cpy(shellfile)) != 0)
E 17
I 17
		if ((v->v_str = str_cpy(default_shellfile)) != 0)
E 17
			v->v_type = V_STR;
		return;
	}
D 17
	if (v->v_str = shellfile) {
E 17
I 17
	if (v->v_str = default_shellfile) {
E 17
		v->v_type = V_STR;
D 7
		for (pp = shell + 1; *pp; pp++)
E 7
I 7
D 17
		for (pp = shell + 1; *pp; pp++) {
E 17
I 17
		for (pp = default_shell + 1; *pp; pp++) {
E 17
E 7
			str_free(*pp);
I 7
			*pp = 0;
		}
E 7
	}
D 7
	if (mkargv(a->v_str, shell, sizeof shell / sizeof *shell) < 0)
		*shell = 0;
	for (pp = shell; *pp; pp++)
		if ((*pp = str_cpy(*pp)) == 0) {
E 7
I 7
D 17
	for (pp = shell, vp = a;
	     vp->v_type != V_ERR && pp < &shell[sizeof shell/sizeof *shell-1];
E 17
I 17
	for (pp = default_shell, vp = a;
	     vp->v_type != V_ERR &&
	     pp < &default_shell[sizeof default_shell/sizeof *default_shell-1];
E 17
	     pp++, vp++)
		if ((*pp = vp->v_type == V_STR ?
		     str_cpy(vp->v_str) : str_itoa(vp->v_num)) == 0) {
E 7
D 17
			/* just leave shell[] the way it is */
E 17
I 17
			/* just leave default_shell[] the way it is */
E 17
			p_memerror();
I 7
			break;
E 7
		}
D 17
	if (shellfile = *shell)
		if (*shell = rindex(shellfile, '/'))
			(*shell)++;
E 17
I 17
	if (default_shellfile = *default_shell)
		if (*default_shell = rindex(default_shellfile, '/'))
			(*default_shell)++;
E 17
		else
D 17
			*shell = shellfile;
E 17
I 17
			*default_shell = default_shellfile;
E 17
I 4
}

struct lcmd_arg arg_alias[] = {
D 7
	{ "name",	1,	ARG_STR },
	{ "string",	1,	ARG_STR },
E 7
I 7
	{ "",	0,		ARG_STR },
	{ "",	0,		ARG_STR|ARG_LIST },
E 7
	0
};

l_alias(v, a)
D 7
struct value *v, *a;
E 7
I 7
	struct value *v, *a;
E 7
{
	if (a->v_type == V_ERR) {
		register struct ww *w;
		int printalias();

		if ((w = openiwin(wwnrow - 3, "Aliases")) == 0) {
			error("Can't open alias window: %s.", wwerror());
			return;
		}
		if (alias_walk(printalias, (int)w) >= 0)
			waitnl(w);
		closeiwin(w);
	} else {
		register struct alias *ap = 0;

		if (ap = alias_lookup(a->v_str)) {
			if ((v->v_str = str_cpy(ap->a_buf)) == 0) {
				p_memerror();
				return;
			}
			v->v_type = V_STR;
		}
D 7
		if (a[1].v_type == V_STR &&
		    alias_set(a[0].v_str, a[1].v_str) == 0) {
			p_memerror();
			return;
E 7
I 7
		if (a[1].v_type == V_STR) {
			register struct value *vp;
			register char *p, *q;
			char *str;
			register n;

			for (n = 0, vp = a + 1; vp->v_type != V_ERR; vp++, n++)
				for (p = vp->v_str; *p; p++, n++)
					;
			if ((str = str_alloc(n)) == 0) {
				p_memerror();
				return;
			}
			for (q = str, vp = a + 1; vp->v_type != V_ERR;
			     vp++, q[-1] = ' ')
				for (p = vp->v_str; *q++ = *p++;)
					;
			q[-1] = 0;
D 10
			if ((ap = alias_set(a[0].v_str, 0)) == 0) {
E 10
I 10
			if ((ap = alias_set(a[0].v_str, (char *)0)) == 0) {
E 10
				p_memerror();
I 10
				str_free(str);
E 10
				return;
			}
			ap->a_buf = str;
E 7
		}
	}
}

printalias(w, a)
register struct ww *w;
register struct alias *a;
{
	if (more(w, 0) == 2)
		return -1;
	wwprintf(w, "%16s    %s\n", a->a_name, a->a_buf);
	return 0;
}

struct lcmd_arg arg_unalias[] = {
D 11
	{ "name",	1,	ARG_STR },
E 11
I 11
	{ "alias",	1,	ARG_STR },
E 11
	0
};

l_unalias(v, a)
struct value *v, *a;
{
	if (a->v_type == ARG_STR)
		v->v_num = alias_unset(a->v_str);
	v->v_type = V_NUM;
E 4
E 3
E 2
}
I 8

struct lcmd_arg arg_echo[] = {
	{ "window",	1,	ARG_NUM },
	{ "",		0,	ARG_ANY|ARG_LIST },
	0
};

/*ARGSUSED*/
l_echo(v, a)
struct value *v;
register struct value *a;
{
	char buf[20];
	struct ww *w;

D 11
	if ((w = vtowin(a++)) == 0)
E 11
I 11
	if ((w = vtowin(a++, selwin)) == 0)
E 11
		return;
	while (a->v_type != V_ERR) {
		if (a->v_type == V_NUM) {
			(void) sprintf(buf, "%d", a->v_num);
			(void) wwwrite(w, buf, strlen(buf));
		} else
			(void) wwwrite(w, a->v_str, strlen(a->v_str));
		if ((++a)->v_type != V_ERR)
			(void) wwwrite(w, " ", 1);
	}
	(void) wwwrite(w, "\r\n", 2);
}
E 8
E 1
