h36424
s 00019/00000/00000
d D 1.1 91/05/07 13:13:26 sklower 1 0
c date and time created 91/05/07 13:13:26 by sklower
e
u
U
t
T
I 1
#define LITTLE_ENDIAN 1
typedef unsigned char u_char;
#define BYTE_ORDER LITTLE_ENDIAN
#include "pk.h"

union foo {
	struct x25_packet pk;
	char	data[10];
} testme;

main() {
	register struct x25_packet *xp = &(testme.pk);

	xp -> fmt_identifier = 1;
	xp -> packet_type = 0xfb;

#define t testme.data 
	printf("%x %x %x %x \n", t[0], t[1], t[2], t[3]);
}
E 1
