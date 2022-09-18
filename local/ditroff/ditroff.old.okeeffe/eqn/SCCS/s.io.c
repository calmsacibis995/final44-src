h62294
s 00005/00000/00237
d D 1.7 85/06/24 13:00:52 slatteng 7 6
c put in search for environment variables "PRINTER" and "TYPESETTER"
e
s 00001/00000/00236
d D 1.6 84/07/23 18:02:30 slatteng 6 5
c made minimum granularity of vertical movement a parameter read from DESC file
e
s 00002/00000/00234
d D 1.5 83/12/19 16:42:23 slatteng 5 4
c make DEVDIR changable in makefile
e
s 00001/00000/00233
d D 1.4 83/10/07 21:28:50 slatteng 4 3
c put in '-P' option as well as '-T'
e
s 00003/00003/00230
d D 1.3 83/09/21 13:07:01 slatteng 3 2
c fix number register 98 in \f commands for two digits.
e
s 00029/00012/00204
d D 1.2 83/08/15 16:28:09 slatteng 2 1
c removed all device-dependent code.  That means anything that was
c optimized for a particular typesetter is gone, and eqn now looks up the
c output device in a device file, like everybody else.
e
s 00216/00000/00000
d D 1.1 83/08/15 10:12:16 slatteng 1 0
c date and time created 83/08/15 10:12:16 by slatteng
e
u
U
t
T
I 1
# include "e.h"
I 2
# include "dev.h"
E 2
#define	MAXLINE	3600	/* maximum input line */
	/* huge for Chris's graphics language */

I 5
#ifndef DEVDIR
E 5
I 2
#define DEVDIR	"/usr/lib/font"		/* place to find "dev" directory */
I 5
#endif
E 5
char	*devdir	= DEVDIR;

E 2
char	in[MAXLINE];	/* input buffer */
int	eqnexit();
int noeqn;

main(argc,argv) int argc; char *argv[];{

	eqnexit(eqn(argc, argv));
}

eqnexit(n) {
#ifdef gcos
	if (n)
		fprintf(stderr, "run terminated due to eqn error\n");
	exit(0);
#endif
	exit(n);
}

eqn(argc,argv) int argc; char *argv[];{
	int i, type;

	setfile(argc,argv);
	init_tbl();	/* install keywords in tables */
	while ((type=getline(in)) != EOF) {
		eqline = linect;
		if (in[0]=='.' && in[1]=='E' && in[2]=='Q') {
			for (i=11; i<100; used[i++]=0);
			printf("%s",in);
D 3
			printf(".nr 99 \\n(.s\n.nr 98 \\n(.f\n");
E 3
I 3
			printf(".nr 99 \\n(.s\n.nr 98 \\n(.f\n.af 98 01\n");
E 3
			markline = 0;
			init();
			yyparse();
			if (eqnreg>0) {
				printf(".nr %d \\w'\\*(%d'\n", eqnreg, eqnreg);
				/* printf(".if \\n(%d>\\n(.l .tm too-long eqn, file %s, between lines %d-%d\n",	*/
				/*	eqnreg, svargv[ifile], eqline, linect);	*/
				printf(".nr MK %d\n", markline);	/* for -ms macros */
				printf(".if %d>\\n(.v .ne %du\n", eqnht, eqnht);
				printf(".rn %d 10\n", eqnreg);
				if(!noeqn)printf("\\*(10\n");
			}
			printf(".ps \\n(99\n.ft \\n(98\n");
			printf(".EN");
			if (lastchar == EOF) {
				putchar('\n');
				break;
			}
			if (putchar(lastchar) != '\n')
				while (putchar(gtc()) != '\n');
		}
		else if (type == lefteq)
			inline();
		else
			printf("%s",in);
	}
	return(0);
}

getline(s) register char *s; {
	register c;
	while((*s++=c=gtc())!='\n' && c!=EOF && c!=lefteq)
		if (s >= in+MAXLINE) {
			error( !FATAL, "input line too long: %.20s\n", in);
			in[MAXLINE] = '\0';
			break;
		}
	if (c==lefteq)
		s--;
	*s++ = '\0';
	return(c);
}

inline() {
	int ds;

D 3
	printf(".nr 99 \\n(.s\n.nr 98 \\n(.f\n");
E 3
I 3
	printf(".nr 99 \\n(.s\n.nr 98 \\n(.f\n.af 98 01\n");
E 3
	ds = oalloc();
	printf(".rm %d \n", ds);
	do{
		if (*in)
			printf(".as %d \"%s\n", ds, in);
		init();
		yyparse();
		if (eqnreg > 0) {
			printf(".as %d \\*(%d\n", ds, eqnreg);
			ofree(eqnreg);
		}
		printf(".ps \\n(99\n.ft \\n(98\n");
	} while (getline(in) == lefteq);
	if (*in)
		printf(".as %d \"%s", ds, in);
	printf(".ps \\n(99\n.ft \\n(98\n");
	printf("\\*(%d\n", ds);
	ofree(ds);
}

putout(p1) int p1; {
	extern int gsize, gfont;
	int before, after;
	if(dbg)printf(".\tanswer <- S%d, h=%d,b=%d\n",p1, eht[p1], ebase[p1]);
	eqnht = eht[p1];
	printf(".ds %d \\x'0'", p1);
	/* suppposed to leave room for a subscript or superscript */
	before = eht[p1] - ebase[p1] - VERT( EM(1.2, ps) );
	if (spaceval != NULL)
		printf("\\x'0-%s'", spaceval);
	else if (before > 0)
		printf("\\x'0-%du'", before);
D 3
	printf("\\f%c\\s%d\\*(%d%s\\s\\n(99\\f\\n(98",
E 3
I 3
	printf("\\f%c\\s%d\\*(%d%s\\s\\n(99\\f(\\n(98",
E 3
		gfont, gsize, p1, rfont[p1] == ITAL ? "\\|" : "");
	after = ebase[p1] - VERT( EM(0.2, ps) );
	if (spaceval == NULL && after > 0)
		printf("\\x'%du'", after);
	putchar('\n');
	eqnreg = p1;
	if (spaceval != NULL) {
		free(spaceval);
		spaceval = NULL;
	}
}

max(i,j) int i,j; {
	return (i>j ? i : j);
}

oalloc() {
	int i;
	for (i=11; i<100; i++)
		if (used[i]++ == 0) return(i);
	error( FATAL, "no eqn strings left", i);
	return(0);
}

ofree(n) int n; {
	used[n] = 0;
}

setps(p) int p; {
	printf(".ps %d\n", EFFPS(p));
}

nrwid(n1, p, n2) int n1, p, n2; {
	printf(".nr %d \\w'\\s%d\\*(%d'\n", n1, EFFPS(p), n2);
}

I 7
char *getenv();

E 7
setfile(argc, argv) int argc; char *argv[]; {
	static char *nullstr = "-";
I 7
	char *cp;
E 7

I 7
	if ((cp = getenv("PRINTER"))) device = cp;
	if ((cp = getenv("TYPESETTER"))) device = cp;
E 7
	svargc = --argc;
	svargv = argv;
	while (svargc > 0 && svargv[1][0] == '-') {
		switch (svargv[1][1]) {

		case 'd': lefteq=svargv[1][2]; righteq=svargv[1][3]; break;
		case 's': gsize = atoi(&svargv[1][2]); break;
		case 'p': deltaps = atoi(&svargv[1][2]); break;
		case 'r': res = atoi(&svargv[1][2]); break;
		case 'm': minsize = atoi(&svargv[1][2]); break;
		case 'f': gfont = svargv[1][2]; break;
		case 'e': noeqn++; break;
I 4
		case 'P':
E 4
D 2
		case 'T':
			if (strcmp(&svargv[1][2], "202") == 0)
				{res = 972; minsize = 5; ttype = DEV202; }
			else if (strcmp(&svargv[1][2], "aps") == 0)
				{res = 723; minsize = 5; ttype = DEVAPS; }
			else if (strcmp(&svargv[1][2], "cat") == 0)
				{res = 432; minsize = 6; ttype = DEVCAT; }
			else if (strcmp(&svargv[1][2], "ver") == 0)
				{res = 200; minsize = 6; ttype = DEVCAT; }
			else
				error(FATAL, "unknown typesetter %s", &argv[1][2]);
			break;
E 2
I 2
		case 'T': device = &(svargv[1][2]); break;
		case 'F': devdir = &(svargv[1][2]); break;
E 2
		default: dbg = 1;
		}
		svargc--;
		svargv++;
	}
I 2

	fileinit();
E 2
	ifile = 1;
	linect = 1;
	if (svargc <= 0) {
		curfile = stdin;
		svargv[1] = nullstr;
	}
	else if ((curfile = fopen(svargv[1], "r")) == NULL)
		error( FATAL,"can't open file %s", svargv[1]);
I 2
}

fileinit()
{
	int fin;
	short readmin;
	struct dev device_info;
	char temp[100];

	sprintf(temp, "%s/dev%s/DESC.out", devdir, device);
	if ((fin = open(temp, 0)) < 0) {
	    fprintf(stderr, "can't open tables for %s\n", temp);
	    exit(1);
	}
	read(fin, &device_info, sizeof(struct dev));
	read(fin, &readmin, sizeof readmin);

		/* if res and minsize were not set by option, do it now */
	if (res <= 0) res = device_info.res;
	if (minsize <= 0) minsize = readmin;
I 6
	minvert = device_info.vert;
E 6
	close(fin);
E 2
}

yyerror() {;}

init() {
	ct = 0;
	ps = gsize;
	ft = gfont;
	setps(ps);
	printf(".ft %c\n", ft);
}

error(fatal, s1, s2) int fatal; char *s1, *s2; {
	if (fatal>0)
		printf("eqn fatal error: ");
	printf(s1,s2);
	printf("\nfile %s, between lines %d and %d\n",
		 svargv[ifile], eqline, linect);
	fprintf(stderr, "eqn: ");
	if (fatal>0)
		fprintf(stderr, "fatal error: ");
	fprintf(stderr, s1, s2);
	fprintf(stderr, "\nfile %s, between lines %d and %d\n",
		 svargv[ifile], eqline, linect);
	if (fatal > 0)
		eqnexit(1);
}
E 1
