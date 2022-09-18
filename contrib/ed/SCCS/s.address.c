h12182
s 00002/00002/00235
d D 8.1 93/05/31 14:28:36 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00006/00229
d D 5.4 93/03/01 16:56:32 bostic 4 3
c 
e
s 00006/00003/00229
d D 5.3 93/02/28 15:28:27 bostic 3 2
c some lint, some bug fixes, ^C handling improvements
c multiple access methods back in (yeeech!)
c new version from Rodney Ruddock (rodney@snowhite.cis.uoguelph.ca)
e
s 00182/00210/00050
d D 5.2 93/01/23 15:47:33 bostic 2 1
c reformat to KNF, prototype the world, fix lint bugs
e
s 00260/00000/00000
d D 5.1 93/01/23 11:12:59 bostic 1 0
c date and time created 93/01/23 11:12:59 by bostic
e
u
U
t
T
I 1
/*-
D 5
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * Rodney Ruddock of the University of Guelph.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

I 2
#include <sys/types.h>

D 3
#include <db.h>
E 3
#include <regex.h>
#include <setjmp.h>
#include <stdio.h>
#include <string.h>

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
 * Make sure that address one comes before address two in the buffer
 */

int
address_check(one, two)
D 2

LINE *one, *two;

E 2
I 2
	LINE *one, *two;
E 2
{
D 2
  LINE *l_cl;
E 2
I 2
	LINE   *l_cl;
E 2

D 2
  l_cl = one;
E 2
I 2
	for (l_cl = one; l_cl != NULL; l_cl = l_cl->below)
		if (l_cl == two)
			return (0);
	return (-1);
}
E 2

D 2
  while (l_cl != NULL)
       {
         if (l_cl == two)
           return(0);
         l_cl = l_cl->below;
       } /* end-while */
  return(-1);
}/* end-address_check */

E 2
/*
 * convert a number given by the user into variable
 */
D 2

E 2
int
dig_num_conv(inputt, errnum)
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
 int l_line=0;
E 2
I 2
	int l_line = 0;
E 2

D 2
 l_line = ss - '0';
 while ((ss=getc(inputt)) != EOF)
    {
      if ((ss < '0') || (ss > '9'))
        break;
      l_line = (l_line * 10) + (ss - '0');
    }
  *errnum = 0;
  ungetc(ss, inputt);
  return(l_line);
E 2
I 2
	l_line = ss - '0';
	while ((ss = getc(inputt)) != EOF) {
		if ((ss < '0') || (ss > '9'))
			break;
		l_line = (l_line * 10) + (ss - '0');
	}
	*errnum = 0;
	ungetc(ss, inputt);
	return (l_line);
E 2
}

/*
 * Convert a numeric address into a LINE address (more useful for ed)
 */
D 2

LINE
*num_to_address(num, errnum)

int num, *errnum;

E 2
I 2
LINE *
num_to_address(num, errnum)
	int num, *errnum;
E 2
{
D 2
  int l_line=1;
  LINE *temp1;
E 2
I 2
	int l_line = 1;
	LINE *temp1;
E 2

D 2
  temp1 = top;
E 2
I 2
D 4
	for (temp1 = top; temp1->below != NULL; temp1 = temp1->below) {
		/* find the matching line number in the buffer */
		if (l_line >= num)
			break;
		l_line++;
E 4
I 4
	if (top) {
		for (temp1 = top; temp1->below != NULL; temp1 = temp1->below) {
			/* find the matching line number in the buffer */
			if (l_line >= num)
				break;
			l_line++;
		}
E 4
	}
E 2

D 2
  while (temp1->below != NULL)
    {
      /* find the matching line number in the buffer */
      if (l_line >= num)
        break;
      l_line++;
      temp1 = temp1->below;
    }
E 2
I 2
D 4
	if (l_line < num) {
E 4
I 4
	if ((l_line < num) || (!top)) {
E 4
		/* the number was wacko */
		*errnum = -1;
		strcpy(help_msg, "bad line number");
		return (NULL);
	} else
		if (num == 0)	/* special case */
			return (NULL);
		else
			return (temp1);
}
E 2

D 2
  if (l_line < num)
    {
      /* the number was wacko */
      *errnum = -1;
      strcpy(help_msg, "bad line number");
      return(NULL);
    }
  else if (num == 0) /* special case */
    return(NULL);
  else
    return(temp1);
E 2

D 2
} /* end-num_to_adddress */


E 2
/*
D 2
 * Figure out what the addresses are spec'd by the user.
 * Note for backward compatability the most recent addresses in
 * a chain are used by the commands (i.e. 3,5,17,22d deletes lines 17 to
 * 22 inclusive. The two leading addresses 3 and 5 are dropped as cmd_loop
 * rolls through here the extra times). Hence, the code may look
 * a little wierder than it should.
 * The variable l_order is used to control for legally constructed addresses
 * as described in ed(1). So, "$-21" and "/RE/++++" are leagal but /RE/-$ is
 * not.
E 2
I 2
 * Figure out what the addresses are spec'd by the user.  Note for backward
 * compatability the most recent addresses in a chain are used by the commands
 * (i.e. 3,5,17,22d deletes lines 17 to 22 inclusive. The two leading addresses
 * 3 and 5 are dropped as cmd_loop rolls through here the extra times).  Hence,
 * the code may look a little wierder than it should.  The variable l_order is
 * used to control for legally constructed addresses as described in ed(1).  So,
D 3
 * "$-21" and "/RE/++++" are leagal but /RE/-$ is not.
E 3
I 3
 * "$-21" and "/RE/++++" are legal but /RE/-$ is not.
E 3
E 2
 */
D 2

LINE
*address_conv(tempp, inputt, errnum)

LINE *tempp;
FILE *inputt;
int *errnum;

E 2
I 2
LINE *
address_conv(tempp, inputt, errnum)
	LINE *tempp;
	FILE *inputt;
	int *errnum;
E 2
{
D 2
  int l_last, l_cnt, l_num, l_order=0;
  LINE *l_dot;
  int l_pass_flag=0;
E 2
I 2
	LINE *l_dot;
	int l_last, l_cnt, l_num, l_order, l_pass_flag;
E 2

D 2
  l_dot = NULL;
  address_flag = 0;
E 2
I 2
	l_dot = NULL;
	l_order = 0;
	l_pass_flag = 0;
	address_flag = 0;
E 2

D 2
  l_last = ss;
  if (tempp == NULL)
    l_dot = current;
  else
    l_dot = tempp;
E 2
I 2
	l_last = ss;
	if (tempp == NULL)
		l_dot = current;
	else
		l_dot = tempp;
E 2

D 2
  while ((ss=getc(inputt)) != EOF)
  {
  switch (ss)
     {
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
                if (l_order == (l_order | 4))
                  {
                    *errnum = -1;
                    strcpy(help_msg, "malformed address");
                    return(NULL);
                  }
                l_order |= 1;
                l_num = dig_num_conv(inputt, errnum);
                /* " " (<space>), historically, gets counted as a "+"
                 * if it's between two 'addable' address forms. Goofy,
                 * but it makes it compatible for those strange old
                 * scripts (or users?)
                 */
                if ((l_last == '+') || ((l_last == ' ') && l_pass_flag))
                  {
                    if (l_last == ' ')
                      l_num++;
                    for (l_cnt=0; l_cnt<l_num-1 ;l_cnt++)
                       {
                         if (l_dot == NULL)
                           {
                             *errnum = -1;
                             return(NULL);
                           }
                         l_dot = l_dot->below;
                       }
                  }
                else if ((l_last == '-') || (l_last == '^'))
                  {
                    for (l_cnt=l_num-1; l_cnt>0; l_cnt--)
                       {
                         if (l_dot == NULL)
                           {
                             *errnum = -1;
                             return(NULL);
                           }
                         l_dot = l_dot->above;
                       }
                  }
                else
                  l_dot = num_to_address(l_num, errnum);
                if (*errnum < 0)
                  return(NULL);
                l_pass_flag = 1;
                break;
      case '\'':
      case '$':
      case '?':
      case '/':
      case '.': if (l_order != 0)
                  {
                    *errnum = -1;
                    strcpy(help_msg, "malformed address");
                    return(NULL);
                  }
                l_order = 4;
                switch (ss)
                {
                  case '\'': l_dot = get_mark(errnum);
                             break;
                  case '$': l_dot = bottom; /* set to bottom */
                            break;
                  case '?': l_dot = search_r(inputt, errnum);
                            break;
                  case '/': l_dot = search(inputt, errnum);
                            break;
                  case '.': l_dot = current;
                            break;
                }
                break;
      case '-':
      case '^':
      case '+': l_order = 2;
                if (ss == '+')
                  {
                    l_dot = l_dot->below;
                    if (l_dot == NULL)
                      {
                        strcpy(help_msg, "at end of buffer");
                        *errnum = -1;
                        return(NULL);
                      }
                  }
                else
                  {
                    l_dot = l_dot->above;
                    if (l_dot == NULL)
                      {
                        strcpy(help_msg, "at top of buffer");
                        *errnum = -1;
                        return(NULL);
                      }
                  }
                break;
      case ' ': break; /* ignore here, but see comment above */
      default: ungetc(ss, inputt);
               return(l_dot);
               break;
     } /* End-switch */
E 2
I 2
	while ((ss = getc(inputt)) != EOF) {
		switch (ss) {
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			if (l_order == (l_order | 4)) {
				*errnum = -1;
				strcpy(help_msg, "malformed address");
				return (NULL);
			}
			l_order |= 1;
			l_num = dig_num_conv(inputt, errnum);
			/*
			 * " " (<space>), historically, gets counted as a "+"
			 * if it's between two 'addable' address forms. Goofy,
			 * but it makes it compatible for those strange old
			 * scripts (or users?)
			 */
			if ((l_last == '+') ||
			    ((l_last == ' ') && l_pass_flag)) {
				if (l_last == ' ')
					l_num++;
				for (l_cnt = 0; l_cnt < l_num - 1; l_cnt++) {
					if (l_dot == NULL) {
						*errnum = -1;
						return (NULL);
					}
					l_dot = l_dot->below;
				}
			} else
				if ((l_last == '-') || (l_last == '^')) {
					for (l_cnt = l_num - 1;
					    l_cnt > 0; l_cnt--) {
						if (l_dot == NULL) {
							*errnum = -1;
							return (NULL);
						}
						l_dot = l_dot->above;
					}
				} else
					l_dot = num_to_address(l_num, errnum);
			if (*errnum < 0)
				return (NULL);
			l_pass_flag = 1;
			break;
		case '\'':
		case '$':
		case '?':
		case '/':
		case '.':
			if (l_order != 0) {
				*errnum = -1;
				strcpy(help_msg, "malformed address");
				return (NULL);
			}
			l_order = 4;
			switch (ss) {
			case '\'':
D 3
				l_dot = get_mark(errnum);
E 3
I 3
				l_dot = get_mark(inputt, errnum);
E 3
				break;
			case '$':
				l_dot = bottom;	/* set to bottom */
				break;
			case '?':
				l_dot = search_r(inputt, errnum);
				break;
			case '/':
				l_dot = search(inputt, errnum);
				break;
			case '.':
				l_dot = current;
				break;
			}
			break;
		case '-':
		case '^':
		case '+':
			l_order = 2;
			if (ss == '+') {
				l_dot = l_dot->below;
				if (l_dot == NULL) {
					strcpy(help_msg, "at end of buffer");
					*errnum = -1;
					return (NULL);
				}
			} else {
				l_dot = l_dot->above;
				if (l_dot == NULL) {
					strcpy(help_msg, "at top of buffer");
					*errnum = -1;
					return (NULL);
				}
			}
			break;
		case ' ':
			break;	/* ignore here, but see comment above */
		default:
			ungetc(ss, inputt);
			return (l_dot);
			break;
		}
E 2

D 2
     if (*errnum < 0)
       break; /* from the while-loop */
     l_last = ss;
   } /* end-while */
E 2
I 2
		if (*errnum < 0)
			break;	/* from the while-loop */
		l_last = ss;
	}
E 2

D 2
  if (ss == EOF)
    return(l_dot);
  *errnum = -1;
  return(NULL);
} /* End-address_conv */
E 2
I 2
	if (ss == EOF)
		return (l_dot);
	*errnum = -1;
	return (NULL);
}
E 2
E 1
