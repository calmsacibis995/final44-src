#include <signal.h>
int opcodes[0400];
int doingtrace,diddump;
Thandler(a,b,c,pc,psw)
char *pc;
{
	register int opc;
	psw |= 0x10;	/* set the trace bit in psw */
	opc = (*pc & 0377);
	opcodes[opc]++;
}

exit()
{
	_cleanup();
	if(doingtrace)Tracedump();
  lab:
	asm("chmk $1");
}

Tracedump()
{
	int fd;
	signal(5,SIG_IGN);
	if(diddump) return;
	diddump = 1;
	if((fd= creat("t.dump",0644)) < 0)
	{
		perror("t.dump");
	}
	else 
	{  
	    write(fd,opcodes,0400*sizeof(int));
	    close(fd);
	}
}


