h34496
s 00018/00004/00038
d D 5.4 95/04/29 10:09:50 bostic 4 3
c It failed to compile on the sparc because `swapresponse' was
c ifdef'ed on vax, sun, i386 (but not sparc).  I made it pass gcc2 -Wall.
c From: Chris Torek <torek@BSDI.COM>
e
s 00005/00004/00037
d D 5.3 94/04/02 15:19:10 bostic 3 2
c put redistributable notice on it, I'm putting it in 4.4BSD-Lite
e
s 00001/00000/00040
d D 5.2 89/05/01 09:17:11 bostic 2 1
c utmp.h needs types.h now
e
s 00040/00000/00000
d D 5.1 89/05/01 09:16:53 bostic 1 0
c date and time created 89/05/01 09:16:53 by bostic
e
u
U
t
T
I 1
D 3
/*
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
/*-
 * Copyright (c) 1983, 1985
 *	The Regents of the University of California.  All rights reserved.
 *
 * %sccs.include.redist.c%
E 3
 *
 *	@(#)talk.h	5.1 (Berkeley) 6/6/85
 */

I 2
#include <sys/types.h>
E 2
#include <curses.h>
#include <utmp.h>

#define forever		for(;;)

#define BUF_SIZE	512

D 4
FILE	*popen();
int	quit();
int	sleeper();

E 4
extern	int sockt;
extern	int curses_initialized;
extern	int invitation_waiting;

extern	char *current_state;
extern	int current_line;

typedef struct xwin {
	WINDOW	*x_win;
	int	x_nlines;
	int	x_ncols;
	int	x_line;
	int	x_col;
	char	kill;
	char	cerase;
	char	werase;
} xwin_t;

extern	xwin_t my_win;
extern	xwin_t his_win;
extern	WINDOW *line_win;
I 4

void	announce_invite __P((void));
int	check_local __P((void));
void	display __P((xwin_t *, char *, int));
void	end_msgs __P((void));
void	get_addrs __P((char *, char *));
void	get_names __P((int, char **));
void	init_display __P((void));
void	invite_remote __P((void));
void	message __P((const char *));
void	open_ctl __P((void));
void	open_sockt __P((void));
__dead void p_error __P((const char *)) __attribute__((volatile));
__dead void quit __P((void)) __attribute__((volatile));
void	send_delete __P((void));
void	set_edit_chars __P((void));
void	start_msgs __P((void));
void	talk __P((void));
E 4
E 1
