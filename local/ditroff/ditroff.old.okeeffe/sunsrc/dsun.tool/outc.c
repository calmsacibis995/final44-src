#include "dsun.tool.hs_h"

/*
#define DEBUG
*/

extern int offset;
extern int verbose;
extern int fontwanted;
extern struct pixwin * dsun_pw;
extern struct dispatch *dispatch;
extern int sunres;
extern int outres;
extern int h_pos;
extern int v_pos;
extern char *bits;
extern struct pixrect *dprect;
extern struct page * curr_proc_pg;
extern int output;
static struct pixrect * src_prect;
static int mem_init = 0;

outc(code)
int code;		/* character to print */
{
    struct dispatch *dis;	/* ptr to character font record */
    int x;			/* x position in page */
    int y;			/* y position in page */
    int hite;			/* height (stores height for use twice) */
    rast_type raster;		/* raster to send to ROPms */

    if (!mem_init){
	mem_init++;
	src_prect = mem_create(0,0,1);
    }

    if (fontwanted)
	if (getfont()) return;
    dis = dispatch + code;

    if (dis->nbytes) {
	x = ((h_pos * sunres) / outres) - dis->left;
	y = ((v_pos * sunres) / outres) - dis->up;

	raster.width = dis->left + dis->right;
	raster.height = hite = dis->up + dis->down;

	src_prect->pr_data->md_image = (short *)(bits + dis->addr);

	/*
	 * Calculate the number of 16 bit words in the character
	 * to be printed out. Using IF statements is faster than doing it
	 * by function and is worth doing when you consider that
	 * this computation must be done for every character printed.
	 */
		
	if (raster.width < 17)
		src_prect->pr_data->md_linebytes = 2;
	else if (raster.width < 33)
		src_prect->pr_data->md_linebytes = 4;
	else if (raster.width < 49)
		src_prect->pr_data->md_linebytes = 6;
	else		/* Ultra big font...use a function */
		src_prect->pr_data->md_linebytes = ((raster.width % 16) == 0)?
					    raster.width / 16 * 2 :
					    (raster.width / 16 + 1) * 2;

	src_prect->pr_size.x = raster.width;
	src_prect->pr_size.y = raster.height;
	src_prect->pr_depth = 1;


				/* if ANY part of raster is off the "page" */
				/* then forget about this character */
/*
	if (x + raster.width > RASTER_LENGTH || x < 0
		|| y + raster.height > SLOP_SIZE + NLINES || y < 0) return;
*/


				/* if at least part of raster will fit on */
	if (y < NLINES) {	/* the screen do the raster-to-screen move */
			
		if (y + raster.height > NLINES)		/* truncate a raster */
			raster.height = NLINES - y;	/* that passes bottom */

/*
 * Write the image of the current character to the memory pixrect of
 * the page currently being processed.
 */
		pr_rop(curr_proc_pg->pg_image, x, y, raster.width, 
			raster.height, PIX_SRC, src_prect, 0, 0);
/*
 * Write stuff out on the screen at the same time if the page
 * begin processed is the one being displayed.
 */


		if (output){
			pw_write(dsun_pw, x , y - offset, raster.width, 
				raster.height, PIX_SRC, src_prect, 0, 0);
		}
	}

    }
}

static 
int round_div8(num)
int num;
{

	fprintf(stderr,"The num is %d\n",num);


	if (num % 8 == 0){
		fprintf(stderr,"Returning: %d\n", num / 8);
		/*return (num / 8);*/
	}else 
		fprintf(stderr,"Returning +1: %d\n", (num /8) + 1);
	/*return((num / 8) +1);*/
	return(2);
}


