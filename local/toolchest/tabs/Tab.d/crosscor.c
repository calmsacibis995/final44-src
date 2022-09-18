/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */

/*
 *
 *	cross correlation routine for determining best matches
 *
 *	crosscor (response, item, type)
 *
 *	response - the user's response
 *	item - the word the response will be scored against - list item
 *	type - FALSE for menu match, TRUE for spelling corrector
 *
 *	This procedure produces correlation scores between two words
 *	(user's response and list item).  It is important that the
 *	user's response is the first argument and the list item is
 *	the second.
 */

#define POINTS	5000
crosscor (response, item, type)
char    *response;	  /* user's response */
char    *item;	  /* the word the response will be scored  against */
char    type;	  /* type = 0 for menu match, 1 for spelling corrector */
{
	register char	*presp;
	register char	*pitem;
	char	*pprev_match;
	int     lens;
	int     lent;
	register int	match_pos;
	register int     score = 0;
	char    item_buf[256];
	register char	*pitem_buf;

	if ((lens = strlen (response)) == 0)
		return (-1);
	if ((lent = strlen (item)) == 0)
		return (-1);

	strcpy (item_buf, item);

	/* if first item matches give it an additional score because
	 * there is no character to the left to test for
	 */
	if (*item_buf == *response)
		score += (2 * POINTS);

	presp = response;
	pprev_match = item + lent;
	while (*presp)
	{
		pitem = item;
		pitem_buf = item_buf;
		while (*pitem)
		{
			if (*presp == *pitem_buf)
			{
				/* make character 0 - can't be matched again */
				*pitem_buf = '\0';

				/* get position of match in item string */
				match_pos = (pitem - item)*100;

				/* increase score */
				score += (POINTS - (match_pos));
				
				/* increase score if previous character also
				 * matches
				 */
				if (pitem != item && presp != response)
					if (*(presp - 1) == *(pitem - 1))
						score += (POINTS - match_pos);

				/* increase score if next character also 
				 * matches
				 */
				if ((*(presp + 1) == *(pitem + 1)) &&
						*(presp + 1))
					score += (POINTS - match_pos);

				/* increase score if this match and prev were 
				 * in left to right order in the item string
				 */	
				if (pitem >= pprev_match)
					score += (POINTS - match_pos);
					
				pprev_match = pitem;
				break;
			}
			pitem++;
			pitem_buf++;
		}
		presp++;
		
		/* reduce score if no match for current response character */
		if (*pitem == '\0')
			score -= (2 * POINTS);
	}
	if (type == 1)
		score += (lens - lent) * POINTS;
	else
		score += lens - lent;
	if (score)
		return (score);
	else
		return (-1);
}
