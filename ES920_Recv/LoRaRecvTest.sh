#!/bin/sh

case $1 in
 0) /home/conprosys/niimi/ES920_Recv/ES920RecvTest -qpwr=13 -qsf=12 -qbw=125k -qc=8 -qcnt=$2
 ;;
 1) /home/conprosys/niimi/ES920_Recv/ES920RecvTest -qpwr=13 -qsf=12 -qbw=125k -qc=8
 ;;
 2) /home/conprosys/niimi/ES920_Recv/ES920RecvTest -qpwr=10 -qsf=12 -qbw=125k -qc=8
 ;;
 3) /home/conprosys/niimi/ES920_Recv/ES920RecvTest -qpwr=0 -qsf=12 -qbw=125k -qc=8
 ;;
 4) /home/conprosys/niimi/ES920_Recv/ES920RecvTest -qpwr=13 -qsf=7 -qbw=125k -qc=8
 ;;
 5) /home/conprosys/niimi/ES920_Recv/ES920RecvTest -qpwr=13 -qsf=8 -qbw=125k -qc=8
 ;;
 6) /home/conprosys/niimi/ES920_Recv/ES920RecvTest -qpwr=13 -qsf=9 -qbw=125k -qc=8
 ;;
 7) /home/conprosys/niimi/ES920_Recv/ES920RecvTest -qpwr=13 -qsf=10 -qbw=125k -qc=8
 ;;
 8) /home/conprosys/niimi/ES920_Recv/ES920RecvTest -qpwr=13 -qsf=11 -qbw=125k -qc=8
 ;;
 9) /home/conprosys/niimi/ES920_Recv/ES920RecvTest -qpwr=13 -qsf=12 -qbw=125k -qc=8
 ;;
 10) /home/conprosys/niimi/ES920_Recv/ES920RecvTest -qpwr=13 -qsf=11 -qbw=62.5k -qc=8
 ;;
 11) /home/conprosys/niimi/ES920_Recv/ES920RecvTest -qpwr=13 -qsf=11 -qbw=250k -qc=4
 ;;
 12) /home/conprosys/niimi/ES920_Recv/ES920RecvTest -qpwr=13 -qsf=11 -qbw=500k -qc=3
 ;;
 13) /home/conprosys/niimi/ES920_Recv/ES920RecvTest -qpwr=13 -qsf=12 -qbw=125k -qc=1
 ;;
 14) /home/conprosys/niimi/ES920_Recv/ES920RecvTest -qpwr=13 -qsf=12 -qbw=125k -qc=15
 ;;
 23) /home/conprosys/niimi/ES920_Recv/ES920RecvTest -qpwr=-4 -qsf=12 -dbw=125k -qc=8
 ;;
 24) /home/conprosys/niimi/ES920_Recv/ES920RecvTest -qpwr=-4 -qsf=7  -dbw=125k -qc=8
 ;;
 25) /home/conprosys/niimi/ES920_Recv/ES920RecvTest -qpwr=-4 -qsf=8  -dbw=125k -qc=8
 ;;
 26) /home/conprosys/niimi/ES920_Recv/ES920RecvTest -qpwr=-4 -qsf=9  -dbw=125k -qc=8
 ;;
 27) /home/conprosys/niimi/ES920_Recv/ES920RecvTest -qpwr=-4 -qsf=10 -dbw=125k -qc=8
 ;;
 28) /home/conprosys/niimi/ES920_Recv/ES920RecvTest -qpwr=-4 -qsf=11 -dbw=125k -qc=8
 ;;
 30) /home/conprosys/niimi/ES920_Recv/ES920RecvTest -qpwr=-4 -qsf=11 -dbw=62.5k -qc=8
 ;;
 31) /home/conprosys/niimi/ES920_Recv/ES920RecvTest -qpwr=-4 -qsf=11 -dbw=250k -qc=4
 ;;
 32) /home/conprosys/niimi/ES920_Recv/ES920RecvTest -qpwr=-4 -qsf=11 -dbw=500k -qc=3
 ;;
esac
