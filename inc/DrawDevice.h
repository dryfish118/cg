#ifndef _DRAWDEVICE_H_
#define _DRAWDEVICE_H_

class CG_EXPORT CDrawDevice
{
public:
	virtual ~CDrawDevice();

	virtual void drawPoint(const CGePoint& pnt) = 0;
};


#endif