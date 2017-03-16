/***

	libeasel_ES920_func.c - EASEL_ES920_functions library

	Copyright (C) 2016  masayuki kubou, Syunsuke Okamoto.<okamoto@contec.jp>

***/

#ifndef __EASEL_ES920__
#define __EASEL_ES920__

#include <math.h>	// used function log2l
#include <pthread.h> // used pthread
#include <sys/queue.h> // used circle Q macros

// BOOL define
typedef unsigned int BOOL;
#define FALSE 0
#define TRUE 1

// BYTE define n
typedef unsigned char BYTE,*LPBYTE;
typedef unsigned short WORD,*LPWORD;
typedef unsigned long DWORD,*LPDWORD;  

#ifndef array_size
#define array_size(x)		(sizeof(x) / sizeof((x)[0]))
#endif

// EASEL
#define EASEL_ES920_INIT_TERMINAL 1		///< Mode : Terminal
#define EASEL_ES920_INIT_PROCESSOR 2	///< Mode:Processor

#define EASEL_ES920_NODE_COORDINATOR 1	///< node:Coordinator
#define EASEL_ES920_NODE_ENDDEVICE 2		///< node:EndDevice

#define EASEL_ES920_BANDWIDTH_31250 1		///< BandWidth: 31.25kHz
#define EASEL_ES920_BANDWIDTH_41700 2		///< BandWidth: 41.7kHz
#define EASEL_ES920_BANDWIDTH_62500 3		///< BandWidth: 62.5kHz
#define EASEL_ES920_BANDWIDTH_125K 4		///< BandWidth: 125kHz
#define EASEL_ES920_BANDWIDTH_250K 5		///< BandWidth: 250kHz
#define EASEL_ES920_BANDWIDTH_500K 6		///< BandWidth: 500kHz

#define EASEL_ES920_SF7 7		///< Spreading Factor: 7
#define EASEL_ES920_SF8 8		///< Spreading Factor: 8
#define EASEL_ES920_SF9 9		///< Spreading Factor: 9
#define EASEL_ES920_SF10 10		///< Spreading Factor: 10
#define EASEL_ES920_SF11 11		///< Spreading Factor: 11
#define EASEL_ES920_SF12 12   		///< Spreading Factor: 12

#define EASEL_ES920_ACK_ON  1		///< ACK : ON
#define EASEL_ES920_ACK_OFF  2		///< ACK : OFF

#define EASEL_ES920_TRASMOD_PAYLOAD 1	///< Transmode : Payload
#define EASEL_ES920_TRASMOD_FRAME 2	///< Transmode : Frame

#define EASEL_ES920_RCVID_ON 1		///< Receive Node ID information:	ON
#define EASEL_ES920_RCVID_OFF 2		///< Receive Node ID information:	OFF

#define EASEL_ES920_RSSI_ON 1 		///< RSSI information:	ON
#define EASEL_ES920_RSSI_OFF 2 		///< RSSI information:	OFF

#define EASEL_ES920_MODE_CONFIGRATION 1 	///< Configuration Mode
#define EASEL_ES920_MODE_OPERATION 2	 	///< Operation Mode

#define EASEL_ES920_BAUD_9600	 1	///< Baudrate:	9600
#define EASEL_ES920_BAUD_19200   2	///< Baudrate:	19200
#define EASEL_ES920_BAUD_38400   3	///< Baudrate:	38400
#define EASEL_ES920_BAUD_57600   4	///< Baudrate:	57600
#define EASEL_ES920_BAUD_115200  5	///< Baudrate:	115200
#define EASEL_ES920_BAUD_230400  6	///< Baudrate:	230400

#define EASEL_ES920_BAUDRATE( baudrate ) \
	( baudrate >= 57600 )?( log2( baudrate / 57600 ) + 4 ):( log2(baudrate / 9600 ) + 1 )

#define EASEL_ES920_SLEEP_OFF  1 	///< Sleep Mode:	OFF
#define EASEL_ES920_SLEEP_TIMER_WAKEUP 2 	///< Sleep Mode:	Timer Wakeup
#define EASEL_ES920_SLEEP_INTERRUPT_WAKEUP  3	///< Sleep Mode:	INT Wakeup

#define EASEL_ES920_COMMUNICATION_ASCII	1	///<  ASCII
#define EASEL_ES920_COMMUNICATION_BINARY	2	///<  Binary

typedef struct _easel_received_temp_buffer{
	int length;
	int state;		// '\r' ...1, '\n' ... 2, otherwize ... 0
	unsigned char data[124]; // 2message
}EASEL920_TEMPBUFFER, *PEASEL920_TEMPBUFFER;

typedef struct es920_ring_buffer{
	CIRCLEQ_ENTRY(es920_ring_buffer) entry;
	int rssi;
	unsigned int src_id;
	unsigned int src_addr;
	unsigned char data[50];
}EASEL920_READBUFFER, *PEASEL920_READBUFFER;

CIRCLEQ_HEAD(_es920_ring_buffer_head, es920_ring_buffer) es920_ring_buffer_head;

typedef struct __easelES920_param{
	int node;	///< node
	int bw;	///< band witdh
	int sf;	///< spread factor
	int ch;	///< channel
	int panid;	///< PAN ID
	int ownid;	///< Own ID
	int dstid;	///< Distination ID
	int ack;	///< Acknowlge
	int retry;	///< Retry
	int transmod;	///< Transfer Mode
	int rcvid;		///< receive ID
	int rssi;		///< RSSI
	int mode;		///< Mode
	int baudrate;	///< BaudRate
	int sleep;		///< sleep
	long sleeptime;	///< sleep time
	int power;

	// Serial Port func Parameter
	int SerialPort;	///< Serial Port
	int SerialWait;	///< Serial Port Wait

	// Application Parameter
	int app_comm_mode;	///< Communicatoin Mode ( 1: Ascii, 2: Binary )

	pthread_t read_id;

} EASEL920PARAM, *PEASEL920PARAM;


//Function
extern int easel_ES920_init(char* PortName,int iBaudrate);
extern int SendCommand(unsigned char buf[], int command );
extern int RecvCommandAck(void);
extern int easel_ES920_SetProcessorMode(char buf[], int command);
extern void easel_ES920_GetErrorString(int iRet,char *msg);
extern int easel_ES920_exit(void);


//RS232C
extern int rs232c_init(char* PortName);
extern int rs232c_exit(void);

//ES920 command list

extern int easel_ES920_set_mode_config(int command);
extern int easel_ES920_save_param();
extern int easel_ES920_save_param();
extern int easel_ES920_set_node(int node);
extern int easel_ES920_set_bw(int bw);
extern int easel_ES920_set_sf(int sf);
extern int easel_ES920_set_ch(int ch);
extern int easel_ES920_set_panid(int panid);
extern int easel_ES920_set_ownid(int ownid);
extern int easel_ES920_set_dstid(int dstid);
extern int easel_ES920_set_acksw(int acksw);
extern int easel_ES920_set_ackRetryNum(int ackRetryNum);
extern int easel_ES920_set_trmode(int trmode);
extern int easel_ES920_set_rcvsw(int rcvsw);
extern int easel_ES920_set_rssisw(int rssisw);
extern int easel_ES920_set_opmode(int opmode);
extern int easel_ES920_set_brate(int brate);
extern int easel_ES920_set_slepsw(int slepsw);
extern int easel_ES920_set_slept(int slepNum);
extern int easel_ES920_set_outpw(int outpw);

#define easel_ES920_set_processor_mode()	easel_ES920_set_mode_config( EASEL_ES920_INIT_PROCESSOR )
#define easel_ES920_set_mode_operation()	_easel_es920_send_recv("z", 0);  // any value is ok 
#define easel_ES920_save_param()	_easel_es920_send_recv("w",0)
#define easel_ES920_load_default()	_easel_es920_send_recv("x",0)


int SendTelegram(unsigned char *buf, unsigned int dst_id, unsigned int dst_addr );
int RecvTelegram(unsigned char *buf, short *rx_pwr, unsigned short *src_id, unsigned short *src_addr );
int RecvRS232C(unsigned char *buf);
int SendRS232C(unsigned char *buf);

void *RecvPollingThread(void *arg);

// wrapper function
extern int easel_ES920_set_wireless_default();
extern int easel_ES920_set_wireless( int node, int bw, int sf, int ch, int panid, int ownid, int dstid, int acksw, int ackRetryNum, int trmode, int rcvsw, int rssisw, int opmode, int brate, int slepsw, int slepNum, int outpw);

#endif
