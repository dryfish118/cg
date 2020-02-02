
// ddaDoc.cpp: CddaDoc 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "dda.h"
#endif

#include "ddaDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CddaDoc

IMPLEMENT_DYNCREATE(CddaDoc, CDocument)

BEGIN_MESSAGE_MAP(CddaDoc, CDocument)
	ON_COMMAND(ID_LINE_DDA, &CddaDoc::OnLineDda)
END_MESSAGE_MAP()


// CddaDoc 构造/析构

CddaDoc::CddaDoc() noexcept
	: m_state(kNone)
{
	// TODO: 在此添加一次性构造代码

}

CddaDoc::~CddaDoc()
{
	for (ObjectIt it = m_objects.begin(); it != m_objects.end(); it++)
	{
		delete *it;
	}
	m_objects.clear();
}

BOOL CddaDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CddaDoc 序列化

void CddaDoc::Serialize(CArchive& ar)
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
void CddaDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CddaDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CddaDoc::SetSearchContent(const CString& value)
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

// CddaDoc 诊断

#ifdef _DEBUG
void CddaDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CddaDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CddaDoc 命令

void CddaDoc::OnLineDda()
{
	m_state = kGetFirstPoint;
	POSITION pos = GetFirstViewPosition();
	CddaView* pView = (CddaView*)GetNextView(pos);
	pView->getPoint(this);
}

void CddaDoc::onGetPoint(const CGePoint& pnt)
{
	if (m_state == kGetFirstPoint)
	{
		m_point = pnt;

		m_state = kGetSecondPoint;
		POSITION pos = GetFirstViewPosition();
		CddaView* pView = (CddaView*)GetNextView(pos);
		pView->getPoint(this);
	}
	else if (m_state == kGetSecondPoint)
	{
		m_state = kNone;
		CDbLine* line = new CDbLine(m_point, pnt);
		m_objects.push_back(line);
		UpdateAllViews(NULL);
	}
}
