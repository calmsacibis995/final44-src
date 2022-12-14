h13037
s 00003/00003/00282
d D 1.2 93/06/08 14:43:29 elan 2 1
c 4.4BSD support.
e
s 00285/00000/00000
d D 1.1 93/05/19 14:58:10 elan 1 0
c date and time created 93/05/19 14:58:10 by elan
e
u
U
t
T
I 1
case $CONFIG in
'')
    if test ! -f config.sh; then
	ln ../config.sh . || \
	ln ../../config.sh . || \
	ln ../../../config.sh . || \
	(echo "Can't find config.sh."; exit 1)
    fi 2>/dev/null
    . ./config.sh
    ;;
esac
: This forces SH files to create target in same directory as SH file.
: This is so that make depend always knows where to find SH derivatives.
case "$0" in
*/*) cd `expr X$0 : 'X\(.*\)/'` ;;
esac
echo "Extracting h2ph (with variable substitutions)"
: This section of the file will have variable substitutions done on it.
: Move anything that needs config subs from !NO!SUBS! section to !GROK!THIS!.
: Protect any dollar signs and backticks that you do not want interpreted
: by putting a backslash in front.  You may delete these comments.
rm -f h2ph
$spitshell >h2ph <<!GROK!THIS!
#!$bin/perl
'di';
'ig00';

\$perlincl = '$installprivlib';
!GROK!THIS!

: In the following dollars and backticks do not need the extra backslash.
$spitshell >>h2ph <<'!NO!SUBS!'

chdir '/usr/include' || die "Can't cd /usr/include";

@isatype = split(' ',<<END);
	char	uchar	u_char
	short	ushort	u_short
	int	uint	u_int
	long	ulong	u_long
	FILE
END

@isatype{@isatype} = (1) x @isatype;

@ARGV = ('-') unless @ARGV;

foreach $file (@ARGV) {
    if ($file eq '-') {
	open(IN, "-");
	open(OUT, ">-");
    }
    else {
	($outfile = $file) =~ s/\.h$/.ph/ || next;
	print "$file -> $outfile\n";
	if ($file =~ m|^(.*)/|) {
	    $dir = $1;
	    if (!-d "$perlincl/$dir") {
		mkdir("$perlincl/$dir",0777);
	    }
	}
	open(IN,"$file") || ((warn "Can't open $file: $!\n"),next);
	open(OUT,">$perlincl/$outfile") || die "Can't create $outfile: $!\n";
    }
    while (<IN>) {
	chop;
	while (/\\$/) {
	    chop;
	    $_ .= <IN>;
	    chop;
	}
	if (s:/\*:\200:g) {
	    s:\*/:\201:g;
	    s/\200[^\201]*\201//g;	# delete single line comments
	    if (s/\200.*//) {		# begin multi-line comment?
		$_ .= '/*';
		$_ .= <IN>;
		redo;
	    }
	}
	if (s/^#\s*//) {
	    if (s/^define\s+(\w+)//) {
		$name = $1;
		$new = '';
		s/\s+$//;
		if (s/^\(([\w,\s]*)\)//) {
		    $args = $1;
		    if ($args ne '') {
			foreach $arg (split(/,\s*/,$args)) {
			    $arg =~ s/^\s*([^\s].*[^\s])\s*$/$1/;
			    $curargs{$arg} = 1;
			}
			$args =~ s/\b(\w)/\$$1/g;
			$args = "local($args) = \@_;\n$t    ";
		    }
		    s/^\s+//;
		    do expr();
		    $new =~ s/(["\\])/\\$1/g;
		    if ($t ne '') {
			$new =~ s/(['\\])/\\$1/g;
			print OUT $t,
			  "eval 'sub $name {\n$t    ${args}eval \"$new\";\n$t}';\n";
		    }
		    else {
			print OUT "sub $name {\n    ${args}eval \"$new\";\n}\n";
		    }
		    %curargs = ();
		}
		else {
		    s/^\s+//;
		    do expr();
		    $new = 1 if $new eq '';
		    if ($t ne '') {
			$new =~ s/(['\\])/\\$1/g;
			print OUT $t,"eval 'sub $name {",$new,";}';\n";
		    }
		    else {
			print OUT $t,"sub $name {",$new,";}\n";
		    }
		}
	    }
	    elsif (/^include\s+<(.*)>/) {
		($incl = $1) =~ s/\.h$/.ph/;
		print OUT $t,"require '$incl';\n";
	    }
	    elsif (/^ifdef\s+(\w+)/) {
		print OUT $t,"if (defined &$1) {\n";
		$tab += 4;
		$t = "\t" x ($tab / 8) . ' ' x ($tab % 8);
	    }
	    elsif (/^ifndef\s+(\w+)/) {
		print OUT $t,"if (!defined &$1) {\n";
		$tab += 4;
		$t = "\t" x ($tab / 8) . ' ' x ($tab % 8);
	    }
	    elsif (s/^if\s+//) {
		$new = '';
		do expr();
		print OUT $t,"if ($new) {\n";
		$tab += 4;
		$t = "\t" x ($tab / 8) . ' ' x ($tab % 8);
	    }
	    elsif (s/^elif\s+//) {
		$new = '';
		do expr();
		$tab -= 4;
		$t = "\t" x ($tab / 8) . ' ' x ($tab % 8);
		print OUT $t,"}\n${t}elsif ($new) {\n";
		$tab += 4;
		$t = "\t" x ($tab / 8) . ' ' x ($tab % 8);
	    }
	    elsif (/^else/) {
		$tab -= 4;
		$t = "\t" x ($tab / 8) . ' ' x ($tab % 8);
		print OUT $t,"}\n${t}else {\n";
		$tab += 4;
		$t = "\t" x ($tab / 8) . ' ' x ($tab % 8);
	    }
	    elsif (/^endif/) {
		$tab -= 4;
		$t = "\t" x ($tab / 8) . ' ' x ($tab % 8);
		print OUT $t,"}\n";
	    }
	}
    }
    print OUT "1;\n";
}

sub expr {
    while ($_ ne '') {
	s/^(\s+)//		&& do {$new .= ' '; next;};
	s/^(0x[0-9a-fA-F]+)//	&& do {$new .= $1; next;};
	s/^(\d+)//		&& do {$new .= $1; next;};
	s/^("(\\"|[^"])*")//	&& do {$new .= $1; next;};
	s/^'((\\"|[^"])*)'//	&& do {
	    if ($curargs{$1}) {
		$new .= "ord('\$$1')";
	    }
	    else {
		$new .= "ord('$1')";
	    }
	    next;
	};
	s/^sizeof\s*\(([^)]+)\)/{$1}/ && do {
	    $new .= '$sizeof';
	    next;
	};
	s/^([_a-zA-Z]\w*)//	&& do {
	    $id = $1;
	    if ($id eq 'struct') {
		s/^\s+(\w+)//;
		$id .= ' ' . $1;
		$isatype{$id} = 1;
	    }
	    elsif ($id eq 'unsigned') {
		s/^\s+(\w+)//;
		$id .= ' ' . $1;
		$isatype{$id} = 1;
	    }
	    if ($curargs{$id}) {
		$new .= '$' . $id;
	    }
	    elsif ($id eq 'defined') {
		$new .= 'defined';
	    }
	    elsif (/^\(/) {
		s/^\((\w),/("$1",/ if $id =~ /^_IO[WR]*$/i;	# cheat
		$new .= " &$id";
	    }
	    elsif ($isatype{$id}) {
		if ($new =~ /{\s*$/) {
		    $new .= "'$id'";
		}
		elsif ($new =~ /\(\s*$/ && /^[\s*]*\)/) {
		    $new =~ s/\(\s*$//;
		    s/^[\s*]*\)//;
		}
		else {
		    $new .= $id;
		}
	    }
	    else {
		$new .= ' &' . $id;
	    }
	    next;
	};
	s/^(.)//			&& do {$new .= $1; next;};
    }
}
##############################################################################

	# These next few lines are legal in both Perl and nroff.

.00;			# finish .ig
 
'di			\" finish diversion--previous line must be blank
.nr nl 0-1		\" fake up transition to first page again
.nr % 0			\" start at page 1
'; __END__ ############# From here on it's a standard manual page ############
I 2
!NO!SUBS!
cat << ENDOFMAN > h2ph.man
E 2
.TH H2PH 1 "August 8, 1990"
.AT 3
.SH NAME
h2ph \- convert .h C header files to .ph Perl header files
.SH SYNOPSIS
.B h2ph [headerfiles]
.SH DESCRIPTION
.I h2ph
converts any C header files specified to the corresponding Perl header file
format.
It is most easily run while in /usr/include:
.nf

	cd /usr/include; h2ph * sys/*

.fi
If run with no arguments, filters standard input to standard output.
.SH ENVIRONMENT
No environment variables are used.
.SH FILES
/usr/include/*.h
.br
/usr/include/sys/*.h
.br
etc.
.SH AUTHOR
Larry Wall
.SH "SEE ALSO"
perl(1)
.SH DIAGNOSTICS
The usual warnings if it can't read or write the files involved.
.SH BUGS
Doesn't construct the %sizeof array for you.
.PP
It doesn't handle all C constructs, but it does attempt to isolate
definitions inside evals so that you can get at the definitions
that it can translate.
.PP
It's only intended as a rough tool.
You may need to dicker with the files produced.
.ex
D 2
!NO!SUBS!
E 2
I 2
ENDOFMAN
E 2
chmod 755 h2ph
$eunicefix h2ph
D 2
rm -f h2ph.man
ln h2ph h2ph.man
E 2
E 1
