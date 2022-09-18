h61446
s 00000/00000/00021
d D 8.1 93/06/04 16:31:51 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00021/00000/00000
d D 5.1 90/05/03 17:47:40 bostic 1 0
c date and time created 90/05/03 17:47:40 by bostic
e
u
U
t
T
I 1
/*
 * Definitions etc. for regexp(3) routines.
 *
 * Caveat:  this is V8 regexp(3) [actually, a reimplementation thereof],
 * not the System V one.
 */
#define NSUBEXP  10
typedef struct regexp {
	char *startp[NSUBEXP];
	char *endp[NSUBEXP];
	char regstart;		/* Internal use only. */
	char reganch;		/* Internal use only. */
	char *regmust;		/* Internal use only. */
	int regmlen;		/* Internal use only. */
	char program[1];	/* Unwarranted chumminess with compiler. */
} regexp;

extern regexp *regcomp();
extern int regexec();
extern void regsub();
extern void regerror();
E 1
