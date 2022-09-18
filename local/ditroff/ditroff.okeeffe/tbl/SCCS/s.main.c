h31457
s 00000/00000/00176
d D 1.6 93/07/27 09:16:24 bostic 6 5
c checkpoint; Mike Karels left this checked out.
e
s 00007/00005/00169
d D 1.5 87/12/01 00:38:51 jaap 5 4
c Andries fixed the linedrawing, at least he says so
e
s 00011/00000/00163
d D 1.4 86/11/10 15:36:46 jaap 4 3
c Just updating
e
s 00011/00000/00152
d D 1.3 85/10/02 15:28:37 jaap 3 2
c tbl will now pick up the typesetter from environment, just like the
e
s 00026/00024/00126
d D 1.2 85/10/02 14:37:32 jaap 2 1
c Removed a lot of commented out debug code, takes now -d argument
c for debug output. some tidy up.
e
s 00150/00000/00000
d D 1.1 85/10/01 18:09:05 jaap 1 0
c date and time created 85/10/01 18:09:05 by jaap
e
u
U
t
T
I 1
#ifndef lint
D 5
static char sccsid[] = "%W% (CWI) %E%";
E 5
I 5
static char sccsid[] = "@(#)main.c	1.4 (CWI) 86/11/10";
E 5
#endif lint

D 2

 /* t1.c: main control and input switching */

E 2
/*
 * tbl troff preprocessor.
 *
 * Tidied, and changed by jna
 *
 */

#include <signal.h>
#include "defs.h"
#include "ext.h"

static int     sargc;
static char  **sargv;

main(argc, argv)
int	argc; char   *argv[];
{
	char line[BUFSIZ];
I 3
	register char *p;
	char *getenv();
E 3
	extern int badsig();

	signal(SIGPIPE, badsig);
I 3

	if (p = getenv("TYPESETTER")) {
		if(strcmp(p, "har") == 0)
			device = HARRIS;
		else if(strcmp(p, "ver") == 0)
			device = DEVVER;
I 4
		else if(strcmp(p, "psc") == 0)
			device = DEVPSC;
E 4
D 5
		else
			fprintf(stderr, "tbl: warning: unknown typesetter %s\n", p);
E 5
I 5
		/* johan doesnt want to see error messages in a context like
			TYPESETTER=1650.10 tbl files | eqn | nroff -ms
		so I removed the warning here. Besides, there is no complaint
		for an option -Tfoo either. */
E 5
	}
E 3

	tabin = stdin;
	sargv = ++argv;
	if((sargc = --argc) > 0)
		(void) swapin();

	while(gets1(line)){
		printf("%s\n", line);
		if(prefix(".TS", line))
			tableput();
	}
	fclose(tabin);
	return(0);
}

swapin()
{
	while(sargc > 0 && **sargv == '-'){
		if(strcmp("-ms", *sargv) == 0){
			*sargv = MACROS;
			break;
		}
		if(strcmp("-mm", *sargv) == 0){
			*sargv = PYMACS;
			break;
		}
		if(strcmp("-TX", *sargv) == 0){
			pr1403 = 1;
			sargc--;
			sargv++;
			break;
		}
		if(strcmp("-Thar", *sargv) == 0){
			device = HARRIS;
			sargc--;
			sargv++;
			break;
		}
		if(strcmp("-Tver", *sargv) == 0){
			device = DEVVER;
			sargc--;
			sargv++;
			break;
		}
I 4
		if(strcmp("-Tpsc", *sargv) == 0){
			device = DEVPSC;
			sargc--;
			sargv++;
			break;
		}
E 4
I 2
		if(strcmp("-d", *sargv) == 0){
			dbg++;
E 2
			sargc--;
			sargv++;
I 2
			break;
		}
D 5
			sargc--;
			sargv++;
E 5
I 5
		sargc--;
		sargv++;
E 5
E 2
	}
	if(sargc <= 0)
		return(0);
	if(tabin != stdin)
		(void) fclose(tabin);
	if(strcmp(*sargv, "-") == 0)
		tabin = stdin;
	else
		tabin = fopen(ifile = *sargv, "r");
	iline = 1;
	printf(".ds f. %s\n", ifile);
	/*
	 * support for .lf request (jna)
	 */
	printf(".lf 1 %s\n", ifile);
	if(tabin == NULL)
		error("Can't open file");
	sargc--;
	sargv++;
	return(1);
}

badsig()
{
	signal(SIGPIPE, SIG_IGN);
	exit(0);
}

D 2
 /* t2.c:  subroutine sequencing for one table */
E 2
tableput(){

	switch(device){
	case CAT:
D 2
		printf(".\\\" -- device CAT\n");
E 2
I 2
		dprint(".\\\" -- device CAT\n");
E 2
		break;
	case HARRIS:
D 2
		printf(".\\\" -- device HARRIS\n");
E 2
I 2
		dprint(".\\\" -- device HARRIS\n");
I 4
		break;
	case DEVPSC:
		dprint(".\\\" -- device PostScript\n");
E 4
E 2
		break;
	case DEVVER:
D 2
		printf(".\\\" -- device VERSATEC\n");
E 2
I 2
		dprint(".\\\" -- device VERSATEC\n");
E 2
		break;
	}
D 2
printf(".\\\" -- saveline\n");
E 2
I 2
	dprint(".\\\" -- saveline\n");
E 2
	saveline();
D 2
printf(".\\\" -- savefill\n");
E 2
I 2
	dprint(".\\\" -- savefill\n");
E 2
	savefill();
D 2
printf(".\\\" -- ifdivert\n");
E 2
I 2
	dprint(".\\\" -- ifdivert\n");
E 2
	ifdivert();
D 2
printf(".\\\" -- cleanfc\n");
E 2
I 2
	dprint(".\\\" -- cleanfc\n");
E 2
	cleanfc();
D 2
printf(".\\\" -- getcomm\n");
E 2
I 2
	dprint(".\\\" -- getcomm\n");
E 2
	getcomm();
D 2
printf(".\\\" -- getspec\n");
E 2
I 2
	dprint(".\\\" -- getspec\n");
E 2
	getspec();
D 2
printf(".\\\" -- gettbl\n");
E 2
I 2
	dprint(".\\\" -- gettbl\n");
E 2
	gettbl();
D 2
printf(".\\\" -- getstop\n");
E 2
I 2
	dprint(".\\\" -- getstop\n");
E 2
	getstop();
D 2
printf(".\\\" -- checkuse\n");
E 2
I 2
	dprint(".\\\" -- checkuse\n");
E 2
	checkuse();
D 2
printf(".\\\" -- choochar\n");
E 2
I 2
	dprint(".\\\" -- choochar\n");
E 2
	choochar();
D 2
printf(".\\\" -- maktab\n");
E 2
I 2
	dprint(".\\\" -- maktab\n");
E 2
	maktab();
D 2
printf(".\\\" -- runout\n");
E 2
I 2
	dprint(".\\\" -- runout\n");
E 2
	runout();
D 2
printf(".\\\" -- release\n");
E 2
I 2
	dprint(".\\\" -- release\n");
E 2
	release();
D 2
printf(".\\\" -- rstofill\n");
E 2
I 2
	dprint(".\\\" -- rstofill\n");
E 2
	rstofill();
D 2
printf(".\\\" -- endoff\n");
E 2
I 2
	dprint(".\\\" -- endoff\n");
E 2
	endoff();
D 2
printf(".\\\" -- restline\n");
E 2
I 2
	dprint(".\\\" -- restline\n");
E 2
	restline();
D 2
printf(".\\\" -- end off tableput\n");
E 2
I 2
	dprint(".\\\" -- end off tableput\n");
E 2
}
E 1
