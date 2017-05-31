#!/bin/sh

cnt=$2
timeout=$3
senddata=0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ012345678

case $1 in
1) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=12 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddata
 ;;
2) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=10 -qsf=12 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddata
 ;;
3) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=0 -qsf=12 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddata
 ;;
4) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=7 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddata
 ;;
5) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=8 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddata
 ;;
6) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=9 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddata
 ;;
7) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=10 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddata
 ;;
8) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=11 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddata
 ;;
9) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=12 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddata
 ;;
10) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=11 -qbw=62.5k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddata
 ;;
11) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=11 -qbw=250k -qc=4 -qcnt=$cnt -qrcnt=$timeout -d$senddata
 ;;
12) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=11 -qbw=500k -qc=3 -qcnt=$cnt -qrcnt=$timeout -d$senddata
 ;;
13) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=12 -qbw=125k -qc=1 -qcnt=$cnt -qrcnt=$timeout -d$senddata
 ;;
14) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=12 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddata
 ;;
23) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=12 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddata
 ;;
24) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=7 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddata
 ;;
25) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=8 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddata
 ;;
26) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=9 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddata
 ;;
27) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=10 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddata
 ;;
28) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=11 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddata
 ;;
30) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=11 -qbw=62.5k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddata
 ;;
31) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=11 -qbw=250k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddata
 ;;
32) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=11 -qbw=500k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddata
 ;;
33) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=12 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddata
 ;;
34) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=7 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddata
 ;;
35) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=8 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddata
 ;;
36) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=9 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddata
 ;;
37) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=10 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddata
 ;;
38) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=11 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddata
 ;;
40) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=11 -qbw=62.5k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddata
 ;;
41) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=11 -qbw=250k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddata
 ;;
42) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=11 -qbw=500k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddata
 ;;
esac
