.PH ""
.PF "'Copyright (c) 1984, 1985, 1986, 1987''AT&T All Rights Reserved'"
.BL
.LI
.B "SOFTWARE TITLE:"
\(em Tab: Tools for Creating Window Based Electronic Forms
.PH "''- Tab Forms Package \\\\nP -''"
.LI
.B "ABSTRACT:"
.P
Tab can be used to produce window based user interfaces for data
processing facilities.  Tab incorporates qualities from both menu and
block mode electronic forms in one unified interactive system.
The interface provided by this package has qualities that make it
desirable for interfaces for both novice (i.e. casual) and expert (i.e.
frequent) users.
.P
The electronic forms produced using Tab may be conceptualized as a
collection of controlled input and output areas within CRT based windows.
The input areas or fields may be moved within and between windows while
the form is running.  More than one window may be used at a time.  Like
fields, the windows may also be moved per the requirements of the
application.
.P
CRT windows are constructed with a portable virtual terminal library.
The window based virtual terminal creates windows as three dimensional
rectangular objects.  Windows that are ``closer'' to the user occlude
more distant windows.  In this environment windows may be moved
to arbitrary spatial positions on the CRT screen and in depth.
.P
Forms are constructed by calling Tab procedures or primitives from some
interpreted or compiled language (e.g. C).  These algorithmically defined
forms are more dynamic than the old boiler-plate forms of the
past.  Tab is delivered as a set of library routines that may be used
with any UNIX*
.FS *
UNIX is a Trademark of Bell Telephone Laboratories.
.FE
supported language.
.LI
.B "TYPE OF PACKAGE:"
\(em Tool and/or application software
.LI
.B "APPLICATION CATEGORY:"
\(em Office automation
.LI
.B "CPU/OPERATING SYSTEM:"
\(em UNIX on the 3B20 and VAX
.LI
.B "ADDITIONAL HARDWARE/SOFTWARE NEEDED:"
\(em None
.LI
.B "SOURCE LANGUAGE:"
\(em C
.LI
.B "PORTING ISSUES:"
.P
No changes are required for UNIX based operations.  Sample a.out's
produced using Tab are in the 40-50K range for text.  Data space for
screens, etc. is determined dynamically based on the CRT and the number
of windows used.
.LI
.B "OPERATIONAL DATE:"
\(em Immediate
.LI
.B "DOCUMENTATION AVAILABLE:"
\(em user's manual with examples
.LI
.B "CONTACT NAME:"
\(em C. Douglas Blewett
.LI
.B "MAILING ADDRESS:"
\(em MH 3-C-319
.LI
.B "TELEPHONE:"
\(em (201) 582-5837
.LI
.B "COMMENTS:"
.P
Tab has virtual terminal support for standard CRT's as well as the Blit.
.LE
