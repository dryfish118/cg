#include "pch.h"

#include "DbObject.h"

CDbObject::CDbObject()
	: m_color(eColorBlack)
{

}

CDbObject::~CDbObject()
{

}

void CDbObject::setColor(int c)
{
	m_color = c;
}

int CDbObject::color() const
{
	return m_color;
}
