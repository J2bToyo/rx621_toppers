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
	init_tsw();
}

//---------   ���C���^�X�N  ----------------------------//
//�@�X���[�v���đ҂���Ԃ�
//------------------------------------------------------//
void main_task(intptr_t exinf)
{
	sci3_tx_str("EventFlag:start!\r\n");
	
	while(1) {
		slp_tsk();
	}
}

//---------   SW�^�X�N  --------------------------------//
//�@SW��Ԃ��Ď�
//------------------------------------------------------//
void sw_task(intptr_t exinf)
{
	unsigned char old, new;
	
	old = tsw_in();
	while(1) {
		new = tsw_in();
		if ((new != OFF) && (old != new)) {
			set_flg(SW_FLAG, new);
		}
		old = new;
		
		dly_tsk(100);
	}
}

//---------   �A���[�g�^�X�N  --------------------------//
//�@�C�x���g�t���O�҂�����w��r�b�g�����ƃ��b�Z�[�W�o��
//------------------------------------------------------//
void alert_task(intptr_t exinf)
{
	FLGPTN p_flgptn;
	
	while(1) {
		wai_flg(SW_FLAG, (0x0001<<(exinf-1)), TWF_ANDW, &p_flgptn);
		//clr_flg(SW_FLAG, ~(0x0001<<(exinf-1)));
		
		sci3_tx_str("SW");
		sci3_tx(exinf + '0');
		sci3_tx_str(":ON!!\r\n");
	}
}

