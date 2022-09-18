h33245
s 00016/00000/00000
d D 5.1 90/05/02 08:39:16 bostic 1 0
c date and time created 90/05/02 08:39:16 by bostic
e
u
U
t
T
I 1
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */
/* def.func_tab.h - version 1.0.2 */

struct func_tab {
	char f_char;
	int (*f_funct)();
};

extern struct func_tab cmdlist[];

struct ext_func_tab {
	char *ef_txt;
	int (*ef_funct)();
};

extern struct ext_func_tab extcmdlist[];
E 1
