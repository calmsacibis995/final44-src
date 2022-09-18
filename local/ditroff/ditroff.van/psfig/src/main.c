/***	
 ***	main.c --
 ***	
 ***	Central stuff for the psfig preprocessor.
 ***	
 ***	T.Darrell, 3/86.
 ***/

# include "psfig.h"

int	linenumber = 0;		/* line counter */

char	delimSt = 0,
	delimEnd = 0;		/* delimeters */

char	*XFlush = NULL;		/* The character to flush \X with */

char	*searchDirTable[MAXDIRS] = { "." };
int	dircnt = 0;

char	errbuf[SMBUFSZ];	/* temp buffer for error msg formatting */

int 	psditfix = TRUE;	/* use fix that compensates for the weird
					way psdit V2 draws lines (a point
					off here and there) 
				   "-t" option turns off this flag */

int 	newbb = TRUE;		/* search for bounding box comments the
					new way.
				   "-b" option turns off this flag */

/* 
 * error:
 * 
 * Print an error message, and leave.
 */

error(s)
char	*s;
{
	fprintf(stderr,"psfig: line %d: %s\n", linenumber, s);
	exit(1);
}
warn(s)
char	*s;
{
	fprintf(stderr,"psfig: line %d: warning -- %s\n", linenumber, s);
}

/* 
 * getaline:
 * 
 * A function that we can pass to the lineio level to get more lines when
 * processing .F+ .F- commands. Claims that there is no more input when it
 * hits a .F-.
 */

char *
getaline(buf)
char	*buf;
{
	if (getline(buf, BUFSZ, stdin) == NULL)
		return NULL;

	if (!strncmp(buf, FGEND, strlen(FGEND))) {
		ungetline(buf);
		return NULL;
	}

	return buf;
}

/* 
 * main:
 * 
 * The basic loop of the program is simply to read lines from the input, and
 * if thereare psfig commands to process, to process them. There are three
 * different ways to mark psfig commands:
 * 
 * 	1. Between .F+ and .F-
 * 	2. Between delimiter characters
 * 	3. The rest of a line that starts with .F=
 */

main(argc, argv)
int	argc;
char	*argv[];
{
	char		**argp;

	/* 
	 * Process arguments.
	 */
	
	argc--;
	argp = argv+1;

	while ((*argp)[0] == '-' && argc--) {
		switch ((*argp)[1]) {

		case 'd':	/* Specify draft level to run at */
			if ((*argp)[2] == '\0') {
				Draft = 0;
				break;
			} 
			*argp += 2;
			Draft = atoi(*argp);
			break;

		case 'f':	/* Ditroff bug: must flush before \X */
			XFlush = *argp + 2;
			if (strlen(XFlush) != 2) {
				XFlush = "ts";
			}
			break;

		case 't':	/* disable compensation for psdit's line drawing */
			psditfix = FALSE;
			break;

		case 'b':	/* use old bounding box comment search method */
			newbb = FALSE;
			break;
			
		case 'D':	/* add directory to search list */
			if (++dircnt > MAXDIRS)
				error("too many search directories");

			searchDirTable[dircnt] = strsave((*argp)+2);
			break;
		default:
			error("bad flag");
		}

		argp++;
	}
	
	searchDirTable[dircnt + 1] = NULL;

	/* 
	 * If we are flushing \X with a character, make sure it doesn't get
	 * printed.
	 */

	if (XFlush != NULL) {
		printf(".tr \\(%s \n", XFlush);
	}

	/* 
	 * Now we process files. No arguments means standard input. Otherwise,
	 * we just use the named files.
	 */
	
	if (argc == 0) {
		doit();
	} else {
		while (argc-- > 0) {
			if (!freopen(*argp++, "r", stdin)) {
				perror("error opening input file");
				exit(1);
			} else {
				clearerr(stdin);
				doit();
			}
		}
	}

	exit(0);
} /* main */

doit() {
	char		*ptr, *ptr1, *rest;
	char		*getaline();
	static char	buf[BUFSZ];

	while (getline(buf, sizeof(buf), stdin) != NULL) {
		
		if (!strncmp(buf, FGST, strlen(FGST))) {
			fputs(buf, stdout);			
			*buf = 0;
			setInput(buf, getaline);
			if (dofigcmd()) {
				(void) fputc('\n', stdout);
			}
			(void) getline(buf, sizeof(buf), stdin);
			fputs(buf, stdout);
			continue;
		}

		ptr = rest = buf;
		while (delimSt && (ptr1 = index(ptr, delimSt))) {
			ptr = ptr1;

			*(ptr++) = '\0';

			fputs(rest, stdout);

			if (rest = index(ptr, delimEnd)) {
				*(rest++) = '\0';
			} else {
				error("Unbalanced delimiters");
			}

			++inLineFlag;
			setInput(ptr, (char *(*)()) NULL);
			(void) dofigcmd();
			--inLineFlag; 
			ptr = rest;

		} 
		fputs(ptr, stdout);
	}
}

/* 
 * getFileBB:
 * 
 * Takes a file name and tries to find out what its bounding box is. If it
 * finds the info, it writes it into the four floats pointed to.
 */

getFileBB(filenm, llx, lly, urx, ury)
char	*filenm;
float	*llx, *lly, *urx, *ury;
{
	char	 	*bbcomment = "%%BoundingBox:";
	char 		*atend = "(atend)";
	char	 	*trailer = "%%Trailer";
	char 		*endcom = "%%EndComments";
	FILE		*psfile;
	static char	buf[BUFSZ];
	float		tllx, tlly, turx, tury;
	int		foundbb = FALSE;
	int		intrailer = FALSE;

	if (!(psfile = fopen(filenm, "r"))) {
		(void) sprintf(errbuf, "error opening file `%s'", filenm);
		error(errbuf);
	}

	(void) fgets(buf, sizeof(buf), psfile);
	if (strncmp(buf, "%!", 2)) {
		(void) sprintf(errbuf, "`%s' not a postscript file", filenm);
		error(errbuf);
	}



	if (newbb)
	     /* 
	      * Use full search for bb comment. Pays attention to
	      * "%%EndComments", "(atend)", and "%%Trailer"
	      */
	     
	     while (fgets(buf, sizeof(buf), psfile)) {

		/* If the first n chars of buf == %%BoundingBox: */
		if (!strncmp(buf, bbcomment, strlen(bbcomment))) {
			char *args = buf;
			args += strlen(bbcomment);
			while (*args == ' ') args++;
			if (!strncmp(args, atend, strlen(atend))) {
				/* 
				 * Scan for trailer section
				 */
				intrailer = FALSE;
				while (fgets(buf, sizeof(buf), psfile)) 
				    if (!strncmp(buf, trailer, strlen(trailer))) {
					intrailer = TRUE;
					break;
				    }
				if (!intrailer) {
					sprintf(errbuf, 
					 "%%%%Trailer not found in %s", filenm);
					error(errbuf);
					break;
				}
				/* 
				 * Now that we've fouind the trailer
				 * section, we can continue seaching from 
				 * the main while.
				 */
				continue;
			} 

			if (sscanf(args,"%f %f %f %f", &tllx, &tlly, &turx, &tury)
			       == 4) {
				/* 
				 * We found a match, now if we are in the
				 * header section we can leave straight away,
				 * since the *first* bb comment is the
				 * relevant one, but if we are in the trailer
				 * we have to keep going, since the *last*
				 * instance of a bb is the one we want to use.
				 * 
				 * At least so says the Adobe book.
				 */
				if (!intrailer) {
					*llx = tllx; *lly = tlly;
					*urx = turx; *ury = tury;
					foundbb = TRUE;
					fclose(psfile);
					return;
				} else {
					*llx = tllx; *lly = tlly;
					*urx = turx; *ury = tury;
					foundbb = TRUE;
					continue;
				}

			} 
			(void) sprintf(errbuf,
				"malformed bounding box comment in %s", filenm);
			error(errbuf);

		} /* endif the first n chars match %%BoundingBox */

		/* 
		 * If the first two characters aren't %% or %!, or
		 * if we reach %%EndComments, and we're not in the
		 * trailer, then we're done.
		 */
		if (intrailer) continue;

		if ((strncmp(buf, "%%", 2) && strncmp(buf, "%!", 2))
			|| !strncmp(buf, endcom, strlen(endcom)))
			break;
	    }
	else
	    /* 
	     * Use old (simple) search for bb comment.
	     */
	    
	    while (fgets(buf, sizeof(buf), psfile)) {
		if (sscanf(buf,"%%%%BoundingBox: %f %f %f %f",
						llx, lly, urx, ury) == 4) {
			fclose(psfile);
			return;
		}
	    }

	if (foundbb) {
		fclose(psfile);
		return;
	}

	(void) sprintf(errbuf,"no bounding box found in %s",filenm);
	error(errbuf);
}

/* 
 * abspath:
 * 
 * Return the absolute expansion of a path, searching all the relevant
 * directories.
 */

char *
abspath(path)
char	*path;
{
	static char	pathbuf[SMBUFSZ];
	static char	absbuf[SMBUFSZ];
	char		**searchDir = searchDirTable;

	if (!*path) return path;

	if (*path != '/') {
		/* 
		 * path is relative, so attempt to locate file
		 * in one of the search directories
		 */
		
		do {
			strcpy(pathbuf, *searchDir);
			strcat(pathbuf, "/");
			strcat(pathbuf, path);

			if (access(pathbuf, F_OK) >= 0) {
				/* 
				 * Now that we know where the file is, we make
				 * it absolute if necessary, and return it.
				 */

				if (*pathbuf != '/') {
					getwd(absbuf);
					strcat(absbuf, "/");
					strcat(absbuf, pathbuf);
					return absbuf;
				} else {
					return pathbuf;
				}
			}
		} while (*(++searchDir));

		/* 
		 * the file was not found in any of the 
		 * search directories, so notify the user
		 * and return the bare path
		 */

		sprintf(errbuf, "`%s' not found in search directories", path);
		warn(errbuf);
	}

	return path;
}

/* end of main.c */
