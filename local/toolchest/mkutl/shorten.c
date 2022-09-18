/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
/*	/ipaa/devsolid/src/cmain/s.shorten.c
	shorten.c	1.6	1/3/84 13:30:18
	"Stolen" from /usr/lbin (aka /usr/local/bin).
	Used in the development environment and hence "bought".
*/
static	char	sccsid[] = "@(#)  shorten.c 1.6";

/* shorten	Prints on the standard output the files given as
		argument folding any lines longer than -fNN (default -
		60) characters at the last blank beyond NN and before the
		-eMM (default - 80) character.
		If -iII is specified, the remainder of the line is
		indented II blanks before continuing.
		If -I'<string>' is specified, folded lines are indented
		with the given <string>.
		Arguments are taken in the order encountered so
		multiple files may be processed with different fold,
		end, and indent values.
*/

#include	<stdio.h>
#include	<string.h>

static	int	end = 80;	/* line length */
static	int	fold = 60;	/* fold-point, first character where line may be
				folded */
static	int	indent = 0;
static	char	*indentstr = 0;
static	char	*trailer = "";
static	FILE	*file = stdin;
static	char	ibuf[ BUFSIZ ];

static	int	cr, lc;

#define	BUFFSIZE	250
static	char	buff[ BUFFSIZE + 5 ];
static	char	*cmd;


main(argc, argv)
int	argc;
char	*argv[];
{
	register int	c;
	register int	file_opened = 0;
	extern int	optind;
	extern char	*optarg;

	cmd = argv[0];
	setbuf( stdin, ibuf );
	for(;  optind <argc;  optind++ ) {
		while( (c = getopt( argc, argv, "f:e:i:I:t:" )) != EOF ) {
			switch ( c ) {
			case 'f':
				fold = patoi(c, optarg);
				break;
			case 'e':
				end = patoi(c, optarg);
				break;
			case 'i':
				indent = patoi(c, optarg);
				indentstr = 0;
				break;
			case 'I':
				indentstr = optarg;
				indent = 0;
				for( ;  *indentstr;  indentstr++ )
					indent = colct( *indentstr, indent );
				indentstr = optarg;
				break;
			case 't':
				trailer = optarg;
				break;
			case '?':
				exit(1);
			default:
				fprintf( stderr, "%s:  getopt(3) error!",
					cmd );
				exit( 1 );
			}
		}
		if( optind >= argc )
			break;
		file_opened++;
		if( !strcmp( argv[optind], "-" ) ) {
			file = stdin;
			process();
			continue;
		}
		if( file != stdin )
			fclose( file );
		if( ( file = fopen( argv[optind], "r" ) ) == NULL )
			fprintf( stderr, "%s:  cannot open %s\n", cmd,
				argv[optind] );
		else
			process();
	}
	if( !file_opened ) {	/* no files names listed,
				process the standard input */
		file = stdin;
		process();
	}
	exit( 0 );
}


static
process()
{
	register int	c;

	if (end - fold > BUFFSIZE) {
		fprintf( stderr, "%s:  end-point - fold-point > %d\n",
			cmd, BUFFSIZE );
		exit(1);
	}
	while( ( c = getc( file ) ) != EOF)
	{
		cr = colct( c, cr );
		if( c == '\n' )
		{
			cr = 0;
		}
		if( cr > end ) {
			putchar( '\n' );
			cr = 0;
			cr = colct( c, cr );
		}
		putchar( c );
		while( cr > fold )
			buffer();
	}
}


/*	column count
	given a character and the current column number,
	return the new column number.
*/
static
colct( c, cn )
int	c;
int	cn;
{
	switch( c ) {
	default:
		cn++;
		break;
	case '\b':
		if( cn )
			cn -= 1;	/* decriment by 1 for backspace */
		break;
	case '\t':
		cn = ((cn/8) + 1)*8;
	}
	return  cn;
}


/*
	buffer the input from the fold point to the end point
*/
static
buffer()
{
	register int	buffct;
	register int	c;
	register int	iblank;

	buffct = 0;
	/* printf("in buffer()\n"); */
	while( ( ( c = getc( file ) ) != EOF ) ) {
		buff[ buffct ] = c;
		if( c == '\n' ) {
			putbuff( 0, buffct );
			cr = 0;
			return;
		}
		if( (cr = colct( c, cr )) > end )
			break;
		buffct++;
	}
	switch( c ) {
	case ' ':
	case '\t':
		/* The last character we saw was white space.  It is possible
		that there is a long string of white space or that everything
		from here to the end of the line is white space.
		We will throw away any excess white space and if we see the
		new-line, output the buffer */
		while( ( c = getc( file ) ) != EOF ) {
			switch( c ) {
			case ' ':
			case '\t':
				continue;
			case '\n':
				buff[ buffct ] = c;
				putbuff( 0, buffct );
				cr = 0;
				return;
			default:
				goto leaveloop;
			}
		}
	    leaveloop:
		ungetc( c, file );
	}
	/* printf("cr %d, c %c, buffct %d\n", cr, c, buffct); */
	/*	find the last blank or tab ("white space") in buff */
	for (iblank = buffct;  iblank >= 0;  iblank--) {
		switch( buff[ iblank ] ) {
		case ' ':
		case '\t':
			goto exitloop;
		}
	}
	exitloop:

	/* printf("iblank %d\n", iblank); */
	if (iblank < 0) {
		/*	no white space, put out entire buffer */
		putbuff( 0, iblank = buffct - 1 );
	}
	else {
		/*	put out buff up to but not including last white space */
		for( lc = iblank;
		    buff[ lc ] == '\t'  ||  buff[ lc ] == ' '  &&  lc > 0;
		    lc-- );
		putbuff( 0, lc );
	}
	puts( trailer );	/* includes new-line */
	if ( indentstr )
		fputs( indentstr, stdout );
	else
		for( lc = 0; lc < indent; lc++)
			putchar(' ');
	cr = indent;
	for( lc = iblank + 1; lc <= buffct; lc++ ) {
		switch( c = buff[ lc ] ) {
		case ' ':
		case '\t':
			continue;
		}
		putchar( c );
		cr = colct( c, cr );
	}
}


/*
	positive atoi()
*/
#include	<ctype.h>

static
patoi( flag, a )
int	flag;
char	*a;
{
	register char	*cp;

	for( cp = a;  *cp;  cp++ ) {
		if( !isdigit( *cp ) ) {
			fprintf( stderr,
				"%s:  illegal numeric argument \"-%c %s\"\n",
				cmd, flag, a );
			exit(1);
		}
	}
	return  atoi(a);
}


static
putbuff( begin, finish )
register int	begin;
register int	finish;
{
	for( ;  begin <= finish;  putchar( buff[ begin++ ] ) );
}
