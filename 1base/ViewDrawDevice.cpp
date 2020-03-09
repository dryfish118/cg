#include "pch.h"

#include "ViewDrawDevice.h"

void CViewDrawDevice::drawPoint(CDbObject* pObj, double x, double y)
{
	CRect rect;
	rect.left = (int)x * GRIPSIZE;
	rect.right = rect.left + GRIPSIZE;
	rect.top = (int)y * GRIPSIZE;
	rect.bottom = rect.top + GRIPSIZE;

	COLORREF clr = RGB(0, 0, 0);
	switch (pObj->color())
	{
	case CDbObject::eColorBlack:
		clr = RGB(0, 0, 0);
		break;
	case CDbObject::eColorRed:
		clr = RGB(255, 0, 0);
		break;
	case CDbObject::eColorLime:
		clr = RGB(0, 255, 0);
		break;
	case CDbObject::eColorGreen:
		clr = RGB(0, 128, 0);
		break;
	case CDbObject::eColorBlue:
		clr = RGB(0, 0, 255);
		break;
	case CDbObject::eColorPink:
		clr = RGB(255, 192, 203);
		break;
	case CDbObject::eColorYellow:
		clr = RGB(255, 255, 0);
		break;
	case CDbObject::eColorOlive:
		clr = RGB(128, 128, 0);
		break;
	case CDbObject::eColorOrange:
		clr = RGB(255, 165, 0);
		break;
	case CDbObject::eColorCyan:
		clr = RGB(0, 255, 255);
		break;
	case CDbObject::eColorFuchsia:
		clr = RGB(255, 0, 255);
		break;
	default:
		break;
	}

	m_pDC->FillSolidRect(&rect, clr);
}
