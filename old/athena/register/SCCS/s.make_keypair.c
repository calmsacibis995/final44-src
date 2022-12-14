h03482
s 00001/00001/00065
d D 1.2 88/12/12 22:58:56 kfall 2 1
c fix instructions a bit
e
s 00066/00000/00000
d D 1.1 88/12/12 20:54:51 kfall 1 0
c date and time created 88/12/12 20:54:51 by kfall
e
u
U
t
T
I 1
#include <sys/types.h>
#include <kerberos/krb.h>
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/file.h>
#include "register_proto.h"

#define	KFILE	"update.key%s"

main(argc, argv)
char	**argv;
{
	char		namebuf[255];
	int		fd;
	struct hostent	*hp;
	char		*addr;
	int		i;
	struct sockaddr_in	sin;

	if(argc != 2) {
		usage(argv[0]);
		exit(1);
	}

	hp = gethostbyname(argv[1]);
	for(i = 0; addr = hp->h_addr_list[i]; i++) {
		addr = hp->h_addr_list[i];
		bcopy(addr, &sin.sin_addr, hp->h_length);

		printf("Making key for host %s (%s)\n",
			argv[1], inet_ntoa(sin.sin_addr));
		make_key(sin.sin_addr);
	}
	printf("==========\n");
	printf("One copy of the each key should be put in /kerberos on the\n");
	printf("Kerberos machine (mode 600, owner root).\n");
	printf("Another copy of each key should be put on the named\n");
D 2
	printf("client as /.updated.keyXXX.XXX.XXX.XXX (same modes as above).\n");
E 2
I 2
	printf("client as /.update.keyXXX.XXX.XXX.XXX (same modes as above).\n");
E 2
	fflush(stdout);
}

make_key(addr)
	struct in_addr	addr;
{
	struct keyfile_data	kfile;
	char		namebuf[255];
	int		fd;

	sprintf(namebuf, KFILE, inet_ntoa(addr));
	fd = open(namebuf, O_WRONLY|O_CREAT, 0600);
	if(fd < 0) {
		perror("open");
		exit(1);
	}
	random_key(kfile.kf_key);
	if(write(fd, &kfile, sizeof(kfile)) != sizeof(kfile)) {
		fprintf(stderr, "error writing file %s\n", namebuf);
	}
	close(fd);
}
usage(name)
	char	*name;
{
	fprintf(stderr, "usage: %s host\n", name);
}
E 1
