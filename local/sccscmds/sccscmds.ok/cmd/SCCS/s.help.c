h50554
s 00007/00008/00147
d D 4.4 90/11/11 08:56:57 bostic 4 3
c move binaries from /usr/local to /usr/local/bin
e
s 00002/00001/00153
d D 4.3 88/02/02 15:56:02 bostic 3 2
c sprintf doesn't return a pointer to it's first arg, anymore
e
s 00003/00003/00151
d D 4.2 87/02/15 20:57:54 lepreau 2 1
c modern syntax for asgops & inits cause Donn's latest ccom rejects the old.
e
s 00154/00000/00000
d D 4.1 81/01/15 00:16:36 eric 1 0
c date and time created 81/01/15 00:16:36 by eric
e
u
U
f b 
f i 
t
T
I 1
# include	"../hdr/defines.h"
I 4
# include	"pathnames.h"
E 4

D 2
SCCSID(%W%);
E 2
I 2
static char Sccsid[] = "%W%	%G%";
E 2

/*
	Program to locate helpful info in an ascii file.
	The program accepts a variable number of arguments.

	The file to be searched is determined from the argument. If the
	argument does not contain numerics, the search
	will be attempted on '/usr/local/lib/help/cmds', with the search key
	being the whole argument.
	If the argument begins with non-numerics but contains
	numerics (e.g, zz32) the search will be attempted on
	'/usr/local/lib/help/<non-numeric prefix>', (e.g,/usr/lib/help/zz),
	with the search key being <remainder of arg>, (e.g., 32).
	If the argument is all numeric, or if the file as
	determined above does not exist, the search will be attempted on
D 4
	'/usr/local/lib/sccs.hf', which is the old help file, with the
E 4
I 4
	_PATH_OLDHELP, which is the old help file, with the
E 4
	search key being the entire argument.
	In no case will more than one search per argument be performed.

	File is formatted as follows:

		* comment
		* comment
		-str1
		text
		-str2
		text
		* comment
		text
		-str3
		text

	The "str?" that matches the key is found and
	the following text lines are printed.
	Comments are ignored.

	If the argument is omitted, the program requests it.
*/
D 2
char	oldfile[]	"/usr/local/lib/sccs.hf";
char	helpdir[]	"/usr/local/lib/help/";
E 2
I 2
D 4
char	oldfile[] = "/usr/local/lib/sccs.hf";
char	helpdir[] = "/usr/local/lib/help/";
E 4
E 2
char	hfile[64];
FILE	*iop;
char	line [512];


main(argc,argv)
int argc;
char *argv[];
{
	register int i;
	extern int Fcnt;

	/*
	Tell 'fatal' to issue messages, clean up, and return to its caller.
	*/
	Fflags = FTLMSG | FTLCLN | FTLJMP;

	if (argc == 1)
		findprt(ask());		/* ask user for argument */
	else
		for (i = 1; i < argc; i++)
			findprt(argv[i]);

	exit(Fcnt ? 1 : 0);
}


findprt(p)
char *p;
{
	register char *q;
	char key[50];

	if (setjmp(Fjmp))		/* set up to return here from */
		return;			/* 'fatal' and return to 'main' */

	if (size(p) > 50)
		fatal("argument too long (he2)");

	q = p;

	while (*q && !numeric(*q))
		q++;

	if (*q == '\0') {		/* all alphabetics */
		copy(p,key);
D 4
		cat(hfile,helpdir,"cmds",0);
E 4
I 4
		cat(hfile,_PATH_HELPDIR,"cmds",0);
E 4
		if (!exists(hfile))
D 4
			copy(oldfile,hfile);
E 4
I 4
			copy(_PATH_OLDHELP,hfile);
E 4
	}
	else
		if (q == p) {		/* first char numeric */
			copy(p,key);
D 4
			copy(oldfile,hfile);
E 4
I 4
			copy(_PATH_OLDHELP,hfile);
E 4
		}
	else {				/* first char alpha, then numeric */
		copy(p,key);		/* key used as temporary */
		*(key + (q - p)) = '\0';
D 4
		cat(hfile,helpdir,key,0);
E 4
I 4
		cat(hfile,_PATH_HELPDIR,key,0);
E 4
		copy(q,key);
		if (!exists(hfile)) {
			copy(p,key);
D 4
			copy(oldfile,hfile);
E 4
I 4
			copy(_PATH_OLDHELP,hfile);
E 4
		}
	}

	iop = xfopen(hfile,0);

	/*
	Now read file, looking for key.
	*/
	while ((q = fgets(line,512,iop)) != NULL) {
		repl(line,'\n','\0');		/* replace newline char */
		if (line[0] == '-' && equal(&line[1],key))
			break;
	}

	if (q == NULL) {	/* endfile? */
		printf("\n");
D 3
		fatal(sprintf(Error,"%s not found (he1)",p));
E 3
I 3
		sprintf(Error,"%s not found (he1)",p);
		fatal(Error);
E 3
	}

	printf("\n%s:\n",p);

	while (fgets(line,512,iop) != NULL && line[0] == '-')
		;
	do {
		if (line[0] != '*')
			printf("%s",line);
	} while (fgets(line,512,iop) != NULL && line[0] != '-');

	fclose(iop);
}


ask()
{
	static char resp[51];

	iop = stdin;

	printf("msg number or comd name? ");
	fgets(resp,51,iop);
	return(repl(resp,'\n','\0'));
}


clean_up()
{
	fclose(iop);
}
E 1
