awk '

# this program checks whether an old awk program will
# stumble over a feature of the new awk.
# it does NOT check whether a new awk program
# will run on the old awk.
# it is dumb about quoted things.

	{ sub(/^/, " ") }
/[^a-zA-Z0-9]close[^a-zA-Z0-9]/	{ warn("\"close\" is now a built-in function") }
/[^a-zA-Z0-9]system[^a-zA-Z0-9]/ { warn("\"system\" is now a built-in function") }
/[^a-zA-Z0-9]atan2[^a-zA-Z0-9]/	{ warn("\"atan2\" is now a built-in function") }
/[^a-zA-Z0-9]sin[^a-zA-Z0-9]/	{ warn("\"sin\" is now a built-in function") }
/[^a-zA-Z0-9]cos[^a-zA-Z0-9]/	{ warn("\"cos\" is now a built-in function") }
/[^a-zA-Z0-9]s?rand[^a-zA-Z0-9]/	{ warn("\"rand\" and \"srand\" are now built-in functions") }
/[^a-zA-Z0-9]match[^a-zA-Z0-9]/	{ warn("\"match\" is now a built-in function") }
/[^a-zA-Z0-9]sub[^a-zA-Z0-9]/	{ warn("\"sub\" is now a built-in function") }
/[^a-zA-Z0-9]gsub[^a-zA-Z0-9]/	{ warn("\"gsub\" is now a built-in function") }

/[^a-zA-Z0-9]ARGC[^a-zA-Z0-9]/	{ warn("\"ARGC\" is now a built-in variable") }
/[^a-zA-Z0-9]ARGV[^a-zA-Z0-9]/	{ warn("\"ARGV\" is now a built-in variable") }
/[^a-zA-Z0-9]FNR[^a-zA-Z0-9]/	{ warn("\"FNR\" is now a built-in variable") }
/[^a-zA-Z0-9]RSTART[^a-zA-Z0-9]/ { warn("\"RSTART\" is now a built-in variable") }
/[^a-zA-Z0-9]RLENGTH[^a-zA-Z0-9]/ { warn("\"RLENGTH\" is now a built-in variable") }
/[^a-zA-Z0-9]SUBSEP[^a-zA-Z0-9]/ { warn("\"SUBSEP\" is now a built-in variable") }

/[^a-zA-Z0-9]getline[^a-zA-Z0-9]/ { warn("getline behavior is potentially different") }
/[^a-zA-Z0-9]func[^a-zA-Z0-9]/	{ warn("\"func\" is now a keyword") }
/[^a-zA-Z0-9]function[^a-zA-Z0-9]/	{ warn("\"function\" is now a keyword") }
/[^a-zA-Z0-9]delete[^a-zA-Z0-9]/ { warn("\"delete\" is now a keyword") }
/[^a-zA-Z0-9]do[^a-zA-Z0-9]/ { warn("\"do\" is now a keyword") }

function warn(s) {
	sub(/^[ \t]*/, "")
	printf("%d: %s\n\t%s\n", NR, $0, s) }

' $*
