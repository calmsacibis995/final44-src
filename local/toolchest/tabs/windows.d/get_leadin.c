/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
#include <stdio.h>
#include "vt.h"
#include "windows.h"

get_leadin()
{
	register int	i;
	register int	j;
	
	KLEADIN = 0;
	for( i = 0; i < _NKEYS; i++ )
	{
		if (PAD_KEYS[ i ])
		{
			if(KLEADIN == 0 )
			{
				KLEADIN = PAD_KEYS[ i ];
				/* same leadin character? */
				for( j = 0; j < _NKEYS; j++ )
					if (PAD_KEYS[j] && *KLEADIN != *PAD_KEYS[j])
						return;
			}
			PAD_KEYS[i]++;
		}
	}
}
