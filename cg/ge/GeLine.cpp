#include "pch.h"

#include "GeLine.h"

CGeLine::CGeLine()
{

}

CGeLine::CGeLine(const CGePoint& ptStart, const CGePoint& ptEnd)
	: m_start(ptStart)
	, m_end(ptEnd)
{

}