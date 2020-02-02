#ifndef _VIEWDRAWDEVICE_H_
#define _VIEWDRAWDEVICE_H_ 

class CViewDrawDevice : public CDrawDevice
{
public:
	virtual void drawPoint(const CGePoint& pnt);

public:
	int m_cols;
	int m_rows;
	CDC* m_pDC;
};


#endif