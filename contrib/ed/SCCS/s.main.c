h58856
s 00005/00005/00594
d D 8.1 93/05/31 14:29:43 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00598
d D 5.13 93/05/31 13:58:18 bostic 13 12
c fix 'l' to work on other than text -- from Rodney for 4.4BSD
e
s 00012/00006/00586
d D 5.12 93/05/11 12:07:55 bostic 12 11
c update from Rodney Ruddock (rodney@snowhite.cis.uoguelph.ca)
e
s 00015/00012/00577
d D 5.11 93/04/30 00:10:06 bostic 11 10
c update from Rodney Ruddock for 4.4BSD; bug fixes, plus reworking
c of the bang command to permit sh scripts from within ed, a la SunOS
e
s 00001/00001/00588
d D 5.10 93/04/28 18:20:34 bostic 10 9
c lint, "%?" isn't a valid format
e
s 00002/00001/00587
d D 5.9 93/04/28 18:18:23 bostic 9 8
c isatty(3) declared by unistd.h
e
s 00024/00006/00564
d D 5.8 93/04/28 18:07:11 bostic 8 7
c corrections for echoing the last command when "!!" is given,
c undo working when 0 or 1 lines were in the buffer before the last buffer
c modification, a RE interpretation correction; from Rodney Ruddock
e
s 00010/00006/00560
d D 5.7 93/03/18 12:17:33 bostic 7 6
c update from Rodney Ruddock
e
s 00022/00022/00544
d D 5.6 93/03/08 18:31:51 ralph 6 5
c changed start to Start and start_default to Start_default to
c avoid conflicts with start defined in crt0.o
e
s 00008/00005/00558
d D 5.5 93/03/01 17:01:24 bostic 5 4
c longjmp fixes
e
s 00001/00000/00562
d D 5.4 93/02/28 15:43:35 bostic 4 3
c lint
e
s 00044/00026/00518
d D 5.3 93/02/28 15:28:58 bostic 3 2
c some lint, some bug fixes, ^C handling improvements
c multiple access methods back in (yeeech!)
c new version from Rodney Ruddock (rodney@snowhite.cis.uoguelph.ca)
e
s 00458/00440/00086
d D 5.2 93/01/23 15:47:50 bostic 2 1
c reformat to KNF, prototype the world, fix lint bugs
e
s 00526/00000/00000
d D 5.1 93/01/23 11:13:18 bostic 1 0
c date and time created 93/01/23 11:13:18 by bostic
e
u
U
t
T
I 1
/*-
D 14
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
 *
 * This code is derived from software contributed to Berkeley by
 * Rodney Ruddock of the University of Guelph.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
I 8
D 14
char copyright[] =
"%Z% Copyright (c) 1992 The Regents of the University of California.\n\
 All rights reserved.\n";
E 14
I 14
static char copyright[] =
"%Z% Copyright (c) 1992, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 14
#endif /* not lint */

#ifndef lint
E 8
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

I 2
#include <sys/types.h>
I 3
#include <sys/ioctl.h>
E 3

I 9
#include <limits.h>
E 9
D 3
#include <db.h>
E 3
I 3
D 5
#include <limits.h>
E 5
E 3
#include <regex.h>
#include <setjmp.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
I 4
D 5
#include <unistd.h>
E 5
I 5
D 9
#include <limits.h>
E 9
I 9
#include <unistd.h>
E 9
E 5
E 4

I 3
#ifdef DBI
#include <db.h>
#endif

E 3
E 2
#include "ed.h"
I 2
#include "extern.h"
E 2

/*
 * This is where all of the "global" variables are declared. They are
 * set for extern in the ed.h header file (so everyone can get them).
 */

D 6
int nn_max, nn_max_flag, start_default, End_default, address_flag;
E 6
I 6
int nn_max, nn_max_flag, Start_default, End_default, address_flag;
E 6
D 3
int zsnum, filename_flag, add_flag=0;
E 3
I 3
int zsnum, filename_flag, add_flag=0, join_flag=0;
E 3
D 8
int help_flag=0;
E 8
I 8
D 11
int help_flag=0, gut_num;
E 11
I 11
int help_flag=0, gut_num=-1;
E 11
E 8
I 3
#ifdef STDIO
FILE *fhtmp;
int file_seek;
#endif
E 3

I 3
#ifdef DBI
E 3
D 2
#ifdef STDIO
FILE *fhtmp;
int file_seek;
#endif

#ifdef DBI
E 2
DB *dbhtmp;
I 3
#endif
E 3
D 2
#endif
E 2

LINE *nn_max_start, *nn_max_end;

struct MARK mark_matrix[26]; /* in init set all to null */ 

char *text;
I 8
LINE **gut=NULL;
E 8
char *filename_current, *prompt_string=NULL, help_msg[130];
char *template=NULL;
int prompt_str_flg=0, start_up_flag=0, name_set=0;

D 6
LINE *top, *current, *bottom, *start, *End; 
E 6
I 6
LINE *top, *current, *bottom, *Start, *End; 
E 6
struct u_layer *u_stk;
struct d_layer *d_stk;
LINE *u_current, *u_top, *u_bottom;
int u_set;
regex_t RE_comp;
regmatch_t RE_match[RE_SEC];
int RE_sol=0, RE_flag=0;
char *RE_patt=NULL;

int ss; /* for the getc() */
D 8
int explain_flag=1, g_flag=0, GV_flag=0, printsfx=0;
E 8
I 8
int explain_flag=1, g_flag=0, GV_flag=0, printsfx=0, exit_code=0;
E 8
long change_flag=0L;
int line_length;
D 2
jmp_buf ctrl_position; /* for SIGnal handling */
E 2
I 2
D 3
jmp_buf ctrl_position; 		/* For SIGnal handling. */
E 2
int sigint_flag, sighup_flag, sigspecial;
E 3
I 3
D 5
jmp_buf ctrl_position, ctrl_position2; /* For SIGnal handling. */
int sigint_flag, sighup_flag, sigspecial=0, sigspecial2=0;
E 5
I 5
jmp_buf ctrl_position, ctrl_position2, ctrl_position3; /* For SIGnal handling. */
int sigint_flag, sighup_flag, sigspecial=0, sigspecial2=0, sigspecial3=0;
E 5
E 3

D 2
/* SIGINT is never turned off. We flag it happened and then pay attention
 * to it at certain logical locations in the code
 * we don't do more here cause some of our buffer pointer's may be in
 * an inbetween state at the time of the SIGINT. So we flag it happened,
 * let the local fn handle it and do a jump back to the cmd_loop
 */
sigint_handler()
E 2
I 2
static void sigint_handler __P((int));
static void sighup_handler __P((int));
E 2

I 2
/*
 * Starts the whole show going. Set things up as the arguments spec
 * in the shell and set a couple of the global variables.
 *
 * Note naming viol'n with errnum for consistancy.
 */
int
main(argc, argv)
	int argc;
	char *argv[];
E 2
{
D 2
  sigint_flag = 1;
  if (sigspecial)  /* unstick when SIGINT on read(stdin) */
    SIGINT_ACTION;
} /* end-sigint_handler */
E 2
I 2
D 3
	int l_num, l_ret, errnum = 0, l_err = 0;
	char *l_fnametmp, l_bp[1024], *l_term;
E 3
I 3
D 12
	int l_num, errnum = 0, l_err = 0;
E 12
I 12
	int l_num, errnum=0, l_err=0;
E 12
D 7
	char *l_fnametmp, *l_col;
E 7
I 7
	char *l_fnametmp, *l_col, buf[2];
E 7
	struct winsize win;
E 3
E 2

I 7
	setbuffer(stdin, buf, 1);
E 7
D 2
sighup_handler()
E 2
I 2
D 3
	l_term = getenv("TERM");
	l_ret = tgetent(l_bp, l_term);
	if (l_ret < 1)
		line_length = 78;	/* Reasonable number for all term's. */
	else
		if ((line_length = tgetnum("co") - 1) < 2)
			line_length = 78;
E 3
I 3
	line_length = ((l_col = getenv("COLUMNS")) == NULL ? 0 : atoi(l_col));
D 8
	if (line_length == 0 && isatty(STDOUT_FILENO) &&
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &win) != -1)
E 8
I 8
	if ((line_length == 0 && isatty(STDOUT_FILENO) &&
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &win) != -1))
E 8
		line_length = win.ws_col;
	if (line_length == 0)
		line_length = 78;
I 13
	line_length -= 3;	/* for the octal to break properly in 'l' */
E 13
E 3
E 2

D 2
{
  fprintf(stderr,"\n  SIGHUP \n");
  sighup_flag = 1;
  undo();
  do_hup(); /* we shouldn't return from here */
  SIGHUP_ACTION; /* it shouldn't get here */
} /* end-sighup_handler */
E 2
I 2
D 6
	start = End = NULL;
E 6
I 6
	Start = End = NULL;
E 6
	top = bottom = NULL;
	current = NULL;
	nn_max_flag = 0;
	nn_max_start = nn_max_end = NULL;
	l_fnametmp = calloc(FILENAME_LEN, sizeof(char));
	if (l_fnametmp == NULL)
		ed_exit(4);
	text = calloc(NN_MAX_START + 2, sizeof(char));
	if (text == NULL)
		ed_exit(4);
D 6
	start_default = End_default = 0;
E 6
I 6
	Start_default = End_default = 0;
E 6
	zsnum = 22;		/* for the 'z' command */
I 11
	help_msg[0] = '\0';
E 11
	u_stk = NULL;
	d_stk = NULL;
	u_current = u_top = u_bottom = NULL;
	u_set = 0;		/* for in d after a j */
	filename_flag = 0;
	filename_current = NULL;
E 2

I 2
	l_num = 1;
	for (;;) {
		/* Process the command line options */
		if (l_num >= argc)
			break;
		switch (argv[l_num][0]) {
		case '-':
			switch (argv[l_num][1]) {
			case '\0':	/* this is why 'getopt' not used */
			case 's':
				explain_flag = 0;
				break;
			case 'p':
				if (++l_num < argc) {
					prompt_string =
					    calloc(strlen(argv[l_num]),
					    sizeof(char));
					if (prompt_string == NULL)
						ed_exit(4);
					strcpy(prompt_string, argv[l_num]);
					prompt_str_flg = 1;
					break;
				}
				l_err = 1;
I 7
			case 'v':
#ifdef BSD
D 11
				printf("ed: in BSD mode:\n");
E 11
I 11
				(void)printf("ed: in BSD mode:\n");
E 11
#endif
#ifdef POSIX
D 11
				printf("ed: in POSIX mode:\n");
E 11
I 11
				(void)printf("ed: in POSIX mode:\n");
E 11
#endif
I 8
				break;
E 8
E 7
			default:
				l_err++;
				ed_exit(l_err);
			}
			break;
		default:
			if (name_set)
				ed_exit(3);
			strcpy(l_fnametmp, argv[l_num]);
			filename_current = l_fnametmp;
			name_set = 1;
			if (prompt_str_flg)
				break;
			/* default ed prompt */
			prompt_string = (char *) calloc(3, sizeof(char));
			strcpy(prompt_string, "*");
			break;
		}
		l_num++;
	}

	start_up_flag = 1;
	cmd_loop(stdin, &errnum);
	/* NOTREACHED */
}

E 2
/*
D 2
 * the command loop. What the command is that the user has specified
E 2
I 2
 * The command loop. What the command is that the user has specified
E 2
 * is determined here. This is not just for commands coming from
 * the terminal but any standard i/o stream; see the global commands.
 * Some of the commands are handled within here (i.e. 'H') while most
 * are handled in their own functions (as called).
 */
D 2

E 2
void
cmd_loop(inputt, errnum)
D 2

FILE *inputt;
int *errnum;

E 2
I 2
	FILE *inputt;
	int *errnum;
E 2
{
D 2
  int l_last, l_jmp_flag;
  LINE *l_tempp;
E 2
I 2
	LINE *l_tempp;
	int l_last, l_jmp_flag;
E 2

D 2
  l_last = 0;
E 2
I 2
D 3
	l_last = 0;
E 3
I 3
	l_last = 0; /* value in l_last may be clobbered (reset to = 0) by longjump, but that's okay */
E 3
E 2

D 2
  if (g_flag ==0) /* big, BIG trouble if we don't check! think. */
    {
      /* set the jump point for the signals */
      l_jmp_flag = setjmp(ctrl_position);
      signal(SIGINT, sigint_handler);
      signal(SIGHUP, sighup_handler);
      switch (l_jmp_flag)
            {
              case JMP_SET: break;
              case INTERUPT: /* some general cleanup not specific to the jmp pt */
                             sigint_flag = 0;
                             GV_flag = 0; /* safest place to do these flags */
                             g_flag = 0;
                             printf("?\n");
                             break;
              case HANGUP: /* shouldn't get here. */
                           break;
              default: fprintf(stderr, "Signal jump problem\n");
            }
      /* only do this once! */
      if (start_up_flag)
        {
          start_up_flag = 0;
          /* simulate the 'e' at startup */
          e2(inputt, errnum);
        }
    } /* end-if */
E 2
I 2
	if (g_flag == 0) {	/* big, BIG trouble if we don't check! think. */
		/* set the jump point for the signals */
		l_jmp_flag = setjmp(ctrl_position);
		signal(SIGINT, sigint_handler);
		signal(SIGHUP, sighup_handler);
		switch (l_jmp_flag) {
		case JMP_SET:
			break;
		/* Some general cleanup not specific to the jmp pt. */
		case INTERUPT:
			sigint_flag = 0;
			GV_flag = 0;	/* safest place to do these flags */
			g_flag = 0;
D 3
			printf("?\n");
E 3
I 3
D 11
			printf("\n?\n");
E 11
I 11
			(void)printf("\n?\n");
E 11
E 3
			break;
		case HANGUP:		/* shouldn't get here. */
			break;
		default:
			(void)fprintf(stderr, "Signal jump problem\n");
		}
		/* Only do this once! */
		if (start_up_flag) {
			start_up_flag = 0;
			/* simulate the 'e' at startup */
			e2(inputt, errnum);
I 12
			if (*errnum == 0)
				goto errmsg2;
E 12
		}
	}
	for (;;) {
		if (prompt_str_flg == 1)
			(void)printf("%s", prompt_string);
D 3
		sigspecial = 1;	/* see the SIGINT function above */
E 3
		ss = getc(inputt);
D 3
		sigspecial = 0;
E 3
		*errnum = 0;
D 6
		l_tempp = start = End = NULL;
		start_default = End_default = 1;
E 6
I 6
		l_tempp = Start = End = NULL;
		Start_default = End_default = 1;
E 6
E 2

D 2
  while (1)
       {

         if (prompt_str_flg == 1)
           printf("%s", prompt_string);
         sigspecial = 1;  /* see the SIGINT function above */
         ss = getc(inputt);
         sigspecial = 0;
         *errnum = 0;
         l_tempp = start = End = NULL;
         start_default = End_default = 1;

         while (1)
         {
         switch (ss)
               {
                 /* this isn't nice and alphabetical mainly because of
                  * retrictions with 'G' and 'V' (see ed(1)).
                  */
                 case 'd': d(inputt, errnum);
                           break;
                 case 'e':
                 case 'E': e(inputt, errnum);
                           break;
                 case 'f': f(inputt, errnum);
                           break;
                 case 'a': 
                 case 'c':
                 case 'i':
                 case 'g':
                 case 'G':
                 case 'v':
                 case 'V': if (GV_flag == 1)
                             {
                               strcpy(help_msg, "command `");
                               strncat(help_msg, &ss, 1);
                               strcat(help_msg, "' illegal in G/V");
                               *errnum = -1;
                               break;
                             }
                           switch (ss)
                                 {
                                   case 'a': a(inputt, errnum);
                                             break;
                                   case 'c': c(inputt, errnum);
                                             break;
                                   case 'i': i(inputt, errnum);
                                             break;
                                    default: g(inputt, errnum);
                                 } /* end-switch */
                           break;
                 case 'h': if (rol(inputt, errnum))
                             break;
                           printf("%s\n", help_msg);
                           *errnum = 1;
                           break;
                 case 'H': if (rol(inputt, errnum))
                             break;
                           if (help_flag == 0)
                             {
                               help_flag = 1;
                               printf("%?: %s\n", help_msg);
                             }
                           else
                             help_flag = 0;
                           *errnum = 1;
                           break;
                 case 'j': j(inputt, errnum);
                           break;
                 case 'k': set_mark(inputt, errnum);
                           break;
                 case 'l': l(inputt, errnum);
                           break;
                 case 'm': m(inputt, errnum);
                           break;
E 2
I 2
		/*
		 * This isn't nice and alphabetical mainly because of
		 * restrictions with 'G' and 'V' (see ed(1)).
		 */
		for (;;) {
			switch (ss) {
			case 'd':
				d(inputt, errnum);
				break;
			case 'e':
			case 'E':
				e(inputt, errnum);
I 12
				if (*errnum == 0)
					goto errmsg2;
E 12
				break;
			case 'f':
				f(inputt, errnum);
				break;
			case 'a':
			case 'c':
			case 'i':
			case 'g':
			case 'G':
			case 'v':
			case 'V':
				if (GV_flag == 1) {
					(void)sprintf(help_msg,
					    "command `%c' illegal in G/V", ss);
					*errnum = -1;
					break;
				}
				switch (ss) {
				case 'a':
					a(inputt, errnum);
					break;
				case 'c':
					c(inputt, errnum);
					break;
				case 'i':
					i(inputt, errnum);
					break;
				default:
					g(inputt, errnum);
				}
				break;
			case 'h':
				if (rol(inputt, errnum))
					break;
D 11
				(void)printf("%s\n", help_msg);
E 11
I 11
				if (help_msg[0])
					(void)printf("%s\n", help_msg);
E 11
				*errnum = 1;
				break;
			case 'H':
				if (rol(inputt, errnum))
					break;
				if (help_flag == 0) {
					help_flag = 1;
D 10
					printf("%?: %s\n", help_msg);
E 10
I 10
D 11
					printf("?: %s\n", help_msg);
E 11
I 11
					if (help_msg[0])
						(void)printf("%s\n",
						    help_msg);
E 11
E 10
				} else
					help_flag = 0;
				*errnum = 1;
				break;
			case 'j':
				j(inputt, errnum);
				break;
			case 'k':
				set_mark(inputt, errnum);
				break;
			case 'l':
				l(inputt, errnum);
				break;
			case 'm':
				m(inputt, errnum);
				break;
E 2
#ifdef POSIX
D 2
                           /* in POSIXland 'P' toggles the prompt */
                 case 'P': if (rol(inputt, errnum))
                             break;
                           prompt_str_flg = prompt_str_flg?0:1;
                           *errnum = 1;
                           break;
E 2
I 2
				/* In POSIX-land 'P' toggles the prompt. */
			case 'P':
				if (rol(inputt, errnum))
					break;
				prompt_str_flg = prompt_str_flg ? 0 : 1;
				*errnum = 1;
				break;
E 2
#endif
D 2
                 case '\n': if (GV_flag == 1)
                              return;
                            ungetc(ss, inputt); /* for 'p' to consume */
                            if ((current == bottom) && (End == NULL))
                              {
                                strcpy(help_msg, "at end of buffer");
                                *errnum = -1;
                                break;
                              }
                            current = current->below;
E 2
I 2
			case '\n':
				if (GV_flag == 1)
					return;
				/* For 'p' to consume. */
				ungetc(ss, inputt);
				if ((current == bottom) && (End == NULL)) {
					strcpy(help_msg, "at end of buffer");
					*errnum = -1;
					break;
				}
				current = current->below;
E 2
#ifdef BSD
D 2
                           /* in BSD 'P'=='p' */
                 case 'P':
E 2
I 2
				/* In BSD 'P'=='p'. */
			case 'P':
E 2
#endif
D 2
                 case 'p': p(inputt, errnum, 0);
                           break;
                 case 'n': p(inputt, errnum, 1);
                           break;
                           /* an EOF means 'q' unless we're still in the middle
                            * of a global command, in whcih case it was just
                            * the end of the command list found
                            */
                 case EOF: clearerr(inputt);
                           if (g_flag > 0)
                             return;
                           ss = 'q';
                 case 'q':
                 case 'Q': q(inputt, errnum);
                           break;
                 case 'r': r(inputt, errnum);
                           break;
                 case 's': s(inputt, errnum);
                           break;
                 case 't': t(inputt, errnum);
                           break;
                 case 'u': u(inputt, errnum);
                           break;
                 case 'w':
                 case 'W': w(inputt, errnum);
                           break;
                 case 'z': z(inputt, errnum);
                           break;
                 case '!': bang (inputt, errnum);
                           break;
                 case '=': equal (inputt, errnum);
                           break;
                         /* control of address forms from here down */
                         /* It's a head-game to understand why ";" and ","
                          * look as they do below, but a lot of it has to
                          * do with ";" and "," being special address pair
                          * forms themselves and the compatibility for
                          * address "chains".
                          */
                 case ';': if ((End_default == 1) && (start_default == 1))
                             {
                               start = current;
                               End = bottom;
                               start_default = End_default = 0;
                             }
                           else
                             {
                               start = current = End;
                               start_default = 0;
                               End_default = 1;
                             }
                           l_tempp = NULL;
                           break;
                           /* note address ".,x" where x is a cmd is legal;
                            * not a bug - for backward compatability */
                 case ',': if ((End_default == 1) && (start_default == 1))
                             {
                               start = top;
                               End = bottom;
                               start_default = End_default = 0;
                             }
                           else
                             {
                               start = End;
                               start_default = 0;
                               End_default = 1;
                             }
                           l_tempp = NULL;
                           break;
                 case '%': if (End_default == 0)
                             {
                               strcpy(help_msg, "'%' is an address pair");
                               *errnum = -1;
                               break;
                             }
                           start = top;
                           End = bottom;
                           start_default = End_default = 0;
                           l_tempp = NULL;
                           break;
                 case ' ': /* within address_conv=>l_last='+', foobar, but
                              historical and now POSIX... */
                           break;
                 case '0':
                 case '1':
                 case '2':
                 case '3':
                 case '4':
                 case '5':
                 case '6':
                 case '7':
                 case '8':
                 case '9':
                 case '-':
                 case '^':
                 case '+':
                 case '\'':
                 case '$':
                 case '?':
                 case '/':
                 case '.': ungetc(ss, inputt);
                           if ((start_default == 0) && (End_default == 0))
                             {
                               strcpy(help_msg, "badly formed address");
                               *errnum = -1;
                               break;
                             }
                           ss = l_last;
                           l_tempp = address_conv(l_tempp, inputt, errnum);
                           if (*errnum < 0)
                             break;
                           End = l_tempp;
                           End_default = 0;
                           if (start_default == 0)
                             *errnum = address_check(start, End);
                           break;
                 default: *errnum = -1;
                          strcpy(help_msg, "unknown command");
                          break;
               } /* end-switch(ss) */
E 2
I 2
			case 'p':
				p(inputt, errnum, 0);
				break;
			case 'n':
				p(inputt, errnum, 1);
				break;
			/*
			 * An EOF means 'q' unless we're still in the middle
			 * of a global command, in which case it was just the
			 * end of the command list found.
			 */
			case EOF:
				clearerr(inputt);
				if (g_flag > 0)
					return;
D 7
				ss = 'q';
E 7
I 7
				/*ss = 'q';*/
E 7
			case 'q':
			case 'Q':
I 12
				if ((!isatty(STDIN_FILENO)) && (ss == 'q'))
					ss = 'Q';
E 12
				q(inputt, errnum);
				break;
			case 'r':
				r(inputt, errnum);
I 12
				if (*errnum == 0)
					goto errmsg2;
E 12
				break;
			case 's':
				s(inputt, errnum);
				break;
			case 't':
				t(inputt, errnum);
				break;
			case 'u':
				u(inputt, errnum);
				break;
			case 'w':
			case 'W':
				w(inputt, errnum);
				break;
			case 'z':
				z(inputt, errnum);
				break;
			case '!':
				bang(inputt, errnum);
				break;
			case '=':
				equal(inputt, errnum);
				break;
			/*
			 * Control of address forms from here down.
			 *
			 * It's a head-game to understand why ";" and "," look
			 * as they do below, but a lot of it has to do with ";"
			 * and "," being special address pair forms themselves
			 * and the compatibility for address "chains".
			 */
			case ';':
D 6
				if (End_default == 1 && start_default == 1) {
					start = current;
E 6
I 6
				if (End_default == 1 && Start_default == 1) {
					Start = current;
E 6
					End = bottom;
D 6
					start_default = End_default = 0;
E 6
I 6
					Start_default = End_default = 0;
E 6
				} else {
D 6
					start = current = End;
					start_default = 0;
E 6
I 6
					Start = current = End;
					Start_default = 0;
E 6
					End_default = 1;
				}
				l_tempp = NULL;
				break;
			/*
			 * Note address ".,x" where x is a cmd is legal; not a
			 * bug - for backward compatability.
			 */
			case ',':
D 6
				if (End_default == 1 && start_default == 1) {
					start = top;
E 6
I 6
				if (End_default == 1 && Start_default == 1) {
					Start = top;
E 6
					End = bottom;
D 6
					start_default = End_default = 0;
E 6
I 6
					Start_default = End_default = 0;
E 6
				} else {
D 6
					start = End;
					start_default = 0;
E 6
I 6
					Start = End;
					Start_default = 0;
E 6
					End_default = 1;
				}
				l_tempp = NULL;
				break;
			case '%':
				if (End_default == 0) {
					strcpy(help_msg,
					    "'%' is an address pair");
					*errnum = -1;
					break;
				}
D 6
				start = top;
E 6
I 6
				Start = top;
E 6
				End = bottom;
D 6
				start_default = End_default = 0;
E 6
I 6
				Start_default = End_default = 0;
E 6
				l_tempp = NULL;
				break;
			/*
			 * Within address_conv => l_last = '+', foobar, but
			 * historical and now POSIX...
			 */
			case ' ':
				break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			case '-':
			case '^':
			case '+':
			case '\'':
			case '$':
			case '?':
			case '/':
			case '.':
				ungetc(ss, inputt);
D 6
				if (start_default == 0 && End_default == 0) {
E 6
I 6
				if (Start_default == 0 && End_default == 0) {
E 6
					strcpy(help_msg,
					    "badly formed address");
					*errnum = -1;
					break;
				}
				ss = l_last;
				l_tempp = address_conv(l_tempp, inputt, errnum);
				if (*errnum < 0)
					break;
				End = l_tempp;
				End_default = 0;
D 6
				if (start_default == 0)
					*errnum = address_check(start, End);
E 6
I 6
				if (Start_default == 0)
					*errnum = address_check(Start, End);
E 6
				break;
			default:
				*errnum = -1;
				strcpy(help_msg, "unknown command");
				break;
			}	/* end-switch(ss) */
E 2

D 2
          if (*errnum > 0)
            {
              /* things came out okay with the last command */
              if (GV_flag == 1)
                return;
              /* do the suffixes if there were any */
              if (printsfx > 0)
                {
                  start = End = current;
                  ungetc(ss, inputt);
                  if (printsfx == 1)
                    p(inputt, errnum, 0);
                  else if (printsfx == 2)
                    p(inputt, errnum, 1);
                  else if (printsfx == 4)
                    l(inputt, errnum);
                  if (*errnum < 0)
                    goto errmsg; /* unlikely it's needed, but... */
                }
              break;
            }
          else if (*errnum < 0)
            {
errmsg:
              /* there was a problem with the last command */
              while (((ss=getc(inputt)) != '\n') && (ss != EOF))
                   ;
              if (help_flag == 1)
                printf("%?: %s\n", help_msg);
              else
                printf("?\n");
              if (g_flag > 0)
                  return;
              break;
            }
          l_last = ss;
          ss = getc(inputt);
          } /* second while */
          
       } /* end-while(1) */
} /* end-cmd_loop */
E 2
I 2
			/* Things came out okay with the last command. */
			if (*errnum > 0) {
				if (GV_flag == 1)
					return;
				/* Do the suffixes if there were any. */
				if (printsfx > 0) {
D 6
					start = End = current;
E 6
I 6
					Start = End = current;
E 6
					ungetc(ss, inputt);
					if (printsfx == 1)
						p(inputt, errnum, 0);
					else
						if (printsfx == 2)
							p(inputt, errnum, 1);
						else if (printsfx == 4)
							l(inputt, errnum);
					/* Unlikely it's needed, but... */
					if (*errnum < 0)
						goto errmsg;
				}
				break;
			}
			/* There was a problem with the last command. */
			else if (*errnum < 0) {
errmsg:				while (((ss = getc(inputt)) != '\n') &&
				    (ss != EOF));
I 12
				(void)printf("?\n");
errmsg2:			if (help_flag)
					(void)printf("%s\n", help_msg);
E 12
I 8
				exit_code = 4;
E 8
D 3
					if (help_flag == 1)
						printf("%?: %s\n", help_msg);
					else
						printf("?\n");
					if (g_flag > 0)
						return;
					break;
E 3
I 3
D 11
				if (help_flag == 1)
D 8
					printf("%?: %s\n", help_msg);
E 8
I 8
					printf("?: %s\n", help_msg);
E 8
				else
					printf("?\n");
E 11
I 11
D 12
				if (g_flag == 0) {
					(void)printf("?\n");
					if (help_flag)
						(void)printf("%s\n", help_msg);
				}
E 12
E 11
I 8
/* for people wanting scripts to carry on after a cmd error, then
 * define NOENDONSCRIPT on the compile line.
 */
#ifndef NOENDONSCRIPT
				if (!isatty(STDIN_FILENO)) {
					ss = 'Q';
					ungetc('\n', inputt);
					q(inputt, errnum);
				}
#endif
E 8
D 11
				if (g_flag > 0)
					return;
E 11
				break;
E 3
			}
			l_last = ss;
			ss = getc(inputt);
		}
	}
}
E 2

D 2

/* exits ed and prints an appropriate message about the command line
E 2
I 2
/*
 * Exits ed and prints an appropriate message about the command line
E 2
 * being malformed (see below).
 */
D 2

E 2
void
ed_exit(err)
D 2

int err;

E 2
I 2
	int err;
E 2
{
D 2
  switch (err)
        {
          case 1: fprintf(stderr, "ed: illegal option\n");
                  break;
          case 2: fprintf(stderr, "ed: missing promptstring\n");
                  break;
          case 3: fprintf(stderr, "ed: too many filenames\n");
                  break;
          case 4: fprintf(stderr, "ed: out of memory error\n");
                  break;
          default: fprintf(stderr, "ed: command line error\n");
                   break;
        } /* end-switch */
  fprintf(stderr, "ed: ed [ -s ] [ -p promtstring ] [ filename ]\n");
  exit(1);
} /* end-ed_exit */
E 2
I 2
	switch (err) {
          case 1:
		(void)fprintf(stderr, "ed: illegal option\n");
		break;
          case 2:
		(void)fprintf(stderr, "ed: missing promptstring\n");
		break;
          case 3:
		(void)fprintf(stderr, "ed: too many filenames\n");
		break;
          case 4:
		(void)fprintf(stderr, "ed: out of memory error\n");
		break;
I 3
	  case 5:
		(void)fprintf(stderr, "ed: unable to create buffer\n");
		break;
E 3
          default:
		(void)fprintf(stderr, "ed: command line error\n");
		break;
        }
	(void)fprintf(stderr,
	    "ed: ed [ -s ] [ -p promptstring ] [ filename ]\n");
	exit(1);
}
E 2

D 2

E 2
/*
D 2
 * Starts the whole show going. Set things up as the arguments spec
 * in the shell and set a couple of the global variables.
E 2
I 2
 * SIGINT is never turned off. We flag it happened and then pay attention
 * to it at certain logical locations in the code we don't do more here
 * cause some of our buffer pointer's may be in an inbetween state at the
 * time of the SIGINT. So we flag it happened, let the local fn handle it
 * and do a jump back to the cmd_loop
E 2
 */
I 2
static void
sigint_handler(signo)
	int signo;
{
	sigint_flag = 1;
I 5
	if (sigspecial3) {
		sigspecial3 = 0;
		SIGINT_ILACTION;
D 7
	}
E 5
D 3
	if (sigspecial)  /* Unstick when SIGINT on read(stdin). */
		SIGINT_ACTION;
E 3
I 3
	if (sigspecial2) {
		sigspecial2 = 0;
D 5
		SIGINT_ILACTION;
E 5
I 5
		SIGINT_ALACTION;
E 7
E 5
	}
	else
		if (sigspecial);
		else
			SIGINT_ACTION;
E 3
}
E 2

D 2
void
main(argc, argv)

int argc;
char *argv[];

E 2
I 2
static void
sighup_handler(signo)
	int signo;
E 2
{
D 2
  int l_num, errnum=0, l_err=0; /* note naming viol'n with errnum for consistancy */
  char *l_fnametmp;
#ifdef DBI
  RECNOINFO l_dbaccess;
#endif
  /* termcap isn't really need unless you move back and forth between 80 and
   * 123 column terminals. And if your system is wacked and you have to use
   * ed because it's the only reliable editor (sysadmin-types know what I'm
   * talking about), you likely don't want the termcap routines.
   * See the Makefile about compile options.
   */
#ifndef NOTERMCAP
  int l_ret;
  char l_bp[1024], *l_term;
#endif
E 2
I 2
D 8
	(void)fprintf(stderr,"\n  SIGHUP \n");
E 8
	sighup_flag = 1;
	undo();
	do_hup();
	/* NOTREACHED */
E 2

D 2
  setuid(getuid()); /* in case some fool does suid on ed */

#ifndef NOTERMCAP
  l_term = getenv("TERM");
  l_ret = tgetent(l_bp, l_term);
  if (l_ret < 1)
    line_length = 78; /* reasonable number for all term's */
  else if ((line_length = tgetnum("co") - 1) < 2)
#endif
    line_length = 78;
  
  start = End = NULL;
  top = bottom = NULL;
  current = NULL;
  nn_max_flag = 0;
  nn_max_start = nn_max_end = NULL;
  l_fnametmp = (char *)calloc(FILENAME_LEN, sizeof(char));
  if (l_fnametmp == NULL)
    ed_exit(4);
  text = (char *)calloc(NN_MAX_START+2, sizeof(char));
  if (text == NULL)
    ed_exit(4);
  start_default = End_default = 0;
  zsnum = 22; /* for the 'z' command */
  u_stk = NULL;
  d_stk = NULL;
  u_current = u_top = u_bottom = NULL;
  u_set = 0; /* for in d after a j */
  filename_flag = 0;
  filename_current = NULL;

  l_num = 1;
  while (1)
       {
         /* process the command line options */
         if (l_num >= argc)
           break;
         switch (argv[l_num][0])
               {
                 case '-':
                           switch (argv[l_num][1])
                                 {
                                   case '\0': /* this is why 'getopt' not used */
                                   case 's': explain_flag = 0;
                                             break;
                                   case 'p': if (++l_num < argc)
                                               {
                                                 prompt_string = (char *)calloc(strlen(argv[l_num]), sizeof(char));
                                                 if (prompt_string == NULL)
                                                   ed_exit(4);
                                                 strcpy(prompt_string, argv[l_num]);
                                                 prompt_str_flg = 1;
                                                 break;
                                               }
                                             l_err = 1;
                                   default: l_err++;
                                            ed_exit(l_err);
                                 } /* end-switch */
                           break;
                 default:  if (name_set)
                             ed_exit(3);
                           strcpy(l_fnametmp, argv[l_num]);
                           filename_current = l_fnametmp;
                           name_set = 1;
                           if (prompt_str_flg)
                             break;
                           /* default ed prompt */
                           prompt_string = (char *)calloc(3, sizeof(char));
                           strcpy(prompt_string, "*");
                           break;
               } /* end-switch */
         l_num++;
       } /* end-while(1) */

  start_up_flag = 1;
  cmd_loop(stdin, &errnum);
} /* end-main */
E 2
I 2
	SIGHUP_ACTION;
}
E 2
E 1
