/*
 * �v���O�����F ���C���^�X�N�̒�`
 * �t�@�C�����F main.c
 * ��`���e�@�F ���C���^�X�N�A���������[�`��
 */
 
#include <kernel.h>
#include <t_syslog.h>
#include <t_stdlib.h>
#include "syssvc/serial.h"
#include "syssvc/syslog.h"
#include "kernel_cfg.h"

#include "main.h"
#include "drv.h"

//---------   ���������[�`��  --------------------------//
//�@�J�[�l���N���O�̏���������
//------------------------------------------------------//
void initialize(intptr_t exinf)
{
	init_sci3(BAUD_9600BPS);
	init_lm61();
	init_lcd();
}

//---------   ���C���^�X�N  ----------------------------//
//�@�X���[�v���đ҂���Ԃ�
//------------------------------------------------------//
void main_task(intptr_t exinf)
{
	sci3_tx_str("DataQueue:start!\r\n");
	
	while(1) {
		slp_tsk();
	}
}

//---------   ���M�^�X�N  --------------------------//
//�@�f�[�^�L���[��p���Đ��l�𑗐M
//------------------------------------------------------//
void send_task(intptr_t exinf)
{
	//intptr_t data = 0;
	int temp;
	
    while(1){
		temp = lm61_temp10();
		snd_dtq( NUM_DATAQUE, (intptr_t)temp );
			
    	// �f�[�^�L���[���M�FNUM_DATAQUE�C�J�E���g�f�[�^
        //snd_dtq( NUM_DATAQUE, data );
	
        //data++;
        //if( data > 9 ) data = 0;
			
        dly_tsk(500);
    }
}

//---------   ��M�^�X�N  --------------------------//
//�@�f�[�^�L���[���琔�l����M
//------------------------------------------------------//
void receive_task(intptr_t exinf)
{
    //intptr_t data;
	int temp;
	
	while(1){
		// �f�[�^�L���[��M�FNUM_DATAQUE�C��M�f�[�^
        //rcv_dtq( NUM_DATAQUE, &data );
		
        //sci3_tx( data + '0');
		
		rcv_dtq( NUM_DATAQUE, (intptr_t*)&temp );
		lcd_cur(5, 0);
		lcd_num_string(temp, 3);
    }
}
