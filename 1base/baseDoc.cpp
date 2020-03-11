
// baseDoc.cpp: CbaseDoc 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "base.h"
#endif

#include "baseDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CbaseDoc

IMPLEMENT_DYNCREATE(CbaseDoc, CDocument)

BEGIN_MESSAGE_MAP(CbaseDoc, CDocument)
	ON_COMMAND(ID_LINE_DDA, &CbaseDoc::OnLineDDA)
	ON_COMMAND(ID_LINE_BRESENHAM, &CbaseDoc::OnLineBresenham)
	ON_COMMAND(ID_CLEAR_CLEAR, &CbaseDoc::OnClearClear)
END_MESSAGE_MAP()


// CbaseDoc 构造/析构

CbaseDoc::CbaseDoc() noexcept
	: m_state(kNone)
{
	// TODO: 在此添加一次性构造代码

}

CbaseDoc::~CbaseDoc()
{
	clear();
}

BOOL CbaseDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	CDbLine* line;
	
	CGePoint cen(50, 50);

	// 0
	line = new CDbBresenhamLine(cen, cen + CGeVector(10, 0));
	line->setColor(CDbObject::eColorBlack);
	m_objects.push_back(line);

	// 30
	line = new CDbBresenhamLine(cen, cen + CGeVector(10, 5));
	line->setColor(CDbObject::eColorBlue);
	m_objects.push_back(line);

	// 45
	line = new CDbBresenhamLine(cen, cen + CGeVector(10, 10));
	line->setColor(CDbObject::eColorBlue);
	m_objects.push_back(line);

	// 60
	line = new CDbBresenhamLine(cen, cen + CGeVector(5, 10));
	line->setColor(CDbObject::eColorBlue);
	m_objects.push_back(line);

	// 90
	line = new CDbBresenhamLine(cen, cen + CGeVector(0, 10));
	line->setColor(CDbObject::eColorBlack);
	m_objects.push_back(line);

	// 120
	line = new CDbBresenhamLine(cen, cen + CGeVector(-5, 10));
	line->setColor(CDbObject::eColorPink);
	m_objects.push_back(line);

	// 135
	line = new CDbBresenhamLine(cen, cen + CGeVector(-10, 10));
	line->setColor(CDbObject::eColorPink);
	m_objects.push_back(line);

	// 150
	line = new CDbBresenhamLine(cen, cen + CGeVector(-10, 5));
	line->setColor(CDbObject::eColorPink);
	m_objects.push_back(line);

	// 180
	line = new CDbBresenhamLine(cen, cen + CGeVector(-10, 0));
	line->setColor(CDbObject::eColorBlack);
	m_objects.push_back(line);

	// 210
	line = new CDbBresenhamLine(cen, cen + CGeVector(-10, -5));
	line->setColor(CDbObject::eColorLime);
	m_objects.push_back(line);

	// 225
	line = new CDbBresenhamLine(cen, cen + CGeVector(-10, -10));
	line->setColor(CDbObject::eColorLime);
	m_objects.push_back(line);

	// 240
	line = new CDbBresenhamLine(cen, cen + CGeVector(-5, -10));
	line->setColor(CDbObject::eColorLime);
	m_objects.push_back(line);

	// 270
	line = new CDbBresenhamLine(cen, cen + CGeVector(0, -10));
	line->setColor(CDbObject::eColorBlack);
	m_objects.push_back(line);

 	// 300
	line = new CDbBresenhamLine(cen, cen + CGeVector(5, -10));
	line->setColor(CDbObject::eColorOlive);
	m_objects.push_back(line);

	// 315
	line = new CDbBresenhamLine(cen, cen + CGeVector(10, -10));
	line->setColor(CDbObject::eColorOlive);
	m_objects.push_back(line);

	// 330
	line = new CDbBresenhamLine(cen, cen + CGeVector(10, -5));
	line->setColor(CDbObject::eColorOlive);
	m_objects.push_back(line);

	return TRUE;
}

void CbaseDoc::clear()
{
	for (ObjectIt it = m_objects.begin(); it != m_objects.end(); it++)
	{
		delete *it;
	}
	m_objects.clear();
}

// CbaseDoc 序列化

void CbaseDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CbaseDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CbaseDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CbaseDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CbaseDoc 诊断

#ifdef _DEBUG
void CbaseDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CbaseDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CbaseDoc 命令

void CbaseDoc::OnLineDDA()
{
	m_state = kGetDDAFirstPoint;
	POSITION pos = GetFirstViewPosition();
	CbaseView* pView = (CbaseView*)GetNextView(pos);
	pView->getPoint(this);
}

void CbaseDoc::OnLineBresenham()
{
	m_state = kGetBresenhamFirstPoint;
	POSITION pos = GetFirstViewPosition();
	CbaseView* pView = (CbaseView*)GetNextView(pos);
	pView->getPoint(this);
}

void CbaseDoc::onGetPoint(const CGePoint& pnt)
{
	if (m_state == kGetDDAFirstPoint)
	{
		m_point = pnt;

		m_state = kGetDDASecondPoint;
		POSITION pos = GetFirstViewPosition();
		CbaseView* pView = (CbaseView*)GetNextView(pos);
		pView->getPoint(this);
	}
	else if (m_state == kGetDDASecondPoint)
	{
		m_state = kNone;
		CDbLine* line = new CDbDDALine(m_point, pnt);
		m_objects.push_back(line);
		UpdateAllViews(NULL);
	}
	else if (m_state == kGetBresenhamFirstPoint)
	{
		m_point = pnt;

		m_state = kGetBresenhamSecondPoint;
		POSITION pos = GetFirstViewPosition();
		CbaseView* pView = (CbaseView*)GetNextView(pos);
		pView->getPoint(this);
	}
	else if (m_state == kGetBresenhamSecondPoint)
	{
		m_state = kNone;
		CDbLine* line = new CDbBresenhamLine(m_point, pnt);
		m_objects.push_back(line);
		UpdateAllViews(NULL);
	}
}


void CbaseDoc::OnClearClear()
{
	clear();
	UpdateAllViews(NULL);
}
