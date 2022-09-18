#!/bin/csh -f
dd if=$1 of=$2 ibs=32 skip=1 obs=1024b
