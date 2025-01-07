/*
 * プログラム： メインタスクの定義
 * ファイル名： main.c
 * 定義内容　： メインタスク、初期化ルーチン
 */
 
#include <kernel.h>
#include <t_syslog.h>
#include <t_stdlib.h>
#include "syssvc/serial.h"
#include "syssvc/syslog.h"
#include "kernel_cfg.h"

#include "main.h"
#include "drv.h"

void speaker_music(const unsigned short ongaku[][2]);

//---------   初期化ルーチン  --------------------------//
//　カーネル起動前の初期化処理
//------------------------------------------------------//
void initialize(intptr_t exinf)
{
	init_sci3(BAUD_9600BPS);
	
	// LEDバー，スピーカ，タクトSWの初期化
	init_tsw();
	init_ledbar();
	init_speaker();
}

//---------   メインタスク  ----------------------------//
//　スリープして待ち状態に
//------------------------------------------------------//
void main_task(intptr_t exinf)
{
	sci3_tx_str("AppliTask:start!\r\n");
	
	while(1) {
		slp_tsk();
	}
}

//---------   SWタスク  --------------------------------//
//　SW1でLEDタスク起床
//　SW2でスピーカタスク起床
//------------------------------------------------------//
void sw_task(intptr_t exinf)
{
	unsigned char old, new;
	
	old = tsw_in();
	while(1) {
		// タクトSW状態を取り込む
		new = tsw_in();
		
		// タクトSWの状態が変化してONのとき
		if ((new != OFF) && (old != new)) {
			
			// タクトSW1がONのとき
			if ((new & TSW1_BIT) == TSW1_BIT) {
				
				// LEDタスクを起床させる
				wup_tsk(LED_TASK);
			}
			
			// タクトSW2がONのとき
			if ((new & TSW2_BIT) == TSW2_BIT) {
				
				// スピーカタスクを起床させる
				wup_tsk(SPEAKER_TASK);
			}
		}
		old = new;
		
		dly_tsk(100);
	}
}

//---------   LEDタスク  -------------------------------//
//　起床待ち、LEDを点滅動作
//------------------------------------------------------//
void led_task(intptr_t exinf)
{
	unsigned char led_dat = 0x00;
	int i;
	
	while(1) {
		// 起床待ち状態へ
		slp_tsk();
		
		// LED点滅処理(10回)
		for(i=0; i<10; i++) {
			led_dat = ~led_dat;
			ledbar_out(led_dat);
			
			dly_tsk(200);
		}
	}
}

//---------   スピーカータスク  ------------------------//
//　起床待ち、チャルメラ再生
//------------------------------------------------------//
#define ONTEI  0
#define NAGASA 1

void speaker_task(intptr_t exinf)
{
	const unsigned short charumera[][2] = {
		{RA1,  N4},
		{SHI1, N4},
		{S_DO2,N2},
		{SHI1, N4},
		{RA1,  N4},
		{RA1,  N4},
		{SHI1, N4},
		{S_DO2,N4},
		{SHI1, N4},
		{RA1,  N8},
		{SHI1, N1},
		{FIN,  FIN}
	};

	while(1) {
		// 起床待ち状態へ
		slp_tsk();
		
		// チャルメラの再生
		speaker_music(charumera);
	}
}

//---------   CMI1割込みハンドラ  ----------------------//
//　CMI1割込みでスピーカーを鳴らす
//------------------------------------------------------//
void cmi1_inthandler(void)
{
	speaker_ring();
}

//---------  音楽再生関数  -----------------------------//
//	音階・長さデータを連続出力
//	引数：音階・長さデータの二次元配列
//	戻値：なし
//------------------------------------------------------//
void speaker_music(const unsigned short ongaku[][2])
{
	int n = 0;
	
	while(ongaku[n][ONTEI] != FIN) {
		speaker_onkai(ongaku[n][ONTEI]);
		
		speaker_start();
		dly_tsk(ongaku[n][NAGASA]);
		
		speaker_stop();
		dly_tsk(50);
				
		n++;
	}
}