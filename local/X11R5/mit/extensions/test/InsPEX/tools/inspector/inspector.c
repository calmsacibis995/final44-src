/* $XConsortium: inspector.c,v 5.2 91/05/29 18:13:57 hersh Exp $ */

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
 * inspector.c - Image comparison tool for Inspex
 * 
 * System and library calls used (should be common to SysV and 4.2BSD):
 * printf(), fprintf(), system(),
 * opendir(), readdir()
 */

#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include "X11/Xlib.h"
#include "X11/Xutil.h"
#include "X11/Xatom.h"
#ifdef ATHENA
#include "toolkitaw.h"
#else
#include "toolkit.h"
#endif
#include "imagelib.h"

#define DEBUG
#ifdef DEBUG
#define DebugSync(display) XSync(display,0)
#else
#define DebugSync(display)
#endif

char *getenv();

/* dimensions of various window components */
#define IMAGE_SIZE 400
#define IMAGE_WIDTH IMAGE_SIZE
#define IMAGE_HEIGHT IMAGE_SIZE
#define CONTROL_WIDTH 160
#define IMAGE_LABEL_HEIGHT 30

#define MAX_FILENAME_LEN 20 	/* max length of image file base name */
#define MAX_IMAGE_TEXT_LEN 64	/* max len of text description in image file*/


/* 
 * Xlib stuff
 */
GC	    gc;
Display	    *display;
Window      ref_win, curr_win, main_win_xid;
Window	    ref_pseudowin, curr_pseudowin;
XVisualInfo visinfo;
int	    screen;
I_image	    ref_image, curr_image, refdiff_image, currdiff_image;
I_cmap	    ref_cmap, curr_cmap;

/* 
 * toolkit stuff 
 */
TK_Main_Window	    main_win;
TK_Control_Window   control_win, reflabel_win;
TK_Message_Item	    filename_item, status_item, reflabel_item, descr_item;
TK_Button	    accept_button, reject_button, unseen_button,
		    diffs_button, load_button, quit_button;
TK_List		    file_list;

/*
 * parameters of images being displayed (reference and current)
 */
unsigned short rw, rh, rncol,   /* width, height, # of columns */
    cw, ch, cncol;
unsigned long rblack, cblack;	/* black pixel */


/* 
 * Advance declaration of event handling routines and other functions
 */
void
    ref_win_repaint_proc(),
    curr_win_repaint_proc(),
    accept_notify(),
    reject_notify(),
    unseen_notify(),
    diffs_notify(),
    load_notify(),
    quit_notify();
int list_notify();
void get_directory_info();


char	filename_string[48],	/* image file name output string */    
	status_string[48],	/* status output string */
	reference_string[256];	/* reference path output string */
char	*ref_file;		/* pathname of reference image */

int	currfile_index=0;	/* index in list of current file */
char	*currfile_name=NULL;	/* name of current file (from list) */

char	*currdir_name,		/* names of current, reference image dirs*/
	*refdir_name,
	*localrefdir_name;

char	buff[128];		/* general usage string buffer */
int	err;			/* for return of error values */

int	diff_mode = 0;		/* true iff image differences are displayed */
int	diff_calculated = 0;	/* true iff differences have been computed */
int	twocmapused;		/* true iff two images can be loaded into */
				/* one color map */
FILE	*logfile = stdout;


/*
 * main() - create two X drawables and the control panel, 
 * read the image directory, and pass control
 * to event handling loop.
 */
main(argc,argv)
int	argc;
char	*argv[];
{
    Window subwins[2];
    XSetWindowAttributes winattr;
    XSizeHints hints;
    XWMHints wmhints;
    Atom atom;

    /* 
     * set up the windows: main window, image label window, 
     * control panel window.
     */
    tk_init(argc,argv);
    main_win = tk_create_main_window("comparison tool", 
		IMAGE_HEIGHT+IMAGE_LABEL_HEIGHT+2,
		2*IMAGE_WIDTH+CONTROL_WIDTH+4, &display);
   reflabel_win = tk_create_control_window(main_win,
		0, IMAGE_HEIGHT+2,
		IMAGE_LABEL_HEIGHT, 2*IMAGE_WIDTH+CONTROL_WIDTH+2);
    control_win = tk_create_control_window(main_win,
		2*IMAGE_WIDTH+4, 0,
		IMAGE_HEIGHT, CONTROL_WIDTH);

    /*
     * create the control devices
     */
    filename_item = tk_create_message_item(control_win, 1, 1,
		"no image file loaded");    
    status_item = tk_create_message_item(control_win, 2, 1, " ");    
    accept_button = tk_create_button(control_win, 3, 1, "accept", accept_notify,
	    TK_BUTTON_INACTIVE);
    reject_button = tk_create_button(control_win, 3, -1, "reject", reject_notify,
	    TK_BUTTON_INACTIVE);
    unseen_button = tk_create_button(control_win, 4, 1, "mark unseen", 
	    unseen_notify, TK_BUTTON_INACTIVE);
    diffs_button =  tk_create_button(control_win, 5, 1, "show diffs", diffs_notify,
	    TK_BUTTON_INACTIVE);
    load_button = tk_create_button(control_win, 6, 1, "load", load_notify,
	    TK_BUTTON_ACTIVE);
    quit_button = tk_create_button(control_win, 6, -1, "quit", quit_notify,
	    TK_BUTTON_ACTIVE);
    file_list = tk_create_list(control_win,7,1,list_notify);
    reflabel_item = tk_create_message_item(reflabel_win, -1, 1,
		"reference file: none");
    descr_item = tk_create_message_item(reflabel_win, -1, 60, " ");

    /*
     * extract information about image directories
     */
    get_directory_info();

    /* 
     * get PseudoColor visual information, create pseudocolor
     * windows for image display
     */
    screen = DefaultScreen(display);
    if (!XMatchVisualInfo(display, screen, DefaultDepth(display,screen),
	PseudoColor, &visinfo)) {
	    fatal("couldn't match PseudoColor Visual info\n");
    }
    main_win_xid = tk_get_xid(main_win);
    winattr.colormap = 
	    XCreateColormap(display,main_win_xid,visinfo.visual,AllocNone);
    winattr.background_pixel = WhitePixel(display,screen);
    if (getenv("INS_MULTIWIN")) {
	/* image windows are separate X windows */
	ref_win = XCreateWindow(display, 
			DefaultRootWindow(display),
			0, 0, IMAGE_WIDTH, IMAGE_HEIGHT, 
			1, DefaultDepth(display,screen), InputOutput, 
			visinfo.visual, CWColormap|CWBackPixel, &winattr);
	/* inform window manager of name and geometry */
	XStoreName(display, ref_win, "Reference Image");
	hints.x = 50; hints.y = 50;
	hints.width = IMAGE_WIDTH; hints.height = IMAGE_HEIGHT;
	hints.min_width = IMAGE_WIDTH/2; hints.min_height = IMAGE_HEIGHT/2;
	hints.flags = PPosition | PSize | PMinSize;
	XSetNormalHints(display, ref_win, &hints);
	curr_win = XCreateWindow(display, 
			 DefaultRootWindow(display),
			 IMAGE_WIDTH+10, 0, IMAGE_WIDTH, IMAGE_HEIGHT, 
			 1, DefaultDepth(display,screen), InputOutput, 
			 visinfo.visual, CWColormap|CWBackPixel, &winattr);
	XStoreName(display, curr_win, "Current Image");
	hints.x += IMAGE_WIDTH+10;
	XSetNormalHints(display, curr_win, &hints);
	/* inform window manager that these windows are a group */
	wmhints.window_group = main_win_xid;
	wmhints.flags = WindowGroupHint;
	XSetWMHints(display, main_win_xid, &wmhints);
	XSetWMHints(display, ref_win, &wmhints);
	XSetWMHints(display, curr_win, &wmhints);
    } else {
	/* create the windows as subwindows of main win */
	ref_win = XCreateWindow(display, main_win_xid,
			0, 0, IMAGE_WIDTH, IMAGE_HEIGHT, 
			1, DefaultDepth(display,screen), InputOutput, 
			visinfo.visual, CWColormap|CWBackPixel, &winattr);
	curr_win = XCreateWindow(display, main_win_xid, 
			 IMAGE_WIDTH+2, 0, IMAGE_WIDTH, IMAGE_HEIGHT, 
			 1, DefaultDepth(display,screen), InputOutput, 
			 visinfo.visual, CWColormap|CWBackPixel, &winattr);
	/*
	 * Set WM_COLORMAP_WINDOWS property so that window manager
	 * will install the cmaps of these subwindows.  (see ICCCM,
	 * sect. 4.1.8 on client colormaps)
	 */
	atom = XInternAtom(display,"WM_COLORMAP_WINDOWS", False);
	subwins[0] = ref_win;
	subwins[1] = curr_win;
	XChangeProperty(display, main_win_xid, atom, XA_WINDOW, 32,
			PropModePrepend, subwins, 2);
    }


    XMapRaised(display,ref_win);
    XMapRaised(display, curr_win);

    /*
     * Start the main loop
     */

    tk_main_loop(main_win);

    return 0;
}



/*
 * get_directory_info() - extract pathnames of the 3 image directories
 * from environment variables, confirm that they exist.  Read filenames
 * from current images directory into the toolkit file list.
 */
static void
get_directory_info()
{
    int i, len;
    struct dirent *dir_entry;	/* for directory reading */
    DIR	    *dirp;
    char *inspexhome,		/* from environment variables */
	*inspexdest, 
	*inspeximageref;
    static char *refimages = "/refimages";  /* names of image subdirs */
    static char *localrefimages = "/localrefimages";
    static char *currimages = "/currimages";

    /* the main reference directory */
    if ((inspeximageref = getenv("INSPEXIMAGEREF")) == NULL) {
	if ((inspexhome = getenv("INSPEXHOME")) == NULL) {
	    fatal("must set environment var INSPEXHOME or INSPEXIMAGEREF\n");
	} else {
	    refdir_name =
		(char*)malloc(strlen(inspexhome)+strlen(refimages)+2);
	    sprintf(refdir_name, "%s%s", inspexhome, refimages);
	}
    } else {
	refdir_name = inspeximageref;
    }
    if ((dirp = opendir(refdir_name)) == NULL) {
	fprintf(stderr, "Error - couldn't open reference image directory %s\n",
		refdir_name);
	exit(1);
    } 
    closedir(dirp);

    /* the local image reference directory */
    if((inspexdest = getenv("INSPEXDEST")) == NULL) {
	fatal("must set environment variable INSPEXDEST\n");
    } else {
	localrefdir_name = 
	    (char*)malloc(strlen(inspexdest)+strlen(localrefimages)+1);
	strcpy(localrefdir_name,inspexdest);
	strcat(localrefdir_name,localrefimages);
    }
    if ((dirp = opendir(localrefdir_name)) == NULL) {
	fprintf(stderr, "Error - couldn't open local reference image dir %s\n",
		localrefdir_name);
	exit(1);
    } 
    closedir(dirp);

    /* The current images directory */
    currdir_name = (char*)malloc(strlen(inspexdest)+strlen(currimages)+1);
    strcpy(currdir_name,inspexdest);
    strcat(currdir_name, currimages);
    if ((dirp = opendir(currdir_name)) == NULL) {
	fprintf(stderr, "Error - couldn't open current image directory %s\n",
		currdir_name);
	exit(1);	
    }

    /* read directory entries into the toolkit file list */
    for (dir_entry=readdir(dirp), i=0; dir_entry!=NULL; dir_entry=readdir(dirp)) {
	if ((len=strlen(dir_entry->d_name)) > 2 && len < 20) { 
	    tk_insert_list_item(file_list,i++,dir_entry->d_name);
	}
    }
    closedir(dirp);
   
}

/*
 *
 * event-handling functions
 *
 */

/*
 * accept_notify() - attached to "accept" button.  Accept the current
 * image by moving it to the local reference image directory.
 */
void
accept_notify()
{
    static char none[] = "file: none";
    static char empty[] = " ";
    int result;

    /* Accept file by moving to local reference directory  */
    fprintf(logfile, "Accepted file %s\n", currfile_name);
    sprintf(buff, "mv %s/%s %s/%s", currdir_name, currfile_name,
	    localrefdir_name, currfile_name);
    if (is_rejected(currfile_name)) {
	/* remove rejection marker */
	buff[strlen(buff)-1] = '\0';
    }
    result = system(buff);
    if (result) {
	fprintf("error - couldn't execute command: %s\n", buff);
	exit (1);
    }

    tk_delete_list_item(file_list,currfile_index);
    tk_set_message(filename_item, none);    
    tk_set_message(status_item, empty);

    /* after acceptance, there is no current file */
    currfile_name = NULL;
    tk_set_message(reflabel_item, "reference file: none");
    tk_set_message(descr_item, " ");
    tk_deactivate_button(accept_button);
    tk_deactivate_button(reject_button);
    tk_deactivate_button(unseen_button);
    tk_deactivate_button(diffs_button);
    ref_win_repaint_proc();
    curr_win_repaint_proc();
}

void
reject_notify()
{
    int result;
    static char newname[MAX_FILENAME_LEN];

    if (!is_rejected(currfile_name)) { 
	/* reject by adding "-" to filename */
        sprintf(newname, "%s-", currfile_name);

	sprintf(buff, "mv %s/%s %s/%s", currdir_name, currfile_name,
		currdir_name, newname);
	result = system(buff);
	if (result) {
	    fprintf(stderr, "error: couldn't execute command: %s\n", buff);
	    exit (1);
	}
	fprintf(logfile, "Rejected file %s\n", currfile_name);
	tk_set_list_item(file_list,currfile_index,newname);
	currfile_name = tk_get_list_item(file_list,currfile_index);
	tk_set_message(status_item, "Status: Rejected");
    }
    tk_deactivate_button(reject_button);
    tk_activate_button(unseen_button);
}

/*
 * unseen_notify() - attached to "mark unseen" button.  Marks
 * current file as unseen.
 */
void
unseen_notify()
{
    char *newname;
    int result;

    if (is_rejected(currfile_name)) {
	/* change the filename to un-rejected version, removing trailing "-" */
	newname = (char*)malloc(sizeof(currfile_name)+1);
	strcpy(newname,currfile_name);
	newname[strlen(currfile_name)-1] = '\0';

	sprintf(buff, "mv %s/%s %s/%s", currdir_name, currfile_name,
		currdir_name, newname);
	result = system(buff);
	if (result) {
	    fprintf(stderr, "error: couldn't execute command %s\n", buff);
	    exit (1);
	}

	fprintf(logfile, "Marked file %s unseen\n", currfile_name);
	tk_set_list_item(file_list,currfile_index,newname);
	currfile_name = tk_get_list_item(file_list,currfile_index);
	tk_set_message(status_item, "Status: Unseen");
    }
    tk_activate_button(reject_button);
    tk_deactivate_button(unseen_button);
}

/*
 * diffs_notify() -- attached to diffs button.  Toggles between diffs
 * mode, in which difference images are displayed in the two 
 * windows, and normal mode, in which the stored images themselves
 * are displayed.
 */
void
diffs_notify()
{
    if (!diff_mode) {
	/* set up diff mode - calculate images if necessary */
	if (!diff_calculated) {
	    if (twocmapused) {
		i_diff_image(display, &ref_cmap, &curr_cmap, &ref_image, 
		    &curr_image, &refdiff_image, &currdiff_image, &err);
	    } else {
		/* they share one color map */
		i_diff_image(display, &curr_cmap, &curr_cmap, &ref_image, 
		    &curr_image, &refdiff_image, &currdiff_image, &err);
	    }
	    if (err) {
	        fprintf(stderr, "Error - could not calculate differences\n");
		diff_calculated = 0;
		tk_deactivate_button(diffs_button);
	    } else {
		diff_calculated = 1;		
	    }

	}
	/* only set diff_mode flag if diff calculation has worked */
	if (diff_calculated) {
	    diff_mode = 1;
	    tk_set_button_label(diffs_button, "show normal");
	}
    } else {
	/* restore normal mode */
	tk_set_button_label(diffs_button, "show diffs");
	diff_mode = 0;
    }
    ref_win_repaint_proc();
    curr_win_repaint_proc();
    /* Synchronize so that button stays grayed until images shown,
     * to avoid user frustration
     */
    XSync(display); 
}

/*
 * load_notify() - attached to "load" button.  Load the image
 * file currently selected, and the corresponding reference image
 * if it exists.  Enable buttons appropriately.
 */
void
load_notify()
{
    XSetWindowAttributes winattr;
    static char rtext[MAX_IMAGE_TEXT_LEN], *ctext;  /* textual image descr. */
    static char descr_string[MAX_IMAGE_TEXT_LEN+24] = "image description: ";

    ctext = descr_string + strlen("image description: ");
    
    if (currfile_name != NULL) {
	/* dispose of memory for images now displayed */
	i_free_image(&curr_image);
	i_free_cmap(display, &curr_cmap);
	if (ref_file != NULL) {
	    i_free_image(&ref_image);
	    if (twocmapused) i_free_cmap(display, &ref_cmap);
	    if (diff_calculated) {
		i_free_image(&refdiff_image);
		i_free_image(&currdiff_image);
	    }
	}
    }
    /* get full path name of current image  */
    currfile_name = tk_get_selected_list_item(file_list, &currfile_index);
    sprintf(buff, "%s/%s", currdir_name, currfile_name);

    DebugSync(display);

    /* pathname of reference image will be placed directly into message buf */
    strcpy(reference_string, "reference image: ");
    ref_file = reference_string + strlen(reference_string);

    /* find appropriate reference image file and load the images */
    if (find_reference(currfile_name, ref_file)) {
	i_load_image2(buff, ref_file, display,visinfo.visual, 
	    &curr_image, &ref_image, &curr_cmap, &ref_cmap,
	     ctext, rtext, &twocmapused, &err);
	DebugSync(display);
    } else {
	/* no reference image found */
	strcpy(ref_file, "none");
	ref_file = NULL;
	i_load_image(buff,display,visinfo.visual, &curr_image, &curr_cmap, 
	    ctext, &err);
    }
    if (err) {
	fprintf(stderr, "Error - could not load image file(s)\n");
	return;
    }

    /* display image name & status, enable unseen or reject button */
    sprintf(filename_string,"file: %s", currfile_name);
    tk_set_message(filename_item, filename_string);
    tk_set_message(descr_item, descr_string);
    if (is_rejected(currfile_name)) {
	tk_set_message(status_item, "Status: rejected");
	tk_activate_button(unseen_button);
	tk_deactivate_button(reject_button);
    } else {
	tk_set_message(status_item, "Status: unseen");
	tk_activate_button(reject_button);
	tk_deactivate_button(accept_button);
    }

    /* update button status and flags */
    if (diff_mode) {
	tk_set_button_label(diffs_button, "show diffs");
	diff_mode = 0;
    }
    diff_calculated = 0;
    tk_activate_button(accept_button);
    if (ref_file != NULL) {
	tk_activate_button(diffs_button);
    }
    tk_set_message(reflabel_item, reference_string);

    /* if image windows are separate X windows, raise them */
    if (getenv("INS_MULTIWIN")) {
	XRaiseWindow(display, ref_win);
	XRaiseWindow(display, curr_win);
    }
    /*  update color maps & background pixels and redraw windows */
    winattr.colormap = curr_cmap.cmap;
    winattr.background_pixel = curr_cmap.blackpixel;
    XChangeWindowAttributes(display, curr_win, 
		CWColormap|CWBackPixel, &winattr);
    if (ref_file != NULL && twocmapused) {
	    winattr.colormap = ref_cmap.cmap;
            winattr.background_pixel = ref_cmap.blackpixel;
	}
    /* change ref window's attributes even if no reference image, */
    /* since its old cmap may have been destroyed */
    XChangeWindowAttributes(display, ref_win, 
		CWColormap|CWBackPixel, &winattr);
    ref_win_repaint_proc();
    curr_win_repaint_proc();
}

/*
 * list_notify() - XView doesn't seem to call this - bug?
 */
int
list_notify()
{
/*    printf("list notify procedure called! (didn't work before)\n");
*/
    return (1);
}

/*
 * quit_notify() -- attached to quit button - quits!
 */
void
quit_notify()
{
    if (currfile_name != NULL) {
	/* dispose of memory for images now displayed */
	i_free_image(&curr_image);
	i_free_cmap(display, &curr_cmap);
	if (ref_file != NULL) {
	    i_free_image(&ref_image);
	    if (twocmapused) i_free_cmap(display, &ref_cmap);
	    if (diff_calculated) {
		i_free_image(&refdiff_image);
		i_free_image(&currdiff_image);
	    }
	}
    }

    exit(0);
}

/*
 * ref_win_repaint_proc() - repaint the reference window.
 * if there is a reference image, draw either it or the the 
 * appropriate difference image, depending on the value of
 * diff_mode.
 */
void
ref_win_repaint_proc()
{
    XClearWindow(display, ref_win);
    if (currfile_name != NULL && ref_file != NULL) {
	if (diff_mode) {
	    i_display_image(display, ref_win, &refdiff_image);
	} else { 
	    i_display_image(display, ref_win, &ref_image);
	}
	DebugSync(display);
    }
}

/*
 * curr_win_repaint_proc() - repaint the current image window.
 * If there is a current image, draw either it or the appropriate
 * difference image, depending on diff_mode.
 */
void
curr_win_repaint_proc()
{
    XClearWindow(display, curr_win);
    if (currfile_name != NULL) {
	if (diff_mode) {
	    i_display_image(display, curr_win, &currdiff_image);
	} else  {
	    i_display_image(display, curr_win, &curr_image);
	}
	DebugSync(display);
    }
}


/* 
 * is_rejected - return true iff the named file is marked as rejected
 */
static int
is_rejected(name)
    char *name;
{
    return (name[strlen(name)-1] == '-');
}

/*
 * find_reference(image, pathout) - if a reference image for "image"
 * is found, copy the whole path into pathout and return true.
 * Otherwise, return false.
 */
static int
find_reference(imagename, pathout)
    char *imagename, *pathout;
{
    int fd;

    sprintf(pathout, "%s/%s", localrefdir_name, imagename);
    if (is_rejected(imagename)) {
	/* reference file won't have rejection marker */
	pathout[strlen(pathout)-1] = '\0';
    }
    if ((fd = open(pathout, O_RDONLY)) != -1) {
	/* file exists */
	close(fd);
	return (1);
    } 
    /* if we got here, it isn't in local reference -- look in main ref */
    sprintf(pathout, "%s/%s", refdir_name, imagename);
    if (is_rejected(imagename)) {
	/* reference file won't have rejection marker */
	pathout[strlen(pathout)-1] = '\0';
    }
    if ((fd = open(pathout, O_RDONLY)) != -1) {
	/* file exists */
	close(fd);
	return (1);
    }
    /* if we got this far, reference image not found in either place */
    return (0);

}

static int
fatal(msg) 
    char *msg;
{
    fprintf(stderr, "inspector error: %s", msg);
    exit(1);
}
