h37191
s 00007/00002/00442
d D 5.4 94/01/21 17:36:28 bostic 4 3
c add USL's copyright notice
e
s 00006/00003/00438
d D 5.3 91/02/26 14:05:45 bostic 3 2
c ANSI fixes, use strdup(3) instead of rolling your own
e
s 00001/00011/00440
d D 5.2 90/06/01 16:10:08 bostic 2 1
c new copyright notice
e
s 00451/00000/00000
d D 5.1 89/08/28 15:14:24 bostic 1 0
c date and time created 89/08/28 15:14:24 by bostic
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1989
 *	The Regents of the University of California.  All rights reserved.
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * Ozan Yigit.
 *
D 2
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 2
I 2
 * %sccs.include.redist.c%
E 2
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
 * serv.c
 * Facility: m4 macro processor
 * by: oz
 */
 
I 3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
E 3
#include "mdef.h"
#include "extr.h" 
I 3
#include "pathnames.h"
E 3

extern ndptr lookup();
extern ndptr addent();
D 3
extern char  *strsave();
E 3
 
char *dumpfmt = "`%s'\t`%s'\n"; /* format string for dumpdef   */
 
/*
 * expand - user-defined macro expansion
 *
 */
expand(argv, argc)
register char *argv[];
register int argc;
{
        register char *t;
        register char *p;
        register int  n;
        register int  argno;
 
        t = argv[0];    /* defn string as a whole */
        p = t;
        while (*p)
                p++;
        p--;            /* last character of defn */
        while (p > t) {
                if (*(p-1) != ARGFLAG)
                        putback(*p);
                else {
                        switch (*p) {
 
                        case '#':
                                pbnum(argc-2);
                                break;
                        case '0':
                        case '1':
                        case '2':
                        case '3':
                        case '4':
                        case '5':
                        case '6':
                        case '7':
                        case '8':
                        case '9':
                                if ((argno = *p - '0') < argc-1)
                                        pbstr(argv[argno+1]);
                                break;
                        case '*':
                                for (n = argc - 1; n > 2; n--) {
                                        pbstr(argv[n]);
                                        putback(',');
                                }
                                pbstr(argv[2]);
                                break;
                        default :
                                putback(*p);
                                break;
                        }
                        p--;
                }
                p--;
        }
        if (p == t)         /* do last character */
                putback(*p);
}
 
/*
 * dodefine - install definition in the table
 *
 */
dodefine(name, defn)
register char *name;
register char *defn;
{
        register ndptr p;
 
        if (!*name)
                error("m4: null definition.");
        if (strcmp(name, defn) == 0)
                error("m4: recursive definition.");
        if ((p = lookup(name)) == nil)
                p = addent(name);
        else if (p->defn != null)
                free(p->defn);
        if (!*defn)
                p->defn = null;
        else
D 3
                p->defn = strsave(defn);
E 3
I 3
                p->defn = strdup(defn);
E 3
        p->type = MACRTYPE;
}
 
/*
 * dodefn - push back a quoted definition of
 *      the given name.
 */
 
dodefn(name)
char *name;
{
        register ndptr p;
 
        if ((p = lookup(name)) != nil && p->defn != null) {
                putback(rquote);
                pbstr(p->defn);
                putback(lquote);
        }
}
     
/*
 * dopushdef - install a definition in the hash table
 *      without removing a previous definition. Since
 *      each new entry is entered in *front* of the
 *      hash bucket, it hides a previous definition from
 *      lookup.
 */
dopushdef(name, defn)
register char *name;
register char *defn;
{
        register ndptr p;
 
        if (!*name)
                error("m4: null definition");
        if (strcmp(name, defn) == 0)
                error("m4: recursive definition.");
        p = addent(name);
        if (!*defn)
                p->defn = null;
        else
D 3
                p->defn = strsave(defn);
E 3
I 3
                p->defn = strdup(defn);
E 3
        p->type = MACRTYPE;
}
 
/*
 * dodumpdef - dump the specified definitions in the hash
 *      table to stderr. If nothing is specified, the entire
 *      hash table is dumped.
 *
 */
dodump(argv, argc)
register char *argv[];
register int argc;
{
        register int n;
        ndptr p;
 
        if (argc > 2) {
                for (n = 2; n < argc; n++)
                        if ((p = lookup(argv[n])) != nil)
                                fprintf(stderr, dumpfmt, p->name,
                                p->defn);
        }
        else {
                for (n = 0; n < HASHSIZE; n++)
                        for (p = hashtab[n]; p != nil; p = p->nxtptr)
                                fprintf(stderr, dumpfmt, p->name,
                                p->defn);
        }
}
 
/*
 * doifelse - select one of two alternatives - loop.
 *
 */
doifelse(argv,argc)
register char *argv[];
register int argc;
{
        cycle {
                if (strcmp(argv[2], argv[3]) == 0)
                        pbstr(argv[4]);
                else if (argc == 6)
                        pbstr(argv[5]);
                else if (argc > 6) {
                        argv += 3;
                        argc -= 3;
                        continue;
                }
                break;
        }
}
 
/*
 * doinclude - include a given file.
 *
 */
doincl(ifile)
char *ifile;
{
        if (ilevel+1 == MAXINP)
                error("m4: too many include files.");
        if ((infile[ilevel+1] = fopen(ifile, "r")) != NULL) {
                ilevel++;
                return (1);
        }
        else
                return (0);
}
 
#ifdef EXTENDED
/*
 * dopaste - include a given file without any
 *           macro processing.
 */
dopaste(pfile)
char *pfile;
{
        FILE *pf;
        register int c;
 
        if ((pf = fopen(pfile, "r")) != NULL) {
                while((c = getc(pf)) != EOF)
                        putc(c, active);
                (void) fclose(pf);
                return(1);
        }
        else
                return(0);
}
#endif
 
/*
 * dochq - change quote characters
 *
 */
dochq(argv, argc)
register char *argv[];
register int argc;
{
        if (argc > 2) {
                if (*argv[2])
                        lquote = *argv[2];
                if (argc > 3) {
                        if (*argv[3])
                                rquote = *argv[3];
                }
                else
                        rquote = lquote;
        }
        else {
                lquote = LQUOTE;
                rquote = RQUOTE;
        }
}
 
/*
 * dochc - change comment characters
 *
 */
dochc(argv, argc)
register char *argv[];
register int argc;
{
        if (argc > 2) {
                if (*argv[2])
                        scommt = *argv[2];
                if (argc > 3) {
                        if (*argv[3])
                                ecommt = *argv[3];
                }
                else
                        ecommt = ECOMMT;
        }
        else {
                scommt = SCOMMT;
                ecommt = ECOMMT;
        }
}
 
/*
 * dodivert - divert the output to a temporary file
 *
 */
dodiv(n)
register int n;
{
        if (n < 0 || n >= MAXOUT)
                n = 0;                  /* bitbucket */
        if (outfile[n] == NULL) {
                m4temp[UNIQUE] = n + '0';
                if ((outfile[n] = fopen(m4temp, "w")) == NULL)
                        error("m4: cannot divert.");
        }
        oindex = n;
        active = outfile[n];
}
 
/*
 * doundivert - undivert a specified output, or all
 *              other outputs, in numerical order.
 */
doundiv(argv, argc)
register char *argv[];
register int argc;
{
        register int ind;
        register int n;
 
        if (argc > 2) {
                for (ind = 2; ind < argc; ind++) {
                        n = atoi(argv[ind]);
                        if (n > 0 && n < MAXOUT && outfile[n] != NULL)
                                getdiv(n);
 
                }
        }
        else
                for (n = 1; n < MAXOUT; n++)
                        if (outfile[n] != NULL)
                                getdiv(n);
}
 
/*
 * dosub - select substring
 *
 */
dosub (argv, argc)
register char *argv[];
register int  argc;
{
        register char *ap, *fc, *k;
        register int nc;
 
        if (argc < 5)
                nc = MAXTOK;
        else
#ifdef EXPR
                nc = expr(argv[4]);
#else
		nc = atoi(argv[4]);
#endif
        ap = argv[2];                   /* target string */
#ifdef EXPR
        fc = ap + expr(argv[3]);        /* first char */
#else
        fc = ap + atoi(argv[3]);        /* first char */
#endif
        if (fc >= ap && fc < ap+strlen(ap))
                for (k = fc+min(nc,strlen(fc))-1; k >= fc; k--)
                        putback(*k);
}
 
/*
 * map:
 * map every character of s1 that is specified in from
 * into s3 and replace in s. (source s1 remains untouched)
 *
 * This is a standard implementation of map(s,from,to) function of ICON 
 * language. Within mapvec, we replace every character of "from" with 
 * the corresponding character in "to". If "to" is shorter than "from", 
 * than the corresponding entries are null, which means that those 
 * characters dissapear altogether. Furthermore, imagine 
 * map(dest, "sourcestring", "srtin", "rn..*") type call. In this case, 
 * `s' maps to `r', `r' maps to `n' and `n' maps to `*'. Thus, `s' 
 * ultimately maps to `*'. In order to achieve this effect in an efficient 
 * manner (i.e. without multiple passes over the destination string), we 
 * loop over mapvec, starting with the initial source character. if the 
 * character value (dch) in this location is different than the source 
 * character (sch), sch becomes dch, once again to index into mapvec, until 
 * the character value stabilizes (i.e. sch = dch, in other words 
 * mapvec[n] == n). Even if the entry in the mapvec is null for an ordinary 
 * character, it will stabilize, since mapvec[0] == 0 at all times. At the 
 * end, we restore mapvec* back to normal where mapvec[n] == n for 
 * 0 <= n <= 127. This strategy, along with the restoration of mapvec, is 
 * about 5 times faster than any algorithm that makes multiple passes over 
 * destination string.
 *
 */
     
map(dest,src,from,to)
register char *dest;
register char *src;
register char *from;
register char *to;
{
        register char *tmp;
        register char sch, dch;
        static char mapvec[128] = {
                0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
                12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
                24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
                36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
                48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
                60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71,
                72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83,
                84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95,
                96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107,
                108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119,
                120, 121, 122, 123, 124, 125, 126, 127
        };
 
        if (*src) {
                tmp = from;
	/*
	 * create a mapping between "from" and "to"
	 */
                while (*from)
                        mapvec[*from++] = (*to) ? *to++ : (char) 0;
     
                while (*src) {
                        sch = *src++;
                        dch = mapvec[sch];
                        while (dch != sch) {
                                sch = dch;
                                dch = mapvec[sch];
                        }
                        if (*dest = dch)
                                dest++;
                }
	/*
	 * restore all the changed characters
	 */
                while (*tmp) {
                        mapvec[*tmp] = *tmp;
                        tmp++;
                }
        }
        *dest = (char) 0;
}
E 1
