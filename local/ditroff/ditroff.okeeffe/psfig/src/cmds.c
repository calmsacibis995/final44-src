/***	
 ***	cmds.c --
 ***	
 ***	Handle parsing of commands for psfig.
 ***	
 ***	T.Darrell, 3/86.
 ***/

# include "psfig.h"
# include "item.h"

int	Draft = DraftDefault;

int	inLineFlag = 0;		/* are we generating an in-line figure? */

/* 
 * dofigcmd()
 */

dofigcmd()
{
	int		end = 0;
	int		didsome = 0;
	int		global = 0;
	static char	cmdbuf[SMBUFSZ];
	static char	bigbuf[BUFSIZ];

	while (!end) {
		switch (getItem(cmdbuf)) {

		case iEndOfInput:
			++end;
		case iSeparator:			
			break;

		case iDefine:
			switch (getItem(cmdbuf)) {
			case iEndOfInput:
			case iSeparator:
				error("empty define");

			case iWord:
				if (getString(bigbuf, sizeof(bigbuf))) {
					addMacro(cmdbuf, bigbuf);
				} else {
					deleteMacro(cmdbuf);
				}
				break;

			default:
				error("can't define a keyword");
			}
			break;

		case iDelim:
			switch (getItem(cmdbuf)) {
			case iEndOfInput:
				++end;
			case iSeparator:
				delimSt = delimEnd = 0;
				break;

			case iWord:
				delimSt = cmdbuf[0];
				if (cmdbuf[1])
					delimEnd = cmdbuf[1];
				else
					delimEnd = delimSt;
				break;
			}
			break;

		case iSpace:
			switch(getItem(cmdbuf)) {
			case iWord:
				saveSpaceH(cmdbuf);
				didsome++;
				break;
			default:
				error("bad space command");
			}
			break;

		case iLiteral:

			if (!getString(bigbuf, sizeof(bigbuf))) 
				break;

			for (;;) {
				switch (getItem(cmdbuf)) {
				case iLevel:
					if (getItem(cmdbuf) != iWord)
						error("bad level in literal");
					if (atoi(cmdbuf) < Draft) {
						++didsome;
						emitLiteral(bigbuf);
					}
					continue;

				case iGlobal:
					++global;
					emitLiteral("globalstart");
					continue;

				default:
					if (didsome) {
						unGetItem(cmdbuf);
						break;
					}
					if (inLineFlag) {
						if (InLineLevel < Draft) {
							emitLiteral(bigbuf);
							++didsome;
						}
					} else {
						if (BrokenOutLevel < Draft) {
							emitLiteral(bigbuf);
							++didsome;
						}
					}
	
					unGetItem(cmdbuf);
					break;
				}
				break;
			}
			if (global) {
				emitLiteral("globalend");
				global = 0;
			}
			break;

		case iFile:
			*bigbuf = 0;
			if (getItem(bigbuf) != iWord)
				error("bad file command");

			for (;;) {
				switch (getItem(cmdbuf)) {
				case iLevel:
					if (getItem(cmdbuf) != iWord)
						error("bad level in literal");
					if (atoi(cmdbuf) < Draft) {
						includeFile(abspath(bigbuf));
						++didsome;
					}
					continue;

				case iGlobal:
					++global;
 					emitLiteral("globalstart");
					continue;
	
				default:
					if (inLineFlag) {
						if (InLineLevel < Draft) {
						  includeFile(abspath(bigbuf));
						  ++didsome;
						}
					} else {
						if (BrokenOutLevel < Draft) {
						  includeFile(abspath(bigbuf));
						  ++didsome;
						}
					}
					unGetItem(cmdbuf);
					break;
				}
				break;
			}
			if (global) {
				emitLiteral("globalend");
				global = 0;
			}

			break;
			
		case iFigure:
			includeFig();
			didsome++;
			break;

		case iWord:
			unGetItem(cmdbuf);
			includeFig();
			didsome++;
			break;

		default:
			error("unknown command");
		}
	}

	return didsome;
}


/* 
 * includeFig:
 * 
 * Appends the ditroff code needed to save space for figure specifed by the
 * 'file' command in cmd to dStr, and returns the new string.
 * 
 * The ditroff commands leave the "pen" in the upper right hand corner.
 */

static char path[SMBUFSZ], filenm[SMBUFSZ];
static char x[SMBUFSZ], y[SMBUFSZ];	/* postscript size */
static char rx[SMBUFSZ], ry[SMBUFSZ];	/* ditroff reserve size */
int doClip;
int nbox, draftlvl;
int bflag;				/* have bounds been set? */
float bb_llx, bb_lly, bb_urx, bb_ury;
char head[BUFSZ], foot[BUFSZ];		/* things to do before and
					 * after the figure is inlcluded
					 * (arguments, etc...)
					 */
char *
includeFig()
{
	float		fx, fy;

	bflag = 0;

	parse();

	(void) strcpy(filenm, abspath(path));

	/* 
	 * If no size was specified, use size from file (in points).
	 * If only a width was specified, calculate
	 * 	height = fileheight * (width / filewidth).
	 * If only a height, calculate
	 * 	width = filewidth * (height / fileheight).
	 */

	if (!bflag) {
		getFileBB(filenm, &bb_llx, &bb_lly, &bb_urx, &bb_ury);
	}

	fx = bb_urx - bb_llx;
	fy = bb_ury - bb_lly;
	
	if (!*x && !*y) {
		(void) sprintf(x, "%.2fp", fx);
		(void) sprintf(y, "%.2fp", fy);
	} else if (!*x) {
		(void) sprintf(x,"(%.2fp*%s/%.2fp)", fx, y, fy);
	} else if (!*y) {
		(void) sprintf(y,"(%.2fp*%s/%.2fp)", fy, x, fx);
	}

	/* 
	 * If reserve size was ommited, = figure size
	 */
	
	if (*rx == 0) 
		(void) strcpy(rx, x);
	if (*ry == 0)
		(void) strcpy(ry, y);


	if (draftlvl >= Draft) {

		if (!inLineFlag && strcmp(ry, "0")) {
			draftNote(path);
			makeBox(rx, ry);
		} else {
			if (strcmp(ry,"0"))
				saveSpaceV(ry, (inLineFlag ? UP : DOWN));

			saveSpaceH(rx);
		}
				
	} else {

		if (inLineFlag) 
			moveUp(y);

		startfig(x, y, bb_llx, bb_lly, bb_urx, bb_ury);
		if (doClip) emitDoClip();
		fputs(head, stdout);
		includeFile(filenm);
		fputs(foot, stdout);
		endfig();		

		/* Dont save space if == "0" */
		if (strcmp(ry, "0"))
			saveSpaceV(ry, (inLineFlag ? UP : DOWN));
		saveSpaceH(rx);

		if (inLineFlag)
			moveDown(y);
	}
}

/* 
 * parse:
 * 
 * parse file command.
 */

parse()
{
	int		end = 0;
	int		foundPath = 0;
	static char	tmpbuf[SMBUFSZ];
	static char	word[SMBUFSZ];

	/* 
	 *  initialize all values to their defaults,
	 *  then fill them in as specifed on the cmd line.
	 */

	strcpy(head, strcpy(foot, ""));

	if (inLineFlag)
		draftlvl = InLineLevel;
	else
		draftlvl = BrokenOutLevel;
	nbox = 0;
	doClip = 0;

	(void) strcpy(rx, strcpy(x, strcpy(y, "")));

	/* 
	 * If we are in-line, set default vert. reserve to nothing ("0")
	 * otherwise, set default reserve to NULL, which signals
	 * it should later be filled in with x,y.
	 */
	if (inLineFlag)
		(void) strcpy(ry, "0");
	else
		(void) strcpy(ry, "");

	while (!end) {
		switch(getItem(word)) {
			case iHeight:
				if (getItem(y) != iWord)
					error("bad height");
				break;
			case iWidth:
				if (getItem(x) != iWord)
					error("bad width");
				break;
			case iReserve:
				if (getItem(rx) != iWord) {
					unGetItem(rx);
					(void) strcpy(rx, strcpy(ry, ""));
					break;
				}
				if (getItem(ry) != iWord)
					error("bad reserve");
				break;
			case iClip:
				++doClip;
				break;
			case iLevel:
				if (getItem(tmpbuf) != iWord)
					error("bad level");
				draftlvl = atoi(tmpbuf);
				break;
			case iBounds:
				if (getItem(tmpbuf) != iWord)
					error("bad bounds");
				sscanf(tmpbuf, "%f", &bb_llx);
					
				if (getItem(tmpbuf) != iWord)
					error("bad bounds");
				sscanf(tmpbuf, "%f", &bb_lly);
	
				if (getItem(tmpbuf) != iWord)
					error("bad bounds");
				sscanf(tmpbuf, "%f", &bb_urx);
	
				if (getItem(tmpbuf) != iWord)
					error("bad bounds");
				sscanf(tmpbuf, "%f", &bb_ury);
				++bflag;
				break;
			case iLeftBrace:
				parse_format();
				break;
			case iEndOfInput:
			case iSeparator:
				++end;
				break;
			case iWord:
				if (!foundPath) {
					strcpy(path, word);
					++foundPath;
					break;
				}
				/* flow through */
			default:
				unGetItem(word);
				++end;
				break;
		}
	}

	/* 
	 * Make sure we have a file name.
	 */

	if (!foundPath) {
		error("missing file name in figure command");
	}
}

parse_format() {
	static char word[SMBUFSZ];
	int pre = 1; /* true until `figure' is encountered */

	for (;;) switch (getItem(word)) {

		case iFile :
			if (getItem(word) != iWord)
				error("bad file command in format");

			sIncludeFile((pre ? head : foot), abspath(word),BUFSZ);
			break;

		case iLiteral :
			if (!getString(word, sizeof(word)))
				error("bad literal in format");

			sEmitLiteral((pre ? head : foot), word, BUFSZ);
			break;

		case iFigure :
			pre = 0;
			break;

		case iRightBrace:
			return;

		default :
			error("bad command in format");
	}
}
/* end of cmds.c */
