#pragma once


enum class Status_ID														//�����X�e�[�^�X
{
	���x��,
	HP,
	�ő�HP,
	�X�^�~�i,
	�U����,
	�h���,
	�ő�X�^�~�i,
	�̗�,
	���v��,
	�ؗ�,
	�q��,
	��,
	MAX
};


Status_ID begin(Status_ID);
Status_ID end(Status_ID);
Status_ID operator*(Status_ID& key);
Status_ID operator++(Status_ID& key);