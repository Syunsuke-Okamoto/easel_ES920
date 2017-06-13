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
83) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=12 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddata
;;
84) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=7 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddata
;;
85) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=8 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddata
;;
86) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=9 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddata
;;
87) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=10 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddata
;;
88) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=11 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddata
;;

143) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=12 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddata -qa=2
;;
144) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=7 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddata -qa=2
;;
145) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=8 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddata -qa=2
;;
146) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=9 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddata -qa=2
;;
147) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=10 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddata -qa=2
;;
148) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=11 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddata -qa=2
;;
153) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=12 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddatab
;;
154) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=7 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddatab
;;
155) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=8 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddatab
;;
156) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=9 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddatab
;;
157) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=10 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddatab
;;
158) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=11 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddatab
;;
163) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=12 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddatab -qa=2
;;
164) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=7 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddatab -qa=2
;;
165) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=8 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddatab -qa=2
;;
166) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=9 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddatab -qa=2
;;
167) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=10 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddatab -qa=2
;;
168) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=-4 -qsf=11 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddatab -qa=2
;;

243) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=12 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddata -qa=2
;;
244) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=7 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddata -qa=2
;;
245) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=8 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddata -qa=2
;;
246) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=9 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddata -qa=2
;;
247) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=10 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddata -qa=2
;;
248) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=11 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddata -qa=2
;;
253) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=12 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddatab
;;
254) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=7 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddatab
;;
255) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=8 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddatab
;;
256) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=9 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddatab
;;
257) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=10 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddatab
;;
258) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=11 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddatab
;;
263) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=12 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddatab -qa=2
;;
264) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=7 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddatab -qa=2
;;
265) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=8 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddatab -qa=2
;;
266) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=9 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddatab -qa=2
;;
267) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=10 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddatab -qa=2
;;
268) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=11 -qbw=125k -qc=8 -qcnt=$cnt -qrcnt=$timeout -d$senddatab -qa=2
;;
343) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=12 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddata -qa=2
;;
344) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=7 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddata -qa=2
;;
345) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=8 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddata -qa=2
;;
346) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=9 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddata -qa=2
;;
347) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=10 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddata -qa=2
;;
348) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=11 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddata -qa=2
;;
353) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=12 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddatab
;;
354) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=7 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddatab
;;
355) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=8 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddatab
;;
356) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=9 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddatab
;;
357) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=10 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddatab
;;
358) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=11 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddatab
;;
363) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=12 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddatab -qa=2
;;
364) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=7 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddatab -qa=2
;;
365) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=8 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddatab -qa=2
;;
366) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=9 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddatab -qa=2
;;
367) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=10 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddatab -qa=2
;;
368) /home/conprosys/niimi/ES920_Throughput/ES920ThroughputTest -qpwr=13 -qsf=11 -qbw=125k -qc=15 -qcnt=$cnt -qrcnt=$timeout -d$senddatab -qa=2
;;


esac