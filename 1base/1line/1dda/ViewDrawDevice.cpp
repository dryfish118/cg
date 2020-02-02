#include "pch.h"

#include "ViewDrawDevice.h"

void CViewDrawDevice::drawPoint(const CGePoint& pnt)
{
	CRect rect;
	rect.left = (int)pnt.m_x * GRIPSIZE;
	rect.right = rect.left + GRIPSIZE;
	rect.top = (int)pnt.m_y * GRIPSIZE;
	rect.bottom = rect.top + GRIPSIZE;
	m_pDC->FillSolidRect(&rect, RGB(0, 255, 255));
}
