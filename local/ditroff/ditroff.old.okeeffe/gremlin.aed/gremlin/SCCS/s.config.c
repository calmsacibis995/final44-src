h33579
s 00001/00001/00029
d D 1.3 83/06/07 22:34:21 layer 4 3
c changed the mail command (for gripe) to /usr/ucb/Mail
e
s 00002/00002/00028
d D 1.2 83/04/18 14:30:50 slatteng 3 1
c Slattengren takeover
e
s 00002/00002/00028
d R 1.2 83/04/18 14:19:49 slatteng 2 1
c Slattengren takeover
e
s 00030/00000/00000
d D 1.1 83/04/18 13:45:13 slatteng 1 0
c date and time created 83/04/18 13:45:13 by slatteng
e
u
U
t
T
I 1
D 3
/* config.c -
E 3
I 3
/* %W%	%G%
E 3
 *
 * This file contains a few strings that define file locations for
 * the current gremlin configuration.
 */

/* The following string must contain the rooted name of gremlin's
 * library directory.
 */

char GLibrary[] = "/usr/local/gremlib/";

/* The following string contains the full rooted name of the file
 * giving the terminal-to-display mappings.
 */

char GDisplays[] = "/usr/local/displays";


/* The following string gives the shell command used to send mail
 * to the gremlin maintainer.
 */

D 3
char GMailCommand[] = "mail n:barry";
E 3
I 3
D 4
char GMailCommand[] = "mail slatteng@ucbernie";
E 4
I 4
char GMailCommand[] = "/usr/ucb/Mail slatteng@ucbernie";
E 4
E 3

/* The following string should indicate the rooted name of gremlin's 
 * color map
 */

char GMapFile[] = "/usr/local/gremlin.cmap";
E 1
