/******************************************************************************/
// easel_ES920_Send_test.c - easel_ES920_Send_test file
/******************************************************************************/

/*
-- Copyright (c) 2017 tomoyuki niimi

-- Permission is hereby granted, free of charge, to any person obtaining a copy
-- of this software and associated documentation files (the "Software"), to deal
-- in the Software without restriction, including without limitation the rights
-- to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
-- copies of the Software, and to permit persons to whom the Software is
-- furnished to do so, subject to the following conditions:
--
-- The above copyright notice and this permission notice shall be included in
-- all copies or substantial portions of the Software.
--
-- THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
-- IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
-- FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
-- AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
-- LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
-- OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
-- THE SOFTWARE.
--
*/
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/serial.h>
#include <time.h>
#include <sys/time.h>
#include "libeasel_ES920.h"
#include "easel_ES920.h"

#define APP_VERSION "1.0.0"

static volatile int sig_cnt = 0;

// プロトタイプ宣言
void handler(int);

int main(int argc, char **argv)
{
	int iRet;

	char DevName1[26] = "/dev/ttyO3";
	char cSend[512] = "1234567890abcdefghijklmnopqrstuvwxyz";
	char cMsg[512] = {0};
	unsigned char cRecv[50] = {0};
	int i = 1;
	int ret = 0;
	int sig = 0;
	int cnt = 1;
	int cntOK = 0, cntNG = 0;
	int Antenna = 0;
	long iCnt = 1;
	long Retrycnt = 20;
	int iWait = 700;
	int ibaudrate = 115200;

	// 920MHz Setting String
	char qnode[12]="";
	char qbw[6]="";
	int qsf=EASEL_ES920_SPREADINGFACTOR_7;
	int qch=1;
	int qpan=1;
	int qown=1;
	int qdst=0;
	int qack=EASEL_ES920_ACK_ON;
	int qret=0;
	int qbaud=EASEL_ES920_BAUD_115200;
	int qslep=EASEL_ES920_SLEEP_OFF;
	int qsleptm=50;
	int qpwr=13;
	int qcnt=100;

	// 920MHz Setting Int
	int inode=EASEL_ES920_NODE_ENDDEVICE;
	int ibw=EASEL_ES920_BANDWIDTH_125K;

	// マルチホップ対応
	int src_id = 0;
	int src_addr = 0;

	// CSV設定
	char *fname = "/home/conprosys/niimi/ES920LR.csv";
	unsigned int  rx_pwr = 0;
	char str = '0';
	char *test_ret = NULL;

	// CheckSum
	int iChksum = 0;
	int cMsgSize = 0;

	BYTE multi64bitAddr[8]={0};

	//if( argc >= 2 ){

	//	strcpy( DevName1, argv[1] );

		if( argc >= 2 ){

			// 引数解析
			while(i < argc){
				printf("[%d] %s\n", i, argv[i]);

				//help
				if(strncmp(argv[i], "--help", strlen("--help")) == 0 ){
					printf("Version : %s \n", APP_VERSION );
					printf("easel_ES920_through test [options]\n");
					printf("options:\n");
					printf(" -b[baudrate]\n");
					printf(" -c[Count]\n");
					printf(" -r[Retry Count]\n");
					printf(" -d[Data]\n");
					printf(" -D[device node]\n");
					printf(" -w[Wait(ms)]\n");
					printf(" -q[920MHz Option]\n");
					printf("    -qn=[node]\n");
					printf("    -qbw=[bandwidth]\n");
					printf("    -qsf=[sf]\n");
					printf("    -qc=[channel]\n");
					printf("    -qpid=[panid]\n");
					printf("    -qoid=[ownid]\n");
					printf("    -qdid=[dstid]\n");
					printf("    -qa=[ack]\n");
					printf("    -qr=[retry]\n");
					printf("    -qsl=[sleep]\n");
					printf("    -qst=[sleeptime]\n");
					printf("    -qpwr=[power]\n");
					printf("    -qcnt=[sendcount]\n");
					printf("Usage:\n");
					printf("Antenna type internal [0] external [1]\n");
					printf("infinite loop [-1]\n");
					return 0;
				}

				// Cnt
				if(strncmp(argv[i], "-c", strlen("-c")) == 0){
					if(sscanf(argv[i], "-c%ld", &iCnt) != 1){
						ret = -1;
					}
				}

				// Retrycnt
				if(strncmp(argv[i], "-r", strlen("-r")) == 0){
					if(sscanf(argv[i], "-r%ld", &Retrycnt) != 1){
						ret = -1;
					}
				}

				// baudrate
				if(strncmp(argv[i], "-b", strlen("-b")) == 0){
					if(sscanf(argv[i], "-b%d", &ibaudrate) != 1){
						ret = -1;
					}
				}

				// Wait
				if(strncmp(argv[i], "-w", strlen("-w")) == 0){
					if(sscanf(argv[i], "-w%d", &iWait) != 1){
						ret = -1;
					}
				}

				// Data
				if(strncmp(argv[i], "-d", strlen("-d")) == 0){
				 	if(strlen(argv[i]) > 2){
						strcpy(cSend, &argv[i][2]);

						// 暫定処置
						if( strlen(cSend) > 47 ){
							ret = -1;
						}

					}
				}

				// Device
				if(strncmp(argv[i], "-D", strlen("-D")) == 0){
				 	if(strlen(argv[i]) > 2){
						strcpy(DevName1, &argv[i][2]);
					}
				}

				//920MHz Parameter settings
				if(strncmp(argv[i], "-q", strlen("-q")) == 0){

					//node
					if(strncmp(argv[i], "-qn=", strlen("-qn=")) == 0){
				 		if(sscanf(argv[i], "-qn=%s", qnode) != 1){
							ret = -1;
						}
					}

					//bandwidth
					if(strncmp(argv[i], "-qbw=", strlen("-qbw=")) == 0){
						if(sscanf(argv[i], "-qbw=%s", qbw) != 1){
							ret = -1;
						}
					}

					//sf
					if(strncmp(argv[i], "-qsf=", strlen("-qsf=")) == 0){
						if(sscanf(argv[i], "-qsf=%d", &qsf) != 1){
							ret = -1;
						}
					}
					// channel
					if(strncmp(argv[i], "-qc=", strlen("-qc=")) == 0){
						if(sscanf(argv[i], "-qc=%d", &qch) != 1){
							ret = -1;
						}

					}
					// Pan ID
					if(strncmp(argv[i], "-qpid=", strlen("-qpid=")) == 0){
						if(sscanf(argv[i], "-qpid=%d", &qpan) != 1){
							ret = -1;
						}

					}
					//
					if(strncmp(argv[i], "-qoid=", strlen("-qoid=")) == 0){
						if(sscanf(argv[i], "-qoid=%d", &qown) != 1){
							ret = -1;
						}
					}

					if(strncmp(argv[i], "-qdid=", strlen("-qdid=")) == 0){
						if(sscanf(argv[i], "-qdid=%d", &qdst) != 1){
							ret = -1;
						}
					}

					if(strncmp(argv[i], "-qa=", strlen("-qa=")) == 0){
						if(sscanf(argv[i], "-qa=%d", &qack) != 1){
							ret = -1;
						}
					}

					if(strncmp(argv[i], "-qr=", strlen("-qr=")) == 0){
						if(sscanf(argv[i], "-qr=%d", &qret) != 1){
							ret = -1;
						}
					}

					if(strncmp(argv[i], "-qsl=", strlen("-qsl=")) == 0){
						if(sscanf(argv[i], "-qsl=%d", &qslep) != 1){
							ret = -1;
						}
					}

					if(strncmp(argv[i], "-qst=", strlen("-qst=")) == 0){
						if(sscanf(argv[i], "-qst=%d", &qsleptm) != 1){
							ret = -1;
						}
					}

					if(strncmp(argv[i], "-qpwr=", strlen("-qpwr=")) == 0){
						if(sscanf(argv[i], "-qpwr=%d", &qpwr) != 1){
							ret = -1;
						}
					}

					if(strncmp(argv[i], "-qcnt=", strlen("-qcnt=")) == 0){
						if(sscanf(argv[i], "-qcnt=%d", &qcnt) != 1){
							ret = -1;
						}
					}
				}

				i++;
			}
			if(ret){
				printf("param error\n");
				return ret;
			}
		}
	//}

	printf("Wait = %dms Cnt = %ld\n", iWait, iCnt);

	//Initialization
	iRet = easel_ES920_init(DevName1,ibaudrate);
	if( iRet ){
		printf("DevName1: open error\n");
		return 1;
	}

	// 設定モード要求
	iRet = SettingRequest();
	if(iRet){
		printf("CAN'T MOVE ON CONFIGURATION MODE\n");
		iRet = easel_ES920_exit();
		return 0;
	}

	// String→Int変換
	// ノード種別設定
	if( strcmp(qnode,"master") == 0 ||
		strcmp(qnode,"parent") == 0 ||
		strcmp(qnode,"coordinator") == 0 )	inode = EASEL_ES920_NODE_COORDINATOR;
	else if( strcmp(qnode,"slave") == 0 ||
			strcmp(qnode,"child") == 0 ||
			strcmp(qnode,"enddevice") == 0 ) inode = EASEL_ES920_NODE_ENDDEVICE;

	// 帯域幅設定
	if( strcmp(qbw,"125k") == 0 )	ibw = EASEL_ES920_BANDWIDTH_125K;
	else if( strcmp(qbw,"250k") == 0 )	ibw = EASEL_ES920_BANDWIDTH_250K;
	else if( strcmp(qbw,"500k") == 0 )	ibw = EASEL_ES920_BANDWIDTH_500K;

	qbaud = EASEL_ES920_BAUDRATE(ibaudrate);
	//printf("qbaud = %d\n", qbaud);
	// 無線設定要求
	iRet = easel_ES920_set_wireless(
			inode,
			ibw,
			qsf,
			qch,			//Channel: 1
			qpan,			//Panid : 0x0001
			qown,			//Ownid : 0x0001
			qdst,			//Dstid : 0x0000
			qack,  			//1
			qret,			//Rettry: 3
			EASEL_ES920_TRASMOD_PAYLOAD,
			EASEL_ES920_RCVID_ON,
			EASEL_ES920_RSSI_ON,
			EASEL_ES920_MODE_OPERATION,
			qbaud,
			qslep,
			qsleptm,		//Sleep time: 50
			qpwr			//Power: 13dBm
	);
	if(iRet){
		printf("CAN'T SET WIRELESS DATA\n");
		iRet = easel_ES920_exit();
		return 0;
	}

	// 動作モード要求
	iRet = RunRequest();
	if(iRet){
		printf("CAN'T MOVE ON OPERATION MODE\n");
		iRet = easel_ES920_exit();
		return 0;
	}

	printf("----- OPERATION MODE ------\n");

	// シグナルハンドラ設定
	if (SIG_ERR == signal(SIGINT, handler)) {
		printf("failed tio set signal handler\n");
		return 1;
	}

	// 初回の受信側の準備待ち
	int count = 0;
	
	while(sig_cnt == 0){

		printf("Current count = %d, Set count = %d\n", count,qcnt);

		if(count == qcnt)
		{
			break;
		}
		

		cMsgSize = strlen(cSend);
		printf("send size : %d \n", cMsgSize);

		if( cMsgSize >= 1 ){
			iChksum = Serial_SumCheck( cSend, cMsgSize, 1 );

			sprintf(cMsg, "%s%03d",cSend, iChksum);
			cMsgSize += 3;
		}else{
			strcpy(cMsg, cSend);
		}

		printf("Data : %s \r\n", cMsg);

		iRet = SendTeregram(cMsg,0, 0);

		count++;
		memset(cMsg, 0x00, cMsgSize );
		sleep(1);
	}

	easel_ES920_exit();
	printf("ES920 Port Closed...\n");

	system("sudo ./reset_usb_mcs341.sh");

	return 0;
}

// シグナルハンドラ
void handler(int sig) {
	printf("catch signal %d\n", sig);
	sig_cnt++;
}
