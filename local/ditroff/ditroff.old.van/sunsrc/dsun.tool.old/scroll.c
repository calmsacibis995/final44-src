#include "dsun.tool.hs_h"
/* Calculates where on the page we really are from where on the screen the
 * input coordinate thinks we are. If there is not one to one correspondence
 * between screen resoulution and character resolution, then the
 * numbers can not be merely substituted.
 */
#define PAGE_VAL(a) ((a * sunres)/outres)
/*
#define DEBUG
*/

/* Definitions for data shared with dsun.tool */

extern struct pixwin * dsun_pw;
extern struct page   * curr_proc_pg;
extern struct page   * curr_dis_pg;
extern int keyboard;
extern int sunres;
extern int outres;
extern int offset;
extern int new_page;
extern int v_pos;
extern int h_pos;
/*
 * Data that only scrolling routines need to know about.
 */
static int current_v_pos;	/* The vertical number of the pixel at the top 
				 * the visible part of the window.
				 */
static int current_page = -1;	/* The page currently being displayed: not
				 * really necessary.
				 */


scrollup(dis_num, proc_num)
int dis_num;
int proc_num;
/*
 * Scroll the page up the screen so that the bottom half becomes visible.
 */
{
	struct rect win_rect;
	int up_amt;
	int height;

	new_page = 0;
/*
 * Might be scrolling a page for the first time.
 */
	if (dis_num != current_page){
		current_page = dis_num;
		current_v_pos = 0;
	}

	height = win_getheight(keyboard);
				/* Height of the current window height */
				/* check to make sure that this varies */

	up_amt = height / 3;	/* Amount to scroll up */

/* Make sure that we don't go too far */

	if (current_v_pos == (NLINES - height)){/* Nothing left to display */
		reset_v_pos();		/* Reset processing positions */
		return (1);		/* Tell handle_input() to change the
					 * the page.
					 */
	}


/* Otherwise, there's still stuff to display that hasn't been seen */

	current_v_pos += up_amt;	/* Scroll up */

	if (current_v_pos + height > NLINES){
		current_v_pos -= ((current_v_pos + height) - NLINES);
	}

#ifdef DEBUG
fprintf(stderr,"Going to print some stuff out\n");
fprintf(stderr,"current_v_pos = %d\nheight = %d\nup_amt = %d\n",current_v_pos,height,up_amt);
#endif

	offset = current_v_pos;		/* Set offset for continous drawing */

	pw_exposed(dsun_pw);

	pw_writebackground(dsun_pw, 0, 0, RASTER_LENGTH, NLINES, PIX_CLR);

	pw_write(dsun_pw, 0, 0, RASTER_LENGTH, height, PIX_SRC, 
		curr_dis_pg->pg_image, 0, current_v_pos);

	return(0);	/* Continue processing same page */
}


scrolldown(dis_num, proc_num)
int dis_num;
int proc_num;
{

	int down_amt;
	int height;

	new_page = 0;

	height = win_getheight(keyboard);

	down_amt = height / 3;
	
	if (current_v_pos == 0)
		return(1);		/* Tell handle_input() to change the
					 * page.
					 */

	if ((current_v_pos - down_amt) < 0)
		current_v_pos = 0;
	else
		current_v_pos -= down_amt;

	offset = current_v_pos;

	pw_exposed(dsun_pw);

	pw_writebackground(dsun_pw, 0, 0, RASTER_LENGTH, height, PIX_CLR);
	pw_write(dsun_pw, 0, 0, RASTER_LENGTH, height, PIX_SRC, curr_dis_pg->pg_image,
		0, current_v_pos);
	return(0);			/* Tell handle_input() not to change
					 * the current display and process
					 * pages.
					 */

}

/*
 * Used by external routines to reset the vertical position of the
 * the display within this module. Used to maintain what little
 * transparency there still is here.
 */
reset_v_pos()
{
	current_v_pos = 0;
	offset = 0;
}
