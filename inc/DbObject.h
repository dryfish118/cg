#ifndef _DBOBJECT_H_
#define _DBOBJECT_H_

#include <vector>

class CG_EXPORT CDbObject
{
	int m_color;
public:
	CDbObject();
	virtual ~CDbObject();

	void setColor(int c);
	int color() const;

	enum Color
	{
		eColorBlack = 0,
		eColorRed,
		eColorLime,
		eColorGreen,
		eColorBlue,
		eColorPink,
		eColorYellow,
		eColorOlive,
		eColorOrange,
		eColorCyan,
		eColorFuchsia,
	};


	virtual void onDraw(CDrawDevice* dd) = 0;
};

typedef std::vector<CDbObject*> Objects;
typedef Objects::iterator ObjectIt;

#endif