/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
/*
 * C preprocessor generator
 *
 * options:
 *
 *	-m	generate machine dependent constant file
 *	-t	generate table file
 *
 * AT&T Bell Laboratories
 */

#define NOMACHDEP	1	/* don't include machdep.h in cpp.h	*/

#include "cpp.h"

extern char	*calloc();

main(argc, argv)
int	argc;
char	**argv;
{
	if (argc != 2) usage();
	else if (!strcmp(argv[1], "-m")) genmachdep();
	else if (!strcmp(argv[1], "-t")) gentable();
	else usage();
	exit(0);
}

usage()
{
	fprintf(stderr, "cppgen: -m or -t required\n");
	exit(1);
}

genmachdep()
{
	char		sc;
	unsigned char	uc;
	int		sz;

	printf("/*\n");
	printf(" * C preprocessor machine dependent definitions\n");
	printf(" *\n");
	printf(" * AT&T Bell Laboratories\n");
	printf(" */\n\n");

	/*
	 * buffer size
	 */

	printf("#define MAXBUF	%d	/* buffer size		*/\n",
		sizeof(int) == sizeof(long) && sizeof(int) >= 4 ? 4096 : 512);

	/*
	 * signed character offset
	 * NOTE: some compilers {apollo} produce (uc+1)==0
	 */

	sc = 0;
	sc = ~sc;
	uc = 0;
	uc = ~uc;
	sz = uc;
	sz++;
	printf("#define COFF	%d	/* signed char offset	*/\n",
		sc < 0 ? sz / 2 : 0);
	
	/*
	 * character set size
	 */

	printf("#define ALFSIZ	%d	/* character set size	*/\n", sz);
}

gentable()
{
	register char	*p;
	register int	c, coff;
	char		*fastab, *slotab, *toktyp;
	int		alfsiz;
	char		sc;
	unsigned char	uc;
	int		sz;

	/*
	 * signed character offset
	 * NOTE: some compilers {apollo} produce (uc+1)==0
	 */

	sc = 0;
	sc = ~sc;
	uc = 0;
	uc = ~uc;
	sz = uc;
	sz++;
	coff = sc < 0 ? sz / 2 : 0;

	/*
	 * character set size
	 */

	alfsiz = sz;

	/*
	 * allocate the tables
	 */

	fastab = calloc(alfsiz, sizeof(char));
	slotab = calloc(alfsiz, sizeof(char));
	toktyp = calloc(alfsiz, sizeof(char));

	/*
	 * initialize the tables
	 */

	p = "_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	while (c = *p++)
	{
		(fastab + coff)[c] |= IB | NB | SB;
		(toktyp + coff)[c] = IDENT;
	}
	p = "0123456789.";
	while (c = *p++)
	{
		(fastab + coff)[c] |= NB | SB;
                (toktyp + coff)[c] = NUMBR;
	}
	p = "\n\"'\\";
	while (c = *p++)
		(fastab + coff)[c] |= QB | SB;
#if CHECK_COMMENT
	p = ";)/*\n";
#else
	p = "*\n";
#endif
	while (c = *p++)
		(fastab + coff)[c] |= CB;
	(fastab + coff)['/'] |= SB;
	(fastab + coff)[WARN] |= WB | SB;
	(fastab + coff)['\0'] |= CB | QB | SB | WB;
	for (c = alfsiz; --c >= 0;)
		slotab[c] = fastab[c] | SB;
	p = " \t\v\f\r";	/* NOTE: no \n */
	while (c = *p++)
		(toktyp + coff)[c] = BLANK;
#if SPACE_SALT
	p = " \t\v\f\r";
#else
	p = "\v\f\r";
#endif
	while (c = *p++)
		(toktyp + coff)[c] = DELIM;

	/*
	 * output the tables
	 */

	printf("/*\n");
	printf(" * C preprocessor tables\n");
	printf(" *\n");
	printf(" * AT&T Bell Laboratories\n");
	printf(" */\n");
	tabout("fastab", fastab, alfsiz);
	tabout("slotab", slotab, alfsiz);
	tabout("toktyp", toktyp, alfsiz);
}

#define NPERROW		8		/* number of entries per row	*/

/*
 * output the table as character data
 */

tabout(name, tab, alfsiz)
char		*name;
register char	*tab;
{
	register int	i, j;

	printf("\n");
	printf("char %s[] =\n", name);
	printf("{");
	for (i = alfsiz, j = NPERROW; --i >= 0;)
	{
		if (j++ >= NPERROW)
		{
			printf("\n\t");
			j = 1;
		}
		printf("%03o", *tab++);
		if (i > 0) printf(", ");
	}
	if (j > 1) printf("\n");
	printf("};\n");
}
