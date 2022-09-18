/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */

typedef union 
{
	struct ruleinfo	*rule;
	struct list	*list;
	char		*string;
} YYSTYPE;
extern YYSTYPE yylval;
# define APPEND 257
# define COMMANDS 258
# define ELLIPSIS 259
# define NAME 260
# define OP 261
# define VALUE 262
