h15530
s 00002/00002/00184
d D 8.1 93/06/06 14:56:46 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00177
d D 4.9 91/04/17 18:00:38 bostic 9 8
c new copyright; att/bsd/shared
e
s 00001/00001/00178
d D 4.8 91/03/01 14:33:07 bostic 8 7
c ANSI
e
s 00005/00004/00174
d D 4.7 90/02/21 10:58:21 bostic 7 6
c signal fixes, gcc/lint fixes, require directory reading subroutines
e
s 00004/00012/00174
d D 4.6 89/05/10 22:47:13 bostic 6 5
c file reorg, pathnames.h, paths.h
e
s 00002/00002/00184
d D 4.5 86/05/15 17:58:44 bloom 5 4
c updates from John Kunze
e
s 00001/00001/00185
d D 4.4 86/04/03 16:54:07 mckusick 4 3
c do not trash environment (from Steve Hubert <entropy!hubert@uw-beaver.arpa>)
e
s 00002/00002/00184
d D 4.3 83/05/16 17:19:50 jak 3 2
c added set window=23 to EXINIT so that vi scripts work
e
s 00066/00004/00120
d D 4.2 83/04/25 23:59:07 mckusick 2 1
c 
e
s 00124/00000/00000
d D 4.1 83/02/24 12:56:06 mckusick 1 0
c date and time created 83/02/24 12:56:06 by mckusick
e
u
U
t
T
I 9
/*-
D 10
 * Copyright (c) 1986 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
 * %sccs.include.proprietary.c%
 */

E 9
I 1
#ifndef lint
D 9
static char sccsid[] = "%W%	(Berkeley)	%G%";
#endif not lint
E 9
I 9
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 9

I 6
#include <sys/signal.h>
E 6
#include "stdio.h"
D 6
#include "signal.h"
E 6
I 6
#include "pathnames.h"
E 6

#define	EASY	1
#define	MEDIUM	2
#define	HARD	3
I 2
#define	EMAX	256
E 2

I 2
char *envp[EMAX+1];

/*
 * This routine edits the PATH environment variable so that
 * special commands that learners may need will be found.
 * EXINIT is modified so that the editor will always prompt,
 * will not print \r's, and will be usable with open mode.
 */

chgenv()
{
	register char **p;
	register int i;
	extern char **environ;
	extern char *direct;
	char path[BUFSIZ], exinit[BUFSIZ];
	char *malloc();

D 6
	sprintf(path, "PATH=%s/bin:/usr/cc/bin:/usr/ucb/bin:", direct);
E 6
I 6
D 8
	sprintf(path, _PATH_DEFPATH, direct);
E 8
I 8
	sprintf(path, "%s/bin:", direct);
E 8
E 6
D 3
	sprintf(exinit, "EXINIT=set prompt noopt open");
E 3
I 3
	sprintf(exinit, "EXINIT=set prompt noopt open window=23");
E 3
D 5
#if vax
E 5
I 5
#if BSD4_2
E 5
	system("stty old");
	for (p=environ,i=3; *p != 0 && i < EMAX; p++,i++)   {
#else
	for (p=environ,i=2; *p != 0 && i < EMAX; p++,i++)   {
#endif
		envp[i] = *p;
		if (**p != 'P' && **p != 'E')
			continue;
		if (strncmp(*p, "PATH=", 5) == 0)
			sprintf(path, "PATH=%s/bin:%s", direct, &envp[i--][5]);
		else if (strncmp(*p, "EXINIT=", 7) == 0)
D 3
			sprintf(exinit, "%s|set prompt noopt open", envp[i--]);
E 3
I 3
			sprintf(exinit, "%s|set prompt noopt open window=23", envp[i--]);
E 3
D 5
#if vax
E 5
I 5
#if BSD4_2
E 5
D 4
		else if (strncmp(*p, "PS1=", 4) == 0);
E 4
I 4
		else if (strncmp(*p, "PS1=", 4) == 0)
E 4
			i--;
	}
	envp[2] = malloc(7);
	strcpy(envp[2], "PS1=% ");
#else
	}
#endif
	envp[0] = malloc(strlen(path) + 1);
	strcpy(envp[0], path);
	envp[1] = malloc(strlen(exinit) + 1);
	strcpy(envp[1], exinit);
	envp[i] = 0;
	environ = envp;
}

E 2
mysys(s)
char *s;
{
	/* like "system" but rips off "mv", etc.*/
	/* also tries to guess if can get away with exec cmd */
	/* instead of sh cmd */
	char p[300];
	char *np[40];
	register char *t;
	int nv, type, stat;

	type = EASY;	/* we hope */
	for (t = s; *t && type != HARD; t++) {
		switch (*t) {
		case '*': 
		case '[': 
		case '?': 
		case '>': 
		case '<': 
		case '$':
		case '\'':
		case '"':
I 2
		case '`':
		case '{':
		case '~':
E 2
			type = MEDIUM;
			break;
		case '|': 
		case ';': 
		case '&':
			type = HARD;
			break;
		}
	}
	switch (type) {
	case HARD:
		return(system(s));
	case MEDIUM:
		strcpy(p, "exec ");
		strcat(p, s);
		return(system(p));
	case EASY:
		strcpy(p,s);
		nv = getargs(p, np);
		t=np[0];
		if ((strcmp(t, "mv") == 0)||
		    (strcmp(t, "cp") == 0)||
		    (strcmp(t, "rm") == 0)||
		    (strcmp(t, "ls") == 0) ) {
			if (fork() == 0) {
				char b[100];
				signal(SIGINT, SIG_DFL);
D 2
				strcpy(b, "/bin/");
				strcat(b, t);
E 2
				np[nv] = 0;
I 2
				execvp(t, np);
				perror(t);
D 6
			/*	sprintf(b, "/usr/ucb/bin/%s", t);
E 2
				execv(b, np);
D 2
				fprintf(stderr, "Execv failed\n");
E 2
I 2
				sprintf(b, "/usr/ucb/%s", t);
				execv(b, np);
				sprintf(b, "/bin/%s", t);
				execv(b, np);
				sprintf(b, "/usr/bin/%s", t);
				execv(b, np);
				perror(b); */
E 6
				fprintf(stderr, "Mysys:  execv failed on %s\n", np);
E 2
				exit(1);
			}
			wait(&stat);
			return(stat);
		}
		return(system(s));
	}
}

/*
 * system():
 *	same as library version, except that resets
 *	default handling of signals in child, so that
 *	user gets the behavior he expects.
 */

system(s)
char *s;
{
D 7
	int status, pid, w;
	register int (*istat)(), (*qstat)();
E 7
I 7
	register int pid, w;
	sig_t istat, qstat;
	int status;
E 7

	istat = signal(SIGINT, SIG_IGN);
	qstat = signal(SIGQUIT, SIG_IGN);
	if ((pid = fork()) == 0) {
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
D 2
		execl("/bin/sh", "sh", "-c", s, 0);
E 2
I 2
D 6
		execl("/bin/csh", "csh", "-cf", s, 0);
E 6
I 6
		execl(_PATH_CSHELL, "csh", "-cf", s, 0);
E 6
E 2
		_exit(127);
	}
	while ((w = wait(&status)) != pid && w != -1)
		;
	if (w == -1)
		status = -1;
D 7
	signal(SIGINT, istat);
	signal(SIGQUIT, qstat);
E 7
I 7
	(void)signal(SIGINT, istat);
	(void)signal(SIGQUIT, qstat);
E 7
	return(status);
}

getargs(s, v)
char *s, **v;
{
	int i;

	i = 0;
	for (;;) {
		v[i++]=s;
		while (*s != 0 && *s!=' '&& *s != '\t')
			s++;
		if (*s == 0)
			break;
		*s++ =0;
		while (*s == ' ' || *s == '\t')
			s++;
		if (*s == 0)
			break;
	}
	return(i);
}
E 1
