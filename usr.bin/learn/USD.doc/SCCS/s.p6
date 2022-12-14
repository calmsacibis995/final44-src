h38452
s 00000/00000/00163
d D 8.1 93/06/08 11:59:50 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00000/00161
d D 6.2 91/04/17 12:16:01 bostic 2 1
c new copyright; att/bsd/shared
e
s 00161/00000/00000
d D 6.1 86/05/23 09:24:48 kjd 1 0
c date and time created 86/05/23 09:24:48 by kjd
e
u
U
t
T
I 2
.\" %sccs.include.proprietary.roff%
.\"
E 2
I 1
.\"	%W% (Berkeley) %G%
.\"
.NH
Conclusions
.PP
The following observations can be made about
secretaries, typists, and
other non-programmers who have used
.I learn :
.IP (a)
A novice must have assistance with the mechanics
of communicating with the computer to get through to
the first lesson or two;
once the first few lessons are passed people can proceed
on their own.
.IP (b)
The terminology used in the first few lessons
is obscure to those inexperienced with computers.
It would help if there were a low level
reference card for
.UX
to supplement the existing
programmer oriented bulky manual and bulky reference card.
.IP (c)
The concept of ``substitutable argument'' is hard
to grasp, and requires help.
.IP (d)
They enjoy the system for the most part.
Motivation matters a great deal, however.
.LP
It takes an hour or two for a novice to get through
the script on file handling.
The total time for a reasonably intelligent and motivated novice to proceed from ignorance
to a reasonable ability to create new files and manipulate old ones
seems to be a few days, with perhaps half of each day
spent on the machine.
.PP
The normal way of proceeding has been to have students in the same
room with someone who knows
.UX
and the scripts.
Thus the student is not brought to a halt by
difficult questions.  The burden on the counselor, however,
is much lower than that on a teacher of a course.
Ideally, the students should be encouraged to proceed with instruction
immediately prior to their actual use of the computer.
They should exercise the scripts on the same computer and the same
kind of terminal that they will later use
for their real work, and
their first few jobs for the computer should be
relatively easy ones.
Also, both training and initial work should take place on days
when the
.UX
hardware and software
are working reliably.
Rarely is all of this possible, but the closer one comes the better
the result.
For example, if it is known that the hardware is shaky one day, it is better
to attempt to reschedule training for another one.  Students are very
frustrated by machine downtime; when nothing is happening, it takes
some sophistication and experience to distinguish
an infinite loop, a slow but functioning program,
a program waiting for the user, and a broken machine.*
.FS
* We have even known an expert programmer to decide the computer
was broken when he had simply left his terminal in local mode.
Novices have great difficulties with such problems.
.FE
.PP
One disadvantage
of training with
.I
learn
.R
is that students come to depend
completely on the CAI system, and do not try
to read manuals or use other learning aids.
This is unfortunate, not only because of the increased
demands for completeness and accuracy of the
scripts, but because the scripts do not cover all of
the
.UX
system.
New users should have manuals (appropriate for their level) and
read them; the scripts ought to be altered
to recommend suitable documents and urge
students to read them.
.PP
There are several other difficulties which are clearly evident.
From the student's viewpoint,
the most serious is that
lessons still crop up which simply can't be passed.
Sometimes this is due to poor explanations,
but just as often it is some error in the lesson itself
\(em a botched setup, a missing file,
an invalid test for correctness,
or some system facility that doesn't work on the local
system in the same way it did on the development system.
It takes knowledge and a certain healthy arrogance on the part of the user to recognize
that the fault is not his or hers,
but the script writer's.
Permitting the student to get on with the next lesson
regardless does alleviate this somewhat,
and the logging facilities make it easy
to watch for lessons that no one
can pass,
but it is still a problem.
.PP
The biggest problem with the previous
.I learn
was speed (or lack thereof) \(em
it was often excruciatingly slow
and made a significant drain on the system.
The current version so far does not seem
to have that difficulty,
although some scripts,
notably
.I eqn ,
are intrinsically slow.
.I eqn ,
for example,
must do a lot of work even to print its introductions,
let alone check the student responses,
but delay is perceptible in all scripts
from time to time.
.PP
Another potential problem is that it is possible
to break
.ul
learn
inadvertently, by pushing interrupt at the wrong time,
or by removing critical files,
or any number of similar slips.
The defenses against such problems
have steadily been improved, to the point
where most students should not notice difficulties.
Of course, it will always be possible to break
.I
learn
.R
maliciously, but this is not likely to be a problem.
.PP
One area is more fundamental \(em
some
.UX
commands are sufficiently global in their effect
that
.ul
learn
currently
does not allow them to be executed at all.
The most obvious is
.I cd ,
which changes to another directory.
The prospect of a student who is learning about directories
inadvertently moving to some random directory
and removing files has deterred us
from even writing lessons on
.I cd ,
but ultimately lessons on such topics probably should be added.
E 1
