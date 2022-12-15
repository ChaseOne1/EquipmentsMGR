#pragma once

//�豸����
typedef enum EquipmentType
{
	MEC,	//��е��
	CHM,	//��ѧ��
	MDC,	//ҽѧ��
	ELC,	//������
	SPC		//�����豸
}EquipType;


//�豸�ṹ��
typedef struct Equipment
{
	EquipType	type;//�豸����
	char*		name;//�豸����
	char*		id;//�豸���
	long long	buy_date;//��������
	long long	scrap_date;//��������
	double		price;//����۸�
	bool		flag;//���ϱ�־
}Equip;