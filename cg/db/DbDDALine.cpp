#include "pch.h"

#include "DbDDALine.h"

CDbDDALine::CDbDDALine()
{

}

CDbDDALine::CDbDDALine(const CGePoint& ptStart, const CGePoint& ptEnd)
	: CDbLine(ptStart, ptEnd)
{

}

void CDbDDALine::onDraw(CDrawDevice* dd)
{
	double x = m_line.m_start.m_x;
	double y = m_line.m_start.m_y;
	double dx = m_line.m_end.m_x - x;
	double dy = m_line.m_end.m_y - y;

	int steps = 0;
	if (fabs(dx) > fabs(dy))
	{
		steps = (int)fabs(dx);
	}
	else if (dy == 0)
	{
		return;
	}
	else
	{
		steps = (int)fabs(dy);
	}
	
	double delta_x = dx / steps;
	double delta_y = dy / steps;
	for (int i = 0; i < steps; i++)
	{
		dd->drawPoint(this, x, y);
		x += delta_x;
		y += delta_y;
	}
}
