#include "dsun.tool.hs_h"
#include <sys/errno.h>
extern int offset;
extern int new_page;
extern int output;
extern int total_pages;
extern struct pixwin * dsun_pw;
extern short *olist;
extern int nolist;
extern FILE * fp;
extern int keyboard;
extern int currpage;
extern int errno;

extern int top_verbose;

#define NOPAGES 300
#define beep    putc('\007', stderr)

extern struct tool * tool;

handle_input(proc_num, dis_num)
int proc_num;
int dis_num;
{
	int i = 1;
	register short *ptr;		/* used to clear extra page buffer */
	register int pagenum = -1;	/* in use: -1 means no random access */
	register char character;	/* character read in from user */
	struct inputevent event;	/* tty_sub_window input event holder */


	    do {	/*   the next page if user hits spaces */
				/* get a character from window system */

		if (input_readevent(keyboard, &event)) {
		    perror("dsun");
		    leave(1);
		}
		character = event.ie_code;	/* character now has input */

		if (character == ' ') {
		    if (i > 0)
			character = 'u';
		    else
			character = 012;
		}
		
		switch (character) {
		    case '':		/* reset with 'escape' */
			pagenum = -1;
			break;

		    case 'u':		/* scroll up */
		    case 'A':		/* or up arrow */
			new_page = scrollup(dis_num, proc_num);
			character = 0;
			pagenum = (new_page)? (dis_num + 1) : proc_num; 
			output = 1;
			break;

		    case 'd':		/* scroll down */
		    case 'B':		/* or down arrow */
			new_page = scrolldown(dis_num, proc_num);
			character = 0;
			pagenum = (new_page)? (dis_num - 1) : proc_num; 
			output = 1;
			break;

		    case 'C':		/* right arrow - to next page */
		    case 012:		/* CR/LF - next requested page */
		    case 015:
			pagenum = dis_num + 1;
			offset = 0;
			character = 0;
			new_page = 1;    
			output = 1;	/* Do want to print out this page */
			reset_v_pos();
			break;

		    case 'D':		/* back one page */
		    case 'b':
			pagenum = dis_num - 1;
			offset = 0;
			character = 0;
			new_page = 1;
			output = 1;	/* Do want to print out this page */
			reset_v_pos();
			break;

					/* gather a page number to move to */
		    case '0': case '1': case '2': case '3': case '4':
		    case '5': case '6': case '7': case '8': case '9':
			if (pagenum < 0) 
				pagenum = 0;
			pagenum = 10 * pagenum + character - '0';
			reset_v_pos();
			break;

		    case '$':		/* go to last page */
			pagenum = total_pages;
		    case 'g':		/* go to certain page */
		    case 'G':
		    case 'p':
		    	character = 0;
			offset = 0;
			new_page = 1;
			output = 1;	/* Do want to print out this page */
			reset_v_pos();
			break;

		    case 19:		/* ^X */
		    case 3:		/* ^C */
		    case 127:		/* "break" */
		    case 'q':		/* quit */
			leave(0);
			break;

		    case 26:		/* ^Z = forget it */
			character = 0;
			break;
		}
	    } while (character);


	if (pagenum > total_pages)
		pagenum = total_pages;
	else if (pagenum < 1)
		pagenum = 1;

	    return(pagenum);
}
