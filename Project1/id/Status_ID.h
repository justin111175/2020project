#pragma once


enum class Status_ID														//­»Xe[^X
{
	HP,
	ÅåHP,
	MP,
	ÅåMP,
	UÍ,
	häÍ,
	q·,
	ñ,
	¨à,
	MAX
};



Status_ID begin(Status_ID);
Status_ID end(Status_ID);
Status_ID operator*(Status_ID& key);
Status_ID operator++(Status_ID& key);