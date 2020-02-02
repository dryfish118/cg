#include "pch.h"

#include "DbLine.h"

CDbLine::CDbLine()
{

}

CDbLine::CDbLine(const CGePoint& ptStart, const CGePoint& ptEnd)
	: m_line(ptStart, ptEnd)
{

}

void CDbLine::onDraw(CDrawDevice* dd)
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
		dd->drawPoint(CGePoint(x, y));
		x += delta_x;
		y += delta_y;
	}
}
