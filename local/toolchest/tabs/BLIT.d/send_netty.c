/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
#undef PORTABLE
#ifdef UCB
#define PORTABLE	1
#endif

#include <stdio.h>

extern char *strchr();

#define CTRL(x)		('x' & 037)
#define TRUE		1
#define FALSE		0

#define NETTY_BUFF_SIZE	128

format_error ()
{
	printf ("Usage:\n");
	printf ("	send_netty -t mouse_texture_file\n");
	printf (" or\n");
	printf ("	send_netty -i icon_number icon_file\n");
	printf (" or\n");
	printf ("	send_netty -p place_number icon_number title return_string\n");
	printf (" or\n");
	printf ("	send_netty -f function_key_name return_string\n");
	printf (" or\n");
	printf ("	send_netty -m menu_name menu_position display_string return_sting\n");
	printf (" or\n");
	printf ("	send_netty -b banner_string\n");
	printf (" or\n");
	printf ("	send_netty -c (clear)\n");
	cook (1);
}

main (argc, argv)
int     argc;
char  **argv;
{
	char print_buffer[NETTY_BUFF_SIZE];
	char * ptr;
	char bracket;
	char pf_key;
	char menu;
	char menu_position;
	char icon;
	char position;

	ptr = argv[1];
	while (*ptr)
	{
		switch (*ptr++)
		{
		case '-':
			break;
		case 't':	/* Textures */
			if (argc != 3)
				format_error ();
			uncook ();
			Tex16_Load (argv[2]);
			cook (0);
		case 'i':	/* Icons */
			if (argc != 4)
				format_error ();
			icon = icon_number (argv[2]);
			uncook ();
			Icon_Load (icon, argv[3]);
			cook (0);
		case 'p':	/* Position Icons */
			if (argc != 6)
				format_error ();
			position = icon_number (argv[2]);
			icon = icon_number (argv[3]);
			uncook ();
			printf ("\033.%c%c", position, icon);

			trim_string (print_buffer, argv[4]);
			bracket = bracket_char (print_buffer);
			printf ("%c%s%c", bracket, print_buffer, bracket);

			trim_string (print_buffer, argv[5]);
			bracket = bracket_char (print_buffer);
			printf ("%c%s%c", bracket, print_buffer, bracket);
			cook (0);
		case 'f':	/* Function Keys */
			if (argc != 4)
				format_error ();
			pf_key = function_key (argv[2]);
			uncook ();
			trim_string (print_buffer, argv[3]);
			bracket = bracket_char (print_buffer);
			printf ("\033F%c%c%s%c",
				pf_key, bracket, print_buffer, bracket);
			cook (0);
		case 'm':	/* Popup Menus */
			if (argc != 6)
				format_error ();
			menu = menu_name (argv[2]);
			menu_position = menu_item (argv[3]);
			uncook ();
			printf ("\033#%c", menu);

			trim_string (print_buffer, argv[4]);
			bracket = bracket_char (print_buffer);
			printf ("\033M%c%c%s%c",
				menu_position, bracket, print_buffer, bracket);

			trim_string (print_buffer, argv[5]);
			bracket = bracket_char (print_buffer);
			printf ("\033m%c%c%s%c",
				menu_position, bracket, print_buffer, bracket);

			printf ("\033#@");		/* Back to sh Menu */
			cook (0);
		case 'b':	/* Banner Line */
			if (argc != 3)
				format_error ();
			uncook ();
			trim_string (print_buffer, argv[2]);
			bracket = bracket_char (print_buffer);
			printf ("\033b%c%s%c", bracket, print_buffer, bracket);
			cook (0);
		case 'c':	/* Clear */
			printf ("\033^\014");
			exit (0);
		default:
			format_error ();
		}
	}

	format_error ();
}

/*
 * Routine sends an encoded byte to the DMD - hex digits are compacted
 * and sent as one character.
 *
 * The sytle of encoding is like that found on the Concept100 terminal
 *
 */
Send_Concept (number)
register int    number;
{
	static int last_number;
	static int second = FALSE;

/*
 *	Send the hex values as one short
 *
 */
	if (second == FALSE)
	{
		second = TRUE;
		last_number = number;
		if (number < 16)
			return;
	}
	else
	{
		if (number > 15)
		{
			Send_Concept (0);
		}
		else
		{
			number = (last_number << 4) + number;
		}
	}
	second = FALSE;
/*
 *	End hex to short
 *
 */

	if (number < 0)
		number = 0;
	if (number > 287)
		number = 287;

	if (number > 191)
	{
		printf ("%c%c", CTRL (B), ' ' + number - 192);
		return;
	}

	if (number > 95)
	{
		printf ("%c%c", CTRL (A), ' ' + number - 96);
		return;
	}

	printf ("%c", ' ' + number);
}

hex (ch)
register char    ch;
{
    if ((ch >= '0') && (ch <= '9'))
	return (ch - '0');
    if ((ch >= 'A') && (ch <= 'F'))
	return (10 + ch - 'A');
    if ((ch >= 'a') && (ch <= 'f'))
	return (10 + ch - 'a');
    return (0);
}

Icon_Load (id, filename)
char id;
char *filename;
{
	register FILE * fp;
	register int ch;

	if ((fp = fopen (filename, "r")) == NULL)
	{
		printf ("send_netty: Cannot open file: %s\n", filename);
		cook (1);
	}

	printf ("\033t");	/* Trigger the Download */
	printf ("%c", id);

	ch = getc (fp);
	if (((ch >= '0') && (ch <= '9')) ||
		((ch >= 'A') && (ch <= 'F')) ||
		((ch >= 'a') && (ch <= 'f')))
	{
		if (((ch = getc (fp)) != 'x') && (ch != 'X'))
		{
		/* old format */
			fclose (fp);
			if ((fp = fopen (filename, "r")) == NULL)
			{
				Send_Concept (259);
				printf ("send_netty: Cannot open file: %s\n",
					filename);
				cook (1);
			}
			while ((ch = getc (fp)) != EOF)
			{
				if (((ch >= '0') && (ch <= '9')) ||
					((ch >= 'A') && (ch <= 'F')) ||
					((ch >= 'a') && (ch <= 'f')))
				{
					Send_Concept (hex (ch));
				}
				else
				{
					if (ch == '\n')
					{
						Send_Concept (258);
					}
					else
					{
						break;
					}
				}
			}
		}
		else
		{
			for (;;)
			{
				Send_Concept (hex (getc (fp)));
				Send_Concept (hex (getc (fp)));
				Send_Concept (hex (getc (fp)));
				Send_Concept (hex (getc (fp)));
				ch = getc (fp);/* ',' */
				if ((ch != ',') && (ch != EOF))
				{
					Send_Concept (hex (ch));
					Send_Concept (hex (getc (fp)));
					Send_Concept (hex (getc (fp)));
					Send_Concept (hex (getc (fp)));
					getc (fp);/* ',' */
				}
				ch = getc (fp);
				if (ch == '0')
				{
					getc (fp);/* 'x' */
				}
				else
				{
					if (ch == '\n')
					{
						Send_Concept (258);
						getc (fp);/* '0' */
						getc (fp);/* 'x' */
					}
					else
					{
						break;
					}
				}
			}
		}
	}
	else
	{
		while ((ch != '{') && (ch != EOF)) /* } */
			ch = getc (fp);
		for (;;)
		{
			while (((ch = getc (fp)) != 'x') &&
				(ch != 'X') && (ch != EOF))
			{
			};
			if (ch == EOF)
				break;
			Send_Concept (hex (getc (fp)));
			Send_Concept (hex (getc (fp)));
			Send_Concept (hex (getc (fp)));
			Send_Concept (hex (getc (fp)));
			ch = getc (fp);
			if ((ch != ',') && (ch != EOF))
			{
				Send_Concept (hex (ch));
				Send_Concept (hex (getc (fp)));
				Send_Concept (hex (getc (fp)));
				Send_Concept (hex (getc (fp)));
			}
			Send_Concept (258);
		}
	}
	Send_Concept (259);
	fclose (fp);
}

Tex16_Load (filename)
char *filename;
{
	register int    i;
	register int    c;
	register int     number;
	FILE *fp;

	if ((fp = fopen (filename, "r")) == NULL)
	{
		printf ("send_netty: Cannot open file: %s\n", filename);
		cook (1);
	}

	printf ("\033T");

	for (i = 0; i < 16; i++)
	{
		for (c = FALSE, number = 0; !c;)
		{
			if (number == EOF)
			{
				for (number = 0; number < 16; number++)
					printf ("__");

				printf ("\nsend_netty: \"%s\" is not a texture16 file.\n\n",
					filename);

				format_error ();
			}

			if ((number = getc (fp)) != '0')
				continue;

			if ((number = getc (fp)) != 'x')
				continue;

			c = TRUE;
		}

		for (number = 0; number < 4; number++)
		{
			Send_Concept (hex (getc (fp)));
		}
	}
}

trim_string (to_string, from_string)
register char   *from_string;
register char   *to_string;
{
	char   *start;
	int     count;
	int     number;
	int     index;

	count = 1;
	while ((*from_string) && (count < NETTY_BUFF_SIZE))
	{
		switch (*from_string)
		{
		case '\\': 
			from_string++;
			switch (*from_string)
			{
			case 'b':		/* Control H */
				*to_string++ = '\b';
				break;

			case 'f':		/* Control L */
				*to_string++ = '\f';
				break;

			case 'n':		/* Newline */
				*to_string++ = '\n';
				break;

			case 'r':		/* Carriage Return */
				*to_string++ = '\r';
				break;

			case 't':		/* TAB - Control I */
				*to_string++ = '\t';
				break;

			case '\\':		/* Quoted Backslash */
				*to_string++ = '\\';
				break;

			case '0':		/* Octal Numbers */
				index = number = 0;
				while ((*++from_string >= '0' &&
						*from_string <= '7') &&
							(index < 3))
				{
					number <<= 3;
					number |= (*from_string - '0');
					index++;
				}
				*to_string++ = number;
				--from_string;
				break;
			default:		/* Quoted Random Character */
				*to_string++ = *from_string;
			}
			from_string++;
			break;
		default:			/* Normal Character */
			*to_string++ = *from_string++;
		}
		count++;
	}

	*to_string = '\0';

	return (count);
}

bracket_char (buffer)
register char *buffer;
{
	register int number;

	for (number = 1; number < 256; number++)
	{
		if (strchr (buffer, number) == NULL)
			break;
	}
	return (number);
}

#define N_KEYS 15
char *keys[] =
{
	"f1",
	"f2",
	"f3",
	"f4",
	"f5",
	"f6",
	"f7",
	"f8",
	"clear",
	"home",
	"up",
	"bottom",
	"left",
	"down",
	"right"
};

function_key (str)
register char *str;
{
	register int index;

	for (index = 0; index < N_KEYS; index++)
	{
		if (strcmp (keys[index], str) == 0)
			return ('@' + index);
	}
	printf ("send_netty: The function key identifiers are as follows:\n");
	for (index = 0; index < N_KEYS; index++)
		printf ("	%s\n", keys[index]);
	cook (1);
}

#define N_MENUS	4
char *menus[] =
{
	"shell",
	"emacs",
	"vi",
	"extra"
};

menu_name (str)
register char *str;
{
	register int index;

	for (index = 0; index < N_MENUS; index++)
	{
		if (strcmp (menus[index], str) == 0)
			return ('@' + index);
	}
	printf ("send_netty: The menu names are as follows:\n");
	for (index = 0; index < N_MENUS; index++)
		printf ("	%s\n", menus[index]);
	cook (1);
}

#define N_ICONS	32

icon_number (str)
register char *str;
{
	register int index;

	index = atoi (str);

	if ((index >= 1) && (index <= N_ICONS))
		return ('@' + index - 1);
	printf ("send_netty: The icon and position numbers must be in the range (1 ... %d)\n",
		N_ICONS);
	cook (1);
}

#define N_MENU_ITEMS	16

menu_item (str)
register char *str;
{
	register int index;

	index = atoi (str);

	if ((index >= 1) && (index <= N_MENU_ITEMS))
		return ('@' + index - 1);
	printf ("send_netty: The menu numbers must be in the range (1 ... %d)\n",
		N_MENU_ITEMS);
	cook (1);
}

#ifdef PORTABLE
/*
 * use system() to change modes - ah portability!!
 *
 */
cook (value)
register int value;
{
	fflush (stdout);
	system ("exec stty echo -raw");
	exit (value);
}

uncook ()
{
	system ("exec stty -echo raw");
}	

char *
strchr (str, c)
register char *str;
register char c;
{
	for (; *str; str++)
		if (*str == c)
			return (str);

	return (NULL);
}
#else

#include <termio.h>

#define STTYRAW		1
#define STTYNORM	0

struct termio nttybuf;		/* ioctl buffers */
struct termio rttybuf;
static int set_tty;

cook (value)
register int value;
{
	fflush (stdout);
	cp_stty (STTYNORM);
	exit (value);
}

uncook ()
{
	static int first;

	if (first == 0)
	{
		first++;
		cp_start ();
	}
	cp_stty (STTYRAW);
}

/*
 *
 *	cp_start()
 *
 *	This routine initiates the terminal interaction with
 *	comnd.  This is done by getting the terminal mode and
 *	setting up the structures for subsequent calls to cp_stty().
 *
 *	Return: TRUE or FALSE
 *
 */
cp_start()
{

	if(ioctl(0, TCGETA, &nttybuf) < 0)	/* Assume ENOTTY */
	{
		set_tty = FALSE;

	} else {

		set_tty = TRUE;

	/* Setup raw mode struct */

	/* Don't map c/r to newline and Don't map newline to c/r on input */
	/* Disable parity checking on input, and break int.s. */

		rttybuf.c_iflag = nttybuf.c_iflag;
		rttybuf.c_iflag &= ~(IGNPAR | PARMRK | INPCK
				     | INLCR | IGNCR | ICRNL | IGNBRK);
		rttybuf.c_iflag |= (ISTRIP | BRKINT | IXON | IXANY);

		/*	extra flags or assumed from user's stty
		 *	&= ~IUCLC;
		 *	|= IXOFF;
		 */

		/* Map newline to newline c/r on output */
		/* Postprocess the output
		rttybuf.c_oflag = nttybuf.c_oflag;
		rttybuf.c_oflag |= (ONLCR|OPOST);
		rttybuf.c_oflag &= ~OCRNL;
		*/
		rttybuf.c_oflag = 0;

		rttybuf.c_cflag = nttybuf.c_cflag;

		/* Echo newline and flush after int. or quit */
		/* This may cause trouble if you use a lot of */
		/* interrupts - NOFLSH */
		rttybuf.c_lflag = ECHONL | ISIG;

		rttybuf.c_line = nttybuf.c_line;

		rttybuf.c_cc[VINTR] = 0377;
		rttybuf.c_cc[VQUIT] = 0377;

		rttybuf.c_cc[VERASE] = nttybuf.c_cc[VERASE];
		rttybuf.c_cc[VKILL] = nttybuf.c_cc[VKILL];
	
		/* MIN characters to be read */
		rttybuf.c_cc[VMIN] = (unsigned char)1;

		/* MAX time value to wait */
		rttybuf.c_cc[VTIME] = (unsigned char)0;
		rttybuf.c_cc[6] = nttybuf.c_cc[6];
		rttybuf.c_cc[7] = nttybuf.c_cc[7];
	}

	return(set_tty);
}

/*
 *
 *	cp_stty is the routine that handles switching back and forth
 *	from cannonical (cooked) to non-cannonical (raw) modes.
 *
 *	flag is the mode to be instantiated
 *
 *	Return: TRUE or FALSE
 *
 */
cp_stty(flag)
int flag;
{
	register int	cnt = 0;

	if(set_tty)
	{
		while(cnt < 5)
		{
			if(flag == STTYRAW)
			{
				ioctl(0, TCXONC, 1);
				if(ioctl(0, TCSETAW, &rttybuf) == 0) break;
			} else {
				ioctl(0, TCXONC, 1);
				if(ioctl(0, TCSETAW, &nttybuf) == 0) break;
			}
		       cnt++;
		}

		if(cnt == 5)
		{
			return(FALSE);
		}

		return(TRUE);
	}

	return(FALSE);
}
#endif

