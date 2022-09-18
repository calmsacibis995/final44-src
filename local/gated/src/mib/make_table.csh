#
#
#	$Id: make_table.csh,v 1.7 1992/07/29 03:09:51 jch Exp $
#
#    MIB Table/Group Maker
#
#	This is a file designed to create an input file for nroff,
#	includable in a MIB document by putting a line of the form
#
#	.so mibTableFile
#
#	into the boilerplate file.  This works on the principle of
#	conservation of boilerplate.
#
#	input variables:
#
#	$document	The document being instrumented
#	$mib		The name of the nroff input file
#	$group		The page heading text
set t = "Table"
set e = "Entry"
set g = "Group"
set embedded_table = ()
#
#	make_table "$object[$i]" "$entry" "$i" "$document" 
#
if ("$#argv" == "4") then
    set document = "$4"
    set mib = "$1"
    echo .bp >> $mib
    echo This will go in the Table of Contents
    echo -n what is the title of the table\?
    set group = "$<"
    echo -n what is the nroff section 'number?' '(6.?)'
    set number = "$<"
    echo \.\$0 \"$group\" \"$number\" >> $mib
    echo  --\  $group >> $mib
    echo '' >> $mib
    echo describe the 'group;' these comments will head the $mib area
    echo remember to begin each line with the comment symbol '--'
    echo CONTROL D terminates input
    cat >> $mib
    echo '' >> $mib
    set table = "table"
else
    echo -n what document is this\?
    set document = "$<"
    echo -n what is the name of the '.so' file\?
    set mib = "$<"
    echo .bp >> $mib
    echo This will go in the Table of Contents
    echo -n what is the title of the table or 'group?'
    set group = "$<"
    echo -n what is the nroff section 'number?' '(6.?)'
    set number = "$<"
    echo \.\$0 \"$group\" \"$number\" >> $mib
    echo  --\  $group >> $mib
    echo '' >> $mib
    echo describe the 'group;' these comments will head the $mib area
    echo remember to begin each line with the comment symbol '--'
    echo CONTROL D terminates input
    cat >> $mib
    echo '' >> $mib
    echo -n is this a group or a 'table?'
    set table = "$<"
endif

#
# describe the Table
#
if ("table" == "$table") then
#
#	Get description of Table
#
    echo by 'convention', a table or group has an identifying header that
    echo is part of every object name inside 'it,' like the IP Group
    echo contains the ipNetToMediaTable and the 'ipRouteTable,' and the
    echo ipRouteTable specifies the ipRouteEntry and in turn the
    echo 'ipRouteNextHop.' the base name for the IP Group is "'ip'", and
    echo the base name for the ipRouteTable is 'ipRoute.'
    echo ''
    echo -n what is the base 'name?'
    set base = "$<"
    set table = "$base$t"
    set entry = "$base$e"
    set sequence = `entryname $entry`

    echo $table OBJECT-TYPE >> $mib
    echo '   ' SYNTAX ' ' SEQUENCE OF $sequence >> $mib
    echo '   ' ACCESS ' ' not-accessible >> $mib
    echo '   ' STATUS ' ' mandatory >> $mib
    echo '   ' DESCRIPTION >> $mib
    echo .fi >> $mib
    echo .in +.75i >> $mib
    echo please describe the $table, in quotes
    echo CONTROL D terminates input
    echo this is probably something of the form '"A list of ..."'
    cat >> $mib
    echo .in -.75i >> $mib
    echo .nf >> $mib
    echo '   ' REFERENCE >> $mib
    echo .fi >> $mib
    echo .in +.75i >> $mib
    echo please tell me what section and paragraph of $document
    echo is being instrumented by the $table\?
    echo \"$document "$<"\" >> $mib
    echo .in -.75i >> $mib
    echo .nf >> $mib
    if ("$#argv" == "4") then
        echo '    ::= {' $2 $3 '}' >> $mib
    else
        echo -n what is the ASN.1 description for $table\?
        echo '    ::= {' "$<" '}' >> $mib
    endif
    echo '' >> $mib
#
#	Describe the Entry
#
    echo $entry OBJECT-TYPE >> $mib
    echo '   ' SYNTAX ' ' $sequence >> $mib
    echo '   ' ACCESS ' ' not-accessible >> $mib
    echo '   ' STATUS ' ' mandatory >> $mib
    echo '   ' DESCRIPTION >> $mib
    echo .fi >> $mib
    echo .in +.75i >> $mib
    echo please describe the $entry, in quotes
    echo CONTROL D terminates input
    echo this is probably something of the form '"A single ..."'
    cat >> $mib
    echo .in -.75i >> $mib
    echo .nf >> $mib
    echo an instance is one or more of the variables in the entry,
    echo separated by 'commas,' telling me how to specifically get the one
    echo I want.
    echo -n how do you instantiate $entry\?
    echo '   ' INDEX '{' "$<" '}' >> $mib
    echo '    ::= {' $table 1 '}' >> $mib
    echo '' >> $mib
    echo $sequence '::=' >> $mib
    echo '    SEQUENCE {' >> $mib
else
#
#	Get description of Group
#
    set table = ""
    echo -n what is the group\'s base 'name?'
    set base = "$<"
    set entry = "$base$g"
#
#	Describe a Group
#
    echo -n what is the ASN.1 description for $entry\?
    echo $entry OBJECT-TYPE '::= {' "$<" '}' >> $mib
    echo '' >> $mib
endif


#
#	Build the SEQUENCE
#
echo -n how many objects are there in $entry\?
set highest = "$<"
set enumeration = `count $highest`
set object = ()
set type = ()
foreach i ($enumeration)
    echo -n name object $i ':' $base
    set part = "$<"
    set object = ($object:q "$base$part")
    echo -n what type is $object[$i]\?
    set type = ($type:q "$<")
    if ("$table" != "") then
        echo '       ' $object[$i] >> $mib
        if ("$i" == "$highest") then
            echo '           ' $type[$i] >> $mib
        else
            echo '           ' $type[$i], >> $mib
        endif
    endif
end
if ("$table" != "") then
    echo '}' >> $mib
    echo '' >> $mib
endif

#
#	Build the various Object Descriptions
#
foreach i ($enumeration) 
    if ("$type[$i]" == "TABLE") then
	set embedded_table = ($embedded_table:q "$object[$i]")
	set echo
        make_table "$object[$i]" "$entry" "$i" "$document" 
	unset echo
    else
        make_object "$object[$i]" "$type[$i]" "$entry" "$i" "$mib" "$document" 
    endif
end
#
#	import the embedded tables
#
foreach i ($embedded_table)
	echo .so $i >> $mib
end
