/*
_t_e_s_t _u_l _m_o_d_e
*/
#include <sgtty.h>
#include <signal.h>

#define LOGON	"\033&p11C"
#define	LOGOFF	"\033&p13C"
#define ULON	"\033&dA"
#define ULOFF	"\033&d@"

#define ENQ	'\005'
#define ACK	'\006'

#define MAXENQ	2
#define MAXC	30

struct sgttyb ttyb, sttyb;

main(argc, argv)
char *argv[];
{
	int i, j;
	char c;
	char buf[512];
	int enqcnt;
	int onintr();
	int pos_, k, ulmode;

	if (argc > 1) {
		if ((i = open(argv[1], 0)) < 0) {
			perror(argv[1]);
			EXIT(1);
		}
		close(0);
		dup(i);
		close(i);
	}
	gtty(1, &ttyb);
	sttyb = ttyb;
	signal(SIGINT, onintr);
	ttyb.sg_flags |= CBREAK;
	ttyb.sg_flags &= ~ECHO;
	stty(1, &ttyb);

	pos_ = enqcnt = ulmode = 0;
	printf("%s", LOGON);
	while ((i = read(0, buf, sizeof(buf))) > 0) {
		for (j = 0; j < i; j += MAXC) {
			if (enqcnt > MAXENQ) {

				if (read(1, &c, 1) != 1) {
					printf("Got read error\n");
					EXIT(1);
				}
				enqcnt--;
				if (c != ACK) {
					printf("Not ACK\n");
					EXIT(1);
				}
			}
			for (k = j; k < i && k < j+MAXC; k++) {
				if (buf[k] == '_' && pos_ == 0) {
					pos_ = 1;
					continue;
				}
				if (pos_ == 1)
					if (buf[k] == '\b') {
						pos_ = 2;
						if (ulmode)
							continue;
						printf("%s", ULON);
						ulmode++;
						continue;
					} else {
						if (ulmode)
							printf("%s", ULOFF);
						putchar('_');
						ulmode = 0;
						pos_ = 0;
					}
				if (pos_ == 2) {
					putchar(buf[k]);
					pos_ = 0;
					continue;
				}
				pos_ = 0;
				if (ulmode)
					printf("%s", ULOFF);
				ulmode = 0;
				putchar(buf[k]);
			}
			putchar(ENQ);
			enqcnt++;
		}
	}
/*
	while (enqcnt > 0) {
		if (read(1, &c, 1) != 1) {
			printf("Got read error\n");
			EXIT(1);
		}
		enqcnt--;
		if (c != ACK) {
			printf("Not ACK\n");
			EXIT(1);
		}
	}
*/
	sleep(2);
	stty(1, &sttyb);
	printf("%s", ULOFF);
	EXIT(0);
}

onintr()
{
	stty(1, &sttyb);
	printf("%s", ULOFF);
	EXIT(0);
}

EXIT(i)
{
	stty(1, &sttyb);
	printf("%s%s", ULOFF, LOGOFF);
	exit(i);
}
