#pragma once


enum class Status_ID														//�����X�e�[�^�X
{
	HP,
	�ő�HP,
	MP,
	�ő�MP,
	�U����,
	�h���,
	�q��,
	��,
	����,
	MAX
};



Status_ID begin(Status_ID);
Status_ID end(Status_ID);
Status_ID operator*(Status_ID& key);
Status_ID operator++(Status_ID& key);