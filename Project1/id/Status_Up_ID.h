#pragma once


enum class Status_Up_ID													//�����X�e�[�^�X
{
	�U����,
	�h���,
	�q��,
	��,
	�ő�HP,
	�ő�MP,
	�c��{�[�i�X�|�C���g,
	MAX

};
Status_Up_ID begin(Status_Up_ID);
Status_Up_ID end(Status_Up_ID);
Status_Up_ID operator*(Status_Up_ID& key);
Status_Up_ID operator++(Status_Up_ID& key);