#ifndef _DRAWDEVICE_H_
#define _DRAWDEVICE_H_

class CDbObject;

class CG_EXPORT CDrawDevice
{
public:
	virtual ~CDrawDevice();

	virtual void drawPoint(CDbObject* pObj, double x, double y) = 0;
};


#endif