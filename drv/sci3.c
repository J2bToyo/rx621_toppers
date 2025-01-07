/*
 * �v���O�����F SCI3�V���A���ʐM�h���C�o
 * �t�@�C�����F sci3.c
 * ����Ώہ@�F USB-�V���A���ϊ����W���[�� AE-FT231X
 *              RX621���Ӌ@�\�FSCI3(8N1)
 * �ڑ��F
 *      RX621           | TxD3/P23  RxD3/P25
 *      USB�V���A���ϊ� | RXD       TXD
 */

#include "iodefine.h"
#include "sci3.h"

//--------------  SCI3�������֐�  ----------------------//
//	SCI3��ʐM���邽�߂̏�����(1��̂ݎ��s)
//   8n1 ???bps
//	�����Fbaud-�{�[���[�g�l
//	�ߒl�F�Ȃ�
//------------------------------------------------------//
void init_sci3(unsigned char baud)
{
	int i;
	
	// P23/TxD3, P25/RxD3
	//PORT2.DDR.BIT.B3 = 1;	//���M�[�q�͏o�͐ݒ肵�Ȃ��Ă悢
	PORT2.DDR.BIT.B5 = 0;
	PORT2.ICR.BIT.B5 = 1;	//��M�[�q�Ƃ��ė��p����Ƃ��͓��̓o�b�t�@��L���ɂ���
	
	MSTP(SCI3) = 0;			//���W���[���X�^���o�C�@�\����
	SCI3.SCR.BYTE = 0x00;	//���M����֎~�A��M����֎~
	SCI3.SMR.BYTE = 0x00;	//�����������[�h�A�p���e�B�Ȃ��A1�X�g�b�v�r�b�g�A8�r�b�g�f�[�^
	
	SCI3.BRR = baud;		
	
	for(i=0;i<1000;i++);	//�{�[���[�g���肷��܂ł̎��ԑ҂�
	
	SCI3.SCR.BYTE = 0x30;	//����M���싖��.�����ݒ肷��K�v������
	
	//����---------------------------------------------------
	//SCI3.SCR.BIT.TE = 1; ���M�͋�����邪�A��M�ł��Ȃ��B
	//SCI3.SCR.BIT.RE = 1;
	//-------------------------------------------------------
}


//--------------  SCI3��M�֐�  ------------------------//
//	SCI3����1�o�C�g�f�[�^����M�i�����Ƒ҂j
//	�����F�Ȃ�
//	�ߒl�F��M�f�[�^
//------------------------------------------------------//
unsigned char sci3_rx(void)
{
	int err_flg = 0;
	unsigned char rxdata;
	volatile unsigned char dummy;
	
	while(SCI3.SSR.BIT.RDRF == 0){		//��M����܂ő҂�
	
		if((SCI3.SSR.BYTE & 0x38) != 0){//��M�G���[������
			err_flg = 1;				//��M�G���[�t���O���Z�b�g
			break;
		}
	}
	
	if(err_flg){					//�G���[������Ƃ�
		SCI3.SSR.BYTE &= ~0x38;		//�G���[�r�b�g���N���A
		dummy = SCI3.RDR;			//RDRF��0�N���A�ɂ���
		err_flg = 0;				//��M�G���[�t���O�N���A
	}
	else{
		rxdata = SCI3.RDR;			//�����M��
	}
	
	return rxdata;
}


//--------------  SCI3���M�֐�  -----------------------//
//	SCI3����1�o�C�g�f�[�^�𑗐M
//	�����F���M�f�[�^
//	�ߒl�F�Ȃ�
//------------------------------------------------------//
void sci3_tx(unsigned char dat)
{
	while(SCI3.SSR.BIT.TDRE == 0);		//TDR����ɂȂ�܂ő҂�
	SCI3.TDR = dat;						//TDR�ɑ��M�f�[�^���Z�b�g
	while(SCI3.SSR.BIT.TEND == 0);		//���M�����܂ő҂�
}

//-----------  SCI3�����񑗐M�֐�  ---------------------//
//	SCI3���當����f�[�^�𑗐M
//	�����F���M���镶����|�C���^
//	�ߒl�F�Ȃ�
//------------------------------------------------------//
void sci3_tx_str(char *p)
{
	do {
		sci3_tx( *p );
		p++;
	} while(*p != '\0');
}

//--------------  SCI3.RDR�擾�֐�  --------------------//
//	SCI3��RDR�f�[�^�擾
//	�����F�Ȃ�
//	�ߒl�F��M�f�[�^
//------------------------------------------------------//
unsigned char sci3_get_rdr(void)
{
	return SCI3.RDR;
}

//--------------  SCI3.TDR�ݒ�֐�  --------------------//
//	SCI3��TDR�ɑ��M�f�[�^�ݒ�
//	�����F���M�f�[�^
//	�ߒl�F�Ȃ�
//------------------------------------------------------//
void sci3_set_tdr(unsigned char dat)
{
	SCI3.TDR = dat;
}
