#
#
#	$Id: make_object.csh,v 1.7 1992/07/29 03:09:47 jch Exp $
#
#	Build a single object description
#
#	This is used by make_table on an object by object basis.
#	However, it can also be used to add a single object to the
#	end of a table or group.  This is A Good Thing, because
#	one doesn't have to stretch the brain to keep track of nroff
#	text manipulation stuff.  In this case, you will have to edit
#	the mib table file to add the object to the end of the
#	SEQUENCE {}.  Sorry about that.

#	input variables:
#
#	$object		the full name of the object
#	$type		the type (INTEGER, OCTET STRING, whatever)
#	$entry		the name of the mibEntry or Group
#	$identifier	the object name withn the mibEntry or Group
#	$mib		the name of the MIB nroff file being added to
#	$document	the specification being instrumented

if ("$#argv" == "6") then
	set object = "$1"
	set type = "$2"
	set entry = "$3"
	set identifier = "$4"
	set mib = "$5"
	set document = "$6"
else
	echo -n name the object\?
	set object = "$<"
	echo -n what is its ASN.1 type\?
	set type = "$<"
	echo -n what group or entry is this being added to\?
	set entry = "$<"
	echo -n what is its enumeration\?
	set identifier = "$<"
	echo -n what nroff input file\?
	set mib = "$<"
	echo -n what is the document being instruented\?
	set document = "$<"
endif

echo '.(b' >> $mib
echo $object OBJECT-TYPE >> $mib
if ("$type" == "INTEGER") then
    echo -n is $object 'enumerated?'
    if ("$<" == "yes") then
        echo '   ' SYNTAX ' ' $type '{' >> $mib
        echo -n how many values are there\?
	set enum = "$<"
	echo enumeration names MUST have a lower case alphbetic first
	echo character, and by convention capitalize the first letter of
	echo each "'word'" in the name
        foreach j (`count $enum`)
	    echo enter 'name (value):'
	    if ("$j" == "$enum") then
                echo '               ' "$<" >> $mib
	    else
                echo '               ' "$<", >> $mib
	    endif
        end
        echo '             }' >> $mib
    else
        echo -n does $object have a valid 'range?'
        if ("$<" == "yes") then
	echo -n enter it, in the form 'lowest..highest:'
            echo '   ' SYNTAX ' ' $type '(' "$<" ')' >> $mib
        else
            echo '   ' SYNTAX ' ' $type >> $mib
        endif
    endif
else
    echo '   ' SYNTAX ' ' $type >> $mib
endif

echo -n is $object read-only or read-write\?
echo '   ' ACCESS ' ' "$<" >> $mib
echo '   ' STATUS ' ' mandatory >> $mib
echo '   ' DESCRIPTION >> $mib
echo .fi >> $mib
echo .in +.75i >> $mib
echo please describe $object, in quotes
echo CONTROL D terminates input
cat >> $mib
echo .in -.75i >> $mib

echo what section and paragragh of $document\?  '[just return if none]'
set reference = "$<"
if ("$reference" != "") then
    echo .nf >> $mib
    echo '   ' REFERENCE >> $mib
    echo .fi >> $mib
    echo .in +.75i >> $mib
    echo \"$document $reference\" >> $mib
    echo .in -.75i >> $mib
endif

echo -n what is the default value for $object\? '[just return if no default]'
set defval = "$<"
echo .nf >> $mib
if ("$defval" != "") then
    echo '   ' DEFVAL \{ $defval \} >> $mib
endif

echo '    ::= {' $entry $identifier '}' >> $mib
echo '.)b' >> $mib
echo '' >> $mib
