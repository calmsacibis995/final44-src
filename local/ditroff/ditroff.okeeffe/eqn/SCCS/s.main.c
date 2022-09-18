h61700
s 00008/00000/00343
d D 2.4 87/04/01 15:40:24 jaap 4 3
c Oops, forgot local devices
e
s 00042/00038/00301
d D 2.3 87/04/01 15:18:49 jaap 3 2
c Updates from bwk, see README for details
e
s 00005/00000/00334
d D 2.2 86/04/09 22:40:55 jaap 2 1
c Added PostScript resolution
e
s 00334/00000/00000
d D 2.1 85/07/18 18:12:13 jaap 1 0
c date and time created 85/07/18 18:12:13 by jaap
e
u
U
t
T
I 1
#ifndef lint
static char sccsid[] = "%W% (CWI) %E%";
#endif lint
# include "e.h"
#define	MAXLINE	3600	/* maximum input line */

char	in[MAXLINE];	/* input buffer */
D 3
int	eqnexit();
E 3
int	noeqn;
char	*cmdname;

main(argc,argv)
	int argc;
	char *argv[];
{
D 3
	eqnexit(eqn(argc, argv));
E 3
I 3
	exit(eqn(argc, argv));
E 3
}

D 3
eqnexit(n) {
#ifdef gcos
	if (n)
		fprintf(stderr, "run terminated due to eqn error\n");
	exit(0);
#endif
	exit(n);
}

E 3
eqn(argc,argv)
	int argc;
	char *argv[];
{
	int i, type;
D 3
	char *p, *getenv();
E 3
I 3
	char *p, *getenv(), buf[20];
E 3

	cmdname = argv[0];
	if (p = getenv("TYPESETTER"))
		typesetter = p;
	while (argc > 1 && argv[1][0] == '-') {
		switch (argv[1][1]) {

		case 'd':
			if (argv[1][2] == '\0')
				dbg++;
			else {
				lefteq = argv[1][2];
				righteq = argv[1][3];
			}
			break;
D 3
		case 's': gsize = atoi(&argv[1][2]); break;
		case 'p': deltaps = atoi(&argv[1][2]); break;
		case 'r': res = atoi(&argv[1][2]); break;
E 3
I 3
		case 's': szstack[0] = gsize = atoi(&argv[1][2]); break;
		case 'p': deltaps = atoi(&argv[1][2]); dps_set = 1; break;
E 3
		case 'm': minsize = atoi(&argv[1][2]); break;
		case 'f': strcpy(ftstack[0].name,&argv[1][2]); break;
		case 'e': noeqn++; break;
D 3
		case 'T':
			typesetter = &argv[1][2];
			break;
E 3
I 3
		case 'T': typesetter = &argv[1][2]; break;
E 3
		default:
D 3
			dbg = 1;
E 3
I 3
			fprintf(stderr, "%s: unknown option %s\n", cmdname, argv[1]);
			break;
E 3
		}
		argc--;
		argv++;
	}
	settype(typesetter);
D 3
	lookup(deftbl, strsave(typesetter), strsave(typesetter));
E 3
I 3
	sprintf(buf, "\"%s\"", typesetter);
	lookup(deftbl, strsave(typesetter), strsave(buf));
E 3
	init_tbl();	/* install other keywords in tables */
	curfile = infile;
	pushsrc(File, curfile);
	if (argc <= 1) {
		curfile->fin = stdin;
		curfile->fname = strsave("-");
		getdata();
	} else
		while (argc-- > 1) {
			if (strcmp(*++argv, "-") == 0)
				curfile->fin = stdin;
			else if ((curfile->fin = fopen(*argv, "r")) == NULL)
				fatal("can't open file %s", *argv);
			curfile->fname = strsave(*argv);
			getdata();
			if (curfile->fin != stdin)
				fclose(curfile->fin);
		}
	return 0;
}

settype(s)	/* initialize data for particular typesetter */
D 3
	char *s;
{
E 3
I 3
	char *s;	/* the minsize could profitably come from the */
{			/* troff description file /usr/lib/font/dev.../DESC.out */
E 3
	if (strcmp(s, "202") == 0)
D 3
		{ res = 972; minsize = 5; ttype = DEV202; }
E 3
I 3
		{ minsize = 5; ttype = DEV202; }
E 3
	else if (strcmp(s, "aps") == 0)
D 3
		{ res = 723; minsize = 5; ttype = DEVAPS; }
E 3
I 3
		{ minsize = 5; ttype = DEVAPS; }
E 3
	else if (strcmp(s, "cat") == 0)
D 3
		{ res = 432; minsize = 6; ttype = DEVCAT; }
	else if (strcmp(s, "har") == 0)
		{ res = 1445; minsize = 4; ttype = DEVHAR; }
	else if (strcmp(s, "ver") == 0)
		{ res = 200; minsize = 6; ttype = DEVVER; }
I 2
	else if (strcmp(s, "psc") == 0)
		{	/* Postscript printer (Laserwriter) using transcript */
			res = 576;	/* at least, troff thinks so */
			minsize = 4;	/* troff believes 2, but that's so small */
			ttype = DEVPSC; }
E 3
I 3
		{ minsize = 6; ttype = DEVCAT; }
I 4
	else if (strcmp(s, "har") == 0)
		{ minsize = 4; ttype = DEVHAR; }
	else if (strcmp(s, "ver") == 0)
		{ minsize = 6; ttype = DEVVER; }
	else if (strcmp(s, "psc") == 0)
		{/* Postscript printer (Laserwriter) using transcript */
			minsize = 4;	/* troff believes 2, but that's so small */
			ttype = DEVPSC; }
E 4
E 3
E 2
	else
D 3
		{ res = atoi(s); minsize = 6; ttype = DEVCAT; }
E 3
I 3
		{ minsize = 6; ttype = DEVCAT; }
E 3
}

getdata()
{
	register FILE *fin;
	int i, type, ln;
	char fname[100];
	extern int errno;

	errno = 0;
	fin = curfile->fin;
	curfile->lineno = 0;
	printf(".lf 1 %s\n", curfile->fname);
	while ((type = getline(in)) != EOF) {
		if (in[0] == '.' && in[1] == 'E' && in[2] == 'Q') {
			for (i = 11; i < 100; i++)
				used[i] = 0;
			printf("%s", in);
			if (markline) {	/* turn off from last time */
				printf(".nr MK 0\n");
				markline = 0;
			}
			display = 1;
			init();
			yyparse();
			if (eqnreg > 0) {
				if (markline)
					printf(".nr MK %d\n", markline); /* for -ms macros */
				printf(".if %gm>\\n(.v .ne %gm\n", eqnht, eqnht);
				printf(".rn %d 10\n", eqnreg);
				if (!noeqn)
D 3
					printf("\\*(10\n");
E 3
I 3
					printf("\\&\\*(10\n");
E 3
			}
			printf(".EN");
			while (putchar(input()) != '\n')
				;
			printf(".lf %d\n", curfile->lineno+1);
		}
		else if (type == lefteq)
			inline();
		else if (in[0] == '.' && in[1] == 'l' && in[2] == 'f') {
			if (sscanf(in+3, "%d %s", &ln, fname) == 2) {
				free(curfile->fname);
				printf(".lf %d %s\n", curfile->lineno = ln, curfile->fname = strsave(fname));
			} else
				printf(".lf %d\n", curfile->lineno = ln);
		} else
			printf("%s", in);
	}
	return(0);
}

getline(s)
	register char *s;
{
	register c;

	while ((c=input()) != '\n' && c != EOF && c != lefteq) {
		if (s >= in+MAXLINE) {
			error("input line too long: %.20s\n", in);
			in[MAXLINE] = '\0';
			break;
		}
		*s++ = c;
	}
	if (c != lefteq)
		*s++ = c;
	*s = '\0';
	return(c);
}

inline()
{
	int ds, n, sz1 = 0;

	n = curfile->lineno;
	if (szstack[0] != 0)
		printf(".nr %d \\n(.s\n", sz1 = salloc());
	ds = salloc();
	printf(".rm %d \n", ds);
	display = 0;
	do {
		if (*in)
			printf(".as %d \"%s\n", ds, in);
		init();
		yyparse();
		if (eqnreg > 0) {
			printf(".as %d \\*(%d\n", ds, eqnreg);
			sfree(eqnreg);
			printf(".lf %d\n", curfile->lineno+1);
		}
	} while (getline(in) == lefteq);
	if (*in)
		printf(".as %d \"%s", ds, in);
	if (sz1)
		printf("\\s\\n(%d", sz1);
	printf("\\*(%d\n", ds);
	printf(".lf %d\n", curfile->lineno+1);
	if (curfile->lineno > n+3)
		fprintf(stderr, "eqn warning: multi-line %c...%c, lines %d-%d, file %s\n",
			lefteq, righteq, n, curfile->lineno, curfile->fname); 
	sfree(ds);
	if (sz1) sfree(sz1);
}

putout(p1)
	int p1;
{
	float before, after;
I 3
	extern float BeforeSub, AfterSub;
E 3

	dprintf(".\tanswer <- S%d, h=%g,b=%g\n",p1, eht[p1], ebase[p1]);
	eqnht = eht[p1];
D 3
	before = eht[p1] - ebase[p1] - 1.2;	/* leave room for sub or superscript */
	after = ebase[p1] - 0.2;
E 3
I 3
	before = eht[p1] - ebase[p1] - BeforeSub;	/* leave room for sub or superscript */
	after = ebase[p1] - AfterSub;
E 3
	if (spaceval || before > 0.01 || after > 0.01) {
		printf(".ds %d ", p1);	/* used to be \\x'0' here:  why? */
		if (spaceval != NULL)
			printf("\\x'0-%s'", spaceval);
		else if (before > 0.01)
			printf("\\x'0-%gm'", before);
		printf("\\*(%d", p1);
		if (spaceval == NULL && after > 0.01)
			printf("\\x'%gm'", after);
		putchar('\n');
	}
	if (szstack[0] != 0)
		printf(".ds %d %s\\*(%d\\s\\n(99\n", p1, DPS(gsize,gsize), p1);
	eqnreg = p1;
	if (spaceval != NULL) {
		free(spaceval);
		spaceval = NULL;
	}
}

init()
{
	synerr = 0;
	ct = 0;
	ps = gsize;
	ftp = ftstack;
	ft = ftp->ft;
	nszstack = 0;
	if (szstack[0] != 0)	/* absolute gsize in effect */
		printf(".nr 99 \\n(.s\n");
}

salloc()
{
	int i;

	for (i = 11; i < 100; i++)
		if (used[i] == 0) {
			used[i]++;
			return(i);
		}
	error(FATAL, "no eqn strings left (%d)", i);
	return(0);
}

sfree(n)
	int n;
{
	used[n] = 0;
}

nrwid(n1, p, n2)
	int n1, p, n2;
{
	printf(".nr %d 0\\w'%s\\*(%d'\n", n1, DPS(gsize,p), n2);	/* 0 defends against - width */
I 3
}

char *ABSPS(dn)	/* absolute size dn in printable form \sd or \s(dd (dd >= 40) */
	int dn;
{
	static char buf[100], *lb = buf;
	char *p;

	if (lb > buf + sizeof(buf) - 10)
		lb = buf;
	p = lb;
	*lb++ = '\\';
	*lb++ = 's';
	if (dn >= 10) {		/* \s(dd only works in new troff */
		if (dn >= 40)
			*lb++ = '(';
		*lb++ = dn/10 + '0';
		*lb++ = dn%10 + '0';
	} else {
		*lb++ = dn + '0';
	}
	*lb++ = '\0';	
	return p;
E 3
}

char *DPS(f, t)	/* delta ps (t-f) in printable form \s+d or \s-d or \s+-(dd */
	int f, t;
{
	static char buf[100], *lb = buf;
	char *p;
	int dn;

	if (lb > buf + sizeof(buf) - 10)
		lb = buf;
	p = lb;
	*lb++ = '\\';
	*lb++ = 's';
	dn = EFFPS(t) - EFFPS(f);
	if (szstack[nszstack] != 0)	/* absolute */
		dn = EFFPS(t);		/* should do proper \s(dd */
	else if (dn >= 0)
		*lb++ = '+';
	else {
		*lb++ = '-';
		dn = -dn;
	}
	if (dn >= 10) {		/* \s+(dd only works in new troff */
		*lb++ = '(';
		*lb++ = dn/10 + '0';
		*lb++ = dn%10 + '0';
	} else {
		*lb++ = dn + '0';
	}
	*lb++ = '\0';	
	return p;
}

EFFPS(n)	/* effective value of n */
	int n;
{
	if (n >= minsize)
		return n;
	else
		return minsize;
}

double EM(m, ps)	/* convert m to ems in gsize */
	double m;
	int ps;
{
	m *= (float) EFFPS(ps) / gsize;
	if (m <= 0.001 && m >= -0.001)
		return 0;
	else
		return m;
}

double REL(m, ps)	/* convert m to ems in ps */
	double m;
	int ps;
{
	m *= (float) gsize / EFFPS(ps);
	if (m <= 0.001 && m >= -0.001)
		return 0;
	else
		return m;
}
E 1
