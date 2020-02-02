#include "pch.h"

#include "DbLine.h"

CDbLine::CDbLine()
{

}

CDbLine::CDbLine(const CGePoint& ptStart, const CGePoint& ptEnd)
	: m_line(ptStart, ptEnd)
{

}
