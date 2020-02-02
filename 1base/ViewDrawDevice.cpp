#include "pch.h"

#include "ViewDrawDevice.h"

void CViewDrawDevice::drawPoint(double x, double y)
{
	CRect rect;
	rect.left = (int)x * GRIPSIZE;
	rect.right = rect.left + GRIPSIZE;
	rect.top = (int)y * GRIPSIZE;
	rect.bottom = rect.top + GRIPSIZE;
	m_pDC->FillSolidRect(&rect, RGB(0, 255, 255));
}
