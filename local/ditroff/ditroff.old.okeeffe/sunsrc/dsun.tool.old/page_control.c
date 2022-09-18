#include "dsun.tool.hs_h"
/*
#define DEBUG
*/

#define msg(x,y) 	fprintf(stderr,"%s %d\n",x, y)
#define MAXPAGES 300
#define MAXBUFFERS 5
#define MAXPAGEBUFFER 2			/* Maximum number of pages on either side
					 * of page being displayed
					 */
#define STOP -25
extern int font;			/* Current font being used. Used in this
					 * module to be able to restore the 
					 * current font state.
					 */
extern int size;			/* Current point size of font. Used in
					 * this module to restore the current
					 * point size state after page 
					 * processing has been interrupted by 
					 * I/O.
					 */
extern int io_pending;			/* There is io to be processed */
extern struct page * curr_proc_pg, * curr_dis_pg;
extern int h_pos, v_pos;
extern curr_dis_pgno;			/* Number of page currently displayed */
extern struct tool * tool;
extern int verbose;
extern int top_verbose;
extern curr_proc_pgno;			/* Number of page currently being processed*/
extern struct pixfont * pf;		/* Font for printing out page numbers */
extern int crop;
int processor_pid;
int new_page;
int pg_init = 0;			/* Should display window repair damage
					 * to the retained rect or should it 
					 * just repaint using the bit map
					 * for the current display page */
struct list * pg;			/* Circular buffer for describing pages
					 * currently in memory.
					 */
int output;				/* Do we print out the page currently
					 * being processed or not.
					 */

struct page * page_image[MAXPAGES];	/* Bit images of the pages. */
long pageaddr[MAXPAGES];		/* ftell() locations for the pages */
int  total_pages;			/* Number of pages in the paper */

/*
 * Control the printing of all pages in the document. This function
 * serves as the controller for dsun.tool
 * Processes pages until either the user submits a request (notified by
 * SIGIO, or there are no more pages to process for the buffer.
 * Maintains a 5 page buffer.
 *
 * General Idea : The main loop of this function of this driver is really
 * the main loop for the entire program. Subsequently, it should be simple
 * and straightforward. It's not.
 *
 * It must take care of the following things:
 *	1) Interrupt driven I.O - When an interrupt occurs, we must find out
 *	   what the user wants and process that request.
 *	
 *	2) Buffer pages both ahead and behind the page currently being
 *	   viewed. This is the motivation for doing interrupt driven I.O.
 *
 *	3) Allow I.O operations concerning both the page currently being
 *	   displayed (such as scrolling) and the pages that have been
 *	   buffered.
 *
 * GENERAL ALGORITHM -
 *	
 *	- Get a pointer to the page struct for the page number whose bit map
 *	  we want to produce.
 *	
 *	- If this bit map is also the one we want to display, then put on the
 *	  screen what we have so far (the flag >>>output<<< will be set).
 *
 *	- Produce the bit map character by character, printing out as we go
 *	  along.
 *
 *	- After we have finished processing the page currently selected for
 *	  display, we'll re-display it, only it will be left-corrected (extra
 *	  white space to the left of the text will be cropped off).
 *
 *	  NOTE: We must check whether the page has been finished before we
 *	  redisplay it since an I.O interrupt could have caused a premature
 *	  return from >>>conv()<<<.
 *
 *	- Return from >>>conv()<<< can be caused by two reasons other than
 *	  abnormal termination.
 *	  1) The bit map currently being produced has been finished -
 *		If this is the case, then we must select the next page
 *		for which to produce a bit map according to our pre-buffering
 *		scheme.
 *	  2) An I.O interrupt has occured - 
 *		If this is the case, then we must >>>handle_input()<<< to
 *		determine which page is to be processed next and which is
 *		to be displayed next.
 */

page_control(fp)
FILE * fp;			/* Pointer into the ditroff file */
{
	int done = 0;
	struct page * find_page();

	new_page = 1;
	output = 0;			/* Can't output anything until after 
					 * the device control information is 
					 * read.
					 */

	curr_proc_pgno = curr_dis_pgno = 1;   /* Start at the first page */


	init_page_buf();		/* Set up image data structure */

	set_page_address(fp);		/* Get the ftell() numbers for all
					 * the pages.
					 */

	fseek(fp,0,0);			/*
					 * Go to the beginning of the file.
					 */

	curr_dis_pg = curr_proc_pg = page_image[1];
					/*
					 * Get the page struct for the first page */

	conv(fp);			/*
					 * Get device information.
					 */



	output = 1;

	while (!done){
		curr_proc_pg = find_page(curr_proc_pgno, curr_dis_pgno); 
							   /* process
							   */

		if (output && new_page){
			curr_dis_pg = curr_proc_pg; /* used for repairing
						     * damage.
						     * ...and scrolling.
						     */
			curr_dis_pgno = curr_proc_pgno;
			display(curr_proc_pg);   /* Print what we have of the
						  * page so far.
						  */				
		}
		if (!curr_proc_pg->done){
			output = (curr_proc_pgno == curr_dis_pgno);
					/* Only output if the page being
					 * displayed is the same one
					 * being processed.
					 */
			fseek(fp, curr_proc_pg->temp_loc, 0);
			size = curr_proc_pg->size;	/* Restore point size */
			setsize(size);
			font = curr_proc_pg->font;	/* Restore font */
			setfont(font);

			v_pos = curr_proc_pg->v_pos;
			h_pos = curr_proc_pg->h_pos;
			conv(fp);
			
			add_pgno(curr_proc_pg);  /* Put the page number on
						  * the top of the page.
						  */

			output = 0;		/* Turn off printing: default */

		} else 
			output = 0;   		/* We displayed an already
						 * processed page.
						 */


		if (io_pending){
			curr_proc_pgno = handle_input(curr_proc_pgno, 
							curr_dis_pgno);
		/*	curr_dis_pgno = curr_proc_pgno;	*/
			io_pending = 0;
		} else {
			output = 0;
			curr_proc_pgno = next(curr_dis_pgno, curr_proc_pgno);
		}
	}
}
			


/*
 * Get the ftell() numbers that mark the beginning of each page
 * in the ditroff file. These points are found by looking for lines
 * that begin with a lowercase p. The text that follows a given p
 * until the end of the file or the next p constitutes the body of the
 * page given by the number following the leading p.
 */

set_page_address(fp)
FILE *fp;
{
	char buf[256];
	int i = 0;
	int k, j;
	int min_h_pos = RASTER_LENGTH;


	while (fgets(buf, sizeof(buf), fp) != NULL){
		if (buf[0] == 'p'){
			i++;
			pageaddr[i] = ftell(fp);
			if (crop)
				page_image[i - 1]->min_h_pos = min_h_pos - 5;
					/* Subtract one to be consistent with
					 * addressing page_image array elewhere
					 */
			else
				page_image[i - 1]->min_h_pos = 0;
			min_h_pos = RASTER_LENGTH;
		}
		if (buf[0] == 'H'){
			k = atoi(&buf[1]);
			if (k < min_h_pos)
				min_h_pos = k;
		}
	}

	/*
	 * Only adjust the last page if we are cropping white space.
	 */
	if (crop)
		page_image[i]->min_h_pos = min_h_pos - 5;

	total_pages = i;
}

/*
 * Get the number of the next page that should be processed.
 * --Since a two page buffer is maintained both in front and
 * in back of the page currently being displayed, page numbers
 * are chosen in the following order...
 *	If the display page is "i" : "i + 1", "i + 2", "i - 2", "i - 1"
 */

next(dis, i)
int dis;
int i;
{

	if (!curr_proc_pg->done) return(i);



/*
 * Check to see if new page has exceeded the upper boundry on pages
 * currently being processed...is it greater than 2 more than the page
 * being displayed or does it refer to a page that doesn't really
 * exist in the document.
 */

	if (((i + 1) > total_pages) || ((i + 1) > (dis + 2)))
		i = dis - 1;
	else if (((i + 1) == (dis + 2)) || ((i + 1)  == (dis + 1)))
		i += 1;
	else if ((i + 1) == dis) 
		i -= 1;
	else if (i == (dis - 2)){
		i = dis;
		io_pending = 1;
	}

	if (i < 1){
		i = dis;
		io_pending = 1;
	}
	return(i);
}


struct page * 
find_page(page_num, dis)
int page_num;				/* Page to be found */
int dis;
{
	struct page * p;		
	int i = 1;
	int found = 0;
	int repl;
	struct pixrect * pr;



/*
 * Look for the page we want in the buffer of pages.
 * If the page has a bit map allocated for it then processing should have
 * already begun and we need not do anything to it...
 */
	if (page_num < 1){
		fprintf(stderr, "Bad page num \n");
		page_num = 1;
	}
	if (page_image[page_num]->pg_image != (struct pixrect *)NULL){
		return(page_image[page_num]);
	} else { 
		repl = pick_replacement_page(dis, page_num); 
/*
 * Only destroy the image if there was one there to begin with. We might
 * have a null entry as when the buffers are first being filled.
 */
		if (repl){

			pr_rop(page_image[repl]->pg_image, 0, 0, 
				RASTER_LENGTH, NLINES, PIX_CLR, 
				page_image[repl]->pg_image, 0, 0);        
						 /* Destroy the bit map of the
						  * old page.
						  */
			pr = page_image[repl]->pg_image;
		} else
			pr = mem_create(RASTER_LENGTH, NLINES, 1);

		page_image[repl]->pg_image = (struct pixrect *)NULL;
		p = page_image[page_num];

/*
 * Initialize page struct
 */
				 
		 p->page_number = page_num;
		 p->temp_loc = pageaddr[page_num];
		 p->font = font;
		 p->size = size;
		 p->h_pos = 0;
		 p->v_pos = 0;
	   	 p->pg_image = pr;
	   	 p->done = 0;
	}

	pg_init = 1;
	return(p);
}

/*
 * Pick the page that is farthest away from the page currently being displayed
 * for removal of it's bit map. If there is an empty buffer then 0 is returned.
 * If not, the the number of the page that is chosen for replacement is the
 * one that is farthest away in absolute distance from the page currently
 * being displayed.
 *
 * Note that any page inspected that is within TWO page frames of the
 * page currently being displayed is NOT considered since this is a page
 * that will have to be processed eventually anyway.
 */
pick_replacement_page(dis, page_num)
int dis;			/* Page currently being displayed */
int page_num;			/* Number of page for which a new slot must 
				 * be found.
				 */
{
	struct list * p;
	int i;
	int t;
	int maximum = 0;
	int distance;
	char buf[80];

	for (i = 1; i <= 5; i++){
		if (pg->num == 0){
			pg->num = page_num;
			return(0);
		}
		distance = abs(pg->num - dis);
		if ((distance > maximum) && (distance > 2)){
			t = pg->num;	/* Current max page num */
			p = pg;		/* Remember this slot */
			maximum = distance;
		}
		pg = pg->next;
	}
	p->num = page_num;	/* Slot gets new page number */
#ifdef DEBUG
fprintf(stderr,"pick_repl: Page number selected is = %d\n", t);
fflush(stderr);
#endif
	return(t);
}

