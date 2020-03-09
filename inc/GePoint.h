#ifndef _GEPOINT_H_
#define _GEPOINT_H_

#include "GeVector.h"

class CG_EXPORT CGePoint
{
public:
	CGePoint();
	CGePoint(double x, double y);

	CGePoint operator+(const CGeVector& v) const;

	double m_x;
	double m_y;
};


#endif