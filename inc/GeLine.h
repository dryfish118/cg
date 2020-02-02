#ifndef _GELINE_H_
#define _GELINE_H_

#include "GePoint.h"

class CG_EXPORT CGeLine
{
public:
	CGeLine();
	CGeLine(const CGePoint& ptStart, const CGePoint& ptEnd);

public:
	CGePoint m_start;
	CGePoint m_end;
};


#endif