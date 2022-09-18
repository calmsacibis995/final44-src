h44925
s 00005/00004/00117
d D 4.2 88/10/21 16:19:22 bostic 4 3
c fixes for gcc
e
s 00000/00000/00121
d D 4.1 80/10/01 16:37:58 bill 3 2
c Define 4.1
e
s 00001/00001/00120
d D 3.2 80/09/20 18:38:13 bill 2 1
c typo
e
s 00121/00000/00000
d D 3.1 80/08/15 01:55:05 bill 1 0
c date and time created 80/08/15 01:55:05 by bill
e
u
U
t
T
I 1
static	char sccsid[] = "%Z%%M% %I% %G%";
/*
 * arcv - convert old to new archive format
 */

#include <signal.h>
D 2
#include <newar.h>
E 2
I 2
#include <ar.h>
E 2
#define	OARMAG	0177545
struct	oar_hdr {
	char	oar_name[14];
	long	oar_date;
	char	oar_uid;
	char	oar_gid;
	int	oar_mode;
	long	oar_size;
};

struct	ar_hdr nh;
struct	oar_hdr oh;
D 4
char	*tmp;
E 4
I 4
char	tmp[] = "/usr/tmp/arcXXXXXX";
E 4
char	*mktemp();
int	f;
char	buf[512];
int	tf;
main(argc, argv)
char *argv[];
{
	register i;

	if (argc>1 && strcmp(argv[1], "-t")==0) {
D 4
		tmp = mktemp("/usr/tmp/arcXXXXXX");
E 4
		argc--;
		argv++;
D 4
	} else
		tmp = mktemp("/tmp/arcXXXXXX");
E 4
I 4
	} else {
		strcpy(tmp, "/tmp/arcXXXXXX");
	}
	mktemp(tmp);
E 4
	for(i=1; i<4; i++)
		signal(i, SIG_IGN);
	for(i=1; i<argc; i++) {
		if (argc>1)
			printf("%s:\n", argv[i]);
		conv(argv[i]);
	}
	unlink(tmp);
	return(0);
}

conv(fil)
char *fil;
{
	int oldmagic;
	long n;
	unsigned i;

	f = open(fil, 2);
	if(f < 0) {
		printf("arcv: cannot open %s\n", fil);
		return;
	}
	close(creat(tmp, 0600));
	tf = open(tmp, 2);
	if(tf < 0) {
		printf("arcv: cannot open temp\n");
		close(f);
		return;
	}
	oldmagic = 0;
	read(f, (char *)&oldmagic, sizeof(oldmagic));
	if(oldmagic != 0177545) {
		printf("arcv: %s not old archive format\n", fil);
		close(tf);
		close(f);
		return;
	}
	chkwrite(tf, ARMAG, SARMAG);
loop:
	i = read(f, (char *)&oh, sizeof(oh));
	if(i != sizeof(oh))
		goto out;

	sprintf(buf, "%-16.14s%-12ld%-6u%-6u%-8o%-10ld%-2s",
	   oh.oar_name,
	   oh.oar_date,
	   oh.oar_uid,
	   oh.oar_gid,
	   (unsigned short)oh.oar_mode,
	   oh.oar_size,
	   ARFMAG);
	strncpy((char *)&nh, buf, sizeof(nh));
	n = oh.oar_size;
	chkwrite(tf, (char *)&nh, sizeof(nh));
	while(n > 0) {
		i = 512;
		if (n<i)
			i = n;
		read(f, buf, i&01? i+1:i);
		if (i&01) {
			buf[i] = '\n';
			i++;
		}
		chkwrite(tf, buf, i);
		n -= i;
	}
	goto loop;
out:
	lseek(f, 0L, 0);
	lseek(tf, 0L, 0);
	while((i=read(tf, buf, 512)) > 0)
		chkwrite(f, buf, i);
	close(f);
	close(tf);
}

chkwrite(f, b, n)
char *b;
{
	if (write(f, b, n) != n) {
		printf("arcv: write error\n");
		unlink(tmp);
		exit(1);
	}
}
E 1
