h57634
s 00002/00002/00091
d D 8.1 93/05/31 14:28:53 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00007/00087
d D 5.6 93/04/28 18:07:05 bostic 6 5
c corrections for echoing the last command when "!!" is given,
c undo working when 0 or 1 lines were in the buffer before the last buffer
c modification, a RE interpretation correction; from Rodney Ruddock
e
s 00002/00002/00092
d D 5.5 93/03/08 18:31:47 ralph 5 4
c changed start to Start and start_default to Start_default to
c avoid conflicts with start defined in crt0.o
e
s 00004/00003/00090
d D 5.4 93/03/01 16:57:22 bostic 4 3
c longjmp fixes
e
s 00025/00005/00068
d D 5.3 93/02/28 15:28:38 bostic 3 2
c some lint, some bug fixes, ^C handling improvements
c multiple access methods back in (yeeech!)
c new version from Rodney Ruddock (rodney@snowhite.cis.uoguelph.ca)
e
s 00022/00108/00051
d D 5.2 93/01/23 15:47:37 bostic 2 1
c reformat to KNF, prototype the world, fix lint bugs
e
s 00159/00000/00000
d D 5.1 93/01/23 11:13:04 bostic 1 0
c date and time created 93/01/23 11:13:04 by bostic
e
u
U
t
T
I 1
/*-
D 7
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * This code is derived from software contributed to Berkeley by
 * Rodney Ruddock of the University of Guelph.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

D 2
#include <sys/types.h>
#include <sys/stat.h>
E 2
I 2
D 3
#define	FILENAME_LEN	1023
E 3
I 3
#define	FILENAME_LEN	PATH_MAX
E 3
#define	JMP_SET		(int)0
#define	INTERUPT	(int)1
#define	HANGUP		(int)2
D 3
#define	SIGINT_ACTION	longjmp(ctrl_position, INTERUPT); fflush(stdin)
E 3
I 3
#define	SIGINT_ACTION	longjmp(ctrl_position, INTERUPT)
D 4
#define SIGINT_ILACTION	longjmp(ctrl_position2, INTERUPT)
E 4
I 4
#define SIGINT_ALACTION	longjmp(ctrl_position2, INTERUPT)
#define SIGINT_ILACTION	longjmp(ctrl_position3, INTERUPT)
E 4
E 3
#define	SIGHUP_ACTION	longjmp(ctrl_position, HANGUP)
#define	NN_MAX_START	510
I 6
#ifndef STDIN_FILENO
#define STDIN_FILENO 0
#endif
E 6
I 3
#ifndef STDOUT_FILENO
#define STDOUT_FILENO 1
#endif
E 3
E 2

D 2
#include <fcntl.h>
#include <regex.h>
#include <setjmp.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef DBI
#include <limits.h>
#include <db.h>
#endif

#define FILENAME_LEN 1023
#define JMP_SET (int)0
#define INTERUPT (int)1
#define HANGUP (int)2
#define SIGINT_ACTION longjmp(ctrl_position, INTERUPT); fflush(stdin)
#define SIGHUP_ACTION longjmp(ctrl_position, HANGUP)
#define NN_MAX_START 510

E 2
typedef struct A {
D 2
                 struct A *above, *below;
#ifdef STDIO
                 long handle;
#endif
#ifdef DBI
                 recno_t handle;
#endif
#ifdef MEMORY
                 char *handle;
#endif
                 size_t len;
               } LINE;
E 2
I 2
	struct A *above, *below;
I 3
#ifdef STDIO
	long handle;
#endif
#ifdef DBI
E 3
	recno_t handle;
I 3
#endif
#ifdef MEMORY
	char *handle;
#endif
E 3
	size_t len;
} LINE;
E 2

struct MARK {
D 2
              LINE *address;
            };
E 2
I 2
	LINE *address;
};
E 2

D 2

E 2
D 6
struct g_list {
D 2
                 struct g_list *next;
                 LINE *cell;
               };
E 2
I 2
	struct g_list *next;
	LINE *cell;
};
E 2

E 6
struct u_layer {
D 2
                 LINE *val, **cell;
                 struct u_layer *below;
               };
E 2
I 2
	LINE *val, **cell;
	struct u_layer *below;
};
E 2

struct d_layer {
D 2
                 LINE *begin, *end;
                 struct d_layer *next;
               };
E 2
I 2
	LINE *begin, *end;
	struct d_layer *next;
};
E 2

D 2
extern void cmd_loop();
extern void a();
extern void c();
extern void d();
extern void d_add();
extern void d_do();
extern void e();
extern void e2();
extern void f();
extern void g();
extern void i();
extern void j();
extern void k();
extern void ku_chk();
extern void l();
extern void m();
extern void p();
extern void q();
extern void r();
extern void s();
extern void t();
extern void u();
extern void u_add_stk();
extern void u_clr_stk();
extern void w();
extern void z();
extern void equal();
extern void bang();
extern void set_mark();
extern LINE *get_mark();
extern LINE *search();
extern LINE *search_r();
extern long input_lines();
#ifdef STDIO
extern long add_line();
#endif
#ifdef DBI
extern recno_t add_line();
#endif
#ifdef MEMORY
extern char *add_line();
#endif
extern void get_line();
extern int num_dig_conv();
extern LINE *address_conv();
extern struct bounds *re_search();
extern struct re_pattern *re_compile();
extern void undo();
extern char *re_replace();
extern char *get_pattern();
extern char *filename();
extern int rol();
extern void ed_exit();

E 2
D 5
extern int nn_max, nn_max_flag, start_default, End_default, address_flag;
extern LINE *nn_max_start, *nn_max_end, *start, *End, *current;
E 5
I 5
extern int nn_max, nn_max_flag, Start_default, End_default, address_flag;
extern LINE *nn_max_start, *nn_max_end, *Start, *End, *current;
E 5
extern char *text, *prompt_string, help_msg[];
I 6
extern LINE **gut;
E 6
extern struct MARK mark_matrix[];
extern char *filename_current, *buf;
extern int zsnum;  /* z sticky number */
extern LINE *top, *bottom; /* ...of the buffer */
D 6
extern int ss, explain_flag, name_set;
D 3
extern int filename_flag, add_flag;
E 3
I 3
extern int filename_flag, add_flag, join_flag;
E 6
I 6
extern int ss, explain_flag, name_set, exit_code;
extern int filename_flag, add_flag, join_flag, gut_num;
E 6
E 3
extern long change_flag;
extern int pat_err, flag, g_flag, GV_flag, printsfx;

I 3
#ifdef STDIO
extern FILE *fhtmp;
extern int file_seek;
extern char *template;
#endif

#ifdef DBI
E 3
D 2
#ifdef STDIO
extern FILE *fhtmp;
extern int file_seek;
extern char *template;
#endif

#ifdef DBI
E 2
extern DB *dbhtmp;
extern char *template;
I 3
#endif
E 3
D 2
#endif
E 2

extern struct u_layer *u_stk;
extern LINE *u_current, *u_top, *u_bottom;
extern int u_set, line_length;
extern struct d_layer *d_stk;

D 3
extern int sigint_flag, sighup_flag;
extern jmp_buf ctrl_position;
E 3
I 3
D 4
extern int sigint_flag, sighup_flag, sigspecial, sigspecial2;
extern jmp_buf ctrl_position, ctrl_position2;
E 4
I 4
extern int sigint_flag, sighup_flag, sigspecial, sigspecial2, sigspecial3;
extern jmp_buf ctrl_position, ctrl_position2, ctrl_position3;
E 4
E 3

#define RE_SEC 10
extern regex_t RE_comp;
extern regmatch_t RE_match[];
extern int RE_sol, RE_flag;
extern char *RE_patt;
E 1
