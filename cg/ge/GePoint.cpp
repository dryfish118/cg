#include "pch.h"

#include "GePoint.h"

CGePoint::CGePoint()
	: m_x(0)
	, m_y(0)
{

}

CGePoint::CGePoint(double x, double y)
	: m_x(x)
	, m_y(y)
{

}

CGePoint CGePoint::operator+(const CGeVector& v) const
{
	CGePoint p;
	p.m_x = m_x + v.m_x;
	p.m_y = m_y + v.m_y;

	return p;
}
