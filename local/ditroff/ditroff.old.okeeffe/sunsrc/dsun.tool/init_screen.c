#include "dsun.tool.hs_h"
#include <strings.h>
#include <sys/errno.h>
#include <fcntl.h>

/* system externs */
extern int offset;
extern int errno;
extern int pg_init;
extern int    io_pending;
extern struct toolsw* dsun_window;
extern struct tool *tool;
extern struct pixrect *dprect;
extern struct pixwin * dsun_pw;
extern struct inputmask im;
extern struct rect whole_screen;
extern struct page * curr_dis_pg;
extern int    keyboard; 
extern int top_verbose;
extern int dsun_pid;
extern int offset;			/* Offset value for scrolling */
struct pixfont * pf;			/* Font for displaying the pages
					 * currently available for display.
					 */

struct rect display_rect = { 0, 0, RASTER_LENGTH, NLINES };
int    verbose;
int    top_verbose;
int    null_input();
int    null_func();
int    sigwinched();
int    parentsigwinched();
int    sigchlded();
int    sigioed();
static struct pixwin * root_pw;

/*----------------------------------------------------------------------------*
 | Routine:	init_screen()
 |
 | Results:	Creates the graphics subwindow for dsun to run in based either
 |		on initial environment variable settings or default values.
 *----------------------------------------------------------------------------*/

init_screen(crop)
int crop;			/* Is the document to be cropped or not */
{

	char line[80];
	char name[80];
	char *argsw[2];
	struct gfxsubwindow * tmpgfxsw;
	int  watcher_pid;

	argsw[0] = "-r";

	signal(SIGWINCH, SIG_IGN);

	if (!getenv("WINDOW_PARENT")) {
		error(FATAL, "dsun.tool must run under suntools...run dsun");
	}

	whole_screen.r_width = (crop) ? CROP_LENGTH : RASTER_LENGTH;

	load_from_env(&whole_screen);

					/* Create i/o subwindow */
	dsun_window = (struct toolsw *)gfxsw_createtoolsubwindow(tool, "dsun",
							1024, 800, argsw);


	if (dsun_window == (struct toolsw *) NULL)
		error(FATAL, "can't open subwindow");

/*
 * Use a temporary struct so that lint won't complain...I don't know
 * how to do it properly.
 * This will just have to do.
 */
	tmpgfxsw = (struct gfxsubwindow *)dsun_window->ts_data;

	offset = 0;		/* Set offset for scrolling */

	keyboard = tmpgfxsw->gfx_windowfd;

	dsun_pw = tmpgfxsw->gfx_pixwin;

	pw_writebackground(dsun_pw, 0, 0, 800, 800, PIX_CLR);

	tool->tl_sw->ts_io.tio_selected = null_input;	
	signal(SIGCHLD, sigchlded);
	
	if (dsun_pid = fork()){

		if (dsun_pid < 0)
			error(FATAL,"can't fork dsun process");

		dsun_window->ts_io.tio_handlesigwinch = null_func;
					       /* Function for 
						* handling input is special.
						* It will send a signal to
						* the bit processing process.
						*/
		signal(SIGWINCH, parentsigwinched);

		tool_install(tool);
		tool_select(tool,1);
		tool_destroy(tool);
		exit(0);
	}

	signal(SIGWINCH, sigwinched);	/* Damage repair */
	signal(SIGCONT, sigioed);	/* Special signal that means that
					 * I/O is pending.
					 */

	im.im_flags = IM_ASCII;		/* Set up I/O */
	win_setinputmask(keyboard, &im, &im, WIN_NULLLINK);
	return;

}

/*
 * Loads the initial dimensions of dsun.tool from the environment
 * if the environment variable DSUN_TOOL has been set. If it has
 * not or it has been improperly declared,  then the default values are used.
 */
load_from_env(r)
struct rect * r;		/* rect describing dsun.tool dimensions */
{
	char * p, * ri;
	struct rect rect;
	int x, y, w, h;

	rect.r_left = rect.r_top = rect.r_width = rect.r_width = -2;

	if ((ri = getenv("DSUN_TOOL")) == (char *)NULL)
		return;
	p = ri;
	while(*p){
		p = index(p, ',');
		if (!p)
			break;
		*p = ' ';
		p++;
	}

	sscanf(ri, "%d %d %d %d", &x, &y, &w, &h);

	rect.r_left = x;
	rect.r_top = y;
	rect.r_width = w;
	rect.r_height = h;

	if(rect.r_left == -2 || rect.r_top == -2 || rect.r_width == -2 
			|| rect.r_height == -2)	/* If something hasn't been
						 * set then just don't save
						 * any of the numbers.
						 */
		return;
/*
 * Set up default values if user has entered -1's instead of meaningful
 * values.
 */

	rect.r_left = (x == -1) ? 0 : x;
	rect.r_top = (y == -1) ? 0 : y;
	rect.r_width = (w == -1) ? r->r_width : w;	/* Set before call to
							 * this routine.
							 */
	rect.r_height = (h == -1) ? 800 : h;

	bcopy((char *)&rect, (char *)r, sizeof(struct rect));
					/* Copy the result to the rect that
					 * will be used to initialize
					 * the window.
					 */
}

/*
 * This is the function that will be called by tool->tl_io.tio_handlesigwinch()
 * in order to repair any damage done to the child. Since the child must repair
 * it's own damage, we don't want the parent to touch the window.
 */
null_func()
{}

parentsigwinched()		/* Want the parent to make sure to draw itself */
{
	tool_sigwinch(tool);
	kill(dsun_pid, SIGWINCH);
}

/*
 * I/O has just been received by the window process
 */
sigioed()
{
	io_pending = 1;
}


sigchlded()
{

	tool_sigchld(tool);
}

sigwinched()
{
	pw_exposed(dsun_pw);

	if (pg_init)
		pw_write(dsun_pw, 0, 0, 1024, 800, PIX_SRC, 
			curr_dis_pg->pg_image, 0, offset);
	else
	 	(tool->tl_sw->ts_io.tio_handlesigwinch)
		((struct gfxsubwindow *)dsun_window->ts_data);

}

null_input(data, ibits, obits, ebits, timer)
caddr_t data;
int * ibits;
int * obits;
int * ebits;
struct timeval **timer;
{

	/* Do nothing...Don't want parent stealing input meant for
	 * the child.
	 * But, we do want to notify the child that input has occurred
	 */
	if (*ibits & (1<<keyboard)){
		kill(dsun_pid, SIGCONT);
	}
	*ibits = 0;		/* reset the file descriptor */
	sleep(3);

	
}
