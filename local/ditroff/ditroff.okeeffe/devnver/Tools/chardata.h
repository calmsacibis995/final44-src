

struct chardata {
	short charno;		/* character number	*/
	int XO, YO;		/* origin of char rel. to troff positions */
	int width, height;	/* scaled size in bits  */
	char *cbitmap;		/* bitmap of character  */
	short nbytes;		/* length of bitmap     */
	struct chardata *nextchar;
};

