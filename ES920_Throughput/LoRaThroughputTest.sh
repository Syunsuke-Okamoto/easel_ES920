#!/bin/sh

cnt=100
cnt=$2
case $1 in
 1) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=12 -qbw=125k -qc=8 -qcnt=$cnt
 ;;
 2) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=10 -qsf=12 -qbw=125k -qc=8 -qcnt=$cnt
 ;;
 3) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=0 -qsf=12 -qbw=125k -qc=8 -qcnt=$cnt
 ;;
 4) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=7 -qbw=125k -qc=8 -qcnt=$cnt
 ;;
 5) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=8 -qbw=125k -qc=8 -qcnt=$cnt
 ;;
 6) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=9 -qbw=125k -qc=8 -qcnt=$cnt
 ;;
 7) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=10 -qbw=125k -qc=8 -qcnt=$cnt
 ;;
 8) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=11 -qbw=125k -qc=8 -qcnt=$cnt
 ;;
 9) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=12 -qbw=125k -qc=8 -qcnt=$cnt
 ;;
 10) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=11 -qbw=62.5k -qc=8 -qcnt=$cnt
 ;;
 11) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=11 -qbw=250k -qc=4 -qcnt=$cnt
 ;;
 12) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=11 -qbw=500k -qc=3 -qcnt=$cnt
 ;;
 13) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=12 -qbw=125k -qc=1 -qcnt=$cnt
 ;;
 14) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=12 -qbw=125k -qc=15 -qcnt=$cnt
 ;;
 23) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=12 -qbw=125k -qc=15 -qcnt=$cnt
 ;;
 24) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=7 -qbw=125k -qc=15 -qcnt=$cnt
 ;;
 25) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=8 -qbw=125k -qc=15 -qcnt=$cnt
 ;;
 26) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=9 -qbw=125k -qc=15 -qcnt=$cnt
 ;;
 27) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=10 -qbw=125k -qc=15 -qcnt=$cnt
 ;;
 28) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=11 -qbw=125k -qc=15 -qcnt=$cnt
 ;;
 30) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=11 -qbw=62.5k -qc=15 -qcnt=$cnt
 ;;
 31) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=11 -qbw=250k -qc=15 -qcnt=$cnt
 ;;
 32) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=11 -qbw=500k -qc=15 -qcnt=$cnt
 ;;
 33) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=12 -qbw=125k -qc=8 -qcnt=$cnt
 ;;
 34) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=7 -qbw=125k -qc=8 -qcnt=$cnt
 ;;
 35) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=8 -qbw=125k -qc=8 -qcnt=$cnt
 ;;
 36) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=9 -qbw=125k -qc=8 -qcnt=$cnt
 ;;
 37) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=10 -qbw=125k -qc=8 -qcnt=$cnt
 ;;
 38) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=11 -qbw=125k -qc=8 -qcnt=$cnt
 ;;
 40) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=11 -qbw=62.5k -qc=8 -qcnt=$cnt
 ;;
 41) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=11 -qbw=250k -qc=8 -qcnt=$cnt
 ;;
 42) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=11 -qbw=500k -qc=8 -qcnt=$cnt
 ;;
esac
