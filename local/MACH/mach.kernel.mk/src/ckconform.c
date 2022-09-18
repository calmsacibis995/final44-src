/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log$
 */

#include <stdio.h>
#include <libc.h>
#include <c.h>

char *prog;

main(argc, argv)
int argc;
char **argv;
{
    int edit = 0;

    if (argc < 2)
	quit(1, "usage: ckconform files ...\n");

    if ((prog = rindex(argv[0], '/')) == NULL)
	prog = argv[0];
    else
	prog++;
    argv++;
    argc--;

    if (strcmp(argv[0], "-edit") == 0) {
	edit++;
	argv++;
	argc--;
    }
    while (argc-- > 0) {
	if (check_conform(*argv) && edit)
	    for (;;) {
		editor(*argv,
		       "Please update to conform with current standards.");
		if (check_conform(*argv) == 0)
		    break;
		if (!getbool("Edit again?", 1))
		    break;
	    }
	argv++;
    }
    exit(0);
}

check_conform(file)
char *file;
{
    FILE *fp;
    char *p, buffer[BUFSIZ];
    int state = 1;
    int NR = 0;
    int pound = 0;
    int quote = 0;

    if ((fp = fopen(file, "r")) == NULL) {
	fprintf(stderr, "%s: fopen %s: %s\n", prog, file, errmsg(-1));
	return(1);
    }
    fprintf(stderr, "%s:\n", file);
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
	if (state == 13)
	    break;
	NR++;
	if ((p = rindex(buffer, '\n')) != NULL)
	    *p = '\0';
	p = buffer;
	switch (state) {
	case 1:
	    if (*p == '%') {
		p++;
		if (*p++ != '{')
		    break;
		while (*p == ' ')
		    p++;
		if (*p != '\0')
		    break;
		continue;
	    }
	    if (*p == '"') {
		p++;
		quote++;
	    } else if (*p == '#') {
		p++;
		if (*p == '!')
		    continue;
		pound++;
	    } else {
		if (*p++ != '/')
		    break;
		if (*p++ != '*')
		    break;
	    }
	    while (*p == ' ')
		p++;
	    if (*p != '\0')
		break;
	    state++;
	    continue;
	case 2:
	    if (quote) {
		if (strcmp(p, "\" Mach Operating System") != 0)
		    break;
	    } else if (pound) {
		if (strcmp(p, "# Mach Operating System") != 0)
		    break;
	    } else if (strcmp(p, " * Mach Operating System") != 0)
		break;
	    state++;
	    continue;
	case 3:
	    if (quote) {
		if (strcmp(p, "\" Copyright (c) 1989 Carnegie-Mellon University") != 0)
		    break;
	    } else if (pound) {
		if (strcmp(p, "# Copyright (c) 1989 Carnegie-Mellon University") != 0)
		    break;
	    } else if (strcmp(p, " * Copyright (c) 1989 Carnegie-Mellon University") != 0)
		break;
	    state++;
	    continue;
	case 4:
	    if (quote) {
		if (strcmp(p, "\" All rights reserved.  The CMU software License Agreement specifies") == 0) {
		    state++;
		    continue;
		}
		if (strncmp(p, "\" Copyright (c) 19", 18) != 0)
		    break;
		p += 18;
	    } else if (pound) {
		if (strcmp(p, "# All rights reserved.  The CMU software License Agreement specifies") == 0) {
		    state++;
		    continue;
		}
		if (strncmp(p, "# Copyright (c) 19", 18) != 0)
		    break;
		p += 18;
	    } else {
		if (strcmp(p, " * All rights reserved.  The CMU software License Agreement specifies") == 0) {
		    state++;
		    continue;
		}
		if (strncmp(p, " * Copyright (c) 19", 19) != 0)
		    break;
		p += 19;
	    }
	    if (*p < '7' || *p > '9')
		break;
	    p++;
	    if (*p < '0' || *p > '9')
		break;
	    p++;
	    if (strcmp(p, " Carnegie-Mellon University") != 0)
		break;
	    continue;
	case 5:
	    if (quote) {
		if (strcmp(p, "\" the terms and conditions for use and redistribution.") != 0)
		    break;
	    } else if (pound) {
		if (strcmp(p, "# the terms and conditions for use and redistribution.") != 0)
		    break;
	    } else if (strcmp(p, " * the terms and conditions for use and redistribution.") != 0)
		break;
	    state++;
	    continue;
	case 6:
	    if (quote) {
		if (*p++ != '"')
		    break;
	    } else if (pound) {
		if (*p++ != '#')
		    break;
	    } else {
		if (*p++ != ' ')
		    break;
		if (*p++ != '*')
		    break;
		if (*p++ != '/')
		    break;
	    }
	    while (*p == ' ')
		p++;
	    if (*p != '\0')
		break;
	    state++;
	    continue;
	case 7:
	    if (quote) {
		if (*p++ != '"')
		    break;
	    } else if (pound) {
		if (*p++ != '#')
		    break;
	    } else {
		if (*p++ != '/')
		    break;
		if (*p++ != '*')
		    break;
	    }
	    while (*p == ' ')
		p++;
	    if (*p != '\0')
		break;
	    state++;
	    continue;
	case 8:
	    if (quote) {
		if (strcmp(p, "\" HISTORY") != 0)
		    break;
	    } else if (pound) {
		if (strcmp(p, "# HISTORY") != 0)
		    break;
	    } else if (strcmp(p, " * HISTORY") != 0)
		break;
	    state++;
	    continue;
	case 9:
	    if (check_log(p, pound, quote) == 0) {
		state++;
		continue;
	    }
	    if (check_at(p, pound, quote))
		break;
	    state += 3;
	    continue;
	case 10:
	    if (check_rev(p, pound, quote) == 0 ||
		check_at(p, pound, quote) == 0) {
		state++;
		continue;
	    }
	    if (!pound && !quote) {
		if (strncmp(p, " */", 3) != 0)
		    break;
		p += 3;
	    }
	    while (*p == ' ')
		p++;
	    if (*p != '\0')
		break;
	    state += 3;
	    continue;
	case 11:
	    if (pound || quote) {
		if ((quote && *p == '"') || (pound && *p == '#')) {
		    p++;
		    if (*p != '\0' && *p != ' ' && *p != '\t')
			break;
		    continue;
		}
		p++;
		while (*p == ' ')
		    p++;
		if (*p != '\0')
		    break;
		state += 2;
		continue;
	    }
	    if (*p++ != ' ')
		break;
	    if (*p++ != '*')
		break;
	    if (*p == '/') {
		p++;
		while (*p == ' ')
		    p++;
		if (*p != '\0')
		    break;
		state += 2;
		continue;
	    }
	    if (*p != '\0' && *p != ' ' && *p != '\t')
		break;
	    continue;
	case 12:
	    if (check_log(p, pound, quote) == 0) {
		state -= 2;
		continue;
	    }
	    if (quote) {
		if (*p++ != '"')
		    break;
	    } else if (pound) {
		if (*p++ != '#')
		    break;
	    } else {
		if (*p++ != ' ')
		    break;
		if (*p++ != '*')
		    break;
	    }
	    if (*p != '\0' && *p != ' ' && *p != '\t')
		break;
	    continue;
	default:
	    fprintf(stderr, "unknown state %d\n", state);
	    break;
	}
	fprintf(stderr, "%s\n", buffer);
	fprintf(stderr, "Error on line %d (state %d)\n", NR, state);
	break;
    }
    (void) fclose(fp);
    if (state != 13) {
	fprintf(stderr, "File does not conform to standards (state %d)\n",
		state);
	return(1);
    }
    return(0);
}

check_at(p, pound, quote)
char *p;
int pound, quote;
{
    if (quote) {
	if (*p++ != '"')
	    return(1);
    } else if (pound) {
	if (*p++ != '#')
	    return(1);
    } else {
	if (*p++ != ' ')
	    return(1);
	if (*p++ != '*')
	    return(1);
    }
    if (*p++ != ' ')
	return(1);
    if (*p != ' ' && (*p < '0' || *p > '3'))
	return(1);
    p++;
    if (*p < '0' || *p > '9')
	return(1);
    p++;
    if (*p++ != '-')
	return(1);
    if (*p < 'A' || *p > 'Z')
	return(1);
    p++;
    if (*p < 'a' || *p > 'z')
	return(1);
    p++;
    if (*p < 'a' || *p > 'z')
	return(1);
    p++;
    if (*p++ != '-')
	return(1);
    if (*p < '7' || *p > '9')
	return(1);
    p++;
    if (*p < '0' || *p > '9')
	return(1);
    p++;
    if (*p++ != ' ')
	return(1);
    while (*p != '(' && *p != '\0')
	p++;
    if (*(p-1) != ' ')
	return(1);
    if (*p++ != '(')
	return(1);
    while (*p != ')' && *p != ' ' && *p != '\0')
	p++;
    if (*p++ != ')')
	return(1);
    if (*p++ != ' ')
	return(1);
    if (*p++ != 'a')
	return(1);
    if (*p++ != 't')
	return(1);
    if (*p++ != ' ')
	return(1);
    return(0);
}

check_log(p, pound, quote)
char *p;
int pound, quote;
{
    if (quote) {
	if (strncmp(p, "\" $Log", 6) != 0)
	    return(1);
	p += 6;
    } else if (pound) {
	if (strncmp(p, "# $Log", 6) != 0)
	    return(1);
	p += 6;
    } else {
	if (strncmp(p, " * $Log", 7) != 0)
	    return(1);
	p += 7;
    }
    if (*p == '$' && *(p+1) == '\0')
	return(0);
    if (*p++ != ':')
	return(1);
    if (*p++ != '\t')
	return(1);
    while (*p == '-' || *p == '.' || *p == '_' ||
	   (*p >= 'A' && *p <= 'Z') ||
	   (*p >= 'a' && *p <= 'z') ||
	   (*p >= '0' && *p <= '9'))
	p++;
    if (*p++ != ',')
	return(1);
    if (*p++ != 'v')
	return(1);
    if (*p++ != ' ')
	return(1);
    if (*p++ != '$')
	return(1);
    if (*p++ != '\0')
	return(1);
    return(0);
}

check_rev(p, pound, quote)
char *p;
int pound, quote;
{
    if (quote) {
	if (strncmp(p, "\" Revision ", 11) != 0)
	    return(1);
	p += 11;
    } else if (pound) {
	if (strncmp(p, "# Revision ", 11) != 0)
	    return(1);
	p += 11;
    } else {
	if (strncmp(p, " * Revision ", 12) != 0)
	    return(1);
	p += 12;
    }
    while (*p >= '0' && *p <= '9')
	p++;
    if (*p++ != '.')
	return(1);
    while (*p >= '0' && *p <= '9')
	p++;
    if (*p++ != ' ')
	return(1);
    if (*p++ != ' ')
	return(1);
    if (*p < '7' || *p > '9')
	return(1);
    p++;
    if (*p < '0' || *p > '9')
	return(1);
    p++;
    if (*p++ != '/')
	return(1);
    if (*p < '0' || *p > '1')
	return(1);
    p++;
    if (*p < '0' || *p > '9')
	return(1);
    p++;
    if (*p++ != '/')
	return(1);
    if (*p < '0' || *p > '3')
	return(1);
    p++;
    if (*p < '0' || *p > '9')
	return(1);
    p++;
    if (*p++ != ' ')
	return(1);
    if (*p++ != ' ')
	return(1);
    if (*p < '0' || *p > '2')
	return(1);
    p++;
    if (*p < '0' || *p > '9')
	return(1);
    p++;
    if (*p++ != ':')
	return(1);
    if (*p < '0' || *p > '5')
	return(1);
    p++;
    if (*p < '0' || *p > '9')
	return(1);
    p++;
    if (*p++ != ':')
	return(1);
    if (*p < '0' || *p > '5')
	return(1);
    p++;
    if (*p < '0' || *p > '9')
	return(1);
    p++;
    if (*p++ != ' ')
	return(1);
    if (*p++ != ' ')
	return(1);
    while (*p != ' ' && *p != '\0')
	p++;
    if (*p != '\0')
	return(1);
    return(0);
}
