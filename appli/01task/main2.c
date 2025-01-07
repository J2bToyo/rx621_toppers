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
	
}

//---------   ���C���^�X�N  ----------------------------//
//�@��1�b���ƂɃ��b�Z�[�W���V���A���o��
//�@TOPPERS�N����̌o�ߎ��Ԃ��܂�
//------------------------------------------------------//
void main_task(intptr_t exinf)
{
	SYSTIM st;
	
	while(1) {
		get_tim(&st);
		
		sci3_tx_str("TOPPERS RX621: ");
		sci3_tx('0' + (st / 10000) % 10);
		sci3_tx('0' + (st / 1000) % 10);
		sci3_tx('0' + (st / 100) % 10);
		sci3_tx('0' + (st / 10) % 10);
		sci3_tx('0' + (st / 1) % 10);
		sci3_tx_str("ms\r\n");

		delay_ms(1000);
	}
}
