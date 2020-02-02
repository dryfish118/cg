#ifndef _DBDDALINE_H_
#define _DBDDALINE_H_

#include "DbLine.h"

class CG_EXPORT CDbDDALine : public CDbLine
{
public:
	CDbDDALine();
	CDbDDALine(const CGePoint& ptStart, const CGePoint& ptEnd);

	virtual void onDraw(CDrawDevice* dd);
};


#endif