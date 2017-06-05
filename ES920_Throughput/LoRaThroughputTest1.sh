#!/bin/sh

cnt=$2
timeout=$3
#payload 48
senddata=0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ012345678
#payload 10
senddatab=0123456

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
43) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=12 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddata -qa=2
 ;;
44) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=7 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddata -qa=2
 ;;
45) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=8 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddata -qa=2
 ;;
46) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=9 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddata -qa=2
 ;;
47) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=10 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddata -qa=2
 ;;
48) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=11 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddata -qa=2
 ;;
50) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=11 -qbw=62.5k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddata -qa=2
 ;;
51) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=11 -qbw=250k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddata -qa=2
 ;;
52) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=11 -qbw=500k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddata -qa=2
 ;;
53) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=12 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddatab
 ;;
54) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=7 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddatab
 ;;
55) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=8 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddatab
 ;;
56) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=9 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddatab
 ;;
57) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=10 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddatab
 ;;
58) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=11 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddatab
 ;;
60) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=11 -qbw=62.5k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddatab
 ;;
61) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=11 -qbw=250k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddatab
 ;;
62) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=11 -qbw=500k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddatab
 ;;
63) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=12 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddatab -qa=2
 ;;
64) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=7 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddatab -qa=2
 ;;
65) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=8 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddatab -qa=2
 ;;
66) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=9 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddatab -qa=2
 ;;
67) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=10 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddatab -qa=2
 ;;
68) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=11 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddatab -qa=2
 ;;
70) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=11 -qbw=62.5k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddatab -qa=2
 ;;
71) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=11 -qbw=250k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddatab -qa=2
 ;;
72) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=11 -qbw=500k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddatab -qa=2
 ;;
esac
