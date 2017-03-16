/***

	libeasel_ES920_func.c - easel_ES920_functions library
	
	Copyright (C) 2016 masayuki kubou, Syunsuke Okamoto.<okamoto@contec.jp>
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
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <pthread.h>

#include "libeasel_ES920.h"
#include "serialfunc.h"

/*!
 @~English
 @name DebugPrint macro
 @~Japanese
 @name デバッグ用表示マクロ
*/
/// @{

#if 0
#define DbgPrint(fmt...)	printf(fmt)
#else
#define DbgPrint(fmt...)	do { } while (0)
#endif

#if 0
#define DbgAllocFreeCheck(fmt...)	printf(fmt)
#else
#define DbgAllocFreeCheck(fmt...)	do { } while (0)
#endif

#if 0
#define DbgDataLength(fmt...)	printf(fmt)
#else
#define DbgDataLength(fmt...)	do { } while (0)
#endif

#if 0
#define DbgPrintRecvTelegram(fmt...)	printf(fmt)
#else
#define DbgPrintRecvTelegram(fmt...)	do { } while (0)
#endif

/// @}

static EASEL920PARAM param;	///< EASEL Parameter

struct timeval tim_int;	///< time interval
struct tm *curTime;	///< Current Time Structure

/**
	@~English
	@brief Change String to Number
	@param str : value
	@param mal : mal
	@return Success: dbm
	@~Japanese
	@brief 文字列から数値に変換する関数
	@param str : 文字列
	@param mal :　進数
	@return 成功:  dBm
**/
int _easel_es920_Str2Num(unsigned char *str, int mal){

	unsigned int num = 0;
	unsigned int i;
	unsigned int length = sizeof( str ) / sizeof( str[0] );
	int dBm;

	for( i = 0; i < length ; i ++ ){
		if( str[i] <= '9' && str[i] >='0' ){
			dBm = dBm * mal + str[i] - '0';
		}
		else if( str[i] <= 'F' && str[i] >='A' ){
			dBm = dBm * mal + str[i] -'A' + 10;
		}
		else if( str[i] <= 'f' && str[i] >='a' ){
			dBm = dBm * mal + str[i] -'a' + 10;
		}
	}

	if( str[0] == '-' )	dBm *= ( -1 );

	return dBm;
}

/**
	@~English
	@brief Change Number to String
	@param num : number
	@param str : value
	@param mal : mal
	@return Success: dbm
	@~Japanese
	@brief 数値から文字列に変換する関数
	@param str_pwr : 文字列
	@param mal :　進数
	@return 成功:  dBm
**/
void _easel_es920_Num2Str(int num ,unsigned char str[], int mal){

	unsigned int i;
	unsigned int isSign = 0;
	unsigned int length;
	int p_num = num;

	if( num < 0 ){
		isSign = 1;
		str[0]='-';
		num *= (-1);
	}

	length = ( num / mal ) + 1;

	for( i = isSign ; i < length + isSign ; i++ ){

		str[i] = num / pow(mal, length - i - 1 + isSign);
		num -= str[i] * pow(mal, length - i - 1 + isSign);

		switch(mal){
		case 2:
		case 10 :
			str[i] = str[i] + '0';
		  break;
		case 16:
		 	if( str[i] < 10 )
		 		str[i] = str[i] + '0';
		 	else if( str[i] < 16 )
		 		str[i] = ( str[i] - 10 ) + 'A';
		    break;
		}
	}
	DbgPrint("Num2Str %x = %s \r\n", p_num, str );
}

/**
	@~English
	@brief Change String(Decimal)to Number
	@param str : String
	@return Success: Number
	@~Japanese
	@brief 文字列(10進数)から値に変換する関数
	@param str_pwr : 文字列
	@return 成功:  数値
**/
#define _easel_es920_StrDec2Num( str )	_easel_es920_Str2Num( str , 10 )

/**
	@~English
	@brief Change String(Hexadecimal)to Number
	@param str : String
	@return Success: Number
	@~Japanese
	@brief 文字列(16進数)から値に変換する関数
	@param str : 文字列
	@return 成功:  値
**/
#define _easel_es920_StrHex2Num( str )	_easel_es920_Str2Num( str , 16 )

/**
	@~English
	@brief Change String(Bin)to Number
	@param str : value
	@return Success: value
	@~Japanese
	@brief 文字列(2進数)から2進数に変換する関数
	@param str_pwr : 文字列
	@return 成功: 値
**/
#define _easel_es920_StrBin2Num( str )	_easel_es920_Str2Num( str , 2 )

/**
	@~English
	@brief Change Number to String(Decimal)
	@param num : Number
	@param str : String(Decimal)
	@~Japanese
	@brief 値から文字列(10進数)に変換する関数
	@param num : 数値
	@param str : 文字列
**/
#define _easel_es920_Num2StrDec( num, str )	_easel_es920_Num2Str( num, str, 10 )

/**
	@~English
	@brief Change Number to String(Hexadecimal)
	@param num : number
	@param str : String
	@~Japanese
	@brief 値から文字列(16進数)に変換する関数
	@param num : 値
	@param str : 文字列
**/
#define _easel_es920_Num2StrHex( num, str )	_easel_es920_Num2Str( num, str, 16 )

/**
	@~English
	@brief Change Number　to String(Bin)
	@param num : value
	@param str : String(Bin)
	@return Success: value
	@~Japanese
	@brief 数値から文字列(2進数)に変換する関数
	@param num : 値
	@param str : 文字列
**/
#define _easel_es920_Num2StrBin( num, str )	_easel_es920_Num2Str( num, str, 2 )

/**
	@~English
	@brief EASEL 920 Module change from binary charctor to twice ascii code
	@param binStr : Binary Data
	@param ascStr : Ascii Code Data
	@return Success : 0 , Failed : -1
	@~Japanese
	@brief EASEL 920MHzモジュールへ送るためにバイナリデータをアスキーコードデータに変換する関数
	@param binStr : バイナリ文字列データ
	@param ascStr : アスキーコード文字列データ
	@return 成功:  0 失敗 :  エラー: -1
**/
long easel_ES920_bin2asc( unsigned char binStr[] , unsigned char ascStr[])
{
	unsigned int ascLen = 0, binLen = 0;
	unsigned int n = 0, m = 0;

	if( ascStr !=(unsigned char *)NULL ){
		ascLen = ( sizeof(ascStr) / sizeof(ascStr[0]) );
	}

	if( binStr !=(unsigned char *)NULL ){
		binLen = ( sizeof(binStr) / sizeof(binStr[0]) );
	}

	// バイナリ文字の2倍　送受信用文字列が用意されていなかったら Error
	if( ascLen < binLen * 2 )
		return -1;

	while ( n < binLen && m < ascLen ){

		// バイナリ文字1文字に対して ascii 2byte消費
		// 'A'(0x41) -> ascStr[m] = '1', ascStr[m + 1] = '4'
		// ' '(0x20) -> ascStr[m] = '0', ascStr[m + 1] = '2'
		ascStr[m] = (binStr[n] % 16) + 0x30;
		ascStr[m + 1] = (binStr[n] / 16) + 0x30;
		m += 2;
		n += 1;
	}
	return 0;
}


/**
	@~English
	@brief EASEL 920 Module change from twice ascii code to binary data
	@param ascStr : Ascii Code Data
	@param binStr : Binary Data
	@return Success : 0 , Failed : -1
	@~Japanese
	@brief EASEL 920MHzモジュールから受けたアスキーコードデータをバイナリデータに変換する関数
	@param ascStr : アスキーコード文字列データ
	@param binStr : バイナリ文字列データ
	@return 成功:  0 失敗 :  エラー: -1
**/
long easel_ES920_asc2bin( unsigned char ascStr[] , unsigned char binStr[])
{
	unsigned int ascLen = 0, binLen = 0;
	unsigned int n = 0, m = 0;

	if( ascStr !=(unsigned char *)NULL ){
		ascLen = ( sizeof(ascStr) / sizeof( ascStr[0] ) );
	}

	if( binStr !=(unsigned char *)NULL ){
		binLen = ( sizeof(binStr) / sizeof( binStr[0] ) );
	}

	// バイナリ文字の2倍　用意されていなかったら Error
	if( ascLen < binLen * 2 )
		return 1;

	while ( n < ascLen && m < binLen ){

		// bin文字2文字に対して 1キャラクタ消費
		// 'A'(0x41) <- binStr[m] = '1', binStr[m + 1] = '4'
		// ' '(0x20) <- binStr[m] = '0', binStr[m + 1] = '2'

		binStr[n] = ( ascStr[m + 1] - 0x30 ) * 16 + ( ascStr[m] - 0x30 );
		m += 2;
		n += 1;
	}
	return 0;
}

/**
	@~English
	@brief Change Hex　to dBm
	@param hex : value
	@return Success: dbm
	@~Japanese
	@brief 16進数からdBmに変換する関数
	@param hex :　16進数
	@return 成功:  dBm
**/
unsigned int _easel_es920_Hex2dBm(char *str_pwr){

	unsigned int dBm;

	sscanf(str_pwr,"%x",&dBm);
	//prietf("rx_pwr: %x, %d ",dBm,dBm);

	dBm = ~dBm;
	dBm = dBm + 0x0001;

	return dBm;
}

void easel_ES920_GetErrorString(int iRet,char *msg)
{

	switch(iRet){

		case 1:	sprintf(msg,"PARAMETER SETTING NG: %s","UNDEFINED COMMAND");
			break;
		
		case 2: sprintf(msg,"PARAMETER SETTING NG: %s","UNEXPECTED OPTION VALUE");
			break;

		case 3: sprintf(msg,"PARAMETER SETTING NG: %s","FlashROM: DELETE ERROR"); 
			break;

		case 4:	sprintf(msg,"PARAMETER SETTING NG: %s","FlashROM: SAVE ERROR");
			break;

		case 5: sprintf(msg,"PARAMETER SETTING NG: %s","FlashROM: LOAD ERROR");
			break;

		case 6: sprintf(msg,"PARAMETER SETTING NG: %s","FlashROM: LOAD ERROR");
			break;

		case 100: sprintf(msg,"PARAMETER SETTING NG: %s", "UNEXPECTE SIZE OF DATA");
			  break;

		case 101: sprintf(msg,"PARAMETER SETTING NG: %s","SENDING ERROR");
			  break;

		case 102: sprintf(msg,"PARAMETER SETTING NG: %s","SENDING ERROR");
			  break;

		case 103: sprintf(msg,"PARAMETER SETTING NG: %s","UNRECEIVING ERROR");
			  break;

		default: sprintf(msg,"PARAMETER SETTING NG: %s","UNKNOWN ERROR");
			 break;
	}

}	
 
/**
	@~English
	@brief EASEL 920 Module send and Ack receive
	@param buf : Send Data
	@param command : CMM920 Command
	@return Success : 0 , Failed : Otherwise 0
	@~Japanese
	@brief EASEL 920MHzモジュールに送信とAck受信を行う関数
	@param buf : 送信データ
	@param command : CMM920 コマンド
	@return 成功:  0 失敗 :  0以外
**/
int _easel_es920_send_recv(char buf[], int command )
{
	int iRet;
	char msg[128]={0};
	 
	iRet = SendCommand(buf,command);
	if( iRet < 0 )	return iRet;

	usleep(param.SerialWait);

	iRet = RecvCommandAck();
	if( iRet < 0 )	return iRet;

	else if(iRet > 0 ){
		easel_ES920_GetErrorString(iRet,msg);
		DbgPrint("%s\n", msg);
	}


	return iRet;
}

/**
	@~English
	@brief EASEL 920 Module set integer parameter
	@param buf : Send Data
	@param command : Command
	@param size : size of value
	@param value : save parameter
	@return Success : 0 , Failed : Otherwise 0
	@~Japanese
	@brief EASEL 920MHzモジュールのパラメータの設定関数
	@param buf : 送信データ
	@param command : ES920 コマンド
	@param size : valueのサイズ
	@param value : 保存するパラメータ
	@return 成功:  0 失敗 :  0以外
**/
int _easel_es920_set_parameter( char buf[], int command , int size, void *value ){

	int iRet  = 0;
	int *iValue;
	long *lValue;

	iRet = _easel_es920_send_recv( buf, command );

	if( iRet == 0 ){
		if( value != NULL ){
			if( size == 2 ){
				iValue = (int *)value;
				*iValue = command;
			}
			else if( size == 4 ){
				lValue = (long *)value;
				*lValue = command;
			}
		}
	}

	return iRet;
}

/**
	@~English
	@brief EASEL 920 Module set integer parameter
	@param buf : Send Data
	@param command : Command
	@param value : save parameter
	@return Success : 0 , Failed : Otherwise 0
	@~Japanese
	@brief EASEL 920MHzモジュールの整数パラメータの設定関数
	@param buf : 送信データ
	@param command : ES920 コマンド
	@param value : 保存するパラメータ
	@return 成功:  0 失敗 :  0以外
**/
#define _easel_es920_set_parameter_int( buf,command ,value )	\
	_easel_es920_set_parameter( buf, command, 2, value )

/**
	@~English
	@brief EASEL 920 Module set long parameter
	@param buf : Send Data
	@param command : Command
	@param value : save parameter
	@return Success : 0 , Failed : Otherwise 0
	@~Japanese
	@brief EASEL 920MHzモジュールの倍精度整数パラメータの設定関数
	@param buf : 送信データ
	@param command : ES920 コマンド
	@param value : 保存するパラメータ
	@return 成功:  0 失敗 :  0以外
**/
#define _easel_es920_set_parameter_long( buf,command ,value )	\
	_easel_es920_set_parameter( buf, command, 4, value )


/**
	@~English
	@brief EASEL 920 Module set initialize mode
	@param command : Command ( Terminal or Processor )
	@return Success : 0 , Failed : Otherwise 0
	@~Japanese
	@brief EASEL 920MHzモジュールの起動モードを設定する関数
	@param command : ES920 コマンド (ターミナルかプロセッサモード)
	@return 成功:  0 失敗 :  0以外
**/
int easel_ES920_set_mode_config( int command ){
	return _easel_es920_set_parameter_int( NULL, command, NULL );
}

/**
	@~English
	@brief EASEL 920 Module set node type
	@param command : Command ( EndDevice or Coordinator )
	@return Success : 0 , Failed : Otherwise 0
	@~Japanese
	@brief EASEL 920MHzモジュールのノードタイプを設定する関数
	@param command : ES920 コマンド (エンドデバイスか コーディネーター)
	@return 成功:  0 失敗 :  0以外
**/
int easel_ES920_set_node( int command ){
	return _easel_es920_set_parameter_int( "node", command, &param.node );
}

/**
	@~English
	@brief EASEL 920 Module set bandwidth
	@param command : Command ( from 31.25kHz to 500 kHz )
	@return Success : 0 , Failed : Otherwise 0
	@~Japanese
	@brief EASEL 920MHzモジュールのバンド幅を設定する関数
	@param command : ES920 コマンド (31.25kHz　~ 500kHz )
	@return 成功:  0 失敗 :  0以外
**/
int easel_ES920_set_bw(int command)
{
	return _easel_es920_set_parameter_int( "bw", command, &param.bw );
}

/**
	@~English
	@brief EASEL 920 Module set Spreading Factor
	@param command : Command ( from 7 to 12 )
	@return Success : 0 , Failed : Otherwise 0
	@~Japanese
	@brief EASEL 920MHzモジュールの拡散率を設定する関数
	@param command : ES920 コマンド  ( 7- 12)
	@return 成功:  0 失敗 :  0以外
**/
int easel_ES920_set_sf(int command)
{
	return _easel_es920_set_parameter_int( "sf", command, &param.sf );
}

/**
	@~English
	@brief EASEL 920 Module set Channel
	@param command : Command
	@return Success : 0 , Failed : Otherwise 0
	@~Japanese
	@brief EASEL 920MHzモジュールのチャネル数を設定する関数
	@param command : ES920 コマンド
	@return 成功:  0 失敗 :  0以外
**/
int easel_ES920_set_ch(int command)
{
	int max_ch;

	switch( param.bw ){
		case EASEL_ES920_BANDWIDTH_31250:
		case EASEL_ES920_BANDWIDTH_41700:
		case EASEL_ES920_BANDWIDTH_62500:
		case EASEL_ES920_BANDWIDTH_125K:
			max_ch = 37;
			break;
		case EASEL_ES920_BANDWIDTH_250K:
			max_ch = 18;
			break;
		case EASEL_ES920_BANDWIDTH_500K:
			max_ch = 12;
			break;
	}

	if( command < 1 && max_ch < command ){
		DbgPrint("Invalid Value of ch");
		return -1;
	}

	return _easel_es920_set_parameter_int( "channel", command, &param.ch );
}

/**
	@~English
	@brief EASEL 920 Module set PAN ID
	@param command : Command (From 1 to FFFE [Hex] )
	@return Success : 0 , Failed : Otherwise 0
	@~Japanese
	@brief EASEL 920MHzモジュールのPAN IDを設定する関数
	@param command : ES920 コマンド ( 1 ~ 65534 )
	@return 成功:  0 失敗 :  0以外
**/
int easel_ES920_set_panid(int command)
{
	return _easel_es920_set_parameter_int( "panid", command, &param.panid );
}

/**
	@~English
	@brief EASEL 920 Module set Owner Address
	@param command : Command (From 0 to FFFE [Hex] )
	@return Success : 0 , Failed : Otherwise 0
	@~Japanese
	@brief EASEL 920MHzモジュール自身の Addressを設定する関数
	@param command : ES920 コマンド ( 0 ~ 65534 )
	@return 成功:  0 失敗 :  0以外
**/
int easel_ES920_set_ownid(int command)
{
	return _easel_es920_set_parameter_int( "ownid", command, &param.ownid );
}

/**
	@~English
	@brief EASEL 920 Module set Destination Address
	@param command : Command (From 0 to FFFF [Hex] )
	@return Success : 0 , Failed : Otherwise 0
	@~Japanese
	@brief EASEL 920MHzモジュールの 送信先Addressを設定する関数
	@param command : ES920 コマンド ( 0 ~ 65535 )
	@note 送信モードがPayloadのときだけ有効 ?
	@return 成功:  0 失敗 :  0以外
**/
int easel_ES920_set_dstid(int command)
{
	return _easel_es920_set_parameter_int( "dstid", command, &param.dstid );
}

/**
	@~English
	@brief EASEL 920 Module set Acknowledge Signal
	@param command : Command ( 0 or 1 )
	@return Success : 0 , Failed : Otherwise 0
	@~Japanese
	@brief EASEL 920MHzモジュールのACKを設定する関数
	@param command : ES920 コマンド ( OFF or ON )
	@return 成功:  0 失敗 :  0以外
**/
int easel_ES920_set_acksw(int command)
{
	return _easel_es920_set_parameter_int( "ack", command, &param.ack );
}

/**
	@~English
	@brief EASEL 920 Module set Acknowledge Retry Number
	@param command : Command ( from 0 to 10 )
	@return Success : 0 , Failed : Otherwise 0
	@~Japanese
	@brief EASEL 920MHzモジュールのリトライ回数を設定する関数
	@param command : ES920 コマンド ( 0 ～ 10 )
	@return 成功:  0 失敗 :  0以外
**/
int easel_ES920_set_ackRetryNum(int command)
{
	return _easel_es920_set_parameter_int( "retry", command, &param.retry );
}

/**
	@~English
	@brief EASEL 920 Module set Transfer mode
	@param command : Command ( Payload or Frame )
	@return Success : 0 , Failed : Otherwise 0
	@~Japanese
	@brief EASEL 920MHzモジュールの送信モードを設定する関数
	@param command : ES920 コマンド ( Payload or Frame )
	@return 成功:  0 失敗 :  0以外
**/
int easel_ES920_set_trmode(int command)
{
	return _easel_es920_set_parameter_int( "transmode", command, &param.transmod );
}

/**
	@~English
	@brief EASEL 920 Module set Receive Packet with adding id
	@param command : Command ( OFF or ON )
	@return Success : 0 , Failed : Otherwise 0
	@~Japanese
	@brief EASEL 920MHzモジュールの受信パケットにID付加を設定する関数
	@param command : ES920 コマンド ( OFF or ON )
	@return 成功:  0 失敗 :  0以外
**/
int easel_ES920_set_rcvsw(int command)
{
	return _easel_es920_set_parameter_int( "rcvid", command, &param.rcvid );
}

/**
	@~English
	@brief EASEL 920 Module set Receive Packet with adding RSSI
	@param command : Command ( OFF or ON )
	@return Success : 0 , Failed : Otherwise 0
	@~Japanese
	@brief EASEL 920MHzモジュールの受信パケットにRSSI付加を設定する関数
	@param command : ES920 コマンド ( OFF or ON )
	@return 成功:  0 失敗 :  0以外
**/
int easel_ES920_set_rssisw(int command)
{
	return _easel_es920_set_parameter_int( "rssi", command, &param.rssi );
}

/**
	@~English
	@brief EASEL 920 Module set booting mode
	@param command : Command ( Configration or Operation )
	@return Success : 0 , Failed : Otherwise 0
	@~Japanese
	@brief EASEL 920MHzモジュールの起動時のモードを設定する関数
	@param command : ES920 コマンド ( Configration or Operation )
	@return 成功:  0 失敗 :  0以外
**/
int easel_ES920_set_opmode(int command)
{
	return _easel_es920_set_parameter_int( "operation", command, &param.mode );
}

/**
	@~English
	@brief EASEL 920 Module set baudrate
	@param command : Command ( from 1 to 6 [9600bps to 230400bps] )
	@return Success : 0 , Failed : Otherwise 0
	@~Japanese
	@brief EASEL 920MHzモジュールのボーレートを設定する関数
	@param command : ES920 コマンド ( 1～6  [9600bps ～ 230400bps]  )
	@return 成功:  0 失敗 :  0以外
**/
int easel_ES920_set_brate(int command)
{
	return _easel_es920_set_parameter_int( "baudrate", command, &param.baudrate );
}

/**
	@~English
	@brief EASEL 920 Module set sleep mode
	@param command : Command ( OFF or ON )
	@return Success : 0 , Failed : Otherwise 0
	@~Japanese
	@brief EASEL 920MHzモジュールのスリープモードを設定する関数
	@param command : ES920 コマンド (  OFF or ON )
	@return 成功:  0 失敗 :  0以外
**/
int easel_ES920_set_slepsw(int command)
{
	return _easel_es920_set_parameter_int( "sleep", command, &param.sleep );
}

/**
	@~English
	@brief EASEL 920 Module set sleep time
	@param command : Command ( from 1 to 864000 [ x0.1sec　] )
	@return Success : 0 , Failed : Otherwise 0
	@~Japanese
	@brief EASEL 920MHzモジュールのスリープ時間を設定する関数
	@param command : ES920 コマンド (  1～864000 [ x0.1秒 ]  )
	@return 成功:  0 失敗 :  0以外
**/
int easel_ES920_set_slept(int command)
{
	return _easel_es920_set_parameter_long( "sleeptime", command, &param.sleeptime );
}

/**
	@~English
	@brief EASEL 920 Module set output power
	@param command : Command ( from -4 to 13 [ dBm　] )
	@return Success : 0 , Failed : Otherwise 0
	@~Japanese
	@brief EASEL 920MHzモジュールの出力を設定する関数
	@param command : ES920 コマンド (  -4 ～13 [ dBm ]  )
	@return 成功:  0 失敗 :  0以外
**/
int easel_ES920_set_outpw(int command)
{
	return _easel_es920_set_parameter_int( "power", command, &param.power );
}


// Version Read
/**
	@~English
	@brief EASEL 920MHz Module Version Read function
	@param command : Command
	@param ver : module version
	@return Success : 0 , Failed :
	@~Japanese
	@brief EASEL 920MHz　Module の バージョン読み込み 関数
	@param command : ES920 コマンド (  -4 ～13 [ dBm ]  )
	@param ver : モジュールのバージョン
	@return 成功:  0 失敗 :
**/
/*
int easel_es920_version(int command, int *ver)
*/


/**
	@~English
	@brief EASEL 920 Module set serial wait time
	@param waitMsecTime  : wait time [msec]
	@return Success : 0
	@~Japanese
	@brief EASEL 920MHzモジュールとのシリアル送受信のウェイト時間を設定する関数
	@param waitMsecTime : シリアル通信中のウェイト [ msec ]  )
	@return 成功:  0
**/
int easel_ES920_set_serial_wait( int waitMsecTime )
{
	param.SerialWait = waitMsecTime * 1000;
	return 0;
}


/**
	@~English
	@brief EASEL 920MHz Initialize
	@param PortName : Serial port name
	@return Success : 0 , Failed : otherwise 0
	@~Japanese
	@brief EASEL 920MHzモジュールの初期化
	@param PortName : シリアル通信ポート名
	@return 成功:  0 失敗 :  0以外
**/

int easel_ES920_init(char* PortName,int iBaudrate){

	//int iBaudrate = 115200;
	int iLength = 8;
	int iStop = 1;
	int iParity = 0;
	int iFlow=0;
	int iPort;
	pthread_t tid;

	iPort = Serial_PortOpen_Full(
		PortName,
		iBaudrate,
		iLength,
		iStop,
		iParity,
		10,
		iFlow,
		0
	);

	if(iPort < 0){
		return 1;
	}

	param.SerialPort = iPort;
	param.SerialWait = 50000;
	param.app_comm_mode = EASEL_ES920_COMMUNICATION_ASCII;


	// 内部 ReadThread 起動
	if( param.read_id == 0 ){
		//if( !pthread_create(&tid, NULL, RecvPollingThread,NULL) ){
		//	param.read_id = tid;
		//}
	}

	//Circle Q 初期化
	CIRCLEQ_INIT(&es920_ring_buffer_head);

	return 0;
}


/**
	@~English
	@brief EASEL 920MHz Module Send Data add frame header
	@param buf : Send Data
	@param value : value
	@~Japanese
	@brief CONEXIO 920MHz　Module の 送信データにヘッダフレームを追加する関数
	@param buf : 送信データ
	@param value : 値
**/
void _easel_es920_add_frameheader( unsigned char buf[], int value ){
	int count;
	int data;
	for( count = 0; count < 4; count -- ){
		data = (( value & (0xF << (8 * (3 - count) ))) >> (8 * (3 - count) ) );
		_easel_es920_Num2StrHex( data, &buf[ count ] );
	}
}

/**
	@~English
	@brief EASEL 920MHz Module data send function
	@param buf : send data buffer
	@return Success : 0 , Failed : -1
	@~Japanese
	@brief EASEL 920MHz　Module のデータ送信 関数
	@param buf : 送信データバッファ
	@return 成功:  0 失敗 :  エラー:  -1, -2
**/
int SendTeregram(unsigned char *buf, unsigned int dst_id, unsigned int dst_addr )
{
	unsigned char *send_buf;
	int length, tx_length = 0, success_length = 0, address_offset = 0;
	int current_index = 0, total_index = 0;
	int trans_header_data = 0;
	int count;
	char ES920_PacketData[58];

	if( buf != (unsigned char*)NULL ){
		tx_length = strlen((char *)buf);
	}else{
		return -1;
	}

	switch ( param.app_comm_mode ){
	case EASEL_ES920_COMMUNICATION_BINARY:
		tx_length = tx_length * 2;
		send_buf = (unsigned char*)malloc(sizeof(unsigned char) * ( tx_length ) );
		//ASCII -> バイナリ変換
		easel_ES920_asc2bin( buf , send_buf );
		break;

	case EASEL_ES920_COMMUNICATION_ASCII:
		send_buf = (unsigned char*)malloc(sizeof(unsigned char) * (tx_length ) );
		// 文字列コピー
		memcpy(send_buf, buf, sizeof(unsigned char) * tx_length);
		break;
	}

	count = 0;
	total_index = (tx_length / 44) + 1;
	current_index = 1;

	do {
		if( current_index < total_index  ){
			length = 44;
		}else{
			length = (tx_length - count);
		}

		memset( ES920_PacketData, 0x00, 58 );

		// Frame タイプ送信の場合、送信先PAN ID(dst_id)と、送信先アドレス(dst_addr)を追加
		if( param.transmod == EASEL_ES920_TRASMOD_FRAME ){
			address_offset = 8;
			_easel_es920_add_frameheader( &ES920_PacketData[0], dst_id);
			_easel_es920_add_frameheader( &ES920_PacketData[4], dst_addr);
		}else{
			//Payload タイプ送信の場合、アドレスを付加しないため offset = 0
			address_offset = 0;
		}

		// Send type
		if(0)
		{
			ES920_PacketData[address_offset + 0] = param.app_comm_mode + '0';

			// Reserved ES920_PacketData[address_offset + 1]
			ES920_PacketData[address_offset + 1] = '0';
			//index
			ES920_PacketData[address_offset + 2] = (current_index / 16) + '0';
			ES920_PacketData[address_offset + 3] = (current_index % 16) + '0';
			ES920_PacketData[address_offset + 4] = (total_index / 16) + '0';
			ES920_PacketData[address_offset + 5] = (total_index % 16) + '0';
		}


		//memcpy(&ES920_PacketData[address_offset + 5], &send_buf[count], length);
		memcpy(&ES920_PacketData[address_offset + 0], &send_buf[count], length);

		//delimiter
		//ES920_PacketData[length + address_offset + 5] = '\r';
		//ES920_PacketData[length + address_offset + 6] = '\n';
		ES920_PacketData[length + address_offset + 0] = '\r';
		ES920_PacketData[length + address_offset + 1] = '\n';

		//success_length = Serial_PutString(param.SerialPort, ES920_PacketData, ( (length + address_offset +  6)*sizeof(unsigned char) ) );
		success_length = Serial_PutString(param.SerialPort, ES920_PacketData, ( (length + address_offset +  2)*sizeof(unsigned char) ) );

		if( success_length == 0 ){
				free(send_buf);
				return -2;
		}

		count += length;
		current_index += 1;

	}while( count < tx_length );

	DbgPrint("==== SendTelegram =======================\n");
	DbgPrint("Data\n");
//	for( count = 0; count < tx_length; count++ ) DbgPrint("%02x ",send_buf[count]);
	for( count = 0; count < (length + address_offset +  2); count++ ) DbgPrint("%02x ",ES920_PacketData[count]);
	DbgPrint("\n");
	/*
	gettimeofday(&myTime,NULL);
	time_st = localtime(&myTime.tv_sec);
	printf("TIME:%02d:%02d:%02d.%06d\n",
				time_st->tm_hour,
				time_st->tm_min,
				time_st->tm_sec,
				myTime.tv_usec
	      );
	*/

	DbgPrint("<SendTelegram> Port %x, Data %s\n",param.SerialPort, buf);

	free(send_buf);

	return tx_length;
}

//#define SendTeregramPayload( buf )	SendTeregram( buf, NULL, NULL )

int SendTeregramPayload(unsigned char *buf)
{
	int iRet=0;
	char Data[50]={0};
	int length;
	int count;

	//make the format
	for( count =0; count < 50; count++ ){
		Data[count] = buf[count];
	}

	length = strlen(Data);

	//send the format
	length = Serial_PutString(param.SerialPort, Data, length * sizeof(char));
	if(iRet<0) return -1;

	DbgPrint("==== SendTelegram =======================\n");
	DbgPrint("Data\n");
	for( count = 0; count < length; count++ ) DbgPrint("%02x ",Data[count]);
	DbgPrint("\n");
	/*
	gettimeofday(&myTime,NULL);
	time_st = localtime(&myTime.tv_sec);
	printf("TIME:%02d:%02d:%02d.%06d\n",
				time_st->tm_hour,
				time_st->tm_min,
				time_st->tm_sec,
				myTime.tv_usec
	      );
	*/

	DbgPrint("<SendTelegram> Port %x, ret %d, Data %s\n",param.SerialPort,iRet,Data);

	return iRet;
}

/**
	@~English
	@brief Change Hex to Bcd Dec
	@param hex : value
	@return Success: Bcd Dec-
	@~Japanese
	@brief 16進数から 10進のBCDコードに変換する関数
	@param hex : 16進数
	@return 成功:  10進数BCDコード
**/
BYTE _calc_Hex2Bcd( BYTE hex ){

	return ( ( hex / 16 ) * 10 + ( hex % 16 ) );

}

EASEL920_TEMPBUFFER temp_recv_buf;

void *RecvPollingThread(void *arg)
{
	int iRet=0;

	int readlen = 0;
	int count;
	int iTempLen = 0;
	unsigned char str_pwr[4]={0};
	unsigned char str_id[4];
	unsigned char str_addr[4];
	int header_length[2] ={0};

	unsigned char temp_char;

	PEASEL920_READBUFFER new_buffer;

	//get the data length(header + response data)
	memset(&str_pwr[0], 0x00, 4 );
	memset(&str_id[0], 0x00, 4 );
	memset(&str_addr[0], 0x00, 4 );

	/* */
	while( 1 ){

		// set header_length
		if( param.rssi == EASEL_ES920_RSSI_ON ) header_length[0] = 4;
		if( param.rcvid == EASEL_ES920_RCVID_ON ) header_length[1] = 8;

		Serial_Get_In_Buffer( param.SerialPort, &readlen );

		if( readlen == 0 ) continue;

		for(count = 0;count < readlen;count++){
			temp_char = Serial_GetChar(param.SerialPort);

			switch( temp_char ){
			case '\r':
				temp_recv_buf.state = 1;
				break;
			case '\n':
				temp_recv_buf.state = 2;
				break;
				temp_recv_buf.data[temp_recv_buf.length + count] = temp_char;
				temp_recv_buf.length += 1;
				break;
			}

			if( temp_recv_buf.length + count < 50 ){
				temp_recv_buf.data[temp_recv_buf.length + count] = Serial_GetChar(param.SerialPort);
			}
			else{

			}
		}


		if( temp_recv_buf.state == 2 ){
			DbgPrintRecvTelegram("===========RecvTele=======================\n");
			DbgPrintRecvTelegram("Data\n");
			for(count=0;count < temp_recv_buf.length;count++)
				DbgPrintRecvTelegram("%02x ",temp_recv_buf.data[count]);
			DbgPrintRecvTelegram("\n");

	/*gettimeofday(&myTime,NULL);
	time_st = localtime(&myTime.tv_sec);
	printf("TIME:%02d:%02d:%02d.%06d\n",
			time_st->tm_hour,
			time_st->tm_min,
			time_st->tm_sec,
			myTime.tv_usec
      );
	 */

			if(!strcmp((char *)temp_recv_buf.data,"OK")) return;

			DbgPrintRecvTelegram("DATA:");


			for( count = 0; count < header_length[0] + header_length[1]; count ++ ){

				if( count < header_length[0] ){
					//rx_pwr
					str_pwr[count] = temp_recv_buf.data[count];
				}else if( count < header_length[0] + 4 ){
					// id
					str_id[count - header_length[0]] = temp_recv_buf.data[count];
				}else if( count < header_length[0] + header_length[1] ){
					// addr
					str_addr[count - header_length[0] - 4] = temp_recv_buf.data[count];
				}
			}

			// ここで新しいバッファ作成
			new_buffer = ( PEASEL920_READBUFFER ) malloc(sizeof(EASEL920_READBUFFER));

			if( new_buffer != ( PEASEL920_READBUFFER )NULL ){
				new_buffer->rssi = _easel_es920_StrHex2Num(str_pwr);
				new_buffer->src_id = _easel_es920_StrHex2Num(str_id);
				new_buffer->src_addr = _easel_es920_StrHex2Num(str_addr);

				memset(&new_buffer->data[0], 0x00, 50 );

				for(count = 0; count < (temp_recv_buf.length - header_length[0] - header_length[1] ); count ++ ){
					new_buffer->data[count] = temp_recv_buf.data[count];
				}

				//リングバッファの末尾に追加
				CIRCLEQ_INSERT_TAIL(&es920_ring_buffer_head, new_buffer, entry);

				//表示
				DbgPrintRecvTelegram("<RecvTelegram>Data %s buf %s rx_pwr %d src_id %d src_addr %d\n",
					new_buffer->data,temp_recv_buf.data,new_buffer->rssi, new_buffer->src_id, new_buffer->src_addr );
			}
		}
		usleep(100 * 1000);
	}

	return;

}


/**
	@~English
	@brief EASEL 920MHz Module data receive function
	@param buf : receive data buffer
	@return Success : 0 , Failed : From -1 to -15 : Parameter Error, From -16 to -31 Send Error, less than -32 : Receive Error
	@~Japanese
	@brief EASEL 920MHz　Module のデータ受信 関数
	@param buf : 受信データバッファ
	@return 成功:  0 失敗 :  送信 エラー:  -1～-15 -16～-31,　受信エラー : -32～
**/
//int RecvTelegram(unsigned char *buf)
int RecvTelegram(unsigned char *buf, short *rx_pwr, unsigned short *src_id, unsigned short *src_addr )
{
	int iRet=0;
	unsigned char Data[62];
	int readlen = 0;
	int count;
	int iTempLen = 0, bef_iTempLen = 0;
	unsigned char str_pwr[4]={0};
	unsigned char str_id[4]={0};
	unsigned char str_addr[4]={0};
	int header_length[2] ={0};

	//get the data length(header + response data)
	memset(&Data[0],0x00, 62);
	memset(&str_pwr[0], 0x00, 4 );
	memset(&str_id[0], 0x00, 4 );
	memset(&str_addr[0], 0x00, 4 );

	// set header_length
	if( param.rssi == EASEL_ES920_RSSI_ON ) header_length[0] = 4;
	if( param.rcvid == EASEL_ES920_RCVID_ON ) header_length[1] = 8;

	do{
		bef_iTempLen=iTempLen;
		iTempLen = 0;
		usleep(100 * 1000);
		Serial_Get_In_Buffer( param.SerialPort, &iTempLen );
//		DbgPrintRecvTelegram(" before : %d len %d\n", bef_iTempLen, iTempLen);
	}while( iTempLen != bef_iTempLen );

	readlen = iTempLen;
	
	if( readlen == 0 ) return -1;

	for(count=0;count < readlen;count++){
		Data[count] = Serial_GetChar(param.SerialPort);
	}
	DbgPrintRecvTelegram("===========RecvTele=======================\n");
	DbgPrintRecvTelegram("Data\n");
	for(count=0;count < readlen;count++)
		DbgPrintRecvTelegram("%02x ",Data[count]);
	DbgPrintRecvTelegram("\n");

	/*gettimeofday(&myTime,NULL);
	time_st = localtime(&myTime.tv_sec);
	printf("TIME:%02d:%02d:%02d.%06d\n",
			time_st->tm_hour,
			time_st->tm_min,
			time_st->tm_sec,
			myTime.tv_usec
      );
	 */

	if(!strcmp((char *)Data,"OK\r\n")) return 0;

	DbgPrintRecvTelegram("DATA:");


	for( count = 0; count < readlen; count ++ ){

		if( count < header_length[0] ){
			//rx_pwr
			str_pwr[count] = Data[count];
		}else if( count < header_length[0] + 4 ){
			// id
			str_id[count - header_length[0]] = Data[count];
		}else if( count < header_length[0] + header_length[1] ){
			// addr
			str_addr[count - header_length[0] - 4] = Data[count];
		}else{
			buf[count - header_length[0] - header_length[1] ] = Data[count];
		}
	}


	if( rx_pwr != NULL )	*rx_pwr = _easel_es920_StrHex2Num(str_pwr);
	if( src_id != NULL )	*src_id = _easel_es920_StrHex2Num(str_id);
	if( src_addr != NULL )	*src_addr = _easel_es920_StrHex2Num(str_addr);


	DbgPrintRecvTelegram("<RecvTelegram>Data %s buf %s rx_pwr %d src_id %d src_addr %d\n",
			Data,buf,*rx_pwr, *src_id, *src_addr );

	return readlen;
}

//#define RecvTelegramPayload( buf )	RecvTelegram( buf, NULL, NULL, NULL )

int RecvTelegramPayload(unsigned char *buf)
{
	int iRet=0;
	char Data[62]={0};
	int readlen = 0;
	int count;
	int bef_readlen = 0;
	char str_pwr[4]={0};
	unsigned char rx_pwr;

	//get the data length(header + response data)
	memset(&Data[0],0x00, 62);

	ioctl( param.SerialPort, FIONREAD, &readlen );
	if(readlen == 0)
	{
		DbgPrintRecvTelegram("NO Data Received\n");
		return 0;
	}

	while(1){
		bef_readlen=readlen;
		usleep(100*1000);
		ioctl(param.SerialPort,FIONREAD,&readlen);
		if(bef_readlen==readlen) break;
	}
	//if(readlen==0) return 0;

	for(count=0;count < readlen;count++){
		Data[count] = Serial_GetChar(param.SerialPort);
	}

	DbgPrintRecvTelegram("===========RecvTele=======================\n");
	DbgPrintRecvTelegram("Data\n");
	for(count=0;count < readlen;count++)
		DbgPrintRecvTelegram("%02x ",Data[count]);

	DbgPrintRecvTelegram("\n");

	/*gettimeofday(&myTime,NULL);
	time_st = localtime(&myTime.tv_sec);
	printf("TIME:%02d:%02d:%02d.%06d\n",
				time_st->tm_hour,
				time_st->tm_min,
				time_st->tm_sec,
				myTime.tv_usec
	      );
	*/

	//Serial_GetChar(param.SerialPort);
	if(!strcmp(Data,"OK\r\n")) return 0;
	DbgPrintRecvTelegram("DATA:");

	//for(i=0;i<=readlen ;i++) ;

/*
	if( readlen >= 2 ){
		if( Data[readlen - 2] == '\r' &&
			Data[readlen -1] == '\n' ){
				memset(&buf[readlen-2],'\0', 2);
		}
	}
*/

	for( count = 0; count < readlen; count ++ ){

		if( count < 4 ){
			//rx_pwr
			str_pwr[count] = Data[count];
		}else if( count < 8 ){
			// id
		}else if( count < 12){
			// addr
		}else{
			buf[count-12] = Data[count];
		}
	}

	//tmp_pwr = atoi(rx_pwr);
	//sscanf(str_pwr,"%x",&rx_pwr);

	//memcpy(buf, buf, (readlen-13) * sizeof(unsigned char) );


	//printf("\n");

	//buf = strtok(Data,"\r");
	rx_pwr = _easel_es920_Hex2dBm(str_pwr);
	DbgPrintRecvTelegram("<RecvTelegram>Data %s buf %s rx_pwr -%d\n",
				Data,buf,rx_pwr);

	//make the area of data length
	//length = (int)_calc_Hex2Bcd(head[0]);

	//DbgPrint("length:%d,panid:%x%x,ownid:%x%x,dstid:%x%x\n",
	//		length,head[5],head[6],head[7],head[8],head[9],head[10]);

	return readlen;
}

// Send Command ES920
/**
	@~English
	@brief EASEL 920MHz Module command send function
	@param buf : send data buffer
	@param command : command
	@return Success : 0 , Failed : -1
	@~Japanese
	@brief EASEL 920MHz　Module のコマンドデータ受信 関数
	@param buf : 送信データバッファ
	@param command : コマンド
	@return 成功:  0 失敗 :   -1
**/
int SendCommand(unsigned char buf[], int command )
{
	int iRet=0;
	unsigned char *Data;
	int length;

	if( buf != NULL ){
//		length = sizeof(buf) / sizeof((buf)[0]) + 4;
		length = strlen((char *)buf) + 5; //(space,number,\r ,\n, \0) 5 words
	}else{
		length = 3;
	}
	DbgPrint("send SIZE %d.\r\n", length);
	//make the format	
	Data = (unsigned char *)malloc( sizeof(unsigned char) * length );

	if( Data == (unsigned char*) NULL ) return -1;

	if( buf == NULL ){
		DbgPrint("--- Processoer Mode ----\n");
		sprintf((char *)Data,"%d\r\n",command);
	}
	else{
		switch( buf[0] ){
			case 'x':
			case 'w':
			case 'z':
				sprintf((char *)Data,"%s\r\n",buf);
				DbgPrint("start or save or load\n");
				break;
			default:
				sprintf((char *)Data,"%s %d\r\n",buf,command);
				DbgPrint("setting parameter\n");
				break;
		}
	}

	length = strlen((char *)Data );

	DbgPrint("<SendCommand> Len : %d\n",length);
	DbgPrint("<SendCommand> Data : %s\n",Data);

	if(length != Serial_PutString(param.SerialPort, Data, length ))
		iRet=-1;

	DbgPrint("<SendCommand> Port %x, buf %s, command %d, ret %d\n",param.SerialPort, buf, command,iRet);

	free(Data);
	return iRet;
}


/**
	@~English
	@brief EASEL 920MHz Module Address function
	@return Success : 0 , Failed : Error
	@~Japanese
	@brief CONEXIO 920MHz　Module の アドレス関数
	@return 成功:  0 , 失敗：それ以外
**/

int RecvCommandAck(void)
{

	unsigned char res[8]={0};
	int iRet = 0;
	int cnt = 0;
	int iTempLen = 0, bef_iTempLen = 0;
	int resSize = strlen((char *)res);
	
	//size get
	//Serial_GetString(param.SerialPort, res, resSize);

	for(cnt=0;cnt < 8;cnt++){
		res[cnt] = Serial_GetChar(param.SerialPort);
	}

	//divide response  
//	//if( res[0] == 255 ){
		usleep( param.SerialWait );
		// received error
	//	DbgPrint("Received Error.\r\n");
	//	iRet = -1;
	//}
	if( memcmp( &res[0], "NG" , 2 ) == 0 ){
		// get error code
		for( cnt = 0; cnt < 3; cnt ++ ){
			iRet += ( res[cnt + 3] - 0x30) * pow(10.0, (2 - cnt) );
		} //必ず数字は3桁 ( NG 001とか)
	}
	else {
		
	}

	DbgPrint("<RecvCommandAck> Port %x, res %s, ret %d\n",param.SerialPort,res,iRet);
	return iRet;
}

/**
	@~English
	@brief EASEL 920MHz Exit
	@return Success : 0 , Failed : otherwise 0
	@~Japanese
	@brief EASEL 920MHzモジュールの終了
	@return 成功:  0 失敗 :  0以外
**/
int easel_ES920_exit(void)
{
	if(param.SerialPort == 0) return 0;

	Serial_PortClose(param.SerialPort);

	// 内部 ReadThread 強制切離し
	if( param.read_id != 0 ){
		pthread_detach(param.read_id);
	}


	return 0;
}
