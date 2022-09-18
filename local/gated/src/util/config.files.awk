#
#	$Id: config.files.awk,v 1.9.4.2 1994/03/17 04:10:25 jch Exp $
#
# %(Copyright.header)
#
BEGIN {
	OBJS[""]=  "" ;
	SRCS[""]=  "" ;
	HDRS[""]=  "" ;
	DEFS[""]=  "" ;
	MYS[""]=  "" ;
	MANS[""] = "" ;
	MANS["ALL_"] = "" ;
	LINKS = "" ;
}

#
#	Ignore comments and blank lines
#
/^#.*$/	|| /^[ \t]*$/ {
	next ;
}

{
	if (NF >= 2) {
		INDEX = $2 ;
	} else {
		INDEX = "" ;
	}	
}

#
#	C files
#
substr($1, length($1) - 1, 2) == ".c" {
	src = $1 ;
	if (index(src, "/")) {
		LINKS = LINKS " " src ;
		while (c = index(src, "/")) {
			src = substr(src, c+1) ;
		}
	}
	SRCS[INDEX] = SRCS[INDEX] " " src ;
	OBJS[INDEX] = OBJS[INDEX] " " substr(src, 1, length(src) - 2) ".o" ;
	next ;
}

#
#	H files
#
substr($1, length($1) - 1, 2) == ".h" {
	hdr = $1 ;
	if (index(hdr, "/")) {
		LINKS = LINKS " " hdr ;
		while (c = index(hdr, "/")) {
			hdr = substr(hdr, c+1) ;
		}
	}
	HDRS[INDEX] = HDRS[INDEX] " " hdr ;
	next ;
}

#
#	L files
#
substr($1, length($1) - 1, 2) == ".l" {
	if (index($1, "/")) {
		LINKS = LINKS " " $1 ;
	}
	next ;
}

#
#	Object files
#
substr($1, length($1) - 1, 2) == ".o" {
	OBJS[INDEX] = OBJS[INDEX] " " $1 ;
	next ;
}

#
#	ISODE SNMP MIB definition files
#
substr($1, length($1) - 4, 5) == ".defs" {
	def = $1 ;
	DEFS[INDEX] = DEFS[INDEX] " " def ;
	next ;
}

substr($1, length($1) - 2, 3) == ".my" {
	my = $1 ;
	MYS[INDEX] = MYS[INDEX] " " my ;
	next ;
}

#
#	Man pages
#
substr($1, length($1) - 1, 2) == ".8" {
	man = $1 ;
	if (index(man, "/")) {
		LINKS = LINKS " " man ;
		while (c = index(man, "/")) {
			man = substr(man, c+1) ;
		}
	}
	MANS[INDEX] = MANS[INDEX] " " man ;
	MANS["ALL_"] = MANS["ALL_"] " " man ;
	next;
}
#
#	Catch invalid file names
#	
{
	printf "invalid input on %s line %d: %s\n", FILENAME, NR, $0 ;
	error = 1;
	exit 1;
}

#
#	Print the Makefile header
#
END {
	for (i in SRCS) {
		n_files = split(SRCS[i], files, " ") ;

		if (n_files > 1) {
			printf "%sSRCS=\t%s \\\n", i, files[1] > MAKEFILE ;
			for (ii = 2; ii < n_files; ii++) {
				printf "\t%s \\\n", files[ii] > MAKEFILE ;
			}
			printf "\t%s\n\n", files[ii] > MAKEFILE ;
		} else {
			printf "%sSRCS=\t%s\n\n", i, files[1] > MAKEFILE ;
		}
	}
	for (i in HDRS) {
		n_files = split(HDRS[i], files, " ") ;

		if (n_files > 1) {
			printf "%sHDRS=\t%s \\\n", i, files[1] > MAKEFILE ;
			for (ii = 2; ii < n_files; ii++) {
				printf "\t%s \\\n", files[ii] > MAKEFILE ;
			}
			printf "\t%s\n\n", files[ii] > MAKEFILE ;
		} else {
			printf "%sHDRS=\t%s\n\n", i, files[1] > MAKEFILE ;
		}
	}
	for (i in OBJS) {
		n_files = split(OBJS[i], files, " ") ;

		if (n_files > 1) {
			printf "%sOBJS=\t%s \\\n", i, files[1] > MAKEFILE ;
			for (ii = 2; ii < n_files; ii++) {
				printf "\t%s \\\n", files[ii] > MAKEFILE ;
			}
			printf "\t%s\n\n", files[ii] > MAKEFILE ;
		} else {
			printf "%sOBJS=\t%s\n\n", i, files[1] > MAKEFILE ;
		}
	}
	for (i in DEFS) {
		n_files = split(DEFS[i], files, " ") ;

		if (n_files > 1) {
			printf "%sDEFS=\t%s \\\n", i, files[1] > MAKEFILE ;
			for (ii = 2; ii < n_files; ii++) {
				printf "\t%s \\\n", files[ii] > MAKEFILE ;
			}
			printf "\t%s\n\n", files[ii] > MAKEFILE ;
		} else {
			printf "%sDEFS=\t%s\n\n", i, files[1] > MAKEFILE ;
		}
	}
	for (i in MYS) {
		n_files = split(MYS[i], files, " ") ;

		if (n_files > 1) {
			printf "%sMYS=\t%s \\\n", i, files[1] > MAKEFILE ;
			for (ii = 2; ii < n_files; ii++) {
				printf "\t%s \\\n", files[ii] > MAKEFILE ;
			}
			printf "\t%s\n\n", files[ii] > MAKEFILE ;
		} else {
			printf "%sMYS=\t%s\n\n", i, files[1] > MAKEFILE ;
		}
	}
	for (i in MANS) {
		n_files = split(MANS[i], files, " ") ;

		if (n_files > 1) {
			printf "%sMANS=\t%s \\\n", i, files[1] > MAKEFILE ;
			for (ii = 2; ii < n_files; ii++) {
				printf "\t%s \\\n", files[ii] > MAKEFILE ;
			}
			printf "\t%s\n\n", files[ii] > MAKEFILE ;
		} else {
			printf "%sMANS=\t%s\n\n", i, files[1] > MAKEFILE ;
		}
	}
	n_files = split(LINKS, files, " ") ;

	if (n_files > 1) {
		printf "LINKS=\t%s \\\n", files[1] > MAKEFILE ;
		for (ii = 2; ii < n_files; ii++) {
			printf "\t%s \\\n", files[ii] > MAKEFILE ;
		}
		printf "\t%s\n\n", files[ii] > MAKEFILE ;
	} else {
		printf "LINKS=\t%s\n\n", files[1] > MAKEFILE ;
	}
}

#
# %(Copyright)
#
