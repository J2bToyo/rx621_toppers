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
			
			// �C�x���g�t���O�̃Z�b�g�FSW_FLAG�CSW�f�[�^
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
		// �C�x���g�t���O�҂��FSW_FLAG�C����2bit�C�����ꂩ
		wai_flg(SW_FLAG, 0x0003, TWF_ORW, &p_flgptn);
		
		// �C�x���g�t���O�̃N���A�FSW_FLAG�C����2bit
		clr_flg(SW_FLAG, ~(0x0003));
		
		sci3_tx_str("SW:ON!!\r\n");
	}
}
