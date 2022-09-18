h01680
s 00039/00008/00312
d D 5.8 95/04/29 10:30:57 bostic 8 7
c changes to byacc 1.9 for dynamic stack expansion
c From: Chris Torek <torek@BSDI.COM>
e
s 00046/00030/00274
d D 5.7 93/05/24 21:29:30 bostic 7 6
c revision 1.9 from Bob Corbett
e
s 00036/00010/00268
d D 5.6 91/01/27 18:03:34 corbett 6 5
c I updated the banner line for version 1.8.  -rpc
e
s 00001/00011/00277
d D 5.5 90/06/01 16:14:11 bostic 5 4
c new copyright notice
e
s 00001/00001/00287
d D 5.4 90/03/11 22:32:16 corbett 4 3
c I changed the banner to match the current revision of the skeleton. 
c -rpc
e
s 00001/00003/00287
d D 5.3 90/03/06 14:44:25 bostic 3 2
c output token #defines after user-specified text
e
s 00007/00000/00283
d D 5.2 90/02/15 09:44:18 bostic 2 1
c update from Bob Corbett
e
s 00283/00000/00000
d D 5.1 89/12/25 14:24:40 bostic 1 0
c date and time created 89/12/25 14:24:40 by bostic
e
u
U
t
T
I 1
/*
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Robert Paul Corbett.
 *
D 5
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
E 5
I 5
 * %sccs.include.redist.c%
E 5
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include "defs.h"

D 6
/*  The three line banner used here should be replaced with a one line	*/
/*  #ident directive if the target C compiler supports #ident		*/
/*  directives.								*/
E 6
I 6
D 7
/*  The banner used here should be replaced with an #ident directive	*/
/*  if the target C compiler supports #ident directives.		*/
E 7
I 7
/*  The definition of yysccsid in the banner should be replaced with	*/
/*  a #pragma ident directive if the target C compiler supports		*/
/*  #pragma ident directives.						*/
E 7
E 6
/*									*/
/*  If the skeleton is changed, the banner should be changed so that	*/
D 7
/*  the altered version can easily be distinguished from the original.	*/
E 7
I 7
/*  the altered version can be easily distinguished from the original.	*/
/*									*/
/*  The #defines included with the banner are there because they are	*/
/*  useful in subsequent code.  The macros #defined in the header or	*/
/*  the body either are not useful outside of semantic actions or	*/
/*  are conditional.							*/
E 7

char *banner[] =
{
    "#ifndef lint",
D 4
    "char yysccsid[] = \"@(#)yaccpar	1.1 (Berkeley) 12/10/89\";",
E 4
I 4
D 6
    "char yysccsid[] = \"@(#)yaccpar	1.4 (Berkeley) 02/25/90\";",
E 6
I 6
D 7
    "static char yysccsid[] = \"@(#)yaccpar	1.8 (Berkeley) 01/20/90\";",
E 7
I 7
    "static char yysccsid[] = \"@(#)yaccpar	1.9 (Berkeley) 02/21/93\";",
E 7
E 6
E 4
    "#endif",
I 8
    "#include <stdlib.h>",
E 8
I 6
    "#define YYBYACC 1",
I 7
    "#define YYMAJOR 1",
    "#define YYMINOR 9",
    "#define yyclearin (yychar=(-1))",
    "#define yyerrok (yyerrflag=0)",
    "#define YYRECOVERING (yyerrflag!=0)",
E 7
E 6
    0
};


I 6
char *tables[] =
{
    "extern short yylhs[];",
    "extern short yylen[];",
    "extern short yydefred[];",
    "extern short yydgoto[];",
    "extern short yysindex[];",
    "extern short yyrindex[];",
    "extern short yygindex[];",
    "extern short yytable[];",
    "extern short yycheck[];",
    "#if YYDEBUG",
    "extern char *yyname[];",
    "extern char *yyrule[];",
    "#endif",
    0
};


E 6
char *header[] =
{
D 7
    "#define yyclearin (yychar=(-1))",
    "#define yyerrok (yyerrflag=0)",
E 7
D 6
    "#ifndef YYSTACKSIZE",
E 6
I 6
    "#ifdef YYSTACKSIZE",
D 7
    "#ifndef YYMAXDEPTH",
E 7
I 7
    "#undef YYMAXDEPTH",
E 7
    "#define YYMAXDEPTH YYSTACKSIZE",
D 7
    "#endif",
E 7
    "#else",
E 6
    "#ifdef YYMAXDEPTH",
    "#define YYSTACKSIZE YYMAXDEPTH",
    "#else",
D 6
    "#define YYSTACKSIZE 300",
E 6
I 6
D 8
    "#define YYSTACKSIZE 500",
    "#define YYMAXDEPTH 500",
E 8
I 8
    "#define YYSTACKSIZE 10000",
    "#define YYMAXDEPTH 10000",
E 8
E 6
    "#endif",
    "#endif",
I 8
    "#define YYINITSTACKSIZE 200",
E 8
    "int yydebug;",
    "int yynerrs;",
    "int yyerrflag;",
    "int yychar;",
    "short *yyssp;",
    "YYSTYPE *yyvsp;",
    "YYSTYPE yyval;",
    "YYSTYPE yylval;",
D 6
    "#define yystacksize YYSTACKSIZE",
E 6
D 8
    "short yyss[YYSTACKSIZE];",
    "YYSTYPE yyvs[YYSTACKSIZE];",
I 6
    "#define yystacksize YYSTACKSIZE",
E 8
I 8
    "short *yyss;",
    "short *yysslim;",
    "YYSTYPE *yyvs;",
    "int yystacksize;",
E 8
E 6
    0
};


char *body[] =
{
I 8
    "/* allocate initial stack or double stack size, up to YYMAXDEPTH */",
    "static int yygrowstack()",
    "{",
    "    int newsize, i;",
    "    short *newss;",
    "    YYSTYPE *newvs;",
    "",
    "    if ((newsize = yystacksize) == 0)",
    "        newsize = YYINITSTACKSIZE;",
    "    else if (newsize >= YYMAXDEPTH)",
    "        return -1;",
    "    else if ((newsize *= 2) > YYMAXDEPTH)",
    "        newsize = YYMAXDEPTH;",
    "    i = yyssp - yyss;",
    "    if ((newss = realloc(yyss, newsize * sizeof *newss)) == NULL)",
    "        return -1;",
    "    yyss = newss;",
    "    yyssp = newss + i;",
    "    if ((newvs = realloc(yyvs, newsize * sizeof *newvs)) == NULL)",
    "        return -1;",
    "    yyvs = newvs;",
    "    yyvsp = newvs + i;",
    "    yystacksize = newsize;",
    "    yysslim = yyss + newsize - 1;",
    "    return 0;",
    "}",
    "",
E 8
I 2
    "#define YYABORT goto yyabort",
I 7
    "#define YYREJECT goto yyabort",
E 7
E 2
    "#define YYACCEPT goto yyaccept",
    "#define YYERROR goto yyerrlab",
    "int",
    "yyparse()",
    "{",
    "    register int yym, yyn, yystate;",
    "#if YYDEBUG",
    "    register char *yys;",
    "    extern char *getenv();",
    "",
    "    if (yys = getenv(\"YYDEBUG\"))",
    "    {",
    "        yyn = *yys;",
D 3
    "        if (yyn == '0')",
    "            yydebug = 0;",
    "        else if (yyn >= '1' && yyn <= '9')",
E 3
I 3
    "        if (yyn >= '0' && yyn <= '9')",
E 3
    "            yydebug = yyn - '0';",
    "    }",
    "#endif",
    "",
    "    yynerrs = 0;",
    "    yyerrflag = 0;",
    "    yychar = (-1);",
    "",
I 8
    "    if (yyss == NULL && yygrowstack()) goto yyoverflow;",
E 8
    "    yyssp = yyss;",
    "    yyvsp = yyvs;",
    "    *yyssp = yystate = 0;",
    "",
    "yyloop:",
    "    if (yyn = yydefred[yystate]) goto yyreduce;",
    "    if (yychar < 0)",
    "    {",
    "        if ((yychar = yylex()) < 0) yychar = 0;",
    "#if YYDEBUG",
    "        if (yydebug)",
    "        {",
    "            yys = 0;",
    "            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];",
    "            if (!yys) yys = \"illegal-symbol\";",
D 7
    "            printf(\"yydebug: state %d, reading %d (%s)\\n\", yystate,",
    "                    yychar, yys);",
E 7
I 7
    "            printf(\"%sdebug: state %d, reading %d (%s)\\n\",",
    "                    YYPREFIX, yystate, yychar, yys);",
E 7
    "        }",
    "#endif",
    "    }",
    "    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&",
    "            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)",
    "    {",
    "#if YYDEBUG",
    "        if (yydebug)",
D 7
    "            printf(\"yydebug: state %d, shifting to state %d\\n\",",
    "                    yystate, yytable[yyn]);",
E 7
I 7
    "            printf(\"%sdebug: state %d, shifting to state %d\\n\",",
    "                    YYPREFIX, yystate, yytable[yyn]);",
E 7
    "#endif",
D 8
    "        if (yyssp >= yyss + yystacksize - 1)",
E 8
I 8
    "        if (yyssp >= yysslim && yygrowstack())",
E 8
    "        {",
    "            goto yyoverflow;",
    "        }",
    "        *++yyssp = yystate = yytable[yyn];",
    "        *++yyvsp = yylval;",
    "        yychar = (-1);",
    "        if (yyerrflag > 0)  --yyerrflag;",
    "        goto yyloop;",
    "    }",
    "    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&",
    "            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)",
    "    {",
    "        yyn = yytable[yyn];",
    "        goto yyreduce;",
    "    }",
    "    if (yyerrflag) goto yyinrecovery;",
I 2
    "#ifdef lint",
    "    goto yynewerror;",
    "#endif",
E 2
    "yynewerror:",
    "    yyerror(\"syntax error\");",
I 2
    "#ifdef lint",
    "    goto yyerrlab;",
    "#endif",
E 2
    "yyerrlab:",
    "    ++yynerrs;",
    "yyinrecovery:",
    "    if (yyerrflag < 3)",
    "    {",
    "        yyerrflag = 3;",
    "        for (;;)",
    "        {",
    "            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&",
    "                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)",
    "            {",
    "#if YYDEBUG",
    "                if (yydebug)",
D 7
    "                    printf(\"yydebug: state %d, error recovery shifting\\",
    " to state %d\\n\", *yyssp, yytable[yyn]);",
E 7
I 7
    "                    printf(\"%sdebug: state %d, error recovery shifting\\",
    " to state %d\\n\", YYPREFIX, *yyssp, yytable[yyn]);",
E 7
    "#endif",
D 8
    "                if (yyssp >= yyss + yystacksize - 1)",
E 8
I 8
    "                if (yyssp >= yysslim && yygrowstack())",
E 8
    "                {",
    "                    goto yyoverflow;",
    "                }",
    "                *++yyssp = yystate = yytable[yyn];",
    "                *++yyvsp = yylval;",
    "                goto yyloop;",
    "            }",
    "            else",
    "            {",
    "#if YYDEBUG",
    "                if (yydebug)",
D 7
    "                    printf(\"yydebug: error recovery discarding state %d\
E 7
I 7
    "                    printf(\"%sdebug: error recovery discarding state %d\
E 7
\\n\",",
D 7
    "                            *yyssp);",
E 7
I 7
    "                            YYPREFIX, *yyssp);",
E 7
    "#endif",
    "                if (yyssp <= yyss) goto yyabort;",
    "                --yyssp;",
    "                --yyvsp;",
    "            }",
    "        }",
    "    }",
    "    else",
    "    {",
    "        if (yychar == 0) goto yyabort;",
    "#if YYDEBUG",
    "        if (yydebug)",
    "        {",
    "            yys = 0;",
    "            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];",
    "            if (!yys) yys = \"illegal-symbol\";",
D 7
    "            printf(\"yydebug: state %d, error recovery discards token %d\
E 7
I 7
    "            printf(\"%sdebug: state %d, error recovery discards token %d\
E 7
 (%s)\\n\",",
D 7
    "                    yystate, yychar, yys);",
E 7
I 7
    "                    YYPREFIX, yystate, yychar, yys);",
E 7
    "        }",
    "#endif",
    "        yychar = (-1);",
    "        goto yyloop;",
    "    }",
    "yyreduce:",
    "#if YYDEBUG",
    "    if (yydebug)",
D 7
    "        printf(\"yydebug: state %d, reducing by rule %d (%s)\\n\",",
    "                yystate, yyn, yyrule[yyn]);",
E 7
I 7
    "        printf(\"%sdebug: state %d, reducing by rule %d (%s)\\n\",",
    "                YYPREFIX, yystate, yyn, yyrule[yyn]);",
E 7
    "#endif",
    "    yym = yylen[yyn];",
    "    yyval = yyvsp[1-yym];",
    "    switch (yyn)",
    "    {",
    0
};


char *trailer[] =
{
    "    }",
    "    yyssp -= yym;",
    "    yystate = *yyssp;",
    "    yyvsp -= yym;",
    "    yym = yylhs[yyn];",
    "    if (yystate == 0 && yym == 0)",
    "    {",
D 6
    "#ifdef YYDEBUG",
E 6
I 6
    "#if YYDEBUG",
E 6
    "        if (yydebug)",
D 7
    "            printf(\"yydebug: after reduction, shifting from state 0 to\\",
    " state %d\\n\", YYFINAL);",
E 7
I 7
    "            printf(\"%sdebug: after reduction, shifting from state 0 to\\",
    " state %d\\n\", YYPREFIX, YYFINAL);",
E 7
    "#endif",
    "        yystate = YYFINAL;",
    "        *++yyssp = YYFINAL;",
    "        *++yyvsp = yyval;",
    "        if (yychar < 0)",
    "        {",
    "            if ((yychar = yylex()) < 0) yychar = 0;",
    "#if YYDEBUG",
    "            if (yydebug)",
    "            {",
    "                yys = 0;",
    "                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];",
    "                if (!yys) yys = \"illegal-symbol\";",
D 7
    "                printf(\"yydebug: state %d, reading %d (%s)\\n\",",
    "                        YYFINAL, yychar, yys);",
E 7
I 7
    "                printf(\"%sdebug: state %d, reading %d (%s)\\n\",",
    "                        YYPREFIX, YYFINAL, yychar, yys);",
E 7
    "            }",
    "#endif",
    "        }",
    "        if (yychar == 0) goto yyaccept;",
    "        goto yyloop;",
    "    }",
    "    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&",
    "            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)",
    "        yystate = yytable[yyn];",
    "    else",
    "        yystate = yydgoto[yym];",
D 6
    "#ifdef YYDEBUG",
E 6
I 6
    "#if YYDEBUG",
E 6
    "    if (yydebug)",
D 7
    "        printf(\"yydebug: after reduction, shifting from state %d \\",
    "to state %d\\n\", *yyssp, yystate);",
E 7
I 7
    "        printf(\"%sdebug: after reduction, shifting from state %d \\",
    "to state %d\\n\", YYPREFIX, *yyssp, yystate);",
E 7
    "#endif",
D 8
    "    if (yyssp >= yyss + yystacksize - 1)",
E 8
I 8
    "    if (yyssp >= yysslim && yygrowstack())",
E 8
    "    {",
    "        goto yyoverflow;",
    "    }",
    "    *++yyssp = yystate;",
    "    *++yyvsp = yyval;",
    "    goto yyloop;",
    "yyoverflow:",
    "    yyerror(\"yacc stack overflow\");",
    "yyabort:",
    "    return (1);",
    "yyaccept:",
    "    return (0);",
    "}",
    0
};


write_section(section)
char *section[];
{
I 7
    register int c;
E 7
    register int i;
I 6
D 7
    register FILE *fp;
E 7
I 7
    register char *s;
    register FILE *f;
E 7
E 6

I 6
D 7
    fp = code_file;
E 6
    for (i = 0; section[i]; ++i)
E 7
I 7
    f = code_file;
    for (i = 0; s = section[i]; ++i)
E 7
    {
	++outline;
D 6
	fprintf(output_file, "%s\n", section[i]);
E 6
I 6
D 7
	fprintf(fp, "%s\n", section[i]);
E 7
I 7
	while (c = *s)
	{
	    putc(c, f);
	    ++s;
	}
	putc('\n', f);
E 7
E 6
    }
}
E 1
