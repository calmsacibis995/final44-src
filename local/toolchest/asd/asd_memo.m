.nr H1 -1
.(B
.tl @Copyright (c) 1984, 1985, 1986, 1987@@AT&T All Rights Reserved@
.(E 2
.de Es
.DS I
.ft 5
..
.de Ee
.FT R
.DE
..
.TL
Automatic Software Distribution
.AU "Andrew Koenig" ARK "" "" "" ""
.AS
The author of a popular program frequently has trouble
ensuring that each user has a copy of the current version.
When there are many users, the problem is made even tougher
by the need to maintain data integrity and security.
.P
We discuss some tools we have built to help solve
this problem.
These tools make it possible to execute:
.ft 5
.P
     ship /bin/who
.ft P
.P
After one has supplied the correct password,
this will eventually cause new copies of the
.I who
command to appear on many remote machines.
.AE
.MT 4
.H 1 "Introduction"
Our lab operates a number of small computers,
each running the
.UX
operating system.
Because these machines share a
common hardware architecture, we try to keep only
a single copy of the system's source programs
and replicate the object programs as necessary.
.P
Many of our people are actively writing new software.
When a new program is ready, the author typically puts a
copy of the program on one (or a few) of our
machines and tells people about it.
Potential users who hear about the program may
copy it onto their own machines.
.P
If the program is popular, copies eventually migrate to
several machines.
Since the program has probably changed during this period,
each machine might have a different version.
An author who learns of a bug from a user
may have trouble deciding whether that
bug still exists or whether the user is running
an obsolete version of the program.
.P
For example, Mike Lesk has mentioned
that two thirds of the bug reports he gets
on one popular program he wrote
refer to things he has already fixed
in the latest version.
.P
Why does this happen?
The main reason is that it is too much work for an
author to keep copies of his program up to date
for all users.
If a user is reasonably satisfied with the behavior
of a program, there is usually little incentive
to install an update.
Even if a user is dissatisfied,
that user might have to go to the system administrator
to get a new version installed.
.P
It would be nice if all users of a program always
had the latest version.
To make this more firm, though, we must answer
several hard questions:
What does it mean to have the latest version of a program?
How does one go about installing a new version?
What about data integrity and security?
.H 2 "What's in a version?"
Imagine that the author of a widely used program,
such as the
.I ls
command,
could somehow send new versions of that
program to all its users.
To send out a new version,
the author might send three files:
.I /bin/ls ,
the executable object program,
.I /usr/man/man1/ls.1 ,
the text of the reference manual page that describes the
program, and
.I /usr/src/cmd/ls.c ,
the source program.
In the minimal case, one need only send
.I /bin/ls .
If the receiving machines have different hardware, it may
be useless to send
.I /bin/ls
directly.
Instead, the receiving machine must be told to create
a new
.I /bin/ls
from the source code.
.P
We learn several things from this simple example.
First, sending a new version of even a straightforward
program may involve updating several files on each
receiving machine.
Second, we may need to send different things to different machines.
Third, installing a new version of a program may involve
more than just copying data (such as system-dependent
initialization).
.H 2 "What granularity?"
Should it be possible to send only part of a file?
Perhaps.
For example, a distribution mechanism might be used to
effect user enrollment on a community of machines.
.P
Unfortunately, partial file updating raises two questions.
First, just what updating operations should be supported?
Second, how do we ensure that the file was correct before
modification?
.P
Replacing only entire files avoids
both problems.
Moreover, if it is possible to execute a program on the receiving
machine as part of installation,
it is unnecessary to provide another mechanism
for partial updates.
.H 2 "Structure"
Part 1 of this paper describes
.I mkpkg
and
.I inspkg ,
tools for creating and installing packages.
Part 2 describes
.I seal
and
.I unseal ,
which make it difficult for a package to be
modified in transit without detection.
Part 3 describes
a simple ``gatekeeper''
that permits
.I inspkg
to be executed with the appropriate
privileges while limiting the risk
of unwanted execution.
Part 4 describes a simple shell script
that puts all these pieces together into
a system.
Part 5 discusses the current state of that
system and hints at future directions.
.H 1 "Putting data into packages"
Because updating a piece of software
often requires changing several files together,
it is important to have a data structure
that contains all the information in
a collection of files.
We call this structure a
.I package ,
and manipulate packages with
.I mkpkg
and
.I inspkg .
.I Mkpkg
gathers a set of files into a
package, and
.I inspkg
uses that package to re-create a copy
of the files.
For example,
.Es
mkpkg a b c >foo
.Ee
collects the contents of files
.I a ,
.I b ,
and
.I c
into a single file named
.I foo ,
and
.Es
inspkg foo
.Ee
unpacks
.I foo
and re-creates the original
files.
.P
A package contains a copy of the contents of each
file stored in it, as well as that file's full
pathname, its owner, group, mode, and reference
and modification times.
As many of these as possible are restored
when the file is re-created.
If
.I mkpkg
is given the name of a directory, all files
in that directory are (recursively) included
in the package.
.P
Re-creating a file generally involves deleting it first, in
case a file with the same name already existed.
This is true even if the file is a directory:
all files in that directory are deleted, and the
directory itself is then removed.
To guard against possible inadvertent destruction
of large amounts of data,
.I inspkg
has a backup option, which causes it to create a package
of everything destroyed during installation.
The backup package can be installed by
.I inspkg
in the usual way.
.P
When an argument to
.I mkpkg
names a non-existent file, the resulting package
includes an instruction to delete that file.
.P
Sometimes it is useful to install files at a different
absolute pathname than implied in the package.
For instance, programs in
.I /usr/bin
on one machine might be more
appropriate for
.I /usr/lbin
on another.
Similarly, it can be useful when making a package
to pretend that a file is somewhere other than
its true location.
To these ends,
.I mkpkg
and
.I inspkg
allow a list of pairs of pathnames to be given.
Whenever a file is found whose name matches the
first element of a pair, the matching prefix
is replaced by the second element of the pair.
.P
Finally, it is possible to ``pretend'' to install a
package: a backup is made and the usual checks
are done, but no files are actually changed.
This allows a user to see what files are
affected by a package without doing
any damage.
.P
The package data structure contains only printable
characters.
Thus, a package containing only entirely printable
files is itself entirely printable.
This is intended to make debugging easier,
at the cost of a good deal of complexity in
the programs themselves.
.H 1 "What's in a file?"
When sending a file, it is often important to preserve
more than just the file's name and contents.
For instance, some commands (such as
.I mail
and
.I uucp )
must be owned by particular users,
and modification times may be important for libraries
and collections of files accessed by the
.I make
program.
When preserving the owner of a file, it is important
to use the character representation of the owner,
rather than the absolute numeric
.I uid :
common practice is for the same individual to have different
.I uid s
on different machines, but the same login name.
The protection bits are also important.
Special files do not have contents as such,
but the major and minor device numbers are
important.
.H 1 "What's in a package?"
A package is actually an archive
(as if generated by the
.I ar
command),
with one component for each file it ``contains,''
and an extra component (named
.I Instructions )
that tells
.I inspkg
how to install it.
Choosing this format is actually responsible
for a good deal of the complexity in
.I inspkg ,
but it makes it possible to use the
.I ar
command
to break open a package in an emergency.
.P
The
.I Instructions
component contains a sequence of instructions to
.I inspkg ,
each one on a single line.
The first character of an instruction identifies the
type of instruction; the format of the rest of the instruction
is type-dependent.
For example, an instruction that describes a file has
a type letter of
.B f ,
followed by the name of the archive component that
contains the file, the owner's user and group id,
and the full pathname of the destination.
File instructions do not include date or mode, as this
information already appears in the archive header.
Other instructions can cause
.I inspkg
to make directories or links, or delete files.
.P
.I Inspkg
insists that the archive components be in the same sequence
as the corresponding instructions.
.H 1 "Naming conventions"
All files named in a package are remembered
by their full pathnames.
.I Mkpkg
helps in this by putting the name of the current
directory in front of any relative pathnames.
Thus
.I inspkg
need deal only with full pathnames.
.P
Sometimes it is useful to install a file in
a directory with a different name than the one
that originally contained it.
Both
.I mkpkg
and
.I inspkg
therefore allow a primitive name replacement.
For example, suppose we want to create a package
containing a new command that is stored in
.I /usr/bin/lcl/newcmd
on our machine.
We may want the package to indicate that this
file should be installed in
.I /usr/bin/newcmd .
This is done as follows:
.Es
mkpkg -D/usr/bin/lcl=/usr/bin /usr/bin/lcl/newcmd >newpkg
.Ee
Similarly, the recipient of this package may want
to install the command in
.I /usr/nbin .
The way to do this is:
.Es
inspkg -D/usr/bin=/usr/nbin newpkg
.Ee
As with all pathnames given to
.I mkpkg
and
.I inspkg ,
relative names are made absolute.
.P
Once a
.B \-D
option has caused a name to be changed,
that name is not touched further.
Thus
.Es
mkpkg -Dx=y -Dy=x x y >z
.Ee
will put a package in
.I z
that contains files
.I x
and
.I y ,
and will pretend that the names have been interchanged.
.P
The
.B \-b
option requests a backup package:
.Es
inspkg -b newpkg >oldpkg
.Ee
.I Oldpkg
will contain everything that was deleted during
installation of
.I newpkg .
.H 1 "Installation note"
Some
.UX
systems do not allow a file to be modified while a process
is executing it.
For this reason, files are installed by
first deleting any old file that might
exist and then re-creating a new file
with the right characteristics.
If
.I inspkg
cannot delete the file, it tries to overwrite it
anyway, just in case it succeeds.
.P
Once the file has been created,
.I inspkg
tries to set its owner and group.
On some systems, this can only be done by
the super-user.
.H 1 "Tamper-resistant packages"
Once upon a time, some people were trying to break into a
computer system.
They tried everything they could imagine,
but were unable to get in.
Finally, they hit on a clever idea.
They made their own copy of the system and
changed that copy to make it easy to break in.
They then put the changes on a reel of tape,
put the tape in a box with the name of the
operating system's manufacturer on its return address
label, and mailed it to the system administrator.
The administrator, a trusting soul, looked at the box
and said: ``Aha, another system update.  Let's install it!''
.P
Valuable objects are generally shipped in sealed
packages.
Such packages usually serve two purposes.
First, they make the contents easy to handle
safely.
They do this, in part, by enclosing the objects
in a box whose shape makes it easy to transport.
Second, they make it difficult for anyone to tamper
with the objects without being detected.
It is extremely difficult to prevent a box from
vanishing altogether, but that is usually not
the sender's motivation.
Rather, the sender wants to ensure that any damage
done in transit is detected quickly, so that claims
can be pursued against the shipping company.
.P
Suppose software updates are installed automatically.
How can the receiving machine ensure the identity
of the sender?
It is clearly insufficient for the sending machine to
announce its name: that, by itself, is too easily imitated.
It would be nice to be able to defend against a
rogue superuser on the sending machine, but
that is probably too much to ask: the programs
that send things out are subject to corruption, too.
The most we can hope for is to require the author
to supply a password when sending things:
it is best that the password not be stored
on the sending machine at all.
.P
Much can go wrong when sending data to another site.
Some transmission programs will only accept printable
characters, grouped into reasonably short lines.
These programs may quietly garble
data that do not fit their standards.
Data can also be corrupted by hardware errors or line noise.
Bugs in transmission software can cause data to be
corrupted or lost.
Data, particularly if
of economic importance,
can be altered by direct human
intervention.
In general, it is extremely difficult to prevent
data from being altered, but it is important to
know about it when it happens.
.P
A similar problem arises when trying to send
valuable physical objects through the mail.
Things can be protected against physical damage
by cushioned packaging, and packages can be
sealed to protect against pilferage, but it is
impossible to prevent an entire package from
disappearing.
.P
The outer box on a package thus serves two
purposes: it makes it more convenient for
the shipper to transport the contents (by
enclosing it in a regular shape),
and it makes it hard for anyone
to affect the contents without leaving
externally visible signs.
.P
We accomplish these purposes with two commands called
.I seal
and
.I unseal .
After executing
.Es
seal a b c >x
.Ee
the file
.I x
will represent the concatenation of
.I a ,
.I b ,
and
.I c .
This representation contains only printable characters,
divided into lines of reasonable length.
Executing
.Es
unseal x >y
.Ee
will unscramble this representation, and make
.I y
into a copy of the concatenation of
.I a ,
.I b ,
and
.I c .
.P
In effect, these commands are a roundabout way of saying
.Es
cat a b c >y
.Ee
The difference is that
.I x ,
the intermediate form,
is protected against inadvertent damage in transit.
If more security is important, one can say
.Es
seal -k a b c >x
.Ee
.I Seal
will now ask for a key.
To unseal
.I x ,
done by saying
.Es
unseal -k x >y
.Ee
the same key must be supplied.
.P
Note that
.I seal
does not attempt to encrypt the data being sent,
or to prevent the data from being modified.
Instead, it makes it hard to
modify data
.I "without detection" .
.P
If
.I unseal
finds something wrong, it
writes nothing at all on the standard output
(and complains appropriately on the standard error file).
This means that the output from
.I unseal
can be safely piped into other programs without further testing.
In particular, consider the pipeline
.Es
mkpkg \fIfile ...\fP | seal | \fIchannel\fP | unseal | inspkg
.Ee
Here,
.I channel
might represent the process of sending data from one
machine to another, and might therefore be somewhat
unreliable.
.I Unseal
ensures that if it finds an error in its input,
.I inspkg
will be given a null input file.
.H 1 "How it works"
Sealing a package has two purposes:
allowing it to be sent easily and protecting its
contents against change.
.P
Easy transportation is assured by using an escape
scheme to encode the bits that make up unprintable
characters.
Files with too many unprintables are encoded
a word at a time, to make sure that the encoded
file is not too much larger than the original.
The method is more complicated than it needs to be,
but has the advantage that text files are often
changed very little during encoding.
.P
.I Seal
tries to preserve data integrity by putting the length
and a checksum of the data at the end of the
sealed file.
.I Unseal
expects these to match exactly.
If a key is given,
.I seal
encrypts the data before taking the checksum,
but does not send the ciphertext.
.I Unseal
duplicates the process: giving the wrong key
will result in a checksum mismatch.
.P
It is important to realize that merely encrypting the
checksum isn't good enough.
Although this would make it hard for an interloper
to change the
.I checksum ,
it is open to attack by someone who can figure out how
to make dangerous changes that leave the checksum
invariant.
This would be easy if the data being sent were,
for example, a source program with comments:
changes to the program text (not changing the length)
could be balanced by appropriate changes to an
arbitrarily chosen comment.
.H 1 "Options"
We have already encountered the
.B \-k
option, causing both
.I seal
and
.I unseal
to demand a key.
Sometimes it is useful for the key to come from
somewhere other than the terminal.
Thus both
.I seal
and
.I unseal
also provide a
.B \-K
option.
This is followed by the name of a file that
contains the key.
There is no way to specify the key directly on the
command line, because it is too easy to discover such a key
by using the
.I ps
command.
.H 1 "A simple gatekeeper"
We have now seen how to transport a collection of files
from one machine to another.
First, put them in a sealed package:
.Es
mkpkg \fIfile ...\fP | seal -k > package
.Ee
Second, transport that package to the destination machine.
The transportation method need not be highly secure.
Third, unseal the package and install the contents:
.Es
unseal -k package | inspkg
.Ee
Because
.I unseal
only produces output when everything works flawlessly,
it is even safe to make this process more automatic:
.Es
unseal -K /etc/secretkey package | inspkg
.Ee
provided that the file with the key can be kept secret.
Given this, and given the fact that these files may be
received by daemons with no special privileges,
it seems useful to have a program that will automatically
install files sealed with the proper key.
This program is called
.I asdrcv .
.P
We take the view that each individual who uses this
tool kit to update programs on our machine will have
a separate password, and that an individual is uniquely
identified by a machine name and a login id.
We use the file system to do our mapping
by assuming that the key is in a file named
.I /etc/asd/keys/machine/user .
.P
.I Asdrcv
has a simple job.
Suppose a file named
.I package
is intended to contain a sealed package created by
.I research!ark .
We merely tell
.I asdrcv
the purported creator of this package:
.Es
asdrcv research ark < package
.Ee
.I Asdrcv
can safely execute the following pipeline:
.Es
unseal -K /etc/asd/keys/research/ark | inspkg
.Ee
because if the package is not what it seems,
.I unseal
will give an empty input to
.I inspkg ,
and nothing will be hurt.
In fact, we add an extra measure of security by
executing, in effect:
.Es
(unseal -K /etc/asd/keys/research | inspkg) 2>&1 | mail research!ark
.Ee
In other words, the standard output of
.I inspkg
and the standard error files of
.I unseal
and
.I inspkg
are merged and sent as mail to
.I research!ark .
.H 1 "Installation permissions"
.I Asdrcv
is actually a little more complicated than this.
It runs as super-user, but consults a file
to find out what user to impersonate.
The name of this file again depends on the
claimed creator of the package;
in the example given above it would be
.I /etc/asd/perm/research/ark .
.P
This file must exist, or
.I asdrcv
fails.
If it is empty,
.I asdrcv
runs as the super-user.
Otherwise, it contains the name of a user and group,
separated by white space.
.I Asdrcv
looks up these items in the password file
and impersonates that user and that group.
It is therefore possible to allow particular
authors to modify only files writable by particular
users or groups.
.P
Once
.I asdrcv
is installed on a machine and
.I /etc/asd/keys
and
.I /etc/asd/perm
have appropriate permissions and contents,
installing a new version is just a matter of
arranging for
.I asdrcv
to be executed with the proper arguments and standard input.
Suppose, for instance, that
.I mach1!user
wants to put a new version
of the
.I who
command on
.I mach2 .
It could be done this way:
.Es
mkpkg /bin/who | seal -k | uux - 'mach2!asdrcv mach1 user'
.Ee
The call to
.I uux
eventually causes
.I asdrcv
to be executed on
.I mach2
with arguments
.I mach1
and
.I user ,
and a standard input that is probably
identical to the output from
.I seal .
If something goes wrong,
.I mach1!user
will be told about it.
.H 1 "Putting it all together"
Here is a simple way to use these tools to distribute software.
Our machines have something very similar to this in
.I /usr/bin/ship :
.Es
T=/usr/tmp/asd$$
trap 'rm -f $T.[12]; exit 0' 1 2 3
if mkpkg $* >$T.1
then    seal -k $T.1 >$T.2
        rm -f $T.1
        (trap '' 1
        for i in ${dest:=`comm -23 /etc/asd/machines /etc/whoami`}
        do      uux - "$i!asdrcv `cat /etc/whoami` `getuid`" <$T.2
        done
        rm -f $T.2)&
else    rm -f $T.[12]
fi
trap 1 2 3
.Ee
The first two lines invent names for temporary files
and arrange that those files will disappear if the
script is interrupted.
.P
The third line begins the real work.
It tries to make a package of all the things to be sent
and put it in a temporary file.
If unsuccessful, it removes the temporary file and exits.
.P
Suppose
.I mkpkg
succeeds.
The next line seals the package (asking for a key),
and puts the sealed package in a second temporary file.
We now enter a loop that does one iteration for each destination
machine.
The destinations' names are stored in
.I /etc/asd/machines
and the current machine's name is in
.I /etc/whoami .
Thus, the expression involving
.I comm
removes the source machine from the destination list,
thus allowing the list to be identical on all machines.
This expression is used to initialize the variable
.I dest
if it is not already set.
.P
The next line invokes
.I uux
for each destination machine.
As we have already seen, this will eventually cause
.I asdrcv
to validate and install the package on each destination.
Since all these invocations of
.I uux
take some time,
we do them in the background.
.P
Finally, we clean up the temporary files and exit.
.H 1 "How to use it"
To propagate a file around our machines,
it is merely necessary to say
.Es
ship \fIfile\fP
.Ee
and supply the proper password.
To send a file to specific machines, say
.Es
dest='\fImachine1 machine2 ...\fP' ship \fIfile\fP
.Ee
In order for all this work, each receiving machine
needs two files.
.I /etc/asd/keys/machine/user
contains the key for files sent from
.I machine!user ,
and
.I /etc/asd/perm/machine/user
contains the user and group ID under which
things sent by
.I machine!user
will be installed.
The files and directories in
.I /etc/asd/perm
should generally be owned by the super-user,
with write permission for the owner only
and global read permission.
Each file in
.I /etc/asd/keys
should be readable only by the
user named in the corresponding file
in
.I /etc/asd/perm .
We keep the directory
.I /etc/asd/keys
and its subdirectories
owned by the super-user, with execute permission only
for others.
This is mostly out of a sense of general paranoia:
it is probably enough to protect the original files.
.H 1 "Discussion"
About a dozen people in our lab are presently using these tools
to install software on 25 machines.
We have given a copy of the tools
to one other organization;
they are now using them to send things around
to five machines.
.P
The current design has a few problems.
First, its security depends on being able to keep the keyfiles
secret.
This is a bad idea for
the long run \- as the number of machines using a particular key grows,
so does the chance of someone's discovering a key through
administrative carelessness.
We believe that the right way to solve this problem
is ultimately by using public-key encryption,
but this is somewhat of a nuisance to implement
and may run into performance problems.
An intermediate measure might be to store a different key
on each receiving machine.
This key could be systematically derived from the
author's master key and the name of the receiving machine,
perhaps by applying an effectively irreversible hash function
to the concatenation of the two.
Such a precaution would make each password hold the key to
only a single machine, but it would still be important to keep
the passwords secret.
.P
Another potential security problem is that a package
once created and sealed with the proper key, is quite
a potent item.
For example, an interloper who kept copies of old packages
could use them to re-install old versions of programs.
This would normally do little harm, but someone with an
interest in keeping a particular bug around could do so for
some time.
This can eventually be avoided by making the gatekeeper
somewhat smarter.
It could, for instance, reject any attempt to install a
package that is older than what it is replacing.
.P
It is tough to decide whether
.I asdrcv
should run
.I inspkg
with the
.B \-v
option or not.
If the option is used, running
.I ship
eventually results in a flood of mail messages,
often too many to be worth sifting through by hand.
On the other hand, without
.B \-v ,
it is hard to know when the new version of something
has finally been installed.
Sometimes packages get lost in transit,
and a return receipt is a good way of guarding against that.
.P
The way to handle this in the long run is probably to institute
some kind of automatic acknowledgments.
For instance, instead of running
.I mail
on the receiving machine,
.I asdrcv
could use
.I uux
to run some acknowledgment program on the sending machine.
.I Ship
could put the outgoing package on a list of 
unacknowledged items, and the acknowledgment
program could remove them from this list.
More complex schemes can also be imagined.
.P
Finally, attempting to distribute to too many machines will
ultimately cause severe performance problems.
We feel that such problems should be addressed as part of the
transmission medium, not as part of the distribution scheme.
By assuming that the transmission medium might be insecure,
we are in a better position to take advantage of new
media as the come along.
For example, it should not be difficult to use the
\s-2USENET\s0 software to distribute files to many hundreds
of machines if there is a demand for it.
.H 1 "Acknowledgment"
Mike Lesk,
who wrote the first version of
.I uucp ,
first suggested that
.I uucp
might eventually become a way
to help keep programs up to date on
a multiplicity of machines.
My work is inspired by that suggestion.
