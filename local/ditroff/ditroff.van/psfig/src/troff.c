/***	
 ***	troff.c --
 ***	
 ***	Functions to output perverted Troff command strings for psfig.
 ***	
 ***	T.Darrell, 3/86.
 ***/

# include "psfig.h"

/* 
 * Ditroff output format strings.
 */

char saveSpaceDown_s[] = "\\x'%s'";
char saveSpaceUp_s[] = "\\x'-(%s-\\n(.vu)'";

saveSpaceV(y, sign)
char	*y;
int	sign;
{
	if (sign == UP)
		printf(saveSpaceUp_s, y);
	else
		printf(saveSpaceDown_s, y);
}


char incl_file_s[] = "\\X'f%s'";
includeFile(filenm)
char *filenm; {
	printf(incl_file_s, filenm);
}

sIncludeFile(outbuf, filenm, len)
int len;
char *filenm; {
	sprintf(endof(outbuf), incl_file_s, filenm);
	if (strlen(outbuf) > len)
		error("buffer overflow");
}

char endfig_s[] = "\\X'pendFig'";
endfig() {
	printf(endfig_s);
}

char startfig_s[] =
"\\X'p\\w@\\h@%s@@'\\X'p\\w@\\h@%s@@'\\X'p%.2f'\\X'p%.2f'\\X'p%.2f'\\X'p%.2f'\\X'pstartFig'";

startfig(x, y, llx, lly, urx, ury)
char	*x, *y;
float	llx, lly, urx, ury;
{
	flushX();
	printf(startfig_s, x, y, llx, lly, urx, ury);
}

emitDoClip() {
	printf("\\X'pdoclip'");
}

flushX()
{
	if (XFlush != NULL) {
		printf("\\z\\(%s", XFlush);
	}
}

char makeBoxDn_s_psditfix[] = 
"\\L'%s\\(br'\\v'+1p'\\l'%s\\(ul'\\v'-1p'\\L'-%s\\(br'\\v'+1p'\\l'-%s\\(ul'\\x'%s'\\v'-1p'";
char makeBoxDn_s[] = 
"\\L'%s\\(br'\\l'%s\\(ul'\\L'-%s\\(br'\\l'-%s\\(ul'\\x'%s'";

makeBox(x, y)
char	*x, *y; 
{
	if (psditfix)
		printf(makeBoxDn_s_psditfix, y, x, y, x, y);
	else
		printf(makeBoxDn_s, y, x, y, x, y);

}

char moveDown_s[] = "\\v'%s'";

moveDown(y)
char	*y;
{
	printf(moveDown_s, y);
}

char moveUp_s[] = "\\v'-%s'";

moveUp(y)
char	*y;
{
	printf(moveUp_s, y);
}

char draftNote_s[] = "\\v'1m'\\h'1n'%s\\h'-\\w'%s'u'\\h'-1n'\\v'-1m'";

draftNote(filenm)
char	*filenm;
{
	printf(draftNote_s, filenm, filenm);
}

char saveSpaceH_s[] = "\\h'%s'";

saveSpaceH(x)
char	*x;
{
	printf(saveSpaceH_s, x);
}

#define isWhite(ch) ((ch) == ' ' || (ch) == '\t' || (ch) == '\n')

char literal_s[] = "\\X'p%s'";
emitLiteral(text)
char *text; {
	static char litbuf[BUFSZ];

	*litbuf = 0;
	sEmitLiteral(litbuf, text, sizeof(litbuf));
	fputs(litbuf, stdout);
}

sEmitLiteral(outbuf, text, len)
int len;
char *outbuf, *text; {
	char *ptr = text;

	/* 
	 * print each word of the literal (stuff separated by whitespace)
	 * in a separate \X'p'
	 */
	
	while (isWhite(*ptr)) ++ptr;

	/* 
	 * find delimiting character
	 */
	
	while (*ptr) {

		/* 
		 * skip to next delimiting char.
		 */
		
		for (text = ptr; *ptr && !isWhite(*ptr); ++ptr) ;

		/* 
		 * termainate string here, print this piece, 
		 * then repeat on the rest of the string.
		 */

		if (!*ptr) {
			sprintf(endof(outbuf), literal_s, text);
			break;
		}
	
		*(ptr++) = 0;
		sprintf(endof(outbuf), literal_s, text);
	
		while (isWhite(*ptr)) ++ptr;
	}

	if (strlen(outbuf) > len) 
		error("buffer overflow");
}
	

/* end of troff.c */
