#include "pch.h"

#include "DbBresenhamLine.h"

CDbBresenhamLine::CDbBresenhamLine()
{

}

CDbBresenhamLine::CDbBresenhamLine(const CGePoint& ptStart, const CGePoint& ptEnd)
	: CDbLine(ptStart, ptEnd)
{

}

void CDbBresenhamLine::onDraw(CDrawDevice* dd)
{
	double x1 = m_line.m_start.m_x,
		y1 = m_line.m_start.m_y,
		x2 = m_line.m_end.m_x,
		y2 = m_line.m_end.m_y;
	double dx = fabs(x2 - x1);
	double dy = fabs(y2 - y1);
	int inc = ((x2 - x1) * (y2 - y1) >= 0) ? 1 : -1;

	if ((dx > dy) ? (x2 < x1) : (y2 < y1))
	{
		double tmp = x1;
		x1 = x2;
		x2 = tmp;
		tmp = y1;
		y1 = y2;
		y2 = tmp;
	}

	if (dx > dy)
	{
		double p = 2 * dy - dx;
		double const1 = 2 * dy;
		double const2 = 2 * (dy - dx);
		double x = x1,
			y = y1;
		dd->drawPoint(this, x, y);
		while (x < x2)
		{
			x += 1;
			if (p < 0)
			{
				p += const1;
			}
			else
			{
				p += const2;
				y += inc;
			}
			dd->drawPoint(this, x, y);
		}
	}
	else
	{
		double p = 2 * dx - dy;
		double const1 = 2 * dx;
		double const2 = 2 * (dx - dy);
		double x = x1,
			y = y1;
		dd->drawPoint(this, x, y);
		while (y < y2)
		{
			y += 1;
			if (p < 0)
			{
				p += const1;
			}
			else
			{
				p += const2;
				x += inc;
			}
			dd->drawPoint(this, x, y);
		}
	}
}
