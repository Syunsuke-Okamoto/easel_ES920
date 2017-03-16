#!/bin/sh

PROGRAM_DIR="/home/conprosys/niimi/ES920_Send"
PROGRAM_NAME="gpmc_testd"

#gpioreset
$PROGRAM_DIR/$PROGRAM_NAME -w1 3 f > /dev/null 2>&1

$PROGRAM_DIR/$PROGRAM_NAME -w1 3 7 > /dev/null 2>&1
sleep 1
$PROGRAM_DIR/$PROGRAM_NAME -w1 3 3 > /dev/null 2>&1
sleep 1

sleep 10

#DIRECTION
#$PROGRAM_DIR/$PROGRAM_NAME -w1 2 f > /dev/null 2>&1

#Reset
$PROGRAM_DIR/$PROGRAM_NAME -w1 3 7 > /dev/null 2>&1

sleep 1

#
$PROGRAM_DIR/$PROGRAM_NAME -w1 3 f > /dev/null 2>&1
sleep 3

#$PROGRAM_DIR/$PROGRAM_NAME -w1 3 2f > /dev/null 2>&1

#sleep 10
