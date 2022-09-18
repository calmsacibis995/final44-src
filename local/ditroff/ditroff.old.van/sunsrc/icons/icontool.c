#ifndef lint
static char  sccsid[] = "@(#)icontool.c 1.8 84/03/06 Sun Micro";
#endif

/*
 *	1984 by Sun Microsystems Inc.
 *
 *	icontool:	bitmap editor for icons & cursors
 *
 */

#include <suntool/tool_hs.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include "patches.h"
#include <suntool/msgsw.h>
#include <suntool/optionsw.h>

extern char	*sys_errlist[];
extern int	 errno;

#define ICONIC		 1
#define ICON_SIZE	 8
#define CURSOR		 0
#define CURSOR_SIZE	(ICON_SIZE * 4)

#define	MSG_HEIGHT	 24
#define	PROOF_SIDE	 96
#define	PROOF_MARGIN	 16
#define	OPTIONS_HEIGHT	PROOF_SIDE
#define	CANVAS_DISPLAY	(CURSOR_SIZE * 16)
#define	CANVAS_MARGIN	 16
#define	CANVAS_SIDE	(CANVAS_DISPLAY + 2 * CANVAS_MARGIN)
#define BIG		2048

static u_int	icon_array[128];
mpr_static(icon_pr, 64, 64, 1, icon_array);

static u_int	new_cursor_array[16];
mpr_static(new_cursor_pr, 16, 16, 1, new_cursor_array);
static struct cursor	new_cursor  =  {
				0, 0,
				PIX_SRC ^ PIX_DST,
				&new_cursor_pr
};

static u_int	main_cursor_array[8]  =  {
			0xC000E000, 0xF000F800,
			0xFC00F000, 0x90001800,
			0x18000C00, 0x0C000600,
			0x06000300, 0x03000100
		};
mpr_static(main_cursor_pr, 16, 16, 1, main_cursor_array);
static struct cursor	main_cursor  =  {
				0, 0,
				PIX_SRC | PIX_DST,
				&main_cursor_pr
};


/*				general tool area			*/

#include "icontool.icon"
mpr_static(my_icon_pr, 64, 64, 1, icon_data);
static struct icon	 my_icon  =  {
				TOOL_ICONWIDTH, TOOL_ICONHEIGHT, NULL,
				{0, 0, TOOL_ICONWIDTH, TOOL_ICONHEIGHT},
				&my_icon_pr, {0, 0, 0, 0}, NULL, NULL, 0
			};

static char		 tool_name[]  =  "Icon Tool 1.2 [for creating gremlin icons]";
static struct rect	 tool_rect;
static struct tool	*tool;

static			 sigwinched();


/*				error message area			*/

static struct toolsw	*msg_sw;
struct msgsubwindow	*msw;


/*				painting area				*/

static struct toolsw	*canvas_sw;
static struct pixwin	*canvas_pixwin;
static struct pixrect	*canvas_pr;
static struct pixrect	*fill_pr;
static int	       (*canvas_reader)();
static			 canvas_sighandler();
static			 canvas_selected();
static			 canvas_basereader();
static			 canvas_tracker();
static			 set_canvas_tracker();
static			 reset_canvas_reader();
static			 canvas_feedback();
static			 wait_legal_mouse();


/*				result-display area			*/

static struct toolsw	*proof_sw;
static struct pixwin	*proof_pixwin;
static struct pixrect	*proof_pr;
static	proof_sighandler();


/*				commands and options area		*/

static struct toolsw	*options_sw;
caddr_t			 osw;

/*  labels for items in the order they occur; enum values appear below  */

caddr_t		   mode_item;
struct typed_pair  mode_label  = {IM_TEXT, "Draw a" };
void		   mode_proc();

caddr_t		   label_item;
struct typed_pair  name_label  =
			{IM_TEXT, "Left paints, Middle erases  " };

caddr_t		   quit_item;
struct typed_pair  quit_label  = {IM_TEXT, "Quit" };
void		   quit_proc();

caddr_t		   load_item;
struct typed_pair  load_label  = {IM_TEXT, "Load" };
void		   load_proc();

caddr_t		   store_item;
struct typed_pair  store_label  = {IM_TEXT, "Store" };
void		   store_proc();

caddr_t		   fname_item;
struct typed_pair  file_label  = {IM_TEXT, "File" };

caddr_t		   fill_item;
struct typed_pair  fill_label  = {IM_TEXT, "Fill" };
void		   fill_proc();

caddr_t		   fill_value_item;
struct typed_pair  fill_value_label  = {IM_TEXT, "with" };
void		   fill_value_proc();

caddr_t		   invert_item;
struct typed_pair  invert_label  = {IM_TEXT, "Invert" };
void		   invert_proc();

caddr_t		   fill_op_item;
struct typed_pair  fill_op_label  = {IM_TEXT, "Load / Fill should" };
void		   fill_op_proc();

caddr_t		   paint_op_item;
struct typed_pair  paint_op_label  = {IM_TEXT, "Cursor op" };
void		   paint_op_proc();
int		   paint_op_removed = FALSE;

caddr_t		   bkgrnd_value_item;
struct typed_pair  bkgrnd_value_label  = {IM_TEXT, "Proof background" };
void		   bkgrnd_proc();

/*	Values for enums above						*/

#define OP_OR	0			/*  paint ops		*/
#define OP_XOR	1
 
#define OP_REPLACE	0		/*  load / fill ops	*/
#define OP_MERGE	1

#define GR_WHITE	0		/*  gray codes		*/
#define GR_GRAY25	1
#define GR_ROOT_GRAY	2
#define GR_GRAY50	3
#define GR_GRAY75	4
#define GR_BLACK	5

void
mode_proc(optsw, ip, val)
caddr_t	  optsw;
caddr_t	  ip;
u_int	  val;
{
	set_state(val);
}

#define IC_MODECOUNT	2
char		  *mode_values[IC_MODECOUNT+1]  =  { "Cursor", "Icon" };
struct typed_pair  mode_choices  = {IM_TEXTVEC, (caddr_t)mode_values };

#define IC_GRAYCOUNT	6
char		  *gray_values[IC_GRAYCOUNT+1]  =  {
	"White", "25%", "Root Gray", "50%", "75%", "Black" };
struct typed_pair  gray_choices  = {IM_TEXTVEC, (caddr_t)gray_values };

#define IC_FOPCOUNT	2
char		  *fill_op_values[IC_FOPCOUNT+1]  =  { "Replace", "Merge" };
struct typed_pair  fill_op_choices  = {IM_TEXTVEC, (caddr_t)fill_op_values };

#define IC_POPCOUNT	2
char		  *paint_op_values[IC_POPCOUNT+1]  =  { "OR", "XOR" };
struct typed_pair  paint_op_choices  = {IM_TEXTVEC, (caddr_t)paint_op_values };


/*			general globals					*/

int	errno;

static u_int	cur_x, cur_y,
		cur_op,
		cell_count,
		cell_size,
		state	=	-1;	/* so first set_state really does  */

char		file_default[] = "test.icon";
char		file_name[1024];

struct pixfont *font;
FILE	       *sysout = stderr;

main(argc,argv)
int	  argc;
char	**argv;
{
	tool = tool_create(tool_name, TOOL_NAMESTRIPE, NULL, &my_icon);
	if (tool == (struct tool *)0)
		exit(1);

	font = pf_default();
	msg_sw = msgsw_createtoolsubwindow(tool, "", -1, MSG_HEIGHT, "", font);
	if (msg_sw == (struct toolsw *)0)
		exit(1);
	msw = (struct msgsubwindow *)msg_sw->ts_data;

	proof_sw = tool_createsubwindow(tool, "", PROOF_SIDE, PROOF_SIDE);
	if (proof_sw == (struct toolsw *)0)
		exit(1);
	init_proof();

	options_sw = optsw_createtoolsubwindow(tool, "", -1, OPTIONS_HEIGHT);
	if (options_sw == (struct toolsw *)0)
		exit(1);
	init_options();

	canvas_sw = tool_createsubwindow(tool, "", -1, CANVAS_SIDE);
	if (canvas_sw == (struct toolsw *)0)
		exit(1);
	init_canvas();

	fix_tool_rect();
	set_state(CURSOR);
	fill_value_proc(NULL, NULL, GR_ROOT_GRAY);
	bkgrnd_proc(NULL, NULL, GR_ROOT_GRAY);
	signal(SIGWINCH, sigwinched);
	tool_install(tool);

	tool_select(tool, 0);

	tool_destroy(tool);
	exit(0);
}

fix_tool_rect()
{
	if (wmgr_iswindowopen(tool->tl_windowfd) )  {
		win_getrect(tool->tl_windowfd, &tool_rect);
	} else {
		win_getsavedrect(tool->tl_windowfd, &tool_rect);
	}
	tool_rect.r_width = 2*tool_borderwidth(tool) +
			    max(PROOF_SIDE + optsw_coltox(osw, 64)  +
				tool_subwindowspacing(tool),
				CANVAS_SIDE);
	tool_rect.r_height = MSG_HEIGHT
			   + CANVAS_SIDE + PROOF_SIDE
			   + tool_stripeheight(tool)
			   + tool_borderwidth(tool)
			   + 2*tool_subwindowspacing(tool);
	if (rect_bottom(&tool_rect) >= 800)  {
		tool_rect.r_top -= rect_bottom(&tool_rect) - 799;
	}
	if (wmgr_iswindowopen(tool->tl_windowfd) )  {
		win_setrect(tool->tl_windowfd, &tool_rect);
	} else {
		win_setsavedrect(tool->tl_windowfd, &tool_rect);
	}
}


set_state(which)
{
	if (state == which)  {
		return;
	}
	if ( (state = which) == CURSOR)  {
		canvas_pr = &new_cursor_pr;
		cell_size = CURSOR_SIZE;
		if (paint_op_removed) {
			optsw_restoreitems(osw, paint_op_item, 1, TRUE);
			paint_op_removed = FALSE;
		}
	} else {
		canvas_pr = &icon_pr;
		cell_size = ICON_SIZE;
		if (!paint_op_removed) {
			optsw_removeitems(osw, paint_op_item, 1, TRUE);
			paint_op_removed = TRUE;
		}
		
	}
	optsw_setvalue(osw, mode_item, which);
	set_cursor();
	cell_count = CANVAS_DISPLAY / cell_size;
	paint_proof(); 
	paint_canvas();
}

set_cursor()
{
	if (state == ICONIC)  {
		win_setcursor(proof_sw->ts_windowfd, &main_cursor);
	} else {
		win_setcursor(proof_sw->ts_windowfd, &new_cursor);
	}
}

static
sigwinched()
{
	tool_sigwinch(tool);
}

nullproc()
{
	return;
}


int   (*saved_handler)();
int	saved_mask;
int	clear_message();

bitch(format, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8)
char   *format, *arg1, *arg2, *arg3, *arg4, *arg5, *arg6, *arg7, *arg8;
{
	char	buf[256];

	sprintf(buf,format, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
	msgsw_setstring(msw, buf);
	saved_mask = tool->tl_io.tio_inputmask;
	tool->tl_io.tio_inputmask = (1 << tool->tl_windowfd)  +
				    (1 << canvas_sw->ts_windowfd)  +
				    (1 << options_sw->ts_windowfd);
	if (tool->tl_io.tio_selected != clear_message)  {
		saved_handler = tool->tl_io.tio_selected;
	}
	tool->tl_io.tio_selected = clear_message;
}

clear_message(datum, ibits, obits, ebits, timer)
caddr_t		 datum;
u_int		*ibits, *obits, *ebits;
struct timeval **timer;
{
	msgsw_setstring(msw, "");
	tool->tl_io.tio_selected = saved_handler;
	tool->tl_io.tio_inputmask = saved_mask;
}

/*
 *	Proof Section
 */

init_proof()
{
	struct inputmask  mask;

	input_imnull(&mask);
	win_setinputmask(proof_sw->ts_windowfd, &mask, NULL, WIN_NULLLINK);
	proof_sw->ts_io.tio_handlesigwinch = proof_sighandler;
	proof_sw->ts_destroy = nullproc;
	proof_pixwin = pw_open(proof_sw->ts_windowfd);
}

static
proof_sighandler(sw_data)
caddr_t	 sw_data;
{
	pw_damaged(proof_pixwin);
	paint_proof();
	pw_donedamaged(proof_pixwin);
	proof_sw->ts_width = win_getwidth(proof_sw->ts_windowfd);
	proof_sw->ts_height = win_getheight(proof_sw->ts_windowfd);
}

paint_proof()
{
	int	x, y;

	for (y = 0; y < proof_sw->ts_height; y += 64)  {
		for (x = 0; x < proof_sw->ts_width; x += 64)  {
			pw_write(proof_pixwin, x, y, 64, 64,
				 PIX_SRC, proof_pr, 0, 0);
		}
	}
	if (state == ICONIC)  {
		paint_proof_icon();
	}
}

paint_proof_icon()
{
	pw_write(proof_pixwin, PROOF_MARGIN, PROOF_MARGIN, 64, 64,
		 PIX_SRC, &icon_pr, 0, 0);
}

/*
 *	Options subwindow section
 */
init_options()
{
	win_setcursor(options_sw->ts_windowfd, &main_cursor);

	osw = options_sw->ts_data;

	mode_item = optsw_enum(osw, &mode_label, &mode_choices,
				0, CURSOR, mode_proc);
	start_new_line(mode_item);

	label_item = optsw_label(osw, &name_label);
 
	quit_item = optsw_command(osw, &quit_label, quit_proc);
 
	load_item = optsw_command(osw, &load_label, load_proc);
	start_new_line(load_item);

	store_item = optsw_command(osw, &store_label, store_proc);

	fname_item = optsw_text(osw, &file_label, file_default, 0, NULL);

	fill_item = optsw_command(osw, &fill_label, fill_proc);
	start_new_line(fill_item);

	fill_value_item = optsw_enum(osw, &fill_value_label,
					  &gray_choices,
					  0, 2, fill_value_proc);

	invert_item = optsw_command(osw, &invert_label, invert_proc);

	fill_op_item = optsw_enum(osw, &fill_op_label,
				       &fill_op_choices,
				       0, 0, NULL);
	start_new_line(fill_op_item);

	paint_op_item = optsw_enum(osw, &paint_op_label,
					&paint_op_choices,
					0, 1, paint_op_proc);

	bkgrnd_value_item = optsw_enum(osw, &bkgrnd_value_label,
					    &gray_choices,
					    0, 2, bkgrnd_proc);
	start_new_line(bkgrnd_value_item);
}

start_new_line(item)		/*  special-case routine for legibility  */
caddr_t	item;
{
	struct item_place  p;

	rect_construct(&p.rect, 0, -1, -1, -1);
	p.fixed.x = TRUE;
	p.fixed.y = p.fixed.w = p.fixed.h = FALSE;
	optsw_setplace(osw, item, &p, 0);
}

/*	handlers for the various option items, in their creation order  */

void
quit_proc(optsw, ip)
caddr_t	  optsw;
caddr_t	  ip;
{
	msgsw_setstring(msw,
	"Please confirm with the left mouse button, or cancel with right or middle.");
	if (cursor_confirm(canvas_sw->ts_windowfd)) {
		tool_done(tool);
	} else {
		bitch("Quit cancelled.");
	}
}

void
load_proc(optsw, ip)
caddr_t	  optsw;
caddr_t	  ip;
{
	int			 c;
	u_int			 count, result;
	u_int			 data[256], *dp;
	u_int			 op, mode, chunks;
#define SHORT_CHUNKS	2
#define LONG_CHUNKS	1
	struct string_buf	 file_name_buf;
	FILE			*fd;

	file_name_buf.limit = 1024;
	file_name_buf.data = file_name;
	result = optsw_getvalue(fname_item, &file_name_buf);
	if (result < 0)  {
		bitch("Trouble: icontool couldn't read the filename");
		sleep(10);
		exit(-1);
	}
	fd = fopen(file_name, "r");
	if (fd == NULL) {
		bitch("Sorry, couldn't open %s", file_name);
		return;
	}
	while ( (c= getc(fd)) != '{')  {		/*  matching  }	*/
		if (c==EOF)  {
			bitch("Sorry, I need an array of shorts or unsigneds");
			return;
		}
	}
	dp = data;
	count =0;
	do {	result = fscanf(fd, " 0x%X,", dp++);
		count++;
	} while (result == 1);
	close(fd);

	switch (--count)  {
	  case   8:	mode = CURSOR;
			chunks = LONG_CHUNKS;
			break;
	  case  16:	mode = CURSOR;
			chunks = SHORT_CHUNKS;
			break;
	  case 128:	mode = ICONIC;
			chunks = LONG_CHUNKS;
			break;
	  case 256:	mode = ICONIC;
			chunks = SHORT_CHUNKS;
			break;
	  default:	bitch("Sorry, I don't understand that array.");
			return;
	}
	op = optsw_getvalue(fill_op_item, &result);
	if (mode == CURSOR)  {
		dp = new_cursor_array;
	} else {
		dp = icon_array;
	}
	if (chunks == LONG_CHUNKS)  {
		if (op == OP_REPLACE)  {
			replace_longs(dp, data, count);
		} else {
			merge_longs(dp, data, count);
		}
	} else {
		if (op == OP_REPLACE)  {
			replace_shorts(dp, data, count);
		} else {
			merge_shorts(dp, data, count);
		}
	}
	state = -1;
	set_state(mode);
}

static
replace_longs(target, source, count)
int	*target, *source, count;
{
	while (count-- > 0) {
		target[count] = source[count];
	}
}

static
merge_longs(target, source, count)
int   *target, *source, count; 
{
	while (count-- > 0) {
		target[count] |= source[count];
	}
}

static
replace_shorts(target, source, count)
int	*target, *source, count;
{
	while (count-- > 0) {
		target[count/2] = source[count];
		target[count/2] |= (source[count-1] << 16);
		count -= 1;
	}
}

static
merge_shorts(target, source, count)
int	*target, *source, count;
{
	while (count-- > 0) {
		target[count/2] |= source[count];
		target[count/2] |= (source[count-1] << 16);
		count -= 1;
	}
}

void
store_proc(optsw, ip)
caddr_t	  optsw;
caddr_t	  ip;
{
	int			 i, limit, result, size;
	u_int			*data;
	char			token[128];
	struct string_buf	 file_name_buf;
	FILE			*fd;
	struct stat		 stat_buf;

	file_name_buf.limit = 1024;
	file_name_buf.data = file_name;
	result = optsw_getvalue(fname_item, &file_name_buf);

	/* modified for gremlin icon creation */
	if (state == CURSOR) {
		size = 16;
		data = new_cursor_array;
	} else {
		size = 64;
		data = icon_array;
	}

	if (strncmp("icon.", file_name_buf.data, 5) == 0)
		strcpy(token, &file_name_buf.data[5]);
	else
		strcpy(token, file_name_buf.data);
	for (i=0; i<strlen(token); i++)
		if (token[i] == '.')
			token[i] = '_';

	if (stat(file_name, &stat_buf) == -1)  {
		if (errno != ENOENT)  {
			bitch("Sorry, %s", sys_errlist[errno]);
			return;
		}
	} else {			/* stat succeeded; file exists	*/
		bitch("%s exists; please confirm overwrite.", file_name);
		if (!cursor_confirm(canvas_sw->ts_windowfd))  {
			return;
		}
	}
	fd = fopen(file_name, "w");
	if (fd == NULL)  {
		bitch("Sorry, can't write to %s", file_name);
		return;
	}
	fprintf(fd, "static short icon_%s_data[%d] = {\n",
		token, size * size / 16);

	limit = size * size / 128;
#define twoshorts(n) (((n)&0xFFFF0000)>>16)&0xFFFF, (n)&0xFFFF
	for (i=0; i<limit;++i) {
		fprintf(fd, "\t0x%-04X, 0x%-04X, 0x%-04X, 0x%-04X, 0x%-04X, 0x%-04X, 0x%-04X, 0x%-04X,\n",
			twoshorts(data[0]), twoshorts(data[1]),
			twoshorts(data[2]), twoshorts(data[3]));
		data += 4;
	}
	fputs("};\n", fd);
	fprintf(fd, "mpr_static(%s_pr, ICON_SIZE, ICON_SIZE, 1, icon_%s_data);\n\n",
				token, token);
	fclose(fd);
}

void
fill_proc(optsw, ip, val)
{
	int	op, x, y, result;

	switch (optsw_getvalue(fill_op_item, &result) )  {
	  case OP_REPLACE:	op = PIX_SRC; break;
	  case OP_MERGE:	op = PIX_SRC | PIX_DST; break;
	  default:	bitch("Trouble: fill doesn't know what to do.");
	}
	for (y = 0; y < cell_count; y += 64)  {
		for (x = 0; x < cell_count; x += 64)  {
			pr_rop(canvas_pr, x, y, cell_count, cell_count,
					  op, fill_pr, 0, 0);
		}
	}
	paint_canvas();
	if (state == ICONIC)  {
		paint_proof_icon();
	} else {
		set_cursor();
	}
}

void
fill_value_proc(optsw, ip, val)
{
	switch (val)  {
	    case  GR_WHITE:	fill_pr = &white_patch;
				break;
	    case  GR_GRAY25:	fill_pr = &gray25_patch;
				break;
	    case  GR_ROOT_GRAY:	fill_pr = &root_gray_patch;
				break;
	    case  GR_GRAY50:	fill_pr = &gray50_patch;
				break;
	    case  GR_GRAY75:	fill_pr = &gray75_patch;
				break;
	    case  GR_BLACK:	fill_pr = &black_patch;
				break;
	    default:		fill_pr = &root_gray_patch;
	}
}

void
invert_proc()
{
	pr_rop(canvas_pr, 0, 0, cell_count, cell_count,
		PIX_NOT(PIX_DST), 0, 0, 0);
	paint_canvas();
	if (state == ICONIC)  {
		paint_proof_icon();
	} else {
		set_cursor();
	}
}

void
paint_op_proc(optsw, ip, val)
caddr_t	  optsw;
caddr_t	  ip;
u_int	  val;
{
	u_int	op;

	if (val == OP_XOR) {
		new_cursor.cur_function = PIX_SRC ^ PIX_DST;
	} else {
		new_cursor.cur_function = PIX_SRC | PIX_DST;
	}
	set_cursor();
}

void
bkgrnd_proc(optsw, ip, val)
{
	switch (val)  {
	    case  GR_WHITE:	proof_pr = &white_patch;
				break;
	    case  GR_GRAY25:	proof_pr = &gray25_patch;
				break;
	    case  GR_ROOT_GRAY:	proof_pr = &root_gray_patch;
				break;
	    case  GR_GRAY50:	proof_pr = &gray50_patch;
				break;
	    case  GR_GRAY75:	proof_pr = &gray75_patch;
				break;
	    case  GR_BLACK:	proof_pr = &black_patch;
				break;
	    default:		proof_pr = &root_gray_patch;
	}
	paint_proof();
}

/*
 *	 Canvas Section
 */

init_canvas()
{
	struct inputmask mask;

	canvas_reader = canvas_basereader;
	canvas_pixwin = pw_open(canvas_sw->ts_windowfd);
	canvas_sw->ts_io.tio_selected = canvas_selected;
	canvas_sw->ts_io.tio_handlesigwinch = canvas_sighandler;
	canvas_sw->ts_destroy = nullproc;

	input_imnull(&mask);
	win_setinputcodebit(&mask, MS_LEFT );
	win_setinputcodebit(&mask, MS_MIDDLE);
	win_setinputcodebit(&mask, LOC_MOVEWHILEBUTDOWN);
	win_setinputcodebit(&mask, LOC_STILL);
	win_setinputcodebit(&mask, LOC_WINEXIT);
	mask.im_flags |= IM_NEGEVENT;
	win_setinputmask(canvas_sw->ts_windowfd, &mask, NULL, WIN_NULLLINK);
	win_setcursor(canvas_sw->ts_windowfd, &main_cursor);
	cur_x = cur_y = -1;
}

static
canvas_selected(nullsw, ibits, obits, ebits, timer)
caddr_t		*nullsw;
int		*ibits, *obits, *ebits;
struct timeval	*timer;
{
	struct	inputevent  ie;

	if (input_readevent(canvas_sw->ts_windowfd, &ie) == -1) {
		perror("icontool input failed");
		abort();
	}
	(*canvas_reader)(&ie);
	*ibits = *obits = *ebits = 0;
}

static
canvas_basereader(ie)
struct  inputevent  *ie;
{
	if (win_inputnegevent(ie) ) {
		return;
	}
	switch (ie->ie_code) {
	  case MS_LEFT:	    cur_op = 1;
			    break;
	  case MS_MIDDLE:   cur_op = 0;
			    break;
	  default:	    return;		/* ignore all other input  */
	}
	set_canvas_tracker();
	canvas_feedback(ie);
}

static
canvas_tracker(ie)
struct	inputevent  *ie;
{
	if (win_inputnegevent(ie))  {
		switch (ie->ie_code) {
		  case MS_LEFT:		/*  mouse button up		*/
		  case MS_MIDDLE:
			reset_canvas_reader();
			if (state == ICONIC)  {
				paint_proof_icon();
			}
		}
		return;
	}
	switch (ie->ie_code) {
	  case LOC_WINEXIT:	reset_canvas_reader();
				if (state == ICONIC)  {
					paint_proof_icon();
				}
				return;
	  case MS_LEFT:			/*  two buttons down?	     */
	  case MS_MIDDLE:	cur_op = -1;
			 	canvas_reader = wait_legal_mouse;
				return;
	  case LOC_STILL:
	  case LOC_MOVEWHILEBUTDOWN:
				canvas_feedback(ie);
				return;
	}				/* ignore all other input  */
}

static
wait_legal_mouse(ie)
struct	inputevent  *ie;
{
	if (ie->ie_code == LOC_WINEXIT)  {
		reset_canvas_reader();
		return;
	}
	if (win_inputnegevent(ie))  {
		switch (ie->ie_code) {
		  case MS_LEFT:		cur_op = 0;
					break;
		  case MS_MIDDLE:	cur_op = 1;
					break;
		  default:		return;
		}
	set_canvas_tracker();
	canvas_feedback(ie);
	}
}

static
set_canvas_tracker()
{
	cur_x = cur_y = -1;
	canvas_reader = canvas_tracker;
}

static
reset_canvas_reader()
{
	canvas_reader = canvas_basereader;
	cur_op = -1;
}

static
canvas_feedback(ie)
struct	inputevent  *ie;
{
	register int	new_x, new_y, color;

	if (ie->ie_code == LOC_STILL && state == ICONIC)  {
		paint_proof_icon();
		return;
	}
	if (ie->ie_locx < CANVAS_MARGIN || ie->ie_locy < CANVAS_MARGIN)  {
		return;
	}
	new_x = (ie->ie_locx - CANVAS_MARGIN) / cell_size;
	new_y = (ie->ie_locy - CANVAS_MARGIN) / cell_size;
	if (new_x >= cell_count || new_y >= cell_count)  {
		return;
	}
	color = pr_get(canvas_pr, new_x, new_y);
	if (new_x == cur_x && new_y == cur_y && cur_op == color) 
		return;
	cur_x  =  new_x;
	cur_y  =  new_y;
	paint_cell(new_x, new_y, cur_op);
	pr_put(canvas_pr, new_x, new_y, cur_op);
	if (state == CURSOR)  {
		set_cursor();
	}
}

static
canvas_sighandler()
{
	pw_damaged(canvas_pixwin);
	paint_canvas();
	pw_donedamaged(canvas_pixwin);
}

paint_canvas()
{
	register int	x, y;
	struct rect	 r;

	pw_writebackground(canvas_pixwin, 0, 0, BIG, BIG, PIX_CLR);
	r.r_left = CANVAS_MARGIN;
	r.r_width = cell_count * cell_size;
	r.r_height = cell_size;
	pw_vector(canvas_pixwin, CANVAS_MARGIN, CANVAS_MARGIN,
				 rect_right(&r), CANVAS_MARGIN,
				 PIX_SET, 1);
	pw_vector(canvas_pixwin, CANVAS_MARGIN, CANVAS_MARGIN,
				 CANVAS_MARGIN, rect_right(&r),
				 PIX_SET, 1);
	for (y = 0; y < cell_count; y++) {
		r.r_top = CANVAS_MARGIN + cell_size * y;
		pw_lock(canvas_pixwin, &r);
		for (x = 0; x < cell_count; x++) {
			if (pr_get(canvas_pr, x,y))  {
				paint_cell(x, y, 1);
			}
		}
		pw_unlock(canvas_pixwin);
	}
	r.r_top = CANVAS_MARGIN;
	r.r_width +=1;
	r.r_height = cell_count * cell_size + 1;
	pw_lock(canvas_pixwin, &r);
/*	for (x = CANVAS_MARGIN;
 *	     x < CANVAS_MARGIN + r.r_width;
 *	     x += cell_size) {
 *		pw_vector(canvas_pixwin, x, CANVAS_MARGIN,
 *				   1, r.r_height, PIX_SET);
 *	}
 */
	pw_vector(canvas_pixwin, rect_right(&r), CANVAS_MARGIN,
				 rect_right(&r), rect_bottom(&r),
				 PIX_SET, 1);
	pw_vector(canvas_pixwin, CANVAS_MARGIN, rect_bottom(&r),
				 rect_right(&r), rect_bottom(&r),
				 PIX_SET, 1);
	pw_unlock(canvas_pixwin);
}

paint_cell(x, y, color)
int	x, y, color;
{
	register int	dx, dy, dim;

	dx = CANVAS_MARGIN + cell_size*x + 1;
	dy = CANVAS_MARGIN + cell_size*y + 1;
	dim = cell_size - 1;
	pw_write(canvas_pixwin, dx, dy, dim, dim, PIX_SRC,
		 (color ? &gray50_patch : &white_patch), 1, 1);
}
