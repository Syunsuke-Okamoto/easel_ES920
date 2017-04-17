#!/bin/sh

PROGRAM_DIR="/home/conprosys/niimi/ES920_Callback"
PROGRAM_NAME="gpmc_testd"

case $1 in
	0)
		# 3G_IO_4 ON
		$PROGRAM_DIR/$PROGRAM_NAME -w 3 2f > /dev/null 2>&1
		;;
	1)
		# 3G_IO_4 OFF
		$PROGRAM_DIR/$PROGRAM_NAME -w 3 f > /dev/null 2>&1
		;;
esac



