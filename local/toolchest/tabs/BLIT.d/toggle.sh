
#
#      Copyright (c) 1984, 1985 AT&T
#      All Rights Reserved
#
#      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
#      CODE OF AT&T.
#      The copyright notice above does not 
#      evidence any actual or intended
#      publication of such source code.
#
# A toggle program for netty icons.
ILIB=/a8/rgh/forms.d/BLIT.d
ILIB=/usr/dmd/icon/large

SWITCH1_ICON=1
SWITCH2_ICON=2
POS1=1
POS2=2

if [ $# = 0 ]
then
	send_netty -i $SWITCH1_ICON $ILIB/bigswitch1
	send_netty -i $SWITCH2_ICON $ILIB/bigswitch2
	send_netty -p $POS1 $SWITCH2_ICON "OFF" "toggle.sh $POS1 ON\r"
	send_netty -p $POS2 $SWITCH2_ICON "OFF" "toggle.sh $POS2 ON\r"
	exit 0
fi

if [ "$1" = $POS1 ]
then
	position=$POS1
else
	position=$POS2
fi
if [ "$2" = "OFF" ]
then
	title="OFF"
	ret="toggle.sh $position ON\r"
	icon=$SWITCH2_ICON
else
	title="ON"
	ret="toggle.sh $position OFF\r"
	icon=$SWITCH1_ICON
fi
send_netty -p $position $icon "$title" "$ret"
