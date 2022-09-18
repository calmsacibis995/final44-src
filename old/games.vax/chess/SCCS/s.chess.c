h45768
s 00001/00002/00009
d D 4.2 88/10/19 16:53:59 bostic 2 1
c this should never have worked!  Anyhow, remove DUNGEON path, make
c error message useful
e
s 00011/00000/00000
d D 4.1 82/10/24 18:26:12 mckusick 1 0
c date and time created 82/10/24 18:26:12 by mckusick
e
u
U
t
T
I 1

static char sccsid[] = "	%M%	%I%	%E%	";

#include <stdio.h>
main()
{
	execl("/usr/games/lib/compat", "chess", "/usr/games/lib/chess", 0);
D 2
	execl("/usr/games/DUNGEON", "chess", "/usr/games/lib/chess", 0);
	printf(stderr, "Sorry, not today\n");
E 2
I 2
	fprintf(stderr, "chess: can't find /usr/games/lib/compat.\n");
E 2
	exit(1);
}
E 1
