#include "dsun.tool.hs_h"
#include <strings.h>
#include <sys/errno.h>
#include <fcntl.h>

#define FONT "/usr/suntool/fixedwidthfonts/sail.r.6"

/* Icon for dsun.tool */


static short	dsun_icon[256] = {
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x8000, 0x0000,
		0x0000, 0x0401, 0x0010, 0x0000, 0x0000, 0x0401, 0x0010, 0x0000,
		0x0000, 0x0401, 0x0030, 0x0000, 0x0000, 0x0401, 0x0020, 0x0000,
		0x0000, 0x0201, 0x0020, 0x0000, 0x0100, 0x0201, 0x0020, 0x0000,
		0x0080, 0x0211, 0x0020, 0x0000, 0x00C0, 0x0211, 0x0020, 0x00C0,
		0x0060, 0x0111, 0x0840, 0x0080, 0x0030, 0x2111, 0x0840, 0x8300,
		0x0010, 0x3191, 0x9041, 0x0200, 0x0018, 0x0888, 0x9043, 0x0C00,
		0x000C, 0x0848, 0x9082, 0x0800, 0x0002, 0x0C48, 0x1084, 0x1000,
		0x00C1, 0x0400, 0x0108, 0x3000, 0x6020, 0x8000, 0x0108, 0x2000,
		0x3818, 0xC000, 0x0018, 0x4000, 0x0C0C, 0x203F, 0xF010, 0x8000,
		0x0306, 0x0AFF, 0xFF01, 0x0100, 0x0180, 0x1FFF, 0xFFC0, 0x0602,
		0x0060, 0x7FFF, 0xFFF0, 0x1806, 0x0019, 0xFC3F, 0xF0FC, 0x0018,
		0x0003, 0xFC3F, 0xF0FF, 0x0030, 0x0407, 0xFC3F, 0xF0FF, 0x01C0,
		0x03CF, 0xFFFF, 0xFFFF, 0x8700, 0x700F, 0xFFFF, 0xFFFF, 0xC400,
		0x1F9F, 0xFFFF, 0xFFFF, 0xE000, 0x001F, 0xFFFF, 0xFFFF, 0xF000,
		0x7FFF, 0xFFFF, 0xFFFF, 0xFFFE, 0x7FFF, 0xFFFF, 0xFFFF, 0xFFFE,
		0x7000, 0x0000, 0x0000, 0x000E, 0x7000, 0x0000, 0x0000, 0x000E,
		0x7000, 0x0000, 0x0000, 0x000E, 0x703F, 0xFE00, 0x0020, 0x000E,
		0x7000, 0x8000, 0x0020, 0x000E, 0x7000, 0x8000, 0x0020, 0x000E,
		0x7000, 0x8000, 0x0020, 0x000E, 0x7000, 0x8078, 0x7820, 0x000E,
		0x7000, 0x8084, 0x8420, 0x000E, 0x7000, 0x8084, 0x8420, 0x000E,
		0x7000, 0x8084, 0x8420, 0x000E, 0x7000, 0x8084, 0x8420, 0x000E,
		0x7000, 0x8078, 0x7820, 0x000E, 0x7000, 0x0000, 0x0000, 0x000E,
		0x7000, 0x0000, 0x0000, 0x000E, 0x7000, 0x0000, 0x0000, 0x000E,
		0x7000, 0x1F00, 0x0000, 0x000E, 0x7000, 0x1080, 0x0000, 0x000E,
		0x7000, 0x1080, 0x0000, 0x000E, 0x7000, 0x1080, 0x0000, 0x000E,
		0x7000, 0x1F00, 0x0000, 0x000E, 0x7000, 0x1087, 0x8840, 0x000E,
		0x7000, 0x1048, 0x4480, 0x000E, 0x7000, 0x1048, 0x4300, 0x000E,
		0x7000, 0x1048, 0x4300, 0x000E, 0x7000, 0x1088, 0x4480, 0x000E,
		0x7000, 0x1F07, 0x8840, 0x000E, 0x7000, 0x0000, 0x0000, 0x000E,
		0x7000, 0x0000, 0x0000, 0x000E, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		};
mpr_static(icon_mpr, 64, 64, 1, dsun_icon);

static  struct icon icon = {64, 64, (struct pixrect *)NULL, 0, 0, 64, 64,
	    &icon_mpr, 0, 0, 0, 0, (char *)NULL, (struct pixfont *)NULL,
			ICON_BKGRDGRY};

/* system externs */
extern int offset;
extern int errno;
extern int pg_init;
extern int    io_pending;
extern struct gfxsubwindow * dsun_window;
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
 | Results:	
 |
 | Side Efct:	sets the global variable "tool" to be a nonzero ONLY if dsun
 |		is being run in the window system.
 |
 | Bugs:	
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

						/* Create tool window */
	tool = tool_create("Dsun.Tool",TOOL_NAMESTRIPE | TOOL_BOUNDARYMGR,
				&whole_screen, &icon);


	if (tool == (struct tool *) NULL)
		error(FATAL, "can't create subwindow");

					/* Create i/o subwindow */
	dsun_window = gfxsw_createtoolsubwindow(tool, "dsun",
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
