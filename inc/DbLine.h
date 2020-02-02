#ifndef _DBLINE_H_
#define _DBLINE_H_

#include "DbObject.h"

class CG_EXPORT CDbLine : public CDbObject
{
public:
	CDbLine();
	CDbLine(const CGePoint& ptStart, const CGePoint& ptEnd);

	virtual void onDraw(CDrawDevice* dd);

public:
	CGeLine m_line;
};


#endif