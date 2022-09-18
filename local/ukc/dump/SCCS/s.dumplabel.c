h57902
s 00015/00001/00389
d D 1.3 87/08/11 16:48:20 pc 3 2
c Alter to improve printed output and to write the hostname
e
s 00066/00050/00324
d D 1.2 87/08/08 16:53:25 pc 2 1
c Corrections - now it works (?)
e
s 00374/00000/00000
d D 1.1 87/08/08 01:10:09 pc 1 0
c date and time created 87/08/08 01:10:09 by pc
e
u
U
t
T
I 1
#ifndef lint
static char *sccsid = "%W% (UKC) %G%";
#endif not lint
/***

* program name:
	dumplabel.c
* function:
	prints the label from a header
	writes a dummy dump header at the start of a tape
	Doesn't do any checksum
* switches:
	-f <tapename>
	-r	rewind/offline each tape
	-l	label format
	followed by list of tape labels in the same format at given to the
		locally modified dump program
	if no tape labels are given print the details on the start of a tape
* libraries used:
	standard
* compile time parameters:
	cc -o dumplabel dumplabel.c
* history:
	Written August 1987 Peter Collinson UKC

***/
#include "dump.h"
#include <sys/ioctl.h>
#include <sys/mtio.h>

#define	LABMAX	100		/* get space for 100 */

char	*labarg[LABMAX];	/* vector of map entries */

char	*labfmt;		/* format for tape label */

int	labct;			/* number of entries */
				/* if zero then no labels used */

char *tape = "/dev/rmt8";

int	dorew;			/* set if rewind offline on exit */
int	tapecount;		/* number of tapes dealt with */

I 2
char	*index();
E 2

main(argc, argv)
char **argv;
{	register i;
	register char *p;
	while (--argc) {
		argv++;
		if (**argv == '-') {
			for (p = *argv; *p; p++)
				switch (*p) {

				case 'f':
					if (--argc > 0) {
						argv++;
						tape = *argv;
					}
					break;
				case 'r':
					dorew++;	/* no rewind/offline */
					break;
				case 'l':
					if (--argc > 0) {
						argv++;
						labfmt = *argv;
					}
				}
		} else {
D 2
			storelabelmap(arg);
E 2
I 2
			storelabelmap(*argv);
			if (labfmt && labct)
				if (index(labfmt, '%') == NULL)
					fprintf(stderr, "Warning - no format specifier (%%s) found in -l argument\n");
E 2
			for (i = 1; i <= labct; i++)
				dolabel(i);
			labct = 0;
		}
	}
	if (tapecount == 0) {
		if (labfmt) {
			labct = 0;
			dolabel(1);	/* pretend a volume number of 1 */
		} else
D 2
			printlabel()
E 2
I 2
			printlabel();
E 2
	}
	exit(0);
}

/*
 *	Store map list
 *	The map list 
 *	allows a simple way to specify a range of tapes
 *	This generates a string which is inserted into the label format
 *	by use of an sprint operation
 *
 *	The basic form here is:
 *	<string>			a single string
 *	<string>,<string>,......	a list of strings
 *	<string>-<string>		a range of strings
 *					where the string is `incremented'
 *					to generate a list
 */
storelabelmap(arg)
	char *arg;
{
	register char *ss, *es;
	register char *incbase, *incr;
	register lastc;
	char *labskip();
	char *strstore();

	/*
	 *	Parse the argument looking for a single string
	 */
D 2
	for (ss = arg; *ss; ss = es, labct++) {
E 2
I 2
	for (ss = arg; *ss; ss = es) {
E 2
		es = labskip(ss);
		lastc = *es;	/* save last character */
		*es++ = '\0';	/* make the first label into a string */
		if (labct > LABMAX)
			labfatal("Too many (> %d) tape labels specified\n", LABMAX);
I 2
		if (*ss == '\0')
			labfatal("Zero length label found\n");
E 2
		labarg[labct++] = strstore(ss);

		if (lastc == 0)
			break;		/* end of list */

		if (lastc == '-') {
			/*
			 * this gives a tape range
			 * increment the source number until it equals the final
			 * value
			 */
			incbase = ss;
			ss = es;
			es = labskip(ss);
			if (*es == '-')
				labfatal("Range has the format <string>-<string>\n");
			lastc = *es;
D 2
			*es = '\0';
E 2
I 2
			if (lastc)
				*es++ = '\0';
E 2
			/*
			 * basic test the source string length must be equal to the
			 * end string length
			 */
			if (strlen(incbase) != strlen(ss))
				labfatal("strlen(\"%s\") != strlen(\"%s\")\n", incbase, ss);
			labelrange(incbase, ss);
		}
	}
}

/*
 *	Expand a label range
 */
/* static */
labelrange(startrange, endrange)
	char *startrange, *endrange;
{
	register char *incr;
	register int carry;
	
	
	for (incr = startrange + strlen(startrange) - 1;
			strcmp(startrange, endrange) != 0; ) {
		/* start incrementing */
D 2
		for (carry = 0; carry; ) {
E 2
I 2
		carry = 0;
		do {
E 2
			if (isdigit(*incr)) {
				if (*incr == '9') {
					*incr = '0';
					carry = 1;
				} else
D 2
					*incr++;
E 2
I 2
					(*incr)++;
E 2
			} else
			if (isupper(*incr)) {
				if (*incr == 'Z') {
					*incr = 'A';
					carry = 1;
				} else
D 2
					*incr++;
E 2
I 2
					(*incr)++;
E 2
			} else
			if (islower(*incr)) {
				if (*incr == 'z') {
					*incr = 'a';
					carry = 1;
				} else
D 2
					*incr++;
E 2
I 2
					(*incr)++;
E 2
			} else
				labfatal("Problem with label map range spec - can only increment alphanumeric values\n");
			if (carry) {
				incr--;
				if (incr < startrange)
					labfatal("Problem with label map range spec - end of range reached\n");
			}
D 2
		}
E 2
I 2
		} while (carry);
		
E 2
		if (labct > LABMAX)
			labfatal("Too many (> %d) tape labels specified\n", LABMAX);
		labarg[labct++] = strstore(startrange);

	}
}

/*
 *	Store a string using malloc
 */
/* static */
char *
strstore(arg)
	char *arg;
{
	register len = strlen(arg)+1;
	register char *dest;
	char *malloc();

	dest = malloc(len);
	if (dest == NULL)
		labfatal("No memory for string storage\n");
	bcopy(arg, dest, len);
	return(dest);
}

/*
 *	Create a tape label from a volume number
 */
char *
createlabel(volno)
	int volno;
{
	static char buf[LBLSIZE+LBLSIZE];
D 2
	static int lastvol;
E 2
	char volbuf[8];
	register char *arg;
	
D 2
	if (userlabel == 0)
		return ("none");		/* previous behaviour */

	if (volno == lastvol)			/* cache */
		return(buf);
	lastvol = volno;
E 2
	
	if (labfmt == NULL)
		labfmt = "%s";

	if (labct == 0)
	{	(void) sprintf(volbuf, "%d", volno);
		arg = volbuf;
	}
	else		
		arg = labarg[volno-1];		/* volumes run 1-> */
	(void) sprintf(buf, labfmt, arg);
	buf[LBLSIZE-1] = '\0';			/* Truncate to correct size */
	return(buf);
}

/*
 *	skip forward looking for valid end of label characters
 */
char *
labskip(str)
register char *str;
{	while (*str != ',' && *str != '-' && *str)
		str++;
	return (str);
}

/*
 *	do the actual labelling
 */
dolabel(index)
{	register fd;

D 2
	if (tapecount++)
		askformount(index);
E 2
I 2
	tapecount++;
	askformount(index);
E 2

	while ((fd = open(tape, 2)) < 0)
	{	fprintf(stderr, "Tape open error\n");
		askformount(index);
	}
I 3
	if (spcl.c_host[0] == '\0') 
	{	gethostname(spcl.c_host, NAMELEN);
		spcl.c_level = 0;
		strcpy(spcl.c_filesys, "Tape has only been labelled");
		strcpy(spcl.c_dev, "???????????");
	}
E 3
	strcpy(spcl.c_label, createlabel(index));
	if (write(fd, (char *)&u_spcl, sizeof (u_spcl)) != sizeof (u_spcl))
	{	perror("Tape write error");
		exit(1);
	}
	rewind(fd);
	close(fd);
}

/*
 *	ask for a tape to be mounted
 */
askformount(index)
{
D 2
	while (query("Mount tape `%s'\nReady to go?", createlabel(index)) != 1);
E 2
I 2
	while (query("Mount tape `%s'\nReady to go? ", createlabel(index)) != 1);
E 2
}

/*
 *	ask yes/no question
 *	return	1 on yes
 *		0 on no
 */
query(question, arg)
char	*question;
char *arg;
{
	char	replybuffer[64];
	int	back;

D 2
	for(;;)
	{ 
E 2
I 2
	for(;;) {
E 2
		fprintf(stdout, question, arg);
		fflush(stdout);
D 2
		if (fgets(replybuffer, 63, stdin) == NULL)
		{	if(ferror(stdin))
			{	clearerr(stdin);
E 2
I 2
		if (fgets(replybuffer, 63, stdin) == NULL) {
			if(ferror(stdin)) {
				clearerr(stdin);
E 2
				continue;
			}
		}
D 2
		else
		if ((strcmp(replybuffer, "yes\n") == 0) ||
			    (strcmp(replybuffer, "Yes\n") == 0))
		{
			back = 1;
			goto done;
E 2
I 2
		else {
			qclean(replybuffer);
			if (strcmp(replybuffer, "yes") == 0 ||
			    strcmp(replybuffer, "y") == 0) {
				back = 1;
				goto done;
			}
			else
			if (strcmp(replybuffer, "no") == 0 ||
			    strcmp(replybuffer, "n") == 0) {
				if (query("Abort? "))
					labfatal("Aborting\n");
				back = 0;
				goto done;
			}
			else
				fprintf(stderr, "\"yes\" or \"no\" ONLY!\n");
E 2
		}
D 2
		else
		if ((strcmp(replybuffer, "no\n") == 0) ||
			    (strcmp(replybuffer, "No\n") == 0))
		{
			if (query("Abort? "))
				labfatal("Aborting\n");
			back = 0;
			goto done;
		}
		else
			fprintf(stderr, "\"Yes\" or \"No\" ONLY!\n");
E 2
	}
    done:
	return(back);
}

I 2
qclean(ptr)
	register char *ptr;
{
	for (;*ptr; ptr++) {
		if (isupper(*ptr))
			*ptr = tolower(*ptr);
		if (*ptr == '\n') {
			*ptr = '\0';
			break;
		}
	}
}
			
E 2
rewind(fd)
{
	struct mtop mtop;
D 2
	if (dorew)
	{	mtop.mt_op = MTOFFL;
E 2
I 2

	if (dorew) {
		mtop.mt_op = MTOFFL;
E 2
		mtop.mt_count = 1;
		ioctl(fd, MTIOCTOP, &mtop);
	}
}

/*
 *	fatal error message routine
 */
labfatal(fmt, a1, a2, a3, a4, a5)
D 2
char	*fmt;
int	a1, a2, a3, a4, a5;
{	fprintf(stderr, fmt, a1, a2, a3, a4, a5);
E 2
I 2
	char	*fmt;
	int	a1, a2, a3, a4, a5;
{
	fprintf(stderr, fmt, a1, a2, a3, a4, a5);
E 2
	exit(1);
}

/*
 *	print the label from a tape
 */
printlabel()
{
	register fd;
	
D 2
	if ((fd = open(tape, 2)) < 0)
	{	perror("Tape open error");
E 2
I 2
	if ((fd = open(tape, 2)) < 0) {
		perror("Tape open error");
E 2
		exit(1);
	}
D 2
	if (read(fd, (char *)&u_spcl, sizeof u_spcl) < 0)
	{	perror("Tape read");
E 2
I 2
	if (read(fd, (char *)&u_spcl, sizeof u_spcl) < 0) {
		perror("Tape read");
E 2
		exit(1);
	}
D 3
	printf("%s\n", spcl.c_label);
E 3
I 3
	printf("Dump   date: %s", ctime(&spcl.c_date));
	printf("Dumped from: %s", ctime(&spcl.c_ddate));
	if (spcl.c_host[0] == '\0')
		return;
	printf("Level %d dump of %s on %s:%s\n",
		spcl.c_level, spcl.c_filesys, spcl.c_host, spcl.c_dev);
	printf("Label: %s\n", spcl.c_label);
	printf("Volume %d of the dump, starting at inode %d\n",
			spcl.c_volume, spcl.c_inumber);
E 3
	close(fd);
}
E 1
