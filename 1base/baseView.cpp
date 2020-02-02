
// baseView.cpp: CbaseView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "base.h"
#endif

#include "baseDoc.h"
#include "baseView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CbaseView

IMPLEMENT_DYNCREATE(CbaseView, CView)

BEGIN_MESSAGE_MAP(CbaseView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()

// CbaseView 构造/析构

CbaseView::CbaseView() noexcept
	: m_lButtonDown(false)
	, m_cb(NULL)
{
	// TODO: 在此处添加构造代码

}

CbaseView::~CbaseView()
{
}

BOOL CbaseView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CbaseView 绘图

#include "ViewDrawDevice.h"

void CbaseView::OnDraw(CDC* pDC)
{
	CbaseDoc* pDoc = GetDocument();
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


// CbaseView 诊断

#ifdef _DEBUG
void CbaseView::AssertValid() const
{
	CView::AssertValid();
}

void CbaseView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CbaseDoc* CbaseView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CbaseDoc)));
	return (CbaseDoc*)m_pDocument;
}
#endif //_DEBUG


// CbaseView 消息处理程序

void CbaseView::getPoint(CGetPointCallback* cb)
{
	m_cb = cb;
}


void CbaseView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_cb)
	{
		OutputDebugString(L"\n OnLButtonDown");

		SetCapture();
		m_lButtonDown = true;
	}

	CView::OnLButtonDown(nFlags, point);
}


void CbaseView::OnLButtonUp(UINT nFlags, CPoint point)
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


void CbaseView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_lButtonDown)
	{
		OutputDebugString(L"\n OnMouseMove");

		ReleaseCapture();
		m_lButtonDown = false;
	}

	CView::OnMouseMove(nFlags, point);
}


void CbaseView::OnKillFocus(CWnd* pNewWnd)
{
	CView::OnKillFocus(pNewWnd);

	if (m_lButtonDown)
	{
		OutputDebugString(L"\n OnKillFocus");

		ReleaseCapture();
		m_lButtonDown = false;
	}
}
