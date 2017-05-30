/******************************************************************************/
// easel_ES920_Callback_test.c - easel_ES920_Callback_test file
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
int keyhandler(void);
void handler(int);
void easel_ES920_newline_remove(char *);
void easel_ES920_checksum_remove(char *);
int easel_ES920_csv_write(char *fdate, short rx_pwr, char *data, char ret[], int qch, int ibw, int qsf);
int nullcheck(const char *str);

int main(int argc, char **argv)
{
	int iRet;

	char DevName1[26] = "/dev/ttyO3";
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
	int qown=0;
	int qdst=1;
	int qack=EASEL_ES920_ACK_ON;
	int qret=0;
	int qbaud=EASEL_ES920_BAUD_115200;
	int qslep=EASEL_ES920_SLEEP_OFF;
	//int qslep=EASEL_ES920_SLEEP_INTERRUPT_WAKEUP;
	int qsleptm=50;
	int qpwr=13;
	unsigned int qcnt=100;

	// 920MHz Setting Int
	int inode=EASEL_ES920_NODE_ENDDEVICE;
	int ibw=EASEL_ES920_BANDWIDTH_125K;

	// マルチホップ対応
	int src_id = 0;
	int src_addr = 0;

	// CSV設定
	char fdate[64] = {0};
	short  rx_pwr = 0;
	char str = '0';
	char test_ret[3] = {0};

	// CheckSum
	int iRecvChksum = 0, iSendChksum = 0;
	int cRecvSize = 0;
	int iChksum = 0;
	int cMsgSize = 0;

	BYTE multi64bitAddr[8]={0};

	// 結果表示
	int ok_cnt = 0;
	int ng_cnt = 0;
	int total_cnt = 0;

	// シリアル通信ウェイト時間
	int waitMsecTime = 0;

	// CSVの時刻を設定
	struct tm *tm;
	time_t t = time(NULL);
	tm = localtime(&t);
	strftime(fdate,sizeof(fdate),"%Y%m%d%H%M.csv",tm);

	// Debug Msg
	char Debug_OK[4] = "OK";
	char Debug_NG[4] = "NG";

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
					//printf(" -c[Count]\n");
					//printf(" -r[Retry Count]\n");
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
					printf("    -qcnt=[recvcount]\n");
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
						strcpy(cMsg, &argv[i][2]);
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
		else
		{
			printf("Please specify an argument\n\n");

			printf("Version : %s \n", APP_VERSION );
			printf("Version : %s \n", APP_VERSION );
			printf("easel_ES920_through test [options]\n");
			printf("options:\n");
			printf(" -b[baudrate]\n");
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
			printf("    -qcnt=[recvcount]\n");
			printf("Usage:\n");
			printf("Antenna type internal [0] external [1]\n");
			printf("infinite loop [-1]\n");
			return 0;
		}
	//}

	printf("Wait = %dms Cnt = %ld\n", iWait, iCnt);

	// 設定値の妥当性を確認
	// Data
	int cMsglen = strlen(cMsg);
	if(cMsglen < 0 || cMsglen > 47)	ret = -1;
	//printf("Debug Data chk = %d\n",ret);
	// sf
	if(qsf < 7 || qsf > 12) ret = -1;
	//printf("Debug sf chk = %d\n",ret);
	// chaneel
	if(qch < 1 || qch > 15) ret = -1;
	//printf("Debug chaneel chk = %d\n",ret);
	// panid
	if(qpan < 1 || qpan > 9999) ret = -1;
	//printf("Debug panid chk = %d\n",ret);
	// ownid
	if(qown < 0 || qown > 9999) ret = -1;
	//printf("Debug ownid chk = %d\n",ret);
	// dstid
	if(qdst < 0 || qdst > 9999) ret = -1;
	//printf("Debug dstid chk = %d\n",ret);
	// ack
	if(qack < 1 || qack > 2) ret = -1;
	//printf("Debug ack chk = %d\n",ret);
	// retry
	if(qret < 0 || qret > 10) ret = -1;
	//printf("Debug retry chk = %d\n",ret);
	// sleep
	if(qslep < 1 || qslep > 3) ret = -1;
	//printf("Debug sleep chk = %d\n",ret);
	// sleeptime
	if(qsleptm < 1 || qsleptm > 86400) ret = -1;
	//printf("Debug sleeptime chk = %d\n",ret);
	// power
	if(qpwr < -4 || qpwr > 13) ret = -1;
	//printf("Debug power chk = %d\n",ret);
	// count
	if(qcnt < 1 || qcnt > 65535) ret = -1;
	//printf("Debug count chk = %d\n",ret);

	if(ret){
		printf("param error\n");
		return ret;
	}

	//Debug add
	//return 0;

	//Initialization
	iRet = easel_ES920_init(DevName1,ibaudrate);
	if( iRet ){
		printf("DevName1: open error\n");
		easel_ES920_Debug_write(fdate, 0, Debug_NG, qch, ibw, qsf);
		return 1;
	}
	else
	{
		easel_ES920_Debug_write(fdate, 0, Debug_OK, qch, ibw, qsf);
	}

	// 設定モード要求
	iRet = SettingRequest();
	if(iRet){
		printf("CAN'T MOVE ON CONFIGURATION MODE\n");
		easel_ES920_Debug_write(fdate, 1, Debug_NG, qch, ibw, qsf);
		iRet = easel_ES920_exit();
		return 1;
	}
	else
	{
		easel_ES920_Debug_write(fdate, 1, Debug_OK, qch, ibw, qsf);
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
	else if( strcmp(qbw,"250k") == 0 ) ibw = EASEL_ES920_BANDWIDTH_250K;
	else if( strcmp(qbw,"500k") == 0 ) ibw = EASEL_ES920_BANDWIDTH_500K;
	else if( strcmp(qbw,"62.5k") == 0 ) ibw = EASEL_ES920_BANDWIDTH_62500;

	qbaud = EASEL_ES920_BAUDRATE(ibaudrate);

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
		easel_ES920_Debug_write(fdate, 2, Debug_NG, qch, ibw, qsf);
		return 1;
	}
	else
	{
		easel_ES920_Debug_write(fdate, 2, Debug_OK, qch, ibw, qsf);
	}

	// 動作モード要求
	iRet = RunRequest();
	if(iRet){
		printf("CAN'T MOVE ON OPERATION MODE\n");
		iRet = easel_ES920_exit();
		easel_ES920_Debug_write(fdate, 3, Debug_NG, qch, ibw, qsf);
		return 1;
	}
	else
	{
		easel_ES920_Debug_write(fdate, 3, Debug_OK, qch, ibw, qsf);
	}

	printf("----- OPERATION MODE ------\n");

	// シリアル通信のウェイト時間を定義
	// マージン x BIT x 最大受信文字列長 x msec ) / ボーレート
	waitMsecTime = (2 * 10 * 62 * 1000) / ibaudrate;
	easel_ES920_set_serial_wait(waitMsecTime);
	printf("%d = set serial wait time\n", waitMsecTime);

	// シグナルハンドラ設定
	if (SIG_ERR == signal(SIGINT, handler)) {
		printf("failed tio set signal handler\n");
		return 1;
	}

	//CSVの時刻を設定
	//struct tm *tm;
	//time_t t = time(NULL);
	//tm = localtime(&t);
	//strftime(fdate,sizeof(fdate),"%Y%m%d%H%M.csv",tm);

	// 初回の受信側の準備待ち
	int count = 0;
	int sleep_cnt = 0;

	while(sig_cnt == 0){
		//printf("Debug 1\n");
		if(Keyhandler()) {
			printf("catch push key\n");
			break;
		}

		if(qslep == EASEL_ES920_SLEEP_INTERRUPT_WAKEUP)
		{
			if(sleep_cnt % 2 == 0)
			{
				system("sudo ./onoff.sh 0");
				printf("Sleep Mode ON\n");
			}
			else
			{
				system("sudo ./onoff.sh 1");
				printf("Sleep Mode OFF\n");
			}
			sleep(3);
			sleep_cnt++;
		}
		else
		{
			//printf("Debug 2\n");
			//DATA FROM EASEL to
			memset(cRecv,'\0',sizeof(cRecv));
			iRet = RecvTelegram(cRecv, &rx_pwr, &src_id, &src_addr);
			//printf("Debug 3\n");
			if(iRet > 0)
			{

				// 受信データから不要な改行を除去
				easel_ES920_newline_remove(cRecv);
				// 受信データから不要なチェックサムを除去
				easel_ES920_checksum_remove(cRecv);

				printf("send back receive data\n");

				cMsgSize = strlen(cRecv);
				printf("send size : %d \n", cMsgSize);

				if( cMsgSize >= 1 ){
					iChksum = Serial_SumCheck(cRecv, cMsgSize, 1);

					sprintf(cMsg, "%s%03d",cRecv, iChksum);
					cMsgSize += 3;
				}else{
					strcpy(cMsg, cRecv);
				}

				printf("Data : %s \r\n", cMsg);
				// 受信データを折り返し送信
				//SendTeregram(cMsg,0, 0);

				strcpy(test_ret,"OK");
				easel_ES920_csv_write(fdate, rx_pwr, cRecv, test_ret, qch, ibw, qsf);

				memset(cMsg, 0x00, cMsgSize );
			}

			//usleep(500000);
			usleep(250000);
			//usleep(100000);
			//sleep(1);
		}
	}

	easel_ES920_exit();
	printf("ES920 Port Closed...\n");

	system("sudo ./reset_usb_mcs341.sh");

	return 0;
}

// 最後に入る改行コードを除去する関数
void easel_ES920_newline_remove(char *str)
{
	char *p;
	p = strchr(str, '\r');
	if(p != NULL) {
		*p = '\0';
	}
}

// 最後に入るチェックサムを除去する関数
void easel_ES920_checksum_remove(char *str)
{
	unsigned char tmp[50] = {0};
	int len;
	int i;
	len = strlen(str);

	for(i = 0; i <(len-3); i++)
	{
		tmp[i] = str[i];
	}

	memset(&str[len-3], 0x00, 3);

	strcpy(str,tmp);
}

// CSV書き込み関数
int easel_ES920_csv_write(char *fdate, short rx_pwr, char *data, char ret[], int qch, int ibw, int qsf)
{
	FILE *fp;
	struct tm *tm;

	char date[64];
	char *fpwd = "/home/conprosys/niimi/ES920_Callback/";
	char fch[2];
	char fbw[2];
	char fsf[2];
	sprintf(fch,"%d",qch);
	sprintf(fsf,"%d",qsf);

	switch (ibw)	{
		case 4 :
			sprintf(fbw,"%d",125);
			break;
		case 5 :
			sprintf(fbw,"%d",250);
			break;
		case 6 :
			sprintf(fbw,"%d",500);
			break;
	}

	char fname[256];

	time_t t = time(NULL);
	tm = localtime(&t);
	strftime(date, sizeof(date), "%m/%d %a %H:%M:%S", tm);
	sprintf(fname,"%s%s_%s_%s_%s",fpwd,fch,fbw,fsf,fdate);

	fp = fopen(fname, "a");
	if(fp == NULL){
		printf("%s file open error\n", fname);
		return -1;
	}

	fprintf(fp, "%s,%d,%s,%s\n", date,rx_pwr,data,ret);
	fclose(fp );

	printf("%s file write finished\n", fname);
	return 0;
}


int easel_ES920_Debug_write(char *fdate, int num, char ret[], int qch, int ibw, int qsf)
{
	FILE *fp;
	struct tm *tm;

	char date[64];
	char *fpwd = "/home/conprosys/niimi/ES920_Callback/";
	char fch[2];
	char fbw[2];
	char fsf[2];
	sprintf(fch,"%d",qch);
	sprintf(fsf,"%d",qsf);

	switch (ibw)	{
			case 3 :
			sprintf(fbw,"%d",62);
			break;
		case 4 :
			sprintf(fbw,"%d",125);
			break;
		case 5 :
			sprintf(fbw,"%d",250);
			break;
		case 6 :
			sprintf(fbw,"%d",500);
			break;
	}

	char fname[256];

	time_t t = time(NULL);
	tm = localtime(&t);
	strftime(date, sizeof(date), "%m/%d %a %H:%M:%S", tm);
	sprintf(fname,"%s%s_%s_%s_%s",fpwd,fch,fbw,fsf,fdate);

	fp = fopen(fname, "a");
	if(fp == NULL){
		printf("%s file open error\n", fname);
		return -1;
	}

	fprintf(fp, "%s,%d,%s\n", date,num,ret);
	fclose(fp );

	printf("%s file write finished\n", fname);
	return 0;
}

// シグナルハンドラ
void handler(int sig) {
	printf("catch signal %d\n", sig);
	sig_cnt++;
}

// Keyハンドラ
int Keyhandler(void) {
	struct termios oldt, newt;
	int ch;
	int oldf;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	ch = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);

	if(ch != EOF) {
		ungetc(ch, stdin);
		return 1;
	}

	return 0;
}

// NULLチェック
int nullcheck(const char *str) {
	if (str == NULL) {
		return TRUE;
	}
	if (strlen(str) == 0) {
		return TRUE;
	}

	return FALSE;
}
