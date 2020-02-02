
// ddaView.cpp: CddaView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "dda.h"
#endif

#include "ddaDoc.h"
#include "ddaView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CddaView

IMPLEMENT_DYNCREATE(CddaView, CView)

BEGIN_MESSAGE_MAP(CddaView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()

// CddaView 构造/析构

CddaView::CddaView() noexcept
	: m_lButtonDown(false)
	, m_cb(NULL)
{
	// TODO: 在此处添加构造代码

}

CddaView::~CddaView()
{
}

BOOL CddaView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CddaView 绘图

#include "ViewDrawDevice.h"

void CddaView::OnDraw(CDC* pDC)
{
	CddaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect rect;
	GetClientRect(&rect);

	int cols = rect.Width() / GRIPSIZE;
	int rows = rect.Height() / GRIPSIZE;
	for (int i = 1; i <= cols; i++)
	{
		pDC->MoveTo(i * GRIPSIZE, 0);
		pDC->LineTo(i * GRIPSIZE, rect.Height());
	}
	for (int i = 1; i <= rows; i++)
	{
		pDC->MoveTo(0, i * GRIPSIZE);
		pDC->LineTo(rect.Width(), i * GRIPSIZE);
	}

	CViewDrawDevice vdd;
	vdd.m_pDC = pDC;
	vdd.m_cols = cols;
	vdd.m_rows = rows;
	for (ObjectIt it = pDoc->m_objects.begin(); it != pDoc->m_objects.end(); it++)
	{
		(*it)->onDraw(&vdd);
	}
}


// CddaView 诊断

#ifdef _DEBUG
void CddaView::AssertValid() const
{
	CView::AssertValid();
}

void CddaView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CddaDoc* CddaView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CddaDoc)));
	return (CddaDoc*)m_pDocument;
}
#endif //_DEBUG


// CddaView 消息处理程序

void CddaView::getPoint(CGetPointCallback* cb)
{
	m_cb = cb;
}


void CddaView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_cb)
	{
		OutputDebugString(L"\n OnLButtonDown");

		SetCapture();
		m_lButtonDown = true;
	}

	CView::OnLButtonDown(nFlags, point);
}


void CddaView::OnLButtonUp(UINT nFlags, CPoint point)
{
	ReleaseCapture();

	if (m_lButtonDown)
	{
		OutputDebugString(L"\n OnLButtonUp");

		m_lButtonDown = false;
		if (m_cb)
		{
			CGetPointCallback* cb = m_cb;
			m_cb = NULL;

			CGePoint pt;
			pt.m_x = point.x / GRIPSIZE;
			pt.m_y = point.y / GRIPSIZE;
			cb->onGetPoint(pt);
		}
	}
	else
	{
		m_cb = NULL;
	}

	CView::OnLButtonUp(nFlags, point);
}


void CddaView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_lButtonDown)
	{
		OutputDebugString(L"\n OnMouseMove");

		ReleaseCapture();
		m_lButtonDown = false;
	}

	CView::OnMouseMove(nFlags, point);
}


void CddaView::OnKillFocus(CWnd* pNewWnd)
{
	CView::OnKillFocus(pNewWnd);

	if (m_lButtonDown)
	{
		OutputDebugString(L"\n OnKillFocus");

		ReleaseCapture();
		m_lButtonDown = false;
	}
}
