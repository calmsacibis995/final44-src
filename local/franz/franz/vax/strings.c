/*
 * functions herein are not subject to Unix licensing
 */

strcmpn(s1,s2,n)
register char *s1 ,*s2;
{
    register int i;
    
    for (i = n ; i > 0 ; i--)
    {
	if(*s1 == *s2)
	{
	    if (*s1) continue;	/* around the loop */
	    else break;		/* both strings end, get out */
	}
	else if (*s1 < *s2)
	  then return(-1);	  /* s1 < s2 */
	else return(1);
	s1++; s2++;
    }
    return(0);
}
