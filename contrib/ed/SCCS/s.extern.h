h28550
s 00002/00002/00083
d D 8.1 93/05/31 14:29:02 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00084
d D 5.3 93/04/28 18:24:07 bostic 3 2
c declare u_pop_n_swap
e
s 00021/00001/00063
d D 5.2 93/02/28 15:28:47 bostic 2 1
c some lint, some bug fixes, ^C handling improvements
c multiple access methods back in (yeeech!)
c new version from Rodney Ruddock (rodney@snowhite.cis.uoguelph.ca)
e
s 00064/00000/00000
d D 5.1 93/02/28 14:53:24 bostic 1 0
c date and time created 93/02/28 14:53:24 by bostic
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

I 2
#include <sys/cdefs.h>

E 2
void	 a __P((FILE *, int *));
I 2

#ifdef STDIO
long	add_line __P((char *, long));
#endif
#ifdef DBI
E 2
recno_t	 add_line __P((char *, long));
I 2
#endif
#ifdef MEMORY
char	*add_line __P((char *, long));
#endif

E 2
int	 address_check __P((LINE *, LINE *));
LINE	*address_conv __P((LINE *, FILE *, int *));
void	 bang __P((FILE *, int *));
void	 c __P((FILE *, int *));
void	 cmd_loop __P((FILE *, int *));
void	 d __P((FILE *, int *));
void	 d_do __P((void));
int	 dig_num_conv __P((FILE *, int *));
void	 e __P((FILE *, int *));
void	 e2 __P((FILE *, int *));
void	 ed_exit __P((int));
int	 edwrite __P((FILE *, LINE *, LINE *));
void	 equal __P((FILE *, int *));
void	 f __P((FILE *, int *));
char	*filename __P((FILE *, int *));
void	 g __P((FILE *, int *));
I 2
#ifdef STDIO
void     get_line __P((long, int));
#endif
#ifdef DBI
E 2
void	 get_line __P((recno_t, int));
D 2
LINE	*get_mark __P((int *));
E 2
I 2
#endif
#ifdef MEMORY
void     get_line __P((char *, int));
#endif;
LINE	*get_mark __P((FILE *, int *));
E 2
char	*get_pattern __P((int, FILE *, int *, int));
void	 i __P((FILE *, int *));
long	 input_lines __P((FILE *, int *));
void	 j __P((FILE *, int *));
void	 ku_chk __P((LINE *, LINE *, LINE *));
void	 l __P((FILE *, int *));
int	 line_number __P((LINE *));
void	 m __P((FILE *, int *));
LINE	*num_to_address __P((int, int *));
void	 p __P((FILE *, int *, int));
void	 q __P((FILE *, int *));
void	 r __P((FILE *, int *));
int	 rol __P((FILE *, int *));
void	 s __P((FILE *, int *));
LINE	*search __P((FILE *, int *));
LINE	*search_r __P((FILE *, int *));
void	 set_mark __P((FILE *, int *));
void	 t __P((FILE *, int *));
void	 u __P((FILE *, int *));
void	 u_add_stk __P((LINE **));
void	 u_clr_stk __P((void));
I 3
void	 u_pop_n_swap __P((LINE **));
E 3
void	 undo __P((void));
__dead void do_hup __P((void));
void	 w __P((FILE *, int *));
void	 z __P((FILE *, int *));

#ifdef REG_STARTEND
char	*re_replace __P((char *, size_t, regmatch_t [], char *));
int	 regexec_n __P((regex_t *,
	    char *, size_t, regmatch_t [], int, int, size_t, int));
#else
char	*re_replace __P((char *, size_t, regmatch_t [], char *, size_t));
int	 regexec_n __P((regex_t *,
	    char *, size_t, regmatch_t [], int, int, size_t *, int));
#endif
E 1
