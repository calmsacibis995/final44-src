h46087
s 00039/00011/00339
d D 1.3 87/08/11 16:50:04 pc 3 2
c Revise the way label reading is done
e
s 00039/00066/00311
d D 1.2 87/08/08 16:50:17 pc 2 1
c Add label handling and rewind off line
e
s 00377/00000/00000
d D 1.1 87/08/07 18:38:13 pc 1 0
c date and time created 87/08/07 18:38:13 by pc
e
u
U
t
T
I 1
#ifndef lint
static char *sccsid = "%W% (UKC) %G%";
#endif not lint
/*
 *	This file included by Peter Collinson
 *	to handle tape labelling 
 *	There are two dump parameters which are used to specify labels
 *	-l	Give the basic label format string - this may contain 
 *		a single %s to insert the volume number string
 *	-m	Map string - used to map volume numbers into a string
 *
 *	Routines are:
 *	storelabel(arg)		- called from main() to store a label format
 *
 *	storelabelmap(arg)	- called from main() to process a map argument
 *				- which is
 *					string		simple string
 *					string-string	expanded by incrementing
 *					string,string,..list of the above
 *	char *
 *	createlabel(volno)	- returns a label appropriate for the volume
 *					
 *	initialtape()		- called to print an operator message asking for
 *				- the 1st tape 
 *	
 *	labelest(etapes)	- checks if there are enough tape labels
 *				- specified for a given dump
 *
 *	labelcheck()		- reads one record from tape
 *				- checks that the labels match
 *				- backspace one record back
 *				- so that multi-volume dumps work
 *
 *	log_volume()		- write a logfile entry for the volume
 *	
D 2
 *	This file also contains the rewind_offline() routine so that
 *	the tape can be dismounted at the end of each volume write
 *
E 2
 */

#include "dump.h"
D 2
#include <sys/ioctl.h>
#include <sys/mtio.h>
E 2
#include <math.h>


#define	LABMAX	100		/* get space for 100 */

char	*labfmt;		/* Basic tape format */

char	*labarg[LABMAX];	/* Pointer to argument list */

int	labct;			/* number of entries */
				/* if zero then no labels used */

I 2
int	userlabel;		/* set if user has given a label */

E 2
int	labchk;			/* check labels - set by t(est) flag */

/*
 *	The file /etc/dumpvolumes is used to maintain a log of
 *	tapes which are/have been used for tape dumping
 *	The format is:
 *	label: date dev=<devname> level=<dump level> reel=<volume number> inode=<start inode>
 */
char dumpvolumes[] = "/etc/dumpvolumes";

I 3
#ifdef RDUMP
extern char *host;
#endif RDUMP

E 3
/*
 *	Called from argument decoding to store the
 *	basic label format
 *	This is the parameter to the -l parameter
 */
storelabel(arg)
	char *arg;
{
D 2
	labelarg = arg;

E 2
I 2
	labfmt = arg;
	userlabel = 1;
E 2
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
I 2
	char *strstore();
E 2
	
I 2
	userlabel = 1;

E 2
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
D 2
		lablist[labct++] = strstore(ss);
E 2
I 2
		if (*ss == '\0')
			labfatal("Zero length tape label found\n");
		labarg[labct++] = strstore(ss);
E 2

D 2
		if (lastch == 0)
E 2
I 2
		if (lastc == 0)
E 2
			break;		/* end of list */

D 2
		if (lastch == '-') {
E 2
I 2
		if (lastc == '-') {
E 2
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
D 2
			lastch = *es;
			*es = '\0';
E 2
I 2
			lastc = *es;
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
D 2
		lablist[labct++] = strstore(startrange);
E 2
I 2
		labarg[labct++] = strstore(startrange);
E 2

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
I 2
	char *malloc();
E 2

	dest = malloc(len);
	if (dest == NULL)
		labfatal("No memory for string storage\n");
	bcopy(arg, dest, len);
	return(dest);
}
	
/*
 *	Create a tape label from a volume number
D 2
 *	if have not had a -l or -m parameter - return none
 *	if have not had a -l parameter - set format to %s
 *	if have not had a -m paramter - pass the volume number as a string
E 2
 */
char *
createlabel(volno)
	int volno;
{
	static char buf[LBLSIZE+LBLSIZE];
D 2
	static char volbuf[8];
E 2
	static int lastvol;
I 2
	char volbuf[8];
E 2
	register char *arg;
	
D 2
	if (labfmt == NULL && labct == 0)
E 2
I 2
	if (userlabel == 0)
E 2
		return ("none");		/* previous behaviour */

D 2
	if (volno == lastvol)
E 2
I 2
	if (volno == lastvol)			/* cache */
E 2
		return(buf);
D 2
			
	if (labelfmt == NULL)
		labelfmt = "%s";
E 2
I 2
	lastvol = volno;
	
	if (labfmt == NULL)
		labfmt = "%s";
E 2

	if (labct == 0)
	{	(void) sprintf(volbuf, "%d", volno);
		arg = volbuf;
	}
	else		
D 2
		arg = lablist[volno];
	(void) sprintf(buf, labelfmt, lablist[volno - 1]);	/* volumes run 1-> */
	buf[LBLSIZE-1] = '\0';
E 2
I 2
		arg = labarg[volno-1];		/* volumes run 1-> */
	(void) sprintf(buf, labfmt, arg);
	buf[LBLSIZE-1] = '\0';			/* Truncate to correct size */
E 2
	return(buf);
}

initialtape()
{	static firstpr;

	if (labchk == 0)
		return;
	if (firstpr == 0)
D 3
		msg("Mount tape %s for reel 1 of the dump\n", createlabel(0));
E 3
I 3
		msg("Mount tape %s for reel 1 of the dump\n", createlabel(1));
E 3
	firstpr = 1;
}

/*
 *	given an estimated number of tapes, check that
 *	there are enough tapes on the label list
 */
labelest(etapes)
	double etapes;
{	int et;

	if (labct) {
		et = ceil(etapes);
		if (et > labct)
			labfatal("Only %d labe%s given, estimated need %d\n",
				labct, labct == 1 ? "l" : "ls", et);
	}
}

/*
 *	labelcheck
 *	read a dump header and check that the tape header contains
 *	the label we expected
D 3
 *	close the fd on error to allow upper levels to loop
E 3
I 3
 *	close the tape after use
E 3
 */
D 3
labelcheck(fd, tno)
	int fd;
E 3
I 3
labelcheck(tno)
E 3
	int tno;
{	
D 3
	union u_spcl uin;	/* lots on the stack but that should be OK */
E 3
I 3
	register fd;
	union u_spcl uin;
E 3
	register char *label;
	register char *ontape = uin.s_spcl.c_label;
D 2
	struct mtop mtop;
E 2
D 3

E 3
I 3
	
E 3
	if (labchk == 0 || pipeout)
		return(0);
	label = createlabel(tno);
I 3

#ifdef RDUMP
	/* doing it this way to make it easier to read */
	if (host) {
		while (rmtopen(tape, 0) < 0)
			if (!query("Cannot open tape. Do you want to retry the open?"))
				dumpabort();
		if (rmtread((char *)&uin, sizeof uin) != sizeof uin) {
			msg("Tape does not start with the correctly sized record\n");
			(void)rmtclose();
			return(-1);
		}
		if (ontape[0] == '\0' ||
		    strcmp(ontape, "none") == 0 ||
		    strcmp(ontape, label) == 0) {
			(void)rmtclose();
			return(0);
		}
		msg("Tape labels do not match should be `%s' is `%s'\n", label, ontape);
		(void)rmtclose();
		return(-1);
	}
#endif RDUMP
	while ((fd = open(tape, 0)) < 0)
		if (!query("Cannot open tape. Do you want to retry the open?"))
			dumpabort();
E 3
	if (read(fd, (char *)&uin, sizeof uin) != sizeof uin) {
		msg("Tape does not start with the correctly sized record\n");
D 3
		close(fd);
E 3
I 3
		(void)close(fd);
E 3
		return(-1);
	}
	if (ontape[0] == '\0' ||
	    strcmp(ontape, "none") == 0 ||
	    strcmp(ontape, label) == 0) {
D 3
		/* skip back one record */
D 2
		mtop.mt_op = MTBSR;
		mtop.mt_count = 1;
#ifdef RDUMP
		if (rmtioctl(fd, MTIOCTOP, &mtop) < 0)
#else RDUMP
		if (ioctl(fd, MTIOCTOP, &mtop) < 0)
#endif RDUMP
E 2
I 2
		if (backone(fd) < 0)
E 2
			labfatal("Label check cannot backspace tape\n");
E 3
I 3
		(void)close(fd);
E 3
		return(0);
	}
	msg("Tape labels do not match should be `%s' is `%s'\n", label, ontape);
D 3
	close(fd);
E 3
I 3
	(void)close(fd);
E 3
	return(-1);
}

/*
 *	write a log entry for the volume into the log file
 */
D 2
log_volume()
E 2
I 2
log_volume(tlabel)
	char *tlabel;
E 2
{
	char *ctime();
	FILE *logfd;

	if (uflag == 0 || labchk == 0)
		return;
D 2
	if ((logfd = fopen(dumpvolume, "a")) == NULL)
E 2
I 2
	if ((logfd = fopen(dumpvolumes, "a")) == NULL)
E 2
		return;
	fprintf(logfd, "%s: date=%20.20s dev=%s level=%c reel=%d ino=%d\n",
			tlabel, ctime(&spcl.c_date)+4, disk, incno, tapeno,
			tapeno == 1 ? ROOTINO : ino);
	fclose(logfd);
}

/*
 *	skip forward looking for valid end of label characters
 */
/* static */
char *
labskip(str)
	register char *str;
{	
	while (*str != ',' && *str != '-' && *str)
		str++;
	return (str);
}

/*
 *	generate a fatal error message
 */
	/* VARARGS1 */
	/* ARGSUSED */
labfatal(fmt, a1, a2, a3, a4, a5)
	char	*fmt;
	int	a1, a2, a3, a4, a5;
{	
	msg(fmt, a1, a2, a3, a4, a5);
	dumpabort();
}

D 2

/*
 *	put a tape drive offline
 */
rewind_offline(fd)
{	
	struct mtop mtop;

#ifdef RDUMP
#define ioctl rmtioctl
#endif RDUMP

	mtop.mt_op = MTWEOF;
	mtop.mt_count = 1;
	if (ioctl(fd, MTIOCTOP, &mtop) < 0)
		perror("Cannot write end of file record");
	mtop.mt_op = MTWEOF;
	mtop.mt_count = 1;
	if (ioctl(fd, MTIOCTOP, &mtop) < 0)
		perror("Cannot write end of file record");
	mtop.mt_op = MTOFFL;
	mtop.mt_count = 1;
	if (ioctl(fd, MTIOCTOP, &mtop) < 0)
		perror("Cannot put the tape offline");
}
E 2
E 1
