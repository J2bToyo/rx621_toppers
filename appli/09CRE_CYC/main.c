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
//�@�X���[�v���đ҂���Ԃ�
//------------------------------------------------------//
void main_task(intptr_t exinf)
{
	sci3_tx_str("CycleHandler:start!\r\n");

	while(1) {
		slp_tsk();
	}
}

//---------   �����n���h��  --------------------------//
//�@1000ms�����Ŏ��s�����
//------------------------------------------------------//
void cyc_handler(intptr_t exinf)
{
	static long tim;
	
	tim+=1000;		// �o�ߎ���
	
	sci3_tx('0' + (tim / 10000) % 10);
	sci3_tx('0' + (tim / 1000) % 10);
	sci3_tx('0' + (tim / 100) % 10);
	sci3_tx('0' + (tim / 10) % 10);
	sci3_tx('0' + (tim / 1) % 10);
	sci3_tx_str("ms\r\n");
}
