/*
 * $Id: ospf_chksum.c,v 1.12 1993/05/04 16:06:54 jch Exp $
 */

/* %(Copyright.header) */


#define	INCLUDE_TIME
#include "include.h"
#include "inet.h"
#include "ospf.h"

/*
 * 		Fletcher checksum
 *		- Based on RFC 1008
 */
#define MODX 4102		/* larges signed value without overflow */

void
fletch(data, len)
byte *data;		/* the Packet to be checksummed */
size_t len;			/* length */
{
    int low_byte = 0, high_byte = 0;
    u_int8 *d = data;		/* current data ptr */
    u_int8 *p;
    u_int8 *walk;		/* window of loop between d and walk */
    u_int8 *last_byte = data + len;	/* The last byte of data */
    int low_res, high_res;

    /* Zero out cksum field - bytes 16 and 17 */
    data[16] = (data[17] = 0x00);

    while (d < last_byte) {	/* walk length of data */
	walk = d + MODX;
	if (walk > last_byte)	/* back up to last byte */
	    walk = last_byte;
	for (p = d; p < walk; p++)	/* walk between d & d + MODX */
	    high_byte += (low_byte += (*p));

	/* adjust sums to mod 255 */
	low_byte %= 255;
	high_byte %= 255;
	d = walk;
    }

    /* compute cksum (Voodoo) and insert in data */
    low_res = (((len - 17) * low_byte - high_byte) % 255);
    if (low_res <= 0)
	low_res += 255;
    data[16] = low_res;

    high_res = (510 - low_byte - low_res);
    if (high_res > 255)
	high_res -= 255;
    data[17] = high_res;
}


/*
 * %(Copyright)
 * %(Copyright.OSPF)
 */
