#ifndef _DBOBJECT_H_
#define _DBOBJECT_H_

#include <vector>

class CG_EXPORT CDbObject
{
public:
	virtual ~CDbObject();

	virtual void onDraw(CDrawDevice* dd) = 0;
};

typedef std::vector<CDbObject*> Objects;
typedef Objects::iterator ObjectIt;

#endif