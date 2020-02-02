#ifndef _DRAWDEVICE_H_
#define _DRAWDEVICE_H_

class CG_EXPORT CDrawDevice
{
public:
	virtual ~CDrawDevice();

	virtual void drawPoint(double x, double y) = 0;
};


#endif