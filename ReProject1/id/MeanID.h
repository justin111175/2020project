#pragma once


enum class MeanID
{
	�X�e�[�^�X,
	�ۑ�,
	�I��,
	MAX
};

MeanID begin(MeanID);
MeanID end(MeanID);
MeanID operator*(MeanID key);
MeanID operator++(MeanID& key);