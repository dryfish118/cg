
// ddaView.h: CddaView 类的接口
//

#pragma once

class CddaDoc;

class CGetPointCallback
{
public:
	virtual void onGetPoint(const CGePoint& pnt) = 0;
};

class CddaView : public CView
{
protected: // 仅从序列化创建
	CddaView() noexcept;
	DECLARE_DYNCREATE(CddaView)

// 特性
public:
	CddaDoc* GetDocument() const;

// 操作
public:
	void getPoint(CGetPointCallback* cb);

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CddaView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	bool m_lButtonDown;
	CGetPointCallback* m_cb;

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
};

#ifndef _DEBUG  // ddaView.cpp 中的调试版本
inline CddaDoc* CddaView::GetDocument() const
   { return reinterpret_cast<CddaDoc*>(m_pDocument); }
#endif

