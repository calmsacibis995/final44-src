
/* $XConsortium: testutils.c,v 5.2 91/07/24 18:42:26 hersh Exp $ */

/*****************************************************************
Copyright (c) 1989,1990, 1991 by Sun Microsystems, Inc. and the X Consortium.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the names of Sun Microsystems,
the X Consortium, and MIT not be used in advertising or publicity 
pertaining to distribution of the software without specific, written 
prior permission.  

SUN MICROSYSTEMS DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, 
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT 
SHALL SUN MICROSYSTEMS BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL 
DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/



/* 
 * This file contains PHIGS testing utilties 
 */
#include "X11/Xlib.h"
#include "X11/Xatom.h"
#include "stdio.h"
#include "signal.h"
#include "pixutils.h"
#include "logmsg.h"
#include "imath.h"
#include "testutils.h"
#define BUFSIZE 1024

#ifdef NEWT
#include "NewTvararg.h"
#else
#include "varargs.h"
#endif

#define MAXCOLOR 256

#define eqstring(a,b)  !strcmp((a),(b))    /* compare text string */
#define SCALE_FACTOR 255
#define SEPS 1
#define SEQ(a,b) ( (int)(a)>(int)(b)-SEPS && (int)(a)<(int)(b)+SEPS )
#define MINIMUM(a,b)  flt((a),(b))? (a):(b)

/*
 * global variables
 */

/*
 * forward declaration
 */
/*
 * export routines
 */
void i_fake_button();
void i_open_phigs();
void i_open_ws();
void i_open_x_ws();
Ppoint3* i_generate_n_Ppoint3();
Ppoint_list3* i_generate_n_Ppoint_list3();
void i_grid();
int i_check_pixel3();
int i_check_line3();
void i_viewxform_point3();
void i_wsxform_point3();
void i_get_window_dim();
void i_make_xwindow();
Pint i_get_ws_type();
void i_print_var();
void i_pause();
int i_bogus_error();
Pdyn_mod i_get_ws_dyn_mod();
Pdyn_mod i_get_struct_dyn_mod();
int i_get_phigs_info();
int i_is_posted_struct();


#ifdef NEWT
void _tfprintf();
void _tvprintf();
void _tabort();
#endif

/* local data structure */
typedef struct {
	Pint x;
	Pint y;
} int_point;

/* local routines */
static void i_get_ws_info();
static void post_button();
static void post_button_on_interrupt();

/* global variables */
Display *save_display;
Window save_window;
int save_x;
int save_y;

/*
 * i_open_phigs(errfile,memsize)
 * call popen_phigs() by default, if environment variables 
 * "I_NO_MONITOR" and/or "I_CLIENT_SIDE" is set, then 
 * call popen_xphigs() instead
 */
void
i_open_phigs(errfile,memsize)
	char* errfile;
	size_t memsize;
{
	static Pxphigs_info pexinfo = {NULL,NULL,{NULL,NULL},{NULL,NULL},{0,0}};
	unsigned long mask = 0;

	if (clientside) {
		pexinfo.flags.force_client_SS = 1;
		mask |= PXPHIGS_INFO_FLAGS_CLIENT_SS;
	} if (nomonitor)  {
		pexinfo.flags.no_monitor = 1;
		mask |= PXPHIGS_INFO_FLAGS_NO_MON;
	} if (pexinfo.flags.force_client_SS || pexinfo.flags.no_monitor) 
        	popen_xphigs(errfile,memsize,mask,&pexinfo);
	else 
        	popen_phigs(errfile, memsize);
}

/*
 * i_open_ws(ws)
 * open a simple x_tool type PHIGS workstation
 */
void
i_open_ws(ws)
	int ws;
{
	popen_ws(ws,NULL,phigs_ws_type_x_tool);
}

/*
 * i_open_x_ws(ws,display,window,x,y,w,h)
 * open a x drawable type ws by default, if the environment variable
 * "I_X_TOOL_WS" is set, then open a x tool type ws.
 * If "I_WIN_X_OFFSET" and/or "I_WIN_Y_OFFSET" is set, the values are
 * used in offsetting the position of the window.
 * This functions takes as input the ws id, position of window (x,y) and
 * its width(w) and height(h), the display pointer(display) and the 
 * window id of the ws (window) is returned.
 */
void
i_open_x_ws(ws,display,window,x,y,w,h)
	int ws;
	Display **display;
	Window *window;
	int x,y,w,h;
{
	Pconnid_x_drawable ws_conn;
	int wstype;
        Pescape_out_data *escout;
        Pescape_in_data escin;
        Pstore     store;
        Pint       err;

	if (xtoolws) {
		wstype = phigs_ws_type_create(phigs_ws_type_x_tool,
                	PHIGS_TOOL_X, x + winxoffset,
                	PHIGS_TOOL_Y, y + winyoffset,
                	PHIGS_TOOL_WIDTH, w,
                	PHIGS_TOOL_HEIGHT, h,
			NULL);
        	popen_ws(1, NULL, wstype);

        	pcreate_store(&err, &store );
        	if (err) 
			tabort("ERROR: i_get_ws_info: %d in pcreate_store\n",err);
        	escin.escape_in_u2.ws_id = ws;
        	pescape(PUESC_DPYINFO, &escin, store, &escout);
        	*window = escout->escape_out_u2.drawable_id;
		if (clientside && ! nomonitor)
			*display = XOpenDisplay(escout->escape_out_u2.display_name);
		else
        		*display = escout->escape_out_u2.display;
	} else {
        	i_make_xwindow(display, window, &ws_conn, x, y, w, h);
		popen_ws(ws,&ws_conn,phigs_ws_type_x_drawable);
	}
}

/*
 * i_get_ws_info(ws,display,overlay)
 * to return the X's display and the overlay input window of the given ws
 */
static void
i_get_ws_info(ws,display,overlay)
	Pint ws;
	Display **display;
	Window *overlay;
{
        Pescape_out_data *escout;
        Pescape_in_data escin;
        Pstore     store;
        Pint       err;

        pcreate_store(&err, &store );
        if (err) 
		tabort("ERROR: i_get_ws_info: %d in pcreate_store\n",err);
        escin.escape_in_u2.ws_id = ws;
        pescape(PUESC_DPYINFO, &escin, store, &escout);
        *overlay = escout->escape_out_u2.input_overlay_id;
	if (clientside && ! nomonitor)
		*display = XOpenDisplay(escout->escape_out_u2.display_name);
	else
        	*display = escout->escape_out_u2.display;
}

/*
 * i_fake_button(ws,viewind,point,timeout)
 * to simulate button input, if timeout > 0, then post the event at interrupt
 * after timeout seconds
 */
void
i_fake_button(ws,viewind,point,timeout)
	Pint ws;
	Pint viewind;
	Ppoint3 point;
	int timeout;
{
	Display *display;
	Window overlay;
	int pcptx,pcpty;
	Ppoint3 ndcpt;
	int offdisplay;

 	i_get_ws_info(ws,&display,&overlay);
	/* calculate position in dc */
        /* apply view xform */
        i_viewxform_point3(ws,viewind,point,&ndcpt);

        /* apply workstation xform */
        i_wsxform_point3(display,overlay,ws,ndcpt,&pcptx,&pcpty,&offdisplay);
        if (offdisplay) {/* pixel is off display */
                return;
	}
	if (timeout > 0) {
        	save_display = display;
		save_window = overlay;
		save_x = pcptx;
		save_y = pcpty;
                signal(SIGALRM,post_button_on_interrupt);
		alarm(timeout);
	} else {
 		post_button(display,overlay,pcptx,pcpty);
	}
}

/*
 * post_button_on_interrupt()
 * to post button input on receiving an alarm signal
 */
static void
post_button_on_interrupt()
{
        post_button(save_display,save_window,save_x,save_y);
}

/*
 * post_button(display,window,x,y)
 * to post button input to specified window
 */
static void
post_button(display,window,x,y)
	Display *display;
	Window window;
	Pint x,y;
{
	XEvent button;
	unsigned long mask;

	/* stuff event structure */
	mask = ButtonPress;
	button.xbutton.display = display;
	button.xbutton.window = window;
	button.xbutton.root = DefaultRootWindow(display);
	button.xbutton.subwindow = None;
	button.xbutton.type = ButtonPress;
	button.xbutton.button = 1;
	button.xbutton.time = CurrentTime;
	button.xbutton.send_event = True;
	button.xbutton.same_screen = True;
        button.xbutton.x = x;
        button.xbutton.y = y;
        button.xbutton.x_root = 0;
        button.xbutton.y_root = 0;
        button.xbutton.serial = 0;

	/* send button press event */
	XSendEvent(display,window,True,mask,&button);
	XSync(display,0);
}

/*
 * i_generate_n_Ppoint3(n)
 * return an array of n points  
 */
Ppoint3* 
i_generate_n_Ppoint3(n,x,y,delta)
	int n;		/* number of points */
	Pfloat x; 	/* x coordinate of starting position */
	Pfloat y; 	/* y coordinate of starting position */
	Pfloat delta; 	/* increment */
{
	Ppoint3* p;
	int i;
	int xdir = 1;
	int ydir = 1;

	p = (Ppoint3*) malloc(n*sizeof(Ppoint3));
        for (i=0;i<n;i++) {
                p[i].x = x;
                p[i].y = y;
                p[i].z = 0.0;
                if (i%2)
                        x += delta * xdir;
                else
                        y += delta * ydir;
                if ( i==n/4) ydir = -1;
                else if ( i==n/2) xdir = -1;
                else if ( i==n*3/4) ydir = 1;
        }
	return(p);
}

/*
 * i_generate_n_Ppoint_list3(row,col)
 * generate an array of row*col point_list3 type
 */

Ppoint_list3* 
i_generate_n_Ppoint_list3(row,col)
{
	Ppoint_list3* pl;
	Ppoint3* p;
	int i,j,k;

	pl = (Ppoint_list3*) malloc(row*col*sizeof(Ppoint_list3));
        for (i=0,k=0; i<row; ++i) {
            for (j=0; j<col; ++j,++k) {
                pl[k].num_points = 4;
		p = (Ppoint3*) malloc(4*sizeof(Ppoint3));
                pl[k].points = p;
                p[0].x = p[3].x = j * 0.05;
                p[0].y = p[1].y = i * 0.05;
                p[1].x = p[2].x = j * 0.05 + 0.03;
                p[2].y = p[3].y = i * 0.05 + 0.03;
                p[0].z = p[1].z =
                p[2].z = p[3].z = 0.0;
            }
        }
	return(pl);
}

/*
 * i_grid(ws,str,pri,x1,y1,x2,y2,xinc,yinc,col,linetype)
 * Draw a grid on the given workstation using given structure
 * only if the environment variable GRID is set
 */
void 
i_grid(ws,str,pri,x1,y1,x2,y2,xinc,yinc,col,linetype)
	Pint ws; 	/* workstation id */
	Pint str; 	/* structure id */
	Pfloat pri; 	/* structure posting priority */
	Pfloat x1;  	/* x coordinate of upper left corner */
	Pfloat y1;  	/* x coordinate of upper left corner */
	Pfloat x2;  	/* x coordinate of lower right corner */
	Pfloat y2;  	/* x coordinate of lower right corner */
	Pfloat xinc;  	/* x increment */
	Pfloat yinc;  	/* y increment */
	Pint col;  	/* colour index */
	Pint linetype; 	/* line type */
{
	Ppoint line[2];
	Ppoint_list pl;
	Pint err,id;
	Popen_struct_status status;

	if (grid) {
	pl.num_points = 2;
	pl.points = line;
	pinq_open_struct(&err,&status,&id);
	if (err)
		tabort("ERROR: pinq_open_struct: %d in pinq_open_struct\n",err);
	if (status==PSTRUCT_OPEN)
		pclose_struct();
	popen_struct(str); 
	pset_view_ind(0);
	pset_linetype(linetype);
	pset_line_colr_ind(col);
	for (line[0].x = x1, line[1].x = x2, line[0].y = line[1].y = y1; 
			fle(line[0].y, y2);  
			line[1].y = (line[0].y += yinc))
			ppolyline(&pl);
	for (line[0].y = y1, line[1].y = y2, line[0].x = line[1].x = x1; 
			 fle(line[0].x, x2);  
			line[1].x = (line[0].x += xinc))
			ppolyline(&pl);
	pclose_struct();
	ppost_struct(ws,str,pri);
	if (status==PSTRUCT_OPEN)
		popen_struct(id);
	}
}

/* 
 * i_get_phigs_info(class)
 * return in the form of an integer certain informations from PHIGS 
 */
int i_get_phigs_info(class)
	char *class;
{
	int err,num;

	if (eqstring(class,"pattern capability of tool workstation")) {
        	pinq_pat_facs(phigs_ws_type_x_tool,&err,&num);
		if (err)
		    tabort("ERROR: i_get_phigs_info: %d in pinqpatfacil\n",err);
		return(num > 0);
	} else
		tvprintf(0,"i_get_phigs_info: unknown class\n");
}

/* 
 * i_get_ws_dyn_mod(ws,class)
 * return the dynamic modification type of the given class
 */
Pdyn_mod
i_get_ws_dyn_mod(ws,class)
	Pint ws;
	char *class;
{
	Pdyns_ws_attrs wsmods;
	Pint err;
        Pint wstype;
        Pconnid cid;

	pinq_ws_conn_type(ws,BUFSIZE,&err,&cid,&wstype);
        if (err) 
		tabort("ERROR: i_get_ws_dyn_mod: %d in pinq_ws_conn_type\n",err);
	pinq_dyns_ws_attrs(wstype,&err,&wsmods);
        if (err) 
		tabort("ERROR: i_get_ws_dyn_mod: %d in pinq_dyns_ws_attrs\n",err);
	if (eqstring(class,"workstation transformation modification"))
		return(wsmods.ws_tran);
	if (eqstring(class,"view representation modification"))
		return(wsmods.view_rep);
	if (eqstring(class,"invisibility filter modification"))
		return(wsmods.invis_filter);
	if (eqstring(class,"colour representation modification"))
		return(wsmods.colr_rep);
	if (eqstring(class,"polyline bundle representation modification"))
		return(wsmods.line_bundle);
	else
		tvprintf(0,"i_get_ws_dyn_mod: unknown class\n");
}

/* 
 * i_get_struct_dyn_mod(ws,class)
 * return the dynamic modification type of the given class
 */
Pdyn_mod
i_get_struct_dyn_mod(ws,class)
	Pint ws;
	char *class;
{
	Pdyns_structs structmods;
	Pint err;
        Pint wstype;
        Pconnid cid;

	pinq_ws_conn_type(ws,BUFSIZE,&err,&cid,&wstype);
        if (err) 
		tabort("ERROR: i_get_struct_dyn_mod: %d in pinq_ws_conn_type\n",err);
	pinq_dyns_structs(wstype,&err,&structmods);
        if (err) 
		tabort("ERROR: i_get_struct_dyn_mod: %d in pinq_dyns_structs\n",err);
	if (eqstring(class,"post structure"))
		return(structmods.post);
	if (eqstring(class,"unpost structure"))
		return(structmods.unpost);
	if (eqstring(class,"structure content modification"))
		return(structmods.content);
	if (eqstring(class,"reference modification"))
		return(structmods.ref);
	if (eqstring(class,"delete structure"))
		return(structmods.del);
	else
		tvprintf(0,"i_get_struct_dyn_mod: unknown class\n");
}

/* 
 * i_bogus_error()
 * return a bogus value -1234
 */
int
i_bogus_error()
{
	return(-1234);
}

/*
 * i_check_line3(display,window,ws,viewind,line,dim,col)
 * check the existence of a line of the specified colour by sampling pixels 
 * at the end points and the middle of the line after view and ws transformation
 * return value 
 *	      = 1, if found 
 *            = 0, if not found
 */
int
i_check_line3(display,window,ws,viewind,line,dim,col)
	Display *display;	/* X display */
	Window window;		/* X window */
	Pint ws; 		/* workstation id */
	Pint viewind;		/* view index */
	Ppoint3 *line;		/* line in wc 3D */
	int dim;		/* dimension of square area to be examined */
	Pint col;		/* colour index */
{
	Ppoint3 midpt;

	midpt.x = (line[0].x + line[1].x) /2;
	midpt.y = (line[0].y + line[1].y) /2;
	midpt.z = (line[0].z + line[1].z) /2;
	if ( i_check_pixel3(display,window,ws,viewind,line[0],dim,col) &&
	     i_check_pixel3(display,window,ws,viewind,line[1],dim,col) &&
	     i_check_pixel3(display,window,ws,viewind,midpt,dim,col) )
		return(1);
	else
		return(0);
}

/*
 * i_check_pixel3(display,window,ws,viewind,wcpt,dim,col)
 * check the existence of the any pixel of the specifed colour within 
 * the bounding box after view and ws transformation
 * return value 
 *	      = 1, if found 
 *            = 0, if not found 
 */
int
i_check_pixel3(display,window,ws,viewind,wcpt,dim,col)
	Display *display;	/* X display */
	Window window;		/* X window */
	Pint ws; 		/* workstation id */
	Pint viewind;		/* view index */
	Ppoint3 wcpt;		/* wc point 3D */
	Pint dim;		/* dimension of square area to be examined */
	Pint col;		/* colour index */
{
	int pcptx,pcpty;
	Ppoint3 ndcpt;
	int x,y,i,j,err;
	int found;
	Unsign8 *pp,*pixbuf;
	Unsign8 cmaptbl[MAXCOLOR][4];
	Unsign8 r,g,b;
	Colormap cmap;
	int offdisplay;
	Unsign8 colr,colg,colb;
	Pcolr_rep rep;
	int bits_per_rgb;
	XWindowAttributes attr;


	found = 0;
	for (i=0;i<MAXCOLOR;++i)
		cmaptbl[i][3] = 0;

	/* apply view xform */
    	i_viewxform_point3(ws,viewind,wcpt,&ndcpt);

	/* apply workstation xform */
    	i_wsxform_point3(display,window,ws,ndcpt,&pcptx,&pcpty,&offdisplay);
	if (offdisplay) { /* pixel is off display */
		return(0);
	}

    	x = (Pint) (pcptx - (dim >> 1));
    	y = (Pint) (pcpty - (dim >> 1));

	/* make sure the pixel grid is entirely inside the window*/
        if (!XGetWindowAttributes(display,window,&attr))
                tabort("ERROR: i_check_pixel3: in XGetWIndowAttributes, exiting...\n");
	if (x < 0) 
		x = 0;
	else if (x+dim >= attr.width) 
		x = attr.width - 1 - dim;
	if (y < 0) 
		y = 0;
	else if (y+dim >= attr.height) 
		y = attr.height - 1 - dim;

	/* retrieve pixels from xwindow */
	pp = pixbuf = i_get_pixel_array(display,window,x,y,dim,dim);
	cmap = i_get_window_cmap(display,window);
#ifdef INQ_COLR_REP_BUG
	printf("WARNING: test is faking pinq_colr_rep\n");
	switch (col) {
	case 1:
		rep.rgb.red = rep.rgb.green = rep.rgb.blue = 1.0;
		break;
	case 2:
		rep.rgb.red = 1.0;
		rep.rgb.green = rep.rgb.blue = 0.0;
		break;
	case 3:
		rep.rgb.green = 1.0;
		rep.rgb.red = rep.rgb.blue = 0.0;
		break;
	case 4:
		rep.rgb.blue = 1.0;
		rep.rgb.red = rep.rgb.green = 0.0;
		break;
	case 5:
		rep.rgb.red = rep.rgb.green = 1.0;
		rep.rgb.blue = 0.0;
		break;
	case 6:
		rep.rgb.green = rep.rgb.blue = 1.0;
		rep.rgb.red = 0.0;
		break;
	case 7:
		rep.rgb.red = rep.rgb.blue = 1.0;
		rep.rgb.green = 0.0;
		break;
	default: 
		puts("i_check_pixel3: unknown colour");
	}
#else
	pinq_colr_rep(ws,col,PINQ_REALIZED,&err,&rep);
	if (err)  
		tabort("ERROR: i_check_pixel3: %d in pinq_colr_rep, exiting...\n",err);
#endif
	colr = rep.rgb.red * SCALE_FACTOR + 0.5;
	colg = rep.rgb.green * SCALE_FACTOR + 0.5;
	colb = rep.rgb.blue * SCALE_FACTOR + 0.5;
	bits_per_rgb = i_get_bits_per_rgb(display);
	for (i=0;i<dim*dim;++i,++pp) {
		if (cmaptbl[(int)*pp][3] == 0) { /* new color */
			i_pixel_to_rgb(display,cmap,(unsigned long)*pp,
				bits_per_rgb,&r,&g,&b);
			cmaptbl[(int)*pp][0] = r;
			cmaptbl[(int)*pp][1] = g;
			cmaptbl[(int)*pp][2] = b;
			cmaptbl[(int)*pp][3] = 1;
		}
		if (SEQ(cmaptbl[(int)*pp][0],colr) &&
		    SEQ(cmaptbl[(int)*pp][1],colg) &&
		    SEQ(cmaptbl[(int)*pp][2],colb)) {
			found = 1;
			break;
		}
	}
	free(pixbuf);
	if (verbosity >= 3) {
		tvprintf(4, "i_check_pixel3: pcpt (%d,%d), pixel array: ",x,y);
		for (i=0;i<dim;++i) {
			printf("[");
			for (j=0;j<dim;++j)
				printf("%d ",pixbuf[dim*i + j]);
			printf("]");
		}
		puts("");
	}
	return(found);
}

/*
 * i_viewxform_point3(ws,viewind,wcpt,npcpt) 
 * transform a pt from wc to ndc, without view clipping
 */
void
i_viewxform_point3(ws,viewind,wcpt,npcpt,status) 
	Pint ws; 		/* workstation id */
	Pint viewind;		/* view index */
	Ppoint3 wcpt;		/* wc point 3D */
	Ppoint3 *npcpt;		/* OUT ndc point */
	int *status;		/* OUT status */
{
	int err;
	Pview_rep3 curviewrep,reqviewrep;
	Pupd_st upd;
	Ppoint3 vrcpt;		/* pt in view reference coordinate */

    	pinq_view_rep(ws, viewind, &err, &upd, &curviewrep, &reqviewrep);
	if (err)
		tabort("ERROR: i_viewxform_point3: %d in pinq_view_rep, exiting...\n",err);
	/* view orientation xform */
    	ptran_point3(&wcpt, curviewrep.ori_matrix, &err, &vrcpt);
	if (err)
		tabort("ERROR: i_viewxform_point3: %d in ptrans_point3, exiting...\n",err);

	/* view mapping xform */
    	ptran_point3(&vrcpt, curviewrep.map_matrix, &err, npcpt);
	if (err)
		tabort("ERROR: i_viewxform_point3: %d in ptranspt3, exiting\n",err);

	tvprintf(3,"i_viewxform_point3:wcpt(%.2f,%.2f,%.2f) npcpt(%.2f,%.2f,%.2f)\n",
		wcpt.x,wcpt.y,wcpt.z,npcpt->x,npcpt->y,npcpt->z);

}

/*
 * i_wsxform_point3(display,window,ws,npcpt,pcptx,pcpty,offdisplay) 
 * transform a pt from ndc to dc without ws clipping
 * OUT offdisplay = 1 if point in pixel coordinate is offdisplay
 *                = 0 otherwise
 */
void
i_wsxform_point3(display,window,ws,npcpt,pcptx,pcpty,offdisplay) 
	Display *display;	/* X display */
	Window window;		/* X window */
	Pint ws; 		/* workstation id */
	Ppoint3 npcpt;		/* wc point 3D */
	int *pcptx;		/* OUT x in pixel coordinate */
	int *pcpty;		/* OUT y in pixel coordinate */
	int *offdisplay;	/* OUT is pixel offdisplay? */
{
	int err;
	Pmatrix3 wstr;
	float mult;
	int i,j;
	int w,h;
	Plimit3 *winp,*vportp;
	Ppoint3 dcpt;
	Plimit3 cwin,rwin,cvport,rvport;
	Pupd_st updst;

	*offdisplay = 0;
        pinq_ws_tran3(ws, &err, &updst,&rwin,&cwin,&rvport,&cvport);
	if (err)
		tabort("ERROR: i_wsform_point3: %d in pinq_ws_tran3, exiting\n",err);

	/* figure out matrix for ws xform */
	vportp = &cvport;
	winp = &cwin;
    	mult = MINIMUM((vportp->x_max-vportp->x_min)/(winp->x_max-winp->x_min),
         (vportp->y_max-vportp->y_min)/(winp->y_max-winp->y_min));
    	for (i = 0; i < 4; i++)
        	for (j = 0; j < 4; j++)
            		wstr[i][j] = 0.0;
    	for (i = 0; i < 2; i++)
        	wstr[i][i] = mult;
    	if (feq (winp->z_min, winp->z_max))
            	wstr[2][2] = 0.0;
    	else
        	wstr[2][2] = (vportp->z_max-vportp->z_min) / 
			(winp->z_max - winp->z_min);
    	wstr[0][3] = vportp->x_min - mult * winp->x_min;
    	wstr[1][3] = vportp->y_min - mult * winp->y_min;
    	wstr[2][3] = vportp->z_min - wstr[2][2] * winp->z_min;
    	wstr[3][3] = 1.0;

	/* apply ws xform */
    	ptran_point3(&npcpt, wstr, &err, &dcpt); 
	if (err)
		tabort("ERROR: i_wsform_point3: %d in ptranspt3, exiting...\n",err);

	/* convert dc (device coordinate) to pc (pixel coordinate) */
 	i_get_window_dim(display,window,&w,&h);
    	*pcptx = dcpt.x;
    	*pcpty = h - dcpt.y;
	if (fgt (*pcptx, w-1) || flt (*pcptx,0) ||
	    fgt (*pcpty, h-1) || flt (*pcpty,0) ) {
		tvprintf(3,"i_wsxform_point3:this point is off display\n");
		*offdisplay = 1;
	}
	tvprintf(3,"i_wsxform_point3:npcpt(%.2f,%.2f,%.2f) dcpt(%.2f,%.2f,%.2f) pcpt(%d,%d)\n",
		npcpt.x,npcpt.y,npcpt.z,dcpt.x,dcpt.y,dcpt.z,*pcptx,*pcpty);
}
 
/*
 * i_get_window_dim(display,window,w,h) retrieve window's dimension
 */
void
i_get_window_dim(display,window,w,h)
	Display *display;	/* X display */
	Window window;		/* X window */
	int *w; 		/* width */
	int *h; 		/* height */
{
        /* Return the colormap of the window */
        XWindowAttributes attr;

        if (!XGetWindowAttributes(display,window,&attr))
		tabort("ERROR: i_get_window_dim: in XGetWindowAttributes, exiting\n");
	*w = attr.width;
	*h = attr.height;
}


/*
 * i_get_ws_type(string) 
 * returns a Pint variable according to the input string
 */

Pint 
i_get_ws_type(string)
	char *string;
{
	if (eqstring(string,"phigs_ws_type_x_tool"))
		return(phigs_ws_type_x_tool);
	else if (eqstring(string,"phigs_ws_type_x_drawable"))
		return(phigs_ws_type_x_drawable);
	else
		tvprintf(0,"i_get_ws_type: unknown type\n");
}

/*
 * i_make_xwindow(display,window,conn,x,y,w,h) 
 * creates a X window origin at (x,y) with dimension (w,h)
 * it opens a X display if for the first time and initialize
 * the PHIGS connection id
 */
void
i_make_xwindow(display,window,conn,x,y,w,h)
	Display **display;
	Window *window;
	Pconnid_x_drawable *conn;
	int x,y,w,h;
{
	Visual visual;
        XSetWindowAttributes xswa;
	XEvent exposureEvent;
	static firsttime = 1;
	static Visual *vis;
	XSizeHints wmhint;
	int status;

	if (firsttime) { /* call XOpenDisplay only the first time */ 
			 /* this function is called */
		firsttime = 0;
		*display = XOpenDisplay("");
		if (!*display)
			tabort("ERROR: i_make_xwindow: in XOpenDisplay, exiting...\n");
        	vis = DefaultVisual(*display,DefaultScreen(*display));
        	if (vis->class != PseudoColor)
                	tabort("ERROR: i_make_xwindow: inpex currently supports only PSEUDOCOLOR, exiting...\n");
	}

	x += winxoffset;
	y += winyoffset;
        xswa.backing_store = NotUseful;
        xswa.event_mask = ExposureMask | StructureNotifyMask;
        xswa.background_pixel = BlackPixel(*display, DefaultScreen(*display));
        xswa.border_pixel = WhitePixel(*display, DefaultScreen(*display));
        visual.visualid = vis->visualid;
        *window = XCreateWindow(*display,RootWindow(*display,DefaultScreen(*display)),
                x, y, w, h, 1,
                DefaultDepth(*display, DefaultScreen(*display)),InputOutput, 
		&visual,CWEventMask|CWBackingStore|CWBorderPixel|CWBackPixel, 
		&xswa);
	if (!*window)
		tabort("ERROR: i_make_xwindow: in XCreateWindow, exiting...\n");
	wmhint.x = x;
	wmhint.y = y;
	wmhint.width = w;
	wmhint.height = h;
	wmhint.flags = PPosition | PSize;
	XSetStandardProperties(*display,*window,"inspex","inspex",None,NULL,0,
		&wmhint);
	XMapWindow(*display,*window);
        XSync(*display,0);
        XWindowEvent(*display, *window, ExposureMask, &exposureEvent);
	conn->display = *display;
	conn->drawable_id = *window;
}

/*
 * i_print_var(type,va_alist)  prints the value of a PHIGS variable
 */

void
i_print_var(type,va_alist) 
	char *type;
	va_dcl
{ 
        int i,j;
	va_list ap;
	Pmatrix3 *vmatrix3;
	Pmatrix *vmatrix;
	Ppoint3 vpoint3;
	Ppoint vpoint;
	Pint_list vintlst;
	Plimit vlimit;
	Plimit3 vlimit3;

	printf("%s:",type);
	va_start(ap);
	if (eqstring(type,"Pmatrix")) {
		vmatrix = va_arg(ap,Pmatrix*);
        	for (i=0;i<3;++i){
                	for (j=0;j<3;++j)
                        	printf("%.2f ",(*vmatrix)[i][j]);
                	puts("");
        	}
	} else if (eqstring(type,"Pmatrix3")) {
		vmatrix3 = va_arg(ap,Pmatrix3*);
        	for (i=0;i<4;++i){
                	for (j=0;j<4;++j)
                        	printf("%.2f ",(*vmatrix3)[i][j]);
                	puts("");
        	}
	} else if (eqstring(type,"Ppoint3")) {
		vpoint3 = va_arg(ap,Ppoint3);
		printf("(%.4f,%.4f,%.4f)\n",vpoint3.x,vpoint3.y,vpoint3.z);
	} else if (eqstring(type,"Ppoint")) {
		vpoint = va_arg(ap,Ppoint);
		printf("(%.4f,%.4f)\n",vpoint.x,vpoint.y);
	} else if (eqstring(type,"Pint_list")) {
		vintlst = va_arg(ap,Pint_list);
		printf("number: %d, list: ",vintlst.num_ints);
		for (i=0;i<vintlst.num_ints;++i)
			printf("%d ",vintlst.ints[i]);
		puts("");
	} else if (eqstring(type,"Plimit3")) {
		vlimit3 = va_arg(ap,Plimit3);
		printf("(%.2f,%.2f,%.2f,%.2f,%.2f,%.2f)\n",
		vlimit3.x_min,vlimit3.x_max,vlimit3.y_min,vlimit3.y_max,
		vlimit3.z_min,vlimit3.z_max);
	} else if (eqstring(type,"Plimit")) {
		vlimit = va_arg(ap,Plimit);
		printf("(%.2f,%.2f,%.2f,%.2f)\n",
		vlimit.x_min,vlimit.x_max,vlimit.y_min,vlimit.y_max);
	} else
		puts("i_print_var: invalid type");
	va_end(ap);
}

/*
 * i_pause() pause while until user hit return to continue execution
 */
void 
i_pause()
{
	if (pausebetweenframe) {
		printf("hit return to continue...");
		getchar();
	}
}


/*
 * i_is_posted_struct(ws,struct,&priority) - inquires the
 * posted structures of workstation ws, and sees whether struct
 * is among them.  If so, set priority to its priority and return 1.
 * Otherwise, return 0.
 */
int
i_is_posted_struct(ws, struct_id, priority)
    Pint ws;
    Pint struct_id;
    Pfloat *priority;		/* OUT: priority if struct_id is posted */
{
    Pposted_struct_list postlst;	/* structure for returned list of structures */
    Pint length;		/* length of the list */
    Pint error;
    Pint i, length2;

    error = i_bogus_error();

    /* get the length of the list of posted structures */
    pinq_posted_structs(ws, 0, 0, &error, &postlst, &length);
    if (error) 
	tabort("ERROR: pinq_posted_structs w/ length 0 returned error %d\n", 
	       error);
    
    /* allocate space for the list */
    postlst.postings = (Pposted_struct *) malloc(length * sizeof(Pposted_struct));

    /* inquire the actual list of structures, check for consistency */
    pinq_posted_structs(ws, length, 0, &error, &postlst, &length2);
    if (error) 
	tabort("ERROR: pinq_posted_structs w/ length %d returned error %d\n", 
	       length, error);
    if (length != length2)
	tfprintf("failed: two inquired lengths (%d, %d) don't match\n",
		 length, length2);
    if (length != postlst.num_postings)
	tfprintf("failed: inquired length %d != length %d in postlst struct\n",
		 length, postlst.num_postings);

    /* search for the given structure ID */
    for (i=0; i<postlst.num_postings; i++) {
	if (postlst.postings[i].id == struct_id) {
	    *priority = postlst.postings[i].disp_pri;
	    return (1);
	}
    }

    /* if we got this far, we didn't find the posted structure */
    return (0);
}





#ifdef NEWT

/*
 * _tfprintf(fmt,va_alist) prints out msg, incs fail
 */
void
_tfprintf(fmt, va_alist)
    char           *fmt;        /* message fmt */
    va_dcl                      /* variable data */
{
    va_list         ap;
    
    va_start(ap);
    printf("%s: ",testname);
    _printf(fmt, ap);
    va_end(ap);

    if (++numfail >= maxfail) {
        printf("%s: Exiting, too many failures (%d).\n",testname,numfail);
	tendtest();
        exit(1); 
    }
}

/*
 * _tvprintf(ver,fmt,va_alist) prints out message according to given verbosity
 */
void
_tvprintf(ver, fmt, va_alist)
    int             ver;        /* current verbosity */
    char           *fmt;        /* message fmt */
    va_dcl                          /* variable data */
{
    va_list         ap;

    /* print out message if VERBOSITY >= this message's verbosity */
    if (ver <= verbosity) {
        va_start(ap);
        printf("%s: ",testname);
        _printf(fmt, ap);
        va_end(ap);
    }
}

/*
 * _tabort(fmt,va_alist) prints out message and abort test
 */
void
_tabort(fmt, va_alist)
    char           *fmt;        /* message fmt */
    va_dcl                          /* variable data */
{
    va_list         ap;

    va_start(ap);
    printf("%s: ",testname);
    _printf(fmt, ap);
    va_end(ap);
    ++numfail;
    tendtest();
    exit(1);
}


#endif
