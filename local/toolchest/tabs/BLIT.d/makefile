#
# For load_netty - the location of netty.m
#
DETTY=/usr/dmd/lib/netty.m
JETTY=/usr/jerq/lib/netty.m

CFLAGS=-O -DDETTY=\"${DETTY}\" -DJETTY=\"${JETTY}\"

all:	netty.m load_netty Blit_Time send_netty n/netty

blit:	68knetty.m 68kload_netty Blit_Time send_netty n/netty


netty.m:	netty.c
	dmdcc ${CFLAGS} -o netty.m netty.c


Blit_Time:	Blit_Time.c
	cc ${CFLAGS} -o Blit_Time Blit_Time.c


send_netty:	send_netty.c
	cc ${CFLAGS} -o send_netty send_netty.c


load_netty:	load_netty.c
	cc ${CFLAGS} -DDMD -o load_netty load_netty.c


n/netty:	netty.ti
	TERMINFO=`pwd` tic netty.ti

#
#	the 68k optimizer is not working on the 3b's
#
68knetty.m:	netty.c
	-set +e; \
	if u3b; \
	then	mcc -Dmc68000 -o 68knetty.m netty.c ; \
	else	mcc ${CFLAGS} -Dmc68000 -o 68knetty.m netty.c ; \
	fi


68kload_netty:	load_netty.c
	cc ${CFLAGS} -Dmc68000 -o 68kload_netty load_netty.c


clean:
	-rm -rf *.m load_netty send_netty Blit_Time *.o 68k* n


print:
	lprint netty.c netty.h load_netty.c send_netty.c Blit_Time.c makefile
