h50359
s 00038/00030/00237
d D 5.3 93/05/24 21:29:44 bostic 3 2
c revision 1.9 from Bob Corbett
e
s 00025/00016/00242
d D 5.2 90/02/15 09:43:32 bostic 2 1
c update from Bob Corbett
e
s 00258/00000/00000
d D 5.1 90/02/15 09:39:05 bostic 1 0
c date and time created 90/02/15 09:39:05 by bostic
e
u
U
t
T
I 1
#ifndef lint
D 2
char yysccsid[] = "@(#)yaccpar	1.1 (Berkeley) 12/10/89";
E 2
I 2
D 3
char yysccsid[] = "@(#)yaccpar	1.3 (Berkeley) 01/21/90";
E 3
I 3
static char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
E 3
E 2
#endif
I 3
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define yyclearin (yychar=(-1))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING (yyerrflag!=0)
#define YYPREFIX "yy"
E 3
#define YYERRCODE 256
D 2
#ifndef YYCONST
#define YYCONST /* const */
#endif
YYCONST short yylhs[] = {                                -1,
E 2
I 2
short yylhs[] = {                                        -1,
E 2
    0,
};
D 2
YYCONST short yylen[] = {                                 2,
E 2
I 2
short yylen[] = {                                         2,
E 2
    1,
};
D 2
YYCONST short yydefred[] = {                              0,
E 2
I 2
short yydefred[] = {                                      0,
E 2
    1,    0,
};
D 2
YYCONST short yydgoto[] = {                               2,
E 2
I 2
short yydgoto[] = {                                       2,
E 2
};
D 2
YYCONST short yysindex[] = {                           -256,
E 2
I 2
short yysindex[] = {                                   -256,
E 2
    0,    0,
};
D 2
YYCONST short yyrindex[] = {                              0,
E 2
I 2
short yyrindex[] = {                                      0,
E 2
    0,    0,
};
D 2
YYCONST short yygindex[] = {                              0,
E 2
I 2
short yygindex[] = {                                      0,
E 2
};
D 2
#define	YYTABLESIZE		0
YYCONST short yytable[] = {                               1,
E 2
I 2
#define YYTABLESIZE 0
short yytable[] = {                                       1,
E 2
};
D 2
YYCONST short yycheck[] = {                             256,
E 2
I 2
short yycheck[] = {                                     256,
E 2
};
#define YYFINAL 2
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 0
#if YYDEBUG
D 2
YYCONST char *yyname[] = {
E 2
I 2
char *yyname[] = {
E 2
"end-of-file",
};
D 2
YYCONST char *yyrule[] = {
E 2
I 2
char *yyrule[] = {
E 2
"$accept : S",
"S : error",
};
#endif
#ifndef YYSTYPE
typedef int YYSTYPE;
#endif
D 3
#define yyclearin (yychar=(-1))
#define yyerrok (yyerrflag=0)
#ifndef YYSTACKSIZE
E 3
I 3
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
E 3
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
D 3
#define YYSTACKSIZE 300
E 3
I 3
#define YYSTACKSIZE 500
#define YYMAXDEPTH 500
E 3
#endif
#endif
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
D 3
#define yystacksize YYSTACKSIZE
E 3
short yyss[YYSTACKSIZE];
YYSTYPE yyvs[YYSTACKSIZE];
I 3
#define yystacksize YYSTACKSIZE
E 3
I 2
#line 4 "error.y"
main(){printf("yyparse() = %d\n",yyparse());}
yylex(){return-1;}
yyerror(s)char*s;{printf("%s\n",s);}
D 3
#line 70 "error.tab.c"
E 3
I 3
#line 80 "error.tab.c"
E 3
#define YYABORT goto yyabort
I 3
#define YYREJECT goto yyabort
E 3
E 2
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse()
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register char *yys;
    extern char *getenv();

    if (yys = getenv("YYDEBUG"))
    {
        yyn = *yys;
D 3
        if (yyn == '0')
            yydebug = 0;
        else if (yyn >= '1' && yyn <= '9')
E 3
I 3
        if (yyn >= '0' && yyn <= '9')
E 3
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if (yyn = yydefred[yystate]) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
D 3
            printf("yydebug: state %d, reading %d (%s)\n", yystate,
                    yychar, yys);
E 3
I 3
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
E 3
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
D 3
            printf("yydebug: state %d, shifting to state %d\n",
                    yystate, yytable[yyn]);
E 3
I 3
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
E 3
#endif
        if (yyssp >= yyss + yystacksize - 1)
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
I 2
#ifdef lint
    goto yynewerror;
#endif
E 2
yynewerror:
    yyerror("syntax error");
I 2
#ifdef lint
    goto yyerrlab;
#endif
E 2
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
D 3
                    printf("yydebug: state %d, error recovery shifting\
 to state %d\n", *yyssp, yytable[yyn]);
E 3
I 3
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
E 3
#endif
                if (yyssp >= yyss + yystacksize - 1)
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
D 3
                    printf("yydebug: error recovery discarding state %d\n",
                            *yyssp);
E 3
I 3
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
E 3
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
D 3
            printf("yydebug: state %d, error recovery discards token %d (%s)\n",
                    yystate, yychar, yys);
E 3
I 3
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
E 3
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
D 3
        printf("yydebug: state %d, reducing by rule %d (%s)\n",
                yystate, yyn, yyrule[yyn]);
E 3
I 3
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
E 3
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
D 3
#ifdef YYDEBUG
E 3
I 3
#if YYDEBUG
E 3
        if (yydebug)
D 3
            printf("yydebug: after reduction, shifting from state 0 to\
 state %d\n", YYFINAL);
E 3
I 3
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
E 3
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
D 3
                printf("yydebug: state %d, reading %d (%s)\n",
                        YYFINAL, yychar, yys);
E 3
I 3
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
E 3
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
D 3
#ifdef YYDEBUG
E 3
I 3
#if YYDEBUG
E 3
    if (yydebug)
D 3
        printf("yydebug: after reduction, shifting from state %d \
to state %d\n", *yyssp, yystate);
E 3
I 3
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
E 3
#endif
    if (yyssp >= yyss + yystacksize - 1)
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}
E 1
