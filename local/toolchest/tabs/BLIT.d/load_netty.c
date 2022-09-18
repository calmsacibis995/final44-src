/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
#include <stdio.h>
#include <termio.h>
#include <sys/jioctl.h>

/*
 *	This program, "load_netty", loads a compiled copy of netty.c
 *	into a Blit layer and sets the environmental variables for
 *	running the assorted UNIX(TM) screen oriented software tools.
 *	load_netty is invoked with the following line to the shell.
 *
 *		$ exec load_netty [optional flags and strings]
 *
 *	If a banner line command is provided load_netty will
 *	configure netty.m so that one of the lines of the layer will
 *	be reserved as a banner line.
 *
 *	After load_netty has completed the download it exec's a shell
 *	to take over in the layer.  If -s shell is speicified "shell"
 *	will be exec'ed.  Otherwise the shell variable SHELL
 *	is used.  If SHELL is undefined then /bin/sh is used.
 *
 */

/*
 *	JETTY_ARGS controls banner line attributes.
 *	This constant is only used if a backgroud process
 *	is supplied.
 *
 */
#define JETTY_ARGS	"-Top"

/*
 *	The following two constants define the location of the
 *	local copies of the Blit loader (JLD) and the compiled
 *	version of netty.c (JETTY).
 *
 */

/*
#define JETTY		"/usr/jerq/lib/netty.m"
*/
#define JLD		"68ld"


/*
#define DETTY		"/usr/dmd/lib/netty.m"
*/
#define DLD		"32ld"

#define FALSE	0
#define TRUE	1

void
do_help ()
{
printf ("usage: exec load_netty [-eiv] [-f flags] [-s shell] [-b banner_prog]\n\n");
printf ("   -e	for ignore eof for exec'ed shell\n");
printf ("   -i	reserve space for icons\n");
printf ("   -v	for vi mode - don't change the baud rate\n");
printf ("   -f	flags for 68ld - typically t and/or T\n");
printf ("   -s	shell or program to exec in the layer\n");
printf ("   -b	banner line program - also reserves 1 line for banner stuff\n\n");
printf ("The load flags will be ignored it -b has not been specified.\n");
printf ("The default load flag is T for Top banner.  Use t for texture.\n");
printf ("Load flags other than \"Tti\" translate to \"banner on the bottom\".\n");
}

main (argc, argv)
int     argc;
char  **argv;
{
	void do_help ();
	extern  char   **environ;
	char   *new_env[256];
	char  **tptr;				/* TERM */
	char  **cptr;				/* COLUMNS */
	char  **lptr;				/* LINES */
	char  **tcptr;				/* TERMCAP */
	char  **shptr;				/* SHELL */
	char   *ptr1;
	char    buffer[4096];
	char    down_load[1024];
	char    exec_banner[1024];
	char   *background;
	char   *shell;
	char   *ld_flags;
	char   *icon_flags;
	int     vi_mode;
	int	ignore_eof;
	int	icons;
	int     x;
	int     y;
	int     len;
	struct  jwinsize jtty_stuff;
	struct  termio ntty_stuff;
	register char **p1 = new_env;
	register char **p2 = environ;

	background = 0;
	shell = 0;
	ld_flags = JETTY_ARGS;
	ignore_eof = FALSE;
	icons = FALSE;
	icon_flags = "\0";
	vi_mode = FALSE;
/*
 *	Process the command line arguments
 *
 */
 	for (x = 1; x < argc; x++)
 	{
 		ptr1 = argv[x];
 		if (*ptr1 != '-')
 			continue;
 		ptr1++;
 		while (*ptr1)
 		{
			switch (*ptr1)
			{
			case '\0':	/* Normal Use */
				break;
			case 'b':	/* Background Process */
				background = argv[x + 1];
				x++;
				break;
			case 'e':	/* No eof */
				ignore_eof = TRUE;
				break;
			case 'i':	/* icons */
				icon_flags = "i";
				icons = TRUE;
				break;
			case 'f':	/* Specify 68ld flags */
				ld_flags = argv[x + 1];
				x++;
				break;
			case 's':	/* Specify a Shell */
				shell = argv[x + 1];
				x++;
				break;
			case 'v':	/* vi Mode */
				vi_mode = TRUE;
				break;
			default:
				do_help ();
				exit (0);
			}

			ptr1++;
 		}
 	}

/*
 *	Check if this is running under layers
 *
 */
	if (ioctl (0, JMPX, 0) == -1)
	{
		fprintf (stderr, "load_netty only works in a layer.\n");
		exit(1);
	}

	if (ioctl (0, JWINSIZE, &jtty_stuff) == -1)
	{
		fprintf (stderr, "load_netty cannot determine the layer size.\n");
		exit(1);
	}

	if(ioctl(0, TCGETA, &ntty_stuff) == -1)
	{
		fprintf (stderr, "load_netty cannot determine the tty speed.\n");
		exit(1);
	}

	y = jtty_stuff.bytesy;
	if (background)
		y--;
	x = jtty_stuff.bytesx;

/*
 *	Remap the environment
 *
 */
	environ = new_env;

	while ((*p1 = *p2++) != NULL)
	{
		if (strncmp ("TERM=", *p1, 5) == 0)
		{
			tptr = p1++;
			continue;
		}
		if (strncmp ("COLUMNS=", *p1, 8) == 0)
		{
#ifdef DO_LINES
			cptr = p1++;
#else
			cptr = p1;
#endif
			continue;
		}
		if (strncmp ("LINES=", *p1, 6) == 0)
		{
#ifdef DO_LINES
			lptr = p1++;
#else
			lptr = p1;
#endif
			continue;
		}
		if (strncmp ("TERMCAP=", *p1, 8) == 0)
		{
			tcptr = p1++;
			continue;
		}
		if (strncmp ("SHELL=", *p1, 5) == 0)
		{
			shptr = p1++;
			continue;
		}
		p1++;
	}

	if (tptr == NULL)				/* TERM */
		tptr = p1++;
#ifdef DO_LINES
	if (cptr == NULL)				/* COLUMNS */
		cptr = p1++;
	if (lptr == NULL)				/* LINES */
		lptr = p1++;
#endif
	if (tcptr == NULL)				/* TERMCAP */
		tcptr = p1++;
	if (shell == 0)
	{
		if (shptr == NULL)			/* SHELL */
			ptr1 = "/bin/sh";
		else
			ptr1 = (char *) strchr (*shptr, '=') + 1;
	}
	else
		ptr1 = shell;

/*
 *	Set the TERM variable to netty - change this to $HOME/.nettyPID
 *	for EMACS without the Blit patches - see the code below
 *
 */
	*tptr = buffer;

	if (vi_mode)
		len = sprintf (buffer, "TERM=%s", "netty-vi");
	else
		len = sprintf (buffer, "TERM=%s", "netty");
/*
 *	If you are using EMACS without the Blit patches use
 *	the following to define your TERM variable.
 *
{
	FILE *fp;

	len = sprintf (buffer, "TERM=%s/%s%d",
		getenv ("HOME"), "netty", getpid());

	if ((fp = fopen (*tptr, "w")) == NULL)
	{
		fprintf (stderr, "load_netty: Cannot open %s for writing.", *tptr);
	}
	else
	{
	frpintf (fp, "%s\n",
		"CW=\033v%c%c%c%c\nJQ=1\nal=\033O!\nAL=\033O%c\nam=1\nbl=\07");
	frpintf (fp, "%s\n"
		"bx=32\nby=32\nce=\033Z\ncl=\014\ncm=\033Y%c%c");
	frpintf (fp, "%s\n"
		"dc=\033d\ndl=\033D!\nDL=\033D%c\nei=\033I@\nim=\033IA");
	frpintf (fp, "%s\n"
		"kd=\030OB\nkh=\030OE\nkl=\030OC\nkm=\033#\nkr=\030OD");
	frpintf (fp, "%s\n"
		"ku=\030OA\nkz=\030OF\nsf=\\\n\nSF=\033S%c\nup=\033A");
	frpintf (fp, "%s\n%s\nco=%d\nli=%d\n"
		"ve=\033{@\033#@\033X@",
		"vs=\033C@\033I@\033U@\033R@\033W@\033P@\033{B\033[@\033#A\033XA",
		x, y);
	fclose (fp);
	}
}
 */

	buffer[len++] = '\0';

/*
 *	Construct a termcap entry so that stuff like CMU EMACS will work
 *
 */
	*tcptr = &buffer[len];

	len += sprintf (&buffer[len],

	"TERMCAP=netty|netty-vi|netty-vi-new:\
	:al=\\EO!:AL=\\EO%%+ :am:bs:ce=\\EZ:cl=\\014:cm=\\EY%%r%%+ %%+ :\
	:dc=\\Ed:dl=\\ED!:DL=\\ED%%+ :ei=\\EI@:im=\\EIA:\
	:kd=\\030OB:kh=\\030OE:kl=\\030OC:kr=\\030OD:ku=\\030OA:pt:\
	:se=\\033R@:so=\\033RA:\
	:te=\\E{@\\E#@\\EX@:\
	:ti=\\EC@\\EI@\\EU@\\ER@\\EW@\\EP@\\E{B\\E[@\\E#A\\EXA:\
	:up=\\EA:\
	:vs=\\EC@\\EI@\\EU@\\ER@\\EW@\\EP@\\E{A\\E[A\\E#B\\EX@\\E[A:\
	:ve=\\E{@\\E[@\\E#@\\E[@:\
	:co#%d:li#%d",

		x, y);

	buffer[len++] = '\0';

#ifdef DO_LINES
/*
 *	Add the LINES and COLUMNS variables for curses and Warren's
 *	EMACS.
 *
 */
	*cptr = &buffer[len];
	len += sprintf (&buffer[len], "COLUMNS=%d", x);
	buffer[len++] = '\0';
	*lptr = &buffer[len];
	len += sprintf (&buffer[len], "LINES=%d", y);
	buffer[len++] = '\0';
#endif

/*
 *	Construct the download command and execute it
 *
	if (getenv ("DMD"))
 */
#ifdef DMD
 	{
		if (background)
			sprintf (down_load, "%s %s %s %s",
				DLD, DETTY, ld_flags, icon_flags);
		else
			sprintf (down_load, "%s %s %s",
				DLD, DETTY, icon_flags);
 	}
#endif
/*
 	else
*/
#ifdef mc68000
 	{
		if (background)
			sprintf (down_load, "%s %s %s", JLD, JETTY, ld_flags);
		else
			sprintf (down_load, "%s %s", JLD, JETTY);
 	}
#endif
	system (down_load);

 	fflush (stdout);

/*
 *	Set the speed down so look ahead and padding are more appropriate
 *	for BTL EMACS - comment this out if you primarily use vi or CMU
 *	EMACS.
 *
 */
	if (vi_mode == FALSE)
	{
	 	ntty_stuff.c_cflag &= ~(017);
	 	ntty_stuff.c_cflag |= 011;
	}
 	ntty_stuff.c_lflag |= 020;	/* Enable ECHOE */
	ioctl(0, TCXONC, 1);
	ioctl(0, TCSETAW, &ntty_stuff);

/*
 *	Start up the banner line in the background
 *
 */
	if (background)
	{
		sprintf (exec_banner, "exec %s &", background);
		system (exec_banner);
	}

/*
 *	Exec() in the new shell with the converted environment, etc.
 *
 */
	sprintf (exec_banner, "exec %s", ptr1);

	if (ignore_eof)
	{
		do
		{
			system (exec_banner);
	
		} while (ignore_eof);
	}
	else
	{
		execl ("/bin/sh", "sh", "-c", exec_banner, 0);
		perror ("load_netty");
	}
}
