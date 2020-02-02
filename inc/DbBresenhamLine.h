#ifndef _DBBRESENHAMLINE_H_
#define _DBBRESENHAMLINE_H_

#include "DbLine.h"

class CG_EXPORT CDbBresenhamLine : public CDbLine
{
public:
	CDbBresenhamLine();
	CDbBresenhamLine(const CGePoint& ptStart, const CGePoint& ptEnd);

	virtual void onDraw(CDrawDevice* dd);
};


#endif