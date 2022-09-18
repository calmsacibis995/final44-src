#
#	$Id: version.awk,v 1.2 1993/05/28 10:59:47 jch Exp $
#
BEGIN {
	RECORD = 0;
	filename= "";
}
FILENAME == VERSION_IDS {
	file = substr($3, 2);
	versions[file] = $0;
	next;
}
{
	RECORD = RECORD + 1;
}
filename != FILENAME {
	RECORD = 1;
	filename = FILENAME;
	while (i = index(filename, "/")) {
		filename = substr(filename, i+1);
	}
}
RECORD < 6 {
	for ( i = 1; i < NF && i < 5; i++) {
		if (index($i, FILENAME)) {
			name = $i;
			file = filename;
			while (i = index(file, ".")) {
				file = substr(file, 1, i - 1) "_" substr(file, i + 1);
			}
			what = $0;
			if (i = index(what, name)) {
				what = substr(what, i + length(name));
			}
			versions[file] = "const char *"file" = \"@(#)$Id: "filename what"\";" ;
			break;
		}
	}
}

END {
	for (file in versions) {
		print versions[file] ;
	}
}
