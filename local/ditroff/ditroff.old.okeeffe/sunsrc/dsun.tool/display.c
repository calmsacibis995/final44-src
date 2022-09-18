#include "dsun.tool.hs_h"
#define hgoto(n)	h_pos = n
#define vgoto(n)	v_pos = n
extern int total_pages;			/* Total number of pages in document */
extern int verbose;
extern int h_pos;
extern int v_pos;
extern int outres;
extern int sunres;
extern int total_pages;			/* Total number of pages in the document*/
extern struct pixwin * dsun_pw;		/* Pixwin to which dsun output goes */

/* 
 * Display the page struct passed as the arguement in the dsun pixwin...
 * For generality this pixwin should be a parameter...but not this time...
 */

display(display_page)
struct page * display_page;
{

	int x_pos = 0;
	pw_exposed(dsun_pw);		/* Get clipping information */

	if (verbose)
		fprintf(stderr, "Displaying page\n");

	

	
/* 
 * New page...wipe out the image of
 * the old one.
 */
	pw_writebackground(dsun_pw, 0, 0, 1200, 800, PIX_CLR);

/*
 * Write out the new page image
 */
/*
	if (display_page->done)
		x_pos = (display_page->min_h_pos * sunres) / outres;
*/

	pw_write(dsun_pw, 0, 0, RASTER_LENGTH, 400, PIX_SRC, display_page->pg_image, 0, 0);
	pw_write(dsun_pw, 0, 400, RASTER_LENGTH, 400, PIX_SRC, display_page->pg_image, 0, 400);

}

add_pgno(page)
struct page * page;
{
	char notice[40];
	int n = page->page_number;

	if (page->done){

		sprintf (notice, "%sage %d:", (n >= 0) && (n < total_pages) ? "P" : "Last p", n);
		hgoto(5);	 /* move to 1/10" from left edge */
		vgoto(outres / 3);	 /*   and 1/3" from top of screen */
		setsize(t_size(10)); /*   change to 10 point in currrent font */
		t_text(notice);	 /*   and print the message */
	}

}
