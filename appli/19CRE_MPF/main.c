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

#include <string.h>

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
	char *str;
	void *p_blk;

	sci3_tx_str("MemoryPool:start!\r\n");
	
	// �Œ蒷�������v�[���̊l���FSHARE_MEMBLK, p_blk
	get_mpf(SHARE_MEMBLK, &p_blk);
	
	str = (char*)p_blk;
	strcpy(str, "Share Memory Get!");
	
	// �Œ蒷�������v�[���̕ԋp�FSHARE_MEMBLK, p_blk
	rel_mpf(SHARE_MEMBLK, p_blk);

	while(1) {	
		slp_tsk();
	}
}

//---------   �A�N�Z�X�^�X�N  --------------------------//
//�@�Œ蒷�������v�[���i���L�������j�ɃA�N�Z�X
//------------------------------------------------------//
void access_task(intptr_t exinf)
{
	char *str;
	void *p_blk;
	
	// �Œ蒷�������v�[���̊l���FSHARE_MEMBLK, p_blk
	get_mpf(SHARE_MEMBLK, &p_blk);
	
	str = (char*)p_blk;
	sci3_tx_str(str);
	sci3_tx_str("\r\n");
	
	// �Œ蒷�������v�[���̕ԋp�FSHARE_MEMBLK, p_blk
	rel_mpf(SHARE_MEMBLK, p_blk);
}

