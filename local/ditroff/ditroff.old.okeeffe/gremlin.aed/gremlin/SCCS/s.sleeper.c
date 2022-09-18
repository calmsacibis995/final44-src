h34736
s 00021/00000/00000
d D 1.1 83/04/18 13:46:07 slatteng 1 0
c date and time created 83/04/18 13:46:07 by slatteng
e
u
U
t
T
I 1
#include <signal.h>

int lasttime = 0;
int intcount = 0;
sigquit(x)
{
	int curtime;
	signal(SIGQUIT,sigquit);
	curtime = time(0);
	if(curtime - lasttime < 10) exit();
	lasttime = curtime;
}
	
main()
{
	signal(SIGINT,SIG_IGN);
	signal(SIGQUIT,sigquit);
	chmod(ttyname(1),0666);
	system("echo tty is: ; tty");
	while(1) sleep(200000);
}
E 1
