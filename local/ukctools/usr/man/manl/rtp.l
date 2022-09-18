.TH RTP 1  "22 July 1987"
.UC 4
.SH NAME
rtp \- on-the-fly real-time visual profiler for C and FORTRAN
.SH SYNOPSIS
\fBmake\  "CC=rtpcc\  [-b]"
.br
or
.br
make\  "FC=rtpf77"
.br
or
.br
make\  "CC=rtpcc\  [-b]"\  "FC=rtpf77"\fP
.br

.B rtp
[
.B \-w
]
object
[
.B object's args
]
.br
or
.br
object
[
.B object's args
]
.br
.B rtp
<running objects pid>
object
.SH DESCRIPTION
.I rtp
produces an execution profile of programs written in C, FORTRAN, or any mixture of
the two.
This profile is regularly updated
.I whilst
the profiled program is running.  This is in contrast to other
profilers currently available. These are all post-mortem profilers, ie.
they display the profile
.I after
the program has run.

.I rtp
presents three different levels of profile information:
.TP
1.
Time spent in each function.  To get this information, your program need only
be re-linked using
.I rtpcc
or
.I rtpf77.
The original .o files need not be re-compiled.

This time based information comes in two flavours:
.TP
1.
A flat profile.  This shows the user and system time spent in each routine.
This information is of limited use as the user generally wishes to know
the time spent in a particular routine, including the time taken in all
the routines called from it.
2.
A folding profile.  This shows the user time spent in each routine.  If the user
is not interested in the time taken in a given routine then that routine
can be hidden.  From then can be hidden.  From then on all time in that routine will be
attributed to its parent.  In this way the user can see how much time
has been spent in a routine, including the time spent in its children.

This second form of time-based profiling has the disadvantage of only
showing the user time taken by the process.  If the profiled code is
spending a good deal of its time in system calls (use the flat profile
to see) then this type of profile will not be truly represetative.
.TP
2.
Time spent in each source line.  This information can only be displayed if
the corresponding source file was compiled using the `-g' option to
.I cc
or
.I f77.
There is no need to specify the `-g' flag if the sources are compiled using
.I
rtpcc
or
.I
rtpf77,
as it is done for you.  This information also comes in two flavours, as above.
.TP
3.
The number of times each function and each source line has been executed.
This facility is only available for C code, and can only be displayed if
the C source was compiled using
.I rtpcc.
The information is gathered by seeding the C source with extra statements
to do the counting.  This seeding does not change your original source file.

Basic block execution counting is enabled by
giving the `-b' flag to
.I rtpcc.
Some files may not compile under this option.  See the BUGS section.

.LP
In order for a program to profiled by
.I rtp
the following steps have to be taken:
.TP
1.
Compile the program using
.I rtpcc
instead of
.I cc
and
.I rtpf77
instead of
.I f77.
To do this simply replace any literal occurrences of "cc" and "f77" in your makefile with $(CC) and $(FC) respectively,
then compile with:

make \ "CC=rtpcc\  [-b]"\  "FC=rtpf77"\  [normal args]

Obviously, if you are only compiling C then the "FC=rtpf77" is not needed.  In
the same way, FORTRAN programmers need not specify "CC=rtpcc".

If the .o files were previously compiled with the
.I -g
flag and statement counts are not required,
then the .o's simply need to be re-linked, otherwise remove all the .o
files.
.LP
.I rtp
does handle .o files that have not been compiled with the
.I -g
flag, but profiling will only be done on a per-routine (as
opposed to per-line) basis for .o files compiled in this way.

.I rtp
can only display execution counts for C files that were compiled using
.I rtpcc
with the `-b' flag.  Execution counts are not available in FORTRAN.
\.o files.
.TP
2.
Execute the program.  If you wish to view the profile immediately then type:
.br
.I rtp [-w] object [object's args]
.br
Alternatively, you may run the object in the usual way, ie:
.br
.I object [object's args]
.br
and then attach the profiler to it at a later date by typing:
.br
.I rtp <running objects pid> object
.br
The running objects pid (process id) can be found using
.I ps(1).
.LP
If you are using suntools then the profiler will start up in the current
window.
If you are using Xwindows then you will be prompted for the window in which
.I rtp
will be run.

On startup, the profiler presents you with a list of function names.  These
are either the functions that have so far been sampled, or if the profiled
code was written in C and compiled using
.I rtpcc,
the functions that have so far been executed.
.LP
Underneath each function name is a a bar.  This can show either the
number of times the function has been executed or the number of
program counter samples that have fallen within the function (proportional
to the amount of time spent within the function) or both, one below the other.
.LP
Execution counts are displayed as hollow bars, sample counts are displayed
as filled bars.  The profiler will default to displaying just the execution
counts unless none of the object files have been compiled to supply this
information.  If this is the case then the sample counts will be displayed.
.TP
.B Button\ 1
Scrolls the list.
.TP
.B Button\ 2
Displays the source code for the routine you are pointing at, along
with profiling information on a per-line basis.  The source code can be
scrolled in the same way as the function name list.  As with the function
names, each source line has one or two bars beneath it that either display
an execution count, a sample count, or both.
.TP
.B Button\ 3
Is used to cover / uncover displayed routines.  Routines that are covered
are not normally displayed.
Use the
.I show
option in the main menu to display them.
.LP
At the top of both scrollable lists is either one or two scales.  The number at the
right of each scale is the size of the largest histogram bar.  Its units
are either
.I number of times executed
or
.I number of samples.
The scale is marked in ones, tens, hundreds, etc. depending on what is sensible.
The scale showing the maximum number of samples in any one place is
particularly important. If there haven't been many samples so far then the
profile is not very representative.

Menu options are:
.TP
.B refresh
Sets how often the histogram is updated.
.TP
.B info
Determines whether the histogram displays execution counts, sample counts, or
both.
.TP
.B sort
Determines whether routines are sorted by name, by how many times
they have been sampled, or by execution count.
.TP
.B victim
Starts / stops the profiled program.  This can be useful if things are
happening too fast.
.TP
.B show
Determines whether covered routines are displayed.  Covered routines
will be cross-hatched to distinguish them from uncovered routines.
.TP
.B quit
Quits
.I rtp.
You may re-attach the profiler to the running object at a later date by
typing:
.br
.I rtp <running objects pid> object.
The running objects pid (process id) can be found using
.I ps(1).
.SH "RTP OPTIONS"
.TP
.B \-w
start up a terminal emulator for the profiled program.
Useful when profiling programs that do not start up their own window.  Essential
for when profiling sunview graphical programs that run in a blanket window.
.SH "RTPCC OPTIONS"
.TP
.B \-b
insert extra code at compile time to count the number of times each
function or basic block has been executed.
.SH FILES
/tmp/sockfile
.SH "SEE ALSO"
prof(1), gprof(1), ps(1)
.SH DIAGNOSTICS
.SH BUGS
If the `-b' flag is given to
.I rtpcc
then the C code will be seeded with extra statements to keep count of
how many times each basic block has been executed.  In order to do this seeding,
the C has to be parsed.  The grammer used should parse any ANSI standard C, but
the C compiler's parser may be more intelligent/irresponsible than
.I rtpcc's.

Should the parser trip up over a particularly baroque piece of C then ommit
the `-b' flag to
.I rtpcc
for the offending source file.

Beware of quantisation errors.  The more CPU time the profiled code has
used, the more reliable the execution profile.  Notice the scales at the top of
the source and function name lists.
