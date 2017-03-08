/***

	libeasel_ES920_wrap.c - conexio_CMM920_Wrapper functions library
	Copyright (C) 2016 masayuki kubou, Syunsuke Okamoto.<okamoto@contec.jp>.
*
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
* 
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
* 
* You should have received a copy of the GNU Lesser General Public
* License along with this library; if not, see
   <http://www.gnu.org/licenses/>.  

***/

#include <stdio.h>
#include "libeasel_ES920.h"

// wrapper


/***
default setting function
	@~English
	@brief EASEL 920MHz Default Module Parameter Set
	@par Default Parameter : 125kHz, 1channel, PanID : 1 , Send Level -85dBm, Receive Level -95dBm, Send Time 130(usec), Send Num 6, Ack Retry Num 4, Ack Time 100(usec)
	@~Japanese
	@brief EASEL 920MHz　Module の 無線  通常設定関数
	@par パラメータ : 100kBps, 60チャネル, 1mW , 送信レベル -85dBm, 受信レベル -95dBm, 送信時間 130(usec), 送信回数 6回, ACKリトライ回数 4回, ACKリトライ時間 100 (usec)
***/

int easel_ES920_set_wireless_default(void)
{

	return easel_ES920_set_wireless(
			EASEL_ES920_NODE_ENDDEVICE,
			EASEL_ES920_BANDWIDTH_125K,
			EASEL_ES920_SF7,	
			1,			//Channel: 1
			1,			//Panid : 0x0001
			0,			//OwnAddr : 0x0001
			1,			//DstAddr : 0x0000
			EASEL_ES920_ACK_ON,  	 
			3,			//Retry: 3
			EASEL_ES920_TRASMOD_PAYLOAD,
			EASEL_ES920_RCVID_ON,	
			EASEL_ES920_RSSI_ON,
			EASEL_ES920_MODE_OPERATION,
			EASEL_ES920_BAUD_115200,
			EASEL_ES920_SLEEP_OFF, 
			50,			//Sleep time: 50
			13			//Power: 13dBm
	);
}


/**
	@~English
	@brief CONEXIO 920MHz Module Set Wireless function
	@param iBitrate : bit rate
	@param channel : channel
	@param power : send power
	@param sendLv : send sence level
	@param recvLv : receive sence level
	@param sendTim : send sence retry time
	@param sendNum : send sence retry number
	@param ackRetryNum : acknowledge retry number
	@param ackWaitTim : acknowledge retry time
	@return Success : 0 , Failed : From -1 to -15 : Parameter Error, From -16 to -31 Send Error, less than -32 : Receive Error
	@~Japanese
	@brief CONEXIO 920MHz　Module の 無線設定関数
	@param iBitrate : ビットレート
	@param channel : チャネル
	@param power : 送信出力
	@param sendLv : 送信センスレベル
	@param recvLv : 受信センスレベル
	@param sendTim : 送信センス再送時間
	@param sendNum : 送信センス再送回数
	@param ackRetryNum : ACKリトライ回数
	@param ackWaitTim : ACK待ち時間
	@return 成功:  0 失敗 :  送信 エラー:  -1～-15 -16～-31,　受信エラー : -32～
**/

int easel_ES920_set_wireless( int node, int bw, int sf, int ch, int panid, int ownid, int dstid, int acksw, int ackRetryNum, int trmode, int rcvsw, int rssisw, int opmode, int brate, int slepsw, int slepNum, int outpw)
{
	int iRet;

	iRet = easel_ES920_set_node(node);
	if(iRet) return -1;	

	iRet = easel_ES920_set_bw(bw);
	if(iRet) return -1;	

	iRet = easel_ES920_set_sf(sf);
	if(iRet) return -1;	

	iRet = easel_ES920_set_ch(ch);
	if(iRet) return -1;	

	iRet = easel_ES920_set_panid(panid);
	if(iRet) return -1;	

	iRet = easel_ES920_set_ownid(ownid);
	if(iRet) return -1;	

	iRet = easel_ES920_set_dstid(dstid);
	if(iRet) return -1;	

	iRet = easel_ES920_set_acksw(acksw);
	if(iRet) return -1;	

	iRet = easel_ES920_set_ackRetryNum(ackRetryNum);
	if(iRet) return -1;	

	iRet = easel_ES920_set_trmode(trmode);
	if(iRet) return -1;	

	iRet = easel_ES920_set_rcvsw(rcvsw);
	if(iRet) return -1;	

	iRet = easel_ES920_set_rssisw(rssisw);
	if(iRet) return -1;	

	iRet = easel_ES920_set_opmode(opmode);
	if(iRet) return -1;	
	
	iRet = easel_ES920_set_brate(brate);
	if(iRet) return -1;	

	iRet = easel_ES920_set_slepsw(slepsw);
	if(iRet) return -1;	

	iRet = easel_ES920_set_slept(slepNum);
	if(iRet) return -1;	

	iRet = easel_ES920_set_outpw(outpw);
	if(iRet) return -1;	

	return 0;
}	

int easel_ES920_set_wireless_by_structure( EASEL920PARAM es920param )
{

	return easel_ES920_set_wireless(
			es920param.node,
			es920param.bw,
			es920param.sf,
			es920param.ch,
			es920param.panid,
			es920param.ownid,
			es920param.dstid,
			es920param.ack,
			es920param.retry,
			es920param.transmod,
			es920param.rcvid,
			es920param.rssi,
			es920param.mode,
			es920param.baudrate,
			es920param.sleep,
			es920param.sleeptime,
			es920param.power
			);
}


