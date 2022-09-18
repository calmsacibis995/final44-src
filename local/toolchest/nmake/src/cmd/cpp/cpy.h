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
	int	number;
	char	*string;
} YYSTYPE;
extern YYSTYPE yylval;
# define NAME 257
# define NUMBER 258
# define STOP 259
# define EQ 260
# define NE 261
# define LE 262
# define GE 263
# define LS 264
# define RS 265
# define ANDAND 266
# define OROR 267
# define UMINUS 268
