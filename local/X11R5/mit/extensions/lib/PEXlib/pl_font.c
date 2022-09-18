/* $XConsortium: pl_font.c,v 1.7 92/11/23 16:58:54 mor Exp $ */

/******************************************************************************
Copyright 1987,1991 by Digital Equipment Corporation, Maynard, Massachusetts
Copyright 1992 by the Massachusetts Institute of Technology

                        All Rights Reserved

Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that copyright
notice and this permission notice appear in supporting documentation, and that
the name of Digital or M.I.T. not be used in advertising or publicity
pertaining to distribution of the software without specific, written prior
permission.  Digital and M.I.T. make no representations about the suitability
of this software for any purpose.  It is provided "as is" without express or
implied warranty.

DIGITAL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
DIGITAL BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.
******************************************************************************/

#include "PEXlib.h"
#include "PEXlibint.h"


PEXFont
PEXLoadFont (display, fontname)

INPUT Display	*display;
INPUT char	*fontname;

{
    pexLoadFontReq	*req;
    pexFont		id;


    /*
     * Lock around critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetReq (LoadFont, req);
    req->numBytes = strlen (fontname);
    req->font = id = XAllocID (display);
    req->length += (req->numBytes + 3) >> 2;

    Data (display, (char *) fontname, req->numBytes);


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);

    return (id);
}


void
PEXUnloadFont (display, font)

INPUT Display	*display;
INPUT PEXFont	font;

{
    pexResourceReq *req;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetReq (UnloadFont, req);
    req->id = font;


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}


PEXFontInfo *
PEXQueryFont (display, font)

INPUT Display		*display;
INPUT PEXFont		font;

{
    pexQueryFontReply 	rep;
    pexQueryFontReq	*req;
    pexFontInfo		*buf;
    int 		prop_size;
    PEXFontInfo		*fontInfoReturn;


    /*
     * Lock around critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer and get a reply.
     */

    PEXGetReq (QueryFont, req);
    req->font = font;

    if (_XReply (display, &rep, 0, xFalse) == 0)
    {
	UnlockDisplay (display);
	PEXSyncHandle (display);
	return (NULL);            /* return an error */
    }


    /*
     * Allocate a scratch buffer and copy the reply data to the buffer.
     */

    buf = (pexFontInfo *) _XAllocScratch (display,
	(unsigned long) (rep.length << 2));

    _XRead (display, (char *) buf, (long) (rep.length << 2));


    /*
     * Allocate a buffer for the replies to pass back to the client.
     */

    fontInfoReturn = (PEXFontInfo *)
	PEXAllocBuf ((unsigned) sizeof (PEXFontInfo));

    fontInfoReturn->first_glyph = buf->firstGlyph;
    fontInfoReturn->last_glyph = buf->lastGlyph;
    fontInfoReturn->default_glyph = buf->defaultGlyph;
    fontInfoReturn->all_exist = buf->allExist;
    fontInfoReturn->stroke = buf->strokeFont;
    fontInfoReturn->count = buf->numProps;

    prop_size = buf->numProps * sizeof (PEXFontProp);
    fontInfoReturn->props = (PEXFontProp *) PEXAllocBuf ((unsigned ) prop_size);
    buf++;
    COPY_AREA ((char *) buf, (char *) fontInfoReturn->props, prop_size);


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);

    return (fontInfoReturn);
}


char **
PEXListFonts (display, pattern, maxNames, countReturn)

INPUT Display		*display;
INPUT char		*pattern;
INPUT unsigned int	maxNames;
OUTPUT unsigned long	*countReturn;

{
    pexListFontsReply 	rep;
    pexListFontsReq   	*req;
    long		numChars;
    pexString 		*repStrings;
    char		**names;
    int			i;


    /*
     * Lock around critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer and get a reply.
     */

    PEXGetReq (ListFonts, req);
    req->maxNames = maxNames;
    numChars = req->numChars = strlen (pattern);
    req->length += (numChars + 3) >> 2;

    Data (display, (char *) pattern, numChars);

    if (_XReply (display, &rep, 0, xFalse) == 0)
    {
	UnlockDisplay (display);
	PEXSyncHandle (display);
	*countReturn = 0;
	return (NULL);            /* return an error */
    }

    *countReturn = rep.numStrings;


    /*
     * Allocate a scratch buffer and copy the reply data to the buffer.
     */

    repStrings = (pexString *)
	_XAllocScratch (display, (unsigned long) (rep.length << 2));

    _XRead (display, (char *) repStrings, (long) (rep.length << 2));


    /*
     * Allocate a buffer for the replies to pass back to the client.
     */

    names = (char **) PEXAllocBuf (rep.numStrings * sizeof (char *));

    for (i = 0; i < rep.numStrings; i++)
    {
	names[i] = (char *) PEXAllocBuf ((unsigned) repStrings->length + 1);

	COPY_AREA ((char *) &repStrings[1], names[i],
	    (unsigned) repStrings->length);
	names[i][repStrings->length] = '\0';	/* null terminate string */

	repStrings = (pexString *) ((char *) repStrings +
	    PADDED_BYTES (sizeof (pexString) + repStrings->length));
    }


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);

    return (names);
}


char **
PEXListFontsWithInfo (display, pattern, maxNames, countReturn, fontInfoReturn)

INPUT Display		*display;
INPUT char		*pattern;
INPUT unsigned int	maxNames;
OUTPUT unsigned long	*countReturn;
OUTPUT PEXFontInfo	**fontInfoReturn;

{
    pexListFontsWithInfoReq	*req;
    pexListFontsWithInfoReply	rep;
    long			numChars;
    int				font_info_size, prop_size;
    int				numFontInfoReturn, i;
    char			*buf, **names;
    pexString			*repStrings;
    PEXFontInfo			*pFontInfo;


    /*
     * Lock around critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer and get a reply.
     */

    PEXGetReq (ListFontsWithInfo, req);
    req->maxNames = maxNames;
    numChars = req->numChars = strlen (pattern);
    req->length += (numChars + 3) >> 2;

    Data (display, (char *) pattern, numChars);

    if (_XReply (display, &rep, 0, xFalse) == 0)
    {
	UnlockDisplay (display);
        PEXSyncHandle (display);
	*countReturn = 0;
        return (NULL);                /* return an error */
    }

    *countReturn = rep.numStrings;


    /*
     * Allocate a scratch buffer and copy the reply data to the buffer.
     */

    buf = (char *) _XAllocScratch (display, (unsigned long) (rep.length << 2));

    _XRead (display, (char *) buf, (long) (rep.length << 2));


    /*
     * Allocate a buffer for the font names to pass back to the client.
     */

    names = (char **) PEXAllocBuf (rep.numStrings * sizeof (char *));

    repStrings = (pexString *) buf;
    for (i = 0; i < rep.numStrings; i++)
    {
        names[i] = (char *) PEXAllocBuf ((unsigned) repStrings->length + 1);

        COPY_AREA ((char *) &repStrings[1], names[i],
            (unsigned) repStrings->length);
	names[i][repStrings->length] = '\0';	/* null terminate string */

        repStrings = (pexString *) ((char *) repStrings +
            PADDED_BYTES (sizeof (pexString) + repStrings->length));
    }


    /*
     * Allocate a buffer for the font info to pass back to the client.
     */

    buf = (char *) repStrings;
    numFontInfoReturn = (int) *((CARD32 *) buf); 
    buf += sizeof (CARD32);

    font_info_size = numFontInfoReturn * sizeof (PEXFontInfo);
    *fontInfoReturn = pFontInfo = (PEXFontInfo *) PEXAllocBuf (font_info_size);

    for (i = 0; i < numFontInfoReturn; i++, pFontInfo++)
    {
	pFontInfo->first_glyph = ((pexFontInfo *) buf)->firstGlyph;
	pFontInfo->last_glyph = ((pexFontInfo *) buf)->lastGlyph;
	pFontInfo->default_glyph = ((pexFontInfo *) buf)->defaultGlyph;
	pFontInfo->all_exist = ((pexFontInfo *) buf)->allExist;
	pFontInfo->stroke = ((pexFontInfo *) buf)->strokeFont;
	pFontInfo->count = ((pexFontInfo *) buf)->numProps;

	prop_size = ((pexFontInfo *) buf)->numProps * sizeof (PEXFontProp);
	pFontInfo->props = (PEXFontProp *) PEXAllocBuf ((unsigned ) prop_size);
	buf += sizeof (pexFontInfo);
    	COPY_AREA ((char *) buf, (char *) pFontInfo->props, prop_size);
	buf += prop_size;
    }


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);

    return (names);
}


PEXTextExtent *
PEXQueryTextExtents (display, id, fontGroup, path, expansion, spacing, height, 
    halign, valign, count, text)

INPUT Display			*display;
INPUT XID			id;
INPUT unsigned int		fontGroup;
INPUT int			path;
INPUT double			expansion;
INPUT double			spacing;
INPUT double			height;
INPUT int			halign;
INPUT int			valign;
INPUT unsigned long		count;
INPUT PEXStringData		*text;
{
    pexQueryTextExtentsReq	*req;
    pexQueryTextExtentsReply 	rep;
    char			*ch;
    pexMonoEncoding 		pMonoEncoding;
    int				convertFP, numEncodings, i;
    PEXTextExtent		*textExtent, *ptextExtents;


    /*
     * Lock around critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer and get a reply.
     */

    PEXGetFPReq (QueryTextExtents, req, convertFP);
    req->textPath = path;
    req->id = id;
    req->fontGroupIndex = (pexTableIndex) fontGroup;
    req->charExpansion = expansion;
    req->charSpacing = spacing;
    req->charHeight = height;
    req->textAlignment.vertical = valign;
    req->textAlignment.horizontal = halign;
    req->numStrings = count;

    req->length += count * (LENOF (CARD32) + LENOF (pexMonoEncoding));
    for (i = 0; i < count; i++)
	req->length += (((int) text[i].length + 3) >> 2);

    pMonoEncoding.characterSet = (INT16) 1;
    pMonoEncoding.characterSetWidth = (CARD8) PEXCSByte;
    pMonoEncoding.encodingState = 0;  

    numEncodings = 1;

    for (i = 0; i < count; i++)
    {
	Data (display, (char *) &numEncodings, sizeof (CARD32));
	pMonoEncoding.numChars = (CARD16) (text[i].length);
	Data (display, (char *) &pMonoEncoding, sizeof (pexMonoEncoding));
	Data (display, (char *) text[i].ch, text[i].length);
    }

    if (_XReply (display, &rep, 0, xFalse) == 0)
    {
        UnlockDisplay (display);
        PEXSyncHandle (display);
        return (NULL);            /* return an error */
    }


    /*
     * Allocate a scratch buffer and copy the reply data to the buffer.
     */

    ch = (char *) _XAllocScratch (display, (unsigned long) (rep.length << 2));

    _XRead (display, ch, (long) (rep.length << 2));


    /*
     * Allocate a buffer for the replies to pass back to the client.
     */

    textExtent = ptextExtents =
	(PEXTextExtent *) PEXAllocBuf (count * sizeof (PEXTextExtent));

    for (i = 0; i < count; i++, textExtent++)
    {
	textExtent->lower_left = *(PEXCoord2D *) ch;
	ch += sizeof (PEXCoord2D);
	textExtent->upper_right = *(PEXCoord2D *) ch;
	ch += sizeof (PEXCoord2D);
	textExtent->concat_point = *(PEXCoord2D *) ch;
	ch += sizeof (PEXCoord2D);
    }


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);

    return (ptextExtents);
}


PEXTextExtent *
PEXQueryEncodedTextExtents (display, id, fontGroup, path, expansion,
    spacing, height, halign, valign, count, encoded_text)

INPUT Display			*display;
INPUT XID			id;
INPUT unsigned int		fontGroup;
INPUT int			path;
INPUT double			expansion;
INPUT double			spacing;
INPUT double			height;
INPUT int			halign;
INPUT int			valign;
INPUT unsigned long		count;
INPUT PEXListOfEncodedText    	*encoded_text;

{
    pexQueryTextExtentsReq	*req;
    pexQueryTextExtentsReply 	rep;
    PEXEncodedTextData      	*string;
    char			*ch;
    int				i, j;
    int				convertFP;
    PEXTextExtent		*textExtent, *ptextExtents;


    /*
     * Lock around critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetFPReq (QueryTextExtents, req, convertFP);
    req->textPath = path;
    req->id = id;
    req->fontGroupIndex = (pexTableIndex) fontGroup;
    req->charExpansion = expansion;
    req->charSpacing = spacing;
    req->charHeight = height;
    req->textAlignment.vertical = valign;
    req->textAlignment.horizontal = halign;
    req->numStrings = count;


    /*
     * Update the request length header.
     */

    req->length += (count * LENOF (CARD32));
    for (i = 0; i < count; i++)
    {
	string = encoded_text[i].encoded_text;
	for (j = 0; j < (int) encoded_text[i].count; j++, string++)
	{
	    req->length += LENOF (pexMonoEncoding);
	    if (string->character_set_width == PEXCSLong) 
		req->length += string->length;
	    else if (string->character_set_width == PEXCSShort) 
		req->length += ((int) string->length + 1) >> 1;
	    else /* string->character_set_width == PEXCSByte) */ 
		req->length += ((int) string->length + 3) >> 2;
	} 
    }


    /*
     * Put the encoded text in the request.
     */

    for (i = 0; i < count; i++)
    {
	unsigned long numEncodings = encoded_text[i].count;
	string = encoded_text[i].encoded_text;

	Data (display, (char *) &numEncodings, sizeof (CARD32));

	for (j = 0; j < (int) numEncodings; j++, string++)
	{
	    Data (display, (char *) string, sizeof (pexMonoEncoding));

	    if (string->character_set_width == PEXCSLong) 
	    {
		Data (display, string->ch, string->length * sizeof (long));
	    }
	    else if (string->character_set_width == PEXCSShort) 
	    {
		Data (display, string->ch, string->length * sizeof (short));
	    }
	    else /* string->character_set_width == PEXCSByte) */ 
	    {
		Data (display, string->ch, string->length);
	    }
	}
    }


    /*
     * Get a reply.
     */

    if (_XReply (display, &rep, 0, xFalse) == 0)
    {
        UnlockDisplay (display);
        PEXSyncHandle (display);
        return (NULL);            /* return an error */
    }


    /*
     * Allocate a scratch buffer and copy the reply data to the buffer.
     */

    ch = (char *) _XAllocScratch (display, (unsigned long) (rep.length << 2));

    _XRead (display, ch, (long) (rep.length << 2));


    /*
     * Allocate a buffer for the replies to pass back to the client.
     */

    textExtent = ptextExtents =
	(PEXTextExtent *) PEXAllocBuf (count * sizeof (PEXTextExtent));

    for (i = 0; i < count; i++, textExtent++)
    {
	textExtent->lower_left = *(PEXCoord2D *) ch;
	ch += sizeof (PEXCoord2D);
	textExtent->upper_right = *(PEXCoord2D *) ch;
	ch += sizeof (PEXCoord2D);
	textExtent->concat_point = *(PEXCoord2D *) ch;
	ch += sizeof (PEXCoord2D);
    }


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);

    return (ptextExtents);
}
