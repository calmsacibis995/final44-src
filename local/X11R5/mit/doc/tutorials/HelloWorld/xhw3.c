#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>
#include <X11/Xaw/Label.h>

#define	STRING	"Hello,  World"

Arg wargs[] = {
    {XtNlabel,	(XtArgVal) STRING},
};

main(argc, argv)
    int argc;
    char **argv;
{
    Widget      toplevel, label;

    /*
     * Create the Widget that represents the window.
     * See Section 14 of the Toolkit manual.
     */
    toplevel = XtInitialize(argv[0], "XLabel", NULL, 0, &argc, argv);

    /*
     * Create a Widget to display the string,  using wargs to set
     * the string as its value.  See Section 9.1.
     */
    label = XtCreateWidget(argv[0], labelWidgetClass,
			   toplevel, wargs, XtNumber(wargs));

    /*
     * Tell the toplevel widget to display the label.  See Section 13.5.2.
     */
    XtManageChild(label);

    /*
     * Create the windows,  and set their attributes according
     * to the Widget data.  See Section 9.2.
     */
    XtRealizeWidget(toplevel);

    /*
     * Now process the events.  See Section 16.6.2.
     */
    XtMainLoop();
}
